#include <iostream>
#include <sstream>
#include <string>

#include <msgpack.hpp>

// /usr/include/poppler/...
#include <GfxFont.h>
#include <GfxState.h>
#include <OutputDev.h>

#include "util.hpp"

const int EO_FILL = 10;
const int STROKE = 11;
const int FILL = 12;
const int SET_STROKE_COLOR = 13;
const int SET_STROKE_WIDTH = 14;
const int SET_FILL_COLOR = 15;

typedef struct { double x, y; } Point;

class Mat2x3 {
  const double *m;

public:
  Mat2x3(const double m[6]) : m(m) {}

  inline const Point mul(const double x, const double y) const {
    auto xt = x * m[0] + y * m[2] + m[4];
    auto yt = x * m[1] + y * m[3] + m[5];
    return Point{xt, yt};
  }
};

class PathPoint {
public:
  PathPoint(double x, double y) : line(x, y), is_curve(false) {}
  PathPoint(double a, double b, double c, double d, double e, double f)
      : curve(a, b, c, d, e, f), is_curve(true) {}

  std::tuple<double, double> line;
  std::tuple<double, double, double, double, double, double> curve;

  bool is_curve;

  void msgpack_pack(msgpack::packer<std::basic_ostream<char>> &pk) const {
    if (is_curve) {
      pk.pack(curve);
    } else {
      pk.pack(line);
    }
  }
};

bool operator!=(const GfxRGB &a, const GfxRGB &b) {
  return !(a.r == b.r && a.g == b.g && a.b == b.b);
}


namespace msgpack {
MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
namespace adaptor {

template <>
struct pack<GfxRGB> {
  template <typename Stream>
  msgpack::packer<Stream>& operator()(msgpack::packer<Stream>& p, GfxRGB const &color) const {
    auto c = [](const GfxColorComp x) -> uint8_t {
      // 255 * x + 0.5  =  256 * x - x + 0x8000
      return static_cast<uint8_t>(((x << 8) - x + 0x8000) >> 16);
    };
    p.pack_array(3);
    p.pack_fix_uint8(c(color.r));
    p.pack_fix_uint8(c(color.g));
    p.pack_fix_uint8(c(color.b));
    return p;
  }
};

} // namespace adaptor
} // MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS)
} // namespace msgpack


class DumpPathsAsMsgPackDev : public OutputDev {
public:
  DumpPathsAsMsgPackDev() : packer(buffer), path_count(0) {}

  std::ostringstream buffer;
  msgpack::packer<std::ostream> packer;
  int path_count;

  GfxRGB prevFillRGB = {0, 0, 0}, prevStrokeRGB = {0, 0, 0};
  double prevStrokeWidth;

public:
  // Writes the packed path information to a stream.
  //
  // The `packer` is initialized with a `buffer`
  // when an instance of `DumpAsMsgPackDev` is created.
  // The path information is written to the `packer` and
  // the packed data is in this method streamed to `out`.
  void pack(std::ostream &out) {
    msgpack::packer<std::ostream>(out).pack_array(path_count);
    out << buffer.str();
  }

  GBool upsideDown() { return gTrue; }
  GBool useDrawChar() { return gTrue; }
  GBool interpretType3Chars() { return gTrue; }

  void eoFill(GfxState *state) {
    doPath(state, state->getCTM(), state->getPath(), EO_FILL);
  }

  void stroke(GfxState *state) {
    doPath(state, state->getCTM(), state->getPath(), STROKE);
  }

  void fill(GfxState *state) {
    doPath(state, state->getCTM(), state->getPath(), FILL);
  }

  void recordStateChanges(GfxState *state, int path_type) {
    switch (path_type) {

      case FILL:
      case EO_FILL:
        GfxRGB curFillRGB;
        state->getFillRGB(&curFillRGB);
        if (prevFillRGB != curFillRGB) {
          prevFillRGB = curFillRGB;
          packer.pack_array(2);
          packer.pack_fix_uint8(SET_FILL_COLOR);
          packer.pack(curFillRGB);
          path_count++;
        }

        // break;
        // Fallthrough. Strokes apply to fills, too.

      case STROKE:
        GfxRGB curStrokeRGB;
        state->getStrokeRGB(&curStrokeRGB);
        if (prevStrokeRGB != curStrokeRGB) {
          prevStrokeRGB = curStrokeRGB;
          packer.pack_array(2);
          packer.pack_fix_uint8(SET_STROKE_COLOR);
          packer.pack(curStrokeRGB);
          path_count++;
        }

        double curStrokeWidth;
        curStrokeWidth = state->getLineWidth();
        if (prevStrokeWidth != curStrokeWidth) {
          prevStrokeWidth = curStrokeWidth;
          packer.pack(std::make_tuple(SET_STROKE_WIDTH, curStrokeWidth));
          path_count++;
        }

        break;

      default:
        std::cerr << "unknown path type: " << path_type << std::endl;

    }
  }

  void doPath(GfxState *state, const Mat2x3 &transform, GfxPath *path, int path_type) {
    recordStateChanges(state, path_type);

    auto n = path->getNumSubpaths();

    for (auto i = 0; i < n; ++i) {
      auto subpath = path->getSubpath(i);
      auto m = subpath->getNumPoints();
      auto j = 0;

      std::vector<PathPoint> path_points;
      while (j < m) {
        if (subpath->getCurve(j)) {
          auto a = transform.mul(subpath->getX(j + 0), subpath->getY(j + 0)),
               b = transform.mul(subpath->getX(j + 1), subpath->getY(j + 1)),
               c = transform.mul(subpath->getX(j + 2), subpath->getY(j + 2));

          path_points.push_back(PathPoint(a.x, a.y, b.x, b.y, c.x, c.y));
        } else {
          auto x = subpath->getX(j), y = subpath->getY(j);

          auto t = transform.mul(x, y);
          path_points.push_back(PathPoint(t.x, t.y));
        }
        ++j;
      }

      if (!path_points.empty()) {
        if (subpath->isClosed()) {
          path_points.push_back(path_points[0]);
        }
        packer.pack(std::make_tuple(path_type, path_points));
        path_count++;
      }
    }
  }
};

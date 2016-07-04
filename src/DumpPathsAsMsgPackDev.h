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

class DumpPathsAsMsgPackDev : public OutputDev {
public:
  DumpPathsAsMsgPackDev() : packer(buffer), path_count(0) {}

  std::ostringstream buffer;
  msgpack::packer<std::ostream> packer;
  int path_count;

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
    doPath(state->getCTM(), state->getPath(), EO_FILL);
  }

  void stroke(GfxState *state) {
    doPath(state->getCTM(), state->getPath(), STROKE);
  }

  void fill(GfxState *state) {
    doPath(state->getCTM(), state->getPath(), FILL);
  }

  void doPath(const Mat2x3 &transform, GfxPath *path, int path_type) {
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

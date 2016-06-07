#include <iostream>
#include <sstream>
#include <string>

#include <msgpack.hpp>
#include <poppler/OutputDev.h>
#include <poppler/GfxState.h>
#include <poppler/GfxFont.h>

#include "util.hpp"

const int LINE_TO = 0;
const int CURVE_TO = 1;

const int EO_FILL = 10;
const int STROKE = 11;
const int FILL = 12;

typedef struct {
  double x, y;
} Point;

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

  void doPath(const Mat2x3 &transform, GfxPath *path, int pathType) {
    auto n = path->getNumSubpaths();

    for (auto i = 0; i < n; ++i) {
      auto subpath = path->getSubpath(i);
      auto m = subpath->getNumPoints();

      auto j = 1;
      std::vector<std::tuple<double, double>> aggregated_line_to;
      std::vector<std::tuple<double, double, double, double, double, double>> aggregated_curve_to;
      while (j < m) {
        if (subpath->getCurve(j)) {

          auto a = transform.mul(subpath->getX(j+0), subpath->getY(j+0)),
               b = transform.mul(subpath->getX(j+1), subpath->getY(j+1)),
               c = transform.mul(subpath->getX(j+2), subpath->getY(j+2));

          auto curve = std::make_tuple(a.x, a.y, b.x, b.y, c.x, c.y);
          aggregated_curve_to.push_back(curve);
        } else {
          auto x = subpath->getX(j),
               y = subpath->getY(j);

          auto t = transform.mul(x, y);
          auto line = std::make_tuple(t.x, t.y);
          aggregated_line_to.push_back(line);
        }
        ++j;
      }
      if (subpath->isClosed()) {
        if (!aggregated_line_to.empty()) {
          aggregated_line_to.push_back(aggregated_line_to[0]);
        }
      }
      if (!aggregated_line_to.empty()) {
        auto path = std::make_tuple(pathType, LINE_TO, aggregated_line_to);
        packer.pack(path);
        path_count++;
      }
      if (!aggregated_curve_to.empty()) {
        auto path = std::make_tuple(pathType, CURVE_TO, aggregated_curve_to);
        packer.pack(path);
        path_count++;
      }
    }
  }

};

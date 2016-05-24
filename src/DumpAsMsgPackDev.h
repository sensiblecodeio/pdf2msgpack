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

class DumpAsMsgPackDev : public OutputDev {
public:
  DumpAsMsgPackDev() : packer(buffer), path_count(0) {}

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

  GBool upsideDown() { return gFalse; }
  GBool useDrawChar() { return gTrue; }
  GBool interpretType3Chars() { return gTrue; }

  void eoFill(GfxState *state) {
    doPath(state->getPath(), EO_FILL);
  }

  void stroke(GfxState *state) {
    doPath(state->getPath(), STROKE);
  }

  void fill(GfxState *state) {
    doPath(state->getPath(), FILL);
  }

  void doPath(GfxPath *path, int pathType) {
    auto n = path->getNumSubpaths();

    for (auto i = 0; i < n; ++i) {
      auto subpath = path->getSubpath(i);
      auto m = subpath->getNumPoints();

      auto j = 1;
      while (j < m) {
        if (subpath->getCurve(j)) {
          path_count++;
          auto a = subpath->getX(j),
               b = subpath->getY(j),
               c = subpath->getX(j+1),
               d = subpath->getY(j+1),
               e = subpath->getX(j+2),
               f = subpath->getY(j+2);

          packer.pack(std::make_tuple(pathType, CURVE_TO, a, b, c, d, e, f));
          j += 3;
        } else {
          path_count++;
          auto x = subpath->getX(j),
               y = subpath->getY(j);
          packer.pack(std::make_tuple(pathType, LINE_TO, x, y));
          ++j;
        }
      }
      if (subpath->isClosed()) {
        // perform action if subpath is closed
      }
    }
  }

};

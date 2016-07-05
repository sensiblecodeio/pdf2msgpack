#include <OutputDev.h>

class DumpGlyphsNew : public OutputDev {
public:
  std::ostringstream buffer;
  msgpack::packer<std::ostream> packer;
  int count;

public:
  // Writes the packed path information to a stream.
  //
  // The `packer` is initialized with a `buffer`
  // when an instance of `DumpAsMsgPackDev` is created.
  // The path information is written to the `packer` and
  // the packed data is in this method streamed to `out`.
  void pack(std::ostream &out) {
    msgpack::packer<std::ostream>(out).pack_array(count);
    out << buffer.str();
  }

  DumpGlyphsNew() : packer(buffer), count(0) {}

  GBool upsideDown() { return gTrue; }
  GBool useDrawChar() { return gTrue; }
  GBool interpretType3Chars() { return gTrue; }

  void drawChar(GfxState *state, double x, double y,
  			     double dx, double dy,
  			     double originX, double originY,
  			     CharCode c, int nBytes, Unicode *u, int uLen) {

    auto s = toUTF8(u, uLen);

    auto font = state->getFont();
    double *m = state->getTextMat();
    auto tm = std::make_tuple(m[0], m[1], m[2], m[3], m[4], m[5]);

    packer.pack(std::make_tuple(tm, x, y, dx, dy, originX, originY, s));
    count++;
  }
};

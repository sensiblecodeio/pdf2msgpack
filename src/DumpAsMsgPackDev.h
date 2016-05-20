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

bool equal(const GfxRGB &left, const GfxRGB &right) {
    return left.r == right.r && left.g == right.g && left.b == right.b;
}

class DumpAsMsgPackDev : public OutputDev {
public:
  GfxFont *lastFont;
  GfxRGB prev;

  DumpAsMsgPackDev() : packer(buffer), path_count(0) {}

  std::stringstream buffer;
  msgpack::packer<std::ostream> packer;
  int path_count;

public:

  void pack(std::ostream &out) {
    msgpack::packer<std::ostream>(out).pack_array(path_count);
    out << buffer.rdbuf();
  }

  GBool upsideDown() { return gFalse; }
  GBool useDrawChar() { return gTrue; }
  GBool interpretType3Chars() { return gTrue; }

  void updateStrokeColor(GfxState *state) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);

    if (!equal(prev, rgb)) {
        // printf("New stroke color: %d %d %d\n", rgb.r, rgb.g, rgb.b);
        prev = rgb;
    }
  }

  void updateFillColor(GfxState *state) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    // printf("New fill color: %d %d %d\n", rgb.r, rgb.g, rgb.b);
  }

  void updateFont(GfxState *state) {
    auto font = state->getFont();
    if (font == NULL)
      return;
    if (font == lastFont)
      return;
    lastFont = font;
    // printf("New font: %s\n", font->getName()->getCString());
  }

  void updateTextMat(GfxState *state) {
    // printf("updateTextMat()\n");

  }

  void updateRender(GfxState *state) {
    // printf("updateRender()\n");
  }

  void updateRise(GfxState *) {
    // printf("updateRise()\n");
  }

  void drawCharDisabled(
      GfxState *state,
      double x, double y,
      double dx, double dy,
      double originX, double originY,
      CharCode code, int nBytes, Unicode *u, int uLen
  ) {
    auto utf8 = toUTF8(std::u32string(reinterpret_cast<char32_t*>(u), uLen));

    double m[4];
    state->getFontTransMat(&m[0], &m[1], &m[2], &m[3]);


    double size = state->getFontSize();

    msgpack::type::tuple<double, double, double, double, double, double, std::string, double, double, double, double, double> //, CharCode, int>
      msg(x, y, dx, dy, originX, originY, utf8, m[0], m[1], m[2], m[3], size); //, code, nBytes);

    packer.pack(msg);
  }

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
          auto a = subpath->getX(j),
               b = subpath->getY(j);
          packer.pack(std::make_tuple(pathType, LINE_TO, a, b));
          ++j;
        }
      }
      if (subpath->isClosed()) {
        // perform action if subpath is closed
      }
    }
  }


  void drawImageMask(GfxState *state, Object *ref, Stream *str,
           int width, int height, GBool invert, GBool interpolate,
           GBool inlineImg) {
    // printf("drawImageMask()\n");
  }

  void setSoftMaskFromImageMask(GfxState *state,
          Object *ref, Stream *str,
          int width, int height, GBool invert,
          GBool inlineImg, double *baseMatrix) {
    // printf("setSoftMaskFromImageMask()\n");
  }

  void unsetSoftMaskFromImageMask(GfxState *state, double *baseMatrix) {
    // printf("unsetSoftMaskFromImageMask()\n");
  }

  void drawImage(GfxState *state, Object *ref, Stream *str,
       int width, int height, GfxImageColorMap *colorMap,
       GBool interpolate, int *maskColors, GBool inlineImg) {
    // printf("drawImage()\n");
  }

  void drawMaskedImage(GfxState *state, Object *ref, Stream *str,
             int width, int height,
             GfxImageColorMap *colorMap, GBool interpolate,
             Stream *maskStr, int maskWidth, int maskHeight,
             GBool maskInvert, GBool maskInterpolate) {
    // printf("drawMaskedImage()\n");
  }

  void drawSoftMaskedImage(GfxState *state, Object *ref, Stream *str,
           int width, int height,
           GfxImageColorMap *colorMap,
           GBool interpolate,
           Stream *maskStr,
           int maskWidth, int maskHeight,
           GfxImageColorMap *maskColorMap,
           GBool maskInterpolate) {
    // printf("drawSoftMaskedImage()\n");
  }

};

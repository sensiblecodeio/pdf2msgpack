#include <iostream>

#include <msgpack.hpp>
#include <poppler/OutputDev.h>
#include <poppler/GfxState.h>
#include <poppler/GfxFont.h>

msgpack::packer<std::ostream> packer(&std::cout);

class DumpAsMsgPackDev : public OutputDev {
public:
  GfxFont *lastFont;

public:

  GBool upsideDown() { return gTrue; }
  GBool useDrawChar() { return gTrue; }
  GBool interpretType3Chars() { return gTrue; }

  void updateStrokeColor(GfxState *state) {
    GfxRGB rgb;
    state->getStrokeRGB(&rgb);
    printf("New stroke color: %d %d %d\n", rgb.r, rgb.g, rgb.b);
  }

  void updateFillColor(GfxState *state) {
    GfxRGB rgb;
    state->getFillRGB(&rgb);
    printf("New fill color: %d %d %d\n", rgb.r, rgb.g, rgb.b);
  }

  void updateFont(GfxState *state) {
    auto font = state->getFont();
    if (font == NULL)
      return;
    if (font == lastFont)
      return;
    lastFont = font;
    printf("New font: %s\n", font->getName()->getCString());
  }

  void updateTextMat(GfxState *state) {
    printf("updateTextMat()\n");
  }

  void updateRender(GfxState *state) {
    printf("updateRender()\n");
  }

  void updateRise(GfxState *) {
    printf("updateRise()\n");
  }

  void drawChar(
      GfxState *state,
      double x, double y,
      double dx, double dy,
      double originX, double originY,
      CharCode code, int nBytes, Unicode *u, int uLen
  ) {
    printf("char %d %c\n", code, char(int(*u)));

    // msgpack::type::tuple<double, double, double, double, double, double> //, CharCode, int>
    //   msg(x, y, dx, dy, originX, originY); //, code, nBytes);
    //
    // packer.pack_array(2);
    // packer.pack(msg);
    //
    // packer.pack_array(uLen);
    // for (int i = 0; i < uLen; i++)
    //   packer.pack(u[i]);
  }

  void stroke(GfxState *state) {
    printf("stroke\n");
    doPath(state->getPath());
  }


  void fill(GfxState *state) {
    printf("fill\n");
    doPath(state->getPath());
  }

  void doPath(GfxPath *path) {
    auto n = path->getNumSubpaths();

    for (auto i = 0; i < n; ++i) {
      auto subpath = path->getSubpath(i);
      auto m = subpath->getNumPoints();

      printf("  start %f %f\n", subpath->getX(0), subpath->getY(0));
      auto j = 1;
      while (j < m) {
        if (subpath->getCurve(j)) {
          printf("   point %f %f %f %f %f %f c\n",
          subpath->getX(j), subpath->getY(j),
          subpath->getX(j+1), subpath->getY(j+1),
          subpath->getX(j+2), subpath->getY(j+2));
          j += 3;
        } else {
          printf("  end %f %f l\n", subpath->getX(j), subpath->getY(j));
          ++j;
        }
      }
      if (subpath->isClosed()) {
        printf("  closed\n");
      }
    }
  }


  void drawImageMask(GfxState *state, Object *ref, Stream *str,
           int width, int height, GBool invert, GBool interpolate,
           GBool inlineImg) {
    printf("drawImageMask()\n");
  }

  void setSoftMaskFromImageMask(GfxState *state,
          Object *ref, Stream *str,
          int width, int height, GBool invert,
          GBool inlineImg, double *baseMatrix) {
    printf("setSoftMaskFromImageMask()\n");
  }

  void unsetSoftMaskFromImageMask(GfxState *state, double *baseMatrix) {
    printf("unsetSoftMaskFromImageMask()\n");
  }

  void drawImage(GfxState *state, Object *ref, Stream *str,
       int width, int height, GfxImageColorMap *colorMap,
       GBool interpolate, int *maskColors, GBool inlineImg) {
    printf("drawImage()\n");
  }

  void drawMaskedImage(GfxState *state, Object *ref, Stream *str,
             int width, int height,
             GfxImageColorMap *colorMap, GBool interpolate,
             Stream *maskStr, int maskWidth, int maskHeight,
             GBool maskInvert, GBool maskInterpolate) {
    printf("drawMaskedImage()\n");
  }

  void drawSoftMaskedImage(GfxState *state, Object *ref, Stream *str,
           int width, int height,
           GfxImageColorMap *colorMap,
           GBool interpolate,
           Stream *maskStr,
           int maskWidth, int maskHeight,
           GfxImageColorMap *maskColorMap,
           GBool maskInterpolate) {
    printf("drawSoftMaskedImage()\n");
  }

};

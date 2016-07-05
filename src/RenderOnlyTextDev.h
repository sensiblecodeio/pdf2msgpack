class RenderOnlyTextDev : public SplashOutputDev {
public:
  using SplashOutputDev::SplashOutputDev;

  //----- path painting
  virtual void stroke(GfxState *) {}
  virtual void fill(GfxState *) {}
  virtual void eoFill(GfxState *) {}
  virtual GBool tilingPatternFill(GfxState *, Gfx *, Catalog *, Object *,
                                  double *, int, int, Dict *, double *,
                                  double *, int, int, int, int, double,
                                  double) {
    return gTrue;
  }
  virtual GBool functionShadedFill(GfxState *, GfxFunctionShading *) {
    return gTrue;
  }
  virtual GBool axialShadedFill(GfxState *, GfxAxialShading *, double, double) {
    return gTrue;
  }
  virtual GBool radialShadedFill(GfxState *, GfxRadialShading *, double,
                                 double) {
    return gTrue;
  }
  virtual GBool gouraudTriangleShadedFill(GfxState *,
                                          GfxGouraudTriangleShading *) {
    return gTrue;
  }

  //----- image drawing
  virtual void drawImageMask(GfxState *, Object *, Stream *, int, int, GBool,
                             GBool, GBool) {}
  virtual void setSoftMaskFromImageMask(GfxState *, Object *, Stream *, int,
                                        int, GBool, GBool, double *) {}
  virtual void unsetSoftMaskFromImageMask(GfxState *, double *) {}
  virtual void drawImage(GfxState *, Object *, Stream *, int, int,
                         GfxImageColorMap *, GBool, int *, GBool) {}
  virtual void drawMaskedImage(GfxState *, Object *, Stream *, int, int,
                               GfxImageColorMap *, GBool, Stream *, int, int,
                               GBool, GBool) {}
  virtual void drawSoftMaskedImage(GfxState *, Object *, Stream *, int, int,
                                   GfxImageColorMap *, GBool, Stream *, int,
                                   int, GfxImageColorMap *, GBool) {}

  virtual void drawChar(GfxState *state, double x, double y, double dx,
                        double dy, double originX, double originY,
                        CharCode code, int nBytes, Unicode *u, int uLen) {
    double xx, yy;
    // cvtUserToDev(x, y, &xx, &yy);
    state->transform(x, y, &xx, &yy);

    double w1, h1, dx2, dy2, sp;
    // subtract char and word spacing from the dx,dy values
    sp = state->getCharSpace();
    if (code == (CharCode)0x20) {
      sp += state->getWordSpace();
    }
    state->textTransformDelta(sp * state->getHorizScaling(), 0, &dx2, &dy2);
    dx -= dx2;
    dy -= dy2;
    state->transformDelta(dx, dy, &w1, &h1);

    std::cerr << "Char " << char(code) << " -- " << x << ", " << y << " - "
              << xx << ", " << yy << " -- " << w1 << std::endl;

    // auto *b = getSplash()->getBitmap();
    // auto *data = reinterpret_cast<char *>(b->getDataPtr());
    // data[int(yy) * b->getRowSize() + int(xx)] = 0x80;

    SplashColor paperColor;
    paperColor[0] = 128;
    paperColor[1] = 128;
    paperColor[2] = 128;
    paperColor[3] = 128;

    getSplash()->clear(paperColor);
    // SplashOutputDev::drawChar(state, x, y, dx, dy, originX, originY, code,
    //                           nBytes, u, uLen);
  }
};

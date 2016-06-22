#include <poppler/GfxFont.h>
#include <poppler/GfxState.h>
#include <poppler/OutputDev.h>

#include "util.hpp"

// Automatically generated, lists all functions and their prototypes.
// (Or see poppler/OutputDev.h).
class DumpAsTextDev : public OutputDev {
public:
  GBool upsideDown() { return gTrue; }

  GBool useDrawChar() { return gTrue; }

  GBool useTilingPatternFill() {
    printf("useTilingPatternFill\n");
    return OutputDev::useTilingPatternFill();
  }

  GBool useShadedFills(int type) {
    printf("useShadedFills\n");
    return OutputDev::useShadedFills(type);
  }

  GBool useFillColorStop() {
    printf("useFillColorStop\n");
    return OutputDev::useFillColorStop();
  }

  GBool useDrawForm() {
    printf("useDrawForm\n");
    return OutputDev::useDrawForm();
  }

  GBool interpretType3Chars() {
    printf("interpretType3Chars\n");
    return gTrue;
  }

  GBool needNonText() {
    printf("needNonText\n");
    return OutputDev::needNonText();
  }

  GBool needCharCount() {
    printf("needCharCount\n");
    return OutputDev::needCharCount();
  }

  GBool needClipToCropBox() {
    printf("needClipToCropBox\n");
    return OutputDev::needClipToCropBox();
  }

  void setDefaultCTM(double *ctm) {
    printf("setDefaultCTM\n");
    return OutputDev::setDefaultCTM(ctm);
  }

  GBool checkPageSlice(Page *page, double hDPI, double vDPI, int rotate,
                       GBool useMediaBox, GBool crop, int sliceX, int sliceY,
                       int sliceW, int sliceH, GBool printing,
                       GBool (*abortCheckCbk)(void *), void *abortCheckCbkData,
                       GBool (*annotDisplayDecideCbk)(Annot *, void *),
                       void *annotDisplayDecideCbkData) {
    printf("checkPageSlice\n");
    return OutputDev::checkPageSlice(
        page, hDPI, vDPI, rotate, useMediaBox, crop, sliceX, sliceY, sliceW,
        sliceH, printing, abortCheckCbk, abortCheckCbkData,
        annotDisplayDecideCbk, annotDisplayDecideCbkData);
  }

  void startPage(int pageNum, GfxState *state, XRef *xref) {
    printf("startPage\n");
    return OutputDev::startPage(pageNum, state, xref);
  }

  void endPage() {
    printf("endPage\n");
    return OutputDev::endPage();
  }

  void dump() {
    printf("dump\n");
    return OutputDev::dump();
  }

  void cvtDevToUser(double dx, double dy, double *ux, double *uy) {
    printf("cvtDevToUser\n");
    return OutputDev::cvtDevToUser(dx, dy, ux, uy);
  }

  void cvtUserToDev(double ux, double uy, int *dx, int *dy) {
    printf("cvtUserToDev\n");
    return OutputDev::cvtUserToDev(ux, uy, dx, dy);
  }

  double *getDefCTM() {
    printf("getDefCTM\n");
    return OutputDev::getDefCTM();
  }

  double *getDefICTM() {
    printf("getDefICTM\n");
    return OutputDev::getDefICTM();
  }

  void saveState(GfxState *A) {
    printf("saveState\n");
    return OutputDev::saveState(A);
  }

  void restoreState(GfxState *A) {
    printf("restoreState\n");
    return OutputDev::restoreState(A);
  }

  void updateAll(GfxState *state) {
    printf("updateAll\n");
    return OutputDev::updateAll(state);
  }

  void updateCTM(GfxState *A, double B, double C, double D, double E, double F,
                 double G) {
    printf("updateCTM\n");
    return OutputDev::updateCTM(A, B, C, D, E, F, G);
  }

  void updateLineDash(GfxState *A) {
    printf("updateLineDash\n");
    return OutputDev::updateLineDash(A);
  }

  void updateFlatness(GfxState *A) {
    printf("updateFlatness\n");
    return OutputDev::updateFlatness(A);
  }

  void updateLineJoin(GfxState *A) {
    printf("updateLineJoin\n");
    return OutputDev::updateLineJoin(A);
  }

  void updateLineCap(GfxState *A) {
    printf("updateLineCap\n");
    return OutputDev::updateLineCap(A);
  }

  void updateMiterLimit(GfxState *A) {
    printf("updateMiterLimit\n");
    return OutputDev::updateMiterLimit(A);
  }

  void updateLineWidth(GfxState *A) {
    printf("updateLineWidth\n");
    return OutputDev::updateLineWidth(A);
  }

  void updateStrokeAdjust(GfxState *A) {
    printf("updateStrokeAdjust\n");
    return OutputDev::updateStrokeAdjust(A);
  }

  void updateAlphaIsShape(GfxState *A) {
    printf("updateAlphaIsShape\n");
    return OutputDev::updateAlphaIsShape(A);
  }

  void updateTextKnockout(GfxState *A) {
    printf("updateTextKnockout\n");
    return OutputDev::updateTextKnockout(A);
  }

  void updateFillColorSpace(GfxState *A) {
    printf("updateFillColorSpace\n");
    return OutputDev::updateFillColorSpace(A);
  }

  void updateStrokeColorSpace(GfxState *A) {
    printf("updateStrokeColorSpace\n");
    return OutputDev::updateStrokeColorSpace(A);
  }

  void updateFillColor(GfxState *A) {
    printf("updateFillColor\n");
    return OutputDev::updateFillColor(A);
  }

  void updateStrokeColor(GfxState *A) {
    printf("updateStrokeColor\n");
    return OutputDev::updateStrokeColor(A);
  }

  void updateBlendMode(GfxState *A) {
    printf("updateBlendMode\n");
    return OutputDev::updateBlendMode(A);
  }

  void updateFillOpacity(GfxState *A) {
    printf("updateFillOpacity\n");
    return OutputDev::updateFillOpacity(A);
  }

  void updateStrokeOpacity(GfxState *A) {
    printf("updateStrokeOpacity\n");
    return OutputDev::updateStrokeOpacity(A);
  }

  //
  // void updatePatternOpacity(GfxState * A) {
  //   printf("updatePatternOpacity\n");
  //   return OutputDev::updatePatternOpacity(A);
  // }
  //
  //
  // void clearPatternOpacity(GfxState * A) {
  //   printf("clearPatternOpacity\n");
  //   return OutputDev::clearPatternOpacity(A);
  // }

  void updateFillOverprint(GfxState *A) {
    printf("updateFillOverprint\n");
    return OutputDev::updateFillOverprint(A);
  }

  void updateStrokeOverprint(GfxState *A) {
    printf("updateStrokeOverprint\n");
    return OutputDev::updateStrokeOverprint(A);
  }

  void updateOverprintMode(GfxState *A) {
    printf("updateOverprintMode\n");
    return OutputDev::updateOverprintMode(A);
  }

  void updateTransfer(GfxState *A) {
    printf("updateTransfer\n");
    return OutputDev::updateTransfer(A);
  }

  void updateFillColorStop(GfxState *A, double B) {
    printf("updateFillColorStop\n");
    return OutputDev::updateFillColorStop(A, B);
  }

  void updateFont(GfxState *A) {
    printf("updateFont\n");
    return OutputDev::updateFont(A);
  }

  void updateTextMat(GfxState *A) {
    printf("updateTextMat\n");
    return OutputDev::updateTextMat(A);
  }

  void updateCharSpace(GfxState *A) {
    printf("updateCharSpace\n");
    return OutputDev::updateCharSpace(A);
  }

  void updateRender(GfxState *A) {
    printf("updateRender\n");
    return OutputDev::updateRender(A);
  }

  void updateRise(GfxState *A) {
    printf("updateRise\n");
    return OutputDev::updateRise(A);
  }

  void updateWordSpace(GfxState *A) {
    printf("updateWordSpace\n");
    return OutputDev::updateWordSpace(A);
  }

  void updateHorizScaling(GfxState *A) {
    printf("updateHorizScaling\n");
    return OutputDev::updateHorizScaling(A);
  }

  void updateTextPos(GfxState *A) {
    printf("updateTextPos\n");
    return OutputDev::updateTextPos(A);
  }

  void updateTextShift(GfxState *A, double B) {
    printf("updateTextShift\n");
    return OutputDev::updateTextShift(A, B);
  }

  void saveTextPos(GfxState *A) {
    printf("saveTextPos\n");
    return OutputDev::saveTextPos(A);
  }

  void restoreTextPos(GfxState *A) {
    printf("restoreTextPos\n");
    return OutputDev::restoreTextPos(A);
  }

  void stroke(GfxState *A) {
    printf("stroke\n");
    return OutputDev::stroke(A);
  }

  void fill(GfxState *A) {
    printf("fill\n");
    return OutputDev::fill(A);
  }

  void eoFill(GfxState *A) {
    printf("eoFill\n");
    return OutputDev::eoFill(A);
  }

  GBool tilingPatternFill(GfxState *A, Gfx *B, Catalog *C, Object *D, double *E,
                          int F, int G, Dict *H, double *I, double *J, int K,
                          int L, int M, int N, double O, double P) {
    printf("tilingPatternFill\n");
    return OutputDev::tilingPatternFill(A, B, C, D, E, F, G, H, I, J, K, L, M,
                                        N, O, P);
  }

  GBool functionShadedFill(GfxState *A, GfxFunctionShading *B) {
    printf("functionShadedFill\n");
    return OutputDev::functionShadedFill(A, B);
  }

  GBool axialShadedFill(GfxState *A, GfxAxialShading *B, double C, double D) {
    printf("axialShadedFill\n");
    return OutputDev::axialShadedFill(A, B, C, D);
  }

  GBool axialShadedSupportExtend(GfxState *A, GfxAxialShading *B) {
    printf("axialShadedSupportExtend\n");
    return OutputDev::axialShadedSupportExtend(A, B);
  }

  GBool radialShadedFill(GfxState *A, GfxRadialShading *B, double C, double D) {
    printf("radialShadedFill\n");
    return OutputDev::radialShadedFill(A, B, C, D);
  }

  GBool radialShadedSupportExtend(GfxState *A, GfxRadialShading *B) {
    printf("radialShadedSupportExtend\n");
    return OutputDev::radialShadedSupportExtend(A, B);
  }

  GBool gouraudTriangleShadedFill(GfxState *state,
                                  GfxGouraudTriangleShading *shading) {
    printf("gouraudTriangleShadedFill\n");
    return OutputDev::gouraudTriangleShadedFill(state, shading);
  }

  GBool patchMeshShadedFill(GfxState *state, GfxPatchMeshShading *shading) {
    printf("patchMeshShadedFill\n");
    return OutputDev::patchMeshShadedFill(state, shading);
  }

  void clip(GfxState *A) {
    printf("clip\n");
    return OutputDev::clip(A);
  }

  void eoClip(GfxState *A) {
    printf("eoClip\n");
    return OutputDev::eoClip(A);
  }

  void clipToStrokePath(GfxState *A) {
    printf("clipToStrokePath\n");
    return OutputDev::clipToStrokePath(A);
  }

  void beginStringOp(GfxState *A) {
    printf("beginStringOp\n");
    return OutputDev::beginStringOp(A);
  }

  void endStringOp(GfxState *A) {
    printf("endStringOp\n");
    return OutputDev::endStringOp(A);
  }

  void beginString(GfxState *A, GooString *B) {
    printf("beginString\n");
    return OutputDev::beginString(A, B);
  }

  void endString(GfxState *A) {
    printf("endString\n");
    return OutputDev::endString(A);
  }

  void drawChar(GfxState *A, double B, double C, double D, double E, double F,
                double G, CharCode H, int I, Unicode *J, int K) {
    auto s = toUTF8(J, K);
    // printf("drawChar(%s)\n", char(int(*J)));
    std::cout << "drawChar(" << s << ")" << std::endl;
    return OutputDev::drawChar(A, B, C, D, E, F, G, H, I, J, K);
  }

  void drawString(GfxState *A, GooString *B) {
    printf("drawString\n");
    return OutputDev::drawString(A, B);
  }

  GBool beginType3Char(GfxState *A, double B, double C, double D, double E,
                       CharCode F, Unicode *G, int H) {
    printf("beginType3Char\n");
    return OutputDev::beginType3Char(A, B, C, D, E, F, G, H);
  }

  void endType3Char(GfxState *A) {
    printf("endType3Char\n");
    return OutputDev::endType3Char(A);
  }

  void beginTextObject(GfxState *A) {
    printf("beginTextObject\n");
    return OutputDev::beginTextObject(A);
  }

  void endTextObject(GfxState *A) {
    printf("endTextObject\n");
    return OutputDev::endTextObject(A);
  }

  void incCharCount(int A) {
    printf("incCharCount\n");
    return OutputDev::incCharCount(A);
  }

  void beginActualText(GfxState *A, GooString *B) {
    printf("beginActualText\n");
    return OutputDev::beginActualText(A, B);
  }

  void endActualText(GfxState *A) {
    printf("endActualText\n");
    return OutputDev::endActualText(A);
  }

  void drawImageMask(GfxState *state, Object *ref, Stream *str, int width,
                     int height, GBool invert, GBool interpolate,
                     GBool inlineImg) {
    printf("drawImageMask\n");
    return OutputDev::drawImageMask(state, ref, str, width, height, invert,
                                    interpolate, inlineImg);
  }

  void setSoftMaskFromImageMask(GfxState *state, Object *ref, Stream *str,
                                int width, int height, GBool invert,
                                GBool inlineImg, double *baseMatrix) {
    printf("setSoftMaskFromImageMask\n");
    return OutputDev::setSoftMaskFromImageMask(state, ref, str, width, height,
                                               invert, inlineImg, baseMatrix);
  }

  void unsetSoftMaskFromImageMask(GfxState *state, double *baseMatrix) {
    printf("unsetSoftMaskFromImageMask\n");
    return OutputDev::unsetSoftMaskFromImageMask(state, baseMatrix);
  }

  void drawImage(GfxState *state, Object *ref, Stream *str, int width,
                 int height, GfxImageColorMap *colorMap, GBool interpolate,
                 int *maskColors, GBool inlineImg) {
    printf("drawImage\n");
    return OutputDev::drawImage(state, ref, str, width, height, colorMap,
                                interpolate, maskColors, inlineImg);
  }

  void drawMaskedImage(GfxState *state, Object *ref, Stream *str, int width,
                       int height, GfxImageColorMap *colorMap,
                       GBool interpolate, Stream *maskStr, int maskWidth,
                       int maskHeight, GBool maskInvert,
                       GBool maskInterpolate) {
    printf("drawMaskedImage\n");
    return OutputDev::drawMaskedImage(state, ref, str, width, height, colorMap,
                                      interpolate, maskStr, maskWidth,
                                      maskHeight, maskInvert, maskInterpolate);
  }

  void drawSoftMaskedImage(GfxState *state, Object *ref, Stream *str, int width,
                           int height, GfxImageColorMap *colorMap,
                           GBool interpolate, Stream *maskStr, int maskWidth,
                           int maskHeight, GfxImageColorMap *maskColorMap,
                           GBool maskInterpolate) {
    printf("drawSoftMaskedImage\n");
    return OutputDev::drawSoftMaskedImage(
        state, ref, str, width, height, colorMap, interpolate, maskStr,
        maskWidth, maskHeight, maskColorMap, maskInterpolate);
  }

  void endMarkedContent(GfxState *state) {
    printf("endMarkedContent\n");
    return OutputDev::endMarkedContent(state);
  }

  void beginMarkedContent(char *name, Dict *properties) {
    printf("beginMarkedContent\n");
    return OutputDev::beginMarkedContent(name, properties);
  }

  void markPoint(char *name) {
    printf("markPoint\n");
    return OutputDev::markPoint(name);
  }

  void markPoint(char *name, Dict *properties) {
    printf("markPoint\n");
    return OutputDev::markPoint(name, properties);
  }

  void opiBegin(GfxState *state, Dict *opiDict) {
    printf("opiBegin\n");
    return OutputDev::opiBegin(state, opiDict);
  }

  void opiEnd(GfxState *state, Dict *opiDict) {
    printf("opiEnd\n");
    return OutputDev::opiEnd(state, opiDict);
  }

  void type3D0(GfxState *A, double B, double C) {
    printf("type3D0\n");
    return OutputDev::type3D0(A, B, C);
  }

  void type3D1(GfxState *A, double B, double C, double D, double E, double F,
               double G) {
    printf("type3D1\n");
    return OutputDev::type3D1(A, B, C, D, E, F, G);
  }

  void drawForm(Ref A) {
    printf("drawForm\n");
    return OutputDev::drawForm(A);
  }

  void psXObject(Stream *A, Stream *B) {
    printf("psXObject\n");
    return OutputDev::psXObject(A, B);
  }

  void startProfile() {
    printf("startProfile\n");
    return OutputDev::startProfile();
  }

  GooHash *getProfileHash() {
    printf("getProfileHash\n");
    return OutputDev::getProfileHash();
  }

  GooHash *endProfile() {
    printf("endProfile\n");
    return OutputDev::endProfile();
  }

  GBool checkTransparencyGroup(GfxState *A, GBool B) {
    printf("checkTransparencyGroup\n");
    return OutputDev::checkTransparencyGroup(A, B);
  }

  void beginTransparencyGroup(GfxState *A, double *B, GfxColorSpace *C, GBool D,
                              GBool E, GBool F) {
    printf("beginTransparencyGroup\n");
    return OutputDev::beginTransparencyGroup(A, B, C, D, E, F);
  }

  void endTransparencyGroup(GfxState *A) {
    printf("endTransparencyGroup\n");
    return OutputDev::endTransparencyGroup(A);
  }

  void paintTransparencyGroup(GfxState *A, double *B) {
    printf("paintTransparencyGroup\n");
    return OutputDev::paintTransparencyGroup(A, B);
  }

  void setSoftMask(GfxState *A, double *B, GBool C, Function *D, GfxColor *E) {
    printf("setSoftMask\n");
    return OutputDev::setSoftMask(A, B, C, D, E);
  }

  void clearSoftMask(GfxState *A) {
    printf("clearSoftMask\n");
    return OutputDev::clearSoftMask(A);
  }

  void processLink(AnnotLink *A) {
    printf("processLink\n");
    return OutputDev::processLink(A);
  }

  GBool getVectorAntialias() {
    printf("getVectorAntialias\n");
    return OutputDev::getVectorAntialias();
  }

  void setVectorAntialias(GBool A) {
    printf("setVectorAntialias\n");
    return OutputDev::setVectorAntialias(A);
  }
};

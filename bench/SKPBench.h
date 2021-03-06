/*
 * Copyright 2014 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SKPBench_DEFINED
#define SKPBench_DEFINED

#include "Benchmark.h"
#include "SkCanvas.h"
#include "SkPicture.h"

/**
 * Runs an SkPicture as a benchmark by repeatedly drawing it scaled inside a device clip.
 */
class SKPBench : public Benchmark {
public:
    SKPBench(const char* name, const SkPicture*, const SkIRect& devClip, SkScalar scale,
             bool useMultiPictureDraw);
    ~SKPBench() override;

protected:
    const char* onGetName() override;
    const char* onGetUniqueName() override;
    void onPerCanvasPreDraw(SkCanvas*) override;
    void onPerCanvasPostDraw(SkCanvas*) override;
    bool isSuitableFor(Backend backend) override;
    void onDraw(const int loops, SkCanvas* canvas) override;
    SkIPoint onGetSize() override;

    virtual void drawMPDPicture();
    virtual void drawPicture();

    const SkPicture* picture() const { return fPic; }
    const SkTDArray<SkSurface*>& surfaces() const { return fSurfaces; }
    const SkTDArray<SkIRect>& tileRects() const { return fTileRects; }

private:
    SkAutoTUnref<const SkPicture> fPic;
    const SkIRect fClip;
    const SkScalar fScale;
    SkString fName;
    SkString fUniqueName;

    const bool fUseMultiPictureDraw;
    SkTDArray<SkSurface*> fSurfaces;   // for MultiPictureDraw
    SkTDArray<SkIRect> fTileRects;     // for MultiPictureDraw

    typedef Benchmark INHERITED;
};

#endif

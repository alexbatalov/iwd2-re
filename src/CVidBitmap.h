#ifndef CVIDBITMAP_H_
#define CVIDBITMAP_H_

#include "CResBitmap.h"
#include "CVidImage.h"

class CVidBitmap : public CVidImage, public CResHelper<CResBitmap, 1> {
public:
    CVidBitmap();
    ~CVidBitmap();
    BOOL GetPixelColor(RGBQUAD& color, INT nX, INT nY, BOOL bLoaded);

    /* 00B0 */ SHORT m_nBitCount;
    /* 00B6 */ BOOL m_bDoubleSize;
};

#endif /* CVIDBITMAP_H_ */

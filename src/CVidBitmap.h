#ifndef CVIDBITMAP_H_
#define CVIDBITMAP_H_

#include "CResBitmap.h"
#include "CVidImage.h"

#define CVIDBITMAP_4BIT 4
#define CVIDBITMAP_8BIT 8

class CVidBitmap : public CVidImage, public CResHelper<CResBitmap, 1> {
public:
    CVidBitmap();
    CVidBitmap(CResRef cNewResRef, BOOL bDoubleSize);
    CVidBitmap(CResRef cNewResRef, BOOL bDoubleSize, USHORT nBitCount);
    ~CVidBitmap();
    SHORT GetBitCount(BOOL bDemanded);
    BOOL GetImageDimensions(CSize& size, BOOLEAN bDemanded);
    BOOL GetPixelColor(RGBQUAD& color, INT nX, INT nY, BOOL bLoaded);
    BOOL GetPixelValue(BYTE& value, INT x, INT y, BOOLEAN bDemanded);
    BYTE GetPixelValue(INT x, INT y, BOOLEAN bDemanded);
    void SetRes(CResBitmap* pResBmp);
    BOOL BltBmp8To32(DWORD* pSurface, LONG lPitch, BYTE* pData, const CSize& bmpSize, LONG nDataJump, DWORD dwFlags);

    /* 00B0 */ SHORT m_nBitCount;
    /* 00B6 */ BOOL m_bDoubleSize;
};

#endif /* CVIDBITMAP_H_ */

#ifndef CRESBITMAP_H_
#define CRESBITMAP_H_

#include "CRes.h"

class CResBitmap : public CRes {
public:
    CResBitmap();
    ~CResBitmap();
    void* Demand();
    int GetBitDepth();
    int GetColorCount();
    RGBQUAD* GetColorTable();
    BYTE* GetImageData(BOOL bDoubleSize);
    void GetImageDimensions(CSize& size, BOOL bDoubleSize);
    void* Parse();
    BOOL GetPixelColor(int x, int y, RGBQUAD& color, BOOL bDoubleSize);
    BYTE GetPixelValue(int x, int y, BOOL bDoubleSize);
    int Release();
    BOOL Parse(void* pData);
    BOOL DemandLoadedBitmap();
    void ReleaseLoadedBitmap();

    /* 0050 */ int nColors;
    /* 0054 */ int nXWords;
    /* 0058 */ BOOL bParsed;
    /* 005C */ BYTE* pBitmapData;
    /* 0060 */ LPBITMAPFILEHEADER pBitmapFileHeader;
    /* 0064 */ LPBITMAPINFOHEADER pBitmapInfoHeader;
    /* 0068 */ RGBQUAD* pColorTable;
};

#endif /* CRESBITMAP_H_ */

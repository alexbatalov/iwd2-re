#ifndef CVIDIMAGE_H_
#define CVIDIMAGE_H_

#include "CVidPalette.h"

#define CVIDIMG_TRANSLUCENT 0x2

class CVidImage {
public:
    static DWORD rgbTempPal[256];

    CVidImage();
    ~CVidImage();
    COLORREF GetTintColor();
    void SetAddColor(COLORREF rgbNewColor);
    void SetTintColor(COLORREF rgbNewColor);

    /* 0000 */ INT m_nFxSurface;
    /* 0004 */ CVidPalette m_cPalette;
    /* 0028 */ CVIDIMG_PALETTEAFFECT m_paletteAffects;
};

class CVidTile : public CVidImage {
public:
    static const INT BYTES_PER_TEXEL;
};

#endif /* CVIDIMAGE_H_ */

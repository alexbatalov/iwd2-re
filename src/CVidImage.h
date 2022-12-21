#ifndef CVIDIMAGE_H_
#define CVIDIMAGE_H_

#include "CVidPalette.h"

class CVidImage {
public:
    CVidImage();
    ~CVidImage();
    COLORREF GetTintColor();
    void SetAddColor(COLORREF rgbNewColor);
    void SetTintColor(COLORREF rgbNewColor);

    /* 0000 */ INT m_nFxSurface;
    /* 0004 */ CVidPalette m_cPalette;
    /* 0028 */ CVIDIMG_PALETTEAFFECT m_paletteAffects;
};

#endif /* CVIDIMAGE_H_ */

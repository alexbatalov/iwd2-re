#ifndef CVIDPOLY_H_
#define CVIDPOLY_H_

#include "mfc.h"

class CVidPoly {
public:
    BOOL FillPoly(WORD* pSurface, LONG lPitch, const CRect& rClip, DWORD dwColor, DWORD dwFlags, const CPoint& ptRef);

    int field_0;
    int field_4;
    int field_8;
    int field_C;
    int field_10;
    int field_14;
};

#endif /* CVIDPOLY_H_ */

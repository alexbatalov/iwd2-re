#ifndef CVIDPOLY_H_
#define CVIDPOLY_H_

#include "mfc.h"

typedef struct {
    WORD x;
    WORD y;
} CVIDPOLY_VERTEX;

class CVidPoly {
public:
    BOOL FillPoly(WORD* pSurface, LONG lPitch, const CRect& rClip, DWORD dwColor, DWORD dwFlags, const CPoint& ptRef);
    void SetPoly(WORD* pVertices, WORD nVertices);
    void SetPoly(CVIDPOLY_VERTEX* pVertices, WORD nVertices);
    void DrawHLine16(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef);

    void DrawHLine24(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef);

    int field_0;
    CVIDPOLY_VERTEX* m_pVertices;
    INT m_nVertices;
    int field_C;
    int field_10;
    int field_14;
};

#endif /* CVIDPOLY_H_ */

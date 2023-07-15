#include "CVidPoly.h"

// 0x7C13A0
BOOL CVidPoly::FillPoly(WORD* pSurface, LONG lPitch, const CRect& rClip, DWORD dwColor, DWORD dwFlags, const CPoint& ptRef)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7C18B0
void CVidPoly::SetPoly(WORD* pVertices, WORD nVertices)
{
    m_pVertices = reinterpret_cast<CVIDPOLY_VERTEX*>(pVertices);
    m_nVertices = nVertices;
}

// 0x7C18D0
void CVidPoly::SetPoly(CVIDPOLY_VERTEX* pVertices, WORD nVertices)
{
    m_pVertices = pVertices;
    m_nVertices = nVertices;
}

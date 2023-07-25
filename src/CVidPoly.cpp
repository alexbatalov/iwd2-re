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

// 0x7C1AA0
void CVidPoly::DrawHLine16(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned short* pSurface16 = reinterpret_cast<unsigned short*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface16 += xMin;

        for (int x = 0; x < width; x++) {
            *pSurface16++ = static_cast<unsigned short>(dwColor);
        }
    }
}

// 0x7D6970
void CVidPoly::DrawHLine24(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned char* pSurface8 = reinterpret_cast<unsigned char*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface8 += xMin * 3;

        for (int x = 0; x < width; x++) {
            *pSurface8++ = GetRValue(dwColor);
            *pSurface8++ = GetGValue(dwColor);
            *pSurface8++ = GetBValue(dwColor);
        }
    }
}

// 0x7D6AF0
void CVidPoly::DrawHLine32(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned int* pSurface32 = reinterpret_cast<unsigned int*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface32 += xMin;

        for (int x = 0; x < width; x++) {
            *pSurface32++ = dwColor;
        }
    }
}

#include "CVidPoly.h"

#include "CChitin.h"

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

// 0x7C1AF0
void CVidPoly::DrawHLineMirrored16(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned short* pSurface16 = reinterpret_cast<unsigned short*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface16 += rSurface.Width() - xMin;

        for (int x = 0; x < width; x++) {
            *pSurface16-- = static_cast<unsigned short>(dwColor);
        }
    }
}

// 0x7C1B50
void CVidPoly::DrawHLineDithered16(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned short* pSurface16 = reinterpret_cast<unsigned short*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface16 += xMin;

        if ((ptRef.y & 1) != 0) {
            if (((xMin + ptRef.x) & 1) != 0) {
                pSurface16++;
                width--;
            }
        } else {
            if (((xMin + ptRef.x) & 1) == 0) {
                pSurface16++;
                width--;
            }
        }

        width /= 2;
        for (int x = 0; x < width; x++) {
            *pSurface16 = static_cast<unsigned short>(dwColor);
            pSurface16 += 2;
        }
    }
}

// 0x7C1BB0
void CVidPoly::DrawHLineDitheredMirrored16(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned short* pSurface16 = reinterpret_cast<unsigned short*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface16 += rSurface.Width() - xMin;

        if ((ptRef.y & 1) != 0) {
            if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) != 0) {
                pSurface16--;
                width--;
            }
        } else {
            if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) == 0) {
                pSurface16--;
                width--;
            }
        }

        width /= 2;
        for (int x = 0; x < width; x++) {
            *pSurface16 = static_cast<unsigned short>(dwColor);
            pSurface16 -= 2;
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

// 0x7D69B0
void CVidPoly::DrawHLineMirrored24(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned char* pSurface8 = reinterpret_cast<unsigned char*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface8 += (rSurface.Width() - xMin) * 3;

        for (int x = 0; x < width; x++) {
            pSurface8[0] = GetRValue(dwColor);
            pSurface8[1] = GetGValue(dwColor);
            pSurface8[2] = GetBValue(dwColor);
            pSurface8 -= 3;
        }
    }
}

// 0x7D6A00
void CVidPoly::DrawHLineDithered24(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned char* pSurface8 = reinterpret_cast<unsigned char*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface8 += xMin;

        if ((ptRef.y & 1) != 0) {
            if (((xMin + ptRef.x) & 1) != 0) {
                pSurface8 += 3;
                width--;
            }
        } else {
            if (((xMin + ptRef.x) & 1) == 0) {
                pSurface8 += 3;
                width--;
            }
        }

        width /= 2;
        for (int x = 0; x < width; x++) {
            pSurface8[0] = GetRValue(dwColor);
            pSurface8[1] = GetGValue(dwColor);
            pSurface8[2] = GetBValue(dwColor);
            pSurface8 += 6;
        }
    }
}

// 0x7D6A70
void CVidPoly::DrawHLineDitheredMirrored24(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned char* pSurface8 = reinterpret_cast<unsigned char*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface8 += (rSurface.Width() - xMin) * 3;

        if ((ptRef.y & 1) != 0) {
            if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) != 0) {
                pSurface8 -= 3;
                width--;
            }
        } else {
            if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) == 0) {
                pSurface8 -= 3;
                width--;
            }
        }

        width /= 2;
        for (int x = 0; x < width; x++) {
            pSurface8[0] = GetRValue(dwColor);
            pSurface8[1] = GetGValue(dwColor);
            pSurface8[2] = GetBValue(dwColor);
            pSurface8 -= 6;
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

// 0x7D6B20
void CVidPoly::DrawHLineMirrored32(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned int* pSurface32 = reinterpret_cast<unsigned int*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface32 += rSurface.Width() - xMin;

        for (int x = 0; x < width; x++) {
            *pSurface32-- = dwColor;
        }
    }
}

// 0x7D6B60
void CVidPoly::DrawHLineDithered32(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned int* pSurface32 = reinterpret_cast<unsigned int*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface32 += xMin;

        if (g_pChitin->cVideo.Is3dAccelerated()) {
            for (int x = 0; x < width; x++) {
                unsigned int rgb = *pSurface32;
                *pSurface32++ = (rgb & 0xFFFFFF) | ((rgb >> 1) & 0x7F000000);
            }
        } else {
            if ((ptRef.y & 1) != 0) {
                if (((xMin + ptRef.x) & 1) != 0) {
                    pSurface32++;
                    width--;
                }
            } else {
                if (((xMin + ptRef.x) & 1) == 0) {
                    pSurface32++;
                    width--;
                }
            }

            width /= 2;
            for (int x = 0; x < width; x++) {
                *pSurface32 = dwColor;
                pSurface32 += 2;
            }
        }
    }
}

// 0x7D6BF0
void CVidPoly::DrawHLineDitheredMirrored32(void* pSurface, int xMin, int xMax, DWORD dwColor, const CRect& rSurface, const CPoint& ptRef)
{
    unsigned int* pSurface32 = reinterpret_cast<unsigned int*>(pSurface);

    int width = xMax - xMin + 1;
    if (width > 0) {
        pSurface32 += rSurface.Width() - xMin;

        if (g_pChitin->cVideo.Is3dAccelerated()) {
            for (int x = 0; x < width; x++) {
                unsigned int rgb = *pSurface32;
                *pSurface32-- = (rgb & 0xFFFFFF) | ((rgb >> 1) & 0x7F000000);
            }
        } else {
            if ((ptRef.y & 1) != 0) {
                if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) != 0) {
                    pSurface32--;
                    width--;
                }
            } else {
                if (((rSurface.Width() + xMin + ptRef.x - 1) & 1) == 0) {
                    pSurface32--;
                    width--;
                }
            }

            width /= 2;
            for (int x = 0; x < width; x++) {
                *pSurface32 = dwColor;
                pSurface32 -= 2;
            }
        }
    }
}

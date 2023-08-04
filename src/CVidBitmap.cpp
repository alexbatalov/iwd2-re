#include "CVidBitmap.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x7B2A40
CVidBitmap::CVidBitmap()
{
    m_nBitCount = 8;
    m_bDoubleSize = FALSE;
}

// 0x7B2DB0
CVidBitmap::~CVidBitmap()
{
}

// FIXME: Use reference.
//
// 0x7B2AD0
CVidBitmap::CVidBitmap(CResRef cNewResRef, BOOL bDoubleSize)
{
    // NOTE: Uninline.
    SetResRef(cNewResRef, TRUE, TRUE);

    m_nBitCount = 8;
    m_bDoubleSize = bDoubleSize;
}

// FIXME: Use reference.
//
// 0x7B2C40
CVidBitmap::CVidBitmap(CResRef cNewResRef, BOOL bDoubleSize, USHORT nBitCount)
{
    // NOTE: Uninline.
    SetResRef(cNewResRef, TRUE, TRUE);

    m_nBitCount = nBitCount;
    m_bDoubleSize = bDoubleSize;
}

// 0x7B2E90
SHORT CVidBitmap::GetBitCount(BOOL bDemanded)
{
    if (!bDemanded) {
        pRes->Demand();
    }

    SHORT nBitCount = pRes->GetBitDepth();

    if (!bDemanded) {
        pRes->Release();
    }

    return nBitCount;
}

// 0x7B2ED0
BOOL CVidBitmap::GetImageDimensions(CSize& size, BOOLEAN bDemanded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 7277
    UTIL_ASSERT(pRes != NULL);

    if (pRes == NULL) {
        return FALSE;
    }

    if (!bDemanded) {
        if (pRes->Demand() == NULL) {
            return FALSE;
        }
    }

    pRes->GetImageDimensions(size, m_bDoubleSize);

    if (!bDemanded) {
        pRes->Release();
    }

    return TRUE;
}

// 0x7B2F60
BOOL CVidBitmap::GetPixelColor(RGBQUAD& color, INT nX, INT nY, BOOL bLoaded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 7337
    UTIL_ASSERT(pRes != NULL);

    if (pRes == NULL) {
        return FALSE;
    }

    if (bLoaded) {
        pRes->GetPixelColor(nX, nY, color, m_bDoubleSize);
        return TRUE;
    }

    if (pRes->Demand()) {
        pRes->GetPixelColor(nX, nY, color, m_bDoubleSize);
        pRes->Release();
        return TRUE;
    }

    return FALSE;
}

// 0x7B3000
BOOL CVidBitmap::GetPixelValue(BYTE& value, INT x, INT y, BOOLEAN bDemanded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 7400
    UTIL_ASSERT((m_nBitCount == CVIDBITMAP_8BIT || m_nBitCount == CVIDBITMAP_4BIT));

    if (pRes == NULL) {
        return FALSE;
    }

    if (m_nBitCount == CVIDBITMAP_8BIT || m_nBitCount == CVIDBITMAP_4BIT) {
        if (bDemanded) {
            value = pRes->GetPixelValue(x, y, m_bDoubleSize);
            return TRUE;
        }

        if (pRes->Demand() != NULL) {
            value = pRes->GetPixelValue(x, y, m_bDoubleSize);
            pRes->Release();
            return TRUE;
        }
    }

    return FALSE;
}

// 0x7B30C0
BYTE CVidBitmap::GetPixelValue(INT x, INT y, BOOLEAN bDemanded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 7440
    UTIL_ASSERT((m_nBitCount == CVIDBITMAP_8BIT || m_nBitCount == CVIDBITMAP_4BIT));

    if (pRes == NULL) {
        return 0;
    }

    if (m_nBitCount == CVIDBITMAP_8BIT || m_nBitCount == CVIDBITMAP_4BIT) {
        if (bDemanded) {
            return pRes->GetPixelValue(x, y, m_bDoubleSize);
        }

        if (pRes->Demand() != NULL) {
            BYTE value = pRes->GetPixelValue(x, y, m_bDoubleSize);
            pRes->Release();
            return value;
        }
    }

    return 0;
}

// 0x7B3180
void CVidBitmap::SetRes(CResBitmap* pResBmp)
{
    pRes = pResBmp;
}

// 0x7CD5E0
BOOL CVidBitmap::BltBmp8To32(DWORD* pSurface, LONG lPitch, BYTE* pData, const CSize& bmpSize, LONG nDataJump, DWORD dwFlags)
{
    m_cPalette.SetPalette(pRes->GetColorTable(), pRes->GetColorCount(), CVidPalette::TYPE_RESOURCE);
    m_cPalette.Realize(rgbTempPal, 32, dwFlags | 0x800000, &m_paletteAffects, 255);

    for (LONG y = 0; y < bmpSize.cy; y++) {
        for (LONG x = 0; x < bmpSize.cx; x++) {
            *pSurface++ = rgbTempPal[*pData++];
        }

        pSurface += -bmpSize.cx - lPitch / 4;
        pData += nDataJump;
    }

    return TRUE;
}

// 0x7CD690
BOOL CVidBitmap::BltBmp24To32(DWORD* pSurface, LONG lPitch, BYTE* pData, const CSize& bmpSize, LONG nDataJump, DWORD dwFlags)
{
    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();

    DWORD dwRBitShift = pVidMode->m_dwRBitShift;
    DWORD dwGBitShift = pVidMode->m_dwGBitShift;
    DWORD dwBBitShift = pVidMode->m_dwBBitShift;

    if ((dwFlags & 0x1) != 0) {
        for (LONG y = 0; y < bmpSize.cy; y++) {
            for (LONG x = 0; x < bmpSize.cx; x++) {
                BYTE r = pData[2];
                BYTE g = pData[1];
                BYTE b = pData[0];
                BYTE a;

                if (r != 0 || g != 255 || b != 0) {
                    if ((dwFlags & 0x4) == 0 || r != 0 || g != 0 || b != 0) {
                        a = 255;
                    } else {
                        a = 128;
                        r = ((*pSurface >> dwRBitShift) >> 1) & 0x7F;
                        g = ((*pSurface >> dwGBitShift) >> 1) & 0x7F;
                        b = ((*pSurface >> dwBBitShift) >> 1) & 0x7F;
                    }

                    *pSurface = (a << 24) | (r << dwRBitShift) | (g << dwGBitShift) | (b << dwBBitShift);
                }

                pSurface++;
                pData += 3;
            }

            pSurface += -bmpSize.cx - lPitch / 4;
            pData += nDataJump;
        }
    } else {
        for (LONG y = 0; y < bmpSize.cy; y++) {
            for (LONG x = 0; x < bmpSize.cx; x++) {
                *pSurface++ = (pData[0] << dwBBitShift) | (pData[1] << dwGBitShift) | (pData[2] << dwRBitShift);
                pData += 3;
            }

            pSurface += -bmpSize.cx - lPitch / 4;
            pData += nDataJump;
        }
    }

    return TRUE;
}

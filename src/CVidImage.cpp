#include "CVidImage.h"

#include "CChitin.h"
#include "CResTile.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVideo3d.h"

// 0x85E838
const INT CVidTile::BYTES_PER_TEXEL = 4;

// 0xA09FC8
BYTE CVidTile::m_pPixels[16384];

// 0x9064F8
DWORD CVidImage::rgbTempPal[256];

// 0x7ACA60
CVidImage::CVidImage()
{
    m_nFxSurface = -1;
    m_paletteAffects.rgbTintColor = 0xFFFFFF;
    m_paletteAffects.rgbAddColor = 0;
    m_paletteAffects.rgbLightColor = (1 << CVidPalette::LIGHT_SCALE) | ((1 << CVidPalette::LIGHT_SCALE) << 8) | ((1 << CVidPalette::LIGHT_SCALE) << 16);
    memset(m_paletteAffects.pRangeTints, 0, sizeof(m_paletteAffects.pRangeTints[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.pRangeAdds, 0, sizeof(m_paletteAffects.pRangeAdds[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.pRangeLights, 0, sizeof(m_paletteAffects.pRangeLights[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeTintPeriods, 0, sizeof(m_paletteAffects.aRangeTintPeriods[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeAddPeriods, 0, sizeof(m_paletteAffects.aRangeAddPeriods[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeLightPeriods, 0, sizeof(m_paletteAffects.aRangeLightPeriods[0]) * CVidPalette::NUM_RANGES);
    m_paletteAffects.suppressTints = 0;

    // TODO: Incomplete.
}

// 0x7ACC40
CVidImage::~CVidImage()
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x7ACD40
COLORREF CVidImage::GetTintColor()
{
    sizeof(m_cPalette);
    return m_paletteAffects.rgbTintColor;
}

// #binary-identical
// 0x7ACD50
void CVidImage::SetAddColor(COLORREF rgbNewColor)
{
    m_paletteAffects.rgbAddColor = rgbNewColor;
}

// #binary-identical
// 0x7ACD60
void CVidImage::SetTintColor(COLORREF rgbNewColor)
{
    m_paletteAffects.rgbTintColor = rgbNewColor;
}

// 0x7C40D0
void CVidImage::SetPolyColor(DWORD dwFlags)
{
    CVideo3d::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// -----------------------------------------------------------------------------

// 0x7B16E0
CVidTile::CVidTile()
{
    pRes = NULL;
    m_dwFlags = 0;
}

// 0x7B1700
CVidTile::~CVidTile()
{
}

// 0x7B1770
void CVidTile::SetRes(CResTile* pNewResTiles)
{
    pRes = pNewResTiles;
}

// 0x7B1780
BOOL CVidTile::Render(LPDIRECTDRAWSURFACE pSurface, INT x, INT y, const CRect& rClip, DWORD dwFlags)
{
    LONG nDataJump = 0;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 6140
    UTIL_ASSERT(pSurface != NULL);

    if (pRes == NULL) {
        return FALSE;
    }

    if (rClip.IsRectEmpty()) {
        return FALSE;
    }

    pRes->Demand();

    BYTE* pData = pRes->GetTileData();
    if (pData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 6159
        UTIL_ASSERT_MSG(FALSE, "Tile data accessed when not loaded");
    }

    INT nTileSize = pRes->GetTileSize();
    CSize blitSize(nTileSize, nTileSize);

    CRect rTileRect(x, y, x + nTileSize, y + nTileSize);

    INT nSkipTop = rClip.top - rTileRect.top;
    if (nSkipTop > 0) {
        rTileRect.top += nSkipTop;
        pData += nTileSize * nSkipTop;
        blitSize.cy -= nSkipTop;
    }

    INT nSkipBottom = rTileRect.bottom - rClip.bottom;
    if (nSkipBottom > 0) {
        blitSize.cy -= nSkipBottom;
        rTileRect.bottom -= nSkipBottom;
    }

    INT nSkipRight = rTileRect.right - rClip.right;
    if (nSkipRight > 0) {
        blitSize.cx -= nSkipRight;
        rTileRect.right -= nSkipRight;
    }

    INT nSkipLeft = rClip.left - rTileRect.left;
    if (nSkipLeft > 0) {
        blitSize.cx -= nSkipLeft;
        pData += nSkipLeft;
        rTileRect.left += nSkipLeft;
        nDataJump = nSkipLeft;
    }

    if (rTileRect.IsRectEmpty()) {
        pRes->Release();
        return FALSE;
    }

    DDSURFACEDESC ddsd;
    HRESULT hr;

    do {
        ddsd.dwSize = sizeof(ddsd);
        hr = pSurface->Lock(&rTileRect, &ddsd, DDLOCK_WAIT, NULL);
        if (hr == DDERR_SURFACELOST) {
            g_pChitin->GetCurrentVideoMode()->RestoreSurfaces();
        }
    } while (hr == DDERR_SURFACELOST || hr == DDERR_SURFACEBUSY);

    if (hr != DD_OK) {
        pRes->Release();
        return FALSE;
    }

    m_cPalette.SetPalette(pRes->m_pPalette,
        256,
        CVidPalette::TYPE_RESOURCE);

    BOOL bSuccess;

    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        m_cPalette.Realize(rgbTempPal,
            16,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltTile8To16(reinterpret_cast<WORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    case 24:
        m_cPalette.Realize(rgbTempPal,
            24,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltTile8To24(reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    case 32:
        m_cPalette.Realize(rgbTempPal,
            32,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltTile8To32(reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    }

    pSurface->Unlock(ddsd.lpSurface);

    pRes->Release();
    return TRUE;
}

// 0x7B1B30
BOOL CVidTile::Render(LPDIRECTDRAWSURFACE pSurface, INT x, INT y, CResTile* pResStencil, const CRect& rClip, DWORD dwFlags)
{
    LONG nDataJump = 0;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 6325
    UTIL_ASSERT(pSurface != NULL);

    if (pRes == NULL) {
        return FALSE;
    }

    if (rClip.IsRectEmpty()) {
        return FALSE;
    }

    pRes->Demand();

    BYTE* pData = pRes->GetTileData();
    if (pData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 6344
        UTIL_ASSERT_MSG(FALSE, "Tile data accessed when not loaded");
    }

    BYTE* pStencilData = pResStencil->GetTileData();
    if (pStencilData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 6351
        UTIL_ASSERT_MSG(FALSE, "Tile stencil data accessed when not loaded");
    }

    INT nTileSize = pRes->GetTileSize();
    CSize blitSize(nTileSize, nTileSize);

    CRect rTileRect(x, y, x + nTileSize, y + nTileSize);

    INT nSkipTop = rClip.top - rTileRect.top;
    if (nSkipTop > 0) {
        rTileRect.top += nSkipTop;
        pData += nTileSize * nSkipTop;
        blitSize.cy -= nSkipTop;
    }

    INT nSkipBottom = rTileRect.bottom - rClip.bottom;
    if (nSkipBottom > 0) {
        blitSize.cy -= nSkipBottom;
        rTileRect.bottom -= nSkipBottom;
    }

    INT nSkipRight = rTileRect.right - rClip.right;
    if (nSkipRight > 0) {
        blitSize.cx -= nSkipRight;
        rTileRect.right -= nSkipRight;
    }

    INT nSkipLeft = rClip.left - rTileRect.left;
    if (nSkipLeft > 0) {
        blitSize.cx -= nSkipLeft;
        pData += nSkipLeft;
        rTileRect.left += nSkipLeft;
        nDataJump = nSkipLeft;
    }

    if (rTileRect.IsRectEmpty()) {
        pRes->Release();
        pResStencil->Release();
        return FALSE;
    }

    DDSURFACEDESC ddsd;
    HRESULT hr;

    do {
        ddsd.dwSize = sizeof(ddsd);
        hr = pSurface->Lock(&rTileRect, &ddsd, DDLOCK_WAIT, NULL);
        if (hr == DDERR_SURFACELOST) {
            g_pChitin->GetCurrentVideoMode()->RestoreSurfaces();
        }
    } while (hr == DDERR_SURFACELOST || hr == DDERR_SURFACEBUSY);

    if (hr != DD_OK) {
        pRes->Release();
        pResStencil->Release();
        return FALSE;
    }

    m_cPalette.SetPalette(pRes->m_pPalette,
        256,
        CVidPalette::TYPE_RESOURCE);

    BOOL bSuccess;

    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        m_cPalette.Realize(rgbTempPal,
            16,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltStencilTile8To16(reinterpret_cast<WORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            pStencilData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    case 24:
        m_cPalette.Realize(rgbTempPal,
            24,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltStencilTile8To24(reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            pStencilData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    case 32:
        m_cPalette.Realize(rgbTempPal,
            32,
            dwFlags | 0x400000,
            &m_paletteAffects,
            255);
        bSuccess = BltStencilTile8To32(reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch,
            pData,
            pStencilData,
            blitSize,
            nDataJump,
            dwFlags);
        break;
    }

    pSurface->Unlock(ddsd.lpSurface);

    pRes->Release();
    pResStencil->Release();
    return TRUE;
}

// 0x7B22E0
BOOL CVidTile::BltTile8To16(WORD* pSurface, LONG lPitch, BYTE* pData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7B2440
BOOL CVidTile::BltStencilTile8To16(WORD* pSurface, LONG lPitch, BYTE* pData, BYTE* pStencilData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7CDD00
BOOL CVidTile::BltTile8To24(DWORD* pSurface, LONG lPitch, BYTE* pData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7CDF90
BOOL CVidTile::BltStencilTile8To24(DWORD* pSurface, LONG lPitch, BYTE* pData, BYTE* pStencilData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7CE830
BOOL CVidTile::BltTile8To32(DWORD* pSurface, LONG lPitch, BYTE* pData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    INT nSurfaceJump = lPitch - 4 * blitSize.cx;
    DWORD color = g_pChitin->GetCurrentVideoMode()->field_24;

    if ((blitSize.cx & 1) != 0) {
        return FALSE;
    }

    if ((dwFlags & 0x8) != 0) {
        for (int y = 0; y < blitSize.cy; y++) {
            for (int x = 0; x < blitSize.cx; x++) {
                pSurface[0] = rgbTempPal[*pData];

                x++;
                if (x == blitSize.cx) {
                    break;
                }

                pSurface[1] = color;

                pData += 2;
                pSurface += 2;
            }

            pSurface = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(pSurface) + nSurfaceJump);
            pData += nDataJump;

            y++;
            if (y == blitSize.cy) {
                break;
            }

            for (int x = 0; x < blitSize.cx; x++) {
                pSurface[0] = color;

                x++;
                if (x == blitSize.cx) {
                    pSurface[1] = rgbTempPal[*pData];
                }

                pData += 2;
                pSurface += 2;
            }

            pSurface = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(pSurface) + nSurfaceJump);
            pData += nDataJump;
        }
    } else {
        for (int y = 0; y < blitSize.cy; y++) {
            for (int x = 0; x < blitSize.cx; x++) {
                *pSurface++ = rgbTempPal[*pData++];
            }

            pSurface = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(pSurface) + nSurfaceJump);
            pData += nDataJump;
        }
    }

    return TRUE;
}

// 0x7CE290
BOOL CVidTile::BltStencilTile8To32(DWORD* pSurface, LONG lPitch, BYTE* pData, BYTE* pStencilData, const CSize& blitSize, LONG nDataJump, DWORD dwFlags)
{
    INT nDataIndex = 0;
    INT nSurfaceJump = lPitch - 4 * blitSize.cx;
    DWORD color = g_pChitin->GetCurrentVideoMode()->field_24;

    if ((blitSize.cx & 1) != 0) {
        return FALSE;
    }

    for (int y = 0; y < blitSize.cy; y++) {
        if ((y & 1) != 0) {
            for (int x = 0; x < blitSize.cx / 2; x++) {
                if (pStencilData[nDataIndex] == CVidPalette::CLEAR_ENTRY) {
                    pSurface[0] = color;
                } else {
                    pSurface[0] = rgbTempPal[pData[nDataIndex]];
                }

                pSurface[1] = rgbTempPal[pData[nDataIndex + 1]];

                pSurface += 2;
                nDataIndex += 2;
            }
        } else {
            for (int x = 0; x < blitSize.cx / 2; x++) {
                pSurface[0] = rgbTempPal[pData[nDataIndex]];

                if (pStencilData[nDataIndex + 1] == CVidPalette::CLEAR_ENTRY) {
                    pSurface[1] = color;
                } else {
                    pSurface[1] = rgbTempPal[pData[nDataIndex + 1]];
                }

                pSurface += 2;
                nDataIndex += 2;
            }
        }

        pSurface = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(pSurface) + nSurfaceJump);
        pData += nDataJump;
    }

    return TRUE;
}

// NOTE: Inlined.
BOOL CVidTile::BltStencilTile8to32_3d(DWORD* pSurface, LONG lPitch, BYTE* pData, BYTE* pStencilData, const CSize& blitSize, LONG nDataJump, DWORD dwAlpha, DWORD dwFlags)
{
    INT nDataIndex = 0;
    INT nSurfaceJump = lPitch - 4 * blitSize.cx;

    if ((blitSize.cx & 1) != 0) {
        return FALSE;
    }

    for (int y = 0; y < blitSize.cy; y++) {
        for (int x = 0; x < blitSize.cx; x++) {
            *pSurface = rgbTempPal[pData[nDataIndex]];
            if (pStencilData[nDataIndex] == CVidPalette::CLEAR_ENTRY) {
                *pSurface &= (dwAlpha << 24) | 0xFFFFFF;
            }
            pSurface++;
            nDataIndex++;
        }

        pSurface = reinterpret_cast<DWORD*>(reinterpret_cast<BYTE*>(pSurface) + nSurfaceJump);
        pData += nDataJump;
        pStencilData += nDataJump;
    }

    return TRUE;
}

// 0x7C5F60
BOOL CVidTile::ReadyTexture(INT nTextureId, DWORD dwFlags, DWORD dwAlpha)
{
    if (nTextureId < 9 && nTextureId != 2) {
        return FALSE;
    }

    if (pRes == NULL) {
        return FALSE;
    }

    pRes->Demand();

    BYTE* pTileData = pRes->GetTileData();
    if (pTileData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage3d.cpp
        // __LINE__: 1465
        UTIL_ASSERT_MSG(FALSE, "Tile data accessed when not loaded");
    }

    m_dwFlags = dwFlags;

    GLuint textures[1];
    textures[0] = static_cast<GLuint>(nTextureId);

    CVideo3d::glDeleteTextures(1, textures);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    INT nTileSize = pRes->GetTileSize();
    CSize blitSize(nTileSize, nTileSize);

    m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    m_cPalette.Realize(CVidImage::rgbTempPal, 32, dwFlags | 0x400000, &m_paletteAffects, dwAlpha);

    BltTile8To32(reinterpret_cast<DWORD*>(m_pPixels), 256, pTileData, blitSize, 0, dwFlags);

    g_pChitin->cVideo.field_13E = nTextureId;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexImage2D(GL_TEXTURE_2D,
        0,
        g_pChitin->cVideo.field_136,
        nTileSize,
        nTileSize,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        m_pPixels);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    pRes->Release();

    return TRUE;
}

// 0x7C61D0
BOOL CVidTile::ReadyTexture(INT nTextureId, CResTile* pResStencil, DWORD dwFlags, DWORD dwAlpha)
{
    if (nTextureId < 9 && nTextureId != 2) {
        return FALSE;
    }

    if (pRes == NULL) {
        return FALSE;
    }

    pRes->Demand();
    pResStencil->Demand();

    BYTE* pTileData = pRes->GetTileData();
    if (pTileData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage3d.cpp
        // __LINE__: 1564
        UTIL_ASSERT_MSG(FALSE, "Tile data accessed when not loaded");
    }

    BYTE* pStencilData = pResStencil->GetTileData();
    if (pStencilData == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage3d.cpp
        // __LINE__: 1573
        UTIL_ASSERT_MSG(FALSE, "Tile stencil data accessed when not loaded");
    }

    m_dwFlags = dwFlags;

    GLuint textures[1];
    textures[0] = static_cast<GLuint>(nTextureId);

    CVideo3d::glDeleteTextures(1, textures);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    INT nTileSize = pRes->GetTileSize();
    CSize blitSize(nTileSize, nTileSize);

    m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    m_cPalette.Realize(CVidImage::rgbTempPal, 32, dwFlags | 0x400000, &m_paletteAffects, dwAlpha);

    // NOTE: Uninline.
    BltStencilTile8to32_3d(reinterpret_cast<DWORD*>(m_pPixels),
        256,
        pTileData,
        pStencilData,
        blitSize,
        0,
        dwAlpha,
        dwFlags);

    g_pChitin->cVideo.field_13E = nTextureId;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexImage2D(GL_TEXTURE_2D,
        0,
        g_pChitin->cVideo.field_136,
        nTileSize,
        nTileSize,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        m_pPixels);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    pRes->Release();
    pResStencil->Release();

    return TRUE;
}

// 0x7C64F0
void CVidTile::RenderTexture(INT nTextureId, const CRect& rDest, INT x, INT y, DWORD dwFlags)
{
    float x1;
    float y1;
    float x2;
    float y2;

    if (nTextureId < 9 && nTextureId != 2) {
        return;
    }

    x1 = static_cast<float>(x);
    y1 = static_cast<float>(y);
    x2 = static_cast<float>(x) + 64.0f;
    y2 = static_cast<float>(y) + 64.0f;

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    g_pChitin->cVideo.field_13E = nTextureId;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    if ((dwFlags & 0x3) != 0) {
        CVideo3d::glEnable(GL_BLEND);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }

    CVideo3d::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    x1 += CVideo3d::SUB_PIXEL_SHIFT;
    y1 += CVideo3d::SUB_PIXEL_SHIFT;
    x2 += CVideo3d::SUB_PIXEL_SHIFT;
    y2 += CVideo3d::SUB_PIXEL_SHIFT;

    CVideo3d::glBegin(GL_TRIANGLE_STRIP);
    CVideo3d::glTexCoord2f(0.0f, 0.0f);
    CVideo3d::glVertex3f(x1, y1, 0.0f);
    CVideo3d::glTexCoord2f(0.0f, 1.0f);
    CVideo3d::glVertex3f(x1, y2, 0.0f);
    CVideo3d::glTexCoord2f(1.0f, 0.0f);
    CVideo3d::glVertex3f(x2, y1, 0.0f);
    CVideo3d::glTexCoord2f(1.0f, 1.0f);
    CVideo3d::glVertex3f(x2, y2, 0.0f);
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    if ((dwFlags & 0x3) != 0) {
        CVideo3d::glDisable(GL_BLEND);
    }
}

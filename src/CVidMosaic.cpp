#include "CVidMosaic.h"

#include "CUtil.h"
#include "CVidMode.h"

// 0x7B0AA0
CVidMosaic::CVidMosaic()
{
    pRes = NULL;
    m_bDoubleSize = FALSE;
}

// 0x7B0B20
CVidMosaic::~CVidMosaic()
{
    // TODO: Incomplete.
}

// 0x7B0BF0
void CVidMosaic::GetSize(CSize& frameSize, BOOL a3)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5312
    UTIL_ASSERT(pRes != NULL);

    if (!a3) {
        pRes->Demand();
    }

    frameSize.cx = pRes->GetMosaicWidth(m_bDoubleSize);
    frameSize.cy = pRes->GetMosaicHeight(m_bDoubleSize);

    if (!a3) {
        pRes->Release();
    }
}

// 0x7B0C80
BOOL CVidMosaic::Render(INT nSurface, int x, int y, const CRect& rMosaic, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (rClip.IsRectNull()) {
        return TRUE;
    }

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return Render3d(x, y, rMosaic, rClip, dwFlags);
    }

    if (m_nFxSurface == -1) {
        if (!g_pChitin->GetCurrentVideoMode()->GetFXSurface(m_nFxSurface, dwFlags)) {
            return FALSE;
        }
    }

    if (pRes == NULL) {
        return FALSE;
    }

    if (!bDemanded) {
        pRes->Demand();
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5431
    UTIL_ASSERT(nSurface < g_pChitin->GetCurrentVideoMode()->GetNumSurfaces() && g_pChitin->GetCurrentVideoMode()->pSurfaces[nSurface] != NULL);

    BltMosFunc Blt;
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        Blt = &CVidMosaic::BltMos8To16;
        break;
    case 24:
        Blt = &CVidMosaic::BltMos8To24;
        break;
    case 32:
        Blt = &CVidMosaic::BltMos8To32;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 5449
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Original code is different and hard to replicate one to one.
    WORD nTileSize = pRes->GetTileSize(m_bDoubleSize);
    WORD nMosaicWidth = pRes->GetMosaicWidth(m_bDoubleSize);
    WORD nMosaicHeight = pRes->GetMosaicHeight(m_bDoubleSize);

    INT nFirstTileX = rMosaic.left / nTileSize;
    INT nFirstTileY = rMosaic.top / nTileSize;
    INT nLastTileX = rMosaic.right % nTileSize == 0
        ? rMosaic.right / nTileSize
        : rMosaic.right / nTileSize + 1;
    INT nLastTileY = (rMosaic.bottom % nTileSize == 0)
        ? rMosaic.bottom / nTileSize
        : rMosaic.bottom / nTileSize + 1;

    nFirstTileX = max(nFirstTileX, 0);
    nFirstTileY = max(nFirstTileY, 0);
    nLastTileX = min(nLastTileX, pRes->m_pHeader->nXTiles);
    nLastTileY = min(nLastTileY, pRes->m_pHeader->nYTiles);

    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();

    DDSURFACEDESC surfaceDesc;
    surfaceDesc.dwSize = sizeof(surfaceDesc);

    CRect rTile(0, 0, nTileSize, nTileSize);

    for (INT nTileY = nFirstTileY; nTileY < nLastTileY; nTileY++) {
        int destY = y + nTileY * nTileSize;
        if (destY + nTileSize < rClip.top || destY > rClip.bottom) {
            continue;
        }

        rTile.bottom = min(nMosaicHeight - nTileY * nTileSize, nTileSize);

        for (INT nTileX = nFirstTileX; nTileX < nLastTileX; nTileX++) {
            int destX = x + nTileX * nTileSize;
            if (destX + nTileSize < rClip.left || destX > rClip.right) {
                continue;
            }

            rTile.right = min(nMosaicWidth - nTileX * nTileSize, nTileSize);

            if (pVidMode->LockSurface(m_nFxSurface, &surfaceDesc, rTile)) {
                (this->*Blt)(reinterpret_cast<DWORD*>(surfaceDesc.lpSurface),
                    surfaceDesc.lPitch,
                    nTileY * pRes->m_pHeader->nXTiles + nTileX,
                    rTile,
                    dwFlags);
                pVidMode->UnLockSurface(m_nFxSurface, surfaceDesc.lpSurface);

                BltFromFX(pVidMode->pSurfaces[nSurface],
                    destX,
                    destY,
                    rTile.Size(),
                    rClip,
                    dwFlags);
            }
        }
    }

    if (!bDemanded) {
        pRes->Release();
    }

    return TRUE;
}

// 0x7B1330
BOOL CVidMosaic::BltFromFX(LPDIRECTDRAWSURFACE pSurface, int x, int y, const CSize& size, const CRect& rClip, DWORD dwFlags)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5597
    UTIL_ASSERT(m_nFxSurface != -1);

    int origX = x;
    int origY = y;

    RECT srcRect;
    srcRect.left = 0;
    srcRect.top = 0;
    srcRect.right = size.cx;
    srcRect.bottom = size.cy;

    if (x < rClip.left) {
        x = rClip.left;
        srcRect.left = rClip.left - origX;
    }

    if (y < rClip.top) {
        y = rClip.top;
        srcRect.top = rClip.top - origY;
    }

    if (size.cx + origX - 1 >= rClip.right) {
        srcRect.right = rClip.right - origX;
    }

    if (size.cy + origY - 1 >= rClip.bottom) {
        srcRect.bottom = rClip.bottom - origY;
    }

    if (srcRect.bottom >= srcRect.top && srcRect.right >= srcRect.left) {
        if ((dwFlags & 0x1) != 0) {
            do {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(pSurface,
                    x,
                    y,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                    &srcRect,
                    DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
                g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            } while (!g_pChitin->field_1932);
        } else {
            do {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(
                    pSurface,
                    x,
                    y,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[m_nFxSurface],
                    &srcRect,
                    DDBLTFAST_WAIT);
                g_pChitin->GetCurrentVideoMode()->CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            } while (!g_pChitin->field_1932);
        }
    }

    return TRUE;
}

// 0x7B1520
BOOL CVidMosaic::BltMos8To16(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags)
{
    int height = rRect.Height();
    int width = rRect.Width();

    if (width != 0) {
        RGBQUAD* pPalette = pRes->GetTilePalette(nTile);
        m_cPalette.SetPalette(pPalette, 256, CVidPalette::TYPE_RESOURCE);
        m_cPalette.Realize(CVidImage::rgbTempPal, 16, dwFlags | 0x400000, &m_paletteAffects, 255);

        BYTE* pTileData = pRes->GetTileData(nTile, m_bDoubleSize);
        LONG nSkip = lPitch - width * 2;

        // TODO: Original code is different (more optimized).
        BYTE* pSurfaceBytes = reinterpret_cast<BYTE*>(pSurface);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                DWORD rgb = CVidImage::rgbTempPal[*pTileData++];
                *(reinterpret_cast<WORD*>(pSurfaceBytes)) = rgb & 0xFFFF;
                pSurfaceBytes += 2;
            }
            pSurfaceBytes += nSkip;
        }
    }

    return TRUE;
}

// 0x7B1670
int CVidMosaic::GetTileNumber(int x, int y)
{
    return pRes->m_pHeader->nXTiles * (y / pRes->GetTileSize(m_bDoubleSize)) + x / pRes->GetTileSize(m_bDoubleSize);
}

// 0x7CC880
BOOL CVidMosaic::BltMos8To24(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags)
{
    int height = rRect.Height();
    int width = rRect.Width();

    if (width != 0) {
        RGBQUAD* pPalette = pRes->GetTilePalette(nTile);
        if (pPalette == NULL) {
            return FALSE;
        }

        m_cPalette.SetPalette(pPalette, 256, CVidPalette::TYPE_RESOURCE);
        m_cPalette.Realize(CVidImage::rgbTempPal, 24, dwFlags | 0x400000, &m_paletteAffects, 255);

        BYTE* pTileData = pRes->GetTileData(nTile, m_bDoubleSize);
        LONG nSkip = lPitch - width * 3;

        // TODO: Original code is different (more optimized).
        BYTE* pSurfaceBytes = reinterpret_cast<BYTE*>(pSurface);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                DWORD rgb = CVidImage::rgbTempPal[*pTileData++];
                *pSurfaceBytes++ = rgb & 0xFF;
                *pSurfaceBytes++ = (rgb >> 8) & 0xFF;
                *pSurfaceBytes++ = (rgb >> 16) & 0xFF;
            }
            pSurfaceBytes += nSkip;
        }
    }

    return TRUE;
}

// 0x7CC9D0
BOOL CVidMosaic::BltMos8To32(DWORD* pSurface, LONG lPitch, UINT nTile, const CRect& rRect, DWORD dwFlags)
{
    int height = rRect.Height();
    int width = rRect.Width();

    if (width != 0) {
        RGBQUAD* pPalette = pRes->GetTilePalette(nTile);
        if (pPalette == NULL) {
            return FALSE;
        }

        m_cPalette.SetPalette(pPalette, 256, CVidPalette::TYPE_RESOURCE);
        m_cPalette.Realize(CVidImage::rgbTempPal, 32, dwFlags | 0x400000, &m_paletteAffects, 255);

        BYTE* pTileData = pRes->GetTileData(nTile, m_bDoubleSize);
        LONG nSkip = lPitch - width * 4;

        // TODO: Original code is different (more optimized).
        BYTE* pSurfaceBytes = reinterpret_cast<BYTE*>(pSurface);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                *(reinterpret_cast<DWORD*>(pSurfaceBytes)) = CVidImage::rgbTempPal[*pTileData++];
                pSurfaceBytes += 4;
            }
            pSurfaceBytes += nSkip;
        }
    }

    return TRUE;
}

// 0x7C5A00
BOOL CVidMosaic::Render3d(int x, int y, const CRect& rMosaic, const CRect& rClip, DWORD dwFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

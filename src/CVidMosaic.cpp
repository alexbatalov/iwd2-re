#include "CVidMosaic.h"

#include "CUtil.h"
#include "CVidInf.h"
#include "CVideo3d.h"

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
void CVidMosaic::GetSize(CSize& frameSize, BOOL bDemanded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 5312
    UTIL_ASSERT(pRes != NULL);

    if (!bDemanded) {
        pRes->Demand();
    }

    frameSize.cx = pRes->GetMosaicWidth(m_bDoubleSize);
    frameSize.cy = pRes->GetMosaicHeight(m_bDoubleSize);

    if (!bDemanded) {
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
        return Render3d(x, y, rMosaic, rClip, dwFlags, bDemanded);
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

            // TODO: Figure out why pointer needs to be rendered for every tile
            // in mosaic.
            g_pChitin->GetCurrentVideoMode()->RenderPointer();

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

// 0x7C56C0
void CVidMosaic::RenderTexture(INT x, INT y, const CSize& blitSize, const CRect& rClip, DWORD dwFlags)
{
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;

    x1 = static_cast<float>(x);
    y1 = static_cast<float>(y);
    x2 = static_cast<float>(x + blitSize.cx);
    y2 = static_cast<float>(y + blitSize.cy);
    x3 = 0.0f;
    y3 = 0.0f;
    x4 = static_cast<float>(blitSize.cx) / static_cast<float>(CVidInf::FX_WIDTH);
    y4 = static_cast<float>(blitSize.cy) / static_cast<float>(CVidInf::FX_HEIGHT);

    if (x < rClip.left) {
        x1 = static_cast<float>(rClip.left);
        x3 = static_cast<float>(rClip.left - x) / static_cast<float>(CVidInf::FX_WIDTH);
    }

    if (y < rClip.top) {
        y1 = static_cast<float>(rClip.top);
        y3 = static_cast<float>(rClip.top - y) / static_cast<float>(CVidInf::FX_HEIGHT);
    }

    if (x + blitSize.cx > rClip.right) {
        x2 = static_cast<float>(rClip.right);
        x4 = static_cast<float>(rClip.right - x) / static_cast<float>(CVidInf::FX_WIDTH);
    }

    if (y + blitSize.cy > rClip.bottom) {
        y2 = static_cast<float>(rClip.bottom);
        y4 = static_cast<float>(rClip.bottom - y) / static_cast<float>(CVidInf::FX_HEIGHT);
    }

    CVideo3d::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    x1 += CVideo3d::SUB_PIXEL_SHIFT;
    y1 += CVideo3d::SUB_PIXEL_SHIFT;
    x2 += CVideo3d::SUB_PIXEL_SHIFT;
    y2 += CVideo3d::SUB_PIXEL_SHIFT;

    CVideo3d::glBegin(GL_TRIANGLE_STRIP);
    CVideo3d::glTexCoord2f(x3, y3);
    CVideo3d::glVertex3f(x1, y1, 0.0f);
    CVideo3d::glTexCoord2f(x3, y4);
    CVideo3d::glVertex3f(x1, y2, 0.0f);
    CVideo3d::glTexCoord2f(x4, y3);
    CVideo3d::glVertex3f(x2, y1, 0.0f);
    CVideo3d::glTexCoord2f(x4, y4);
    CVideo3d::glVertex3f(x2, y2, 0.0f);
    CVideo3d::glEnd();
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7C5A00
BOOL CVidMosaic::Render3d(int x, int y, const CRect& rMosaic, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (pRes == NULL) {
        return FALSE;
    }

    if (!bDemanded) {
        pRes->Demand();
    }

    // NOTE: Original code is different and hard to replicate one to one. This
    // code is based on `CVidMosaic::Render` implementation and adjusted for
    // 3D stuff.
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

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    g_pChitin->cVideo.field_13E = 2;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, 2);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CRect rTile(0, 0, nTileSize, nTileSize);

    for (INT nTileY = nFirstTileY; nTileY < nLastTileY; nTileY++) {
        int destY = y + nTileY * nTileSize;

        rTile.bottom = min(nMosaicHeight - nTileY * nTileSize, nTileSize);
        if (destY + rTile.bottom < rClip.top || destY > rClip.bottom) {
            continue;
        }

        for (INT nTileX = nFirstTileX; nTileX < nLastTileX; nTileX++) {
            int destX = x + nTileX * nTileSize;

            rTile.right = min(nMosaicWidth - nTileX * nTileSize, nTileSize);
            if (destX + rTile.right < rClip.left || destX > rClip.right) {
                continue;
            }

            LONG lPitch = g_pChitin->cVideo.field_13A
                ? CVidTile::BYTES_PER_TEXEL * CVIDINF_FX_WIDTH
                : CVidTile::BYTES_PER_TEXEL * rTile.right;

            BOOL bSuccess = BltMos8To32(reinterpret_cast<DWORD*>(CVideo3d::texImageData),
                lPitch,
                nTileY * pRes->m_pHeader->nXTiles + nTileX,
                rTile,
                dwFlags);
            if (!bSuccess) {
                if (!bDemanded) {
                    pRes->Release();
                }
                return FALSE;
            }

            if (g_pChitin->cVideo.field_13A) {
                CVideo3d::glTexImage2D(GL_TEXTURE_2D,
                    0,
                    GL_RGBA,
                    CVidInf::FX_WIDTH,
                    CVidInf::FX_HEIGHT,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    CVideo3d::texImageData);
                g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
            } else {
                CVideo3d::glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0,
                    0,
                    rTile.Width(),
                    rTile.Height(),
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    CVideo3d::texImageData);
                g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
            }

            RenderTexture(destX, destY, rTile.Size(), rClip, dwFlags);
        }
    }

    if (!bDemanded) {
        pRes->Release();
    }

    return TRUE;
}

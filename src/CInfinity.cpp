#include "CInfinity.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CResWED.h"
#include "CScreenWorld.h"
#include "CTiledObject.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVideo3d.h"
#include "CVisibility.h"

// 0x851928
const DWORD CInfTileSet::USE_COLORKEY = 1;

// 0x85192C
const DWORD CInfTileSet::TRANSLUCENT = 2;

// 0x851930
const BYTE CInfTileSet::byte_851930 = 1;

// 0x851931
const BYTE CInfTileSet::byte_851931 = 2;

// 0x851932
const BYTE CInfTileSet::byte_851932 = 4;

// FIXME: Make const.
//
// 0x8B28B8
DWORD CInfTileSet::WATER_ALPHA = 128;

// NOTE: Unclear what this size represent. The number of elements is not
// validated.
//
// 0x8E7E40
TEXTURE CInfTileSet::m_aTextures[2700];

// 0x8F2700
int CInfTileSet::m_nTextures;

// 0x851934
const DWORD CInfinity::FXPREP_COPYFROMBACK = 0x80;

// 0x851938
const DWORD CInfinity::FXPREP_CLEARFILL = 0x100;

// 0x85193C
const DWORD CInfinity::MIRROR_FX = 0x10;

// 0x851940
const DWORD CInfinity::MIRROR_FX_UPDOWN = 0x20;

// 0x851944
const DWORD CInfinity::CLIPPING_IGNORE_VERTICAL = 0x400;

// 0x851948
const COLORREF CInfinity::RGB_DAY_COLOR = RGB(255, 255, 255);

// 0x85194C
const COLORREF CInfinity::RGB_NIGHT_COLOR = RGB(100, 100, 200);

// 0x851950
const COLORREF CInfinity::RGB_PRIMEDUSK_COLOR = RGB(255, 200, 200);

// 0x851954
const COLORREF CInfinity::RGB_PRIMEDAWN_COLOR = RGB(180, 200, 255);

// 0x851960
const COLORREF CInfinity::RGB_DAY_RAINCOLOR = RGB(110, 110, 110);

// 0x851964
const COLORREF CInfinity::RGB_NIGHT_RAINCOLOR = RGB(70, 70, 90);

// 0x851968
const COLORREF CInfinity::RGB_PRIMEDUSK_RAINCOLOR = RGB(90, 90, 100);

// 0x85196C
const COLORREF CInfinity::RGB_PRIMEDAWN_RAINCOLOR = RGB(90, 90, 100);

// 0x851970
const BYTE CInfinity::TRUE_DAWNDUSK_INTENSITY = 128;

// 0x85197A
const BYTE CInfinity::SCROLL_DELAY = 15;

// 0x851980
const DWORD CInfinity::RENDER_ERROR = 0;

// 0x851984
const DWORD CInfinity::RENDER_OK = 1;

// 0x851988
const DWORD CInfinity::RENDER_MESSAGESCREEN = 2;

// NOTE: Not sure if it belongs to `CInfinity`. Also unclear what's the need for
// separate setting which looks to be in sync with
// `CVidCell::TRANSLUCENT_BLTS_ON`.
//
// 0x8A85F4
BOOLEAN CInfinity::TRANSLUCENT_BLTS_ON = TRUE;

// 0x8E79D8
const CString CInfinity::DAWN_MOVIE("BGSUNRIS");

// 0x8E7A08
const CString CInfinity::DUSK_MOVIE("BGSUNSET");

// 0x8E7A0C
const CString CInfinity::NIGHT_RESREF_SUFFIX("N");

// 0x8E7968
const CString CInfinity::RAIN_RESREF_SUFFIX("R");

// 0x8E7538
CRect CInfinity::stru_8E7538(0, 0, 800, 490);

// 0x8E7548
CRect CInfinity::stru_8E7548(0, 0, 800, 600);

// 0x8E7958
CRect CInfinity::stru_8E7958(0, 0, 800, 316);

// 0x8E7988
CRect CInfinity::stru_8E7988(0, 0, 800, 461);

// 0x8E79A8
CRect CInfinity::stru_8E79A8(0, 0, 800, 450);

// 0x8E79B8
CRect CInfinity::stru_8E79B8(0, 0, 800, 433);

// 0x8E79C8
CRect CInfinity::stru_8E79C8(0, 0, 800, 540);

// 0x8E79E0
CRect CInfinity::stru_8E79E0(0, 0, 800, 493);

// 0x8E79F8
CRect CInfinity::stru_8E79F8(0, 0, 800, 476);

// 0x8E7A10
CRect CInfinity::stru_8E7A10(0, 0, 800, 354);

// 0x8E7970
const CResRef CInfinity::THUNDERRESREFS[3] = {
    CResRef("Amb_E13a"),
    CResRef("Amb_E13b"),
    CResRef("Amb_E13f"),
};

// NOTE: Inlined.
CInfTileSet::CInfTileSet()
{
    m_pResTiles = NULL;
    m_pVRamPool = NULL;
    m_nTiles = 0;
    m_rgbTintColor = RGB(255, 255, 255);
    m_rgbAddColor = RGB(0, 0, 0);
}

// 0x5CAF50
CInfTileSet::~CInfTileSet()
{
    if (m_pResTiles != NULL) {
        for (int index = 0; index < m_nTiles; index++) {
            CResInfTile* pTile = m_pResTiles[index];
            if (pTile != NULL) {
                // NOTE: Uninline.
                m_pVRamPool->EmptyTile(pTile->m_nVRamTile);

                g_pChitin->cDimm.Dump(m_pResTiles[index], 1, 0);

                if (m_pResTiles[index] != NULL) {
                    delete m_pResTiles[index];
                    m_pResTiles[index] = NULL;
                }
            }

            if (index % 700 == 699) {
                SleepEx(60, FALSE);
            }
        }

        free(m_pResTiles);
    }

    m_nTiles = 0;
}

// 0x5CB090
int CInfTileSet::AttachToVRam(int nTile)
{
    if (m_pVRamPool == NULL) {
        return -1;
    }

    if (nTile < 0 || nTile >= m_nTiles) {
        return -1;
    }

    CResInfTile* pTile = m_pResTiles[nTile];
    if (pTile == NULL) {
        return -1;
    }

    if (pTile->m_nVRamTile < 0) {
        int nVRamTile = m_pVRamPool->AssociateTile(this, nTile);
        m_pResTiles[nTile]->m_nVRamFlags &= ~0x2;
        if (nVRamTile == -1) {
            return 0;
        }
    } else {
        m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount++;
    }

    return m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount;
}

// 0x5CB190
int CInfTileSet::DetachFromVRam(int nTile)
{
    if (m_pVRamPool == NULL) {
        return -1;
    }

    if (nTile < 0 || nTile >= m_nTiles) {
        return -1;
    }

    CResInfTile* pTile = m_pResTiles[nTile];
    if (pTile == NULL) {
        return -1;
    }

    if (pTile->m_nVRamTile < 0) {
        return -1;
    }

    m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount--;

    if (m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount > 0) {
        return m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount;
    }

    m_pVRamPool->EmptyTile(pTile->m_nVRamTile);

    return 0;
}

// 0x5CB260
BOOL CInfTileSet::RenderToPrimary(LPDIRECTDRAWSURFACE pSurface, INT nTile, INT nStencilTile, const TILE_CODE& tileCode, BYTE nDualTileCode, int a6, DWORD dwFlags)
{
    DWORD dwNewFlags = 0;
    CRect rClip(0, 0, 64, 64);

    if ((dwFlags & 0x2) != 0) {
        dwNewFlags |= 0x8;
    }

    if ((dwFlags & 0x80000) != 0) {
        dwNewFlags |= 0x80000;
    }

    if ((dwFlags & 0x2000000) != 0) {
        dwNewFlags |= 0x2000000;
    }

    switch (nDualTileCode) {
    case 0:
        m_cVidTile.SetRes(m_pResTiles[nTile]);
        m_cVidTile.SetTintColor(m_rgbTintColor);
        m_cVidTile.SetAddColor(m_rgbAddColor);
        dwNewFlags |= 0x20000;
        break;
    case 1:
        m_cVidTile.SetRes(m_pResTiles[nTile]);
        m_cVidTile.SetAddColor(m_rgbAddColor);
        dwNewFlags |= 0x10000;
        break;
    case 2:
        m_cVidTile.SetRes(m_pResTiles[nTile]->m_pDualTileRes);
        m_cVidTile.SetTintColor(m_rgbTintColor);
        m_cVidTile.SetAddColor(m_rgbAddColor);
        dwNewFlags |= 0x20000;
        break;
    case 4:
        m_cVidTile.SetRes(m_pResTiles[nTile]->m_pDualTileRes);
        m_cVidTile.SetAddColor(m_rgbAddColor);
        dwNewFlags |= 0x10000;
        break;
    }

    if (nStencilTile != -1) {
        m_cVidTile.Render(pSurface, 0, 0, m_pResTiles[nStencilTile], rClip, dwNewFlags);
    } else {
        m_cVidTile.Render(pSurface, 0, 0, rClip, dwNewFlags);
    }

    CVisibilityMap::BltFogOWar(pSurface, tileCode);

    return TRUE;
}

// 0x5CB4A0
BOOL CInfTileSet::Render(CVidMode* pVidMode, INT nSurface, INT nTile, INT nStencilTile, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags, DWORD nColorKey, BYTE nDualTileCode, int a12)
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        return Render3d(nTile, nStencilTile, rDest, x, y, tileCode, dwFlags, nDualTileCode, a12);
    }

    g_pChitin->GetCurrentVideoMode()->RenderPointer();

    if (pVidMode == NULL) {
        return FALSE;
    }

    TILE_CODE renderCode;
    if (!GetTileRenderCode(nTile, renderCode)) {
        return FALSE;
    }

    if (renderCode.tileNW != tileCode.tileNW
        || renderCode.tileNE != tileCode.tileNE
        || renderCode.tileSW != tileCode.tileSW
        || renderCode.tileSE != tileCode.tileSE) {
        m_pResTiles[nTile]->m_nVRamFlags &= ~0x2;
    }

    LPDIRECTDRAWSURFACE pSurface;
    if (m_pVRamPool != NULL && m_pResTiles[nTile]->m_nVRamTile >= 0) {
        pSurface = m_pVRamPool->m_pSurfaces[m_pResTiles[nTile]->m_nVRamTile];

        if ((m_pResTiles[nTile]->m_nVRamFlags & 0x2) == 0) {
            RenderToPrimary(pSurface,
                nTile,
                nStencilTile,
                tileCode,
                nDualTileCode,
                a12,
                dwFlags);
            m_pResTiles[nTile]->m_nVRamFlags |= 0x2;
            m_pResTiles[nTile]->m_renderCode = tileCode;
        }
    } else {
        pSurface = pVidMode->GetFXSurfacePtr(dwFlags);
        RenderToPrimary(pSurface,
            nTile,
            nStencilTile,
            tileCode,
            nDualTileCode,
            a12,
            dwFlags);
    }

    return RenderToSecondary(pSurface, nSurface, rDest, x, y, dwFlags, nColorKey);
}

// 0x5CB630
BOOL CInfTileSet::RenderBlack(CVidMode* pVidMode, INT nSurface, const CRect& rDest, INT x, INT y)
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        CVisibilityMap::BltFogOWar3d(x, y, rDest, CVisibilityMap::UNEXPLORED_FULL);
        return TRUE;
    }

    DDBLTFX fx;
    fx.dwSize = sizeof(fx);
    fx.dwFillColor = pVidMode->ConvertToSurfaceRGB(pVidMode->ApplyBrightnessContrast(RGB(3, 1, 3)));

    LPDIRECTDRAWSURFACE pSurface = pVidMode->pSurfaces[nSurface];
    if (pSurface == NULL) {
        return FALSE;
    }

    CRect rClip(x, y, x + 64, y + 64);

    if (rClip.left < rDest.left) {
        rClip.left = rDest.left;
    }

    if (rClip.top < rDest.top) {
        rClip.top = rDest.top;
    }

    if (rClip.right > rDest.right) {
        rClip.right = rDest.right;
    }

    if (rClip.bottom > rDest.bottom) {
        rClip.bottom = rDest.bottom;
    }

    if (rClip.IsRectEmpty()) {
        return FALSE;
    }

    HRESULT hr;
    do {
        hr = g_pBaldurChitin->cVideo.cVidBlitter.Blt(pSurface,
            &rClip,
            NULL,
            NULL,
            DDBLT_WAIT | DDBLT_COLORFILL,
            &fx);
        pVidMode->CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    return TRUE;
}

// 0x5CB780
BOOL CInfTileSet::RenderToSecondary(LPDIRECTDRAWSURFACE pSurface, INT nSurface, const CRect& rDest, INT x, INT y, DWORD dwFlags, DWORD nColorKey)
{
    CVidMode* pVidMode = g_pBaldurChitin->GetCurrentVideoMode();

    LPDIRECTDRAWSURFACE pDestSurface = pVidMode->pSurfaces[nSurface];

    if (pSurface == NULL || pDestSurface == NULL) {
        return FALSE;
    }

    INT nDestX = x;
    INT nDestY = y;

    if (nDestX + 64 < rDest.left || nDestX >= rDest.right) {
        return TRUE;
    }

    if (nDestY + 64 < rDest.top || nDestY >= rDest.bottom) {
        return TRUE;
    }

    CRect rSrc(0, 0, 64, 64);

    if (nDestY < rDest.top) {
        rSrc.top = rDest.top - nDestY;
        nDestY = rDest.top;
    }

    if (nDestX < rDest.left) {
        rSrc.left = rDest.left - nDestX;
        nDestX = rDest.left;
    }

    if (nDestY + 64 > rDest.bottom) {
        rSrc.bottom = rDest.bottom - nDestY;
    }

    if (nDestX + 64 > rDest.right) {
        rSrc.right = rDest.right - nDestX;
    }

    if ((dwFlags & 1) != 0) {
        DDCOLORKEY ddck;
        ddck.dwColorSpaceLowValue = nColorKey;
        ddck.dwColorSpaceHighValue = nColorKey;
        pSurface->SetColorKey(DDCKEY_SRCBLT, &ddck);

        HRESULT hr;
        do {
            hr = g_pBaldurChitin->cVideo.cVidBlitter.BltFast(pDestSurface,
                nDestX,
                nDestY,
                pSurface,
                &rSrc,
                DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
            pVidMode->CheckResults(hr);
        } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
    } else {
        HRESULT hr;
        do {
            hr = g_pBaldurChitin->cVideo.cVidBlitter.BltFast(pDestSurface,
                nDestX,
                nDestY,
                pSurface,
                &rSrc,
                DDBLTFAST_WAIT);
            pVidMode->CheckResults(hr);
        } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
    }

    return TRUE;
}

// FIXME: `cResRef` should be reference.
// FIXME: `cDualResRef` should be reference.
//
// 0x5CB930
BOOL CInfTileSet::SetResID(RESID nNewID, CResRef cResRef, RESID nNewDualID, CResRef cDualResRef)
{
    if (m_nTiles != 0) {
        for (int index = 0; index < m_nTiles; index++) {
            if (m_pResTiles[index] != NULL) {
                if (m_pVRamPool != NULL) {
                    // NOTE: Uninline.
                    m_pVRamPool->EmptyTile(m_pResTiles[index]->m_nVRamTile);
                }
            }

            g_pChitin->cDimm.Dump(m_pResTiles[index], 1, 0);

            if (m_pResTiles[index] != NULL) {
                delete m_pResTiles[index];
                m_pResTiles[index] = NULL;
            }
        }

        free(m_pResTiles);
    }

    if (nNewDualID != 0) {
        m_nTiles = g_pChitin->cDimm.GetResNumber(nNewDualID, cDualResRef, 1003);
        if (m_nTiles <= 0) {
            return FALSE;
        }

        m_pResTiles = reinterpret_cast<CResInfTile**>(malloc(sizeof(CResInfTile*) * m_nTiles));

        for (int index = 0; index < m_nTiles; index++) {
            m_pResTiles[index] = new CResInfTile(TRUE, FALSE);
            if (m_pResTiles[index] != NULL) {
                m_pResTiles[index]->SetID(nNewID + index);

                if (m_pResTiles[index]->m_pDualTileRes == NULL) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
                    // __LINE__: 1139
                    UTIL_ASSERT(FALSE);
                }

                m_pResTiles[index]->m_pDualTileRes->SetID(nNewDualID + index);

                m_pResTiles[index]->field_58 = cResRef;

                if (m_pResTiles[index]->m_pDualTileRes == NULL) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
                    // __LINE__: 1175
                    UTIL_ASSERT(FALSE);
                }

                m_pResTiles[index]->m_pDualTileRes->field_58 = cDualResRef;
            }
        }
    } else {
        m_nTiles = g_pChitin->cDimm.GetResNumber(nNewID, cResRef, 1003);
        if (m_nTiles <= 0) {
            return FALSE;
        }

        m_pResTiles = reinterpret_cast<CResInfTile**>(malloc(sizeof(CResInfTile*) * m_nTiles));

        for (int index = 0; index < m_nTiles; index++) {
            m_pResTiles[index] = new CResInfTile(FALSE, FALSE);
            if (m_pResTiles[index] != NULL) {
                m_pResTiles[index]->SetID(nNewID + index);
                m_pResTiles[index]->field_58 = cResRef;
            }
        }
    }

    return TRUE;
}

// NOTE: Inlined.
BOOLEAN CInfTileSet::GetTileRenderCode(INT nTile, TILE_CODE& tileCode)
{
    if (nTile < 0 || nTile > m_nTiles) {
        return FALSE;
    }

    if (m_pResTiles[nTile] == NULL) {
        return FALSE;
    }

    tileCode = m_pResTiles[nTile]->m_renderCode;

    return TRUE;
}

// NOTE: Inlined.
BOOLEAN CInfTileSet::SetTileRenderCode(INT nTile, TILE_CODE& tileCode)
{
    if (nTile < 0 || nTile > m_nTiles) {
        return FALSE;
    }

    if (m_pResTiles[nTile] == NULL) {
        return FALSE;
    }

    m_pResTiles[nTile]->m_renderCode = tileCode;

    return TRUE;
}

// 0x5D29A0
BOOL CInfTileSet::Render3d(INT nTile, INT nStencilTile, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags, BYTE nDualTileCode, int a9)
{
    INT nTextureId;

    g_pChitin->GetCurrentVideoMode()->RenderPointer();

    TILE_CODE renderCode;
    if (!GetTileRenderCode(nTile, renderCode)) {
        return FALSE;
    }

    if (renderCode.tileNW != tileCode.tileNW
        || renderCode.tileNE != tileCode.tileNE
        || renderCode.tileSW != tileCode.tileSW
        || renderCode.tileSE != tileCode.tileSE) {
        m_pResTiles[nTile]->m_nVRamFlags &= ~0x2;
    }

    if (m_pVRamPool != NULL && m_pResTiles[nTile]->m_nVRamTile >= 0) {
        nTextureId = m_pResTiles[nTile]->m_nVRamTile + 9;

        if ((m_pResTiles[nTile]->m_nVRamFlags & 0x2) == 0) {
            ReadyTexture(nTextureId,
                nTile,
                nStencilTile,
                tileCode,
                nDualTileCode,
                a9,
                dwFlags);
            m_pResTiles[nTile]->m_nVRamFlags |= 0x2;
            m_pResTiles[nTile]->m_renderCode = tileCode;
        }
        RenderTexture(nTextureId, rDest, x, y, tileCode, dwFlags);
    } else {
        nTextureId = 2;
        ReadyTexture(nTextureId,
            nTile,
            nStencilTile,
            tileCode,
            nDualTileCode,
            a9,
            dwFlags);
        RenderTexture(nTextureId, rDest, x, y, tileCode, dwFlags);

        if (!g_pChitin->cVideo.field_13A) {
            g_pChitin->cVideo.field_13E = nTextureId;
            CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
            g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

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
        }
    }

    return TRUE;
}

// 0x5D2B90
BOOL CInfTileSet::ReadyTexture(INT nTextureId, INT nTile, INT nStencilTile, const TILE_CODE& tileCode, BYTE nDualTileCode, int a9, DWORD dwFlags)
{
    BOOL bResult;

    DWORD dwAlpha;
    DWORD dwTextureFlags;
    if ((dwFlags & TRANSLUCENT) != 0) {
        dwAlpha = WATER_ALPHA;
        dwTextureFlags = nStencilTile != -1 ? 0x0 : 0x2;
    } else {
        dwAlpha = 255;
        dwTextureFlags = 0;
    }

    // NOTE: Original code code is slightly different, each branch have
    // repeting code implying some inlined function.
    if (nDualTileCode == 0) {
        m_cVidTile.SetRes(m_pResTiles[nTile]);
    } else if (nDualTileCode == byte_851930) {
        m_cVidTile.SetRes(m_pResTiles[nTile]);
    } else if (nDualTileCode == byte_851931) {
        m_cVidTile.SetRes(m_pResTiles[nTile]->m_pDualTileRes);
    } else if (nDualTileCode == byte_851932) {
        m_cVidTile.SetRes(m_pResTiles[nTile]->m_pDualTileRes);
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity3d.cpp
        // __LINE__: 271
        UTIL_ASSERT(FALSE);
    }

    if (nStencilTile != -1) {
        bResult = m_cVidTile.ReadyTexture(nTextureId, m_pResTiles[nStencilTile], dwFlags, dwAlpha);
    } else {
        bResult = m_cVidTile.ReadyTexture(nTextureId, dwFlags, dwAlpha);
    }

    return bResult;
}

// 0x5D2D20
void CInfTileSet::RenderTexture(INT nTextureId, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags)
{
    if (x + 64 < rDest.left
        || x > rDest.right
        || y + 64 < rDest.top
        || y > rDest.bottom) {
        return;
    }

    m_cVidTile.RenderTexture(nTextureId,
        rDest,
        x,
        y,
        (dwFlags & TRANSLUCENT) != 0 ? 0x2 : 0x0);

    m_aTextures[m_nTextures].x = static_cast<SHORT>(x);
    m_aTextures[m_nTextures].y = static_cast<SHORT>(y);
    m_aTextures[m_nTextures].left = static_cast<SHORT>(rDest.left);
    m_aTextures[m_nTextures].top = static_cast<SHORT>(rDest.top);
    m_aTextures[m_nTextures].right = static_cast<SHORT>(rDest.right);
    m_aTextures[m_nTextures].bottom = static_cast<SHORT>(rDest.bottom);
    m_aTextures[m_nTextures].tileCode = tileCode;
    m_nTextures++;
}

// 0x5D2DE0
void CInfTileSet::sub_5D2DE0()
{
    INT x;
    INT y;
    CRect rDest;

    for (int index = 0; index < m_nTextures; index++) {
        x = m_aTextures[index].x;
        y = m_aTextures[index].y;
        rDest.left = m_aTextures[index].left;
        rDest.top = m_aTextures[index].top;
        rDest.right = m_aTextures[index].right;
        rDest.bottom = m_aTextures[index].bottom;
        CVisibilityMap::BltFogOWar3d(x, y, rDest, m_aTextures[index].tileCode);
    }
}

// NOTE: Inlined.
void CInfTileSet::Invalidate()
{
    for (int index = 0; index < m_nTiles; index++) {
        if (m_pResTiles[index] != NULL && m_pVRamPool != NULL) {
            m_pResTiles[index]->m_nVRamFlags &= ~0x2;
        }
    }
}

// -----------------------------------------------------------------------------

// 0x5CBC80
CResInfTile::CResInfTile(BOOLEAN a1, BOOLEAN a2)
{
    m_nVRamTile = -1;

    // TODO: Wrong.
    m_nVRamFlags = 0;

    m_renderCode = CVisibilityMap::EXPLORED_FULL;

    if (a1) {
        m_pDualTileRes = new CResTile();
    } else {
        m_pDualTileRes = NULL;
    }

    dwFlags &= ~0x2;
    dwFlags |= 0x1;
}

// 0x5CBD90
CResInfTile::~CResInfTile()
{
    if (m_pDualTileRes != NULL) {
        delete m_pDualTileRes;
    }
}

// -----------------------------------------------------------------------------

// 0x5CBDF0
CVRamPool::CVRamPool()
{
    m_nVTiles = 0;
    m_pTileDefs = NULL;
    m_pSurfaces = NULL;
}

// 0x5CBE00
CVRamPool::~CVRamPool()
{
    // NOTE: Uninline.
    DetachSurfaces();
}

// 0x5CBE70
BOOL CVRamPool::AttachSurfaces(CVidMode* pVidMode)
{
    if (pVidMode->GetType() != 0) {
        return FALSE;
    }

    if (pVidMode == NULL) {
        return FALSE;
    }

    CVidInf* pVidInf = static_cast<CVidInf*>(pVidMode);

    if (pVidInf->m_nVRamSurfaces <= 0) {
        return FALSE;
    }

    if (!g_pChitin->cVideo.Is3dAccelerated() && pVidInf->m_pVRamSurfaces == NULL) {
        return FALSE;
    }

    m_pSurfaces = pVidInf->m_pVRamSurfaces;
    m_nVTiles = pVidInf->m_nVRamSurfaces;
    m_pTileDefs = reinterpret_cast<TileDefinition*>(malloc(sizeof(TileDefinition) * m_nVTiles));

    for (int index = 0; index < m_nVTiles; index++) {
        m_pTileDefs[index].nTile = -1;
        m_pTileDefs[index].pTileSet = NULL;
        m_pTileDefs[index].nRefCount = 0;
    }

    return TRUE;
}

// 0x5CBF30
void CVRamPool::ClearAll()
{
    for (int index = 0; index < m_nVTiles; index++) {
        if (m_pTileDefs[index].pTileSet != NULL) {
            m_pTileDefs[index].pTileSet->m_pResTiles[m_pTileDefs[index].nTile]->m_nVRamTile = -1;
        }

        m_pTileDefs[index].nTile = -1;
        m_pTileDefs[index].pTileSet = NULL;
        m_pTileDefs[index].nRefCount = 0;
    }
}

// 0x5CBF90
BOOL CVRamPool::DetachSurfaces()
{
    // NOTE: Uninline.
    ClearAll();

    if (m_pTileDefs != NULL) {
        free(m_pTileDefs);
        m_pTileDefs = NULL;
    }

    m_pSurfaces = NULL;
    m_nVTiles = 0;

    return TRUE;
}

// 0x5CC010
void CVRamPool::InvalidateAll()
{
    for (int index = 0; index < m_nVTiles; index++) {
        if (m_pTileDefs[index].pTileSet != NULL) {
            m_pTileDefs[index].pTileSet->m_pResTiles[m_pTileDefs[index].nTile]->m_nVRamFlags &= ~0x2;
        }
    }
}

// NOTE: Inlined.
int CVRamPool::AssociateTile(CInfTileSet* pTileSet, int nTile)
{
    if (pTileSet != NULL) {
        for (int index = 0; index < m_nVTiles; index++) {
            if (m_pTileDefs[index].nTile == -1) {
                m_pTileDefs[index].nTile = nTile;
                m_pTileDefs[index].pTileSet = pTileSet;
                m_pTileDefs[index].nRefCount = 1;
                pTileSet->m_pResTiles[nTile]->m_nVRamTile = index;
                return index;
            }
        }
    }

    return -1;
}

// NOTE: Inlined.
BOOL CVRamPool::EmptyTile(int nVTile)
{
    if (nVTile < 0 || nVTile >= m_nVTiles) {
        return FALSE;
    }

    TileDefinition* pTileDef = &(m_pTileDefs[nVTile]);

    if (pTileDef->pTileSet != NULL) {
        pTileDef->pTileSet->m_pResTiles[pTileDef->nTile]->m_nVRamTile = -1;
    }

    pTileDef->nTile = -1;
    pTileDef->pTileSet = NULL;
    pTileDef->nRefCount = 0;

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x5CC360
CInfinity::CInfinity()
{
    pVidMode = NULL;
    m_areaType = 0;
    field_20 = 0;
    bWEDDemanded = FALSE;
    bInitialized = FALSE;
    bRefreshVRamRect = FALSE;
    m_bResizedViewPort = FALSE;
    nAreaX = 0;
    nAreaY = 0;
    nCurrentTileX = 0;
    nCurrentTileY = 0;
    nCurrentX = 0;
    nCurrentY = 0;
    m_ptCurrentPosExact.x = 0;
    m_ptCurrentPosExact.y = 0;
    nOffsetX = 0;
    nOffsetY = 0;
    nNewX = 0;
    nNewY = 0;
    field_98 = 0;
    field_9C = 0;
    field_A0 = 0;
    field_A4 = 0;
    field_A8 = 0;
    field_AC = 0;
    field_B0 = 0;
    field_B4 = 0;
    nTilesX = 0;
    nTilesY = 0;
    rViewPort.left = 0;
    rViewPort.top = 0;
    rViewPort.right = 0;
    rViewPort.bottom = 0;
    nVisibleTilesX = 0;
    nVisibleTilesY = 0;
    m_bMovieBroadcast = FALSE;
    pResWED = NULL;
    pVRPool = NULL;
    rVRamRect.left = -1;
    rVRamRect.top = -1;
    rVRamRect.right = -1;
    rVRamRect.bottom = -1;
    field_68 = -1;
    field_6C = -1;
    field_70 = -1;
    field_74 = -1;
    field_196 = 0;
    pTileSets[0] = NULL;
    pTileSets[1] = NULL;
    pTileSets[2] = NULL;
    pTileSets[3] = NULL;
    pTileSets[4] = NULL;
    m_rgbGlobalLighting = RGB(255, 255, 255);
    nThunderLength = 0;
    nCurrentLightningFrequency = 0;
    nNextLightningFrequency = 0;
    field_124 = 0;
    nCurrentRainLevel = 0;
    nNextRainLevel = 0;
    nCurrentSnowLevel = 0;
    field_134 = 0;
    field_138 = 0;
    field_13C = 0;
    nTimeToNextThunder = -1;
    m_bStartLightning = FALSE;
    m_bStopLightning = FALSE;
    m_rgbTimeOfDayGlobalLighting = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
    m_rgbLightningGlobalLighting = RGB(0, 0, 0);
    bRenderCallLightning = FALSE;
    cLightningPoint.x = -1;
    cLightningPoint.y = -1;
    nRenderLightningTimer = -1;
    m_lightningStrikeProb = 1;
    m_rgbOverCastGlobalLighting = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
    m_rgbTimeOfDayRainColor = RGB(110, 110, 110);
    m_rgbRainColor = RGB(110, 110, 110);
    m_requestDayNightCode = 1;
    field_15E = 0;
    m_renderDayNightCode = 1;
    m_oldRenderDayNightCode = 1;
    m_dayLightIntensity = -1;
    m_nLastTickCount = GetTickCount();
    m_ptScrollDest.x = -1;
    m_autoScrollSpeed = 0;
    m_ptScrollDest.y = -1;
    m_nScrollDelay = 0;
    m_updateListenPosition = 1;
    m_pArea = NULL;
    m_vbMessageScreen.SetResRef(CResRef(""), TRUE, TRUE);
    m_vbMessageScreen.m_bDoubleSize = FALSE;
    m_strMessageText = -1;
    m_nMessageEndTime = -1;
    m_bRenderMessage = 0;
    field_286 = 0;
    m_bScreenShake = FALSE;
    m_screenShakeDelta.x = 0;
    m_screenShakeDelta.y = 0;
    m_screenShakeDecrease.x = 0;
    m_screenShakeDecrease.y = 0;
}

// 0x5CC710
CInfinity::~CInfinity()
{
    if (bWEDDemanded) {
        FreeWED();
    }

    rViewPort.top = 0;
    rViewPort.left = 0;
    rViewPort.right = 0;
    rViewPort.bottom = 0;
    field_20 = 0;
    nAreaX = 0;
    nAreaY = 0;
    nOffsetX = 0;
    nOffsetY = 0;
    nNewX = 0;
    nNewY = 0;
    nTilesX = 0;
    nTilesY = 0;
    nVisibleTilesX = 0;
    nVisibleTilesY = 0;
    pResWED = NULL;
    pVRPool = NULL;
}

// 0x5CC7F0
BOOL CInfinity::AttachWED(CResWED* resNewWED, WORD areaType, BYTE dayNightCode)
{
    RESID nID;
    RESID nDualID;
    CResRef rrTileSet;
    CResRef rrDualTileSet;

    if (resNewWED == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
        // __LINE__: 1810
        UTIL_ASSERT(FALSE);
    }

    if (pResWED != NULL) {
        FreeWED();
    }

    pResWED = resNewWED;
    m_areaType = areaType;
    bWEDDemanded = TRUE;

    if (pResWED->Demand() == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
        // __LINE__: 1827
        UTIL_ASSERT_MSG(FALSE, "Demand for WED file failed.");
    }

    nTilesX = pResWED->m_pLayers[0].nTilesAcross;
    nAreaX = nTilesX * 64;
    nTilesY = pResWED->m_pLayers[0].nTilesDown;
    nAreaY = nTilesY * 64;

    pTileSets[0] = new CInfTileSet();

    if ((m_areaType & 0x40) != 0 && dayNightCode == 2) {
        rrTileSet = pResWED->m_pLayers[0].rrTileSet;
        rrDualTileSet = rrTileSet;

        nID = g_pChitin->cDimm.GetResID(rrTileSet, 1003);
        nDualID = g_pChitin->cDimm.GetResID(rrDualTileSet, 1003);
        if (nID == -1) {
            CString sTileSet;
            rrTileSet.CopyToString(sTileSet);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
            // __LINE__: 1875
            UTIL_ASSERT_MSG(FALSE, CString("Tile set") + sTileSet + " not found");
        }

        pTileSets[0]->SetResID(nDualID, rrDualTileSet, 0, CResRef(""));
    } else {
        rrTileSet = pResWED->m_pLayers[0].rrTileSet;
        nID = g_pChitin->cDimm.GetResID(rrTileSet, 1003);
        if (nID == -1) {
            CString sTileSet;
            rrTileSet.CopyToString(sTileSet);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
            // __LINE__: 1898
            UTIL_ASSERT_MSG(FALSE, CString("Tile set") + sTileSet + " not found");
        }

        pTileSets[0]->SetResID(nID, rrTileSet, 0, CResRef(""));
    }

    for (int index = 1; index < 5; index++) {
        pTileSets[index] = new CInfTileSet();

        if ((m_areaType & 0x4) != 0) {
            rrTileSet = pResWED->m_pLayers[index].rrTileSet;
            rrDualTileSet = rrTileSet;
            rrDualTileSet += RAIN_RESREF_SUFFIX;
            nID = g_pChitin->cDimm.GetResID(rrTileSet, 1003);
            if (nID != -1) {
                nDualID = g_pChitin->cDimm.GetResID(rrDualTileSet, 1003);
                pTileSets[index]->SetResID(nID, rrTileSet, nDualID, rrDualTileSet);
            }
        } else {
            rrTileSet = pResWED->m_pLayers[index].rrTileSet;
            nID = g_pChitin->cDimm.GetResID(rrTileSet, 1003);
            if (nID != -1) {
                pTileSets[index]->SetResID(nID, rrTileSet, 0, CResRef(""));
            }
        }
    }

    return TRUE;
}

// 0x5CCD00
BOOL CInfinity::AttachVRamPool(CVRamPool* pNewVRPool)
{
    if (pNewVRPool == NULL) {
        return FALSE;
    }

    pVRPool = pNewVRPool;

    for (int index = 0; index < 5; index++) {
        pTileSets[index]->m_pVRamPool = pNewVRPool;
    }

    return TRUE;
}

// 0x5CCD30
void CInfinity::CacheTiles()
{
    if (!g_pChitin->cNetwork.GetSessionOpen()
        || g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        DWORD dwFlags = 0;

        ULONG nTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
        ULONG nDelta = (CTimerWorld::TIME_DAY - CTimerWorld::TIME_DAWN) / 2;
        if (nTime >= nDelta + CTimerWorld::TIME_DAWN
            && nTime < nDelta + CTimerWorld::TIME_DUSK
            && (m_areaType & 0x40) != 0) {
            dwFlags |= 0x2;
        } else {
            dwFlags |= 0x1;
        }

        if ((m_areaType & 0x4) != 0 && nCurrentRainLevel != 0) {
            dwFlags |= 0x4;
        }

        for (int index = 0; index < 5; index++) {
            if (pTileSets[index] != NULL && pTileSets[index]->m_pResTiles != NULL) {
                for (int tile = 0; tile < pTileSets[index]->m_nTiles; tile++) {
                    if (tile % 10 < (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nTilesPrecachePercent + 5) / 10) {
                        CResTile* pRes = NULL;
                        if ((dwFlags & 0x6) != 0) {
                            pRes = pTileSets[index]->m_pResTiles[tile]->m_pDualTileRes;
                        }

                        if (pRes == NULL) {
                            pRes = pTileSets[index]->m_pResTiles[tile];
                        }

                        if (pRes != NULL) {
                            if (pRes->Demand() != NULL) {
                                pRes->Release();
                            }
                        }
                    }
                }
            }
        }
    }
}

// 0x5CCE90
BOOL CInfinity::AttachVRamRect(int x1, int y1, int x2, int y2)
{
    if (x1 < 0) {
        x1 = 0;
    }

    if (x1 >= nTilesX) {
        x1 = nTilesX - 1;
    }

    if (x2 < 0) {
        x2 = 0;
    }

    if (x2 >= nTilesX) {
        x2 = nTilesX - 1;
    }

    if (y1 < 0) {
        y1 = 0;
    }

    if (y1 >= nTilesY) {
        y1 = nTilesY - 1;
    }

    if (y2 < 0) {
        y2 = 0;
    }

    if (y2 >= nTilesY) {
        y2 = nTilesY - 1;
    }

    if (rVRamRect.left >= 0) {
        for (int y = rVRamRect.top; y <= rVRamRect.bottom; y++) {
            for (int x = rVRamRect.left; x <= rVRamRect.right; x++) {
                if (x < x1 || x > x2 || y < y1 || y > y2) {
                    WED_TILEDATA* pTileData = pResWED->GetTileData(0, x, y);
                    if (pTileData != NULL) {
                        if ((pTileData->bFlags & 0x1) == 0) {
                            WORD* pTileList = pResWED->GetTileList(0);
                            if (pTileList != NULL) {
                                if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                                    && pTileData->nSecondary != -1) {
                                    pTileSets[0]->DetachFromVRam(pTileData->nSecondary);
                                } else {
                                    for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                        pTileSets[0]->DetachFromVRam(pTileList[index + pTileData->nStartingTile]);
                                    }
                                }
                            }
                        }

                        if ((pTileData->bFlags & 0x1E) != 0) {
                            UINT nLayer;
                            switch (pTileData->bFlags & 0x1E) {
                            case 4:
                                nLayer = 2;
                                break;
                            case 8:
                                nLayer = 3;
                                break;
                            case 16:
                                nLayer = 4;
                                break;
                            default:
                                nLayer = 1;
                                break;
                            }

                            WED_LAYERHEADER* pLayer = pResWED->GetLayerHeader(nLayer);
                            if (pLayer != NULL) {
                                // NOTE: The following code shadows some variables. Find
                                // better names here or in the outside loops.
                                for (WORD y = 0; y < pLayer->nTilesDown; y++) {
                                    for (WORD x = 0; x < pLayer->nTilesAcross; x++) {
                                        WED_TILEDATA* pTileData = pResWED->GetTileData(nLayer, x, y);
                                        if (pTileData != NULL) {
                                            WORD* pTileList = pResWED->GetTileList(nLayer);
                                            if (pTileList != NULL) {
                                                for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                                    pTileSets[nLayer]->DetachFromVRam(pTileList[index + pTileData->nStartingTile]);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            if (rVRamRect.left < 0
                || x < rVRamRect.left
                || x > rVRamRect.right
                || y < rVRamRect.top
                || y > rVRamRect.bottom) {
                WED_TILEDATA* pTileData = pResWED->GetTileData(0, x, y);
                if (pTileData != NULL) {
                    if ((pTileData->bFlags & 0x1) == 0) {
                        WORD* pTileList = pResWED->GetTileList(0);
                        if (pTileList != NULL) {
                            if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                                && pTileData->nSecondary != -1) {
                                pTileSets[0]->AttachToVRam(pTileData->nSecondary);
                            } else {
                                for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                    pTileSets[0]->AttachToVRam(pTileList[index + pTileData->nStartingTile]);
                                }
                            }
                        }
                    }

                    if ((pTileData->bFlags & 0x1E) != 0) {
                        UINT nLayer;
                        switch (pTileData->bFlags & 0x1E) {
                        case 4:
                            nLayer = 2;
                            break;
                        case 8:
                            nLayer = 3;
                            break;
                        case 16:
                            nLayer = 4;
                            break;
                        default:
                            nLayer = 1;
                            break;
                        }

                        WED_LAYERHEADER* pLayer = pResWED->GetLayerHeader(nLayer);
                        if (pLayer != NULL) {
                            // NOTE: The following code shadows some variables. Find
                            // better names here or in the outside loops.
                            for (WORD y = 0; y < pLayer->nTilesDown; y++) {
                                for (WORD x = 0; x < pLayer->nTilesAcross; x++) {
                                    WED_TILEDATA* pTileData = pResWED->GetTileData(nLayer, x, y);
                                    if (pTileData != NULL) {
                                        WORD* pTileList = pResWED->GetTileList(nLayer);
                                        if (pTileList != NULL) {
                                            for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                                pTileSets[nLayer]->AttachToVRam(pTileList[index + pTileData->nStartingTile]);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    rVRamRect.left = x1;
    rVRamRect.right = x2;
    rVRamRect.top = y1;
    rVRamRect.bottom = y2;

    return TRUE;
}

// 0x5CD2E0
BOOL CInfinity::CancelRequestRect(unsigned char a1)
{
    if (field_68 < 0) {
        return FALSE;
    }

    if (field_196) {
        ScrollingCancelRequestRect(a1);
    }

    int nMinX = field_68;
    int nMinY = field_6C;
    int nMaxX = field_70;
    int nMaxY = field_74;

    if (nMinX < 0) {
        nMinX = 0;
    }

    if (nMinX >= nTilesX) {
        nMinX = nTilesX - 1;
    }

    if (nMaxX < 0) {
        nMaxX = 0;
    }

    if (nMaxX >= nTilesX) {
        nMaxX = nTilesX - 1;
    }

    if (nMinY < 0) {
        nMinY = 0;
    }

    if (nMinY >= nTilesY) {
        nMinY = nTilesY - 1;
    }

    if (nMaxY < 0) {
        nMaxY = 0;
    }

    if (nMaxY >= nTilesY) {
        nMaxY = nTilesY - 1;
    }

    for (int y = nMinY; y <= nMaxY; y++) {
        for (int x = nMinX; x <= nMaxX; x++) {
            CancelRequestTile(x, y, a1);
        }
    }

    field_68 = -1;
    field_6C = -1;
    field_70 = -1;
    field_74 = -1;

    return TRUE;
}

// 0x5CD3C0
void CInfinity::ScrollingCancelRequestRect(unsigned char a1)
{
    // TODO: Incomplete.
}

// 0x5CDA70
BOOL CInfinity::DetachVRamRect()
{
    if (rVRamRect.left < 0) {
        return FALSE;
    }

    for (int y = rVRamRect.top; y <= rVRamRect.bottom; y++) {
        for (int x = rVRamRect.left; x <= rVRamRect.right; x++) {
            WED_TILEDATA* pTileData = pResWED->GetTileData(0, x, y);
            if (pTileData != NULL) {
                if ((pTileData->bFlags & 0x1) == 0) {
                    WORD* pTileList = pResWED->GetTileList(0);
                    if (pTileList != NULL) {
                        if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                            && pTileData->nSecondary != -1) {
                            pTileSets[0]->DetachFromVRam(pTileData->nSecondary);
                        } else {
                            for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                pTileSets[0]->DetachFromVRam(pTileList[index + pTileData->nStartingTile]);
                            }
                        }
                    }
                }

                if ((pTileData->bFlags & 0x1E) != 0) {
                    UINT nLayer;
                    switch (pTileData->bFlags & 0x1E) {
                    case 4:
                        nLayer = 2;
                        break;
                    case 8:
                        nLayer = 3;
                        break;
                    case 16:
                        nLayer = 4;
                        break;
                    default:
                        nLayer = 1;
                        break;
                    }

                    WED_LAYERHEADER* pLayer = pResWED->GetLayerHeader(nLayer);
                    if (pLayer != NULL) {
                        // NOTE: The following code shadows some variables. Find
                        // better names here or in the outside loops.
                        for (WORD y = 0; y < pLayer->nTilesDown; y++) {
                            for (WORD x = 0; x < pLayer->nTilesAcross; x++) {
                                WED_TILEDATA* pTileData = pResWED->GetTileData(nLayer, x, y);
                                if (pTileData != NULL) {
                                    WORD* pTileList = pResWED->GetTileList(nLayer);
                                    if (pTileList != NULL) {
                                        for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                            pTileSets[nLayer]->DetachFromVRam(pTileList[index + pTileData->nStartingTile]);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    rVRamRect.left = -1;
    rVRamRect.top = -1;
    rVRamRect.right = -1;
    rVRamRect.bottom = -1;

    return TRUE;
}

// 0x5CDC60
BOOL CInfinity::DrawEllipse(const CPoint& ptCenter, const CSize& axes, COLORREF rgbColor)
{
    CPoint ptObjCenter;
    ptObjCenter.x = ptCenter.x + rViewPort.left - nCurrentX;
    ptObjCenter.y = ptCenter.y + rViewPort.top - nCurrentY;

    rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyFadeAmount(rgbColor);
    rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(rgbColor);
    return pVidMode->DrawEllipse(ptObjCenter,
        axes,
        rViewPort,
        rgbColor);
}

// 0x5CDDC0
BOOL CInfinity::DrawHighlightRect(const CRect& rSquare, COLORREF rgbColor, BYTE width)
{
    // TODO: Incomplete.
    return FALSE;
}

// 0x5CDED0
INT CInfinity::GetSegmentPoints(POINT** ppPoints, int nEndX, int nEndY, int nStartX, int nStartY)
{
    int nTmp;
    int nXDirection = 1;
    int nDx;
    int nDy;
    int nNumPts;

    if (nEndY > nStartY) {
        nTmp = nStartY;
        nStartY = nEndY;
        nEndY = nTmp;

        nTmp = nStartX;
        nStartX = nEndX;
        nEndX = nTmp;
    }

    nDx = nStartX - nEndX;
    nDy = nStartY - nEndY;

    if (nDx < 0) {
        nDx = -nDx;
        nXDirection = -1;
    }

    if (nDx > nDy) {
        nNumPts = nDx / 10 + 2;
        *ppPoints = new POINT[nNumPts];
        GetPointsOctant0(*ppPoints, nEndX, nEndY, nDx, nDy, nXDirection);
    } else {
        nNumPts = nDy / 10 + 2;
        *ppPoints = new POINT[nNumPts];
        GetPointsOctant1(*ppPoints, nEndX, nEndY, nDx, nDy, nXDirection);
    }

    return nNumPts;
}

// 0x5CDFC0
CPoint CInfinity::GetWorldCoordinates(const CPoint& ptScreen)
{
    CPoint ptWorld;

    if (rViewPort.PtInRect(ptScreen)) {
        ptWorld.x = ptScreen.x + nNewX - rViewPort.left;
        ptWorld.y = ptScreen.y + nNewY - rViewPort.top;
    } else {
        ptWorld.x = -1;
        ptWorld.y = -1;
    }

    return ptWorld;
}

// 0x5CE020
BOOL CInfinity::FreeWED()
{
    if (!bWEDDemanded) {
        return FALSE;
    }

    bInitialized = FALSE;
    CancelRequestRect(field_15E);
    DetachVRamRect();
    pResWED->Release();
    pResWED->CancelRequest();

    for (int index = 0; index < 5; index++) {
        if (pTileSets[index] != NULL) {
            delete pTileSets[index];
            pTileSets[index] = NULL;
        }
    }

    bWEDDemanded = FALSE;
    nTilesX = 0;
    nTilesY = 0;

    return TRUE;
}

// 0x5CE0A0
BOOL CInfinity::FXBltFrom(INT nDestSurface, CRect& rFXRect, INT x, INT y, INT nRefPointX, INT nRefPointY, DWORD dwFlags)
{
    if (g_pChitin->GetCurrentVideoMode()->m_nFade == 0) {
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
    // __LINE__: 3163
    UTIL_ASSERT(nDestSurface == CVIDINF_SURFACE_BACK);

    return static_cast<CVidInf*>(pVidMode)->FXBltToBack(rFXRect,
        rViewPort.left + x - nCurrentX,
        rViewPort.top + y - nCurrentY,
        nRefPointX,
        nRefPointY,
        rViewPort,
        dwFlags);
}

// 0x5CE130
BOOL CInfinity::FXPrep(CRect& rFXRect, DWORD dwFlags, INT nDestSurface, const CPoint& ptPos, const CPoint& ptReference)
{
    if ((dwFlags & 0x80) != 0 && nDestSurface == -1) {
        return FALSE;
    }

    if ((dwFlags & 0x80) != 0) {
        return static_cast<CVidInf*>(pVidMode)->FXPrep(rFXRect,
            dwFlags,
            CPoint(ptPos.x + rViewPort.left - nCurrentX, ptPos.y + rViewPort.top - nCurrentY),
            ptReference,
            rViewPort);
    } else {
        return static_cast<CVidInf*>(pVidMode)->FXPrep(rFXRect,
            dwFlags,
            CPoint(0, 0),
            CPoint(0, 0),
            CRect(0, 0, 0, 0));
    }
}

// 0x5CE1F0
BOOL CInfinity::FXLock(CRect& rBack, DWORD dwFlags)
{
    return static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->FXLock(rBack, dwFlags);
}

// 0x5CE230
BOOL CInfinity::FXTextOut(CVidFont* pFont, const CString& sString, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    return static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->FXTextOut(pFont, sString, x, y, rClip, dwFlags, bDemanded);
}

// 0x5CE280
BOOL CInfinity::FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue)
{
    if (g_pChitin->GetCurrentVideoMode()->m_nFade == 0) {
        return TRUE;
    }

    COLORREF rgbTintColor;
    if ((dwFlags & 0x10000) == 0) {
        rgbTintColor = pVidCell->GetTintColor();
        pVidCell->SetTintColor(g_pChitin->GetCurrentVideoMode()->ApplyFadeAmount(rgbTintColor));

        if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
            dwFlags |= 0x20000;
        }
    } else {
        rgbTintColor = dwFlags;
    }

    BOOL bResult = static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->FXRender(pVidCell, nRefPointX, nRefPointY, dwFlags, nTransValue);

    if ((dwFlags & 0x10000) == 0) {
        pVidCell->SetTintColor(rgbTintColor);
    }

    return bResult;
}

// 0x5CE350
BOOL CInfinity::FXRenderClippingPolys(INT nPosX, INT nPosY, INT nPosZ, const CPoint& ptRef, const CRect& rGCBounds, BOOLEAN bDithered, DWORD dwBlitFlags)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5CE930
BOOL CInfinity::FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef)
{
    return static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->FXUnlock(dwFlags, pFxRect, ptRef);
}

// 0x5CE960
COLORREF CInfinity::GetGlobalLighting()
{
    COLORREF rgbGlobalLighting;
    COLORREF rgbLightningGlobalLighting = m_rgbLightningGlobalLighting;
    COLORREF rgbOverCastGlobalLighting = m_rgbOverCastGlobalLighting;
    COLORREF rgbTimeOfDayGlobalLighting = m_rgbTimeOfDayGlobalLighting;

    rgbGlobalLighting = RGB(min(GetRValue(rgbTimeOfDayGlobalLighting), GetRValue(rgbOverCastGlobalLighting)),
        min(GetGValue(rgbTimeOfDayGlobalLighting), GetGValue(rgbOverCastGlobalLighting)),
        min(GetBValue(rgbTimeOfDayGlobalLighting), GetBValue(rgbOverCastGlobalLighting)));

    rgbGlobalLighting = RGB(min(GetRValue(rgbGlobalLighting) + GetRValue(rgbLightningGlobalLighting), 255),
        min(GetGValue(rgbGlobalLighting) + GetGValue(rgbLightningGlobalLighting), 255),
        min(GetBValue(rgbGlobalLighting) + GetBValue(rgbLightningGlobalLighting), 255));

    rgbGlobalLighting = g_pChitin->GetCurrentVideoMode()->ApplyFadeAmount(rgbGlobalLighting);

    return rgbGlobalLighting;
}

// 0x5CEA70
void CInfinity::GetPointsOctant0(POINT* pPoints, int nStartX, int nStartY, int nDx, int nDy, int nXDirection)
{
    int v1 = 2 * nDy;
    int v2 = 2 * nDy - 2 * nDx;
    int v3 = 2 * nDy - nDx;
    int nPointCounter = 9;
    int nIndex = 0;

    pPoints[nIndex].x = nStartX;
    pPoints[nIndex].y = nStartY;
    nIndex++;

    while (nDx > 10) {
        if (v3 < 0) {
            v3 += v1;
        } else {
            v3 += v2;
            nStartY++;
        }

        nStartX += nXDirection;

        if (nPointCounter-- == 0) {
            pPoints[nIndex].x = nStartX + rand() % 10;
            pPoints[nIndex].y = nStartY + rand() % 10;
            nIndex++;
            nPointCounter = 9;
        }

        nDx--;
    }

    while (nDx > 0) {
        if (v3 < 0) {
            v3 += v1;
        } else {
            v3 += v2;
            nStartY++;
        }

        nStartX += nXDirection;

        if (nPointCounter-- == 0) {
            pPoints[nIndex].x = nStartX;
            pPoints[nIndex].y = nStartY + rand() % nDx;
            nIndex++;
            nPointCounter = 9;
        }

        nDx--;
    }

    pPoints[nIndex].x = nStartX;
    pPoints[nIndex].y = nStartY;
}

// 0x5CEB90
void CInfinity::GetPointsOctant1(POINT* pPoints, int nStartX, int nStartY, int nDx, int nDy, int nXDirection)
{
    int v1 = 2 * nDx;
    int v2 = 2 * nDx - 2 * nDy;
    int v3 = 2 * nDx - nDy;
    int nPointCounter = 9;
    int nIndex = 0;

    pPoints[nIndex].x = nStartX;
    pPoints[nIndex].y = nStartY;
    nIndex++;

    while (nDy > 10) {
        if (v3 < 0) {
            v3 += v1;
        } else {
            v3 += v2;
            nStartX += nXDirection;
        }

        nStartY++;

        if (nPointCounter-- == 0) {
            pPoints[nIndex].x = nStartX + rand() % 10;
            pPoints[nIndex].y = nStartY + rand() % 10;
            nIndex++;
            nPointCounter = 9;
        }

        nDy--;
    }

    while (nDy > 0) {
        if (v3 < 0) {
            v3 += v1;
        } else {
            v3 += v2;
            nStartX += nXDirection;
        }

        nStartY++;

        if (nPointCounter-- == 0) {
            pPoints[nIndex].x = nStartX + rand() % nDy;
            pPoints[nIndex].y = nStartY;
            nIndex++;
            nPointCounter = 9;
        }

        nDy--;
    }

    pPoints[nIndex].x = nStartX;
    pPoints[nIndex].y = nStartY;
}

// 0x5CECB0
void CInfinity::GetViewPosition(INT& x, INT& y)
{
    x = nNewX;
    y = nNewY;
}

// 0x5D1100
BOOL CInfinity::SetViewPort(const CRect& rRect)
{
    LONG oldLeft = rViewPort.left;
    LONG oldTop = rViewPort.top;

    if (!bWEDDemanded) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
        // __LINE__: 5615
        UTIL_ASSERT(FALSE);
    }

    rViewPort = rRect;

    if ((nCurrentX != m_ptScrollDest.x || nCurrentY != m_ptScrollDest.y)
        && (m_ptScrollDest.x != -1 || m_ptScrollDest.y != -1)) {
        m_ptScrollDest.x += rViewPort.left - oldLeft;
        m_ptScrollDest.y += rViewPort.top - oldTop;
    }

    SetViewPosition(rViewPort.left + nCurrentX - oldLeft,
        rViewPort.top + nCurrentY - oldTop,
        TRUE);
    m_bResizedViewPort = TRUE;

    return TRUE;
}

// 0x5CEDE0
BOOL CInfinity::PostRender(CVidMode* pNewVidMode, int a2, CSearchBitmap* pVisibilityMap)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;
    CSnowStorm* pSnowStorm = &(pWorld->m_weather.m_snowStorm);
    CRainStorm* pRainStorm = &(pWorld->m_weather.m_rainStorm);

    pVidMode = pNewVidMode;
    if (pVidMode == NULL) {
        return FALSE;
    }

    if (nCurrentRainLevel != 0 && pRainStorm->IsInitialized()) {
        COLORREF rgbRainColor = g_pChitin->GetCurrentVideoMode()->ApplyFadeAmount(m_rgbRainColor);
        rgbRainColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(rgbRainColor);

        CRect rClip(nCurrentX,
            nCurrentY,
            nCurrentX + rViewPort.Width(),
            nCurrentY + rViewPort.Height());

        pRainStorm->Render(pVidMode,
            a2,
            rClip,
            rgbRainColor);
    }

    if (nCurrentSnowLevel != 0 && pSnowStorm->IsInitialized()) {
        COLORREF rgbSnowColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(m_rgbGlobalLighting);

        CRect rClip(nCurrentX,
            nCurrentY,
            nCurrentX + rViewPort.Width(),
            nCurrentY + rViewPort.Height());

        pSnowStorm->Render(pVidMode,
            a2,
            rClip,
            rgbSnowColor);
    }

    if (bRenderCallLightning) {
        CPoint ptLightning = GetScreenCoordinates(cLightningPoint);
        if (ptLightning.x != -1) {
            RenderLightning(a2,
                rViewPort,
                ptLightning.x,
                rViewPort.top,
                ptLightning.x,
                ptLightning.y,
                RGB(255, 255, 255),
                RGB(0, 200, 255),
                RGB(0, 50, 200));
        }
    }

    if (g_pChitin->GetCurrentVideoMode()->m_nFade != CVidMode::NUM_FADE_FRAMES) {
        CVidMode::RenderBlackFade3d();
    }

    return TRUE;
}

// 0x5CEFD0
DWORD CInfinity::Render(CVidMode* pNewVidMode, INT nSurface, INT nScrollState, CVisibilityMap* pVisibilityMap)
{
    ULONG currTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime;
    BYTE currRenderDayNightCode = m_renderDayNightCode;
    BYTE nRainCode = 0;
    DWORD dwRenderFlag = 0;

    if (g_pBaldurChitin->GetObjectGame()->m_nTimeStop != 0) {
        currTime = 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
    // __LINE__: 4184
    UTIL_ASSERT(pVisibilityMap != NULL);

    pVidMode = pNewVidMode;
    if (pVidMode == NULL) {
        return RENDER_ERROR;
    }

    if (m_bRenderMessage) {
        return RenderMessageScreen(pNewVidMode, nSurface);
    }

    if (nScrollState != 0
        || (m_ptScrollDest.x == -1 && m_ptScrollDest.y == -1)) {
        AdjustViewPosition(nScrollState);
    } else {
        Scroll(m_ptScrollDest, m_autoScrollSpeed);
    }

    if (!bInitialized) {
        return RENDER_ERROR;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    BOOL bWorldTimerActive = pGame->GetWorldTimer()->m_active;
    BOOL bTimeStop = pGame->m_nTimeStop;

    if (m_bScreenShake) {
        if (bWorldTimerActive && !bTimeStop) {
            SetViewPosition(nNewX + (m_screenShakeDelta.x >> CGameSprite::EXACT_SCALE),
                nNewY + (m_screenShakeDelta.y >> CGameSprite::EXACT_SCALE),
                TRUE);

            if (m_screenShakeDelta.x > 0 && (currTime & 7) < 4) {
                m_screenShakeDelta.x = min(m_screenShakeDecrease.x, m_screenShakeDelta.x) - m_screenShakeDelta.x;
                if (rand() % 2 == 0) {
                    m_screenShakeDelta.x = -m_screenShakeDelta.x;
                }
            } else {
                m_screenShakeDelta.x = -m_screenShakeDelta.x;
            }

            if (m_screenShakeDelta.y > 0 && (currTime & 7) < 4) {
                m_screenShakeDelta.y = min(m_screenShakeDecrease.y, m_screenShakeDelta.y) - m_screenShakeDelta.y;
            } else {
                m_screenShakeDelta.y = -m_screenShakeDelta.y;
            }
        }
    }

    if (currRenderDayNightCode != m_oldRenderDayNightCode) {
        CResWED* pNewResWED;
        if ((currRenderDayNightCode & 2) != 0) {
            CResRef wedResRef = pResWED->GetResRef();
            wedResRef += NIGHT_RESREF_SUFFIX;
            pNewResWED = static_cast<CResWED*>(g_pChitin->cDimm.GetResObject(wedResRef, 1001, TRUE));
        } else {
        }

        if (pNewResWED != NULL) {
            FreeWED();
            g_pChitin->cDimm.ReleaseResObject(pResWED);

            pResWED = pNewResWED;
            pResWED->Request();
            AttachWED(pResWED, m_areaType, currRenderDayNightCode);

            // NOTE: Uninline.
            AttachVRamPool(&(g_pBaldurChitin->GetObjectGame()->m_cVRamPool));

            m_pArea->SetNewResWED(pResWED);

            if (pVRPool != NULL) {
                // NOTE: Uninline.
                pVRPool->InvalidateAll();
            }
        }

        bRefreshVRamRect = TRUE;
        bInitialized = TRUE;
        m_oldRenderDayNightCode = currRenderDayNightCode;
    }

    COLORREF rgbNewGlobalLighting = GetGlobalLighting();
    if (rgbNewGlobalLighting != m_rgbGlobalLighting) {
        if (!g_pChitin->cVideo.Is3dAccelerated()) {
            if (pVRPool != NULL) {
                // NOTE: Uninline.
                pVRPool->InvalidateAll();
            }
        }
        m_rgbGlobalLighting = rgbNewGlobalLighting;
    }

    pVidMode->rgbGlobalTint = m_rgbGlobalLighting;

    if ((m_areaType & 0x4) != 0) {
        int oldRainLevel = nCurrentRainLevel;
        if (oldRainLevel != nNextRainLevel) {
            nCurrentRainLevel = nNextRainLevel;
            if (oldRainLevel == 0 || nCurrentRainLevel == 0) {
                // NOTE: Uninline.
                InvalidateRainTiles();
            }
        }

        if (nCurrentRainLevel != 0) {
            nRainCode = 4;
        }
    }

    if (nNewX != nCurrentX
        || nNewY != nCurrentY
        || bRefreshVRamRect
        || m_bResizedViewPort) {
        if (bRefreshVRamRect) {
            bRefreshVRamRect = FALSE;
            CancelRequestRect(field_15E);
            DetachVRamRect();
        }

        if (m_bResizedViewPort) {
            CVidMode::Set3dClipRect(rViewPort);
        }

        m_bResizedViewPort = FALSE;

        nCurrentX = nNewX;
        nCurrentY = nNewY;

        if (nCurrentX >= 0) {
            nCurrentTileX = nCurrentX / 64;
            nOffsetX = 64 - nCurrentX % 64;
        } else {
            nCurrentTileX = (nCurrentX - 63) / 64;
            nOffsetX = -nCurrentX % 64;
        }

        if (nCurrentY >= 0) {
            nCurrentTileY = nCurrentY / 64;
            nOffsetY = 64 - nCurrentY % 64;
        } else {
            nCurrentTileY = (nCurrentY - 63) / 64;
            nOffsetY = -nCurrentY % 64;
        }

        nVisibleTilesX = nOffsetX != 0
            ? (rViewPort.Width() - nOffsetX) / 64 + 2
            : rViewPort.Width() / 64 + 1;

        nVisibleTilesY = nOffsetY != 0
            ? (rViewPort.Height() - nOffsetY) / 64 + 2
            : rViewPort.Height() / 64 + 1;

        if (((rViewPort.Width() - nOffsetX) & 63) != 0) {
            nVisibleTilesX++;
        }

        if (((rViewPort.Height() - nOffsetY) & 63) != 0) {
            nVisibleTilesX++;
        }

        if (nScrollState == 0 || nScrollState == 9) {
            RequestRect(nCurrentTileX - 3,
                nCurrentTileY - 3,
                nCurrentTileX + nVisibleTilesX + 2,
                nCurrentTileY + nVisibleTilesY + 2);
        } else {
            ScrollingRequestRect(nCurrentTileX,
                nCurrentTileY,
                nCurrentTileX + nVisibleTilesX - 1,
                nCurrentTileY + nVisibleTilesY - 1,
                nScrollState);
        }

        AttachVRamRect(nCurrentTileX,
            nCurrentTileY,
            nCurrentTileX + nVisibleTilesX - 1,
            nCurrentTileY + nVisibleTilesY - 1);
    } else if (field_196) {
        if (nCurrentX >= 0) {
            nCurrentTileX = nCurrentX / 64;
        } else {
            nCurrentTileX = (nCurrentX - 63) / 64;
        }

        if (nCurrentY >= 0) {
            nCurrentTileY = nCurrentY / 64;
        } else {
            nCurrentTileY = (nCurrentY - 63) / 64;
        }

        RequestRect(nCurrentTileX,
            nCurrentTileY,
            nCurrentTileX + nVisibleTilesX + 2,
            nCurrentTileY + nVisibleTilesY + 2);
    }

    for (int nTileY = nCurrentTileY; nTileY < nCurrentTileY + nVisibleTilesY; nTileY++) {
        for (int nTileX = nCurrentTileX; nTileX < nCurrentTileX + nVisibleTilesX; nTileX++) {
            int x;
            if (nOffsetX) {
                x = nOffsetX + (nTileX - nCurrentTileX - 1) * 64;
            } else {
                x = (nTileX - nCurrentTileX) * 64;
            }
            x += rViewPort.left;

            int y;
            if (nOffsetY) {
                y = nOffsetY + (nTileY - nCurrentTileY - 1) * 64;
            } else {
                y = (nTileY - nCurrentTileY) * 64;
            }
            y += rViewPort.top;

            WED_TILEDATA* pTileData = pResWED->GetTileData(0, nTileX, nTileY);
            if (pTileData != NULL) {
                dwRenderFlag &= ~0x3;
                if ((pTileData->bFlags & 0x1E) != 0) {
                    UINT nLayer;
                    switch (pTileData->bFlags & 0x1E) {
                    case 4:
                        nLayer = 2;
                        break;
                    case 8:
                        nLayer = 3;
                        break;
                    case 16:
                        nLayer = 4;
                        break;
                    default:
                        nLayer = 1;
                        break;
                    }

                    if (pResWED->GetLayerHeader(nLayer) != NULL) {
                        WED_TILEDATA* pSubData = pResWED->GetTileData(nLayer, 0, 0);
                        if (pSubData != NULL) {
                            WORD* pTileList = pResWED->GetTileList(nLayer);
                            if (pTileList != NULL) {
                                pTileSets[nLayer]->m_rgbTintColor = m_rgbGlobalLighting;

                                pTileSets[nLayer]->Render(pVidMode,
                                    nSurface,
                                    pTileList[pSubData->nStartingTile + (currTime / 2) % pSubData->nNumTiles],
                                    -1,
                                    rViewPort,
                                    x,
                                    y,
                                    CVisibilityMap::EXPLORED_FULL,
                                    0,
                                    0,
                                    nRainCode,
                                    0);

                                dwRenderFlag |= 0x3;
                            }
                        }
                    }
                }

                if ((pTileData->bFlags & 0x1) == 0) {
                    WORD* pTileList = pResWED->GetTileList(0);
                    if (pTileList != NULL) {
                        int nAnimSpeed = pTileData->bAnimSpeed;
                        if (nAnimSpeed == 0) {
                            nAnimSpeed = 1;
                        }

                        pTileSets[0]->m_rgbTintColor = m_rgbGlobalLighting;

                        WORD nTile;
                        if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                            && pTileData->nSecondary != -1) {
                            nTile = pTileData->nSecondary;
                        } else {
                            nTile = pTileList[pTileData->nStartingTile + (currTime / nAnimSpeed) % pTileData->nNumTiles];
                        }

                        TILE_CODE tileCode;
                        pVisibilityMap->GetTileCode(nTileY * nTilesX + nTileX, tileCode);

                        if ((pTileData->bFlags & 0x1E) != 0) {
                            pTileSets[0]->Render(pVidMode,
                                nSurface,
                                nTile,
                                pTileData->nSecondary,
                                rViewPort,
                                x,
                                y,
                                tileCode,
                                dwRenderFlag,
                                pVidMode->field_24,
                                0,
                                0);
                        } else {
                            pTileSets[0]->Render(pVidMode,
                                nSurface,
                                nTile,
                                -1,
                                rViewPort,
                                x,
                                y,
                                tileCode,
                                dwRenderFlag,
                                0,
                                0,
                                0);
                        }
                    }
                } else {
                    if ((pTileData->bFlags & 0x1E) == 0) {
                        pTileSets[0]->RenderBlack(pVidMode,
                            nSurface,
                            rViewPort,
                            x,
                            y);
                    }
                }
            } else {
                pTileSets[0]->RenderBlack(pVidMode,
                    nSurface,
                    rViewPort,
                    x,
                    y);
            }
        }
    }

    if (m_bScreenShake) {
        if (bWorldTimerActive
            && !bTimeStop
            && nNewX != -1) {
            SetViewPosition(nNewX, nNewY, TRUE);
            if (m_screenShakeDelta.x == 0 || m_screenShakeDelta.y == 0) {
                m_bScreenShake = FALSE;
            }
        }
    }

    if (g_pChitin->cVideo.Is3dAccelerated()) {
        CVidMode::RenderTint3d(m_rgbGlobalLighting, rViewPort);
    }

    return RENDER_OK;
}

// 0x5CFB40
BOOL CInfinity::RenderLightning(INT nSurface, CRect& rSurface, INT nStartX, INT nStartY, INT nEndX, INT nEndY, COLORREF rgbCenter, COLORREF rgbMiddle, COLORREF rgbOuter)
{
    int nRange;
    int nSeg1;
    int nSeg2;
    int nSeg3;
    int nSeg4;
    POINT pPoints[5];
    POINT* pSegPoints1;
    POINT* pSegPoints2;
    POINT* pSegPoints3;
    POINT* pSegPoints4;

    if (pVidMode == NULL) {
        pVidMode = g_pChitin->GetCurrentVideoMode();
    }

    // NOTE: Original code is messy.
    pPoints[0].x = nStartX;
    pPoints[0].y = nStartY;
    pPoints[1].x = pPoints[0].x + (nEndX - pPoints[0].x) / 4;
    pPoints[1].y = pPoints[0].y + (nEndY - pPoints[0].y) / 4;
    pPoints[2].x = pPoints[1].x + (nEndX - pPoints[1].x) / 4;
    pPoints[2].y = pPoints[1].y + (nEndY - pPoints[1].y) / 4;
    pPoints[3].x = pPoints[2].x + (nEndX - pPoints[2].x) / 4;
    pPoints[3].y = pPoints[2].y + (nEndY - pPoints[2].y) / 4;
    pPoints[4].x = nEndX;
    pPoints[4].y = nEndY;

    nRange = abs((nEndX - nStartX) / 4) + abs((nEndY - nStartY) / 4);
    pPoints[1].x += rand() % nRange - nRange / 2;
    pPoints[1].y += rand() % nRange - nRange / 2;
    pPoints[2].x += rand() % nRange - nRange / 2;
    pPoints[2].y += rand() % nRange - nRange / 2;
    pPoints[3].x += rand() % nRange - nRange / 2;
    pPoints[3].y += rand() % nRange - nRange / 2;

    nSeg1 = GetSegmentPoints(&pSegPoints1, pPoints[0].x, pPoints[0].y, pPoints[1].x, pPoints[1].y);
    nSeg2 = GetSegmentPoints(&pSegPoints2, pPoints[1].x, pPoints[1].y, pPoints[2].x, pPoints[2].y);
    nSeg3 = GetSegmentPoints(&pSegPoints3, pPoints[2].x, pPoints[2].y, pPoints[3].x, pPoints[3].y);
    nSeg4 = GetSegmentPoints(&pSegPoints4, pPoints[3].x, pPoints[3].y, pPoints[4].x, pPoints[4].y);

    pVidMode->PolyLine(nSurface, rSurface, pSegPoints1, nSeg1, rgbOuter, 5);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints2, nSeg2, rgbOuter, 5);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints3, nSeg3, rgbOuter, 5);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints4, nSeg4, rgbOuter, 5);

    pVidMode->PolyLine(nSurface, rSurface, pSegPoints1, nSeg1, rgbMiddle, 3);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints2, nSeg2, rgbMiddle, 3);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints3, nSeg3, rgbMiddle, 3);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints4, nSeg4, rgbMiddle, 3);

    pVidMode->PolyLine(nSurface, rSurface, pSegPoints1, nSeg1, rgbCenter, 1);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints2, nSeg2, rgbCenter, 1);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints3, nSeg3, rgbCenter, 1);
    pVidMode->PolyLine(nSurface, rSurface, pSegPoints4, nSeg4, rgbCenter, 1);

    delete[] pSegPoints1;
    delete[] pSegPoints2;
    delete[] pSegPoints3;
    delete[] pSegPoints4;

    return TRUE;
}

// 0x5CFE80
BOOL CInfinity::RequestRect(int x1, int y1, int x2, int y2)
{
    CRect r(0, 0, nTilesX, nTilesY);

    CancelRequestRect(field_15E);

    BYTE flags;
    if ((m_areaType & 0x40) != 0) {
        flags = m_requestDayNightCode;
    } else {
        flags = 1;
    }

    if ((m_areaType & 0x4) != 0 && nCurrentRainLevel != 0) {
        flags |= 0x4;
    }

    field_15E = flags;

    int nMinX = max(x1 + 3, 0);
    int nMaxX = min(x2 - 3, nTilesX - 1);
    int nMinY = max(y1 + 3, 0);
    int nMaxY = min(y2 - 3, nTilesY - 1);

    for (int y = nMinY; y < nMaxY; y++) {
        for (int x = nMinX; x < nMaxX; x++) {
            RequestTile(x, y, flags, CDimm::PRIORITY_HIGH);
        }
    }

    for (int delta = 0; delta < 3; delta++) {
        for (int x = x1; x < x2; x++) {
            if (r.PtInRect(CPoint(x, y1 + delta))) {
                RequestTile(x, y1 + delta, flags, CDimm::PRIORITY_MEDIUM);
            }

            if (r.PtInRect(CPoint(x, y1 - delta))) {
                RequestTile(x, y1 - delta, flags, CDimm::PRIORITY_MEDIUM);
            }
        }
    }

    for (int y = y1 + 3; y < y2 - 3; y++) {
        for (int delta = 0; delta < 3; delta++) {
            if (r.PtInRect(CPoint(x1 + delta, y))) {
                RequestTile(x1 + delta, y, flags, CDimm::PRIORITY_MEDIUM);
            }

            if (r.PtInRect(CPoint(x1 - delta, y))) {
                RequestTile(x1 - delta, y, flags, CDimm::PRIORITY_MEDIUM);
            }
        }
    }

    field_68 = x1;
    field_6C = y1;
    field_70 = x2;
    field_74 = y2;

    field_196 = 0;

    return TRUE;
}

// 0x5D00C0
BOOL CInfinity::ScrollingRequestRect(int x1, int y1, int x2, int y2, INT nScrollState)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x5D07B0
void CInfinity::CancelRequestTile(int x, int y, unsigned char a3)
{
    BYTE v1 = (a3 & 0x4) != 0 ? 0x4 : 0x1;
    a3 &= 0x3;

    WED_TILEDATA* pTileData = pResWED->GetTileData(0, x, y);
    if (pTileData == NULL) {
        return;
    }

    if ((pTileData->bFlags & 0x1) == 0) {
        WORD* pTileList = pResWED->GetTileList(0);
        if (pTileList != NULL) {
            if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                && pTileData->nSecondary != -1) {
                if (pTileData->nSecondary >= 0 && pTileData->nSecondary < pTileSets[0]->m_nTiles) {
                    CResInfTile* pRes = pTileSets[0]->m_pResTiles[pTileData->nSecondary];
                    if (pRes != NULL) {
                        if ((a3 & 1) != 0) {
                            pRes->CancelRequest();
                        }

                        if ((a3 & 0x2) != 0) {
                            if (pRes->m_pDualTileRes != NULL) {
                                pRes->m_pDualTileRes->CancelRequest();
                            }
                        }

                        // FIXME: Will never be true.
                        if ((a3 & 0x4) != 0) {
                            if (pRes->m_pDualTileRes != NULL) {
                                pRes->m_pDualTileRes->CancelRequest();
                            }
                        }
                    }
                } else {
                    for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                        int nTile = pTileList[index + pTileData->nStartingTile];
                        if (nTile < pTileSets[0]->m_nTiles) {
                            CResInfTile* pRes = pTileSets[0]->m_pResTiles[nTile];
                            if (pRes != NULL) {
                                if ((a3 & 1) != 0) {
                                    pRes->CancelRequest();
                                }

                                if ((a3 & 0x2) != 0) {
                                    if (pRes->m_pDualTileRes != NULL) {
                                        pRes->m_pDualTileRes->CancelRequest();
                                    }
                                }

                                // FIXME: Will never be true.
                                if ((a3 & 0x4) != 0) {
                                    if (pRes->m_pDualTileRes != NULL) {
                                        pRes->m_pDualTileRes->CancelRequest();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if ((pTileData->bFlags & 0x1E) != 0) {
        UINT nLayer;
        switch (pTileData->bFlags & 0x1E) {
        case 4:
            nLayer = 2;
            break;
        case 8:
            nLayer = 3;
            break;
        case 16:
            nLayer = 4;
            break;
        default:
            nLayer = 1;
            break;
        }

        WED_LAYERHEADER* pLayer = pResWED->GetLayerHeader(nLayer);
        if (pLayer != NULL) {
            // NOTE: The following code shadows some variables. Find
            // better names here or in the outside loops.
            for (WORD y = 0; y < pLayer->nTilesDown; y++) {
                for (WORD x = 0; x < pLayer->nTilesAcross; x++) {
                    WED_TILEDATA* pTileData = pResWED->GetTileData(nLayer, x, y);
                    if (pTileData != NULL) {
                        WORD* pTileList = pResWED->GetTileList(nLayer);
                        if (pTileList != NULL) {
                            for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                int nTile = pTileList[index + pTileData->nStartingTile];
                                if (nTile < pTileSets[0]->m_nTiles) {
                                    CResInfTile* pRes = pTileSets[0]->m_pResTiles[nTile];
                                    if (pRes != NULL) {
                                        if ((v1 & 1) != 0) {
                                            pRes->CancelRequest();
                                        }

                                        // FIXME: Will never be true.
                                        if ((v1 & 0x2) != 0) {
                                            if (pRes->m_pDualTileRes != NULL) {
                                                pRes->m_pDualTileRes->CancelRequest();
                                            }
                                        }

                                        if ((v1 & 0x4) != 0) {
                                            if (pRes->m_pDualTileRes != NULL) {
                                                pRes->m_pDualTileRes->CancelRequest();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (pTileData->nSecondary != -1) {
        if (pResWED->GetTileList(0) != NULL) {
            if (pTileData->nSecondary >= 0 && pTileData->nSecondary < pTileSets[0]->m_nTiles) {
                CResInfTile* pRes = pTileSets[0]->m_pResTiles[pTileData->nSecondary];
                if (pRes != NULL) {
                    if ((a3 & 1) != 0) {
                        pRes->CancelRequest();
                    }

                    if ((a3 & 0x2) != 0) {
                        if (pRes->m_pDualTileRes != NULL) {
                            pRes->m_pDualTileRes->CancelRequest();
                        }
                    }

                    // FIXME: Will never be true.
                    if ((a3 & 0x4) != 0) {
                        if (pRes->m_pDualTileRes != NULL) {
                            pRes->m_pDualTileRes->CancelRequest();
                        }
                    }
                }
            }
        }
    }
}

// 0x5D0AD0
void CInfinity::RequestTile(int x, int y, unsigned char a3, int priority)
{
    BYTE v1 = (a3 & 0x4) != 0 ? 0x4 : 0x1;
    a3 &= 0x3;

    WED_TILEDATA* pTileData = pResWED->GetTileData(0, x, y);
    if (pTileData == NULL) {
        return;
    }

    if ((pTileData->bFlags & 0x1) == 0) {
        WORD* pTileList = pResWED->GetTileList(0);
        if (pTileList != NULL) {
            if ((CTiledObject::STATE_SECONDARY_TILE & pTileData->wFlags) != 0
                && pTileData->nSecondary != -1) {
                if (pTileData->nSecondary >= 0 && pTileData->nSecondary < pTileSets[0]->m_nTiles) {
                    CResInfTile* pRes = pTileSets[0]->m_pResTiles[pTileData->nSecondary];
                    if (pRes != NULL) {
                        if ((a3 & 1) != 0) {
                            pRes->SetPriority(priority);
                            pRes->Request();
                        }

                        if ((a3 & 0x2) != 0) {
                            if (pRes->m_pDualTileRes != NULL) {
                                pRes->m_pDualTileRes->SetPriority(priority);
                                pRes->m_pDualTileRes->Request();
                            }
                        }

                        // FIXME: Will never be true.
                        if ((a3 & 0x4) != 0) {
                            if (pRes->m_pDualTileRes != NULL) {
                                pRes->m_pDualTileRes->SetPriority(priority);
                                pRes->m_pDualTileRes->Request();
                            }
                        }
                    }
                } else {
                    for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                        int nTile = pTileList[index + pTileData->nStartingTile];
                        if (nTile < pTileSets[0]->m_nTiles) {
                            CResInfTile* pRes = pTileSets[0]->m_pResTiles[nTile];
                            if (pRes != NULL) {
                                if ((a3 & 1) != 0) {
                                    pRes->SetPriority(priority);
                                    pRes->Request();
                                }

                                if ((a3 & 0x2) != 0) {
                                    if (pRes->m_pDualTileRes != NULL) {
                                        pRes->m_pDualTileRes->SetPriority(priority);
                                        pRes->m_pDualTileRes->Request();
                                    }
                                }

                                // FIXME: Will never be true.
                                if ((a3 & 0x4) != 0) {
                                    if (pRes->m_pDualTileRes != NULL) {
                                        pRes->m_pDualTileRes->SetPriority(priority);
                                        pRes->m_pDualTileRes->Request();
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if ((pTileData->bFlags & 0x1E) != 0) {
        UINT nLayer;
        switch (pTileData->bFlags & 0x1E) {
        case 4:
            nLayer = 2;
            break;
        case 8:
            nLayer = 3;
            break;
        case 16:
            nLayer = 4;
            break;
        default:
            nLayer = 1;
            break;
        }

        WED_LAYERHEADER* pLayer = pResWED->GetLayerHeader(nLayer);
        if (pLayer != NULL) {
            // NOTE: The following code shadows some variables. Find
            // better names here or in the outside loops.
            for (WORD y = 0; y < pLayer->nTilesDown; y++) {
                for (WORD x = 0; x < pLayer->nTilesAcross; x++) {
                    WED_TILEDATA* pTileData = pResWED->GetTileData(nLayer, x, y);
                    if (pTileData != NULL) {
                        WORD* pTileList = pResWED->GetTileList(nLayer);
                        if (pTileList != NULL) {
                            for (WORD index = 0; index < pTileData->nNumTiles; index++) {
                                int nTile = pTileList[index + pTileData->nStartingTile];
                                if (nTile < pTileSets[0]->m_nTiles) {
                                    CResInfTile* pRes = pTileSets[0]->m_pResTiles[nTile];
                                    if (pRes != NULL) {
                                        if ((v1 & 1) != 0) {
                                            pRes->SetPriority(priority);
                                            pRes->Request();
                                        }

                                        // FIXME: Will never be true.
                                        if ((v1 & 0x2) != 0) {
                                            if (pRes->m_pDualTileRes != NULL) {
                                                pRes->m_pDualTileRes->SetPriority(priority);
                                                pRes->m_pDualTileRes->Request();
                                            }
                                        }

                                        if ((v1 & 0x4) != 0) {
                                            if (pRes->m_pDualTileRes != NULL) {
                                                pRes->m_pDualTileRes->SetPriority(priority);
                                                pRes->m_pDualTileRes->Request();
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (pTileData->nSecondary != -1) {
        if (pResWED->GetTileList(0) != NULL) {
            if (pTileData->nSecondary >= 0 && pTileData->nSecondary < pTileSets[0]->m_nTiles) {
                CResInfTile* pRes = pTileSets[0]->m_pResTiles[pTileData->nSecondary];
                if (pRes != NULL) {
                    if ((a3 & 1) != 0) {
                        pRes->SetPriority(priority);
                        pRes->Request();
                    }

                    if ((a3 & 0x2) != 0) {
                        if (pRes->m_pDualTileRes != NULL) {
                            pRes->m_pDualTileRes->SetPriority(priority);
                            pRes->m_pDualTileRes->Request();
                        }
                    }

                    // FIXME: Will never be true.
                    if ((a3 & 0x4) != 0) {
                        if (pRes->m_pDualTileRes != NULL) {
                            pRes->m_pDualTileRes->SetPriority(priority);
                            pRes->m_pDualTileRes->Request();
                        }
                    }
                }
            }
        }
    }
}

// 0x5D0E90
BOOL CInfinity::InitViewPort(const CRect& rRect)
{
    if (!bWEDDemanded) {
        return FALSE;
    }

    nOffsetX = rRect.left;
    nOffsetY = rRect.top;

    rViewPort.left = rRect.left;
    rViewPort.top = rRect.top;
    rViewPort.right = rRect.right;
    rViewPort.bottom = rRect.bottom;

    EnterCriticalSection(&(m_pArea->field_1FC));
    m_bResizedViewPort = TRUE;
    LeaveCriticalSection(&(m_pArea->field_1FC));

    nVisibleTilesX = rRect.Width() / 64 + 1;
    nVisibleTilesY = rRect.Height() / 64 + 1;

    rVRamRect.left = -1;
    rVRamRect.top = -1;
    rVRamRect.right = -1;
    rVRamRect.bottom = -1;

    field_68 = -1;
    field_6C = -1;
    field_70 = -1;
    field_74 = -1;

    nOffsetX = 0;
    nOffsetY = 0;

    nNewX = 0;
    nNewY = 0;

    nCurrentTileX = 0;
    nCurrentTileY = 0;

    nCurrentX = 0;
    nCurrentY = 0;

    m_ptCurrentPosExact.x = 0;
    m_ptCurrentPosExact.y = 0;

    CancelRequestRect(field_15E);
    DetachVRamRect();

    nCurrentTileX = nCurrentX / 64;
    nCurrentTileY = nCurrentY / 64;

    nOffsetX = nCurrentX % 64;
    nOffsetY = nCurrentY % 64;

    if (static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->m_nVRamSurfaces <= CVidMode::word_8BA320) {
        RequestRect(nCurrentTileX - 3,
            nCurrentTileY - 3,
            nCurrentTileX + nVisibleTilesX + 2,
            nCurrentTileY + nVisibleTilesY + 2);
    } else {
        RequestRect(0, 0, nTilesX, nTilesY);
    }

    bRefreshVRamRect = TRUE;
    bInitialized = TRUE;

    return TRUE;
}

// 0x5D11F0
BOOL CInfinity::SetViewPosition(INT x, INT y, BOOLEAN bSetExactScale)
{
    CSingleLock posLock(&m_currentPosCritSect, FALSE);
    posLock.Lock(INFINITE);

    if (x < 0) {
        x = 0;
        m_ptCurrentPosExact.x = 0;
    }

    if (x > nAreaX - rViewPort.Width()) {
        x = nAreaX - rViewPort.Width();
        if (x < 0) {
            x /= 2;
        }
        m_ptCurrentPosExact.x = 10000 * x;
    }

    if (y < 0) {
        y = 0;
        m_ptCurrentPosExact.y = 0;
    }

    if (y > nAreaY - rViewPort.Height()) {
        y = nAreaY - rViewPort.Height();
        if (y < 0) {
            y = 0;
        }
        m_ptCurrentPosExact.y = 10000 * y;
    }

    nNewX = x;
    nNewY = y;

    if (bSetExactScale == TRUE) {
        m_ptCurrentPosExact.x = 10000 * x;
        m_ptCurrentPosExact.y = 10000 * y;
    }

    m_updateListenPosition = TRUE;

    posLock.Unlock();

    return TRUE;
}

// 0x5D1340
void CInfinity::CallLightning(INT xWorldPos, INT yWorldPos)
{
    m_bStartLightning = TRUE;
    bRenderCallLightning = TRUE;
    cLightningPoint.x = xWorldPos;
    cLightningPoint.y = yWorldPos;
    nRenderLightningTimer = 30;
}

// 0x5D1380
void CInfinity::Scroll(CPoint ptDest, SHORT speed)
{
    // TODO: Incomplete.
}

// 0x5D1750
void CInfinity::SetCurrentWeather(COLORREF rgbOvercast, SHORT nWeather, int nWeatherLevel, int nLightningFrequency)
{
    m_rgbOverCastGlobalLighting = rgbOvercast;

    switch (nWeather) {
    case 0:
        nCurrentLightningFrequency = 0;
        nTimeToNextThunder = -1;
        nNextRainLevel = nWeatherLevel;
        break;
    case 1:
        nNextLightningFrequency = nLightningFrequency;
        if (nLightningFrequency != 0) {
            nCurrentLightningFrequency = nLightningFrequency;
            nTimeToNextThunder = 0;
        } else {
            nCurrentLightningFrequency = 0;
            m_bStopLightning = TRUE;
        }
        nNextRainLevel = nWeatherLevel;
        break;
    case 2:
        nCurrentSnowLevel = nWeatherLevel;
        break;
    }
}

// 0x5D17E0
void CInfinity::SetDay()
{
    m_bMovieBroadcast = FALSE;
    if ((m_areaType & 0x40) == 0 && (m_areaType & 0x2) != 0) {
        m_dayLightIntensity = -1;
        m_rgbTimeOfDayGlobalLighting = RGB_DAY_COLOR;
        m_rgbTimeOfDayRainColor = RGB_DAY_RAINCOLOR;
        m_requestDayNightCode &= ~0x2;
        m_requestDayNightCode |= 0x1;
        m_renderDayNightCode &= ~0x2;
        m_renderDayNightCode |= 0x1;
    }
}

// 0x5D1840
void CInfinity::SetNight()
{
    m_bMovieBroadcast = FALSE;
    if ((m_areaType & 0x2) != 0) {
        m_dayLightIntensity = 0;
        m_rgbTimeOfDayGlobalLighting = RGB_NIGHT_COLOR;
        m_rgbTimeOfDayRainColor = RGB_NIGHT_RAINCOLOR;
        m_requestDayNightCode &= ~0x1;
        m_requestDayNightCode |= 0x2;
        m_renderDayNightCode &= ~0x1;
        m_renderDayNightCode |= 0x2;
    }
}

// 0x5D1890
void CInfinity::SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    if ((m_areaType & 0x40) == 0) {
        if ((m_areaType & 0x2) != 0) {
            BYTE nNewIntensity = nIntensity * 2;

            if (nIntensity < TRUE_DAWNDUSK_INTENSITY) {
                m_dayLightIntensity = nIntensity;
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_PRIMEDAWN_COLOR,
                    RGB_NIGHT_COLOR,
                    nNewIntensity);
                m_rgbTimeOfDayRainColor = GetFadedColor(RGB_PRIMEDAWN_RAINCOLOR,
                    RGB_NIGHT_RAINCOLOR,
                    nNewIntensity);
            } else {
                m_dayLightIntensity = nIntensity;
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_DAY_COLOR,
                    RGB_PRIMEDAWN_COLOR,
                    nNewIntensity);
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_DAY_RAINCOLOR,
                    RGB_PRIMEDAWN_RAINCOLOR,
                    nNewIntensity);
            }
        } else {
            if (g_pChitin->cNetwork.GetSessionOpen()
                && g_pChitin->cNetwork.GetSessionHosting()
                && g_pBaldurChitin->GetObjectGame()->ExtendedDayNightAreaActive()) {
                SetDawnMultiHost(nIntensity);
            }
        }
    }
}

// 0x5D1A40
void CInfinity::SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    if ((m_areaType & 0x40) == 0) {
        if ((m_areaType & 0x2) != 0) {
            BYTE nNewIntensity = nIntensity * 2;

            if (nIntensity < TRUE_DAWNDUSK_INTENSITY) {
                m_dayLightIntensity = nIntensity;
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_PRIMEDUSK_COLOR,
                    RGB_NIGHT_COLOR,
                    nNewIntensity);
                m_rgbTimeOfDayRainColor = GetFadedColor(RGB_PRIMEDUSK_RAINCOLOR,
                    RGB_NIGHT_RAINCOLOR,
                    nNewIntensity);
            } else {
                m_dayLightIntensity = nIntensity;
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_DAY_COLOR,
                    RGB_PRIMEDUSK_COLOR,
                    nNewIntensity);
                m_rgbTimeOfDayGlobalLighting = GetFadedColor(RGB_DAY_RAINCOLOR,
                    RGB_PRIMEDUSK_RAINCOLOR,
                    nNewIntensity);
            }
        } else {
            if (g_pChitin->cNetwork.GetSessionOpen()
                && g_pChitin->cNetwork.GetSessionHosting()
                && g_pBaldurChitin->GetObjectGame()->ExtendedDayNightAreaActive()) {
                // NOTE: Uninline.
                SetDuskMultiHost(nIntensity);
            }
        }
    }
}

// #noop
// 0x799CA0
void CInfinity::SetApproachingDawn()
{
}

// #noop
// 0x799CA0
void CInfinity::SetApproachingDusk()
{
}

// 0x5D1C00
void CInfinity::UpdateLightning()
{
    g_pBaldurChitin->GetCurrentVideoMode()->rgbGlobalTint = GetGlobalLighting();
}

// 0x5D1C30
void CInfinity::AdjustViewPosition(BYTE nScrollState)
{
    LONG nScrollSpeed;
    DWORD nCurrentTickCount;
    DWORD nDeltaT;
    int v1;
    int v2;
    int v3;

    if (m_nScrollDelay != 0) {
        nScrollSpeed = (15 - m_nScrollDelay)
            * g_pBaldurChitin->GetObjectGame()->GetScrollSpeed()
            / 15;
    } else {
        nScrollSpeed = g_pBaldurChitin->GetObjectGame()->GetScrollSpeed();
    }

    v1 = 10000 * nScrollSpeed;
    v2 = (30000 * nScrollSpeed) / 4;
    v3 = (10000 * nScrollSpeed) / 2;

    nCurrentTickCount = GetTickCount();

    if (nCurrentTickCount >= m_nLastTickCount) {
        nDeltaT = nCurrentTickCount - m_nLastTickCount;
        if (nDeltaT > 500) {
            nDeltaT = 500;
        }
    } else {
        nDeltaT = 500;
    }

    m_nLastTickCount = nCurrentTickCount;

    if (nScrollState != 0 && nScrollState != 9) {
        m_ptScrollDest.x = -1;
        m_ptScrollDest.y = -1;

        switch (nScrollState) {
        case 1:
            m_ptCurrentPosExact.y -= v3 * nDeltaT / 50;
            break;
        case 2:
            m_ptCurrentPosExact.x += v3 * nDeltaT / 50;
            m_ptCurrentPosExact.y -= v2 * nDeltaT / 50;
            break;
        case 3:
            m_ptCurrentPosExact.x += v1 * nDeltaT / 50;
            break;
        case 4:
            m_ptCurrentPosExact.x += v3 * nDeltaT / 50;
            m_ptCurrentPosExact.y += v2 * nDeltaT / 50;
            break;
        case 5:
            m_ptCurrentPosExact.y += v3 * nDeltaT / 50;
            break;
        case 6:
            m_ptCurrentPosExact.x -= v3 * nDeltaT / 50;
            m_ptCurrentPosExact.y += v2 * nDeltaT / 50;
            break;
        case 7:
            m_ptCurrentPosExact.x -= v1 * nDeltaT / 50;
            break;
        case 8:
            m_ptCurrentPosExact.x -= v3 * nDeltaT / 50;
            m_ptCurrentPosExact.y -= v2 * nDeltaT / 50;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\Infinity.cpp
            // __LINE__: 6461
            UTIL_ASSERT(FALSE);
        }

        SetViewPosition(m_ptCurrentPosExact.x / 10000,
            m_ptCurrentPosExact.y / 10000,
            FALSE);
    }
}

// 0x5D1F30
void CInfinity::AIUpdate()
{
    if (m_bRenderMessage
        && m_nMessageEndTime != -1
        && m_nMessageEndTime < GetTickCount()) {
        m_bRenderMessage = FALSE;
        m_nMessageEndTime = -1;
        for (WORD cnt = 0; cnt < field_286; cnt++) {
            if (m_vbMessageScreen.GetRes() != NULL) {
                m_vbMessageScreen.GetRes()->CancelRequest();
            }
        }
        field_286 = 0;
    }

    if (m_nScrollDelay > 0) {
        m_nScrollDelay--;
    }

    if (m_updateListenPosition) {
        m_updateListenPosition = FALSE;
        m_pArea->SetListenPosition();
    }

    // NOTE: Uninline.
    g_pChitin->GetCurrentVideoMode()->UpdateFade();

    if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_active) {
        if (nThunderLength > 0) {
            nThunderLength--;
            if (nThunderLength <= 0) {
                nThunderLength = 0;
                m_bStopLightning = TRUE;
                nTimeToNextThunder = -1;
            }
        }

        if (nRenderLightningTimer >= 0) {
            nRenderLightningTimer--;
            if (nRenderLightningTimer <= 0) {
                nRenderLightningTimer = -1;
                bRenderCallLightning = FALSE;
            }
        }

        if (nTimeToNextThunder != -1) {
            nTimeToNextThunder--;
            if (nTimeToNextThunder <= 0) {
                nTimeToNextThunder = -1;
                m_bStartLightning = TRUE;
            }
        } else {
            switch (nCurrentLightningFrequency) {
            case 64:
                nTimeToNextThunder = rand() % 1000 + 150;
                break;
            case 128:
                nTimeToNextThunder = rand() % 700 + 100;
                break;
            case 192:
                nTimeToNextThunder = rand() % 200 + 45;
                break;
            }
        }

        if (m_bStartLightning) {
            INT nNumber;

            m_bStartLightning = FALSE;

            nNumber = rand();
            m_rgbRainColor = RGB(255, 255, 255);
            m_rgbLightningGlobalLighting = RGB(nNumber % 155, nNumber % 155, nNumber % 155);

            // NOTE: Uninline.
            sndThunder.SetResRef(THUNDERRESREFS[rand() % 3], TRUE, TRUE);

            sndThunder.SetChannel(1, 0);

            switch (nNextRainLevel) {
            case 0:
                sndThunder.SetVolume(rand() % 10 + 40);
                break;
            case 4:
                sndThunder.SetVolume(rand() % 10 + 50);
                break;
            case 8:
                sndThunder.SetVolume(rand() % 10 + 80);
                break;
            case 12:
                sndThunder.SetVolume(rand() % 10 + 90);
                break;
            }

            if (!g_pChitin->cNetwork.GetSessionOpen()
                || g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bWeatherEnabled
                    && sndThunder.GetVolume() > 85
                    && rand() % 100 < m_lightningStrikeProb) {
                    m_pArea->OnLightningStrike();
                }
            }

            sndThunder.Play(FALSE);

            nThunderLength = (rand() % 15) + 1;
        }

        if (m_bStopLightning) {
            m_bStopLightning = FALSE;
            m_rgbLightningGlobalLighting = RGB(0, 0, 0);
            m_rgbRainColor = m_rgbTimeOfDayRainColor;
            nTimeToNextThunder = -1;
        }
    }
}

// 0x5D2350
void CInfinity::SwapVRamTiles(WORD wFromTile, WORD wToTile)
{
    TILE_CODE tileCode = CVisibilityMap::EXPLORED_FULL;

    INT nRet = pTileSets[0]->DetachFromVRam(wFromTile);

    // NOTE: Uninline.
    pTileSets[0]->GetTileRenderCode(wFromTile, tileCode);

    if (nRet != -1) {
        pTileSets[0]->AttachToVRam(wToTile);

        // NOTE: Uninline.
        pTileSets[0]->SetTileRenderCode(wToTile, tileCode);
    }
}

// FIXME: `resRef` should be reference.
//
// 0x5D23D0
void CInfinity::SetMessageScreen(CResRef resRef, DWORD strText, DWORD nDuration)
{
    m_vbMessageScreen.SetResRef(resRef, TRUE, TRUE);
    m_vbMessageScreen.m_bDoubleSize = g_pBaldurChitin->field_4A2C;

    field_286++;
    m_strMessageText = strText;

    if (nDuration == -1) {
        m_nMessageEndTime = -1;
    } else {
        m_nMessageEndTime = GetTickCount() + nDuration;
    }

    m_bRenderMessage = TRUE;
}

// 0x5D2530
DWORD CInfinity::RenderMessageScreen(CVidMode* pNewVidMode, INT nSurface)
{
    // TODO: Incomplete.

    return RENDER_MESSAGESCREEN;
}

// 0x452C30
void CInfinity::SetAreaType(WORD areaType)
{
    m_areaType = areaType;
}

// NOTE: Inlined.
COLORREF CInfinity::GetFadedColor(COLORREF rgbBrighter, COLORREF rgbDarker, BYTE nIntensity)
{
    return RGB((GetRValue(rgbBrighter) - GetRValue(rgbDarker)) * nIntensity / 256 + GetRValue(rgbDarker),
        (GetGValue(rgbBrighter) - GetGValue(rgbDarker)) * nIntensity / 256 + GetGValue(rgbDarker),
        (GetBValue(rgbBrighter) - GetBValue(rgbDarker)) * nIntensity / 256 + GetBValue(rgbDarker));
}

// NOTE: Inlined.
void CInfinity::SetDawnMultiHost(BYTE nIntensity)
{
    if (nIntensity >= TRUE_DAWNDUSK_INTENSITY && !m_bMovieBroadcast) {
        g_pBaldurChitin->m_pEngineWorld->ReadyMovie(CResRef(DAWN_MOVIE), FALSE);
        m_bMovieBroadcast = TRUE;
    }
}

// NOTE: Inlined.
void CInfinity::SetDuskMultiHost(BYTE nIntensity)
{
    if (nIntensity < TRUE_DAWNDUSK_INTENSITY && !m_bMovieBroadcast) {
        g_pBaldurChitin->m_pEngineWorld->ReadyMovie(CResRef(DUSK_MOVIE), FALSE);
        m_bMovieBroadcast = TRUE;
    }
}

// NOTE: Inlined.
CPoint CInfinity::GetScreenCoordinates(const CPoint& ptWorld)
{
    CPoint ptScreen;

    ptScreen.x = ptWorld.x - nNewX + rViewPort.left;
    ptScreen.y = ptWorld.y - nNewY + rViewPort.top;

    if (!rViewPort.PtInRect(ptScreen)) {
        ptScreen.x = -1;
        ptScreen.y = -1;
    }

    return ptScreen;
}

// NOTE: Inlined.
void CInfinity::InvalidateRainTiles()
{
    if ((m_areaType & 0x4) != 0) {
        for (int index = 1; index < 5; index++) {
            // NOTE: Uninline.
            pTileSets[index]->Invalidate();
        }
    }
}

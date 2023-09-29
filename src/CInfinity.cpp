#include "CInfinity.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CResWED.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVisibility.h"

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

// 0x85197A
const BYTE CInfinity::SCROLL_DELAY = 15;

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
        m_pResTiles[nTile]->m_nVRamFlags &= 0x2;
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

    dwFlags &= 0x2;
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
    field_128 = 0;
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
    field_15B = 1;
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
    field_28C = 0;
    field_294 = 0;
    field_290 = 0;
    field_29C = 0;
    field_298 = 0;
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

// 0x5CD2E0
BOOL CInfinity::CancelRequestRect(int a1)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x5CDA70
BOOL CInfinity::DetachVRamRect()
{
    // TODO: Incomplete.

    return FALSE;
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
    // TODO: Incomplete.

    return 0;
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
        m_rgbTimeOfDayGlobalLighting = 0xFFFFFF;
        m_rgbTimeOfDayRainColor = 0x6E6E6E;
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
        m_rgbTimeOfDayGlobalLighting = 0xC86464;
        m_rgbTimeOfDayRainColor = 0x5A4646;
        m_requestDayNightCode &= ~0x1;
        m_requestDayNightCode |= 0x2;
        m_renderDayNightCode &= ~0x1;
        m_renderDayNightCode |= 0x2;
    }
}

// 0x5D1890
void CInfinity::SetDawn()
{
    // TODO: Incomplete.
}

// 0x5D1A40
void CInfinity::SetDusk()
{
    // TODO: Incomplete.
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

// 0x452C30
void CInfinity::SetAreaType(WORD areaType)
{
    m_areaType = areaType;
}

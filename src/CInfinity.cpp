#include "CInfinity.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidInf.h"

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

// 0x5CC360
CInfinity::CInfinity()
{
    // TODO: Incomplete.
}

// 0x5CC710
CInfinity::~CInfinity()
{
    // TODO: Incomplete.
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

// 0x5CE930
BOOL CInfinity::FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef)
{
    return static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode())->FXUnlock(dwFlags, pFxRect, ptRef);
}

// 0x5CECB0
void CInfinity::GetViewPosition(INT& x, INT& y)
{
    x = nNewX;
    y = nNewY;
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
    // TODO: Incomplete.
}

// 0x452C30
void CInfinity::SetAreaType(WORD areaType)
{
    m_areaType = areaType;
}

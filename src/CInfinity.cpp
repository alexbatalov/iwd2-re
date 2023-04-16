#include "CInfinity.h"

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

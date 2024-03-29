#include "CWeather.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVidPalette.h"

// 0x84EE74
const COLORREF CWeather::OVERCAST_COLOR = RGB(180, 180, 180);

// 0x84EE78
const COLORREF CWeather::RGB_OVERCAST_INCREMENT = RGB(75, 75, 75);

// 0x84EE7C
const USHORT CWeather::VOLUME_LIGHT = 20;

// 0x84EE7E
const USHORT CWeather::VOLUME_MEDIUM = 50;

// 0x84EE80
const USHORT CWeather::VOLUME_HEAVY = 100;

// 0x8E2074
const SHORT CWeather::WEATHER_DURATION_MIN = CTimerWorld::TIMESCALE_MSEC_PER_HOUR + CTimerWorld::TIMESCALE_MSEC_PER_SEC * CTimerWorld::TIMESCALE_SEC_PER_MIN;

// 0x8E2066
const SHORT CWeather::WEATHER_DURATION_MAX = CTimerWorld::TIMESCALE_MSEC_PER_HOUR + 2 * CTimerWorld::TIMESCALE_MSEC_PER_SEC * CTimerWorld::TIMESCALE_SEC_PER_MIN;

// 0x8E2068
const SHORT CWeather::WEATHER_DURATION_MULTIPLAYER = WEATHER_DURATION_MIN;

// 0x8E1C50
const USHORT CWeather::WEATHER_TRANSITION_TIME = 10 * CTimerWorld::TIMESCALE_MSEC_PER_SEC;

// 0x8E1C40
const CResRef CWeather::SOUND_WIND("Amb_E02b");

// 0x8E2058
const CResRef CWeather::SOUND_RAIN("Amb_E11");

// 0x5553B0
CWeather::CWeather()
{
    m_bUpgrading = FALSE;
    m_bOverCast = FALSE;
    m_nLightningFreq = 0;
    m_nCurrentWeather = 0;
    m_nWeatherLevel = 0;
    m_nWeatherEndTime = 0;
    m_nWeatherStageEndTime = 0;
    m_nWindLevel = 0;
    m_nLastTimeChecked = 0;
    m_nWeatherDuration = 0;
    m_bWindOn = FALSE;
    m_nNextTimeToStartChecking = 0;
    m_nWindVolumeLevel = 0;
    m_nRainVolumeLevel = 0;
    m_bReInitialize = FALSE;
    m_nDurationCounter = 0;
    m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
}

// 0x555520
CWeather::~CWeather()
{
    SetWind(0, 0, FALSE);
    SetRainSound(0, WEATHER_TRANSITION_TIME);
}

// 0x555640
void CWeather::CancelCurrentWeather(CGameArea* pArea, ULONG nCurrentTime)
{
    switch (m_nCurrentWeather) {
    case 1:
        m_rainStorm.UnInitialize();
        m_nCurrentWeather = 0;
        m_nLightningFreq = 0;
        m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
        SetWind(0, WEATHER_TRANSITION_TIME, TRUE);
        SetRainSound(0, WEATHER_TRANSITION_TIME);
        break;
    case 2:
        m_snowStorm.UnInitialize();
        m_nCurrentWeather = 0;
        m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
        SetWind(0, WEATHER_TRANSITION_TIME, TRUE);
        break;
    }

    m_nWindVolumeLevel = 0;
    m_nRainVolumeLevel = 0;
    m_nWeatherLevel = 0;

    if (pArea != NULL) {
        m_nNextTimeToStartChecking = CTimerWorld::TIMESCALE_MSEC_PER_HOUR + rand() % CTimerWorld::TIMESCALE_MSEC_PER_DAY;
        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            pArea->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor, m_nCurrentWeather, m_nWeatherLevel, m_nLightningFreq);
        }
        m_nLastTimeChecked = nCurrentTime;

        if (g_pBaldurChitin->cNetwork.GetSessionOpen() && g_pBaldurChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->m_cBaldurMessage.WeatherBroadcast(Marshal());
        }
    }
}

// 0x555790
void CWeather::CheckWeather()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    ULONG nCurrentTime = pGame->GetWorldTimer()->m_gameTime;
    CGameArea* pArea = pGame->GetVisibleArea();
    if (pGame->GetOptions()->m_bWeatherEnabled) {
        if (pArea != NULL) {
            if (nCurrentTime > m_nLastTimeChecked && nCurrentTime >= m_nNextTimeToStartChecking) {
                if ((pArea->m_header.m_areaType & 0x4) != 0) {
                    m_nLastTimeChecked = nCurrentTime;
                    if (nCurrentTime % CTimerWorld::TIMESCALE_MSEC_PER_HOUR == 0) {
                        if (pArea->m_header.m_rainProbability != 0 && rand() % 100 < pArea->m_header.m_rainProbability) {
                            SetCurrentWeather(pArea, nCurrentTime, 1);
                        } else if (pArea->m_header.m_snowProbability != 0 && rand() % 100 < pArea->m_header.m_snowProbability) {
                            SetCurrentWeather(pArea, nCurrentTime, 2);
                        }
                    }
                }
            }
        }
    }
}

// 0x555850
void CWeather::Unmarshal(WORD wWeatherFlags)
{
    m_bReInitialize = TRUE;
    m_nLightningFreq = wWeatherFlags & 0xC0;
    m_nCurrentWeather = wWeatherFlags & 0x3;
    m_nWeatherLevel = wWeatherFlags & 0xC;
    m_bUpgrading = (wWeatherFlags & 0x100) != 0;
}

// 0x555890
WORD CWeather::Marshal()
{
    return m_nLightningFreq | m_nCurrentWeather | m_nWeatherLevel | (m_bUpgrading ? 0x100 : 0);
}

// 0x5558B0
void CWeather::AdvanceWeatherLevel(ULONG nCurrentTime)
{
    // TODO: Check casts.
    ULONG nTime = nCurrentTime + 6 * WEATHER_TRANSITION_TIME + m_nWeatherDuration - m_nWeatherEndTime;
    if (nTime < static_cast<ULONG>(WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 0;
        m_bUpgrading = TRUE;
        return;
    }

    if (nTime < static_cast<ULONG>(2 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 4;
        m_bUpgrading = TRUE;
        return;
    }

    if (nTime < static_cast<ULONG>(3 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 8;
        m_bUpgrading = TRUE;
        return;
    }

    if (nTime < static_cast<ULONG>(m_nWeatherDuration + 3 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 12;
        m_bUpgrading = TRUE;
        return;
    }

    if (nTime < static_cast<ULONG>(m_nWeatherDuration + 4 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 8;
        m_bUpgrading = FALSE;
        return;
    }

    if (nTime < static_cast<ULONG>(m_nWeatherDuration + 5 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 4;
        m_bUpgrading = FALSE;
        return;
    }

    if (nTime < static_cast<ULONG>(m_nWeatherDuration + 6 * WEATHER_TRANSITION_TIME)) {
        m_nWeatherLevel = 0;
        m_bUpgrading = FALSE;
        return;
    }

    CancelCurrentWeather(g_pBaldurChitin->GetObjectGame()->m_pGameAreaMaster, nCurrentTime);
}

// 0x5559D0
void CWeather::CompressTime()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    ULONG nCurrentTime = pGame->GetWorldTimer()->m_gameTime;

    if (m_nCurrentWeather != 0) {
        if (nCurrentTime <= m_nWeatherEndTime) {
            AdvanceWeatherLevel(nCurrentTime);
            m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
            m_nDurationCounter = 0;

            USHORT nDensity;
            switch (m_nWeatherLevel) {
            case 0:
                if (m_bUpgrading) {
                    if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                        m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                    } else {
                        m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                    }
                    m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 6 * WEATHER_TRANSITION_TIME;
                    m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
                    nDensity = 0;
                } else {
                    m_nWeatherEndTime = m_nWeatherStageEndTime;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    nDensity = 0;
                }
                break;
            case 4:
                if (m_bUpgrading) {
                    if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                        m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                    } else {
                        m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                    }
                    m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 5 * WEATHER_TRANSITION_TIME;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    nDensity = CRainStorm::DENSITY_LIGHT_STORM / WEATHER_TRANSITION_TIME;
                } else {
                    m_nWeatherEndTime = nCurrentTime + 2 * WEATHER_TRANSITION_TIME;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    nDensity = CRainStorm::DENSITY_LIGHT_STORM - CRainStorm::DENSITY_LIGHT_STORM / WEATHER_TRANSITION_TIME;
                }
                break;
            case 8:
                if (m_bUpgrading) {
                    if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                        m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                    } else {
                        m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                    }
                    m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 4 * WEATHER_TRANSITION_TIME;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    nDensity = (CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) / WEATHER_TRANSITION_TIME + CRainStorm::DENSITY_LIGHT_STORM;
                } else {
                    m_nWeatherEndTime = nCurrentTime + 3 * WEATHER_TRANSITION_TIME;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    nDensity = CRainStorm::DENSITY_MEDIUM_STORM - (CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) / WEATHER_TRANSITION_TIME;
                }
                break;
            case 12:
                if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                    m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                } else {
                    m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                }
                m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 3 * WEATHER_TRANSITION_TIME;
                m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                nDensity = CRainStorm::DENSITY_HEAVY_STORM / WEATHER_TRANSITION_TIME;
                break;
            }

            switch (m_nCurrentWeather) {
            case 1:
                m_rainStorm.m_nCurrentDensity = nDensity;

                if (m_nWeatherLevel == 12) {
                    SetWind(48, WEATHER_TRANSITION_TIME, TRUE);
                    SetRainSound(12, WEATHER_TRANSITION_TIME);
                }
                break;
            case 2:
                m_snowStorm.m_nCurrentDensity = nDensity;
                break;
            }

            m_nLastTimeChecked = nCurrentTime;
            m_bReInitialize = FALSE;

            pGame->m_pGameAreaMaster->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                m_nCurrentWeather,
                m_nWeatherLevel,
                0);

            m_nLastTimeChecked = nCurrentTime;
        } else {
            CancelCurrentWeather(pGame->m_pGameAreaMaster, nCurrentTime);
        }
    }
}

// 0x555D60
void CWeather::ResetWeather(CGameArea* pArea)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    ULONG nCurrentTime = pGame->GetWorldTimer()->m_gameTime;

    if (m_nCurrentWeather != 0 && pArea == pGame->m_pGameAreaMaster) {
        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            if (pGame->GetOptions()->m_bWeatherEnabled) {
                if (m_bReInitialize) {
                    m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                    m_nDurationCounter = 0;

                    INT x;
                    INT y;
                    USHORT nDensity;
                    switch (m_nWeatherLevel) {
                    case 0:
                        if (m_bUpgrading) {
                            if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                                m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                            } else {
                                m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                            }
                            m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 6 * WEATHER_TRANSITION_TIME;
                            m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);
                            nDensity = 0;
                        } else {
                            m_nWeatherEndTime = m_nWeatherStageEndTime;
                            m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                            nDensity = 0;
                        }
                        break;
                    case 4:
                        if (m_bUpgrading) {
                            if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                                m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                            } else {
                                m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                            }
                            m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 5 * WEATHER_TRANSITION_TIME;
                            m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                            nDensity = CRainStorm::DENSITY_LIGHT_STORM / WEATHER_TRANSITION_TIME;
                        } else {
                            m_nWeatherEndTime = nCurrentTime + 2 * WEATHER_TRANSITION_TIME;
                            m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                            nDensity = CRainStorm::DENSITY_LIGHT_STORM - CRainStorm::DENSITY_LIGHT_STORM / WEATHER_TRANSITION_TIME;
                        }
                        break;
                    case 8:
                        if (m_bUpgrading) {
                            if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                                m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                            } else {
                                m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                            }
                            m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 4 * WEATHER_TRANSITION_TIME;
                            m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                            nDensity = (CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) / WEATHER_TRANSITION_TIME + CRainStorm::DENSITY_LIGHT_STORM;
                        } else {
                            m_nWeatherEndTime = nCurrentTime + 3 * WEATHER_TRANSITION_TIME;
                            m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                            nDensity = CRainStorm::DENSITY_MEDIUM_STORM - (CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) / WEATHER_TRANSITION_TIME;
                        }
                        break;
                    case 12:
                        if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                            m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                        } else {
                            m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                        }
                        m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 3 * WEATHER_TRANSITION_TIME;
                        m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                        nDensity = CRainStorm::DENSITY_HEAVY_STORM;
                        break;
                    }

                    switch (m_nCurrentWeather) {
                    case 1:
                        if (!m_rainStorm.IsInitialized()) {
                            pArea->GetInfinity()->GetViewPosition(x, y);
                            m_rainStorm.GenerateDrops(CPoint(x, y), CInfinity::stru_8E79B8);
                        }

                        m_rainStorm.m_nCurrentDensity = nDensity;

                        if (m_nWeatherLevel == 12) {
                            SetWind(48, WEATHER_TRANSITION_TIME, TRUE);
                            SetRainSound(12, WEATHER_TRANSITION_TIME);
                        }
                        break;
                    case 2:
                        if (!m_snowStorm.IsInitialized()) {
                            pArea->GetInfinity()->GetViewPosition(x, y);
                            m_snowStorm.GenerateFlakes(CPoint(x, y), CInfinity::stru_8E79B8);
                        }

                        m_snowStorm.m_nCurrentDensity = nDensity;
                        break;
                    }

                    m_nLastTimeChecked = nCurrentTime;
                    m_bReInitialize = FALSE;
                }

                pGame->m_pGameAreaMaster->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                    m_nCurrentWeather,
                    m_nWeatherLevel,
                    0);
            }
        } else {
            CancelCurrentWeather(pArea, nCurrentTime);
        }
    }
}

// 0x556190
void CWeather::SetCurrentWeather(CGameArea* pArea, WORD wWeatherFlags)
{
    if (!g_pBaldurChitin->cNetwork.GetSessionOpen() || !g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        CancelCurrentWeather(pArea, g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime);
        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bWeatherEnabled) {
            // NOTE: Uninline.
            Unmarshal(wWeatherFlags);
            ResetWeather(pArea);
        }
    }
}

// 0x556230
void CWeather::SetCurrentWeather(CGameArea* pArea, ULONG nCurrentTime, BYTE nWeatherType)
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()
        || g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        if (m_nCurrentWeather != 0 || nWeatherType == 0) {
            CancelCurrentWeather(pArea, nCurrentTime);
        }

        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bWeatherEnabled) {
            INT x;
            INT y;

            switch (nWeatherType) {
            case 1:
                if (pArea->m_header.m_lightningProbability == 0) {
                    m_nLightningFreq = 0;
                } else if (pArea->m_header.m_lightningProbability < 33) {
                    m_nLightningFreq = 64;
                } else if (pArea->m_header.m_lightningProbability < 66) {
                    m_nLightningFreq = 128;
                } else {
                    m_nLightningFreq = 192;
                }

                pArea->GetInfinity()->GetViewPosition(x, y);
                m_rainStorm.GenerateDrops(CPoint(x, y), CInfinity::stru_8E79B8);
                m_nCurrentWeather = 1;
                m_bUpgrading = TRUE;
                m_nWeatherLevel = 0;
                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;

                if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                    m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                } else {
                    m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                }

                m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 6 * WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
                m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);

                if (g_pBaldurChitin->cNetwork.GetSessionOpen()
                    && g_pBaldurChitin->cNetwork.GetSessionHosting()) {
                    g_pBaldurChitin->GetBaldurMessage()->WeatherBroadcast(Marshal());
                }

                pArea->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                    m_nCurrentWeather,
                    m_nWeatherLevel,
                    0);
                m_nLastTimeChecked = nCurrentTime;
                break;
            case 2:
                pArea->GetInfinity()->GetViewPosition(x, y);
                m_snowStorm.GenerateFlakes(CPoint(x, y), CInfinity::stru_8E79B8);
                m_nCurrentWeather = 2;
                m_nWeatherLevel = 0;
                m_bUpgrading = TRUE;
                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;

                if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
                    m_nWeatherDuration = WEATHER_DURATION_MULTIPLAYER;
                } else {
                    m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                }

                m_nWeatherEndTime = nCurrentTime + m_nWeatherDuration + 6 * WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
                m_rgbCurrentOverCastColor = RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT);

                if (g_pBaldurChitin->cNetwork.GetSessionOpen()
                    && g_pBaldurChitin->cNetwork.GetSessionHosting()) {
                    g_pBaldurChitin->GetBaldurMessage()->WeatherBroadcast(Marshal());
                }

                pArea->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                    m_nCurrentWeather,
                    m_nWeatherLevel,
                    0);
                m_nLastTimeChecked = nCurrentTime;
                break;
            }
        }
    }
}

// 0x5564F0
BYTE CWeather::GetWind()
{
    if (!m_bWindOn) {
        return 100;
    }

    if (m_nWindLevel == 16) {
        // TODO: Check casts.
        if (m_nDurationCounter <= static_cast<ULONG>(WEATHER_TRANSITION_TIME / 5)) {
            return static_cast<BYTE>(100 - 500 * m_nDurationCounter / WEATHER_TRANSITION_TIME);
        }
    }

    return 0;
}

// 0x556550
void CWeather::SetRainSound(SHORT nRainLevel, ULONG nLevelPercentage)
{
    if (nRainLevel != 0) {
        m_nRainVolumeLevel = nLevelPercentage;
        if ((g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->m_header.m_areaType & 4) != 0) {
            switch (nRainLevel) {
            case 4:
                if (!m_sndRain.IsSoundPlaying()) {
                    m_sndRain.SetResRef(SOUND_RAIN, TRUE, TRUE);
                    m_sndRain.SetChannel(1, 0);
                    m_sndRain.Play(TRUE);
                }
                m_sndRain.SetVolume(VOLUME_LIGHT * m_nRainVolumeLevel / WEATHER_TRANSITION_TIME);
                break;
            case 8:
                if (!m_sndRain.IsSoundPlaying()) {
                    m_sndRain.SetResRef(SOUND_RAIN, TRUE, TRUE);
                    m_sndRain.SetChannel(1, 0);
                    m_sndRain.Play(TRUE);
                }
                m_sndRain.SetVolume(VOLUME_MEDIUM * m_nRainVolumeLevel / WEATHER_TRANSITION_TIME);
                break;
            case 12:
                if (!m_sndRain.IsSoundPlaying()) {
                    m_sndRain.SetResRef(SOUND_RAIN, TRUE, TRUE);
                    m_sndRain.SetChannel(1, 0);
                    m_sndRain.Play(TRUE);
                }
                m_sndRain.SetVolume(VOLUME_HEAVY * m_nRainVolumeLevel / WEATHER_TRANSITION_TIME);
                break;
            }
        }
    } else {
        m_sndRain.Stop();
        m_sndRain.SetResRef(CResRef(""), TRUE, TRUE);
    }
}

// 0x556970
void CWeather::SetWind(SHORT nWindLevel, ULONG nLevelPercentage, BOOLEAN bResetAmbients)
{
    if (nWindLevel != 0) {
        m_nWindVolumeLevel = nLevelPercentage;
        if ((g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->m_header.m_areaType & 4) != 0) {
            switch (nWindLevel) {
            case 16:
                if (!m_bWindOn) {
                    m_sndWind.SetResRef(SOUND_WIND, TRUE, TRUE);
                    m_sndWind.SetChannel(1, 0);
                    m_sndWind.Play(TRUE);
                    m_bWindOn = TRUE;
                }

                // TODO: Check casts.
                if (m_nWindVolumeLevel > static_cast<ULONG>(WEATHER_TRANSITION_TIME / 5)) {
                    m_sndWind.SetVolume((VOLUME_LIGHT * m_nWindVolumeLevel - VOLUME_LIGHT * (WEATHER_TRANSITION_TIME / 5)) / (WEATHER_TRANSITION_TIME - WEATHER_TRANSITION_TIME / 5));
                } else {
                    m_sndWind.SetVolume(0);
                    g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->ApplyWindToAmbients(static_cast<BYTE>(100 - 500 * m_nWindVolumeLevel / WEATHER_TRANSITION_TIME));
                }

                m_nWindLevel = 16;
                break;
            case 32:
                if (!m_bWindOn) {
                    m_sndWind.SetResRef(SOUND_WIND, TRUE, TRUE);
                    m_sndWind.SetChannel(1, 0);
                    m_sndWind.Play(TRUE);
                    m_bWindOn = TRUE;
                }

                m_sndWind.SetVolume(VOLUME_MEDIUM * nLevelPercentage / WEATHER_TRANSITION_TIME);
                m_nWindLevel = 32;
                break;
            case 48:
                if (!m_bWindOn) {
                    m_sndWind.SetResRef(SOUND_WIND, TRUE, TRUE);
                    m_sndWind.SetChannel(1, 0);
                    m_sndWind.Play(TRUE);
                    m_bWindOn = TRUE;
                }

                m_sndWind.SetVolume(VOLUME_HEAVY * nLevelPercentage / WEATHER_TRANSITION_TIME);
                m_nWindLevel = 48;
                break;
            }
        }
    } else {
        if (m_bWindOn) {
            m_sndWind.Stop();
            m_sndWind.SetResRef("", TRUE, TRUE);
            m_bWindOn = FALSE;

            if (bResetAmbients) {
                g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->ApplyWindToAmbients(100);
            }
        }
    }
}

// 0x556EA0
void CWeather::OnAreaChange(BOOLEAN bForceOff)
{
    if (m_nCurrentWeather == 1) {
        if (bForceOff || (g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->m_header.m_areaType & 0x4) == 0) {
            if (m_sndRain.IsSoundPlaying()) {
                SetRainSound(0, 0);
            }

            if (m_bWindOn) {
                SetWind(0, 0, TRUE);
            }
        } else {
            if (!m_sndRain.IsSoundPlaying()) {
                SetRainSound(m_nWeatherLevel, m_nRainVolumeLevel);
            }

            if (!m_bWindOn) {
                switch (m_nWeatherLevel) {
                case 0:
                    SetWind(m_nCurrentWeather != 1 ? 16 : 0, m_nWindVolumeLevel, TRUE);
                    break;
                case 4:
                    SetWind(32, m_nWindVolumeLevel, TRUE);
                    break;
                case 8:
                case 12:
                    SetWind(48, m_nWindVolumeLevel, TRUE);
                    break;
                default:
                    SetWind(0, m_nWindVolumeLevel, TRUE);
                    break;
                }
            }
        }
    }
}

// 0x556FF0
void CWeather::Update()
{
    switch (m_nCurrentWeather) {
    case 1:
        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bWeatherEnabled) {
            UpdateRain();

            if (m_nWeatherLevel != 0) {
                if (m_rainStorm.IsInitialized()) {
                    m_rainStorm.AsynchronousUpdate();
                }
            }
        } else {
            CancelCurrentWeather(g_pBaldurChitin->GetObjectGame()->GetVisibleArea(), g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime);
        }
        break;
    case 2:
        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bWeatherEnabled) {
            UpdateSnow();

            if (m_nWeatherLevel != 0) {
                if (m_snowStorm.IsInitialized()) {
                    m_snowStorm.AsynchronousUpdate();
                }
            }
        } else {
            CancelCurrentWeather(g_pBaldurChitin->GetObjectGame()->GetVisibleArea(), g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime);
        }
        break;
    default:
        CheckWeather();
        break;
    }
}

// 0x5570C0
void CWeather::UpdateRain()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CGameArea* pArea = pGame->m_pGameAreaMaster;
    ULONG nCurrentTime = pGame->GetWorldTimer()->m_gameTime;

    if (pArea != NULL
        && nCurrentTime > m_nLastTimeChecked) {
        if (nCurrentTime > m_nWeatherEndTime + 1) {
            CancelCurrentWeather(pArea, nCurrentTime);
        }

        switch (m_nWeatherLevel) {
        case 0:
            if (m_bUpgrading) {
                if (nCurrentTime < m_nWeatherStageEndTime) {
                    m_rgbCurrentOverCastColor = RGB(255 - GetRValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME,
                        255 - GetGValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME,
                        255 - GetBValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                    SetWind(m_nCurrentWeather != 1 ? 16 : 0, m_nDurationCounter, TRUE);
                    m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                } else {
                    m_nWeatherLevel = 4;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                    m_nDurationCounter = 0;
                }
            } else {
                if (nCurrentTime < m_nWeatherStageEndTime) {
                    m_rgbCurrentOverCastColor = RGB(GetRValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetRValue(OVERCAST_COLOR),
                        GetGValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetGValue(OVERCAST_COLOR),
                        GetBValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetBValue(OVERCAST_COLOR));
                    SetWind(m_nCurrentWeather != 1 ? 16 : 0, WEATHER_TRANSITION_TIME - m_nDurationCounter, TRUE);
                    m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                } else {
                    CancelCurrentWeather(pArea, nCurrentTime);
                    return;
                }
            }
            break;
        case 4:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                m_nLastTimeChecked = nCurrentTime;
                if (m_bUpgrading) {
                    SetWind(32, m_nDurationCounter, TRUE);
                    SetRainSound(8, m_nDurationCounter);
                    m_rainStorm.m_nCurrentDensity = static_cast<USHORT>(CRainStorm::DENSITY_LIGHT_STORM * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                } else {
                    SetWind(32, WEATHER_TRANSITION_TIME - m_nDurationCounter, TRUE);
                    SetRainSound(8, WEATHER_TRANSITION_TIME - m_nDurationCounter);
                    m_rainStorm.m_nCurrentDensity = static_cast<USHORT>(CRainStorm::DENSITY_LIGHT_STORM - CRainStorm::DENSITY_LIGHT_STORM * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                }
                return;
            } else {
                if (m_bUpgrading) {
                    m_nWeatherLevel = 8;
                } else {
                    m_nWeatherLevel = 0;
                    SetRainSound(0, WEATHER_TRANSITION_TIME);
                }

                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
            }
            break;
        case 8:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                m_nLastTimeChecked = nCurrentTime;
                if (m_bUpgrading) {
                    SetWind(48, m_nDurationCounter, TRUE);
                    SetRainSound(12, m_nDurationCounter);
                    m_rainStorm.m_nCurrentDensity = static_cast<USHORT>((CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) * m_nDurationCounter / WEATHER_TRANSITION_TIME + CSnowStorm::DENSITY_LIGHT_STORM);
                } else {
                    SetWind(48, WEATHER_TRANSITION_TIME - m_nDurationCounter, TRUE);
                    SetRainSound(12, WEATHER_TRANSITION_TIME - m_nDurationCounter);
                    m_rainStorm.m_nCurrentDensity = static_cast<USHORT>(CRainStorm::DENSITY_MEDIUM_STORM - (CRainStorm::DENSITY_MEDIUM_STORM - CRainStorm::DENSITY_LIGHT_STORM) * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                }
                return;
            } else {
                if (m_bUpgrading) {
                    m_nWeatherLevel = 12;
                    m_rainStorm.m_nCurrentDensity = CRainStorm::DENSITY_HEAVY_STORM;
                    m_nWeatherStageEndTime = nCurrentTime + m_nWeatherDuration;
                } else {
                    m_nWeatherLevel = 4;
                    m_rainStorm.m_nCurrentDensity = CRainStorm::DENSITY_LIGHT_STORM;
                    m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                }

                m_nDurationCounter = 0;
            }
            break;
        case 12:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                if (nCurrentTime % CTimerWorld::TIMESCALE_MSEC_PER_HOUR == 0
                    && !g_pBaldurChitin->cNetwork.GetSessionOpen()
                    && pArea->m_header.m_rainProbability != 0
                    && rand() % 100 < pArea->m_header.m_rainProbability) {
                    m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                    m_nWeatherStageEndTime = nCurrentTime + m_nWeatherDuration;
                    m_nWeatherEndTime = m_nWeatherStageEndTime + 3 * WEATHER_TRANSITION_TIME;
                }
                m_nLastTimeChecked = nCurrentTime;
                return;
            } else {
                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
                m_nWeatherLevel = 8;
                m_bUpgrading = FALSE;
                m_rainStorm.m_nCurrentDensity = CRainStorm::DENSITY_MEDIUM_STORM;
            }
            break;
        }

        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            pArea->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                m_nCurrentWeather,
                m_nWeatherLevel,
                m_nLightningFreq);
        }

        m_nLastTimeChecked = nCurrentTime;
    }
}

// 0x5575D0
void CWeather::UpdateSnow()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CGameArea* pArea = pGame->m_pGameAreaMaster;
    ULONG nCurrentTime = pGame->GetWorldTimer()->m_gameTime;

    if (pArea != NULL
        && nCurrentTime > m_nLastTimeChecked) {
        if (nCurrentTime > m_nWeatherEndTime + 1) {
            CancelCurrentWeather(pArea, nCurrentTime);
        }

        switch (m_nWeatherLevel) {
        case 0:
            if (m_bUpgrading) {
                if (nCurrentTime < m_nWeatherStageEndTime) {
                    m_rgbCurrentOverCastColor = RGB(255 - GetRValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME,
                        255 - GetGValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME,
                        255 - GetBValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                    m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                } else {
                    m_nWeatherLevel = 4;
                    m_rgbCurrentOverCastColor = OVERCAST_COLOR;
                    m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                    m_nDurationCounter = 0;
                }
            } else {
                if (nCurrentTime < m_nWeatherStageEndTime) {
                    m_rgbCurrentOverCastColor = RGB(GetRValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetRValue(OVERCAST_COLOR),
                        GetGValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetGValue(OVERCAST_COLOR),
                        GetBValue(RGB_OVERCAST_INCREMENT) * m_nDurationCounter / WEATHER_TRANSITION_TIME + GetBValue(OVERCAST_COLOR));
                    m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                } else {
                    CancelCurrentWeather(pArea, nCurrentTime);
                    return;
                }
            }
            break;
        case 4:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                m_nLastTimeChecked = nCurrentTime;
                if (m_bUpgrading) {
                    m_snowStorm.m_nCurrentDensity = static_cast<USHORT>(CSnowStorm::DENSITY_LIGHT_STORM * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                } else {
                    m_snowStorm.m_nCurrentDensity = static_cast<USHORT>(CSnowStorm::DENSITY_LIGHT_STORM - CSnowStorm::DENSITY_LIGHT_STORM * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                }
                return;
            } else {
                if (m_bUpgrading) {
                    m_nWeatherLevel = 8;
                } else {
                    m_nWeatherLevel = 0;
                }

                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
            }
            break;
        case 8:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                m_nDurationCounter += nCurrentTime - m_nLastTimeChecked;
                m_nLastTimeChecked = nCurrentTime;
                if (m_bUpgrading) {
                    m_snowStorm.m_nCurrentDensity = static_cast<USHORT>((CSnowStorm::DENSITY_MEDIUM_STORM - CSnowStorm::DENSITY_LIGHT_STORM) * m_nDurationCounter / WEATHER_TRANSITION_TIME + CSnowStorm::DENSITY_LIGHT_STORM);
                } else {
                    m_snowStorm.m_nCurrentDensity = static_cast<USHORT>(CSnowStorm::DENSITY_MEDIUM_STORM - (CSnowStorm::DENSITY_MEDIUM_STORM - CSnowStorm::DENSITY_LIGHT_STORM) * m_nDurationCounter / WEATHER_TRANSITION_TIME);
                }
                return;
            } else {
                if (m_bUpgrading) {
                    m_nWeatherLevel = 12;
                    m_snowStorm.m_nCurrentDensity = CSnowStorm::DENSITY_HEAVY_STORM;
                    m_nWeatherStageEndTime = nCurrentTime + m_nWeatherDuration;
                } else {
                    m_nWeatherLevel = 4;
                    m_snowStorm.m_nCurrentDensity = CSnowStorm::DENSITY_LIGHT_STORM;
                    m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                }

                m_nDurationCounter = 0;
            }
            break;
        case 12:
            if (nCurrentTime < m_nWeatherStageEndTime) {
                // FIXME: Probably a bug - checks for rain probability, but
                // should check for snow.
                if (nCurrentTime % CTimerWorld::TIMESCALE_MSEC_PER_HOUR == 0
                    && !g_pBaldurChitin->cNetwork.GetSessionOpen()
                    && pArea->m_header.m_rainProbability != 0
                    && rand() % 100 < pArea->m_header.m_rainProbability) {
                    m_nWeatherDuration = WEATHER_DURATION_MIN + rand() % (WEATHER_DURATION_MAX - WEATHER_DURATION_MIN);
                    m_nWeatherStageEndTime = nCurrentTime + m_nWeatherDuration;
                    m_nWeatherEndTime = m_nWeatherStageEndTime + 3 * WEATHER_TRANSITION_TIME;
                }
                m_nLastTimeChecked = nCurrentTime;
                return;
            } else {
                m_nWeatherStageEndTime = nCurrentTime + WEATHER_TRANSITION_TIME;
                m_nDurationCounter = 0;
                m_nWeatherLevel = 8;
                m_bUpgrading = FALSE;
                m_snowStorm.m_nCurrentDensity = CSnowStorm::DENSITY_MEDIUM_STORM;
            }
            break;
        }

        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            pArea->GetInfinity()->SetCurrentWeather(m_rgbCurrentOverCastColor,
                m_nCurrentWeather,
                m_nWeatherLevel,
                m_nLightningFreq);
        }

        m_nLastTimeChecked = nCurrentTime;
    }
}

// -----------------------------------------------------------------------------

// 0x84EE82
const BYTE CRainStorm::DENSITY_LIGHT_STORM = 50;

// 0x84EE83
const BYTE CRainStorm::DENSITY_MEDIUM_STORM = 150;

// 0x84EE84
const BYTE CRainStorm::DENSITY_HEAVY_STORM = 250;

// 0x84EE85
const BYTE CRainStorm::RAINDROP_MAX_HEIGHT = 100;

// NOTE: Inlined in `CWeather::CWeather`.
CRainStorm::CRainStorm()
{
    m_rOldWorldViewPort.left = -1;
    m_rOldWorldViewPort.top = -1;
    m_rOldWorldViewPort.right = -1;
    m_rOldWorldViewPort.bottom = -1;
    m_nCurrentDensity = 0;
    m_pRainDrops = NULL;
    m_nWindGustCounter = 0;
}

// 0x5579B0
CRainStorm::~CRainStorm()
{
    if (m_pRainDrops != NULL) {
        delete[] m_pRainDrops;
    }
}

// 0x557A30
void CRainStorm::AsynchronousUpdate()
{
    if (IsInitialized()) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            CRect rNewWorldViewPort(pArea->GetInfinity()->nNewX,
                pArea->GetInfinity()->nNewY,
                pArea->GetInfinity()->nNewX + pArea->GetInfinity()->rViewPort.Width(),
                pArea->GetInfinity()->nNewY + pArea->GetInfinity()->rViewPort.Height());

            CRect rOld(m_rOldWorldViewPort.left << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.top << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.right << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.bottom << CParticle::RESOLUTION_INC);

            CRect rNew(rNewWorldViewPort.left << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.top << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.right << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.bottom << CParticle::RESOLUTION_INC);

            for (int index = 0; index < 250; index++) {
                if (m_pRainDrops[index].AsynchronousUpdate(rOld, rNew) == CParticle::DEAD) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWeather.cpp
                    // __LINE__: 1813
                    UTIL_ASSERT(m_pRainDrops != NULL);

                    m_pRainDrops[index].m_vel.x = 0;
                    m_pRainDrops[index].m_vel.y = 0;
                    m_pRainDrops[index].m_vel.z = 0;

                    m_pRainDrops[index].m_pos.x = (rNewWorldViewPort.left + rand() % rNewWorldViewPort.Width()) << CParticle::RESOLUTION_INC;
                    m_pRainDrops[index].m_pos.y = (rand() % (4 * rNewWorldViewPort.bottom / 3 - 4 * rNewWorldViewPort.top / 3) + 4 * rNewWorldViewPort.top / 3 + RAINDROP_MAX_HEIGHT) << CParticle::RESOLUTION_INC;
                    m_pRainDrops[index].m_pos.z = RAINDROP_MAX_HEIGHT << CParticle::RESOLUTION_INC;
                }
            }

            m_rOldWorldViewPort = rNewWorldViewPort;
        }
    }
}

// 0x557C30
void CRainStorm::GenerateDrops(const CPoint& ptViewPort, const CRect& rBounds)
{
    m_rOldWorldViewPort.SetRect(ptViewPort, ptViewPort + rBounds.Size());

    m_pRainDrops = new CRainDrop[250];
    if (m_pRainDrops != NULL) {
        for (int i = 0; i < 250; i++) {
            WORD z = rand() % RAINDROP_MAX_HEIGHT;
            m_pRainDrops[i].m_pos.x = (ptViewPort.x + rand() % rBounds.Width()) << CParticle::RESOLUTION_INC;
            m_pRainDrops[i].m_pos.y = (4 * ptViewPort.y / 3 + z + rand() % (4 * rBounds.Height() / 3)) << CParticle::RESOLUTION_INC;
            m_pRainDrops[i].m_pos.z = z << CParticle::RESOLUTION_INC;
        }
    }
}

// 0x557D90
void CRainStorm::Render(CVidMode* pVidMode, int a2, const CRect& rClip, COLORREF rgbColor)
{
    CRect& rSurface = g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->rViewPort;

    CSingleLock renderLock(&m_cCriticalSection, TRUE);
    if (m_pRainDrops != NULL && static_cast<CVidInf*>(pVidMode)->BKLock(rSurface)) {
        for (USHORT n = 0; n < m_nCurrentDensity; n++) {
            m_pRainDrops[n].m_rgbColor = rgbColor;
            static_cast<CVidInf*>(pVidMode)->BKRender(&(m_pRainDrops[n]), rClip, CParticle::CONNECT, 5);
        }

        renderLock.Unlock();
        static_cast<CVidInf*>(pVidMode)->BKUnlock();
    } else {
        renderLock.Unlock();
    }
}

// 0x557E90
void CRainStorm::UnInitialize()
{
    CSingleLock lock(&m_cCriticalSection);
    lock.Lock();

    if (m_pRainDrops != NULL) {
        delete[] m_pRainDrops;
        m_pRainDrops = NULL;
    }

    m_nCurrentDensity = 0;

    lock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x84EE86
const BYTE CSnowStorm::DENSITY_LIGHT_STORM = 50;

// 0x84EE87
const BYTE CSnowStorm::DENSITY_MEDIUM_STORM = 150;

// 0x84EE88
const BYTE CSnowStorm::DENSITY_HEAVY_STORM = 250;

// 0x84EE89
const BYTE CSnowStorm::SNOWFLAKE_MAX_HEIGHT = 100;

// NOTE: Inlined in `CWeather::CWeather`.
CSnowStorm::CSnowStorm()
{
    m_rOldWorldViewPort.left = -1;
    m_rOldWorldViewPort.top = -1;
    m_rOldWorldViewPort.right = -1;
    m_rOldWorldViewPort.bottom = -1;
    m_nCurrentDensity = 0;
    m_pSnowFlakes = NULL;
}

// 0x557F30
CSnowStorm::~CSnowStorm()
{
    if (m_pSnowFlakes != NULL) {
        delete[] m_pSnowFlakes;
    }
}

// 0x557FC0
void CSnowStorm::AsynchronousUpdate()
{
    if (IsInitialized()) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if ((pArea->m_header.m_areaType & 0x4) != 0) {
            CRect rNewWorldViewPort(pArea->GetInfinity()->nNewX,
                pArea->GetInfinity()->nNewY,
                pArea->GetInfinity()->nNewX + pArea->GetInfinity()->rViewPort.Width(),
                pArea->GetInfinity()->nNewY + pArea->GetInfinity()->rViewPort.Height());

            CRect rOld(m_rOldWorldViewPort.left << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.top << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.right << CParticle::RESOLUTION_INC,
                m_rOldWorldViewPort.bottom << CParticle::RESOLUTION_INC);

            CRect rNew(rNewWorldViewPort.left << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.top << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.right << CParticle::RESOLUTION_INC,
                rNewWorldViewPort.bottom << CParticle::RESOLUTION_INC);

            for (int index = 0; index < 250; index++) {
                if (m_pSnowFlakes[index].AsynchronousUpdate(rOld, rNew) == CParticle::DEAD) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWeather.cpp
                    // __LINE__: 2125
                    UTIL_ASSERT(m_pSnowFlakes != NULL);

                    m_pSnowFlakes[index].m_pos.x = (rNewWorldViewPort.left + rand() % rNewWorldViewPort.Width()) << CParticle::RESOLUTION_INC;
                    m_pSnowFlakes[index].m_pos.y = (rand() % (4 * rNewWorldViewPort.bottom / 3 - 4 * rNewWorldViewPort.top / 3) + 4 * rNewWorldViewPort.top / 3 + SNOWFLAKE_MAX_HEIGHT) << CParticle::RESOLUTION_INC;
                    m_pSnowFlakes[index].m_pos.z = SNOWFLAKE_MAX_HEIGHT << CParticle::RESOLUTION_INC;
                }
            }

            m_rOldWorldViewPort = rNewWorldViewPort;
        }
    }
}

// 0x5581B0
void CSnowStorm::GenerateFlakes(const CPoint& ptViewPort, const CRect& rBounds)
{
    m_rOldWorldViewPort.SetRect(ptViewPort, ptViewPort + rBounds.Size());

    m_pSnowFlakes = new CSnowFlake[250];
    if (m_pSnowFlakes != NULL) {
        for (int index = 0; index < 250; index++) {
            WORD z = rand() % SNOWFLAKE_MAX_HEIGHT;
            m_pSnowFlakes[index].m_pos.x = (ptViewPort.x + rand() % rBounds.Width()) << CParticle::RESOLUTION_INC;
            m_pSnowFlakes[index].m_pos.y = (4 * ptViewPort.y / 3 + z + rand() % (4 * rBounds.Height() / 3)) << CParticle::RESOLUTION_INC;
            m_pSnowFlakes[index].m_pos.z = z << CParticle::RESOLUTION_INC;
        }
    }
}

// 0x558310
void CSnowStorm::Render(CVidMode* pVidMode, int a2, const CRect& rClip, COLORREF rgbColor)
{
    CRect& rSurface = g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->rViewPort;
    COLORREF rgbSnowColor = RGB(GetRValue(rgbColor) * GetRValue(CSnowFlake::SNOWFLAKE_BASE_COLOR),
        GetGValue(rgbColor) * GetGValue(CSnowFlake::SNOWFLAKE_BASE_COLOR),
        GetBValue(rgbColor) * GetBValue(CSnowFlake::SNOWFLAKE_BASE_COLOR));

    CSingleLock renderLock(&m_cCriticalSection, TRUE);
    if (m_pSnowFlakes != NULL && static_cast<CVidInf*>(pVidMode)->BKLock(rSurface)) {
        for (USHORT n = 0; n < m_nCurrentDensity; n++) {
            m_pSnowFlakes[n].m_rgbColor = rgbSnowColor;
            static_cast<CVidInf*>(pVidMode)->BKRender(&(m_pSnowFlakes[n]), rClip, CParticle::DOTS, 5);
        }

        renderLock.Unlock();
        static_cast<CVidInf*>(pVidMode)->BKUnlock();
    } else {
        renderLock.Unlock();
    }
}

// 0x558470
void CSnowStorm::UnInitialize()
{
    CSingleLock lock(&m_cCriticalSection);
    lock.Lock();

    if (m_pSnowFlakes != NULL) {
        delete[] m_pSnowFlakes;
        m_pSnowFlakes = NULL;
    }

    m_nCurrentDensity = 0;

    lock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x84EE8C
const COLORREF CSnowFlake::SNOWFLAKE_BASE_COLOR = RGB(230, 230, 230);

// 0x84EE90
const BYTE CSnowFlake::MAX_DRIFT_WIDTH = 10;

// 0x84EE91
const BYTE CSnowFlake::MIN_DRIFT_WIDTH = 5;

// 0x84EE92
const BYTE CSnowFlake::DEFAULT_MELT_TIME = 30;

// 0x8E207E
const SHORT CSnowFlake::DRIFT_VELOCITY = 1 << RESOLUTION_INC;

// 0x558530
CSnowFlake::CSnowFlake()
{
    if ((rand() & 1) != 0) {
        m_nLastDriftVelocity = DRIFT_VELOCITY;
    } else {
        m_nLastDriftVelocity = -DRIFT_VELOCITY;
    }

    m_vel.x = m_nLastDriftVelocity;
    m_wType |= CONSTANT_VELOCITY;
    m_nGravity = 500;
    m_nDriftCounter = 0;
    m_nMeltTime = DEFAULT_MELT_TIME;
    m_nDriftWidth = MIN_DRIFT_WIDTH + rand() % (MAX_DRIFT_WIDTH - MIN_DRIFT_WIDTH);
}

// 0x558590
BYTE CSnowFlake::AsynchronousUpdate(const CRect& rOldViewPort, const CRect& rNewViewPort)
{
    LONG nTrueY = (3 * m_pos.y) / 4;

    if (!rOldViewPort.EqualRect(rNewViewPort)) {
        if (m_pos.x < rNewViewPort.left || m_pos.x > rNewViewPort.right) {
            m_pos.x = rOldViewPort.left + rNewViewPort.right - m_pos.x;
        }

        if (nTrueY - m_pos.z < rNewViewPort.top || nTrueY - m_pos.z > rNewViewPort.bottom) {
            m_pos.y = 4 * (rNewViewPort.bottom + rOldViewPort.top + 2 * m_pos.z - nTrueY) / 3;
        }
    }

    if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_active) {
        if (CParticle::AsynchronousUpdate() == AIRBORN) {
            m_nDriftCounter++;
            if (m_nDriftCounter == m_nDriftWidth) {
                m_nDriftCounter = 0;

                LONG nDriftVelocity = m_vel.x;
                if (nDriftVelocity != 0) {
                    m_vel.x = 0;
                    m_vel.y = 0;
                    m_vel.z = 0;
                    m_nLastDriftVelocity = nDriftVelocity;
                } else {
                    m_vel.x = -m_nLastDriftVelocity;
                    m_vel.y = 0;
                    m_vel.z = 0;
                }
            }
        } else {
            m_nMeltTime--;
            if (m_nMeltTime == 0) {
                m_nMeltTime = 30;
                return DEAD;
            }
        }
    }

    return AIRBORN;
}

// -----------------------------------------------------------------------------

// 0x84EE94
const SHORT CRainDrop::VELOCITY_LIGHT_WIND_INC = 100;

// 0x8E207C
const SHORT CRainDrop::VELOCITY_LIGHT_WIND = 1 << RESOLUTION_INC;

// 0x8E2080
const SHORT CRainDrop::VELOCITY_MED_WIND = 4 << RESOLUTION_INC;

// 0x8E206A
const SHORT CRainDrop::VELOCITY_HIGH_WIND = 3 << RESOLUTION_INC;

// 0x558710
CRainDrop::CRainDrop()
{
    m_vel.x = 0;
    m_vel.y = 0;
    m_vel.z = 0;
    m_nTailLength = 1;
}

// 0x558730
BYTE CRainDrop::AsynchronousUpdate(const CRect& rOldViewPort, const CRect& rNewViewPort)
{
    LONG nTrueY = (3 * m_pos.y) / 4;

    if (!rOldViewPort.EqualRect(rNewViewPort)) {
        if (m_pos.x < rNewViewPort.left || m_pos.x > rNewViewPort.right) {
            m_pos.x = rOldViewPort.left + rNewViewPort.right - m_pos.x;
        }

        if (nTrueY - m_pos.z < rNewViewPort.top || nTrueY - m_pos.z > rNewViewPort.bottom) {
            m_pos.y = 4 * (rNewViewPort.bottom + rOldViewPort.top + 2 * m_pos.z - nTrueY) / 3;
        }
    }

    if (m_vel.x < VELOCITY_LIGHT_WIND) {
        m_vel.x += VELOCITY_LIGHT_WIND_INC;
    }

    if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_active) {
        return CParticle::AsynchronousUpdate();
    } else {
        return AIRBORN;
    }
}

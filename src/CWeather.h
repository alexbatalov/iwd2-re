#ifndef CWEATHER_H_
#define CWEATHER_H_

#include "mfc.h"

#include "CParticle.h"

class CGameArea;

class CRainDrop : public CParticle {
public:
    static const SHORT VELOCITY_LIGHT_WIND;
    static const SHORT VELOCITY_MED_WIND;
    static const SHORT VELOCITY_HIGH_WIND;

    CRainDrop();
    BYTE AsynchronousUpdate(const CRect& rOldViewPort, const CRect& rNewViewPort);
};

class CSnowFlake : public CParticle {
public:
    static const SHORT DRIFT_VELOCITY;

    CSnowFlake();
    BYTE AsynchronousUpdate(const CRect& rOldViewPort, const CRect& rNewViewPort);

    BYTE m_nDriftWidth;
    BYTE m_nDriftCounter;
    USHORT m_nMeltTime;
    LONG m_nLastDriftVelocity;
};

class CRainStorm {
public:
    CRainStorm();
    ~CRainStorm();
    void AsynchronousUpdate();
    void GenerateDrops(const CPoint& ptViewPort, const CRect& rBounds);
    void Render(CVidMode* pVidMode, int a2, const CRect& rClip, COLORREF rgbColor);
    void UnInitialize();

    BOOL IsInitialized() { return m_pRainDrops != NULL; }

    /* 0000 */ CRainDrop* m_pRainDrops;
    /* 0004 */ USHORT m_nCurrentDensity;
    /* 0006 */ CRect m_rOldWorldViewPort;
    /* 0016 */ SHORT m_nWindGustCounter;
    /* 0018 */ CCriticalSection m_cCriticalSection;
};

class CSnowStorm {
public:
    CSnowStorm();
    ~CSnowStorm();
    void AsynchronousUpdate();
    void GenerateFlakes(const CPoint& ptViewPort, const CRect& rBounds);
    void Render(CVidMode* pVidMode, int a2, const CRect& rClip, COLORREF rgbColor);
    void UnInitialize();

    BOOL IsInitialized() { return m_pSnowFlakes != NULL; }

    /* 0000 */ CSnowFlake* m_pSnowFlakes;
    /* 0004 */ USHORT m_nCurrentDensity;
    /* 0006 */ CRect m_rOldWorldViewPort;
    /* 0016 */ CCriticalSection m_cCriticalSection;
};

class CWeather {
public:
    static const SHORT WEATHER_DURATION_MIN;
    static const SHORT WEATHER_DURATION_MAX;
    static const SHORT WEATHER_DURATION_MULTIPLAYER;
    static const USHORT WEATHER_TRANSITION_TIME;
    static const CResRef SOUND_WIND;
    static const CResRef SOUND_RAIN;

    CWeather();
    ~CWeather();
    void CancelCurrentWeather(CGameArea* pArea, ULONG nCurrentTime);
    void CheckWeather();
    void Unmarshal(WORD wWeatherFlags);
    WORD Marshal();
    void AdvanceWeatherLevel(ULONG nCurrentTime);
    void CompressTime();
    void ResetWeather(CGameArea* pArea);
    void SetCurrentWeather(CGameArea* pArea, WORD wWeatherFlags);
    void SetCurrentWeather(CGameArea* pArea, ULONG nCurrentTime, BYTE nWeatherType);
    BYTE GetWind();
    void SetRainSound(SHORT nRainLevel, ULONG nLevelPercentage);
    void SetWind(SHORT nWindLevel, ULONG nLevelPercentage, BOOLEAN bResetAmbients);
    void OnAreaChange(BOOLEAN bForceOff);
    void Update();
    void UpdateRain();
    void UpdateSnow();

    /* 0000 */ BOOLEAN m_bOverCast;
    /* 0002 */ USHORT m_nLightningFreq;
    /* 0004 */ USHORT m_nCurrentWeather;
    /* 0006 */ USHORT m_nWeatherLevel;
    /* 0008 */ ULONG m_nWeatherEndTime;
    /* 000C */ ULONG m_nWeatherStageEndTime;
    /* 0010 */ ULONG m_nWeatherDuration;
    /* 0014 */ ULONG m_nLastTimeChecked;
    /* 0018 */ USHORT m_nWindLevel;
    /* 001A */ COLORREF m_rgbCurrentOverCastColor;
    /* 001E */ ULONG m_nDurationCounter;
    /* 0022 */ CSnowStorm m_snowStorm;
    /* 0058 */ CRainStorm m_rainStorm;
    /* 0090 */ CSound m_sndRain;
    /* 00F4 */ CSound m_sndWind;
    /* 0158 */ BOOLEAN m_bWindOn;
    /* 0159 */ BOOLEAN m_bUpgrading;
    /* 015A */ ULONG m_nNextTimeToStartChecking;
    /* 015E */ ULONG m_nWindVolumeLevel;
    /* 0162 */ ULONG m_nRainVolumeLevel;
    /* 0166 */ BOOLEAN m_bReInitialize;
};

#endif /* CWEATHER_H_ */

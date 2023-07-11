#ifndef CINFINITY_H_
#define CINFINITY_H_

#include "mfc.h"

#include "CResRef.h"

class CInfinity {
public:
    static const BYTE SCROLL_DELAY;
    static const CString DAWN_MOVIE;
    static const CString DUSK_MOVIE;
    static const CString NIGHT_RESREF_SUFFIX;
    static const CString RAIN_RESREF_SUFFIX;
    static const CResRef THUNDERRESREFS[3];
    static BOOLEAN TRANSLUCENT_BLTS_ON;

    CInfinity();
    ~CInfinity();

    void GetViewPosition(INT& x, INT& y);
    void CallLightning(INT xWorldPos, INT yWorldPos);
    void SetCurrentWeather(COLORREF rgbOvercast, SHORT nWeather, int nWeatherLevel, int nLightningFrequency);
    void SetDay();
    void SetNight();
    void SetDawn();
    void SetDusk();
    void SetApproachingDawn();
    void SetApproachingDusk();
    void UpdateLightning();

    void SetAreaType(WORD areaType);

    /* 0024 */ BOOL bRefreshVRamRect;
    /* 0040 */ int nNewX;
    /* 0044 */ int nNewY;
    /* 0048 */ CRect rViewPort;
    /* 011C */ int nCurrentLightningFrequency;
    /* 0120 */ int nNextLightningFrequency;
    /* 012C */ int nNextRainLevel;
    /* 0130 */ int nCurrentSnowLevel;
    /* 0140 */ int nTimeToNextThunder;
    /* 0148 */ BOOL bRenderCallLightning;
    /* 014C */ int nRenderLightningTimer;
    /* 0150 */ CPoint cLightningPoint;
    /* 0158 */ WORD m_areaType;
    /* 015A */ BYTE m_renderDayNightCode;
    /* 015C */ BYTE m_dayLightIntensity;
    /* 015D */ BYTE m_requestDayNightCode;
    /* 019A */ BYTE m_nScrollDelay;
    /* 019B */ BOOLEAN m_bMovieBroadcast;
    /* 019C */ BOOL m_bStartLightning;
    /* 01A0 */ BOOL m_bStopLightning;
    /* 01AE */ COLORREF m_rgbOverCastGlobalLighting;
    /* 01B6 */ COLORREF m_rgbTimeOfDayGlobalLighting;
    /* 01BA */ COLORREF m_rgbTimeOfDayRainColor;
};

#endif /* CINFINITY_H_ */

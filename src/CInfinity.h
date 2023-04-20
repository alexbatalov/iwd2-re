#ifndef CINFINITY_H_
#define CINFINITY_H_

#include "mfc.h"

#include "CResRef.h"

class CInfinity {
public:
    static const CString DAWN_MOVIE;
    static const CString DUSK_MOVIE;
    static const CString NIGHT_RESREF_SUFFIX;
    static const CString RAIN_RESREF_SUFFIX;
    static const CResRef THUNDERRESREFS[3];

    CInfinity();
    ~CInfinity();

    void SetCurrentWeather(COLORREF rgbOvercast, SHORT nWeather, int nWeatherLevel, int nLightningFrequency);
    void SetDay();
    void SetNight();
    void SetDawn();
    void SetDusk();
    void SetApproachingDawn();
    void SetApproachingDusk();

    /* 0040 */ int nNewX;
    /* 0044 */ int nNewY;
    /* 0048 */ CRect rViewPort;
    /* 011C */ int nCurrentLightningFrequency;
    /* 0120 */ int nNextLightningFrequency;
    /* 012C */ int nNextRainLevel;
    /* 0130 */ int nCurrentSnowLevel;
    /* 0140 */ int nTimeToNextThunder;
    /* 0158 */ WORD m_areaType;
    /* 015A */ BYTE m_renderDayNightCode;
    /* 015C */ BYTE m_dayLightIntensity;
    /* 015D */ BYTE m_requestDayNightCode;
    /* 019B */ BOOLEAN m_bMovieBroadcast;
    /* 01A0 */ BOOL m_bStopLightning;
    /* 01AE */ COLORREF m_rgbOverCastGlobalLighting;
    /* 01B6 */ COLORREF m_rgbTimeOfDayGlobalLighting;
    /* 01BA */ COLORREF m_rgbTimeOfDayRainColor;
};

#endif /* CINFINITY_H_ */

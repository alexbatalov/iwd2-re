#ifndef CINFINITY_H_
#define CINFINITY_H_

#include "mfc.h"

#include "CResRef.h"

class CVidCell;
class CVidFont;
class CVidMode;

class CInfinity {
public:
    static const DWORD FXPREP_COPYFROMBACK;
    static const DWORD FXPREP_CLEARFILL;
    static const DWORD MIRROR_FX;
    static const DWORD MIRROR_FX_UPDOWN;
    static const DWORD CLIPPING_IGNORE_VERTICAL;
    static const BYTE SCROLL_DELAY;
    static const CString DAWN_MOVIE;
    static const CString DUSK_MOVIE;
    static const CString NIGHT_RESREF_SUFFIX;
    static const CString RAIN_RESREF_SUFFIX;
    static const CResRef THUNDERRESREFS[3];
    static BOOLEAN TRANSLUCENT_BLTS_ON;
    static CRect stru_8E7538;
    static CRect stru_8E7548;
    static CRect stru_8E7958;
    static CRect stru_8E7988;
    static CRect stru_8E79A8;
    static CRect stru_8E79B8;
    static CRect stru_8E79C8;
    static CRect stru_8E79E0;
    static CRect stru_8E79F8;
    static CRect stru_8E7A10;

    CInfinity();
    ~CInfinity();

    BOOL FXBltFrom(INT nDestSurface, CRect& rFXRect, INT x, INT y, INT nRefPointX, INT nRefPointY, DWORD dwFlags);
    BOOL FXPrep(CRect& rFXRect, DWORD dwFlags, int a3, const CPoint& ptPos, const CPoint& ptReference);
    BOOL FXLock(CRect& rBack, DWORD dwFlags);
    BOOL FXTextOut(CVidFont* pFont, const CString& sString, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue);
    BOOL FXRenderClippingPolys(INT nPosX, INT nPosY, INT nPosZ, const CPoint& ptRef, const CRect& rGCBounds, BOOLEAN bDithered, DWORD dwBlitFlags);
    BOOL FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef);
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

    /* 001C */ CVidMode* pVidMode;
    /* 0024 */ BOOL bRefreshVRamRect;
    /* 0040 */ int nNewX;
    /* 0044 */ int nNewY;
    /* 0048 */ CRect rViewPort;
    /* 0090 */ int nCurrentX;
    /* 0094 */ int nCurrentY;
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

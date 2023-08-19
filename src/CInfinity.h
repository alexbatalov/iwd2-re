#ifndef CINFINITY_H_
#define CINFINITY_H_

#include "mfc.h"

#include "CResRef.h"
#include "CVidBitmap.h"

class CGameArea;
class CInfTileSet;
class CResWED;
class CVidCell;
class CVidFont;
class CVidMode;
class CVRamPool;

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
    BOOL FXPrep(CRect& rFXRect, DWORD dwFlags, INT nDestSurface, const CPoint& ptPos, const CPoint& ptReference);
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

    /* 0000 */ CInfTileSet* pTileSets[5];
    /* 0014 */ CResWED* pResWED;
    /* 0018 */ CVRamPool* pVRPool;
    /* 001C */ CVidMode* pVidMode;
    /* 0020 */ int field_20;
    /* 0024 */ BOOL bRefreshVRamRect;
    /* 0028 */ int bInitialized;
    /* 002C */ BOOL bWEDDemanded;
    /* 0030 */ int nOffsetX;
    /* 0034 */ int nOffsetY;
    /* 0038 */ int nTilesX;
    /* 003C */ int nTilesY;
    /* 0040 */ int nNewX;
    /* 0044 */ int nNewY;
    /* 0048 */ CRect rViewPort;
    /* 0058 */ CRect rVRamRect;
    /* 0068 */ int field_68;
    /* 006C */ int field_6C;
    /* 0070 */ int field_70;
    /* 0074 */ int field_74;
    /* 0078 */ int nVisibleTilesX;
    /* 007C */ int nVisibleTilesY;
    /* 0080 */ int nAreaX;
    /* 0084 */ int nAreaY;
    /* 0088 */ int nCurrentTileX;
    /* 008C */ int nCurrentTileY;
    /* 0090 */ int nCurrentX;
    /* 0094 */ int nCurrentY;
    /* 0098 */ int field_98;
    /* 009C */ int field_9C;
    /* 00A0 */ int field_A0;
    /* 00A4 */ int field_A4;
    /* 00A8 */ int field_A8;
    /* 00AC */ int field_AC;
    /* 00B0 */ int field_B0;
    /* 00B4 */ int field_B4;
    /* 011C */ int nCurrentLightningFrequency;
    /* 0120 */ int nNextLightningFrequency;
    /* 0124 */ int field_124;
    /* 0128 */ int field_128;
    /* 012C */ int nNextRainLevel;
    /* 0130 */ int nCurrentSnowLevel;
    /* 0134 */ int field_134;
    /* 0138 */ int field_138;
    /* 013C */ int field_13C;
    /* 0140 */ int nTimeToNextThunder;
    /* 0144 */ int nThunderLength;
    /* 0148 */ BOOL bRenderCallLightning;
    /* 014C */ int nRenderLightningTimer;
    /* 0150 */ CPoint cLightningPoint;
    /* 0158 */ WORD m_areaType;
    /* 015A */ BYTE m_renderDayNightCode;
    /* 015B */ unsigned char field_15B;
    /* 015C */ BYTE m_dayLightIntensity;
    /* 015D */ BYTE m_requestDayNightCode;
    /* 015E */ unsigned char field_15E;
    /* 015F */ BOOLEAN m_bResizedViewPort;
    /* 0160 */ DWORD m_nLastTickCount;
    /* 0164 */ CPoint m_ptCurrentPosExact;
    /* 016C */ CCriticalSection m_currentPosCritSect;
    /* 018C */ SHORT m_autoScrollSpeed;
    /* 018E */ CPoint m_ptScrollDest;
    /* 0196 */ int field_196;
    /* 019A */ BYTE m_nScrollDelay;
    /* 019B */ BOOLEAN m_bMovieBroadcast;
    /* 019C */ BOOL m_bStartLightning;
    /* 01A0 */ BOOL m_bStopLightning;
    /* 01A4 */ BYTE m_lightningStrikeProb;
    /* 01A6 */ COLORREF m_rgbRainColor;
    /* 01AA */ COLORREF m_rgbLightningGlobalLighting;
    /* 01AE */ COLORREF m_rgbOverCastGlobalLighting;
    /* 01B2 */ COLORREF m_rgbGlobalLighting;
    /* 01B6 */ COLORREF m_rgbTimeOfDayGlobalLighting;
    /* 01BA */ COLORREF m_rgbTimeOfDayRainColor;
    /* 01BE */ BOOL m_updateListenPosition;
    /* 01C2 */ CGameArea* m_pArea;
    /* 01C6 */ CVidBitmap m_vbMessageScreen;
    /* 0280 */ DWORD m_strMessageText;
    /* 0284 */ BOOLEAN m_bRenderMessage;
    /* 0286 */ int field_286;
    /* 0288 */ DWORD m_nMessageEndTime;
    /* 028C */ int field_28C;
    /* 0290 */ int field_290;
    /* 0294 */ int field_294;
    /* 0298 */ int field_298;
    /* 029C */ int field_29C;
};

#endif /* CINFINITY_H_ */

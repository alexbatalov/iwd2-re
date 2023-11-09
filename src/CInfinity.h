#ifndef CINFINITY_H_
#define CINFINITY_H_

#include "mfc.h"

#include <ddraw.h>

#include "CResRef.h"
#include "CResTile.h"
#include "CSound.h"
#include "CVidBitmap.h"

class CGameArea;
class CResWED;
class CSearchBitmap;
class CVidCell;
class CVidFont;
class CVidMode;
class CVisibilityMap;
class CVRamPool;

typedef struct {
    BYTE tileNW;
    BYTE tileNE;
    BYTE tileSW;
    BYTE tileSE;
} TILE_CODE;

typedef struct {
    SHORT left;
    SHORT top;
    SHORT right;
    SHORT bottom;
    SHORT x;
    SHORT y;
    TILE_CODE tileCode;
} TEXTURE;

class CResInfTile : public CResTile {
public:
    CResInfTile(BOOLEAN a1, BOOLEAN a2);
    ~CResInfTile() override;

    /* 0064 */ int m_nVRamTile;
    /* 0068 */ TILE_CODE m_renderCode;
    /* 006C */ CResTile* m_pDualTileRes;
    /* 0070 */ unsigned char m_nVRamFlags;
};

class CInfTileSet {
public:
    static const DWORD USE_COLORKEY;
    static const DWORD TRANSLUCENT;
    static const BYTE byte_851930;
    static const BYTE byte_851931;
    static const BYTE byte_851932;
    static DWORD WATER_ALPHA;
    static TEXTURE m_aTextures[2700];
    static int m_nTextures;

    CInfTileSet();
    ~CInfTileSet();

    int AttachToVRam(int nTile);
    int DetachFromVRam(int nTile);
    BOOL RenderToPrimary(LPDIRECTDRAWSURFACE pSurface, INT nTile, INT nStencilTile, const TILE_CODE& tileCode, BYTE nDualTileCode, int a6, DWORD dwFlags);
    BOOL Render(CVidMode* pVidMode, INT nSurface, INT nTile, INT nStencilTile, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags, DWORD nColorKey, BYTE nDualTileCode, int a12);
    BOOL RenderBlack(CVidMode* pVidMode, INT nSurface, const CRect& rDest, INT x, INT y);
    BOOL RenderToSecondary(LPDIRECTDRAWSURFACE pSurface, INT nSurface, const CRect& rDest, INT x, INT y, DWORD dwFlags, DWORD nColorKey);
    BOOL SetResID(RESID nNewID, CResRef cResRef, RESID nNewDualID, CResRef cDualResRef);

    BOOLEAN GetTileRenderCode(INT nTile, TILE_CODE& tileCode);
    BOOLEAN SetTileRenderCode(INT nTile, TILE_CODE& tileCode);

    BOOL Render3d(INT nTile, INT nStencilTile, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags, BYTE nDualTileCode, int a9);
    BOOL ReadyTexture(INT nTextureId, INT nTile, INT nStencilTile, const TILE_CODE& tileCode, BYTE nDualTileCode, int a9, DWORD dwFlags);
    void RenderTexture(INT nTextureId, const CRect& rDest, INT x, INT y, const TILE_CODE& tileCode, DWORD dwFlags);
    static void sub_5D2DE0();

    void Invalidate();

    /* 0000 */ COLORREF m_rgbAddColor;
    /* 0004 */ COLORREF m_rgbTintColor;
    /* 0008 */ CVidTile m_cVidTile;
    /* 00B0 */ CVRamPool* m_pVRamPool;
    /* 00B4 */ CResInfTile** m_pResTiles;
    /* 00B8 */ int m_nTiles;
};

typedef struct TileDefinition {
    /* 0000 */ int nTile;
    /* 0004 */ int nRefCount;
    /* 0008 */ CInfTileSet* pTileSet;
} TileDefinition;

class CVRamPool {
public:
    CVRamPool();
    ~CVRamPool();

    BOOL AttachSurfaces(CVidMode* pVidMode);
    void ClearAll();
    BOOL DetachSurfaces();
    void InvalidateAll();

    int AssociateTile(CInfTileSet* pTileSet, int nTile);
    BOOL EmptyTile(int nVTile);

    int m_nVTiles;
    IDirectDrawSurface** m_pSurfaces;
    TileDefinition* m_pTileDefs;
};

class CInfinity {
public:
    static const DWORD FXPREP_COPYFROMBACK;
    static const DWORD FXPREP_CLEARFILL;
    static const DWORD MIRROR_FX;
    static const DWORD MIRROR_FX_UPDOWN;
    static const DWORD CLIPPING_IGNORE_VERTICAL;
    static const COLORREF RGB_DAY_COLOR;
    static const COLORREF RGB_NIGHT_COLOR;
    static const COLORREF RGB_PRIMEDUSK_COLOR;
    static const COLORREF RGB_PRIMEDAWN_COLOR;
    static const COLORREF RGB_DAY_RAINCOLOR;
    static const COLORREF RGB_NIGHT_RAINCOLOR;
    static const COLORREF RGB_PRIMEDUSK_RAINCOLOR;
    static const COLORREF RGB_PRIMEDAWN_RAINCOLOR;
    static const BYTE TRUE_DAWNDUSK_INTENSITY;
    static const BYTE SCROLL_DELAY;
    static const DWORD RENDER_ERROR;
    static const DWORD RENDER_OK;
    static const DWORD RENDER_MESSAGESCREEN;
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

    BOOL AttachWED(CResWED* resNewWED, WORD areaType, BYTE dayNightCode);
    BOOL AttachVRamPool(CVRamPool* pNewVRPool);
    void CacheTiles();
    BOOL AttachVRamRect(int x1, int y1, int x2, int y2);
    BOOL CancelRequestRect(unsigned char a1);
    void ScrollingCancelRequestRect(unsigned char a1);
    BOOL DetachVRamRect();
    BOOL DrawEllipse(const CPoint& ptCenter, const CSize& axes, COLORREF rgbColor);
    BOOL DrawHighlightRect(const CRect& rSquare, COLORREF rgbColor, BYTE width);
    INT GetSegmentPoints(POINT** ppPoints, int nEndX, int nEndY, int nStartX, int nStartY);
    CPoint GetWorldCoordinates(const CPoint& ptScreen);
    BOOL FreeWED();
    BOOL FXBltFrom(INT nDestSurface, CRect& rFXRect, INT x, INT y, INT nRefPointX, INT nRefPointY, DWORD dwFlags);
    BOOL FXPrep(CRect& rFXRect, DWORD dwFlags, INT nDestSurface, const CPoint& ptPos, const CPoint& ptReference);
    BOOL FXLock(CRect& rBack, DWORD dwFlags);
    BOOL FXTextOut(CVidFont* pFont, const CString& sString, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue);
    BOOL FXRenderClippingPolys(INT nPosX, INT nPosY, INT nPosZ, const CPoint& ptRef, const CRect& rGCBounds, BOOLEAN bDithered, DWORD dwBlitFlags);
    BOOL FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef);
    COLORREF GetGlobalLighting();
    void GetPointsOctant0(POINT* pPoints, int nStartX, int nStartY, int nDx, int nDy, int nXDirection);
    void GetPointsOctant1(POINT* pPoints, int nStartX, int nStartY, int nDx, int nDy, int nXDirection);
    void GetViewPosition(INT& x, INT& y);
    BOOL PostRender(CVidMode* pNewVidMode, int a2, CSearchBitmap* pVisibilityMap);
    DWORD Render(CVidMode* pNewVidMode, INT nSurface, INT nScrollState, CVisibilityMap* pVisibilityMap);
    BOOL RenderLightning(INT nSurface, CRect& rSurface, INT nStartX, INT nStartY, INT nEndX, INT nEndY, COLORREF rgbCenter, COLORREF rgbMiddle, COLORREF rgbOuter);
    BOOL RequestRect(int x1, int y1, int x2, int y2);
    BOOL ScrollingRequestRect(int x1, int y1, int x2, int y2, INT nScrollState);
    void CancelRequestTile(int x, int y, unsigned char a3);
    void RequestTile(int x, int y, unsigned char a3, int priority);
    BOOL InitViewPort(const CRect& rRect);
    BOOL SetViewPort(const CRect& rRect);
    BOOL SetViewPosition(INT x, INT y, BOOLEAN bSetExactScale);
    void CallLightning(INT xWorldPos, INT yWorldPos);
    void Scroll(CPoint ptDest, SHORT speed);
    void SetCurrentWeather(COLORREF rgbOvercast, SHORT nWeather, int nWeatherLevel, int nLightningFrequency);
    void SetDay();
    void SetNight();
    void SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetApproachingDawn();
    void SetApproachingDusk();
    void UpdateLightning();
    void AdjustViewPosition(BYTE nScrollState);
    void AIUpdate();
    void SwapVRamTiles(WORD wFromTile, WORD wToTile);
    void SetMessageScreen(CResRef resRef, DWORD strText, DWORD nDuration);
    DWORD RenderMessageScreen(CVidMode* pNewVidMode, INT nSurface);

    void SetAreaType(WORD areaType);

    COLORREF GetFadedColor(COLORREF rgbBrighter, COLORREF rgbDarker, BYTE nIntensity);
    void SetDawnMultiHost(BYTE nIntensity);
    void SetDuskMultiHost(BYTE nIntensity);
    CPoint GetScreenCoordinates(const CPoint& ptWorld);
    void InvalidateRainTiles();

    void UpdateListenPosition() { m_updateListenPosition = TRUE; }

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
    /* 00B8 */ CSound sndThunder;
    /* 011C */ int nCurrentLightningFrequency;
    /* 0120 */ int nNextLightningFrequency;
    /* 0124 */ int field_124;
    /* 0128 */ int nCurrentRainLevel;
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
    /* 015B */ unsigned char m_oldRenderDayNightCode;
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
    /* 0286 */ WORD field_286;
    /* 0288 */ DWORD m_nMessageEndTime;
    /* 028C */ BOOL m_bScreenShake;
    /* 0290 */ CPoint m_screenShakeDelta;
    /* 0298 */ CPoint m_screenShakeDecrease;
};

#endif /* CINFINITY_H_ */

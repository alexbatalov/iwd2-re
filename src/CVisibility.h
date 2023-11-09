#ifndef CVISIBILITY_H_
#define CVISIBILITY_H_

#include "CInfinity.h"
#include "CVidMode.h"

class CGameArea;

class CVisibilityMap {
public:
    static const BYTE EXPLORED_RANGE_0;
    static const BYTE EXPLORED_RANGE_1;
    static const BYTE EXPLORED_RANGE_2;
    static const BYTE EXPLORED_RANGE_3;
    static const BYTE EXPLORED_RANGE_4;
    static const BYTE EXPLORED_RANGE_5;
    static const BYTE EXPLORED_RANGE_6;

    static const BYTE SQUARE_SIZEX;
    static const BYTE SQUARE_SIZEY;

    static const BYTE EXPLORED;
    static const TILE_CODE EXPLORED_FULL;

    static const BYTE EXPLORED_FLAG;
    static const BYTE VISIBILITY_MASK;
    static const BYTE UNEXPLORED;

    static const BYTE UNEXPLORED_N;
    static const BYTE UNEXPLORED_NE;
    static const BYTE UNEXPLORED_E;
    static const BYTE UNEXPLORED_SE;
    static const BYTE UNEXPLORED_S;
    static const BYTE UNEXPLORED_SW;
    static const BYTE UNEXPLORED_W;
    static const BYTE UNEXPLORED_NW;
    static const TILE_CODE UNEXPLORED_FULL;

    static const BYTE FOGOWAR_EXPLORED_MASK;
    static const BYTE FOGOWAR_EXPLORED_SHIFT;
    static const BYTE FOGOWAR_MASK;
    static const BYTE FOGOWAR_SHIFT;

    static POLYCOLOR FOGOWARSHADE;
    static POLYCOLOR EXPLORESHADE;
    static POLYCOLOR CLEARSHADE;

    CVisibilityMap();
    ~CVisibilityMap();
    BOOL AddCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable);
    void sub_5518A0();
    void ClimbWall(const CPoint& ptStart, const CPoint& ptEnd, BYTE charId, const BYTE* pVisibileTerrainTable, SHORT nHighest);
    static void BltDitherPattern(LPDIRECTDRAWSURFACE pSurface, const TILE_CODE& tileCode);
    static void BltFogOWar(LPDIRECTDRAWSURFACE pSurface, const TILE_CODE& tileCode);
    BOOL IsCharacterIdOnMap(LONG charId);
    BYTE GetSubTileCode(LONG nTile);
    void GetTileCode(SHORT n64x64Tile, TILE_CODE& tileCode);
    void Init(CGameArea* pArea);
    void Marshal(BYTE** pData, DWORD* pnData);
    void Unmarshal(BYTE* pData, DWORD nData);
    void MarkTileLine(const CPoint& ptView, const CPoint& ptSearchMapView, LONG nDestX, LONG nDestY, const CPoint& ptOffset, BYTE charId, const BYTE* pVisibleTerrainTable, BOOLEAN bLookingUp);
    void PrivateAddCharacter(const CPoint& ptPos, BYTE visId, const BYTE* pVisibleTerrainTable);
    void RemoveCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable);
    void sub_553440(const CPoint& pt, BYTE charId);
    void sub_5535D0(const CPoint& pt, BYTE charId);
    void SetAreaExplored();
    void SetAreaUnexplored();
    void sub_553800(const CPoint& ptView, const CPoint& ptSearchMapView, const CPoint& ptOffset, BYTE charId, const BYTE* pVisibleTerrainTable);
    void sub_553990(const CPoint& ptView, const CPoint& ptSearchMapView, const CPoint& ptOffset, BYTE charId, const BYTE* pVisibleTerrainTable);
    void Uninit();
    void UpDate(const CPoint& ptOldPos, const CPoint& ptNewPos, LONG charId, const BYTE* pVisibleTerrainTable);
    BOOLEAN IsTileExplored(LONG nIndex);
    BOOLEAN IsTileVisible(LONG nIndex);
    void SetAreaVisible(BOOLEAN bVisible);

    static void BltFogOWar3d(INT x, INT y, const CRect& rDest, const TILE_CODE& tileCode);
    static void BltExploration3d(BYTE code, const CRect& rDest);
    static void BltVisibility3d(BYTE code, const CRect& rDest);

    SHORT PointToTile(const CPoint& pos);
    LONG GetBossTile(LONG n64x64Tile);
    BYTE GetCharacterPos(LONG charId);
    void SetTileExplored(LONG nIndex);
    void SetTileUnexplored(LONG nIndex);
    void SetTileVisible(LONG nIndex, BYTE charId);

    /* 0000 */ BYTE* m_pMap;
    /* 0004 */ BYTE field_4;
    /* 0006 */ SHORT m_nWidth;
    /* 0008 */ SHORT m_nHeight;
    /* 000A */ LONG m_nMapSize;
    /* 000E */ short field_E;
    /* 0010 */ short field_10;
    /* 0012 */ BYTE* field_12;
    /* 0016 */ BYTE* field_16;
    /* 001A */ BYTE field_1A;
    /* 001B */ BOOLEAN m_bOutDoor;
    /* 001C */ CCriticalSection m_critSect;
    /* 003C */ CSearchBitmap* m_pSearchMap;
    /* 0040 */ LONG m_aCharacterIds[6];
    /* 0058 */ BYTE* m_pDynamicHeight;
};

#endif /* CVISIBILITY_H_ */

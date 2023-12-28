#ifndef CSEARCHBITMAP_H_
#define CSEARCHBITMAP_H_

#include "mfc.h"

#include "CVidBitmap.h"

class CGameArea;

class CSearchBitmap {
public:
    static const BYTE COST_BASE_MELEE;
    static const BYTE COST_SCALE_MELEE;
    static const BYTE TRAVEL_WIDTH;
    static const BYTE PASSABLE;
    static const BYTE IMPASSABLE;
    static const BYTE IMPASSABLE_HEIGHT_ONE;
    static const BYTE IMPASSABLE_HEIGHT_TWO;
    static const BYTE IMPASSABLE_HEIGHT_THREE;

    CSearchBitmap();
    ~CSearchBitmap();
    BYTE GetLOSCost(const CPoint& point, const BYTE* terrainTable, SHORT& nTableIndex, BOOLEAN bVisbilityOutDoor);
    BYTE GetCost(const CPoint& point, const BYTE* terrainTable, BYTE personalSpace, SHORT& nTableIndex, BOOL bCheckBump);
    BYTE GetMobileCost(const CPoint& point, const BYTE* terrainTable, BYTE personalSpace, BOOL bCheckBump);
    SHORT GetStructureHeight(SHORT nTableIndex);
    void Init(CGameArea* pArea, CString szResRef);
    void Uninit();
    void SnapshotInit(const BYTE* terrainTable, BYTE* snapshotDynamicCost, BYTE sourceSide, BYTE snapshotPersonalSpace);
    BYTE SnapshotGetCost(CPoint point, BOOL bBump);
    void SnapshotRemoveObject(CPoint point, BYTE personalSpaceRange, BOOL bBumpable);
    void SnapshotAddObjectDiagonals(CPoint point, BYTE personalSpaceRange, BOOL bBumpable);
    void AddObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, BOOL bBumpable, BOOLEAN& bOnSearchMap);
    void RemoveObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, BOOL bBumpable, BOOLEAN& bOnSearchMap);
    void AddDoor(CPoint* pPoints, USHORT nPoints, BOOL bOpaque);
    void RemoveDoor(CPoint* pPoints, USHORT nPoints);
    BOOLEAN CanToggleDoor(const CPoint* pPoints, USHORT nPoints);

    SHORT GetTableIndex(const CPoint& pt);

    CGameArea* GetArea() { return m_pArea; }

    /* 0000 */ CVidBitmap m_resSearch;
    /* 00BA */ BYTE* m_pDynamicCost;
    /* 00BE */ BYTE* m_snapshotDynamicCost;
    /* 00C2 */ const BYTE* m_snapshotTerrainTable;
    /* 00C6 */ CCriticalSection m_critSect;
    /* 00E6 */ CSize m_GridSquareDimensions;
    /* 00EE */ CGameArea* m_pArea;
    /* 00F2 */ BYTE m_snapshotPersonalSpace;
    /* 00F3 */ BYTE m_sourceSide;
};

class CSearchRequest {
public:
    static const BYTE STATE_WAITING;
    static const BYTE STATE_PROCESSING;
    static const BYTE STATE_NO_TARGET;
    static const BYTE STATE_DONE;
    static const BYTE STATE_STALE;
    static const BYTE STATE_ERROR;

    static const BYTE LIST_FRONT;
    static const BYTE LIST_BACK_PROMOTE;
    static const BYTE LIST_BACK;

    static LONG MINNODES;
    static LONG MAXNODES;
    static LONG MINNODESBACK;
    static LONG MAXNODESBACK;

    CSearchRequest();
    CSearchRequest(const CSearchRequest& other);
    ~CSearchRequest();

    /* 0000 */ BYTE m_serviceState;
    /* 0001 */ BYTE m_collisionDelay;
    /* 0002 */ BOOL m_collisionSearch;
    /* 0006 */ BYTE m_sourceSide;
    /* 0007 */ BYTE m_nPartyIds;
    /* 0008 */ BYTE m_nTargetIds;
    /* 0009 */ BYTE m_nTargetPoints;
    /* 000A */ BOOL m_removeSelf;
    /* 000E */ BYTE m_frontList;
    /* 0010 */ CSearchBitmap* m_searchBitmap;
    /* 0014 */ BYTE m_terrainTable[16];
    /* 0024 */ BOOL m_pathSmooth;
    /* 0028 */ BOOL m_exclusiveTargetPoints;
    /* 002C */ LONG m_sourceId;
    /* 0030 */ POINT m_sourcePt;
    /* 0038 */ LONG* m_partyIds;
    /* 003C */ LONG* m_targetIds;
    /* 0040 */ POINT* m_targetPoints;
    /* 0044 */ LONG m_minNodes;
    /* 0048 */ LONG m_maxNodes;
    /* 004C */ LONG m_minNodesBack;
    /* 0050 */ LONG m_maxNodesBack;
    /* 0054 */ BOOL m_bBump;
    /* 0058 */ SHORT m_searchRc;
    /* 005A */ SHORT m_nPath;
    /* 005C */ LONG* m_pPath;
};

void SearchThreadMain(void* userInfo);

#endif /* CSEARCHBITMAP_H_ */

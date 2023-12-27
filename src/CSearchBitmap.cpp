#include "CSearchBitmap.h"

#include "CAIObjectType.h"
#include "CBaldurChitin.h"
#include "CGameObjectArray.h"
#include "CInfGame.h"
#include "CPathSearch.h"
#include "CUtil.h"

// 0x84EBD8
const BYTE CSearchBitmap::COST_BASE_MELEE = 100;

// 0x84EBD9
const BYTE CSearchBitmap::COST_SCALE_MELEE = 15;

// 0x84EBDA
const BYTE CSearchBitmap::TRAVEL_WIDTH = 2;

// 0x84EBDB
const BYTE CSearchBitmap::PASSABLE = 0;

// 0x84EBDC
const BYTE CSearchBitmap::IMPASSABLE = 4;

// 0x84EBDD
const BYTE CSearchBitmap::IMPASSABLE_HEIGHT_ONE = 1;

// 0x84EBDE
const BYTE CSearchBitmap::IMPASSABLE_HEIGHT_TWO = 2;

// 0x84EBDF
const BYTE CSearchBitmap::IMPASSABLE_HEIGHT_THREE = 3;

// 0x84EBE0
const BYTE CSearchRequest::STATE_WAITING = 0;

// 0x84EBE1
const BYTE CSearchRequest::STATE_PROCESSING = 1;

// 0x84EBE2
const BYTE CSearchRequest::STATE_NO_TARGET = 2;

// 0x84EBE3
const BYTE CSearchRequest::STATE_DONE = 3;

// 0x84EBE4
const BYTE CSearchRequest::STATE_STALE = 4;

// 0x84EBE5
const BYTE CSearchRequest::STATE_ERROR = 5;

// 0x84EBE6
const BYTE CSearchRequest::LIST_FRONT = 0;

// 0x84EBE7
const BYTE CSearchRequest::LIST_BACK_PROMOTE = 1;

// 0x84EBE8
const BYTE CSearchRequest::LIST_BACK = 2;

// 0x8AE1D8
LONG CSearchRequest::MINNODES = 500;

// 0x8AE1DC
LONG CSearchRequest::MAXNODES = 4000;

// 0x8AE1E0
LONG CSearchRequest::MINNODESBACK = 200;

// 0x8AE1E4
LONG CSearchRequest::MAXNODESBACK = 1000;

// -----------------------------------------------------------------------------

// 0x547900
CSearchBitmap::CSearchBitmap()
{
    m_sourceSide = 0;
    m_snapshotTerrainTable = 0;
    m_snapshotDynamicCost = 0;
    m_pDynamicCost = NULL;
    m_snapshotPersonalSpace = 0;
}

// 0x547980
CSearchBitmap::~CSearchBitmap()
{
    if (m_pDynamicCost != NULL) {
        delete m_pDynamicCost;
        m_pDynamicCost = NULL;
    }
}

// 0x547A00
BYTE CSearchBitmap::GetLOSCost(const CPoint& point, const BYTE* terrainTable, SHORT& nTableIndex, BOOLEAN bVisbilityOutDoor)
{
    BYTE cost;

    LONG nIndex = point.x + m_GridSquareDimensions.cx * point.y;
    if (nIndex < m_GridSquareDimensions.cx * m_GridSquareDimensions.cy) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
        // __LINE__: 225
        UTIL_ASSERT(terrainTable != NULL);

        switch (m_pDynamicCost[nIndex] & 0x81) {
        case 0x80:
            nTableIndex = bVisbilityOutDoor ? 8 : 0;
            cost = terrainTable[nTableIndex];
            break;
        case 0x1:
            nTableIndex = 8;
            cost = terrainTable[nTableIndex];
            break;
        default:
            if (m_resSearch.GetBitCount(TRUE) == 8) {
                nTableIndex = m_resSearch.GetPixelValue(point.x, point.y, TRUE) >> 4;
                cost = terrainTable[nTableIndex];
            } else {
                nTableIndex = m_resSearch.GetPixelValue(point.x, point.y, TRUE);
                cost = terrainTable[nTableIndex];
            }
            break;
        }
    } else {
        nTableIndex = 8;
        cost = terrainTable[nTableIndex];
    }

    return cost;
}

// 0x547B10
BYTE CSearchBitmap::GetCost(const CPoint& point, const BYTE* terrainTable, BYTE personalSpace, SHORT& nTableIndex, BOOL bCheckBump)
{
    // TODO: Incomplete.

    return 0;
}

// 0x547D30
BYTE CSearchBitmap::GetMobileCost(const CPoint& point, const BYTE* terrainTable, BYTE personalSpace, BOOL bCheckBump)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
    // __LINE__: 377
    UTIL_ASSERT(terrainTable != NULL);

    int radius = (personalSpace - 2) / 2;
    int minX = max(point.x - radius, 0);
    int maxX = min(point.x + radius, m_GridSquareDimensions.cx);
    int minY = max(point.y - radius, 0);
    int maxY = min(point.y + radius, m_GridSquareDimensions.cy);

    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            BYTE flags = m_pDynamicCost[y * m_GridSquareDimensions.cx + x];
            if ((flags & 0x81) == 0x80) {
                return terrainTable[0];
            } else if ((flags & 0x1) != 0) {
                return terrainTable[8];
            } else if ((flags & 0x70) != 0) {
                return terrainTable[8];
            } else if (bCheckBump && (flags & 0xE) != 0) {
                return terrainTable[8];
            }
        }
    }

    return 0;
}

// 0x547E60
void CSearchBitmap::AddObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, int a4, unsigned char& a5)
{
    // TODO: Incomplete.
}

// 0x548020
void CSearchBitmap::RemoveObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, int a4, unsigned char& a5)
{
    // TODO: Incomplete.
}

// 0x5482B0
SHORT CSearchBitmap::GetStructureHeight(SHORT nTableIndex)
{
    switch (nTableIndex) {
    case 0:
        return 1;
    case 10:
        return 2;
    case 13:
        return 3;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
        // __LINE__: 717
        UTIL_ASSERT(FALSE);
    }
}

// 0x548300
void CSearchBitmap::Init(CGameArea* pArea, CString szResRef)
{
    m_resSearch.SetResRef(CResRef(szResRef), TRUE, TRUE);
    m_resSearch.m_bDoubleSize = FALSE;
    m_resSearch.GetRes()->Demand();
    m_resSearch.GetImageDimensions(m_GridSquareDimensions, TRUE);
    m_pArea = pArea;
    m_pDynamicCost = new BYTE[m_GridSquareDimensions.cx * m_GridSquareDimensions.cy];
    memset(m_pDynamicCost, 0, m_GridSquareDimensions.cx * m_GridSquareDimensions.cy);
}

// 0x548490
void CSearchBitmap::Uninit()
{
    if (m_pDynamicCost != NULL) {
        delete m_pDynamicCost;
        m_pDynamicCost = NULL;
    }
    m_resSearch.GetRes()->Release();
}

// 0x5484C0
void CSearchBitmap::SnapshotInit(const BYTE* terrainTable, BYTE* snapshotDynamicCost, BYTE sourceSide, BYTE snapshotPersonalSpace)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
    // __LINE__: 806
    UTIL_ASSERT(terrainTable != NULL && snapshotDynamicCost != NULL);

    CSingleLock snapshotLock(&m_critSect, FALSE);

    m_snapshotPersonalSpace = snapshotPersonalSpace;
    m_snapshotTerrainTable = terrainTable;
    m_snapshotDynamicCost = snapshotDynamicCost;
    m_sourceSide = sourceSide;

    snapshotLock.Lock(INFINITE);
    memcpy(m_snapshotDynamicCost, m_pDynamicCost, m_GridSquareDimensions.cx * m_GridSquareDimensions.cy);
    snapshotLock.Unlock();
}

// 0x548EE0
void CSearchBitmap::AddDoor(CPoint* pPoints, USHORT nPoints, BOOL bOpaque)
{
    BYTE doorToggle = 0x80;

    if (bOpaque) {
        doorToggle |= 0x1;
    }

    for (USHORT nIndex = 0; nIndex < nPoints; nIndex++) {
        m_pDynamicCost[m_GridSquareDimensions.cx * pPoints[nIndex].y + pPoints[nIndex].x] |= doorToggle;
    }
}

// 0x548F30
void CSearchBitmap::RemoveDoor(CPoint* pPoints, USHORT nPoints)
{
    for (USHORT nIndex = 0; nIndex < nPoints; nIndex++) {
        m_pDynamicCost[m_GridSquareDimensions.cx * pPoints[nIndex].y + pPoints[nIndex].x] &= ~0x81;
    }
}

// 0x548F70
BOOLEAN CSearchBitmap::CanToggleDoor(const CPoint* pPoints, USHORT nPoints)
{
    for (USHORT nIndex = 0; nIndex < nPoints; nIndex++) {
        if ((m_pDynamicCost[m_GridSquareDimensions.cx * pPoints[nIndex].y + pPoints[nIndex].x] & 0x7E) != 0) {
            return FALSE;
        }
    }

    return TRUE;
}

// NOTE: Inlined.
SHORT CSearchBitmap::GetTableIndex(const CPoint& pt)
{
    INT x = pt.x / CPathSearch::GRID_SQUARE_SIZEX;
    INT y = pt.y / CPathSearch::GRID_SQUARE_SIZEY;

    return m_resSearch.GetBitCount(TRUE) == 8
        ? m_resSearch.GetPixelValue(x, y, TRUE) >> 4
        : m_resSearch.GetPixelValue(x, y, TRUE);
}

// -----------------------------------------------------------------------------

// 0x548FD0
CSearchRequest::CSearchRequest()
{
    m_serviceState = STATE_WAITING;
    m_removeSelf = TRUE;
    m_frontList = 0;
    m_searchBitmap = NULL;
    m_terrainTable[0] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[1] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[2] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[3] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[4] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[5] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[6] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[7] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[8] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[9] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[10] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[11] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[12] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[13] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[14] = CPathSearch::COST_IMPASSABLE;
    m_terrainTable[15] = CPathSearch::COST_IMPASSABLE;
    m_pathSmooth = FALSE;
    m_collisionSearch = FALSE;
    m_collisionDelay = 0;
    m_exclusiveTargetPoints = FALSE;
    m_sourceId = CGameObjectArray::INVALID_INDEX;
    m_sourcePt.x = -1;
    m_sourcePt.y = -1;
    m_sourceSide = CAIObjectType::EA_PC;
    m_nPartyIds = 0;
    m_partyIds = NULL;
    m_nTargetIds = 0;
    m_targetIds = NULL;
    m_nTargetPoints = 0;
    m_targetPoints = NULL;
    m_minNodes = g_pBaldurChitin->GetObjectGame()->GetFrameRate() < 10
        ? MINNODES * (g_pBaldurChitin->GetObjectGame()->GetFrameRate() + 1) / 10
        : MINNODES;
    m_maxNodes = MAXNODES;
    m_minNodesBack = g_pBaldurChitin->GetObjectGame()->GetFrameRate() < 10
        ? MINNODESBACK * (g_pBaldurChitin->GetObjectGame()->GetFrameRate() + 1) / 10
        : MINNODESBACK;
    m_maxNodesBack = MAXNODESBACK;
    m_searchRc = 0;
    m_nPath = 0;
    m_pPath = NULL;
    m_bBump = TRUE;
}

// 0x549110
CSearchRequest::CSearchRequest(const CSearchRequest& other)
{
    m_serviceState = STATE_WAITING;
    m_removeSelf = other.m_removeSelf;
    m_frontList = 0;
    m_searchBitmap = other.m_searchBitmap;
    memcpy(m_terrainTable, other.m_terrainTable, sizeof(m_terrainTable));
    m_pathSmooth = other.m_pathSmooth;
    m_collisionSearch = FALSE;
    m_collisionDelay = 0;
    m_exclusiveTargetPoints = other.m_exclusiveTargetPoints;
    m_sourcePt.x = -1;
    m_sourcePt.y = -1;
    m_sourceId = other.m_sourceId;
    m_nPartyIds = 0;
    m_partyIds = NULL;
    if (other.m_nPartyIds > 0) {
        m_partyIds = new LONG[other.m_nPartyIds];
        if (m_partyIds != NULL) {
            m_nPartyIds = other.m_nPartyIds;
            memcpy(m_partyIds, other.m_partyIds, sizeof(LONG) * other.m_nPartyIds);
        }
    }
    m_nTargetIds = 0;
    m_targetIds = NULL;
    if (other.m_nTargetIds > 0) {
        m_targetIds = new LONG[other.m_nTargetIds];
        if (m_targetIds != NULL) {
            m_nTargetIds = other.m_nTargetIds;
            memcpy(m_targetIds, other.m_targetIds, sizeof(LONG) * other.m_nTargetIds);
        }
    }
    m_nTargetPoints = 0;
    m_targetPoints = NULL;
    if (other.m_nTargetPoints > 0) {
        m_targetPoints = new POINT[other.m_nTargetPoints];
        if (m_targetPoints != NULL) {
            m_nTargetPoints = other.m_nTargetPoints;
            memcpy(m_targetPoints, other.m_targetPoints, sizeof(POINT) * other.m_nTargetPoints);
        }
    }
    m_minNodes = other.m_minNodes;
    m_maxNodes = other.m_maxNodes;
    m_minNodesBack = other.m_minNodesBack;
    m_maxNodesBack = other.m_maxNodesBack;
    m_searchRc = 0;
    m_nPath = 0;
    m_pPath = NULL;
    m_bBump = other.m_bBump;
}

// 0x549290
CSearchRequest::~CSearchRequest()
{
    if (m_partyIds != NULL) {
        delete m_partyIds;
    }

    if (m_targetIds != NULL) {
        delete m_targetIds;
    }

    if (m_targetPoints != NULL) {
        delete m_targetPoints;
    }

    if (m_pPath != NULL) {
        delete m_pPath;
    }
}

// -----------------------------------------------------------------------------

// 0x5492E0
void SearchThreadMain(void* userInfo)
{
    // TODO: Incomplete.
}

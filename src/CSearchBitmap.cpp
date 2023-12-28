#include "CSearchBitmap.h"

#include "CAIObjectType.h"
#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
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
    BYTE totalCost;
    BYTE cost;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
    // __LINE__: 265
    UTIL_ASSERT(terrainTable != NULL);

    if (m_resSearch.GetBitCount(TRUE) == 8) {
        nTableIndex = m_resSearch.GetPixelValue(point.x, point.y, TRUE);
        if (terrainTable[nTableIndex >> 4] != CPathSearch::COST_IMPASSABLE) {
            if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bTerrainHugging) {
                totalCost = min(terrainTable[nTableIndex >> 4] * ((nTableIndex & 0xF) + 2) / 2, CPathSearch::COST_IMPASSABLE - 1);
            } else {
                totalCost = terrainTable[nTableIndex >> 4];
            }
        } else {
            totalCost = CPathSearch::COST_IMPASSABLE;
        }
        nTableIndex >>= 4;
    } else {
        nTableIndex = m_resSearch.GetPixelValue(point.x, point.y, TRUE);
        totalCost = terrainTable[nTableIndex];
    }

    if (totalCost == CPathSearch::COST_IMPASSABLE) {
        return totalCost;
    }

    int radius = (personalSpace - 2) / 2;
    int minX = max(point.x - radius, 0);
    int maxX = min(point.x + radius, m_GridSquareDimensions.cx);
    int minY = max(point.y - radius, 0);
    int maxY = min(point.y + radius, m_GridSquareDimensions.cy);

    BYTE shift = 0;
    if (m_resSearch.GetBitCount(TRUE) == 8) {
        shift = 4;
    }

    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            cost = terrainTable[m_resSearch.GetPixelValue(x, y, TRUE) >> shift];
            if (cost == CPathSearch::COST_IMPASSABLE) {
                return cost;
            }
        }
    }

    cost = GetMobileCost(point, terrainTable, personalSpace, bCheckBump);
    if (cost == 0) {
        cost = totalCost;
    }

    return cost;
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

// 0x5488C0
void CSearchBitmap::SnapshotRemoveObject(CPoint point, BYTE personalSpaceRange, BOOL bBumpable)
{
    // TODO: Incomplete.
}

// 0x5489E0
void CSearchBitmap::SnapshotAddObjectDiagonals(CPoint point, BYTE personalSpaceRange, BOOL bBumpable)
{
    // TODO: Incomplete.
}

// 0x547E60
void CSearchBitmap::AddObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, BOOL bBumpable, BOOLEAN& bOnSearchMap)
{
    if (bOnSearchMap != TRUE) {
        if (point.x >= 0 && point.y >= 0 && point.x < 320 && point.y < 320) {
            int radius = (personalSpaceRange - 1) / 2;
            int minX = max(point.x - radius, 0);
            int maxX = min(point.x + radius, m_GridSquareDimensions.cx - 1);
            int minY = max(point.y - radius, 0);
            int maxY = min(point.y + radius, m_GridSquareDimensions.cy - 1);

            CSingleLock lock(&m_critSect, FALSE);
            if (lock.Lock(INFINITE)) {
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        int index = y * m_GridSquareDimensions.cx + x;
                        if (bBumpable) {
                            m_pDynamicCost[index] = (m_pDynamicCost[index] & ~0xE) | ((m_pDynamicCost[index] + 2) & 0xE);
                        } else {
                            m_pDynamicCost[index] = (m_pDynamicCost[index] & ~0x70) | ((m_pDynamicCost[index] + 16) & 0x70);
                        }
                    }
                }
                bOnSearchMap = TRUE;
                lock.Unlock();
            }
        }
    }
}

// 0x548020
void CSearchBitmap::RemoveObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, BOOL bBumpable, BOOLEAN& bOnSearchMap)
{
    if (bOnSearchMap != FALSE) {
        if (point.x >= 0 && point.y >= 0 && point.x < 320 && point.y < 320) {
            int radius = (personalSpaceRange - 1) / 2;
            int minX = max(point.x - radius, 0);
            int maxX = min(point.x + radius, m_GridSquareDimensions.cx - 1);
            int minY = max(point.y - radius, 0);
            int maxY = min(point.y + radius, m_GridSquareDimensions.cy - 1);

            CSingleLock lock(&m_critSect, FALSE);
            if (lock.Lock(INFINITE)) {
                for (int x = minX; x <= maxX; x++) {
                    for (int y = minY; y <= maxY; y++) {
                        int index = y * m_GridSquareDimensions.cx + x;
                        if (bBumpable) {
                            m_pDynamicCost[index] = (m_pDynamicCost[index] & ~0xE) | ((m_pDynamicCost[index] - 2) & 0xE);
                        } else {
                            m_pDynamicCost[index] = (m_pDynamicCost[index] & ~0x70) | ((m_pDynamicCost[index] - 16) & 0x70);
                        }
                    }
                }
                bOnSearchMap = TRUE;
                lock.Unlock();
            } else {
                CString sError;
                sError.Format("Jake says: Can't lock the thread, search map squares not removed at [%d.%d] with personal space of %d",
                    point.x,
                    point.y,
                    personalSpaceRange);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
                // __LINE__: 611
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }
        } else {
            CString sError;
            sError.Format("Jake says: xy is bad, search map squares not removed at [%d.%d] with personal space of %d",
                point.x,
                point.y,
                personalSpaceRange);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
            // __LINE__: 585
            UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
        }
    }
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

// 0x5485A0
BYTE CSearchBitmap::SnapshotGetCost(CPoint point, BOOL bBump)
{
    BYTE terrainCost;
    SHORT totalCost;

    if (m_sourceSide <= CAIObjectType::EA_CONTROLCUTOFF) {
        CPoint pt(point.x * CPathSearch::GRID_SQUARE_SIZEX, point.y * CPathSearch::GRID_SQUARE_SIZEY);
        if (!m_pArea->m_visibility.IsTileExplored(m_pArea->m_visibility.PointToTile(pt))) {
            return CPathSearch::COST_IMPASSABLE;
        }
    }

    if (m_resSearch.GetBitCount(TRUE) == 8) {
        SHORT nTableIndex = m_resSearch.GetPixelValue(point.x, point.y, TRUE) >> 4;
        if (m_snapshotTerrainTable[nTableIndex] != CPathSearch::COST_IMPASSABLE) {
            if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bTerrainHugging) {
                terrainCost = min(m_snapshotTerrainTable[nTableIndex] * (nTableIndex + 2) / 2, CPathSearch::COST_IMPASSABLE - 1);
            } else {
                terrainCost = m_snapshotTerrainTable[nTableIndex];
            }
        } else {
            terrainCost = CPathSearch::COST_IMPASSABLE;
        }
    } else {
        terrainCost = m_snapshotTerrainTable[m_resSearch.GetPixelValue(point.x, point.y, TRUE)];
    }

    totalCost = terrainCost;

    if (totalCost == CPathSearch::COST_IMPASSABLE) {
        return CPathSearch::COST_IMPASSABLE;
    }

    int radius = (m_snapshotPersonalSpace - 2) / 2;
    int minX = max(point.x - radius, 0);
    int maxX = min(point.x + radius, m_GridSquareDimensions.cx);
    int minY = max(point.y - radius, 0);
    int maxY = min(point.y + radius, m_GridSquareDimensions.cy);

    BYTE shift = 0;
    if (m_resSearch.GetBitCount(TRUE) == 8) {
        shift = 4;
    }

    for (int x = minX; x <= maxX; x++) {
        for (int y = minY; y <= maxY; y++) {
            BYTE cost = m_snapshotTerrainTable[m_resSearch.GetPixelValue(x, y, TRUE) >> shift];
            if (cost == CPathSearch::COST_IMPASSABLE) {
                return CPathSearch::COST_IMPASSABLE;
            }

            BYTE dynamicCost = m_snapshotDynamicCost[y * m_GridSquareDimensions.cx + x];
            if ((dynamicCost & 0x80) != 0) {
                return m_snapshotTerrainTable[0];
            } else if ((dynamicCost & 0x70) != 0) {
                return m_snapshotTerrainTable[8];
            }

            if (bBump) {
                totalCost += 10 * terrainCost * (dynamicCost & 0xE) / 2;
            } else {
                if ((dynamicCost & 0xE) != 0) {
                    return m_snapshotTerrainTable[8];
                }
            }
        }
    }

    // NOTE: Signed compare.
    if (totalCost < static_cast<SHORT>(CPathSearch::COST_IMPASSABLE)) {
        return static_cast<BYTE>(totalCost);
    }

    return CPathSearch::COST_IMPASSABLE - 1;
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
    POINT goalPts[15];
    POINT goalRemoveObject[15];
    BYTE goalObjectSpaces[15];
    BOOL goalBumpable[15];
    BOOLEAN isWalking[15];
    CGameObject* pObject;
    CGameArea* pArea;
    CSearchRequest* searchRequest;
    BOOL targetIdPresent = FALSE;
    BOOL targetPointPresent = FALSE;
    BOOL searchShutdown;
    BYTE snapshotDynamicCost[320 * 320]; // NOTE: Forces `alloca`.
    BOOL bBump;
    BOOL bBumpable;
    SHORT cnt;
    BYTE rc;
    BYTE deadLockCnt;
    BYTE objectSpace;
    CRect rGrid;
    POINT startPt;
    CPoint tempPoint;

    CSingleLock searchLock(&(g_pBaldurChitin->GetObjectGame()->field_1B58), FALSE);
    g_pBaldurChitin->RegisterThread();

    while (WaitForSingleObject(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, INFINITE) == WAIT_OBJECT_0) {
        searchLock.Lock();
        if (g_pBaldurChitin->GetObjectGame()->m_searchRequests.IsEmpty()
            && g_pBaldurChitin->GetObjectGame()->m_searchRequestsBack.IsEmpty()) {
            searchLock.Unlock();
            break;
        }

        searchShutdown = g_pBaldurChitin->GetObjectGame()->m_searchShutdown;
        while (!g_pBaldurChitin->GetObjectGame()->m_searchRequests.IsEmpty()
            && !g_pBaldurChitin->GetObjectGame()->m_searchRequestsBack.IsEmpty()) {
            if (g_pBaldurChitin->GetObjectGame()->m_searchRequests.IsEmpty()) {
                searchRequest = g_pBaldurChitin->GetObjectGame()->m_searchRequestsBack.RemoveHead();
            } else {
                searchRequest = g_pBaldurChitin->GetObjectGame()->m_searchRequests.RemoveHead();
            }

            if (searchRequest->m_serviceState != CSearchRequest::STATE_STALE) {
                if (!g_pBaldurChitin->GetObjectGame()->m_bInDestroyGame) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CSearchBitmap.cpp
                    // __LINE__: 1735
                    UTIL_ASSERT(searchRequest->m_serviceState == CSearchRequest::STATE_WAITING);

                    if (!searchShutdown) {
                        if (searchRequest->m_frontList == CSearchRequest::LIST_FRONT) {
                            if (g_pBaldurChitin->GetObjectGame()->m_searchRequests.IsEmpty()) {
                                g_pBaldurChitin->GetObjectGame()->m_searchRequestListEmpty = TRUE;
                            }
                        }
                        searchRequest->m_serviceState = CSearchRequest::STATE_PROCESSING;
                        searchLock.Unlock();

                        if (searchRequest->m_collisionSearch) {
                            g_pBaldurChitin->GetObjectGame()->m_pathSearch->m_pathSmooth = FALSE;
                        } else {
                            g_pBaldurChitin->GetObjectGame()->m_pathSearch->m_pathSmooth = searchRequest->m_pathSmooth;
                        }

                        if (searchRequest->m_nTargetPoints > 0) {
                            memcpy(goalPts, searchRequest->m_targetPoints, sizeof(POINT) * searchRequest->m_nTargetPoints);
                            targetPointPresent = TRUE;
                        }

                        do {
                            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(searchRequest->m_sourceId,
                                CGameObjectArray::THREAD_SEARCH,
                                &pObject,
                                INFINITE);
                        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                        if (rc == CGameObjectArray::SUCCESS
                            && (!searchRequest->m_removeSelf || pObject->OnSearchMap())
                            && pObject->GetArea() == searchRequest->m_searchBitmap->m_pArea) {
                            startPt = pObject->GetPos();
                            startPt.x /= CPathSearch::GRID_SQUARE_SIZEX;
                            startPt.y /= CPathSearch::GRID_SQUARE_SIZEY;
                            if (startPt.x < 0 || startPt.x > CPathSearch::GRID_ACTUALX) {
                                startPt.x = 0;
                            }
                            if (startPt.y < 0 || startPt.y > CPathSearch::GRID_ACTUALY) {
                                startPt.y = 0;
                            }
                            pArea = pObject->GetArea();
                            bBump = searchRequest->m_bBump;
                            if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                                objectSpace = static_cast<CGameSprite*>(pObject)->GetAnimation()->GetPersonalSpace();
                                bBumpable = static_cast<CGameSprite*>(pObject)->field_54A8;
                                if (static_cast<CGameSprite*>(pObject)->GetAIType().GetEnemyAlly() > CAIObjectType::EA_GOODCUTOFF) {
                                    bBump = FALSE;
                                }
                            } else {
                                objectSpace = 0;
                                bBumpable = FALSE;
                                bBump = FALSE;
                            }

                            for (cnt = 0; cnt < searchRequest->m_nTargetIds; cnt++) {
                                deadLockCnt = 0;
                                do {
                                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(searchRequest->m_targetIds[cnt],
                                        CGameObjectArray::THREAD_SEARCH,
                                        &pObject,
                                        INFINITE);
                                    if (rc != CGameObjectArray::DENIED) {
                                        break;
                                    }
                                    deadLockCnt++;
                                } while (deadLockCnt != 255);

                                if (rc == CGameObjectArray::SUCCESS
                                    && pObject->OnSearchMap()
                                    && pArea == pObject->GetArea()) {
                                    if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                                        static_cast<CGameSprite*>(pObject)->GetNextWaypoint(&tempPoint);
                                    } else {
                                        tempPoint = pObject->GetPos();
                                    }

                                    goalPts[cnt + searchRequest->m_nTargetPoints].x = tempPoint.x / CPathSearch::GRID_SQUARE_SIZEX;
                                    goalPts[cnt + searchRequest->m_nTargetPoints].y = tempPoint.y / CPathSearch::GRID_SQUARE_SIZEY;

                                    if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                                        goalObjectSpaces[cnt] = static_cast<CGameSprite*>(pObject)->GetAnimation()->GetPersonalSpace();
                                        goalBumpable[cnt] = static_cast<CGameSprite*>(pObject)->field_54A8;
                                        goalRemoveObject[cnt].x = static_cast<CGameSprite*>(pObject)->GetPos().x / CPathSearch::GRID_SQUARE_SIZEX;
                                        goalRemoveObject[cnt].y = static_cast<CGameSprite*>(pObject)->GetPos().y / CPathSearch::GRID_SQUARE_SIZEY;
                                        targetIdPresent = TRUE;
                                    } else {
                                        goalObjectSpaces[cnt] = 0;
                                        goalBumpable[cnt] = FALSE;
                                        goalRemoveObject[cnt].x = -1;
                                        goalRemoveObject[cnt].y = -1;
                                    }
                                } else {
                                    if (rc == CGameObjectArray::SUCCESS) {
                                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_targetIds[cnt],
                                            CGameObjectArray::THREAD_SEARCH,
                                            INFINITE);
                                    }

                                    searchRequest->m_targetIds[cnt] = CGameObjectArray::INVALID_INDEX;
                                    goalObjectSpaces[cnt] = 1;
                                    goalBumpable[cnt] = FALSE;
                                    goalRemoveObject[cnt].x = -1;
                                    goalRemoveObject[cnt].y = -1;
                                    goalPts[cnt + searchRequest->m_nTargetPoints].x = -1;
                                    goalPts[cnt + searchRequest->m_nTargetPoints].y = -1;
                                }
                            }

                            if (targetPointPresent || targetIdPresent) {
                                if (!searchRequest->m_collisionSearch) {
                                    for (cnt = 0; cnt < searchRequest->m_nPartyIds; cnt++) {
                                        deadLockCnt = 0;
                                        do {
                                            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(searchRequest->m_partyIds[cnt],
                                                CGameObjectArray::THREAD_SEARCH,
                                                &pObject,
                                                INFINITE);
                                            if (rc != CGameObjectArray::DENIED) {
                                                break;
                                            }
                                            deadLockCnt++;
                                        } while (deadLockCnt != 255);

                                        if (rc == CGameObjectArray::SUCCESS
                                            && pObject->OnSearchMap()
                                            && pArea == pObject->GetArea()) {
                                            goalPts[cnt + searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds] = pObject->GetPos();
                                            goalPts[cnt + searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds].x /= CPathSearch::GRID_SQUARE_SIZEX;
                                            goalPts[cnt + searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds].y /= CPathSearch::GRID_SQUARE_SIZEY;

                                            if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                                                goalObjectSpaces[cnt + searchRequest->m_nTargetIds] = static_cast<CGameSprite*>(pObject)->GetAnimation()->GetPersonalSpace();
                                                goalBumpable[cnt + searchRequest->m_nTargetIds] = static_cast<CGameSprite*>(pObject)->field_54A8;
                                                goalRemoveObject[cnt + searchRequest->m_nTargetIds].x = static_cast<CGameSprite*>(pObject)->GetPos().x / CPathSearch::GRID_SQUARE_SIZEX;
                                                goalRemoveObject[cnt + searchRequest->m_nTargetIds].y = static_cast<CGameSprite*>(pObject)->GetPos().y / CPathSearch::GRID_SQUARE_SIZEY;
                                                isWalking[cnt] = static_cast<CGameSprite*>(pObject)->m_nSequence == CGameSprite::SEQ_WALK
                                                    || static_cast<CGameSprite*>(pObject)->m_curAction.GetActionID() == CAIAction::MOVETOPOINT;
                                            } else {
                                                goalObjectSpaces[cnt + searchRequest->m_nTargetIds] = 0;
                                                goalBumpable[cnt + searchRequest->m_nTargetIds] = FALSE;
                                                goalRemoveObject[cnt + searchRequest->m_nTargetIds].x = -1;
                                                goalRemoveObject[cnt + searchRequest->m_nTargetIds].y = -1;
                                                isWalking[cnt] = FALSE;
                                            }
                                        } else {
                                            if (rc == CGameObjectArray::SUCCESS) {
                                                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_partyIds[cnt],
                                                    CGameObjectArray::THREAD_SEARCH,
                                                    INFINITE);
                                            }

                                            searchRequest->m_partyIds[cnt] = CGameObjectArray::INVALID_INDEX;
                                            goalPts[cnt + searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds].x = -1;
                                            goalPts[cnt + searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds].y = -1;
                                            goalObjectSpaces[cnt + searchRequest->m_nTargetIds] = 1;
                                            goalBumpable[cnt + searchRequest->m_nTargetIds] = FALSE;
                                            goalRemoveObject[cnt + searchRequest->m_nTargetIds].x = -1;
                                            goalRemoveObject[cnt + searchRequest->m_nTargetIds].y = -1;
                                        }
                                    }
                                }

                                rGrid.right = searchRequest->m_searchBitmap->m_GridSquareDimensions.cx - 1;
                                rGrid.bottom = searchRequest->m_searchBitmap->m_GridSquareDimensions.cy - 1;

                                searchRequest->m_searchBitmap->SnapshotInit(searchRequest->m_terrainTable,
                                    snapshotDynamicCost,
                                    searchRequest->m_sourceSide,
                                    objectSpace);

                                pArea->m_bInPathSearch = TRUE;

                                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_sourceId,
                                    CGameObjectArray::THREAD_SEARCH,
                                    INFINITE);

                                for (cnt = 0; cnt < searchRequest->m_nTargetIds; cnt++) {
                                    if (searchRequest->m_targetIds[cnt] != CGameObjectArray::INVALID_INDEX) {
                                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_targetIds[cnt],
                                            CGameObjectArray::THREAD_SEARCH,
                                            INFINITE);

                                        searchRequest->m_searchBitmap->SnapshotRemoveObject(CPoint(goalPts[cnt]),
                                            goalObjectSpaces[cnt],
                                            goalBumpable[cnt]);
                                    }
                                }

                                if (!searchRequest->m_collisionSearch) {
                                    for (cnt = 0; cnt < searchRequest->m_nPartyIds; cnt++) {
                                        if (searchRequest->m_partyIds[cnt] != CGameObjectArray::INVALID_INDEX) {
                                            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_partyIds[cnt],
                                                CGameObjectArray::THREAD_SEARCH,
                                                INFINITE);

                                            if (isWalking[cnt]
                                                && searchRequest->m_partyIds[cnt] != searchRequest->m_sourceId) {
                                                searchRequest->m_searchBitmap->SnapshotRemoveObject(CPoint(goalRemoveObject[cnt + searchRequest->m_nTargetIds]),
                                                    goalObjectSpaces[cnt + searchRequest->m_nTargetIds],
                                                    goalBumpable[cnt + searchRequest->m_nTargetIds]);
                                            }
                                        }
                                    }
                                }

                                if (searchRequest->m_removeSelf) {
                                    searchRequest->m_searchBitmap->SnapshotRemoveObject(CPoint(startPt),
                                        objectSpace,
                                        bBumpable);

                                    if (searchRequest->m_collisionSearch) {
                                        searchRequest->m_searchBitmap->SnapshotAddObjectDiagonals(CPoint(startPt),
                                            objectSpace,
                                            bBumpable);
                                    }
                                }

                                targetPointPresent = FALSE;
                                for (cnt = 0; cnt < searchRequest->m_nTargetPoints; cnt++) {
                                    if (goalPts[cnt].x != -1 && goalPts[cnt].y != -1) {
                                        if (searchRequest->m_exclusiveTargetPoints && targetPointPresent) {
                                            goalPts[cnt].x = -1;
                                            goalPts[cnt].y = -1;
                                        } else {
                                            if (pArea->SnapshotAdjustTarget(CPoint(startPt), &(goalPts[cnt]), bBump, 10) == TRUE) {
                                                targetPointPresent = TRUE;
                                            } else {
                                                goalPts[cnt].x = -1;
                                                goalPts[cnt].y = -1;
                                            }
                                        }
                                    }
                                }

                                if (targetPointPresent || targetIdPresent) {
                                    if (!g_pBaldurChitin->GetObjectGame()->m_bInDestroyGame) {
                                        if (searchRequest->m_frontList == CSearchRequest::LIST_FRONT) {
                                            searchRequest->m_searchRc = g_pBaldurChitin->GetObjectGame()->m_pathSearch->FindPath(&startPt,
                                                goalPts,
                                                searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds,
                                                searchRequest->m_minNodes,
                                                searchRequest->m_maxNodes,
                                                searchRequest->m_searchBitmap,
                                                &(searchRequest->m_serviceState),
                                                bBump,
                                                &rGrid);
                                        } else {
                                            searchRequest->m_searchRc = g_pBaldurChitin->GetObjectGame()->m_pathSearch->FindPath(&startPt,
                                                goalPts,
                                                searchRequest->m_nTargetPoints + searchRequest->m_nTargetIds,
                                                searchRequest->m_minNodesBack,
                                                searchRequest->m_maxNodesBack,
                                                searchRequest->m_searchBitmap,
                                                &(searchRequest->m_serviceState),
                                                bBump,
                                                &rGrid);
                                        }

                                        if (!g_pBaldurChitin->GetObjectGame()->m_bInDestroyGame) {
                                            pArea->m_bInPathSearch = FALSE;
                                            searchLock.Lock(INFINITE);

                                            searchRequest->m_pPath = g_pBaldurChitin->GetObjectGame()->m_pathSearch->GetPath(&(searchRequest->m_nPath));
                                            if (searchRequest->m_serviceState != CSearchRequest::STATE_STALE) {
                                                searchRequest->m_serviceState = CSearchRequest::STATE_DONE;
                                            } else {
                                                delete searchRequest;
                                                searchLock.Unlock();
                                            }
                                        } else {
                                            pArea->m_bInPathSearch = FALSE;
                                        }
                                    } else {
                                        pArea->m_bInPathSearch = FALSE;
                                    }
                                } else {
                                    searchLock.Lock(INFINITE);

                                    if (searchRequest->m_serviceState != CSearchRequest::STATE_STALE) {
                                        searchRequest->m_serviceState = CSearchRequest::STATE_NO_TARGET;
                                    } else {
                                        delete searchRequest;
                                    }

                                    searchLock.Unlock();
                                    pArea->m_bInPathSearch = FALSE;
                                }
                            } else {
                                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_sourceId,
                                    CGameObjectArray::THREAD_SEARCH,
                                    INFINITE);

                                for (cnt = 0; cnt < searchRequest->m_nTargetIds; cnt++) {
                                    if (searchRequest->m_targetIds[cnt] != CGameObjectArray::INVALID_INDEX) {
                                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_targetIds[cnt],
                                            CGameObjectArray::THREAD_SEARCH,
                                            INFINITE);
                                    }
                                }

                                searchLock.Lock(INFINITE);
                                if (searchRequest->m_serviceState != CSearchRequest::STATE_STALE) {
                                    searchRequest->m_serviceState = CSearchRequest::STATE_NO_TARGET;
                                } else {
                                    delete searchRequest;
                                }
                                searchLock.Unlock();
                            }
                        } else {
                            if (rc == CGameObjectArray::SUCCESS) {
                                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(searchRequest->m_sourceId,
                                    CGameObjectArray::THREAD_SEARCH,
                                    INFINITE);
                            }

                            searchLock.Lock(INFINITE);
                            if (searchRequest->m_serviceState != CSearchRequest::STATE_STALE) {
                                searchRequest->m_serviceState = CSearchRequest::STATE_ERROR;
                            }
                            delete searchRequest;
                            searchLock.Unlock();
                        }
                    } else {
                        searchRequest->m_serviceState = CSearchRequest::STATE_ERROR;
                    }
                }
            } else {
                delete searchRequest;
            }
        }

        ReleaseSemaphore(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, 1, NULL);

        if (WaitForSingleObject(g_pBaldurChitin->GetObjectGame()->m_hSearchThread, INFINITE) != WAIT_OBJECT_0) {
            break;
        }

        searchLock.Unlock();

        if (searchShutdown) {
            break;
        }
    }

    CloseHandle(g_pBaldurChitin->GetObjectGame()->m_hSearchThread);
    g_pBaldurChitin->GetObjectGame()->m_hSearchThread = NULL;
}

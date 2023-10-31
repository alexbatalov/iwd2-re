#include "CSearchBitmap.h"

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
        case 0x81:
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

// -----------------------------------------------------------------------------

// 0x5492E0
void SearchThreadMain(void* userInfo)
{
    // TODO: Incomplete.
}

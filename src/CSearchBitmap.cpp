#include "CSearchBitmap.h"

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

// -----------------------------------------------------------------------------

// 0x5492E0
void SearchThreadMain(void* userInfo)
{
    // TODO: Incomplete.
}

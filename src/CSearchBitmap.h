#ifndef CSEARCHBITMAP_H_
#define CSEARCHBITMAP_H_

#include "mfc.h"

class CSearchBitmap {
public:
    void RemoveObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, int a4, unsigned char& a5);
    void AddDoor(CPoint* pPoints, USHORT nPoints, BOOL bOpaque);
    void RemoveDoor(CPoint* pPoints, USHORT nPoints);

    /* 00BA */ BYTE* m_pDynamicCost;
    /* 00E6 */ CSize m_GridSquareDimensions;
};

class CSearchRequest {
public:
    static const BYTE STATE_WAITING;
    static const BYTE STATE_PROCESSING;
    static const BYTE STATE_NO_TARGET;
    static const BYTE STATE_DONE;
    static const BYTE STATE_STALE;
    static const BYTE STATE_ERROR;

    static LONG MINNODES;
    static LONG MAXNODES;
    static LONG MINNODESBACK;
    static LONG MAXNODESBACK;

    /* 0000 */ BYTE m_serviceState;
    /* 0001 */ BYTE m_collisionDelay;
};

void SearchThreadMain(void* userInfo);

#endif /* CSEARCHBITMAP_H_ */

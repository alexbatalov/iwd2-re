#ifndef CSEARCHBITMAP_H_
#define CSEARCHBITMAP_H_

#include "mfc.h"

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

    void AddObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, int a4, unsigned char& a5);
    void RemoveObject(const CPoint& point, BYTE sourceSide, BYTE personalSpaceRange, int a4, unsigned char& a5);
    void AddDoor(CPoint* pPoints, USHORT nPoints, BOOL bOpaque);
    void RemoveDoor(CPoint* pPoints, USHORT nPoints);

    CGameArea* GetArea() { return m_pArea; }

    /* 00BA */ BYTE* m_pDynamicCost;
    /* 00E6 */ CSize m_GridSquareDimensions;
    /* 00EE */ CGameArea* m_pArea;
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

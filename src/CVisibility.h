#ifndef CVISIBILITY_H_
#define CVISIBILITY_H_

#include "CInfinity.h"

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

    void AddCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable);
    void RemoveCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable);

    static void BltFogOWar(LPDIRECTDRAWSURFACE pSurface, const TILE_CODE& tileCode);

    /* 000E */ short field_E;
    /* 0058 */ int field_58;
};

#endif /* CVISIBILITY_H_ */

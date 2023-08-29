#include "CVisibility.h"

// 0x84EDCF
const BYTE CVisibilityMap::EXPLORED_RANGE_0 = 4;

// 0x84EDD0
const BYTE CVisibilityMap::EXPLORED_RANGE_1 = 8;

// 0x84EDD1
const BYTE CVisibilityMap::EXPLORED_RANGE_2 = 12;

// 0x84EDD2
const BYTE CVisibilityMap::EXPLORED_RANGE_3 = 14;

// 0x84EDD3
const BYTE CVisibilityMap::EXPLORED_RANGE_4 = 16;

// 0x84EDD4
const BYTE CVisibilityMap::EXPLORED_RANGE_5 = 20;

// 0x84EDD5
const BYTE CVisibilityMap::EXPLORED_RANGE_6 = 24;

// 0x84EDD6
const BYTE CVisibilityMap::SQUARE_SIZEX = 32;

// 0x84EDD7
const BYTE CVisibilityMap::SQUARE_SIZEY = 32;

// 0x84EDDB
const BYTE CVisibilityMap::EXPLORED = 0;

// 0x84EDDC
const TILE_CODE CVisibilityMap::EXPLORED_FULL = { 0, 0, 0, 0 };

// 0x84EDE0
const BYTE CVisibilityMap::UNEXPLORED_N = 9;

// 0x84EDE1
const BYTE CVisibilityMap::UNEXPLORED_NE = 13;

// 0x84EDE2
const BYTE CVisibilityMap::UNEXPLORED_E = 12;

// 0x84EDE3
const BYTE CVisibilityMap::UNEXPLORED_SE = 14;

// 0x84EDE4
const BYTE CVisibilityMap::UNEXPLORED_S = 6;

// 0x84EDE5
const BYTE CVisibilityMap::UNEXPLORED_SW = 7;

// 0x84EDE6
const BYTE CVisibilityMap::UNEXPLORED_W = 3;

// 0x84EDE7
const BYTE CVisibilityMap::UNEXPLORED_NW = 11;

// 0x84EDE8
const TILE_CODE CVisibilityMap::UNEXPLORED_FULL = { 0xF, 0xF, 0xF, 0xF };

// 0x84EDEC
const BYTE CVisibilityMap::FOGOWAR_EXPLORED_MASK = 0xF;

// 0x84EDED
const BYTE CVisibilityMap::FOGOWAR_EXPLORED_SHIFT = 0;

// 0x84EDEE
const BYTE CVisibilityMap::FOGOWAR_MASK = 0xF0;

// 0x84EDEF
const BYTE CVisibilityMap::FOGOWAR_SHIFT = 4;

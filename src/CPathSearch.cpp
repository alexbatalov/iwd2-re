#include "CPathSearch.h"

// 0x84D69C
const SHORT CPathSearch::GRID_ACTUALX = 320;

// 0x84D69E
const SHORT CPathSearch::GRID_ACTUALY = 320;

// 0x84D6A0
const BYTE CPathSearch::GRID_SQUARE_SIZEX = 16;

// 0x84D6A1
const BYTE CPathSearch::GRID_SQUARE_SIZEY = 12;

// 0x84D6A2
const BYTE CPathSearch::COST_MINIMUM = 5;

// 0x84D6A3
const BYTE CPathSearch::COST_IMPASSABLE = 255;

// 0x84D6A4
const BYTE CPathSearch::COST_SCALE_ESTIMATE = 1;

// NOTE: Inlined.
void CPathSearch::PositionToPoint(LONG position, POINT* point)
{
    point->x = position % GRID_ACTUALX;
    point->y = GRID_ACTUALY - position / GRID_ACTUALX - 1;
}

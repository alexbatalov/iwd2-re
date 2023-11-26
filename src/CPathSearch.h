#ifndef CPATHSEARCH_H_
#define CPATHSEARCH_H_

#include "mfc.h"

class CPathSearch {
public:
    static const BYTE GRID_SQUARE_SIZEX;
    static const BYTE GRID_SQUARE_SIZEY;
    static const SHORT GRID_ACTUALX;
    static const SHORT GRID_ACTUALY;
    static const BYTE COST_IMPASSABLE;
    static const BYTE COST_MINIMUM;
    static const BYTE COST_SCALE_ESTIMATE;

    static void PositionToPoint(LONG position, POINT* point);
};

#endif /* CPATHSEARCH_H_ */

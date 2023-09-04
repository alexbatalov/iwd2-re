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
};

#endif /* CPATHSEARCH_H_ */

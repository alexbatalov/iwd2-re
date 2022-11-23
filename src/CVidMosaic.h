#ifndef CVIDMOSAIC_H_
#define CVIDMOSAIC_H_

#include "CResMosaic.h"
#include "CVidImage.h"

class CVidMosaic : public CVidImage, public CResHelper<CResMosaic, 1004> {
public:
    CVidMosaic();
    ~CVidMosaic();

    /* 00B0 */ int field_B0;
};

#endif /* CVIDMOSAIC_H_ */

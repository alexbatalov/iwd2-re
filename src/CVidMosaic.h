#ifndef CVIDMOSAIC_H_
#define CVIDMOSAIC_H_

#include "CResMosaic.h"
#include "CVidImage.h"

class CVidMosaic : public CVidImage, public CResHelper<CResMosaic, 1004> {
public:
    CVidMosaic();
    ~CVidMosaic();
    void GetSize(CSize& frameSize, BOOL a3);
    int GetTileNumber(int x, int y);

    /* 00B0 */ BOOL m_bDoubleSize;
};

#endif /* CVIDMOSAIC_H_ */

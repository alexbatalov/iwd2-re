#ifndef CRESMOSAIC_H_
#define CRESMOSAIC_H_

#include "CRes.h"

class CResMosaic : public CRes {
public:
    CResMosaic();
    ~CResMosaic();

    int field_50;
    int field_54;
    int field_58;
    int field_5C;
    int field_60;
};

#endif /* CRESMOSAIC_H_ */

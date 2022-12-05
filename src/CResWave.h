#ifndef CRESWAVE_H_
#define CRESWAVE_H_

#include "CRes.h"

class CResWave : public CRes {
public:
    CResWave();
    ~CResWave();

    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ int field_58;
    /* 005C */ int field_5C;
    /* 0060 */ int field_60;
    /* 0064 */ int field_64;
};

#endif /* CRESWAVE_H_ */

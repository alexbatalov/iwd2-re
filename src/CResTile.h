#ifndef CRESTILE_H_
#define CRESTILE_H_

#include "CRes.h"
#include "CResRef.h"

class CResTile : public CRes {
public:
    CResTile();
    ~CResTile();

    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ CResRef field_58;
    /* 0060 */ int field_60;
};

#endif /* CRESTILE_H_ */

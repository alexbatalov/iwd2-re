#ifndef CRESPLT_H_
#define CRESPLT_H_

#include "CRes.h"

class CResPLT : public CRes {
public:
    CResPLT();
    ~CResPLT();

    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ int field_58;
};

#endif /* CRESPLT_H_ */

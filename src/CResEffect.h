#ifndef CRESEFFECT_H_
#define CRESEFFECT_H_

#include "CRes.h"

class CResEffect : public CRes {
public:
    CResEffect();
    ~CResEffect();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESEFFECT_H_ */

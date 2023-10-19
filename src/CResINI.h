#ifndef CRESINI_H_
#define CRESINI_H_

#include "CRes.h"

class CResINI : public CRes {
public:
    CResINI();
    ~CResINI();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESINI_H_ */

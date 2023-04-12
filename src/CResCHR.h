#ifndef CRESCHR_H_
#define CRESCHR_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResCHR : public CRes {
public:
    CResCHR();
    ~CResCHR();
    void* Demand();
    int Release();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESCHR_H_ */

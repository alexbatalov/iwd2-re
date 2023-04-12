#ifndef CRESCRE_H_
#define CRESCRE_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResCRE : public CRes {
public:
    CResCRE();
    ~CResCRE();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESCRE_H_ */

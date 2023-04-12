#ifndef CRESSTORE_H_
#define CRESSTORE_H_

#include "CRes.h"

class CResStore : public CRes {
public:
    CResStore();
    ~CResStore();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESSTORE_H_ */

#ifndef CRESAREA_H_
#define CRESAREA_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResArea : public CRes {
public:
    CResArea();
    ~CResArea();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESAREA_H_ */

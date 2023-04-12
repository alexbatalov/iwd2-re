#ifndef CRESWORLDMAP_H_
#define CRESWORLDMAP_H_

#include "CRes.h"

class CResWorldMap : public CRes {
public:
    CResWorldMap();
    ~CResWorldMap();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESWORLDMAP_H_ */

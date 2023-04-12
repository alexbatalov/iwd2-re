#ifndef CRESGAME_H_
#define CRESGAME_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResGame : public CRes {
public:
    CResGame();
    ~CResGame();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESGAME_H_ */

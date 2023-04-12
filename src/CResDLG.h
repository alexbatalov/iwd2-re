#ifndef CRESDLG_H_
#define CRESDLG_H_

#include "CRes.h"

class CResDLG : public CRes {
public:
    CResDLG();
    ~CResDLG();
    void* Demand();
    BOOL Parse(void* pData);

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESDLG_H_ */

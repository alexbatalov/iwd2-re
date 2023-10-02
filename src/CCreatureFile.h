#ifndef CCREATUREFILE_H_
#define CCREATUREFILE_H_

#include "CResCRE.h"

class CCreatureFile : public CResHelper<CResCRE, 1009> {
public:
    CCreatureFile();
    ~CCreatureFile();
    BYTE* GetData();
    DWORD GetDataSize();
    void ReleaseData();
};

#endif /* CCREATUREFILE_H_ */

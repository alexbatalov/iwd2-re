#ifndef CCREATUREFILE_H_
#define CCREATUREFILE_H_

#include "CResCRE.h"

class CCreatureFile : public CResHelper<CResCRE, 1009> {
public:
    CCreatureFile();
    ~CCreatureFile();
    void* GetData();
    DWORD GetDataSize();
};

#endif /* CCREATUREFILE_H_ */

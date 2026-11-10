#ifndef CRESBIO_H_
#define CRESBIO_H_

#include "CRes.h"

// NOTE: Class name is a guess. Character biography text (resource type 1022,
// the `.RES` file next to an exported `.CHR`). Unlike `CResText` the data is
// used as is, without parsing.
class CResBIO : public CRes {
public:
    CResBIO();
    ~CResBIO();
    void* Demand();
    int Release();

    /* 0050 */ BOOL m_bParsed;
};

#endif /* CRESBIO_H_ */

#ifndef CRES_H_
#define CRES_H_

#include <afx.h>
#include <afxmt.h>

#include "CChitin.h"
#include "CResRef.h"

class CRes : public CObject {
public:
    CRes();
    ~CRes();

    int CancelRequest();

    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ CCriticalSection field_20;
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ int field_48;
    /* 004C */ int field_4C;
};

template <class T, int nType>
class CResHelper {
public:
    /* 0000 */ int field_0;
    /* 0004 */ T* pRes;
    /* 0008 */ CResRef cResRef;

    CResHelper()
    {
        pRes = NULL;
        cResRef = "";
        field_0 = 0;
    }

    ~CResHelper()
    {
        if (pRes != NULL && cResRef != "") {
            if (field_0) {
                (static_cast<CRes*>(pRes))->CancelRequest();
                field_0 = 0;
            }
            g_pChitin->cDimm.ReleaseResObject(pRes);
        }
        pRes = NULL;
    }
};

#endif /* CRES_H_ */

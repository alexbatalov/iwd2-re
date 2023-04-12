#ifndef CRESTEXT_H_
#define CRESTEXT_H_

#include "CRes.h"

class CResText : public CRes {
public:
    CResText();
    ~CResText();
    CString GetText() { return m_string; }
    void* Demand();
    BOOL Parse(void* pData);
    CString ParseText(void* pData);
    int Release();

    /* 0050 */ BOOL m_bParsed;
    /* 0054 */ int field_54;
    /* 0058 */ CString m_string;
};

#endif /* CRESTEXT_H_ */

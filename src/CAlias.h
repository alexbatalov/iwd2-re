#ifndef CALIAS_H_
#define CALIAS_H_

#include <afx.h>

class CAlias : public CObject {
public:
    CAlias(CString& a2);
    ~CAlias();

    BOOL ParseRawData(CString& a2);

    /* 0004 */ BOOL field_4;
    /* 0008 */ CString field_8;
    /* 000C */ CStringList field_C;
};

#endif /* CALIAS_H_ */

#ifndef CSWITCHCDSTATUS_H_
#define CSWITCHCDSTATUS_H_

#include <afx.h>
#include <afxmt.h>

#include "CVidFont.h"
#include "CVidMosaic.h"

class CSwitchCDStatus {
public:
    CSwitchCDStatus();
    ~CSwitchCDStatus();

    void Init();
    void Update(BOOLEAN a1, BOOLEAN a2, BYTE a3, const CString& a4, BOOLEAN a5, BOOLEAN a6, BOOLEAN a7);

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ CVidMosaic field_8[4];
    /* 02D8 */ CVidMosaic field_2D8;
    /* 038C */ CVidMosaic field_38C;
    /* 0440 */ CVidMosaic field_440;
    /* 04F4 */ CVidFont field_4F4;
    /* 09F4 */ CVidFont field_9F4;
    /* 0EF4 */ BOOL m_bActivateEngine;
    /* 0EF8 */ CCriticalSection field_EF8;
};

#endif /* CSWITCHCDSTATUS_H_ */

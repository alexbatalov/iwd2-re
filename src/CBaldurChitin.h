#ifndef CBALDURCHITIN_H_
#define CBALDURCHITIN_H_

#include <afxwin.h>

#include "CBaldurMessage.h"
#include "CCacheStatus.h"
#include "CChitin.h"
#include "CMessageHandler.h"
#include "CSwitchCDStatus.h"
#include "CTlkTable.h"
#include "CVidFont.h"

class CBaldurChitin : public CChitin {
public:
    CBaldurChitin();
    ~CBaldurChitin();
    void Init(HINSTANCE hInstance);

    /* 1CAC */ CTlkTable m_cTlkTable;
    /* 1D52 */ CCacheStatus m_cCachingStatus;
    /* 3970 */ CSwitchCDStatus m_cSwitchingCDStatus; // #guess
    /* 4888 */ CBaldurMessage m_cBaldurMessage;
    /* 4980 */ CMessageHandler m_cMessageHandler;
    /* 49AC */ CString field_49AC;
    /* 4A34 */ CVidFont field_4A34;
};

extern CChitin* g_pChitin;
extern CBaldurChitin* g_pBaldurChitin;

#endif /* CBALDURCHITIN_H_ */

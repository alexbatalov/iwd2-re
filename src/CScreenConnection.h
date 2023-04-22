#ifndef CSCREENCONNECTION_H_
#define CSCREENCONNECTION_H_

#include "CBaldurEngine.h"

class CScreenConnection : public CBaldurEngine {
public:
    CScreenConnection();
    ~CScreenConnection();

    void StartConnection(BOOLEAN bDirectPlayLobby);

    /* 0466 */ INT m_nProtocol;
    /* 048A */ DWORD m_dwLastSessionRefresh;
    /* 048E */ INT m_nEnumServiceProvidersCountDown;
    /* 0492 */ BOOL m_bStartedCountDown;
    /* 0497 */ BOOLEAN m_bEliminateInitialize;
    /* 04B2 */ BOOL m_bAllowInput;
    /* 049D */ BOOLEAN m_bDirectPlayLobby;
};

#endif /* CSCREENCONNECTION_H_ */

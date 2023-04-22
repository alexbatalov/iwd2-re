#include "CScreenConnection.h"

#include "CBaldurChitin.h"

// 0x5F9BB0
CScreenConnection::CScreenConnection()
{
    // TODO: Incomplete.
}

// 0x5FA910
CScreenConnection::~CScreenConnection()
{
    // TODO: Incomplete.
}

// 0x600770
void CScreenConnection::StartConnection(BOOLEAN bDirectPlayLobby)
{
    m_bAllowInput = TRUE;
    m_nProtocol = 0;
    if (bDirectPlayLobby) {
        m_bDirectPlayLobby = bDirectPlayLobby;
    } else {
        m_nEnumServiceProvidersCountDown = 2;
        m_bStartedCountDown = 0;
        m_bEliminateInitialize = TRUE;
        m_dwLastSessionRefresh = GetTickCount();
    }

    if (g_pBaldurChitin->m_bIsAutoStarting) {
        m_bAllowInput = FALSE;
    }
}

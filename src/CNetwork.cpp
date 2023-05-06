#include "CNetwork.h"

#include "CChitin.h"

// 0x85E63C
const INT CNetwork::MAX_SERVICE_PROVIDERS = CNETWORK_MAX_SERVICE_PROVIDERS;

// 0x85E64C
const INT CNetwork::SERV_PROV_TCP_IP = 8;

// 0x85E650
const INT CNetwork::SERV_PROV_MODEM = 4;

// 0x85E654
const INT CNetwork::SERV_PROV_SERIAL = 2;

// 0x85E658
const INT CNetwork::SERV_PROV_IPX = 1;

// 0x85E65C
const INT CNetwork::SERV_PROV_NULL = 0;

// 0x85E6A8
const INT CNetwork::ERROR_NONE = 0;

// 0x85E6AC
const INT CNetwork::ERROR_PLAYEREXISTS = 1;

// 0x85E6B0
const INT CNetwork::ERROR_CANNOTCREATEPLAYER = 2;

// 0x85E6B4
const INT CNetwork::ERROR_CANNOTCONNECT = 3;

// 0x85E6B8
const INT CNetwork::ERROR_INVALIDPASSWORD = 4;

// 0x7A3FD0
CNetwork::CNetwork()
{
    field_9D = 0;
    field_9E = 0;
    field_116 = 0;
    field_796 = 0;
    InitializeCriticalSection(&field_F52);
    InitializeCriticalSection(&field_F6A);
    m_lpDirectPlay = NULL;
    m_lpDirectPlayLobby = NULL;
    m_nApplicationGuid = GUID_NULL;
    m_bApplicationGuidDefined = FALSE;
    field_19 = 0;
    m_bServiceProviderEnumerated = FALSE;
    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_nTotalServiceProviders = 0;
    m_serviceProviderGuids[m_nTotalServiceProviders++] = GUID_NULL;
    field_9C = 0;
    m_pServiceProviderConnections[0] = NULL;
    m_pServiceProviderConnections[1] = NULL;
    m_pServiceProviderConnections[2] = NULL;
    m_pServiceProviderConnections[3] = NULL;
    m_pServiceProviderConnections[4] = NULL;
    m_bModemEnumerated = 0;
    m_bModemAddressSelected = FALSE;
    m_nModemAddress = -1;
    m_nTotalModemAddresses = 0;
    field_FA = "";
    field_FE = "";
    m_nSerialBaudRate = 57600;
    m_nSerialPort = 1;
    field_112 = 4;
    field_10E = 0;
    field_10A = 0;
    field_120 = 0;

    for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
        m_psSessionName[nSession] = "";
        m_pSessionGuid[nSession] = GUID_NULL;
        m_pbSessionPasswordRequired[nSession] = FALSE;
    }

    m_bSessionSelected = FALSE;
    m_nSession = -1;
    m_nTotalSessions = 0;
    m_guidSession = GUID_NULL;
    field_67A = 0;
    field_67C = "";
    field_680 = 0;
    field_682 = "";
    m_bAllowNewConnections = 1;
    field_6D8 = 0;
    field_6DC = 0;
    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    m_bSessionOptionsDefined = 0;
    m_nMaxPlayers = 6;
    m_dwSessionFlags = 0;
    field_6F8 = 0;
    field_6F9 = 0;
    field_6FA = 0;
    field_6FE = "";
    field_78E = -1;
    field_78A = -1;
    field_732 = 0;

    for (INT nPlayerNumber = 0; nPlayerNumber < 6; nPlayerNumber++) {
        m_pPlayerID[nPlayerNumber] = 0;
        field_772[nPlayerNumber] = 0;
        m_psPlayerName[nPlayerNumber] = "";
        m_pbPlayerEnumerateFlag[nPlayerNumber] = FALSE;
        m_pbPlayerVisible[nPlayerNumber] = FALSE;
        m_pSlidingWindow[nPlayerNumber].Initialize(nPlayerNumber);
    }

    m_SystemWindow.Initialize(-1);

    for (unsigned int m = 0; m <= 255; m++) {
        unsigned int v1 = m;
        for (unsigned int bit = 8; bit > 0; bit--) {
            if ((v1 & 1) != 0) {
                v1 >>= 1;
                v1 ^= 0xEDB88320;
            } else {
                v1 >>= 1;
            }
        }
        m_dwCRC32[m] = v1;
    }

    for (int j = 0; j < 6; j++) {
        field_71A[j] = 0;
    }

    field_118 = 0;
}

// 0x7A4440
CNetwork::~CNetwork()
{
    if (m_bConnectionEstablished) {
        OnCloseSession();
    }

    m_bServiceProviderEnumerated = FALSE;

    for (INT nServiceProvider = 0; nServiceProvider < CNETWORK_MAX_SERVICE_PROVIDERS; nServiceProvider++) {
        if (m_pServiceProviderConnections[nServiceProvider] != NULL) {
            operator delete(m_pServiceProviderConnections[nServiceProvider]);
        }
    }

    if (m_nServiceProvider != SERV_PROV_NULL) {
        EnterCriticalSection(&field_F6A);

        // TODO: Incomplete.

        LeaveCriticalSection(&field_F6A);
    }

    DeleteCriticalSection(&field_F6A);
    DeleteCriticalSection(&field_F52);
}

// 0x7A4660
void CNetwork::AddModemAddressToList(LPCSTR lpAddress)
{
    m_psModemAddress[m_nTotalModemAddresses] = CString(lpAddress, strlen(lpAddress));
    m_nTotalModemAddresses++;
}

// 0x7A46E0
void CNetwork::AddServiceProviderToList(const CString& sServiceProviderName, const GUID& sServiceProviderGuid, LPVOID lpConnection, size_t size)
{
    if (m_pServiceProviderConnections[m_nTotalServiceProviders] != NULL) {
        operator delete(m_pServiceProviderConnections[m_nTotalServiceProviders]);
    }

    m_pServiceProviderConnections[m_nTotalServiceProviders] = operator new(size);
    if (m_pServiceProviderConnections[m_nTotalServiceProviders] != NULL) {
        memcpy(m_pServiceProviderConnections[m_nTotalServiceProviders], lpConnection, size);

        m_serviceProviderGuids[m_nTotalServiceProviders] = sServiceProviderGuid;
        m_serviceProviderNames[m_nTotalServiceProviders] = sServiceProviderName;

        m_nTotalServiceProviders++;
    }
}

// 0x7A5340
BOOLEAN CNetwork::EnumerateServiceProviders()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A5480
INT CNetwork::FindModemAddress(const CString& sAddress)
{
    if (!m_bModemEnumerated) {
        return -1;
    }

    for (INT nAddressNumber = 0; nAddressNumber < m_nTotalModemAddresses; nAddressNumber++) {
        if (m_psModemAddress[nAddressNumber].Compare(sAddress) == 0) {
            return nAddressNumber;
        }
    }

    return -1;
}

// 0x7A54E0
BOOLEAN CNetwork::GetModemAddress(INT nAddressNumber, CString& sAddress)
{
    if (!m_bModemEnumerated) {
        return FALSE;
    }

    if (!(nAddressNumber >= 0 && nAddressNumber < m_nTotalModemAddresses)) {
        return FALSE;
    }

    sAddress = m_psModemAddress[nAddressNumber];

    return TRUE;
}

// 0x7A5520
BOOLEAN CNetwork::GetServiceProviderType(INT nServiceProviderNumber, INT& nServiceProviderType)
{
    if (!(nServiceProviderNumber >= 0 && nServiceProviderNumber < m_nTotalServiceProviders)) {
        nServiceProviderType = SERV_PROV_NULL;
        return FALSE;
    }

    // TODO: Incomplete.

    nServiceProviderType = SERV_PROV_NULL;
    return TRUE;
}

// 0x7A5600
BOOLEAN CNetwork::InitializeConnectionToServiceProvider(BOOLEAN bHostingGame)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A5720
void CNetwork::RemoveInitializeConnection()
{
    // TODO: Incomplete.
}

// 0x7A5760
BOOLEAN CNetwork::SelectModemAddress(INT nAddressNumber)
{
    if (!m_bModemEnumerated) {
        return FALSE;
    }

    if (!(nAddressNumber >= 0 && nAddressNumber < m_nTotalModemAddresses)) {
        return FALSE;
    }

    m_nModemAddress = nAddressNumber;
    m_bModemAddressSelected = TRUE;

    return TRUE;
}

// 0x7A57A0
BOOLEAN CNetwork::SelectServiceProvider(INT nServiceProviderNumber)
{
    if (!m_bServiceProviderEnumerated) {
        return FALSE;
    }

    if (!(nServiceProviderNumber >= 0 && nServiceProviderNumber < m_nTotalServiceProviders)) {
        return FALSE;
    }

    m_nServiceProvider = nServiceProviderNumber;
    m_bServiceProviderSelected = TRUE;

    return m_bServiceProviderEnumerated;
}

// 0x7A57D0
void CNetwork::SetApplicationOptions(BOOLEAN bKeepAlive, BOOLEAN bMigrateHost)
{
    m_bSessionOptionsDefined = TRUE;
    m_dwSessionFlags = 0;

    if (bKeepAlive == TRUE) {
        m_dwSessionFlags |= 0x40;
    }
}

// 0x7A5800
void CNetwork::SetJoinEnabled(BOOLEAN bJoinEnabled)
{
    if (m_bAllowNewConnections != bJoinEnabled) {
        m_bAllowNewConnections = bJoinEnabled;

        g_pChitin->cGameSpy.sub_4D1EC0(TRUE);
    }
}

// 0x7A5830
BOOLEAN CNetwork::SetSerialBaudRate(UINT nBaudRate)
{
    switch (nBaudRate) {
    case 14400:
    case 19200:
    case 38400:
    case 56000:
    case 57600:
    case 115200:
    case 128000:
    case 256000:
        m_nSerialBaudRate = nBaudRate;
        return TRUE;
    }

    return FALSE;
}

// 0x7A5890
BOOLEAN CNetwork::SetSerialPort(UINT nPort)
{
    if (nPort != 0 || nPort > 4) {
        return FALSE;
    }

    m_nSerialPort = nPort;

    return TRUE;
}

// 0x7A58B0
void CNetwork::UnselectModemAddress()
{
    m_bModemAddressSelected = FALSE;
    m_nModemAddress = -1;
}

// 0x7A5A20
void CNetwork::CloseSession(BOOLEAN bAIResponsible)
{
    if (bAIResponsible == TRUE) {
        g_pChitin->OnMultiplayerSessionToClose();
        SleepEx(1000, FALSE);
        if (m_bConnectionEstablished == TRUE) {
            OnCloseSession();
        }
    } else {
        OnCloseSession();
    }
}

// 0x7A5A60
void CNetwork::OnCloseSession()
{
    // TODO: Incomplete.
}

// 0x7A5D00
BOOLEAN CNetwork::CheckSessionStatus(BOOLEAN bInThreadLoop)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A5F00
void CNetwork::EnumerateSessions(BOOLEAN a1, BOOLEAN a2)
{
    // TODO: Incomplete.
}

// 0x7A61D0
BOOLEAN CNetwork::sub_7A61D0()
{
    return TRUE;
}

// 0x7A61E0
BOOLEAN CNetwork::GetPasswordRequiredForSelectedSession()
{
    if (!(m_nSession >= 0 && m_nSession < m_nTotalSessions)) {
        return FALSE;
    }

    return m_pbSessionPasswordRequired[m_nSession];
}

// 0x7A6200
BOOLEAN CNetwork::GetSessionName(INT nSession, CString& sSessionName)
{
    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    sSessionName = m_psSessionName[nSession];

    return TRUE;
}

// 0x7A6230
BOOLEAN CNetwork::GetSessionGUID(INT nSession, GUID& sessionGuid)
{
    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    sessionGuid = m_pSessionGuid[nSession];

    return TRUE;
}

// 0x7A6270
BOOLEAN CNetwork::HostNewSession()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A64B0
BOOLEAN CNetwork::JoinSelectedSession(INT& nErrorCode)
{
    if (!m_bSessionSelected) {
        nErrorCode = ERROR_CANNOTCONNECT;
        return FALSE;
    }

    // TODO: Incomplete.

    return FALSE;
}

// 0x7A6680
BOOLEAN CNetwork::SelectSession(INT nSession)
{
    if (!field_120) {
        return FALSE;
    }

    if (!(nSession >= 0 && nSession < m_nTotalSessions)) {
        return FALSE;
    }

    m_nSession = nSession;
    m_guidSession = m_pSessionGuid[nSession];
    m_bSessionSelected = TRUE;

    return TRUE;
}

// 0x7A66E0
BOOLEAN CNetwork::SetInSessionOptions()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A6800
void CNetwork::SetMaxPlayers(INT nMaxPlayers)
{
    if (nMaxPlayers <= 6) {
        m_nMaxPlayers = nMaxPlayers;
    }
}

// 0x7A6820
void CNetwork::UnselectSession()
{
    m_bSessionSelected = FALSE;
    m_nSession = -1;
}

// 0x7A6960
BOOLEAN CNetwork::CreatePlayer(INT& nErrorCode)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A6F80
void CNetwork::EnumeratePlayers(BOOLEAN bProtectList)
{
    // TODO: Incomplete.
}

// 0x7A7160
BOOLEAN CNetwork::MakePlayersVisible()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A7220
PLAYER_ID CNetwork::GetPlayerID(INT nPlayerNumber)
{
    if (m_pbPlayerVisible[nPlayerNumber] == TRUE) {
        return m_pPlayerID[nPlayerNumber];
    } else {
        return 0;
    }
}

// 0x7A7240
void CNetwork::GetPlayerName(INT nPlayerNumber, CString& sPlayerName)
{
    if (m_pbPlayerVisible[nPlayerNumber] == TRUE) {
        sPlayerName = m_psPlayerName[nPlayerNumber];
    } else {
        sPlayerName = "";
    }
}

// 0x7A7280
PLAYER_ID CNetwork::GetRawPlayerID(INT nPlayerNumber)
{
    return m_pPlayerID[nPlayerNumber];
}

// 0x7A7290
void CNetwork::GetRawPlayerName(INT nPlayerNumber, CString& sPlayerName)
{
    sPlayerName = m_psPlayerName[nPlayerNumber];
}

// 0x7A72B0
PLAYER_ID CNetwork::FindPlayerIDByName(const CString& sPlayerName, BOOLEAN bInvisible)
{
    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_psPlayerName[nPlayerNumber].Compare(sPlayerName) == 0) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return m_pPlayerID[nPlayerNumber];
            } else {
                return 0;
            }
        }
    }

    return 0;
}

// 0x7A7320
INT CNetwork::FindPlayerLocationByID(PLAYER_ID playerID, BOOLEAN bInvisible)
{
    if (playerID == 0) {
        return -1;
    }

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_pPlayerID[nPlayerNumber] == playerID) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return nPlayerNumber;
            } else {
                return -1;
            }
        }
    }

    return -1;
}

// 0x7A7360
INT CNetwork::FindPlayerLocationByName(const CString& sPlayerName, BOOLEAN bInvisible)
{
    if (sPlayerName.Compare("") == 0) {
        return -1;
    }

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (m_psPlayerName[nPlayerNumber].Compare(sPlayerName) == 0) {
            if (bInvisible || m_pbPlayerVisible[nPlayerNumber]) {
                return nPlayerNumber;
            } else {
                return -1;
            }
        }
    }

    return -1;
}

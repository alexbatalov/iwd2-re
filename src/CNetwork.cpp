#include "CNetwork.h"

#include "CChitin.h"
#include "CUtil.h"

// 0x8FB9CC
const CString CNetwork::MG("MG");

// 0x8FB9D0
const CString CNetwork::JM("JM");

// 0x8FB9C8
const CString CNetwork::JB("JB");

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
#if DPLAY_COMPAT
    InitDirectPlay();
#endif

    field_9D = 0;
    field_9E = 0;
    m_bDirectPlayAddressCreated = FALSE;
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
    m_bConnectionInitialized = FALSE;
    m_pServiceProviderConnections[0] = NULL;
    m_pServiceProviderConnections[1] = NULL;
    m_pServiceProviderConnections[2] = NULL;
    m_pServiceProviderConnections[3] = NULL;
    m_pServiceProviderConnections[4] = NULL;
    m_bModemEnumerated = 0;
    m_bModemAddressSelected = FALSE;
    m_nModemAddress = -1;
    m_nTotalModemAddresses = 0;
    m_sIPAddress = "";
    m_sPhoneNumber = "";
    m_nSerialBaudRate = 57600;
    m_nSerialPort = 1;
    m_nSerialFlowControl = DPCPA_RTSDTRFLOW;
    m_nSerialParity = 0;
    m_nSerialStopBits = 0;
    m_bSessionEnumerated = FALSE;

    for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
        m_psSessionName[nSession] = "";
        m_pSessionGuid[nSession] = GUID_NULL;
        m_pbSessionPasswordRequired[nSession] = FALSE;
    }

    m_bSessionSelected = FALSE;
    m_nSession = -1;
    m_nTotalSessions = 0;
    m_guidSession = GUID_NULL;
    m_bSessionNameToMake = FALSE;
    m_sSessionNameToMake = "";
    m_bSessionPasswordEnabled = FALSE;
    m_sSessionPassword = "";
    m_bAllowNewConnections = TRUE;
    m_pLastSessionBuffer = NULL;
    m_dwLastSessionBufferSize = 0;
    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    m_bSessionOptionsDefined = 0;
    m_nMaxPlayers = CNETWORK_MAX_PLAYERS;
    m_dwSessionFlags = 0;
    m_bPlayerNameToMake = FALSE;
    m_bPlayerCreated = FALSE;
    m_idLocalPlayer = 0;
    m_sLocalPlayerName = "";
    m_nHostPlayer = -1;
    m_nLocalPlayer = -1;
    m_nTotalPlayers = 0;

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
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

    for (INT nSlot = 0; nSlot < CNETWORK_MAX_PLAYERS; nSlot++) {
        field_71A[nSlot] = FALSE;
    }

    m_pDirectPlayAddress = NULL;
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

        if (m_lpDirectPlay != NULL) {
            m_lpDirectPlay->Release();
            m_lpDirectPlay = NULL;
        }

        if (m_lpDirectPlayLobby != NULL) {
            m_lpDirectPlayLobby->Release();
            m_lpDirectPlayLobby = NULL;
        }

        LeaveCriticalSection(&field_F6A);
    }

    DeleteCriticalSection(&field_F6A);
    DeleteCriticalSection(&field_F52);

#if DPLAY_COMPAT
    FreeDirectPlay();
#endif
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

// 0x7A4780
BOOLEAN CNetwork::CreateDirectPlayAddress(BOOLEAN bHostingGame)
{
    DPCOMPOUNDADDRESSELEMENT addressElements[3];
    DWORD dwElementCount = 0;
    char szIpAddress[200];
    WORD nPort;
    char szModemAddress[200];
    char szPhoneNumber[200];
    DPCOMPORTADDRESS com;
    HRESULT hr;

    if (m_bDirectPlayAddressCreated) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }
    }

    if (!m_bServiceProviderSelected
        || m_nServiceProvider < 0
        || m_nServiceProvider >= m_nTotalServiceProviders) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        return FALSE;
    }

    GUID serviceProviderGuid = m_serviceProviderGuids[m_nServiceProvider];

    if (IsEqualGUID(serviceProviderGuid, DPSPGUID_MODEM)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_MODEM;
        dwElementCount++;

        lstrcpyA(szModemAddress, "");
        if (m_bModemAddressSelected == TRUE
            && m_nModemAddress >= 1
            && m_nModemAddress < m_nTotalModemAddresses) {
            lstrcpynA(szModemAddress, m_psModemAddress[m_nModemAddress], 200);

            addressElements[dwElementCount].guidDataType = DPAID_Modem;
            addressElements[dwElementCount].dwDataSize = lstrlenA(szModemAddress) + 1;
            addressElements[dwElementCount].lpData = szModemAddress;
            dwElementCount++;
        }

        if (m_sPhoneNumber.GetLength() > 0 && !bHostingGame) {
            lstrcpynA(szPhoneNumber, m_sPhoneNumber, 200);

            addressElements[dwElementCount].guidDataType = DPAID_Phone;
            addressElements[dwElementCount].dwDataSize = lstrlenA(szPhoneNumber) + 1;
            addressElements[dwElementCount].lpData = szPhoneNumber;
            dwElementCount++;
        }
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_TCPIP)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_TCPIP;
        dwElementCount++;

        lstrcpyA(szIpAddress, "");
        lstrcpynA(szIpAddress, m_sIPAddress, 200);

        if (m_sIPAddress.IsEmpty() && bHostingGame == TRUE) {
            m_sIPAddress = "127.0.0.1";
            lstrcpynA(szIpAddress, m_sIPAddress, 200);
            m_sIPAddress = "";
        }

        addressElements[dwElementCount].guidDataType = DPAID_INet;
        addressElements[dwElementCount].dwDataSize = lstrlenA(szIpAddress) + 1;
        addressElements[dwElementCount].lpData = szIpAddress;
        dwElementCount++;

        nPort = g_pChitin->GetMultiplayerDirectPlayPort();
        if (nPort != 0) {
            addressElements[dwElementCount].guidDataType = DPAID_INetPort;
            addressElements[dwElementCount].dwDataSize = sizeof(WORD);
            addressElements[dwElementCount].lpData = &nPort;
            dwElementCount++;
        }
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_IPX)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_IPX;
        dwElementCount++;
    } else if (IsEqualGUID(serviceProviderGuid, DPSPGUID_SERIAL)) {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = (LPVOID)&DPSPGUID_SERIAL;
        dwElementCount++;

        com.dwComPort = m_nSerialPort;
        com.dwBaudRate = m_nSerialBaudRate;
        com.dwStopBits = m_nSerialStopBits;
        com.dwParity = m_nSerialParity;
        com.dwFlowControl = m_nSerialFlowControl;

        addressElements[dwElementCount].guidDataType = DPAID_ComPort;
        addressElements[dwElementCount].dwDataSize = sizeof(DPCOMPORTADDRESS);
        addressElements[dwElementCount].lpData = &com;
        dwElementCount++;
    } else {
        addressElements[dwElementCount].guidDataType = DPAID_ServiceProvider;
        addressElements[dwElementCount].dwDataSize = sizeof(GUID);
        addressElements[dwElementCount].lpData = &serviceProviderGuid;
        dwElementCount++;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlayLobby == NULL) {
        if (SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x405, (WPARAM)&m_lpDirectPlayLobby, 0) == 0) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                m_bDirectPlayAddressCreated = FALSE;
            }

            LeaveCriticalSection(&field_F6A);
            return FALSE;
        }
    }

    hr = m_lpDirectPlayLobby->CreateCompoundAddress(addressElements,
        dwElementCount,
        NULL,
        &m_pDirectPlayAddressSize);
    if (hr != DPERR_BUFFERTOOSMALL) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_pDirectPlayAddress = new BYTE[m_pDirectPlayAddressSize];
    if (m_pDirectPlayAddress == NULL) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    hr = m_lpDirectPlayLobby->CreateCompoundAddress(addressElements,
        dwElementCount,
        m_pDirectPlayAddress,
        &m_pDirectPlayAddressSize);
    if (FAILED(hr)) {
        if (m_pDirectPlayAddress != NULL) {
            delete m_pDirectPlayAddress;
            m_bDirectPlayAddressCreated = FALSE;
        }

        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_bDirectPlayAddressCreated = TRUE;

    LeaveCriticalSection(&field_F6A);
    return TRUE;
}

// 0x7A4D90
BOOLEAN CNetwork::CreateDirectPlayInterface(const GUID* guid, IDirectPlay4A** lplpDirectPlay4)
{
    GUID guidCopy = *guid;
    IDirectPlay* lpDirectPlay = NULL;
    IDirectPlay4A* lpDirectPlay4 = NULL;

    if (IsEqualGUID(guidCopy, GUID_NULL)) {
        HRESULT hr = CoCreateInstance(CLSID_DirectPlay,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IDirectPlay4A,
            reinterpret_cast<LPVOID*>(&lpDirectPlay4));
        if (hr != S_OK) {
            // NOTE: Not used. Probably were a part of error reporting.
            switch (hr) {
            case REGDB_E_CLASSNOTREG:
                return FALSE;
            case REGDB_E_IIDNOTREG:
                return FALSE;
            }

            return FALSE;
        }
    } else {
        if (DirectPlayCreate(&guidCopy, &lpDirectPlay, NULL) != DP_OK) {
            return FALSE;
        }

        if (lpDirectPlay->QueryInterface(IID_IDirectPlay4A, reinterpret_cast<LPVOID*>(&lpDirectPlay4)) != DP_OK) {
            if (lpDirectPlay != NULL) {
                lpDirectPlay->Release();
            }
            return FALSE;
        }

        lpDirectPlay->Release();
    }

    *lplpDirectPlay4 = lpDirectPlay4;
    return TRUE;
}

// 0x7A4E80
BOOLEAN CNetwork::CreateDirectPlayLobbyInterface(IDirectPlayLobby3A** lplpDirectPlayLobby3)
{
    IDirectPlayLobby* lpDirectPlayLobby = NULL;
    IDirectPlayLobby3A* lpDirectPlayLobby3 = NULL;

    if (DirectPlayLobbyCreateA(NULL, &lpDirectPlayLobby, NULL, NULL, 0) != DP_OK) {
        return FALSE;
    }

    if (lpDirectPlayLobby->QueryInterface(IID_IDirectPlayLobby3A, reinterpret_cast<LPVOID*>(&lpDirectPlayLobby3)) != DP_OK) {
        if (lpDirectPlayLobby != NULL) {
            lpDirectPlayLobby->Release();
        }
        return FALSE;
    }

    lpDirectPlayLobby->Release();
    *lplpDirectPlayLobby3 = lpDirectPlayLobby3;
    return TRUE;
}

// 0x7A4F00
BOOLEAN CNetwork::HasModems()
{
    HKEY hSystem;
    HKEY hCurrentControlSet;
    HKEY hServices;
    HKEY hModem;
    HKEY hEnum;
    HKEY hClass;
    DWORD cSubKeys;

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System", 0, KEY_READ, &hSystem) != ERROR_SUCCESS) {
        return FALSE;
    }

    if (RegOpenKeyExA(hSystem, "CurrentControlSet", 0, KEY_READ, &hCurrentControlSet) != ERROR_SUCCESS) {
        RegCloseKey(hSystem);
        return FALSE;
    }

    if (RegOpenKeyExA(hSystem, "Services", 0, KEY_READ, &hServices) != ERROR_SUCCESS) {
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return FALSE;
    }

    if (g_pChitin->dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (RegOpenKeyExA(hServices, "Modem", 0, KEY_READ, &hModem) != ERROR_SUCCESS) {
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegOpenKeyExA(hModem, "Enum", 0, KEY_READ, &hEnum) != ERROR_SUCCESS) {
            RegCloseKey(hModem);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        RegCloseKey(hEnum);
        RegCloseKey(hModem);
        RegCloseKey(hServices);
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return TRUE;
    } else {
        if (RegOpenKeyExA(hServices, "Class", 0, KEY_READ, &hClass) != ERROR_SUCCESS) {
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegOpenKeyExA(hClass, "Modem", 0, KEY_READ, &hModem) != ERROR_SUCCESS) {
            RegCloseKey(hClass);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        if (RegQueryInfoKeyA(hModem, NULL, NULL, NULL, &cSubKeys, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != ERROR_SUCCESS) {
            RegCloseKey(hModem);
            RegCloseKey(hClass);
            RegCloseKey(hServices);
            RegCloseKey(hCurrentControlSet);
            RegCloseKey(hSystem);
            return FALSE;
        }

        RegCloseKey(hModem);
        RegCloseKey(hClass);
        RegCloseKey(hServices);
        RegCloseKey(hCurrentControlSet);
        RegCloseKey(hSystem);
        return cSubKeys != 0;
    }
}

// 0x7A58D0
static BOOL CALLBACK CNetworkEnumAddressCallback(REFGUID guidDataType, DWORD dwDataSize, LPCVOID lpData, LPVOID lpContext)
{
    if (IsEqualGUID(guidDataType, DPAID_Modem)) {
        LPCSTR lpAddress = (LPCSTR)lpData;
        while (lstrlenA(lpAddress) != 0) {
            g_pChitin->cNetwork.AddModemAddressToList(lpAddress);
            lpAddress += lstrlenA(lpAddress) + 1;
        }
    }

    return TRUE;
}

// 0x7A5150
void CNetwork::EnumerateModems()
{
    IDirectPlay4A* lpDirectPlay;
    LPVOID lpAddress = NULL;
    HRESULT hr;
    DWORD dwSize = 0;

    m_bModemEnumerated = TRUE;
    m_nTotalModemAddresses = 0;

    if (!HasModems()) {
        return;
    }

    for (INT nIndex = 0; nIndex < m_nTotalServiceProviders; nIndex++) {
        if (IsEqualGUID(m_serviceProviderGuids[nIndex], DPSPGUID_MODEM)) {
            // NOTE: Looks odd, probably some inlining.
            if (m_bServiceProviderEnumerated && nIndex < m_nTotalServiceProviders) {
                m_nServiceProvider = nIndex;
                m_bServiceProviderSelected = TRUE;
            }
        }
    }

    if (CreateDirectPlayAddress(FALSE)) {
        if (CreateDirectPlayInterface(&GUID_NULL, &lpDirectPlay)
            && lpDirectPlay->InitializeConnection(m_pDirectPlayAddress, 0) == DP_OK) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }
            m_bConnectionInitialized = TRUE;
        } else {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            m_bConnectionInitialized = FALSE;
        }
    } else {
        m_bConnectionInitialized = FALSE;
    }

    if (m_bConnectionInitialized == TRUE) {
        hr = lpDirectPlay->GetPlayerAddress(0, NULL, &dwSize);
        if (hr == DPERR_BUFFERTOOSMALL) {
            lpAddress = new BYTE[dwSize];
            if (lpAddress != NULL) {
                hr = lpDirectPlay->GetPlayerAddress(0, lpAddress, &dwSize);
            } else {
                hr = DPERR_NOMEMORY;
            }
        }
    } else {
        hr = DP_OK;
    }

    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_bConnectionInitialized = FALSE;

    if (lpDirectPlay != NULL) {
        lpDirectPlay->Release();
        lpDirectPlay = NULL;
    }

    if (lpAddress != NULL) {
        if (dwSize != 0) {
            if (hr == DP_OK) {
                EnterCriticalSection(&field_F6A);
                m_lpDirectPlayLobby->EnumAddress(CNetworkEnumAddressCallback,
                    lpAddress,
                    dwSize,
                    NULL);
                LeaveCriticalSection(&field_F6A);
            }
        }
        delete lpAddress;
    }
}

// 0x7A5930
static BOOL CALLBACK CNetworkEnumConnectionsCallback(LPCGUID lpguidSP, LPVOID lpConnection, DWORD dwConnectionSize, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
    CString sServiceProviderName;

    if (IsEqualGUID(*lpguidSP, DPSPGUID_TCPIP)) {
        sServiceProviderName = "TCP/IP";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_IPX)) {
        sServiceProviderName = "IPX";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_MODEM)) {
        sServiceProviderName = "Modem";
    } else if (IsEqualGUID(*lpguidSP, DPSPGUID_SERIAL)) {
        sServiceProviderName = "Serial";
    }

    if (!sServiceProviderName.IsEmpty()) {
        g_pChitin->cNetwork.AddServiceProviderToList(sServiceProviderName,
            *lpguidSP,
            lpConnection,
            dwConnectionSize);
    }

    return TRUE;
}

// 0x7A5340
BOOLEAN CNetwork::EnumerateServiceProviders()
{
    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Release();
        m_lpDirectPlay = NULL;
    }

    if (!CreateDirectPlayInterface(&GUID_NULL, &m_lpDirectPlay)) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    if (m_lpDirectPlayLobby != NULL) {
        m_lpDirectPlayLobby->Release();
        m_lpDirectPlayLobby = NULL;
    }

    if (!SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x405, reinterpret_cast<WPARAM>(&m_lpDirectPlayLobby), 0)) {
        LeaveCriticalSection(&field_F6A);
        return FALSE;
    }

    m_bServiceProviderEnumerated = TRUE;
    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_nTotalServiceProviders = 0;
    m_serviceProviderGuids[0] = GUID_NULL;
    m_nTotalServiceProviders++;

    m_lpDirectPlay->EnumConnections(&m_nApplicationGuid, CNetworkEnumConnectionsCallback, NULL, DPCONNECTION_DIRECTPLAY);
    LeaveCriticalSection(&field_F6A);

    for (INT nIndex = 0; nIndex < m_nTotalServiceProviders; nIndex++) {
        if (IsEqualGUID(m_serviceProviderGuids[nIndex], DPSPGUID_MODEM)) {
            g_pChitin->cNetwork.EnumerateModems();
        }
    }

    return TRUE;
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

    nServiceProviderType = SERV_PROV_NULL;

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_IPX)) {
        nServiceProviderType = SERV_PROV_IPX;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_SERIAL)) {
        nServiceProviderType = SERV_PROV_SERIAL;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_MODEM)) {
        nServiceProviderType = SERV_PROV_MODEM;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], DPSPGUID_TCPIP)) {
        nServiceProviderType = SERV_PROV_TCP_IP;
        return TRUE;
    }

    if (IsEqualGUID(m_serviceProviderGuids[nServiceProviderNumber], GUID_NULL)) {
        nServiceProviderType = SERV_PROV_NULL;
    }

    return TRUE;
}

// 0x7A5600
BOOLEAN CNetwork::InitializeConnectionToServiceProvider(BOOLEAN bHostingGame)
{
    if (!CreateDirectPlayAddress(bHostingGame)) {
        return FALSE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay == NULL) {
        if (SendMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), 0x406, (WPARAM)&m_lpDirectPlay, 0) == 0) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            LeaveCriticalSection(&field_F6A);
            m_bConnectionInitialized = FALSE;
            return FALSE;
        }
    }

    HRESULT hr;
    if (m_nServiceProvider != 0) {
        hr = m_lpDirectPlay->InitializeConnection(m_pDirectPlayAddress, 0);
    }

    LeaveCriticalSection(&field_F6A);

    if (m_nServiceProvider != 0) {
        if (hr != DP_OK && hr != DPERR_ALREADYINITIALIZED) {
            if (m_pDirectPlayAddress != NULL) {
                delete m_pDirectPlayAddress;
                // FIXME: `m_pDirectPlayAddress` is not nullified.

                m_bDirectPlayAddressCreated = FALSE;
            }

            m_bConnectionInitialized = FALSE;
            return FALSE;
        }
    }

    if (m_pDirectPlayAddress != NULL) {
        delete m_pDirectPlayAddress;
        // FIXME: `m_pDirectPlayAddress` is not nullified.

        m_bDirectPlayAddressCreated = FALSE;
    }

    m_bConnectionInitialized = TRUE;
    return TRUE;
}

// 0x7A5720
void CNetwork::RemoveInitializeConnection()
{
    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Release();
        m_lpDirectPlay = NULL;
    }

    LeaveCriticalSection(&field_F6A);

    m_bConnectionInitialized = FALSE;
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
        m_dwSessionFlags |= DPSESSION_KEEPALIVE;
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
    if (!m_bConnectionEstablished) {
        return;
    }

    g_pChitin->OnMultiplayerSessionClose();

    if (m_bPlayerCreated == TRUE) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            hr = m_lpDirectPlay->DestroyPlayer(m_idLocalPlayer);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr == DP_OK) {
            m_bPlayerCreated = FALSE;
        }
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
    }

    m_nTotalPlayers = 0;

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->Close();
    }

    LeaveCriticalSection(&field_F6A);

    m_bConnectionInitialized = FALSE;
    m_bSessionEnumerated = FALSE;

    for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
        m_psSessionName[nSession] = "";
        m_pSessionGuid[nSession] = GUID_NULL;
        m_pbSessionPasswordRequired[nSession] = FALSE;
    }

    m_bSessionSelected = FALSE;
    m_nSession = -1;
    m_nTotalSessions = 0;
    m_guidSession = GUID_NULL;
    m_bSessionNameToMake = FALSE;
    m_sSessionNameToMake = "";
    m_bAllowNewConnections = FALSE;
    m_bSessionPasswordEnabled = FALSE;
    m_sSessionPassword = "";

    EnterCriticalSection(&field_F6A);

    if (m_pLastSessionBuffer != NULL) {
        delete m_pLastSessionBuffer;
        m_pLastSessionBuffer = NULL;
    }

    m_dwLastSessionBufferSize = 0;

    LeaveCriticalSection(&field_F6A);

    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    m_bSessionOptionsDefined = FALSE;
    m_nMaxPlayers = CNETWORK_MAX_PLAYERS;
    m_dwSessionFlags = 0;
    m_bPlayerNameToMake = FALSE;
    m_bPlayerCreated = FALSE;
    m_idLocalPlayer = 0;
    m_sLocalPlayerName = "";
    m_nHostPlayer = -1;
    m_nLocalPlayer = -1;
    m_nTotalPlayers = 0;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
        m_pSlidingWindow[nPlayer].Initialize(nPlayer);
    }

    m_SystemWindow.RemoveFromAllQueues();

    for (int index = 0; index < 6; index++) {
        field_71A[index] = FALSE;
    }
}

// 0x7A5D00
BOOLEAN CNetwork::CheckSessionStatus(BOOLEAN bInThreadLoop)
{
    HRESULT hr;
    DWORD dwSize = m_dwLastSessionBufferSize;
    INT nCurrentPlayers;
    INT nMaxPlayers;

    if (m_bConnectionEstablished != TRUE) {
        return TRUE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        hr = m_lpDirectPlay->GetSessionDesc(NULL, &dwSize);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr == DPERR_BUFFERTOOSMALL) {
        if (m_dwLastSessionBufferSize < dwSize) {
            EnterCriticalSection(&field_F6A);

            if (m_pLastSessionBuffer != NULL) {
                delete m_pLastSessionBuffer;
                m_pLastSessionBuffer = NULL;
            }

            m_pLastSessionBuffer = new BYTE[dwSize];
            m_dwLastSessionBufferSize = dwSize;

            LeaveCriticalSection(&field_F6A);
        }

        if (m_pLastSessionBuffer == NULL) {
            UTIL_ASSERT_MSG(FALSE, "CNetwork::CheckSessionStatus: Can't create session descriptor.");
        }

        EnterCriticalSection(&field_F6A);

        hr = m_lpDirectPlay->GetSessionDesc(m_pLastSessionBuffer, &dwSize);

        LeaveCriticalSection(&field_F6A);

        nCurrentPlayers = reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer)->dwCurrentPlayers;
        nMaxPlayers = reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer)->dwMaxPlayers;
    } else {
        if (m_nServiceProvider != 0) {
            nCurrentPlayers = 1;
            nMaxPlayers = 1;
        }
    }

    if (!bInThreadLoop && hr == DP_OK) {
        m_sessionDesc = *reinterpret_cast<DPSESSIONDESC2*>(m_pLastSessionBuffer);

        nMaxPlayers = m_sessionDesc.dwMaxPlayers;
        if (nMaxPlayers <= CNETWORK_MAX_PLAYERS) {
            m_nMaxPlayers = nMaxPlayers;
        }
    }

    if (bInThreadLoop == TRUE && m_bIsHost == TRUE && hr == DP_OK) {
        // TODO: Check.
        if ((nCurrentPlayers != CNETWORK_MAX_PLAYERS
                || nMaxPlayers != CNETWORK_MAX_PLAYERS)
            && nMaxPlayers != nCurrentPlayers + 1) {
            m_nMaxPlayers = max(nCurrentPlayers + 1, CNETWORK_MAX_PLAYERS);
            SetInSessionOptions();
        }
    }

    if (hr == DPERR_NOCONNECTION) {
        if (bInThreadLoop) {
            g_pChitin->OnMultiplayerSessionToClose();
            SleepEx(1000, FALSE);

            if (m_bConnectionEstablished == TRUE) {
                OnCloseSession();
            }
        } else {
            OnCloseSession();
        }

        return FALSE;
    }

    if (nCurrentPlayers != m_nTotalPlayers) {
        EnumeratePlayers(bInThreadLoop);
    }

    return TRUE;
}

// 0x7A6840
static BOOL CALLBACK CNetworkEnumSessionsCallback(LPCDPSESSIONDESC2 lpSessionDesc, LPDWORD lpdwTimeOut, DWORD dwFlags, LPVOID lpContext)
{
    CString sSessionName;

    if ((dwFlags & DPESC_TIMEDOUT) != 0) {
        return FALSE;
    }

    sSessionName = lpSessionDesc->lpszPasswordA;

    CNetwork* pNetwork = &(g_pChitin->cNetwork);
    if (pNetwork->m_nTotalSessions < CNETWORK_MAX_SESSIONS) {
        pNetwork->m_psSessionName[pNetwork->m_nTotalSessions] = sSessionName;
        pNetwork->m_pSessionGuid[pNetwork->m_nTotalSessions] = lpSessionDesc->guidInstance;
        pNetwork->m_pbSessionPasswordRequired[pNetwork->m_nTotalSessions] = (lpSessionDesc->dwFlags & DPSESSION_PASSWORDREQUIRED) != 0;
        pNetwork->m_nTotalSessions++;
    }

    return TRUE;
}

// 0x7A5F00
BOOLEAN CNetwork::EnumerateSessions(BOOLEAN a1, BOOLEAN a2)
{
    DPSESSIONDESC2 dpsd = { 0 };
    dpsd.dwSize = sizeof(dpsd);
    dpsd.guidApplication = m_nApplicationGuid;

    DPCAPS caps = { 0 };
    caps.dwSize = sizeof(caps);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->GetCaps(&caps, 0);
    }

    DWORD dwTimeout = 0;
    if (!a1 && !a2) {
        dwTimeout = 3000;
    }

    DWORD dwFlags = DPENUMSESSIONS_AVAILABLE | DPENUMSESSIONS_PASSWORDREQUIRED;

    if (!IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_MODEM)
        && !IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_TCPIP)) {
        dwFlags |= DPENUMSESSIONS_RETURNSTATUS;
    }

    if (a2 == TRUE) {
        dwFlags |= DPENUMSESSIONS_STOPASYNC;
    } else if (a1 == TRUE) {
        dwFlags |= DPENUMSESSIONS_ASYNC;
    }

    if (m_bSessionEnumerated == TRUE) {
        for (INT nSession = 0; nSession < m_nTotalSessions; nSession++) {
            m_psSessionName[nSession] = "";
            m_pSessionGuid[nSession] = GUID_NULL;
            m_pbSessionPasswordRequired[nSession] = FALSE;
        }
        m_nTotalSessions = 0;
    }

    EnterCriticalSection(&field_F6A);

    HRESULT hr;
    if (m_lpDirectPlay != NULL) {
        do {
            hr = m_lpDirectPlay->EnumSessions(&dpsd,
                dwTimeout,
                CNetworkEnumSessionsCallback,
                NULL,
                dwFlags);
        } while (hr == DPERR_CONNECTING);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr != DP_OK) {
        m_bSessionEnumerated = FALSE;

        for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
            m_psSessionName[nSession] = "";
            m_pSessionGuid[nSession] = GUID_NULL;
            m_pbSessionPasswordRequired[nSession] = FALSE;
        }

        return FALSE;
    }

    m_bSessionEnumerated = TRUE;

    if (m_bSessionSelected == TRUE) {
        m_bSessionSelected = FALSE;

        for (INT nSession = 0; nSession < CNETWORK_MAX_SESSIONS; nSession++) {
            if (IsEqualGUID(m_pSessionGuid[nSession], m_guidSession)) {
                m_nSession = nSession;
                m_bSessionSelected = TRUE;
            }
        }

        if (!m_bSessionSelected) {
            m_guidSession = GUID_NULL;
        }
    }

    return TRUE;
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
    char szSessionName[200];
    char szSessionPassword[200];

    if (m_bConnectionInitialized != TRUE) {
        return FALSE;
    }

    if (m_bConnectionEstablished) {
        return FALSE;
    }

    if (!m_bSessionNameToMake) {
        return FALSE;
    }

    m_sessionDesc = { 0 };
    m_sessionDesc.dwFlags = m_dwSessionFlags;
    m_sessionDesc.guidApplication = m_nApplicationGuid;
    m_sessionDesc.dwSize = sizeof(m_sessionDesc);
    m_sessionDesc.dwMaxPlayers = m_nMaxPlayers;

    memset(szSessionName, 0, sizeof(szSessionName));
    strncpy(szSessionName, m_sSessionNameToMake, m_sSessionNameToMake.GetLength());
    m_sessionDesc.lpszSessionNameA = szSessionName;

    if (m_bSessionPasswordEnabled == TRUE) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    DWORD dwOpenFlags = DPOPEN_CREATE;
    if (!IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_MODEM)
        && !IsEqualGUID(m_serviceProviderGuids[m_nServiceProvider], DPSPGUID_TCPIP)) {
        dwOpenFlags |= DPOPEN_RETURNSTATUS;
    }

    if (m_nServiceProvider != 0) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            do {
                hr = m_lpDirectPlay->Open(&m_sessionDesc, dwOpenFlags);
            } while (hr == DPERR_CONNECTING);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr != DP_OK) {
            return FALSE;
        }
    }

    m_bAllowNewConnections = TRUE;
    m_bConnectionEstablished = TRUE;
    m_bIsHost = TRUE;
    m_nHostPlayer = -1;
    m_nTotalPlayers = 0;
    m_nLocalPlayer = -1;

    for (int index = 0; index < CNETWORK_MAX_PLAYERS; index++) {
        m_pPlayerID[index] = 0;
        m_psPlayerName[index] = "";
        m_pbPlayerEnumerateFlag[index] = FALSE;
        m_pbPlayerVisible[index] = FALSE;
        m_pSlidingWindow[index].Initialize(index);
    }

    m_SystemWindow.Initialize(-1);

    g_pChitin->OnMultiplayerSessionOpen(m_sJoinedGame, m_sDroppedGame, m_sLeftGame);

    return TRUE;
}

// 0x7A64B0
BOOLEAN CNetwork::JoinSelectedSession(INT& nErrorCode)
{
    char szSessionPassword[200];

    if (!m_bSessionSelected) {
        nErrorCode = ERROR_CANNOTCONNECT;
        return FALSE;
    }

    m_sessionDesc = { 0 };
    m_sessionDesc.dwSize = sizeof(m_sessionDesc);
    m_sessionDesc.guidInstance = m_guidSession;

    if (m_bSessionPasswordEnabled) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    EnterCriticalSection(&field_F6A);

    HRESULT hr;
    if (m_lpDirectPlay != NULL) {
        do {
            hr = m_lpDirectPlay->Open(&m_sessionDesc, DPOPEN_JOIN);
        } while (hr == DPERR_CONNECTING);
    } else {
        hr = DPERR_NOMEMORY;
    }

    LeaveCriticalSection(&field_F6A);

    if (hr == DPERR_INVALIDPASSWORD) {
        nErrorCode = ERROR_INVALIDPASSWORD;
        return FALSE;
    }

    if (hr != DP_OK) {
        nErrorCode = ERROR_CANNOTCONNECT;
        return FALSE;
    }

    m_bConnectionEstablished = TRUE;
    m_bIsHost = FALSE;
    m_nHostPlayer = -1;
    m_nTotalPlayers = 0;
    m_nLocalPlayer = -1;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pPlayerID[nPlayer] = 0;
        m_psPlayerName[nPlayer] = "";
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
        m_pbPlayerVisible[nPlayer] = FALSE;
        m_pSlidingWindow[nPlayer].Initialize(nPlayer);
    }

    m_SystemWindow.Initialize(-1);

    g_pChitin->OnMultiplayerSessionOpen(m_sJoinedGame, m_sDroppedGame, m_sLeftGame);

    return TRUE;
}

// 0x7A6680
BOOLEAN CNetwork::SelectSession(INT nSession)
{
    if (!m_bSessionEnumerated) {
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
    char szSessionName[200];
    char szSessionPassword[200];

    if (m_bConnectionEstablished != TRUE) {
        return FALSE;
    }

    if (m_bIsHost != TRUE) {
        return FALSE;
    }

    m_sessionDesc.dwMaxPlayers = m_nMaxPlayers;

    memset(szSessionName, 0, sizeof(szSessionName));
    strncpy(szSessionName, m_sSessionNameToMake, m_sSessionNameToMake.GetLength());
    m_sessionDesc.lpszSessionNameA = szSessionName;

    if (m_bAllowNewConnections == TRUE) {
        m_sessionDesc.dwFlags = m_dwSessionFlags;
    } else {
        m_sessionDesc.dwFlags = m_dwSessionFlags | DPSESSION_JOINDISABLED | DPSESSION_NEWPLAYERSDISABLED;
    }

    if (m_bSessionPasswordEnabled == TRUE) {
        memset(szSessionPassword, 0, sizeof(szSessionPassword));
        strncpy(szSessionPassword, m_sSessionPassword, m_sSessionPassword.GetLength());
        m_sessionDesc.lpszPasswordA = szSessionPassword;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        HRESULT hr = m_lpDirectPlay->SetSessionDesc(&m_sessionDesc, 0);
        if (hr != DP_OK) {
            LeaveCriticalSection(&field_F6A);
            return FALSE;
        }
    }

    LeaveCriticalSection(&field_F6A);
    return TRUE;
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
    if (m_bConnectionEstablished != TRUE) {
        m_bPlayerCreated = FALSE;
        return FALSE;
    }

    if (!m_bPlayerNameToMake) {
        m_bPlayerCreated = FALSE;
        return FALSE;
    }

    if (FindPlayerIDByName(m_sLocalPlayerName, TRUE) != 0) {
        m_bPlayerCreated = FALSE;
        nErrorCode = ERROR_PLAYEREXISTS;
        return FALSE;
    }

    DPNAME dpName;
    dpName.dwSize = sizeof(dpName);
    dpName.dwFlags = 0;
    dpName.lpszShortNameA = NULL;
    dpName.lpszLongNameA = NULL;

    char szPlayerName[256];
    memcpy(szPlayerName, m_sLocalPlayerName.GetBuffer(m_sLocalPlayerName.GetLength()), m_sLocalPlayerName.GetLength());
    szPlayerName[m_sLocalPlayerName.GetLength()] = '\0';

    dpName.lpszShortNameA = szPlayerName;
    dpName.lpszLongNameA = szPlayerName;

    DWORD dwPlayerFlags = 0;
    if (m_bIsHost == TRUE) {
        dwPlayerFlags = DPPLAYER_SERVERPLAYER;
    }

    if (m_nServiceProvider != SERV_PROV_NULL) {
        EnterCriticalSection(&field_F6A);

        HRESULT hr;
        if (m_lpDirectPlay != NULL) {
            hr = m_lpDirectPlay->CreatePlayer(&m_idLocalPlayer,
                &dpName,
                g_pChitin->field_180,
                NULL,
                0,
                dwPlayerFlags);
        } else {
            hr = DPERR_NOMEMORY;
        }

        LeaveCriticalSection(&field_F6A);

        if (hr == DPERR_NOCONNECTION || hr == DPERR_GENERIC) {
            m_bPlayerCreated = FALSE;
            nErrorCode = ERROR_CANNOTCONNECT;
            return FALSE;
        }

        if (hr != DP_OK) {
            m_bPlayerCreated = FALSE;
            nErrorCode = ERROR_CANNOTCREATEPLAYER;
            return FALSE;
        }

        AddPlayerToList(m_idLocalPlayer, m_sLocalPlayerName, m_bIsHost, TRUE);
    } else {
        INT nSlot;
        for (nSlot = 0; nSlot < CNETWORK_MAX_PLAYERS; nSlot++) {
            if (!field_71A[nSlot]) {
                break;
            }
        }

        if (nSlot >= CNETWORK_MAX_PLAYERS) {
            return FALSE;
        }

        m_idLocalPlayer = nSlot + 1;
        field_702[nSlot] = szPlayerName;
        field_71A[nSlot] = TRUE;
    }

    m_bPlayerCreated = TRUE;
    AddPlayerToList(m_idLocalPlayer, m_sLocalPlayerName, m_bIsHost, TRUE);

    nErrorCode = ERROR_NONE;
    return TRUE;
}

// 0x7A6BC0
BOOLEAN CNetwork::AddPlayerToList(PLAYER_ID dpID, const CString& sPlayerName, BOOLEAN bIsHost, BOOLEAN bMakeVisible)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
    // __LINE__: 6907
    UTIL_ASSERT(dpID != 0);

    INT nFound = -1;
    BOOLEAN bFound = FALSE;

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (bFound) {
            break;
        }

        if (nFound == -1 && m_pPlayerID[nPlayerNumber] == 0) {
            nFound = nPlayerNumber;
        }

        if (m_pPlayerID[nPlayerNumber] != 0) {
            if (dpID == m_pPlayerID[nPlayerNumber]) {
                bFound = TRUE;
                m_pbPlayerEnumerateFlag[nPlayerNumber] = TRUE;

                if (bIsHost == TRUE) {
                    m_nHostPlayer = nPlayerNumber;
                }
            }

            if (m_idLocalPlayer == m_pPlayerID[nPlayerNumber]) {
                m_nLocalPlayer = nPlayerNumber;
            }
        }
    }

    if (bFound) {
        return FALSE;
    }

    for (INT nPlayerNumber = 0; nPlayerNumber < CNETWORK_MAX_PLAYERS; nPlayerNumber++) {
        if (field_772[nPlayerNumber] == dpID) {
            return FALSE;
        }
    }

    if (nFound == -1) {
        return FALSE;
    }

    m_pPlayerID[nFound] = dpID;
    m_psPlayerName[nFound] = sPlayerName;
    m_pbPlayerVisible[nFound] = bMakeVisible;

    if (bIsHost == TRUE) {
        m_nHostPlayer = nFound;
    }

    if (dpID == m_idLocalPlayer) {
        m_nLocalPlayer = nFound;
    }

    m_pbPlayerEnumerateFlag[nFound] = TRUE;
    m_nTotalPlayers++;

    m_pSlidingWindow[nFound].Initialize(nFound);

    g_pChitin->OnMultiplayerPlayerJoin(m_pPlayerID[nFound], m_psPlayerName[nFound]);

    return TRUE;
}

// 0x7A6EA0
BOOLEAN CNetwork::RemovePlayerFromList(PLAYER_ID dpID, BOOLEAN bAIResponsible)
{
    INT nPlayerToRemove = -1;
    BOOLEAN bFound = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] == dpID) {
            nPlayerToRemove = nPlayer;
            bFound = TRUE;
        }
    }

    if (bFound != TRUE) {
        return bFound;
    }

    if (nPlayerToRemove == m_nHostPlayer) {
        if (bAIResponsible != TRUE) {
            g_pChitin->OnMultiplayerSessionToClose();
            SleepEx(1000, FALSE);

            if (m_bConnectionEstablished == TRUE) {
                OnCloseSession();
            }
        } else {
            OnCloseSession();
        }
    } else {
        g_pChitin->OnMultiplayerPlayerLeave(m_pPlayerID[nPlayerToRemove], m_psPlayerName[nPlayerToRemove]);
        m_pSlidingWindow[nPlayerToRemove].ShutDown();
        m_pPlayerID[nPlayerToRemove] = 0;
        m_psPlayerName[nPlayerToRemove] = "";
        m_pbPlayerEnumerateFlag[nPlayerToRemove] = FALSE;
        m_pbPlayerVisible[nPlayerToRemove] = FALSE;
        m_nTotalPlayers--;
    }

    return TRUE;
}

// 0x7A7510
static BOOL CALLBACK CNetworkEnumPlayersCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
    CString sPlayerName;

    if (dwPlayerType == DPPLAYERTYPE_PLAYER) {
        sPlayerName = lpName->lpszShortNameA;
        g_pChitin->cNetwork.AddPlayerToList(dpId,
            sPlayerName,
            (dwFlags & DPENUMPLAYERS_SERVERPLAYER) != 0,
            FALSE);
    }

    return TRUE;
}

// 0x7A6F80
void CNetwork::EnumeratePlayers(BOOLEAN bProtectList)
{
    if (!m_bConnectionEstablished) {
        return;
    }

    if (!bProtectList) {
        for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
            m_pPlayerID[nPlayer] = 0;
            m_psPlayerName[nPlayer] = "";
            m_pbPlayerVisible[nPlayer] = FALSE;
        }

        m_nTotalPlayers = 0;
    }

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        m_pbPlayerEnumerateFlag[nPlayer] = FALSE;
    }

    EnterCriticalSection(&field_F6A);

    if (m_lpDirectPlay != NULL) {
        m_lpDirectPlay->EnumPlayers(NULL,
            CNetworkEnumPlayersCallback,
            NULL,
            0);
        LeaveCriticalSection(&field_F6A);

        if (bProtectList == TRUE) {
            for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
                if (m_pPlayerID[nPlayer] != 0 && !m_pbPlayerEnumerateFlag[nPlayer]) {
                    CString sLeavingGame;
                    CString sLeftPlayerName;

                    sLeftPlayerName = m_psPlayerName[nPlayer];
                    if (RemovePlayerFromList(m_pPlayerID[nPlayer], FALSE) == TRUE) {
                        sLeavingGame.Format(" %s: %s", (LPCSTR)sLeftPlayerName, (LPCSTR)m_sLeftGame);
                        sLeavingGame.SetAt(0, sLeavingGame.GetLength() - 1);

                        BYTE* pSystemMsg = CreateCopyMessage((LPCSTR)sLeavingGame,
                            sLeavingGame.GetLength(),
                            0,
                            0,
                            1);
                        if (pSystemMsg != NULL) {
                            m_SystemWindow.AddToIncomingQueue(0,
                                m_idLocalPlayer,
                                pSystemMsg,
                                sLeavingGame.GetLength() + 12);
                        }
                    } else {
                        for (INT nIndex = 0; nIndex < CNETWORK_MAX_PLAYERS; nIndex++) {
                            if (field_772[nIndex] == m_pPlayerID[nPlayer]) {
                                field_772[nIndex] = 0;
                            }
                        }
                    }
                }
            }
        }
    } else {
        LeaveCriticalSection(&field_F6A);
    }
}

// NOTE: Inlined.
BOOLEAN CNetwork::MakePlayerVisible(PLAYER_ID playerID)
{
    BOOLEAN bResult = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] == playerID && !m_pbPlayerVisible[nPlayer]) {
            m_pbPlayerVisible[nPlayer] = TRUE;
            g_pChitin->OnMultiplayerPlayerVisible(playerID);

            bResult = TRUE;
        }
    }

    return bResult;
}

// 0x7A7160
BOOLEAN CNetwork::MakePlayersVisible()
{
    BOOLEAN bResult = FALSE;

    for (INT nPlayer = 0; nPlayer < CNETWORK_MAX_PLAYERS; nPlayer++) {
        if (m_pPlayerID[nPlayer] != 0 && !m_pbPlayerVisible[nPlayer]) {
            // NOTE: Uninline.
            bResult |= MakePlayerVisible(m_pPlayerID[nPlayer]);
        }
    }

    return bResult;
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

// 0x7A7490
static BOOL CALLBACK CNetworkLobbyEnumAddressCallback(REFGUID guidDataType, DWORD dwDataSize, LPCVOID lpData, LPVOID lpContext)
{
    if (IsEqualGUID(guidDataType, DPAID_INet)) {
        g_pChitin->cNetwork.field_792 = CString((LPCSTR)lpData);
    }

    return TRUE;
}

// 0x7A73D0
void CNetwork::sub_7A73D0(CString& a1)
{
    HRESULT hr;
    DWORD dwSize;

    a1 = "";

    if (m_lpDirectPlay != NULL) {
        hr = m_lpDirectPlay->GetPlayerAddress(1, NULL, &dwSize);
        if (hr == DPERR_BUFFERTOOSMALL) {
            LPVOID pData = new BYTE[dwSize];

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChNetwork.cpp
            // __LINE__: 7685
            UTIL_ASSERT(pData != NULL);

            hr = m_lpDirectPlay->GetPlayerAddress(1, pData, &dwSize);
            if (hr == DP_OK) {
                if (m_lpDirectPlayLobby != NULL) {
                    field_792 = "";
                    m_lpDirectPlayLobby->EnumAddress(CNetworkLobbyEnumAddressCallback,
                        pData,
                        dwSize,
                        NULL);
                    a1 = field_792;
                }
            }
        }
    }
}

// 0x7A7DF0
BYTE* CNetwork::CreateCopyMessage(const void* lpData, DWORD dwDataSize, unsigned char a3, unsigned char a4, int a5)
{
    // TODO: Incomplete.

    return NULL;
}

// 0x452B40
INT CNetwork::GetServiceProvider()
{
    return m_nServiceProvider;
}

// 0x452B50
BOOLEAN CNetwork::GetSessionOpen()
{
    return m_bConnectionEstablished;
}

// 0x452B60
BOOLEAN CNetwork::GetSessionHosting()
{
    return m_bIsHost;
}

#if DPLAY_COMPAT

static HRESULT WINAPI FakeDirectPlayCreate(LPGUID, LPDIRECTPLAY*, IUnknown*)
{
    return DPERR_GENERIC;
}

static HRESULT WINAPI FakeDirectPlayLobbyCreateA(LPGUID, LPDIRECTPLAYLOBBYA*, IUnknown*, LPVOID, DWORD)
{
    return DPERR_GENERIC;
}

void CNetwork::InitDirectPlay()
{
    hDirectPlayDLL = LoadLibraryA("dplayx");
    if (hDirectPlayDLL != NULL) {
        DirectPlayCreate = (DirectPlayCreateFunc*)GetProcAddress(hDirectPlayDLL, "DirectPlayCreate");
        DirectPlayLobbyCreateA = (DirectPlayLobbyCreateFunc*)GetProcAddress(hDirectPlayDLL, "DirectPlayLobbyCreateA");
    }

    if (DirectPlayCreate == NULL) {
        DirectPlayCreate = FakeDirectPlayCreate;
    }

    if (DirectPlayLobbyCreateA == NULL) {
        DirectPlayLobbyCreateA = FakeDirectPlayLobbyCreateA;
    }
}

void CNetwork::FreeDirectPlay()
{
    if (hDirectPlayDLL != NULL) {
        FreeLibrary(hDirectPlayDLL);
        hDirectPlayDLL = NULL;
    }
}

#endif

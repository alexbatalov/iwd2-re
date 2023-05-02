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
    field_0 = 0;
    field_4 = 0;
    m_nApplicationGuid = GUID_NULL;
    m_bApplicationGuidDefined = FALSE;
    field_19 = 0;
    m_bServiceProviderEnumerated = FALSE;
    m_bServiceProviderSelected = FALSE;
    m_nServiceProvider = -1;
    m_nTotalServiceProviders = 0;
    m_serviceProviderGuids[m_nTotalServiceProviders++] = GUID_NULL;
    field_9C = 0;
    field_24 = 0;
    field_28 = 0;
    field_2C = 0;
    field_30 = 0;
    field_34 = 0;
    field_9F = 0;
    field_A0 = 0;
    field_A2 = -1;
    field_A6 = 0;
    field_FA = "";
    field_FE = "";
    field_106 = 57600;
    field_102 = 1;
    field_112 = 4;
    field_10E = 0;
    field_10A = 0;
    field_120 = 0;

    for (int k = 0; k < 64; k++) {
        field_12A[k] = "";
        field_22A[k] = GUID_NULL;
        field_630[k] = 0;
    }

    m_bSessionSelected = FALSE;
    field_122 = -1;
    field_126 = 0;
    field_66A = GUID_NULL;
    field_67A = 0;
    field_67C = "";
    field_680 = 0;
    field_682 = "";
    field_686 = 1;
    field_6D8 = 0;
    field_6DC = 0;
    m_bConnectionEstablished = FALSE;
    m_bIsHost = FALSE;
    field_6EA = 0;
    field_6EB = 0;
    m_nMaxPlayers = 6;
    field_6E6 = 0;
    field_6F8 = 0;
    field_6F9 = 0;
    field_6FA = 0;
    field_6FE = "";
    field_78E = -1;
    field_78A = -1;
    field_732 = 0;

    for (int l = 0; l < 6; l++) {
        field_74E[l] = 0;
        field_772[l] = 0;
        field_736[l] = "";
        field_76C[l] = 0;
        field_766[l] = 0;
        m_pSlidingWindow[l].Initialize(l);
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
    // TODO: Incomplete.
}

// 0x7A5340
BOOLEAN CNetwork::EnumerateServiceProviders()
{
    // TODO: Incomplete.

    return FALSE;
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

// 0x7A5720
void CNetwork::RemoveInitializeConnection()
{
    // TODO: Incomplete.
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

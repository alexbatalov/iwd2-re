#ifndef CNETWORK_H_
#define CNETWORK_H_

#include "mfc.h"

#include "CNetworkWindow.h"

#define CNETWORK_MAX_SERVICE_PROVIDERS 5
#define CNETWORK_MAX_SESSIONS 64
#define CNETWORK_MAX_PLAYERS 6

typedef DWORD PLAYER_ID;

class CNetwork {
public:
    CNetwork();
    ~CNetwork();
    void AddModemAddressToList(LPCSTR lpAddress);
    void AddServiceProviderToList(const CString& sServiceProviderName, const GUID& sServiceProviderGuid, LPVOID lpConnection, size_t size);
    BOOLEAN EnumerateServiceProviders();
    INT FindModemAddress(const CString& sAddress);
    BOOLEAN GetModemAddress(INT nAddressNumber, CString& sAddress);
    BOOLEAN GetServiceProviderType(INT nServiceProviderNumber, INT& nServiceProviderType);
    BOOLEAN InitializeConnectionToServiceProvider(BOOLEAN bHostingGame);
    void RemoveInitializeConnection();
    BOOLEAN SelectModemAddress(INT nAddressNumber);
    BOOLEAN SelectServiceProvider(INT nServiceProviderNumber);
    void SetApplicationOptions(BOOLEAN bKeepAlive, BOOLEAN bMigrateHost);
    void SetJoinEnabled(BOOLEAN bJoinEnabled);
    BOOLEAN SetSerialBaudRate(UINT nBaudRate);
    BOOLEAN SetSerialPort(UINT nPort);
    void UnselectModemAddress();
    void CloseSession(BOOLEAN bAIResponsible);
    void OnCloseSession();
    BOOLEAN CheckSessionStatus(BOOLEAN bInThreadLoop);
    void EnumerateSessions(BOOLEAN a1, BOOLEAN a2);
    BOOLEAN sub_7A61D0();
    BOOLEAN GetPasswordRequiredForSelectedSession();
    BOOLEAN GetSessionName(INT nSession, CString& sSessionName);
    BOOLEAN GetSessionGUID(INT nSession, GUID& sessionGuid);
    BOOLEAN HostNewSession();
    BOOLEAN JoinSelectedSession(INT& nErrorCode);
    BOOLEAN SelectSession(INT nSession);
    BOOLEAN SetInSessionOptions();
    void SetMaxPlayers(INT nMaxPlayers);
    void UnselectSession();
    BOOLEAN CreatePlayer(INT& nErrorCode);
    void EnumeratePlayers(BOOLEAN bProtectList);
    BOOLEAN MakePlayersVisible();
    PLAYER_ID GetPlayerID(INT nPlayerNumber);
    void GetPlayerName(INT nPlayerNumber, CString& sPlayerName);
    PLAYER_ID GetRawPlayerID(INT nPlayerNumber);
    void GetRawPlayerName(INT nPlayerNumber, CString& sPlayerName);
    PLAYER_ID FindPlayerIDByName(const CString& sPlayerName, BOOLEAN bInvisible);
    INT FindPlayerLocationByID(PLAYER_ID playerID, BOOLEAN bInvisible);
    INT FindPlayerLocationByName(const CString& sPlayerName, BOOLEAN bInvisible);

    BOOLEAN GetSessionOpen();

    static const INT MAX_SERVICE_PROVIDERS;

    static const INT SERV_PROV_TCP_IP;
    static const INT SERV_PROV_MODEM;
    static const INT SERV_PROV_SERIAL;
    static const INT SERV_PROV_IPX;
    static const INT SERV_PROV_NULL;

    static const INT ERROR_NONE;
    static const INT ERROR_PLAYEREXISTS;
    static const INT ERROR_CANNOTCREATEPLAYER;
    static const INT ERROR_CANNOTCONNECT;
    static const INT ERROR_INVALIDPASSWORD;

    /* 0000 */ LPVOID m_lpDirectPlay;
    /* 0004 */ LPVOID m_lpDirectPlayLobby;
    /* 0008 */ GUID m_nApplicationGuid;
    /* 0018 */ BOOLEAN m_bApplicationGuidDefined;
    /* 0019 */ unsigned char field_19;
    /* 001A */ BOOLEAN m_bServiceProviderEnumerated;
    /* 001B */ BOOLEAN m_bServiceProviderSelected;
    /* 001C */ INT m_nServiceProvider;
    /* 0020 */ INT m_nTotalServiceProviders;
    /* 0024 */ LPVOID m_pServiceProviderConnections[CNETWORK_MAX_SERVICE_PROVIDERS];
    /* 0038 */ CString m_serviceProviderNames[CNETWORK_MAX_SERVICE_PROVIDERS];
    /* 004C */ GUID m_serviceProviderGuids[CNETWORK_MAX_SERVICE_PROVIDERS];
    /* 009C */ unsigned char field_9C;
    /* 009D */ unsigned char field_9D;
    /* 009E */ unsigned char field_9E;
    /* 009F */ BOOLEAN m_bModemEnumerated;
    /* 00A0 */ BOOLEAN m_bModemAddressSelected;
    /* 00A2 */ INT m_nModemAddress;
    /* 00A6 */ INT m_nTotalModemAddresses;
    /* 00AA */ CString m_psModemAddress[20];
    /* 00FA */ CString field_FA;
    /* 00FE */ CString field_FE;
    /* 0102 */ UINT m_nSerialPort;
    /* 0106 */ UINT m_nSerialBaudRate;
    /* 010A */ int field_10A;
    /* 010E */ int field_10E;
    /* 0112 */ int field_112;
    /* 0116 */ unsigned char field_116;
    /* 0118 */ int field_118;
    /* 0120 */ unsigned char field_120;
    /* 0121 */ BOOLEAN m_bSessionSelected;
    /* 0122 */ INT m_nSession;
    /* 0126 */ INT m_nTotalSessions;
    /* 012A */ CString m_psSessionName[CNETWORK_MAX_SESSIONS];
    /* 022A */ GUID m_pSessionGuid[CNETWORK_MAX_SESSIONS];
    /* 062A */ BOOLEAN m_pbSessionPasswordRequired[CNETWORK_MAX_SESSIONS];
    /* 066A */ GUID m_guidSession;
    /* 067A */ unsigned char field_67A;
    /* 067C */ CString field_67C;
    /* 0680 */ unsigned char field_680;
    /* 0682 */ CString field_682;
    /* 0686 */ unsigned char m_bAllowNewConnections;
    /* 06D8 */ int field_6D8;
    /* 06DC */ int field_6DC;
    /* 06E0 */ BOOLEAN m_bConnectionEstablished;
    /* 06E1 */ BOOLEAN m_bIsHost;
    /* 06E2 */ int m_nMaxPlayers;
    /* 06E6 */ int m_dwSessionFlags;
    /* 06EA */ unsigned char field_6EA;
    /* 06EB */ BOOLEAN m_bSessionOptionsDefined;
    /* 06EC */ CString field_6EC;
    /* 06F0 */ CString field_6F0;
    /* 06F4 */ CString field_6F4;
    /* 06F8 */ unsigned char field_6F8;
    /* 06F9 */ unsigned char field_6F9;
    /* 06FA */ int field_6FA;
    /* 06FE */ CString field_6FE;
    /* 0702 */ CString field_702[6];
    /* 071A */ int field_71A[6];
    /* 0732 */ int field_732;
    /* 0736 */ CString m_psPlayerName[CNETWORK_MAX_PLAYERS];
    /* 074E */ PLAYER_ID m_pPlayerID[CNETWORK_MAX_PLAYERS];
    /* 0766 */ BOOLEAN m_pbPlayerVisible[CNETWORK_MAX_PLAYERS];
    /* 076C */ BOOLEAN m_pbPlayerEnumerateFlag[CNETWORK_MAX_PLAYERS];
    /* 0772 */ int field_772[CNETWORK_MAX_PLAYERS];
    /* 078A */ int field_78A;
    /* 078E */ int field_78E;
    /* 0792 */ CString field_792;
    /* 0796 */ int field_796;
    /* 079A */ CNetworkWindow m_pSlidingWindow[CNETWORK_MAX_PLAYERS];
    /* 0ACA */ CNetworkWindow m_SystemWindow;
    /* 0B52 */ DWORD m_dwCRC32[256];
    /* 0F52 */ CRITICAL_SECTION field_F52;
    /* 0F6A */ CRITICAL_SECTION field_F6A;
};

#endif /* CNETWORK_H_ */

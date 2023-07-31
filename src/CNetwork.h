#ifndef CNETWORK_H_
#define CNETWORK_H_

#include "mfc.h"

#if _MSC_VER == 1200
#define DPLAY_COMPAT 0
#else
#define DPLAY_COMPAT 1
#endif

#include <dplay.h>
#include <dplobby.h>

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
    BOOLEAN CreateDirectPlayAddress(BOOLEAN bHostingGame);
    BOOLEAN CreateDirectPlayInterface(const GUID* guid, IDirectPlay4A** lplpDirectPlay4);
    BOOLEAN CreateDirectPlayLobbyInterface(IDirectPlayLobby3A** lplpDirectPlayLobby3);
    BOOLEAN HasModems();
    void EnumerateModems();
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
    BOOLEAN EnumerateSessions(BOOLEAN a1, BOOLEAN a2);
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
    BOOLEAN AddPlayerToList(PLAYER_ID dpID, const CString& sPlayerName, BOOLEAN bIsHost, BOOLEAN bMakeVisible);
    BOOLEAN RemovePlayerFromList(PLAYER_ID dpID, BOOLEAN bAIResponsible);
    void EnumeratePlayers(BOOLEAN bProtectList);
    BOOLEAN MakePlayerVisible(PLAYER_ID playerID);
    BOOLEAN MakePlayersVisible();
    PLAYER_ID GetPlayerID(INT nPlayerNumber);
    void GetPlayerName(INT nPlayerNumber, CString& sPlayerName);
    PLAYER_ID GetRawPlayerID(INT nPlayerNumber);
    void GetRawPlayerName(INT nPlayerNumber, CString& sPlayerName);
    PLAYER_ID FindPlayerIDByName(const CString& sPlayerName, BOOLEAN bInvisible);
    INT FindPlayerLocationByID(PLAYER_ID playerID, BOOLEAN bInvisible);
    INT FindPlayerLocationByName(const CString& sPlayerName, BOOLEAN bInvisible);
    void sub_7A73D0(CString& a1);
    BYTE* CreateCopyMessage(const void* lpData, DWORD dwDataSize, unsigned char a3, unsigned char a4, int a5);

    INT GetServiceProvider();
    BOOLEAN GetSessionOpen();
    BOOLEAN GetSessionHosting();

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

    /* 0000 */ IDirectPlay4A* m_lpDirectPlay;
    /* 0004 */ IDirectPlayLobby3A* m_lpDirectPlayLobby;
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
    /* 009C */ BOOLEAN m_bConnectionInitialized;
    /* 009D */ unsigned char field_9D;
    /* 009E */ unsigned char field_9E;
    /* 009F */ BOOLEAN m_bModemEnumerated;
    /* 00A0 */ BOOLEAN m_bModemAddressSelected;
    /* 00A2 */ INT m_nModemAddress;
    /* 00A6 */ INT m_nTotalModemAddresses;
    /* 00AA */ CString m_psModemAddress[20];
    /* 00FA */ CString m_sIPAddress;
    /* 00FE */ CString m_sPhoneNumber;
    /* 0102 */ UINT m_nSerialPort;
    /* 0106 */ UINT m_nSerialBaudRate;
    /* 010A */ DWORD m_nSerialStopBits;
    /* 010E */ DWORD m_nSerialParity;
    /* 0112 */ DWORD m_nSerialFlowControl;
    /* 0116 */ BOOLEAN m_bDirectPlayAddressCreated;
    /* 0118 */ LPVOID m_pDirectPlayAddress;
    /* 011C */ DWORD m_pDirectPlayAddressSize;
    /* 0120 */ BOOLEAN m_bSessionEnumerated;
    /* 0121 */ BOOLEAN m_bSessionSelected;
    /* 0122 */ INT m_nSession;
    /* 0126 */ INT m_nTotalSessions;
    /* 012A */ CString m_psSessionName[CNETWORK_MAX_SESSIONS];
    /* 022A */ GUID m_pSessionGuid[CNETWORK_MAX_SESSIONS];
    /* 062A */ BOOLEAN m_pbSessionPasswordRequired[CNETWORK_MAX_SESSIONS];
    /* 066A */ GUID m_guidSession;
    /* 067A */ BOOLEAN m_bSessionNameToMake;
    /* 067C */ CString m_sSessionNameToMake;
    /* 0680 */ BOOLEAN m_bSessionPasswordEnabled;
    /* 0682 */ CString m_sSessionPassword;
    /* 0686 */ BOOLEAN m_bAllowNewConnections;
    /* 0688 */ DPSESSIONDESC2 m_sessionDesc;
    /* 06D8 */ LPVOID m_pLastSessionBuffer;
    /* 06DC */ DWORD m_dwLastSessionBufferSize;
    /* 06E0 */ BOOLEAN m_bConnectionEstablished;
    /* 06E1 */ BOOLEAN m_bIsHost;
    /* 06E2 */ int m_nMaxPlayers;
    /* 06E6 */ DWORD m_dwSessionFlags;
    /* 06EA */ unsigned char field_6EA;
    /* 06EB */ BOOLEAN m_bSessionOptionsDefined;
    /* 06EC */ CString m_sJoinedGame;
    /* 06F0 */ CString m_sDroppedGame;
    /* 06F4 */ CString m_sLeftGame;
    /* 06F8 */ BOOLEAN m_bPlayerNameToMake;
    /* 06F9 */ BOOLEAN m_bPlayerCreated;
    /* 06FA */ PLAYER_ID m_idLocalPlayer;
    /* 06FE */ CString m_sLocalPlayerName;
    /* 0702 */ CString field_702[CNETWORK_MAX_PLAYERS];
    /* 071A */ BOOL field_71A[CNETWORK_MAX_PLAYERS];
    /* 0732 */ INT m_nTotalPlayers;
    /* 0736 */ CString m_psPlayerName[CNETWORK_MAX_PLAYERS];
    /* 074E */ PLAYER_ID m_pPlayerID[CNETWORK_MAX_PLAYERS];
    /* 0766 */ BOOLEAN m_pbPlayerVisible[CNETWORK_MAX_PLAYERS];
    /* 076C */ BOOLEAN m_pbPlayerEnumerateFlag[CNETWORK_MAX_PLAYERS];
    /* 0772 */ PLAYER_ID field_772[CNETWORK_MAX_PLAYERS];
    /* 078A */ int m_nLocalPlayer;
    /* 078E */ int m_nHostPlayer;
    /* 0792 */ CString field_792;
    /* 0796 */ int field_796;
    /* 079A */ CNetworkWindow m_pSlidingWindow[CNETWORK_MAX_PLAYERS];
    /* 0ACA */ CNetworkWindow m_SystemWindow;
    /* 0B52 */ DWORD m_dwCRC32[256];
    /* 0F52 */ CRITICAL_SECTION field_F52;
    /* 0F6A */ CRITICAL_SECTION field_F6A;

#if DPLAY_COMPAT
    typedef HRESULT(WINAPI DirectPlayCreateFunc)(LPGUID, LPDIRECTPLAY*, IUnknown*);
    typedef HRESULT(WINAPI DirectPlayLobbyCreateFunc)(LPGUID, LPDIRECTPLAYLOBBYA*, IUnknown*, LPVOID, DWORD);

    HMODULE hDirectPlayDLL;
    DirectPlayCreateFunc* DirectPlayCreate;
    DirectPlayLobbyCreateFunc* DirectPlayLobbyCreateA;

    void InitDirectPlay();
    void FreeDirectPlay();
#endif
};

#endif /* CNETWORK_H_ */

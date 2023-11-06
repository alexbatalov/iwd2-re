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

#define CNETWORK_MAX_SERVICE_PROVIDERS 5
#define CNETWORK_MAX_SESSIONS 64
#define CNETWORK_MAX_PLAYERS 6

// NOTE: Seen in `CNetwork::SendMessage` assertion.
#define STATIC_MESSAGE_SIZE 0x8000

typedef DWORD PLAYER_ID;

typedef struct cnetworkwindow_queueentry_st {
    PLAYER_ID idFrom;
    PLAYER_ID idTo;
    BYTE* pData;
    DWORD dwSize;
} CNETWORKWINDOW_QUEUEENTRY;

class CNetworkWindow {
public:
    static const DWORD DEFAULT_PACKET_TIMEOUT;
    static const DWORD DEFAULT_SENDPACKET_TIMEOUT;
    static const DWORD DEFAULT_PLAYER_TIMEOUT;
    static const DWORD MAX_TIMEOUT_TICK_COUNT;

    CNetworkWindow();
    ~CNetworkWindow();
    void AddToIncomingQueue(PLAYER_ID idFrom, PLAYER_ID idTo, BYTE* pData, DWORD dwDataSize);
    BOOLEAN CheckIncomingQueue();
    BOOLEAN CheckIncomingQueueSpecific(BYTE nSpecMsgType, BYTE nSpecMsgSubType);
    BOOLEAN CheckOutgoingQueueForAppendableMsgs(DWORD dwSize);
    void FrameSend(BYTE nFrameKind, WORD nFrameNumber);
    void Initialize(INT nIndex);
    void ShutDown();
    void RemoveFromAllQueues();
    BYTE* RemoveFromIncomingQueue(PLAYER_ID& idDPFrom, PLAYER_ID& idDPTo, DWORD& dwDataSize, BOOLEAN& bCompressed);
    BYTE* RemoveFromIncomingQueueSpecific(BYTE nSpecMsgType, BYTE nSpecMsgSubType, PLAYER_ID& idDPFrom, PLAYER_ID& idDPTo, DWORD& dwDataSize, BOOLEAN& bCompressed);
    void SendCall();
    void ReceiveCall(BYTE* pData, DWORD dwSize);
    void TimeoutCall();

    void SetPlayerTimeout();
    void SetNoMessageTimeout();

    /* 0000 */ BOOLEAN m_bInitialized;
    /* 0001 */ BOOLEAN m_bVSSent;
    /* 0002 */ BOOLEAN m_bVSReceived;
    /* 0003 */ BYTE m_nPlayerNumber;
    /* 0004 */ WORD m_nAckExpected;
    /* 0006 */ WORD m_nNextFrameToSend;
    /* 0008 */ WORD m_nFrameExpected;
    /* 000A */ WORD m_nTooFar;
    /* 000C */ WORD m_nOldestFrame;
    /* 000E */ CNETWORKWINDOW_QUEUEENTRY m_pOutgoingBuffers[1];
    /* 001E */ CNETWORKWINDOW_QUEUEENTRY m_pIncomingBuffers[1];
    /* 002E */ CTypedPtrList<CPtrList, CNETWORKWINDOW_QUEUEENTRY*> m_lQueueIncomingMessages;
    /* 004A */ CTypedPtrList<CPtrList, CNETWORKWINDOW_QUEUEENTRY*> m_lQueueOutgoingMessages;
    /* 0066 */ BOOLEAN m_pbTimeOutSet[1];
    /* 0068 */ DWORD m_pnTimeOut[1];
    /* 006C */ BOOLEAN m_pbArrived[1];
    /* 006E */ WORD m_nNumBuffered;
    /* 0070 */ BOOLEAN m_bNoNak;
    /* 0072 */ DWORD m_nPacketTimeout;
    /* 0076 */ DWORD m_nAckTimer;
    /* 007A */ BOOLEAN m_bAckTimerSet;
    /* 007B */ BOOLEAN m_bSomethingHappened;
    /* 007C */ DWORD m_nNextEvent;
    /* 0080 */ DWORD m_nPlayerTimeout;
    /* 0084 */ DWORD m_nNoMessageTimeout;
};

class CNetwork {
public:
    static const CString MG;
    static const CString JM;
    static const CString JB;

    static const INT MAX_PLAYERS;
    static const INT MAX_SESSIONS;
    static const INT MAX_SERVICE_PROVIDERS;
    static const INT MAX_STRING_LENGTH;
    static const DWORD MAX_TIMEOUT_TICK_COUNT;

    static const INT SERV_PROV_TCP_IP;
    static const INT SERV_PROV_MODEM;
    static const INT SERV_PROV_SERIAL;
    static const INT SERV_PROV_IPX;
    static const INT SERV_PROV_NULL;

    static const INT SEND_ALL_PLAYERS;
    static const INT SEND_GUARANTEED;
    static const INT SEND_RAW;
    static const INT SEND_JOINING_PLAYERS;

    static const INT SPEC_MSG_HEADER_LENGTH;
    static const INT SPEC_MSG_FLAG;
    static const INT SPEC_MSG_TYPE;
    static const INT SPEC_MSG_SUBTYPE;
    static const BYTE SPEC_MSG_FLAG_ENABLED;
    static const DWORD MINIMAL_PACKET_SIZE;
    static const DWORD MAXIMAL_PACKET_SIZE;
    static const DWORD dword_85E68C;
    static const DWORD dword_85E690;
    static const DWORD dword_85E694;
    static const DWORD dword_85E698;
    static const DWORD dword_85E69C;
    static const DWORD dword_85E6A0;
    static const DWORD dword_85E6A4;

    static const INT ERROR_NONE;
    static const INT ERROR_PLAYEREXISTS;
    static const INT ERROR_CANNOTCREATEPLAYER;
    static const INT ERROR_CANNOTCONNECT;
    static const INT ERROR_INVALIDPASSWORD;

    static BYTE STATIC_MESSAGE_BUFFER[STATIC_MESSAGE_SIZE];
    static DWORD DYNAMIC_MESSAGE_SIZE;

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
    BOOLEAN KickPlayer(PLAYER_ID dpID, BOOLEAN bAIResponsible);
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
    INT ThreadLoop();
    void SlidingWindowReceive();
    void SlidingWindowTimeouts();
    BYTE* FetchFrame(PLAYER_ID& id, DWORD& dwSize);
    BOOLEAN HandleSystemMessage(BYTE* pData, DWORD dwSize);
    void AddMessageToWindow(PLAYER_ID idTo, DWORD dwFlags, BYTE* pData, DWORD dwSize);
    BYTE* CreateCopyMessage(const void* lpData, DWORD dwDataSize, BOOLEAN bCompressed, unsigned char a4, INT nFrame);
    BYTE* FetchMessage(INT& nMsgFrom, INT& nMsgTo, DWORD& dwSize);
    BYTE* FetchSpecificMessage(const CString& sPlayerName, BYTE nSpecMsgType, BYTE nSpecMsgSubType, DWORD& dwSize);
    BOOLEAN PeekMessage_();
    BOOLEAN PeekSpecificMessage(const CString& sPlayerName, BYTE nSpecMsgType, BYTE nSpecMsgSubType);
    BOOLEAN SendMessage_(const CString& sPlayerName, DWORD dwFlags, BYTE* pData, DWORD dwSize);
    BOOLEAN SendSpecificMessage(const CString& sPlayerName, DWORD dwFlags, BYTE nSpecMsgType, BYTE nSpecMsgSubType, LPVOID lpData, DWORD nDataSize);
    BYTE* UncompressMessage(BYTE* pData, DWORD& dwSize);

    INT GetServiceProvider();
    BOOLEAN GetSessionOpen();
    BOOLEAN GetSessionHosting();

    PLAYER_ID GetHostPlayerID();
    void GetHostPlayerName(CString& sHostName);

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

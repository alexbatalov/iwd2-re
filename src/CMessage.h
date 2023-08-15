#ifndef CMESSAGE_H_
#define CMESSAGE_H_

#include "mfc.h"

#include "CChatBuffer.h"
#include "CResRef.h"

class CBaldurMessage {
public:
    static const BYTE MSG_TYPE_CMESSAGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_RELEASE;

    static const BYTE DELETEAREA_EMPTY_VOTE;
    static const BYTE SIGNAL_SERVER;
    static const BYTE SIGNAL_END_MAJOR_EVENT;
    static const DWORD SIGNAL_SECONDSTOMPTIMEOUT;

    CBaldurMessage();
    ~CBaldurMessage();
    BOOL SendFullSettingsToClients(const CString& sPlayerName);
    BOOL SendCharacterReadyToServer(INT nCharacterSlot, BOOLEAN bReady);
    BOOL SendImportingOptionToServer(BYTE nImportingBitField);
    BOOL SendRestrictStoreOptionToServer(BOOLEAN bRestrictStore);
    BOOL SendJoinRequestOptionToServer(BOOLEAN bListenToJoin);
    BOOLEAN SendCharacterSlotStatusToServer(SHORT nCharacterSlot, BYTE nStatus);
    BOOLEAN SendArbitrationLockRequestToServer(BOOLEAN bLockValue);
    BOOL SendArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2);
    BOOL SendArbitrationLockAllowInput(BOOLEAN bAllowInput);
    BOOLEAN KickPlayerRequest(const CString& sPlayerName);
    void UpdateDemandCharacters(unsigned char a1, int a2, unsigned char a3);
    BOOLEAN DemandCharacterSlot(SHORT nCharacterSlot, BOOLEAN bDemandFromHost, SHORT nPlayerSlot);
    BOOL ObjectControlRequest(LONG localObjectID);
    BOOL ObjectControl();
    BOOLEAN SendChatMessage(CString& sChatMessage);
    void SetSignalDefaultSecondsToTimeout();
    BOOLEAN SendSignal(BYTE signalType, BYTE signalToSend);
    BOOLEAN SendProgressBarStatus(LONG nActionProgress, LONG nActionTarget, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bTimeoutVisible, DWORD nSecondsToTimeout);
    BOOLEAN ChapterAnnounceStatus(BYTE nChapter, CResRef cResRef);
    void WeatherBroadcast(WORD wWeatherFlags);
    void TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime);
    void TimeChangeToServer(ULONG deltaTime);
    BOOLEAN DemandSettingsNightmareMode(BOOLEAN wait);
    BOOL sub_43E0E0(DWORD a1, DWORD a2, COLORREF a3, COLORREF a4, int a5, int a6, int a7);
    CString GetVersionControlShutdownServerString();
    CString GetVersionControlShutdownClientString();

    /* 0000 */ unsigned char field_0;
    /* 0001 */ unsigned char field_1;
    /* 0002 */ unsigned char field_2;
    /* 0003 */ unsigned char field_3;
    /* 0004 */ unsigned char field_4;
    /* 0005 */ unsigned char field_5;
    /* 0006 */ unsigned char field_6;
    /* 0007 */ BOOLEAN m_bPlayerShutdown;
    /* 0008 */ CChatBuffer m_cChatBuffer;
    /* 0028 */ BYTE m_nSignalQueueSize;
    /* 0029 */ unsigned char field_29;
    /* 002A */ unsigned char field_2A;
    /* 002B */ unsigned char field_2B[24];
    /* 0043 */ unsigned char field_43[24];
    /* 005B */ unsigned char field_5B[24];
    /* 0073 */ unsigned char field_73;
    /* 0074 */ CString field_74;
    /* 0078 */ int field_78;
    /* 007C */ unsigned char field_7C[6];
    /* 0082 */ int field_82[6];
    /* 009A */ CCriticalSection field_9A;
    /* 00BA */ int field_BA[6];
    /* 00D2 */ unsigned char field_D2;
    /* 00D3 */ unsigned char field_D3;
    /* 00D4 */ unsigned char field_D4;
    /* 00D5 */ unsigned char field_D5;
    /* 00D6 */ int field_D6;
    /* 00DA */ unsigned char field_DA;
    /* 00DB */ unsigned char field_DB;
    /* 00DC */ unsigned char field_DC;
    /* 00DD */ unsigned char field_DD;
    /* 00DE */ unsigned char field_DE;
    /* 00DF */ unsigned char field_DF;
    /* 00E0 */ unsigned char field_E0;
    /* 00E1 */ unsigned char field_E1;
    /* 00E2 */ unsigned char field_E2;
    /* 00E3 */ unsigned char field_E3;
    /* 00E4 */ unsigned char field_E4;
    /* 00E5 */ unsigned char field_E5;
    /* 00E6 */ CString m_sVersionControlShutdownClientString;
    /* 00EA */ CString m_sVersionControlShutdownServerString;
    /* 00EE */ BYTE m_nVersionControlShutdownReason;
    /* 00F0 */ DWORD m_dwSignalSecondsToTimeout;
    /* 00F4 */ BOOLEAN m_bMultiplayerSessionShutdown;
    /* 00F5 */ unsigned char field_F5;
    /* 00F6 */ unsigned char field_F6;
};

class CMessage {
public:
    static const SHORT BROADCAST_FORCED;

    CMessage(LONG caller, LONG target);
    /* 0000 */ virtual ~CMessage();
    /* 0004 */ virtual SHORT GetCommType();
    /* 0008 */ virtual BYTE GetMsgType();
    /* 000C */ virtual BYTE GetMsgSubType();
    /* 0010 */ virtual void MarshalMessage(BYTE** pData, DWORD* dwSize);
    /* 0014 */ virtual BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize);
    /* 0018 */ virtual void Run();

    LONG GetTarget() { return m_targetId; }
    LONG GetSource() { return m_sourceId; }

    /* 0004 */ LONG m_targetId;
    /* 0008 */ LONG m_sourceId;
};

class CMessageHandler {
public:
    CMessageHandler();
    ~CMessageHandler();
    void AsynchronousUpdate();
    void PostAsynchronousUpdate();
    void AddMessage(CMessage* message, BOOL bForcePassThrough);

    /* 001C */ BOOLEAN m_bLastArbitrationLockStatus;
};

class CMessageStoreRelease : public CMessage {
public:
    CMessageStoreRelease(const CResRef& store, LONG caller, LONG target);
    /* 0004 */ SHORT GetCommType() override;
    /* 0008 */ BYTE GetMsgType() override;
    /* 000C */ BYTE GetMsgSubType() override;

    CResRef m_store;
};

#endif /* CMESSAGE_H_ */

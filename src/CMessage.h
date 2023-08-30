#ifndef CMESSAGE_H_
#define CMESSAGE_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "CAIAction.h"
#include "CChatBuffer.h"
#include "CColorEffects.h"
#include "CResRef.h"

// TODO: Reuse from `CNetwork.h`.
typedef DWORD PLAYER_ID;

class CGameEffect;

class CBaldurMessage {
public:
    static const BYTE MSG_TYPE_CMESSAGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ADD_ACTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ADD_EFFECT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CHANGE_DIRECTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_ACTIONS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_DIALOG_ACTIONS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_GROUP_SLOT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_TRIGGERS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_CHANGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_RESET;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_UPDATE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_RELEASE;

    static const BYTE DELETEAREA_EMPTY_VOTE;
    static const BYTE SIGNAL_SERVER;
    static const BYTE SIGNAL_END_MAJOR_EVENT;
    static const BYTE SIGNAL_END_GAME;
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
    BOOLEAN RequestClientSignal(BYTE signalToSend);
    BOOLEAN SendSignal(BYTE signalType, BYTE signalToSend);
    BOOLEAN NonBlockingWaitForSignal(BYTE signalType, BYTE signalToWaitFor);
    BOOLEAN SendProgressBarStatus(LONG nActionProgress, LONG nActionTarget, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bTimeoutVisible, DWORD nSecondsToTimeout);
    BOOLEAN ChapterAnnounceStatus(BYTE nChapter, CResRef cResRef);
    BOOLEAN SendMapWorldAnnounceStatus(BOOLEAN bActive, PLAYER_ID idController, LONG nLeavingEdge);
    BOOLEAN MovieAnnounceStatus(CResRef cResMovie);
    BOOLEAN SendReformPartyAnnounceStatus();
    void WeatherBroadcast(WORD wWeatherFlags);
    void TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime);
    void TimeChangeToServer(ULONG deltaTime);
    BOOLEAN DemandSettingsNightmareMode(BOOLEAN wait);
    BOOL DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, LONG caller, LONG target);
    BOOL sub_43E0E0(DWORD a1, DWORD a2, COLORREF a3, COLORREF a4, int a5, int a6, int a7);
    CString GetVersionControlShutdownServerString();
    CString GetVersionControlShutdownClientString();
    BOOLEAN GetDialogRequestPending();
    BOOLEAN GetDialogReplyReturned();
    INT GetDialogReplyUpdates();
    void SetDialogReplyUpdates(INT bValue);

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
    /* 00D3 */ BOOLEAN m_bDialogRequestPending;
    /* 00D4 */ BOOLEAN m_bDialogReplyReturned;
    /* 00D5 */ unsigned char field_D5;
    /* 00D6 */ INT m_nDialogReplyUpdates;
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
    static const SHORT SEND;
    static const SHORT BROADCAST;
    static const SHORT BROADCAST_OTHERS;
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

class CMessageAddAction : public CMessage {
public:
    CMessageAddAction(const CAIAction& action, LONG caller, LONG target);
    ~CMessageAddAction() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAIAction m_action;
};

class CMessageAddEffect : public CMessage {
public:
    CMessageAddEffect(CGameEffect* effect, LONG caller, LONG target);
    ~CMessageAddEffect() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CGameEffect* m_effect;
};

class CMessageChangeDirection : public CMessage {
public:
    CMessageChangeDirection(SHORT face, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ SHORT m_face;
};

class CMessageClearActions : public CMessage {
public:
    CMessageClearActions(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;
};

class CMessageClearDialogActions : public CMessage {
public:
    CMessageClearDialogActions(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;
};

class CMessageClearGroupSlot : public CMessage {
public:
    CMessageClearGroupSlot(SHORT slotNum, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ SHORT m_slotNum;
};

class CMessageClearTriggers : public CMessage {
public:
    CMessageClearTriggers(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;
};

class CMessageColorChange : public CMessage {
public:
    CMessageColorChange(BYTE* colors, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ BYTE m_colors[7];
};

class CMessageColorReset : public CMessage {
public:
    CMessageColorReset(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;
};

class CMessageColorUpdate : public CMessage {
public:
    CMessageColorUpdate(CGameSprite* pSprite, LONG caller, LONG target);
    ~CMessageColorUpdate() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CColorRanges m_appliedColorRanges;
    /* */ CColorEffects m_appliedColorEffects;
};

class CMessageCutSceneModeStatus : public CMessage {
public:
    CMessageCutSceneModeStatus(BOOLEAN mode, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ BOOLEAN m_cutSceneMode;
};

class CMessageDisplayText : public CMessage {
public:
    CMessageDisplayText(const CString& name, const CString& text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target);
    ~CMessageDisplayText() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CString m_name;
    /* 0010 */ CString m_text;
    /* 0014 */ COLORREF m_nameColor;
    /* 0018 */ COLORREF m_textColor;
    /* 001C */ LONG m_marker;
    /* 0020 */ BOOLEAN m_moveToTop;
};

class CMessageDisplayTextRef : public CMessage {
public:
    CMessageDisplayTextRef(STRREF name, STRREF text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ STRREF m_name;
    /* 0010 */ STRREF m_text;
    /* 0014 */ COLORREF m_nameColor;
    /* 0018 */ COLORREF m_textColor;
    /* 001C */ LONG m_marker;
    /* 0020 */ BOOLEAN m_moveToTop;
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

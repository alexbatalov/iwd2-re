#ifndef CMESSAGE_H_
#define CMESSAGE_H_

#include "mfc.h"

#include <bitset>

#include "BalDataTypes.h"
#include "CAIAction.h"
#include "CAITrigger.h"
#include "CChatBuffer.h"
#include "CColorEffects.h"
#include "CGameSpriteEquipment.h"
#include "CImmunities.h"
#include "CItem.h"
#include "CResRef.h"
#include "FileFormat.h"

// TODO: Reuse from `CNetwork.h`.
typedef DWORD PLAYER_ID;

class CGameArea;
class CGameContainer;
class CGameDoor;
class CGameEffect;

class CBaldurMessage {
public:
    static const BYTE MSG_TYPE_PROGRESSBAR;
    static const BYTE MSG_SUBTYPE_PROGRESSBAR_STATUS;

    static const BYTE MSG_TYPE_CMESSAGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ADD_ACTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ADD_EFFECT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ANIMATION_CHANGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CHANGE_DIRECTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_ACTIONS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_DIALOG_ACTIONS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_GROUP_SLOT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CLEAR_TRIGGERS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_CHANGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_RESET;
    static const BYTE MSG_SUBTYPE_CMESSAGE_COLOR_UPDATE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CONTAINER_ADD_ITEM;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CONTAINER_ITEMS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CONTAINER_STATUS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DOOR_STATUS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DROP_PATH;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ENTER_DIALOG;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ENTER_STORE_MODE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_EXIT_DIALOG_MODE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_EXIT_STORE_MODE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_FIRE_PROJECTILE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_INSERT_ACTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_LEAVE_PARTY;
    static const BYTE MSG_SUBTYPE_CMESSAGE_PARTY_GOLD;
    static const BYTE MSG_SUBTYPE_CMESSAGE_PLAY_SOUND;
    static const BYTE MSG_SUBTYPE_CMESSAGE_PLAY_SOUND_REF;
    static const BYTE MSG_SUBTYPE_CMESSAGE_REMOVE_REPLIES;
    static const BYTE MSG_SUBTYPE_CMESSAGE_REPUTATION_CHANGE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_ACTIVE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_AISPEED;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_COMMAND_PAUSE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_DIALOG_WAIT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_DIRECTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_DRAW_POLY;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_FORCE_ACTION_PICK;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_HAPPINESS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_IN_CUT_SCENE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_LAST_ATTACKER;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_LAST_OBJECT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_NUM_TIMES_TALKED_TO;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_PATH;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_SEQUENCE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_TRIGGER;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPRITE_DEATH;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPRITE_EQUIPMENT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPRITE_PETRIFY;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPRITE_UPDATE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_START_FOLLOW;
    static const BYTE MSG_SUBTYPE_CMESSAGE_START_SCROLL;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STOP_ACTIONS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STOP_FOLLOW;
    static const BYTE MSG_SUBTYPE_CMESSAGE_TRIGGER_STATUS;
    static const BYTE MSG_SUBTYPE_CMESSAGE_UNLOCK;
    static const BYTE MSG_SUBTYPE_CMESSAGE_UPDATE_REACTION;
    static const BYTE MSG_SUBTYPE_CMESSAGE_VERBAL_CONSTANT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_VISIBILITY_MAP_MOVE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_VISUAL_EFFECT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_DIALOG_RESREF;
    static const BYTE MSG_SUBTYPE_CMESSAGE_ESCAPE_AREA;
    static const BYTE MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF_SEND;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_CURRENT_ACTION_ID;
    static const BYTE MSG_SUBTYPE_CMESSAGE_MOVE_GLOBAL;
    static const BYTE MSG_SUBTYPE_CMESSAGE_FADE_COLOR;
    static const BYTE MSG_SUBTYPE_CMESSAGE_START_TEXT_SCREEN;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPAWNPT_ACTIVATE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SPAWNPT_SPAWN;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STATIC_START;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_ADD_ITEM;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_REMOVE_ITEM;
    static const BYTE MSG_SUBTYPE_CMESSAGE_FAMILIAR_ADD;
    static const BYTE MSG_SUBTYPE_CMESSAGE_FAMILIAR_REMOVE_RESREF;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STOP_ESCAPE_AREA;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_TIME_STOP;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_RELEASE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_90;
    static const BYTE MSG_SUBTYPE_CMESSAGE_FLOAT_TEXT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_92;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_PROTAGONIST;
    static const BYTE MSG_SUBTYPE_CMESSAGE_START_COMBAT_MUSIC;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SCREENSHAKE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_STORE_DEMAND;
    static const BYTE MSG_SUBTYPE_CMESSAGE_WEAPON_IMMUNITIES_UPDATE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_101;
    static const BYTE MSG_SUBTYPE_CMESSAGE_103;
    static const BYTE MSG_SUBTYPE_CMESSAGE_TOGGLE_INTERFACE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_107;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_AREA_TYPE;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_AREA_REST_ENCOUNTER;
    static const BYTE MSG_SUBTYPE_CMESSAGE_SET_AREA_EXPLORED;
    static const BYTE MSG_SUBTYPE_CMESSAGE_CHANGE_STAT;
    static const BYTE MSG_SUBTYPE_CMESSAGE_120;
    static const BYTE MSG_SUBTYPE_CMESSAGE_END_GAME;

    static const BYTE MSG_TYPE_DIALOG;
    static const BYTE MSG_SUBTYPE_DIALOG_PERMIT_REQUEST;
    static const BYTE MSG_SUBTYPE_DIALOG_PERMIT_REPLY;
    static const BYTE MSG_SUBTYPE_DIALOG_CANCEL_REQUEST;
    static const BYTE MSG_SUBTYPE_DIALOG_KILL_OR_USE;
    static const BYTE DIALOG_REQUESTPENDING;
    static const BYTE DIALOG_NOT_PERMITTED;

    static const BYTE MSG_TYPE_SWAPITEM;
    static const BYTE MSG_SUBTYPE_SWAPITEM_REQUEST;
    static const BYTE MSG_SUBTYPE_SWAPITEM_REPLY;

    static const BYTE MSG_TYPE_JOURNAL;
    static const BYTE MSG_SUBTYPE_JOURNAL_ADD_ENTRY;
    static const BYTE MSG_SUBTYPE_JOURNAL_ANNOUNCE;
    static const BYTE MSG_SUBTYPE_JOURNAL_ADD_USER_ENTRY;
    static const BYTE MSG_SUBTYPE_JOURNAL_ANNOUNCE_USER_ENTRY;
    static const BYTE MSG_SUBTYPE_JOURNAL_CHANGE_ENTRY;
    static const BYTE MSG_SUBTYPE_JOURNAL_ANNOUNCE_CHANGE;

    static const BYTE MSG_TYPE_BIOGRAPHY;
    static const BYTE MSG_SUBTYPE_BIOGRAPHY_CHANGE;
    static const BYTE MSG_SUBTYPE_BIOGRAPHY_CHANGE_ANNOUNCE;

    static const BYTE MSG_TYPE_KICK_PLAYER;
    static const BYTE MSG_SUBTYPE_KICK_PLAYER_REQUEST;
    static const BYTE MSG_SUBTYPE_KICK_PLAYER_SERVER_SUPPORT;
    static const BYTE MSG_SUBTYPE_KICK_PLAYER_HOOFED_OUT;

    static const BYTE DELETEAREA_EMPTY_VOTE;
    static const BYTE DELETEAREA_PENDING_VOTE;
    static const BYTE DELETEAREA_YES_VOTE;
    static const BYTE DELETEAREA_NO_VOTE;

    static const BYTE MSG_TYPE_MPSETTINGS;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_FULLDEMAND;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_FULLSET;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_PERMISSION;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_PLAYER_READY;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_CHAR_READY;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_CHAR_CONTROL;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_IMPORTING;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_LISTEN_JOIN;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_SLOT_STATUS;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_LOCK_STATUS;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_LOCK_ALLOW_INPUT;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_LOCK_REQUEST;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_GORE_LEVEL;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_RESTRICT_STORE;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_NIGHTMAREMODE;
    static const BYTE MSG_SUBTYPE_MPSETTINGS_DEMAND_NIGHTMAREMODE;

    static const BYTE MSG_TYPE_OBJECT;
    static const BYTE MSG_SUBTYPE_OBJECT_ADD;

    static const BYTE MSG_TYPE_PLAYERCHAR;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_UPDATE_DEMAND;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_UPDATE_REPLY;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_DEMAND_SLOT;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_DEMAND_REPLY;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_70;
    static const BYTE MSG_SUBTYPE_PLAYERCHAR_102;

    static const BYTE MSG_TYPE_PAUSING;
    static const BYTE MSG_SUBTYPE_PAUSING_PERMIT_REQUEST;
    static const BYTE MSG_SUBTYPE_PAUSING_ANNOUNCE;

    static const BYTE MSG_TYPE_RESOURCE;
    static const BYTE MSG_SUBTYPE_RESOURCE_DEMAND;

    static const BYTE MSG_TYPE_SIGNAL;
    static const BYTE MSG_SUBTYPE_SIGNAL;
    static const BYTE MSG_SUBTYPE_SIGNAL_REQUEST;
    static const BYTE SIGNAL_ALL_CLIENTS;
    static const BYTE SIGNAL_SERVER;
    static const BYTE SIGNAL_END_MAJOR_EVENT;
    static const BYTE SIGNAL_END_GAME;
    static const BYTE SIGNAL_MPSYNCH;
    static const DWORD SIGNAL_SECONDSTOMPTIMEOUT;

    static const BYTE MSG_TYPE_MPSYNCH;
    static const BYTE MSG_SUBTYPE_MPSYNCH_REQUEST;
    static const BYTE MSG_SUBTYPE_MPSYNCH_REPLY;

    static const BYTE MSG_TYPE_VERSION;
    static const BYTE MSG_SUBTYPE_VERSION_SERVER;
    static const BYTE VERSION_NUM_FIELDS;

    static const BYTE MSG_TYPE_LEAVEAREALUA;
    static const BYTE MSG_SUBTYPE_LEAVEAREALUA_PERMIT_REQUEST;

    static const BYTE MSG_TYPE_LEAVEAREANAME;
    static const BYTE MSG_SUBTYPE_LEAVEAREANAME_PERMIT_REQUEST;

    CBaldurMessage();
    ~CBaldurMessage();
    BOOLEAN DemandResourceFromServer(const CString& sResName, UINT nType, BOOLEAN bSendMessage, BOOLEAN bWaitForMessage, BOOLEAN bSaveToTemp);
    BOOLEAN OnResourceDemanded(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN ResourceSuggestLoad(const CString& sResName, UINT nType, DWORD dwFlags);
    BOOL OnSettingsFullDemanded(INT nMsgFrom);
    BOOL SendFullSettingsToClients(const CString& sPlayerName);
    BOOL OnSettingsFullSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendPermissionToServer(const CString& sPlayerName, INT nPermission, BOOLEAN bValue);
    BOOL OnSettingsPermissionSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendPlayerReadyToServer(PLAYER_ID idPlayer, BOOLEAN bValue);
    BOOLEAN OnSettingsPlayerReadySet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendCharacterControlToServer(CString& sPlayerName, INT nCharacterSlot, BOOLEAN bFlush, BOOLEAN bCharacterUpdate);
    BOOL OnSettingsCharacterControlSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendCharacterReadyToServer(INT nCharacterSlot, BOOLEAN bCharacterReady);
    BOOL OnSettingsCharacterReadySet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendGoreRequirementToServer(DWORD nGore, DWORD nGoreOption);
    BOOL OnSettingsGoreRequirement(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendImportingOptionToServer(BYTE nImportingBitField);
    BOOL OnSettingsImportingOptionSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendRestrictStoreOptionToServer(BOOLEAN bRestrictStore);
    BOOL OnSettingsRestrictStoreOptionSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL SendJoinRequestOptionToServer(BOOLEAN bListenToJoin);
    BOOL OnSettingsJoinRequestOptionSet(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendCharacterSlotStatusToServer(SHORT nCharacterSlot, BYTE nStatus);
    BOOLEAN OnSettingsCharacterSlotStatus(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendArbitrationLockRequestToServer(BOOLEAN bLockValue);
    BOOLEAN OnSettingsArbitrationLockRequest(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2);
    BOOLEAN OnSettingsArbitrationLockStatus(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendArbitrationLockAllowInput(BOOLEAN bAllowInput);
    BOOLEAN OnSettingsArbitrationLockAllowInput(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN KickPlayerRequest(const CString& sPlayerName);
    BOOL OnKickPlayerRequest(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    void KickPlayerServerSupport(const CString& sPlayerName);
    BOOLEAN OnKickPlayerServerSupport(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL OnKickPlayerHoofedOut(INT nMsgFrom);
    BOOL AddDroppedPlayer(PLAYER_ID playerID);
    BOOL PurgeDroppedPlayers();
    void UpdateDemandCharacters(unsigned char a1, int a2, unsigned char a3);
    void BroadcastUpdateCharacterSlot(BOOLEAN bUpdateAllCharacters, INT nUpdatedCharacterSlot, BOOLEAN bProgressBarInPlace);
    BOOLEAN OnUpdateDemandCharacterSlot(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN DemandCharacterSlot(SHORT nCharacterSlot, BOOLEAN bDemandFromHost, SHORT nPlayerSlot);
    BOOLEAN OnDemandCharacterSlot(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN BroadcastDemandCharacterSlotReply(BOOLEAN bUpdateAllCharacters, INT nUpdatedCharacterSlot, BOOLEAN bProgressBarInPlace);
    BOOLEAN DemandCharacterSlotReply(CString& sSendTo, SHORT nCharacterSlot, BOOLEAN bSendCharInfo);
    BOOLEAN OnDemandCharacterSlotReply(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOL ObjectAdd(LONG localObjectID, BYTE nObjectType, BYTE* pObjectData, DWORD dwObjectDataSize);
    BOOL ObjectControlSuggestion(PLAYER_ID playerToSuggestID, LONG localObjectID);
    BOOL ObjectControlRequest(LONG localObjectID);
    BOOL ObjectControl();
    BOOLEAN OnSwapItemRequest(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendChatMessage(CString& sChatMessage);
    BOOLEAN OnChatMessage(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    void SetSignalDefaultSecondsToTimeout();
    BOOLEAN RequestClientSignal(BYTE signalToSend);
    BOOLEAN OnRequestClientSignal(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN RemoveSignalsFromQueue(BYTE signalType, BYTE signalData);
    BOOLEAN SendSignal(BYTE signalType, BYTE signalToSend);
    BOOLEAN OnSignal(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN NonBlockingWaitForSignal(BYTE signalType, BYTE signalToWaitFor);
    BYTE KickOutWaitingForSignal(BYTE signalType, BYTE signalToWaitFor);
    BOOLEAN WaitForSignal(BYTE signalType, BYTE signalToWaitFor);
    BOOLEAN SendProgressBarStatus(LONG nActionProgress, LONG nActionTarget, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bTimeoutVisible, DWORD nSecondsToTimeout);
    BOOLEAN OnProgressBarStatus(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendDialogRequestToServer(BOOLEAN bTestPermission);
    BOOLEAN OnDialogRequestToServer(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN OnDialogReplyFromServer(BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN DialogRequestKillOrUse();
    BOOLEAN OnDialogRequestKillOrUse(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN CancelDialogRequestToServer();
    BOOLEAN OnCancelDialogRequestToServer(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN SendPauseRequestToServer(BOOLEAN bVisualPause, BOOLEAN bPauseToBeSetTo);
    BOOLEAN OnPauseRequestToServer(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN PauseAnnounceStatus(BOOLEAN bHardPauseStatus, BOOLEAN bPauseStatus, PLAYER_ID idPauser);
    BOOLEAN OnPauseAnnounceStatus(INT nMsgFrom, BYTE* pMessage, DWORD dwSize);
    BOOLEAN ChapterAnnounceStatus(BYTE nChapter, CResRef cResRef);
    BOOLEAN SendMapWorldCancelRequestToServer();
    BOOLEAN SendMapWorldAnnounceStatus(BOOLEAN bActive, PLAYER_ID idController, LONG nLeavingEdge);
    BOOLEAN SendMapWorldRevealArea(CString sAreaResRef);
    BOOLEAN SendMovieRequestToServer(CResRef cResMovie);
    BOOLEAN MovieAnnounceStatus(CResRef cResMovie);
    BOOLEAN SendReformPartyAnnounceStatus();
    void WeatherBroadcast(WORD wWeatherFlags);
    void TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime);
    void TimeChangeToServer(ULONG deltaTime);
    BOOLEAN OnLeaveAreaLuaRequestToServer(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN OnLeaveAreaNameRequestToServer(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    void CleanLeaveAreaLuaRequest();
    void CleanLeaveAreaNameRequest();
    BOOLEAN SendJournalEntryToServer(STRREF strText, INT nChapter, LONG nTime);
    BOOLEAN OnSendJournalEntry(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN AnnounceJournalEntry(STRREF strText, INT nChapter, LONG nTime);
    BOOLEAN OnAnnounceJournalEntry(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN SendJournalUserEntry(CString szText, BYTE nCharacter, INT nChapter, LONG nTime, DWORD nIndex);
    BOOLEAN OnSendJournalUserEntry(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN AnnounceJournalUserEntry(CString szText, BYTE nCharacter, INT nChapter, LONG nTime, DWORD nIndex);
    BOOLEAN OnAnnounceJournalUserEntry(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN SendJournalEntryChangeToServer(CString szText, BYTE nCharacter, INT nChapter, DWORD nIndex);
    BOOLEAN OnSendEntryJournalChange(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN AnnounceJournalEntryChange(CString szText, BYTE nCharacter, INT nChapter, DWORD nIndex);
    BOOLEAN OnAnnounceJournalEntryChange(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN SendBiographyToServer(BYTE nFixedPartyId, CString szBio);
    BOOLEAN OnSendBiography(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN AnnounceBiography(BYTE nFixedPartyId, CString szBio);
    BOOLEAN OnAnnounceBiography(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    void SetDeleteAreaString(CString sAreaString);
    CString GetDeleteAreaString();
    BOOLEAN CancelDeleteAreaPoll();
    BOOLEAN DeleteAreaBallotResult();
    BOOLEAN MultiplayerSynchRequest();
    BOOLEAN OnMultiplayerSynchRequest(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN MultiplayerSynchReply();
    BOOLEAN OnMultiplayerSynchReply(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN VersionServer(CString sPlayerName);
    BOOLEAN OnVersionServer(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    void SetVersionControlShutdownServerString(CString sValue);
    void SetVersionControlShutdownClientString(CString sValue);
    BYTE* PollSpecificMessageType(BYTE nMsgType, BYTE nMsgSubType, INT& nMsgFrom, DWORD& dwSize);
    void HandleBlockingMessages();
    BOOLEAN GetGameSpyQueryBasic(CString& sResponse);
    BOOLEAN GetGameSpyQueryInfo(CString& sResponse);
    BOOLEAN GetGameSpyQueryRules(CString& sResponse);
    BOOLEAN GetGameSpyQueryPlayers(CString& sResponse);
    void GameSpyRemoveBadCharacters(CString& sString);
    BOOL SendSettingsNightmareMode(const CString& sPlayerName);
    BOOLEAN OnSettingsNightmareMode(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOLEAN DemandSettingsNightmareMode(BOOLEAN wait);
    BOOL OnDemandSettingsNightmareMode(INT nMsgFrom);
    BOOLEAN OnMovieEndCredits(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize);
    BOOL DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, LONG caller, LONG target);
    BOOL DisplayTextRef(STRREF name, STRREF text, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, LONG caller, LONG target);
    CString GetVersionControlShutdownServerString();
    CString GetVersionControlShutdownClientString();
    BOOLEAN GetDialogRequestPending();
    BOOLEAN GetDialogReplyReturned();
    INT GetDialogReplyUpdates();
    void SetDialogReplyUpdates(INT bValue);

    /* 0000 */ BOOLEAN m_bInOnObjectAdd;
    /* 0001 */ BOOLEAN m_bInOnObjectDelete;
    /* 0002 */ BOOLEAN m_bInOnRestAnnounce;
    /* 0003 */ BOOLEAN m_bInOnJournalAnnounce;
    /* 0004 */ BOOLEAN m_bInOnAreaMapNoteAnnounce;
    /* 0005 */ BOOLEAN m_bInOnAnnounceBiography;
    /* 0006 */ BOOLEAN m_bInHandleBlockingMessages;
    /* 0007 */ BOOLEAN m_bPlayerShutdown;
    /* 0008 */ CChatBuffer m_cChatBuffer;
    /* 0028 */ BYTE m_nSignalQueueSize;
    /* 0029 */ BYTE m_nSignalQueueStart;
    /* 002A */ BYTE m_nSignalQueueEnd;
    /* 002B */ BYTE m_pnSignalFrom[24];
    /* 0043 */ BYTE m_pnSignalType[24];
    /* 005B */ BYTE m_pnSignalData[24];
    /* 0073 */ BOOLEAN m_bDeleteAreaPolling;
    /* 0074 */ CString m_sDeleteAreaString;
    /* 0078 */ DWORD m_dwDeleteAreaTimeout;
    /* 007C */ BYTE m_pnDeleteAreaVotes[6];
    /* 0082 */ PLAYER_ID m_pnDeleteAreaVoters[6];
    /* 009A */ CCriticalSection field_9A;
    /* 00BA */ PLAYER_ID m_pRemovedPlayerID[6];
    /* 00D2 */ BOOLEAN m_bRemovedPlayerID;
    /* 00D3 */ BOOLEAN m_bDialogRequestPending;
    /* 00D4 */ BOOLEAN m_bDialogReplyReturned;
    /* 00D5 */ BOOLEAN m_bDialogReplyValue;
    /* 00D6 */ INT m_nDialogReplyUpdates;
    /* 00DA */ BOOLEAN m_bLeaveAreaLuaRequestPending;
    /* 00DB */ BOOLEAN m_bLeaveAreaLuaReplyReturned;
    /* 00DC */ BYTE m_nLeaveAreaLuaReplyValue;
    /* 00DD */ BOOLEAN m_bLeaveAreaNameRequestPending;
    /* 00DE */ BOOLEAN m_bLeaveAreaNameReplyReturned;
    /* 00DF */ BYTE m_nLeaveAreaNameReplyValue;
    /* 00E0 */ BOOLEAN m_bMultiplayerSynchClientPending;
    /* 00E1 */ BOOLEAN m_bMultiplayerSynchClientFinished;
    /* 00E2 */ BOOLEAN m_bMultiplayerSynchServerPending;
    /* 00E3 */ BOOLEAN m_bMultiplayerSynchServerFinished;
    /* 00E4 */ BOOLEAN m_nMultiplayerSynchClientLocation;
    /* 00E5 */ BOOLEAN m_bVersionControlShutdown;
    /* 00E6 */ CString m_sVersionControlShutdownClientString;
    /* 00EA */ CString m_sVersionControlShutdownServerString;
    /* 00EE */ BYTE m_nVersionControlShutdownReason;
    /* 00F0 */ DWORD m_dwSignalSecondsToTimeout;
    /* 00F4 */ BOOLEAN m_bMultiplayerSessionShutdown;
    /* 00F5 */ BOOLEAN m_bInReputationChange;
    /* 00F6 */ BOOLEAN m_bInMessageSetDrawPoly;
};

class CMessage {
public:
    static const SHORT SEND;
    static const SHORT BROADCAST;
    static const SHORT BROADCAST_OTHERS;
    static const SHORT BROADCAST_FORCED;
    static const SHORT BROADCAST_FORCED_OTHERS;

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
    BOOL ImportantMessage(BYTE* pData, DWORD dwSize);
    SHORT AddMessage(CMessage* message, BOOL bForcePassThrough);
    SHORT AddMessage(CMessage* message, BOOL bForcePassThrough, SHORT nCommType);
    SHORT Broadcast(CMessage* message, BOOLEAN bSendMessageToSelf, BOOLEAN bIgnoreObjectControl);
    SHORT Send(CMessage* message);

    /* 0000 */ CTypedPtrList<CPtrList, CMessage*> m_messageList;
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

class CMessageAnimationChange : public CMessage {
public:
    CMessageAnimationChange(WORD animationId, LONG caller, LONG target);
    ~CMessageAnimationChange() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ WORD m_animationId;
};

class CMessageChangeDirection : public CMessage {
public:
    CMessageChangeDirection(SHORT face, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_face;
};

class CMessageClearActions : public CMessage {
public:
    CMessageClearActions(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageClearDialogActions : public CMessage {
public:
    CMessageClearDialogActions(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageClearGroupSlot : public CMessage {
public:
    CMessageClearGroupSlot(SHORT slotNum, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_slotNum;
};

class CMessageClearTriggers : public CMessage {
public:
    CMessageClearTriggers(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageColorChange : public CMessage {
public:
    CMessageColorChange(BYTE* colors, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BYTE m_colors[7];
};

class CMessageColorReset : public CMessage {
public:
    CMessageColorReset(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageColorUpdate : public CMessage {
public:
    CMessageColorUpdate(CGameSprite* pSprite, LONG caller, LONG target);
    ~CMessageColorUpdate() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CColorRanges m_appliedColorRanges;
    /* 0028 */ CColorEffects m_appliedColorEffects;
};

class CMessageContainerAddItem : public CMessage {
public:
    CMessageContainerAddItem(const CItem&, SHORT slotNum, BOOLEAN bCompressContainer, LONG caller, LONG target);
    ~CMessageContainerAddItem() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CItem m_item;
    /* 00FA */ SHORT m_slotNum;
    /* 00FC */ BOOLEAN m_bCompressContainer;
};

class CMessageContainerItems : public CMessage {
public:
    CMessageContainerItems(CGameContainer* pContainer, LONG caller, LONG target);
    ~CMessageContainerItems() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ SHORT m_nItems;
    /* 000E */ CItem** m_pItems;
};

class CMessageContainerStatus : public CMessage {
public:
    CMessageContainerStatus(DWORD flags, WORD trapActivated, WORD trapDetected, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_dwFlags;
    /* 0010 */ WORD m_trapDetected;
    /* 0012 */ WORD m_trapActivated;
};

class CMessageCutSceneModeStatus : public CMessage {
public:
    CMessageCutSceneModeStatus(BOOLEAN mode, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
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
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ STRREF m_name;
    /* 0010 */ STRREF m_text;
    /* 0014 */ COLORREF m_nameColor;
    /* 0018 */ COLORREF m_textColor;
    /* 001C */ LONG m_marker;
    /* 0020 */ BOOLEAN m_moveToTop;
};

class CMessageDoorStatus : public CMessage {
public:
    CMessageDoorStatus(CGameDoor* pDoor, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_dwFlags;
    /* 0010 */ WORD m_trapDetected;
    /* 0012 */ WORD m_trapActivated;
    /* 0014 */ BOOLEAN m_bOpen;
};

class CMessageEnterDialog : public CMessage {
public:
    CMessageEnterDialog(DWORD entryNum, BOOLEAN a2, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_entryNum;
    /* 0010 */ BOOLEAN field_10;
};

class CMessageDropPath : public CMessage {
public:
    CMessageDropPath(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageEnterStoreMode : public CMessage {
public:
    CMessageEnterStoreMode(const CAIObjectType& cAIProprietor, const CAIObjectType& cAICustomer, const CResRef cResStore, LONG caller, LONG target);
    ~CMessageEnterStoreMode();
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAIObjectType m_cAIProprietor;
    /* 0048 */ CAIObjectType m_cAICustomer;
    /* 0084 */ CResRef m_cResStore;
};

class CMessageExitDialogMode : public CMessage {
public:
    CMessageExitDialogMode(BOOLEAN bButtonPushed, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bButtonPushed;
};

class CMessageExitStoreMode : public CMessage {
public:
    CMessageExitStoreMode(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageInsertAction : public CMessage {
public:
    CMessageInsertAction(const CAIAction& action, LONG caller, LONG target);
    ~CMessageInsertAction() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAIAction m_action;
};

class CMessageLeaveParty : public CMessage {
public:
    CMessageLeaveParty(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessagePartyGold : public CMessage {
public:
    CMessagePartyGold(BOOLEAN bFeedback, BOOLEAN bAdj, LONG gold, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_gold;
    /* 0010 */ BOOLEAN m_bAdjustment;
    /* 0011 */ BOOLEAN m_bFeedback;
};

class CMessagePlaySound : public CMessage {
public:
    CMessagePlaySound(BYTE soundId, BOOL text, BOOL circle, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOL m_showText;
    /* 0010 */ BOOL m_showCircle;
    /* 0014 */ BYTE m_soundId;
};

class CMessagePlaySoundRef : public CMessage {
public:
    CMessagePlaySoundRef(CResRef cResSound, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CResRef m_cResSound;
    /* 0014 */ BYTE m_nChannel;
    /* 0015 */ BOOLEAN m_bPositioned;
};

class CMessageRemoveReplies : public CMessage {
public:
    CMessageRemoveReplies(LONG entryIndex, LONG marker, COLORREF nameColor, const CString& name, LONG caller, LONG target);
    ~CMessageRemoveReplies() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CString m_name;
    /* 0010 */ LONG m_entryIndex;
    /* 0014 */ LONG m_marker;
    /* 0018 */ COLORREF m_nameColor;
};

class CMessageReputationChange : public CMessage {
public:
    CMessageReputationChange(SHORT deltaRep, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_deltaRep;
};

class CMessageScreenShake : public CMessage {
public:
    CMessageScreenShake(WORD duration, CHAR magnitudeX, CHAR magnitudeY, BOOLEAN bOverride, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ WORD m_duration;
    /* 000E */ CHAR m_magnitudeX;
    /* 000F */ CHAR m_magnitudeY;
    /* 0010 */ BOOLEAN m_bOverride;
};

class CMessageSetActive : public CMessage {
public:
    CMessageSetActive(BOOL active, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOL m_active;
};

class CMessageSetAISpeed : public CMessage {
public:
    CMessageSetAISpeed(BYTE speed, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BYTE m_nAISpeed;
};

class CMessageSetCommandPause : public CMessage {
public:
    CMessageSetCommandPause(SHORT pause, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_commandPause;
};

class CMessageSetDialogWait : public CMessage {
public:
    CMessageSetDialogWait(LONG wait, LONG waitTarget, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ LONG m_wait;
    /* 0010 */ LONG m_waitTarget;
};

class CMessageSetDirection : public CMessage {
public:
    CMessageSetDirection(CPoint face, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CPoint m_face;
};

class CMessageSetDrawPoly : public CMessage {
public:
    CMessageSetDrawPoly(SHORT time, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_time;
};

class CMessageSetForceActionPick : public CMessage {
public:
    CMessageSetForceActionPick(BOOLEAN forceActionPick, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_forceActionPick;
};

class CMessageSetHappiness : public CMessage {
public:
    CMessageSetHappiness(SHORT happiness, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_happiness;
};

class CMessageSetInCutScene : public CMessage {
public:
    CMessageSetInCutScene(BOOL status, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOL m_status;
};

class CMessageSetLastAttacker : public CMessage {
public:
    CMessageSetLastAttacker(const CAIObjectType& lAttacker, LONG caller, LONG target);
    ~CMessageSetLastAttacker() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAIObjectType m_lAttacker;
};

class CMessageSetLastObject : public CMessage {
public:
    CMessageSetLastObject(const CAIObjectType& lAttacker, WORD type, LONG caller, LONG target);
    ~CMessageSetLastObject() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAIObjectType m_lAttacker;
    /* 0048 */ WORD m_type;
};

class CMessageSetNumTimesTalkedTo : public CMessage {
public:
    CMessageSetNumTimesTalkedTo(LONG times, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_nNumTimesTalkedTo;
};

class CMessageSetPath : public CMessage {
public:
    CMessageSetPath(LONG position, LONG* pPath, SHORT nPath, SHORT currPath, CPoint currDest, LONG caller, LONG target);
    ~CMessageSetPath() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;

    /* 000C */ SHORT m_nPath;
    /* 000E */ LONG* m_pPath;
    /* 0012 */ SHORT m_currPath;
    /* 0014 */ CPoint m_currDest;
    /* 001C */ LONG m_position;
    /* 0020 */ CString m_sAreaString;
};

class CMessageSetSequence : public CMessage {
public:
    CMessageSetSequence(BYTE sequence, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BYTE m_sequence;
};

class CMessageSetTrigger : public CMessage {
public:
    CMessageSetTrigger(const CAITrigger& trigger, LONG caller, LONG target);
    ~CMessageSetTrigger() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CAITrigger m_trigger;
};

class CMessageSpriteDeath : public CMessage {
public:
    CMessageSpriteDeath(DWORD nDeathType, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_nDeathType;
};

class CMessageSpriteEquipment : public CMessage {
public:
    CMessageSpriteEquipment(CGameSprite* pSprite, LONG caller, LONG target);
    ~CMessageSpriteEquipment() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;

    /* 000C */ CGameSpriteEquipment m_equipment;
    /* 00E0 */ BYTE m_nWeaponSet;
};

class CMessageSpritePetrify : public CMessage {
public:
    CMessageSpritePetrify(BOOLEAN bPetrify, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bPetrify;
};

class CMessageSpriteUpdate : public CMessage {
public:
    CMessageSpriteUpdate(CGameSprite* pSprite, LONG caller, LONG target);
    ~CMessageSpriteUpdate() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;

    /* 000C */ LONG* m_pPath;
    /* 0010 */ SHORT m_nPath;
    /* 0012 */ SHORT m_currPath;
    /* 0014 */ CPoint m_ptDest;
    /* 001C */ CString m_sAreaString;
    /* 0020 */ SHORT m_nSequence;
    /* 0022 */ CPoint m_ptPosition;
    /* 002A */ SHORT m_nFacing;
    /* 002C */ DWORD m_dwState;
    /* 0030 */ std::bitset<256> m_spellStates;
    /* 0038 */ short field_38;
    /* 003A */ short field_3A;
    /* 003C */ short field_3C;
    /* 003E */ short field_3E;
    /* 0040 */ short field_40;
    /* 0042 */ short field_42;
    /* 0044 */ short field_44;
    /* 0046 */ short field_46;
    /* 0048 */ short field_48;
    /* 004A */ short field_4A;
    /* 004C */ short field_4C;
    /* 004E */ short field_4E;
    /* 0050 */ std::bitset<32> m_visualEffects;
    /* 0054 */ BYTE m_nFadeSpeed;
    /* 0055 */ unsigned char field_55;
    /* 0056 */ int field_56;
    /* 005A */ BYTE m_nTranslucent;
    /* 005B */ unsigned char field_5B;
    /* 005C */ SHORT m_nHitPoints;
    /* 005E */ SHORT m_nMaxHitPoints;
    /* 0060 */ int field_60;
    /* 0064 */ short field_64;
    /* 0066 */ short field_66;
    /* 0068 */ short field_68;
    /* 006A */ short field_6A;
    /* 006C */ SHORT m_nACCrushingMod;
    /* 006E */ SHORT m_nACMissileMod;
    /* 0070 */ SHORT m_nACPiercingMod;
    /* 0072 */ SHORT m_nACSlashingMod;
    /* 0074 */ short field_74;
    /* 0076 */ void* field_76;
    /* 007A */ BYTE m_nEnemyAlly;
    /* 007B */ BYTE m_nEnemyAllyLive;
    /* 007C */ BYTE m_nEnemyAllyStart;
    /* 007D */ BOOLEAN m_bMoralFailure;
    /* 007E */ BYTE m_nMoveScale;
    /* 007F */ unsigned char field_7F;
    /* 0080 */ LONG m_nHPCONBonusTotalOld;
    /* 0084 */ BOOLEAN m_bLevelUp;
    /* 0085 */ unsigned char field_85;
    /* 0086 */ BYTE m_baseSkills[64];
    /* 00C6 */ BYTE m_skills[64];
    /* 0106 */ unsigned char field_106;
    /* 0107 */ unsigned char field_107;
    /* 0108 */ int field_108;
};

class CMessageStartFollow : public CMessage {
public:
    CMessageStartFollow(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageStartScroll : public CMessage {
public:
    CMessageStartScroll(CGameArea* pArea, CPoint src, CPoint dest, BYTE speed, LONG caller, LONG target);
    ~CMessageStartScroll() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CString m_sAreaString;
    /* 0010 */ CPoint m_src;
    /* 0018 */ CPoint m_dest;
    /* 0020 */ BYTE m_speed;
};

class CMessageStopActions : public CMessage {
public:
    CMessageStopActions(LONG caller, LONG target, CGameSprite* pSprite);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageStopFollow : public CMessage {
public:
    CMessageStopFollow(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageTriggerStatus : public CMessage {
public:
    CMessageTriggerStatus(DWORD flags, WORD trapActivated, WORD trapDetected, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_dwFlags;
    /* 0010 */ WORD m_trapDetected;
    /* 0012 */ WORD m_trapActivated;
};

class CMessageUnlock : public CMessage {
public:
    CMessageUnlock(DWORD flags, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ DWORD m_dwFlags;
};

class CMessageUpdateReaction : public CMessage {
public:
    CMessageUpdateReaction(LONG nReaction, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_nReaction;
};

class CMessageVerbalConstant : public CMessage {
public:
    CMessageVerbalConstant(LONG verbalConstant, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_verbalConstant;
};

class CMessageVisibilityMapMove : public CMessage {
public:
    CMessageVisibilityMapMove(BOOLEAN moveOn, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_moveOntoList;
};

class CMessageVisualEffect : public CMessage {
public:
    CMessageVisualEffect(BYTE nEffectType, BYTE nEffectProperty, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BYTE m_nEffectType;
    /* 000D */ BYTE m_nEffectProperty;
};

class CMessageSetDialogResRef : public CMessage {
public:
    CMessageSetDialogResRef(CResRef dialog, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CResRef m_cResRefDialog;
};

class CMessageEscapeArea : public CMessage {
public:
    CMessageEscapeArea(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

// NOTE: Same as `CMessageDisplayTextRef` but with different CommType (`SEND`
// instead of `BROADCAST_FORCED`).
class CMessageDisplayTextRefSend : public CMessage {
public:
    CMessageDisplayTextRefSend(STRREF name, STRREF text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ STRREF m_name;
    /* 0010 */ STRREF m_text;
    /* 0014 */ COLORREF m_nameColor;
    /* 0018 */ COLORREF m_textColor;
    /* 001C */ LONG m_marker;
    /* 0020 */ BOOLEAN m_moveToTop;
};

class CMessageSetCurrentActionId : public CMessage {
public:
    CMessageSetCurrentActionId(SHORT actionId, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ SHORT m_actionId;
};

class CMessageFadeColor : public CMessage {
public:
    CMessageFadeColor(BOOLEAN bFadeTo, BYTE redFade, BYTE greenFade, BYTE blueFade, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bFadeTo;
    /* 000D */ BYTE m_redFade;
    /* 000E */ BYTE m_greenFade;
    /* 000F */ BYTE m_blueFade;
};

class CMessageStartTextScreen : public CMessage {
public:
    CMessageStartTextScreen(const CResRef& ref, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void Run() override;

    /* 000C */ CResRef m_screen;
};

class CMessage90 : public CMessage {
public:
    CMessage90(LONG caller, LONG target, int a3);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ int field_C;
};

class CMessageFloatText : public CMessage {
public:
    CMessageFloatText(LONG caller, LONG target, STRREF strRef, BOOLEAN bSpell);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ STRREF m_strRef;
    /* 0010 */ BOOLEAN m_bSpell;
};

class CMessage92 : public CMessage {
public:
    CMessage92(LONG caller, LONG target, int a3);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ int field_C;
};

class CMessageMoveGlobal : public CMessage {
public:
    CMessageMoveGlobal(const CString& sArea, const CPoint& ptStart, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CString m_sArea;
    /* 0010 */ CPoint m_ptStart;
};

class CMessageSpawnPtActivate : public CMessage {
public:
    CMessageSpawnPtActivate(BOOLEAN bActivate, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bActivate;
};

class CMessageSpawnPtSpawn : public CMessage {
public:
    CMessageSpawnPtSpawn(const CPoint& ptFacingTowards, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CPoint m_ptFacingTowards;
};

class CMessageStaticStart : public CMessage {
public:
    CMessageStaticStart(BOOLEAN bStart, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bStart;
};

class CMessageStoreAddItem : public CMessage {
public:
    CMessageStoreAddItem(const CResRef& store, const CCreatureFileItem& item, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CResRef m_store;
    /* 0014 */ CCreatureFileItem m_item;
};

class CMessageStoreRemoveItem : public CMessage {
public:
    CMessageStoreRemoveItem(const CResRef& store, const CResRef& itemId, int a3, int a4, int a5, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CResRef m_store;
    /* 0014 */ CResRef m_itemId;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
};

class CMessageFamiliarAdd : public CMessage {
public:
    CMessageFamiliarAdd(BOOLEAN bFamiliarAdd, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bFamiliarAdd;
};

class CMessageFamiliarRemoveResRef : public CMessage {
public:
    CMessageFamiliarRemoveResRef(const CResRef& resRef, BYTE nAlignment, BYTE nLevel, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CResRef m_resRef;
    /* 0014 */ BYTE m_nAlignment;
    /* 0015 */ BYTE m_nLevel;
};

class CMessageFireProjectile : public CMessage {
public:
    CMessageFireProjectile(WORD projectileType, LONG projectileTargetId, const CPoint& projectileTarget, LONG height, LONG caller, LONG target, unsigned char a7);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;

    /* 000C */ WORD m_projectileType;
    /* 000E */ LONG m_projectileTargetId;
    /* 0012 */ CPoint m_projectileTarget;
    /* 001A */ LONG m_height;
    /* 001E */ unsigned char field_1E;
    /* 0020 */ int field_20;
};

class CMessageStopEscapeArea : public CMessage {
public:
    CMessageStopEscapeArea(LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;
};

class CMessageSetTimeStop : public CMessage {
public:
    CMessageSetTimeStop(LONG time, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_time;
};

class CMessageStoreRelease : public CMessage {
public:
    CMessageStoreRelease(const CResRef& store, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    CResRef m_store;
};

class CMessageSetProtagonist : public CMessage {
public:
    CMessageSetProtagonist(LONG nId, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ LONG m_nId;
};

class CMessageStartCombatMusic : public CMessage {
public:
    CMessageStartCombatMusic(int slot, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ int m_slot;
};

class CMessageStoreDemand : public CMessage {
public:
    CMessageStoreDemand(const CResRef& store, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    CResRef m_store;
};

class CMessage101 : public CMessage {
public:
    CMessage101(BOOLEAN a1, LONG caller, LONG target, BOOLEAN a4);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN field_C;
    /* 000D */ BOOLEAN field_D;
};

class CMessageWeaponImmumityUpdate : public CMessage {
public:
    CMessageWeaponImmumityUpdate(CGameSprite* pSprite, LONG caller, LONG target);
    ~CMessageWeaponImmumityUpdate() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ CImmunitiesWeapon m_weaponImmunities;
};

class CMessage103 : public CMessage {
public:
    CMessage103(BOOLEAN a1, PLAYER_ID idPlayer, INT nPortrait, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN field_C;
    /* 000E */ PLAYER_ID m_idPlayer;
    /* 0012 */ INT m_nCharacterPortraitSlotNumber;
};

class CMessage120 : public CMessage {
public:
    CMessage120(PLAYER_ID idPlayer, BOOLEAN a2, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ PLAYER_ID m_idPlayer;
    /* 0010 */ BOOLEAN field_10;
};

class CMessageSetAreaType : public CMessage {
public:
    CMessageSetAreaType(WORD areaType, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ WORD m_areaType;
};

class CMessageSetAreaRestEncounter : public CMessage {
public:
    CMessageSetAreaRestEncounter(WORD probDay, WORD probNight, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ WORD m_probDay;
    /* 000E */ WORD m_probNight;
};

class CMessageToggleInterface : public CMessage {
public:
    CMessageToggleInterface(BOOLEAN bHide, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bHide;
};

class CMessageSetAreaExplored : public CMessage {
public:
    CMessageSetAreaExplored(BOOLEAN bExplored, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ BOOLEAN m_bExplored;
};

class CMessage107 : public CMessage {
public:
    CMessage107(unsigned char a1, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ unsigned char field_C;
};

class CMessageEndGame : public CMessage {
public:
    CMessageEndGame(int a1, int a2, LONG caller, LONG target);
    ~CMessageEndGame() override;
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ CAIAction m_action;
};

class CMessageChangeStat : public CMessage {
public:
    CMessageChangeStat(WORD stat, DWORD value, BOOLEAN modify, LONG caller, LONG target);
    SHORT GetCommType() override;
    BYTE GetMsgType() override;
    BYTE GetMsgSubType() override;
    void MarshalMessage(BYTE** pData, DWORD* dwSize) override;
    BOOL UnmarshalMessage(BYTE* pData, DWORD dwSize) override;
    void Run() override;

    /* 000C */ WORD m_stat;
    /* 000E */ DWORD m_value;
    /* 0012 */ BOOLEAN m_modify;
};

#endif /* CMESSAGE_H_ */

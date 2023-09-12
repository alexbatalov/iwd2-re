#include "CMessage.h"

#include "CBaldurChitin.h"
#include "CGameAIBase.h"
#include "CGameArea.h"
#include "CGameContainer.h"
#include "CGameDoor.h"
#include "CGameEffect.h"
#include "CGameSound.h"
#include "CGameSpawning.h"
#include "CGameSprite.h"
#include "CGameStatic.h"
#include "CGameTrigger.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenChapter.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenLoad.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSinglePlayer.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CStore.h"
#include "CUIPanel.h"
#include "CUtil.h"

// NOTE: Might be static in `CMessage`.
//
// 0x8ABE0C
static const DWORD STATICBUFFERSIZE = 0x4000;

// 0x848208
const SHORT CMessage::SEND = 1;

// 0x84820A
const SHORT CMessage::BROADCAST = 2;

// 0x84820C
const SHORT CMessage::BROADCAST_OTHERS = 3;

// 0x84820E
const SHORT CMessage::BROADCAST_FORCED = 4;

// 0x848210
const SHORT CMessage::BROADCAST_FORCED_OTHERS = 5;

// 0x84CED4
const BYTE CBaldurMessage::MSG_TYPE_PROGRESSBAR = 66;

// 0x84CED5
const BYTE CBaldurMessage::MSG_SUBTYPE_PROGRESSBAR_STATUS = 83;

// 0x84CED6
const BYTE CBaldurMessage::MSG_TYPE_CMESSAGE = 67;

// 0x84CED7
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ADD_ACTION = 0;

// 0x84CED8
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ADD_EFFECT = 1;

// 0x84CEDB
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CHANGE_DIRECTION = 4;

// 0x84CEDC
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_ACTIONS = 5;

// 0x84CEDD
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_DIALOG_ACTIONS = 6;

// 0x84CEDE
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_GROUP_SLOT = 7;

// 0x84CEDF
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_TRIGGERS = 8;

// 0x84CEE0
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_CHANGE = 9;

// 0x84CEE1
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_RESET = 10;

// 0x84CEE2
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_UPDATE = 11;

// 0x84CEE5
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CONTAINER_STATUS = 14;

// 0x84CEE6
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS = 15;

// 0x84CEE7
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXT = 16;

// 0x84CEE8
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF = 17;

// 0x84CEEA
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DOOR_STATUS = 19;

// 0x84CEEB
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DROP_PATH = 20;

// 0x84CEEE
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ENTER_STORE_MODE = 23;

// 0x84CEEF
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_EXIT_DIALOG_MODE = 24;

// 0x84CEF0
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_EXIT_STORE_MODE = 25;

// 0x84CEF2
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_INSERT_ACTION = 27;

// 0x84CEF4
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_LEAVE_PARTY = 29;

// 0x84CEF6
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_PARTY_GOLD = 31;

// 0x84CEF7
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_PLAY_SOUND = 32;

// 0x84CEFB
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_REPUTATION_CHANGE = 36;

// 0x84CEFC
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_ACTIVE = 37;

// 0x84CEFD
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_AISPEED = 38;

// 0x84CEFE
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_COMMAND_PAUSE = 39;

// 0x84CEFF
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIALOG_WAIT = 40;

// 0x84CF00
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIRECTION = 41;

// 0x84CF01
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DRAW_POLY = 42;

// 0x84CF02
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_FORCE_ACTION_PICK = 43;

// 0x84CF03
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_HAPPINESS = 44;

// 0x84CF04
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_IN_CUT_SCENE = 45;

// 0x84CF05
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_LAST_ATTACKER = 46;

// 0x84CF07
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_NUM_TIMES_TALKED_TO = 48;

// 0x84CF09
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_SEQUENCE = 50;

// 0x84CF0B
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_TRIGGER = 52;

// 0x84CF06
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_LAST_OBJECT = 47;

// 0x84CF0D
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPRITE_DEATH = 54;

// 0x84CF0F
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPRITE_PETRIFY = 56;

// 0x84CF11
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_FOLLOW = 58;

// 0x84CF11
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_ACTIONS = 60;

// 0x84CF12
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_FOLLOW = 61;

// 0x84CF15
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_TRIGGER_STATUS = 62;

// 0x84CF16
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_UNLOCK = 63;

// 0x84CF17
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_UPDATE_REACTION = 64;

// 0x84CF18
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_VERBAL_CONSTANT = 65;

// 0x84CF19
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_VISIBILITY_MAP_MOVE = 66;

// 0x84CF1B
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIALOG_RESREF = 68;

// 0x84CF1C
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ESCAPE_AREA = 69;

// 0x84CF1D
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF_SEND = 70;

// 0x84CF1E
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_CURRENT_ACTION_ID = 71;

// 0x84CF21
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_TEXT_SCREEN = 74;

// 0x84CF22
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPAWNPT_ACTIVATE = 75;

// 0x84CF23
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPAWNPT_SPAWN = 76;

// 0x84CF24
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STATIC_START = 77;

// 0x84CF25
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_ADD_ITEM = 78;

// 0x84CF26
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_REMOVE_ITEM = 79;

// 0x84CF27
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_FAMILIAR_ADD = 80;

// 0x84CF28
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_FAMILIAR_REMOVE_RESREF = 81;

// 0x84CF29
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_ESCAPE_AREA = 82;

// 0x84CF2E
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_RELEASE = 87;

// 0x84CF35
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_COMBAT_MUSIC = 94;

// 0x84CF3B
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_DEMAND = 100;

// 0x84CF3D
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_WEAPON_IMMUNITIES_UPDATE = 102;

// 0x84CF76
const BYTE CBaldurMessage::DELETEAREA_EMPTY_VOTE = 101;

// 0x84CF9F
const BYTE CBaldurMessage::MSG_TYPE_PLAYER_CHAR = 80;

// 0x84CFA3
const BYTE CBaldurMessage::MSG_SUBTYPE_PLAYERCHAR_DEMAND_REPLY = 100;

// 0x84CFB0
const BYTE CBaldurMessage::MSG_TYPE_RESOURCE = 82;

// 0x84CFB1
const BYTE CBaldurMessage::MSG_SUBTYPE_RESOURCE_DEMAND = 68;

// 0x84CFBB
const BYTE CBaldurMessage::SIGNAL_ALL_CLIENTS = 67;

// 0x84CFBC
const BYTE CBaldurMessage::SIGNAL_SERVER = 83;

// 0x84CFBD
const BYTE CBaldurMessage::SIGNAL_END_MAJOR_EVENT = 49;

// 0x84CFC2
const BYTE CBaldurMessage::SIGNAL_END_GAME = 54;

// 0x84CFC4
const DWORD CBaldurMessage::SIGNAL_SECONDSTOMPTIMEOUT = 200;

// 0x4294F0
CBaldurMessage::CBaldurMessage()
{
    field_6 = 0;
    m_nVersionControlShutdownReason = 0;
    field_0 = 0;
    field_1 = 0;
    field_2 = 0;
    field_3 = 0;
    field_5 = 0;
    field_4 = 0;
    m_bDialogRequestPending = FALSE;
    m_bDialogReplyReturned = FALSE;
    field_D5 = 0;
    m_nDialogReplyUpdates = 0;
    field_DA = 0;
    field_DB = 0;
    field_DC = 0;
    field_DD = 0;
    field_DE = 0;
    field_DF = 0;
    field_74 = "";
    field_73 = 0;
    field_78 = 0;

    for (int k = 0; k < 6; k++) {
        field_82[k] = 0;
        field_7C[k] = DELETEAREA_EMPTY_VOTE;
    }

    field_E0 = 0;
    field_E1 = 0;
    field_E2 = 0;
    field_E3 = 0;
    field_E4 = -1;
    field_29 = 0;
    field_2A = 0;
    m_nSignalQueueSize = 24;

    for (BYTE l = 0; l < m_nSignalQueueSize; l++) {
        field_2B[l] = -1;
        field_5B[l] = 0;
        field_43[l] = 0;
    }

    field_D2 = 0;

    for (int m = 0; m < 6; m++) {
        field_BA[m] = 0;
    }

    field_E5 = 0;
    m_dwSignalSecondsToTimeout = SIGNAL_SECONDSTOMPTIMEOUT;
    m_bPlayerShutdown = FALSE;
    m_bMultiplayerSessionShutdown = FALSE;
    m_bInReputationChange = FALSE;
    m_bInMessageSetDrawPoly = FALSE;
}

// 0x429720
CBaldurMessage::~CBaldurMessage()
{
}

// 0x4297C0
BOOLEAN CBaldurMessage::DemandResourceFromServer(const CString& sResName, UINT nType, BOOLEAN bSendMessage, BOOLEAN bWaitForMessage, BOOLEAN bSaveToTemp)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x429A90
BOOLEAN CBaldurMessage::OnResourceDemanded(INT nMsgFrom, BYTE* pByteMessage, DWORD dwSize)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42B2B0
BOOL CBaldurMessage::SendFullSettingsToClients(const CString& sPlayerName)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42BC00
BOOL CBaldurMessage::SendCharacterReadyToServer(INT nCharacterSlot, BOOLEAN bReady)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C0E0
BOOL CBaldurMessage::SendImportingOptionToServer(BYTE nImportingBitField)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C390
BOOL CBaldurMessage::SendRestrictStoreOptionToServer(BOOLEAN bRestrictStore)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C640
BOOL CBaldurMessage::SendJoinRequestOptionToServer(BOOLEAN bListenToJoin)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C8F0
BOOLEAN CBaldurMessage::SendCharacterSlotStatusToServer(SHORT nCharacterSlot, BYTE nStatus)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CAD0
BOOLEAN CBaldurMessage::SendArbitrationLockRequestToServer(BOOLEAN bLockValue)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CCA0
BOOL CBaldurMessage::SendArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CEF0
BOOL CBaldurMessage::SendArbitrationLockAllowInput(BOOLEAN bAllowInput)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42D070
BOOLEAN CBaldurMessage::KickPlayerRequest(const CString& sPlayerName)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42D860
void CBaldurMessage::UpdateDemandCharacters(unsigned char a1, int a2, unsigned char a3)
{
    // TODO: Incomplete.
}

// 0x42F100
BOOLEAN CBaldurMessage::DemandCharacterSlot(SHORT nCharacterSlot, BOOLEAN bDemandFromHost, SHORT nPlayerSlot)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42FA60
BOOLEAN CBaldurMessage::OnDemandCharacterSlotReply(INT nMsgFrom, BYTE* pMessage, DWORD dwSize)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x430980
BOOL CBaldurMessage::ObjectControlRequest(LONG localObjectID)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x430C50
BOOL CBaldurMessage::ObjectControl()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x432C50
BOOLEAN CBaldurMessage::SendChatMessage(CString& sChatMessage)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433150
void CBaldurMessage::SetSignalDefaultSecondsToTimeout()
{
    m_dwSignalSecondsToTimeout = GetPrivateProfileIntA("Multiplayer",
        "Client Timeout",
        SIGNAL_SECONDSTOMPTIMEOUT,
        g_pBaldurChitin->GetIniFileName());

    if (m_dwSignalSecondsToTimeout <= 30 || m_dwSignalSecondsToTimeout > 9999) {
        m_dwSignalSecondsToTimeout = SIGNAL_SECONDSTOMPTIMEOUT;
    }
}

// 0x4331A0
BOOLEAN CBaldurMessage::RequestClientSignal(BYTE signalToSend)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x4333C0
BOOLEAN CBaldurMessage::SendSignal(BYTE signalType, BYTE signalToSend)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433580
BOOLEAN CBaldurMessage::NonBlockingWaitForSignal(BYTE signalType, BYTE signalToWaitFor)
{
    // TODO: Incomplete.

    return -1;
}

// 0x4337D0
BYTE CBaldurMessage::KickOutWaitingForSignal(BYTE signalType, BYTE signalToWaitFor)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433950
BOOLEAN CBaldurMessage::WaitForSignal(BYTE signalType, BYTE signalToWaitFor)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433BE0
BOOLEAN CBaldurMessage::SendProgressBarStatus(LONG nActionProgress, LONG nActionTarget, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bTimeoutVisible, DWORD nSecondsToTimeout)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433D30
BOOLEAN CBaldurMessage::OnProgressBarStatus(INT nMsgFrom, BYTE* pMessage, DWORD dwSize)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x434EB0
BOOLEAN CBaldurMessage::ChapterAnnounceStatus(BYTE nChapter, CResRef cResRef)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x4354E0
BOOLEAN CBaldurMessage::SendMapWorldAnnounceStatus(BOOLEAN bActive, PLAYER_ID idController, LONG nLeavingEdge)
{
    // TODO: Incomplete.

    return FALSE;
}

// FIXME: `cResMovie` should be reference.
//
// 0x4369E0
BOOLEAN CBaldurMessage::MovieAnnounceStatus(CResRef cResMovie)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x436DF0
BOOLEAN CBaldurMessage::SendReformPartyAnnounceStatus()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x436F50
void CBaldurMessage::WeatherBroadcast(WORD wWeatherFlags)
{
    // TODO: Incomplete.
}

// 0x4370B0
void CBaldurMessage::TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime)
{
    // TODO: Incomplete.
}

// 0x437240
void CBaldurMessage::TimeChangeToServer(DWORD deltaTime)
{
    // TODO: Incomplete.
}

// 0x43C390
BYTE* CBaldurMessage::PollSpecificMessageType(BYTE nMsgType, BYTE nMsgSubType, INT& nMsgFrom, DWORD& dwSize)
{
    // TODO: Incomplete.

    return NULL;
}

// 0x43C4A0
void CBaldurMessage::HandleBlockingMessages()
{
    // TODO: Incomplete.
}

// 0x43D590
BOOLEAN CBaldurMessage::DemandSettingsNightmareMode(BOOLEAN wait)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x43DF60
BOOL CBaldurMessage::DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, LONG caller, LONG target)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bInLoadGame == TRUE) {
        return FALSE;
    }

    CMessageDisplayText* pMessage = new CMessageDisplayText(sName,
        sText,
        rgbNameColor,
        rgbTextColor,
        lMarker,
        caller,
        target);

    g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

    return TRUE;
}

// 0x43E0E0
BOOL CBaldurMessage::DisplayTextRef(STRREF name, STRREF text, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, LONG caller, LONG target)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bInLoadGame == TRUE) {
        return FALSE;
    }

    CMessageDisplayTextRef* pMessage = new CMessageDisplayTextRef(name,
        text,
        rgbNameColor,
        rgbTextColor,
        lMarker,
        caller,
        target);

    g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

    return TRUE;
}

// 0x605AA0
CString CBaldurMessage::GetVersionControlShutdownServerString()
{
    return m_sVersionControlShutdownServerString;
}

// 0x605AD0
CString CBaldurMessage::GetVersionControlShutdownClientString()
{
    return m_sVersionControlShutdownClientString;
}

// 0x4F4F50
BOOLEAN CBaldurMessage::GetDialogRequestPending()
{
    return m_bDialogRequestPending;
}

// 0x4F4F50
BOOLEAN CBaldurMessage::GetDialogReplyReturned()
{
    return m_bDialogReplyReturned;
}

// 0x4F4F70
INT CBaldurMessage::GetDialogReplyUpdates()
{
    return m_nDialogReplyUpdates;
}

// 0x4F4F80
void CBaldurMessage::SetDialogReplyUpdates(INT nValue)
{
    m_nDialogReplyUpdates = nValue;
}

// -----------------------------------------------------------------------------

// 0x45DEA0
CMessage::CMessage(LONG caller, LONG target)
{
    m_sourceId = caller;
    m_targetId = target;
}

// 0x4051F0
CMessage::~CMessage()
{
}

// 0x405140
SHORT CMessage::GetCommType()
{
    // __FILE__: .\Include\CMessage.h
    // __LINE__: 965
    UTIL_ASSERT(FALSE);
}

// 0x405160
BYTE CMessage::GetMsgType()
{
    // __FILE__: .\Include\CMessage.h
    // __LINE__: 966
    UTIL_ASSERT(FALSE);
}

// 0x405180
BYTE CMessage::GetMsgSubType()
{
    // __FILE__: .\Include\CMessage.h
    // __LINE__: 967
    UTIL_ASSERT(FALSE);
}

// 0x4051A0
void CMessage::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    *pData = NULL;
    *dwSize = 0;
}

// 0x4051C0
BOOL CMessage::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    return FALSE;
}

// 0x4051D0
void CMessage::Run()
{
    // __FILE__: .\Include\CMessage.h
    // __LINE__: 972
    UTIL_ASSERT(FALSE);
}

// -----------------------------------------------------------------------------

// 0x4F7470
CMessageHandler::CMessageHandler()
{
    m_bLastArbitrationLockStatus = FALSE;
}

// 0x4F7490
CMessageHandler::~CMessageHandler()
{
    // TODO: Incomplete.
}

// 0x4EE020
void CMessageHandler::AsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x4F7110
void CMessageHandler::PostAsynchronousUpdate()
{
    if (g_pChitin->field_1932 == TRUE) {
        return;
    }

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        g_pChitin->cGameSpy.sub_4D2210();
    }

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        STRREF strError;
        if (g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame == TRUE
            && (g_pBaldurChitin->GetObjectGame()->CanSaveGame(strError, 0, 0) == TRUE
                || g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE)) {
            if ((g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineLoad
                    && g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineCreateChar
                    && g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineMultiPlayer
                    && g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineSinglePlayer
                    && g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineConnection)
                || (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineMultiPlayer
                    && g_pBaldurChitin->m_pEngineMultiPlayer->field_45C != 1)) {
                g_pBaldurChitin->GetObjectGame()->MultiplayerSetCharacterCreationLocation();

                g_pBaldurChitin->GetObjectGame()->m_tempCursor = 4;

                g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 1;
                g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(1);
                g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);

                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetArbitrationLockStatus(1, 0);
            }

            if (g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame == TRUE) {
                g_pBaldurChitin->GetBaldurMessage()->SendFullSettingsToClients(CString(""));
                g_pBaldurChitin->GetBaldurMessage()->UpdateDemandCharacters(1, 0, 0);
            } else {
                if (!m_bLastArbitrationLockStatus
                    && g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus != TRUE) {
                    g_pBaldurChitin->GetBaldurMessage()->UpdateDemandCharacters(1, 0, 0);
                }
            }

            g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame = FALSE;
        }
    }

    m_bLastArbitrationLockStatus = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus;

    if (g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSessionShutdown == TRUE) {
        g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSessionShutdown = FALSE;
        g_pChitin->cNetwork.CloseSession(TRUE);
    }

    if (g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown == TRUE) {
        if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineConnection);

            if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
            }

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                g_pBaldurChitin->GetObjectGame()->SaveGame(0, 0, 1);
            }

            g_pBaldurChitin->GetObjectGame()->DestroyGame(1, 0);
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            g_pChitin->cNetwork.CloseSession(TRUE);
        }

        g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown = FALSE;
    }
}

// 0x4F7500
void CMessageHandler::AddMessage(CMessage* message, BOOL bForcePassThrough)
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x4F4F90
CMessageAddAction::CMessageAddAction(const CAIAction& action, LONG caller, LONG target)
    : CMessage(caller, target)
{
    // NOTE: Uninline.
    m_action = action;
}

// 0x405240
CMessageAddAction::~CMessageAddAction()
{
}

// 0x40A0D0
SHORT CMessageAddAction::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageAddAction::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x405210
BYTE CMessageAddAction::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ADD_ACTION;
}

// 0x4F83C0
void CMessageAddAction::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->AddAction(m_action);
            pSprite->m_interrupt = TRUE;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4533D0
CMessageAddEffect::CMessageAddEffect(CGameEffect* effect, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_effect = effect;
}

// 0x453410
CMessageAddEffect::~CMessageAddEffect()
{
    if (m_effect != NULL) {
        delete m_effect;
        m_effect = NULL;
    }
}

// 0x40A0D0
SHORT CMessageAddEffect::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageAddEffect::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4533C0
BYTE CMessageAddEffect::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ADD_EFFECT;
}

// 0x4F8CA0
void CMessageAddEffect::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->AddEffect(m_effect, CGameAIBase::EFFECT_LIST_TIMED, FALSE, TRUE);
            m_effect = NULL;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5200
CMessageChangeDirection::CMessageChangeDirection(SHORT face, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_face = face;
}

// 0x453510
SHORT CMessageChangeDirection::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageChangeDirection::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5230
BYTE CMessageChangeDirection::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CHANGE_DIRECTION;
}

// 0x4F9890
void CMessageChangeDirection::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 5951
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG) + sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 5972
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_face;
        cnt += sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 5994
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4F99C0
BOOL CMessageChangeDirection::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6022
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_face = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6048
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4F9A70
void CMessageChangeDirection::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->SetDirection(m_face);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5240
CMessageClearActions::CMessageClearActions(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageClearActions::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageClearActions::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4637A0
BYTE CMessageClearActions::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_ACTIONS;
}

// 0x4F9B10
void CMessageClearActions::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6119
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6139
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6159
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4F9C30
BOOL CMessageClearActions::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6187
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6209
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4F9CD0
void CMessageClearActions::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->ClearActions(FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5260
CMessageClearDialogActions::CMessageClearDialogActions(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageClearDialogActions::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageClearDialogActions::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5280
BYTE CMessageClearDialogActions::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_DIALOG_ACTIONS;
}

// 0x4F9D70
void CMessageClearDialogActions::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6281
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6301
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6321
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4F9E90
BOOL CMessageClearDialogActions::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6349
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6371
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4F9F30
void CMessageClearDialogActions::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->ClearDialogActions();
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5290
CMessageClearGroupSlot::CMessageClearGroupSlot(SHORT slotNum, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_slotNum = slotNum;
}

// 0x453510
SHORT CMessageClearGroupSlot::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageClearGroupSlot::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F52C0
BYTE CMessageClearGroupSlot::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_DIALOG_ACTIONS;
}

// 0x4F9FD0
void CMessageClearGroupSlot::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6444
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6449
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<SHORT*>(*pData + cnt) = m_slotNum;
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6466
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FA060
BOOL CMessageClearGroupSlot::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6490
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_slotNum = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6498
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FA0C0
void CMessageClearGroupSlot::Run()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if (pGame->m_groupInventory[m_slotNum] != NULL) {
        delete pGame->m_groupInventory[m_slotNum];
        pGame->m_groupInventory[m_slotNum] = NULL;
    }
}

// -----------------------------------------------------------------------------

// 0x4F52D0
CMessageClearTriggers::CMessageClearTriggers(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageClearTriggers::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageClearTriggers::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F52F0
BYTE CMessageClearTriggers::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CLEAR_TRIGGERS;
}

// 0x4FA110
void CMessageClearTriggers::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6559
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6579
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6599
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FA230
BOOL CMessageClearTriggers::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6627
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6649
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FA2D0
void CMessageClearTriggers::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->ClearTriggers();
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5300
CMessageColorChange::CMessageColorChange(BYTE* colors, LONG caller, LONG target)
    : CMessage(caller, target)
{
    for (int index = 0; index < 7; index++) {
        m_colors[index] = colors[index];
    }
}

// 0x4088A0
SHORT CMessageColorChange::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageColorChange::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5340
BYTE CMessageColorChange::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_CHANGE;
}

// 0x4FA370
void CMessageColorChange::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6721
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + 7;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6743
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        memcpy(*pData + cnt, m_colors, 7);
        cnt += 7;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6766
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FA4B0
BOOL CMessageColorChange::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6794
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    memcpy(m_colors, pData + cnt, 7);
    cnt += 7;

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6819
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FA570
void CMessageColorChange::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            for (int index = 0; index < 7; index++) {
                pSprite->GetBaseStats()->m_colors[index] = m_colors[index];

                // NOTE: Uninline.
                pSprite->GetAnimation()->SetColorRange(index, m_colors[index]);
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5350
CMessageColorReset::CMessageColorReset(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x4088A0
SHORT CMessageColorReset::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageColorReset::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5370
BYTE CMessageColorReset::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_RESET;
}

// 0x4FA680
void CMessageColorReset::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6896
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pSprite->m_remotePlayerID;
        LONG remoteObjectID = pSprite->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6916
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 6936
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FA7A0
BOOL CMessageColorReset::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6964
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 6986
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FA840
void CMessageColorReset::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            BYTE* colors = pSprite->GetBaseStats()->m_colors;
            for (int index = 0; index < 7; index++) {
                // NOTE: Uninline.
                pSprite->GetAnimation()->SetColorRange(index, colors[index]);
            }

            // NOTE: Uninline.
            pSprite->GetAnimation()->ClearColorEffectsAll();
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4FA960
CMessageColorUpdate::CMessageColorUpdate(CGameSprite* pSprite, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_appliedColorRanges = pSprite->GetDerivedStats()->m_appliedColorRanges;
    m_appliedColorEffects = pSprite->GetDerivedStats()->m_appliedColorEffects;
}

// 0x4F6FC0
CMessageColorUpdate::~CMessageColorUpdate()
{
}

// 0x453510
SHORT CMessageColorUpdate::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageColorUpdate::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4FAA10
BYTE CMessageColorUpdate::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_COLOR_UPDATE;
}

// 0x4FAA40
void CMessageColorUpdate::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 7084
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        BYTE* ranges;
        ULONG rangeSize = m_appliedColorRanges.Marshal(&ranges);

        BYTE* effects;
        DWORD effectSize = m_appliedColorEffects.Marshal(&effects);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(ULONG)
            + rangeSize
            + sizeof(ULONG)
            + effectSize;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 7116
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<ULONG*>(*pData + cnt) = rangeSize;
        cnt += sizeof(ULONG);

        memcpy(*pData + cnt, ranges, rangeSize);
        cnt += rangeSize;

        *reinterpret_cast<ULONG*>(*pData + cnt) = effectSize;
        cnt += sizeof(ULONG);

        memcpy(*pData + cnt, effects, effectSize);
        cnt += effectSize;

        if (ranges != NULL) {
            delete ranges;
        }

        if (effects != NULL) {
            delete effects;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 7158
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FAC10
BOOL CMessageColorUpdate::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 7186
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    ULONG rangeSize = *reinterpret_cast<ULONG*>(pData + cnt);
    cnt += sizeof(ULONG);

    m_appliedColorRanges.Unmarshal(pData + cnt, rangeSize);
    cnt += rangeSize;

    ULONG effectSize = *reinterpret_cast<ULONG*>(pData + cnt);
    cnt += sizeof(ULONG);

    m_appliedColorEffects.Unmarshal(pData + cnt, effectSize);
    cnt += effectSize;

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 7223
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FACF0
void CMessageColorUpdate::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            BYTE* colors = pSprite->GetBaseStats()->m_colors;
            for (int index = 0; index < 7; index++) {
                // NOTE: Uninline.
                pSprite->GetAnimation()->SetColorRange(index, colors[index]);
            }

            m_appliedColorRanges.Apply(pSprite);
            m_appliedColorEffects.Apply(pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5380
CMessageContainerStatus::CMessageContainerStatus(DWORD flags, WORD trapActivated, WORD trapDetected, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_dwFlags = flags;
    m_trapActivated = trapActivated;
    m_trapDetected = trapDetected;
}

// 0x43E170
SHORT CMessageContainerStatus::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageContainerStatus::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47D7A0
BYTE CMessageContainerStatus::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CONTAINER_STATUS;
}

// 0x4FBB50
void CMessageContainerStatus::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8053
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(remoteObjectID)
            + sizeof(LONG)
            + sizeof(DWORD)
            + sizeof(WORD)
            + sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 8076
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_dwFlags;
        cnt += sizeof(DWORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapActivated;
        cnt += sizeof(WORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapDetected;
        cnt += sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 8106
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FBC90
BOOL CMessageContainerStatus::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8134
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_dwFlags = *reinterpret_cast<DWORD*>(pData + cnt);
    cnt += sizeof(DWORD);

    m_trapActivated = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    m_trapDetected = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8167
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FBD50
void CMessageContainerStatus::Run()
{
    CGameContainer* pContainer;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pContainer),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pContainer->SetFlags(m_dwFlags);
        pContainer->SetTrapActivated(m_trapActivated);
        pContainer->SetTrapDetected(m_trapDetected);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F53C0
CMessageCutSceneModeStatus::CMessageCutSceneModeStatus(BOOLEAN mode, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_cutSceneMode = mode;
}

// 0x43E170
SHORT CMessageCutSceneModeStatus::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageCutSceneModeStatus::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x453470
BYTE CMessageCutSceneModeStatus::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS;
}

// 0x4FBE00
void CMessageCutSceneModeStatus::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8247
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(remoteObjectID)
            + sizeof(LONG)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 8268
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_cutSceneMode;
        cnt += sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 8106
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FBF30
BOOL CMessageCutSceneModeStatus::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8319
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_cutSceneMode = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8351
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FBFD0
void CMessageCutSceneModeStatus::Run()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (pGame->field_43E2 == 1282) {
        pGame->field_43E6 = 0;

        // NOTE: Unused.
        CString sError("Trying to start a cut scene while in a dialog.");
    } else {
        if (m_cutSceneMode) {
            CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;
            if (pWorld->m_bPaused == TRUE
                && g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                if (!pWorld->TogglePauseGame(0, 1, 0)) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
                    // __LINE__: 8396
                    UTIL_ASSERT(FALSE);
                }
            }

            pGame->field_43E2 = 322;
            pGame->field_43E6 = 1;

            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);

            pGame->SetTempCursor(4);
            pGame->GetVisibleArea()->m_nScrollState = 0;

            g_pBaldurChitin->GetActiveEngine()->SelectEngine(pWorld);
        } else {
            if (pGame->field_43E2 == 322) {
                pGame->field_43E2 = -1;

                g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(1)->SetActive(TRUE);
                g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(1)->InvalidateRect(NULL);
            }
            pGame->field_43E6 = 0;
        }
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CMessageDisplayText::CMessageDisplayText(const CString& name, const CString& text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_name = name;
    m_text = text;
    m_nameColor = nameColor;
    m_textColor = textColor;
    m_marker = marker;
    m_moveToTop = FALSE;
}

// 0x43E090
CMessageDisplayText::~CMessageDisplayText()
{
}

// 0x43E170
SHORT CMessageDisplayText::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageDisplayText::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x43E060
BYTE CMessageDisplayText::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS;
}

// 0x4FC4F0
void CMessageDisplayText::Run()
{
    g_pBaldurChitin->m_pEngineWorld->DisplayText(m_name,
        m_text,
        m_nameColor,
        m_textColor,
        m_marker,
        m_moveToTop);
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CMessageDisplayTextRef::CMessageDisplayTextRef(STRREF name, STRREF text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_name = name;
    m_text = text;
    m_nameColor = nameColor;
    m_textColor = textColor;
    m_marker = marker;
    m_moveToTop = FALSE;
}

// 0x43E170
SHORT CMessageDisplayTextRef::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageDisplayTextRef::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x43E180
BYTE CMessageDisplayTextRef::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF;
}

// 0x4FC520
void CMessageDisplayTextRef::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8677
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID)
        + sizeof(LONG)
        + sizeof(STRREF)
        + sizeof(STRREF)
        + sizeof(COLORREF)
        + sizeof(COLORREF)
        + sizeof(LONG)
        + sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8705
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    *reinterpret_cast<STRREF*>(*pData + cnt) = m_name;
    cnt += sizeof(STRREF);

    *reinterpret_cast<STRREF*>(*pData + cnt) = m_text;
    cnt += sizeof(STRREF);

    *reinterpret_cast<COLORREF*>(*pData + cnt) = m_nameColor;
    cnt += sizeof(COLORREF);

    *reinterpret_cast<COLORREF*>(*pData + cnt) = m_textColor;
    cnt += sizeof(COLORREF);

    *reinterpret_cast<LONG*>(*pData + cnt) = m_marker;
    cnt += sizeof(LONG);

    *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_moveToTop;
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8746
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FC670
BOOL CMessageDisplayTextRef::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8774
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_name = *reinterpret_cast<STRREF*>(pData + cnt);
    cnt += sizeof(STRREF);

    m_text = *reinterpret_cast<STRREF*>(pData + cnt);
    cnt += sizeof(STRREF);

    m_nameColor = *reinterpret_cast<COLORREF*>(pData + cnt);
    cnt += sizeof(COLORREF);

    m_textColor = *reinterpret_cast<COLORREF*>(pData + cnt);
    cnt += sizeof(COLORREF);

    m_marker = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    m_moveToTop = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8819
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FC740
void CMessageDisplayTextRef::Run()
{
    STR_RES strResName;
    STR_RES strResText;
    CString sName("");

    BYTE rc;
    CGameSprite* pSprite;

    if (m_name >= -7 && m_name != -1) {
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(-2 - m_name);

        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            sName = pSprite->GetName();

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    } else {
        g_pBaldurChitin->GetTlkTable().Fetch(m_name, strResName);
        sName = strResName.szText;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(m_text, strResText);

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (strResText.cSound.GetRes() != NULL) {
            if (strResText.cSound.m_nLooping == 0) {
                strResText.cSound.SetFireForget(TRUE);
            }

            strResText.cSound.SetChannel(14, reinterpret_cast<DWORD>(pSprite->GetArea()));

            // FIXME: Calls `GetPos` twice.
            strResText.cSound.Play(pSprite->GetPos().x,
                pSprite->GetPos().y,
                0,
                FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    g_pBaldurChitin->m_pEngineWorld->DisplayText(sName,
        strResText.szText,
        m_nameColor,
        m_textColor,
        m_marker,
        m_moveToTop);
}

// -----------------------------------------------------------------------------

// 0x4FD370
CMessageDoorStatus::CMessageDoorStatus(CGameDoor* pDoor, LONG caller, LONG target)
    : CMessage(caller, target)
{
    if (pDoor != NULL) {
        m_bOpen = (pDoor->m_dwFlags & 0x1) != 0;
        m_dwFlags = pDoor->m_dwFlags;
        m_trapDetected = pDoor->m_trapDetected;
        m_trapActivated = pDoor->m_trapActivated;
    } else {
        m_bOpen = FALSE;
        m_dwFlags = 0;
        m_trapDetected = 0;
        m_trapActivated = 0;
    }
}

// 0x43E170
SHORT CMessageDoorStatus::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageDoorStatus::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4FD3D0
BYTE CMessageDoorStatus::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DOOR_STATUS;
}

// 0x4FD3E0
void CMessageDoorStatus::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9469
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(remoteObjectID)
            + sizeof(LONG)
            + sizeof(BOOLEAN)
            + sizeof(DWORD)
            + sizeof(WORD)
            + sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 9493
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bOpen;
        cnt += sizeof(BOOLEAN);

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_dwFlags;
        cnt += sizeof(DWORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapActivated;
        cnt += sizeof(WORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapDetected;
        cnt += sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 9525
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x4FD530
BOOL CMessageDoorStatus::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9553
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_bOpen = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    m_dwFlags = *reinterpret_cast<DWORD*>(pData + cnt);
    cnt += sizeof(DWORD);

    m_trapActivated = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    m_trapDetected = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9588
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FD5F0
void CMessageDoorStatus::Run()
{
    CGameDoor* pDoor;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pDoor),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pDoor->OnDoorStatusUpdate(m_bOpen,
            m_dwFlags,
            m_trapActivated,
            m_trapDetected);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4BD900
CMessageDropPath::CMessageDropPath(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x453510
SHORT CMessageDropPath::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageDropPath::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4B34E0
BYTE CMessageDropPath::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DROP_PATH;
}

// 0x4FD6A0
void CMessageDropPath::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9662
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 9682
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // NOTE: Missing trailing control seen in other functions.
    } else {
        *dwSize = 0;
    }
}

// 0x4FD7A0
BOOL CMessageDropPath::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9733
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing control seen in other functions.

    return TRUE;
}

// 0x4FD830
void CMessageDropPath::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->DropPath();
            pSprite->DropSearchRequest();

            if (pSprite->m_nSequence == CGameSprite::SEQ_WALK) {
                pSprite->SetSequence(CGameSprite::SEQ_READY);
            }

            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID) {
                pSprite->m_bSendSpriteUpdate = TRUE;
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// FIXME: `cResStore` should be reference.
//
// 0x4F5520
CMessageEnterStoreMode::CMessageEnterStoreMode(const CAIObjectType& cAIProprietor, const CAIObjectType& cAICustomer, const CResRef cResStore, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_cAIProprietor.Set(cAIProprietor);
    m_cAICustomer.Set(cAICustomer);
    m_cResStore = cResStore;
}

// 0x4F5630
CMessageEnterStoreMode::~CMessageEnterStoreMode()
{
}

// 0x4536E0
SHORT CMessageEnterStoreMode::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageEnterStoreMode::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5600
BYTE CMessageEnterStoreMode::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ENTER_STORE_MODE;
}

// 0x4FF480
void CMessageEnterStoreMode::Run()
{
    g_pBaldurChitin->m_pEngineWorld->StartStore(m_cAIProprietor,
        m_cAICustomer,
        m_cResStore,
        FALSE);
}

// -----------------------------------------------------------------------------

// 0x4F56E0
CMessageExitDialogMode::CMessageExitDialogMode(BOOLEAN bButtonPushed, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bButtonPushed = bButtonPushed;
}

// 0x4536E0
SHORT CMessageExitDialogMode::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageExitDialogMode::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5700
BYTE CMessageExitDialogMode::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_EXIT_DIALOG_MODE;
}

// 0x4FF970
void CMessageExitDialogMode::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11426
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID)
        + sizeof(LONG)
        + sizeof(BOOLEAN)
        + sizeof(unsigned char);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11454
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bButtonPushed;
    cnt += sizeof(BOOLEAN);

    *reinterpret_cast<unsigned char*>(*pData + cnt) = g_pBaldurChitin->m_pEngineWorld->field_1204;
    cnt += sizeof(unsigned char);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11485
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FFAB0
BOOL CMessageExitDialogMode::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11513
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_bButtonPushed = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    g_pBaldurChitin->m_pEngineWorld->field_1204 = *reinterpret_cast<unsigned char*>(pData + cnt);
    cnt += sizeof(unsigned char);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11548
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FFB70
void CMessageExitDialogMode::Run()
{
    g_pBaldurChitin->m_pEngineWorld->field_1150 = 0;
    g_pBaldurChitin->m_pEngineWorld->EndDialog(1, 1);
    g_pBaldurChitin->m_pEngineWorld->field_F04 = 0;
}

// -----------------------------------------------------------------------------

// 0x4F5710
CMessageExitStoreMode::CMessageExitStoreMode(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x4536E0
SHORT CMessageExitStoreMode::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageExitStoreMode::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5730
BYTE CMessageExitStoreMode::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_EXIT_STORE_MODE;
}

// 0x4FFBB0
void CMessageExitStoreMode::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11617
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11640
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11660
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FFCD0
BOOL CMessageExitStoreMode::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11688
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11711
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FFD70
void CMessageExitStoreMode::Run()
{
    g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
    g_pBaldurChitin->m_pEngineWorld->StopStore();
}

// -----------------------------------------------------------------------------

// 0x4F5830
CMessageInsertAction::CMessageInsertAction(const CAIAction& action, LONG caller, LONG target)
    : CMessage(caller, target)
{
    // NOTE: Uninline.
    m_action = action;
}

// 0x45BD40
CMessageInsertAction::~CMessageInsertAction()
{
}

// 0x40A0D0
SHORT CMessageInsertAction::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageInsertAction::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x45BD10
BYTE CMessageInsertAction::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_INSERT_ACTION;
}

// 0x501730
void CMessageInsertAction::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->InsertAction(m_action);
            pSprite->m_interrupt = TRUE;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5A60
CMessageLeaveParty::CMessageLeaveParty(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageLeaveParty::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageLeaveParty::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5A80
BYTE CMessageLeaveParty::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_LEAVE_PARTY;
}

// 0x5028E0
void CMessageLeaveParty::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14116
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14139
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14159
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x502A00
BOOL CMessageLeaveParty::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14187
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14210
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x502AA0
void CMessageLeaveParty::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->LeaveParty();
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5B90
CMessagePartyGold::CMessagePartyGold(BOOLEAN bFeedback, BOOLEAN bAdj, LONG gold, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bFeedback = bFeedback;
    m_bAdjustment = bAdj;
    m_gold = gold;
}

// 0x43E170
SHORT CMessagePartyGold::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessagePartyGold::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x465190
BYTE CMessagePartyGold::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_PARTY_GOLD;
}

// 0x503040
void CMessagePartyGold::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14529
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = sizeof(LONG)
        + sizeof(BYTE)
        + sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14534
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<LONG*>(*pData + cnt) = m_gold;
    cnt += sizeof(LONG);

    *reinterpret_cast<BYTE*>(*pData + cnt) = m_bAdjustment;
    cnt += sizeof(BYTE);

    *reinterpret_cast<BYTE*>(*pData + cnt) = m_bFeedback;
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14557
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x5030E0
BOOL CMessagePartyGold::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14582
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_gold = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    m_bAdjustment = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    m_bFeedback = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14596
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x503150
void CMessagePartyGold::Run()
{
    if (m_bAdjustment == TRUE) {
        if (m_bFeedback) {
            if (!g_pChitin->cNetwork.GetSessionOpen()
                || g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                g_pBaldurChitin->GetObjectGame()->FeedBack(CInfGame::FEEDBACK_GOLD,
                    m_gold,
                    TRUE);
            }
        }

        if (m_gold < 0) {
            // NOTE: Unsigned compare.
            if (static_cast<DWORD>(-m_gold) > g_pBaldurChitin->GetObjectGame()->m_nPartyGold) {
                g_pBaldurChitin->GetObjectGame()->m_nPartyGold = 0;
            } else {
                g_pBaldurChitin->GetObjectGame()->m_nPartyGold += m_gold;
            }
        } else {
            g_pBaldurChitin->GetObjectGame()->m_nPartyGold += m_gold;
        }
    } else {
        g_pBaldurChitin->GetObjectGame()->m_nPartyGold = m_gold;
    }

    CBaldurEngine* pActiveEngine = g_pBaldurChitin->GetActiveEngine();
    if (pActiveEngine != NULL) {
        pActiveEngine->UpdatePartyGoldStatus();
    }
}

// -----------------------------------------------------------------------------

// 0x4F5BC0
CMessagePlaySound::CMessagePlaySound(BYTE soundId, BOOL text, BOOL circle, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_soundId = soundId;
    m_showText = text;
    m_showCircle = circle;
}

// 0x43E170
SHORT CMessagePlaySound::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessagePlaySound::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4A8DE0
BYTE CMessagePlaySound::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_PLAY_SOUND;
}

// 0x503210
void CMessagePlaySound::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14673
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BYTE)
            + sizeof(BOOLEAN)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 14694
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BYTE*>(*pData + cnt) = m_soundId;
        cnt += sizeof(BYTE);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_showText == TRUE;
        cnt += sizeof(BOOLEAN);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_showCircle == TRUE;
        cnt += sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 14743
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x503360
BOOL CMessagePlaySound::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14773
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_soundId = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    m_showText = *reinterpret_cast<BOOLEAN*>(pData + cnt) == TRUE;
    cnt += sizeof(BOOLEAN);

    m_showCircle = *reinterpret_cast<BOOLEAN*>(pData + cnt) == TRUE;
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 14822
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x503430
void CMessagePlaySound::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->PlaySound(m_soundId, m_showText, m_showCircle, FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5D30
CMessageReputationChange::CMessageReputationChange(SHORT deltaRep, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_deltaRep = deltaRep;
}

// 0x4536E0
SHORT CMessageReputationChange::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageReputationChange::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5D60
BYTE CMessageReputationChange::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_REPUTATION_CHANGE;
}

// 0x504A30
void CMessageReputationChange::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 15714
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 15735
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_deltaRep;
        cnt += sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 15758
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x504B60
BOOL CMessageReputationChange::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 15786
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_deltaRep = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 15806
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x504C00
void CMessageReputationChange::Run()
{
    g_pBaldurChitin->GetBaldurMessage()->m_bInReputationChange = TRUE;
    g_pBaldurChitin->GetObjectGame()->ReputationAdjustment(m_deltaRep, FALSE);
    g_pBaldurChitin->GetBaldurMessage()->m_bInReputationChange = FALSE;
}

// -----------------------------------------------------------------------------

// 0x4F5D70
CMessageSetActive::CMessageSetActive(BOOL active, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_active = active;
}

// 0x453510
SHORT CMessageSetActive::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetActive::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x453520
BYTE CMessageSetActive::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_ACTIVE;
}

// 0x5051C0
void CMessageSetActive::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16189
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16210
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOL*>(*pData + cnt) = m_active;
        cnt += sizeof(BOOL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16233
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x5052F0
BOOL CMessageSetActive::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16261
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_active = *reinterpret_cast<BOOL*>(pData + cnt);
    cnt += sizeof(BOOL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16287
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x5053A0
void CMessageSetActive::Run()
{
    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);
            pSprite->m_activeAI = m_active;
        } else if (pObject->GetObjectType() == CGameObject::TYPE_STATIC) {
            CGameStatic* pStatic = static_cast<CGameStatic*>(pObject);
            if (m_active) {
                pStatic->m_header.m_dwFlags |= 0x1;
            } else {
                pStatic->m_header.m_dwFlags &= ~0x1;
            }
        } else if (pObject->GetObjectType() == CGameObject::TYPE_SOUND) {
            CGameSound* pSound = static_cast<CGameSound*>(pObject);
            pSound->SetActive(m_active);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5D90
CMessageSetAISpeed::CMessageSetAISpeed(BYTE speed, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_nAISpeed = speed;
}

// 0x453510
SHORT CMessageSetAISpeed::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetAISpeed::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5DB0
BYTE CMessageSetAISpeed::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_AISPEED;
}

// 0x505490
void CMessageSetAISpeed::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16389
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BYTE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16410
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BYTE*>(*pData + cnt) = m_nAISpeed;
        cnt += sizeof(BYTE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16433
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x5055C0
BOOL CMessageSetAISpeed::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16461
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_nAISpeed = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16487
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x505660
void CMessageSetAISpeed::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_AISpeed = m_nAISpeed;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5DC0
CMessageSetCommandPause::CMessageSetCommandPause(SHORT pause, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_commandPause = pause;
}

// 0x40A0D0
SHORT CMessageSetCommandPause::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetCommandPause::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x485A00
BYTE CMessageSetCommandPause::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_COMMAND_PAUSE;
}

// 0x505700
void CMessageSetCommandPause::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16559
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16580
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_commandPause;
        cnt += sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16603
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x505830
BOOL CMessageSetCommandPause::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16631
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_commandPause = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16657
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x5058E0
void CMessageSetCommandPause::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_nCommandPause = m_commandPause;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5EB0
CMessageSetDialogWait::CMessageSetDialogWait(LONG wait, LONG waitTarget, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_wait = wait;
    m_waitTarget = waitTarget;
}

// 0x40A0D0
SHORT CMessageSetDialogWait::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetDialogWait::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x485A10
BYTE CMessageSetDialogWait::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIALOG_WAIT;
}

// 0x5062C0
void CMessageSetDialogWait::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_dialogWait = m_wait;
            pSprite->m_dialogWaitTarget = m_waitTarget;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// FIXME: `face` should be reference.
//
// 0x4F5EE0
CMessageSetDirection::CMessageSetDirection(CPoint face, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_face = face;
}

// 0x453510
SHORT CMessageSetDirection::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetDirection::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5F10
BYTE CMessageSetDirection::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIRECTION;
}

// 0x506370
void CMessageSetDirection::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17333
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(LONG)
            + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17353
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_face.x;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_face.y;
        cnt += sizeof(LONG);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x506490
BOOL CMessageSetDirection::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C17408Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16631
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    // NOTE: Other functions set additional properties after validating
    // target.

    m_face.x = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    m_face.y = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x506530
void CMessageSetDirection::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->SetDirection(m_face);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x47D7B0
CMessageSetDrawPoly::CMessageSetDrawPoly(SHORT time, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_time = time;
}

// 0x453510
SHORT CMessageSetDrawPoly::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetDrawPoly::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47D7E0
BYTE CMessageSetDrawPoly::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DRAW_POLY;
}

// 0x5065D0
void CMessageSetDrawPoly::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17503
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17524
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_time;
        cnt += sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17547
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x506700
BOOL CMessageSetDrawPoly::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17575
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_time = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17601
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x5067B0
void CMessageSetDrawPoly::Run()
{
    CGameAIBase* pAIBase;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pAIBase),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly = TRUE;

        if (pAIBase->GetObjectType() == CGameObject::TYPE_DOOR) {
            static_cast<CGameDoor*>(pAIBase)->SetDrawPoly(m_time);
        } else if (pAIBase->GetObjectType() == CGameObject::TYPE_TRIGGER) {
            static_cast<CGameTrigger*>(pAIBase)->SetDrawPoly(m_time);
        } else if (pAIBase->GetObjectType() == CGameObject::TYPE_CONTAINER) {
            static_cast<CGameContainer*>(pAIBase)->SetDrawPoly(m_time);
        }

        g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly = FALSE;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5F20
CMessageSetForceActionPick::CMessageSetForceActionPick(BOOLEAN forceActionPick, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_forceActionPick = forceActionPick;
}

// 0x40A0D0
SHORT CMessageSetForceActionPick::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetForceActionPick::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x466F70
BYTE CMessageSetForceActionPick::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_FORCE_ACTION_PICK;
}

// 0x5068C0
void CMessageSetForceActionPick::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17683
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17704
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_forceActionPick;
        cnt += sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17727
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x5069F0
BOOL CMessageSetForceActionPick::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17755
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_forceActionPick = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17781
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x506A90
void CMessageSetForceActionPick::Run()
{
    CGameAIBase* pAIBase;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pAIBase),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pAIBase->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pAIBase->m_forceActionPick = m_forceActionPick;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5F40
CMessageSetHappiness::CMessageSetHappiness(SHORT happiness, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_happiness = happiness;
}

// 0x40A0D0
SHORT CMessageSetHappiness::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetHappiness::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5F70
BYTE CMessageSetHappiness::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_HAPPINESS;
}

// 0x506B40
void CMessageSetHappiness::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 18858
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17879
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_happiness;
        cnt += sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 17902
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x506C70
BOOL CMessageSetHappiness::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17930
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_happiness = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 17956
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x506D20
void CMessageSetHappiness::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_nHappiness = m_happiness;
            pSprite->m_bHappinessChanged = TRUE;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5F80
CMessageSetInCutScene::CMessageSetInCutScene(BOOL status, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_status = status;
}

// 0x40A0D0
SHORT CMessageSetInCutScene::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetInCutScene::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x463300
BYTE CMessageSetInCutScene::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_IN_CUT_SCENE;
}

// 0x506DD0
void CMessageSetInCutScene::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 18026
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 18047
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOL*>(*pData + cnt) = m_status;
        cnt += sizeof(BOOL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 18070
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x506F00
BOOL CMessageSetInCutScene::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 18098
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_status = *reinterpret_cast<BOOL*>(pData + cnt);
    cnt += sizeof(BOOL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 18124
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x506FB0
void CMessageSetInCutScene::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->m_inCutScene = m_status;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5FA0
CMessageSetLastAttacker::CMessageSetLastAttacker(const CAIObjectType& lAttacker, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_lAttacker.Set(lAttacker);
}

// 0x4F6060
CMessageSetLastAttacker::~CMessageSetLastAttacker()
{
}

// 0x453510
SHORT CMessageSetLastAttacker::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetLastAttacker::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F6030
BYTE CMessageSetLastAttacker::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_LAST_ATTACKER;
}

// 0x5075A0
void CMessageSetLastAttacker::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_lAttacker.Set(m_lAttacker);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x45B780
CMessageSetLastObject::CMessageSetLastObject(const CAIObjectType& lAttacker, WORD type, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_lAttacker.Set(lAttacker);
    m_type = type;
}

// 0x45B840
CMessageSetLastObject::~CMessageSetLastObject()
{
}

// 0x40A0D0
SHORT CMessageSetLastObject::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetLastObject::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x45B810
BYTE CMessageSetLastObject::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_LAST_OBJECT;
}

// 0x507BA0
void CMessageSetLastObject::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            switch (m_type) {
            case 2:
                pSprite->m_lAttacker.Set(m_lAttacker);
                break;
            case 3:
                pSprite->m_lHelp.Set(m_lAttacker);
                break;
            case 6:
                pSprite->m_lOrderedBy.Set(m_lAttacker);
                break;
            case 7:
                pSprite->m_lTalkedTo.Set(m_lAttacker);
                break;
            case 32:
                pSprite->m_lHitter.Set(m_lAttacker);
                break;
            case 47:
                pSprite->m_lHeard.Set(m_lAttacker);
                break;
            case 16412:
                pSprite->m_lSeen.Set(m_lAttacker);
                break;
            default:
                pSprite->m_lTrigger.Set(m_lAttacker);
                break;
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F60B0
CMessageSetNumTimesTalkedTo::CMessageSetNumTimesTalkedTo(LONG times, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_nNumTimesTalkedTo = times;
}

// 0x43E170
SHORT CMessageSetNumTimesTalkedTo::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageSetNumTimesTalkedTo::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F60D0
BYTE CMessageSetNumTimesTalkedTo::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_NUM_TIMES_TALKED_TO;
}

// 0x507CF0
void CMessageSetNumTimesTalkedTo::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 18936
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 18957
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_nNumTimesTalkedTo;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 18980
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x507E20
BOOL CMessageSetNumTimesTalkedTo::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 19008
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_nNumTimesTalkedTo = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 19034
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x507ED0
void CMessageSetNumTimesTalkedTo::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_nNumberOfTimesTalkedTo = m_nNumTimesTalkedTo;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x453530
CMessageSetSequence::CMessageSetSequence(BYTE sequence, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_sequence = sequence;
}

// 0x453510
SHORT CMessageSetSequence::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetSequence::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x453550
BYTE CMessageSetSequence::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_SEQUENCE;
}

// 0x5086D0
void CMessageSetSequence::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 19503
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BYTE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 19523
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BYTE*>(*pData + cnt) = m_sequence;
        cnt += sizeof(BYTE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 19546
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x508800
BOOL CMessageSetSequence::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 19574
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_sequence = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 19600
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x5088A0
void CMessageSetSequence::Run()
{
    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);

            // NOTE: Uninline.
            if (pSprite->GetAnimation()->GetAnimationId() != 0xEC0B) {
                pSprite->CheckSequence(m_sequence);
            }

            pSprite->SetSequence(m_sequence);

            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID) {
                pSprite->m_bSendSpriteUpdate = TRUE;
            }
        } else if (pObject->GetObjectType() == CGameObject::TYPE_STATIC) {
            CGameStatic* pStatic = static_cast<CGameStatic*>(pObject);
            pStatic->m_vidCell.SequenceSet(m_sequence);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F61B0
CMessageSetTrigger::CMessageSetTrigger(const CAITrigger& trigger, LONG caller, LONG target)
    : CMessage(caller, target)
    , m_trigger(CAITrigger::NO_TRIGGER, 0)
{
    m_trigger = trigger;
}

// 0x409370
CMessageSetTrigger::~CMessageSetTrigger()
{
}

// 0x40A0D0
SHORT CMessageSetTrigger::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSetTrigger::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x409340
BYTE CMessageSetTrigger::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_TRIGGER;
}

// 0x50A360
void CMessageSetTrigger::Run()
{
    CGameAIBase* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pSprite->SetTrigger(m_trigger);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined
CMessageSpriteDeath::CMessageSpriteDeath(DWORD nDeathType, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_nDeathType = nDeathType;
}

// 0x4088A0
SHORT CMessageSpriteDeath::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageSpriteDeath::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4AD360
BYTE CMessageSpriteDeath::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPRITE_DEATH;
}

// 0x50B1C0
void CMessageSpriteDeath::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21835
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(DWORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 21856
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_nDeathType;
        cnt += sizeof(DWORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 21879
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x50B2F0
BOOL CMessageSpriteDeath::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21907
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_nDeathType = *reinterpret_cast<DWORD*>(pData + cnt);
    cnt += sizeof(DWORD);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21933
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x50B3A0
void CMessageSpriteDeath::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameEffectDeath death;
            death.m_dwFlags = m_nDeathType;
            death.ApplyEffect(pSprite);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F62C0
CMessageSpritePetrify::CMessageSpritePetrify(BOOLEAN bPetrify, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bPetrify = bPetrify;
}

// 0x4088A0
SHORT CMessageSpritePetrify::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageSpritePetrify::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F62E0
BYTE CMessageSpritePetrify::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPRITE_PETRIFY;
}

// 0x50BE80
void CMessageSpritePetrify::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 22552
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 22573
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bPetrify;
        cnt += sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 22597
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x50BFB0
BOOL CMessageSpritePetrify::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 22625
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_bPetrify = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 22651
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x50C050
void CMessageSpritePetrify::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            if (m_bPetrify == TRUE) {
                CGameEffectPetrification petrify;
                petrify.ApplyEffect(pSprite);
            } else {
                CGameEffectStoneToFlesh unpetrify;
                unpetrify.ApplyEffect(pSprite);
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6390
CMessageStartFollow::CMessageStartFollow(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageStartFollow::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageStartFollow::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x40A0F0
BYTE CMessageStartFollow::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_FOLLOW;
}

// 0x50EEE0
void CMessageStartFollow::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 24971
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 24991
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x50EFE0
BOOL CMessageStartFollow::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25043
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50F060
void CMessageStartFollow::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_followStart = 1;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6480
CMessageStopActions::CMessageStopActions(LONG caller, LONG target, CGameSprite* pSprite)
    : CMessage(caller, target)
{
    if (pSprite != NULL) {
        pSprite->DropPath();
        pSprite->DropSearchRequest();
        pSprite->ClearActions(FALSE);
        pSprite->SetCurrAction(CAIAction::NULL_ACTION);
        pSprite->SetIdleSequence();
        pSprite->m_targetPoint.x = -1;
        pSprite->m_targetPoint.y = -1;
    }
}

// 0x4088A0
SHORT CMessageStopActions::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageStopActions::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4088B0
BYTE CMessageStopActions::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_ACTIONS;
}

// 0x50F860
void CMessageStopActions::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25556
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 25576
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 25596
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x50F980
BOOL CMessageStopActions::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25624
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50F9F0
void CMessageStopActions::Run()
{
    CGameAIBase* pAIBase;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pAIBase),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pAIBase->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameSprite* pSprite = static_cast<CGameSprite*>(pAIBase);
            pSprite->DropPath();
            pSprite->DropSearchRequest();
            pSprite->ClearActions(FALSE);
            pSprite->SetCurrAction(CAIAction::NULL_ACTION);
            pSprite->SetIdleSequence();
            pSprite->m_targetPoint.x = -1;
            pSprite->m_targetPoint.y = -1;
        } else if ((pAIBase->GetObjectType() & CGameObject::TYPE_AIBASE) != 0) {
            pAIBase->ClearActions(FALSE);
            pAIBase->SetCurrAction(CAIAction::NULL_ACTION);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6520
CMessageStopFollow::CMessageStopFollow(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x40A0D0
SHORT CMessageStopFollow::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageStopFollow::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x409810
BYTE CMessageStopFollow::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_FOLLOW;
}

// 0x50FB00
void CMessageStopFollow::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25731
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 25751
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x50FC00
BOOL CMessageStopFollow::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25803
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50FC80
void CMessageStopFollow::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_followStart = 0;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6720
CMessageTriggerStatus::CMessageTriggerStatus(DWORD flags, WORD trapActivated, WORD trapDetected, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_dwFlags = flags;
    m_trapActivated = trapActivated;
    m_trapDetected = trapDetected;
}

// 0x43E170
SHORT CMessageTriggerStatus::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageTriggerStatus::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x466210
BYTE CMessageTriggerStatus::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_TRIGGER_STATUS;
}

// 0x5105B0
void CMessageTriggerStatus::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26399
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(remoteObjectID)
            + sizeof(LONG)
            + sizeof(DWORD)
            + sizeof(WORD)
            + sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26422
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_dwFlags;
        cnt += sizeof(DWORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapActivated;
        cnt += sizeof(WORD);

        *reinterpret_cast<WORD*>(*pData + cnt) = m_trapDetected;
        cnt += sizeof(WORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26452
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x5106F0
BOOL CMessageTriggerStatus::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26480
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_dwFlags = *reinterpret_cast<DWORD*>(pData + cnt);
    cnt += sizeof(DWORD);

    m_trapActivated = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    m_trapDetected = *reinterpret_cast<WORD*>(pData + cnt);
    cnt += sizeof(WORD);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x510790
void CMessageTriggerStatus::Run()
{
    CGameTrigger* pTrigger;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pTrigger),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pTrigger->m_dwFlags = m_dwFlags;
        pTrigger->m_trapActivated = m_trapActivated;
        pTrigger->m_trapDetected = m_trapDetected;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6760
CMessageUnlock::CMessageUnlock(DWORD flags, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_dwFlags = flags;
}

// 0x40A0D0
SHORT CMessageUnlock::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageUnlock::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x466F80
BYTE CMessageUnlock::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_UNLOCK;
}

// 0x510840
void CMessageUnlock::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26595
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(DWORD);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26616
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_dwFlags;
        cnt += sizeof(DWORD);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x510950
BOOL CMessageUnlock::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 22625
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_dwFlags = *reinterpret_cast<DWORD*>(pData + cnt);
    cnt += sizeof(DWORD);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 22651
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x5109E0
void CMessageUnlock::Run()
{
    CGameAIBase* pAIBase;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pAIBase),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pAIBase->GetObjectType() == CGameObject::TYPE_DOOR) {
            CGameDoor* pDoor = static_cast<CGameDoor*>(pAIBase);

            // TODO: Unclear.
            pDoor->m_dwFlags ^= (pDoor->m_dwFlags ^ m_dwFlags) & 0x2;

            CMessageDoorStatus* pMessage = new CMessageDoorStatus(pDoor,
                m_targetId,
                m_targetId);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        } else if (pAIBase->GetObjectType() == CGameObject::TYPE_CONTAINER) {
            CGameContainer* pContainer = static_cast<CGameContainer*>(pAIBase);

            pContainer->SetFlags(m_dwFlags);

            CMessageContainerStatus* pMessage = new CMessageContainerStatus(pContainer->m_dwFlags,
                pContainer->m_trapActivated,
                pContainer->m_trapDetected,
                m_targetId,
                m_targetId);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6780
CMessageUpdateReaction::CMessageUpdateReaction(LONG nReaction, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_nReaction = nReaction;
}

// 0x453510
SHORT CMessageUpdateReaction::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageUpdateReaction::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x45DEC0
BYTE CMessageUpdateReaction::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_UPDATE_REACTION;
}

// 0x510BA0
void CMessageUpdateReaction::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26786
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26807
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_nReaction;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26830
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x510CD0
BOOL CMessageUpdateReaction::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26858
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_nReaction = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x510D50
void CMessageUpdateReaction::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_reactionRoll = static_cast<BYTE>(m_nReaction);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F67A0
CMessageVerbalConstant::CMessageVerbalConstant(LONG verbalConstant, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_verbalConstant = verbalConstant;
}

// 0x453510
SHORT CMessageVerbalConstant::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageVerbalConstant::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4535E0
BYTE CMessageVerbalConstant::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_VERBAL_CONSTANT;
}

// 0x510DF0
void CMessageVerbalConstant::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26957
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26978
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_verbalConstant;
        cnt += sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 27001
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x510F20
BOOL CMessageVerbalConstant::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 27029
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_verbalConstant = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x510FA0
void CMessageVerbalConstant::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->VerbalConstant(m_verbalConstant);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F67C0
CMessageVisibilityMapMove::CMessageVisibilityMapMove(BOOLEAN moveOn, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_moveOntoList = moveOn;
}

// 0x453510
SHORT CMessageVisibilityMapMove::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageVisibilityMapMove::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4AD370
BYTE CMessageVisibilityMapMove::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_VISIBILITY_MAP_MOVE;
}

// 0x511040
void CMessageVisibilityMapMove::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 27127
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 27148
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_moveOntoList;
        cnt += sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 27171
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x511170
BOOL CMessageVisibilityMapMove::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 27199
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_moveOntoList = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x5111F0
void CMessageVisibilityMapMove::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            if (m_moveOntoList) {
                CGameArea* pArea = pSprite->GetArea();
                if (pArea != NULL) {
                    pArea->m_visibility.AddCharacter(pSprite->GetPos(),
                        pSprite->GetId(),
                        pSprite->GetVisibleTerrainTable());
                    pSprite->m_posLastVisMapEntry = pSprite->GetPos();
                }
            } else {
                CGameArea* pArea = pSprite->GetArea();
                if (pArea != NULL) {
                    pArea->m_visibility.RemoveCharacter(pSprite->GetPos(),
                        pSprite->GetId(),
                        pSprite->GetVisibleTerrainTable());
                }
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// FIXME: `dialog` should be reference.
//
// 0x4F5E30
CMessageSetDialogResRef::CMessageSetDialogResRef(CResRef dialog, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_cResRefDialog = dialog;
}

// 0x4088A0
SHORT CMessageSetDialogResRef::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageSetDialogResRef::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4B2330
BYTE CMessageSetDialogResRef::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_DIALOG_RESREF;
}

// 0x505F50
void CMessageSetDialogResRef::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_dialog = m_cResRefDialog;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F5680
CMessageEscapeArea::CMessageEscapeArea(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x4536E0
SHORT CMessageEscapeArea::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageEscapeArea::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F56A0
BYTE CMessageEscapeArea::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ESCAPE_AREA;
}

// 0x4FF4B0
void CMessageEscapeArea::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11068
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11089
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11109
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FF5D0
BOOL CMessageEscapeArea::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11137
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11160
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FF670
void CMessageEscapeArea::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_bEscapingArea = TRUE;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x48AC30
CMessageDisplayTextRefSend::CMessageDisplayTextRefSend(STRREF name, STRREF text, COLORREF nameColor, COLORREF textColor, LONG marker, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_name = name;
    m_text = text;
    m_nameColor = nameColor;
    m_textColor = textColor;
    m_marker = marker;
    m_moveToTop = FALSE;
}

// 0x40A0D0
SHORT CMessageDisplayTextRefSend::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageDisplayTextRefSend::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x489670
BYTE CMessageDisplayTextRefSend::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF_SEND;
}

// 0x4FCA10
void CMessageDisplayTextRefSend::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8934
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID)
        + sizeof(LONG)
        + sizeof(STRREF)
        + sizeof(STRREF)
        + sizeof(COLORREF)
        + sizeof(COLORREF)
        + sizeof(LONG)
        + sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 8962
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    *reinterpret_cast<STRREF*>(*pData + cnt) = m_name;
    cnt += sizeof(STRREF);

    *reinterpret_cast<STRREF*>(*pData + cnt) = m_text;
    cnt += sizeof(STRREF);

    *reinterpret_cast<COLORREF*>(*pData + cnt) = m_nameColor;
    cnt += sizeof(COLORREF);

    *reinterpret_cast<COLORREF*>(*pData + cnt) = m_textColor;
    cnt += sizeof(COLORREF);

    *reinterpret_cast<LONG*>(*pData + cnt) = m_marker;
    cnt += sizeof(LONG);

    *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_moveToTop;
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9003
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FCB60
BOOL CMessageDisplayTextRefSend::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9031
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_name = *reinterpret_cast<STRREF*>(pData + cnt);
    cnt += sizeof(STRREF);

    m_text = *reinterpret_cast<STRREF*>(pData + cnt);
    cnt += sizeof(STRREF);

    m_nameColor = *reinterpret_cast<COLORREF*>(pData + cnt);
    cnt += sizeof(COLORREF);

    m_textColor = *reinterpret_cast<COLORREF*>(pData + cnt);
    cnt += sizeof(COLORREF);

    m_marker = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    m_moveToTop = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 9076
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FCC30
void CMessageDisplayTextRefSend::Run()
{
    STR_RES strResName;
    STR_RES strResText;
    CString sName("");

    BYTE rc;
    CGameSprite* pSprite;

    if (m_name >= -7 && m_name != -1) {
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(-2 - m_name);

        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            sName = pSprite->GetName();

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    } else {
        g_pBaldurChitin->GetTlkTable().Fetch(m_name, strResName);
        sName = strResName.szText;
    }

    g_pBaldurChitin->GetTlkTable().Fetch(m_text, strResText);

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (strResText.cSound.GetRes() != NULL) {
            if (strResText.cSound.m_nLooping == 0) {
                strResText.cSound.SetFireForget(TRUE);
            }

            strResText.cSound.SetChannel(14, reinterpret_cast<DWORD>(pSprite->GetArea()));

            // FIXME: Calls `GetPos` twice.
            strResText.cSound.Play(pSprite->GetPos().x,
                pSprite->GetPos().y,
                0,
                FALSE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    g_pBaldurChitin->m_pEngineWorld->DisplayText(sName,
        strResText.szText,
        m_nameColor,
        m_textColor,
        m_marker,
        m_moveToTop);
}

// -----------------------------------------------------------------------------

// 0x4F5DF0
CMessageSetCurrentActionId::CMessageSetCurrentActionId(SHORT actionId, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_actionId = actionId;
}

// 0x453510
SHORT CMessageSetCurrentActionId::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSetCurrentActionId::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5E20
BYTE CMessageSetCurrentActionId::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SET_CURRENT_ACTION_ID;
}

// 0x505980
void CMessageSetCurrentActionId::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16735
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16756
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_actionId;
        cnt += sizeof(SHORT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 16779
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x505AB0
BOOL CMessageSetCurrentActionId::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16807
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_actionId = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 16833
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x505B60
void CMessageSetCurrentActionId::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_currentActionId = m_actionId;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6810
CMessageStartTextScreen::CMessageStartTextScreen(const CResRef& ref, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_screen = ref;
}

// 0x4088A0
SHORT CMessageStartTextScreen::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageStartTextScreen::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4535F0
BYTE CMessageStartTextScreen::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_TEXT_SCREEN;
}

// 0x508D30
void CMessageStartTextScreen::Run()
{
    // NOTE: Unused.
    CString sScreen;

    m_screen.CopyToString(sScreen);

    g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineChapter);
}

// -----------------------------------------------------------------------------

// 0x4F6270
CMessageSpawnPtActivate::CMessageSpawnPtActivate(BOOLEAN bActivate, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bActivate = bActivate;
}

// 0x453510
SHORT CMessageSpawnPtActivate::GetCommType()
{
    return BROADCAST;
}

// 0x40A0E0
BYTE CMessageSpawnPtActivate::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x467A70
BYTE CMessageSpawnPtActivate::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPAWNPT_ACTIVATE;
}

// 0x50AD10
void CMessageSpawnPtActivate::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21488
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(BOOLEAN);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 21509
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bActivate;
        cnt += sizeof(BOOLEAN);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x50AE20
BOOL CMessageSpawnPtActivate::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21564
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_bActivate = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50AEC0
void CMessageSpawnPtActivate::Run()
{
    CGameSpawning* pSpawning;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSpawning),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSpawning->GetObjectType() == CGameObject::TYPE_SPAWNING) {
            pSpawning->m_spawningObject.m_activated = m_bActivate;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6290
CMessageSpawnPtSpawn::CMessageSpawnPtSpawn(const CPoint& ptFacingTowards, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_ptFacingTowards = ptFacingTowards;
}

// 0x40A0D0
SHORT CMessageSpawnPtSpawn::GetCommType()
{
    return SEND;
}

// 0x40A0E0
BYTE CMessageSpawnPtSpawn::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x467BA0
BYTE CMessageSpawnPtSpawn::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_SPAWNPT_SPAWN;
}

// 0x50AF60
void CMessageSpawnPtSpawn::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21658
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(LONG)
            + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 21679
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_ptFacingTowards.x;
        cnt += sizeof(LONG);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_ptFacingTowards.y;
        cnt += sizeof(LONG);

        // NOTE: Missing trailing guard.
    } else {
        *dwSize = 0;
    }
}

// 0x50B080
BOOL CMessageSpawnPtSpawn::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 21735
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_ptFacingTowards.x = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    m_ptFacingTowards.y = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50B120
void CMessageSpawnPtSpawn::Run()
{
    CGameSpawning* pSpawning;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSpawning),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSpawning->GetObjectType() == CGameObject::TYPE_SPAWNING) {
            pSpawning->Spawn(m_ptFacingTowards, 0);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6460
CMessageStaticStart::CMessageStaticStart(BOOLEAN bStart, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bStart = bStart;
}

// 0x43E170
SHORT CMessageStaticStart::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageStaticStart::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x467C40
BYTE CMessageStaticStart::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STATIC_START;
}

// 0x50F610
void CMessageStaticStart::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25385
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID)
        + sizeof(LONG)
        + sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25406
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bStart;
    cnt += sizeof(BOOLEAN);

    // NOTE: Missing trailing guard.
}

// 0x50F720
BOOL CMessageStaticStart::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25462
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_bStart = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50F7B0
void CMessageStaticStart::Run()
{
    CGameStatic* pStatic;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pStatic),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pStatic->GetObjectType() == CGameObject::TYPE_STATIC) {
            if (m_bStart) {
                pStatic->m_header.m_dwFlags &= ~0x8;
            } else {
                pStatic->m_header.m_dwFlags |= 0x8;
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F65C0
CMessageStoreAddItem::CMessageStoreAddItem(const CResRef& store, const CCreatureFileItem& item, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_store = store;
    memcpy(&m_item, &item, sizeof(CCreatureFileItem));
}

// 0x4536E0
SHORT CMessageStoreAddItem::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageStoreAddItem::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F6660
BYTE CMessageStoreAddItem::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_ADD_ITEM;
}

// 0x50FE30
void CMessageStoreAddItem::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26002
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = RESREF_SIZE
        + sizeof(CCreatureFileItem);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26011
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    memcpy(*pData + cnt, m_store.GetResRef(), RESREF_SIZE);
    cnt += RESREF_SIZE;

    memcpy(*pData + cnt, &m_item, sizeof(CCreatureFileItem));
    cnt += sizeof(CCreatureFileItem);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26032
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x50FED0
BOOL CMessageStoreAddItem::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26056
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_store = pData + cnt;
    cnt += RESREF_SIZE;

    memcpy(&m_item, pData + cnt, sizeof(CCreatureFileItem));
    cnt += sizeof(CCreatureFileItem);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50FF30
void CMessageStoreAddItem::Run()
{
    CStore* pStore;

    if (g_pChitin->cNetwork.GetSessionHosting()) {
        pStore = g_pBaldurChitin->GetObjectGame()->GetServerStore(m_store);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26111
        UTIL_ASSERT(pStore != NULL);

        pStore->AddItemExt(CItem(m_item), 1);
    } else if (g_pChitin->cNetwork.GetSessionOpen()) {
        CStore::InvalidateStore(m_store);
    }

    pStore = g_pBaldurChitin->m_pEngineStore->m_pStore;
    if (pStore != NULL) {
        if (pStore->m_resRef == m_store) {
            CItem item(m_item);
            pStore->AddItemExt(item, 1);
            g_pBaldurChitin->m_pEngineStore->UpdateStoreItems();
            g_pBaldurChitin->m_pEngineStore->UpdateStoreCost();

            if (g_pBaldurChitin->m_pEngineWorld->field_EE0 != CGameObjectArray::BAD_INDEX) {
                CGameObject* pObject;

                BYTE rc;
                do {
                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc == CGameObjectArray::SUCCESS) {
                    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                        || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                        g_pBaldurChitin->m_pEngineStore->UpdateMainPanel();
                    }

                    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }
        } else {
            pStore = g_pBaldurChitin->m_pEngineStore->m_pBag;
            if (pStore != NULL && pStore->m_resRef == m_store) {
                CItem item(m_item);
                pStore->AddItemExt(item, 1);
                g_pBaldurChitin->m_pEngineStore->UpdateGroupItems();
                g_pBaldurChitin->m_pEngineStore->UpdateGroupCost();

                if (g_pBaldurChitin->m_pEngineWorld->field_EE0 != CGameObjectArray::BAD_INDEX) {
                    CGameObject* pObject;

                    BYTE rc;
                    do {
                        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
                            CGameObjectArray::THREAD_ASYNCH,
                            &pObject,
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                            || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                            g_pBaldurChitin->m_pEngineStore->UpdateMainPanel();
                        }

                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------

// 0x4F6670
CMessageStoreRemoveItem::CMessageStoreRemoveItem(const CResRef& store, const CResRef& itemId, int a3, int a4, int a5, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_store = store;
    m_itemId = itemId;
    field_1C = a3;
    field_20 = a4;
    field_24 = a5;
}

// 0x848F48
SHORT CMessageStoreRemoveItem::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageStoreRemoveItem::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47E020
BYTE CMessageStoreRemoveItem::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_REMOVE_ITEM;
}

// 0x5102B0
void CMessageStoreRemoveItem::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26219
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = RESREF_SIZE
        + RESREF_SIZE
        + sizeof(int)
        + sizeof(int)
        + sizeof(int);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26225
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    memcpy(*pData + cnt, m_store.GetResRef(), RESREF_SIZE);
    cnt += RESREF_SIZE;

    memcpy(*pData + cnt, m_itemId.GetResRef(), RESREF_SIZE);
    cnt += RESREF_SIZE;

    *reinterpret_cast<int*>(*pData + cnt) = field_1C;
    cnt += sizeof(int);

    *reinterpret_cast<int*>(*pData + cnt) = field_20;
    cnt += sizeof(int);

    *reinterpret_cast<int*>(*pData + cnt) = field_24;
    cnt += sizeof(int);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26247
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x510370
BOOL CMessageStoreRemoveItem::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 26270
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_store = pData + cnt;
    cnt += RESREF_SIZE;

    m_itemId = pData + cnt;
    cnt += RESREF_SIZE;

    field_1C = *reinterpret_cast<int*>(pData + cnt);
    cnt += sizeof(int);

    field_20 = *reinterpret_cast<int*>(pData + cnt);
    cnt += sizeof(int);

    field_24 = *reinterpret_cast<int*>(pData + cnt);
    cnt += sizeof(int);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x5103F0
void CMessageStoreRemoveItem::Run()
{
    CStore* pStore;

    if (g_pChitin->cNetwork.GetSessionHosting()) {
        pStore = g_pBaldurChitin->GetObjectGame()->GetServerStore(m_store);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 26322
        UTIL_ASSERT(pStore != NULL);

        if (pStore->GetItemIndex(m_itemId) != INT_MAX) {
            pStore->RemoveItemExt(m_itemId,
                field_1C,
                field_20,
                field_24,
                NULL);
        }
    } else if (g_pChitin->cNetwork.GetSessionOpen()) {
        CStore::InvalidateStore(m_store);
    }

    pStore = g_pBaldurChitin->m_pEngineStore->m_pStore;
    if (pStore != NULL) {
        if (pStore->m_resRef == m_store) {
            if (pStore->GetItemIndex(m_itemId) != INT_MAX) {
                pStore->RemoveItemExt(m_itemId,
                    field_1C,
                    field_20,
                    field_24,
                    NULL);

                g_pBaldurChitin->m_pEngineStore->UpdateStoreItems();
                g_pBaldurChitin->m_pEngineStore->UpdateStoreCost();
                g_pBaldurChitin->m_pEngineStore->UpdateMainPanel();
            }
        } else {
            pStore = g_pBaldurChitin->m_pEngineStore->m_pBag;
            if (pStore != NULL && pStore->m_resRef == m_store) {
                if (pStore->GetItemIndex(m_itemId) != INT_MAX) {
                    pStore->RemoveItemExt(m_itemId,
                        field_1C,
                        field_20,
                        field_24,
                        NULL);

                    g_pBaldurChitin->m_pEngineStore->UpdateGroupItems();
                    g_pBaldurChitin->m_pEngineStore->UpdateGroupCost();
                    g_pBaldurChitin->m_pEngineStore->UpdateMainPanel();
                }
            }
        }
    }
}

// -----------------------------------------------------------------------------

// 0x4F5780
CMessageFamiliarAdd::CMessageFamiliarAdd(BOOLEAN bFamiliarAdd, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_bFamiliarAdd = bFamiliarAdd;
}

// 0x43E170
SHORT CMessageFamiliarAdd::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageFamiliarAdd::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x453480
BYTE CMessageFamiliarAdd::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_FAMILIAR_ADD;
}

// 0x4FFF90
void CMessageFamiliarAdd::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11921
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID)
        + sizeof(LONG)
        + sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11944
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_bFamiliarAdd;
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11967
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x5000C0
BOOL CMessageFamiliarAdd::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11994
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    m_bFamiliarAdd = *reinterpret_cast<BOOLEAN*>(pData + cnt);
    cnt += sizeof(BOOLEAN);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12021
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x500170
void CMessageFamiliarAdd::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            if (pSprite->m_bGlobal) {
                if (m_bFamiliarAdd) {
                    pSprite->SetAIType(CAIObjectType(CAIObjectType::EA_FAMILIAR), TRUE, FALSE);
                    g_pBaldurChitin->GetObjectGame()->AddCharacterToFamiliars(m_targetId);
                } else {
                    pSprite->SetAIType(CAIObjectType(CAIObjectType::EA_NEUTRAL), TRUE, FALSE);
                    g_pBaldurChitin->GetObjectGame()->RemoveCharacterFromFamiliars(m_targetId);
                }
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F57A0
CMessageFamiliarRemoveResRef::CMessageFamiliarRemoveResRef(const CResRef& resRef, BYTE nAlignment, BYTE nLevel, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_resRef = resRef;
    m_nAlignment = nAlignment;
    m_nLevel = nLevel;
}

// 0x4536E0
SHORT CMessageFamiliarRemoveResRef::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageFamiliarRemoveResRef::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F5820
BYTE CMessageFamiliarRemoveResRef::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_FAMILIAR_REMOVE_RESREF;
}

// 0x500320
void CMessageFamiliarRemoveResRef::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12100
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = RESREF_SIZE
        + sizeof(BYTE)
        + sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12107
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    memcpy(*pData + cnt, m_resRef.GetResRef(), RESREF_SIZE);

    *reinterpret_cast<BYTE*>(*pData + cnt) = m_nAlignment;
    cnt += sizeof(BYTE);

    *reinterpret_cast<BYTE*>(*pData + cnt) = m_nLevel;
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12129
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x5003C0
BOOL CMessageFamiliarRemoveResRef::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12152
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_resRef = pData + cnt;
    cnt += RESREF_SIZE;

    m_nAlignment = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    m_nLevel = *reinterpret_cast<BYTE*>(pData + cnt);
    cnt += sizeof(BYTE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 12165
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x500440
void CMessageFamiliarRemoveResRef::Run()
{
    g_pBaldurChitin->GetObjectGame()->RemoveFamiliarResRef(m_resRef,
        m_nAlignment,
        m_nLevel);
}

// -----------------------------------------------------------------------------

// 0x4F56B0
CMessageStopEscapeArea::CMessageStopEscapeArea(LONG caller, LONG target)
    : CMessage(caller, target)
{
}

// 0x4536E0
SHORT CMessageStopEscapeArea::GetCommType()
{
    return BROADCAST_FORCED_OTHERS;
}

// 0x40A0E0
BYTE CMessageStopEscapeArea::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x4F56D0
BYTE CMessageStopEscapeArea::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STOP_ESCAPE_AREA;
}

// 0x4FF710
void CMessageStopEscapeArea::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11247
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    } else {
        remotePlayerID = 0;
        remoteObjectID = CGameObjectArray::INVALID_INDEX;
    }

    *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11268
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
    cnt += sizeof(PLAYER_ID);

    *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
    cnt += sizeof(LONG);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11288
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x4FF830
BOOL CMessageStopEscapeArea::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11316
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) == TRUE) {
        m_targetId = localObjectID;
    } else {
        m_targetId = CGameObjectArray::INVALID_INDEX;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 11339
    UTIL_ASSERT(cnt == dwSize);

    return TRUE;
}

// 0x4FF8D0
void CMessageStopEscapeArea::Run()
{
    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetObjectType() == CGameObject::TYPE_SPRITE) {
            pSprite->m_bEscapingArea = FALSE;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6540
CMessageStoreRelease::CMessageStoreRelease(const CResRef& store, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_store = store;
}

// 0x43E170
SHORT CMessageStoreRelease::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageStoreRelease::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47E010
BYTE CMessageStoreRelease::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_RELEASE;
}

// 0x50FD20
void CMessageStoreRelease::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25889
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = RESREF_SIZE;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25894
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    memcpy(*pData + cnt, m_store.GetResRef(), RESREF_SIZE);
    cnt += RESREF_SIZE;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25910
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x50FDB0
BOOL CMessageStoreRelease::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 25934
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_store = pData + cnt;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x50FE00
void CMessageStoreRelease::Run()
{
    if (g_pChitin->cNetwork.GetSessionHosting()) {
        g_pBaldurChitin->GetObjectGame()->ReleaseServerStore(m_store);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6C30
CMessageStartCombatMusic::CMessageStartCombatMusic(int slot, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_slot = slot;
}

// 0x4088A0
SHORT CMessageStartCombatMusic::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageStartCombatMusic::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47A010
BYTE CMessageStartCombatMusic::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_START_COMBAT_MUSIC;
}

// 0x513CB0
void CMessageStartCombatMusic::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 29620
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;
    PLAYER_ID remotePlayerID;
    LONG remoteObjectID;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        remotePlayerID = pObject->m_remotePlayerID;
        remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        *dwSize = sizeof(PLAYER_ID) + sizeof(LONG);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 29641
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<int*>(*pData + cnt) = m_slot;
        cnt += sizeof(int);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 29664
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x513DE0
BOOL CMessageStartCombatMusic::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 29678
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    m_slot = *reinterpret_cast<int*>(pData + cnt);
    cnt += sizeof(int);

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x513E60
void CMessageStartCombatMusic::Run()
{
    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pObject),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pObject->GetArea()->PlaySong(m_slot, 0x10000 | 0x100 | 0x80 | 0x40 | 0x20 | 0x10 | 0x04);

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// -----------------------------------------------------------------------------

// 0x4F6CC0
CMessageStoreDemand::CMessageStoreDemand(const CResRef& store, LONG caller, LONG target)
    : CMessage(caller, target)
{
    m_store = store;
}

// 0x43E170
SHORT CMessageStoreDemand::GetCommType()
{
    return BROADCAST_FORCED;
}

// 0x40A0E0
BYTE CMessageStoreDemand::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x47E030
BYTE CMessageStoreDemand::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_DEMAND;
}

// 0x5143F0
void CMessageStoreDemand::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30020
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    *dwSize = RESREF_SIZE;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30025
    UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

    DWORD cnt = 0;

    memcpy(*pData + cnt, m_store.GetResRef(), RESREF_SIZE);
    cnt += RESREF_SIZE;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30041
    UTIL_ASSERT(cnt == *dwSize);
}

// 0x514480
BOOL CMessageStoreDemand::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30065
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    m_store = pData + cnt;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x5144D0
void CMessageStoreDemand::Run()
{
    if (g_pChitin->cNetwork.GetSessionHosting()) {
        g_pBaldurChitin->GetObjectGame()->DemandServerStore(m_store, FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x514770
CMessageWeaponImmumityUpdate::CMessageWeaponImmumityUpdate(CGameSprite* pSprite, LONG caller, LONG target)
    : CMessage(caller, target)
{
    if (pSprite != NULL) {
        m_weaponImmunities = pSprite->GetDerivedStats()->m_cImmunitiesWeapon;
    }
}

// 0x4F7050
CMessageWeaponImmumityUpdate::~CMessageWeaponImmumityUpdate()
{
}

// 0x4088A0
SHORT CMessageWeaponImmumityUpdate::GetCommType()
{
    return BROADCAST_OTHERS;
}

// 0x40A0E0
BYTE CMessageWeaponImmumityUpdate::GetMsgType()
{
    return CBaldurMessage::MSG_TYPE_CMESSAGE;
}

// 0x514800
BYTE CMessageWeaponImmumityUpdate::GetMsgSubType()
{
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_WEAPON_IMMUNITIES_UPDATE;
}

// 0x514830
void CMessageWeaponImmumityUpdate::MarshalMessage(BYTE** pData, DWORD* dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30314
    UTIL_ASSERT(pData != NULL && dwSize != NULL);

    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
        LONG remoteObjectID = pObject->m_remoteObjectID;

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        BYTE* immunities;
        ULONG immunitySize = m_weaponImmunities.Marshal(&immunities);

        *dwSize = sizeof(PLAYER_ID)
            + sizeof(LONG)
            + sizeof(ULONG)
            + immunitySize;

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 30342
        UTIL_ASSERT(*dwSize <= STATICBUFFERSIZE);

        DWORD cnt = 0;

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = remotePlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = remoteObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<ULONG*>(*pData + cnt) = immunitySize;
        cnt += sizeof(ULONG);

        memcpy(*pData + cnt, immunities, immunitySize);
        cnt += immunitySize;

        if (immunities != NULL) {
            delete immunities;
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
        // __LINE__: 30373
        UTIL_ASSERT(cnt == *dwSize);
    } else {
        *dwSize = 0;
    }
}

// 0x5149A0
BOOL CMessageWeaponImmumityUpdate::UnmarshalMessage(BYTE* pData, DWORD dwSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMessage.cpp
    // __LINE__: 30388
    UTIL_ASSERT(pData != NULL);

    DWORD cnt = CNetwork::SPEC_MSG_HEADER_LENGTH;

    PLAYER_ID remotePlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
    cnt += sizeof(PLAYER_ID);

    LONG remoteObjectID = *reinterpret_cast<LONG*>(pData + cnt);
    cnt += sizeof(LONG);

    ULONG immunitySize = *reinterpret_cast<ULONG*>(pData + cnt);
    cnt += sizeof(ULONG);

    m_weaponImmunities.Unmarshal(pData + cnt, immunitySize);
    cnt += immunitySize;

    LONG localObjectID;
    if (g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Find(remotePlayerID, remoteObjectID, localObjectID) != TRUE) {
        return FALSE;
    }

    m_targetId = localObjectID;

    // NOTE: Missing trailing guard.

    return TRUE;
}

// 0x514A30
void CMessageWeaponImmumityUpdate::Run()
{
    CGameObject* pObject;

    BYTE rc;
    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);
            pSprite->GetDerivedStats()->m_cImmunitiesWeapon = m_weaponImmunities;
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_targetId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

#include "CMessage.h"

#include "CBaldurChitin.h"
#include "CGameAIBase.h"
#include "CGameArea.h"
#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenLoad.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSinglePlayer.h"
#include "CScreenWorld.h"
#include "CUIPanel.h"
#include "CUtil.h"

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

// 0x84CEE6
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS = 15;

// 0x84CEE7
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXT = 16;

// 0x84CEE8
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DISPLAY_TEXTREF = 17;

// 0x84CEEB
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_DROP_PATH = 20;

// 0x84CEEE
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_ENTER_STORE_MODE = 23;

// 0x84CF2E
const BYTE CBaldurMessage::MSG_SUBTYPE_CMESSAGE_STORE_RELEASE = 87;

// 0x84CF76
const BYTE CBaldurMessage::DELETEAREA_EMPTY_VOTE = 101;

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
    field_F5 = 0;
    field_F6 = 0;
}

// 0x429720
CBaldurMessage::~CBaldurMessage()
{
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

    return FALSE;
}

// 0x433BE0
BOOLEAN CBaldurMessage::SendProgressBarStatus(LONG nActionProgress, LONG nActionTarget, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bTimeoutVisible, DWORD nSecondsToTimeout)
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
    return CBaldurMessage::MSG_SUBTYPE_CMESSAGE_CUT_SCENE_MODE_STATUS;
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

// NOTE: Inlined.
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

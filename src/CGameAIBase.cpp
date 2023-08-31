#include "CGameAIBase.h"

#include "CAIScript.h"
#include "CAITrigger.h"
#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CGameTimer.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CTimerWorld.h"
#include "CUtil.h"

// 0x8485C4
const SHORT CGameAIBase::ACTION_DONE = -1;

// 0x8485C6
const SHORT CGameAIBase::ACTION_INTERRUPTABLE = 1;

// 0x8485C8
const SHORT CGameAIBase::ACTION_NORMAL = 0;

// 0x8485CA
const SHORT CGameAIBase::ACTION_ERROR = -2;

// 0x8485CC
const SHORT CGameAIBase::ACTION_NO_ACTION = 2;

// 0x8485CE
const SHORT CGameAIBase::ACTION_STOPPED = -3;

// 0x8485E8
const BYTE CGameAIBase::EFFECT_LIST_TIMED = 1;

// 0x8485E9
const BYTE CGameAIBase::EFFECT_LIST_EQUIPED = 2;

// 0x8D1408
const CString CGameAIBase::DEAD_GLOBAL_PREFIX("_DEAD");

// 0x8D1810
CAIAction CGameAIBase::m_aiAction;

// 0x44C4B0
CGameAIBase::CGameAIBase()
{
    field_592 = 0;
    m_objectType = CGameObject::TYPE_AIBASE;
    m_lAttacker.Set(CAIObjectType::NOONE);
    m_lOrderedBy.Set(CAIObjectType::NOONE);
    field_EA.Set(CAIObjectType::NOONE);
    field_126.Set(CAIObjectType::NOONE);
    field_162.Set(CAIObjectType::NOONE);
    m_lHitter.Set(CAIObjectType::NOONE);
    m_lHelp.Set(CAIObjectType::NOONE);
    m_lTrigger.Set(CAIObjectType::NOONE);
    m_lSeen.Set(CAIObjectType::NOONE);
    m_lTalkedTo.Set(CAIObjectType::NOONE);
    m_lHeard.Set(CAIObjectType::NOONE);
    field_306.Set(CAIObjectType::NOONE);
    field_342.Set(CAIObjectType::NOONE);
    field_37E.Set(CAIObjectType::NOONE);
    field_3BA.Set(CAIObjectType::NOONE);
    m_curResponseNum = -1;
    m_curResponseSetNum = -1;
    m_curScriptNum = -1;
    m_curAction = CAIAction::NULL_ACTION;
    m_interrupt = FALSE;
    m_actionCount = 0;
    field_54C = 0;
    field_550 = 0;
    field_552 = 0;
    field_44A = 0;
    field_3F6 = NULL;
    field_3FA = NULL;
    field_3FE = NULL;
    field_402 = NULL;
    field_406 = NULL;
    field_40A = NULL;
    m_defaultScript = NULL;
    m_inCutScene = FALSE;
    m_reactionRoll = 10;
    field_550 = rand() % 120;

    CAITrigger trigger(CAITrigger::ONCREATION, 0);
    m_pendingTriggers.AddTail(new CAITrigger(trigger));

    m_firstCall = TRUE;
    field_57C = 0;
    field_580 = 0;
    field_592 = -1;
    field_588 = 0;
    field_58C = 0;
    field_594 = 0;
    field_595 = 1;
    field_596 = 0;
    m_randValue = rand() & 0x7FFF;
}

// 0x44D160
CGameAIBase::~CGameAIBase()
{
    POSITION pos;

    pos = m_pendingTriggers.GetHeadPosition();
    while (pos != NULL) {
        CAITrigger* pTrigger = m_pendingTriggers.GetNext(pos);
        if (pTrigger != NULL) {
            delete pTrigger;
        }
    }

    pos = m_queuedActions.GetHeadPosition();
    while (pos != NULL) {
        CAIAction* pAction = m_queuedActions.GetNext(pos);
        if (pAction != NULL) {
            delete pAction;
        }
    }

    pos = m_timers.GetHeadPosition();
    while (pos != NULL) {
        CGameTimer* pTimer = m_timers.GetNext(pos);
        if (pTimer != NULL) {
            delete pTimer;
        }
    }

    if (field_3F6 != NULL) {
        delete field_3F6;
        field_3F6 = NULL;
    }

    if (field_3FA != NULL) {
        delete field_3FA;
        field_3FA = NULL;
    }

    if (field_3FE != NULL) {
        delete field_3FE;
        field_3FE = NULL;
    }

    if (field_402 != NULL) {
        delete field_402;
        field_402 = NULL;
    }

    if (field_406 != NULL) {
        delete field_406;
        field_406 = NULL;
    }

    if (field_40A != NULL) {
        delete field_40A;
        field_40A = NULL;
    }

    if (m_defaultScript != NULL) {
        delete m_defaultScript;
        m_defaultScript = NULL;
    }
}

// 0x44D100
const BYTE* CGameAIBase::GetVisibleTerrainTable()
{
    return CGameObject::DEFAULT_VISIBLE_TERRAIN_TABLE;
}

// 0x44D110
const BYTE* CGameAIBase::GetTerrainTable()
{
    return CGameObject::DEFAULT_TERRAIN_TABLE;
}

// 0x44D120
BOOLEAN CGameAIBase::CompressTime(DWORD deltaTime)
{
    CheckTimers(deltaTime / CTimerWorld::TIMESCALE_MSEC_PER_SEC);
    return TRUE;
}

// 0x44D4B0
void CGameAIBase::CheckTimers(LONG cycles)
{
    // TODO: Incomplete.
}

// 0x44D640
void CGameAIBase::ClearActions(BOOL a1)
{
    if (a1) {
        POSITION pos = m_queuedActions.GetHeadPosition();
        while (pos != NULL) {
            POSITION curr = pos;
            CAIAction* pAction = m_queuedActions.GetNext(pos);
            if (pAction != NULL) {
                if (pAction->m_actionID != CAIAction::SPELL
                    && pAction->m_actionID != CAIAction::SPELLPOINT
                    && pAction->m_actionID != CAIAction::FORCESPELL
                    && pAction->m_actionID != CAIAction::FORCESPELLPOINT
                    && pAction->m_actionID != CAIAction::APPLYSPELL
                    && pAction->m_actionID != CAIAction::REALLYFORCESPELL
                    && pAction->m_actionID != CAIAction::SPELLNODEC
                    && pAction->m_actionID != CAIAction::SPELLPOINTNODEC) {
                    m_queuedActions.RemoveAt(curr);
                    delete pAction;
                }
            }
        }
    } else {
        POSITION pos = m_queuedActions.GetHeadPosition();
        while (pos != NULL) {
            CAIAction* pAction = m_queuedActions.GetNext(pos);
            if (pAction != NULL) {
                delete pAction;
            }
        }
        m_queuedActions.RemoveAll();
    }

    if (m_queuedActions.GetCount() == 0) {
        m_curResponseNum = -1;
        m_curResponseSetNum = -1;
        m_curScriptNum = -1;
    }
}

// 0x44D730
void CGameAIBase::ClearTriggers()
{
    ApplyTriggers();

    POSITION pos = m_pendingTriggers.GetHeadPosition();
    while (pos != NULL) {
        CAITrigger* pTrigger = m_pendingTriggers.GetNext(pos);
        if (pTrigger != NULL) {
            delete pTrigger;
        }
    }
    m_pendingTriggers.RemoveAll();
}

// 0x45D130
void CGameAIBase::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAIBase.cpp
        // __LINE__: 6886
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x44CC70
void CGameAIBase::AddAction(const CAIAction& action)
{
    CAIAction* copy = new CAIAction();
    copy->m_actionID = action.m_actionID;
    copy->m_specificID = action.m_specificID;
    copy->m_actorID.Set(action.m_actorID);
    copy->m_acteeID.Set(action.m_acteeID);
    copy->m_acteeID2.Set(action.m_acteeID2);
    copy->m_dest = action.m_dest;
    copy->m_specificID2 = action.m_specificID2;
    copy->m_specificID3 = action.m_specificID3;
    copy->m_string1 = action.m_string1;
    copy->m_string2 = action.m_string2;
    copy->m_internalFlags = action.m_internalFlags;
    m_queuedActions.AddHead(copy);
}

// 0x44CE20
void CGameAIBase::AddEffect(CGameEffect* pEffect, BYTE list, BOOL noSave, BOOL immediateApply)
{
    if (pEffect != NULL) {
        delete pEffect;
    }
}

// 0x44CE40
void CGameAIBase::ClearAI(BOOLEAN a1)
{
    ClearActions(FALSE);
    ApplyTriggers();

    POSITION pos = m_pendingTriggers.GetHeadPosition();
    while (pos != NULL) {
        CAITrigger* pTrigger = m_pendingTriggers.GetNext(pos);
        if (pTrigger != NULL) {
            delete pTrigger;
        }
    }
    m_pendingTriggers.RemoveAll();

    SetCurrAction(CAIAction::NULL_ACTION);

    m_curAction.m_actionID = CAIAction::NULL_ACTION.m_actionID;
    m_curAction.m_specificID = CAIAction::NULL_ACTION.m_specificID;
    m_curAction.m_actorID.Set(CAIAction::NULL_ACTION.m_actorID);
    m_curAction.m_acteeID.Set(CAIAction::NULL_ACTION.m_acteeID);
    m_curAction.m_acteeID2.Set(CAIAction::NULL_ACTION.m_acteeID2);
    m_curAction.m_dest = CAIAction::NULL_ACTION.m_dest;
    m_curAction.m_specificID2 = CAIAction::NULL_ACTION.m_specificID2;
    m_curAction.m_specificID3 = CAIAction::NULL_ACTION.m_specificID3;
    m_curAction.m_string1 = CAIAction::NULL_ACTION.m_string1;
    m_curAction.m_string2 = CAIAction::NULL_ACTION.m_string2;
    m_curAction.m_internalFlags = CAIAction::NULL_ACTION.m_internalFlags;
}

// 0x44CF50
void CGameAIBase::InsertAction(const CAIAction& action)
{
    CAIAction* copy = new CAIAction();
    copy->m_actionID = action.m_actionID;
    copy->m_specificID = action.m_specificID;
    copy->m_actorID.Set(action.m_actorID);
    copy->m_acteeID.Set(action.m_acteeID);
    copy->m_acteeID2.Set(action.m_acteeID2);
    copy->m_dest = action.m_dest;
    copy->m_specificID2 = action.m_specificID2;
    copy->m_specificID3 = action.m_specificID3;
    copy->m_string1 = action.m_string1;
    copy->m_string2 = action.m_string2;
    copy->m_internalFlags = action.m_internalFlags;
    m_queuedActions.AddTail(copy);
}

// 0x45D190
void CGameAIBase::SetCurrAction(const CAIAction& action)
{
    m_actionCount = 0;
    m_interrupt = FALSE;
    m_curAction.m_actionID = action.m_actionID;
    m_curAction.m_specificID = action.m_specificID;
    m_curAction.m_actorID.Set(action.m_actorID);
    m_curAction.m_acteeID.Set(action.m_acteeID);
    m_curAction.m_acteeID2.Set(action.m_acteeID2);
    m_curAction.m_dest = action.m_dest;
    m_curAction.m_specificID2 = action.m_specificID2;
    m_curAction.m_specificID3 = action.m_specificID3;
    m_curAction.m_string1 = action.m_string1;
    m_curAction.m_string2 = action.m_string2;
    m_curAction.m_internalFlags = action.m_internalFlags;
    if (action.m_actionID != CAIAction::NO_ACTION
        && g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_lNoDecodeList.Find(action.m_actionID) == NULL) {
        m_curAction.Decode(this);
    }
}

// 0x45D280
void CGameAIBase::SetScript(SHORT level, CAIScript* script)
{
    switch (level) {
    case 0:
        if (field_3F6 != NULL) {
            delete field_3F6;
        }
        field_3F6 = script;
        break;
    case 1:
        if (field_3FA != NULL) {
            delete field_3FA;
        }
        field_3FA = script;
        break;
    case 2:
        if (field_3FE != NULL) {
            delete field_3FE;
        }
        field_3FE = script;
        break;
    case 3:
        if (field_402 != NULL) {
            delete field_402;
        }
        field_402 = script;
        break;
    case 4:
        if (field_406 != NULL) {
            delete field_406;
        }
        field_406 = script;
        break;
    case 5:
        if (field_40A != NULL) {
            delete field_40A;
        }
        field_40A = script;
        break;
    case 6:
        if (m_defaultScript != NULL) {
            delete m_defaultScript;
        }
        m_defaultScript = script;
        break;
    }
}

// 0x45D6A0
void CGameAIBase::ApplyTriggers()
{
    // TODO: Incomplete.
}

// 0x45F6D0
SHORT CGameAIBase::MoveCursor(CPoint dest, SHORT speed)
{
    // TODO: Incomplete.

    return ACTION_DONE;
}

// 0x45F900
SHORT CGameAIBase::MoveCursorPoint()
{
    CPoint dest = m_curAction.m_dest;
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    return MoveCursor(dest, speed);
}

// NOTE: Inlined.
SHORT CGameAIBase::ClickLButton(CPoint pt)
{
    g_pBaldurChitin->m_pEngineWorld->OnLButtonDown(pt);
    g_pBaldurChitin->m_pEngineWorld->OnLButtonUp(pt);
    return ACTION_DONE;
}

// 0x45F920
SHORT CGameAIBase::ClickLButtonPoint()
{
    CPoint dest = m_curAction.m_dest;
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return ClickLButton(dest);
}

// 0x45F980
SHORT CGameAIBase::ClickLButtonObject(CGameObject* target)
{
    if (target == NULL) {
        return ACTION_ERROR;
    }

    CPoint dest = target->GetPos();
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return ClickLButton(dest);
}

// NOTE: Inlined.
SHORT CGameAIBase::DoubleClickLButton(CPoint pt)
{
    g_pBaldurChitin->m_pEngineWorld->OnLButtonDown(pt);
    g_pBaldurChitin->m_pEngineWorld->OnLButtonUp(pt);
    g_pBaldurChitin->m_pEngineWorld->OnLButtonDblClk(pt);
    g_pBaldurChitin->m_pEngineWorld->OnLButtonUp(pt);
    return ACTION_DONE;
}

// 0x45F9F0
SHORT CGameAIBase::DoubleClickLButtonPoint()
{
    CPoint dest = m_curAction.m_dest;
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return DoubleClickLButton(dest);
}

// 0x45FA70
SHORT CGameAIBase::DoubleClickLButtonObject(CGameObject* target)
{
    if (target == NULL) {
        return ACTION_ERROR;
    }

    CPoint dest = target->GetPos();
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return DoubleClickLButton(dest);
}

// NOTE: Inlined.
SHORT CGameAIBase::ClickRButton(CPoint pt)
{
    g_pBaldurChitin->m_pEngineWorld->OnRButtonDown(pt);
    g_pBaldurChitin->m_pEngineWorld->OnRButtonUp(pt);
    return ACTION_DONE;
}

// 0x45FB10
SHORT CGameAIBase::ClickRButtonPoint()
{
    CPoint dest = m_curAction.m_dest;
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return ClickRButton(dest);
}

// 0x45FB70
SHORT CGameAIBase::ClickRButtonObject(CGameObject* target)
{
    if (target == NULL) {
        return ACTION_ERROR;
    }

    CPoint dest = target->GetPos();
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return ClickRButton(dest);
}

// NOTE: Inlined.
SHORT CGameAIBase::DoubleClickRButton(CPoint pt)
{
    g_pBaldurChitin->m_pEngineWorld->OnRButtonDown(pt);
    g_pBaldurChitin->m_pEngineWorld->OnRButtonUp(pt);
    g_pBaldurChitin->m_pEngineWorld->OnRButtonDblClk(pt);
    g_pBaldurChitin->m_pEngineWorld->OnRButtonUp(pt);
    return ACTION_DONE;
}

// 0x45FBF0
SHORT CGameAIBase::DoubleClickRButtonPoint()
{
    CPoint dest = m_curAction.m_dest;
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return DoubleClickRButton(dest);
}

// 0x45FC80
SHORT CGameAIBase::DoubleClickRButtonObject(CGameObject* target)
{
    if (target == NULL) {
        return ACTION_ERROR;
    }

    CPoint dest = target->GetPos();
    SHORT speed = static_cast<SHORT>(m_curAction.m_specificID);

    SHORT moveReturn = MoveCursor(dest, speed);
    if (moveReturn != ACTION_DONE) {
        return moveReturn;
    }

    // NOTE: Uninline.
    return DoubleClickLButton(dest);
}

// 0x465110
SHORT CGameAIBase::TakePartyGold()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    DWORD gold = m_curAction.m_specificID;
    if (gold > pGame->m_nPartyGold) {
        gold = pGame->m_nPartyGold;
    }

    if (m_objectType == TYPE_SPRITE) {
        static_cast<CGameSprite*>(this)->GetBaseStats()->m_gold += gold;
        static_cast<CGameSprite*>(this)->GetDerivedStats()->m_nGold += gold;
    }

    CMessagePartyGold* pMessage = new CMessagePartyGold(TRUE,
        TRUE,
        -static_cast<LONG>(gold),
        m_id,
        m_id);

    g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

    return ACTION_DONE;
}

// 0x4651A0
SHORT CGameAIBase::GivePartyGold()
{
    DWORD gold = m_curAction.m_specificID;

    if (m_objectType == TYPE_SPRITE && m_curAction.m_actionID == CAIAction::GIVEPARTYGOLD) {
        if (gold > static_cast<CGameSprite*>(this)->GetDerivedStats()->m_nGold) {
            gold = static_cast<CGameSprite*>(this)->GetDerivedStats()->m_nGold;
        }

        static_cast<CGameSprite*>(this)->GetBaseStats()->m_gold -= gold;
        static_cast<CGameSprite*>(this)->GetDerivedStats()->m_nGold -= gold;
    }

    CMessagePartyGold* pMessage = new CMessagePartyGold(TRUE,
        TRUE,
        gold,
        m_id,
        m_id);

    g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

    return ACTION_DONE;
}

// 0x4668B0
SHORT CGameAIBase::StartMusic()
{
    if (m_pArea == NULL) {
        return ACTION_ERROR;
    }

    // TODO: Check cast.
    m_pArea->PlaySong(static_cast<SHORT>(m_curAction.m_specificID), m_curAction.m_specificID2);

    return ACTION_DONE;
}

// 0x460D60
SCRIPTNAME& CGameAIBase::GetScriptName()
{
    return m_scriptName;
}

// NOTE: Inlined.
void CGameAIBase::SetDefaultScript(CAIScript* script)
{
    if (m_defaultScript != NULL) {
        delete m_defaultScript;
    }

    m_defaultScript = script;
}

// 0x6F2C20
SHORT CGameAIBase::GetVisualRange()
{
    return m_pArea->m_visibility.field_E * 32;
}

// 0x6F2C30
SHORT CGameAIBase::GetHelpRange()
{
    return m_pArea->m_visibility.field_E * 48;
}

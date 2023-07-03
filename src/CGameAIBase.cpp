#include "CGameAIBase.h"

#include "CAIScript.h"
#include "CAITrigger.h"
#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CTimerWorld.h"
#include "CUtil.h"

// 0x44C4B0
CGameAIBase::CGameAIBase()
{
    // TODO: Incomplete.
}

// 0x44D160
CGameAIBase::~CGameAIBase()
{
    // TODO: Incomplete.
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
        if (field_40E != NULL) {
            delete field_40E;
        }
        field_40E = script;
        break;
    }
}

// 0x45D6A0
void CGameAIBase::ApplyTriggers()
{
    // TODO: Incomplete.
}

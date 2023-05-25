#include "CGameAIBase.h"

#include "CAITrigger.h"
#include "CTimerWorld.h"

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

// 0x45D6A0
void CGameAIBase::ApplyTriggers()
{
    // TODO: Incomplete.
}

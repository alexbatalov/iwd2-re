#include "CGameEffectList.h"

#include "CGameEffect.h"
#include "CGameSprite.h"

// NOTE: Inlined.
CGameEffectList::CGameEffectList()
{
    m_posNext = NULL;
    m_posCurrent = NULL;
    m_newEffect = FALSE;
    m_retry = FALSE;
}

// NOTE: Inlined.
CGameEffectList::~CGameEffectList()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pEffect = GetNext(pos);
        delete pEffect;
    }
    RemoveAll();
}

// 0x4C08E0
void CGameEffectList::RemoveAllOfType(CGameSprite* pSprite, WORD effectID, POSITION posLeave, LONG effectAmount)
{
    // TODO: Incomplete.
}

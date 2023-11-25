#include "CGameEffectList.h"

#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CUtil.h"

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

// 0x452F30
POSITION CGameEffectList::GetPosCurrent()
{
    return m_posCurrent;
}

// 0x4C08E0
void CGameEffectList::RemoveAllOfType(CGameSprite* pSprite, WORD effectID, POSITION posLeave, LONG effectAmount)
{
    // TODO: Incomplete.
}

// 0x4C0E00
void CGameEffectList::Unmarshal(BYTE* data, ULONG nSize, CGameSprite* pSprite, BYTE version)
{
    CGameEffect* node;
    LONG numEffects;
    ITEM_EFFECT effect;

    if (version == 0) {
        numEffects = nSize / sizeof(ITEM_EFFECT);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 25475
        UTIL_ASSERT(nSize % sizeof(ITEM_EFFECT) == 0);

        while (numEffects > 0) {
            node = CGameEffect::DecodeEffect(reinterpret_cast<ITEM_EFFECT*>(data),
                CPoint(-1, -1),
                -1,
                CPoint(-1, -1));
            if ((node->m_effectID == CGAMEEFFECT_BASEATTACKBONUS
                    && node->m_targetType == 9)
                || (node->m_effectID == CGAMEEFFECT_RESISTANCETOMAGIC
                    && node->m_targetType == 9)) {
                data += sizeof(ITEM_EFFECT);
                numEffects--;
            } else {
                AddTail(node);
                data += sizeof(ITEM_EFFECT);
                numEffects--;
                node->OnLoad(pSprite);
            }
        }
    } else {
        numEffects = nSize / sizeof(CGameEffectBase);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 25509
        UTIL_ASSERT(nSize % sizeof(CGameEffectBase) == 0);

        while (numEffects > 0) {
            effect.effectID = static_cast<WORD>(reinterpret_cast<CGameEffectBase*>(data)->m_effectID);
            node = CGameEffect::DecodeEffect(&effect,
                CPoint(-1, -1),
                -1,
                CPoint(-1, -1));
            node->CopyFromBase(reinterpret_cast<CGameEffectBase*>(data));
            if ((node->m_effectID == CGAMEEFFECT_BASEATTACKBONUS
                    && (node->m_targetType == 9 || node->m_targetType == 1))
                || (node->m_effectID == CGAMEEFFECT_RESISTANCETOMAGIC
                    && (node->m_targetType == 9 || node->m_targetType == 1))) {
                data += sizeof(CGameEffectBase);
                numEffects--;
            } else {
                AddTail(node);
                data += sizeof(CGameEffectBase);
                numEffects--;
            }
        }
    }
}

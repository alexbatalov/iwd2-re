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

// 0x4C0990
void CGameEffectList::RemoveAllEffectsIgnoreMoreThenPermanent(POSITION posLeave, BOOL checkDispellable, BOOL useLevelDiff, BYTE prob, BYTE dispelLevel)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        POSITION posOld = pos;
        CGameEffect* pEffect = GetNext(pos);
        if (posOld != posLeave
            && (!useLevelDiff || prob > 5 * (pEffect->m_casterLevel - dispelLevel + 10))
            && (!checkDispellable || (pEffect->m_flags & 0x1) != 0)) {
            RemoveAt(posOld);
            delete pEffect;
        }
    }
    m_posNext = NULL;
}

// 0x4C0A30
ULONG CGameEffectList::Marshal(BYTE** ptrPtr, BYTE version, BOOL moreThenPermanentOnly)
{
    POSITION pos;
    CGameEffect* node;
    INT numEffects;
    ULONG size;
    INT index;
    ITEM_EFFECT effect;

    if (version == 0) {
        numEffects = GetCount();
        size = sizeof(ITEM_EFFECT) * numEffects;
        if (moreThenPermanentOnly) {
            numEffects = 0;
            pos = GetHeadPosition();
            while (pos != NULL) {
                node = GetNext(pos);
                if (node->m_durationType == 9) {
                    numEffects++;
                }
            }
            size = sizeof(ITEM_EFFECT) * numEffects;
        }

        if (numEffects > 0) {
            ITEM_EFFECT* effects = new ITEM_EFFECT[numEffects];
            if (effects != NULL) {
                index = 0;
                pos = GetHeadPosition();
                while (pos != NULL) {
                    node = GetNext(pos);
                    if (!moreThenPermanentOnly || node->m_durationType == 9) {
                        effect.effectID = static_cast<WORD>(node->m_effectID);
                        effect.spellLevel = static_cast<BYTE>(node->m_spellLevel);
                        effect.targetType = static_cast<BYTE>(node->m_targetType);
                        effect.dwFlags = node->m_dwFlags;
                        effect.durationType = static_cast<WORD>(node->m_durationType);
                        effect.duration = node->m_duration;
                        effect.probabilityUpper = static_cast<BYTE>(node->m_probabilityUpper);
                        effect.probabilityLower = static_cast<BYTE>(node->m_probabilityLower);
                        node->m_res.GetResRef(effect.res);

                        if (node->UsesDice()) {
                            effect.numDice = node->m_numDice;
                            effect.diceSize = node->m_diceSize;
                        } else {
                            effect.numDice = node->m_maxLevel;
                            effect.diceSize = node->m_diceSize;
                        }

                        effect.savingThrow = node->m_savingThrow;
                        effect.saveMod = node->m_saveMod;
                        effect.special = node->m_special;

                        effects[index] = effect;
                        index++;
                    }
                }
            }
            *ptrPtr = reinterpret_cast<BYTE*>(effects);
        }
    } else {
        numEffects = GetCount();
        size = sizeof(CGameEffectBase) * numEffects;
        if (moreThenPermanentOnly) {
            numEffects = 0;
            pos = GetHeadPosition();
            while (pos != NULL) {
                node = GetNext(pos);
                if (node->m_durationType == 9) {
                    numEffects++;
                }
            }
            size = sizeof(CGameEffectBase) * numEffects;
        }

        if (numEffects > 0) {
            CGameEffectBase* effects = new CGameEffectBase[numEffects];

            // NOTE: Unused.
            CGameEffectBase v1;

            index = 0;
            pos = GetHeadPosition();
            while (pos != NULL) {
                node = GetNext(pos);
                if (!moreThenPermanentOnly || node->m_durationType == 9) {
                    effects[index] = static_cast<CGameEffectBase>(*node);
                    index++;
                }
            }

            *ptrPtr = reinterpret_cast<BYTE*>(effects);
        }
    }

    return size;
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

// 0x4C0FA0
BOOL CGameEffectList::HandleList(CGameSprite* pSprite)
{
    POSITION pos = GetHeadPosition();
    BOOL cont = TRUE;
    BOOL retry = FALSE;

    m_posNext = pos;
    m_posCurrent = pos;

    while (pos != NULL) {
        CGameEffect* pEffect = GetNext(m_posNext);

        if (cont) {
            cont = pEffect->ResolveEffect(pSprite);
        }

        if (pEffect->m_forceRepass) {
            retry = TRUE;
        }

        if (m_posCurrent != NULL && pEffect->m_done) {
            RemoveAt(m_posCurrent);
            delete pEffect;
        }

        pos = m_posNext;
        m_posCurrent = pos;
    }

    m_retry = retry;
    m_posNext = NULL;
    m_posCurrent = NULL;

    return cont;
}

// 0x4C1050
BOOL CGameEffectList::CheckEffects()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pEffect = GetNext(pos);
        if (pEffect->CheckExpiration()) {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x4C0800
BOOL CGameEffectList::IsTypeOnList(WORD effectID)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pEffect = GetNext(pos);
        if (pEffect->m_effectID == effectID) {
            return TRUE;
        }
    }
    return FALSE;
}

#include "CResSpell.h"

#include "CUtil.h"

// 0x4019E0
CResSpell::CResSpell()
{
    m_bParsed = FALSE;
    m_pAbilities = NULL;
    m_pEffects = NULL;
    m_pHeader = NULL;
}

// 0x401A30
void* CResSpell::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        Parse(pData);

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x401A70
SPELL_ABILITY* CResSpell::GetAbility(int nAbility)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            return &(m_pAbilities[nAbility]);
        }
    }

    return NULL;
}

// 0x401AA0
ITEM_EFFECT* CResSpell::GetAbilityEffect(int nAbility, int nEffect, int a4)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            if (nEffect >= 0 && nEffect < m_pAbilities[nAbility].effectCount) {
                ITEM_EFFECT* pEffect = &(m_pEffects[m_pAbilities[nAbility].startingEffect + nEffect]);
                if ((m_pHeader->itemFlags & 0x4000) != 0) {
                    pEffect->duration = 7 * (m_pHeader->field_73 + a4 * m_pHeader->field_72);
                }
                return pEffect;
            }
        }
    }

    return NULL;
}

// 0x401B20
int CResSpell::GetAbilityEffectNo(int nAbility)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            return m_pAbilities[nAbility].effectCount;
        }
    }

    return 0;
}

// 0x401B60
ITEM_EFFECT* CResSpell::GetCastingEffect(int nEffect)
{
    if (m_bParsed) {
        if (nEffect >= 0 && nEffect < m_pHeader->castingEffectCount) {
            return &(m_pEffects[nEffect]);
        }
    }

    return NULL;
}

// 0x4016D0
int CResSpell::GetCastingEffectNo()
{
    if (m_bParsed) {
        return m_pHeader->castingEffectCount;
    }

    return -1;
}

// 0x401BA0
int CResSpell::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pAbilities = NULL;
        m_pEffects = NULL;
        m_pHeader = NULL;
    }
    return rc;
}

// 0x401BD0
BOOL CResSpell::Parse(void* pData)
{
    if (pData == NULL) {
        return m_bParsed;
    }

    m_pHeader = reinterpret_cast<SPELL_HEADER*>(pData);
    if (m_pHeader->nFileType != 'SPL ') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1771
        UTIL_ASSERT_MSG(FALSE, CString("Spell file header type isn't 'SPL '") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".SPL"));
    }

    if (m_pHeader->nFileVersion != 'V2.0') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1784
        UTIL_ASSERT_MSG(FALSE, CString("Spell file version isn't ") + CString("SPL V2.0") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".SPL"));
    }

    m_pEffects = reinterpret_cast<ITEM_EFFECT*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->effectsOffset);
    m_pAbilities = reinterpret_cast<SPELL_ABILITY*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->abilityOffset);

    m_bParsed = TRUE;

    return m_bParsed;
}

#include "CResItem.h"

#include "CUtil.h"

// 0x401560
CResItem::CResItem()
{
    m_bParsed = FALSE;
    m_pAbilities = 0;
    m_pEffects = 0;
    m_pHeader = NULL;
}

// 0x4015A0
CResItem::~CResItem()
{
}

// 0x4015B0
void* CResItem::Demand()
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

// 0x4015F0
ITEM_ABILITY* CResItem::GetAbility(int nAbility)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            return &(m_pAbilities[nAbility]);
        }
    }

    return NULL;
}

// 0x401630
ITEM_EFFECT* CResItem::GetAbilityEffect(int nAbility, int nEffect)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            if (nEffect >= 0 && nEffect <= m_pAbilities[nAbility].effectCount) {
                return &(m_pEffects[m_pAbilities[nAbility].startingEffect + nEffect]);
            }
        }
    }

    return NULL;
}

// 0x401690
int CResItem::GetAbilityEffectNo(int nAbility)
{
    if (m_bParsed) {
        if (nAbility >= 0 && nAbility < m_pHeader->abilityCount) {
            return m_pAbilities[nAbility].effectCount;
        }
    }

    return 0;
}

// 0x4016D0
int CResItem::GetAbilityNo()
{
    if (m_bParsed) {
        return m_pHeader->abilityCount;
    }

    return -1;
}

// 0x4016F0
BOOL CResItem::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    m_pHeader = reinterpret_cast<ITEM_HEADER*>(pData);
    if (m_pHeader->nFileType != 'ITM ') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1356
        UTIL_ASSERT_MSG(FALSE, CString("Item file header type isn't 'ITM '") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".ITM"));
    }

    if (m_pHeader->nFileVersion != 'V2.0') {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\BalDataTypes.cpp
        // __LINE__: 1369
        UTIL_ASSERT_MSG(FALSE, CString("Item file version isn't ") + CString("ITM V2.0") + CString(": ") + CString(reinterpret_cast<const char*>(m_pDimmKeyTableEntry->resRef.GetResRef()), RESREF_SIZE) + CString(".ITM"));
    }

    m_pEffects = reinterpret_cast<ITEM_EFFECT*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->effectsOffset);
    m_pAbilities = reinterpret_cast<ITEM_ABILITY*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->abilityOffset);

    m_bParsed = TRUE;

    return m_bParsed;
}

#include "CImmunities.h"

#include "CGameEffect.h"

// 0x4E6FF0
void CImmunitiesSpellLevel::ClearAll()
{
    for (int index = 0; index < 10; index++) {
        m_levels[index] = FALSE;
    }
}

// 0x4E7030
CImmunitiesSpellLevel& CImmunitiesSpellLevel::operator=(const CImmunitiesSpellLevel& other)
{
    for (int index = 0; index < 10; index++) {
        m_levels[index] = other.m_levels[index];
    }

    return *this;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CSelectiveBonus::CSelectiveBonus()
{
    m_bonus = 0;
}

// NOTE: Inlined.
CSelectiveBonus::CSelectiveBonus(const CSelectiveBonus& other)
{
    m_type.Set(other.m_type);
    m_bonus = other.m_bonus;
}

// -----------------------------------------------------------------------------

// 0x443570
CSelectiveBonusList::~CSelectiveBonusList()
{
    ClearAll();
}

// 0x4E73E0
void CSelectiveBonusList::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CSelectiveBonus* pBonus = GetNext(pos);
        delete pBonus;
    }
    RemoveAll();
}

// 0x4E7420
LONG CSelectiveBonusList::GetBonus(const CAIObjectType& type)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CSelectiveBonus* pBonus = GetNext(pos);
        if (type.OfType(pBonus->m_type, FALSE, FALSE)) {
            return pBonus->m_bonus;
        }
    }
    return 0;
}

// 0x4E7340
CSelectiveBonusList& CSelectiveBonusList::operator=(const CSelectiveBonusList& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CSelectiveBonus* pBonus = other.GetNext(pos);
        AddTail(new CSelectiveBonus(*pBonus));
    }

    return *this;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CImmunitiesItemEquip::CImmunitiesItemEquip()
{
    m_pEffect = NULL;
}

// -----------------------------------------------------------------------------

// 0x4435E0
CImmunitiesItemEquipList::~CImmunitiesItemEquipList()
{
    ClearAll();
}

// 0x4E71B0
void CImmunitiesItemEquipList::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemEquip* pEntry = GetNext(pos);
        delete pEntry;
    }
    RemoveAll();
}

// 0x4E7460
BOOL CImmunitiesItemEquipList::OnList(const CResRef& resRef, STRREF& strError, CGameEffect*& pEffect)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemEquip* pEntry = GetNext(pos);
        if (pEntry->m_res == resRef) {
            strError = pEntry->m_error;

            // FIXME: Looks unsafe - unconditionally attempts to copy effect
            // without checking for null.
            pEffect = pEntry->m_pEffect->Copy();

            return TRUE;
        }
    }

    strError = -1;
    pEffect = NULL;
    return FALSE;
}

// 0x4E74D0
CImmunitiesItemEquipList& CImmunitiesItemEquipList::operator=(const CImmunitiesItemEquipList& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemEquip* pEntry = other.GetNext(pos);
        CImmunitiesItemEquip* pCopy = new CImmunitiesItemEquip;
        pCopy->m_error = pEntry->m_error;

        // FIXME: Looks unsafe - unconditionally attempts to copy effect without
        // checking for null.
        pCopy->m_pEffect = pEntry->m_pEffect->Copy();

        pCopy->m_res = pEntry->m_res;
        AddTail(pCopy);
    }

    return *this;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CImmunitiesItemTypeEquip::CImmunitiesItemTypeEquip()
{
    m_type = 0;
    m_pEffect = NULL;
}

// -----------------------------------------------------------------------------

// 0x443650
CImmunitiesItemTypeEquipList::~CImmunitiesItemTypeEquipList()
{
    ClearAll();
}

// 0x4E71B0
void CImmunitiesItemTypeEquipList::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemTypeEquip* pEntry = GetNext(pos);
        delete pEntry;
    }
    RemoveAll();
}

// 0x4E7590
BOOL CImmunitiesItemTypeEquipList::OnList(DWORD type, STRREF& strError, CGameEffect*& pEffect)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemTypeEquip* pEntry = GetNext(pos);
        if (pEntry->m_type == type) {
            strError = pEntry->m_error;

            // FIXME: Looks unsafe - unconditionally attempts to copy effect
            // without checking for null.
            pEffect = pEntry->m_pEffect->Copy();

            return TRUE;
        }
    }

    strError = -1;
    pEffect = NULL;
    return FALSE;
}

// 0x4E75F0
CImmunitiesItemTypeEquipList& CImmunitiesItemTypeEquipList::operator=(const CImmunitiesItemTypeEquipList& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CImmunitiesItemTypeEquip* pEntry = other.GetNext(pos);
        CImmunitiesItemTypeEquip* pCopy = new CImmunitiesItemTypeEquip;
        pCopy->m_error = pEntry->m_error;

        // FIXME: Looks unsafe - unconditionally attempts to copy effect without
        // checking for null.
        pCopy->m_pEffect = pEntry->m_pEffect->Copy();

        pCopy->m_type = pEntry->m_type;
        AddTail(pCopy);
    }

    return *this;
}

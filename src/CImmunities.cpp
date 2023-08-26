#include "CImmunities.h"

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

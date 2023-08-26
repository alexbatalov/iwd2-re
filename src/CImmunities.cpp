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

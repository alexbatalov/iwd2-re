#include "CGameSpriteSpells.h"

#include "CUtil.h"

// 0x443350
CGameSpriteSpellList::CGameSpriteSpellList()
{
    field_10 = 0;
    field_14 = 0;
    field_18 = 0;
}

// 0x443370
CGameSpriteSpellList::~CGameSpriteSpellList()
{
    if (m_List.size() != 0) {
        field_14 = 0;
        field_18 = 0;
    }
}

// 0x725950
BOOLEAN CGameSpriteSpellList::Add(const UINT& nID, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4)
{
    UINT nIndex = 0;

    // NOTE: Uninline.
    if (Find(nID, nIndex)) {
        unsigned int v1 = m_List[nIndex].field_4 + a2;
        unsigned int v2 = m_List[nIndex].field_8 + a3;

        // NOTE: Unsigned compare.
        if (v1 < v2) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 26483
            UTIL_ASSERT(FALSE);
        }

        m_List[nIndex].field_4 = v1;
        m_List[nIndex].field_8 = v2;
    } else {
        CGameSpriteSpellListEntry entry;
        entry.m_nID = nID;
        entry.field_4 = a2;
        entry.field_8 = a3;
        entry.field_C = a4;
        m_List.push_back(entry);
    }

    if (a3 != 0) {
        field_10 += a3;
    }

    return TRUE;
}

// 0x725B50
BOOLEAN CGameSpriteSpellList::Remove(const UINT& nID, BOOLEAN a2, const unsigned int& a3, const unsigned int& a4)
{
    if (!a2 && a3 == 0 && a4 == 0) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 26518
        UTIL_ASSERT(FALSE);
    }

    unsigned int v1 = a3;
    unsigned int v2 = a4;

    std::vector<CGameSpriteSpellListEntry>::iterator it = m_List.begin();
    while (it != m_List.end()) {
        if (it->m_nID == nID) {
            unsigned int v3 = it->field_4;
            if (v3 < v1) {
                v1 = v3;
            }

            unsigned int v4 = it->field_8;
            if (v4 < v2) {
                v2 = v4;
            }

            if (a2 == TRUE) {
                m_List.erase(it);
            } else {
                it->field_4 = v3 - v1;
                it->field_8 = v4 - v2;

                if (it->field_4 < it->field_8) {
                    v2 += it->field_8 - it->field_4;
                    it->field_8 = it->field_4;
                }
            }

            if (v2 != 0) {
                field_10 -= v2;
            }

            return TRUE;
        }
        it++;
    }

    return FALSE;
}

// 0x725C50
BOOLEAN CGameSpriteSpellList::sub_725C50(const UINT& nID, const unsigned int& a2, const BOOLEAN& a3)
{
    UINT nIndex;

    // NOTE: Uninline.
    if (!Find(nID, nIndex)) {
        return FALSE;
    }

    CGameSpriteSpellListEntry& entry = m_List[nIndex];

    if (entry.field_4 == 0) {
        return FALSE;
    }

    unsigned int v1 = entry.field_8;
    unsigned int v2 = v1 + a2;

    // NOTE: Unsigned compare.
    if (a3 == 1 || v2 > entry.field_4) {
        v2 = entry.field_4;
    }

    field_10 -= v1;
    entry.field_8 = v2;
    field_10 += v2;

    return TRUE;
}

// 0x725CC0
BOOLEAN CGameSpriteSpellList::sub_725CC0(const UINT& nID, const unsigned int& a2, const BOOLEAN& a3)
{
    UINT nIndex;

    // NOTE: Uninline.
    if (!Find(nID, nIndex)) {
        return FALSE;
    }

    CGameSpriteSpellListEntry& entry = m_List[nIndex];

    int v1 = entry.field_8;

    int v2 = v1 - a2;

    // NOTE: Signed compare.
    if (a3 == 1 || v2 < 0) {
        v2 = 0;
    }

    field_10 -= v1;
    entry.field_8 = v2;
    field_10 += v2;

    return TRUE;
}

// 0x725D30
BOOLEAN CGameSpriteSpellList::sub_725D30(const unsigned int& a1, const BOOLEAN& a2)
{
    unsigned int v1 = field_18 + a1;

    // NOTE: Unsigned compare.
    if (a2 == 1 || v1 > field_14) {
        v1 = field_14;
    }

    field_18 = v1;

    for (UINT nIndex = 0; nIndex < m_List.size(); nIndex++) {
        sub_725C50(m_List[nIndex].m_nID, v1 - m_List[nIndex].field_8, FALSE);
    }

    return TRUE;
}

// 0x725DB0
BOOLEAN CGameSpriteSpellList::sub_725DB0(const unsigned int& a1, const BOOLEAN& a2)
{
    int v1 = field_18 - a1;

    // NOTE: Signed compare.
    if (a2 == 1 || v1 < 0) {
        v1 = 0;
    }

    field_18 = v1;

    for (UINT nIndex = 0; nIndex < m_List.size(); nIndex++) {
        // NOTE: Uninline.
        sub_725CC0(m_List[nIndex].m_nID, v1 - m_List[nIndex].field_8, FALSE);
    }

    return TRUE;
}

// 0x725E70
BOOLEAN CGameSpriteSpellList::Find(const UINT& nID, UINT& nIndex)
{
    nIndex = 0;

    std::vector<CGameSpriteSpellListEntry>::iterator it = m_List.begin();
    while (it != m_List.end()) {
        if (it->m_nID == nID) {
            nIndex++;
            return TRUE;
        }
        it++;
    }

    nIndex = 0;
    return FALSE;
}

// NOTE: Inlined.
BOOLEAN CGameSpriteSpellList::CheckF8(UINT nIndex)
{
    // __FILE__: .\Include\FileFormat.h
    // __FILE__: 2428
    UTIL_ASSERT(m_List.size() > 0);

    // __FILE__: .\Include\FileFormat.h
    // __FILE__: 2429
    UTIL_ASSERT(nIndex < m_List.size());

    return m_List[nIndex].field_8 != 0;
}

// NOTE: Inlined.
CGameSpriteSpellListEntry* CGameSpriteSpellList::Get(UINT nIndex)
{
    // __FILE__: .\Include\FileFormat.h
    // __FILE__: 2437
    UTIL_ASSERT(m_List.size() > 0);

    // __FILE__: .\Include\FileFormat.h
    // __FILE__: 2438
    UTIL_ASSERT(nIndex < m_List.size());

    return &(m_List[nIndex]);
}

// NOTE: Convenience.
void CGameSpriteSpellList::Clear()
{
    if (m_List.size() != 0) {
        m_List.clear();
    }
}

// -----------------------------------------------------------------------------

// 0x443320
CGameSpriteGroupedSpellList::CGameSpriteGroupedSpellList()
{
    m_nHighestLevel = 0;
}

// 0x4433F0
CGameSpriteGroupedSpellList::~CGameSpriteGroupedSpellList()
{
}

// 0x58FE80
CGameSpriteSpellList* CGameSpriteGroupedSpellList::GetSpellsAtLevel(const UINT& nLevel)
{
    // __FILE__: .\Include\FileFormat.h
    // __FILE__: 2521
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    return &(m_lists[nLevel]);
}

// 0x725EC0
UINT CGameSpriteGroupedSpellList::GetNumSpells()
{
    UINT nCount = 0;

    for (UINT nIndex = 0; nIndex < m_nHighestLevel; nIndex++) {
        nCount += m_lists[nIndex].m_List.size();
    }

    return nCount;
}

// 0x725F00
UINT CGameSpriteGroupedSpellList::sub_725F00()
{
    UINT nCount = 0;

    for (UINT nIndex = 0; nIndex < m_nHighestLevel; nIndex++) {
        nCount += m_lists[nIndex].field_10;
    }

    return nCount;
}

// 0x725F20
BOOLEAN CGameSpriteGroupedSpellList::Add(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26768
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    BOOLEAN bSuccess = m_lists[nLevel].Add(nID, a3, a4, a5);

    if (bSuccess == TRUE && nLevel + 1 > m_nHighestLevel) {
        m_nHighestLevel = nLevel + 1;
    }

    return bSuccess;
}

// 0x725F90
BOOLEAN CGameSpriteGroupedSpellList::Remove(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26787
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26788
    UTIL_ASSERT(nLevel < m_nHighestLevel);

    BOOLEAN bSuccess = m_lists[nLevel].Remove(nID, a3, a4, a5);

    if (bSuccess) {
        UINT nNewHighestLevel = nLevel + 1;
        if (nNewHighestLevel >= m_nHighestLevel) {
            while (nNewHighestLevel > 0 && m_lists[nNewHighestLevel - 1].m_List.size() == 0) {
                nNewHighestLevel--;
            }
            m_nHighestLevel = nNewHighestLevel;
        }
    }

    return bSuccess;
}

// 0x726060
BOOLEAN CGameSpriteGroupedSpellList::sub_726060(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26822
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    return m_lists[nLevel].sub_725C50(nID, a3, a4);
}

// 0x7260B0
BOOLEAN CGameSpriteGroupedSpellList::sub_7260B0(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26832
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    // NOTE: Uninline.
    return m_lists[nLevel].sub_725CC0(nID, a3, a4);
}

// 0x726150
BOOLEAN CGameSpriteGroupedSpellList::sub_726150(const UINT& nLevel, const unsigned int& a2, const BOOLEAN& a3)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26842
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    m_lists[nLevel].sub_725D30(a2, a3);

    return TRUE;
}

// 0x7261A0
BOOLEAN CGameSpriteGroupedSpellList::sub_7261A0(const UINT& nLevel, const unsigned int& a2, const BOOLEAN& a3)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26852
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    m_lists[nLevel].sub_725DB0(a2, a3);

    return TRUE;
}

// 0x7261F0
BOOLEAN CGameSpriteGroupedSpellList::Find(const UINT& nID, const UINT& nLevel, UINT& nIndex)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
    // __LINE__: 26863
    UTIL_ASSERT(nLevel < CSPELLLIST_MAX_LEVELS);

    nIndex = 0;

    // NOTE: Uninline.
    return m_lists[nLevel].Find(nID, nIndex);
}

// NOTE: Convenience.
void CGameSpriteGroupedSpellList::Clear()
{
    UINT nLevel;

    for (nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
        m_lists[nLevel].Clear();
    }

    m_nHighestLevel = 0;
}

// -----------------------------------------------------------------------------

// 0x5946E0
CGameSpriteGroupedSpellList* CGameSpriteSpells::Get(const UINT& nClassIndex)
{
    // __FILE__: .\Include\FileFormat.h
    // __LINE__: 2572
    UTIL_ASSERT(nClassIndex < CSPELLLIST_NUM_CLASSES);

    return &(m_spellsByClass[nClassIndex]);
}

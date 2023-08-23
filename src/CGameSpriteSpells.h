#ifndef CGAMESPRITESPELLS_H_
#define CGAMESPRITESPELLS_H_

#include <vector>

#include "FileFormat.h"

// NOTE: For unknown reason almost all function params are references instead of
// plain values. I've added `const` qualifier to make their use a little bit
// easier and to identify which references are actually out params. That in
// turn resulted in pretty ugly interface.
//
// Also since many fields remains unclear, there is mess with signness.

class CGameSpriteSpellListEntry {
public:
    /* 0000 */ UINT m_nID;
    /* 0004 */ unsigned int field_4;
    /* 0008 */ unsigned int field_8;
    /* 000C */ unsigned int field_C;
};

class CGameSpriteSpellList {
public:
    CGameSpriteSpellList();
    ~CGameSpriteSpellList();
    BOOLEAN Add(const UINT& nID, const unsigned int& a2, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN Remove(const UINT& nID, BOOLEAN a2, const unsigned& a3, const unsigned& a4);
    BOOLEAN sub_725C50(const UINT& nID, const unsigned int& a2, const BOOLEAN& a3);
    BOOLEAN sub_725CC0(const UINT& nID, const unsigned int& a2, const BOOLEAN& a3);
    BOOLEAN sub_725D30(const unsigned int& a1, const BOOLEAN& a2);
    BOOLEAN sub_725DB0(const unsigned int& a1, const BOOLEAN& a2);
    BOOLEAN Find(const UINT& nID, UINT& nIndex);

    BOOLEAN CheckF8(UINT nIndex);
    CGameSpriteSpellListEntry* Get(UINT nIndex);

    void Clear();

    /* 0000 */ std::vector<CGameSpriteSpellListEntry> m_List;
    /* 0010 */ unsigned int field_10;
    /* 0014 */ unsigned int field_14;
    /* 0018 */ unsigned int field_18;
};

class CGameSpriteGroupedSpellList {
public:
    CGameSpriteGroupedSpellList();
    ~CGameSpriteGroupedSpellList();
    CGameSpriteSpellList* GetSpellsAtLevel(const UINT& nLevel);
    UINT GetNumSpells();
    UINT sub_725F00();
    BOOLEAN Add(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN Remove(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4, const unsigned int& a5);
    BOOLEAN sub_726060(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN sub_7260B0(const UINT& nID, const UINT& nLevel, const unsigned int& a3, const unsigned int& a4);
    BOOLEAN sub_726150(const UINT& nLevel, const unsigned int& a2, const BOOLEAN& a3);
    BOOLEAN sub_7261A0(const UINT& nLevel, const unsigned int& a2, const BOOLEAN& a3);
    BOOLEAN Find(const UINT& nID, const UINT& nLevel, UINT& nIndex);

    void Clear();

    /* 0000 */ CGameSpriteSpellList m_lists[CSPELLLIST_MAX_LEVELS];
    /* 0048 */ UINT m_nHighestLevel;
};

class CGameSpriteSpells {
public:
    CGameSpriteGroupedSpellList* Get(const UINT& nClassIndex);

    /* 0000 */ CGameSpriteGroupedSpellList m_spellsByClass[CSPELLLIST_NUM_CLASSES];
};

#endif /* CGAMESPRITESPELLS_H_ */

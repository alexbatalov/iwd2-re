#ifndef CIMMUNITIES_H_
#define CIMMUNITIES_H_

#include "mfc.h"

class CImmunitiesSpellLevel {
public:
    void ClearAll();
    CImmunitiesSpellLevel& operator=(const CImmunitiesSpellLevel& other);

    /* 0000 */ BOOL m_levels[10];
};

class CWeaponIdentification {
public:
    WORD m_itemType;
    DWORD m_itemFlags;
    DWORD m_itemFlagMask;
    DWORD m_attributes;
};

#endif /* CIMMUNITIES_H_ */

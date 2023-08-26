#ifndef CIMMUNITIES_H_
#define CIMMUNITIES_H_

#include "mfc.h"

#include "CAIObjectType.h"

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

class CSelectiveBonus {
public:
    CSelectiveBonus();
    CSelectiveBonus(const CSelectiveBonus& other);

    CAIObjectType m_type;
    LONG m_bonus;
};

class CSelectiveBonusList : public CTypedPtrList<CPtrList, CSelectiveBonus*> {
public:
    ~CSelectiveBonusList() override;
    void ClearAll();
    LONG GetBonus(const CAIObjectType& type);
    CSelectiveBonusList& operator=(const CSelectiveBonusList& other);
};

#endif /* CIMMUNITIES_H_ */

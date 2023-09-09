#ifndef CIMMUNITIES_H_
#define CIMMUNITIES_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "CAIObjectType.h"
#include "CResRef.h"

class CGameEffect;

class CImmunitiesEffect : public CTypedPtrList<CPtrList, CGameEffect*> {
public:
    ~CImmunitiesEffect() override;
    void ClearAll();
    BOOL OnList(CGameEffect* pEffect);
    CImmunitiesEffect& operator=(const CImmunitiesEffect& other);
};

class CImmunitiesSpellLevel {
public:
    void ClearAll();
    CImmunitiesSpellLevel& operator=(const CImmunitiesSpellLevel& other);

    /* 0000 */ BOOL m_levels[10];
};

class CWeaponIdentification {
public:
    CWeaponIdentification();
    CWeaponIdentification(const CWeaponIdentification& other);
    BOOL OfType(const CWeaponIdentification& other) const;

    /* 0000 */ WORD m_itemType;
    /* 0002 */ DWORD m_itemFlags;
    /* 0006 */ DWORD m_itemFlagMask;
    /* 000A */ DWORD m_attributes;
};

class CImmunitiesWeapon : public CTypedPtrList<CPtrList, CWeaponIdentification*> {
public:
    ~CImmunitiesWeapon() override;
    void ClearAll();
    BOOL OnList(const CWeaponIdentification& other);
    CImmunitiesWeapon& operator=(const CImmunitiesWeapon& other);
    ULONG Marshal(BYTE** ptrPtr);
    void Unmarshal(BYTE* data, ULONG nSize);
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

class CImmunitiesItemEquip {
public:
    CImmunitiesItemEquip();

    /* 0000 */ CResRef m_res;
    /* 0008 */ STRREF m_error;
    /* 000C */ CGameEffect* m_pEffect;
};

class CImmunitiesItemEquipList : public CTypedPtrList<CPtrList, CImmunitiesItemEquip*> {
public:
    ~CImmunitiesItemEquipList() override;
    void ClearAll();
    BOOL OnList(const CResRef& resRef, STRREF& strError, CGameEffect*& pEffect);
    CImmunitiesItemEquipList& operator=(const CImmunitiesItemEquipList& other);
};

class CImmunitiesItemTypeEquip {
public:
    CImmunitiesItemTypeEquip();

    /* 0000 */ DWORD m_type;
    /* 0004 */ STRREF m_error;
    /* 0008 */ CGameEffect* m_pEffect;
};

class CImmunitiesItemTypeEquipList : public CTypedPtrList<CPtrList, CImmunitiesItemTypeEquip*> {
public:
    ~CImmunitiesItemTypeEquipList() override;
    void ClearAll();
    BOOL OnList(DWORD type, STRREF& strError, CGameEffect*& pEffect);
    CImmunitiesItemTypeEquipList& operator=(const CImmunitiesItemTypeEquipList& other);
};

#endif /* CIMMUNITIES_H_ */

#ifndef CITEM_H_
#define CITEM_H_

#include "CResItem.h"
#include "CSound.h"
#include "FileFormat.h"

class CWeaponIdentification;

class CItem : public CResHelper<CResItem, 1005> {
public:
    static const CString VALUE;

    CItem();
    ~CItem();

    CCreatureFileItem GetItemFile();
    BOOL Demand();
    BOOL Release();
    BOOL ReleaseAll();
    void SetResRef(const CResRef& cNewResRef, BOOL bSetAutoRequest);
    INT GetAbilityCount();
    WORD GetUsageCount(INT nAbility);
    WORD GetMaxUsageCount(INT nAbility);
    void SetUsageCount(INT nAbility, WORD nUseCount);
    WORD GetAnimationType();
    ITEM_ABILITY* GetAbility(INT nAbility);
    WORD GetItemType();
    DWORD GetCriticalHitMultiplier();
    DWORD GetWeight();
    CResRef GetUsedUpItemId();
    STRREF GetGenericName();
    STRREF GetIdentifiedName();
    DWORD GetFlagsFile();
    DWORD GetNotUsableBy();
    DWORD GetNotUsableBy2();
    CResRef GetGroundIcon();
    CResRef GetItemIcon();
    WORD GetMaxStackable();
    DWORD GetBaseValue();
    WORD GetLoreValue();
    STRREF GetDescription();
    CResRef GetDescriptionPicture();
    void LoadWeaponIdentification(CWeaponIdentification& weaponId);
    BYTE GetMinLevelRequired();
    BYTE GetMinSTRRequired();
    BYTE GetMinINTRequired();
    BYTE GetMinDEXRequired();
    BYTE GetMinWISRequired();
    BYTE GetMinCONRequired();
    BYTE GetMinCHRRequired();

    /* 0014 */ INT m_nAbilities;
    /* 0018 */ WORD m_useCount1;
    /* 001A */ WORD m_useCount2;
    /* 001C */ WORD m_useCount3;
    /* 001E */ WORD m_wear;
    /* 0020 */ DWORD m_flags;
    /* 0024 */ CSound m_useSound[2];
    /* 00EC */ SHORT m_numSounds;
};

#endif /* CITEM_H_ */
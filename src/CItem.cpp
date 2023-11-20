#include "CItem.h"

#include "CGameSprite.h"
#include "CImmunities.h"
#include "CUtil.h"

// 0x8D828C
const CString CItem::VALUE("VALUE");

// 0x4E7840
CItem::CItem()
{
    m_flags = 0;
    m_nAbilities = 0;
    m_numSounds = 0;
    m_wear = 0;
    m_useCount1 = 0;
    m_useCount2 = 0;
    m_useCount3 = 0;
}

// 0x4E7900
CItem::CItem(const CItem& item)
{
    // TODO: Incomplete.
}

// 0x4E7B60
CItem::CItem(const CCreatureFileItem& item)
{
    // TODO: Incomplete.
}

// FIXME: `id` should be reference.
//
// 0x4E7E90
CItem::CItem(CResRef id, WORD useCount1, WORD useCount2, WORD useCount3, int wear, DWORD flags)
{
    CString sResRef;
    id.CopyToString(sResRef);
    sResRef.MakeUpper();

    m_useCount1 = useCount1;
    m_useCount2 = useCount2;
    m_useCount3 = useCount3;

    // TODO: Incomplete.

    // NOTE: Uninline.
    if (GetMaxStackable() > 1) {
        m_useCount1 = max(m_useCount1, 1);
        m_useCount2 = max(m_useCount2, 1);
        m_useCount3 = max(m_useCount3, 1);
    }

    m_flags = flags;
    m_wear = wear;

    // NOTE: Uninline.
    GetAbilityCount();

    // NOTE: Uninline.
    if (GetLoreValue() == 0) {
        m_flags |= 0x1;
    }

    if ((m_flags & 0x1) == 0) {
        m_flags |= 0x8;
    }
}

// 0x4E8180
CItem::~CItem()
{
    // TODO: Incomplete.
}

// 0x4E8240
CCreatureFileItem CItem::GetItemFile()
{
    CCreatureFileItem temp;

    cResRef.GetResRef(temp.m_itemId);
    temp.m_dynamicFlags = m_flags;
    temp.m_usageCount[0] = m_useCount1;
    temp.m_usageCount[1] = m_useCount2;
    temp.m_usageCount[2] = m_useCount3;
    temp.m_wear = m_wear;

    return temp;
}

// 0x4E82B0
BOOL CItem::Demand()
{
    if (cResRef == "") {
        return FALSE;
    }

    if (pRes == NULL) {
        return FALSE;
    }

    pRes->Demand();

    return pRes != NULL;
}

// 0x4E82F0
BOOL CItem::Release()
{
    if (pRes == NULL) {
        return FALSE;
    }

    pRes->Release();

    return TRUE;
}

// 0x4E8310
BOOL CItem::ReleaseAll()
{
    if (pRes == NULL) {
        return FALSE;
    }

    while (pRes->GetDemands() > 0) {
        pRes->Release();
    }

    return TRUE;
}

// 0x4E8350
void CItem::SetResRef(const CResRef& cNewResRef, BOOL bSetAutoRequest)
{
    CResHelper<CResItem, 1005>::SetResRef(cNewResRef, bSetAutoRequest, TRUE);
}

// 0x4E8440
INT CItem::GetAbilityCount()
{
    if (cResRef == "") {
        m_nAbilities = 0;
    } else {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 810
            UTIL_ASSERT(pRes->Demand());

            m_nAbilities = pRes->m_pHeader->abilityCount;
            pRes->Release();
        }
    }

    return m_nAbilities;
}

// 0x4E85F0
WORD CItem::GetMaxUsageCount(INT nAbility)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 904
    UTIL_ASSERT(pRes->Demand());

    // NOTE: Uninline.
    GetAbilityCount();

    WORD nMaxUsageCount = 0;
    if (nAbility >= 0 && nAbility < m_nAbilities) {
        // NOTE: Uninline.
        if (GetMaxStackable() <= 1) {
            // NOTE: Uninline.
            ITEM_ABILITY* ability = GetAbility(nAbility);
            if (ability != NULL) {
                nMaxUsageCount = ability->maxUsageCount;
            }
        }
    }

    pRes->Release();
    return nMaxUsageCount;
}

// 0x4E84B0
WORD CItem::GetUsageCount(INT nAbility)
{
    // NOTE: Uninline.
    GetAbilityCount();

    if (nAbility < 0) {
        return 0;
    }

    if (nAbility < m_nAbilities) {
        // NOTE: Uninline.
        // NOTE: Not used.
        GetMaxStackable();

        switch (nAbility) {
        case 1:
            return m_useCount2;
        case 2:
            return m_useCount3;
        default:
            return m_useCount1;
        }
    }

    if (nAbility == 0) {
        // NOTE: Uninline.
        if (GetMaxStackable() > 1) {
            return m_useCount1;
        }
    }

    return 0;
}

// 0x4E8760
void CItem::SetUsageCount(INT nAbility, WORD nUseCount)
{
    // NOTE: Uninline.
    GetAbilityCount();

    if (nAbility < 0) {
        return;
    }

    if (nAbility < m_nAbilities) {
        switch (nAbility) {
        case 1:
            m_useCount2 = nUseCount;
            return;
        case 2:
            m_useCount3 = nUseCount;
            return;
        default:
            m_useCount1 = nUseCount;
            return;
        }
    }

    if (nAbility == 0) {
        // NOTE: Uninline.
        if (GetMaxStackable() > 1) {
            m_useCount1 = nUseCount;
        }
    }
}

// 0x4E8860
void CItem::Equip(CGameSprite* pSprite, LONG slotNum, BOOL animationOnly)
{
    // TODO: Incomplete.
}

// 0x4E8DF0
void CItem::Unequip(CGameSprite* pSprite, LONG slotNum, BOOL recalculateEffects, BOOL animationOnly)
{
    // TODO: Incomplete.
}

// 0x4E91F0
WORD CItem::GetAnimationType()
{
    if (cResRef == "") {
        return NULL;
    }

    if (pRes == NULL) {
        return NULL;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1268
    UTIL_ASSERT(pRes->Demand());

    WORD animationType = pRes->m_pHeader->animationType[1] | (pRes->m_pHeader->animationType[0] << 8);
    pRes->Release();

    return animationType;
}

// 0x4E9610
ITEM_ABILITY* CItem::GetAbility(INT nAbility)
{
    if (cResRef == "") {
        return NULL;
    }

    if (pRes == NULL) {
        return NULL;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1478
    UTIL_ASSERT(pRes->Demand());

    ITEM_ABILITY* ability = pRes->GetAbility(nAbility);
    if (ability == NULL) {
        return NULL;
    }

    if (ability->type == 0) {
        return NULL;
    }

    return ability;
}

// 0x4E97E0
WORD CItem::GetItemType()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1595
    UTIL_ASSERT(pRes->Demand());

    WORD nType = pRes->m_pHeader->itemType;
    pRes->Release();

    return nType;
}

// 0x4E9910
DWORD CItem::GetCriticalHitMultiplier()
{
    // NOTE: Uninline.
    WORD nType = GetItemType();
    switch (nType) {
    case 5:
    case 15:
    case 21:
    case 25:
    case 29:
    case 30:
        return 3;
    default:
        return 2;
    }
}

// 0x4E99B0
DWORD CItem::GetWeight()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1688
    UTIL_ASSERT(pRes->Demand());

    DWORD nWeight = pRes->m_pHeader->baseWeight;
    pRes->Release();

    // NOTE: Uninline.
    if (GetMaxStackable() > 1) {
        nWeight *= max(m_useCount1, 1);
    }

    return nWeight;
}

// 0x4E9A80
CResRef CItem::GetUsedUpItemId()
{
    CResRef usedResRef("");

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 1732
            UTIL_ASSERT(pRes->Demand());

            usedResRef = pRes->m_pHeader->usedUpItemID;
            pRes->Release();
        }
    }

    return usedResRef;
}

// 0x4E9B10
STRREF CItem::GetGenericName()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1799
    UTIL_ASSERT(pRes->Demand());

    STRREF strName;
    if ((m_flags & 0x1) != 0) {
        strName = pRes->m_pHeader->identifiedName;
    } else {
        strName = pRes->m_pHeader->genericName;
    }

    pRes->Release();

    return strName;
}

// 0x4E9B80
STRREF CItem::GetIdentifiedName()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1799
    UTIL_ASSERT(pRes->Demand());

    STRREF strName = pRes->m_pHeader->identifiedName;
    pRes->Release();

    return strName;
}

// 0x4E9BE0
DWORD CItem::GetFlagsFile()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1840
    UTIL_ASSERT(pRes->Demand());

    DWORD dwFlags = pRes->m_pHeader->itemFlags;
    pRes->Release();

    return dwFlags;
}

// 0x4E9C40
DWORD CItem::GetNotUsableBy()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1879
    UTIL_ASSERT(pRes->Demand());

    DWORD dwNotUsableBy = pRes->m_pHeader->notUsableBy;
    pRes->Release();

    return dwNotUsableBy;
}

// 0x4E9CA0
DWORD CItem::GetNotUsableBy2()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 1920
    UTIL_ASSERT(pRes->Demand());

    BYTE bNotUsableBy2a = pRes->m_pHeader->notUsableBy2a;
    BYTE bNotUsableBy2b = pRes->m_pHeader->notUsableBy2b;
    BYTE bNotUsableBy2c = pRes->m_pHeader->notUsableBy2c;
    BYTE bNotUsableBy2d = pRes->m_pHeader->notUsableBy2d;
    pRes->Release();

    return bNotUsableBy2d | (bNotUsableBy2c << 8) | (bNotUsableBy2b << 16) | (bNotUsableBy2a << 24);
}

// 0x4E9D40
CResRef CItem::GetGroundIcon()
{
    CResRef iconResRef("");

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 1973
            UTIL_ASSERT(pRes->Demand());

            iconResRef = pRes->m_pHeader->groundIcon;
            pRes->Release();
        }
    }

    if (iconResRef == "") {
        iconResRef = "gsack01";
    }

    return iconResRef;
}

// 0x4E9DF0
CResRef CItem::GetItemIcon()
{
    CResRef iconResRef("");

    if (cResRef != "") {
        if (IsBadReadPtr(pRes, 0x60)) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2019
            UTIL_ASSERT_MSG(FALSE, "Bad item!");
        }

        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2023
            UTIL_ASSERT(pRes->Demand());

            iconResRef = pRes->m_pHeader->itemIcon;
            pRes->Release();
        }
    }

    return iconResRef;
}
// 0x4E9EB0
WORD CItem::GetMaxStackable()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 2061
    UTIL_ASSERT(pRes->Demand());

    WORD nMaxStack = pRes->m_pHeader->maxStackable;
    pRes->Release();

    return nMaxStack;
}

// 0x4E9F10
DWORD CItem::GetBaseValue()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 2099
    UTIL_ASSERT(pRes->Demand());

    DWORD nBaseValue = pRes->m_pHeader->baseValue;
    pRes->Release();

    return nBaseValue;
}

// 0x4E9F70
WORD CItem::GetLoreValue()
{
    if (cResRef == "") {
        return 0;
    }

    if (pRes == NULL) {
        return 0;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 2140
    UTIL_ASSERT(pRes->Demand());

    WORD nLoreValue = pRes->m_pHeader->loreValue;
    pRes->Release();

    return nLoreValue;
}

// 0x4E9FD0
STRREF CItem::GetDescription()
{
    if (cResRef == "") {
        return -1;
    }

    if (pRes == NULL) {
        return -1;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 2176
    UTIL_ASSERT(pRes->Demand());

    STRREF strDescription;
    if ((m_flags & 0x1) != 0 && pRes->m_pHeader->identifiedDescription != -1) {
        strDescription = pRes->m_pHeader->identifiedDescription;
    } else {
        strDescription = pRes->m_pHeader->genericDescription;
    }

    pRes->Release();
    return strDescription;
}

// 0x4EA050
CResRef CItem::GetDescriptionPicture()
{
    CResRef iconResRef("");

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2218
            UTIL_ASSERT(pRes->Demand());

            iconResRef = pRes->m_pHeader->descriptionPicture;
            pRes->Release();
        }
    }

    return iconResRef;
}

// 0x4EA0E0
void CItem::LoadWeaponIdentification(CWeaponIdentification& weaponId)
{
    if (pRes == NULL) {
        return;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
    // __LINE__: 2425
    UTIL_ASSERT(pRes->Demand());

    weaponId.m_itemType = pRes->m_pHeader->itemType;
    weaponId.m_itemFlags = pRes->m_pHeader->itemFlags;
    weaponId.m_itemFlagMask = 0;
    weaponId.m_attributes = pRes->m_pHeader->attributes;

    pRes->Release();
}

// 0x4EA150
BYTE CItem::GetMinLevelRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2464
            UTIL_ASSERT(pRes->Demand());

            nValue = static_cast<BYTE>(pRes->m_pHeader->minLevelRequired);
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA1B0
BYTE CItem::GetMinSTRRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2483
            UTIL_ASSERT(pRes->Demand());

            nValue = static_cast<BYTE>(pRes->m_pHeader->minSTRRequired);
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA210
BYTE CItem::GetMinINTRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2521
            UTIL_ASSERT(pRes->Demand());

            nValue = pRes->m_pHeader->minINTRequired;
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA270
BYTE CItem::GetMinDEXRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2540
            UTIL_ASSERT(pRes->Demand());

            nValue = pRes->m_pHeader->minDEXRequired;
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA2D0
BYTE CItem::GetMinWISRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2559
            UTIL_ASSERT(pRes->Demand());

            nValue = pRes->m_pHeader->minWISRequired;
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA330
BYTE CItem::GetMinCONRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2578
            UTIL_ASSERT(pRes->Demand());

            nValue = pRes->m_pHeader->minCONRequired;
            pRes->Release();
        }
    }

    return nValue;
}

// 0x4EA390
BYTE CItem::GetMinCHRRequired()
{
    BYTE nValue = 0;

    if (cResRef != "") {
        if (pRes != NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CItem.cpp
            // __LINE__: 2597
            UTIL_ASSERT(pRes->Demand());

            nValue = static_cast<BYTE>(pRes->m_pHeader->minCHRRequired);
            pRes->Release();
        }
    }

    return nValue;
}

// 0x675320
bool CItem::operator==(const CItem& other)
{
    return m_useCount1 == other.m_useCount1
        && m_useCount2 == other.m_useCount2
        && m_useCount3 == other.m_useCount3
        && m_wear == other.m_wear
        && m_flags == other.m_flags
        && cResRef == other.cResRef;
}

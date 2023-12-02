#include "CImmunities.h"

#include "CGameEffect.h"
#include "CUtil.h"

// 0x443420
CImmunitiesEffect::~CImmunitiesEffect()
{
    ClearAll();
}

// 0x4E6E50
CImmunitiesEffect& CImmunitiesEffect::operator=(const CImmunitiesEffect& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pEffect = other.GetNext(pos);
        AddTail(pEffect->Copy());
    }

    return *this;
}

// 0x4E6E80
void CImmunitiesEffect::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pEffect = GetNext(pos);
        delete pEffect;
    }
    RemoveAll();
}

// 0x4E6EB0
BOOL CImmunitiesEffect::OnList(CGameEffect* pEffect)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CGameEffect* pCurrEffect = GetNext(pos);
        if (pCurrEffect->Compare(*pEffect)
            || (pCurrEffect->m_compareIdOnly
                && pCurrEffect->m_effectID == pEffect->m_effectID)
            || (pCurrEffect->m_compareIdAndFlagsOnly
                && pCurrEffect->m_effectID == pEffect->m_effectID
                && pCurrEffect->m_dwFlags == pEffect->m_dwFlags)) {
            return TRUE;
        }
    }

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x443490
CImmunitiesAIType::~CImmunitiesAIType()
{
    ClearAll();
}

// 0x4E73E0
void CImmunitiesAIType::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CAIObjectType* type = GetNext(pos);
        delete type;
    }
    RemoveAll();
}

// 0x4E6F20
CImmunitiesAIType& CImmunitiesAIType::operator=(const CImmunitiesAIType& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CAIObjectType* type = other.GetNext(pos);
        AddTail(new CAIObjectType(*type));
    }

    return *this;
}

// 0x4E6FB0
BOOL CImmunitiesAIType::OnList(const CAIObjectType& other)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CAIObjectType* type = GetNext(pos);
        if (other.OfType(*type, FALSE, FALSE)) {
            return TRUE;
        }
    }
    return FALSE;
}

// -----------------------------------------------------------------------------

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
CWeaponIdentification::CWeaponIdentification()
{
    m_itemType = 0;
    m_itemFlags = 0;
    m_itemFlagMask = 0;
    m_attributes = 0;
}

// NOTE: Inlined.
CWeaponIdentification::CWeaponIdentification(const CWeaponIdentification& other)
{
    m_itemType = other.m_itemType;
    m_itemFlags = other.m_itemFlags;
    m_itemFlagMask = other.m_itemFlagMask;
    m_attributes = other.m_attributes;
}

// 0x4E70A0
BOOL CWeaponIdentification::OfType(const CWeaponIdentification& other) const
{
    return (other.m_itemType == m_itemType || other.m_itemType == 0)
        && (((other.m_itemFlags ^ m_itemFlags) & 0x2) != 0 || (other.m_itemFlagMask & 0x2) == 0)
        && (((other.m_itemFlags ^ m_itemFlags) & 0x10) != 0 || (other.m_itemFlagMask & 0x10) == 0)
        && (((other.m_itemFlags ^ m_itemFlags) & 0x40) != 0 || (other.m_itemFlagMask & 0x40) == 0)
        && (((other.m_itemFlags ^ m_itemFlags) & 0x100) != 0 || (other.m_itemFlagMask & 0x100) == 0)
        && (((other.m_itemFlags ^ m_itemFlags) & 0x200) != 0 || (other.m_itemFlagMask & 0x200) == 0)
        && (other.m_attributes >= m_attributes);
}

// -----------------------------------------------------------------------------

// 0x443500
CImmunitiesWeapon::~CImmunitiesWeapon()
{
    ClearAll();
}

// 0x4E7150
CImmunitiesWeapon& CImmunitiesWeapon::operator=(const CImmunitiesWeapon& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        CWeaponIdentification* pBonus = other.GetNext(pos);
        AddTail(new CWeaponIdentification(*pBonus));
    }

    return *this;
}

// 0x4E71B0
void CImmunitiesWeapon::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CWeaponIdentification* pWeaponIdentification = GetNext(pos);
        delete pWeaponIdentification;
    }
    RemoveAll();
}

// 0x4E71E0
BOOL CImmunitiesWeapon::OnList(const CWeaponIdentification& other)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CWeaponIdentification* pBonus = GetNext(pos);
        if (other.OfType(*pBonus)) {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x4E7220
ULONG CImmunitiesWeapon::Marshal(BYTE** ptrPtr)
{
    *ptrPtr = NULL;

    LONG length = sizeof(CWeaponIdentification) * GetCount();
    if (length > 0) {
        // NOTE: Original code is slightly different.
        BYTE* ptr = new BYTE[length];
        int offset = 0;

        POSITION pos = GetHeadPosition();
        while (pos != NULL) {
            CWeaponIdentification* pWeaponIdentification = GetNext(pos);

            *reinterpret_cast<WORD*>(ptr + offset) = pWeaponIdentification->m_itemType;
            offset += sizeof(WORD);

            *reinterpret_cast<DWORD*>(ptr + offset) = pWeaponIdentification->m_itemFlags;
            offset += sizeof(DWORD);

            *reinterpret_cast<DWORD*>(ptr + offset) = pWeaponIdentification->m_itemFlagMask;
            offset += sizeof(DWORD);

            *reinterpret_cast<DWORD*>(ptr + offset) = pWeaponIdentification->m_attributes;
            offset += sizeof(DWORD);
        }

        *ptrPtr = ptr;
    }

    return length;
}

// 0x4E7290
void CImmunitiesWeapon::Unmarshal(BYTE* data, ULONG nSize)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CImmunities.cpp
    // __LINE__: 746
    UTIL_ASSERT(nSize % sizeof(CWeaponIdentification) == 0);

    int count = nSize / sizeof(CWeaponIdentification);
    int offset = 0;

    for (int index = 0; index < count; index++) {
        CWeaponIdentification* pWeaponIdentification = new CWeaponIdentification;

        pWeaponIdentification->m_itemType = *reinterpret_cast<WORD*>(data + offset);
        offset += sizeof(WORD);

        pWeaponIdentification->m_itemFlags = *reinterpret_cast<DWORD*>(data + offset);
        offset += sizeof(DWORD);

        pWeaponIdentification->m_itemFlagMask = *reinterpret_cast<DWORD*>(data + offset);
        offset += sizeof(DWORD);

        pWeaponIdentification->m_attributes = *reinterpret_cast<DWORD*>(data + offset);
        offset += sizeof(DWORD);

        AddTail(pWeaponIdentification);
    }
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

// -----------------------------------------------------------------------------

// NOTE: Inlined.
BOOL CImmunitiesProjectile::OnList(DWORD projectileType)
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        DWORD node = reinterpret_cast<DWORD>(GetNext(pos));
        if (node == projectileType) {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x4E7650
CImmunitiesProjectile& CImmunitiesProjectile::operator=(const CImmunitiesProjectile& other)
{
    // FIXME: Missing `ClearAll`.

    POSITION pos = other.GetHeadPosition();
    while (pos != NULL) {
        DWORD projectileType = reinterpret_cast<DWORD>(other.GetNext(pos));
        AddTail(reinterpret_cast<DWORD*>(projectileType));
    }

    return *this;
}

// 0x4E6DA0
ULONG CImmunitiesProjectile::Marshal(BYTE** ptrPtr)
{
    *ptrPtr = NULL;

    LONG length = sizeof(DWORD) * GetCount();
    if (length > 0) {
        // NOTE: Original code is slightly different.
        BYTE* ptr = new BYTE[length];
        int offset = 0;

        POSITION pos = GetHeadPosition();
        while (pos != NULL) {
            DWORD* pId = GetNext(pos);

            *reinterpret_cast<DWORD*>(ptr + offset) = *pId;
            offset += sizeof(DWORD);
        }

        *ptrPtr = ptr;
    }

    return length;
}

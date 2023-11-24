#include "CGameSpriteEquipment.h"

#include "CGameSprite.h"
#include "CItem.h"
#include "CScreenInventory.h"
#include "CUtil.h"

// 0x85BD79
const BYTE CGameSpriteEquipment::SLOT_AMULET = 0;

// 0x85BD7A
const BYTE CGameSpriteEquipment::SLOT_ARMOR = 1;

// 0x85BD7B
const BYTE CGameSpriteEquipment::SLOT_BELT = 2;

// 0x85BD7C
const BYTE CGameSpriteEquipment::SLOT_BOOTS = 3;

// 0x85BD7D
const BYTE CGameSpriteEquipment::SLOT_CLOAK = 4;

// 0x85BD7E
const BYTE CGameSpriteEquipment::SLOT_GAUNTLETS = 5;

// 0x85BD7F
const BYTE CGameSpriteEquipment::SLOT_HELMET = 6;

// 0x85BD80
const BYTE CGameSpriteEquipment::SLOT_RING_LEFT = 7;

// 0x85BD81
const BYTE CGameSpriteEquipment::SLOT_RING_RIGHT = 8;

// 0x85BD82
const BYTE CGameSpriteEquipment::SLOT_SHIELD = 9;

// 0x85BD83
const BYTE CGameSpriteEquipment::SLOT_FIST = 10;

// 0x85BD84
const BYTE CGameSpriteEquipment::SLOT_AMMO = 11;

// 0x85BD84
const BYTE CGameSpriteEquipment::SLOT_MISC = 15;

// 0x85BD86
const BYTE CGameSpriteEquipment::SLOT_WEAPON = 43;

// 0x85BD87
const BYTE CGameSpriteEquipment::NUM_SLOT = 51;

// 0x85BD88
const WORD CGameSpriteEquipment::NO_WEAPON = 1000;

// 0x7123F0
CGameSpriteEquipment::CGameSpriteEquipment()
{
    for (int index = 0; index < 51; index++) {
        m_items[index] = NULL;
    }

    m_selectedWeaponAbility = 0;
    m_pSprite = 0;
    m_selectedWeapon = 10;
}

// 0x712420
CGameSpriteEquipment::~CGameSpriteEquipment()
{
    ClearMarshal(FALSE);
}

// 0x712430
void CGameSpriteEquipment::ClearMarshal(BOOL bUnequip)
{
    if (m_items[m_selectedWeapon] != NULL && bUnequip) {
        m_items[m_selectedWeapon]->Unequip(m_pSprite, 0, TRUE, FALSE);
    }

    m_selectedWeapon = 10;
    m_selectedWeaponAbility = 0;

    for (int index = 0; index < 51; index++) {
        if (m_items[index] != NULL) {
            if (index < 10 && bUnequip) {
                m_items[index]->Unequip(m_pSprite, index, TRUE, FALSE);
            }

            delete m_items[index];
            m_items[index] = NULL;
        }
    }
}

// 0x7124C0
void CGameSpriteEquipment::Marshal()
{
    // TODO: Incomplete.
}

// 0x713040
void CGameSpriteEquipment::Unmarshal(CCreatureFileEquipment* pHeader, CCreatureFileItem* pItems, DWORD nItems, CGameSprite* pSprite)
{
    CCreatureFileItem* pItem;
    SHORT cnt;

    if (nItems == 0) {
        if (pSprite->GetAIType().m_nClass == CAIOBJECTTYPE_C_MONK) {
            pSprite->SetMonkAbilities();
        } else {
            m_items[SLOT_FIST] = new CItem(CResRef("00FIST"), 0, 0, 0, 0, 0);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15386
            UTIL_ASSERT(m_items[SLOT_FIST] != NULL);

            m_selectedWeapon = SLOT_FIST;
            m_selectedWeaponAbility = 0;
        }
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 15396
        UTIL_ASSERT(m_selectedWeapon == SLOT_FIST);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 15397
        UTIL_ASSERT(pHeader != NULL && pItems != NULL && pSprite != NULL);

        if ((pSprite->GetAIType().m_nClassMask & CLASSMASK_MONK) != 0) {
            pSprite->SetMonkAbilities();
        } else {
            m_items[SLOT_FIST] = new CItem(CResRef("00FIST"), 0, 0, 0, 0, 0);
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
        // __LINE__: 15416
        UTIL_ASSERT(m_items[SLOT_FIST] != NULL);

        if (pHeader->m_helmetItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15419
            UTIL_ASSERT(pHeader->m_helmetItem < nItems);

            pItem = &(pItems[pHeader->m_helmetItem]);

            m_items[SLOT_HELMET] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15422
            UTIL_ASSERT(m_items[SLOT_HELMET] != NULL);

            if (m_items[SLOT_HELMET]->GetResRef() != "") {
                m_items[SLOT_HELMET]->Equip(pSprite, SLOT_HELMET, FALSE);
            } else {
                delete m_items[SLOT_HELMET];
                m_items[SLOT_HELMET] = NULL;
            }
        }

        if (pHeader->m_armorItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15433
            UTIL_ASSERT(pHeader->m_armorItem < nItems);

            pItem = &(pItems[pHeader->m_armorItem]);

            m_items[SLOT_ARMOR] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15436
            UTIL_ASSERT(m_items[SLOT_ARMOR] != NULL);

            if (m_items[SLOT_ARMOR]->GetResRef() != "") {
                m_items[SLOT_ARMOR]->Equip(pSprite, SLOT_ARMOR, FALSE);
            } else {
                delete m_items[SLOT_ARMOR];
                m_items[SLOT_ARMOR] = NULL;
            }
        }

        if (pHeader->m_shieldItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15447
            UTIL_ASSERT(pHeader->m_shieldItem < nItems);

            pItem = &(pItems[pHeader->m_shieldItem]);

            m_items[SLOT_SHIELD] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15450
            UTIL_ASSERT(m_items[SLOT_SHIELD] != NULL);

            if (m_items[SLOT_SHIELD]->GetResRef() != "") {
                m_items[SLOT_SHIELD]->Equip(pSprite, SLOT_SHIELD, FALSE);
            } else {
                delete m_items[SLOT_SHIELD];
                m_items[SLOT_SHIELD] = NULL;
            }
        }

        if (pHeader->m_gauntletsItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15461
            UTIL_ASSERT(pHeader->m_gauntletsItem < nItems);

            pItem = &(pItems[pHeader->m_gauntletsItem]);

            m_items[SLOT_GAUNTLETS] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15465
            UTIL_ASSERT(m_items[SLOT_GAUNTLETS] != NULL);

            if (m_items[SLOT_GAUNTLETS]->GetResRef() != "") {
                m_items[SLOT_GAUNTLETS]->Equip(pSprite, SLOT_GAUNTLETS, FALSE);
            } else {
                delete m_items[SLOT_GAUNTLETS];
                m_items[SLOT_GAUNTLETS] = NULL;
            }
        }

        if (pHeader->m_ringLeftItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15476
            UTIL_ASSERT(pHeader->m_ringLeftItem < nItems);

            pItem = &(pItems[pHeader->m_ringLeftItem]);

            m_items[SLOT_RING_LEFT] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15481
            UTIL_ASSERT(m_items[SLOT_RING_LEFT] != NULL);

            if (m_items[SLOT_RING_LEFT]->GetResRef() != "") {
                m_items[SLOT_RING_LEFT]->Equip(pSprite, SLOT_RING_LEFT, FALSE);
            } else {
                delete m_items[SLOT_RING_LEFT];
                m_items[SLOT_RING_LEFT] = NULL;
            }
        }

        if (pHeader->m_ringRightItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15492
            UTIL_ASSERT(pHeader->m_ringRightItem < nItems);

            pItem = &(pItems[pHeader->m_ringRightItem]);

            m_items[SLOT_RING_RIGHT] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15494
            UTIL_ASSERT(m_items[SLOT_RING_RIGHT] != NULL);

            if (m_items[SLOT_RING_RIGHT]->GetResRef() != "") {
                m_items[SLOT_RING_RIGHT]->Equip(pSprite, SLOT_RING_RIGHT, FALSE);
            } else {
                delete m_items[SLOT_RING_RIGHT];
                m_items[SLOT_RING_RIGHT] = NULL;
            }
        }

        if (pHeader->m_amuletItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15508
            UTIL_ASSERT(pHeader->m_amuletItem < nItems);

            pItem = &(pItems[pHeader->m_amuletItem]);

            m_items[SLOT_AMULET] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15512
            UTIL_ASSERT(m_items[SLOT_AMULET] != NULL);

            if (m_items[SLOT_AMULET]->GetResRef() != "") {
                m_items[SLOT_AMULET]->Equip(pSprite, SLOT_AMULET, FALSE);
            } else {
                delete m_items[SLOT_AMULET];
                m_items[SLOT_AMULET] = NULL;
            }
        }

        if (pHeader->m_beltItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15523
            UTIL_ASSERT(pHeader->m_beltItem < nItems);

            pItem = &(pItems[pHeader->m_beltItem]);

            m_items[SLOT_BELT] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15527
            UTIL_ASSERT(m_items[SLOT_BELT] != NULL);

            if (m_items[SLOT_BELT]->GetResRef() != "") {
                m_items[SLOT_BELT]->Equip(pSprite, SLOT_BELT, FALSE);
            } else {
                delete m_items[SLOT_BELT];
                m_items[SLOT_BELT] = NULL;
            }
        }

        if (pHeader->m_bootsItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15538
            UTIL_ASSERT(pHeader->m_bootsItem < nItems);

            pItem = &(pItems[pHeader->m_bootsItem]);

            m_items[SLOT_BOOTS] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15542
            UTIL_ASSERT(m_items[SLOT_BOOTS] != NULL);

            if (m_items[SLOT_BOOTS]->GetResRef() != "") {
                m_items[SLOT_BOOTS]->Equip(pSprite, SLOT_BOOTS, FALSE);
            } else {
                delete m_items[SLOT_BOOTS];
                m_items[SLOT_BOOTS] = NULL;
            }
        }

        if (pHeader->m_cloakItem != 0xFFFF) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15553
            UTIL_ASSERT(pHeader->m_cloakItem < nItems);

            pItem = &(pItems[pHeader->m_cloakItem]);

            m_items[SLOT_CLOAK] = new CItem(pItem->m_itemId,
                pItem->m_usageCount[0],
                pItem->m_usageCount[1],
                pItem->m_usageCount[2],
                pItem->m_wear,
                pItem->m_dynamicFlags);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
            // __LINE__: 15557
            UTIL_ASSERT(m_items[SLOT_CLOAK] != NULL);

            if (m_items[SLOT_CLOAK]->GetResRef() != "") {
                m_items[SLOT_CLOAK]->Equip(pSprite, SLOT_CLOAK, FALSE);
            } else {
                delete m_items[SLOT_CLOAK];
                m_items[SLOT_CLOAK] = NULL;
            }
        }

        for (cnt = 0; cnt < 8; cnt++) {
            if (pHeader->m_weaponItem[cnt] != 0xFFFF) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15569
                UTIL_ASSERT(pHeader->m_weaponItem[cnt] < nItems);

                pItem = &(pItems[pHeader->m_weaponItem[cnt]]);

                m_items[SLOT_WEAPON + cnt] = new CItem(pItem->m_itemId,
                    pItem->m_usageCount[0],
                    pItem->m_usageCount[1],
                    pItem->m_usageCount[2],
                    pItem->m_wear,
                    pItem->m_dynamicFlags);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15573
                UTIL_ASSERT(m_items[SLOT_WEAPON + cnt] != NULL);

                if (m_items[SLOT_WEAPON + cnt]->GetResRef() == "") {
                    delete m_items[SLOT_WEAPON + cnt];
                    m_items[SLOT_WEAPON + cnt] = NULL;
                }
            }
        }

        for (cnt = 0; cnt < 4; cnt++) {
            if (pHeader->m_ammoItem[cnt] != 0xFFFF) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15583
                UTIL_ASSERT(pHeader->m_ammoItem[cnt] < nItems);

                pItem = &(pItems[pHeader->m_ammoItem[cnt]]);

                m_items[SLOT_AMMO + cnt] = new CItem(pItem->m_itemId,
                    pItem->m_usageCount[0],
                    pItem->m_usageCount[1],
                    pItem->m_usageCount[2],
                    pItem->m_wear,
                    pItem->m_dynamicFlags);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15586
                UTIL_ASSERT(m_items[SLOT_AMMO + cnt] != NULL);

                if (m_items[SLOT_AMMO + cnt]->GetResRef() == "") {
                    delete m_items[SLOT_AMMO + cnt];
                    m_items[SLOT_AMMO + cnt] = NULL;
                }
            }
        }

        for (cnt = 0; cnt < 28; cnt++) {
            if (pHeader->m_miscItem[cnt] != 0xFFFF) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15596
                UTIL_ASSERT(pHeader->m_miscItem[cnt] < nItems);

                pItem = &(pItems[pHeader->m_miscItem[cnt]]);

                m_items[SLOT_MISC + cnt] = new CItem(pItem->m_itemId,
                    pItem->m_usageCount[0],
                    pItem->m_usageCount[1],
                    pItem->m_usageCount[2],
                    pItem->m_wear,
                    pItem->m_dynamicFlags);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjCreature.cpp
                // __LINE__: 15600
                UTIL_ASSERT(m_items[SLOT_MISC + cnt] != NULL);

                if (m_items[SLOT_MISC + cnt]->GetResRef() == "") {
                    delete m_items[SLOT_MISC + cnt];
                    m_items[SLOT_MISC + cnt] = NULL;
                }
            }
        }

        BOOL placed = FALSE;
        if (pHeader->m_selectedWeapon != NO_WEAPON) {
            // NOTE: Can be negative.
            SHORT selectedWeapon = pHeader->m_selectedWeapon;
            if (selectedWeapon != -1 || m_items[42] != NULL) {
                CItem* pItem = m_items[selectedWeapon + SLOT_WEAPON];
                if (pItem != NULL
                    && pHeader->m_selectedWeaponAbility < pItem->GetAbilityCount()) {
                    m_selectedWeapon = selectedWeapon + SLOT_WEAPON;
                    m_selectedWeaponAbility = pHeader->m_selectedWeaponAbility;
                    placed = TRUE;
                }
            }
        }

        if (!placed) {
            m_selectedWeapon = SLOT_FIST;
            m_selectedWeaponAbility = 0;
        }
    }
}

// 0x713FC0
UINT CGameSpriteEquipment::GetUsedSlotsCount()
{
    UINT nCount = 0;

    for (UINT nIndex = 0; nIndex < CScreenInventory::PERSONAL_INVENTORY_SIZE; nIndex++) {
        if (m_items[18 + nIndex] != NULL) {
            nCount++;
        }
    }

    return nCount;
}

// NOTE: Inlined.
void CGameSpriteEquipment::SetSpritePointer(CGameSprite* pSprite)
{
    // __FILE__: .\Include\ObjCreature.h
    // __LINE__: 243
    UTIL_ASSERT(pSprite != NULL);

    m_pSprite = pSprite;
}

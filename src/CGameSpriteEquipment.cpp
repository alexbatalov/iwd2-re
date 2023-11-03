#include "CGameSpriteEquipment.h"

#include "CGameSprite.h"
#include "CItem.h"
#include "CScreenInventory.h"

// 0x85BD83
const BYTE CGameSpriteEquipment::SLOT_FIST = 10;

// 0x85BD87
const BYTE CGameSpriteEquipment::NUM_SLOT = 51;

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
void CGameSpriteEquipment::Unmarshal()
{
    // TODO: Incomplete.
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

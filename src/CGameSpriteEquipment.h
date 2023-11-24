#ifndef CGAMESPRITEEQUIPMENT_H_
#define CGAMESPRITEEQUIPMENT_H_

#include "mfc.h"

#include "FileFormat.h"

class CGameSprite;
class CItem;

class CGameSpriteEquipment {
public:
    static const BYTE SLOT_AMULET;
    static const BYTE SLOT_ARMOR;
    static const BYTE SLOT_BELT;
    static const BYTE SLOT_BOOTS;
    static const BYTE SLOT_CLOAK;
    static const BYTE SLOT_HELMET;
    static const BYTE SLOT_GAUNTLETS;
    static const BYTE SLOT_RING_LEFT;
    static const BYTE SLOT_RING_RIGHT;
    static const BYTE SLOT_SHIELD;
    static const BYTE SLOT_FIST;
    static const BYTE SLOT_AMMO;
    static const BYTE SLOT_MISC;
    static const BYTE SLOT_WEAPON;
    static const BYTE NUM_SLOT;
    static const WORD NO_WEAPON;

    CGameSpriteEquipment();
    ~CGameSpriteEquipment();
    void ClearMarshal(BOOL bUnequip);
    void Marshal();
    void Unmarshal(CCreatureFileEquipment* pHeader, CCreatureFileItem* pItems, DWORD nItems, CGameSprite* pSprite);
    UINT GetUsedSlotsCount();

    void SetSpritePointer(CGameSprite* pSprite);

    /* 0000 */ CItem* m_items[51];
    /* 00CC */ BYTE m_selectedWeapon;
    /* 00CE */ WORD m_selectedWeaponAbility;
    /* 00D0 */ CGameSprite* m_pSprite;
};

#endif /* CGAMESPRITEEQUIPMENT_H_ */

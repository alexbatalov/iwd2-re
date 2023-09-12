#ifndef CGAMESPRITEEQUIPMENT_H_
#define CGAMESPRITEEQUIPMENT_H_

#include "mfc.h"

class CGameSprite;
class CItem;

class CGameSpriteEquipment {
public:
    static const BYTE NUM_SLOT;

    CGameSpriteEquipment();
    ~CGameSpriteEquipment();
    void ClearMarshal(BOOL bUnequip);
    void Marshal();
    void Unmarshal();
    UINT GetUsedSlotsCount();

    /* 0000 */ CItem* m_items[51];
    /* 00CC */ BYTE m_selectedWeapon;
    /* 00CE */ WORD m_selectedWeaponAbility;
    /* 00D0 */ CGameSprite* m_pSprite;
};

#endif /* CGAMESPRITEEQUIPMENT_H_ */

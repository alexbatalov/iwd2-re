#ifndef CGAMESAVE_H_
#define CGAMESAVE_H_

#include "mfc.h"

#include "CResRef.h"

class CItem;

class CGameSave {
public:
    CGameSave();

    /* 0000 */ CResRef m_cResCurrentWorldArea;
    /* 0008 */ DWORD m_nCurrentWorldLink;
    /* 000C */ DWORD m_nPartyGold;
    /* 0010 */ SHORT m_curFormation;
    /* 0012 */ SHORT m_quickFormations[5];
    /* 001C */ CItem* m_groupInventory[100];
    /* 01AC */ int field_1AC;
    /* 01B0 */ short field_1B0;
    /* 01B2 */ int field_1B2;
    /* 01B6 */ DWORD m_mode;
    /* 01BA */ BOOL m_cutScene;
};

#endif /* CGAMESAVE_H_ */

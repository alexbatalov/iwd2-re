#ifndef CINFBUTTONARRAY_H_
#define CINFBUTTONARRAY_H_

#include "CVidCell.h"

class CButtonData;

class CInfButtonSettings {
public:
    CInfButtonSettings();
    ~CInfButtonSettings();

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ CVidCell field_14;
    /* 00EE */ CVidCell field_EE;
    /* 01C8 */ int field_1C8;
    /* 01CC */ int field_1CC;
    /* 01D0 */ int field_1D0;
    /* 01D4 */ int field_1D4;
    /* 01D8 */ int field_1D8;
    /* 01DC */ BOOL m_bGreyOut;
    /* 01E0 */ int field_1E0;
};

class CInfButtonArray {
public:
    static const BYTE STATE_NONE;
    static const BYTE byte_851701;
    static const BYTE byte_85170E;

    CInfButtonArray();

    static void GetSelectedQuickWeaponData(CButtonData& cButtonData);
    static BYTE GetSelectedModalMode();
    BYTE GetButtonId(INT buttonType);
    BOOL ResetState();
    void UpdateState();
    BOOL SetState(INT nState, int a2);
    void UpdateButtons();
    void OnLButtonPressed(int buttonID);
    void OnRButtonPressed(int buttonID);

    void SetSelectedButton(INT nSelectedButton);
    void UpdateCustomizableButtonTypes(INT* pButtonList);
    void UpdateSelectedWeaponSet(BYTE nIndex);

    /* 0000 */ CInfButtonSettings m_buttonArray[12];
    /* 16B0 */ INT m_buttonTypes[12];
    /* 16E0 */ unsigned char field_16E0[8];
    /* 16E8 */ CVidCell field_16E8;
    /* 17C2 */ CVidCell field_17C2;
    /* 189C */ CVidCell field_189C;
    /* 1976 */ unsigned char field_1976[8];
    /* 197E */ INT m_nSelectedButton;
    /* 1982 */ int m_nState;
    /* 1986 */ unsigned char field_1986[44];
    /* 19B2 */ int field_19B2;
    /* 19B6 */ INT m_customizableButtonTypes[9];
    /* 19DA */ unsigned char field_19DA[14];
    /* 19E8 */ BYTE m_nSelectedWeaponSet;
};

#endif /* CINFBUTTONARRAY_H_ */

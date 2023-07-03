#ifndef CINFBUTTONARRAY_H_
#define CINFBUTTONARRAY_H_

#include "CVidCell.h"

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
    /* 01D8 */ int field_1D8;
    /* 01DC */ int field_1DC;
};

class CInfButtonArray {
public:
    CInfButtonArray();

    BOOL ResetState();

    /* 0000 */ CInfButtonSettings m_buttonArray[12];
    /* 16E8 */ CVidCell field_16E8;
    /* 17C2 */ CVidCell field_17C2;
    /* 189C */ CVidCell field_189C;
    /* 197E */ INT m_nSelectedButton;
};

#endif /* CINFBUTTONARRAY_H_ */

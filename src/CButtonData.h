#ifndef CBUTTONDATA_H_
#define CBUTTONDATA_H_

#include "CResRef.h"

class CButtonData {
public:
    CButtonData();

    /* 0000 */ CResRef m_icon;
    /* 0008 */ int field_8;
    /* 000C */ CResRef m_launcherIcon;
    /* 0014 */ int field_14;
    /* 0018 */ short field_18;
    /* 001A */ short field_1A;
    /* 001C */ short field_1C;
    /* 001E */ short field_1E;
    /* 0020 */ CResRef field_20;
    /* 0028 */ short field_28;
    /* 002A */ int field_2A;
    /* 002E */ int field_2E;
    /* 0032 */ int field_32;
    /* 0036 */ unsigned char field_36;
    /* 0037 */ unsigned char field_37;
    /* 0038 */ short field_38;
    /* 003A */ unsigned char field_3A;
    /* 003B */ unsigned char field_3B;
};

#endif /* CBUTTONDATA_H_ */

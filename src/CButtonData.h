#ifndef CBUTTONDATA_H_
#define CBUTTONDATA_H_

#include "BalDataTypes.h"
#include "CResRef.h"

class CAbilityId {
public:
    CAbilityId();
    CAbilityId& operator=(const CAbilityId& other);

    /* 0000 */ SHORT m_itemType;
    /* 0002 */ SHORT m_itemNum;
    /* 0004 */ SHORT m_abilityNum;
    /* 0006 */ CResRef m_res;
    /* 000E */ short m_targetType;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ unsigned char field_1C;
    /* 001D */ unsigned char field_1D;
    /* 001E */ short field_1E;
};

class CButtonData {
public:
    CButtonData();
    CButtonData& operator=(const CButtonData& other);

    /* 0000 */ CResRef m_icon;
    /* 0008 */ STRREF m_name;
    /* 000C */ CResRef m_launcherIcon;
    /* 0014 */ STRREF m_launcherName;
    /* 0018 */ SHORT m_count;
    /* 001A */ CAbilityId m_abilityId;
    /* 003A */ BOOLEAN m_bDisabled;
    /* 003B */ BOOLEAN m_bDisplayCount;
};

#endif /* CBUTTONDATA_H_ */

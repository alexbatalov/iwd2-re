#ifndef CDERIVEDSTATS_H_
#define CDERIVEDSTATS_H_

#include "CAIObjectType.h"

#include <set>

class CGameSprite;
class CCreatureFileHeader;

class CDerivedStats {
public:
    CDerivedStats();
    void Reload(CGameSprite* pSprite, CCreatureFileHeader* pCreature, int a3, int a4);
    CDerivedStats& operator+=(const CDerivedStats& other);
    void CheckLimits();
    LONG GetAtOffset(SHORT offset);
    int sub_447390();
    unsigned char sub_4473A0();
    DWORD GetSorcererWizardLevel();
    DWORD GetBardMonkRogueLevel();
    BOOL HasClassMask(INT iClassType);
    DWORD GetClassMaskLevel(DWORD dwMask);
    DWORD GetClassLevel(INT iClassType);
    void SetClassLevel(INT iClassType, INT nLevel);
    BOOL HasClass(INT iClassType);
    INT GetBestClass();

    /* 0000 */ DWORD m_generalState;
    /* 0004 */ short field_4;
    /* 0006 */ short field_6;
    /* 0008 */ short field_8;
    /* 000A */ short field_A;
    /* 000C */ short field_C;
    /* 000E */ short field_E;
    /* 0010 */ short field_10;
    /* 0012 */ short field_12;
    /* 0014 */ short field_14;
    /* 0016 */ short field_16;
    /* 0018 */ short field_18;
    /* 001A */ short field_1A;
    /* 001C */ short field_1C;
    /* 001E */ short field_1E;
    /* 0020 */ short field_20;
    /* 0022 */ SHORT m_nResistFire;
    /* 0024 */ SHORT m_nResistCold;
    /* 0026 */ SHORT m_nResistElectricity;
    /* 0028 */ SHORT m_nResistAcid;
    /* 002A */ SHORT m_nResistMagic;
    /* 002C */ SHORT m_nResistMagicFire;
    /* 002E */ SHORT m_nResistMagicCold;
    /* 0030 */ SHORT m_nResistSlashing;
    /* 0032 */ SHORT m_nResistCrushing;
    /* 0034 */ SHORT m_nResistPiercing;
    /* 0036 */ short field_36;
    /* 0038 */ short field_38;
    /* 003A */ short field_3A;
    /* 003C */ short field_3C;
    /* 003E */ short field_3E;
    /* 0042 */ DWORD m_classMask;
    /* 0046 */ BYTE m_nLevel;
    union {
        struct {
            /* 0047 */ BYTE m_barbarianLevel;
            /* 0048 */ BYTE m_bardLevel;
            /* 0049 */ BYTE m_clericLevel;
            /* 004A */ BYTE m_druidLevel;
            /* 004B */ BYTE m_fighterLevel;
            /* 004C */ BYTE m_monkLevel;
            /* 004D */ BYTE m_paladinLevel;
            /* 004E */ BYTE m_rangerLevel;
            /* 004F */ BYTE m_rogueLevel;
            /* 0050 */ BYTE m_sorcererLevel;
            /* 0051 */ BYTE m_wizardLevel;
        };
        /* 0047 */ BYTE m_nClassLevels[CAIOBJECT_CLASS_MAX];
    };
    /* 0052 */ short field_52;
    /* 0054 */ SHORT m_nSTR;
    /* 0056 */ SHORT m_nINT;
    /* 0058 */ SHORT m_nWIS;
    /* 005A */ SHORT m_nDEX;
    /* 005C */ SHORT m_nCON;
    /* 005E */ SHORT m_nCHR;
    /* 0060 */ int field_60;
    /* 0064 */ int field_64;
    /* 0068 */ int field_68;
    /* 006C */ int field_6C;
    /* 0070 */ int field_70;
    /* 0074 */ short field_74;
    /* 0076 */ short m_favoredEnemies[8];
    /* 0086 */ short field_86;
    /* 0088 */ short field_88;
    /* 008A */ short field_8A;
    /* 008C */ short field_8C;
    /* 008E */ short field_8E;
    /* 0090 */ short field_90;
    /* 0092 */ short field_92;
    /* 0094 */ SHORT m_nLayOnHandsAmount;
    /* 0096 */ short field_96;
    /* 009A */ int field_9A;
    /* 009E */ int field_9E;
    /* 00A2 */ int m_nSpecialization;
    /* 00A6 */ int field_A6;
    /* 00AA */ int field_AA;
    /* 00AE */ int field_AE;
    /* 00B2 */ short field_B2;
    /* 00B4 */ short field_B4;
    /* 00B6 */ short field_B6;
    /* 00B8 */ short field_B8;
    /* 00BA */ short field_BA;
    /* 00BC */ int field_BC;
    /* 00C0 */ int field_C0;
    /* 00C4 */ short field_C4;
    /* 00C6 */ short field_C6;
    /* 00C8 */ short field_C8;
    /* 00CA */ short field_CA;
    /* 00CC */ int field_CC;
    /* 00D0 */ int field_D0;
    /* 00D4 */ int field_D4;
    /* 00D8 */ int field_D8;
    /* 00DC */ int field_DC;
    /* 00E0 */ int field_E0;
    /* 00E4 */ int field_E4;
    /* 00E8 */ int field_E8;
    /* 00EC */ int field_EC[8];
    /* 010C */ int field_10C;
    /* 0110 */ short field_110;
    /* 0112 */ short field_112;
    /* 0114 */ short field_114;
    /* 0116 */ short field_116;
    /* 0118 */ short field_118;
    /* 011A */ short field_11A;
    /* 011C */ short field_11C;
    /* 011E */ short field_11E;
    /* 0120 */ short field_120;
    /* 0122 */ short field_122;
    /* 0124 */ int field_124;
    /* 0128 */ int field_128;
    /* 012C */ int field_12C;
    /* 0130 */ int field_130;
    /* 0134 */ int field_134;
    /* 0138 */ int field_138;
    /* 013C */ int field_13C;
    /* 0140 */ int field_140;
    /* 0144 */ BYTE field_144[64];
    /* 0184 */ int field_184;
    /* 0188 */ CPtrList field_188;
    /* 01A4 */ CPtrList field_1A4;
    /* 01C0 */ CPtrList field_1C0;
    /* 0204 */ CPtrList field_204;
    /* 0220 */ CPtrList field_220;
    /* 023C */ CPtrList field_23C;
    /* 0258 */ CPtrList field_258;
    /* 0274 */ CPtrList field_274;
    /* 0290 */ CPtrList field_290;
    /* 02AC */ CPtrList field_2AC;
    /* 02C8 */ CPtrList field_2C8;
    /* 02E4 */ CPtrList field_2E4;
    /* 03C8 */ CPtrList field_3C8;
    /* 03E4 */ CPtrList field_3E4;
    /* 0400 */ CPtrList field_400;
    /* 041C */ CPtrList field_41C;
    /* 0438 */ CPtrList field_438;
    /* 0454 */ CPtrList field_454;
    /* 04AC */ CPtrList field_4AC;
    /* 0480 */ std::set<int> m_naturalImmunities;
    /* 04C8 */ CPtrList field_4C8;
    /* 04E4 */ CPtrList field_4E4;
    /* 0500 */ CPtrList field_500;
    /* 051C */ CPtrList field_51C;
    /* 0538 */ CPtrList field_538;
    /* 0554 */ CPtrList field_554;
    /* 0570 */ CPtrList field_570;
    /* 0590 */ CPtrList field_590;
    /* 0DAC */ unsigned char field_DAC[160];
    /* 0E4C */ int field_E4C;
    /* 0E50 */ int field_E50;
    /* 0E54 */ int field_E54;
};

#endif /* CDERIVEDSTATS_H_ */

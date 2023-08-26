#ifndef CDERIVEDSTATS_H_
#define CDERIVEDSTATS_H_

#include "CAIObjectType.h"
#include "CImmunities.h"

#include <set>

// STATE.IDS

#define STATE_NORMAL 0x00000000
#define STATE_DEAD 0x00000800
#define STATE_ACID_DEATH 0x00000400
#define STATE_FLAME_DEATH 0x00000200
#define STATE_EXPLODING_DEATH 0x00000100
#define STATE_STONE_DEATH 0x00000080
#define STATE_FROZEN_DEATH 0x00000040
#define STATE_HELPLESS 0x00000020
#define STATE_INVISIBLE 0x00000010
#define STATE_STUNNED 0x00000008
#define STATE_PANIC 0x00000004
#define STATE_BERSERK 0x00000002
#define STATE_SLEEPING 0x00000001
#define STATE_SILENCED 0x00001000
#define STATE_CHARMED 0x00002000
#define STATE_POISONED 0x00004000
#define STATE_HASTED 0x00008000
#define STATE_SLOWED 0x00010000
#define STATE_INFRAVISION 0x00020000
#define STATE_BLIND 0x00040000
#define STATE_DISEASED 0x00080000
#define STATE_FEEBLEMINDED 0x00100000
#define STATE_NONDETECTION 0x00200000
#define STATE_IMPROVEDINVISIBILITY 0x00400000
#define STATE_BLESS 0x00800000
#define STATE_CHANT 0x01000000
#define STATE_FADE_IN 0x02000000
#define STATE_FADE_OUT 0x04000000
#define STATE_AID 0x08000000
#define STATE_SUMMONED_CREATURE 0x10000000
#define STATE_BLUR 0x20000000
#define STATE_MIRRORIMAGE 0x40000000
#define STATE_CONFUSED 0x80000000

#define STATE_ANY_DEATH         \
    (STATE_DEAD                 \
        | STATE_ACID_DEATH      \
        | STATE_FLAME_DEATH     \
        | STATE_EXPLODING_DEATH \
        | STATE_STONE_DEATH     \
        | STATE_FROZEN_DEATH)

// STATS.IDS

#define STAT_MAXHITPOINTS 1
#define STAT_ARMORCLASS 2
#define STAT_ACBLUDGEONINGMOD 3
#define STAT_ACMISSILEMOD 4
#define STAT_ACPIERCINGMOD 5
#define STAT_ACSLASHINGMOD 6
#define STAT_THAC0 7
#define STAT_NUMBEROFATTACKS 8
#define STAT_SAVEFORTITUDE 9
#define STAT_SAVEREFLEX 10
#define STAT_SAVEWILL 11
#define STAT_KNOWLEDGEARCANA 12
#define STAT_RESISTFIRE 14
#define STAT_RESISTCOLD 15
#define STAT_RESISTELECTRICITY 16
#define STAT_RESISTACID 17
#define STAT_RESISTMAGIC 18
#define STAT_RESISTMAGICFIRE 19
#define STAT_RESISTMAGICCOLD 20
#define STAT_RESISTSLASHING 21
#define STAT_RESISTBLUDGEONING 22
#define STAT_RESISTPIERCING 23
#define STAT_RESISTMISSILE 24
#define STAT_ALCHEMY 25
#define STAT_LOCKPICKING 26
#define STAT_MOVESILENTLY 27
#define STAT_TRAPS 28
#define STAT_PICKPOCKET 29
#define STAT_FATIGUE 30
#define STAT_INTOXICATION 31
#define STAT_LUCK 32
#define STAT_TRACKING 33
#define STAT_LEVEL 34
#define STAT_SEX 35
#define STAT_STR 36
#define STAT_STREXTRA 37
#define STAT_INT 38
#define STAT_WIS 39
#define STAT_DEX 40
#define STAT_CON 41
#define STAT_CHR 42
#define STAT_XPVALUE 43
#define STAT_XP 44
#define STAT_GOLD 45
#define STAT_MORALEBREAK 46
#define STAT_MORALERECOVERYTIME 47
#define STAT_REPUTATION 48
#define STAT_HATEDRACE 49
#define STAT_DAMAGEBONUS 50
#define STAT_SPELLFAILUREMAGE 51
#define STAT_SPELLFAILUREPRIEST 52
#define STAT_SPELLDURATIONMODMAGE 53
#define STAT_SPELLDURATIONMODPRIEST 54
#define STAT_TURNUNDEADLEVEL 55
#define STAT_BACKSTABDAMAGEMULTIPLIER 56
#define STAT_LAYONHANDSAMOUNT 57
#define STAT_HELD 58
#define STAT_POLYMORPHED 59
#define STAT_TRANSLUCENT 60
#define STAT_IDENTIFYMODE 61
#define STAT_ENTANGLE 62
#define STAT_SANCTUARY 63
#define STAT_MINORGLOBE 64
#define STAT_SHIELDGLOBE 65
#define STAT_GREASE 66
#define STAT_WEB 67
#define STAT_LEVEL2 68
#define STAT_LEVEL3 69
#define STAT_CASTERHOLD 70
#define STAT_ENCUMBERANCE 71
#define STAT_MISSILETHAC0BONUS 72
#define STAT_MAGICDAMAGERESISTANCE 73
#define STAT_RESISTPOISON 74
#define STAT_DONOTJUMP 75
#define STAT_AURACLEANSING 76
#define STAT_MENTALSPEED 77
#define STAT_PHYSICALSPEED 78
#define STAT_CASTINGLEVELBONUSMAGE 79
#define STAT_CASTINGLEVELBONUSCLERIC 80
#define STAT_SEEINVISIBLE 81
#define STAT_IGNOREDIALOGPAUSE 82
#define STAT_MINHITPOINTS 83
#define STAT_THAC0BONUSRIGHT 84
#define STAT_THAC0BONUSLEFT 85
#define STAT_DAMAGEBONUSRIGHT 86
#define STAT_DAMAGEBONUSLEFT 87
#define STAT_STONESKINS 88
#define STAT_KIT 89
#define STAT_HIDEINSHADOWS 90
#define STAT_MOVESILENTLYMTPBONUS 91
#define STAT_HIDEINSHADOWSMTPBONUS 92
#define STAT_SUBRACE 93
#define STAT_USEMAGICDEVICE 94
#define STAT_CLASSLEVELSUM 95
#define STAT_CLASSLEVELBARBARIAN 96
#define STAT_CLASSLEVELBARD 97
#define STAT_CLASSLEVELCLERIC 98
#define STAT_CLASSLEVELDRUID 99
#define STAT_CLASSLEVELFIGHTER 100
#define STAT_CLASSLEVELMONK 101
#define STAT_CLASSLEVELPALADIN 102
#define STAT_CLASSLEVELRANGER 103
#define STAT_CLASSLEVELROGUE 104
#define STAT_CLASSLEVELSORCERER 105
#define STAT_CLASSLEVELWIZARD 106
#define STAT_107 107

class CCreatureFileHeader;
class CGameSprite;
class CGameSpriteGroupedSpellList;
class CGameSpriteSpells;

class CDerivedStats {
public:
    CDerivedStats();
    void Reload(CGameSprite* pSprite, CCreatureFileHeader* pCreature, CGameSpriteSpells* pSpells, CGameSpriteGroupedSpellList* pDomainSpells);
    void BonusInit();
    CDerivedStats& operator+=(const CDerivedStats& other);
    void CheckLimits();
    LONG GetAtOffset(SHORT offset);
    int GetXP();
    BYTE GetLevel();
    DWORD GetSorcererWizardLevel();
    DWORD GetBardMonkRogueLevel();
    BOOL HasClassMask(INT iClassType);
    DWORD GetClassMaskLevel(DWORD dwMask);
    DWORD GetClassLevel(INT iClassType);
    void SetClassLevel(INT iClassType, INT nLevel);
    BOOL HasClass(INT iClassType);
    INT GetBestClass();

    /* 0000 */ DWORD m_generalState;
    /* 0004 */ SHORT m_nMaxHitPoints;
    /* 0006 */ short field_6;
    /* 0008 */ short field_8;
    /* 000A */ short field_A;
    /* 000C */ short field_C;
    /* 000E */ SHORT m_nACCrushingMod;
    /* 0010 */ SHORT m_nACMissileMod;
    /* 0012 */ SHORT m_nACPiercingMod;
    /* 0014 */ SHORT m_nACSlashingMod;
    /* 0016 */ short field_16;
    /* 0018 */ SHORT m_nTHAC0;
    /* 001A */ SHORT m_nNumberOfAttacks;
    /* 001C */ SHORT m_nSaveVSFortitude;
    /* 001E */ SHORT m_nSaveVSReflex;
    /* 0020 */ SHORT m_nSaveVSWill;
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
    /* 0036 */ SHORT m_nResistMissile;
    /* 0038 */ SHORT m_nFatigue;
    /* 003A */ SHORT m_nIntoxication;
    /* 003C */ SHORT m_nLuck;
    /* 003E */ DWORD m_nSubRace;
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
    /* 0052 */ SHORT m_nSex;
    /* 0054 */ SHORT m_nSTR;
    /* 0056 */ SHORT m_nINT;
    /* 0058 */ SHORT m_nWIS;
    /* 005A */ SHORT m_nDEX;
    /* 005C */ SHORT m_nCON;
    /* 005E */ SHORT m_nCHR;
    /* 0060 */ DWORD m_nXPValue;
    /* 0064 */ DWORD m_nXP;
    /* 0068 */ DWORD m_nGold;
    /* 006C */ DWORD m_nMoraleBreak;
    /* 0070 */ DWORD m_nMoraleRecoveryTime;
    /* 0074 */ SHORT m_nReputation;
    /* 0076 */ SHORT m_favoredEnemies[8];
    /* 0086 */ SHORT m_nDamageBonus;
    /* 0088 */ SHORT m_nSpellFailureArcane; // #guess
    /* 008A */ SHORT m_nSpellFailureDivine; // #guess
    /* 008C */ SHORT m_nSpellDurationModMage;
    /* 008E */ SHORT m_nSpellDurationModPriest;
    /* 0090 */ SHORT m_nTurnUndeadLevel;
    /* 0092 */ SHORT m_nBackstabDamageMultiplier;
    /* 0094 */ SHORT m_nLayOnHandsAmount;
    /* 0096 */ BOOL m_bHeld;
    /* 009A */ BOOL m_bPolymorphed;
    /* 009E */ BOOL m_bIdentifyMode;
    /* 00A2 */ DWORD m_nSpecialization;
    /* 00A6 */ LONG m_nMoveSilentlyMTPBonus;
    /* 00AA */ LONG m_nHideInShadowsMTPBonus;
    /* 00AE */ BOOL m_bCasterHold;
    /* 00B2 */ SHORT m_nTranslucent;
    /* 00B4 */ SHORT m_nEncumberance;
    /* 00B6 */ SHORT m_nMissileTHAC0Bonus;
    /* 00B8 */ SHORT m_nMagicDamageResistance;
    /* 00BA */ SHORT m_nResistPoison;
    /* 00BC */ BOOL m_bDoNotJump;
    /* 00C0 */ BOOL m_bAuraCleansing;
    /* 00C4 */ SHORT m_nMentalSpeed;
    /* 00C6 */ SHORT m_nPhysicalSpeed;
    /* 00C8 */ SHORT m_nCastingLevelBonusMage;
    /* 00CA */ SHORT m_nCastingLevelBonusCleric;
    /* 00CC */ BOOL m_bSeeInvisible;
    /* 00D0 */ BOOL m_bIgnoreDialogPause;
    /* 00D4 */ LONG m_nMinHitPoints;
    /* 00D8 */ LONG m_THAC0BonusRight;
    /* 00DC */ LONG m_THAC0BonusLeft;
    /* 00E0 */ LONG m_DamageBonusRight;
    /* 00E4 */ LONG m_DamageBonusLeft;
    /* 00E8 */ LONG m_nStoneSkins;
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
    /* 0144 */ BYTE m_nSkills[64];
    /* 0184 */ int field_184;
    /* 0188 */ CPtrList field_188;
    /* 01A4 */ CPtrList field_1A4;
    /* 01C0 */ CPtrList field_1C0;
    /* 01DC */ CImmunitiesSpellLevel m_cImmunitiesSpellLevel;
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
    /* 0DA8 */ int field_DA8;
    /* 0DAC */ unsigned char field_DAC[160];
    /* 0E4C */ int field_E4C;
    /* 0E50 */ int field_E50;
    /* 0E54 */ int field_E54;
};

#endif /* CDERIVEDSTATS_H_ */

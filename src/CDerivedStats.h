#ifndef CDERIVEDSTATS_H_
#define CDERIVEDSTATS_H_

#include "CAIObjectType.h"
#include "CColorEffects.h"
#include "CImmunities.h"

#include <bitset>
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

// SPLSTATE.IDS

#define SPLSTATE_HOPELESSNESS 0
#define SPLSTATE_PROTECTION_FROM_EVIL 1
#define SPLSTATE_ARMOR_OF_FAITH 2
#define SPLSTATE_NAUSEA 3
#define SPLSTATE_ENFEEBLED 4
#define SPLSTATE_RED_FIRESHIELD 5
#define SPLSTATE_BLUE_FIRESHIELD 6
#define SPLSTATE_HELD 7
#define SPLSTATE_DEATH_WARD 8
#define SPLSTATE_HOLY_POWER 9
#define SPLSTATE_BENEFICIAL_CHANT 10
#define SPLSTATE_DETRIMENTAL_CHANT 11
#define SPLSTATE_BENEFICIAL_PRAYER 12
#define SPLSTATE_DETRIMENTAL_PRAYER 13
#define SPLSTATE_BENEFICIAL_RECITATION 14
#define SPLSTATE_DETRIMENTAL_RECITATION 15
#define SPLSTATE_ALLIED_RIGHTEOUS_WRATH_OF_THE_FAITHFUL 16
#define SPLSTATE_ALLIED_AND_SAME_ALIGNMENT_RIGHTEOUS_WRATH_OF_THE_FAITHFUL 17
#define SPLSTATE_STONESKIN 18
#define SPLSTATE_IRON_SKINS 19
#define SPLSTATE_SANCTUARY 20
#define SPLSTATE_OTILUKES_RESILIENT_SPHERE 21
#define SPLSTATE_BLESS 22
#define SPLSTATE_AID 23
#define SPLSTATE_BARKSKIN 24
#define SPLSTATE_DRAW_UPON_HOLY_MIGHT 25
#define SPLSTATE_ENTANGLE 26
#define SPLSTATE_WEB 27
#define SPLSTATE_GREASE 28
#define SPLSTATE_FREE_ACTION 29
#define SPLSTATE_ENTROPY_SHIELD 30
#define SPLSTATE_STORM_SHELL 31
#define SPLSTATE_PROTECTION_FROM_THE_ELEMENTS 32
#define SPLSTATE_BERSERK_ALWAYS_ACTIVE 33
#define SPLSTATE_BLOOD_RAGE 34
#define SPLSTATE_SUPPRESS_HP_INFO 35
#define SPLSTATE_DOESNT_AWAKEN_ON_DAMAGE 36
#define SPLSTATE_UNSTUN_ON_DAMAGE 37
#define SPLSTATE_DEAFENED 38
#define SPLSTATE_ANIMAL_RAGE 39
#define SPLSTATE_SNEAK_ATTACK_IMMUNITY 40
#define SPLSTATE_CHAOTIC_COMMANDS 41
#define SPLSTATE_MISCAST_MAGIC 42
#define SPLSTATE_PAIN 43
#define SPLSTATE_MALISON 44
#define SPLSTATE_CATS_GRACE 45
#define SPLSTATE_MOLD_TOUCH 46
#define SPLSTATE_SHROUD_OF_FLAME 47
#define SPLSTATE_EYE_OF_THE_MIND 48
#define SPLSTATE_EYE_OF_THE_SWORD 49
#define SPLSTATE_EYE_OF_THE_MAGE 50
#define SPLSTATE_EYE_OF_VENOM 51
#define SPLSTATE_EYE_OF_THE_SPIRIT 52
#define SPLSTATE_EYE_OF_FORTITUDE 53
#define SPLSTATE_EYE_OF_STONE 54
#define SPLSTATE_AEGIS 55
#define SPLSTATE_EXECUTIONERS_EYES 56
#define SPLSTATE_ENERGY_DRAINED 57
#define SPLSTATE_TORTOISE_SHELL 58
#define SPLSTATE_BLINK 59
#define SPLSTATE_MINOR_GLOBE_OF_INVULNERABILITY 60
#define SPLSTATE_PROTECTION_FROM_MISSILES 61
#define SPLSTATE_GHOST_ARMOR 62
#define SPLSTATE_REFLECTED_IMAGE 63
#define SPLSTATE_KAI_64 64
#define SPLSTATE_CALLED_SHOT 65
#define SPLSTATE_MIRROR_IMAGE 66
#define SPLSTATE_TURNED 67
#define SPLSTATE_BLADE_BARRIER 68
#define SPLSTATE_COAT_WEAPON_WITH_POISON 69
#define SPLSTATE_STUNNING_BLOW_70 70
#define SPLSTATE_QUIVERING_PALM 71
#define SPLSTATE_MENTAL_DOMINATION 72
#define SPLSTATE_GLOBE_OF_INVULNERABILITY 73
#define SPLSTATE_SHIELD 74
#define SPLSTATE_ANTIMAGIC_SHELL 75
#define SPLSTATE_FEAT_POWER_ATTACK_1 76
#define SPLSTATE_FEAT_POWER_ATTACK_2 77
#define SPLSTATE_FEAT_POWER_ATTACK_3 78
#define SPLSTATE_FEAT_POWER_ATTACK_4 79
#define SPLSTATE_FEAT_POWER_ATTACK_5 80
#define SPLSTATE_FEAT_EXPERTISE_1 81
#define SPLSTATE_FEAT_EXPERTISE_2 82
#define SPLSTATE_FEAT_EXPERTISE_3 83
#define SPLSTATE_FEAT_EXPERTISE_4 84
#define SPLSTATE_FEAT_EXPERTISE_5 85
#define SPLSTATE_FEAT_ARTERIAL_STRIKE 86
#define SPLSTATE_FEAT_HAMSTRING 87
#define SPLSTATE_FEAT_RAPID_SHOT 88
#define SPLSTATE_IRON_BODY 89
#define SPLSTATE_TENSERS_TRANSFORMATION 90
#define SPLSTATE_SMITE_EVIL 91
#define SPLSTATE_ALICORN_LANCE 92
#define SPLSTATE_CALL_LIGHTNING 93
#define SPLSTATE_CHAMPIONS_STRENGTH 94
#define SPLSTATE_CIRCLE_OF_BONES 95
#define SPLSTATE_CLOAK_OF_FEAR 96
#define SPLSTATE_CLOUD_OF_PESTILENCE 97
#define SPLSTATE_CONTAGION 98
#define SPLSTATE_BANE 99
#define SPLSTATE_DEFENSIVE_HARMONY 100
#define SPLSTATE_DESTRUCTION 101
#define SPLSTATE_DOLOROUS_DECAY 102
#define SPLSTATE_DOOM 103
#define SPLSTATE_EXALTATION 104
#define SPLSTATE_FAERIE_FIRE 105
#define SPLSTATE_FIND_TRAPS 106
#define SPLSTATE_GREATER_SHIELD_OF_LATHANDER 107
#define SPLSTATE_MAGIC_RESISTANCE 108
#define SPLSTATE_NEGATIVE_ENERGY_PROTECTION 109
#define SPLSTATE_PROTECTION_FROM_FIRE 110
#define SPLSTATE_PROTECTION_FROM_LIGHTNING 111
#define SPLSTATE_MINOR_ELEMENTAL_BARRIER 112
#define SPLSTATE_SHIELD_OF_LATHANDER 113
#define SPLSTATE_SLOW_POISON 114
#define SPLSTATE_SPELL_SHIELD 115
#define SPLSTATE_STATIC_CHARGE 116
#define SPLSTATE_STRENGTH_OF_ONE 117
#define SPLSTATE_UNDEAD_WARD 118
#define SPLSTATE_RESIST_FATIGUE 119
#define SPLSTATE_WALL_OF_FIRE 120
#define SPLSTATE_WALL_OF_MOONLIGHT 121
#define SPLSTATE_CHAOS 122
#define SPLSTATE_CHARMED 123
#define SPLSTATE_DIRE_CHARMED 124
#define SPLSTATE_CONTROLLED 125
#define SPLSTATE_CONFUSION 126
#define SPLSTATE_DOMINATED 127
#define SPLSTATE_FEEBLEMIND 128
#define SPLSTATE_MIND_BLANK 129
#define SPLSTATE_RIGID_THINKING 130
#define SPLSTATE_ARMOR 131
#define SPLSTATE_BELTYNS_BURNING_BLOOD 132
#define SPLSTATE_CLOUDKILL 133
#define SPLSTATE_DEATH_ARMOR 134
#define SPLSTATE_DISINTEGRATE 135
#define SPLSTATE_FLESH_TO_STONE 136
#define SPLSTATE_EAGLES_SPLENDOR 137
#define SPLSTATE_IMPROVED_HASTE 138
#define SPLSTATE_HASTE 139
#define SPLSTATE_LOWER_RESISTANCE 140
#define SPLSTATE_LUCK 141
#define SPLSTATE_MELFS_ACID_ARROW 142
#define SPLSTATE_OTILUKES_FREEZING_SPHERE 143
#define SPLSTATE_PROTECTION_FROM_ACID 144
#define SPLSTATE_PROTECTION_FROM_ELECTRICITY 145
#define SPLSTATE_PROTECTION_FROM_NORMAL_MISSILES 146
#define SPLSTATE_PROTECTION_FROM_PETRIFICATION 147
#define SPLSTATE_RAY_OF_ENFEEBLEMENT 148
#define SPLSTATE_SEVEN_EYES 149
#define SPLSTATE_SOUL_EATER 150
#define SPLSTATE_SPIRIT_ARMOR 151
#define SPLSTATE_STRENGTH 152
#define SPLSTATE_SUFFOCATE 153
#define SPLSTATE_TROLLISH_FORTITUDE 154
#define SPLSTATE_VIPERGOUT 155
#define SPLSTATE_VITRIOLIC_SPHERE 156
#define SPLSTATE_VOCALIZE 157
#define SPLSTATE_ANIMAL_AFFINITY 158
#define SPLSTATE_BARBARIAN_RAGE 159
#define SPLSTATE_GREATER_BARBARIAN_RAGE 160
#define SPLSTATE_KAI_161 161
#define SPLSTATE_SHAPESHIFTS_WEREWOLF 162
#define SPLSTATE_STUNNING_BLOW_163 163
#define SPLSTATE_CANNOT_CAST 164
#define SPLSTATE_CANNOT_FIGHT 165
#define SPLSTATE_DRUID_SHAPESHIFT_ARCTIC_BOAR 166
#define SPLSTATE_DRUID_SHAPESHIFT_BORING_BEETLE 167
#define SPLSTATE_DRUID_SHAPESHIFT_POLAR_BEAR 168
#define SPLSTATE_DRUID_SHAPESHIFT_DIRE_BEAR 169
#define SPLSTATE_DRUID_SHAPESHIFT_BLACK_PANTHER 170
#define SPLSTATE_DRUID_SHAPESHIFT_DIRE_PANTHER 171
#define SPLSTATE_DRUID_SHAPESHIFT_EARTH_ELEMENTAL 172
#define SPLSTATE_DRUID_SHAPESHIFT_AIR_ELEMENTAL 173
#define SPLSTATE_DRUID_SHAPESHIFT_FIRE_ELEMENTAL 174
#define SPLSTATE_DRUID_SHAPESHIFT_WATER_ELEMENTAL 175
#define SPLSTATE_DRUID_SHAPESHIFT_SHAMBLING_MOUND 176
#define SPLSTATE_DRUID_SHAPESHIFT_WINTER_WOLF 177

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
    /* 00EC */ std::bitset<256> m_spellStates;
    /* 010C */ int field_10C;
    /* 0110 */ SHORT m_nDamageModFire;
    /* 0112 */ SHORT m_nDamageModCold;
    /* 0114 */ SHORT m_nDamageModElectricity;
    /* 0116 */ SHORT m_nDamageModAcid;
    /* 0118 */ SHORT m_nDamageModMagic;
    /* 011A */ SHORT m_nDamageModPoison;
    /* 011C */ SHORT m_nDamageModSlashing;
    /* 011E */ SHORT m_nDamageModPiercing;
    /* 0120 */ SHORT m_nDamageModCrushing;
    /* 0122 */ SHORT m_nDamageModMissile;
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
    /* 01A4 */ CImmunitiesEffect m_cImmunitiesEffect;
    /* 01C0 */ CPtrList field_1C0;
    /* 01DC */ CImmunitiesSpellLevel m_cImmunitiesSpellLevel;
    /* 0204 */ CPtrList field_204;
    /* 0220 */ CSelectiveBonusList m_cToHitBonusList;
    /* 023C */ CSelectiveBonusList m_cDamageBonusList;
    /* 0258 */ CImmunitiesItemEquipList m_cImmunitiesItemEquip;
    /* 0274 */ CImmunitiesItemTypeEquipList m_cImmunitiesItemTypeEquip;
    /* 0290 */ CImmunitiesItemEquipList field_290;
    /* 02AC */ CImmunitiesItemTypeEquipList field_2AC;
    /* 02C8 */ CPtrList field_2C8;
    /* 02E4 */ CImmunitiesEffect m_cBounceEffect;
    /* 03C8 */ CPtrList field_3C8;
    /* 03E4 */ CPtrList field_3E4;
    /* 0400 */ CPtrList field_400;
    /* 041C */ CPtrList field_41C;
    /* 0438 */ CImmunitiesItemEquipList m_cImmunitiesItemUse;
    /* 0454 */ CImmunitiesItemTypeEquipList m_cImmunitiesItemTypeUse;
    /* 04AC */ CPtrList field_4AC;
    /* 0480 */ std::set<int> m_naturalImmunities;
    /* 04C8 */ CPtrList field_4C8;
    /* 04E4 */ CPtrList field_4E4;
    /* 0500 */ CPtrList field_500;
    /* 051C */ CPtrList field_51C;
    /* 0538 */ CPtrList field_538;
    /* 0554 */ CPtrList field_554;
    /* 0570 */ CPtrList field_570;
    /* 0590 */ CColorEffects m_appliedColorEffects;
    /* 0DA8 */ int field_DA8;
    /* 0DAC */ BOOL m_disabledButtons[40];
    /* 0E4C */ BOOL m_disabledSpellTypes[3];
};

#endif /* CDERIVEDSTATS_H_ */

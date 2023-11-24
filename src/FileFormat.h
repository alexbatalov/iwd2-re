#ifndef FILEFORMAT_H_
#define FILEFORMAT_H_

#include "BalDataTypes.h"

#define MAX_HATED_RACES 8

#define CSPELLLIST_MAX_LEVELS 9
#define CSPELLLIST_NUM_CLASSES 7

#define CGAMESAVE_NUM_QUICK_FORMATIONS 5

#define CGAMESAVECHARACTER_NUM_QUICK_ITEMS21 3

#define CGAMESAVECHARACTER_NUM_QUICK_WEAPONS22 8
#define CGAMESAVECHARACTER_NUM_QUICK_ITEMS22 3
#define CGAMESAVECHARACTER_NUM_QUICK_SPELLS22 9
#define CGAMESAVECHARACTER_NUM_QUICK_ABILITIES22 9
#define CGAMESAVECHARACTER_NUM_QUICK_SONGS22 9
#define CGAMESAVECHARACTER_NUM_CUSTOM_BUTTONS22 9

#define CGAMESAVECHARACTER_NUM_STATS_SPELLS 4
#define CGAMESAVECHARACTER_NUM_STATS_WEAPONS 4

#define CCREATUREFILEEQUIPMENT21_WEAPON_NUM 8
#define CCREATUREFILEEQUIPMENT21_WEAPON_NUM_SETS 4

class CSavedGameHeader {
public:
    CSavedGameHeader()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ DWORD m_worldTime;
    /* 0004 */ SHORT m_curFormation;
    /* 0006 */ SHORT m_quickFormations[5];
    /* 0010 */ DWORD m_nPartyGold;
    /* 0014 */ WORD m_nPCAreaViewed;
    /* 0016 */ WORD m_wWeatherFlags;
    /* 0018 */ DWORD m_partyCreatureTableOffset;
    /* 001C */ DWORD m_partyCreatureTableCount;
    /* 0020 */ DWORD m_partyInventoryTableOffset;
    /* 0024 */ DWORD m_partyInventoryTableCount;
    /* 0028 */ DWORD m_globalCreatureTableOffset;
    /* 002C */ DWORD m_globalCreatureTableCount;
    /* 0030 */ DWORD m_globalVariablesOffset;
    /* 0034 */ DWORD m_globalVariablesCount;
    /* 0038 */ RESREF m_currentWorldArea;
    /* 0040 */ DWORD m_currentLink;
    /* 0044 */ DWORD m_journalEntriesCount;
    /* 0048 */ DWORD m_journalEntriesOffset;
    /* 004C */ LONG m_reputation;
    /* 0050 */ RESREF m_masterArea;
    /* 0058 */ DWORD m_dwFlags;
    /* 005C */ DWORD m_versionNumber;
    /* 0060 */ DWORD m_familiarsOffset;
    /* 0064 */ DWORD m_storedLocationsOffset;
    /* 0068 */ DWORD m_storedLocationsCount;
    /* 006C */ DWORD m_gameTime;
    /* 0070 */ DWORD m_storedLocationsOffsetPocketPlane;
    /* 0074 */ DWORD m_storedLocationsCountPocketPlane;
    /* 0098 */ unsigned char field_78[52];
};

class CSavedGameJournalEntry {
public:
    CSavedGameJournalEntry()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ STRREF m_strEntry;
    /* 0004 */ DWORD m_time;
    /* 0008 */ BYTE m_chapter;
    /* 0009 */ BYTE m_read;
    /* 000A */ BYTE m_type;
    /* 000B */ BYTE m_character;
};

#pragma pack(push)
#pragma pack(2)

class CSavedGamePartyCreature {
public:
    CSavedGamePartyCreature()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ WORD m_wFlags;
    /* 0002 */ WORD m_portraitId;
    /* 0004 */ DWORD m_creatureOffset;
    /* 0008 */ DWORD m_creatureSize;
    /* 000C */ RESREF m_creatureResRef;
    /* 0014 */ DWORD m_creatureFacing;
    /* 0018 */ RESREF m_areaName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ WORD m_posViewX;
    /* 0026 */ WORD m_posViewY;
    /* 0028 */ WORD m_nModalState;
    /* 002A */ SHORT m_nHappiness;
    /* 002C */ LONG m_nNumberOfTimesInteractedWith[24];
    /* 008C */ SHORT m_quickWeaponsItemNum[8];
    /* 009C */ SHORT m_quickWeaponsAbilityNum[8];
    /* 00AC */ RESREF m_quickSpellsSpellId[9];
    /* 00F4 */ BYTE m_quickSpellsClass[9];
    /* 00FE */ SHORT m_quickItemsItemNum[3];
    /* 0104 */ SHORT m_quickItemsAbilityNum[3];
    /* 010A */ RESREF m_quickInnatesSpellId[9];
    /* 0152 */ RESREF m_quickSongsSpellId[9];
    /* 019A */ int field_19A[9];
    /* 01BE */ SCRIPTNAME m_name;
    /* 01DE */ LONG m_nNumberOfTimesTalkedTo;
    /* 01E2 */ STRREF m_strStrongestKillName;
    /* 01E6 */ DWORD m_nStrongestKillXPValue;
    /* 01EA */ ULONG m_nPreviousTimeWithParty;
    /* 01EE */ ULONG m_nJoinPartyTime;
    /* 01F2 */ BOOL m_bWithParty;
    /* 01F6 */ DWORD m_nChapterKillsXPValue;
    /* 01FA */ DWORD m_nChapterKillsNumber;
    /* 01FE */ DWORD m_nGameKillsXPValue;
    /* 0202 */ DWORD m_nGameKillsNumber;
    /* 0206 */ RESREF m_lSpellStatsName[4];
    /* 0226 */ SHORT m_lSpellStatsCount[4];
    /* 022E */ RESREF m_lWeaponStatsName[4];
    /* 024E */ SHORT m_lWeaponStatsCount[4];
    /* 0256 */ RESREF m_secondarySounds;
    /* 025E */ unsigned char field_25E[32];
    /* 027E */ BYTE m_nLastSpellbookClassIndex;
    /* 027F */ BYTE m_nLastSpellbookSpellLevel;
    /* 0280 */ BYTE field_280[9];
    /* 0289 */ BYTE m_nWeaponSet;
    /* 028A */ int field_28A[5];
    /* 029E */ unsigned char field_29E[9];
    /* 02A7 */ BYTE field_2A7[8];
    /* 02AF */ BYTE m_nLastSong;
    /* 02B0 */ unsigned char field_2B0[144];
};

#pragma pack(pop)

class CAreaFileCreature {
public:
    CAreaFileCreature()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ WORD m_startingPosX;
    /* 0026 */ WORD m_startingPosY;
    /* 0028 */ DWORD m_dwFlags;
    /* 002C */ WORD m_type;
    /* 002E */ char m_cFirstResSlot;
    /* 002F */ BYTE structureAlignment1[1];
    /* 0030 */ DWORD m_animationType;
    /* 0034 */ WORD m_facing;
    /* 0036 */ BYTE structureAlignment2[2];
    /* 0038 */ DWORD m_expirationTime;
    /* 003C */ WORD m_huntingRange;
    /* 003E */ WORD m_followRange;
    /* 0040 */ DWORD m_timeOfDayVisible;
    /* 0044 */ DWORD m_numberTimesTalkedTo;
    /* 0048 */ RESREF m_dialogOverride;
    /* 0050 */ RESREF m_overrideScriptOverride;
    /* 0058 */ RESREF m_special3ScriptOverride;
    /* 0060 */ RESREF m_special2ScriptOverride;
    /* 0068 */ RESREF m_combatScriptOverride;
    /* 0070 */ RESREF m_movementScriptOverride;
    /* 0078 */ RESREF m_teamScriptOverride;
    /* 0080 */ RESREF m_creatureData;
    /* 0088 */ DWORD m_creatureOffset;
    /* 008C */ DWORD m_creatureSize;
    /* 0090 */ RESREF m_special1ScriptOverride;
    /* 0098 */ DWORD m_notUsed[30];
};

class CAreaFileRandomMonsterSpawningPoint {
public:
    CAreaFileRandomMonsterSpawningPoint()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ RESREF m_randomCreature[10];
    /* 0074 */ WORD m_randomCreatureNum;
    /* 0076 */ WORD m_difficulty;
    /* 0078 */ WORD m_spawningRate;
    /* 007A */ WORD m_wFlags;
    /* 007C */ DWORD m_lifeSpan;
    /* 0080 */ WORD m_huntingRange;
    /* 0082 */ WORD m_followRange;
    /* 0084 */ WORD m_maxTypeNum;
    /* 0086 */ WORD m_activated;
    /* 0088 */ DWORD m_timeOfDayVisible;
    /* 008C */ WORD m_probDay;
    /* 008E */ WORD m_probNight;
    /* 0090 */ DWORD m_frequency;
    /* 0094 */ DWORD m_countdown;
    /* 0098 */ BYTE m_weights[10];
    /* 00A2 */ WORD m_notUsed[19];
};

class CAreaFileCharacterEntryPoint {
public:
    CAreaFileCharacterEntryPoint()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_entryName;
    /* 0020 */ WORD m_startX;
    /* 0022 */ WORD m_startY;
    /* 0024 */ DWORD m_facing;
    /* 0028 */ DWORD m_notUsed[16];
};

class CAreaFileContainer {
public:
    CAreaFileContainer()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ WORD m_containerType;
    /* 0026 */ WORD m_lockDifficulty;
    /* 0028 */ DWORD m_dwFlags;
    /* 002C */ WORD m_trapDetectionDifficulty;
    /* 002E */ WORD m_trapRemovalDifficulty;
    /* 0030 */ WORD m_trapActivated;
    /* 0032 */ WORD m_trapDetected;
    /* 0034 */ WORD m_posXTrapOrigin;
    /* 0036 */ WORD m_posYTrapOrigin;
    /* 0038 */ WORD m_boundingRectLeft;
    /* 003A */ WORD m_boundingRectTop;
    /* 003C */ WORD m_boundingRectRight;
    /* 003E */ WORD m_boundingRectBottom;
    /* 0040 */ DWORD m_startingItem;
    /* 0044 */ DWORD m_itemCount;
    /* 0048 */ RESREF m_script;
    /* 0050 */ DWORD m_pickPointStart;
    /* 0054 */ WORD m_pickPointCount;
    /* 0056 */ WORD m_triggerRange;
    /* 0058 */ SCRIPTNAME m_ownedBy;
    /* 0078 */ RESREF m_keyType;
    /* 0080 */ DWORD m_breakDifficulty;
    /* 0084 */ STRREF m_strNotPickable;
    /* 0088 */ DWORD m_notUsed[14];
};

class CAreaFileSoundObject {
public:
    CAreaFileSoundObject()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ WORD m_range;
    /* 0026 */ BYTE structureAlignment1[2];
    /* 0028 */ DWORD m_pitchVariance;
    /* 002C */ WORD m_volumeVariance;
    /* 002E */ WORD m_volume;
    /* 0030 */ RESREF m_soundObject[10];
    /* 0080 */ WORD m_soundObjectNum;
    /* 0082 */ BYTE structureAlignment2[2];
    /* 0084 */ DWORD m_period;
    /* 0088 */ DWORD m_periodVariance;
    /* 008C */ DWORD m_timeOfDayActive;
    /* 0090 */ DWORD m_dwFlags;
    /* 0094 */ DWORD m_notUsed[16];
};

class CAreaFileTriggerObject {
public:
    CAreaFileTriggerObject()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_triggerType;
    /* 0022 */ WORD m_boundingRectLeft;
    /* 0024 */ WORD m_boundingRectTop;
    /* 0026 */ WORD m_boundingRectRight;
    /* 0028 */ WORD m_boundingRectBottom;
    /* 002A */ WORD m_pickPointCount;
    /* 002C */ DWORD m_pickPointStart;
    /* 0030 */ DWORD m_triggerValue;
    /* 0034 */ DWORD m_cursorType;
    /* 0038 */ RESREF m_newArea;
    /* 0040 */ SCRIPTNAME m_newEntryPoint;
    /* 0060 */ DWORD m_dwFlags;
    /* 0064 */ STRREF m_description;
    /* 0068 */ WORD m_trapDetectionDifficulty;
    /* 006A */ WORD m_trapDisarmingDifficulty;
    /* 006C */ WORD m_trapActivated;
    /* 006E */ WORD m_trapDetected;
    /* 0070 */ WORD m_posXTrapOrigin;
    /* 0072 */ WORD m_posYTrapOrigin;
    /* 0074 */ RESREF m_keyType;
    /* 007C */ RESREF m_script;
    /* 0084 */ WORD m_transitionWalkToX;
    /* 0086 */ WORD m_transitionWalkToY;
    /* 0088 */ LONG field_88;
    /* 008C */ LONG field_8C;
    /* 0090 */ DWORD m_notUsed[13];
};

class CAreaFileDoorObject {
public:
    CAreaFileDoorObject()
    {
        memset(this, 0, sizeof(*this));
    }

    SCRIPTNAME m_scriptName;
    RESREF m_doorID;
    DWORD m_dwFlags;
    DWORD m_openSelectionPointStart;
    WORD m_openSelectionPointCount;
    WORD m_closedSelectionPointCount;
    DWORD m_closedSelectionPointStart;
    WORD m_openBoundingRectLeft;
    WORD m_openBoundingRectTop;
    WORD m_openBoundingRectRight;
    WORD m_openBoundingRectBottom;
    WORD m_closedBoundingRectLeft;
    WORD m_closedBoundingRectTop;
    WORD m_closedBoundingRectRight;
    WORD m_closedBoundingRectBottom;
    DWORD m_openSearchSquaresStart;
    WORD m_openSearchSquaresCount;
    WORD m_closedSearchSquaresCount;
    DWORD m_closedSearchSquaresStart;
    SHORT m_hitPoints;
    SHORT m_armourClass;
    RESREF m_openSound;
    RESREF m_closeSound;
    DWORD m_cursorType;
    WORD m_trapDetectionDifficulty;
    WORD m_trapDisarmingDifficulty;
    WORD m_trapActivated;
    WORD m_trapDetected;
    WORD m_posXTrapOrigin;
    WORD m_posYTrapOrigin;
    RESREF m_keyType;
    RESREF m_script;
    DWORD m_detectionDifficulty;
    DWORD m_lockDifficulty;
    WORD m_posXWalkTo1;
    WORD m_posYWalkTo1;
    WORD m_posXWalkTo2;
    WORD m_posYWalkTo2;
    STRREF m_strNotPickable;
    SCRIPTNAME m_triggerName;
    DWORD m_notUsed[3];
};

class CAreaFileTiledObject {
public:
    CAreaFileTiledObject()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ RESREF m_tileID;
    /* 0028 */ DWORD m_dwFlags;
    /* 002C */ DWORD m_primarySearchSquaresStart;
    /* 0030 */ WORD m_primarySearchSquaresCount;
    /* 0032 */ WORD m_secondarySearchSquaresCount;
    /* 0034 */ DWORD m_secondarySearchSquaresStart;
    /* 0038 */ DWORD m_notUsed[12];
};

class CAreaFileStaticObject {
public:
    CAreaFileStaticObject()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ WORD m_posX;
    /* 0022 */ WORD m_posY;
    /* 0024 */ DWORD m_timeOfDayVisible;
    /* 0028 */ RESREF m_resRef;
    /* 0030 */ DWORD m_nSequence;
    /* 0034 */ DWORD m_dwFlags;
    /* 0038 */ short m_height;
    /* 003A */ WORD m_translucency;
    /* 003C */ WORD m_startFrameRange;
    /* 003E */ BYTE m_probability;
    /* 003F */ BYTE m_period;
    /* 0040 */ RESREF m_paletteResRef;
    /* 0048 */ WORD m_sizeX;
    /* 004A */ WORD m_sizeY;
};

class CAreaPoint {
public:
    WORD m_xPos;
    WORD m_yPos;
};

class CAreaUserNote {
public:
    CAreaUserNote()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ WORD m_startX;
    /* 0002 */ WORD m_startY;
    /* 0004 */ STRREF m_note;
    /* 0008 */ DWORD m_dwflags;
    /* 000C */ DWORD m_id;
    /* 0010 */ DWORD m_notUsed[9];
};

class CCreatureFileHeader {
public:
    CCreatureFileHeader()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ DWORD m_name;
    /* 0004 */ DWORD m_apparentName;
    /* 0008 */ DWORD m_flags;
    /* 000C */ DWORD m_xpValue;
    /* 0010 */ DWORD m_xp;
    /* 0014 */ DWORD m_gold;
    /* 0018 */ DWORD m_generalState;
    /* 001C */ SHORT m_hitPoints;
    /* 001E */ WORD m_maxHitPointsBase;
    /* 0020 */ short m_animationType;
    /* 0022 */ short field_22;
    /* 0024 */ BYTE m_colors[7];
    /* 002B */ BYTE m_effectVersion;
    /* 002C */ RESREF m_portraitSmall;
    /* 0034 */ RESREF m_portraitLarge;
    /* 003C */ BYTE m_reputation;
    /* 003E */ short field_3E;
    /* 0040 */ SHORT m_armorClassCrushingAdjustment;
    /* 0042 */ SHORT m_armorClassMissileAdjustment;
    /* 0044 */ SHORT m_armorClassPiercingAdjustment;
    /* 0046 */ SHORT m_armorClassSlashingAdjustment;
    /* 0048 */ BYTE m_attackBase;
    /* 0049 */ BYTE m_numberOfAttacksBase;
    /* 004A */ BYTE m_saveVSFortitudeBase;
    /* 004B */ BYTE m_saveVSReflexBase;
    /* 004C */ BYTE m_saveVSWillBase;
    /* 004D */ signed char m_resistFireBase;
    /* 004E */ signed char m_resistColdBase;
    /* 004F */ signed char m_resistElectricityBase;
    /* 0050 */ signed char m_resistAcidBase;
    /* 0051 */ signed char m_resistMagicBase;
    /* 0052 */ signed char m_resistMagicFireBase;
    /* 0053 */ signed char m_resistMagicColdBase;
    /* 0054 */ signed char m_resistSlashingBase;
    /* 0055 */ signed char m_resistCrushingBase;
    /* 0056 */ signed char m_resistPiercingBase;
    /* 0057 */ signed char m_resistMissileBase;
    /* 0058 */ signed char m_resistMagicDamageBase;
    /* 0059 */ unsigned char field_59;
    /* 005A */ unsigned char field_5A;
    /* 005B */ unsigned char field_5B;
    /* 005C */ unsigned char field_5C;
    /* 005D */ BYTE m_fatigue;
    /* 005E */ BYTE m_intoxication;
    /* 005F */ signed char m_luckBase;
    /* 0060 */ unsigned char field_60[34];
    /* 0082 */ BYTE m_characterLevel;
    /* 0083 */ union {
        struct {
            /* 0083 */ BYTE m_barbarianLevel;
            /* 0084 */ BYTE m_bardLevel;
            /* 0085 */ BYTE m_clericLevel;
            /* 0086 */ BYTE m_druidLevel;
            /* 0087 */ BYTE m_fighterLevel;
            /* 0088 */ BYTE m_monkLevel;
            /* 0089 */ BYTE m_paladinLevel;
            /* 008A */ BYTE m_rangerLevel;
            /* 008B */ BYTE m_rogueLevel;
            /* 008C */ BYTE m_sorcererLevel;
            /* 008D */ BYTE m_wizardLevel;
        };
        BYTE m_classLevels[11];
    };
    /* 008E */ unsigned char field_8E[22];
    /* 00A4 */ STRREF m_speech[63];
    /* 01A0 */ STRREF m_biography;
    /* 01A4 */ RESREF m_scriptTeam;
    /* 01AC */ RESREF m_scriptSpecial1;
    /* 01B4 */ int field_1B4;
    /* 01B8 */ DWORD m_feats[3];
    /* 01C4 */ unsigned char field_1C4[12];
    /* 01D0 */ BYTE m_featBow;
    /* 01D1 */ BYTE m_featCrossbow;
    /* 01D2 */ BYTE m_featMissile;
    /* 01D3 */ BYTE m_featAxe;
    /* 01D4 */ BYTE m_featMace;
    /* 01D5 */ BYTE m_featFlail;
    /* 01D6 */ BYTE m_featPolearm;
    /* 01D7 */ BYTE m_featHammer;
    /* 01D8 */ BYTE m_featQuarterStaff;
    /* 01D9 */ BYTE m_featGreatSword;
    /* 01DA */ BYTE m_featLargeSword;
    /* 01DB */ BYTE m_featSmallBlade;
    /* 01DC */ BYTE m_featToughness;
    /* 01DD */ BYTE m_featArmoredArcana;
    /* 01DE */ BYTE m_featCleave;
    /* 01DF */ BYTE m_featArmorProficiency;
    /* 01E0 */ BYTE m_featFocusEnchantment;
    /* 01E1 */ BYTE m_featFocusEvocation;
    /* 01E2 */ BYTE m_featFocusNecromancy;
    /* 01E3 */ BYTE m_featFocusTransmutation;
    /* 01E4 */ BYTE m_featSpellPenetration;
    /* 01E5 */ BYTE m_featExtraRage;
    /* 01E6 */ BYTE m_featExtraShapeshifting;
    /* 01E7 */ BYTE m_featExtraSmiting;
    /* 01E8 */ BYTE m_featExtraTurning;
    /* 01E9 */ BYTE m_featBastardSword;
    /* 01EA */ unsigned char field_1EA[38];
    /* 0210 */ BYTE m_skills[64];
    /* 0250 */ unsigned char field_250;
    /* 0251 */ unsigned char field_251;
    /* 0252 */ unsigned char field_252;
    /* 0253 */ BYTE m_favoredEnemies[MAX_HATED_RACES];
    /* 025B */ BYTE m_subrace;
    /* 025C */ unsigned char field_25C;
    /* 025D */ BYTE m_sex;
    /* 025E */ BYTE m_STRBase;
    /* 025F */ BYTE m_DEXBase;
    /* 0260 */ BYTE m_CONBase;
    /* 0261 */ BYTE m_INTBase;
    /* 0262 */ BYTE m_WISBase;
    /* 0263 */ BYTE m_CHRBase;
    /* 0264 */ BYTE m_morale;
    /* 0265 */ BYTE m_moraleBreak;
    /* 0266 */ WORD m_moraleRecoveryTime;
    /* 0268 */ DWORD m_specialization;
    /* 026C */ RESREF m_scriptOverRide;
    /* 0274 */ RESREF m_scriptSpecial2;
    /* 027C */ RESREF m_scriptCombat;
    /* 0284 */ RESREF m_scriptSpecial3;
    /* 028C */ RESREF m_scriptMovement;
    /* 02FA */ BYTE m_fadeSpeed;
    /* 02FB */ unsigned char field_2FB;
    /* 02FC */ unsigned char field_2FC;
};

class CCreatureFileItem {
public:
    CCreatureFileItem()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ RESREF m_itemId;
    /* 0008 */ WORD m_wear;
    /* 000A */ WORD m_usageCount[3];
    /* 0010 */ DWORD m_dynamicFlags;
};

class CCreatureFileEquipment {
public:
    CCreatureFileEquipment()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ WORD m_helmetItem;
    /* 0002 */ WORD m_armorItem;
    /* 0004 */ WORD m_shieldItem;
    /* 0006 */ WORD m_gauntletsItem;
    /* 0008 */ WORD m_ringLeftItem;
    /* 000A */ WORD m_ringRightItem;
    /* 000C */ WORD m_amuletItem;
    /* 000E */ WORD m_beltItem;
    /* 0010 */ WORD m_bootsItem;
    /* 0012 */ WORD m_weaponItem[8];
    /* 0022 */ WORD m_ammoItem[4];
    /* 002A */ WORD m_cloakItem;
    /* 002C */ WORD m_miscItem[28];
    /* 0064 */ WORD m_selectedWeapon;
    /* 0066 */ WORD m_selectedWeaponAbility;
};

class CWorldMapHeader {
public:
    DWORD m_nMapCount;
    DWORD m_nMapOffset;
};

class CWorldMapData {
public:
    CWorldMapData()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_resMosaic;
    DWORD m_nWidth;
    DWORD m_nHeight;
    DWORD m_nMapID;
    STRREF m_strTitle;
    DWORD m_nStartCenteredOnX;
    DWORD m_nStartCenteredOnY;
    DWORD m_nAreas;
    DWORD m_nAreasOffset;
    DWORD m_nOffsetToLinks;
    DWORD m_nLinks;
    RESREF m_resAreaIcons;
    DWORD m_dwFlags;
    DWORD nUnused[31];
};

class CWorldMapArea {
public:
    CWorldMapArea()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_resCurrentArea;
    RESREF m_resOriginalArea;
    SCRIPTNAME m_strName;
    DWORD m_dwFlags;
    DWORD m_sequence;
    DWORD m_mapLocationX;
    DWORD m_mapLocationY;
    STRREF m_strLabel;
    STRREF m_strAreaName;
    RESREF m_resAreaLoadMosaic;
    DWORD m_nNorthEdgeStartingLink;
    DWORD m_nNorthEdgeCount;
    DWORD m_nWestEdgeStartingLink;
    DWORD m_nWestEdgeCount;
    DWORD m_nSouthEdgeStartingLink;
    DWORD m_nSouthEdgeCount;
    DWORD m_nEastEdgeStartingLink;
    DWORD m_nEastEdgeCount;
    DWORD nUnused[32];
};

class CWorldMapLinks {
public:
    CWorldMapLinks()
    {
        memset(this, 0, sizeof(*this));
    }

    DWORD m_nArea;
    SCRIPTNAME m_entryPoint;
    DWORD m_nDistanceScale;
    DWORD m_dwLinkFlags;
    RESREF m_resRandomEncounterArea0;
    RESREF m_resRandomEncounterArea1;
    RESREF m_resRandomEncounterArea2;
    RESREF m_resRandomEncounterArea3;
    RESREF m_resRandomEncounterArea4;
    DWORD m_nEncounterProbability;
    DWORD nUnused[32];
};

class CAreaVariable {
public:
    CAreaVariable()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_name;
    /* 0020 */ WORD m_type;
    /* 0022 */ WORD m_resRefType;
    /* 0024 */ DWORD m_dwValue;
    /* 0028 */ LONG m_intValue;
    /* 002C */ double m_floatValue;
    /* 0034 */ SCRIPTNAME m_stringValue;
};

// Seen in `CScreenStore::OpenBag`.
#define CSTOREFILEHEADER_STORETYPE_BAG 4

class CStoreFileHeader {
public:
    CStoreFileHeader()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ DWORD m_nStoreType;
    /* 0004 */ STRREF m_strName;
    /* 0008 */ DWORD m_nStoreFlags;
    /* 000C */ DWORD m_nBuyMarkUp;
    /* 0010 */ DWORD m_nSellMarkDown;
    /* 0014 */ DWORD m_nAdditionalMarkDown;
    /* 0018 */ WORD m_nStealDifficulty;
    /* 001A */ WORD m_nMaxItems;
    /* 001C */ RESREF m_script;
    /* 0024 */ DWORD m_nbuyTypesOffset;
    /* 0028 */ DWORD m_nBuyTypesCount;
    /* 002C */ DWORD m_nInventoryOffset;
    /* 0030 */ DWORD m_nInventoryCount;
    /* 0034 */ DWORD m_nLore;
    /* 0038 */ DWORD m_nIdentifyCost;
    /* 003C */ RESREF m_resRumor;
    /* 0044 */ DWORD m_drinkOffset;
    /* 0048 */ DWORD m_drinkCount;
    /* 004C */ RESREF m_resDonation;
    /* 0054 */ DWORD m_nInnFlags;
    /* 0058 */ DWORD m_nRoomCostPeasant;
    /* 005C */ DWORD m_nRoomCostMerchant;
    /* 0060 */ DWORD m_nRoomCostNoble;
    /* 0064 */ DWORD m_nRoomCostRoyal;
    /* 0068 */ DWORD m_spellOffset;
    /* 006C */ DWORD m_spellCount;
    /* 0070 */ DWORD m_rouletMaxBet;
    /* 0074 */ DWORD m_crapsMaxBet;
    /* 0078 */ DWORD m_wheelMaxBet;
    /* 007C */ DWORD m_rouletWinChance;
    /* 0080 */ DWORD m_crapsWinChance;
    /* 0084 */ DWORD m_wheelWinChance;
    /* 0088 */ DWORD m_rouletWinAmount;
    /* 008C */ DWORD m_crapsWinAmount;
    /* 0090 */ DWORD m_wheelWinAmount;
    /* 0094 */ int field_94[21];
};

class CStoreFileSpell {
public:
    CStoreFileSpell()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_spell;
    DWORD m_cost;
};

class CStoreFileItem {
public:
    CStoreFileItem()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_itemId;
    WORD m_wear;
    WORD m_usageCount[3];
    DWORD m_dynamicFlags;
    DWORD m_nInStock;
    DWORD m_nStoreFlags;
};

class CStoreFileDrinks {
public:
    CStoreFileDrinks()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_icon;
    STRREF m_strName;
    DWORD m_nCost;
    DWORD m_nRumorChance;
};

#endif /* FILEFORMAT_H_ */

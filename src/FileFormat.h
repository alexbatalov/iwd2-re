#ifndef FILEFORMAT_H_
#define FILEFORMAT_H_

#include "BalDataTypes.h"

#define CSPELLLIST_MAX_LEVELS 9
#define CSPELLLIST_NUM_CLASSES 7

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
    /* 01A4 */ RESREF field_1A4;
    /* 01AC */ RESREF field_1AC;
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
    /* 0253 */ BYTE m_favoredEnemies[8];
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
    /* 026C */ RESREF field_26C;
    /* 0274 */ RESREF field_274;
    /* 027C */ RESREF field_27C;
    /* 0284 */ RESREF field_284;
    /* 028C */ RESREF field_28C;
    /* 02FA */ BYTE m_fadeSpeed;
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

    SCRIPTNAME m_name;
    WORD m_type;
    WORD m_resRefType;
    DWORD m_dwValue;
    LONG m_intValue;
    double m_floatValue;
    SCRIPTNAME m_stringValue;
};

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

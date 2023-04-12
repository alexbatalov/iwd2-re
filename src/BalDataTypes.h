#ifndef BALDATATYPES_H_
#define BALDATATYPES_H_

#include "ChDataTypes.h"

typedef DWORD STRREF;

typedef struct UI_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ DWORD nPanels;
    /* 000C */ DWORD nOffsetToControlTable;
    /* 0010 */ DWORD nOffsetToPanelTable;
} UI_HEADER;

typedef struct UI_ControlTableEntry_st {
    /* 0000 */ DWORD nControlOffset;
    /* 0004 */ DWORD nControlSize;
} UI_CONTROLTABLEENTRY;

typedef struct UI_PanelHeader_st {
    /* 0000 */ DWORD nPanelID;
    /* 0004 */ WORD x;
    /* 0006 */ WORD y;
    /* 0008 */ WORD nWidth;
    /* 000A */ WORD nHeight;
    /* 000C */ WORD nType;
    /* 000E */ WORD nControls;
    /* 0010 */ RESREF refMosaic;
    /* 0018 */ WORD nFirstControl;
    /* 001A */ WORD wFlags;
} UI_PANELHEADER;

typedef struct UI_Control_st {
    /* 0000 */ DWORD nID;
    /* 0004 */ WORD x;
    /* 0006 */ WORD y;
    /* 0008 */ WORD nWidth;
    /* 000A */ WORD nHeight;
    /* 000C */ WORD nType;
} UI_CONTROL;

// TODO: Incomplete.
typedef struct UI_Control_Button_st {
    UI_CONTROL base;
} UI_CONTROL_BUTTON;

typedef struct WED_WedHeader_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ DWORD nLayers;
    /* 000C */ DWORD nTiledObjects;
    /* 0010 */ DWORD nOffsetToLayerHeaders;
    /* 0014 */ DWORD nOffsetToPolyHeader;
    /* 0018 */ DWORD nOffsetToTiledObjects;
    /* 001C */ DWORD nOffsetToObjectTileList;
    /* 0020 */ WORD nVisiblityRange;
    /* 0022 */ WORD nChanceOfRain;
    /* 0024 */ WORD nChanceOfFog;
    /* 0026 */ WORD nChanceOfSnow;
    /* 0028 */ DWORD dwFlags;
} WED_WEDHEADER;

typedef struct WED_LayerHeader_st {
    /* 0000 */ WORD nTilesAcross;
    /* 0002 */ WORD nTilesDown;
    /* 0004 */ RESREF rrTileSet;
    /* 000C */ WORD nNumUniqueTiles;
    /* 000E */ WORD nLayerFlags;
    /* 0010 */ DWORD nOffsetToTileData;
    /* 0014 */ DWORD nOffsetToTileList;
} WED_LAYERHEADER;

typedef struct WED_PolyHeader_st {
    /* 0000 */ DWORD nPolys;
    /* 0004 */ DWORD nOffsetToPolyList;
    /* 0008 */ DWORD nOffsetToPointList;
    /* 000C */ DWORD nOffsetToScreenSectionList;
    /* 0010 */ DWORD nOffsetToScreenPolyList;
} WED_POLYHEADER;

typedef struct WED_ScreenSectionList {
    /* 0000 */ WORD nStartingPoly;
    /* 0002 */ WORD nNumPolys;
} WED_SCREENSECTIONLIST;

typedef struct WED_PolyList_st {
    /* 0000 */ DWORD nStartingPoint;
    /* 0004 */ DWORD nNumPoints;
    /* 0008 */ BYTE nType;
    /* 0009 */ BYTE nHeight;
    /* 000A */ WORD nLeft;
    /* 000C */ WORD nRight;
    /* 000E */ WORD nTop;
    /* 0010 */ WORD nBottom;
} WED_POLYLIST;

typedef struct WED_PolyPoint_st {
    /* 0000 */ WORD x;
    /* 0002 */ WORD y;
} WED_POLYPOINT;

typedef struct WED_TileData_st {
    /* 0000 */ WORD nStartingTile;
    /* 0002 */ WORD nNumTiles;
    /* 0004 */ WORD nSecondary;
    /* 0006 */ BYTE bFlags;
    /* 0007 */ BYTE bAnimSpeed;
    /* 0008 */ WORD wFlags;
} WED_TILEDATA;

typedef struct WED_TiledObject_st {
    /* 0000 */ RESREF resID;
    /* 0008 */ WORD bType;
    /* 000A */ WORD nStartingTile;
    /* 000C */ WORD nNumTiles;
    /* 000E */ WORD nNumPrimaryPolys;
    /* 0010 */ WORD nNumSecondaryPolys;
    /* 0012 */ DWORD nOffsetToPrimaryPolys;
    /* 0016 */ DWORD nOffsetToSecondaryPolys;
} WED_TILEDOBJECT;

// NOTE: This struct is V1.0, probably does not match V2.0 used in IWD2.
typedef struct Item_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ STRREF genericName;
    /* 000C */ STRREF identifiedName;
    /* 0010 */ RESREF usedUpItemID;
    /* 0018 */ DWORD itemFlags;
    /* 001C */ WORD itemType;
    /* 001E */ DWORD notUsableBy;
    /* 0022 */ BYTE animationType[2];
    /* 0024 */ WORD minLevelRequired;
    /* 0026 */ WORD minSTRRequired;
    /* 0028 */ BYTE minSTRBonusRequired;
    /* 0029 */ BYTE notUsableBy2a;
    /* 002A */ BYTE minINTRequired;
    /* 002B */ BYTE notUsableBy2b;
    /* 002C */ BYTE minDEXRequired;
    /* 002D */ BYTE notUsableBy2c;
    /* 002E */ BYTE minWISRequired;
    /* 002F */ BYTE notUsableBy2d;
    /* 0030 */ BYTE minCONRequired;
    /* 0031 */ BYTE proficiencyType;
    /* 0032 */ WORD minCHRRequired;
    /* 0034 */ DWORD baseValue;
    /* 0038 */ WORD maxStackable;
    /* 003A */ RESREF itemIcon;
    /* 0042 */ WORD loreValue;
    /* 0044 */ RESREF groundIcon;
    /* 004C */ DWORD baseWeight;
    /* 0050 */ STRREF genericDescription;
    /* 0054 */ STRREF identifiedDescription;
    /* 0058 */ RESREF descriptionPicture;
    /* 0060 */ DWORD attributes;
    /* 0064 */ DWORD abilityOffset;
    /* 0068 */ WORD abilityCount;
    /* 006A */ DWORD effectsOffset;
    /* 006E */ WORD equipedStartingEffect;
    /* 0070 */ WORD equipedEffectCount;
} ITEM_HEADER;

typedef struct Item_ability_st {
    /* 0000 */ WORD type;
    /* 0002 */ BYTE quickSlotType;
    /* 0003 */ BYTE largeDamageDice;
    /* 0004 */ RESREF quickSlotIcon;
    /* 000C */ BYTE actionType;
    /* 000D */ BYTE actionCount;
    /* 000E */ WORD range;
    /* 0010 */ BYTE launcherType;
    /* 0011 */ BYTE largeDamageDiceCount;
    /* 0012 */ BYTE speedFactor;
    /* 0013 */ BYTE largeDamageDiceBonus;
    /* 0014 */ SHORT thac0Bonus;
    /* 0016 */ BYTE damageDice;
    /* 0017 */ BYTE school;
    /* 0018 */ BYTE damageDiceCount;
    /* 0019 */ BYTE secondaryType;
    /* 001A */ SHORT damageDiceBonus;
    /* 001C */ WORD damageType;
    /* 001E */ WORD effectCount;
    /* 0020 */ WORD startingEffect;
    /* 0022 */ WORD maxUsageCount;
    /* 0024 */ WORD usageFlags;
    /* 0026 */ DWORD abilityFlags;
    /* 002A */ WORD missileType;
    /* 002C */ WORD attackProbability[6];
} ITEM_ABILITY;

typedef struct Item_effect_st {
    /* 0000 */ WORD effectID;
    /* 0002 */ BYTE targetType;
    /* 0003 */ BYTE spellLevel;
    /* 0004 */ int effectAmount;
    /* 0008 */ DWORD dwFlags;
    /* 000C */ WORD durationType;
    /* 000E */ DWORD duration;
    /* 0012 */ BYTE probabilityUpper;
    /* 0013 */ BYTE probabilityLower;
    /* 0014 */ RESREF res;
    /* 001C */ DWORD numDice;
    /* 0020 */ DWORD diceSize;
    /* 0024 */ DWORD savingThrow;
    /* 0028 */ LONG saveMod;
    /* 002C */ DWORD special;
} ITEM_EFFECT;

typedef struct Spell_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ STRREF genericName;
    /* 000C */ STRREF identifiedName;
    /* 0010 */ RESREF usedUpItemID;
    /* 0018 */ DWORD itemFlags;
    /* 001C */ WORD itemType;
    /* 001E */ DWORD notUsableBy;
    /* 0022 */ WORD castingAnimationType;
    /* 0024 */ BYTE minLevelRequired;
    /* 0025 */ BYTE school;
    /* 0026 */ BYTE minSTRRequired;
    /* 0027 */ BYTE secondaryType;
    /* 0028 */ BYTE minSTRBonusRequired;
    /* 0029 */ BYTE notUsableBy2a;
    /* 002A */ BYTE minINTRequired;
    /* 002B */ BYTE notUsableBy2b;
    /* 002C */ BYTE minDEXRequired;
    /* 002D */ BYTE notUsableBy2c;
    /* 002E */ BYTE minWISRequired;
    /* 002F */ BYTE notUsableBy2d;
    /* 0030 */ WORD minCONRequired;
    /* 0032 */ WORD minCHRRequired;
    /* 0034 */ DWORD spellLevel;
    /* 0038 */ WORD maxStackable;
    /* 003A */ RESREF itemIcon;
    /* 0042 */ WORD loreValue;
    /* 0044 */ RESREF groundIcon;
    /* 004C */ DWORD baseWeight;
    /* 0050 */ STRREF genericDescription;
    /* 0054 */ STRREF identifiedDescription;
    /* 0058 */ RESREF descriptionPicture;
    /* 0060 */ DWORD attributes;
    /* 0064 */ DWORD abilityOffset;
    /* 0068 */ WORD abilityCount;
    /* 006A */ DWORD effectsOffset;
    /* 006E */ WORD castingStartingEffect;
    /* 0070 */ WORD castingEffectCount;
    /* 0072 */ BYTE field_72;
    /* 0073 */ BYTE field_73;
} SPELL_HEADER;

typedef struct Spell_ability_st {
    /* 0000 */ WORD type;
    /* 0002 */ WORD quickSlotType;
    /* 0004 */ RESREF quickSlotIcon;
    /* 000C */ BYTE actionType;
    /* 000D */ BYTE actionCount;
    /* 000E */ WORD range;
    /* 0010 */ WORD minCasterLevel;
    /* 0012 */ WORD speedFactor;
    /* 0014 */ WORD timesPerDay;
    /* 0016 */ WORD damageDice;
    /* 0018 */ WORD damageDiceCount;
    /* 001A */ WORD damageDiceBonus;
    /* 001C */ WORD damageType;
    /* 001E */ WORD effectCount;
    /* 0020 */ WORD startingEffect;
    /* 0022 */ WORD maxUsageCount;
    /* 0024 */ WORD usageFlags;
    /* 0026 */ WORD missileType;
} SPELL_ABILITY;

// NOTE: There are no traces of such struct in the code.
typedef struct Creature_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
} CREATURE_HEADER;

// NOTE: There are no traces of such struct in the code.
typedef struct ExportCharacter_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
} EXPORT_CHARACTER_HEADER;

#endif /* BALDATATYPES_H_ */

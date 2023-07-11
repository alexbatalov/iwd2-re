#ifndef FILEFORMAT_H_
#define FILEFORMAT_H_

#include "BalDataTypes.h"

class CCreatureFileHeader {
public:
    /* 0000 */ DWORD m_name;
    /* 0008 */ DWORD m_flags;
    /* 002C */ RESREF m_portraitSmall;
    /* 0034 */ RESREF m_portraitLarge;
    /* 0048 */ BYTE m_attackBase;
    /* 0083 */ BYTE m_barbarianLevel;
    /* 0084 */ BYTE m_bardLevel;
    /* 0085 */ BYTE m_clericLevel;
    /* 0086 */ BYTE m_druidLevel;
    /* 0087 */ BYTE m_fighterLevel;
    /* 0088 */ BYTE m_monkLevel;
    /* 0089 */ BYTE m_paladinLevel;
    /* 008B */ BYTE m_rogueLevel;
    /* 01A0 */ int field_1A0;
    /* 01B8 */ DWORD m_feats[3];
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
    /* 0210 */ BYTE m_skills[16];
    /* 0253 */ BYTE m_favoredEnemies[8];
    /* 025E */ BYTE m_STRBase;
    /* 025F */ BYTE m_DEXBase;
    /* 0260 */ BYTE m_CONBase;
    /* 0261 */ BYTE m_INTBase;
    /* 0262 */ BYTE m_WISBase;
    /* 0263 */ BYTE m_CHRBase;
    /* 0268 */ DWORD m_specialization;
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

#endif /* FILEFORMAT_H_ */

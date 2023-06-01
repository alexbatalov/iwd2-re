#ifndef FILEFORMAT_H_
#define FILEFORMAT_H_

#include "BalDataTypes.h"

class CCreatureFileHeader {
public:
    /* 0000 */ DWORD m_name;
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

#endif /* FILEFORMAT_H_ */

#include "CDerivedStats.h"

#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CUtil.h"
#include "FileFormat.h"

// 0x443B30
CDerivedStats::CDerivedStats()
{
    // TODO: Incomplete.

    BonusInit();

    // TODO: Incomplete.
}

// 0x4440F0
void CDerivedStats::Reload(CGameSprite* pSprite, CCreatureFileHeader* pCreature, int a3, int a4)
{
    int index;

    field_92 = 0;
    m_nLayOnHandsAmount = 0;

    m_generalState = pCreature->m_generalState;
    m_nMaxHitPoints = pCreature->m_maxHitPointsBase;
    field_6 = 0;
    field_8 = 0;
    field_A = 0;
    field_C = pCreature->field_3E;
    field_E = pCreature->field_40;
    field_10 = pCreature->field_42;
    field_12 = pCreature->field_44;
    field_14 = pCreature->field_46;

    // TODO: Incomplete.

    field_16 = 0;
    field_18 = 0;
    field_1A = pCreature->field_49;
    m_nSaveVSFortitude = pCreature->m_saveVSFortitudeBase;
    m_nSaveVSReflex = pCreature->m_saveVSReflexBase;
    m_nSaveVSWill = pCreature->m_saveVSWillBase;
    m_nResistFire = pCreature->m_resistFireBase;
    m_nResistCold = pCreature->m_resistColdBase;
    m_nResistElectricity = pCreature->m_resistElectricityBase;
    m_nResistAcid = pCreature->m_resistAcidBase;
    m_nResistMagic = pCreature->m_resistMagicBase;
    m_nResistMagicFire = pCreature->m_resistMagicFireBase;
    m_nResistMagicCold = pCreature->m_resistMagicColdBase;
    m_nResistSlashing = pCreature->m_resistSlashingBase;
    m_nResistCrushing = pCreature->m_resistCrushingBase;
    m_nResistPiercing = pCreature->m_resistPiercingBase;
    field_36 = pCreature->field_57;
    field_3A = pCreature->field_5D;
    field_3C = pCreature->field_5F;

    memcpy(field_144, pCreature->m_skills, 64);

    field_3E = pCreature->field_25B;

    m_nLevel = pCreature->m_characterLevel;
    m_barbarianLevel = pCreature->m_barbarianLevel;
    m_bardLevel = pCreature->m_bardLevel;
    m_clericLevel = pCreature->m_clericLevel;
    m_druidLevel = pCreature->m_druidLevel;
    m_fighterLevel = pCreature->m_fighterLevel;
    m_monkLevel = pCreature->m_monkLevel;
    m_paladinLevel = pCreature->m_paladinLevel;
    m_rangerLevel = pCreature->m_rangerLevel;
    m_rogueLevel = pCreature->m_rogueLevel;
    m_sorcererLevel = pCreature->m_sorcererLevel;
    m_wizardLevel = pCreature->m_wizardLevel;

    field_52 = pCreature->field_25D;

    m_nSTR = pCreature->m_STRBase;
    m_nINT = pCreature->m_INTBase;
    m_nWIS = pCreature->m_WISBase;
    m_nDEX = pCreature->m_DEXBase;
    m_nCON = pCreature->m_CONBase;
    m_nCHR = pCreature->m_CHRBase;

    field_60 = pCreature->field_C;
    field_64 = pCreature->field_10;
    field_68 = pCreature->field_14;
    m_nMoraleRecoveryTime = pCreature->m_moraleRecoveryTime;
    field_74 = pCreature->field_3C;
    m_nMoraleBreak = pCreature->m_moraleBreak;

    for (index = 0; index < 8; index++) {
        m_favoredEnemies[index] = pCreature->m_favoredEnemies[index];
    }

    m_nSpecialization = pCreature->m_specialization;
    field_A6 = 0;
    field_AA = 0;
    field_86 = 0;
    field_88 = 0;
    field_8A = 0;
    field_8C = 100;
    field_8E = 100;
    field_90 = 0;
    field_96 = 0;
    field_9A = 0;
    field_B2 = 0;
    field_9E = 0;

    for (index = 0; index < 8; index++) {
        field_EC[index] = 0;
    }

    field_10C = 0;
    field_AE = 0;
    field_B4 = 0;
    field_B8 = pCreature->field_58;
    field_BA = 0;
    field_BC = 0;
    field_C0 = 0;
    field_C4 = 0;
    field_C6 = 0;
    field_C8 = 0;
    field_CA = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    field_D8 = 0;
    field_DC = 0;
    field_E0 = 0;
    field_E4 = 0;
    field_E8 = 0;
    field_110 = 0;
    field_112 = 0;
    field_114 = 0;
    field_116 = 0;
    field_118 = 0;
    field_11A = 0;
    field_11C = 0;
    field_11E = 0;
    field_120 = 0;
    field_122 = 0;
    field_124 = 0;
    field_128 = 0;
    field_12C = 0;
    field_130 = 0;
    field_134 = 0;
    field_138 = 0;
    field_13C = 0;
    field_140 = 0;
    field_184 = 0;

    // TODO: Incomplete.

    m_naturalImmunities.clear();

    // TODO: Incomplete.

    memset(field_DAC, 0, sizeof(field_DAC));
    field_E4C = 0;
    field_E50 = 0;
    field_E54 = 0;

    if (pSprite != NULL) {
        CAIObjectType typeAI(pSprite->GetAIType());

        if (typeAI.m_nRace == CAIOBJECTTYPE_R_ELF
            || typeAI.m_nRace == CAIOBJECTTYPE_R_HALF_ELF) {
            m_naturalImmunities.insert(CGAMEEFFECT_SLEEP);
            m_naturalImmunities.insert(CGAMEEFFECT_POWERWORDSLEEP);
        }

        if (pSprite->m_derivedStats.m_paladinLevel != 0) {
            m_naturalImmunities.insert(CGAMEEFFECT_DISEASE);

            if (pSprite->m_derivedStats.m_paladinLevel >= 2) {
                m_naturalImmunities.insert(CGAMEEFFECT_PANIC);
            }
        }

        if (pSprite->m_derivedStats.m_druidLevel >= 9) {
            m_naturalImmunities.insert(CGAMEEFFECT_POISON);
        }

        if (pSprite->m_derivedStats.m_druidLevel >= 15) {
            m_naturalImmunities.insert(CGAMEEFFECT_FATIGUE);
        }

        if (typeAI.m_nRace == CAIOBJECTTYPE_R_DWARF
            && typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_DWARF_GRAY) {
            m_naturalImmunities.insert(CGAMEEFFECT_HOLDCREATURE);
        }

        if (pSprite->m_derivedStats.m_monkLevel >= 5) {
            m_naturalImmunities.insert(CGAMEEFFECT_DISEASE);
        }

        if (pSprite->m_derivedStats.m_monkLevel >= 11) {
            m_naturalImmunities.insert(CGAMEEFFECT_POISON);
        }

        // TODO: Incomplete.
    }
}

// 0x445E40
void CDerivedStats::BonusInit()
{
    int index;

    m_generalState = 0;
    m_nMaxHitPoints = 0;
    field_6 = 0;
    field_8 = 0;
    field_A = 0;
    field_C = 0;
    field_E = 0;
    field_10 = 0;
    field_12 = 0;

    // TODO: Incomplete.

    field_16 = 0;
    field_18 = 0;
    field_1A = 0;
    m_nSaveVSFortitude = 0;
    m_nSaveVSReflex = 0;
    m_nSaveVSWill = 0;
    m_nResistFire = 0;
    m_nResistCold = 0;
    m_nResistElectricity = 0;
    m_nResistAcid = 0;
    m_nResistMagic = 0;
    m_nResistMagicFire = 0;
    m_nResistMagicCold = 0;
    m_nResistSlashing = 0;
    m_nResistCrushing = 0;
    m_nResistPiercing = 0;
    field_36 = 0;

    memset(field_144, 0, 64);

    field_38 = 0;
    field_3A = 0;
    field_3C = 0;
    field_3E = 0;
    m_nLevel = 0;
    field_52 = 0;
    m_nSTR = 0;
    m_nINT = 0;
    m_nWIS = 0;
    m_nDEX = 0;
    m_nCON = 0;
    m_nCHR = 0;
    field_60 = 0;
    field_64 = 0;
    field_68 = 0;
    m_nMoraleRecoveryTime = 0;
    field_74 = 0;
    m_nMoraleBreak = 0;

    for (index = 0; index < 8; index++) {
        m_favoredEnemies[index] = CAIObjectType::R_NO_RACE;
    }

    field_86 = 0;
    field_88 = 0;
    field_8A = 0;
    field_8C = 0;
    field_8E = 0;
    field_90 = 0;
    field_92 = 0;
    m_nLayOnHandsAmount = 0;
    field_96 = 0;
    field_9A = 0;
    field_B2 = 0;
    field_9E = 0;
    m_nSpecialization = 0;
    field_A6 = 0;
    field_AA = 0;

    for (index = 0; index < 8; index++) {
        field_EC[index] = 0;
    }

    field_10C = 0;
    field_AE = 0;
    field_B4 = 0;
    field_B6 = 0;
    field_B8 = 0;
    field_BA = 0;
    field_BC = 0;
    field_C0 = 0;
    field_C4 = 0;
    field_C6 = 0;
    field_C8 = 0;
    field_CA = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    field_D8 = 0;
    field_DC = 0;
    field_E0 = 0;
    field_E4 = 0;
    field_E8 = 0;
    field_110 = 0;
    field_112 = 0;
    field_114 = 0;
    field_116 = 0;
    field_118 = 0;
    field_11A = 0;
    field_11C = 0;
    field_11E = 0;
    field_120 = 0;
    field_122 = 0;
    field_124 = 0;
    field_128 = 0;
    field_12C = 0;
    field_130 = 0;
    field_134 = 0;
    field_138 = 0;
    field_13C = 0;
    field_140 = 0;
    field_184 = 0;

    // TODO: Incomplete.

    field_DA8 = 0;

    m_barbarianLevel = 0;
    m_bardLevel = 0;
    m_clericLevel = 0;
    m_druidLevel = 0;
    m_fighterLevel = 0;
    m_monkLevel = 0;
    m_paladinLevel = 0;
    m_rangerLevel = 0;
    m_rogueLevel = 0;
    m_sorcererLevel = 0;
    m_wizardLevel = 0;
    m_classMask = 0;
}

// 0x4464E0
CDerivedStats& CDerivedStats::operator+=(const CDerivedStats& other)
{
    int index;

    m_nMaxHitPoints += other.m_nMaxHitPoints;
    field_6 += other.field_6;
    field_8 += other.field_8;
    field_A += other.field_A;
    field_C += other.field_C;
    field_E += other.field_E;
    field_10 += other.field_10;
    field_12 += other.field_12;
    field_14 += other.field_14;
    field_16 += other.field_16;
    field_18 += other.field_18;
    field_1A += other.field_1A;
    m_nSaveVSFortitude += other.m_nSaveVSFortitude;
    m_nSaveVSReflex += other.m_nSaveVSReflex;
    m_nSaveVSWill += other.m_nSaveVSWill;
    m_nResistFire += other.m_nResistFire;
    m_nResistCold += other.m_nResistCold;
    m_nResistElectricity += other.m_nResistElectricity;
    m_nResistAcid += other.m_nResistAcid;
    m_nResistMagic += other.m_nResistMagic;
    m_nResistMagicFire += other.m_nResistMagicFire;
    m_nResistMagicCold += other.m_nResistMagicCold;
    m_nResistSlashing += other.m_nResistSlashing;
    m_nResistCrushing += other.m_nResistCrushing;
    m_nResistPiercing += other.m_nResistPiercing;
    field_36 += other.field_36;
    field_B8 += other.field_B8;
    field_38 += other.field_38;
    field_3A += other.field_3A;
    field_3C += other.field_3C;
    m_nLevel += other.m_nLevel;
    m_nSTR += other.m_nSTR;
    m_nINT += other.m_nINT;
    m_nWIS += other.m_nWIS;
    m_nDEX += other.m_nDEX;
    m_nCON += other.m_nCON;
    m_nCHR += other.m_nCHR;
    field_60 += other.field_60;
    field_64 += other.field_64;
    field_68 += other.field_68;
    m_nMoraleBreak += other.m_nMoraleBreak;
    m_nMoraleRecoveryTime += other.m_nMoraleRecoveryTime;
    field_74 += other.field_74;
    m_nMoraleBreak += other.m_nMoraleBreak;
    field_86 += other.field_86;
    field_88 += other.field_88;
    field_8A += other.field_8A;
    field_8C += other.field_8C;
    field_8E += other.field_8E;
    field_90 += other.field_90;
    field_92 += other.field_92;
    m_nLayOnHandsAmount += other.m_nLayOnHandsAmount;
    field_96 |= other.field_96;
    field_9A |= other.field_9A;
    field_B2 += other.field_B2;
    field_9E |= other.field_9E;
    field_A6 += other.field_A6;
    field_AA += other.field_AA;

    for (index = 0; index < 8; index++) {
        field_EC[index] |= other.field_EC[index];
    }

    field_10C |= other.field_10C;
    field_E8 += other.field_E8;
    field_AE |= other.field_AE;
    field_184 |= other.field_184;
    field_110 += other.field_110;
    field_112 += other.field_112;
    field_114 += other.field_114;
    field_116 += other.field_116;
    field_118 += other.field_118;
    field_11A += other.field_11A;
    field_11C += other.field_11C;
    field_11E += other.field_11E;
    field_120 += other.field_120;
    field_122 += other.field_122;
    field_124 += other.field_124;
    field_128 += other.field_128;
    field_12C += other.field_12C;
    field_130 += other.field_130;
    field_134 += other.field_134;
    field_138 += other.field_138;
    field_13C += other.field_13C;
    field_140 += other.field_140;

    for (index = 0; index < 64; index++) {
        field_144[index] += other.field_144[index];
    }

    CheckLimits();

    return *this;
}

// 0x4468F0
void CDerivedStats::CheckLimits()
{
    if ((m_generalState & 0x800) != 0) {
        m_generalState &= ~0xFFFFF03F;
    }

    m_nMaxHitPoints = max(m_nMaxHitPoints, 1);
    field_E = min(max(field_E, -20), 20);
    field_10 = min(max(field_10, -20), 20);
    field_12 = min(max(field_12, -20), 20);
    field_14 = min(max(field_14, -20), 20);
    field_18 = min(max(field_18, -255), 255);
    field_1A = min(max(field_1A, 0), 5);
    m_nSaveVSFortitude = min(max(m_nSaveVSFortitude, -40), 40);
    m_nSaveVSReflex = min(max(m_nSaveVSReflex, -40), 40);
    m_nSaveVSWill = min(max(m_nSaveVSWill, -40), 40);
    field_144[10] = min(max(field_144[10], -128), 127);
    field_144[9] = min(max(field_144[9], -128), 127);
    field_144[6] = min(max(field_144[6], -128), 127);
    field_144[14] = min(max(field_144[14], -128), 127);
    field_144[12] = min(max(field_144[12], -128), 127);
    field_144[11] = min(max(field_144[11], -128), 127);
    field_144[15] = min(max(field_144[15], -128), 127);
    field_38 = min(max(field_38, 0), 100);
    field_3A = min(max(field_3A, 0), 100);
    field_3C = min(max(field_3C, 0), 100);
    m_nLevel = min(m_nLevel, 50);
    m_nSTR = min(max(m_nSTR, 1), 40);
    m_nINT = min(max(m_nINT, 1), 40);
    m_nWIS = min(max(m_nWIS, 1), 40);
    m_nDEX = min(max(m_nDEX, 1), 40);
    m_nCON = min(max(m_nCON, 1), 40);
    m_nCHR = min(max(m_nCHR, 1), 40);
    field_60 = min(max(field_60, -1), 0);
    field_64 = min(max(field_64, -1), 0);
    field_68 = min(max(field_68, -1), 0);
    m_nMoraleRecoveryTime = min(max(m_nMoraleRecoveryTime, -1), 0);
    field_74 = min(max(field_74, 10), 200);
    m_nMoraleBreak = min(max(m_nMoraleBreak, 10), 200);
    field_86 = min(max(field_86, -128), 127);
    field_88 = min(max(field_88, 0), 100);
    field_8A = min(max(field_8A, 0), 100);
    field_8C = min(max(field_8C, 0), 255);
    field_8E = min(max(field_8E, 0), 255);
    field_90 = max(field_90, 0);
    field_92 = max(field_92, 0);
    m_nLayOnHandsAmount = max(m_nLayOnHandsAmount, 0);
    field_B2 = min(field_B2, 255);
}

// 0x446DD0
LONG CDerivedStats::GetAtOffset(SHORT offset)
{
    switch (offset) {
    case 1:
        return m_nMaxHitPoints;
    case 2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1323
        UTIL_ASSERT_MSG(FALSE, "armor class not available -rjf");
    case 3:
        return field_E;
    case 4:
        return field_10;
    case 5:
        return field_12;
    case 6:
        return field_14;
    case 7:
        return field_18;
    case 8:
        return field_1A;
    case 9:
        return m_nSaveVSFortitude;
    case 10:
        return m_nSaveVSReflex;
    case 11:
        return m_nSaveVSWill;
    case 12:
        return field_144[8];
    case 14:
        return m_nResistFire;
    case 15:
        return m_nResistCold;
    case 16:
        return m_nResistElectricity;
    case 17:
        return m_nResistAcid;
    case 18:
        return m_nResistMagic;
    case 19:
        return m_nResistMagicFire;
    case 20:
        return m_nResistMagicCold;
    case 21:
        return m_nResistSlashing;
    case 22:
        return m_nResistCrushing;
    case 23:
        return m_nResistPiercing;
    case 24:
        return field_36;
    case 25:
        return field_144[0];
    case 26:
        return field_144[10];
    case 27:
        return field_144[9];
    case 28:
        return field_144[12];
    case 29:
        return field_144[11];
    case 30:
        return field_38;
    case 31:
        return field_3A;
    case 32:
        return field_3C;
    case 33:
        return field_144[15];
    case 34:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1397
        UTIL_ASSERT(FALSE);
    case 35:
        return field_52;
    case 36:
        return m_nSTR;
    case 37:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1412
        UTIL_ASSERT(FALSE);
    case 38:
        return m_nINT;
    case 39:
        return m_nWIS;
    case 40:
        return m_nDEX;
    case 41:
        return m_nCON;
    case 42:
        return m_nCHR;
    case 43:
        return field_60;
    case 44:
        return field_64;
    case 45:
        return field_68;
    case 46:
        return m_nMoraleBreak;
    case 47:
        return m_nMoraleRecoveryTime;
    case 48:
        return field_74;
    case 49:
        return m_favoredEnemies[0];
    case 50:
        return field_86;
    case 51:
        return field_88;
    case 52:
        return field_8A;
    case 53:
        return field_8C;
    case 54:
        return field_8E;
    case 55:
        return field_90;
    case 56:
        return field_92;
    case 57:
        return m_nLayOnHandsAmount;
    case 58:
        return field_96;
    case 59:
        return field_9A;
    case 60:
        return field_B2;
    case 61:
        return field_9E;
    case 68:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1400
        UTIL_ASSERT(FALSE);
    case 69:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1403
        UTIL_ASSERT(FALSE);
    case 70:
        return field_AE;
    case 71:
        return field_B4;
    case 72:
        return field_B6;
    case 73:
        return field_B8;
    case 74:
        return field_BA;
    case 75:
        return field_BC;
    case 76:
        return field_C0;
    case 77:
        return field_C4;
    case 78:
        return field_C6;
    case 79:
        return field_C8;
    case 80:
        return field_CA;
    case 81:
        return field_CC;
    case 82:
        return field_D0;
    case 83:
        return field_D4;
    case 84:
        return field_D8;
    case 85:
        return field_DC;
    case 86:
        return field_E0;
    case 87:
        return field_E4;
    case 88:
        return field_E8;
    case 89:
        return m_nSpecialization;
    case 90:
        return field_144[6];
    case 91:
        return field_A6;
    case 92:
        return field_AA;
    case 93:
        return field_3E;
    case 94:
        return field_144[14];
    case 95:
        return m_nLevel;
    case 96:
    case 97:
    case 98:
    case 99:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
        return GetClassLevel(offset - 95);
    case 107:
        return 1984;
    default:
        return 0;
    }
}

// 0x447390
int CDerivedStats::sub_447390()
{
    return field_64;
}

// 0x4473A0
unsigned char CDerivedStats::sub_4473A0()
{
    return m_nLevel;
}

// 0x4473B0
DWORD CDerivedStats::GetSorcererWizardLevel()
{
    // NOTE: Uninline.
    return GetClassMaskLevel(CLASSMASK_SORCERER | CLASSMASK_WIZARD);
}

// 0x4473F0
DWORD CDerivedStats::GetBardMonkRogueLevel()
{
    // NOTE: Uninline.
    return GetClassMaskLevel(CLASSMASK_BARD | CLASSMASK_MONK | CLASSMASK_ROGUE);
}

// 0x447940
BOOL CDerivedStats::HasClassMask(INT iClassType)
{
    return (iClassType & m_classMask) != 0;
}

// 0x447950
DWORD CDerivedStats::GetClassMaskLevel(DWORD dwMask)
{
    DWORD nLevel = 0;
    DWORD dwCurrentClassMask = 1;

    DWORD dwClassMask = dwMask & m_classMask;
    if (dwClassMask == 0) {
        return 0;
    }

    for (int index = 0; index < CAIOBJECT_CLASS_MAX; index++) {
        if (dwCurrentClassMask > dwMask) {
            break;
        }

        if ((dwClassMask & dwCurrentClassMask) != 0) {
            nLevel += m_nClassLevels[index];
        }

        dwCurrentClassMask <<= 1;
    }

    return nLevel;
}

// 0x447990
DWORD CDerivedStats::GetClassLevel(int iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2070
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2071
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_nClassLevels[iClassType - 1];
}

// 0x4479E0
void CDerivedStats::SetClassLevel(INT iClassType, INT nLevel)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2087
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2088
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    BYTE nOldLevel = m_nClassLevels[iClassType - 1];
    m_nClassLevels[iClassType - 1] = nLevel;
    m_nLevel += nLevel - nOldLevel;

    if (nLevel != 0) {
        m_classMask |= 1 << (iClassType - 1);
    } else {
        m_classMask &= ~(1 << (iClassType - 1));
    }
}

// 0x447A70
BOOL CDerivedStats::HasClass(INT iClassType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2121
    UTIL_ASSERT(iClassType > 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
    // __LINE__: 2122
    UTIL_ASSERT(iClassType <= CAIOBJECT_CLASS_MAX);

    return m_nClassLevels[iClassType - 1] != 0;
}

// 0x447AD0
INT CDerivedStats::GetBestClass()
{
    int nBestClassLevel = 0;
    int nBestClass = 0;
    for (int nClass = 0; nClass < CAIOBJECT_CLASS_MAX; nClass++) {
        if (nBestClassLevel < m_nClassLevels[nClass]) {
            nBestClassLevel = m_nClassLevels[nClass];
            nBestClass = nClass;
        }
    }

    return nBestClass + 1;
}

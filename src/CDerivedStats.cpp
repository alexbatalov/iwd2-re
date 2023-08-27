#include "CDerivedStats.h"

#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CGameSpriteSpells.h"
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
void CDerivedStats::Reload(CGameSprite* pSprite, CCreatureFileHeader* pCreature, CGameSpriteSpells* pSpells, CGameSpriteGroupedSpellList* pDomainSpells)
{
    int index;

    m_nBackstabDamageMultiplier = 0;
    m_nLayOnHandsAmount = 0;

    m_generalState = pCreature->m_generalState;
    m_nMaxHitPoints = pCreature->m_maxHitPointsBase;
    field_6 = 0;
    field_8 = 0;
    field_A = 0;
    field_C = pCreature->field_3E;
    m_nACCrushingMod = pCreature->m_armorClassCrushingAdjustment;
    m_nACMissileMod = pCreature->m_armorClassMissileAdjustment;
    m_nACPiercingMod = pCreature->m_armorClassPiercingAdjustment;
    m_nACSlashingMod = pCreature->m_armorClassSlashingAdjustment;

    // TODO: Incomplete.

    field_16 = 0;
    m_nTHAC0 = 0;
    m_nNumberOfAttacks = pCreature->m_numberOfAttacksBase;
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
    m_nResistMissile = pCreature->m_resistMissileBase;
    m_nFatigue = pCreature->m_fatigue;
    m_nIntoxication = pCreature->m_intoxication;
    m_nLuck = pCreature->m_luckBase;

    memcpy(m_nSkills, pCreature->m_skills, 64);

    m_nSubRace = pCreature->m_subrace;

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

    m_nSex = pCreature->m_sex;

    m_nSTR = pCreature->m_STRBase;
    m_nINT = pCreature->m_INTBase;
    m_nWIS = pCreature->m_WISBase;
    m_nDEX = pCreature->m_DEXBase;
    m_nCON = pCreature->m_CONBase;
    m_nCHR = pCreature->m_CHRBase;

    m_nXPValue = pCreature->m_xpValue;
    m_nXP = pCreature->m_xp;
    m_nGold = pCreature->m_gold;
    m_nMoraleRecoveryTime = pCreature->m_moraleRecoveryTime;
    m_nReputation = pCreature->m_reputation;
    m_nMoraleBreak = pCreature->m_moraleBreak;

    for (index = 0; index < 8; index++) {
        m_favoredEnemies[index] = pCreature->m_favoredEnemies[index];
    }

    m_nSpecialization = pCreature->m_specialization;
    m_nMoveSilentlyMTPBonus = 0;
    m_nHideInShadowsMTPBonus = 0;
    m_nDamageBonus = 0;
    m_nSpellFailureArcane = 0;
    m_nSpellFailureDivine = 0;
    m_nSpellDurationModMage = 100;
    m_nSpellDurationModPriest = 100;
    m_nTurnUndeadLevel = 0;
    m_bHeld = FALSE;
    m_bPolymorphed = FALSE;
    m_nTranslucent = 0;
    m_bIdentifyMode = FALSE;

    m_spellStates.reset();

    field_10C = 0;
    m_bCasterHold = FALSE;
    m_nEncumberance = 0;
    m_nMagicDamageResistance = pCreature->m_resistMagicDamageBase;
    m_nResistPoison = 0;
    m_bDoNotJump = FALSE;
    m_bAuraCleansing = FALSE;
    m_nMentalSpeed = 0;
    m_nPhysicalSpeed = 0;
    m_nCastingLevelBonusMage = 0;
    m_nCastingLevelBonusCleric = 0;
    m_bSeeInvisible = FALSE;
    m_bIgnoreDialogPause = FALSE;
    m_nMinHitPoints = 0;
    m_THAC0BonusRight = 0;
    m_THAC0BonusLeft = 0;
    m_DamageBonusRight = 0;
    m_DamageBonusLeft = 0;
    m_nStoneSkins = 0;
    m_nDamageModFire = 0;
    m_nDamageModCold = 0;
    m_nDamageModElectricity = 0;
    m_nDamageModAcid = 0;
    m_nDamageModMagic = 0;
    m_nDamageModPoison = 0;
    m_nDamageModSlashing = 0;
    m_nDamageModPiercing = 0;
    m_nDamageModCrushing = 0;
    m_nDamageModMissile = 0;
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

    for (int buttonIndex = 0; buttonIndex < 40; buttonIndex++) {
        m_disabledButtons[buttonIndex] = FALSE;
    }

    m_disabledSpellTypes[0] = FALSE;
    m_disabledSpellTypes[1] = FALSE;
    m_disabledSpellTypes[2] = FALSE;

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
    m_nACCrushingMod = 0;
    m_nACMissileMod = 0;
    m_nACPiercingMod = 0;

    // TODO: Incomplete.

    field_16 = 0;
    m_nTHAC0 = 0;
    m_nNumberOfAttacks = 0;
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
    m_nResistMissile = 0;

    memset(m_nSkills, 0, 64);

    m_nFatigue = 0;
    m_nIntoxication = 0;
    m_nLuck = 0;
    m_nSubRace = 0;
    m_nLevel = 0;
    m_nSex = 0;
    m_nSTR = 0;
    m_nINT = 0;
    m_nWIS = 0;
    m_nDEX = 0;
    m_nCON = 0;
    m_nCHR = 0;
    m_nXPValue = 0;
    m_nXP = 0;
    m_nGold = 0;
    m_nMoraleRecoveryTime = 0;
    m_nReputation = 0;
    m_nMoraleBreak = 0;

    for (index = 0; index < 8; index++) {
        m_favoredEnemies[index] = CAIObjectType::R_NO_RACE;
    }

    m_nDamageBonus = 0;
    m_nSpellFailureArcane = 0;
    m_nSpellFailureDivine = 0;
    m_nSpellDurationModMage = 0;
    m_nSpellDurationModPriest = 0;
    m_nTurnUndeadLevel = 0;
    m_nBackstabDamageMultiplier = 0;
    m_nLayOnHandsAmount = 0;
    m_bHeld = FALSE;
    m_bPolymorphed = FALSE;
    m_nTranslucent = 0;
    m_bIdentifyMode = FALSE;
    m_nSpecialization = 0;
    m_nMoveSilentlyMTPBonus = 0;
    m_nHideInShadowsMTPBonus = 0;

    m_spellStates.reset();

    field_10C = 0;
    m_bCasterHold = FALSE;
    m_nEncumberance = 0;
    m_nMissileTHAC0Bonus = 0;
    m_nMagicDamageResistance = 0;
    m_nResistPoison = 0;
    m_bDoNotJump = FALSE;
    m_bAuraCleansing = FALSE;
    m_nMentalSpeed = 0;
    m_nPhysicalSpeed = 0;
    m_nCastingLevelBonusMage = 0;
    m_nCastingLevelBonusCleric = 0;
    m_bSeeInvisible = FALSE;
    m_bIgnoreDialogPause = FALSE;
    m_nMinHitPoints = 0;
    m_THAC0BonusRight = 0;
    m_THAC0BonusLeft = 0;
    m_DamageBonusRight = 0;
    m_DamageBonusLeft = 0;
    m_nStoneSkins = 0;
    m_nDamageModFire = 0;
    m_nDamageModCold = 0;
    m_nDamageModElectricity = 0;
    m_nDamageModAcid = 0;
    m_nDamageModMagic = 0;
    m_nDamageModPoison = 0;
    m_nDamageModSlashing = 0;
    m_nDamageModPiercing = 0;
    m_nDamageModCrushing = 0;
    m_nDamageModMissile = 0;
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
    m_nACCrushingMod += other.m_nACCrushingMod;
    m_nACMissileMod += other.m_nACMissileMod;
    m_nACPiercingMod += other.m_nACPiercingMod;
    m_nACSlashingMod += other.m_nACSlashingMod;
    field_16 += other.field_16;
    m_nTHAC0 += other.m_nTHAC0;
    m_nNumberOfAttacks += other.m_nNumberOfAttacks;
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
    m_nResistMissile += other.m_nResistMissile;
    m_nMagicDamageResistance += other.m_nMagicDamageResistance;
    m_nFatigue += other.m_nFatigue;
    m_nIntoxication += other.m_nIntoxication;
    m_nLuck += other.m_nLuck;
    m_nLevel += other.m_nLevel;
    m_nSTR += other.m_nSTR;
    m_nINT += other.m_nINT;
    m_nWIS += other.m_nWIS;
    m_nDEX += other.m_nDEX;
    m_nCON += other.m_nCON;
    m_nCHR += other.m_nCHR;
    m_nXPValue += other.m_nXPValue;
    m_nXP += other.m_nXP;
    m_nGold += other.m_nGold;
    m_nMoraleBreak += other.m_nMoraleBreak;
    m_nMoraleRecoveryTime += other.m_nMoraleRecoveryTime;
    m_nReputation += other.m_nReputation;
    m_nMoraleBreak += other.m_nMoraleBreak;
    m_nDamageBonus += other.m_nDamageBonus;
    m_nSpellFailureArcane += other.m_nSpellFailureArcane;
    m_nSpellFailureDivine += other.m_nSpellFailureDivine;
    m_nSpellDurationModMage += other.m_nSpellDurationModMage;
    m_nSpellDurationModPriest += other.m_nSpellDurationModPriest;
    m_nTurnUndeadLevel += other.m_nTurnUndeadLevel;
    m_nBackstabDamageMultiplier += other.m_nBackstabDamageMultiplier;
    m_nLayOnHandsAmount += other.m_nLayOnHandsAmount;
    m_bHeld |= other.m_bHeld;
    m_bPolymorphed |= other.m_bPolymorphed;
    m_nTranslucent += other.m_nTranslucent;
    m_bIdentifyMode |= other.m_bIdentifyMode;
    m_nMoveSilentlyMTPBonus += other.m_nMoveSilentlyMTPBonus;
    m_nHideInShadowsMTPBonus += other.m_nHideInShadowsMTPBonus;

    m_spellStates |= other.m_spellStates;

    field_10C |= other.field_10C;
    m_nStoneSkins += other.m_nStoneSkins;
    m_bCasterHold |= other.m_bCasterHold;
    field_184 |= other.field_184;
    m_nDamageModFire += other.m_nDamageModFire;
    m_nDamageModCold += other.m_nDamageModCold;
    m_nDamageModElectricity += other.m_nDamageModElectricity;
    m_nDamageModAcid += other.m_nDamageModAcid;
    m_nDamageModMagic += other.m_nDamageModMagic;
    m_nDamageModPoison += other.m_nDamageModPoison;
    m_nDamageModSlashing += other.m_nDamageModSlashing;
    m_nDamageModPiercing += other.m_nDamageModPiercing;
    m_nDamageModCrushing += other.m_nDamageModCrushing;
    m_nDamageModMissile += other.m_nDamageModMissile;
    field_124 += other.field_124;
    field_128 += other.field_128;
    field_12C += other.field_12C;
    field_130 += other.field_130;
    field_134 += other.field_134;
    field_138 += other.field_138;
    field_13C += other.field_13C;
    field_140 += other.field_140;

    for (index = 0; index < 64; index++) {
        m_nSkills[index] += other.m_nSkills[index];
    }

    CheckLimits();

    return *this;
}

// 0x4468F0
void CDerivedStats::CheckLimits()
{
    if ((m_generalState & STATE_DEAD) != 0) {
        m_generalState &= STATE_ANY_DEATH;
    }

    m_nMaxHitPoints = max(m_nMaxHitPoints, 1);
    m_nACCrushingMod = min(max(m_nACCrushingMod, -20), 20);
    m_nACMissileMod = min(max(m_nACMissileMod, -20), 20);
    m_nACPiercingMod = min(max(m_nACPiercingMod, -20), 20);
    m_nACSlashingMod = min(max(m_nACSlashingMod, -20), 20);
    m_nTHAC0 = min(max(m_nTHAC0, -255), 255);
    m_nNumberOfAttacks = min(max(m_nNumberOfAttacks, 0), 5);
    m_nSaveVSFortitude = min(max(m_nSaveVSFortitude, -40), 40);
    m_nSaveVSReflex = min(max(m_nSaveVSReflex, -40), 40);
    m_nSaveVSWill = min(max(m_nSaveVSWill, -40), 40);
    m_nSkills[10] = min(max(m_nSkills[10], -128), 127);
    m_nSkills[9] = min(max(m_nSkills[9], -128), 127);
    m_nSkills[6] = min(max(m_nSkills[6], -128), 127);
    m_nSkills[14] = min(max(m_nSkills[14], -128), 127);
    m_nSkills[12] = min(max(m_nSkills[12], -128), 127);
    m_nSkills[11] = min(max(m_nSkills[11], -128), 127);
    m_nSkills[15] = min(max(m_nSkills[15], -128), 127);
    m_nFatigue = min(max(m_nFatigue, 0), 100);
    m_nIntoxication = min(max(m_nIntoxication, 0), 100);
    m_nLuck = min(max(m_nLuck, 0), 100);
    m_nLevel = min(m_nLevel, 50);
    m_nSTR = min(max(m_nSTR, 1), 40);
    m_nINT = min(max(m_nINT, 1), 40);
    m_nWIS = min(max(m_nWIS, 1), 40);
    m_nDEX = min(max(m_nDEX, 1), 40);
    m_nCON = min(max(m_nCON, 1), 40);
    m_nCHR = min(max(m_nCHR, 1), 40);
    m_nXPValue = min(max(m_nXPValue, -1), 0);
    m_nXP = min(max(m_nXP, -1), 0);
    m_nGold = min(max(m_nGold, -1), 0);
    m_nMoraleRecoveryTime = min(max(m_nMoraleRecoveryTime, -1), 0);
    m_nReputation = min(max(m_nReputation, 10), 200);
    m_nMoraleBreak = min(max(m_nMoraleBreak, 10), 200);
    m_nDamageBonus = min(max(m_nDamageBonus, -128), 127);
    m_nSpellFailureArcane = min(max(m_nSpellFailureArcane, 0), 100);
    m_nSpellFailureDivine = min(max(m_nSpellFailureDivine, 0), 100);
    m_nSpellDurationModMage = min(max(m_nSpellDurationModMage, 0), 255);
    m_nSpellDurationModPriest = min(max(m_nSpellDurationModPriest, 0), 255);
    m_nTurnUndeadLevel = max(m_nTurnUndeadLevel, 0);
    m_nBackstabDamageMultiplier = max(m_nBackstabDamageMultiplier, 0);
    m_nLayOnHandsAmount = max(m_nLayOnHandsAmount, 0);
    m_nTranslucent = min(m_nTranslucent, 255);
}

// 0x446DD0
LONG CDerivedStats::GetAtOffset(SHORT offset)
{
    switch (offset) {
    case STAT_MAXHITPOINTS:
        return m_nMaxHitPoints;
    case STAT_ARMORCLASS:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1323
        UTIL_ASSERT_MSG(FALSE, "armor class not available -rjf");
    case STAT_ACBLUDGEONINGMOD:
        return m_nACCrushingMod;
    case STAT_ACMISSILEMOD:
        return m_nACMissileMod;
    case STAT_ACPIERCINGMOD:
        return m_nACPiercingMod;
    case STAT_ACSLASHINGMOD:
        return m_nACSlashingMod;
    case STAT_THAC0:
        return m_nTHAC0;
    case STAT_NUMBEROFATTACKS:
        return m_nNumberOfAttacks;
    case STAT_SAVEFORTITUDE:
        return m_nSaveVSFortitude;
    case STAT_SAVEREFLEX:
        return m_nSaveVSReflex;
    case STAT_SAVEWILL:
        return m_nSaveVSWill;
    case STAT_KNOWLEDGEARCANA:
        return m_nSkills[8];
    case STAT_RESISTFIRE:
        return m_nResistFire;
    case STAT_RESISTCOLD:
        return m_nResistCold;
    case STAT_RESISTELECTRICITY:
        return m_nResistElectricity;
    case STAT_RESISTACID:
        return m_nResistAcid;
    case STAT_RESISTMAGIC:
        return m_nResistMagic;
    case STAT_RESISTMAGICFIRE:
        return m_nResistMagicFire;
    case STAT_RESISTMAGICCOLD:
        return m_nResistMagicCold;
    case STAT_RESISTSLASHING:
        return m_nResistSlashing;
    case STAT_RESISTBLUDGEONING:
        return m_nResistCrushing;
    case STAT_RESISTPIERCING:
        return m_nResistPiercing;
    case STAT_RESISTMISSILE:
        return m_nResistMissile;
    case STAT_ALCHEMY:
        return m_nSkills[0];
    case STAT_LOCKPICKING:
        return m_nSkills[10];
    case STAT_MOVESILENTLY:
        return m_nSkills[9];
    case STAT_TRAPS:
        return m_nSkills[12];
    case STAT_PICKPOCKET:
        return m_nSkills[11];
    case STAT_FATIGUE:
        return m_nFatigue;
    case STAT_INTOXICATION:
        return m_nIntoxication;
    case STAT_LUCK:
        return m_nLuck;
    case STAT_TRACKING:
        return m_nSkills[15];
    case STAT_LEVEL:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1397
        UTIL_ASSERT(FALSE);
    case STAT_SEX:
        return m_nSex;
    case STAT_STR:
        return m_nSTR;
    case STAT_STREXTRA:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1412
        UTIL_ASSERT(FALSE);
    case STAT_INT:
        return m_nINT;
    case STAT_WIS:
        return m_nWIS;
    case STAT_DEX:
        return m_nDEX;
    case STAT_CON:
        return m_nCON;
    case STAT_CHR:
        return m_nCHR;
    case STAT_XPVALUE:
        return m_nXPValue;
    case STAT_XP:
        return m_nXP;
    case STAT_GOLD:
        return m_nGold;
    case STAT_MORALEBREAK:
        return m_nMoraleBreak;
    case STAT_MORALERECOVERYTIME:
        return m_nMoraleRecoveryTime;
    case STAT_REPUTATION:
        return m_nReputation;
    case STAT_HATEDRACE:
        return m_favoredEnemies[0];
    case STAT_DAMAGEBONUS:
        return m_nDamageBonus;
    case STAT_SPELLFAILUREMAGE:
        return m_nSpellFailureArcane;
    case STAT_SPELLFAILUREPRIEST:
        return m_nSpellFailureDivine;
    case STAT_SPELLDURATIONMODMAGE:
        return m_nSpellDurationModMage;
    case STAT_SPELLDURATIONMODPRIEST:
        return m_nSpellDurationModPriest;
    case STAT_TURNUNDEADLEVEL:
        return m_nTurnUndeadLevel;
    case STAT_BACKSTABDAMAGEMULTIPLIER:
        return m_nBackstabDamageMultiplier;
    case STAT_LAYONHANDSAMOUNT:
        return m_nLayOnHandsAmount;
    case STAT_HELD:
        return m_bHeld;
    case STAT_POLYMORPHED:
        return m_bPolymorphed;
    case STAT_TRANSLUCENT:
        return m_nTranslucent;
    case STAT_IDENTIFYMODE:
        return m_bIdentifyMode;
    case STAT_LEVEL2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1400
        UTIL_ASSERT(FALSE);
    case STAT_LEVEL3:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CDerivedStats.cpp
        // __LINE__: 1403
        UTIL_ASSERT(FALSE);
    case STAT_CASTERHOLD:
        return m_bCasterHold;
    case STAT_ENCUMBERANCE:
        return m_nEncumberance;
    case STAT_MISSILETHAC0BONUS:
        return m_nMissileTHAC0Bonus;
    case STAT_MAGICDAMAGERESISTANCE:
        return m_nMagicDamageResistance;
    case STAT_RESISTPOISON:
        return m_nResistPoison;
    case STAT_DONOTJUMP:
        return m_bDoNotJump;
    case STAT_AURACLEANSING:
        return m_bAuraCleansing;
    case STAT_MENTALSPEED:
        return m_nMentalSpeed;
    case STAT_PHYSICALSPEED:
        return m_nPhysicalSpeed;
    case STAT_CASTINGLEVELBONUSMAGE:
        return m_nCastingLevelBonusMage;
    case STAT_CASTINGLEVELBONUSCLERIC:
        return m_nCastingLevelBonusCleric;
    case STAT_SEEINVISIBLE:
        return m_bSeeInvisible;
    case STAT_IGNOREDIALOGPAUSE:
        return m_bIgnoreDialogPause;
    case STAT_MINHITPOINTS:
        return m_nMinHitPoints;
    case STAT_THAC0BONUSRIGHT:
        return m_THAC0BonusRight;
    case STAT_THAC0BONUSLEFT:
        return m_THAC0BonusLeft;
    case STAT_DAMAGEBONUSRIGHT:
        return m_DamageBonusRight;
    case STAT_DAMAGEBONUSLEFT:
        return m_DamageBonusLeft;
    case STAT_STONESKINS:
        return m_nStoneSkins;
    case STAT_KIT:
        return m_nSpecialization;
    case STAT_HIDEINSHADOWS:
        return m_nSkills[6];
    case STAT_MOVESILENTLYMTPBONUS:
        return m_nMoveSilentlyMTPBonus;
    case STAT_HIDEINSHADOWSMTPBONUS:
        return m_nHideInShadowsMTPBonus;
    case STAT_SUBRACE:
        return m_nSubRace;
    case STAT_USEMAGICDEVICE:
        return m_nSkills[14];
    case STAT_CLASSLEVELSUM:
        return m_nLevel;
    case STAT_CLASSLEVELBARBARIAN:
    case STAT_CLASSLEVELBARD:
    case STAT_CLASSLEVELCLERIC:
    case STAT_CLASSLEVELDRUID:
    case STAT_CLASSLEVELFIGHTER:
    case STAT_CLASSLEVELMONK:
    case STAT_CLASSLEVELPALADIN:
    case STAT_CLASSLEVELRANGER:
    case STAT_CLASSLEVELROGUE:
    case STAT_CLASSLEVELSORCERER:
    case STAT_CLASSLEVELWIZARD:
        // NOTE: Uninline.
        return GetClassLevel(offset - STAT_CLASSLEVELSUM);
    case STAT_107:
        return field_184;
    default:
        return 0;
    }
}

// 0x447390
int CDerivedStats::GetXP()
{
    return m_nXP;
}

// 0x4473A0
BYTE CDerivedStats::GetLevel()
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

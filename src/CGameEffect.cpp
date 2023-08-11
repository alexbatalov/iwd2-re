#include "CGameEffect.h"

#include "CGameSprite.h"
#include "CUtil.h"

// NOTE: Inlined.
CGameEffectBase::CGameEffectBase()
{
    memset(this, 0, sizeof(*this));

    m_version = "EFF V2.0";
    m_effectID = 0;
    m_targetType = 0;
    m_spellLevel = 0;
    m_effectAmount = 0;
    m_dwFlags = 0;
    m_durationType = 0;
    m_duration = 0;
    m_probabilityUpper = 100;
    m_probabilityLower = 0;
    m_res = "";
    m_numDice = 0;
    m_diceSize = 0;
    m_savingThrow = 0;
    m_saveMod = 0;
    m_special = 0;
    field_44 = 0;
    field_48 = 0;
    m_minLevel = 0;
    m_maxLevel = 0;
    m_flags = 0;
    m_effectAmount2 = 0;
    m_effectAmount3 = 0;
    m_effectAmount4 = 0;
    m_effectAmount5 = 0;
    m_res2 = "";
    m_res3 = "";
    m_source.x = -1;
    m_source.y = -1;
    m_target.x = -1;
    m_target.y = -1;
    m_sourceType = 0;
    m_sourceRes = "";
    m_sourceFlags = 0;
    m_projectileType = 0;
    m_slotNum = -1;
    m_casterLevel = 0;
    m_firstCall = 0;
    m_secondaryType = 1;
    memset(m_pad, 0, sizeof(m_pad));
}

// 0x48C800
CGameEffect* CGameEffect::DecodeEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, const CPoint& target)
{
    if (effect->diceSize == -1) {
        effect->diceSize = 0;
    }

    if (effect->effectID == 36 || effect->effectID == 37) {
        CString sError;
        sError.Format("Old saving throw effect (breath or spell) detected:  id=%d  res=%s",
            effect->effectID,
            effect->res);
        effect->effectID = CGAMEEFFECT_SAVEVSWILL;
    }

    switch (effect->effectID) {
    case CGAMEEFFECT_AC:
        return new CGameEffectAC(effect, source, sourceID, target);
    case CGAMEEFFECT_ATTACKNO:
        return new CGameEffectAttackNo(effect, source, sourceID, target);
    case CGAMEEFFECT_AWAKEN:
        return new CGameEffectAwaken(effect, source, sourceID, target);
    case CGAMEEFFECT_BERSERK:
        return new CGameEffectBerserk(effect, source, sourceID, target);
    case CGAMEEFFECT_CALM:
        return new CGameEffectCalm(effect, source, sourceID, target);
    case CGAMEEFFECT_CHARM:
        return new CGameEffectCharm(effect, source, sourceID, target);
    case CGAMEEFFECT_CHR:
        return new CGameEffectCHR(effect, source, sourceID, target);
    case CGAMEEFFECT_COLORCHANGE:
        return new CGameEffectColorChange(effect, source, sourceID, target);
    case CGAMEEFFECT_COLORGLOWSOLID:
        return new CGameEffectColorGlowSolid(effect, source, sourceID, target);
    case CGAMEEFFECT_COLORGLOWPULSE:
        return new CGameEffectColorGlowPulse(effect, source, sourceID, target);
    case CGAMEEFFECT_CON:
        return new CGameEffectCON(effect, source, sourceID, target);
    case CGAMEEFFECT_CUREPOISON:
        return new CGameEffectCurePoison(effect, source, sourceID, target);
    case CGAMEEFFECT_DAMAGE:
        return new CGameEffectDamage(effect, source, sourceID, target);
    case CGAMEEFFECT_DEATH:
        return new CGameEffectDeath(effect, source, sourceID, target);
    case CGAMEEFFECT_DEFROST:
        return new CGameEffectDefrost(effect, source, sourceID, target);
    case CGAMEEFFECT_DEX:
        return new CGameEffectDEX(effect, source, sourceID, target);
    case CGAMEEFFECT_HASTE:
        return new CGameEffectHaste(effect, source, sourceID, target);
    case CGAMEEFFECT_HEAL:
        return new CGameEffectHeal(effect, source, sourceID, target);
    case CGAMEEFFECT_HITPOINTS:
        return new CGameEffectHitPoints(effect, source, sourceID, target);
    case CGAMEEFFECT_INT:
        return new CGameEffectINT(effect, source, sourceID, target);
    case CGAMEEFFECT_INVISIBLE:
        return new CGameEffectInvisible(effect, source, sourceID, target);
    case CGAMEEFFECT_LORE:
        return new CGameEffectLore(effect, source, sourceID, target);
    case CGAMEEFFECT_LUCK:
        return new CGameEffectLuck(effect, source, sourceID, target);
    case CGAMEEFFECT_MORALE:
        return new CGameEffectMorale(effect, source, sourceID, target);
    case CGAMEEFFECT_PANIC:
        return new CGameEffectPanic(effect, source, sourceID, target);
    case CGAMEEFFECT_POISON:
        return new CGameEffectPoison(effect, source, sourceID, target);
    case CGAMEEFFECT_REMOVECURSE:
        return new CGameEffectRemoveCurse(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTACID:
        return new CGameEffectResistAcid(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTCOLD:
        return new CGameEffectResistCold(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTELECTRICITY:
        return new CGameEffectResistElectricity(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTFIRE:
        return new CGameEffectResistFire(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTMAGIC:
        return new CGameEffectResistMagic(effect, source, sourceID, target);
    case CGAMEEFFECT_RESURRECT:
        return new CGameEffectResurrect(effect, source, sourceID, target);
    case CGAMEEFFECT_SAVEVSFORTITUDE:
        return new CGameEffectSaveVsFortitude(effect, source, sourceID, target);
    case CGAMEEFFECT_SAVEVSRELFEX:
        return new CGameEffectSaveVsRelfex(effect, source, sourceID, target);
    case CGAMEEFFECT_SAVEVSWILL:
        return new CGameEffectSaveVsWill(effect, source, sourceID, target);
    case CGAMEEFFECT_SILENCE:
        return new CGameEffectSilence(effect, source, sourceID, target);
    case CGAMEEFFECT_SLEEP:
        return new CGameEffectSleep(effect, source, sourceID, target);
    case CGAMEEFFECT_SLOW:
        return new CGameEffectSlow(effect, source, sourceID, target);
    case CGAMEEFFECT_SPARKLE:
        return new CGameEffectSparkle(effect, source, sourceID, target);
    case CGAMEEFFECT_SPELLMEMORIZATIONMAGE:
        return new CGameEffectSpellMemorizationMage(effect, source, sourceID, target);
    case CGAMEEFFECT_STONETOFLESH:
        return new CGameEffectStoneToFlesh(effect, source, sourceID, target);
    case CGAMEEFFECT_STR:
        return new CGameEffectSTR(effect, source, sourceID, target);
    case CGAMEEFFECT_STUN:
        return new CGameEffectStun(effect, source, sourceID, target);
    case CGAMEEFFECT_UNSTUN:
        return new CGameEffectUnstun(effect, source, sourceID, target);
    case CGAMEEFFECT_VISIBLE:
        return new CGameEffectVisible(effect, source, sourceID, target);
    case CGAMEEFFECT_VOCALIZE:
        return new CGameEffectVocalize(effect, source, sourceID, target);
    case CGAMEEFFECT_WIS:
        return new CGameEffectWIS(effect, source, sourceID, target);
    case CGAMEEFFECT_SINGLECOLORPULSEALL:
        return new CGameEffectSingleColorPulseAll(effect, source, sourceID, target);
    case CGAMEEFFECT_COLORTINTSOLID:
        return new CGameEffectColorTintSolid(effect, source, sourceID, target);
    case CGAMEEFFECT_COLORLIGHTSOLID:
        return new CGameEffectColorLightSolid(effect, source, sourceID, target);
    case CGAMEEFFECT_ANIMATIONCHANGE:
        return new CGameEffectAnimationChange(effect, source, sourceID, target);
    case CGAMEEFFECT_BASEATTACKBONUS:
        return new CGameEffectBaseAttackBonus(effect, source, sourceID, target);
    case CGAMEEFFECT_SLAY:
        return new CGameEffectSlay(effect, source, sourceID, target);
    case CGAMEEFFECT_ALIGNMENTREVERSAL:
        return new CGameEffectAlignmentReversal(effect, source, sourceID, target);
    case CGAMEEFFECT_ALIGNMENTCHANGE:
        return new CGameEffectAlignmentChange(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELEFFECTS:
        return new CGameEffectDispelEffects(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLSTEALTH:
        return new CGameEffectSkillStealth(effect, source, sourceID, target);
    case CGAMEEFFECT_CASTINGFAILURE:
        return new CGameEffectCastingFailure(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLALCHEMY:
        return new CGameEffectSkillAlchemy(effect, source, sourceID, target);
    case CGAMEEFFECT_SPELLMEMOIZATIONCLERIC:
        return new CGameEffectSpellMemoizationCleric(effect, source, sourceID, target);
    case CGAMEEFFECT_INFRAVISION:
        return new CGameEffectInfravision(effect, source, sourceID, target);
    case CGAMEEFFECT_INFRAVISIONOFF:
        return new CGameEffectInfravisionOff(effect, source, sourceID, target);
    case CGAMEEFFECT_BLUR:
        return new CGameEffectBlur(effect, source, sourceID, target);
    case CGAMEEFFECT_TRANSLUCENT:
        return new CGameEffectTranslucent(effect, source, sourceID, target);
    case CGAMEEFFECT_SUMMON:
        return new CGameEffectSummon(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLUNSUMMON:
        return new CGameEffectSkillUnsummon(effect, source, sourceID, target);
    case CGAMEEFFECT_NONDETECTION:
        return new CGameEffectNonDetection(effect, source, sourceID, target);
    case CGAMEEFFECT_ENDNONDETECTION:
        return new CGameEffectEndNonDetection(effect, source, sourceID, target);
    case CGAMEEFFECT_SEXCHANGE:
        return new CGameEffectSexChange(effect, source, sourceID, target);
    case CGAMEEFFECT_AICHANGE:
        return new CGameEffectAIChange(effect, source, sourceID, target);
    case CGAMEEFFECT_DAMAGEMOD:
        return new CGameEffectDamageMod(effect, source, sourceID, target);
    case CGAMEEFFECT_BLINDNESS:
        return new CGameEffectBlindness(effect, source, sourceID, target);
    case CGAMEEFFECT_CUREBLINDNESS:
        return new CGameEffectCureBlindness(effect, source, sourceID, target);
    case CGAMEEFFECT_FEEBLEMINDEDNESS:
        return new CGameEffectFeebleMindedness(effect, source, sourceID, target);
    case CGAMEEFFECT_CUREFEEBLEMINDEDNESS:
        return new CGameEffectCureFeebleMindedness(effect, source, sourceID, target);
    case CGAMEEFFECT_DISEASE:
        return new CGameEffectDisease(effect, source, sourceID, target);
    case CGAMEEFFECT_CUREDISEASE:
        return new CGameEffectCureDisease(effect, source, sourceID, target);
    case CGAMEEFFECT_DEAFNESS:
        return new CGameEffectDeafness(effect, source, sourceID, target);
    case CGAMEEFFECT_CUREDEAFNESS:
        return new CGameEffectCureDeafness(effect, source, sourceID, target);
    case CGAMEEFFECT_SETAISCRIPT:
        return new CGameEffectSetAIScript(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYTOPROJECTILE:
        return new CGameEffectImmunityToProjectile(effect, source, sourceID, target);
    case 84:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 890
        UTIL_ASSERT_MSG(FALSE, "CGameEffectResistMagicFire game effect not supported in Icewind II (-rjf)");
    case 85:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 890
        UTIL_ASSERT_MSG(FALSE, "CGameEffectResistMagicCold game effect not supported in Icewind II (-rjf)");
    case CGAMEEFFECT_RESISTSLASHING:
        return new CGameEffectResistSlashing(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTCRUSHING:
        return new CGameEffectResistCrushing(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTPIERCING:
        return new CGameEffectResistPiercing(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTMISSILE:
        return new CGameEffectResistMissile(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLLOCKPICKING:
        return new CGameEffectSkillLockPicking(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLTRAPS:
        return new CGameEffectSkillTraps(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLPICKPOCKET:
        return new CGameEffectSkillPickPocket(effect, source, sourceID, target);
    case CGAMEEFFECT_FATIGUE:
        return new CGameEffectFatigue(effect, source, sourceID, target);
    case CGAMEEFFECT_INTOXICATION:
        return new CGameEffectIntoxication(effect, source, sourceID, target);
    case CGAMEEFFECT_SKILLTRACKING:
        return new CGameEffectSkillTracking(effect, source, sourceID, target);
    case CGAMEEFFECT_LEVEL:
        return new CGameEffectLevel(effect, source, sourceID, target);
    case CGAMEEFFECT_STREXTRA:
        return new CGameEffectSTRExtra(effect, source, sourceID, target);
    case CGAMEEFFECT_REGENERATION:
        return new CGameEffectRegeneration(effect, source, sourceID, target);
    case CGAMEEFFECT_DURATIONCASTING:
        return new CGameEffectDurationCasting(effect, source, sourceID, target);
    case CGAMEEFFECT_PROTECTIONFROMCREATURE:
        return new CGameEffectProtectionFromCreature(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYTOEFFECT:
        return new CGameEffectImmunityToEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYTOSPELLLEVEL:
        return new CGameEffectImmunityToSpellLevel(effect, source, sourceID, target);
    case CGAMEEFFECT_NAME:
        return new CGameEffectName(effect, source, sourceID, target);
    case CGAMEEFFECT_XP:
        return new CGameEffectXP(effect, source, sourceID, target);
    case CGAMEEFFECT_GOLD:
        return new CGameEffectGold(effect, source, sourceID, target);
    case CGAMEEFFECT_MORALBREAK:
        return new CGameEffectMoralBreak(effect, source, sourceID, target);
    case CGAMEEFFECT_PORTRAIT:
        return new CGameEffectPortrait(effect, source, sourceID, target);
    case CGAMEEFFECT_REPUTATION:
        return new CGameEffectReputation(effect, source, sourceID, target);
    case CGAMEEFFECT_HOLDCREATURE:
        return new CGameEffectHoldCreature(effect, source, sourceID, target);
    case CGAMEEFFECT_RETREATFROM:
        return new CGameEffectRetreatFrom(effect, source, sourceID, target);
    case CGAMEEFFECT_CREATEWEAPON:
        return new CGameEffectCreateWeapon(effect, source, sourceID, target);
    case CGAMEEFFECT_DESTROYWEAPON:
        return new CGameEffectDestroyWeapon(effect, source, sourceID, target);
    case CGAMEEFFECT_EQUIPWEAPON:
        return new CGameEffectEquipWeapon(effect, source, sourceID, target);
    case CGAMEEFFECT_DITHER:
        return new CGameEffectDither(effect, source, sourceID, target);
    case 115:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 988
        UTIL_ASSERT_MSG(FALSE, "CGameEffectDetectAlignment game effect not supported in Icewind II (-rjf)");
    case CGAMEEFFECT_DISPELINVISIBLE:
        return new CGameEffectDispelInvisible(effect, source, sourceID, target);
    case CGAMEEFFECT_SHOWAREA:
        return new CGameEffectShowArea(effect, source, sourceID, target);
    case CGAMEEFFECT_SHOWCREATURES:
        return new CGameEffectShowCreatures(effect, source, sourceID, target);
    case CGAMEEFFECT_MIRRORIMAGE:
        return new CGameEffectMirrorImage(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNETOWEAPON:
        return new CGameEffectImmuneToWeapon(effect, source, sourceID, target);
    case CGAMEEFFECT_VISUALANIMATIONEFFECT:
        return new CGameEffectVisualAnimationEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_CREATEITEM:
        return new CGameEffectCreateItem(effect, source, sourceID, target);
    case CGAMEEFFECT_DESTROYITEM:
        return new CGameEffectDestroyItem(effect, source, sourceID, target);
    case CGAMEEFFECT_TELEPORT:
        return new CGameEffectTeleport(effect, source, sourceID, target);
    case CGAMEEFFECT_KNOCK:
        return new CGameEffectKnock(effect, source, sourceID, target);
    case CGAMEEFFECT_MOVEMENTRATE_126:
        return new CGameEffectMovementRate(effect, source, sourceID, target);
    case 127:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 1025
        UTIL_ASSERT_MSG(FALSE, "CGameEffectSummon game effect not supported in Icewind II (-rjf)");
    case CGAMEEFFECT_RANDOMSUMMON:
        return new CGameEffectRandomSummon(effect, source, sourceID, target);
    case CGAMEEFFECT_CONFUSION:
        return new CGameEffectConfusion(effect, source, sourceID, target);
    case CGAMEEFFECT_NON_CUMULATIVEAID:
        return new CGameEffectNon_CumulativeAid(effect, source, sourceID, target);
    case CGAMEEFFECT_NON_CUMULATIVECHANT:
        return new CGameEffectNon_CumulativeChant(effect, source, sourceID, target);
    case CGAMEEFFECT_NON_CUMULATIVEDRAWUPONHOLYMIGHT:
        return new CGameEffectNon_CumulativeDrawUponHolyMight(effect, source, sourceID, target);
    case CGAMEEFFECT_NON_CUMULATIVELUCK:
        return new CGameEffectNon_CumulativeLuck(effect, source, sourceID, target);
    case CGAMEEFFECT_PETRIFICATION:
        return new CGameEffectPetrification(effect, source, sourceID, target);
    case CGAMEEFFECT_POLYMORPH:
        return new CGameEffectPolymorph(effect, source, sourceID, target);
    case CGAMEEFFECT_FORCEVISIBLE:
        return new CGameEffectForceVisible(effect, source, sourceID, target);
    case 137:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 1056
        UTIL_ASSERT_MSG(FALSE, "CGameEffectNon_CumulativeChantBad game effect not supported in Icewind II (-rjf)");
    case CGAMEEFFECT_SETSEQUENCE:
        return new CGameEffectSetSequence(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPLAYSTRING:
        return new CGameEffectDisplayString(effect, source, sourceID, target);
    case CGAMEEFFECT_CASTINGGLOW:
        return new CGameEffectCastingGlow(effect, source, sourceID, target);
    case CGAMEEFFECT_VISUALSPELLHIT:
        return new CGameEffectVisualSpellHit(effect, source, sourceID, target);
    case CGAMEEFFECT_PORTRAITICON:
        return new CGameEffectPortraitIcon(effect, source, sourceID, target);
    case CGAMEEFFECT_REPLACEITEM:
        return new CGameEffectReplaceItem(effect, source, sourceID, target);
    case CGAMEEFFECT_DISABLEBUTTON:
        return new CGameEffectDisableButton(effect, source, sourceID, target);
    case CGAMEEFFECT_DISABLESPELLTYPE:
        return new CGameEffectDisableSpellType(effect, source, sourceID, target);
    case CGAMEEFFECT_CASTSPELL:
        return new CGameEffectCastSpell(effect, source, sourceID, target);
    case CGAMEEFFECT_LEARNSPELL:
        return new CGameEffectLearnSpell(effect, source, sourceID, target);
    case CGAMEEFFECT_CASTSPELLPOINT:
        return new CGameEffectCastSpellPoint(effect, source, sourceID, target);
    case CGAMEEFFECT_IDENTIFY:
        return new CGameEffectIdentify(effect, source, sourceID, target);
    case CGAMEEFFECT_DETECTTRAPS:
        return new CGameEffectDetectTraps(effect, source, sourceID, target);
    case CGAMEEFFECT_REPLACESELF:
        return new CGameEffectReplaceSelf(effect, source, sourceID, target);
    case CGAMEEFFECT_PLAYMOVIE:
        return new CGameEffectPlayMovie(effect, source, sourceID, target);
    case CGAMEEFFECT_SANCTUARY:
        return new CGameEffectSanctuary(effect, source, sourceID, target);
    case CGAMEEFFECT_ENTANGLE:
        return new CGameEffectEntangle(effect, source, sourceID, target);
    case 155:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 818
        UTIL_ASSERT_MSG(FALSE, "CGameEffectMinorGlobe game effect not supported in Icewind II (-rjf)");
    case 156:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
        // __LINE__: 1822
        UTIL_ASSERT_MSG(FALSE, "CGameEffectShieldGlobe game effect not supported in Icewind II (-rjf)");
    case CGAMEEFFECT_WEBHOLD:
        return new CGameEffectWebHold(effect, source, sourceID, target);
    case CGAMEEFFECT_GREASEPOOL:
        return new CGameEffectGreasePool(effect, source, sourceID, target);
    case CGAMEEFFECT_MIRRORIMAGERUN:
        return new CGameEffectMirrorImageRun(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELSANCTUARY:
        return new CGameEffectDispelSanctuary(effect, source, sourceID, target);
    case CGAMEEFFECT_REMOVEPANIC:
        return new CGameEffectRemovePanic(effect, source, sourceID, target);
    case CGAMEEFFECT_REMOVEHOLD:
        return new CGameEffectRemoveHold(effect, source, sourceID, target);
    case CGAMEEFFECT_RESTOREMOVEMENTRATE:
        return new CGameEffectRestoreMovementRate(effect, source, sourceID, target);
    case CGAMEEFFECT_REMOVEINTOXICATION:
        return new CGameEffectRemoveIntoxication(effect, source, sourceID, target);
    case CGAMEEFFECT_PAUSECASTER:
        return new CGameEffectPauseCaster(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTANCETOMAGIC:
        return new CGameEffectResistanceToMagic(effect, source, sourceID, target);
    case CGAMEEFFECT_MISSILETHAC0BONUS:
        return new CGameEffectMissileTHAC0Bonus(effect, source, sourceID, target);
    case CGAMEEFFECT_DESTROYSELF:
        return new CGameEffectDestroySelf(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYTOPORTRAITICON:
        return new CGameEffectImmunityToPortraitIcon(effect, source, sourceID, target);
    case CGAMEEFFECT_DAMAGEVISUALEFFECT:
        return new CGameEffectDamageVisualEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_ADDINNATEABILITY:
        return new CGameEffectAddInnateAbility(effect, source, sourceID, target);
    case CGAMEEFFECT_REMOVEINNATEABILITY:
        return new CGameEffectRemoveInnateAbility(effect, source, sourceID, target);
    case CGAMEEFFECT_RESISTANCETOPOISON:
        return new CGameEffectResistanceToPoison(effect, source, sourceID, target);
    case CGAMEEFFECT_PLAYSOUND:
        return new CGameEffectPlaySound(effect, source, sourceID, target);
    case CGAMEEFFECT_HOLDCREATURESPELL_175:
        return new CGameEffectHoldCreatureSpell(effect, source, sourceID, target);
    case CGAMEEFFECT_MOVEMENTRATE_176:
        return new CGameEffectMovementRate(effect, source, sourceID, target);
    case CGAMEEFFECT_APPLYEFFECT:
        return new CGameEffectApplyEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_SELECTIVETOHITBONUS:
        return new CGameEffectSelectiveToHitBonus(effect, source, sourceID, target);
    case CGAMEEFFECT_SELECTDAMAGEBONUS:
        return new CGameEffectSelectDamageBonus(effect, source, sourceID, target);
    case CGAMEEFFECT_RESTRICTEQUIPITEM:
        return new CGameEffectRestrictEquipItem(effect, source, sourceID, target);
    case CGAMEEFFECT_RESTRICTEQUIPITEMTYPE:
        return new CGameEffectRestrictEquipItemType(effect, source, sourceID, target);
    case CGAMEEFFECT_APPLYEFFECTEQUIPITEM:
        return new CGameEffectApplyEffectEquipItem(effect, source, sourceID, target);
    case CGAMEEFFECT_APPLYEFFECTEQUIPITEMTYPE:
        return new CGameEffectApplyEffectEquipItemType(effect, source, sourceID, target);
    case CGAMEEFFECT_SETDONOJUMP:
        return new CGameEffectSetDoNoJump(effect, source, sourceID, target);
    case CGAMEEFFECT_HOLDCREATURESPELL_185:
        return new CGameEffectHoldCreatureSpell(effect, source, sourceID, target);
    case CGAMEEFFECT_JUMPTOAREA:
        return new CGameEffectJumpToArea(effect, source, sourceID, target);
    case CGAMEEFFECT_SETLOCALVARIABLE:
        return new CGameEffectSetLocalVariable(effect, source, sourceID, target);
    case CGAMEEFFECT_AURACLEANSING:
        return new CGameEffectAuraCleansing(effect, source, sourceID, target);
    case CGAMEEFFECT_MENTALSPEED:
        return new CGameEffectMentalSpeed(effect, source, sourceID, target);
    case CGAMEEFFECT_PHYSICALSPEED:
        return new CGameEffectPhysicalSpeed(effect, source, sourceID, target);
    case CGAMEEFFECT_CASTINGLEVELBONUS:
        return new CGameEffectCastingLevelBonus(effect, source, sourceID, target);
    case CGAMEEFFECT_FINDFAMILIAR:
        return new CGameEffectFindFamiliar(effect, source, sourceID, target);
    case CGAMEEFFECT_SEEINVISIBLE:
        return new CGameEffectSeeInvisible(effect, source, sourceID, target);
    case CGAMEEFFECT_IGNOREDIALOGPAUSE:
        return new CGameEffectIgnoreDialogPause(effect, source, sourceID, target);
    case CGAMEEFFECT_HITPOINTSONDEATH:
        return new CGameEffectHitPointsOnDeath(effect, source, sourceID, target);
    case CGAMEEFFECT_FAMILIARBLOCK:
        return new CGameEffectFamiliarBlock(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCEPROJECTILE:
        return new CGameEffectBounceProjectile(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCEEFFECT:
        return new CGameEffectBounceEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCELEVEL:
        return new CGameEffectBounceLevel(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCELEVELDECREMENT:
        return new CGameEffectBounceLevelDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYLEVELDECREMENT:
        return new CGameEffectImmunityLevelDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCESCHOOL:
        return new CGameEffectBounceSchool(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCESECONDARYTYPE:
        return new CGameEffectBounceSecondaryType(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYSCHOOL:
        return new CGameEffectImmunitySchool(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYSECONDARYTYPE:
        return new CGameEffectImmunitySecondaryType(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYSPELL:
        return new CGameEffectImmunitySpell(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCESPELL:
        return new CGameEffectBounceSpell(effect, source, sourceID, target);
    case CGAMEEFFECT_MINHITPOINTS:
        return new CGameEffectMinHitPoints(effect, source, sourceID, target);
    case CGAMEEFFECT_POWERWORDKILL:
        return new CGameEffectPowerWordKill(effect, source, sourceID, target);
    case CGAMEEFFECT_POWERWORDSTUN:
        return new CGameEffectPowerWordStun(effect, source, sourceID, target);
    case CGAMEEFFECT_IMPRISONMENT:
        return new CGameEffectImprisonment(effect, source, sourceID, target);
    case CGAMEEFFECT_FREEDOM:
        return new CGameEffectFreedom(effect, source, sourceID, target);
    case CGAMEEFFECT_MAZE:
        return new CGameEffectMaze(effect, source, sourceID, target);
    case CGAMEEFFECT_SECONDARYCASTLIST:
        return new CGameEffectSecondaryCastList(effect, source, sourceID, target);
    case CGAMEEFFECT_VISUALEFFECT:
        return new CGameEffectVisualEffect(effect, source, sourceID, target);
    case CGAMEEFFECT_LEVELDRAIN:
        return new CGameEffectLevelDrain(effect, source, sourceID, target);
    case CGAMEEFFECT_POWERWORDSLEEP:
        return new CGameEffectPowerWordSleep(effect, source, sourceID, target);
    case CGAMEEFFECT_STONESKINS:
        return new CGameEffectStoneSkins(effect, source, sourceID, target);
    case CGAMEEFFECT_PROTECTIONCIRCLE:
        return new CGameEffectProtectionCircle(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELSCHOOL:
        return new CGameEffectDispelSchool(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELSECONDARYTYPE:
        return new CGameEffectDispelSecondaryType(effect, source, sourceID, target);
    case CGAMEEFFECT_RANDOMTELEPORT:
        return new CGameEffectRandomTeleport(effect, source, sourceID, target);
    case CGAMEEFFECT_IMMUNITYSCHOOLDECREMENT:
        return new CGameEffectImmunitySchoolDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_LEVELRESTORATION:
        return new CGameEffectLevelRestoration(effect, source, sourceID, target);
    case CGAMEEFFECT_REVEALMAGIC:
        return new CGameEffectRevealMagic(effect, source, sourceID, target);
    case CGAMEEFFECT_SECONDARYTYPEDECREMENT:
        return new CGameEffectSecondaryTypeDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCESCHOOLDECREMENT:
        return new CGameEffectBounceSchoolDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_BOUNCESECONDARYTYPEDECREMENT:
        return new CGameEffectBounceSecondaryTypeDecrement(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELSCHOOLONE:
        return new CGameEffectDispelSchoolOne(effect, source, sourceID, target);
    case CGAMEEFFECT_DISPELSECONDARYTYPEONE:
        return new CGameEffectDispelSecondaryTypeOne(effect, source, sourceID, target);
    case CGAMEEFFECT_TIMESTOP:
        return new CGameEffectTimeStop(effect, source, sourceID, target);
    }

    // TODO: Incomplete.

    CString sError;
    sError.Format("Unknown effect id:  %d", effect->effectID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameEffect.cpp
    // __LINE__: 1744
    UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
}

// 0x48C310
CGameEffect::CGameEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target, BOOL usesDice)
{
    m_effectID = effect->effectID;
    m_targetType = effect->targetType;
    m_spellLevel = effect->spellLevel;
    m_effectAmount = effect->effectAmount;
    m_dwFlags = effect->dwFlags;

    if ((effect->durationType & 0x100) != 0) {
        m_flags |= 0x1;
    }

    if ((effect->durationType & 0x200) != 0) {
        m_flags |= 0x2;
    }

    m_durationType = effect->durationType & ~0x300;
    m_duration = effect->duration;
    m_probabilityUpper = effect->probabilityUpper;
    m_probabilityLower = effect->probabilityLower;

    m_res = effect->res;

    if (usesDice) {
        m_numDice = effect->numDice;
        m_diceSize = effect->diceSize;
    } else {
        m_minLevel = effect->diceSize;
        m_maxLevel = effect->numDice;
    }

    m_savingThrow = effect->savingThrow;
    m_saveMod = effect->saveMod;
    m_special = effect->special;

    m_source = source;
    m_sourceID = sourceID;
    m_target = target;
}

// 0x499B10
CGameEffect::~CGameEffect()
{
}

// 0x452E20
CGameEffect* CGameEffect::Copy()
{
    // __FILE__: .\Include\CGameEffect.h
    // __LINE__: 496
    UTIL_ASSERT(FALSE);
}

// 0x452E40
BOOL CGameEffect::ApplyEffect(CGameSprite* pSprite)
{
    // __FILE__: .\Include\CGameEffect.h
    // __LINE__: 565
    UTIL_ASSERT(FALSE);
}

// 0x78E6E0
BOOL CGameEffect::UsesDice()
{
    return FALSE;
}

// 0x4A4B00
ITEM_EFFECT* CGameEffect::GetItemEffect()
{
    ITEM_EFFECT* effect = new ITEM_EFFECT;
    effect->effectID = static_cast<WORD>(m_effectID);
    effect->targetType = static_cast<BYTE>(m_targetType);
    effect->spellLevel = static_cast<BYTE>(m_spellLevel);
    effect->effectAmount = m_effectAmount;
    effect->dwFlags = m_dwFlags;
    effect->durationType = static_cast<WORD>(m_durationType);

    if ((m_flags & 0x1) != 0) {
        effect->durationType |= 0x100;
    }

    if ((m_flags & 0x2) != 0) {
        effect->durationType |= 0x200;
    }

    effect->duration = m_duration;
    effect->probabilityUpper = static_cast<BYTE>(m_probabilityUpper);
    effect->probabilityLower = static_cast<BYTE>(m_probabilityLower);
    m_res.GetResRef(effect->res);

    if (UsesDice()) {
        effect->numDice = m_numDice;
        effect->diceSize = m_diceSize;
    } else {
        effect->numDice = m_maxLevel;
        effect->diceSize = m_minLevel;
    }

    effect->savingThrow = m_savingThrow;
    effect->saveMod = m_saveMod;
    effect->special = m_special;

    return effect;
}

// 0x48C670
void CGameEffect::CopyFromBase(CGameEffectBase* pBase)
{
    m_version = pBase->m_version;
    m_effectID = pBase->m_effectID;
    m_targetType = pBase->m_targetType;
    m_spellLevel = pBase->m_spellLevel;
    m_effectAmount = pBase->m_effectAmount;
    m_dwFlags = pBase->m_dwFlags;
    m_durationType = pBase->m_durationType;
    m_duration = pBase->m_duration;
    m_probabilityUpper = pBase->m_probabilityUpper;
    m_probabilityLower = pBase->m_probabilityLower;
    m_res = pBase->m_res;
    m_numDice = pBase->m_numDice;
    m_diceSize = pBase->m_diceSize;
    m_savingThrow = pBase->m_savingThrow;
    m_saveMod = pBase->m_saveMod;
    m_special = pBase->m_special;
    field_44 = pBase->field_44;
    field_48 = pBase->field_48;
    m_minLevel = pBase->m_minLevel;
    m_maxLevel = pBase->m_maxLevel;
    m_flags = pBase->m_flags;
    m_effectAmount2 = pBase->m_effectAmount2;
    m_effectAmount3 = pBase->m_effectAmount3;
    m_effectAmount4 = pBase->m_effectAmount4;
    m_effectAmount5 = pBase->m_effectAmount5;
    m_res2 = pBase->m_res2;
    m_res3 = pBase->m_res3;
    m_source = pBase->m_source;
    m_target = pBase->m_target;
    m_sourceType = pBase->m_sourceType;
    m_sourceRes = pBase->m_sourceRes;
    m_sourceFlags = pBase->m_sourceFlags;
    m_projectileType = pBase->m_projectileType;
    m_slotNum = pBase->m_slotNum;
    memcpy(m_scriptName, pBase->m_scriptName, 32);
    m_casterLevel = pBase->m_casterLevel;
    m_firstCall = pBase->m_firstCall;
    m_secondaryType = pBase->m_secondaryType;
}

// 0x4933E0
void CGameEffect::SetEffectID(WORD effectID)
{
    m_effectID = effectID;
}

// 0x4933F0
void CGameEffect::SetDWFlags(DWORD dwFlags)
{
    m_dwFlags = dwFlags;
}

// 0x493400
void CGameEffect::sub_493400(BOOL a1)
{
    if (a1) {
        m_flags |= 0x2;
    } else {
        m_flags &= ~0x2;
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAC::CGameEffectAC(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493420
CGameEffect* CGameEffectAC::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAC* copy = new CGameEffectAC(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAttackNo::CGameEffectAttackNo(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4934D0
CGameEffect* CGameEffectAttackNo::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAttackNo* copy = new CGameEffectAttackNo(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAwaken::CGameEffectAwaken(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493580
CGameEffect* CGameEffectAwaken::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAwaken* copy = new CGameEffectAwaken(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBerserk::CGameEffectBerserk(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493630
CGameEffect* CGameEffectBerserk::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBerserk* copy = new CGameEffectBerserk(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCalm::CGameEffectCalm(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4937D0
CGameEffect* CGameEffectCalm::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCalm* copy = new CGameEffectCalm(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCharm::CGameEffectCharm(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4938C0
CGameEffect* CGameEffectCharm::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCharm* copy = new CGameEffectCharm(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCHR::CGameEffectCHR(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493A60
CGameEffect* CGameEffectCHR::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCHR* copy = new CGameEffectCHR(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectColorChange::CGameEffectColorChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493B10
CGameEffect* CGameEffectColorChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectColorChange* copy = new CGameEffectColorChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectColorGlowSolid::CGameEffectColorGlowSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493BC0
CGameEffect* CGameEffectColorGlowSolid::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectColorGlowSolid* copy = new CGameEffectColorGlowSolid(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectColorGlowPulse::CGameEffectColorGlowPulse(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493C70
CGameEffect* CGameEffectColorGlowPulse::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectColorGlowPulse* copy = new CGameEffectColorGlowPulse(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCON::CGameEffectCON(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493F30
CGameEffect* CGameEffectCON::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCON* copy = new CGameEffectCON(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCurePoison::CGameEffectCurePoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493FE0
CGameEffect* CGameEffectCurePoison::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCurePoison* copy = new CGameEffectCurePoison(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDamage::CGameEffectDamage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
    if (m_special == 0) {
        m_special = -1;
    }
}

// 0x494090
CGameEffect* CGameEffectDamage::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDamage* copy = new CGameEffectDamage(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDeath::CGameEffectDeath(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
    field_18C = 0;
}

// 0x452E70
CGameEffect* CGameEffectDeath::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDeath* copy = new CGameEffectDeath(effect, m_source, m_sourceID, m_target);
    copy->field_18C = field_18C;
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDefrost::CGameEffectDefrost(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494190
CGameEffect* CGameEffectDefrost::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDefrost* copy = new CGameEffectDefrost(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDEX::CGameEffectDEX(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494240
CGameEffect* CGameEffectDEX::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDEX* copy = new CGameEffectDEX(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHaste::CGameEffectHaste(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4942F0
CGameEffect* CGameEffectHaste::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHaste* copy = new CGameEffectHaste(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHeal::CGameEffectHeal(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x4943A0
CGameEffect* CGameEffectHeal::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHeal* copy = new CGameEffectHeal(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHitPoints::CGameEffectHitPoints(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x494450
CGameEffect* CGameEffectHitPoints::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHitPoints* copy = new CGameEffectHitPoints(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectINT::CGameEffectINT(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494500
CGameEffect* CGameEffectINT::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectINT* copy = new CGameEffectINT(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectInvisible::CGameEffectInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4945B0
CGameEffect* CGameEffectInvisible::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectInvisible* copy = new CGameEffectInvisible(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectLore::CGameEffectLore(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494660
CGameEffect* CGameEffectLore::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLore* copy = new CGameEffectLore(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectLuck::CGameEffectLuck(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4947C0
CGameEffect* CGameEffectLuck::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLuck* copy = new CGameEffectLuck(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMorale::CGameEffectMorale(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494870
CGameEffect* CGameEffectMorale::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMorale* copy = new CGameEffectMorale(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPanic::CGameEffectPanic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494960
CGameEffect* CGameEffectPanic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPanic* copy = new CGameEffectPanic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPoison::CGameEffectPoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494A10
CGameEffect* CGameEffectPoison::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPoison* copy = new CGameEffectPoison(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRemoveCurse::CGameEffectRemoveCurse(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494AC0
CGameEffect* CGameEffectRemoveCurse::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRemoveCurse* copy = new CGameEffectRemoveCurse(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistAcid::CGameEffectResistAcid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494B70
CGameEffect* CGameEffectResistAcid::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistAcid* copy = new CGameEffectResistAcid(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistCold::CGameEffectResistCold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494C20
CGameEffect* CGameEffectResistCold::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistCold* copy = new CGameEffectResistCold(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistElectricity::CGameEffectResistElectricity(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494CD0
CGameEffect* CGameEffectResistElectricity::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistElectricity* copy = new CGameEffectResistElectricity(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistFire::CGameEffectResistFire(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494D80
CGameEffect* CGameEffectResistFire::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistFire* copy = new CGameEffectResistFire(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistMagic::CGameEffectResistMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494E30
CGameEffect* CGameEffectResistMagic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistMagic* copy = new CGameEffectResistMagic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResurrect::CGameEffectResurrect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494EE0
CGameEffect* CGameEffectResurrect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResurrect* copy = new CGameEffectResurrect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSaveVsFortitude::CGameEffectSaveVsFortitude(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494F90
CGameEffect* CGameEffectSaveVsFortitude::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSaveVsFortitude* copy = new CGameEffectSaveVsFortitude(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSaveVsRelfex::CGameEffectSaveVsRelfex(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495040
CGameEffect* CGameEffectSaveVsRelfex::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSaveVsRelfex* copy = new CGameEffectSaveVsRelfex(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSaveVsWill::CGameEffectSaveVsWill(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4950F0
CGameEffect* CGameEffectSaveVsWill::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSaveVsWill* copy = new CGameEffectSaveVsWill(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSilence::CGameEffectSilence(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4951A0
CGameEffect* CGameEffectSilence::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSilence* copy = new CGameEffectSilence(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSleep::CGameEffectSleep(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495290
CGameEffect* CGameEffectSleep::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSleep* copy = new CGameEffectSleep(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSlow::CGameEffectSlow(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495340
CGameEffect* CGameEffectSlow::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSlow* copy = new CGameEffectSlow(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSparkle::CGameEffectSparkle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4953F0
CGameEffect* CGameEffectSparkle::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSparkle* copy = new CGameEffectSparkle(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSpellMemorizationMage::CGameEffectSpellMemorizationMage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4954A0
CGameEffect* CGameEffectSpellMemorizationMage::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSpellMemorizationMage* copy = new CGameEffectSpellMemorizationMage(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectStoneToFlesh::CGameEffectStoneToFlesh(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495600
CGameEffect* CGameEffectStoneToFlesh::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectStoneToFlesh* copy = new CGameEffectStoneToFlesh(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSTR::CGameEffectSTR(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4956B0
CGameEffect* CGameEffectSTR::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSTR* copy = new CGameEffectSTR(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectStun::CGameEffectStun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495760
CGameEffect* CGameEffectStun::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectStun* copy = new CGameEffectStun(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectUnstun::CGameEffectUnstun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495810
CGameEffect* CGameEffectUnstun::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectUnstun* copy = new CGameEffectUnstun(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectVisible::CGameEffectVisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4958C0
CGameEffect* CGameEffectVisible::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectVisible* copy = new CGameEffectVisible(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectVocalize::CGameEffectVocalize(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495970
CGameEffect* CGameEffectVocalize::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectVocalize* copy = new CGameEffectVocalize(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectWIS::CGameEffectWIS(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495A20
CGameEffect* CGameEffectWIS::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectWIS* copy = new CGameEffectWIS(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSingleColorPulseAll::CGameEffectSingleColorPulseAll(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493E80
CGameEffect* CGameEffectSingleColorPulseAll::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSingleColorPulseAll* copy = new CGameEffectSingleColorPulseAll(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectColorTintSolid::CGameEffectColorTintSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493D20
CGameEffect* CGameEffectColorTintSolid::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectColorTintSolid* copy = new CGameEffectColorTintSolid(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectColorLightSolid::CGameEffectColorLightSolid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x493DD0
CGameEffect* CGameEffectColorLightSolid::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectColorLightSolid* copy = new CGameEffectColorLightSolid(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAnimationChange::CGameEffectAnimationChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495AD0
CGameEffect* CGameEffectAnimationChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAnimationChange* copy = new CGameEffectAnimationChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBaseAttackBonus::CGameEffectBaseAttackBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495BB0
CGameEffect* CGameEffectBaseAttackBonus::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBaseAttackBonus* copy = new CGameEffectBaseAttackBonus(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSlay::CGameEffectSlay(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495C60
CGameEffect* CGameEffectSlay::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSlay* copy = new CGameEffectSlay(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAlignmentReversal::CGameEffectAlignmentReversal(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495D10
CGameEffect* CGameEffectAlignmentReversal::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAlignmentReversal* copy = new CGameEffectAlignmentReversal(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAlignmentChange::CGameEffectAlignmentChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495DC0
CGameEffect* CGameEffectAlignmentChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAlignmentChange* copy = new CGameEffectAlignmentChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDispelEffects::CGameEffectDispelEffects(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495E70
CGameEffect* CGameEffectDispelEffects::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelEffects* copy = new CGameEffectDispelEffects(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillStealth::CGameEffectSkillStealth(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495F20
CGameEffect* CGameEffectSkillStealth::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillStealth* copy = new CGameEffectSkillStealth(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCastingFailure::CGameEffectCastingFailure(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496080
CGameEffect* CGameEffectCastingFailure::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCastingFailure* copy = new CGameEffectCastingFailure(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillAlchemy::CGameEffectSkillAlchemy(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x494710
CGameEffect* CGameEffectSkillAlchemy::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillAlchemy* copy = new CGameEffectSkillAlchemy(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSpellMemoizationCleric::CGameEffectSpellMemoizationCleric(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x495550
CGameEffect* CGameEffectSpellMemoizationCleric::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSpellMemoizationCleric* copy = new CGameEffectSpellMemoizationCleric(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectInfravision::CGameEffectInfravision(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496130
CGameEffect* CGameEffectInfravision::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectInfravision* copy = new CGameEffectInfravision(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectInfravisionOff::CGameEffectInfravisionOff(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4961E0
CGameEffect* CGameEffectInfravisionOff::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectInfravisionOff* copy = new CGameEffectInfravisionOff(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBlur::CGameEffectBlur(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496290
CGameEffect* CGameEffectBlur::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBlur* copy = new CGameEffectBlur(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectTranslucent::CGameEffectTranslucent(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496600
CGameEffect* CGameEffectTranslucent::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectTranslucent* copy = new CGameEffectTranslucent(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x55F5E0
CGameEffectSummon::CGameEffectSummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
    field_18C = 0;
    field_190 = 0;
}

// 0x55F620
CGameEffect* CGameEffectSummon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSummon* copy = new CGameEffectSummon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillUnsummon::CGameEffectSkillUnsummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4966B0
CGameEffect* CGameEffectSkillUnsummon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillUnsummon* copy = new CGameEffectSkillUnsummon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectNonDetection::CGameEffectNonDetection(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496760
CGameEffect* CGameEffectNonDetection::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectNonDetection* copy = new CGameEffectNonDetection(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectEndNonDetection::CGameEffectEndNonDetection(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496810
CGameEffect* CGameEffectEndNonDetection::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectEndNonDetection* copy = new CGameEffectEndNonDetection(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSexChange::CGameEffectSexChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4968C0
CGameEffect* CGameEffectSexChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSexChange* copy = new CGameEffectSexChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAIChange::CGameEffectAIChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496970
CGameEffect* CGameEffectAIChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAIChange* copy = new CGameEffectAIChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDamageMod::CGameEffectDamageMod(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496A20
CGameEffect* CGameEffectDamageMod::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDamageMod* copy = new CGameEffectDamageMod(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBlindness::CGameEffectBlindness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496AD0
CGameEffect* CGameEffectBlindness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBlindness* copy = new CGameEffectBlindness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCureBlindness::CGameEffectCureBlindness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496C30
CGameEffect* CGameEffectCureBlindness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCureBlindness* copy = new CGameEffectCureBlindness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectFeebleMindedness::CGameEffectFeebleMindedness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496CE0
CGameEffect* CGameEffectFeebleMindedness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectFeebleMindedness* copy = new CGameEffectFeebleMindedness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCureFeebleMindedness::CGameEffectCureFeebleMindedness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496D90
CGameEffect* CGameEffectCureFeebleMindedness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCureFeebleMindedness* copy = new CGameEffectCureFeebleMindedness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDisease::CGameEffectDisease(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496E40
CGameEffect* CGameEffectDisease::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDisease* copy = new CGameEffectDisease(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCureDisease::CGameEffectCureDisease(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496EF0
CGameEffect* CGameEffectCureDisease::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCureDisease* copy = new CGameEffectCureDisease(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDeafness::CGameEffectDeafness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496FA0
CGameEffect* CGameEffectDeafness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDeafness* copy = new CGameEffectDeafness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCureDeafness::CGameEffectCureDeafness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497050
CGameEffect* CGameEffectCureDeafness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCureDeafness* copy = new CGameEffectCureDeafness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSetAIScript::CGameEffectSetAIScript(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497100
CGameEffect* CGameEffectSetAIScript::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSetAIScript* copy = new CGameEffectSetAIScript(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunityToProjectile::CGameEffectImmunityToProjectile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4971B0
CGameEffect* CGameEffectImmunityToProjectile::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunityToProjectile* copy = new CGameEffectImmunityToProjectile(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistSlashing::CGameEffectResistSlashing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497260
CGameEffect* CGameEffectResistSlashing::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistSlashing* copy = new CGameEffectResistSlashing(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistCrushing::CGameEffectResistCrushing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497310
CGameEffect* CGameEffectResistCrushing::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistCrushing* copy = new CGameEffectResistCrushing(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistPiercing::CGameEffectResistPiercing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4973C0
CGameEffect* CGameEffectResistPiercing::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistPiercing* copy = new CGameEffectResistPiercing(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistMissile::CGameEffectResistMissile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497470
CGameEffect* CGameEffectResistMissile::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistMissile* copy = new CGameEffectResistMissile(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillLockPicking::CGameEffectSkillLockPicking(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497520
CGameEffect* CGameEffectSkillLockPicking::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillLockPicking* copy = new CGameEffectSkillLockPicking(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillTraps::CGameEffectSkillTraps(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4975D0
CGameEffect* CGameEffectSkillTraps::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillTraps* copy = new CGameEffectSkillTraps(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillPickPocket::CGameEffectSkillPickPocket(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497680
CGameEffect* CGameEffectSkillPickPocket::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillPickPocket* copy = new CGameEffectSkillPickPocket(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectFatigue::CGameEffectFatigue(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4977E0
CGameEffect* CGameEffectFatigue::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectFatigue* copy = new CGameEffectFatigue(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectIntoxication::CGameEffectIntoxication(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497890
CGameEffect* CGameEffectIntoxication::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectIntoxication* copy = new CGameEffectIntoxication(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSkillTracking::CGameEffectSkillTracking(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497940
CGameEffect* CGameEffectSkillTracking::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSkillTracking* copy = new CGameEffectSkillTracking(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectLevel::CGameEffectLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4979F0
CGameEffect* CGameEffectLevel::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLevel* copy = new CGameEffectLevel(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSTRExtra::CGameEffectSTRExtra(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497AA0
CGameEffect* CGameEffectSTRExtra::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSTRExtra* copy = new CGameEffectSTRExtra(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRegeneration::CGameEffectRegeneration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497B50
CGameEffect* CGameEffectRegeneration::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRegeneration* copy = new CGameEffectRegeneration(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDurationCasting::CGameEffectDurationCasting(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497C00
CGameEffect* CGameEffectDurationCasting::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDurationCasting* copy = new CGameEffectDurationCasting(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectProtectionFromCreature::CGameEffectProtectionFromCreature(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497CB0
CGameEffect* CGameEffectProtectionFromCreature::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectProtectionFromCreature* copy = new CGameEffectProtectionFromCreature(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunityToEffect::CGameEffectImmunityToEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497D60
CGameEffect* CGameEffectImmunityToEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunityToEffect* copy = new CGameEffectImmunityToEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunityToSpellLevel::CGameEffectImmunityToSpellLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497E10
CGameEffect* CGameEffectImmunityToSpellLevel::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunityToSpellLevel* copy = new CGameEffectImmunityToSpellLevel(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectName::CGameEffectName(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497EC0
CGameEffect* CGameEffectName::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectName* copy = new CGameEffectName(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectXP::CGameEffectXP(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x497F70
CGameEffect* CGameEffectXP::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectXP* copy = new CGameEffectXP(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectGold::CGameEffectGold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498020
CGameEffect* CGameEffectGold::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectGold* copy = new CGameEffectGold(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMoralBreak::CGameEffectMoralBreak(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4980D0
CGameEffect* CGameEffectMoralBreak::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMoralBreak* copy = new CGameEffectMoralBreak(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPortrait::CGameEffectPortrait(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498180
CGameEffect* CGameEffectPortrait::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPortrait* copy = new CGameEffectPortrait(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectReputation::CGameEffectReputation(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498230
CGameEffect* CGameEffectReputation::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectReputation* copy = new CGameEffectReputation(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHoldCreature::CGameEffectHoldCreature(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498320
CGameEffect* CGameEffectHoldCreature::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHoldCreature* copy = new CGameEffectHoldCreature(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRetreatFrom::CGameEffectRetreatFrom(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4983D0
CGameEffect* CGameEffectRetreatFrom::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRetreatFrom* copy = new CGameEffectRetreatFrom(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCreateWeapon::CGameEffectCreateWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498480
CGameEffect* CGameEffectCreateWeapon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCreateWeapon* copy = new CGameEffectCreateWeapon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDestroyWeapon::CGameEffectDestroyWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498530
CGameEffect* CGameEffectDestroyWeapon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDestroyWeapon* copy = new CGameEffectDestroyWeapon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectEquipWeapon::CGameEffectEquipWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4985E0
CGameEffect* CGameEffectEquipWeapon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectEquipWeapon* copy = new CGameEffectEquipWeapon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDither::CGameEffectDither(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498690
CGameEffect* CGameEffectDither::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDither* copy = new CGameEffectDither(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDispelInvisible::CGameEffectDispelInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498740
CGameEffect* CGameEffectDispelInvisible::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelInvisible* copy = new CGameEffectDispelInvisible(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectShowArea::CGameEffectShowArea(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4987F0
CGameEffect* CGameEffectShowArea::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectShowArea* copy = new CGameEffectShowArea(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectShowCreatures::CGameEffectShowCreatures(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4988A0
CGameEffect* CGameEffectShowCreatures::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectShowCreatures* copy = new CGameEffectShowCreatures(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMirrorImage::CGameEffectMirrorImage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498950
CGameEffect* CGameEffectMirrorImage::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMirrorImage* copy = new CGameEffectMirrorImage(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmuneToWeapon::CGameEffectImmuneToWeapon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498AB0
CGameEffect* CGameEffectImmuneToWeapon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmuneToWeapon* copy = new CGameEffectImmuneToWeapon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectVisualAnimationEffect::CGameEffectVisualAnimationEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498B60
CGameEffect* CGameEffectVisualAnimationEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectVisualAnimationEffect* copy = new CGameEffectVisualAnimationEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCreateItem::CGameEffectCreateItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498C10
CGameEffect* CGameEffectCreateItem::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCreateItem* copy = new CGameEffectCreateItem(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDestroyItem::CGameEffectDestroyItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498CC0
CGameEffect* CGameEffectDestroyItem::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDestroyItem* copy = new CGameEffectDestroyItem(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectTeleport::CGameEffectTeleport(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498D70
CGameEffect* CGameEffectTeleport::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectTeleport* copy = new CGameEffectTeleport(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectKnock::CGameEffectKnock(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498E20
CGameEffect* CGameEffectKnock::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectKnock* copy = new CGameEffectKnock(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMovementRate::CGameEffectMovementRate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498ED0
CGameEffect* CGameEffectMovementRate::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMovementRate* copy = new CGameEffectMovementRate(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRandomSummon::CGameEffectRandomSummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499380
CGameEffect* CGameEffectRandomSummon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRandomSummon* copy = new CGameEffectRandomSummon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectConfusion::CGameEffectConfusion(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499430
CGameEffect* CGameEffectConfusion::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectConfusion* copy = new CGameEffectConfusion(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectNon_CumulativeAid::CGameEffectNon_CumulativeAid(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4994E0
CGameEffect* CGameEffectNon_CumulativeAid::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectNon_CumulativeAid* copy = new CGameEffectNon_CumulativeAid(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectNon_CumulativeChant::CGameEffectNon_CumulativeChant(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499590
CGameEffect* CGameEffectNon_CumulativeChant::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectNon_CumulativeChant* copy = new CGameEffectNon_CumulativeChant(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectNon_CumulativeDrawUponHolyMight::CGameEffectNon_CumulativeDrawUponHolyMight(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499640
CGameEffect* CGameEffectNon_CumulativeDrawUponHolyMight::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectNon_CumulativeDrawUponHolyMight* copy = new CGameEffectNon_CumulativeDrawUponHolyMight(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectNon_CumulativeLuck::CGameEffectNon_CumulativeLuck(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4996F0
CGameEffect* CGameEffectNon_CumulativeLuck::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectNon_CumulativeLuck* copy = new CGameEffectNon_CumulativeLuck(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPetrification::CGameEffectPetrification(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4997A0
CGameEffect* CGameEffectPetrification::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPetrification* copy = new CGameEffectPetrification(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPolymorph::CGameEffectPolymorph(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499850
CGameEffect* CGameEffectPolymorph::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPolymorph* copy = new CGameEffectPolymorph(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectForceVisible::CGameEffectForceVisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499900
CGameEffect* CGameEffectForceVisible::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectForceVisible* copy = new CGameEffectForceVisible(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSetSequence::CGameEffectSetSequence(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4999B0
CGameEffect* CGameEffectSetSequence::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSetSequence* copy = new CGameEffectSetSequence(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDisplayString::CGameEffectDisplayString(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499A60
CGameEffect* CGameEffectDisplayString::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDisplayString* copy = new CGameEffectDisplayString(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCastingGlow::CGameEffectCastingGlow(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49DCA0
CGameEffect* CGameEffectCastingGlow::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCastingGlow* copy = new CGameEffectCastingGlow(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectVisualSpellHit::CGameEffectVisualSpellHit(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499B30
CGameEffect* CGameEffectVisualSpellHit::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectVisualSpellHit* copy = new CGameEffectVisualSpellHit(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPortraitIcon::CGameEffectPortraitIcon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499C00
CGameEffect* CGameEffectPortraitIcon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPortraitIcon* copy = new CGameEffectPortraitIcon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectReplaceItem::CGameEffectReplaceItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499CB0
CGameEffect* CGameEffectReplaceItem::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectReplaceItem* copy = new CGameEffectReplaceItem(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDisableButton::CGameEffectDisableButton(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499D60
CGameEffect* CGameEffectDisableButton::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDisableButton* copy = new CGameEffectDisableButton(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDisableSpellType::CGameEffectDisableSpellType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499E10
CGameEffect* CGameEffectDisableSpellType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDisableSpellType* copy = new CGameEffectDisableSpellType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCastSpell::CGameEffectCastSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499EC0
CGameEffect* CGameEffectCastSpell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCastSpell* copy = new CGameEffectCastSpell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectLearnSpell::CGameEffectLearnSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499F70
CGameEffect* CGameEffectLearnSpell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLearnSpell* copy = new CGameEffectLearnSpell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCastSpellPoint::CGameEffectCastSpellPoint(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A020
CGameEffect* CGameEffectCastSpellPoint::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCastSpellPoint* copy = new CGameEffectCastSpellPoint(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectIdentify::CGameEffectIdentify(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A0D0
CGameEffect* CGameEffectIdentify::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectIdentify* copy = new CGameEffectIdentify(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDetectTraps::CGameEffectDetectTraps(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A180
CGameEffect* CGameEffectDetectTraps::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDetectTraps* copy = new CGameEffectDetectTraps(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectReplaceSelf::CGameEffectReplaceSelf(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A230
CGameEffect* CGameEffectReplaceSelf::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectReplaceSelf* copy = new CGameEffectReplaceSelf(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPlayMovie::CGameEffectPlayMovie(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A2E0
CGameEffect* CGameEffectPlayMovie::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPlayMovie* copy = new CGameEffectPlayMovie(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSanctuary::CGameEffectSanctuary(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496340
CGameEffect* CGameEffectSanctuary::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSanctuary* copy = new CGameEffectSanctuary(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectEntangle::CGameEffectEntangle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4963F0
CGameEffect* CGameEffectEntangle::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectEntangle* copy = new CGameEffectEntangle(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectWebHold::CGameEffectWebHold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4964A0
CGameEffect* CGameEffectWebHold::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectWebHold* copy = new CGameEffectWebHold(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectGreasePool::CGameEffectGreasePool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x496550
CGameEffect* CGameEffectGreasePool::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectGreasePool* copy = new CGameEffectGreasePool(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMirrorImageRun::CGameEffectMirrorImageRun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x498A00
CGameEffect* CGameEffectMirrorImageRun::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMirrorImageRun* copy = new CGameEffectMirrorImageRun(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDispelSanctuary::CGameEffectDispelSanctuary(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A390
CGameEffect* CGameEffectDispelSanctuary::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelSanctuary* copy = new CGameEffectDispelSanctuary(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRemovePanic::CGameEffectRemovePanic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A440
CGameEffect* CGameEffectRemovePanic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRemovePanic* copy = new CGameEffectRemovePanic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRemoveHold::CGameEffectRemoveHold(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A4F0
CGameEffect* CGameEffectRemoveHold::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRemoveHold* copy = new CGameEffectRemoveHold(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRestoreMovementRate::CGameEffectRestoreMovementRate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A5A0
CGameEffect* CGameEffectRestoreMovementRate::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRestoreMovementRate* copy = new CGameEffectRestoreMovementRate(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRemoveIntoxication::CGameEffectRemoveIntoxication(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A650
CGameEffect* CGameEffectRemoveIntoxication::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRemoveIntoxication* copy = new CGameEffectRemoveIntoxication(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPauseCaster::CGameEffectPauseCaster(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A700
CGameEffect* CGameEffectPauseCaster::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPauseCaster* copy = new CGameEffectPauseCaster(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistanceToMagic::CGameEffectResistanceToMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A7B0
CGameEffect* CGameEffectResistanceToMagic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistanceToMagic* copy = new CGameEffectResistanceToMagic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMissileTHAC0Bonus::CGameEffectMissileTHAC0Bonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A860
CGameEffect* CGameEffectMissileTHAC0Bonus::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMissileTHAC0Bonus* copy = new CGameEffectMissileTHAC0Bonus(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDestroySelf::CGameEffectDestroySelf(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A910
CGameEffect* CGameEffectDestroySelf::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDestroySelf* copy = new CGameEffectDestroySelf(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunityToPortraitIcon::CGameEffectImmunityToPortraitIcon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49A9C0
CGameEffect* CGameEffectImmunityToPortraitIcon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunityToPortraitIcon* copy = new CGameEffectImmunityToPortraitIcon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectDamageVisualEffect::CGameEffectDamageVisualEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AA70
CGameEffect* CGameEffectDamageVisualEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDamageVisualEffect* copy = new CGameEffectDamageVisualEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAddInnateAbility::CGameEffectAddInnateAbility(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AB20
CGameEffect* CGameEffectAddInnateAbility::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAddInnateAbility* copy = new CGameEffectAddInnateAbility(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRemoveInnateAbility::CGameEffectRemoveInnateAbility(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49ABD0
CGameEffect* CGameEffectRemoveInnateAbility::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRemoveInnateAbility* copy = new CGameEffectRemoveInnateAbility(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectResistanceToPoison::CGameEffectResistanceToPoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AC80
CGameEffect* CGameEffectResistanceToPoison::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectResistanceToPoison* copy = new CGameEffectResistanceToPoison(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPlaySound::CGameEffectPlaySound(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AD30
CGameEffect* CGameEffectPlaySound::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPlaySound* copy = new CGameEffectPlaySound(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHoldCreatureSpell::CGameEffectHoldCreatureSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49ADE0
CGameEffect* CGameEffectHoldCreatureSpell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHoldCreatureSpell* copy = new CGameEffectHoldCreatureSpell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectApplyEffect::CGameEffectApplyEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AE90
CGameEffect* CGameEffectApplyEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectApplyEffect* copy = new CGameEffectApplyEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSelectiveToHitBonus::CGameEffectSelectiveToHitBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AF40
CGameEffect* CGameEffectSelectiveToHitBonus::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSelectiveToHitBonus* copy = new CGameEffectSelectiveToHitBonus(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSelectDamageBonus::CGameEffectSelectDamageBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49AFF0
CGameEffect* CGameEffectSelectDamageBonus::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSelectDamageBonus* copy = new CGameEffectSelectDamageBonus(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRestrictEquipItem::CGameEffectRestrictEquipItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B0A0
CGameEffect* CGameEffectRestrictEquipItem::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRestrictEquipItem* copy = new CGameEffectRestrictEquipItem(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectRestrictEquipItemType::CGameEffectRestrictEquipItemType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B150
CGameEffect* CGameEffectRestrictEquipItemType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRestrictEquipItemType* copy = new CGameEffectRestrictEquipItemType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectApplyEffectEquipItem::CGameEffectApplyEffectEquipItem(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B200
CGameEffect* CGameEffectApplyEffectEquipItem::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectApplyEffectEquipItem* copy = new CGameEffectApplyEffectEquipItem(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectApplyEffectEquipItemType::CGameEffectApplyEffectEquipItemType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B2B0
CGameEffect* CGameEffectApplyEffectEquipItemType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectApplyEffectEquipItemType* copy = new CGameEffectApplyEffectEquipItemType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSetDoNoJump::CGameEffectSetDoNoJump(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B360
CGameEffect* CGameEffectSetDoNoJump::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSetDoNoJump* copy = new CGameEffectSetDoNoJump(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectJumpToArea::CGameEffectJumpToArea(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B410
CGameEffect* CGameEffectJumpToArea::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectJumpToArea* copy = new CGameEffectJumpToArea(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSetLocalVariable::CGameEffectSetLocalVariable(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B4C0
CGameEffect* CGameEffectSetLocalVariable::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSetLocalVariable* copy = new CGameEffectSetLocalVariable(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectAuraCleansing::CGameEffectAuraCleansing(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B570
CGameEffect* CGameEffectAuraCleansing::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectAuraCleansing* copy = new CGameEffectAuraCleansing(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectMentalSpeed::CGameEffectMentalSpeed(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B620
CGameEffect* CGameEffectMentalSpeed::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMentalSpeed* copy = new CGameEffectMentalSpeed(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectPhysicalSpeed::CGameEffectPhysicalSpeed(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B6D0
CGameEffect* CGameEffectPhysicalSpeed::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPhysicalSpeed* copy = new CGameEffectPhysicalSpeed(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectCastingLevelBonus::CGameEffectCastingLevelBonus(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B780
CGameEffect* CGameEffectCastingLevelBonus::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectCastingLevelBonus* copy = new CGameEffectCastingLevelBonus(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectFindFamiliar::CGameEffectFindFamiliar(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499160
CGameEffect* CGameEffectFindFamiliar::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectFindFamiliar* copy = new CGameEffectFindFamiliar(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectSeeInvisible::CGameEffectSeeInvisible(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B830
CGameEffect* CGameEffectSeeInvisible::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSeeInvisible* copy = new CGameEffectSeeInvisible(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectIgnoreDialogPause::CGameEffectIgnoreDialogPause(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B8E0
CGameEffect* CGameEffectIgnoreDialogPause::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectIgnoreDialogPause* copy = new CGameEffectIgnoreDialogPause(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectHitPointsOnDeath::CGameEffectHitPointsOnDeath(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x499210
CGameEffect* CGameEffectHitPointsOnDeath::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectHitPointsOnDeath* copy = new CGameEffectHitPointsOnDeath(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectFamiliarBlock::CGameEffectFamiliarBlock(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4992C0
CGameEffect* CGameEffectFamiliarBlock::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectFamiliarBlock* copy = new CGameEffectFamiliarBlock(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceProjectile::CGameEffectBounceProjectile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49B990
CGameEffect* CGameEffectBounceProjectile::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceProjectile* copy = new CGameEffectBounceProjectile(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceEffect::CGameEffectBounceEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BA40
CGameEffect* CGameEffectBounceEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceEffect* copy = new CGameEffectBounceEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceLevel::CGameEffectBounceLevel(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BAF0
CGameEffect* CGameEffectBounceLevel::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceLevel* copy = new CGameEffectBounceLevel(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceLevelDecrement::CGameEffectBounceLevelDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BBA0
CGameEffect* CGameEffectBounceLevelDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceLevelDecrement* copy = new CGameEffectBounceLevelDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunityLevelDecrement::CGameEffectImmunityLevelDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BC50
CGameEffect* CGameEffectImmunityLevelDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunityLevelDecrement* copy = new CGameEffectImmunityLevelDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceSchool::CGameEffectBounceSchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BD00
CGameEffect* CGameEffectBounceSchool::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceSchool* copy = new CGameEffectBounceSchool(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectBounceSecondaryType::CGameEffectBounceSecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BDB0
CGameEffect* CGameEffectBounceSecondaryType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceSecondaryType* copy = new CGameEffectBounceSecondaryType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CGameEffectImmunitySchool::CGameEffectImmunitySchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BE60
CGameEffect* CGameEffectImmunitySchool::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunitySchool* copy = new CGameEffectImmunitySchool(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49BF10
CGameEffectImmunitySecondaryType::CGameEffectImmunitySecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49BF50
CGameEffect* CGameEffectImmunitySecondaryType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunitySecondaryType* copy = new CGameEffectImmunitySecondaryType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C000
CGameEffectImmunitySpell::CGameEffectImmunitySpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C040
CGameEffect* CGameEffectImmunitySpell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunitySpell* copy = new CGameEffectImmunitySpell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C0F0
CGameEffectBounceSpell::CGameEffectBounceSpell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C130
CGameEffect* CGameEffectBounceSpell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceSpell* copy = new CGameEffectBounceSpell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C1E0
CGameEffectMinHitPoints::CGameEffectMinHitPoints(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C220
CGameEffect* CGameEffectMinHitPoints::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMinHitPoints* copy = new CGameEffectMinHitPoints(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C2D0
CGameEffectPowerWordKill::CGameEffectPowerWordKill(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C310
CGameEffect* CGameEffectPowerWordKill::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPowerWordKill* copy = new CGameEffectPowerWordKill(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C3C0
CGameEffectPowerWordStun::CGameEffectPowerWordStun(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C400
CGameEffect* CGameEffectPowerWordStun::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPowerWordStun* copy = new CGameEffectPowerWordStun(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C4B0
CGameEffectImprisonment::CGameEffectImprisonment(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C4F0
CGameEffect* CGameEffectImprisonment::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImprisonment* copy = new CGameEffectImprisonment(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C5A0
CGameEffectFreedom::CGameEffectFreedom(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C5E0
CGameEffect* CGameEffectFreedom::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectFreedom* copy = new CGameEffectFreedom(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C690
CGameEffectMaze::CGameEffectMaze(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C6D0
CGameEffect* CGameEffectMaze::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectMaze* copy = new CGameEffectMaze(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C780
CGameEffectSecondaryCastList::CGameEffectSecondaryCastList(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C7C0
CGameEffect* CGameEffectSecondaryCastList::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSecondaryCastList* copy = new CGameEffectSecondaryCastList(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C870
CGameEffectVisualEffect::CGameEffectVisualEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C8B0
CGameEffect* CGameEffectVisualEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectVisualEffect* copy = new CGameEffectVisualEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49C960
CGameEffectLevelDrain::CGameEffectLevelDrain(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49C9A0
CGameEffect* CGameEffectLevelDrain::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLevelDrain* copy = new CGameEffectLevelDrain(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CA50
CGameEffectPowerWordSleep::CGameEffectPowerWordSleep(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49CA90
CGameEffect* CGameEffectPowerWordSleep::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectPowerWordSleep* copy = new CGameEffectPowerWordSleep(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CB40
CGameEffectStoneSkins::CGameEffectStoneSkins(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49CB80
CGameEffect* CGameEffectStoneSkins::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectStoneSkins* copy = new CGameEffectStoneSkins(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CC30
CGameEffectProtectionCircle::CGameEffectProtectionCircle(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49CC70
CGameEffect* CGameEffectProtectionCircle::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectProtectionCircle* copy = new CGameEffectProtectionCircle(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CD20
CGameEffectDispelSchool::CGameEffectDispelSchool(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49CD60
CGameEffect* CGameEffectDispelSchool::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelSchool* copy = new CGameEffectDispelSchool(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CE10
CGameEffectDispelSecondaryType::CGameEffectDispelSecondaryType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49CE50
CGameEffect* CGameEffectDispelSecondaryType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelSecondaryType* copy = new CGameEffectDispelSecondaryType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CF00
CGameEffectRandomTeleport::CGameEffectRandomTeleport(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49CF40
CGameEffect* CGameEffectRandomTeleport::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRandomTeleport* copy = new CGameEffectRandomTeleport(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49CFF0
CGameEffectImmunitySchoolDecrement::CGameEffectImmunitySchoolDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D030
CGameEffect* CGameEffectImmunitySchoolDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectImmunitySchoolDecrement* copy = new CGameEffectImmunitySchoolDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D0E0
CGameEffectLevelRestoration::CGameEffectLevelRestoration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D120
CGameEffect* CGameEffectLevelRestoration::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectLevelRestoration* copy = new CGameEffectLevelRestoration(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D1D0
CGameEffectRevealMagic::CGameEffectRevealMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D210
CGameEffect* CGameEffectRevealMagic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectRevealMagic* copy = new CGameEffectRevealMagic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D2C0
CGameEffectSecondaryTypeDecrement::CGameEffectSecondaryTypeDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D300
CGameEffect* CGameEffectSecondaryTypeDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectSecondaryTypeDecrement* copy = new CGameEffectSecondaryTypeDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D3B0
CGameEffectBounceSchoolDecrement::CGameEffectBounceSchoolDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D3F0
CGameEffect* CGameEffectBounceSchoolDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceSchoolDecrement* copy = new CGameEffectBounceSchoolDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D4A0
CGameEffectBounceSecondaryTypeDecrement::CGameEffectBounceSecondaryTypeDecrement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D4E0
CGameEffect* CGameEffectBounceSecondaryTypeDecrement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectBounceSecondaryTypeDecrement* copy = new CGameEffectBounceSecondaryTypeDecrement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D590
CGameEffectDispelSchoolOne::CGameEffectDispelSchoolOne(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D5D0
CGameEffect* CGameEffectDispelSchoolOne::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelSchoolOne* copy = new CGameEffectDispelSchoolOne(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D680
CGameEffectDispelSecondaryTypeOne::CGameEffectDispelSecondaryTypeOne(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D6C0
CGameEffect* CGameEffectDispelSecondaryTypeOne::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectDispelSecondaryTypeOne* copy = new CGameEffectDispelSecondaryTypeOne(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49D770
CGameEffectTimeStop::CGameEffectTimeStop(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49D7B0
CGameEffect* CGameEffectTimeStop::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectTimeStop* copy = new CGameEffectTimeStop(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}
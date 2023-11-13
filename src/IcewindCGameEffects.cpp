#include "IcewindCGameEffects.h"

#include "CGameSprite.h"
#include "CUtil.h"
#include "IcewindMisc.h"

// 0x49DB70
IcewindCGameEffectBeltynsBurningBlood::IcewindCGameEffectBeltynsBurningBlood(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49DBB0
CGameEffect* IcewindCGameEffectBeltynsBurningBlood::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBeltynsBurningBlood* copy = new IcewindCGameEffectBeltynsBurningBlood(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49DC60
IcewindCGameEffectCastingGlow::IcewindCGameEffectCastingGlow(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49DCA0
CGameEffect* IcewindCGameEffectCastingGlow::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectCastingGlow* copy = new IcewindCGameEffectCastingGlow(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49DD50
IcewindCGameEffectPrayer::IcewindCGameEffectPrayer(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49DD90
CGameEffect* IcewindCGameEffectPrayer::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectPrayer* copy = new IcewindCGameEffectPrayer(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49DE40
IcewindCGameEffectRecitation::IcewindCGameEffectRecitation(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49DE80
CGameEffect* IcewindCGameEffectRecitation::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRecitation* copy = new IcewindCGameEffectRecitation(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49DF30
IcewindCGameEffectRighteousWrathOfFaithful::IcewindCGameEffectRighteousWrathOfFaithful(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49DF70
CGameEffect* IcewindCGameEffectRighteousWrathOfFaithful::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRighteousWrathOfFaithful* copy = new IcewindCGameEffectRighteousWrathOfFaithful(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E020
IcewindCGameEffectSavingThrowChange::IcewindCGameEffectSavingThrowChange(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E060
CGameEffect* IcewindCGameEffectSavingThrowChange::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSavingThrowChange* copy = new IcewindCGameEffectSavingThrowChange(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E110
IcewindCGameEffectSlowPoison::IcewindCGameEffectSlowPoison(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E150
CGameEffect* IcewindCGameEffectSlowPoison::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSlowPoison* copy = new IcewindCGameEffectSlowPoison(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E200
IcewindCGameEffectVampiricTouch::IcewindCGameEffectVampiricTouch(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49E240
CGameEffect* IcewindCGameEffectVampiricTouch::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectVampiricTouch* copy = new IcewindCGameEffectVampiricTouch(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E2F0
IcewindCGameEffectColorGlowDissipate::IcewindCGameEffectColorGlowDissipate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E330
CGameEffect* IcewindCGameEffectColorGlowDissipate::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectColorGlowDissipate* copy = new IcewindCGameEffectColorGlowDissipate(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x55F5E0
IcewindCGameEffectSummon::IcewindCGameEffectSummon(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
    field_18C = 0;
    field_190 = 0;
}

// 0x55F620
CGameEffect* IcewindCGameEffectSummon::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSummon* copy = new IcewindCGameEffectSummon(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x49DB60
void IcewindCGameEffectSummon::sub_49DB60(int a1)
{
    field_190 = a1;
}

// -----------------------------------------------------------------------------

// 0x49E3E0
IcewindCGameEffectVisualSpellHit::IcewindCGameEffectVisualSpellHit(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E420
CGameEffect* IcewindCGameEffectVisualSpellHit::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectVisualSpellHit* copy = new IcewindCGameEffectVisualSpellHit(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E4D0
IcewindCGameEffectRemoveEffectOfResource::IcewindCGameEffectRemoveEffectOfResource(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E510
CGameEffect* IcewindCGameEffectRemoveEffectOfResource::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRemoveEffectOfResource* copy = new IcewindCGameEffectRemoveEffectOfResource(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E5C0
IcewindCGameEffectSalamanderAura::IcewindCGameEffectSalamanderAura(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49E600
CGameEffect* IcewindCGameEffectSalamanderAura::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSalamanderAura* copy = new IcewindCGameEffectSalamanderAura(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E6B0
IcewindCGameEffectUmberHulkGaze::IcewindCGameEffectUmberHulkGaze(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49E6F0
CGameEffect* IcewindCGameEffectUmberHulkGaze::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectUmberHulkGaze* copy = new IcewindCGameEffectUmberHulkGaze(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E7A0
IcewindCGameEffectImmunityToResource::IcewindCGameEffectImmunityToResource(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E7E0
CGameEffect* IcewindCGameEffectImmunityToResource::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectImmunityToResource* copy = new IcewindCGameEffectImmunityToResource(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E890
IcewindCGameEffectAnimationRemove::IcewindCGameEffectAnimationRemove(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E8D0
CGameEffect* IcewindCGameEffectAnimationRemove::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectAnimationRemove* copy = new IcewindCGameEffectAnimationRemove(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49E980
IcewindCGameEffectImmunityToEffectAndResource::IcewindCGameEffectImmunityToEffectAndResource(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49E9C0
CGameEffect* IcewindCGameEffectImmunityToEffectAndResource::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectImmunityToEffectAndResource* copy = new IcewindCGameEffectImmunityToEffectAndResource(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49EA70
IcewindCGameEffectDominate::IcewindCGameEffectDominate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49EAB0
CGameEffect* IcewindCGameEffectDominate::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectDominate* copy = new IcewindCGameEffectDominate(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49EB60
IcewindCGameEffectStaticCharge::IcewindCGameEffectStaticCharge(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49EBA0
CGameEffect* IcewindCGameEffectStaticCharge::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectStaticCharge* copy = new IcewindCGameEffectStaticCharge(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49EC50
IcewindCGameEffectCallLightning::IcewindCGameEffectCallLightning(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49EC90
CGameEffect* IcewindCGameEffectCallLightning::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectCallLightning* copy = new IcewindCGameEffectCallLightning(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49ED40
IcewindCGameEffectCloakOfFear::IcewindCGameEffectCloakOfFear(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49ED80
CGameEffect* IcewindCGameEffectCloakOfFear::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectCloakOfFear* copy = new IcewindCGameEffectCloakOfFear(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49EE30
IcewindCGameEffectForceMovementRate::IcewindCGameEffectForceMovementRate(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49EE70
CGameEffect* IcewindCGameEffectForceMovementRate::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectForceMovementRate* copy = new IcewindCGameEffectForceMovementRate(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49EF20
IcewindCGameEffectRemoveConfusion::IcewindCGameEffectRemoveConfusion(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49EF60
CGameEffect* IcewindCGameEffectRemoveConfusion::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRemoveConfusion* copy = new IcewindCGameEffectRemoveConfusion(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F010
IcewindCGameEffectEyeOfMind::IcewindCGameEffectEyeOfMind(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F050
CGameEffect* IcewindCGameEffectEyeOfMind::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfMind* copy = new IcewindCGameEffectEyeOfMind(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F100
IcewindCGameEffectEyeOfSword::IcewindCGameEffectEyeOfSword(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F140
CGameEffect* IcewindCGameEffectEyeOfSword::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfSword* copy = new IcewindCGameEffectEyeOfSword(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F1F0
IcewindCGameEffectEyeOfMage::IcewindCGameEffectEyeOfMage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F230
CGameEffect* IcewindCGameEffectEyeOfMage::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfMage* copy = new IcewindCGameEffectEyeOfMage(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F2E0
IcewindCGameEffectEyeOfVenom::IcewindCGameEffectEyeOfVenom(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F320
CGameEffect* IcewindCGameEffectEyeOfVenom::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfVenom* copy = new IcewindCGameEffectEyeOfVenom(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F3D0
IcewindCGameEffectEyeOfSpirit::IcewindCGameEffectEyeOfSpirit(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F410
CGameEffect* IcewindCGameEffectEyeOfSpirit::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfSpirit* copy = new IcewindCGameEffectEyeOfSpirit(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F4C0
IcewindCGameEffectEyeOfFortitude::IcewindCGameEffectEyeOfFortitude(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F500
CGameEffect* IcewindCGameEffectEyeOfFortitude::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfFortitude* copy = new IcewindCGameEffectEyeOfFortitude(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F5B0
IcewindCGameEffectEyeOfStone::IcewindCGameEffectEyeOfStone(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F5F0
CGameEffect* IcewindCGameEffectEyeOfStone::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEyeOfStone* copy = new IcewindCGameEffectEyeOfStone(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F6A0
IcewindCGameEffectRemoveSevenEyes::IcewindCGameEffectRemoveSevenEyes(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F6E0
CGameEffect* IcewindCGameEffectRemoveSevenEyes::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRemoveSevenEyes* copy = new IcewindCGameEffectRemoveSevenEyes(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F790
IcewindCGameEffectRemoveAllOfType::IcewindCGameEffectRemoveAllOfType(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F7D0
CGameEffect* IcewindCGameEffectRemoveAllOfType::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRemoveAllOfType* copy = new IcewindCGameEffectRemoveAllOfType(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F880
IcewindCGameEffectShroudOfFlame::IcewindCGameEffectShroudOfFlame(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F8C0
CGameEffect* IcewindCGameEffectShroudOfFlame::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectShroudOfFlame* copy = new IcewindCGameEffectShroudOfFlame(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49F970
IcewindCGameEffectAnimalRage::IcewindCGameEffectAnimalRage(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49F9B0
CGameEffect* IcewindCGameEffectAnimalRage::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectAnimalRage* copy = new IcewindCGameEffectAnimalRage(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FA60
IcewindCGameEffectTurnUndead::IcewindCGameEffectTurnUndead(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49FAA0
CGameEffect* IcewindCGameEffectTurnUndead::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectTurnUndead* copy = new IcewindCGameEffectTurnUndead(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FB50
IcewindCGameEffectVitriolicSphere::IcewindCGameEffectVitriolicSphere(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x49FB90
CGameEffect* IcewindCGameEffectVitriolicSphere::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectVitriolicSphere* copy = new IcewindCGameEffectVitriolicSphere(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FC50
IcewindCGameEffectSuppressHPDisplay::IcewindCGameEffectSuppressHPDisplay(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49FC90
CGameEffect* IcewindCGameEffectSuppressHPDisplay::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSuppressHPDisplay* copy = new IcewindCGameEffectSuppressHPDisplay(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FD40
IcewindCGameEffectFloatText::IcewindCGameEffectFloatText(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49FD80
CGameEffect* IcewindCGameEffectFloatText::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFloatText* copy = new IcewindCGameEffectFloatText(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FE30
IcewindCGameEffectMaceOfDisruption::IcewindCGameEffectMaceOfDisruption(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49FE70
CGameEffect* IcewindCGameEffectMaceOfDisruption::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectMaceOfDisruption* copy = new IcewindCGameEffectMaceOfDisruption(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x49FF20
IcewindCGameEffectRangerTracking::IcewindCGameEffectRangerTracking(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x49FF60
CGameEffect* IcewindCGameEffectRangerTracking::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRangerTracking* copy = new IcewindCGameEffectRangerTracking(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0010
IcewindCGameEffectImmunityToBackstab::IcewindCGameEffectImmunityToBackstab(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0050
CGameEffect* IcewindCGameEffectImmunityToBackstab::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectImmunityToBackstab* copy = new IcewindCGameEffectImmunityToBackstab(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0100
IcewindCGameEffectSetSpellState::IcewindCGameEffectSetSpellState(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0140
CGameEffect* IcewindCGameEffectSetSpellState::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSetSpellState* copy = new IcewindCGameEffectSetSpellState(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A01F0
IcewindCGameEffectRodOfSmiting::IcewindCGameEffectRodOfSmiting(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0230
CGameEffect* IcewindCGameEffectRodOfSmiting::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRodOfSmiting* copy = new IcewindCGameEffectRodOfSmiting(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A02E0
IcewindCGameEffectMagicalRest::IcewindCGameEffectMagicalRest(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0320
CGameEffect* IcewindCGameEffectMagicalRest::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectMagicalRest* copy = new IcewindCGameEffectMagicalRest(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A03D0
IcewindCGameEffectBeholderDispelMagic::IcewindCGameEffectBeholderDispelMagic(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x4A0410
CGameEffect* IcewindCGameEffectBeholderDispelMagic::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBeholderDispelMagic* copy = new IcewindCGameEffectBeholderDispelMagic(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A04C0
IcewindCGameEffectHarpyWail::IcewindCGameEffectHarpyWail(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x4A0500
CGameEffect* IcewindCGameEffectHarpyWail::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectHarpyWail* copy = new IcewindCGameEffectHarpyWail(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A05B0
IcewindCGameEffectJackalwereGaze::IcewindCGameEffectJackalwereGaze(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, TRUE)
{
}

// 0x4A05F0
CGameEffect* IcewindCGameEffectJackalwereGaze::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectJackalwereGaze* copy = new IcewindCGameEffectJackalwereGaze(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A06A0
IcewindCGameEffectSetGlobal::IcewindCGameEffectSetGlobal(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A06E0
CGameEffect* IcewindCGameEffectSetGlobal::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSetGlobal* copy = new IcewindCGameEffectSetGlobal(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0790
IcewindCGameEffectHopelessness::IcewindCGameEffectHopelessness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A07D0
CGameEffect* IcewindCGameEffectHopelessness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectHopelessness* copy = new IcewindCGameEffectHopelessness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0880
IcewindCGameEffectProtectionFromEvil::IcewindCGameEffectProtectionFromEvil(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A08C0
CGameEffect* IcewindCGameEffectProtectionFromEvil::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectProtectionFromEvil* copy = new IcewindCGameEffectProtectionFromEvil(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0970
IcewindCGameEffectApplyEffectsList::IcewindCGameEffectApplyEffectsList(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A09B0
CGameEffect* IcewindCGameEffectApplyEffectsList::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectApplyEffectsList* copy = new IcewindCGameEffectApplyEffectsList(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0A60
IcewindCGameEffectArmorOfFaith::IcewindCGameEffectArmorOfFaith(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0AA0
CGameEffect* IcewindCGameEffectArmorOfFaith::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectArmorOfFaith* copy = new IcewindCGameEffectArmorOfFaith(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0B50
IcewindCGameEffectNausea::IcewindCGameEffectNausea(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0B90
CGameEffect* IcewindCGameEffectNausea::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectNausea* copy = new IcewindCGameEffectNausea(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0C40
IcewindCGameEffectEnfeeblement::IcewindCGameEffectEnfeeblement(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0C80
CGameEffect* IcewindCGameEffectEnfeeblement::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEnfeeblement* copy = new IcewindCGameEffectEnfeeblement(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0D30
IcewindCGameEffectFireshield::IcewindCGameEffectFireshield(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0D70
CGameEffect* IcewindCGameEffectFireshield::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFireshield* copy = new IcewindCGameEffectFireshield(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0E20
IcewindCGameEffectDeathWard::IcewindCGameEffectDeathWard(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0E60
CGameEffect* IcewindCGameEffectDeathWard::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectDeathWard* copy = new IcewindCGameEffectDeathWard(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A0F10
IcewindCGameEffectHolyPower::IcewindCGameEffectHolyPower(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A0F50
CGameEffect* IcewindCGameEffectHolyPower::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectHolyPower* copy = new IcewindCGameEffectHolyPower(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1000
IcewindCGameEffectVisualEffect::IcewindCGameEffectVisualEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1040
CGameEffect* IcewindCGameEffectVisualEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectVisualEffect* copy = new IcewindCGameEffectVisualEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A10F0
IcewindCGameEffectOtilukesResilientSphere::IcewindCGameEffectOtilukesResilientSphere(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1130
CGameEffect* IcewindCGameEffectOtilukesResilientSphere::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectOtilukesResilientSphere* copy = new IcewindCGameEffectOtilukesResilientSphere(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A11E0
IcewindCGameEffectBarkskin::IcewindCGameEffectBarkskin(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1220
CGameEffect* IcewindCGameEffectBarkskin::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBarkskin* copy = new IcewindCGameEffectBarkskin(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A12D0
IcewindCGameEffectBleedingWounds::IcewindCGameEffectBleedingWounds(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1310
CGameEffect* IcewindCGameEffectBleedingWounds::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBleedingWounds* copy = new IcewindCGameEffectBleedingWounds(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A13C0
IcewindCGameEffectAreaOfEffect::IcewindCGameEffectAreaOfEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1400
CGameEffect* IcewindCGameEffectAreaOfEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectAreaOfEffect* copy = new IcewindCGameEffectAreaOfEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A14B0
IcewindCGameEffectFreeAction::IcewindCGameEffectFreeAction(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A14F0
CGameEffect* IcewindCGameEffectFreeAction::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFreeAction* copy = new IcewindCGameEffectFreeAction(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A15A0
IcewindCGameEffectUnconsciousness::IcewindCGameEffectUnconsciousness(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A15E0
CGameEffect* IcewindCGameEffectUnconsciousness::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectUnconsciousness* copy = new IcewindCGameEffectUnconsciousness(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1690
IcewindCGameEffectEntropyShield::IcewindCGameEffectEntropyShield(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A16D0
CGameEffect* IcewindCGameEffectEntropyShield::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEntropyShield* copy = new IcewindCGameEffectEntropyShield(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1780
IcewindCGameEffectStormShell::IcewindCGameEffectStormShell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A17C0
CGameEffect* IcewindCGameEffectStormShell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectStormShell* copy = new IcewindCGameEffectStormShell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1870
IcewindCGameEffectProtectionFromElements::IcewindCGameEffectProtectionFromElements(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A18B0
CGameEffect* IcewindCGameEffectProtectionFromElements::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectProtectionFromElements* copy = new IcewindCGameEffectProtectionFromElements(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56A140
BOOL IcewindCGameEffectProtectionFromElements::ApplyEffect(CGameSprite* pSprite)
{
    if (m_secondaryType) {
        DisplayStringRef(pSprite, 8842); // "Protected by Protection from the Elements"
    }

    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_PROTECTION_FROM_THE_ELEMENTS]) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_PROTECTION_FROM_THE_ELEMENTS] = true;

        // NOTE: Uninline.
        AddPortraitIcon(pSprite, 93);

        AddColorEffect(pSprite, 192, 0, 0, 61);
        AddColorEffect(pSprite, 0, 192, 0, 43);
        AddColorEffect(pSprite, 0, 0, 192, 79);

        pSprite->m_bonusStats.m_nResistFire += 15;
        pSprite->m_bonusStats.m_nResistCold += 15;
        pSprite->m_bonusStats.m_nResistElectricity += 15;
        pSprite->m_bonusStats.m_nResistAcid += 15;
    }
    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A1960
IcewindCGameEffectAegis::IcewindCGameEffectAegis(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A19A0
CGameEffect* IcewindCGameEffectAegis::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectAegis* copy = new IcewindCGameEffectAegis(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1A50
IcewindCGameEffectExecutionersEyes::IcewindCGameEffectExecutionersEyes(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1A90
CGameEffect* IcewindCGameEffectExecutionersEyes::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectExecutionersEyes* copy = new IcewindCGameEffectExecutionersEyes(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56A500
BOOL IcewindCGameEffectExecutionersEyes::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EXECUTIONERS_EYES]) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EXECUTIONERS_EYES] = true;

        // NOTE: Uninline.
        AddPortraitIcon(pSprite, 120);

        pSprite->SetColorRange(8);
        pSprite->GetDerivedStats()->m_nTHAC0 += 4;
        pSprite->GetDerivedStats()->m_nCriticalHitBonus += 4;
    }
    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A1B40
IcewindCGameEffectWhenStruck::IcewindCGameEffectWhenStruck(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1B80
CGameEffect* IcewindCGameEffectWhenStruck::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectWhenStruck* copy = new IcewindCGameEffectWhenStruck(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1C30
IcewindCGameEffectProjectile::IcewindCGameEffectProjectile(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1C70
CGameEffect* IcewindCGameEffectProjectile::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectProjectile* copy = new IcewindCGameEffectProjectile(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A1D20
IcewindCGameEffectEnergyDrain::IcewindCGameEffectEnergyDrain(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1D60
CGameEffect* IcewindCGameEffectEnergyDrain::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectEnergyDrain* copy = new IcewindCGameEffectEnergyDrain(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56A910
BOOL IcewindCGameEffectEnergyDrain::ApplyEffect(CGameSprite* pSprite)
{
    if (pSprite != NULL && pSprite->field_72B6) {
        return FALSE;
    }

    if (m_secondaryType) {
        DisplayStringRef(pSprite, 16286);
    }

    // NOTE: Using `set` (with bounds check).
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_ENERGY_DRAINED, true);

    // NOTE: Uninline.
    AddPortraitIcon(pSprite, 123);

    pSprite->GetDerivedStats()->m_nTHAC0 -= static_cast<SHORT>(m_effectAmount);
    pSprite->GetDerivedStats()->m_nSaveVSFortitude -= static_cast<SHORT>(m_effectAmount);
    pSprite->GetDerivedStats()->m_nSaveVSReflex -= static_cast<SHORT>(m_effectAmount);
    pSprite->GetDerivedStats()->m_nSaveVSWill -= static_cast<SHORT>(m_effectAmount);
    pSprite->GetDerivedStats()->m_nMaxHitPoints += -5 * static_cast<SHORT>(m_effectAmount);

    if (m_secondaryType) {
        pSprite->GetBaseStats()->m_hitPoints += -5 * static_cast<SHORT>(m_effectAmount);
    }

    if (pSprite->GetBaseStats()->m_hitPoints <= 0 || pSprite->GetDerivedStats()->m_nMaxHitPoints <= 0) {
        CGameEffectDeath* pDeath = new CGameEffectDeath();
        pDeath->m_source = m_source;
        pDeath->m_sourceID = m_sourceID;
        pDeath->m_dwFlags = 0x4;
        pSprite->AddEffect(pDeath, CGameAIBase::EFFECT_LIST_TIMED, TRUE, TRUE);

        pSprite->GetDerivedStats()->m_nMaxHitPoints = 1;
        pSprite->GetBaseStats()->m_hitPoints = 0;
        m_done = TRUE;
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A1E10
IcewindCGameEffectTortoiseShell::IcewindCGameEffectTortoiseShell(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1E50
CGameEffect* IcewindCGameEffectTortoiseShell::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectTortoiseShell* copy = new IcewindCGameEffectTortoiseShell(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56AAE0
BOOL IcewindCGameEffectTortoiseShell::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_TORTOISE_SHELL]) {
        if (m_secondaryType) {
            DisplayStringRef(pSprite, 17063); // "Encased in Tortoise Shell"
        }

        // NOTE: Using `set` (with bounds check).
        pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_TORTOISE_SHELL, true);
        pSprite->GetDerivedStats()->m_spellStatesExtra.set(SPLSTATEEXTRA_30, true);

        // NOTE: Uninline.
        AddPortraitIcon(pSprite, 125);

        pSprite->field_9D15 = 1;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_HELD] = true;
        pSprite->GetDerivedStats()->m_generalState |= STATE_HELPLESS;
        pSprite->GetDerivedStats()->field_124 = m_effectAmount;
    } else {
        m_done = TRUE;
    }
    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A1F00
IcewindCGameEffectBlink::IcewindCGameEffectBlink(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A1F40
CGameEffect* IcewindCGameEffectBlink::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBlink* copy = new IcewindCGameEffectBlink(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56ABB0
BOOL IcewindCGameEffectBlink::ApplyEffect(CGameSprite* pSprite)
{
    pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_BLINK] = true;
    pSprite->GetDerivedStats()->m_spellStatesExtra[SPLSTATEEXTRA_25] = true;

    switch (m_dwFlags) {
    case 0:
        AddPortraitIcon(pSprite, 130);
        break;
    case 1:
        AddPortraitIcon(pSprite, 145);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\IcewindCGameEffects.cpp
        // __LINE__: 6894
        UTIL_ASSERT(FALSE);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A1FF0
IcewindCGameEffectPersistantEffect::IcewindCGameEffectPersistantEffect(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2030
CGameEffect* IcewindCGameEffectPersistantEffect::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectPersistantEffect* copy = new IcewindCGameEffectPersistantEffect(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A20E0
IcewindCGameEffectDamageReduction::IcewindCGameEffectDamageReduction(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2120
CGameEffect* IcewindCGameEffectDamageReduction::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectDamageReduction* copy = new IcewindCGameEffectDamageReduction(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A21D0
IcewindCGameEffectProtectionFromArrows::IcewindCGameEffectProtectionFromArrows(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2210
CGameEffect* IcewindCGameEffectProtectionFromArrows::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectProtectionFromArrows* copy = new IcewindCGameEffectProtectionFromArrows(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A22C0
IcewindCGameEffectTensersTransformation::IcewindCGameEffectTensersTransformation(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2300
CGameEffect* IcewindCGameEffectTensersTransformation::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectTensersTransformation* copy = new IcewindCGameEffectTensersTransformation(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B0F0
BOOL IcewindCGameEffectTensersTransformation::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_TENSERS_TRANSFORMATION]) {
        pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_TENSERS_TRANSFORMATION, true);

        // NOTE: Uninline.
        AddPortraitIcon(pSprite, 55);

        pSprite->SetColorRange(62);

        if (m_secondaryType) {
            m_effectAmount2 = IcewindMisc::Roll(m_casterLevel, 6);
            m_effectAmount3 = IcewindMisc::Roll(2, 4);
            m_effectAmount4 = IcewindMisc::Roll(2, 4);
        }

        pSprite->GetDerivedStats()->m_nMaxHitPoints += static_cast<SHORT>(m_effectAmount2);
        if (m_secondaryType) {
            pSprite->GetBaseStats()->m_hitPoints += static_cast<SHORT>(m_effectAmount2);
        }
        pSprite->GetDerivedStats()->m_nSTR += static_cast<SHORT>(m_effectAmount3);
        pSprite->GetDerivedStats()->m_nDEX += static_cast<SHORT>(m_effectAmount4);
        pSprite->GetDerivedStats()->m_nTHAC0 += static_cast<BYTE>(m_casterLevel) / 2;
        pSprite->GetDerivedStats()->m_nSaveVSFortitude += 5;
        pSprite->GetDerivedStats()->field_C += 4;
        pSprite->GetDerivedStats()->m_disabledSpellTypes[0] = TRUE;
        pSprite->GetDerivedStats()->m_disabledSpellTypes[1] = TRUE;
    }
    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A23B0
IcewindCGameEffectSmiteEvil::IcewindCGameEffectSmiteEvil(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A23F0
CGameEffect* IcewindCGameEffectSmiteEvil::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectSmiteEvil* copy = new IcewindCGameEffectSmiteEvil(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B220
BOOL IcewindCGameEffectSmiteEvil::ApplyEffect(CGameSprite* pSprite)
{
    pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_SMITE_EVIL] = true;
    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A24A0
IcewindCGameEffectRestoration::IcewindCGameEffectRestoration(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A24E0
CGameEffect* IcewindCGameEffectRestoration::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectRestoration* copy = new IcewindCGameEffectRestoration(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A2590
IcewindCGameEffectAlicornLanceGlow::IcewindCGameEffectAlicornLanceGlow(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A25D0
CGameEffect* IcewindCGameEffectAlicornLanceGlow::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectAlicornLanceGlow* copy = new IcewindCGameEffectAlicornLanceGlow(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B4B0
BOOL IcewindCGameEffectAlicornLanceGlow::ApplyEffect(CGameSprite* pSprite)
{
    if (m_secondaryType) {
        DisplayStringRef(pSprite, 21646);
    }

    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_ALICORN_LANCE]) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_ALICORN_LANCE] = true;
        pSprite->GetDerivedStats()->field_C -= 2;
        AddColorEffect(pSprite, 185, 185, 185);
        m_done = FALSE;
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2680
IcewindCGameEffectGlobeOfInvulnerability::IcewindCGameEffectGlobeOfInvulnerability(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A26C0
CGameEffect* IcewindCGameEffectGlobeOfInvulnerability::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectGlobeOfInvulnerability* copy = new IcewindCGameEffectGlobeOfInvulnerability(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// -----------------------------------------------------------------------------

// 0x4A2770
IcewindCGameEffectLowerResistance::IcewindCGameEffectLowerResistance(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A27B0
CGameEffect* IcewindCGameEffectLowerResistance::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectLowerResistance* copy = new IcewindCGameEffectLowerResistance(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B680
BOOL IcewindCGameEffectLowerResistance::ApplyEffect(CGameSprite* pSprite)
{
    if (m_secondaryType) {
        DisplayStringRef(pSprite, 16967); // "Spell Resistance Lowered"
    }

    if (!pSprite->GetDerivedStats()->m_spellStates[CGAMEEFFECT_CASTINGGLOW]) {
        pSprite->GetDerivedStats()->m_spellStates[CGAMEEFFECT_CASTINGGLOW] = true;
        AdjustResistMagic(pSprite, -static_cast<BYTE>(m_casterLevel) * 2);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2860
IcewindCGameEffectBane::IcewindCGameEffectBane(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A28A0
CGameEffect* IcewindCGameEffectBane::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectBane* copy = new IcewindCGameEffectBane(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B710
BOOL IcewindCGameEffectBane::ApplyEffect(CGameSprite* pSprite)
{
    if (m_secondaryType) {
        DisplayStringRef(pSprite, 14406); // "Afflicted by Bane"
        RemoveAllOfType(pSprite, CGAMEEFFECT_NON_CUMULATIVEAID, -1);
    }

    if (!pSprite->GetDerivedStats()->m_spellStates[CGAMEEFFECT_DURATIONCASTING]) {
        AddPortraitIcon(pSprite, 35);
        AddColorEffect(pSprite, 0, 0, 128, 30);
        SetSpellState(pSprite, CGAMEEFFECT_DURATIONCASTING);
        AdjustTHAC0(pSprite, -1);
        pSprite->GetBaseStats()->m_morale--;
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2950
IcewindCGameEffectFeatPowerAttack::IcewindCGameEffectFeatPowerAttack(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2990
CGameEffect* IcewindCGameEffectFeatPowerAttack::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFeatPowerAttack* copy = new IcewindCGameEffectFeatPowerAttack(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B790
BOOL IcewindCGameEffectFeatPowerAttack::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->sub_763150(CGAMESPRITE_FEAT_POWER_ATTACK)) {
        return FALSE;
    }

    INT nRank = pSprite->sub_726270(CGAMESPRITE_FEAT_POWER_ATTACK);

    // NOTE: Using `set` (with bounds check).
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_1, nRank == 1);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_2, nRank == 2);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_3, nRank == 3);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_4, nRank == 4);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_5, nRank == 5);

    if (nRank != 0
        && (pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_1)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_2)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_3)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_4)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_5))) {
        if (m_secondaryType) {
            // NOTE: Odd mixing of `test` (with bounds check) and `operator[]`.
            if (pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_1)
                || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_2)
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_3]
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_4]
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_5]) {
                pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                    1,
                    0,
                    0,
                    35785, // // "Expertise"
                    0,
                    0);
            }
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                0,
                0,
                0,
                35794, // "Power Attack"
                0,
                0);
        }

        // NOTE: Odd mixing of `set` (with bounds check) and `operator[]`.
        pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_1, false);
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_2] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_3] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_4] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_EXPERTISE_5] = false;
    } else {
        m_done = TRUE;
        if (m_secondaryType) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                1,
                nRank,
                0,
                35794, // "Power Attack"
                0,
                0);
        }
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2A40
IcewindCGameEffectFeatExpertise::IcewindCGameEffectFeatExpertise(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2A80
CGameEffect* IcewindCGameEffectFeatExpertise::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFeatExpertise* copy = new IcewindCGameEffectFeatExpertise(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56B960
BOOL IcewindCGameEffectFeatExpertise::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->sub_763150(CGAMESPRITE_FEAT_EXPERTISE)) {
        return FALSE;
    }

    INT nRank = pSprite->sub_726270(CGAMESPRITE_FEAT_EXPERTISE);

    // NOTE: Using `set` (with bounds check).
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_1, nRank == 1);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_2, nRank == 2);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_3, nRank == 3);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_4, nRank == 4);
    pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_EXPERTISE_5, nRank == 5);

    if (nRank != 0
        && (pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_1)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_2)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_3)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_4)
            || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_EXPERTISE_5))) {
        if (m_secondaryType) {
            // NOTE: Odd mixing of `test` (with bounds check) and `operator[]`.
            if (pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_1)
                || pSprite->GetDerivedStats()->m_spellStates.test(SPLSTATE_FEAT_POWER_ATTACK_2)
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_3]
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_4]
                || pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_5]) {
                pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                    1,
                    0,
                    0,
                    35794, // "Power Attack"
                    0,
                    0);
            }
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                0,
                0,
                0,
                35785, // "Expertise"
                0,
                0);
        }

        // NOTE: Odd mixing of `set` (with bounds check) and `operator[]`.
        pSprite->GetDerivedStats()->m_spellStates.set(SPLSTATE_FEAT_POWER_ATTACK_1, false);
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_2] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_3] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_4] = false;
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_POWER_ATTACK_5] = false;
    } else {
        m_done = TRUE;
        if (m_secondaryType) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                1,
                nRank,
                0,
                35785, // "Expertise"
                0,
                0);
        }
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2B30
IcewindCGameEffectFeatArterialStrike::IcewindCGameEffectFeatArterialStrike(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2B70
CGameEffect* IcewindCGameEffectFeatArterialStrike::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFeatArterialStrike* copy = new IcewindCGameEffectFeatArterialStrike(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56BB30
BOOL IcewindCGameEffectFeatArterialStrike::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->sub_763150(CGAMESPRITE_FEAT_ARTERIAL_STRIKE)) {
        return FALSE;
    }

    INT nRank = pSprite->sub_726270(CGAMESPRITE_FEAT_ARTERIAL_STRIKE);
    if (nRank > 0) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_ARTERIAL_STRIKE] = true;
        if (m_secondaryType != 0) {
            if (pSprite->GetDerivedStats()->m_spellStates[CGAMESPRITE_FEAT_HAMSTRING]) {
                pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                    1,
                    0,
                    0,
                    35787, // "Hamstring"
                    0,
                    0);
            }
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                0,
                0,
                0,
                35774, // "Arterial Strike"
                0,
                0);
        }
        pSprite->GetDerivedStats()->m_spellStates[CGAMESPRITE_FEAT_HAMSTRING] = false;
    } else {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_ARTERIAL_STRIKE] = false;
        m_done = TRUE;
        if (m_secondaryType != 0) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                1,
                0,
                0,
                35774, // "Arterial Strike"
                0,
                0);
        }
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2C20
IcewindCGameEffectFeatHamstring::IcewindCGameEffectFeatHamstring(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2C60
CGameEffect* IcewindCGameEffectFeatHamstring::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    IcewindCGameEffectFeatHamstring* copy = new IcewindCGameEffectFeatHamstring(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56BC20
BOOL IcewindCGameEffectFeatHamstring::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->sub_763150(CGAMESPRITE_FEAT_HAMSTRING)) {
        return FALSE;
    }

    INT nRank = pSprite->sub_726270(CGAMESPRITE_FEAT_HAMSTRING);
    if (nRank > 0) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_HAMSTRING] = true;
        if (m_secondaryType != 0) {
            if (pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_ARTERIAL_STRIKE]) {
                pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                    1,
                    0,
                    0,
                    35774, // "Arterial Strike"
                    0,
                    0);
            }
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                0,
                0,
                0,
                35787, // "Hamstring"
                0,
                0);
        }
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_ARTERIAL_STRIKE] = false;
    } else {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_HAMSTRING] = false;
        m_done = TRUE;
        if (m_secondaryType != 0) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                1,
                0,
                0,
                35787, // "Hamstring"
                0,
                0);
        }
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x4A2D10
IcewindCGameEffectFeatRapidShot::IcewindCGameEffectFeatRapidShot(ITEM_EFFECT* effect, const CPoint& source, LONG sourceID, CPoint target)
    : CGameEffect(effect, source, sourceID, target, FALSE)
{
}

// 0x4A2D50
CGameEffect* IcewindCGameEffectFeatRapidShot::Copy()
{
    ITEM_EFFECT* effect = GetItemEffect();
    CGameEffectStoneSkins* copy = new CGameEffectStoneSkins(effect, m_source, m_sourceID, m_target);
    delete effect;
    copy->CopyFromBase(this);
    return copy;
}

// 0x56BD10
BOOL IcewindCGameEffectFeatRapidShot::ApplyEffect(CGameSprite* pSprite)
{
    if (!pSprite->sub_763150(CGAMESPRITE_FEAT_RAPID_SHOT)) {
        return FALSE;
    }

    INT nRank = pSprite->sub_726270(CGAMESPRITE_FEAT_RAPID_SHOT);
    if (nRank > 0) {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_RAPID_SHOT] = true;
        if (m_secondaryType != 0) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                0,
                0,
                0,
                35796, // "Rapid Shot"
                0,
                0);
        }
    } else {
        pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_FEAT_RAPID_SHOT] = false;
        m_done = TRUE;
        if (m_secondaryType != 0) {
            pSprite->FeedBack(CGameSprite::FEEDBACK_TOGGLEFEAT,
                1,
                0,
                0,
                35796, // "Rapid Shot"
                0,
                0);
        }
    }

    return TRUE;
}

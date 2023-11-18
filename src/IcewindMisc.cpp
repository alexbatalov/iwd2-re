#include "IcewindMisc.h"

#include "CBaldurChitin.h"
#include "CButtonData.h"
#include "CGameAnimationType.h"
#include "CGameEffect.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CSpell.h"
#include "CUtil.h"
#include "IcewindCGameEffects.h"

// 0x5845D0
INT IcewindMisc::Roll(INT nRolls, INT nSides)
{
    INT nResult = 0;

    while (nRolls > 0) {
        nResult += (nSides != 0 ? rand() % nSides : 0) + 1;
        nRolls--;
    }

    return nResult;
}

// NOTE: Unclear if it returns CPoint or CSize.
//
// 0x584610
CPoint IcewindMisc::sub_584610(INT nDirection)
{
    switch (nDirection) {
    case 0:
        return CPoint(0, 20);
    case 1:
        return CPoint(-10, 18);
    case 2:
        return CPoint(-19, 14);
    case 3:
        return CPoint(-25, 8);
    case 4:
        return CPoint(-20, 0);
    case 5:
        return CPoint(-25, -8);
    case 6:
        return CPoint(-19, -14);
    case 7:
        return CPoint(-10, -18);
    case 8:
        return CPoint(0, -20);
    case 9:
        return CPoint(10, -18);
    case 10:
        return CPoint(19, -14);
    case 11:
        return CPoint(25, -8);
    case 12:
        return CPoint(20, 0);
    case 13:
        return CPoint(25, 8);
    case 14:
        return CPoint(19, 14);
    case 15:
        return CPoint(10, 18);
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\IcewindMisc.cpp
        // __LINE__: 57
        UTIL_ASSERT(FALSE);
    }
}

// 0x5847B0
CPoint IcewindMisc::sub_5847B0(const CPoint& pt, int x, int y, int radius)
{
    if (x != 0 || y != 0) {
        float v1 = static_cast<float>(sqrt(static_cast<float>(radius * radius) / static_cast<float>(x * x + y * y)));
        return CPoint(pt.x + static_cast<int>(x * v1), pt.y + static_cast<int>(y * v1));
    } else {
        return pt;
    }
}

// 0x584880
void IcewindMisc::sub_584880(CGameSprite* pSprite, STRREF strRef, INT nNumber)
{
    if (strRef != -1 && (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nEffectTextLevel & 0x8) != 0) {
        if (nNumber != 0) {
            STR_RES strRes;
            g_pBaldurChitin->GetTlkTable().Fetch(strRef, strRes);

            if (strRes.szText != "") {
                CString sText;
                sText.Format("%s (%d)", (LPCSTR)strRes.szText, nNumber);
                g_pBaldurChitin->GetBaldurMessage()->DisplayText(pSprite->GetName(),
                    sText,
                    CVidPalette::RANGE_COLORS[pSprite->GetBaseStats()->m_colors[CVIDPALETTE_RANGE_MAIN_CLOTH]],
                    RGB(215, 215, 190),
                    -1,
                    pSprite->GetId(),
                    pSprite->GetId());
            }
        } else {
            g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(pSprite->GetNameRef(),
                strRef,
                CVidPalette::RANGE_COLORS[pSprite->GetBaseStats()->m_colors[CVIDPALETTE_RANGE_MAIN_CLOTH]],
                RGB(215, 215, 190),
                -1,
                pSprite->GetId(),
                pSprite->GetId());
        }
    }
}

// 0x584A40
BOOLEAN IcewindMisc::IsUndead(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nGeneral == CAIObjectType::G_UNDEAD;
}

// 0x584A60
BOOLEAN IcewindMisc::IsImmuneToFire(CGameSprite* pSprite)
{
    return pSprite->GetDerivedStats()->m_nResistFire >= 100;
}

// 0x584A70
BOOLEAN IcewindMisc::IsImmuneToCold(CGameSprite* pSprite)
{
    return pSprite->GetDerivedStats()->m_nResistCold >= 100;
}

// 0x584A80
BOOLEAN IcewindMisc::IsHumanoid(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nGeneral == CAIObjectType::G_HUMANOID;
}

// 0x584AA0
BOOLEAN IcewindMisc::IsAberration(CGameSprite* pSprite)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\IcewindMisc.cpp
    // __LINE__: 273
    UTIL_ASSERT(pSprite != NULL);

    switch (pSprite->GetAIType().m_nRace) {
    case CAIOBJECTTYPE_R_ETTERCAP:
    case CAIOBJECTTYPE_R_CARRION_CRAWLER:
    case CAIOBJECTTYPE_R_UMBERHULK:
    case CAIOBJECTTYPE_R_BEHOLDER:
    case CAIOBJECTTYPE_R_HOOK_HORROR:
    case CAIOBJECTTYPE_R_DRIDER:
    case CAIOBJECTTYPE_R_184:
    case CAIOBJECTTYPE_R_WILLOWISP:
    case CAIOBJECTTYPE_R_OTYUGH:
        return TRUE;
    }

    return FALSE;
}

// 0x584B50
BOOLEAN IcewindMisc::IsAnimal(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nGeneral == CAIObjectType::G_ANIMAL;
}

// 0x584B70
BOOLEAN IcewindMisc::IsElemental(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_ELEMENTAL;
}

// 0x584B90
BOOLEAN IcewindMisc::IsFungus(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nRace) {
    case CAIOBJECTTYPE_R_MYCONID:
    case CAIOBJECTTYPE_R_SHRIEKER:
        return TRUE;
    }

    return FALSE;
}

// NOTE: Name might be wrong.
//
// 0x584BC0
BOOLEAN IcewindMisc::IsLarge(CGameSprite* pSprite)
{
    // NOTE: No assertion, so it's not pSprite->GetAnimation()->GetAnimationId()
    USHORT nID = pSprite->m_animation.m_animation->m_animationID;

    switch (nID) {
    case ANIM_WYVERN:
    case ANIM_BEETLE_RHINOCEROUS:
    case ANIM_REMORHAZ:
    case ANIM_CYCLOPS:
    case ANIM_ETTIN:
    case ANIM_GIANT_FROST:
    case ANIM_ELEMENTAL_EARTH:
    case ANIM_ELEMENTAL_FIRE:
    case ANIM_ELEMENTAL_WATER:
    case ANIM_GOLEM_IRON:
    case ANIM_GOLEM_ICE:
    case ANIM_UMBER_HULK:
    case ANIM_UMBER_HULK_VODYANOI:
    case ANIM_LIZARD_MAN_KING:
    case ANIM_BELHIFET:
    case ANIM_EB52:
    case ANIM_EB8A:
    case ANIM_DRAGON_WHITE:
    case ANIM_EC1D:
    case ANIM_CORNUGON:
    case ANIM_GLABREZU:
    case ANIM_GIANT_FIRE:
    case ANIM_SAHUAGIN_LARGE:
        return TRUE;
    }

    return FALSE;
}

// 0x584CB0
BOOLEAN IcewindMisc::IsOutsider(CGameSprite* pSprite)
{
    if (pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_ELEMENTAL) {
        return TRUE;
    }

    if (pSprite->m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN) {
        if (pSprite->m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR
            || pSprite->m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING) {
            return TRUE;
        }
    }

    if (pSprite->GetClassLevel(CAIOBJECTTYPE_C_MONK) >= 20) {
        return TRUE;
    }

    // NOTE: No assertion, so it's not pSprite->GetAnimation()->GetAnimationId()
    USHORT nID = pSprite->m_animation.m_animation->m_animationID;

    switch (nID) {
    case ANIM_DJINNI:
    case ANIM_DJINNI_LEGS:
    case ANIM_RAVER:
    case ANIM_SLAYER:
    case ANIM_ABISHAI_WHITE:
    case ANIM_SALAMANDER:
    case ANIM_SALAMANDER_FROST:
    case ANIM_CORNUGON:
    case ANIM_GLABREZU:
    case ANIM_LEMURE:
        return TRUE;
    }

    return FALSE;
}

// 0x584D60
BOOLEAN IcewindMisc::IsElf(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_ELF;
}

// 0x584D80
BOOLEAN IcewindMisc::IsUmberhulk(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_UMBERHULK;
}

// 0x584DA0
BOOLEAN IcewindMisc::IsHalfElf(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_HALF_ELF;
}

// 0x584DC0
BOOLEAN IcewindMisc::IsBlind(CGameSprite* pSprite)
{
    return (pSprite->GetBaseStats()->m_generalState & STATE_BLIND) != 0
        || (pSprite->GetDerivedStats()->m_generalState & STATE_BLIND) != 0;
}

// 0x584DF0
BOOLEAN IcewindMisc::IsGolem(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_GOLEM;
}

// 0x584E10
BOOLEAN IcewindMisc::IsMinotaur(CGameSprite* pSprite)
{
    return pSprite->m_animation.m_animation->m_animationID == 0xE708;
}

// 0x584E30
BOOLEAN IcewindMisc::IsGood(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_GOOD:
    case CAIOBJECTTYPE_NEUTRAL_GOOD:
    case CAIOBJECTTYPE_CHAOTIC_GOOD:
        return TRUE;
    }

    return FALSE;
}

// 0x584E50
BOOLEAN IcewindMisc::IsNeutral(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_NEUTRAL:
    case CAIOBJECTTYPE_NEUTRAL_GOOD:
    case CAIOBJECTTYPE_NEUTRAL:
    case CAIOBJECTTYPE_NEUTRAL_EVIL:
    case CAIOBJECTTYPE_CHAOTIC_NEUTRAL:
        return TRUE;
    }

    return FALSE;
}

// 0x584EB0
BOOLEAN IcewindMisc::IsEvil(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_EVIL:
    case CAIOBJECTTYPE_NEUTRAL_EVIL:
    case CAIOBJECTTYPE_CHAOTIC_EVIL:
        return TRUE;
    }

    return FALSE;
}

// 0x584ED0
BOOLEAN IcewindMisc::IsPaladin(CGameSprite* pSprite)
{
    return (pSprite->GetAIType().m_nClassMask & CLASSMASK_PALADIN) != 0;
}

// 0x584FA0
BOOLEAN IcewindMisc::IsAcquatic(CGameSprite* pSprite)
{
    // NOTE: No assertion, so it's not pSprite->GetAnimation()->GetAnimationId()
    USHORT nID = pSprite->m_animation.m_animation->m_animationID;

    switch (nID) {
    case ANIM_ELEMENTAL_WATER:
    case ANIM_WATER_WEIRD:
    case ANIM_DROWNED_DEAD:
    case ANIM_TROLL_SCRAG:
    case ANIM_UMBER_HULK_VODYANOI:
    case ANIM_SAHUAGIN:
    case ANIM_SAHUAGIN_LARGE:
        return TRUE;
    }

    return FALSE;
}

// 0x584FF0
BOOLEAN IcewindMisc::IsLiving(CGameSprite* pSprite)
{
    if (pSprite->GetAIType().m_nGeneral == CAIObjectType::G_UNDEAD) {
        return FALSE;
    }

    if (pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_GOLEM) {
        return FALSE;
    }

    // NOTE: No assertion, so it's not pSprite->GetAnimation()->GetAnimationId()
    USHORT nID = pSprite->m_animation.m_animation->m_animationID;

    switch (nID) {
    case ANIM_SLIME_MUSTARD:
    case ANIM_ELEMENTAL_EARTH:
    case ANIM_ELEMENTAL_FIRE:
    case ANIM_ELEMENTAL_WATER:
    case ANIM_WATER_WEIRD:
    case ANIM_ANIMATED_PLATE:
    case ANIM_ANIMATED_PLATE_2:
    case ANIM_ANIMATED_PLATE_3:
        return FALSE;
    }

    return TRUE;
}

// 0x585070
BOOLEAN IcewindMisc::sud_585070(CGameSprite* pSprite)
{
    if (pSprite->GetAIType().m_nGeneral == CAIObjectType::G_UNDEAD) {
        return TRUE;
    }

    if (pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_ELEMENTAL) {
        return TRUE;
    }

    if (pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_GOLEM) {
        return TRUE;
    }

    if (pSprite->m_typeAI.m_nRace == CAIOBJECTTYPE_R_HUMAN) {
        if (pSprite->m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_AASIMAR
            || pSprite->m_typeAI.m_nSubRace == CAIOBJECTTYPE_SUBRACE_HUMAN_TIEFLING) {
            return TRUE;
        }
    }

    // NOTE: No assertion, so it's not pSprite->GetAnimation()->GetAnimationId()
    USHORT nID = pSprite->m_animation.m_animation->m_animationID;

    switch (nID) {
    case ANIM_DJINNI:
    case ANIM_DJINNI_LEGS:
    case ANIM_RAVER:
    case ANIM_ANIMATED_PLATE:
    case ANIM_ANIMATED_PLATE_2:
    case ANIM_ANIMATED_PLATE_3:
    case ANIM_TANARI:
    case ANIM_SALAMANDER:
    case ANIM_SALAMANDER_FROST:
    case ANIM_EC1D:
    case ANIM_CORNUGON:
    case ANIM_GLABREZU:
    case ANIM_LEMURE:
    case ANIM_KEG_1:
    case ANIM_KEG_2:
    case ANIM_KEG_3:
        return TRUE;
    }

    return FALSE;
}

// 0x585170
BOOLEAN IcewindMisc::IsMale(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nGender == CAIOBJECTTYPE_SEX_MALE;
}

// 0x585190
BOOLEAN IcewindMisc::IsLawful(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nAlignment) {
    case CAIOBJECTTYPE_LAWFUL_GOOD:
    case CAIOBJECTTYPE_LAWFUL_NEUTRAL:
    case CAIOBJECTTYPE_LAWFUL_EVIL:
        return TRUE;
    }

    return FALSE;
}

// 0x5851B0
BOOLEAN IcewindMisc::IsChaotic(CGameSprite* pSprite)
{
    switch (pSprite->GetAIType().m_nAlignment) {
    case CAIOBJECTTYPE_CHAOTIC_GOOD:
    case CAIOBJECTTYPE_CHAOTIC_NEUTRAL:
    case CAIOBJECTTYPE_CHAOTIC_EVIL:
        return TRUE;
    }

    return FALSE;
}

// 0x5851D0
BOOLEAN IcewindMisc::IsDead(CGameSprite* pSprite)
{
    DWORD generalState = pSprite->GetDerivedStats()->m_generalState;
    return (generalState & STATE_DEAD) != 0
        || (generalState & (STATE_STONE_DEATH | STATE_FROZEN_DEATH)) != 0;
}

// 0x5851F0
BOOLEAN IcewindMisc::IsPC(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nEnemyAlly == CAIObjectType::EA_PC;
}

// 0x585210
BOOLEAN IcewindMisc::sub_585210(CGameSprite* pSprite)
{
    BYTE nRace = pSprite->GetAIType().m_nRace;
    return nRace > 0 && nRace <= CAIOBJECTTYPE_R_GNOME;
}

// 0x585230
BOOLEAN IcewindMisc::sub_585230(CGameSprite* pSprite1, CGameSprite* pSprite2)
{
    if (pSprite1->GetAIType().m_nEnemyAlly <= CAIObjectType::EA_CONTROLCUTOFF
        && pSprite2->GetAIType().m_nEnemyAlly <= CAIObjectType::EA_CONTROLCUTOFF) {
        return TRUE;
    }

    if (pSprite1->GetAIType().m_nEnemyAlly >= CAIObjectType::EA_EVILCUTOFF
        && pSprite2->GetAIType().m_nEnemyAlly >= CAIObjectType::EA_EVILCUTOFF) {
        return TRUE;
    }

    return FALSE;
}

// 0x5852A0
BOOLEAN IcewindMisc::sub_5852A0(CGameSprite* pSprite1, CGameSprite* pSprite2)
{
    if (pSprite1->GetAIType().m_nEnemyAlly <= CAIObjectType::EA_GOODCUTOFF
        && pSprite2->GetAIType().m_nEnemyAlly >= CAIObjectType::EA_EVILCUTOFF) {
        return TRUE;
    }

    if (pSprite1->GetAIType().m_nEnemyAlly >= CAIObjectType::EA_EVILCUTOFF
        && pSprite2->GetAIType().m_nEnemyAlly <= CAIObjectType::EA_GOODCUTOFF) {
        return TRUE;
    }

    return FALSE;
}

// 0x585310
BOOLEAN IcewindMisc::sub_585310(CGameSprite* pSprite)
{
    return CAIObjectType::EA_GOODCUTOFF >= pSprite->GetAIType().m_nEnemyAlly;
}

// 0x585330
BOOLEAN IcewindMisc::IsAlignmentSame(CGameSprite* pSprite1, CGameSprite* pSprite2)
{
    return pSprite1->GetAIType().m_nAlignment == pSprite2->GetAIType().m_nAlignment;
}

// 0x585350
BOOLEAN IcewindMisc::IsGoodEvilSame(CGameSprite* pSprite1, CGameSprite* pSprite2)
{
    return ((pSprite1->GetAIType().m_nAlignment ^ pSprite2->GetAIType().m_nAlignment) & 0xF) == 0;
}

// 0x585380
CGameEffect* IcewindMisc::sub_585380(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    return CreateEffectDamage(pObject, 0x400000, numDice, diceSize, effectAmount, spellLevel, savingThrow);
}

// 0x5853B0
CGameEffect* IcewindMisc::sub_5853B0(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    return CreateEffectDamage(pObject, 0x80000, numDice, diceSize, effectAmount, spellLevel, savingThrow);
}

// 0x5853E0
CGameEffect* IcewindMisc::sub_5853E0(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    return CreateEffectDamage(pObject, 0x20000, numDice, diceSize, effectAmount, spellLevel, savingThrow);
}

// 0x585410
CGameEffect* IcewindMisc::sub_585410(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    return CreateEffectDamage(pObject, 0, numDice, diceSize, effectAmount, spellLevel, savingThrow);
}

// 0x585440
CGameEffect* IcewindMisc::CreateEffectDamage(CGameObject* pObject, DWORD dwFlags, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_DAMAGE);
    effect.effectAmount = effectAmount;
    effect.dwFlags = dwFlags;
    effect.spellLevel = spellLevel;
    effect.numDice = numDice;
    effect.diceSize = diceSize;
    effect.durationType = 1;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;
    effect.duration = 0;

    CGameEffectDamage* pEffect = static_cast<CGameEffectDamage*>(CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1)));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
        sub_5860F0(static_cast<CGameSprite*>(pObject), pEffect);
    }

    return pEffect;
}

// 0x585510
CGameEffect* IcewindMisc::CreateEffectImmunityToBackstab(CGameObject* pObject, DWORD duration)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_IMMUNITYTOBACKSTAB);
    effect.spellLevel = 0;
    effect.durationType = 0;
    effect.savingThrow = 0;
    effect.duration = duration;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags &= ~0x1;

    return pEffect;
}

// 0x5855B0
CGameEffect* IcewindMisc::CreateEffectSTR(CGameObject* pObject, int effectAmount, DWORD duration, BYTE spellLevel)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_STR);
    effect.spellLevel = spellLevel;
    effect.effectAmount = effectAmount;
    effect.durationType = 0;
    effect.dwFlags = 0;
    effect.savingThrow = 0;
    effect.duration = duration;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x585650
CGameEffect* IcewindMisc::CreateEffectBerserk(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_BERSERK);
    effect.durationType = 0;
    effect.duration = duration;
    effect.spellLevel = spellLevel;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x5856F0
CGameEffect* IcewindMisc::CreateEffectPortraitIcon(CGameObject* pObject, DWORD dwFlags, DWORD duration, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_PORTRAITICON);
    effect.spellLevel = spellLevel;
    effect.dwFlags = dwFlags;
    effect.duration = duration;
    effect.durationType = 0;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x585790
CGameEffect* IcewindMisc::CreateEffectDisplayString(CGameObject* pObject, int effectAmount, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_DISPLAYSTRING);
    effect.effectAmount = effectAmount;
    effect.spellLevel = spellLevel;
    effect.durationType = 1;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    return pEffect;
}

// 0x585830
CGameEffect* IcewindMisc::CreateEffectVisualSpellHit(CGameObject* pObject, DWORD dwFlags, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_VISUALSPELLHIT);
    effect.dwFlags = dwFlags;
    effect.durationType = 1;
    effect.spellLevel = spellLevel;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    return pEffect;
}

// 0x5858D0
CGameEffect* IcewindMisc::CreateEffectHitPoints(CGameObject* pObject, int effectAmount, DWORD duration, BYTE spellLevel, BYTE targetType)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_HITPOINTS);
    effect.targetType = targetType;
    effect.effectAmount = effectAmount;
    effect.spellLevel = spellLevel;
    effect.dwFlags = 0;

    if (duration != 0) {
        effect.durationType = 0;
        effect.duration = duration;
    } else {
        effect.durationType = 1;
    }

    effect.numDice = 0;
    effect.diceSize = 0;
    effect.savingThrow = 0;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x585990
CGameEffect* IcewindMisc::CreateEffectImmunitySpell(CGameObject* pObject, const BYTE* res, DWORD dwFlags, DWORD duration, BYTE spellLevel, BYTE targetType)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_IMMUNITYSPELL);
    effect.targetType = targetType;
    effect.dwFlags = dwFlags;
    effect.durationType = 0;
    effect.spellLevel = spellLevel;
    effect.duration = duration;
    strncpy(reinterpret_cast<char*>(effect.res),
        reinterpret_cast<const char*>(res),
        RESREF_SIZE);
    effect.savingThrow = 0;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    return pEffect;
}

// 0x585A40
CGameEffect* IcewindMisc::CreateEffectRemoveAllOfType(CGameObject* pObject, DWORD dwFlags, BYTE spellLevel)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_REMOVEALLOFTYPE);
    effect.spellLevel = spellLevel;
    effect.durationType = 1;
    effect.dwFlags = dwFlags;
    effect.targetType = 2;
    effect.savingThrow = 0;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    return pEffect;
}

// 0x585AE0
CGameEffect* IcewindMisc::CreateEffectConfusion(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_CONFUSION);
    effect.durationType = 0;
    effect.duration = duration;
    effect.spellLevel = spellLevel;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x585B80
CGameEffect* IcewindMisc::CreateEffectStun(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_STUN);
    effect.durationType = 0;
    effect.duration = duration;
    effect.spellLevel = spellLevel;
    effect.savingThrow = savingThrow;
    effect.targetType = 2;
    effect.dwFlags = 0;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();
    pEffect->m_flags |= 0x1;

    return pEffect;
}

// 0x585C20
CGameEffect* IcewindMisc::CreateEffectSkillUnsummon(CGameObject* pObject, DWORD duration, BYTE spellLevel)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, CGAMEEFFECT_SKILLUNSUMMON);
    effect.spellLevel = spellLevel;
    effect.duration = duration;
    effect.durationType = 4;
    effect.targetType = 2;
    effect.savingThrow = 0;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    pEffect->m_source = pObject->GetPos();
    pEffect->m_sourceID = pObject->GetId();

    return pEffect;
}

// 0x585CC0
CGameEffect* IcewindMisc::CreateEffectColorGlowDissipate(BYTE a1, BYTE a2, BYTE a3, BYTE a4)
{
    ITEM_EFFECT effect;
    CGameEffect::ClearItemEffect(&effect, ICEWIND_CGAMEEFFECT_COLORGLOWDISSIPATE);
    effect.dwFlags = a4 << 16;
    effect.targetType = 2;
    effect.savingThrow = 0;
    effect.effectAmount = (a3 << 24) | (a2 << 16) | (a1 << 8);
    effect.durationType = 1;

    CGameEffect* pEffect = CGameEffect::DecodeEffect(&effect,
        CPoint(-1, -1),
        -1,
        CPoint(-1, -1));

    return pEffect;
}

// 0x585D50
INT IcewindMisc::GetSneakAttackRolls(CGameSprite* pSprite)
{
    if ((pSprite->GetAIType().m_nClassMask & CLASSMASK_ROGUE) != 0) {
        return (pSprite->GetDerivedStats()->GetClassLevel(CAIOBJECTTYPE_C_ROGUE) - 1) / 2 + 1;
    } else {
        return 0;
    }
}

// 0x585D80
INT IcewindMisc::GetSneakAttackDice()
{
    return 6;
}

// 0x585D90
INT IcewindMisc::sub_585D90()
{
    return 21;
}

// 0x585DA0
BOOLEAN IcewindMisc::sub_585DA0(CGameSprite* pSprite)
{
    return (pSprite->GetClassLevel(CAIOBJECTTYPE_C_ROGUE) >= 2
               || pSprite->HasClassLevel(CAIOBJECTTYPE_C_MONK))
        && (pSprite->GetDerivedStats()->m_generalState & (STATE_DEAD | STATE_HELPLESS | STATE_STUNNED | STATE_SLEEPING)) == 0
        && pSprite->m_nSequence != 5
        && !pSprite->sub_724690(2)
        && !pSprite->sub_724690(3);
}

// 0x585E00
CButtonData* IcewindMisc::CreateButtonData(BYTE* resRef)
{
    CResRef cResRef(resRef);
    CSpell cSpell(cResRef);
    SPELL_ABILITY* ability = cSpell.GetAbility(0);

    CButtonData* button = new CButtonData();

    // NOTE: Original code creates temporary `CString` whose duration is only
    // this assignment implying some inlined function.
    button->m_icon = ability->quickSlotIcon;

    button->m_name = cSpell.GetGenericName();
    button->m_abilityId.m_itemType = 1;
    button->m_abilityId.m_res = resRef;
    button->m_abilityId.m_targetType = ability->actionType;
    button->m_abilityId.field_10 = cSpell.GetGenericName();
    button->m_bDisabled = FALSE;
    button->m_bDisplayCount = 0;

    return button;
}

// 0x5860F0
void IcewindMisc::sub_5860F0(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (pEffect->m_effectID == CGAMEEFFECT_DAMAGE) {
        int nDamageMod;

        switch (pEffect->m_dwFlags) {
        case 0x0:
        case 0x4000000:
        case 0x8000000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModCrushing;
            break;
            break;
        case 0x10000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModAcid;
            break;
        case 0x20000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModCold;
            break;
        case 0x40000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModElectricity;
            break;
        case 0x80000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModFire;
            break;
        case 0x100000:
        case 0x2000000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModPiercing;
            break;
        case 0x200000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModPoison;
            break;
        case 0x400000:
        case 0x10000000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModMagic;
            break;
        case 0x1000000:
            nDamageMod = pSprite->GetDerivedStats()->m_nDamageModSlashing;
            break;
        default:
            nDamageMod = 0;
            break;
        }

        if (nDamageMod != 0) {
            pEffect->m_effectAmount += nDamageMod * (pEffect->m_effectAmount + pEffect->m_numDice * pEffect->m_diceSize / 2) / 100;
        }
    }
}

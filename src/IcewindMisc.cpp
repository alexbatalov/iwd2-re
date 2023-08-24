#include "IcewindMisc.h"

#include "CGameSprite.h"
#include "CUtil.h"

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

// 0x584DF0
BOOLEAN IcewindMisc::IsGolem(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nRace == CAIOBJECTTYPE_R_GOLEM;
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

// 0x5851F0
BOOLEAN IcewindMisc::IsPC(CGameSprite* pSprite)
{
    return pSprite->GetAIType().m_nEnemyAlly == CAIObjectType::EA_PC;
}

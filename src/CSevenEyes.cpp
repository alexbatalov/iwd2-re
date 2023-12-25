#include "CSevenEyes.h"

#include <string>

#include "CGameEffect.h"
#include "CGameSprite.h"
#include "IcewindCGameEffects.h"
#include "IcewindMisc.h"

// 0x76C2F0
bool CSevenEyes::CheckEyeOfMind(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_THE_MIND]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_BERSERK:
    case CGAMEEFFECT_CHARM:
    case CGAMEEFFECT_PANIC:
    case CGAMEEFFECT_FEEBLEMINDEDNESS:
    case CGAMEEFFECT_CONFUSION:
        immune = true;
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (s.compare("SPWI419") != 0
        && s.compare("SPIN247") != 0
        && s.compare("SPWI420") != 0
        && s.compare("SPWI421") != 0
        && s.compare("SPWI411") != 0
        && s.compare("SPPR102") != 0
        && s.compare("SPPR311") != 0
        && s.compare("SPPR715") != 0
        && !immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFMIND, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_THE_MIND));

    // "Eye of the Mind blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21654, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76C6B0
bool CSevenEyes::CheckEyeOfSword(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_THE_SWORD]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_DAMAGE:
        switch ((pEffect->m_dwFlags >> 16) << 16) {
        case 0:
        case 0x100000:
        case 0x1000000:
        case 0x2000000:
        case 0x4000000:
            immune = true;
            break;
        }
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEYOFSWORD, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_THE_SWORD));

    // "Eye of the Sword blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21653, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76C8C0
bool CSevenEyes::CheckEyeOfMage(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_THE_MAGE]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_DAMAGE:
        switch ((pEffect->m_dwFlags >> 16) << 16) {
        case 0x10000:
        case 0x20000:
        case 0x40000:
        case 0x80000:
            immune = true;
            break;
        }
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFMAGE, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_THE_MAGE));

    // "Eye of the Mage blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21652, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76CAC0
bool CSevenEyes::CheckEyeOfVenom(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_VENOM]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_DAMAGE:
        if (((pEffect->m_dwFlags >> 16) << 16) == 0x200000) {
            immune = true;
        }
        break;
    case CGAMEEFFECT_POISON:
        immune = true;
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFVENOM, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_VENOM));

    // "Eye of Venom blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21651, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76CCB0
bool CSevenEyes::CheckEyeOfSpirit(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_THE_SPIRIT]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case ICEWIND_CGAMEEFFECT_MAGIC_DEATH:
        immune = true;
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFSPIRIT, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_THE_SPIRIT));

    // "Eye of the Spirit blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21650, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76CE80
bool CSevenEyes::CheckEyeOfFortitude(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_FORTITUDE]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_SILENCE:
    case CGAMEEFFECT_STUN:
    case CGAMEEFFECT_BLINDNESS:
    case CGAMEEFFECT_DEAFNESS:
    case CGAMEEFFECT_HOLDCREATURE:
    case CGAMEEFFECT_HOLDCREATURESPELL_175:
        immune = true;
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFFORTITUDE, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_FORTITUDE));

    // "Eye of Fortitude blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21649, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

// 0x76D110
bool CSevenEyes::CheckEyeOfStone(CGameSprite* pSprite, CGameEffect* pEffect)
{
    if (!pSprite->GetDerivedStats()->m_spellStates[SPLSTATE_EYE_OF_STONE]) {
        return false;
    }

    bool immune = false;
    switch (pEffect->m_effectID) {
    case CGAMEEFFECT_PETRIFICATION:
        immune = true;
        break;
    }

    std::string s(pEffect->m_sourceRes.GetResRefStr());

    if (!immune) {
        return false;
    }

    pSprite->AddEffect(IcewindMisc::CreateEffectRemoveAllOfType(pSprite, ICEWIND_CGAMEEFFECT_EYEOFSTONE, 0),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    pSprite->RemoveSpecialAbility(CResRef(RESREF_EYE_OF_STONE));

    // "Eye of Stone blocks effect and dissipates."
    IcewindMisc::sub_584880(pSprite, 21648, 0);

    pSprite->AddEffect(IcewindMisc::CreateEffectImmunitySpell(pSprite, reinterpret_cast<const BYTE*>(s.c_str()), 0, 1, 0, 2),
        CGameAIBase::EFFECT_LIST_TIMED,
        TRUE,
        TRUE);

    return true;
}

#ifndef CRESSPELL_H_
#define CRESSPELL_H_

#include "BalDataTypes.h"
#include "CRes.h"

class CResSpell : public CRes {
public:
    CResSpell();

    void* Demand();
    SPELL_ABILITY* GetAbility(int nAbility);
    ITEM_EFFECT* GetAbilityEffect(int nAbility, int nEffect, int a4);
    int GetAbilityEffectNo(int nAbility);
    ITEM_EFFECT* GetCastingEffect(int nEffect);
    int GetCastingEffectNo();
    int Release();
    BOOL Parse(void* pData);

    /* 0050 */ SPELL_ABILITY* m_pAbilities;
    /* 0054 */ ITEM_EFFECT* m_pEffects;
    /* 0058 */ SPELL_HEADER* m_pHeader;
    /* 005C */ BOOL m_bParsed;
};

#endif /* CRESSPELL_H_ */

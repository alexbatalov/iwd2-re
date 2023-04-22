#ifndef CSPELL_H_
#define CSPELL_H_

#include "CResSpell.h"

class CSpell : public CResHelper<CResSpell, 1006> {
public:
    BOOL Demand();
    BOOL Release();
    INT GetAbilityCount();
    BOOL GetIcon(BYTE* resRef);
    SPELL_ABILITY* GetAbility(LONG nAbilityNo) const;
    SHORT GetLevel() const;
    DWORD GetNotUsableBy() const;
    STRREF GetGenericName() const;
    STRREF GetDescription() const;
    SHORT GetCasterType() const;
    SHORT GetCastingEffectNo() const;
    WORD GetAnimationType() const;
    DWORD GetItemFlags() const;
    BYTE GetSchool() const;
};

#endif /* CSPELL_H_ */

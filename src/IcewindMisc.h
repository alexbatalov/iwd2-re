#ifndef ICEWINDMISC_H_
#define ICEWINDMISC_H_

#include "mfc.h"

#include "BalDataTypes.h"

class CButtonData;
class CGameEffect;
class CGameObject;
class CGameSprite;

// NOTE: The name is obviously wrong and misleading, but at least it matches
// file name (which is seen via assertions).
class IcewindMisc {
public:
    static INT Roll(INT nRolls, INT nSides);
    static CPoint sub_584610(INT nDirection);
    static CPoint sub_5847B0(const CPoint& pt, int x, int y, int radius);
    static void sub_584880(CGameSprite* pSprite, STRREF strRef, INT nNumber);
    static BOOLEAN IsUndead(CGameSprite* pSprite);
    static BOOLEAN IsImmuneToFire(CGameSprite* pSprite);
    static BOOLEAN IsImmuneToCold(CGameSprite* pSprite);
    static BOOLEAN IsHumanoid(CGameSprite* pSprite);
    static BOOLEAN IsAberration(CGameSprite* pSprite);
    static BOOLEAN IsAnimal(CGameSprite* pSprite);
    static BOOLEAN IsElemental(CGameSprite* pSprite);
    static BOOLEAN IsFungus(CGameSprite* pSprite);
    static BOOLEAN IsLarge(CGameSprite* pSprite);
    static BOOLEAN IsOutsider(CGameSprite* pSprite);
    static BOOLEAN IsElf(CGameSprite* pSprite);
    static BOOLEAN IsUmberhulk(CGameSprite* pSprite);
    static BOOLEAN IsHalfElf(CGameSprite* pSprite);
    static BOOLEAN IsBlind(CGameSprite* pSprite);
    static BOOLEAN IsGolem(CGameSprite* pSprite);
    static BOOLEAN IsMinotaur(CGameSprite* pSprite);
    static BOOLEAN IsGood(CGameSprite* pSprite);
    static BOOLEAN IsNeutral(CGameSprite* pSprite);
    static BOOLEAN IsEvil(CGameSprite* pSprite);
    static BOOLEAN IsPaladin(CGameSprite* pSprite);
    static BOOLEAN IsAcquatic(CGameSprite* pSprite);
    static BOOLEAN IsLiving(CGameSprite* pSprite);
    static BOOLEAN sud_585070(CGameSprite* pSprite);
    static BOOLEAN IsMale(CGameSprite* pSprite);
    static BOOLEAN IsLawful(CGameSprite* pSprite);
    static BOOLEAN IsChaotic(CGameSprite* pSprite);
    static BOOLEAN IsDead(CGameSprite* pSprite);
    static BOOLEAN IsPC(CGameSprite* pSprite);
    static BOOLEAN sub_585210(CGameSprite* pSprite);
    static BOOLEAN sub_585230(CGameSprite* pSprite1, CGameSprite* pSprite2);
    static BOOLEAN sub_5852A0(CGameSprite* pSprite1, CGameSprite* pSprite2);
    static BOOLEAN sub_585310(CGameSprite* pSprite);
    static BOOLEAN IsAlignmentSame(CGameSprite* pSprite1, CGameSprite* pSprite2);
    static BOOLEAN IsGoodEvilSame(CGameSprite* pSprite1, CGameSprite* pSprite2);
    static CGameEffect* sub_585380(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* sub_5853B0(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* sub_5853E0(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* sub_585410(CGameObject* pObject, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectImmunityToBackstab(CGameObject* pObject, DWORD duration);
    static CGameEffect* CreateEffectSTR(CGameObject* pObject, int effectAmount, DWORD duration, BYTE spellLevel);
    static CGameEffect* CreateEffectBerserk(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectPortraitIcon(CGameObject* pObject, DWORD dwFlags, DWORD duration, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectDisplayString(CGameObject* pObject, int effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectHitPoints(CGameObject* pObject, int effectAmount, DWORD duration, BYTE spellLevel, BYTE targetType);
    static CGameEffect* CreateEffectImmunitySpell(CGameObject* pObject, const BYTE* res, DWORD dwFlags, DWORD duration, BYTE spellLevel, BYTE targetType);
    static CGameEffect* CreateEffectConfusion(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectDamage(CGameObject* pObject, DWORD dwFlags, DWORD numDice, DWORD diceSize, LONG effectAmount, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectStun(CGameObject* pObject, DWORD duration, BYTE spellLevel, DWORD savingThrow);
    static CGameEffect* CreateEffectSkillUnsummon(CGameObject* pObject, DWORD duration, BYTE spellLevel);
    static INT GetSneakAttackRolls(CGameSprite* pSprite);
    static INT GetSneakAttackDice();
    static INT sub_585D90();
    static BOOLEAN sub_585DA0(CGameSprite* pSprite);
    static CButtonData* CreateButtonData(BYTE* resRef);
    static void sub_5860F0(CGameSprite* pSprite, CGameEffect* pEffect);
};

#endif /* ICEWINDMISC_H_ */

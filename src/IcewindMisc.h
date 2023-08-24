#ifndef ICEWINDMISC_H_
#define ICEWINDMISC_H_

#include "mfc.h"

class CGameSprite;

// NOTE: The name is obviously wrong and misleading, but at least it matches
// file name (which is seen via assertions).
class IcewindMisc {
public:
    static BOOLEAN IsUndead(CGameSprite* pSprite);
    static BOOLEAN IsImmuneToFire(CGameSprite* pSprite);
    static BOOLEAN IsImmuneToCold(CGameSprite* pSprite);
    static BOOLEAN IsHumanoid(CGameSprite* pSprite);
    static BOOLEAN IsAberration(CGameSprite* pSprite);
    static BOOLEAN IsAnimal(CGameSprite* pSprite);
    static BOOLEAN IsElemental(CGameSprite* pSprite);
    static BOOLEAN IsFungus(CGameSprite* pSprite);
    static BOOLEAN IsElf(CGameSprite* pSprite);
    static BOOLEAN IsUmberhulk(CGameSprite* pSprite);
    static BOOLEAN IsHalfElf(CGameSprite* pSprite);
    static BOOLEAN IsGolem(CGameSprite* pSprite);
    static BOOLEAN IsGood(CGameSprite* pSprite);
    static BOOLEAN IsNeutral(CGameSprite* pSprite);
    static BOOLEAN IsEvil(CGameSprite* pSprite);
    static BOOLEAN IsPaladin(CGameSprite* pSprite);
    static BOOLEAN IsMale(CGameSprite* pSprite);
    static BOOLEAN IsLawful(CGameSprite* pSprite);
    static BOOLEAN IsChaotic(CGameSprite* pSprite);
    static BOOLEAN IsPC(CGameSprite* pSprite);
};

#endif /* ICEWINDMISC_H_ */

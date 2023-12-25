#ifndef CSEVENEYES_H_
#define CSEVENEYES_H_

class CGameSprite;
class CGameEffect;

class CSevenEyes {
public:
    static bool CheckEyeOfMind(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfSword(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfMage(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfVenom(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfSpirit(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfFortitude(CGameSprite* pSprite, CGameEffect* pEffect);
    static bool CheckEyeOfStone(CGameSprite* pSprite, CGameEffect* pEffect);
};

#endif /* CSEVENEYES_H_ */

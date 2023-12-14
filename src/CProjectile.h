#ifndef CPROJECTILE_H_
#define CPROJECTILE_H_

#include "CGameEffectList.h"
#include "CGameObject.h"

class CProjectile : public CGameObject {
public:
    /* 0068 */ BOOLEAN IsProjectile() override;
    /* 0074 */ virtual void RemoveSelf();

    void AddEffect(CGameEffect* pEffect);
    LONG DetermineHeight(CGameSprite* pSprite);

    /* 006E */ WORD m_projectileType;
    /* 007E */ CGameEffectList m_effectList;
    /* 016A */ BOOLEAN m_bHasHeight;
};

#endif /* CPROJECTILE_H_ */

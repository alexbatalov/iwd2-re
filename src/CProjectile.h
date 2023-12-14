#ifndef CPROJECTILE_H_
#define CPROJECTILE_H_

#include "CGameObject.h"

class CProjectile : public CGameObject {
public:
    /* 0068 */ BOOLEAN IsProjectile() override;
    /* 0074 */ virtual void RemoveSelf();

    LONG DetermineHeight(CGameSprite* pSprite);

    /* 016A */ BOOLEAN m_bHasHeight;
};

#endif /* CPROJECTILE_H_ */

#ifndef CPROJECTILE_H_
#define CPROJECTILE_H_

#include "CGameEffectList.h"
#include "CGameObject.h"
#include "CSound.h"

class CGameArea;

class CProjectile : public CGameObject {
public:
    /* 0068 */ BOOLEAN IsProjectile() override;
    /* 006C */ virtual void Fire(CGameArea* pArea, LONG source, LONG target, CPoint targetPos, LONG nHeight, SHORT nType);
    /* 0070 */ virtual void OnArrival();
    /* 0074 */ virtual void RemoveSelf();
    /* 0078 */ virtual void DeliverEffects();
    /* 007C */ virtual void CallBack();

    void AddEffect(CGameEffect* pEffect);
    void ClearEffects();
    LONG DetermineHeight(CGameSprite* pSprite);
    SHORT GetDirection(CPoint target);
    void PlaySound(CResRef resRef, BOOL loop, BOOL fireAndForget);

    /* 006E */ WORD m_projectileType;
    /* 0076 */ LONG m_targetId;
    /* 007A */ LONG m_callBackProjectile;
    /* 007E */ CGameEffectList m_effectList;
    /* 00EA */ CGameArea* m_pArea;
    /* 00EE */ CSound m_sound;
    /* 015E */ CResRef m_arrivalSoundRef;
    /* 0166 */ BOOL m_loopArrivalSound;
    /* 016A */ BOOLEAN m_bHasHeight;
    /* 0182 */ LONG field_182;
};

#endif /* CPROJECTILE_H_ */

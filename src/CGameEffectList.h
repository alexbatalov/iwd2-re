#ifndef CGAMEEFFECTLIST_H_
#define CGAMEEFFECTLIST_H_

#include "mfc.h"

class CGameEffect;
class CGameSprite;

class CGameEffectList : public CTypedPtrList<CPtrList, CGameEffect*> {
public:
    CGameEffectList();
    ~CGameEffectList() override;

    POSITION GetPosCurrent();
    void RemoveAllOfType(CGameSprite* pSprite, WORD effectID, POSITION posLeave, LONG effectAmount);
    void RemoveAllEffectsIgnoreMoreThenPermanent(POSITION posLeave, BOOL checkDispellable, BOOL useLevelDiff, BYTE prob, BYTE dispelLevel);
    ULONG Marshal(BYTE** ptrPtr, BYTE version, BOOL moreThenPermanentOnly);
    void Unmarshal(BYTE* data, ULONG nSize, CGameSprite* pSprite, BYTE version);
    BOOL HandleList(CGameSprite* pSprite);
    BOOL CheckEffects();

    /* 001C */ POSITION m_posNext;
    /* 0020 */ POSITION m_posCurrent;
    /* 0024 */ BOOL m_newEffect;
    /* 0028 */ BOOL m_retry;
};

#endif /* CGAMEEFFECTLIST_H_ */

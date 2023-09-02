#ifndef CGAMECONTAINER_H_
#define CGAMECONTAINER_H_

#include "CGameAIBase.h"

class CItem;
class CResRef;

class CGameContainer : public CGameAIBase {
public:
    void SetFlags(DWORD dwFlags);
    void SetTrapActivated(WORD active);
    void SetTrapDetected(WORD state);
    void SetDrawPoly(SHORT time);
    SHORT FindItemSlot(const CResRef& res);

    /* 05AE */ CTypedPtrList<CPtrList, CItem*> m_lstItems;
    /* 088E */ DWORD m_dwFlags;
    /* 0896 */ WORD m_trapActivated;
    /* 0898 */ WORD m_trapDetected;
    /* 08D0 */ SHORT m_drawPoly;
};

#endif /* CGAMECONTAINER_H_ */

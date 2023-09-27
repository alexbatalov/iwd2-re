#ifndef CGAMECONTAINER_H_
#define CGAMECONTAINER_H_

#include "CGameAIBase.h"
#include "CResRef.h"

class CItem;

class CGameContainer : public CGameAIBase {
public:
    CGameContainer(CGameArea* pArea, const CRect& rBound);
    /* 000C */ void AIUpdate() override;
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0050 */ BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter) override;

    void CompressContainer();
    CItem* GetItem(SHORT nSlotNum);
    void SetItem(SHORT nSlotNum, CItem* pItem);
    void SetFlags(DWORD dwFlags);
    void SetTrapActivated(WORD active);
    void SetTrapDetected(WORD state);
    void SetDrawPoly(SHORT time);
    SHORT FindItemSlot(const CResRef& res);
    SHORT CountItem(const CResRef& res);

    void SetScriptRes(CString scriptRes);

    /* 05AE */ CTypedPtrList<CPtrList, CItem*> m_lstItems;
    /* 05CA */ WORD m_containerType;
    /* 0863 */ BOOLEAN m_bDeleteMe;
    /* 0864 */ RESREF m_scriptRes;
    /* 088C */ WORD m_lockDifficulty;
    /* 088E */ DWORD m_dwFlags;
    /* 0892 */ WORD m_trapDetectionDifficulty;
    /* 0894 */ WORD m_trapRemovalDifficulty;
    /* 0896 */ WORD m_trapActivated;
    /* 0898 */ WORD m_trapDetected;
    /* 089A */ CPoint m_posTrapOrigin;
    /* 08C4 */ CResRef m_keyType;
    /* 08D0 */ SHORT m_drawPoly;
};

#endif /* CGAMECONTAINER_H_ */

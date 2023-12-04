#ifndef CGAMECONTAINER_H_
#define CGAMECONTAINER_H_

#include "CGameAIBase.h"
#include "CResRef.h"
#include "CVidCell.h"
#include "FileFormat.h"

class CItem;

class CGameContainer : public CGameAIBase {
public:
    static const CResRef RESREF_AR6051;

    CGameContainer(CGameArea* pArea, CAreaFileContainer* pContainerObject, CAreaPoint* pPoints, WORD maxPts, CCreatureFileItem* pItems, DWORD maxItems);
    CGameContainer(CGameArea* pArea, const CRect& rBound);
    /* 0000 */ ~CGameContainer() override;
    /* 000C */ void AIUpdate() override;
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0050 */ BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter) override;
    /* 0058 */ void SetCursor(LONG nToolTip) override;

    void CompressContainer();
    CItem* GetItem(SHORT nSlotNum);
    void SetItem(SHORT nSlotNum, CItem* pItem);
    void sub_480480(SHORT nSlotNum, CItem* pItem);
    BOOLEAN PlaceItemInBlankSlot(CItem* pItem, BOOLEAN bCompressContainer, SHORT nRecommendedSlotNum);
    void RefreshRenderPile();
    void OpenContainer(const CAIObjectType& user);
    void SetFlags(DWORD dwFlags);
    void SetTrapActivated(WORD active);
    void SetTrapDetected(WORD state);
    void SetDrawPoly(SHORT time);
    SHORT FindItemSlot(const CResRef& res);
    SHORT CountItem(const CResRef& res);

    void SetScriptRes(CString scriptRes);
    SHORT GetNumItems();

    /* 0598 */ CRect m_rBounding;
    /* 05A8 */ CPoint* m_pPolygon;
    /* 05AC */ WORD m_nPolygon;
    /* 05AE */ CTypedPtrList<CPtrList, CItem*> m_lstItems;
    /* 05CA */ WORD m_containerType;
    /* 05CC */ CPoint m_ptWalkToUse;
    /* 05D4 */ CVidCell m_pileVidCell[3];
    /* 0863 */ BOOLEAN m_bDeleteMe;
    /* 0864 */ RESREF m_scriptRes;
    /* 088C */ WORD m_lockDifficulty;
    /* 088E */ DWORD m_dwFlags;
    /* 0892 */ WORD m_trapDetectionDifficulty;
    /* 0894 */ WORD m_trapRemovalDifficulty;
    /* 0896 */ WORD m_trapActivated;
    /* 0898 */ WORD m_trapDetected;
    /* 089A */ CPoint m_posTrapOrigin;
    /* 0862 */ BYTE m_nPileVidCell;
    /* 08A2 */ WORD m_triggerRange;
    /* 08A4 */ SCRIPTNAME m_ownedBy;
    /* 08C4 */ CResRef m_keyType;
    /* 08CC */ DWORD m_breakDifficulty;
    /* 08EA */ CAreaPoint* field_8EA;
    /* 08D0 */ SHORT m_drawPoly;
    /* 08D2 */ int field_8D2;
    /* 08D6 */ CArray<CRect*> field_8D6;
};

#endif /* CGAMECONTAINER_H_ */

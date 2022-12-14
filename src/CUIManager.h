#ifndef CUIMANAGER_H_
#define CUIMANAGER_H_

#include <afx.h>
#include <afxmt.h>
#include <afxtempl.h>

#include "BalDataTypes.h"
#include "CResRef.h"

class CUIControlBase;
class CUIPanel;
class CWarp;

class CUIManager {
public:
    CUIManager();
    ~CUIManager();
    void AddPanel(UI_PANELHEADER* panelInfo);
    void ReorderPanelAfter(DWORD nID1, DWORD nID2);
    CUIPanel* GetPanel(DWORD nID);
    void SetCapture(CUIControlBase* pControl, unsigned char a3);
    void ClearTooltip();
    void OnLButtonUp(CPoint pt);
    void OnRButtonUp(CPoint pt);
    BOOL OnKeyDown(SHORT nKey);
    void Render();
    void InvalidateRect(const CRect* rect);
    void InvalidateCursorRect(const CRect& rect);
    void ForceToolTip();
    void ShiftPanels(const CPoint& pt);

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ CResRef field_8;
    /* 0010 */ CWarp* m_pWarp; // #guess
    /* 0014 */ CUIControlBase* m_pFocusedControl; // #guess
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ int field_28;
    /* 002C */ unsigned char field_2C;
    /* 002E */ unsigned char field_2E;
    /* 002D */ unsigned char field_2D;
    /* 0032 */ int field_32;
    /* 0036 */ CCriticalSection field_36;
    /* 0056 */ CCriticalSection field_56;
    /* 0076 */ int field_76;
    /* 007A */ CRect field_7A;
    /* 008A */ CRect field_8A;
    /* 009A */ CRect field_9A;
    /* 00AA */ int field_AA;
    /* 00AE */ CTypedPtrList<CPtrList, CUIPanel*> m_lPanels; // #guess
};

#endif /* CUIMANAGER_H_ */

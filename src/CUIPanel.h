#ifndef CUIPANEL_H_
#define CUIPANEL_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "CVidMosaic.h"

class CUIControlBase;
class CUIManager;

class CUIPanel {
public:
    CUIPanel(CUIManager* manager, UI_PANELHEADER* panelInfo);
    void SetInactiveRender(BOOL bInactiveRender);
    void SetEnabled(BOOL bEnabled);
    ~CUIPanel();
    void AddControl(UI_CONTROL* controlInfo);
    BOOL RemoveControl(DWORD nID);
    DWORD TimerAsynchronousUpdate();
    CUIControlBase* GetControl(DWORD nID);
    BOOL IsOver(const CPoint& pt);
    BOOL sub_4D2D20();
    BOOL sub_4D2D50();
    BOOL OnLButtonDown(const CPoint& pt);
    BOOL OnLButtonDblClk(const CPoint& pt);
    void OnMouseMove(const CPoint& pt);
    BOOL OnRButtonDown(const CPoint& pt);
    void Render();
    void RenderDither(const CRect& rClip);
    void InvalidateRect(const CRect* pRect);
    void SetActive(BOOL bActive);
    void SetBackgroundResRef(CResRef cNewResRef, BOOL bDoubleSize);

    /* 0000 */ CUIManager* m_pManager; // #guess
    /* 0004 */ CTypedPtrList<CPtrList, CUIControlBase*> m_lControls; // #guess
    /* 0020 */ DWORD m_nID;
    /* 0024 */ CPoint m_ptOrigin;
    /* 0030 */ CPoint m_ptBaseOrigin;
    /* 0034 */ CSize m_size;
    /* 003C */ WORD m_wFlags;
    /* 003E */ CVidMosaic m_mosBackground;
    /* 00F2 */ SHORT m_nRenderCount;
    /* 00F4 */ BOOL m_bActive;
    /* 00F8 */ CRect m_rDirty;
    /* 0108 */ BOOLEAN m_bNeedAsyncUpdate;
    /* 0109 */ BOOLEAN m_bNeedMouseMove;
    /* 010A */ BOOL m_bInactiveRender;
    /* 010E */ BOOL m_bEnabled;
    /* 0112 */ int field_112;
    /* 0116 */ CRect field_116;
    /* 0126 */ int field_126;
};

#endif /* CUIPANEL_H_ */

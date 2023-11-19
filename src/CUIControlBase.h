#ifndef CUICONTROLBASE_H_
#define CUICONTROLBASE_H_

#include "mfc.h"

#include "BalDataTypes.h"

class CUIPanel;

class CUIControlBase {
public:
    static CUIControlBase* CreateControl(CUIPanel* pPanel, UI_CONTROL* controlInfo);

    CUIControlBase(CUIPanel* pPanel, UI_CONTROL* controlInfo, int a4);
    /* 0000 */ virtual ~CUIControlBase();
    /* 0004 */ virtual void SetActive(BOOLEAN bActive);
    /* 0008 */ virtual BOOL IsOverPixel(const CPoint& pt);
    /* 000C */ virtual void KillFocus();
    /* 0010 */ virtual void SetFocus();
    /* 0014 */ virtual void OnMouseMove(CPoint pt);
    /* 0018 */ virtual BOOL OnLButtonDown(CPoint pt);
    /* 001C */ virtual void OnLButtonUp(CPoint pt);
    /* 0020 */ virtual BOOL OnLButtonDblClk(CPoint pt);
    /* 0024 */ virtual BOOL OnRButtonDown(CPoint pt);
    /* 0028 */ virtual void OnRButtonUp(CPoint pt);
    /* 002C */ virtual void OnKeyDown(short nKey);
    /* 0030 */ virtual void TimerAsynchronousUpdate(BOOLEAN bInside);
    /* 0034 */ virtual int GetToolTipStrRef();
    /* 0038 */ virtual int GetSecondaryToolTipStrRef();
    /* 003C */ virtual int GetTertiaryToolTipStrRef();
    /* 0040 */ virtual void ResetToolTip();
    /* 0044 */ virtual void SetToolTipStrRef(STRREF strRef, STRREF secondaryStrRef, STRREF tertiaryStrRef);
    /* 0048 */ virtual void SetToolTipHotKey(USHORT nHotKeyIndex1, USHORT nHotKeyIndex2, const CString& sKey);
    /* 004C */ virtual void ActivateToolTip();
    /* 0050 */ virtual void InvalidateRect() = 0;
    /* 0054 */ virtual void func_54();
    /* 0058 */ virtual BOOL Render(BOOL bForce) = 0;
    /* 005C */ virtual BOOL GetInactiveRender();
    /* 0060 */ virtual void SetInactiveRender(BOOL bInactiveRender);
    /* 0064 */ virtual BOOL NeedRender();

    void SetNeedAsyncUpdate();
    void SetNeedMouseMove();

    // NOTE: Convenience.
    inline BOOL IsOver(const CPoint& pt)
    {
        return pt.x >= m_ptOrigin.x && pt.x <= m_ptOrigin.x + m_size.cx
            && pt.y >= m_ptOrigin.y && pt.y <= m_ptOrigin.y + m_size.cy;
    }

    /* 0004 */ unsigned char field_4;
    /* 0008 */ CUIPanel* m_pPanel; // #guess
    /* 000A */ DWORD m_nID; // #guess
    /* 000E */ CPoint m_ptOrigin;
    /* 0016 */ CSize m_size;
    /* 001E */ BOOLEAN m_bActive; // #guess
    /* 001F */ BOOLEAN m_bNeedAsyncUpdate;
    /* 0020 */ BOOLEAN m_bNeedMouseMove;
    /* 0022 */ CRect m_rDirty;
    /* 0032 */ BOOL m_bInactiveRender; // #guess
    /* 0036 */ int field_36;
    /* 003A */ BOOL m_bToolTipActive;
    /* 003E */ STRREF m_nToolTipStrRef; // #guess
    /* 0042 */ STRREF m_nSecondaryToolTipStrRef; // #guess
    /* 0046 */ STRREF m_nTertiaryToolTipStrRef; // #guess
    /* 004A */ USHORT m_nToolTipHotKeyIndex1; // #guess
    /* 004C */ USHORT m_nToolTipHotKeyIndex2; // #guess
    /* 004E */ CString m_sKey; // #guess
};

#endif /* CUICONTROLBASE_H_ */

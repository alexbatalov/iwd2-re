#ifndef CUICONTROLBASE_H_
#define CUICONTROLBASE_H_

#include "mfc.h"

#include "BalDataTypes.h"

class CUIPanel;

class CUIControlBase {
public:
    static const BYTE byte_84C89C;
    static const BYTE byte_84C89D;
    static const BYTE byte_84C89E;

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
    /* 0058 */ virtual void Render(int a2) = 0;
    /* 005C */ virtual BOOL GetInactiveRender();
    /* 0060 */ virtual void SetInactiveRender(BOOL bInactiveRender);
    /* 0064 */ virtual BOOL NeedRender();

    /* 0004 */ unsigned char field_4;
    /* 0008 */ CUIPanel* m_pPanel; // #guess
    /* 000A */ DWORD m_nID; // #guess
    /* 000E */ INT m_nX; // #guess
    /* 0012 */ INT m_nY; // #guess
    /* 0016 */ INT m_nWidth; // #guess
    /* 001A */ INT m_nHeight; // #guess
    /* 001E */ BOOLEAN m_bActive; // #guess
    /* 001F */ unsigned char field_1F;
    /* 0020 */ unsigned char field_20;
    /* 0022 */ CRect field_22;
    /* 0032 */ BOOL m_bInactiveRender; // #guess
    /* 0036 */ int field_36;
    /* 003A */ BOOL m_bToolTipActive;
    /* 003E */ int m_nToolTipStrRef; // #guess
    /* 0042 */ int m_nSecondaryToolTipStrRef; // #guess
    /* 0046 */ int m_nTertiaryToolTipStrRef; // #guess
    /* 004A */ USHORT m_nToolTipHotKeyIndex1; // #guess
    /* 004C */ USHORT m_nToolTipHotKeyIndex2; // #guess
    /* 004E */ CString m_sKey; // #guess
};

#endif /* CUICONTROLBASE_H_ */

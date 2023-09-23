#ifndef CUICONTROLBUTTON_H_
#define CUICONTROLBUTTON_H_

#include "CUIControlBase.h"
#include "CVidCell.h"
#include "CVidFont.h"

class CUIControlButton : public CUIControlBase {
public:
    static const BYTE LBUTTON;
    static const BYTE RBUTTON;

    static const COLORREF TINT_DISABLED;
    static const COLORREF TINT_INVALID;

    static const WORD TYPE_WORD_WRAP;

    static const int dword_8AB9B4;

    CUIControlButton(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5);
    /* 0000 */ ~CUIControlButton() override;
    /* 000C */ void KillFocus() override;
    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0020 */ BOOL OnLButtonDblClk(CPoint pt) override;
    /* 0024 */ BOOL OnRButtonDown(CPoint pt) override;
    /* 0028 */ void OnRButtonUp(CPoint pt) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0054 */ void func_54() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void OnLButtonClick(CPoint pt);
    /* 006C */ virtual void OnLButtonDoubleClick(CPoint pt);
    /* 0070 */ virtual void OnRButtonClick(CPoint pt);
    /* 0074 */ virtual void SetText(const CString& sText);

    void SetEnabled(BOOL bEnabled);
    void SetValid(BOOL bValid);

    /* 0052 */ CVidCell m_cVidCell; // #guess
    /* 012C */ SHORT m_nNormalFrame; // #guess
    /* 012E */ SHORT m_nPressedFrame; // #guess
    /* 0130 */ SHORT m_nDisabledFrame; // #guess
    /* 0132 */ SHORT m_nRenderCount; // #guess
    /* 0134 */ BOOL m_bPressed; // #guess
    /* 0138 */ BYTE m_nMouseButtons; // #guess
    /* 0139 */ unsigned char field_139;
    /* 013A */ CString* m_pText;
    /* 013E */ CVidFont m_cVidFont; // #guess
    /* 063E */ int field_63E;
    /* 0642 */ int field_642;
    /* 0646 */ BOOL m_bEnabled; // #guess
    /* 064A */ int m_nTextLines;
    /* 064C */ int field_64C;
    /* 0650 */ BOOL m_bValid; // #guess
    /* 0654 */ short field_654;
    /* 0656 */ BYTE m_nMaxLines;
    /* 0657 */ BYTE m_nTextFlags;
    /* 0658 */ int field_658;
    /* 065C */ int field_65C;
    /* 0660 */ unsigned char field_660;
    /* 0662 */ int field_662;
};

#endif /* CUICONTROLBUTTON_H_ */

#ifndef CUICONTROLEDITMULTILINE_H_
#define CUICONTROLEDITMULTILINE_H_

#include "CUIControlBase.h"
#include "CVidCell.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

class CUIControlEditMultiLine : public CUIControlBase {
public:
    CUIControlEditMultiLine(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo, int a3);
    /* 0000 */ ~CUIControlEditMultiLine() override;
    /* 000C */ void KillFocus() override;
    /* 0010 */ void SetFocus() override;
    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0024 */ BOOL OnRButtonDown(CPoint pt) override;
    /* 002C */ void OnKeyDown(SHORT nKey) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void SetColor(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor);
    /* 006C */ virtual void OnEditReturn(CString sText);
    /* 0070 */ virtual CString GetText();
    /* 0074 */ virtual void SetText(CString sText);
    /* 0078 */ virtual void AdjustVisibleIndex();

    void Remove();
    void ReConstitute();
    void CalculateNewLines(BYTE a1);

    /* 0052 */ CVidMosaic m_mosBackground;
    /* 0106 */ CVidMosaic m_mosTextFocusedBackground;
    /* 01BA */ CVidMosaic m_mosTextUnFocusedBackground;
    /* 026E */ CVidCell m_vcCursor;
    /* 0348 */ CPoint m_ptText;
    /* 0350 */ int field_350;
    /* 0354 */ int field_354;
    /* 0358 */ CVidFont m_cVidFont;
    /* 0858 */ WORD m_nTextCapitalization;
    /* 085A */ short field_85A;
    /* 085C */ SHORT m_nRenderCount;
    /* 085E */ BOOL m_bFocused;
    /* 0862 */ CString m_sText;
    /* 0866 */ CString field_866;
    /* 086A */ int field_86A;
    /* 086E */ int field_86E;
    /* 0872 */ int field_872;
    /* 0876 */ int field_876;
    /* 0877 */ unsigned char field_877;
    /* 0878 */ short field_878;
    /* 087A */ short field_87A;
    /* 087C */ COLORREF m_rgbForegroundColor;
    /* 0880 */ COLORREF m_rgbBackgroundColor;
    /* 0888 */ unsigned char field_888;
    /* 088A */ int field_88A;
    /* 088E */ int field_88E;
};

class CUIControlEditMultiLineScroller : public CUIControlEditMultiLine {
public:
    CUIControlEditMultiLineScroller(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditMultiLineScroller() override;
    void AdjustVisibleIndex() override;

    void OnScroll(SHORT a1, SHORT a2);
    void OnScrollUp();
    void OnScrollDown();
    void OnPageUp(DWORD nLines);
    void OnPageDown(DWORD nLines);

    /* 0892 */ int field_892;
    /* 0896 */ unsigned char field_896;
    /* 0897 */ unsigned char field_897;
    /* 0898 */ unsigned char field_898;
    /* 0899 */ unsigned char field_899;
};

#endif /* CUICONTROLEDITMULTILINE_H_ */

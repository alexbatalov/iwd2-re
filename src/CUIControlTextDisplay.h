#ifndef CUICONTROLTEXTDISPLAY_H_
#define CUICONTROLTEXTDISPLAY_H_

#include "CUIControlBase.h"
#include "CVidFont.h"

class CDisplayString {
public:
    CString& GetLabel() { return m_sLabel; }
    CString& GetString() { return m_sString; }
    POSITION GetBossPos() { return m_posBoss; }
    INT GetNumLines() { return m_nNumLines; }
    LONG GetMarker() { return m_lMarker; }
    COLORREF GetLabelColor() { return m_rgbLabelColor; }
    COLORREF GetTextColor() { return m_rgbTextColor; }

    CString m_sLabel;
    CString m_sString;
    POSITION m_posBoss;
    LONG m_lMarker;
    COLORREF m_rgbLabelColor;
    COLORREF m_rgbTextColor;
    INT m_nNumLines;
    SHORT m_nOffset;
    SHORT m_nLine;
};

class CUIControlTextDisplay : public CUIControlBase {
public:
    static const CString NAME_SEPARATOR;

    CUIControlTextDisplay(CUIPanel* pPanel, UI_CONTROL_TEXTDISPLAY* pControlInfo, BOOLEAN a3);
    /* 0000 */ ~CUIControlTextDisplay() override;
    /* 0004 */ void SetActive(BOOLEAN bActive) override;
    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0030 */ void TimerAsynchronousUpdate(BOOLEAN bInside) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void HighlightItem(POSITION posBossItem);
    /* 006C */ virtual void UnHighlightItem();
    /* 0070 */ virtual void OnButtonLClick(CPoint pt);
    /* 0074 */ virtual void OnItemSelected(LONG lMarker);

    POSITION DisplayString(const CString& sLabel, const CString& sString, COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor, LONG lMarker, BOOLEAN a6, BOOLEAN bTrim);
    void AdjustScrollBar();
    INT GetNumLines(POSITION posBossItem);
    void OnScroll(SHORT a1, SHORT a2);
    void OnScrollDown();
    void OnScrollUp();
    void OnPageDown(DWORD a1);
    void OnPageUp(DWORD a1);
    void RemoveAll();
    void RemoveString(POSITION pos);
    SHORT ParseAndInsertStringAfter(POSITION tail, const CString& sLabel, const CString& sString, COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor, LONG a6, POSITION& posBoss, BOOLEAN bTrim);
    void SetItemMarker(POSITION posBossItem, LONG lMarker);
    void SetItemTextColor(POSITION posBossItem, COLORREF rgbColor);
    void SetTopString(POSITION posTopString);
    void ScrollToBottom();
    POSITION GetBossPosition(INT nIndex);
    void GetString(INT nIndex, CString& sString);
    BOOLEAN GetItem(INT nItemIndex, CString& sLabel, CString& sString);
    BOOLEAN GetItemTextColor(INT nItemIndex, COLORREF& rgbColor);
    POSITION GetItemBossPosition(INT nIndex);

    /* 0052 */ CTypedPtrList<CPtrList, CDisplayString*>* m_plstStrings;
    /* 0056 */ POSITION m_posTopString;
    /* 005A */ short field_5A;
    /* 005C */ short field_5C;
    /* 005E */ SHORT m_nRenderCount;
    /* 0060 */ CVidFont m_textFont;
    /* 0560 */ CVidFont m_labelFont;
    /* 0A60 */ SHORT m_nFontHeight;
    /* 0A62 */ short field_A62;
    /* 0A64 */ unsigned char field_A64;
    /* 0A65 */ unsigned char field_A65;
    /* 0A66 */ unsigned char field_A66;
    /* 0A67 */ unsigned char field_A67;
    /* 0A68 */ short field_A68;
    /* 0A6C */ short field_A6A;
    /* 0A6C */ short field_A6C;
    /* 0A6E */ DWORD m_nScrollBarID;
    /* 0A72 */ COLORREF m_rgbLabelColor;
    /* 0A76 */ COLORREF m_rgbBackgroundColor;
    /* 0A7A */ COLORREF m_rgbTextColor;
    /* 0A7E */ COLORREF m_rgbHighlightColor;
    /* 0A82 */ POSITION m_posHighlightedItem;
    /* 0A86 */ COLORREF m_rgbTextColorBeforeHighlight;
    /* 0A8A */ COLORREF m_rgbLabelColorBeforeHighlight;
    /* 0A8E */ CCriticalSection field_A8E;
    /* 0AAE */ BOOLEAN field_AAE;
    /* 0AAF */ BOOLEAN field_AAF;
    /* 0AB0 */ CString m_sNameSeparator;
    /* 0AB4 */ short field_AB4;
    /* 0AB6 */ BOOLEAN field_AB6;
    /* 0AB7 */ unsigned char field_AB7;
};

#endif /* CUICONTROLTEXTDISPLAY_H_ */

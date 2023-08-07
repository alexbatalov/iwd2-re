#ifndef CUICONTROLSCROLLBAR_H_
#define CUICONTROLSCROLLBAR_H_

#include "CUIControlBase.h"

#include "CUIControlButton.h"
#include "CVidCell.h"

#define CUICONTROLBUTTONSCROLLBAR_DIRECTION_UP 1
#define CUICONTROLBUTTONSCROLLBAR_DIRECTION_DOWN 2

class CUIControlButtonScrollBar;
class CVidInf;

class CUIControlScrollBar : public CUIControlBase {
public:
    CUIControlScrollBar(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    /* 0000 */ ~CUIControlScrollBar() override;
    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0020 */ BOOL OnLButtonDblClk(CPoint pt) override;
    /* 0030 */ void TimerAsynchronousUpdate(BOOLEAN bInside) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void OnLButtonClick(CPoint pt);
    /* 006C */ virtual void OnScroll();
    /* 0070 */ virtual void OnScrollUp();
    /* 0074 */ virtual void OnScrollDown();
    /* 0078 */ virtual void OnScrollButtonUp(BYTE nDirection);
    /* 007C */ virtual void OnPageUp(DWORD nLines);
    /* 0080 */ virtual void OnPageDown(DWORD nLines);

    void AdjustScrollBar(SHORT a1, SHORT a2, SHORT a3);
    BOOLEAN OverThumb(const CPoint& pt);

    /* 0052 */ SHORT m_nRenderCount;
    /* 0054 */ DWORD m_nTextDisplayID;
    /* 0058 */ CVidCell m_cVidCell;
    /* 0132 */ SHORT m_nSequence;
    /* 0134 */ SHORT m_nTrackFrame;
    /* 0136 */ SHORT m_nThumbFrame;
    /* 0138 */ CUIControlButtonScrollBar* m_pScrollUpButton;
    /* 013C */ CUIControlButtonScrollBar* m_pScrollDownButton;
    /* 0140 */ short field_140;
    /* 0142 */ short field_142;
    /* 0144 */ short field_144;
    /* 0146 */ unsigned char field_146;
    /* 0148 */ short field_148;
};

class CUIControlButtonScrollBar : public CUIControlButton {
public:
    CUIControlButtonScrollBar(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, CUIControlScrollBar* scrollBar, BYTE nDirection);
    /* 0000 */ ~CUIControlButtonScrollBar();
    /* 000C */ void KillFocus() override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0030 */ void TimerAsynchronousUpdate(BOOLEAN bInside) override;

    void BKRender(CVidInf* pVidInf, INT x, INT y, const CRect& rClip, BOOLEAN bDemanded);

    /* 0666 */ CUIControlScrollBar* m_pScrollBar;
    /* 066A */ BYTE m_nDirection;
    /* 066C */ SHORT m_nAUCounter;
};

#endif /* CUICONTROLSCROLLBAR_H_ */

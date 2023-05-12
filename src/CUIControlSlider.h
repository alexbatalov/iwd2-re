#ifndef CUICONTROLSLIDER_H_
#define CUICONTROLSLIDER_H_

#include "CUIControlBase.h"
#include "CVidCell.h"
#include "CVidMosaic.h"

class CUIControlSlider : public CUIControlBase {
public:
    static const CSize stru_8D7A28;

    CUIControlSlider(CUIPanel* panel, UI_CONTROL_SLIDER* controlInfo);
    ~CUIControlSlider();

    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void OnThumbChange();
    /* 006C */ virtual void OnThumbFinalChange();

    /* 0052 */ CVidMosaic m_mosBackground;
    /* 0106 */ CVidCell m_vcKnob;
    /* 01E0 */ SHORT m_nSequence;
    /* 01E2 */ SHORT m_nKnobFrame;
    /* 01E4 */ SHORT m_nActiveKnobFrame;
    /* 01E6 */ SHORT m_nDisabledKnobFrame;
    /* 01E8 */ int m_nKnobOffsetX;
    /* 01EC */ int m_nKnobOffsetY;
    /* 01F0 */ SHORT m_nKnobJumpWidth;
    /* 01F2 */ SHORT m_nKnobJumpCount;
    /* 01F4 */ CRect m_rTrack;
    /* 0204 */ BOOLEAN m_bKnobEnabled;
    /* 0206 */ SHORT m_nRenderCount;
    /* 0208 */ SHORT m_nValue;
    /* 020A */ BOOL m_bTracking;
    /* 020E */ BOOL m_bValueChanged;
    /* 0212 */ int field_212;
};

#endif /* CUICONTROLSLIDER_H_ */

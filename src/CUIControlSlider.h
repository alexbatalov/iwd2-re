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
    /* 0058 */ void Render(int a2) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ virtual void OnThumbChange();
    /* 006C */ virtual void OnThumbFinalChange();

    /* 0052 */ CVidMosaic field_52;
    /* 0106 */ CVidCell field_106;
    /* 0204 */ unsigned char field_204;
    /* 0206 */ SHORT m_nRenderCount;
    /* 020A */ int field_20A;
    /* 020E */ int field_20E;
};

#endif /* CUICONTROLSLIDER_H_ */

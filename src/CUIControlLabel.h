#ifndef CUICONTROLLABEL_H_
#define CUICONTROLLABEL_H_

#include "CUIControlBase.h"

#include "CVidFont.h"

class CUIControlLabel : public CUIControlBase {
public:
    CUIControlLabel(CUIPanel* pPanel, UI_CONTROL_LABEL* pControlInfo);
    ~CUIControlLabel();

    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;

    void SetText(const CString& sString);
    void SetForegroundColor(COLORREF rgbColor);

    /* 0052 */ CString* m_pText;
    /* 0056 */ SHORT m_nRenderCount;
    /* 0058 */ CVidFont field_58;
    /* 055A */ short field_55A;
    short field_55C;
    unsigned char field_55E;
};

#endif /* CUICONTROLLABEL_H_ */

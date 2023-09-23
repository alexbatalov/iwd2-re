#ifndef CUICONTROLLABEL_H_
#define CUICONTROLLABEL_H_

#include "CUIControlBase.h"

#include "CVidFont.h"

class CUIControlLabel : public CUIControlBase {
public:
    static const WORD TYPE_WORD_WRAP;

    CUIControlLabel(CUIPanel* pPanel, UI_CONTROL_LABEL* pControlInfo);
    ~CUIControlLabel();

    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;

    void SetText(const CString& sString);
    void SetForegroundColor(COLORREF rgbColor);

    /* 0052 */ CString* m_pText;
    /* 0056 */ SHORT m_nRenderCount;
    /* 0058 */ CVidFont m_cVidFont;
    /* 0558 */ SHORT m_nFontHeight;
    /* 055A */ WORD m_nTextFlags;
    /* 055C */ SHORT m_nTextLines;
    /* 055E */ BYTE m_nMaxLines;
};

#endif /* CUICONTROLLABEL_H_ */

#ifndef CUICONTROLBUTTON3STATE_H_
#define CUICONTROLBUTTON3STATE_H_

#include "CUIControlButton.h"

class CUIControlButton3State : public CUIControlButton {
public:
    CUIControlButton3State(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5);
    ~CUIControlButton3State();
    void SetSelected(INT nSelected);
    void OnLButtonClick(CPoint pt) override;
    BOOL Render(BOOL bForce) override;

    /* 0666 */ SHORT m_nSelectedFrame;
    /* 0668 */ SHORT m_nNotSelectedFrame;
    /* 066A */ BOOL m_bSelected;
};

#endif /* CUICONTROLBUTTON3STATE_H_ */

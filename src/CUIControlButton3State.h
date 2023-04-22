#ifndef CUICONTROLBUTTON3STATE_H_
#define CUICONTROLBUTTON3STATE_H_

#include "CUIControlButton.h"

class CUIControlButton3State : public CUIControlButton {
public:
    CUIControlButton3State(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5);
    ~CUIControlButton3State();
    void SetSelected(INT nSelected);
    void OnLButtonClick(CPoint pt) override;
    void Render(int a2) override;

    SHORT m_nSelectedFrame;
    SHORT m_nNotSelectedFrame;
    BOOL m_bSelected;
};

#endif /* CUICONTROLBUTTON3STATE_H_ */

#ifndef CUICONTROLBUTTONPLUSMINUS_H_
#define CUICONTROLBUTTONPLUSMINUS_H_

#include "CUIControlButton.h"

class CUIControlButtonPlusMinus : public CUIControlButton {
public:
    CUIControlButtonPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonPlusMinus() override;
    void KillFocus() override;
    void TimerAsynchronousUpdate(BOOLEAN bInside) override;
    BOOL OnLButtonDown(CPoint pt) override;
    void OnLButtonUp(CPoint pt) override;
    virtual void AdjustValue() = 0;

    /* 0666 */ DWORD m_nAUCounter;
};

#endif /* CUICONTROLBUTTONPLUSMINUS_H_ */

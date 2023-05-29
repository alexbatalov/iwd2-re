#include "CUIControlButtonPlusMinus.h"

// 0x4E63F0
CUIControlButtonPlusMinus::CUIControlButtonPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetNeedAsyncUpdate();
    m_nAUCounter = 0;
}

// 0x4E6480
CUIControlButtonPlusMinus::~CUIControlButtonPlusMinus()
{
}

// 0x4E6520
BOOL CUIControlButtonPlusMinus::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    m_nAUCounter = 1;
    AdjustValue();

    return TRUE;
}

// 0x4E6580
void CUIControlButtonPlusMinus::OnLButtonUp(CPoint pt)
{
    m_nAUCounter = 0;
    CUIControlButton::OnLButtonUp(pt);
}

// 0x4E65A0
void CUIControlButtonPlusMinus::KillFocus()
{
    // NOTE: Uninline.
    CUIControlButton::KillFocus();
    m_nAUCounter = 0;
}

// 0x4E65E0
void CUIControlButtonPlusMinus::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CUIControlBase::TimerAsynchronousUpdate(bInside);

    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            AdjustValue();
        } else {
            m_nAUCounter++;
        }
    }
}

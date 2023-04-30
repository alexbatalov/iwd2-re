#include "CUIControlButton3State.h"

// 0x4D59D0
CUIControlButton3State::CUIControlButton3State(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5)
    : CUIControlButton(panel, controlInfo, nMouseButtons, a5)
{
    m_nNotSelectedFrame = m_nNormalFrame;
    m_nSelectedFrame = 2;
    m_bSelected = FALSE;
}

// 0x4D5A40
CUIControlButton3State::~CUIControlButton3State()
{
}

// 0x4D5AE0
void CUIControlButton3State::SetSelected(BOOL bSelected)
{
    if (bSelected != m_bSelected) {
        m_bSelected = bSelected;
        InvalidateRect();
    }
}

// 0x4D5B00
void CUIControlButton3State::OnLButtonClick(CPoint pt)
{
    // NOTE: Looks like inlining, check.
    SetSelected(!m_bSelected);
}

// 0x4D5B20
BOOL CUIControlButton3State::Render(BOOL bForce)
{
    if (!m_bPressed) {
        if (m_bEnabled) {
            if (m_bSelected) {
                m_cVidCell.FrameSet(m_nSelectedFrame);
            } else {
                m_cVidCell.FrameSet(m_nNotSelectedFrame);
            }
        } else {
            m_cVidCell.FrameSet(m_nDisabledFrame);
        }
    }

    return CUIControlButton::Render(bForce);
}

#include "CUIControlButton.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x4D47D0
CUIControlButton::CUIControlButton(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5)
    : CUIControlBase(panel, &(controlInfo->base), a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 106
    UTIL_ASSERT(panel != NULL && controlInfo != NULL);

    // TODO: Incomplete.
}

// 0x4D4B80
CUIControlButton::~CUIControlButton()
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x4D4C20
BOOL CUIControlButton::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && m_nRenderCount > 0;
}

// 0x4D4C50
void CUIControlButton::KillFocus()
{
    if (m_bEnabled) {
        m_cVidCell.FrameSet(m_nNormalFrame);
    } else {
        m_cVidCell.FrameSet(m_nDisabledFrame);
    }
    m_bPressed = FALSE;
}

// 0x4D4CA0
void CUIControlButton::OnMouseMove(CPoint pt)
{
    if (!(pt.x >= m_nX && pt.y >= m_nY && pt.x <= m_nX + m_nWidth && pt.y <= m_nY + m_nHeight)) {
        if (m_bPressed) {
            m_cVidCell.FrameSet(m_nNormalFrame);
            m_bPressed = FALSE;

            InvalidateRect();
        }
    }

    if (pt.x >= m_nX && pt.y >= m_nY && pt.x <= m_nX + m_nWidth && pt.y <= m_nY + m_nHeight) {
        if (!m_bPressed) {
            m_cVidCell.FrameSet(m_nPressedFrame);
            m_bPressed = TRUE;

            InvalidateRect();

            if (field_662 != 0) {
                static_cast<CBaldurEngine*>(m_pPanel->m_pManager->m_pWarp)->PlayGUISound(CBaldurEngine::RESREF_SOUND_CLICKLEFT);
            }
        }
    }
}

// 0x4D4D70
BOOL CUIControlButton::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & 1) == 0) {
        return FALSE;
    }

    m_cVidCell.FrameSet(m_nPressedFrame);
    m_bPressed = TRUE;
    m_pPanel->m_pManager->SetCapture(this, byte_84C89C);

    InvalidateRect();

    m_pPanel->m_pManager->field_2D = 0;
    m_pPanel->m_pManager->field_32 = m_nID;
    m_pPanel->m_pManager->field_1C = 0;

    if (field_662 != 0) {
        static_cast<CBaldurEngine*>(m_pPanel->m_pManager->m_pWarp)->PlayGUISound(CBaldurEngine::RESREF_SOUND_CLICKLEFT);
    }

    return TRUE;
}

// 0x4D4E10
void CUIControlButton::OnLButtonUp(CPoint pt)
{
    CSingleLock lock(&(m_pPanel->m_pManager->field_36), FALSE);
    lock.Lock(INFINITE);

    m_cVidCell.FrameSet(m_nNormalFrame);
    m_bPressed = FALSE;
    InvalidateRect();

    lock.Unlock();

    if (m_bActive) {
        if ((m_nMouseButtons & 1) != 0) {
            if (pt.x >= m_nX && pt.y >= m_nY && pt.x <= m_nX + m_nWidth && pt.y <= m_nY + m_nHeight) {
                OnLButtonClick(pt);
            }
        }
    }
}

// 0x4D4F30
BOOL CUIControlButton::OnLButtonDblClk(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & 1) == 0) {
        return FALSE;
    }

    OnLButtonDoubleClick(pt);

    return TRUE;
}

// 0x4D4F70
BOOL CUIControlButton::OnRButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & 2) == 0) {
        return FALSE;
    }

    m_cVidCell.FrameSet(m_nPressedFrame);

    m_bPressed = TRUE;
    m_pPanel->m_pManager->SetCapture(this, byte_84C89D);

    InvalidateRect();

    m_pPanel->m_pManager->field_2D = 0;
    m_pPanel->m_pManager->field_32 = m_nID;
    m_pPanel->m_pManager->field_1C = 0;

    static_cast<CBaldurEngine*>(m_pPanel->m_pManager->m_pWarp)->PlayGUISound(CBaldurEngine::RESREF_SOUND_CLICKRIGHT);

    return TRUE;
}

// 0x4D5000
void CUIControlButton::OnRButtonUp(CPoint pt)
{
    m_cVidCell.FrameSet(m_nNormalFrame);
    m_bPressed = FALSE;

    InvalidateRect();

    if (m_bActive) {
        if ((m_nMouseButtons & 2) != 0) {
            if (pt.x >= m_nX && pt.y >= m_nY && pt.x <= m_nX + m_nWidth && pt.y <= m_nY + m_nHeight) {
                OnRButtonClick(pt);
            }
        }
    }
}

// 0x4D5070
void CUIControlButton::Render(int a2)
{
    // TODO: Incomplete.
}

// 0x4D56A0
void CUIControlButton::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);

        m_nRenderCount = CBaldurChitin::RENDER_COUNT;

        lock.Unlock();
    }
}

// 0x4D5730
void CUIControlButton::func_54()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);

        m_nRenderCount = 0;

        lock.Unlock();
    }
}

// 0x4D57C0
void CUIControlButton::SetEnabled(BOOL bEnabled)
{
    if (bEnabled != m_bEnabled || bEnabled != m_bActive) {
        if (bEnabled) {
            SetActive(TRUE);
            SetInactiveRender(FALSE);

            if (m_bPressed) {
                m_cVidCell.FrameSet(m_nPressedFrame);
            } else {
                m_cVidCell.FrameSet(m_nNormalFrame);
            }
        } else {
            SetActive(FALSE);
            SetInactiveRender(TRUE);
            m_cVidCell.FrameSet(m_nDisabledFrame);
        }

        m_bEnabled = bEnabled;

        if (g_pBaldurChitin->field_1A0 == 0) {
            InvalidateRect();
        } else {
            // NOTE: Result is unused.
            g_pChitin->GetWnd();
            if (g_pChitin->cImm.field_128 == 0) {
                InvalidateRect();
            }
        }
    }
}

// 0x4D5880
void CUIControlButton::SetValid(BOOL bValid)
{
    if (m_bValid != bValid) {
        m_bValid = bValid;
        InvalidateRect();
    }
}

// 0x4D58A0
void CUIControlButton::SetText(const CString& sText)
{
    // TODO: Incomplete.
}

// 0x778900
void CUIControlButton::OnLButtonClick(CPoint pt)
{
}

// 0x778900
void CUIControlButton::OnLButtonDoubleClick(CPoint pt)
{
}

// 0x778900
void CUIControlButton::OnRButtonClick(CPoint pt)
{
}

#include "CUIControlButton.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVidMode.h"

// 0x8AB9B4
const int CUIControlButton::dword_8AB9B4 = 2;

// 0x4D47D0
CUIControlButton::CUIControlButton(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons, unsigned char a5)
    : CUIControlBase(panel, &(controlInfo->base), a5)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 106
    UTIL_ASSERT(panel != NULL && controlInfo != NULL);

    field_139 = 0;
    m_nTextFlags = controlInfo->nTextFlags;
    if (m_pPanel->m_pManager->m_bDoubleSize) {
        field_658 = ((2 * controlInfo->xHigh) << 8) | (2 * controlInfo->xLow);
        field_65C = ((2 * controlInfo->yHigh) << 8) | (2 * controlInfo->yLow);
    } else {
        field_658 = (controlInfo->xHigh << 8) | controlInfo->xLow;
        field_65C = (controlInfo->yHigh << 8) | controlInfo->yLow;
    }

    m_nNormalFrame = controlInfo->nNormalFrame;
    m_nPressedFrame = controlInfo->nPressedFrame;
    m_bPressed = FALSE;
    m_nRenderCount = 0;
    m_nDisabledFrame = controlInfo->nDisabledFrame;
    m_nMouseButtons = nMouseButtons;
    field_660 = 0;
    field_662 = 1;

    CResRef resRef(controlInfo->refBam);
    m_cVidCell.SetResRef(resRef, FALSE, TRUE);
    m_cVidCell.field_B4.SetResRef(resRef, FALSE, FALSE);

    if (m_cVidCell.pRes != NULL) {
        m_cVidCell.pRes->field_7E = m_cVidCell.field_B4.GetResRef() == "";
    }

    m_cVidCell.field_D6 = m_pPanel->m_pManager->m_bDoubleSize;
    m_cVidCell.SequenceSet(controlInfo->nSequence);
    m_cVidCell.FrameSet(m_nNormalFrame);

    m_nTextLines = 0;
    m_cVidFont.SetResRef(CResRef("NORMAL"), m_pPanel->m_pManager->m_bDoubleSize, FALSE);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        field_63E = 4;
        field_642 = 4;
    } else {
        field_63E = 1;
        field_642 = 2;
    }

    m_cVidFont.SetColor(RGB(255, 255, 255), RGB(25, 25, 25), FALSE);
    m_bEnabled = TRUE;
    m_bValid = TRUE;
    field_64C = 0;
    field_654 = 0;
    if ((m_nTextFlags & 0x40) == 0) {
        field_654 = 256;
    }

    SHORT nFontHeight = m_cVidFont.GetFontHeight(FALSE);
    if (nFontHeight > m_nHeight - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1)) {
        nFontHeight = m_nHeight - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    }

    if (nFontHeight != 0) {
        m_nMaxLines = (m_nHeight - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1)) / nFontHeight;
    } else {
        m_nMaxLines = 1;
    }

    m_pText = new CString[m_nMaxLines];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 171
    UTIL_ASSERT(m_pText);
}

// 0x4D4B80
CUIControlButton::~CUIControlButton()
{
    delete[] m_pText;
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
BOOL CUIControlButton::Render(BOOL bForce)
{
    CVidInf* pVidMode = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    CRect rControlRect(CPoint(m_pPanel->m_ptOrigin.x + m_nX, m_pPanel->m_ptOrigin.y + m_nY),
        CSize(m_nWidth, m_nHeight));

    CRect rDirtyRect;
    rDirtyRect.IntersectRect(rControlRect, field_22);

    if (!pVidMode->BKLock(rDirtyRect)) {
        return FALSE;
    }

    CPoint pt = rControlRect.TopLeft() - rDirtyRect.TopLeft();
    rDirtyRect.OffsetRect(-rDirtyRect.left, -rDirtyRect.top);

    m_cVidCell.pRes->Demand();

    DWORD dwFlags = field_64C != 0 ? 0x80001 : 0x1;
    m_cVidCell.RealizePalette(dwFlags);
    BOOL bResult = pVidMode->BKRender(&m_cVidCell, pt.x, pt.y, rDirtyRect, TRUE, dwFlags);
    m_cVidCell.pRes->Release();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 575
    UTIL_ASSERT(bResult);

    if (m_pText != NULL) {
        // TODO: Incomplete.
    }

    pVidMode->BKUnlock();
    return TRUE;
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
    CString sCopy(sText);

    if ((m_nTextFlags & 0x20) == 0) {
        sCopy.MakeLower();
        if (sCopy.Compare(sText) == 0) {
            sCopy.MakeUpper();
        } else {
            sCopy = sText;
        }
    }

    BOOL bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
    if ((field_654 & 0x100) != 0) {
        m_nTextLines = CUtil::SplitString(&m_cVidFont,
            sCopy,
            m_nWidth - 2 * dword_8AB9B4 * (bDoubleSize ? 2 : 1),
            m_nMaxLines,
            m_pText,
            FALSE,
            FALSE,
            TRUE,
            -1);
    } else {
        m_nTextLines = CUtil::SplitString(&m_cVidFont,
            sCopy,
            m_nWidth - 2 * dword_8AB9B4 * (bDoubleSize ? 2 : 1),
            1,
            m_pText,
            FALSE,
            FALSE,
            TRUE,
            -1);
    }

    InvalidateRect();
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

#include "CUIControlButton.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"
#include "CVidMode.h"

// 0x84C920
const BYTE CUIControlButton::LBUTTON = 1;

// 0x84C921
const BYTE CUIControlButton::RBUTTON = 2;

// 0x84C924
const COLORREF CUIControlButton::TINT_DISABLED = RGB(180, 180, 180);

// 0x84C928
const COLORREF CUIControlButton::TINT_INVALID = RGB(180, 180, 180);

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

    // NOTE: Uninline.
    m_cVidCell.SetResRef(CResRef(controlInfo->refBam), m_pPanel->m_pManager->m_bDoubleSize, FALSE);

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
    if (nFontHeight > m_size.cy - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1)) {
        nFontHeight = m_size.cy - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    }

    if (nFontHeight != 0) {
        m_nMaxLines = (m_size.cy - 2 * dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1)) / nFontHeight;
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
    if (!IsOver(pt)) {
        if (m_bPressed) {
            m_cVidCell.FrameSet(m_nNormalFrame);
            m_bPressed = FALSE;

            InvalidateRect();
        }
    }

    if (IsOver(pt)) {
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

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    m_cVidCell.FrameSet(m_nPressedFrame);
    m_bPressed = TRUE;
    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSELBUTTON);

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
        if ((m_nMouseButtons & LBUTTON) != 0) {
            if (IsOver(pt)) {
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

    if ((m_nMouseButtons & LBUTTON) == 0) {
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

    if ((m_nMouseButtons & RBUTTON) == 0) {
        return FALSE;
    }

    m_cVidCell.FrameSet(m_nPressedFrame);

    m_bPressed = TRUE;
    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSERBUTTON);

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
        if ((m_nMouseButtons & RBUTTON) != 0) {
            if (IsOver(pt)) {
                OnRButtonClick(pt);
            }
        }
    }
}

// 0x4D5070
BOOL CUIControlButton::Render(BOOL bForce)
{
    CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());
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

    CRect rControlRect(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

    CRect rDirtyRect;
    rDirtyRect.IntersectRect(rControlRect, m_rDirty);

    if (!pVidInf->BKLock(rDirtyRect)) {
        return FALSE;
    }

    CPoint pt = rControlRect.TopLeft() - rDirtyRect.TopLeft();
    rDirtyRect.OffsetRect(-rDirtyRect.left, -rDirtyRect.top);

    m_cVidCell.pRes->Demand();

    DWORD dwFlags = field_64C != 0 ? 0x80001 : 0x1;
    m_cVidCell.RealizePalette(dwFlags);
    BOOL bResult = pVidInf->BKRender(&m_cVidCell, pt.x, pt.y, rDirtyRect, TRUE, dwFlags);
    m_cVidCell.pRes->Release();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 575
    UTIL_ASSERT(bResult);

    if (m_pText != NULL) {
        if (m_bPressed) {
            pt.x += field_63E;
            pt.y += field_642;
        }

        DWORD dwFlags;
        if (field_64C) {
            dwFlags = 0x80000;
        } else if (m_bEnabled) {
            dwFlags = 0;
        } else {
            m_cVidFont.SetTintColor(RGB(180, 180, 180));

            if (g_pChitin->field_1A0) {
                m_cVidFont.SetTintColor(RGB(80, 80, 80));
            }

            dwFlags = 0x20000;
        }

        m_cVidFont.pRes->Demand();

        SHORT nBaseLineHeight = m_cVidFont.GetBaseLineHeight(TRUE);
        SHORT nFontHeight = m_cVidFont.GetFontHeight(TRUE);

        if ((m_nTextFlags & 0x10) != 0) {
            if ((m_nTextFlags & 0x4) != 0) {
                pt.y += field_65C;
            } else if ((m_nTextFlags & 0x8) != 0) {
                pt.y += field_65C - nFontHeight + m_nTextLines;
            } else {
                pt.y += field_65C - nFontHeight * m_nTextLines / 2;
            }
        } else {
            if ((m_nTextFlags & 0x4) != 0) {
                pt.y += dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
            } else if ((m_nTextFlags & 0x8) != 0) {
                pt.y += m_size.cy
                    - dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1)
                    - nFontHeight * m_nTextLines;
            } else {
                pt.y += (m_size.cy - nFontHeight * m_nTextLines) / 2;
            }
        }

        for (int nLine = 0; nLine < m_nTextLines; nLine++) {
            int x;
            if ((m_nTextFlags & 0x10) != 0) {
                if ((m_nTextFlags & 0x1) != 0) {
                    x = pt.x + field_658;
                } else if ((m_nTextFlags & 0x2) != 0) {
                    x = pt.x + field_658
                        - m_cVidFont.GetStringLength(m_pText[nLine], TRUE);
                } else {
                    x = pt.x + field_658
                        - m_cVidFont.GetStringLength(m_pText[nLine], TRUE) / 2;
                }
            } else {
                if ((m_nTextFlags & 0x1) != 0) {
                    x = pt.x + dword_8AB9B4 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                } else if ((m_nTextFlags & 0x2) != 0) {
                    // FIXME: Calculating string width twice.
                    x = pt.x + max(m_size.cx - m_cVidFont.GetStringLength(m_pText[nLine], TRUE), 0);
                } else {
                    // FIXME: Calculating string width twice.
                    x = pt.x + max(m_size.cx - m_cVidFont.GetStringLength(m_pText[nLine], TRUE), 0) / 2;
                }
            }

            pVidInf->BKTextOut(&m_cVidFont,
                m_pText[nLine],
                x,
                pt.y + nBaseLineHeight,
                rDirtyRect,
                dwFlags,
                TRUE);

            pt.y += nFontHeight;
        }
    }

    pVidInf->BKUnlock();
    return TRUE;
}

// 0x4D56A0
void CUIControlButton::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);

        m_nRenderCount = CUIManager::RENDER_COUNT;

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
            m_size.cx - 2 * dword_8AB9B4 * (bDoubleSize ? 2 : 1),
            m_nMaxLines,
            m_pText,
            FALSE,
            FALSE,
            TRUE,
            -1);
    } else {
        m_nTextLines = CUtil::SplitString(&m_cVidFont,
            sCopy,
            m_size.cx - 2 * dword_8AB9B4 * (bDoubleSize ? 2 : 1),
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

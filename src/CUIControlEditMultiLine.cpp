#include "CUIControlEditMultiLine.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CUIControlScrollBar.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x4D9410
CUIControlEditMultiLine::CUIControlEditMultiLine(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo, int a3)
    : CUIControlBase(panel, &(controlInfo->base), 0)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 2458
    UTIL_ASSERT(panel != NULL && controlInfo != NULL);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        m_ptText.x = 2 * controlInfo->x;
        m_ptText.y = 2 * controlInfo->y;
    } else {
        m_ptText.x = controlInfo->x;
        m_ptText.y = controlInfo->y;
    }

    field_350 = 0;
    field_354 = 0;
    m_nTextCapitalization = controlInfo->nTextCapitalization;
    field_85A = controlInfo->field_68;
    m_nRenderCount = 0;
    m_bFocused = FALSE;
    m_sText = controlInfo->initialText;
    field_86A = -1;
    field_86E = 0;
    field_877 = 1;

    CResRef cursorResRef(controlInfo->refCursor);
    m_vcCursor.SetResRef(cursorResRef, m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

    m_vcCursor.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

    m_vcCursor.SequenceSet(controlInfo->nSequence);
    m_vcCursor.FrameSet(controlInfo->nFrame);

    m_cVidFont.SetResRef(CResRef(controlInfo->refFont), m_pPanel->m_pManager->m_bDoubleSize, FALSE);
    m_cVidFont.SetColor(RGB(200, 200, 200), RGB(60, 60, 60), 0);

    field_872 = a3;
    field_88A = -1;
    field_88E = -1;
    field_87A = 0;
    field_878 = 0;
    field_888 = 0;
    m_rgbForegroundColor = RGB(200, 200, 200);
    m_rgbBackgroundColor = RGB(60, 60, 60);
    field_36 = 1;
    field_876 = 1;

    // NOTE: Uninline.
    SetNeedMouseMove();

    m_size.cx -= m_ptText.x;
    m_size.cy -= m_ptText.y;
}

// 0x4D96C0
void CUIControlEditMultiLine::SetColor(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor)
{
    m_rgbForegroundColor = rgbForegroundColor;
    m_rgbBackgroundColor = rgbBackgroundColor;
}

// 0x4D96E0
void CUIControlEditMultiLine::OnEditReturn(CString sText)
{
}

// 0x4D9740
CUIControlEditMultiLine::~CUIControlEditMultiLine()
{
}

// 0x4D9800
void CUIControlEditMultiLine::Remove()
{
    m_sText.Empty();
    field_86A = 0;
    InvalidateRect();
}

// 0x4D9830
void CUIControlEditMultiLine::ReConstitute()
{
    // TODO: Incomplete.
}

// 0x4D9D00
void CUIControlEditMultiLine::CalculateNewLines(BYTE a1)
{
    // TODO: Incomplete.
}

// 0x4DAA10
CString CUIControlEditMultiLine::GetText()
{
    CString sText;
    sText.Empty();

    if (m_sText.GetLength() > 0) {
        int start = 0;
        int end;
        do {
            end = CUtil::Find(m_sText, '\r', start);
            if (end == -1) {
                end = m_sText.GetLength();
            }

            sText += m_sText.Mid(start, end);
            start = end + 1;
        } while (end < m_sText.GetLength());
    }

    return sText;
}

// 0x4DAAF0
void CUIControlEditMultiLine::KillFocus()
{
    // FIXME: Unused.
    CWnd* pWnd = g_pChitin->GetWnd();
    if (g_pChitin->cImm.field_128) {
        g_pChitin->cImm.sub_7C2E10(g_pChitin->GetWnd()->GetSafeHwnd());
        m_pPanel->InvalidateRect(&(m_pPanel->m_rImeSuggestionsFrame));
        m_pPanel->m_rImeSuggestionsFrame.SetRectEmpty();
        m_pPanel->m_pImeSuggestionsFont = NULL;
    }

    static_cast<CBaldurEngine*>(m_pPanel->m_pManager->m_pWarp)->DisableEditKeys();

    m_bFocused = FALSE;
    InvalidateRect();
}

// 0x4DAB80
void CUIControlEditMultiLine::SetFocus()
{
    m_bFocused = TRUE;
    field_866 = m_sText;

    InvalidateRect();

    static_cast<CBaldurEngine*>(m_pPanel->m_pManager->m_pWarp)->EnableEditKeys(field_85A);
}

// 0x4DABD0
BOOL CUIControlEditMultiLine::OnLButtonDown(CPoint pt)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x4DB070
void CUIControlEditMultiLine::OnLButtonUp(CPoint pt)
{
    if (m_bActive) {
        field_888 = 0;
        m_pPanel->m_pManager->SetCapture(this, 2);
        if (field_88E == field_88A) {
            field_86A = field_88E;
            field_88E = -1;
        }

        InvalidateRect();
    }
}

// 0x4DB0C0
BOOL CUIControlEditMultiLine::OnRButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    int x = pt.x - (m_ptText.x + m_ptOrigin.x);
    int y = pt.y - (m_ptText.y + m_ptOrigin.y);

    if (x < 0 || x >= m_size.cx || y < 0 || y >= m_size.cy) {
        if (m_bFocused == TRUE) {
            if (field_872) {
                m_sText = field_866;
                ReConstitute();
            }

            // NOTE: Uninline.
            m_pPanel->m_pManager->KillCapture();
        }
    }

    return TRUE;
}

// 0x4DB160
void CUIControlEditMultiLine::OnKeyDown(SHORT nKey)
{
    // TODO: Incomplete.
}

// 0x4E05B0
void CUIControlEditMultiLine::OnMouseMove(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x4E09F0
BOOL CUIControlEditMultiLine::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && m_nRenderCount > 0;
}

// 0x4E0A20
BOOL CUIControlEditMultiLine::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x4E1580
void CUIControlEditMultiLine::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount = CUIManager::RENDER_COUNT;
        lock.Unlock();
    }
}

// 0x4E1610
void CUIControlEditMultiLine::AdjustVisibleIndex()
{
    if (field_87A > field_878) {
        if (field_86A == 0) {
            field_86E = 0;
        }

        if (field_86A != m_sText.GetLength()) {
            int numberOfLines = 0;
            if (m_sText.GetLength() > 0) {
                int start = 0;
                int end;
                do {
                    end = CUtil::FindOneOf(m_sText.Mid(start), CString("\n\r"), 0);
                    if (end == -1) {
                        end = m_sText.GetLength();
                    }

                    if (start <= field_86A && field_86A <= end + start) {
                        break;
                    }

                    start += end + 1;
                    numberOfLines++;

                    if (start >= m_sText.GetLength()) {
                        start = m_sText.GetLength();
                    }
                } while (end < m_sText.GetLength());
            }

            if (field_86E >= numberOfLines || numberOfLines >= field_86E + field_878) {
                if (field_86E < numberOfLines) {
                    field_86E = max(numberOfLines - field_878 + 1, 0);
                } else {
                    field_86E = numberOfLines;
                }
            } else {
                if (field_87A - field_86E < field_878) {
                    field_86E = field_87A - field_878;
                }

                if (field_86E < numberOfLines) {
                    field_86E = max(numberOfLines - field_878 + 1, 0);
                } else {
                    field_86E = numberOfLines;
                }
            }
        } else {
            field_86E = field_87A - field_878;
        }
    } else {
        field_86E = 0;
    }
}

// 0x4E17B0
void CUIControlEditMultiLine::SetText(CString sText)
{
    field_866 = sText;
    if (sText != m_sText) {
        m_sText = sText;
        field_86A = 0;
        if (sText.GetLength() != 0) {
            CalculateNewLines(3);
            InvalidateRect();
        }
    }
}

// -----------------------------------------------------------------------------

// 0x4E1860
CUIControlEditMultiLineScroller::CUIControlEditMultiLineScroller(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEditMultiLine(panel, controlInfo, 0)
{
    field_896 = 0;
    field_897 = 0;
    field_898 = 0;
    field_899 = 0;
    field_892 = field_36;
}

// 0x4E18D0
CUIControlEditMultiLineScroller::~CUIControlEditMultiLineScroller()
{
}

// 0x4E1990
void CUIControlEditMultiLineScroller::AdjustVisibleIndex()
{
    CUIControlEditMultiLine::AdjustVisibleIndex();

    if (field_892 != -1) {
        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_878, field_878, field_87A);
    }
}

// NOTE: Uninline.
void CUIControlEditMultiLineScroller::OnScroll(SHORT a1, SHORT a2)
{
    if (field_87A < field_878) {
        return;
    }

    // TODO: Check casts.
    int v1 = static_cast<int>(static_cast<float>(a1) / static_cast<float>(a2) * (field_87A - field_878));

    if (v1 == field_86E || v1 < 0 || v1 > field_87A - field_878) {
        return;
    }

    field_86E = v1;

    if (field_892 != -1) {
        CUIControlEditScrollBar* pScrollBar = static_cast<CUIControlEditScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_86E, field_87A, field_878);
    }

    InvalidateRect();
}

// NOTE: Uninline.
void CUIControlEditMultiLineScroller::OnScrollUp()
{
    field_86E--;
    if (field_86E < 0) {
        field_86E = 0;
    }

    if (field_892 != -1) {
        CUIControlEditScrollBar* pScrollBar = static_cast<CUIControlEditScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_86E, field_87A, field_878);
    }

    InvalidateRect();
}

// NOTE: Uninline.
void CUIControlEditMultiLineScroller::OnScrollDown()
{
    field_86E++;
    if (field_86E > field_87A - field_878) {
        field_86E = field_87A - field_878;
    }

    if (field_892 != -1) {
        CUIControlEditScrollBar* pScrollBar = static_cast<CUIControlEditScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_86E, field_87A, field_878);
    }

    InvalidateRect();
}

// NOTE: Uninline.
void CUIControlEditMultiLineScroller::OnPageUp(DWORD nLines)
{
    SHORT v1 = static_cast<SHORT>(nLines);
    if (v1 > field_878) {
        v1 = field_878;
    }

    field_86E -= v1;
    if (field_86E < 0) {
        field_86E = 0;
    }

    if (field_892 != -1) {
        CUIControlEditScrollBar* pScrollBar = static_cast<CUIControlEditScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_86E, field_87A, field_878);
    }

    InvalidateRect();
}

// NOTE: Uninline.
void CUIControlEditMultiLineScroller::OnPageDown(DWORD nLines)
{
    if (field_87A < field_878) {
        field_86E = 0;
    } else {
        SHORT v1 = static_cast<SHORT>(nLines);
        if (v1 > field_878) {
            v1 = field_878;
        }

        field_86E += v1;
        if (field_86E > field_87A - field_878) {
            field_86E = field_87A - field_878;
        }
    }

    if (field_892 != -1) {
        CUIControlEditScrollBar* pScrollBar = static_cast<CUIControlEditScrollBar*>(m_pPanel->GetControl(field_892));

        // NOTE: Uninline.
        pScrollBar->AdjustScrollBar(field_86E, field_87A, field_878);
    }

    InvalidateRect();
}

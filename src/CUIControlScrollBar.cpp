#include "CUIControlScrollBar.h"

#include "CBaldurChitin.h"
#include "CUIControlEditMultiLine.h"
#include "CUIControlTextDisplay.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x4E47C0
CUIControlScrollBar::CUIControlScrollBar(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlBase(panel, &(controlInfo->base), 1)
{
    // NOTE: Uninline.
    m_cVidCell.SetResRef(CResRef(controlInfo->refBam), m_pPanel->m_pManager->m_bDoubleSize, FALSE, TRUE);

    m_cVidCell.SequenceSet(controlInfo->nSequence);
    m_cVidCell.pRes->Demand();

    UI_CONTROL_BUTTON buttonInfo;
    CSize buttonNormalSize;
    CSize buttonPressedSize;

    m_cVidCell.GetFrameSize(controlInfo->nSequence,
        controlInfo->nScrollUpNormalFrame,
        buttonNormalSize,
        TRUE);

    m_cVidCell.GetFrameSize(controlInfo->nSequence,
        controlInfo->nScrollUpPressedFrame,
        buttonPressedSize,
        TRUE);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        buttonNormalSize.cx /= 2;
        buttonNormalSize.cy /= 2;
        buttonPressedSize.cx /= 2;
        buttonPressedSize.cy /= 2;
    }

    // TODO: Many narrowing casts, check.

    buttonInfo.base.nID = 0;
    buttonInfo.base.x = controlInfo->base.x;
    buttonInfo.base.y = controlInfo->base.y;
    buttonInfo.base.nWidth = controlInfo->base.nWidth;
    buttonInfo.base.nHeight = static_cast<WORD>(max(buttonNormalSize.cy, buttonPressedSize.cy));
    buttonInfo.base.nType = 0;
    memcpy(buttonInfo.refBam, controlInfo->refBam, RESREF_SIZE);
    buttonInfo.nSequence = static_cast<BYTE>(controlInfo->nSequence);
    buttonInfo.nNormalFrame = static_cast<BYTE>(controlInfo->nScrollUpNormalFrame);
    buttonInfo.nPressedFrame = static_cast<BYTE>(controlInfo->nScrollUpPressedFrame);
    buttonInfo.nSelectedFrame = 0;
    buttonInfo.nDisabledFrame = 0;

    m_pScrollUpButton = new CUIControlButtonScrollBar(m_pPanel, &buttonInfo, this, 1);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        field_140 = 2 * (controlInfo->base.nHeight - buttonInfo.base.nHeight);
    } else {
        field_140 = controlInfo->base.nHeight - buttonInfo.base.nHeight;
    }

    CSize thumbSize;
    m_cVidCell.GetFrameSize(controlInfo->nSequence,
        controlInfo->nThumbFrame,
        thumbSize,
        TRUE);

    m_cVidCell.GetFrameSize(controlInfo->nSequence,
        controlInfo->nScrollDownNormalFrame,
        buttonNormalSize,
        TRUE);

    m_cVidCell.GetFrameSize(controlInfo->nSequence,
        controlInfo->nScrollDownPressedFrame,
        buttonPressedSize,
        TRUE);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        buttonNormalSize.cx /= 2;
        buttonNormalSize.cy /= 2;
        buttonPressedSize.cx /= 2;
        buttonPressedSize.cy /= 2;
    }

    buttonInfo.base.y = controlInfo->base.y
        + controlInfo->base.nHeight
        - static_cast<WORD>(max(buttonNormalSize.cy, buttonPressedSize.cy));
    buttonInfo.base.nHeight = static_cast<WORD>(max(buttonNormalSize.cy, buttonPressedSize.cy));
    buttonInfo.nNormalFrame = static_cast<BYTE>(controlInfo->nScrollDownNormalFrame);
    buttonInfo.nPressedFrame = static_cast<BYTE>(controlInfo->nScrollDownPressedFrame);

    m_pScrollDownButton = new CUIControlButtonScrollBar(m_pPanel, &buttonInfo, this, 2);

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        field_140 -= 2 * buttonInfo.base.nHeight;
    } else {
        field_140 -= buttonInfo.base.nHeight;
    }

    m_cVidCell.pRes->Release();

    field_142 = static_cast<short>(max(field_140 - thumbSize.cy, 1));
    m_nRenderCount = 0;
    m_nTextDisplayID = controlInfo->nTextDisplayID;
    m_nSequence = controlInfo->nSequence;
    m_nTrackFrame = controlInfo->nTrackFrame;
    m_nThumbFrame = controlInfo->nThumbFrame;
    field_144 = 0;
    field_146 = 0;
    SetNeedAsyncUpdate();
}

// 0x4E4C00
CUIControlScrollBar::~CUIControlScrollBar()
{
    if (m_pScrollUpButton != NULL) {
        delete m_pScrollUpButton;
    }

    if (m_pScrollDownButton != NULL) {
        delete m_pScrollDownButton;
    }
}

// 0x4E4C80
void CUIControlScrollBar::AdjustScrollBar(SHORT a1, SHORT a2, SHORT a3)
{
    if (!field_146) {
        if (a2 - a3 > 0) {
            field_144 = min(field_142 * a1 / (a2 - a3), field_142);
            InvalidateRect();
        } else {
            if (a2 != 0) {
                field_144 = field_142 * a1 / a2;
                InvalidateRect();
            } else {
                field_144 = 0;
                InvalidateRect();
            }
        }
    }
}

// 0x4E4D10
void CUIControlScrollBar::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        m_pScrollUpButton->InvalidateRect();
        m_pScrollDownButton->InvalidateRect();

        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount = CUIManager::RENDER_COUNT;
        lock.Unlock();
    }
}

// 0x4E4DB0
BOOL CUIControlScrollBar::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if (m_pScrollUpButton->IsOver(pt)) {
        if (m_pScrollUpButton->IsOverPixel(pt)) {
            m_pScrollUpButton->OnLButtonDown(pt);
            return TRUE;
        }
    }

    if (m_pScrollDownButton->IsOver(pt)) {
        if (m_pScrollDownButton->IsOverPixel(pt)) {
            m_pScrollDownButton->OnLButtonDown(pt);
            return TRUE;
        }
    }

    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSELBUTTON);

    if (OverThumb(pt)) {
        field_146 = 1;
    }

    return TRUE;
}

// 0x4E4EC0
void CUIControlScrollBar::OnLButtonUp(CPoint pt)
{
    if (field_146) {
        if (m_nTextDisplayID != -1) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
            if (pText->m_plstStrings->GetCount() <= pText->field_A6A) {
                if (field_144 != 0) {
                    field_144 = 0;
                    InvalidateRect();
                }
            }
        }
    }

    if (m_bActive) {
        if (IsOver(pt)) {
            OnLButtonClick(pt);
        } else {
            field_146 = 0;
        }
    }
}

// 0x4E4F60
void CUIControlScrollBar::OnMouseMove(CPoint pt)
{
    if (m_bActive && field_146) {
        int v1 = pt.y - field_148;
        int v2 = m_ptOrigin.y + m_pScrollUpButton->m_size.cy;
        if (v1 >= v2) {
            if (v1 <= v2 + field_142) {
                field_144 = v1 - v2;
                OnScroll();
            } else {
                field_144 = field_142;
                OnScroll();
            }
        } else {
            field_144 = 0;
            OnScroll();
        }

        InvalidateRect();
    }
}

// 0x4E5000
BOOLEAN CUIControlScrollBar::OverThumb(const CPoint& pt)
{
    CSize size;
    m_cVidCell.GetFrameSize(m_nSequence, m_nThumbFrame, size, FALSE);

    CPoint origin(m_ptOrigin.x + m_size.cx / 2 - size.cx / 2,
        m_ptOrigin.y + field_144 + m_pScrollUpButton->m_size.cy);
    CRect rect(origin, size);

    if (!rect.PtInRect(pt)) {
        return FALSE;
    }

    // TODO: Check cast.
    field_148 = static_cast<short>(pt.y - origin.y);
    return TRUE;
}

// 0x4E50B0
void CUIControlScrollBar::OnLButtonClick(CPoint pt)
{
    if (!field_146) {
        if (pt.y <= m_ptOrigin.y + field_144 + m_pScrollUpButton->m_size.cy) {
            OnPageUp(-1);
        } else {
            OnPageDown(-1);
        }
    }
    field_146 = 0;
}

// 0x4E5110
void CUIControlScrollBar::OnPageUp(DWORD nLines)
{
    if (m_nTextDisplayID != -1) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
        pText->OnPageUp(nLines);
    }
}

// 0x4E5130
void CUIControlScrollBar::OnPageDown(DWORD nLines)
{
    if (m_nTextDisplayID != -1) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
        pText->OnPageDown(nLines);
    }
}

// 0x4E5150
void CUIControlScrollBar::OnScrollUp()
{
    if (m_nTextDisplayID != -1) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pText->OnScrollUp();
    }
}

// 0x4E51A0
void CUIControlScrollBar::OnScrollDown()
{
    if (m_nTextDisplayID != -1) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pText->OnScrollDown();
    }
}

// 0x4E51F0
void CUIControlScrollBar::OnScroll()
{
    if (m_nTextDisplayID != -1) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
        pText->OnScroll(field_144, field_142);
    }
}

// 0x4E5220
void CUIControlScrollBar::OnScrollButtonUp(BYTE nDirection)
{
    switch (nDirection) {
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_UP:
        if (m_nTextDisplayID != -1) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
            pText->field_A66 = 0;
        }
        break;
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_DOWN:
        if (m_nTextDisplayID != -1) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(m_nTextDisplayID));
            pText->field_A67 = 0;
        }
        break;
    }
}

// 0x4E5270
BOOL CUIControlScrollBar::NeedRender()
{
    return (m_bActive || m_bInactiveRender)
        && (m_pScrollUpButton->NeedRender()
            || m_pScrollDownButton->NeedRender()
            || m_nRenderCount > 0);
}

// 0x4E52B0
BOOL CUIControlScrollBar::Render(BOOL bForce)
{
    CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (!NeedRender() && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    m_cVidCell.pRes->Demand();
    m_cVidCell.RealizePalette(0);

    CRect rControlRect(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

    CRect rDirtyRect;
    rDirtyRect.IntersectRect(rControlRect, m_rDirty);

    if (!pVidInf->BKLock(rDirtyRect)) {
        // FIXME: `pRes` is not released.
        return FALSE;
    }

    CPoint pt = rControlRect.TopLeft() - rDirtyRect.TopLeft();
    rDirtyRect.OffsetRect(-rDirtyRect.left, -rDirtyRect.top);

    CRect rUp;
    rUp.left = pt.x + (m_size.cx - m_pScrollUpButton->m_size.cx) / 2;
    rUp.top = pt.y;
    rUp.right = rUp.left + m_pScrollUpButton->m_size.cx;
    rUp.bottom = rUp.top + m_pScrollUpButton->m_size.cy;

    CRect rUpClip;
    if (rUpClip.IntersectRect(rUp, rDirtyRect)) {
        m_pScrollUpButton->BKRender(pVidInf,
            rUp.left,
            rUp.top,
            rUpClip,
            TRUE);
    }

    CSize trackCenter;
    m_cVidCell.GetFrameCenterPoint(m_nSequence, m_nTrackFrame, trackCenter, TRUE);

    CSize trackSize;
    m_cVidCell.GetFrameSize(m_nSequence, m_nTrackFrame, trackSize, TRUE);

    m_cVidCell.FrameSet(m_nTrackFrame);

    int y = 0;
    while (y < field_140) {
        CRect rTrack;
        rTrack.left = pt.x + (m_size.cx - trackSize.cx) / 2;
        rTrack.top = y + m_pScrollUpButton->m_size.cy + pt.y;
        rTrack.right = rTrack.left + trackSize.cx;
        rTrack.bottom = min(rTrack.top + trackSize.cy, field_140);

        CRect rTrackClip;
        if (rTrackClip.IntersectRect(rTrack, rDirtyRect)) {
            pVidInf->BKRender(&m_cVidCell,
                rTrack.left + trackCenter.cx,
                rTrack.top + trackCenter.cy,
                rTrackClip,
                TRUE,
                0);
        }

        y += trackSize.cy;
    }

    CRect rDown;
    rDown.left = pt.x + (m_size.cx - m_pScrollDownButton->m_size.cx) / 2;
    rDown.top = pt.y + m_pScrollUpButton->m_size.cy + field_140;
    rDown.right = rDown.left + m_pScrollDownButton->m_size.cx;
    rDown.bottom = rDown.top + m_pScrollDownButton->m_size.cy;

    CRect rDownClip;
    if (rDownClip.IntersectRect(rDown, rDirtyRect)) {
        m_pScrollDownButton->BKRender(pVidInf,
            rDown.left,
            rDown.top,
            rDownClip,
            TRUE);
    }

    CSize thumbCenter;
    m_cVidCell.GetFrameCenterPoint(m_nSequence, m_nThumbFrame, thumbCenter, TRUE);

    CSize thumbSize;
    m_cVidCell.GetFrameSize(m_nSequence, m_nThumbFrame, thumbSize, TRUE);

    if (field_140 >= thumbSize.cy) {
        m_cVidCell.FrameSet(m_nThumbFrame);

        CRect rThumb;
        rThumb.left = pt.x + m_size.cx / 2 - thumbSize.cx / 2;
        rThumb.top = pt.y + m_pScrollUpButton->m_size.cy + field_144;
        rThumb.right = rThumb.left + thumbSize.cx;
        rThumb.bottom = rThumb.top + thumbSize.cy;

        CRect rThumbClip;
        if (rThumbClip.IntersectRect(rThumb, rDirtyRect)) {
            pVidInf->BKRender(&m_cVidCell,
                rThumb.left + thumbCenter.cx,
                rThumb.top + thumbCenter.cy,
                rThumbClip,
                TRUE,
                0);
        }
    }

    pVidInf->BKUnlock();
    m_cVidCell.pRes->Release();

    return TRUE;
}

// 0x4E5860
void CUIControlScrollBar::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CPoint pt = g_pBaldurChitin->m_ptPointer - m_pPanel->m_ptOrigin;

    if (m_pScrollUpButton->IsOver(pt)) {
        if (m_pScrollUpButton->IsOverPixel(pt)) {
            m_pScrollUpButton->TimerAsynchronousUpdate(TRUE);
            return;
        }
    }

    if (m_pScrollDownButton->IsOver(pt)) {
        if (m_pScrollDownButton->IsOverPixel(pt)) {
            m_pScrollDownButton->TimerAsynchronousUpdate(TRUE);
            return;
        }
    }
}

// -----------------------------------------------------------------------------

// NOTE: Odd location.
//
// 0x778A00
CUIControlEditScrollBar::CUIControlEditScrollBar(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlEditScrollBar::~CUIControlEditScrollBar()
{
}

// 0x4E5950
void CUIControlEditScrollBar::OnLButtonUp(CPoint pt)
{
    if (field_146) {
        if (m_nTextDisplayID != -1) {
            CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));
            if (pEdit->field_86E == 0) {
                if (field_144 != 0) {
                    field_144 = 0;
                    InvalidateRect();
                }
            }
        }
    }

    if (m_bActive) {
        if (IsOver(pt)) {
            OnLButtonClick(pt);
        } else {
            field_146 = 0;
        }
    }
}

// 0x4E59E0
void CUIControlEditScrollBar::OnScroll()
{
    if (m_nTextDisplayID != -1) {
        CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pEdit->OnScroll(field_144, field_142);
    }
}

// 0x4E5B60
void CUIControlEditScrollBar::OnScrollUp()
{
    if (m_nTextDisplayID != -1) {
        CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pEdit->OnScrollUp();
    }
}

// 0x4E5C60
void CUIControlEditScrollBar::OnScrollDown()
{
    if (m_nTextDisplayID != -1) {
        CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pEdit->OnScrollDown();
    }
}

// 0x4E5D70
void CUIControlEditScrollBar::OnScrollButtonUp(BYTE nDirection)
{
    switch (nDirection) {
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_UP:
        if (m_nTextDisplayID != -1) {
            CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));
            pEdit->field_898 = 0;
        }
        break;
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_DOWN:
        if (m_nTextDisplayID != -1) {
            CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));
            pEdit->field_899 = 0;
        }
        break;
    }
}

// 0x4E5DC0
void CUIControlEditScrollBar::OnPageUp(DWORD nLines)
{
    if (m_nTextDisplayID != -1) {
        CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pEdit->OnPageUp(nLines);
    }
}

// 0x4E5EE0
void CUIControlEditScrollBar::OnPageDown(DWORD nLines)
{
    if (m_nTextDisplayID != -1) {
        CUIControlEditMultiLineScroller* pEdit = static_cast<CUIControlEditMultiLineScroller*>(m_pPanel->GetControl(m_nTextDisplayID));

        // NOTE: Uninline.
        pEdit->OnPageDown(nLines);
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined in `CUIControlScrollBar::CUIControlScrollBar`.
CUIControlButtonScrollBar::CUIControlButtonScrollBar(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, CUIControlScrollBar* pScrollBar, BYTE nDirection)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_pScrollBar = pScrollBar;
    m_nDirection = nDirection;
    m_nAUCounter = 0;
}

// 0x4E60C0
CUIControlButtonScrollBar::~CUIControlButtonScrollBar()
{
}

// 0x4E6160
BOOL CUIControlButtonScrollBar::OnLButtonDown(CPoint pt)
{
    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    switch (m_nDirection) {
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_UP:
        m_pScrollBar->OnScrollUp();
        m_nAUCounter = 1;
        break;
    case CUICONTROLBUTTONSCROLLBAR_DIRECTION_DOWN:
        m_pScrollBar->OnScrollDown();
        m_nAUCounter = 1;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
        // __LINE__: 9132
        UTIL_ASSERT(FALSE);
    }

    return TRUE;
}

// 0x4E61F0
void CUIControlButtonScrollBar::OnLButtonUp(CPoint pt)
{
    CUIControlButton::OnLButtonUp(pt);
    m_nAUCounter = 0;
    m_pScrollBar->OnScrollButtonUp(m_nDirection);
}

// 0x4E6230
void CUIControlButtonScrollBar::KillFocus()
{
    if (m_bEnabled) {
        m_cVidCell.FrameSet(m_nNormalFrame);
    } else {
        m_cVidCell.FrameSet(m_nDisabledFrame);
    }

    m_bPressed = FALSE;
    m_nAUCounter = 0;
    m_pScrollBar->OnScrollButtonUp(m_nDirection);
}

// 0x4E6290
void CUIControlButtonScrollBar::BKRender(CVidInf* pVidInf, INT x, INT y, const CRect& rClip, BOOLEAN bDemanded)
{
    if (m_bActive || m_bInactiveRender) {
        if (m_nRenderCount != 0) {
            CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
            lock.Lock(INFINITE);
            m_nRenderCount--;
            lock.Unlock();
        }

        BOOL bResult = pVidInf->BKRender(&m_cVidCell, x, y, rClip, bDemanded, 0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
        // __LINE__: 9240
        UTIL_ASSERT(bResult);
    }
}

// 0x4E6370
void CUIControlButtonScrollBar::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CUIControlBase::TimerAsynchronousUpdate(bInside);

    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            switch (m_nDirection) {
            case CUICONTROLBUTTONSCROLLBAR_DIRECTION_UP:
                m_pScrollBar->OnScrollUp();
                break;
            case CUICONTROLBUTTONSCROLLBAR_DIRECTION_DOWN:
                m_pScrollBar->OnScrollDown();
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
                // __LINE__: 9281
                UTIL_ASSERT(FALSE);
            }
        } else {
            m_nAUCounter++;
        }
    }
}

// NOTE: Odd location.
//
// 0x61A070
BOOL CUIControlScrollBar::OnLButtonDblClk(CPoint pt)
{
    return OnLButtonDown(pt);
}

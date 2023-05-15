#include "CUIControlSlider.h"

#include "CBaldurChitin.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x8D7A28
const CSize CUIControlSlider::stru_8D7A28(5, 5);

// 0x4D5B90
CUIControlSlider::CUIControlSlider(CUIPanel* panel, UI_CONTROL_SLIDER* controlInfo)
    : CUIControlBase(panel, &(controlInfo->base), 0)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 1016
    UTIL_ASSERT(panel != NULL && controlInfo != NULL);

    m_bValueChanged = 0;
    field_212 = 0;
    m_nSequence = controlInfo->nSequence;
    m_nKnobFrame = controlInfo->nKnobFrame;
    m_nActiveKnobFrame = controlInfo->nActiveKnobFrame;
    m_nDisabledKnobFrame = 2;

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        m_nKnobOffsetX = 2 * controlInfo->nKnobOffsetX;
        m_nKnobOffsetY = 2 * controlInfo->nKnobOffsetY;
        m_nKnobJumpWidth = 2 * controlInfo->nKnobJumpWidth;
    } else {
        m_nKnobOffsetX = controlInfo->nKnobOffsetX;
        m_nKnobOffsetY = controlInfo->nKnobOffsetY;
        m_nKnobJumpWidth = controlInfo->nKnobJumpWidth;
    }

    m_nKnobJumpCount = controlInfo->nKnobJumpCount;

    if (m_pPanel->m_pManager->m_bDoubleSize) {
        m_rTrack.left = 2 * controlInfo->nTrackMinX;
        m_rTrack.top = 2 * controlInfo->nTrackMinY;
        m_rTrack.right = 2 * controlInfo->nTrackMaxX;
        m_rTrack.bottom = 2 * controlInfo->nTrackMaxY;
    } else {
        m_rTrack.left = controlInfo->nTrackMinX;
        m_rTrack.top = controlInfo->nTrackMinY;
        m_rTrack.right = controlInfo->nTrackMaxX;
        m_rTrack.bottom = controlInfo->nTrackMaxY;
    }

    m_nRenderCount = 0;
    m_nValue = 0;
    m_bTracking = FALSE;
    m_bKnobEnabled = TRUE;

    CResRef backgroundResRef(controlInfo->refBackground);
    m_mosBackground.SetResRef(backgroundResRef, FALSE, TRUE);
    m_mosBackground.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

    CResRef knobResRef(controlInfo->refKnob);
    m_vcKnob.SetResRef(knobResRef, FALSE, TRUE);
    m_vcKnob.m_header.SetResRef(knobResRef, FALSE, FALSE);

    if (m_vcKnob.pRes != NULL) {
        m_vcKnob.pRes->field_7E = m_vcKnob.m_header.GetResRef() != "";
    }

    m_vcKnob.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

    m_vcKnob.SequenceSet(m_nSequence);
}

// 0x4D5FA0
CUIControlSlider::~CUIControlSlider()
{
}

// 0x4D6010
void CUIControlSlider::OnMouseMove(CPoint pt)
{
    if (!m_bActive) {
        return;
    }

    if (!m_bKnobEnabled) {
        return;
    }

    SHORT nValue;
    if (field_212 + pt.x - m_nX < m_rTrack.right) {
        nValue = max((field_212 + pt.x - m_nX + m_nKnobJumpWidth / 2 - m_rTrack.left) / m_nKnobJumpWidth, 0);
    } else {
        nValue = m_nKnobJumpCount - 1;
    }

    if (nValue != m_nValue) {
        m_nValue = nValue;

        CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderLock.Lock(INFINITE);
        m_nRenderCount = CBaldurChitin::RENDER_COUNT;
        renderLock.Unlock();

        m_bValueChanged = TRUE;
        OnThumbChange();
    }
}

// 0x4D6120
BOOL CUIControlSlider::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if (!m_bKnobEnabled) {
        return FALSE;
    }

    int x = pt.x - m_nX;
    int y = pt.y - m_nY;

    CPoint ptKnob(m_nKnobJumpWidth * m_nValue + m_nKnobOffsetX, m_nKnobOffsetY);

    CSize frameSize;
    m_vcKnob.GetFrameSize(m_nSequence, m_nKnobFrame, frameSize, FALSE);

    CRect rKnob(ptKnob, frameSize);
    rKnob.InflateRect(stru_8D7A28);

    if (x >= rKnob.left && x < rKnob.right
        && y >= rKnob.top && y < rKnob.bottom) {
        m_bTracking = TRUE;

        CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderLock.Lock(INFINITE);
        m_nRenderCount = CBaldurChitin::RENDER_COUNT;
        renderLock.Unlock();

        m_pPanel->m_pManager->SetCapture(this, 0);

        m_bValueChanged = FALSE;
        field_212 = ptKnob.x + frameSize.cx / 2 - x;
    } else if (x >= m_rTrack.left && x <= m_rTrack.right
        && y >= m_rTrack.top && y <= m_rTrack.bottom) {
        SHORT nValue = (x + m_nKnobJumpWidth / 2 - m_rTrack.left) / m_nKnobJumpWidth;
        if (nValue != m_nValue) {
            m_nValue = nValue;

            CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
            renderLock.Lock(INFINITE);
            m_nRenderCount = CBaldurChitin::RENDER_COUNT;
            renderLock.Unlock();

            OnThumbChange();
            OnThumbFinalChange();
        }
    }

    return TRUE;
}

// 0x4D6380
void CUIControlSlider::OnLButtonUp(CPoint pt)
{
    m_bTracking = FALSE;

    CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
    lock.Lock(INFINITE);
    m_nRenderCount = CBaldurChitin::RENDER_COUNT;
    lock.Unlock();

    if (m_bActive && m_bKnobEnabled && m_bValueChanged) {
        OnThumbFinalChange();
    }
}

// 0x4D6430
BOOL CUIControlSlider::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && m_nRenderCount > 0;
}

// 0x4D6460
BOOL CUIControlSlider::Render(BOOL bForce)
{
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
    rDirtyRect.IntersectRect(rControlRect, m_rDirty);

    CRect rClip(rDirtyRect);
    CRect rMosaic(rDirtyRect);

    rMosaic.OffsetRect(-rMosaic.left, -rMosaic.top);

    m_mosBackground.Render(CVIDINF_SURFACE_BACK,
        rClip.left,
        rClip.top,
        rMosaic,
        rClip,
        0,
        FALSE);

    int x = m_nKnobJumpWidth * m_nValue + m_nKnobOffsetX + rControlRect.left;
    int y = m_nKnobOffsetY + rControlRect.top;

    if (m_bKnobEnabled) {
        if (m_bTracking) {
            m_vcKnob.FrameSet(m_nActiveKnobFrame);
        } else {
            m_vcKnob.FrameSet(m_nKnobFrame);
        }
    } else {
        m_vcKnob.FrameSet(m_nDisabledKnobFrame);
    }

    CSize frameSize;
    m_vcKnob.GetCurrentFrameSize(frameSize, FALSE);

    CRect rKnobClip;
    rKnobClip.IntersectRect(CRect(CPoint(x, y), frameSize), m_rDirty);

    m_vcKnob.Render(CVIDINF_SURFACE_BACK,
        x,
        y,
        rKnobClip,
        NULL,
        0,
        0,
        -1);

    return TRUE;
}

// 0x4D66E0
void CUIControlSlider::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);

        m_nRenderCount = CBaldurChitin::RENDER_COUNT;

        lock.Unlock();
    }
}

// 0x78E730
void CUIControlSlider::OnThumbChange()
{
}

// 0x78E730
void CUIControlSlider::OnThumbFinalChange()
{
}

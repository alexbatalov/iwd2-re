#include "CUIControlSlider.h"

#include "CBaldurChitin.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8D7A28
const CSize CUIControlSlider::stru_8D7A28(5, 5);

// 0x4D5B90
CUIControlSlider::CUIControlSlider(CUIPanel* panel, UI_CONTROL_SLIDER* controlInfo)
    : CUIControlBase(panel, &(controlInfo->base), 0)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 1016
    UTIL_ASSERT(panel != NULL && controlInfo != NULL);

    // TODO: Incomplete.
}

// 0x4D5FA0
CUIControlSlider::~CUIControlSlider()
{
}

// 0x4D6010
void CUIControlSlider::OnMouseMove(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x4D6120
BOOL CUIControlSlider::OnLButtonDown(CPoint pt)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x4D6380
void CUIControlSlider::OnLButtonUp(CPoint pt)
{
    field_20A = 0;

    CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
    lock.Lock(INFINITE);

    m_nRenderCount = CBaldurChitin::RENDER_COUNT;

    lock.Unlock();

    if (m_bActive && field_204 && field_20E) {
        OnThumbFinalChange();
    }
}

// 0x4D6430
BOOL CUIControlSlider::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && m_nRenderCount > 0;
}

// 0x4D6460
void CUIControlSlider::Render(int a2)
{
    // TODO: Incomplete.
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

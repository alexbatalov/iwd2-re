#include "CUIControlLabel.h"

#include "CBaldurChitin.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x4E4000
CUIControlLabel::CUIControlLabel(CUIPanel* pPanel, UI_CONTROL_LABEL* pControlInfo)
    : CUIControlBase(pPanel, &(pControlInfo->base), 0)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 7620
    UTIL_ASSERT(pPanel != NULL && pControlInfo != NULL);

    m_nRenderCount = 0;

    // TODO: Incomplete.
}

// 0x4E42A0
CUIControlLabel::~CUIControlLabel()
{
    if (m_pText != NULL) {
        delete[] m_pText;
    }
}

// 0x4E4330
void CUIControlLabel::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);

        m_nRenderCount = CBaldurChitin::RENDER_COUNT;

        lock.Unlock();
    }
}

// 0x4E43C0
BOOL CUIControlLabel::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && m_nRenderCount > 0;
}

// 0x4E43E0
BOOL CUIControlLabel::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x4E46F0
void CUIControlLabel::SetText(const CString& sString)
{
    if ((field_55A & 0x100) != 0) {
        field_55C = CUtil::SplitString(&field_58, sString, m_nWidth, field_55E, m_pText, FALSE, FALSE, TRUE, -1);
        InvalidateRect();
    } else {
        field_55C = CUtil::SplitString(&field_58, sString, m_nWidth, 1, m_pText, FALSE, FALSE, TRUE, -1);
        InvalidateRect();
    }
}

// 0x4E4780
void CUIControlLabel::SetForegroundColor(COLORREF rgbColor)
{
    if ((field_55A & 0x1) != 0) {
        if (field_58.m_rgbForegroundColor != rgbColor) {
            field_58.SetColor(rgbColor, field_58.m_rgbBackgroundColor, FALSE);
            InvalidateRect();
        }
    }
}

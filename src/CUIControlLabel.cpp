#include "CUIControlLabel.h"

#include "CBaldurChitin.h"
#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x4E4000
CUIControlLabel::CUIControlLabel(CUIPanel* pPanel, UI_CONTROL_LABEL* pControlInfo)
    : CUIControlBase(pPanel, &(pControlInfo->base), 0)
{
    STR_RES strRes;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 7620
    UTIL_ASSERT(pPanel != NULL && pControlInfo != NULL);

    m_nRenderCount = 0;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 7625
    UTIL_ASSERT(pControlInfo->refTextFont[0] != 0);

    m_cVidFont.SetResRef(CResRef(pControlInfo->refTextFont), m_pPanel->m_pManager->m_bDoubleSize, FALSE);

    if ((pControlInfo->nTextFlags & 0x1) != 0) {
        m_cVidFont.SetColor(pControlInfo->nForegroundColor, pControlInfo->nBackgroundColor, FALSE);
    }

    m_nFontHeight = m_cVidFont.GetFontHeight(FALSE);
    m_bNeedAsyncUpdate = FALSE;

    m_nTextFlags = pControlInfo->nTextFlags;
    m_nTextFlags |= 0x100;

    if ((m_nTextFlags & (0x10 | 0x8)) == 0) {
        m_nTextFlags |= 0x4;
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(pControlInfo->nText, strRes);

    SHORT nLineHeight = m_cVidFont.GetFontHeight(FALSE);
    if (nLineHeight > m_nHeight) {
        nLineHeight = m_nHeight;
    }

    m_nMaxLines = m_nHeight / nLineHeight;

    m_pText = new CString[m_nMaxLines];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUIControls.cpp
    // __LINE__: 7620
    UTIL_ASSERT(m_pText != NULL);

    // NOTE: Uninline.
    SetText(strRes.szText);
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

    CRect rFrame(m_pPanel->m_ptOrigin + CPoint(m_nX, m_nY),
        CSize(m_nWidth, m_nHeight));

    CRect rDirtyFrame;
    rDirtyFrame.IntersectRect(rFrame, m_rDirty);

    if (!pVidInf->BKLock(rDirtyFrame)) {
        return FALSE;
    }

    CPoint pt = rFrame.TopLeft() - rDirtyFrame.TopLeft();

    CRect rClip = rDirtyFrame;
    rClip.OffsetRect(-rDirtyFrame.left, -rDirtyFrame.top);

    m_cVidFont.pRes->Demand();

    SHORT nFontHeight = m_cVidFont.GetFontHeight(TRUE);

    if ((m_nTextFlags & 0x20) == 0) {
        if ((m_nTextFlags & 0x80) != 0) {
            pt.y += m_nHeight - nFontHeight * m_nTextLines;
        } else {
            pt.y += m_nHeight / 2 - nFontHeight * m_nTextLines / 2;
        }
    }

    SHORT nBaseLineHeight = m_cVidFont.GetBaseLineHeight(TRUE);

    // NOTE: `x` appears uninitialized, but constructor guarantees that one of
    // the horizontal alignment flags is set.
    int x;
    if ((m_nTextFlags & 0x8) == 0) {
        x = pt.x;
    }

    for (SHORT nLine = 0; nLine < m_nTextLines; nLine++) {
        if ((m_nTextFlags & 0x10) != 0) {
            // FIXME: Calculating string length twice.
            x = pt.x + max(m_nWidth - m_cVidFont.GetStringLength(m_pText[nLine], TRUE), 0);
        } else if ((m_nTextFlags & 0x4) != 0) {
            // FIXME: Calculating string length twice.
            x = pt.x + max(m_nWidth / 2 - m_cVidFont.GetStringLength(m_pText[nLine], TRUE) / 2, 0);
        }

        pVidInf->BKTextOut(&m_cVidFont,
            m_pText[nLine],
            x,
            pt.y + nBaseLineHeight,
            rClip,
            0,
            TRUE);

        pt.y += nFontHeight;
    }

    m_cVidFont.pRes->Release();
    pVidInf->BKUnlock();

    return TRUE;
}

// 0x4E46F0
void CUIControlLabel::SetText(const CString& sString)
{
    if ((m_nTextFlags & 0x100) != 0) {
        m_nTextLines = CUtil::SplitString(&m_cVidFont,
            sString,
            m_nWidth,
            m_nMaxLines,
            m_pText,
            FALSE,
            FALSE,
            TRUE,
            -1);
        InvalidateRect();
    } else {
        m_nTextLines = CUtil::SplitString(&m_cVidFont,
            sString,
            m_nWidth,
            1,
            m_pText,
            FALSE,
            FALSE,
            TRUE,
            -1);
        InvalidateRect();
    }
}

// 0x4E4780
void CUIControlLabel::SetForegroundColor(COLORREF rgbColor)
{
    if ((m_nTextFlags & 0x1) != 0) {
        if (m_cVidFont.m_rgbForegroundColor != rgbColor) {
            m_cVidFont.SetColor(rgbColor, m_cVidFont.m_rgbBackgroundColor, FALSE);
            InvalidateRect();
        }
    }
}

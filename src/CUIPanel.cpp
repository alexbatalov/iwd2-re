#include "CUIPanel.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CInfGame.h"
#include "CUIControlBase.h"
#include "CUIManager.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x4D2750
CUIPanel::CUIPanel(CUIManager* manager, UI_PANELHEADER* panelInfo)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUI.cpp
    // __LINE__: 286
    UTIL_ASSERT(manager != NULL && panelInfo != NULL);

    field_126 = 0;
    m_pManager = manager;
    m_nID = panelInfo->nPanelID;

    if (manager->m_bDoubleSize) {
        m_ptOrigin.x = panelInfo->x * 2;
        m_ptOrigin.y = panelInfo->y * 2;
        m_ptBaseOrigin.x = panelInfo->x * 2;
        m_ptBaseOrigin.y = panelInfo->y * 2;
        m_size.cx = panelInfo->nWidth * 2;
        m_size.cy = panelInfo->nHeight * 2;
    } else {
        m_ptOrigin.x = panelInfo->x;
        m_ptOrigin.y = panelInfo->y;
        m_ptBaseOrigin.x = panelInfo->x;
        m_ptBaseOrigin.y = panelInfo->y;
        m_size.cx = panelInfo->nWidth;
        m_size.cy = panelInfo->nHeight;
    }

    m_bActive = TRUE;
    m_bEnabled = TRUE;
    m_wFlags = panelInfo->wFlags;
    m_nRenderCount = 0;
    field_108 = 0;
    field_109 = 0;
    m_bInactiveRender = FALSE;
    field_112 = 0;

    SetRectEmpty(&field_116);

    if (panelInfo->nType == 1) {
        m_mosBackground.SetResRef(CResRef(panelInfo->refMosaic), FALSE, TRUE);
        m_mosBackground.m_bDoubleSize = m_pManager->m_bDoubleSize;
    }
}

// 0x4D29A0
void CUIPanel::SetInactiveRender(BOOL bInactiveRender)
{
    m_bInactiveRender = bInactiveRender;

    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetNext(pos);
        pControl->SetInactiveRender(bInactiveRender);
    }
}

// 0x4D29D0
void CUIPanel::SetEnabled(BOOL bEnabled)
{
    if (m_bEnabled != bEnabled) {
        m_bEnabled = bEnabled;

        // NOTE: Uninline.
        SetActive(bEnabled);

        // NOTE: Uninline.
        SetInactiveRender(bEnabled == FALSE);

        InvalidateRect(NULL);
    }

    if (bEnabled) {
        m_pManager->field_2E = (m_wFlags & 0x1) == 0;
    }
}

// 0x4D2A60
CUIPanel::~CUIPanel()
{
    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetNext(pos);
        if (pControl != NULL) {
            delete pControl;
        }
    }

    m_lControls.RemoveAll();
}

// 0x4D2AE0
void CUIPanel::AddControl(UI_CONTROL* controlInfo)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUI.cpp
    // __LINE__: 447
    UTIL_ASSERT(controlInfo != NULL);

    CUIControlBase* pControl = CUIControlBase::CreateControl(this, controlInfo);
    if (pControl != NULL) {
        m_lControls.AddTail(pControl);
    }
}

// 0x4D2B20
BOOL CUIPanel::RemoveControl(DWORD nID)
{
    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetAt(pos);
        POSITION curr = pos;

        m_lControls.GetNext(pos);

        if (pControl->m_nID == nID) {
            if (m_pManager->m_pFocusedControl == pControl && m_pManager->m_pFocusedControl != NULL) {
                m_pManager->m_pFocusedControl->KillFocus();
                m_pManager->m_pFocusedControl = NULL;
            }

            m_lControls.RemoveAt(curr);

            // NOTE: Not sure what the check is for.
            if (pControl != NULL) {
                delete pControl;
            }

            return TRUE;
        }
    }

    return TRUE;
}

// 0x4D2B90
DWORD CUIPanel::TimerAsynchronousUpdate()
{
    DWORD nID = -1;

    if (m_bActive || m_bInactiveRender) {
        CPoint pt = g_pBaldurChitin->field_1906 - m_ptOrigin;

        POSITION pos = m_lControls.GetHeadPosition();
        while (pos != NULL) {
            CUIControlBase* pControl = m_lControls.GetNext(pos);
            if (pControl->m_bActive
                && (g_pBaldurChitin->m_pObjectGame->m_cOptions.m_nTooltips != INT_MAX || m_pManager->field_76)
                && pt.x >= pControl->m_nX && pt.x <= pControl->m_nX + pControl->m_nWidth
                && pt.y >= pControl->m_nY && pt.y <= pControl->m_nY + pControl->m_nHeight) {
                pControl->TimerAsynchronousUpdate(TRUE);
                nID = pControl->m_nID;
            } else if (pControl->field_1F) {
                BOOLEAN bInside = FALSE;
                if (pt.x >= pControl->m_nX && pt.x <= pControl->m_nX + pControl->m_nWidth
                    && pt.y >= pControl->m_nY && pt.y <= pControl->m_nY + pControl->m_nHeight) {
                    bInside = TRUE;
                }
                pControl->TimerAsynchronousUpdate(bInside);
            }
        }
    }

    return nID;
}

// 0x4D2CA0
CUIControlBase* CUIPanel::GetControl(DWORD nID)
{
    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetNext(pos);
        if (pControl->m_nID == nID) {
            return pControl;
        }
    }

    return NULL;
}

// 0x4D2CC0
BOOL CUIPanel::IsOver(const CPoint& pt)
{
    CRect rect(m_ptOrigin, m_size);
    m_pManager->m_pWarp->NormalizePanelRect(m_nID, rect);
    return rect.PtInRect(pt);
}

// 0x4D2D20
BOOL CUIPanel::sub_4D2D20()
{
    if ((m_wFlags & 0x1) == 0) {
        return FALSE;
    }

    m_wFlags &= ~0x1;
    field_112 = TRUE;
    return TRUE;
}

// 0x4D2D50
BOOL CUIPanel::sub_4D2D50()
{
    if (!field_112) {
        return FALSE;
    }

    m_wFlags |= 0x1;
    field_112 = FALSE;

    return TRUE;
}

// 0x4D2D80
BOOL CUIPanel::OnLButtonDown(const CPoint& pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    POSITION pos = m_lControls.GetTailPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetPrev(pos);
        if (pt.x - m_ptOrigin.x >= pControl->m_nX
            && pt.x - m_ptOrigin.x <= pControl->m_nX + pControl->m_nWidth
            && pt.y - m_ptOrigin.y >= pControl->m_nY
            && pt.y - m_ptOrigin.y <= pControl->m_nY + pControl->m_nHeight) {
            if (pControl->IsOverPixel(pt - m_ptOrigin)) {
                if (pControl->OnLButtonDown(pt - m_ptOrigin)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

// 0x4D2E60
BOOL CUIPanel::OnLButtonDblClk(const CPoint& pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    POSITION pos = m_lControls.GetTailPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetPrev(pos);
        if (pt.x - m_ptOrigin.x >= pControl->m_nX
            && pt.x - m_ptOrigin.x <= pControl->m_nX + pControl->m_nWidth
            && pt.y - m_ptOrigin.y >= pControl->m_nY
            && pt.y - m_ptOrigin.y <= pControl->m_nY + pControl->m_nHeight) {
            if (pControl->IsOverPixel(pt - m_ptOrigin)) {
                if (pControl->OnLButtonDblClk(pt - m_ptOrigin)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

// 0x4D2F40
void CUIPanel::OnMouseMove(const CPoint& pt)
{
    if (!m_bActive) {
        return;
    }

    if (!field_109) {
        return;
    }

    POSITION pos = m_lControls.GetTailPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetPrev(pos);
        if (pControl->field_20) {
            if (pt.x - m_ptOrigin.x >= pControl->m_nX
                && pt.x - m_ptOrigin.x <= pControl->m_nX + pControl->m_nWidth
                && pt.y - m_ptOrigin.y >= pControl->m_nY
                && pt.y - m_ptOrigin.y <= pControl->m_nY + pControl->m_nHeight) {
                if (pControl->IsOverPixel(pt - m_ptOrigin)) {
                    pControl->OnMouseMove(pt - m_ptOrigin);
                    return;
                }
            }
        }
    }
}

// 0x4D3020
BOOL CUIPanel::OnRButtonDown(const CPoint& pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    POSITION pos = m_lControls.GetTailPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetPrev(pos);
        if (pt.x - m_ptOrigin.x >= pControl->m_nX
            && pt.x - m_ptOrigin.x <= pControl->m_nX + pControl->m_nWidth
            && pt.y - m_ptOrigin.y >= pControl->m_nY
            && pt.y - m_ptOrigin.y <= pControl->m_nY + pControl->m_nHeight) {
            if (pControl->IsOverPixel(pt - m_ptOrigin)) {
                if (pControl->OnRButtonDown(pt - m_ptOrigin)) {
                    return TRUE;
                }
            }
        }
    }

    return FALSE;
}

// 0x4D3100
void CUIPanel::Render()
{
    CRect rDirty(0, 0, 0, 0);

    if (!m_bActive && !m_bInactiveRender) {
        return;
    }

    CRect v2 = m_pManager->field_9A;
    v2.OffsetRect(-m_ptOrigin);

    CRect v3;
    v3.IntersectRect(v2, CRect(0, 0, m_size.cx, m_size.cy));

    m_pManager->m_pWarp->NormalizePanelRect(m_nID, v3);

    CRect v4;
    if (m_nRenderCount == 0) {
        v4 = v3;
    } else {
        v4.UnionRect(m_rDirty, v3);
    }

    if (v4.IsRectEmpty()) {
        rDirty.SetRectEmpty();
    } else {
        CRect rTemp = v4;
        rTemp.OffsetRect(m_ptOrigin);
        rDirty = rTemp;
    }

    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetNext(pos);
        if (pControl->NeedRender()) {
            CRect rControl(CPoint(pControl->m_nX, pControl->m_nY),
                CSize(pControl->m_nWidth, pControl->m_nHeight));
            m_pManager->m_pWarp->NormalizePanelRect(m_nID, rControl);
            if (!rControl.IsRectEmpty()) {
                if (rDirty.IsRectEmpty()) {
                    rDirty = rControl;
                } else {
                    rDirty.UnionRect(rDirty, rControl);
                }
            }
        }
    }

    if (!rDirty.IsRectEmpty()) {
        CRect rMosaic = rDirty;
        rMosaic.OffsetRect(-m_ptOrigin);

        if (m_nRenderCount != 0) {
            CSingleLock lock(&(m_pManager->field_56), FALSE);
            lock.Lock(INFINITE);
            m_nRenderCount--;
            lock.Unlock();
        }

        m_mosBackground.Render(CVIDINF_SURFACE_BACK,
            m_ptOrigin.x,
            m_ptOrigin.y,
            rMosaic,
            rDirty,
            0x1,
            FALSE);

        POSITION pos = m_lControls.GetHeadPosition();
        while (pos != NULL) {
            CUIControlBase* pControl = m_lControls.GetNext(pos);
            CRect rControl(m_ptOrigin + CPoint(pControl->m_nX, pControl->m_nY),
                CSize(pControl->m_nWidth, pControl->m_nHeight));

            CRect rDirtyControl;
            rDirtyControl.IntersectRect(rDirty, rControl);

            if (!rDirtyControl.IsRectNull()) {
                pControl->field_22 = rDirtyControl;
                pControl->Render(TRUE);
            }
        }

        if (!m_bEnabled) {
            RenderDither(rDirty);
        }
    }

    if (m_bEnabled) {
        if (!field_116.IsRectNull()) {
            CRect r;
            r.IntersectRect(field_116, CRect(m_ptOrigin, m_size));
            g_pChitin->cImm.sub_7C3140(field_116, r, field_126, FALSE);
        }
    }
}

// 0x4D3610
void CUIPanel::RenderDither(const CRect& rClip)
{
    // TODO: Incomplete.
}

// 0x4D3810
void CUIPanel::InvalidateRect(const CRect* pRect)
{
    if (m_bActive || m_bInactiveRender) {
        CRect r;
        if (pRect != NULL) {
            r.IntersectRect(pRect, CRect(m_ptOrigin, m_size));
            if (r.IsRectEmpty()) {
                return;
            }
        }

        if (m_nRenderCount == 0) {
            m_rDirty.SetRect(0, 0, 0, 0);
        }

        CSingleLock lock(&(m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount = CBaldurChitin::RENDER_COUNT;
        lock.Unlock();

        if (pRect != NULL) {
            r.OffsetRect(-m_ptOrigin);
            m_rDirty.UnionRect(m_rDirty, r);
        } else {
            m_rDirty.SetRect(0, 0, m_size.cx, m_size.cy);
        }

        if (m_pManager != NULL) {
            m_pManager->m_pWarp->NormalizePanelRect(m_nID, m_rDirty);
        }
    }
}

// 0x4D3980
void CUIPanel::SetActive(BOOL bActive)
{
    m_bActive = bActive;

    POSITION pos = m_lControls.GetHeadPosition();
    while (pos != NULL) {
        CUIControlBase* pControl = m_lControls.GetNext(pos);
        pControl->SetActive(bActive);
    }
}

// 0x5FF320
void CUIPanel::SetBackgroundResRef(CResRef cNewResRef, BOOL bDoubleSize)
{
    m_mosBackground.SetResRef(cNewResRef, TRUE, TRUE);
    m_mosBackground.m_bDoubleSize = bDoubleSize;
}

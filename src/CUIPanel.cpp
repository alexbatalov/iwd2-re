#include "CUIPanel.h"

#include "CBaldurEngine.h"
#include "CUIControlBase.h"
#include "CUIManager.h"
#include "CUtil.h"

// 0x4D2750
CUIPanel::CUIPanel(CUIManager* manager, UI_PANELHEADER* panelInfo)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ChUI.cpp
    // __LINE__: 286
    UTIL_ASSERT(manager != NULL && panelInfo != NULL);

    field_126 = 0;
    m_pManager = manager;
    m_nID = panelInfo->nPanelID;

    if (manager->field_AA) {
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
    field_F2 = 0;
    field_108 = 0;
    field_109 = 0;
    m_bInactiveRender = FALSE;
    field_112 = 0;

    SetRectEmpty(&field_116);

    if (panelInfo->nType == 1) {
        field_3E.SetResRef(CResRef(panelInfo->refMosaic), FALSE, TRUE);
        field_3E.m_bDoubleSize = m_pManager->field_AA;
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

// 0x4D3100
void CUIPanel::Render()
{
    // TODO: Incomplete.
}

// 0x4D3810
void CUIPanel::InvalidateRect(const RECT* pRect)
{
    // TODO: Incomplete.
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

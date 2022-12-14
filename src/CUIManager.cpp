#include "CUIManager.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CUIControlBase.h"
#include "CUIPanel.h"
#include "CWarp.h"

// 0x4D39B0
CUIManager::CUIManager()
{
    field_18 = 1;
    field_2E = 1;
    field_2D = 1;
    m_pWarp = NULL;
    field_2C = 0;
    field_0 = 0;
    field_4 = 0;
    m_pFocusedControl = NULL;
    field_1C = 0;
    field_20 = 0;
    field_24 = 0;
    field_28 = 0;
    field_32 = -1;
    field_76 = 0;
    field_7A.SetRect(0, 0, 0, 0);
    field_8A.SetRect(0, 0, 0, 0);
    field_9A.SetRect(0, 0, 0, 0);
    field_AA = 0;
}

// 0x4D3AB0
CUIManager::~CUIManager()
{
    if (field_4 != 0) {
        POSITION pos = m_lPanels.GetHeadPosition();
        while (pos != NULL) {
            CUIPanel* panel = m_lPanels.GetNext(pos);
            if (panel != NULL) {
                delete panel;
            }
        }
        m_lPanels.RemoveAll();
        field_4 = 0;
    }
}

// 0x4D3DE0
void CUIManager::AddPanel(UI_PANELHEADER* panelInfo)
{
    if (field_4 != 0) {
        if (panelInfo->nWidth != 0 && panelInfo->nHeight != 0) {
            CUIPanel* pPanel = new CUIPanel(this, panelInfo);
            if (pPanel != NULL) {
                m_lPanels.AddTail(pPanel);
            }
        }
    }
}

// 0x4D3E70
void CUIManager::ReorderPanelAfter(DWORD nID1, DWORD nID2)
{
    if (field_4) {
        // NOTE: Uninline.
        CUIPanel* pPanel1 = GetPanel(nID1);
        if (pPanel1 != NULL) {
            // NOTE: Uninline.
            CUIPanel* pPanel2 = GetPanel(nID2);
            if (pPanel2 != NULL) {
                m_lPanels.RemoveAt(m_lPanels.Find(pPanel1, NULL));
                m_lPanels.InsertAfter(m_lPanels.Find(pPanel2, NULL), pPanel1);
            }
        }
    }
}

// 0x4D4000
CUIPanel* CUIManager::GetPanel(DWORD nID)
{
    if (field_4 != 0) {
        POSITION pos = m_lPanels.GetHeadPosition();
        while (pos != NULL) {
            CUIPanel* pPanel = m_lPanels.GetNext(pos);
            if (pPanel->m_nID == nID) {
                return pPanel;
            }
        }
    }

    return NULL;
}

// 0x4D4030
void CUIManager::SetCapture(CUIControlBase* pControl, unsigned char a3)
{
    if (m_pFocusedControl != NULL) {
        m_pFocusedControl->KillFocus();
    }

    m_pFocusedControl = pControl;
    field_2C = a3;

    m_pFocusedControl->SetFocus();
}

// 0x4D4060
void CUIManager::ClearTooltip()
{
    // TODO: Incomplete.
}

// 0x4D42B0
void CUIManager::OnLButtonUp(CPoint pt)
{
    if (m_pFocusedControl != NULL && field_2C == 0) {
        CUIControlBase* pPrevFocusedControl = m_pFocusedControl;

        m_pFocusedControl->OnLButtonUp(pt - m_pFocusedControl->m_pPanel->m_ptOrigin);

        if (pPrevFocusedControl == m_pFocusedControl && field_2C == 0) {
            if (m_pFocusedControl != NULL) {
                m_pFocusedControl->KillFocus();
                m_pFocusedControl = NULL;
            }
        }
    }
}

// 0x4D44B0
void CUIManager::OnRButtonUp(CPoint pt)
{
    if (m_pFocusedControl != NULL && field_2C == 1) {
        CUIControlBase* pPrevFocusedControl = m_pFocusedControl;

        m_pFocusedControl->OnRButtonUp(pt - m_pFocusedControl->m_pPanel->m_ptOrigin);

        if (pPrevFocusedControl == m_pFocusedControl && field_2C == 1) {
            if (m_pFocusedControl != NULL) {
                m_pFocusedControl->KillFocus();
                m_pFocusedControl = NULL;
            }
        }
    }
}

// 0x4D4510
BOOL CUIManager::OnKeyDown(SHORT nKey)
{
    if (field_0 == 0) {
        if (m_pFocusedControl != NULL && field_2C == 2) {
            m_pFocusedControl->OnKeyDown(nKey);
            return TRUE;
        }
    }

    return FALSE;
}

// 0x4D4540
void CUIManager::Render()
{
    CSingleLock renderLock(&field_36, FALSE);
    renderLock.Lock(INFINITE);

    if (field_4 != 0) {
        if (field_18 != 0) {
            if (field_0 == 0) {
                POSITION pos = m_lPanels.GetHeadPosition();
                while (pos != NULL) {
                    CUIPanel* pPanel = m_lPanels.GetNext(pos);
                    pPanel->Render();
                }
            }
        }
    }

    renderLock.Unlock();
}

// 0x4D45E0
void CUIManager::InvalidateRect(const CRect* rect)
{
    if (field_4 != 0) {
        if (field_18 != 0) {
            POSITION pos = m_lPanels.GetHeadPosition();
            while (pos != NULL) {
                CUIPanel* pPanel = m_lPanels.GetNext(pos);
                pPanel->InvalidateRect(rect);
            }
        }
    }
}

// 0x4D4620
void CUIManager::InvalidateCursorRect(const CRect& rect)
{
    field_7A = field_8A;
    field_8A = rect;

    field_9A.left = min(field_8A.left, field_7A.left);
    field_9A.top = min(field_8A.top, field_7A.top);
    field_9A.right = max(field_8A.right, field_7A.right);
    field_9A.bottom = max(field_8A.bottom, field_7A.bottom);
}

// 0x4D46D0
void CUIManager::ForceToolTip()
{
    field_76 = 1;
    field_1C = g_pBaldurChitin->m_pObjectGame->m_cOptions.m_nTooltips;
}

// 0x4D46F0
void CUIManager::ShiftPanels(const CPoint& pt)
{
    POSITION pos = m_lPanels.GetHeadPosition();
    while (pos != NULL) {
        CUIPanel* pPanel = m_lPanels.GetNext(pos);
        pPanel->m_ptOrigin = pPanel->m_ptBaseOrigin + pt;
    }
}

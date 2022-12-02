#include "CUIManager.h"

// 0x4D39B0
CUIManager::CUIManager()
{
    field_18 = 1;
    field_2E = 1;
    field_2D = 1;
    field_10 = 0;
    field_2C = 0;
    field_0 = 0;
    field_4 = 0;
    field_14 = 0;
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

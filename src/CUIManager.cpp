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
    SetRect(&field_7A, 0, 0, 0, 0);
    SetRect(&field_8A, 0, 0, 0, 0);
    SetRect(&field_9A, 0, 0, 0, 0);
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

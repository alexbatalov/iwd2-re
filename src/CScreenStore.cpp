#include "CScreenStore.h"

#include "CBaldurChitin.h"

// 0x6709E0
CScreenStore::CScreenStore()
{
    // TODO: Incomplete.
}

// 0x671830
CScreenStore::~CScreenStore()
{
    // TODO: Incomplete.
}

// 0x683720
CUIControlPortraitStore::CUIControlPortraitStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x683770
CUIControlPortraitStore::~CUIControlPortraitStore()
{
}

// 0x683810
void CUIControlPortraitStore::OnLButtonClick(CPoint pt)
{
    static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnPortraitLClick(m_nID);
}

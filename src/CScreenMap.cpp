#include "CScreenMap.h"

#include "CBaldurChitin.h"
#include "CUtil.h"

// 0x63F960
CScreenMap::CScreenMap()
{
    // TODO: Incomplete.
}

// 0x640610
CScreenMap::~CScreenMap()
{
    // TODO: Incomplete.
}

// 0x6422D0
void CScreenMap::OnErrorButtonClick(INT nButton)
{
    // TODO: Incomplete.
}

// 0x642460
void CScreenMap::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x6424D0
void CScreenMap::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x6458B0
CUIControlButtonMapError::CUIControlButtonMapError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x645900
CUIControlButtonMapError::~CUIControlButtonMapError()
{
}

// 0x6459A0
void CUIControlButtonMapError::OnLButtonClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4202
    UTIL_ASSERT(pMap != NULL);

    pMap->OnErrorButtonClick(m_nID);
}

// -----------------------------------------------------------------------------

// 0x6459E0
CUIControlButtonMapNoteDone::CUIControlButtonMapNoteDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x645A30
CUIControlButtonMapNoteDone::~CUIControlButtonMapNoteDone()
{
}

// 0x645AD0
void CUIControlButtonMapNoteDone::OnLButtonClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4246
    UTIL_ASSERT(pMap != NULL);

    pMap->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x645B10
CUIControlButtonMapNoteCancel::CUIControlButtonMapNoteCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x645B60
CUIControlButtonMapNoteCancel::~CUIControlButtonMapNoteCancel()
{
}

// 0x645C00
void CUIControlButtonMapNoteCancel::OnLButtonClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4290
    UTIL_ASSERT(pMap != NULL);

    pMap->OnCancelButtonClick();
}

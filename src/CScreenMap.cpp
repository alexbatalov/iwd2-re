#include "CScreenMap.h"

#include "CBaldurChitin.h"
#include "CScreenWorldMap.h"
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

// 0x6426E0
CUIControlButtonMapWorld::CUIControlButtonMapWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_nToolTipStrRef = 15418;
}

// 0x642740
CUIControlButtonMapWorld::~CUIControlButtonMapWorld()
{
}

// 0x6427E0
void CUIControlButtonMapWorld::OnLButtonClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 2037
    UTIL_ASSERT(pMap != NULL);

    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 2039
    UTIL_ASSERT(pWorldMap != NULL);

    CSingleLock renderLock(&(pMap->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pWorldMap->StartWorldMap(0, 8, 0);
    pMap->SelectEngine(pWorldMap);

    renderLock.Unlock();
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

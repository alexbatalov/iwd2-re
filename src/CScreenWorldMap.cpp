#include "CScreenWorldMap.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenMap.h"
#include "CScreenWorld.h"
#include "CTimerWorld.h"
#include "CUIControlEdit.h"
#include "CUIControlScrollBar.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F89DC
const LONG FATIGUE_TIME_CAP = 24 * CTimerWorld::TIMESCALE_MSEC_PER_HOUR;

// 0x698860
CScreenWorldMap::CScreenWorldMap()
{
    m_nEngineState = 0;
    m_pMapControl = NULL;
    field_FF2 = 0;
    field_FF6 = 0;
    field_FFE = 0;
    m_nCurrentLink = 0;
    m_bInControl = FALSE;
    m_bClickedArea = FALSE;
    field_1050 = 0;

    SetVideoMode(0);

    m_pVirtualKeys[0] = CKeyInfo(VK_ESCAPE, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo('1', 0, 0);
    m_pVirtualKeys[2] = CKeyInfo('2', 0, 0);
    m_pVirtualKeys[3] = CKeyInfo('3', 0, 0);
    m_pVirtualKeys[4] = CKeyInfo('4', 0, 0);
    m_pVirtualKeys[5] = CKeyInfo('5', 0, 0);
    m_pVirtualKeys[6] = CKeyInfo('6', 0, 0);
    m_pVirtualKeys[7] = CKeyInfo('7', 0, 0);
    m_pVirtualKeys[8] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[9] = CKeyInfo('9', 0, 0);
    m_pVirtualKeys[10] = CKeyInfo(VK_SPACE, -1, 0);
    m_pVirtualKeys[11] = CKeyInfo('A', 0, 0);
    m_pVirtualKeys[12] = CKeyInfo('B', 0, 0);
    m_pVirtualKeys[13] = CKeyInfo('C', 0, 0);
    m_pVirtualKeys[14] = CKeyInfo('D', 0, 0);
    m_pVirtualKeys[15] = CKeyInfo('E', 0, 0);
    m_pVirtualKeys[16] = CKeyInfo('F', 0, 0);
    m_pVirtualKeys[17] = CKeyInfo('G', 0, 0);
    m_pVirtualKeys[18] = CKeyInfo('H', 0, 0);
    m_pVirtualKeys[19] = CKeyInfo('I', 0, 0);
    m_pVirtualKeys[20] = CKeyInfo('J', 0, 0);
    m_pVirtualKeys[21] = CKeyInfo('K', 0, 0);
    m_pVirtualKeys[22] = CKeyInfo('L', 0, 0);
    m_pVirtualKeys[23] = CKeyInfo('M', 0, 0);
    m_pVirtualKeys[24] = CKeyInfo('N', 0, 0);
    m_pVirtualKeys[25] = CKeyInfo('O', 0, 0);
    m_pVirtualKeys[26] = CKeyInfo('P', 0, 0);
    m_pVirtualKeys[27] = CKeyInfo('Q', 0, 0);
    m_pVirtualKeys[28] = CKeyInfo('R', 0, 0);
    m_pVirtualKeys[29] = CKeyInfo('S', 0, 0);
    m_pVirtualKeys[30] = CKeyInfo('T', 0, 0);
    m_pVirtualKeys[31] = CKeyInfo('U', 0, 0);
    m_pVirtualKeys[32] = CKeyInfo('V', 0, 0);
    m_pVirtualKeys[33] = CKeyInfo('W', 0, 0);
    m_pVirtualKeys[34] = CKeyInfo('X', 0, 0);
    m_pVirtualKeys[35] = CKeyInfo('Y', 0, 0);
    m_pVirtualKeys[36] = CKeyInfo('Z', 0, 0);
    m_pVirtualKeys[37] = CKeyInfo('0', 0, 0);
    m_pVirtualKeys[38] = CKeyInfo(VK_BACK, 0, 0);
    m_pVirtualKeys[39] = CKeyInfo(VK_END, -1, 0);
    m_pVirtualKeys[40] = CKeyInfo(VK_HOME, -1, 0);
    m_pVirtualKeys[41] = CKeyInfo(VK_LEFT, 0, 0);
    m_pVirtualKeys[42] = CKeyInfo(VK_UP, 0, 0);
    m_pVirtualKeys[43] = CKeyInfo(VK_RIGHT, 0, 0);
    m_pVirtualKeys[44] = CKeyInfo(VK_DOWN, 0, 0);
    m_pVirtualKeys[45] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[46] = CKeyInfo(VK_INSERT, -1, 0);
    m_pVirtualKeys[47] = CKeyInfo(VK_DELETE, 0, 0);
    m_pVirtualKeys[48] = CKeyInfo(VK_NUMPAD0, -1, 0);
    m_pVirtualKeys[49] = CKeyInfo(VK_NUMPAD1, -1, 0);
    m_pVirtualKeys[50] = CKeyInfo(VK_NUMPAD2, -1, 0);
    m_pVirtualKeys[51] = CKeyInfo(VK_NUMPAD3, -1, 0);
    m_pVirtualKeys[52] = CKeyInfo(VK_NUMPAD4, -1, 0);
    m_pVirtualKeys[53] = CKeyInfo(VK_NUMPAD5, -1, 0);
    m_pVirtualKeys[54] = CKeyInfo(VK_NUMPAD6, -1, 0);
    m_pVirtualKeys[55] = CKeyInfo(VK_NUMPAD7, -1, 0);
    m_pVirtualKeys[56] = CKeyInfo(VK_NUMPAD8, -1, 0);
    m_pVirtualKeys[57] = CKeyInfo(VK_NUMPAD9, -1, 0);
    m_pVirtualKeys[58] = CKeyInfo(VK_MULTIPLY, -1, 0);
    m_pVirtualKeys[59] = CKeyInfo(VK_ADD, -1, 0);
    m_pVirtualKeys[60] = CKeyInfo(VK_SEPARATOR, -1, 0);
    m_pVirtualKeys[61] = CKeyInfo(VK_SUBTRACT, -1, 0);
    m_pVirtualKeys[62] = CKeyInfo(VK_DECIMAL, -1, 0);
    m_pVirtualKeys[63] = CKeyInfo(VK_DIVIDE, -1, 0);
    m_pVirtualKeys[64] = CKeyInfo(VK_F1, -1, 0);
    m_pVirtualKeys[65] = CKeyInfo(VK_F2, -1, 0);
    m_pVirtualKeys[66] = CKeyInfo(VK_F3, -1, 0);
    m_pVirtualKeys[67] = CKeyInfo(VK_F4, -1, 0);
    m_pVirtualKeys[68] = CKeyInfo(VK_F5, -1, 0);
    m_pVirtualKeys[69] = CKeyInfo(VK_F6, -1, 0);
    m_pVirtualKeys[70] = CKeyInfo(VK_F7, -1, 0);
    m_pVirtualKeys[71] = CKeyInfo(VK_F8, -1, 0);
    m_pVirtualKeys[72] = CKeyInfo(VK_F9, -1, 0);
    m_pVirtualKeys[73] = CKeyInfo(VK_F10, -1, 0);
    m_pVirtualKeys[74] = CKeyInfo(VK_F11, -1, 0);
    m_pVirtualKeys[75] = CKeyInfo(VK_F12, -1, 0);
    m_pVirtualKeys[76] = CKeyInfo(VK_NUMLOCK, -1, 0);
    m_pVirtualKeys[77] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[78] = CKeyInfo(VK_OEM_3, 0, 0);
    m_pVirtualKeys[79] = CKeyInfo(VK_OEM_MINUS, 0, 0);
    m_pVirtualKeys[80] = CKeyInfo(VK_OEM_PLUS, 0, 0);
    m_pVirtualKeys[81] = CKeyInfo(VK_OEM_4, 0, 0);
    m_pVirtualKeys[82] = CKeyInfo(VK_OEM_6, 0, 0);
    m_pVirtualKeys[83] = CKeyInfo(VK_OEM_5, 0, 0);
    m_pVirtualKeys[84] = CKeyInfo(VK_OEM_1, 0, 0);
    m_pVirtualKeys[85] = CKeyInfo(VK_OEM_7, 0, 0);
    m_pVirtualKeys[86] = CKeyInfo(VK_OEM_COMMA, 0, 0);
    m_pVirtualKeys[87] = CKeyInfo(VK_OEM_PERIOD, 0, 0);
    m_pVirtualKeys[88] = CKeyInfo(VK_OEM_2, 0, 0);
    m_pVirtualKeys[89] = CKeyInfo(VK_TAB, -1, 0);

    m_bCtrlKeyDown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_ptMapView.x = 0;
    m_ptMapView.y = 0;
    field_FCA = RGB(224, 180, 15);
    m_vfLabel.SetColor(field_FCA, 0, FALSE);
    field_FCE = -1;
    m_nSelectedArea = -1;
    m_bOverSelectedArea = FALSE;
    m_nToolTip = 0;
    m_ptMapStartMousePos.x = 0;
    m_ptMapStartMousePos.y = 0;
    m_ptMapStartView.x = 0;
    m_ptMapStartView.y = 0;
    m_bMapLeftDown = FALSE;
    m_bMapDragging = FALSE;
    m_pPath = NULL;
    m_pMainPanel = NULL;
    m_pChatDisplay = NULL;
    field_104A = 0;
}

// 0x49FC40
BOOL CScreenWorldMap::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x6995A0
void CScreenWorldMap::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x6995B0
BOOL CScreenWorldMap::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenWorldMap::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x6995C0
void CScreenWorldMap::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x6995D0
BOOL CScreenWorldMap::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenWorldMap::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x6995E0
void CScreenWorldMap::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x6995F0
BOOL CScreenWorldMap::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x699600
SHORT CScreenWorldMap::GetNumVirtualKeys()
{
    return CSCREENWORLDMAP_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenWorldMap::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x699620
BYTE* CScreenWorldMap::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x699650
CScreenWorldMap::~CScreenWorldMap()
{
    // TODO: Incomplete.
}

// 0x699E40
void CScreenWorldMap::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontTool.Unload();

    field_FE = 0;
    field_102 = 0;

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    m_bOverSelectedArea = FALSE;
    m_bMapLeftDown = FALSE;
    m_bMapDragging = FALSE;
    field_FCE = -1;
    m_nSelectedArea = -1;

    g_pBaldurChitin->GetObjectGame()->m_tempCursor = 4;
}

// 0x699F10
void CScreenWorldMap::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIWMAP"), g_pBaldurChitin->field_4A28);

    CPoint pt;
    if (g_pBaldurChitin->field_4A28) {
        pt.x = CVideo::SCREENWIDTH / 2 - CBaldurChitin::DEFAULT_SCREEN_WIDTH;
        pt.y = CVideo::SCREENHEIGHT / 2 - CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
    } else {
        pt.x = (CVideo::SCREENWIDTH - CBaldurChitin::DEFAULT_SCREEN_WIDTH) / 2;
        pt.y = (CVideo::SCREENHEIGHT - CBaldurChitin::DEFAULT_SCREEN_HEIGHT) / 2;
    }

    m_cUIManager.ShiftPanels(pt);

    for (int index = 0; index < 4; index++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->field_49B4[index]));
    }

    m_ptMapView.x = 0;
    m_ptMapView.y = 0;
    m_nSelectedCharacter = 0;
    m_pCurrentScrollBar = NULL;
    field_FCA = RGB(224, 180, 15);
    m_vfLabel.SetColor(field_FCA, field_FCA, FALSE);
    field_FCE = 0;
    m_nSelectedArea = -1;
    m_ptMapStartMousePos.x = 0;
    m_ptMapStartMousePos.y = 0;
    m_bOverSelectedArea = FALSE;
    m_bMapLeftDown = FALSE;
    m_bMapDragging = FALSE;
    m_pPath = NULL;
    m_pMainPanel = NULL;
    m_pChatDisplay = NULL;
    field_104A = 0;
    m_ptMapStartView.x = 0;
    m_ptMapStartView.y = 0;
}

// 0x5D72C0
void CScreenWorldMap::EngineGameUninit()
{
    m_cUIManager.fUninit();
}

// 0x49FC40
BOOL CScreenWorldMap::CheckMouseMove()
{
    return TRUE;
}

// 0x69A400
void CScreenWorldMap::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
    m_nToolTip = 0;
}

// 0x49FC40
BOOL CScreenWorldMap::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenWorldMap::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenWorldMap::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenWorldMap::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenWorldMap::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenWorldMap::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenWorldMap::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x69A430
void CScreenWorldMap::TimerAsynchronousUpdate()
{
    if (m_pChatDisplay != NULL) {
        field_104A = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(m_pChatDisplay, field_104A);
    }

    if (m_nEngineState == 0) {
        g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    }

    OnMapAsyncUpdate();

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x63BAA0
void CScreenWorldMap::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x69A4B0
void CScreenWorldMap::UpdateMainPanel()
{
    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(m_pMainPanel->GetControl(6));
}

// NOTE: Inlined.
void CScreenWorldMap::OnDoneButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nEngineState) {
    case 0:
        StopWorldMap(FALSE);
        SelectEngine(g_pBaldurChitin->m_pEngineMap);
        break;
    case 1:
        if (m_bInControl && !m_bClickedArea) {
            StopWorldMap(FALSE);
            SelectEngine(g_pBaldurChitin->m_pEngineWorld);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 1405
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x69A4D0
void CScreenWorldMap::SetMapView(const CPoint& ptMapView)
{
    // TODO: Incomplete.
}

// 0x69A640
void CScreenWorldMap::OnMapMouseDown(const CPoint& ptMousePos)
{
    // TODO: Incomplete.
}

// 0x69A840
void CScreenWorldMap::OnMapMouseUp(const CPoint& ptMousePos)
{
    // TODO: Incomplete.
}

// 0x69A920
void CScreenWorldMap::OnMapMouseMove(const CPoint& ptMousePos)
{
    // TODO: Incomplete.
}

// 0x69A9D0
void CScreenWorldMap::OnMapAsyncUpdate()
{
    // TODO: Incomplete.
}

// 0x69BA70
BOOL CScreenWorldMap::DrawMap(const CRect& r)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x69C2A0
void CScreenWorldMap::StartWorldMap(INT nEngineState, LONG nLeavingEdge, BOOLEAN bInControl)
{
    // TODO: Incomplete.
}

// 0x69C9E0
void CScreenWorldMap::StopWorldMap(BOOLEAN bAreaClicked)
{
    // TODO: Incomplete.
}

// 0x69CE20
DWORD CScreenWorldMap::FindAreaHit(const CPoint& pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 2824
    UTIL_ASSERT(pGame != NULL);

    CString sResArea;

    pGame->GetVisibleArea()->m_resRef.CopyToString(sResArea);

    CWorldMap* pWorldMap = pGame->GetWorldMap(sResArea);

    CPoint ptMapPos = m_ptMapView + pt;
    DWORD nFoundArea = -1;

    DWORD nNumAreas = pWorldMap->GetNumAreas(pWorldMap->sub_55A3A0());
    for (DWORD nArea = 0; nArea < nNumAreas; nArea++) {
        CRect rArea = field_1012[nArea];
        if (rArea.PtInRect(ptMapPos)
            && (pWorldMap->GetArea(pWorldMap->sub_55A3A0(), nArea)->m_dwFlags & 0x4) != 0) {
            nFoundArea = nArea;
            break;
        }
    }

    return nFoundArea;
}

// 0x69CF90
void CScreenWorldMap::InvalidateArea(DWORD nArea)
{
    if (nArea != -1 && field_1016 > 0) {
        CRect rArea = field_1012[nArea];
        CRect rControl(m_pMapControl->m_ptOrigin, m_pMapControl->m_size);

        rArea.OffsetRect(-m_ptMapView);
        rArea.OffsetRect(m_pMapControl->m_ptOrigin);

        CRect rDirty;
        rDirty.IntersectRect(rArea, rControl);

        if (!rDirty.IsRectNull()) {
            m_pMapControl->m_pPanel->InvalidateRect(&rDirty);
        }
    }
}

// 0x69FFC0
void CScreenWorldMap::GetMarkerPosition(CPoint& ptMarker)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4208
    UTIL_ASSERT(pGame != NULL);

    CString sResArea;

    pGame->GetVisibleArea()->m_resRef.CopyToString(sResArea);

    CWorldMap* pWorldMap = pGame->GetWorldMap(sResArea);

    if (m_nCurrentLink != -1) {
        DWORD nSrcArea = pWorldMap->FindSourceAreaIndex(pWorldMap->sub_55A3A0(), m_nCurrentLink);
        DWORD nDstArea = pWorldMap->GetLink(pWorldMap->sub_55A3A0(), m_nCurrentLink)->m_nArea;
        CWorldMapArea* pSrcArea = pWorldMap->GetArea(pWorldMap->sub_55A3A0(), nSrcArea);
        CWorldMapArea* pDstArea = pWorldMap->GetArea(pWorldMap->sub_55A3A0(), nDstArea);
        ptMarker.y = (pSrcArea->m_mapLocationY + pDstArea->m_mapLocationY) / 2;
        ptMarker.x = (pWorldMap->GetAreaPosition(pSrcArea).cx + pWorldMap->GetAreaPosition(pDstArea).cx) / 2;
    } else {
        if (m_cResCurrentArea == "") {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 4258
            UTIL_ASSERT(FALSE);
        }

        DWORD nArea;
        if (pWorldMap->GetAreaIndex(pWorldMap->sub_55A3A0(), m_cResCurrentArea, nArea)
            || pWorldMap->GetAreaIndex(pWorldMap->sub_55A3A0(), CResRef("AR2626"), nArea)) {
            CRect rArea = field_1012[nArea];
            ptMarker.x = (rArea.left + rArea.right) / 2;
            ptMarker.y = rArea.top;
        } else {
            ptMarker.x = 0;
            ptMarker.y = 0;
        }
    }
}

// 0x6A01C0
void CScreenWorldMap::ClearChatMessages()
{
    field_104A = 0;
}

// 0x6A01D0
void CScreenWorldMap::GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture)
{
    if (m_pMainPanel->m_nID == 3) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(m_pMainPanel->GetControl(7));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 4442
        UTIL_ASSERT(pEdit != NULL);

        sChatText = pEdit->GetText();
        bInputCapture = m_cUIManager.m_pFocusedControl == pEdit;
    } else {
        sChatText = "";
        bInputCapture = FALSE;
    }
}

// 0x6A02A0
void CScreenWorldMap::SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture)
{
    if (m_pMainPanel->m_nID == 3) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(m_pMainPanel->GetControl(7));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 4480
        UTIL_ASSERT(pEdit != NULL);

        pEdit->SetText(sChatText);

        if (bInputCapture) {
            m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
        }
    }
}

// -----------------------------------------------------------------------------

// 0x6A0310
CUIControlButtonWorldMapScroll::CUIControlButtonWorldMapScroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
}

// 0x6A0310
CUIControlButtonWorldMapScroll::~CUIControlButtonWorldMapScroll()
{
}

// 0x6A03F0
void CUIControlButtonWorldMapScroll::AdjustValue()
{
    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4543
    UTIL_ASSERT(pWorldMap != NULL);

    switch (m_nID) {
    case 1:
        if (!pWorldMap->m_bMapDragging) {
            pWorldMap->SetMapView(pWorldMap->m_ptMapView - CPoint(0, 20));
        }
        break;
    case 2:
        if (!pWorldMap->m_bMapDragging) {
            pWorldMap->SetMapView(pWorldMap->m_ptMapView + CPoint(0, 20));
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 4556
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x6A04B0
CUIControlButtonWorldMapDone::CUIControlButtonWorldMapDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x6A0500
CUIControlButtonWorldMapDone::~CUIControlButtonWorldMapDone()
{
}

// 0x6A05A0
void CUIControlButtonWorldMapDone::OnLButtonClick(CPoint pt)
{
    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4609
    UTIL_ASSERT(pWorldMap != NULL);

    // NOTE: Uninline.
    pWorldMap->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6A06B0
CUIControlButtonWorldMapWorldMap::CUIControlButtonWorldMapWorldMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    field_676 = 0;
    field_67A = 0;
}

// 0x6A0710
CUIControlButtonWorldMapWorldMap::~CUIControlButtonWorldMapWorldMap()
{
}

// 0x6A07B0
BOOL CUIControlButtonWorldMapWorldMap::Render(BOOL bForce)
{
    if (!m_bActive || !m_bInactiveRender) {
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

    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4701
    UTIL_ASSERT(pWorldMap != NULL);

    CRect r = m_rDirty;
    r.OffsetRect(-m_ptOrigin);
    r.OffsetRect(-m_pPanel->m_ptOrigin);

    return pWorldMap->DrawMap(r);
}

// 0x6A0940
void CUIControlButtonWorldMapWorldMap::OnLButtonUp(CPoint pt)
{
    if (m_bActive) {
        if ((m_nMouseButtons & LBUTTON) != 0) {
            // NOTE: Uninline.
            m_pPanel->m_pManager->KillCapture();

            CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 4740
            UTIL_ASSERT(pWorldMap != NULL);

            pWorldMap->OnMapMouseUp(pt);
        }
    }
}

// 0x6A09B0
BOOL CUIControlButtonWorldMapWorldMap::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSELBUTTON);
    m_pPanel->m_pManager->field_2D = 0;
    m_pPanel->m_pManager->field_32 = m_nID;
    m_pPanel->m_pManager->field_1C = 0;

    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4780
    UTIL_ASSERT(pWorldMap != NULL);

    pWorldMap->OnMapMouseDown(pt);

    return TRUE;
}

// 0x6A0A40
void CUIControlButtonWorldMapWorldMap::OnMouseMove(CPoint pt)
{
    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 4832
    UTIL_ASSERT(pWorldMap != NULL);

    pWorldMap->OnMapMouseMove(pt);
}

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
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

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
    m_nChatMessageCount = 0;
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

// 0x699760
void CScreenWorldMap::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    if (m_cUIManager.m_bInitialized) {
        m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
        m_preLoadFontRealms.RegisterFont();

        m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
        m_preLoadFontTool.RegisterFont();

        CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
        CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 328
        UTIL_ASSERT(pLeftPanel != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 329
        UTIL_ASSERT(pRightPanel != NULL);

        pLeftPanel->SetEnabled(FALSE);
        pRightPanel->SetEnabled(FALSE);

        CheckEnablePortaits(1);
        CheckEnableLeftPanel();

        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(m_pMainPanel->GetControl(6));

        UpdateCursorShape(0);
        g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);

        m_nToolTip = 0;
        m_cUIManager.InvalidateRect(NULL);

        if (m_pChatDisplay != NULL) {
            m_nChatMessageCount = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(m_pChatDisplay,
                m_nChatMessageCount);
            m_pChatDisplay->ScrollToBottom();
        }

        CResRef cResRef = "WorldE";

        C2DArray tWorldE;
        tWorldE.Load(cResRef);
        if (tWorldE.Demand()) {
            tWorldE.Release();

            CString sResArea;

            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

            pGame->GetVisibleArea()->m_resRef.CopyToString(sResArea);

            CWorldMap* pWorldMap = pGame->GetWorldMap(sResArea);
            DWORD nMap = pWorldMap->sub_55A3A0();

            for (INT y = 0; y < tWorldE.GetHeight(); y++) {
                CString sOtherResArea;
                sOtherResArea = tWorldE.GetAt(CPoint(1, y));
                if (sOtherResArea.GetLength() > 0) {
                    DWORD nMap = pWorldMap->sub_55A450(sOtherResArea);

                    pWorldMap->SetExplorable(nMap,
                        CResRef(sOtherResArea),
                        FALSE);

                    CString sVarName = tWorldE.GetAt(CPoint(0, y));

                    CVariable* pVar = g_pBaldurChitin->GetObjectGame()->GetVariables()->FindKey(sVarName);
                    if (pVar != NULL) {
                        if (pVar->GetName() != "") {
                            if (pVar->m_intValue != 0) {
                                pWorldMap->EnableArea(nMap,
                                    CResRef(sOtherResArea),
                                    TRUE);

                                g_pBaldurChitin->GetBaldurMessage()->SendMapWorldRevealArea(sOtherResArea);
                            } else {
                                pWorldMap->EnableArea(nMap,
                                    CResRef(sOtherResArea),
                                    FALSE);
                            }
                        }
                    }
                }
            }

            pWorldMap->SetExplorable(nMap, CResRef(sResArea), TRUE);

            DWORD nArea;
            if (pWorldMap->GetAreaIndex(nMap, CResRef(sResArea), nArea)) {
                // FIXME: Unused.
                pWorldMap->GetArea(nMap, nArea);

                DWORD nMap = pWorldMap->sub_55A3A0();
                CWorldMapList* pLinks = pWorldMap->GetAllLinks(nMap, nArea);

                POSITION pos = pLinks->GetHeadPosition();
                while (pos != NULL) {
                    DWORD nLink = pLinks->GetNext(pos);
                    CWorldMapLinks* pLink = pWorldMap->GetLink(nMap, nLink);
                    CWorldMapArea* pArea = pWorldMap->GetArea(nMap, pLink->m_nArea);
                    if (pArea != NULL) {
                        pWorldMap->SetExplorable(nMap,
                            CResRef(pArea->m_resCurrentArea),
                            (pArea->m_dwFlags & 0x1) != 0);
                    }
                }

                delete pLinks;
            }
        }
    }
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
    m_nChatMessageCount = 0;
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

// 0x69A0A0
void CScreenWorldMap::OnKeyDown(SHORT nKeysFlags)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 688
    UTIL_ASSERT(pGame != NULL);

    for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
        if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_TAB:
                m_cUIManager.ForceToolTip();
                m_nToolTip = pGame->GetOptions()->m_nTooltips;
                break;
            case VK_RETURN:
                OnDoneButtonClick();
                break;
            case VK_ESCAPE:
                OnCancelButtonClick();
                break;
            case VK_UP:
                if (!m_bMapDragging) {
                    SetMapView(CPoint(m_ptMapView.x, m_ptMapView.y - 20));
                }
                break;
            case VK_DOWN:
                if (!m_bMapDragging) {
                    SetMapView(CPoint(m_ptMapView.x, m_ptMapView.y + 20));
                }
                break;
            case VK_SNAPSHOT:
                g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                break;
            default:
                for (SHORT index = 0; index < CINFGAME_KEYMAP_SIZE; index) {
                    // __FILE__: .\Include\InfGame.h
                    // __LINE__: 1486
                    UTIL_ASSERT(index >= 0 && index < CINFGAME_KEYMAP_SIZE);

                    // __FILE__: .\Include\InfGame.h
                    // __LINE__: 1487
                    UTIL_ASSERT(index >= 0 && index < CINFGAME_KEYMAP_SIZE);

                    if (pGame->m_pKeymap[index] == m_pVirtualKeysFlags[nKeyFlag]
                        && pGame->m_pKeymapFlags[index] == m_bCtrlKeyDown) {
                        switch (index) {
                        case 24:
                            FocusChatEditBox();
                            break;
                        }
                        break;
                    }
                }
            }
        }
    }
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
        m_nChatMessageCount = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(m_pChatDisplay, m_nChatMessageCount);
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
void CScreenWorldMap::OnCancelButtonClick()
{
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
        // __LINE__: 1362
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Inlined.
void CScreenWorldMap::OnDoneButtonClick()
{
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
}

// 0x69A4D0
void CScreenWorldMap::SetMapView(const CPoint& ptMapView)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 1438
    UTIL_ASSERT(pGame != NULL);

    CString sArea;
    pGame->GetVisibleArea()->m_resRef.CopyToString(sArea);

    CWorldMap* pWorldMap = pGame->GetWorldMap(sArea);

    if (pGame->sub_5C79C0(sArea)) {
        CSize cViewSize = m_pMapControl->m_size;
        cViewSize.cx += 1;
        cViewSize.cy += 1;

        CSize cMapSize = pWorldMap->GetMapSize(pWorldMap->sub_55A3A0());

        CPoint ptNewView;
        ptNewView.x = max(min(ptMapView.x, cMapSize.cx - cViewSize.cx), 0);
        ptNewView.y = max(min(ptMapView.y, cMapSize.cy - cViewSize.cy), 0);

        if (ptNewView != m_ptMapView) {
            m_ptMapView = ptNewView;
            m_pMapControl->InvalidateRect();
            m_nToolTip = 0;
        }
    }
}

// 0x69A640
void CScreenWorldMap::OnMapMouseDown(const CPoint& ptMousePos)
{
    m_ptMapStartMousePos = ptMousePos;
    m_ptMapStartView = m_ptMapView;
    m_bMapLeftDown = TRUE;
    m_bMapDragging = FALSE;
    m_bOverSelectedArea = FALSE;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 1495
    UTIL_ASSERT(pGame != NULL);

    CString sArea;
    pGame->GetVisibleArea()->m_resRef.CopyToString(sArea);

    CWorldMap* pWorldMap = pGame->GetWorldMap(sArea);

    if (m_nEngineState == 1
        && m_bInControl
        && !m_bClickedArea) {
        m_nSelectedArea = -1;

        if (m_pMapControl->IsOver(ptMousePos)) {
            m_nSelectedArea = FindAreaHit(ptMousePos - m_pMapControl->m_ptOrigin);
        }

        if (m_nSelectedArea != -1) {
            CWorldMapArea* pArea = pWorldMap->GetArea(pWorldMap->sub_55A3A0(), m_nSelectedArea);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 1513
            UTIL_ASSERT(pArea != NULL);

            if ((pArea->m_dwFlags & 0x1) != 0 && (pArea->m_dwFlags & 0x4) != 0) {
                m_bOverSelectedArea = TRUE;
                InvalidateArea(m_nSelectedArea);
            } else {
                m_nSelectedArea = -1;
                m_bOverSelectedArea = FALSE;
            }
        }
    }
}

// 0x69A840
void CScreenWorldMap::OnMapMouseUp(const CPoint& ptMousePos)
{
    if (m_nEngineState == 1
        && m_bInControl
        && !m_bClickedArea
        && m_nSelectedArea != -1) {
        DWORD nSelectedArea = -1;
        if (m_pMapControl->IsOver(ptMousePos)) {
            nSelectedArea = FindAreaHit(ptMousePos - m_pMapControl->m_ptOrigin);
        }

        if (nSelectedArea == m_nSelectedArea) {
            OnAreaMouseClick(m_nSelectedArea, ptMousePos);
        }

        InvalidateArea(m_nSelectedArea);

        m_nSelectedArea = -1;
        m_bOverSelectedArea = FALSE;
    }

    m_bMapLeftDown = FALSE;
    m_bMapDragging = FALSE;
}

// 0x69A920
void CScreenWorldMap::OnMapMouseMove(const CPoint& ptMousePos)
{
    if (m_bMapLeftDown) {
        if (m_nEngineState == 0
            || !m_bInControl
            || m_bClickedArea
            || m_nEngineState != 1
            || m_nSelectedArea == -1) {
            CPoint pt = ptMousePos - m_ptMapStartMousePos;
            if (pt.x < -5 || pt.x > 5 || pt.y <= -5 || pt.y >= 5) {
                m_bMapDragging = TRUE;
            }

            if (m_bMapDragging) {
                SetMapView(m_ptMapStartView - pt);
            }
        }
    }
}

// 0x69A9D0
void CScreenWorldMap::OnMapAsyncUpdate()
{
    // TODO: Incomplete.
}

// 0x69ACF0
void CScreenWorldMap::OnAreaMouseClick(DWORD nArea, const CPoint& ptMousePos)
{
    // TODO: Incomplete.
}

// 0x69BA70
BOOL CScreenWorldMap::DrawMap(const CRect& r)
{
    BOOL bResult;

    CSingleLock renderLock(&field_1022, FALSE);
    renderLock.Lock(INFINITE);

    if (m_aAreaRect.GetCount() != 0) {
        CString sLabel;

        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 2244
        UTIL_ASSERT(pGame != NULL);

        CString sArea;
        pGame->GetVisibleArea()->m_resRef.CopyToString(sArea);

        CWorldMap* pWorldMap = pGame->GetWorldMap(sArea);

        CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());

        CRect rControl(m_pMapControl->m_pPanel->m_ptOrigin + m_pMapControl->m_ptOrigin,
            m_pMapControl->m_size);

        CRect rMap1(r);
        rMap1.OffsetRect(rControl.TopLeft());

        CRect rClip;
        rClip.IntersectRect(rControl, rMap1);

        CSize mapSize = pWorldMap->GetMapSize(pWorldMap->sub_55A3A0());

        if (mapSize.cx >= m_pMapControl->m_size.cx) {
            mapSize.cx = m_pMapControl->m_size.cx;
        }

        if (mapSize.cy >= m_pMapControl->m_size.cy) {
            mapSize.cy = m_pMapControl->m_size.cy;
        }

        CRect rMap2(r);
        rMap2.OffsetRect(m_ptMapView);

        CRect rMosaic;
        rMosaic.IntersectRect(CRect(m_ptMapView, mapSize), rMap2);

        BOOL bResult = m_vmMap.Render(CVIDINF_SURFACE_BACK,
            rControl.left - m_ptMapView.x,
            rControl.top - m_ptMapView.y,
            rMosaic,
            rClip,
            0,
            FALSE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 2266
        UTIL_ASSERT(bResult);

        if (pVidInf->BKLock(rClip)) {
            int v1 = rControl.left - rClip.left;
            int v2 = rControl.top - rClip.top;
            rClip.OffsetRect(-rClip.left, -rClip.top);

            m_vcAreas.pRes->Demand();
            m_vfLabel.pRes->Demand();

            if (field_FCA != RGB(250, 250, 250)) {
                field_FCA = RGB(250, 250, 250);
                m_vfLabel.SetColor(field_FCA, RGB(0, 0, 0), FALSE);
            }

            for (DWORD nArea = 0; nArea < pWorldMap->GetNumAreas(pWorldMap->sub_55A3A0()); nArea++) {
                CWorldMapArea* pArea = pWorldMap->GetArea(pWorldMap->sub_55A3A0(), nArea);
                if ((pArea->m_dwFlags & 0x1) != 0) {
                    CRect rArea = m_aAreaRect[nArea];

                    CRect rAreaDirty;
                    rAreaDirty.IntersectRect(rMosaic, rArea);

                    if (!rAreaDirty.IsRectEmpty()) {
                        COLORREF rgbColor;

                        if (pArea->m_sequence == 23) {
                            rgbColor = RGB(170, 170, 170);
                        } else if ((pArea->m_dwFlags & 0x8) != 0) {
                            rgbColor = RGB(0, 0, 0);
                        } else if ((pArea->m_dwFlags & 0x4) != 0) {
                            rgbColor = RGB(255, 220, 90);
                        } else {
                            rgbColor = RGB(224, 180, 15);
                        }

                        if (!m_bMapDragging
                            && m_nEngineState == 1
                            && m_bInControl
                            && !m_bClickedArea) {
                            if (nArea == m_nSelectedArea && m_bOverSelectedArea) {
                                rgbColor = RGB(255, 255, 255);
                            } else if (nArea == field_FCE && m_nSelectedArea == -1) {
                                rgbColor = sub_69CB40(rgbColor);
                            }
                        }

                        m_vcAreas.SequenceSet(static_cast<SHORT>(pArea->m_sequence));
                        m_vcAreas.RealizePalette(0x1);

                        bResult = pVidInf->BKRender(&m_vcAreas,
                            v1 - m_ptMapView.x + pWorldMap->GetAreaPosition(pArea).cx,
                            v2 - m_ptMapView.y + pWorldMap->GetAreaPosition(pArea).cy,
                            rClip,
                            TRUE,
                            0);

                        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
                        // __LINE__: 2358
                        UTIL_ASSERT(bResult);

                        if (field_FCA != rgbColor) {
                            field_FCA = rgbColor;
                            m_vfLabel.SetColor(field_FCA, RGB(0, 0, 0), FALSE);
                        }

                        if (pArea->m_strLabel != -1) {
                            sLabel = FetchString(pArea->m_strLabel);

                            bResult = pVidInf->BKTextOut(&m_vfLabel,
                                sLabel,
                                v1 + rArea.left + (rArea.Width() - m_vfLabel.GetStringLength(sLabel, FALSE)) / 2 - m_ptMapView.x,
                                v2 + rArea.bottom - m_vfLabel.GetFontHeight(FALSE) / (g_pBaldurChitin->field_4A28 ? 2 : 1) - m_ptMapView.y,
                                rClip,
                                0,
                                TRUE);

                            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
                            // __LINE__: 2372
                            UTIL_ASSERT(bResult);
                        }
                    }
                }
            }

            m_vcAreas.pRes->Release();
            m_vfLabel.pRes->Release();

            CPoint ptMarker;
            GetMarkerPosition(ptMarker);

            m_vcMarker.pRes->Demand();
            m_vcMarker.RealizePalette(0x1);
            bResult = pVidInf->BKRender(&m_vcMarker,
                v1 + ptMarker.x - m_ptMapView.x,
                v2 + ptMarker.y - m_ptMapView.y,
                rClip,
                FALSE, // FIXME: Should be `TRUE`, res is demanded.
                0);
            m_vcMarker.pRes->Release();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 2390
            UTIL_ASSERT(bResult);

            pVidInf->BKUnlock();
        }

        bResult = TRUE;
    } else {
        bResult = FALSE;
    }

    renderLock.Unlock();

    return bResult;
}

// 0x69C2A0
void CScreenWorldMap::StartWorldMap(INT nEngineState, LONG nLeavingEdge, BOOLEAN bInControl)
{
    // TODO: Incomplete.
}

// 0x69C9E0
void CScreenWorldMap::StopWorldMap(BOOLEAN bAreaClicked)
{
    if (m_bInControl == TRUE && !bAreaClicked) {
        if (!g_pChitin->cNetwork.GetSessionOpen()
            || g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            g_pBaldurChitin->GetBaldurMessage()->SendMapWorldAnnounceStatus(FALSE, 0, 0);
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetBaldurMessage()->SendMapWorldCancelRequestToServer();
        }
    }

    if (m_nEngineState == 1) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
        // __LINE__: 2646
        UTIL_ASSERT(pGame != NULL);

        pGame->SelectAll(FALSE);
        pGame->GetGroup()->ClearActions();
    }

    CSingleLock lock(&field_1022, FALSE);
    lock.Lock(INFINITE);

    // NOTE: Uninline.
    m_aAreaRect.SetSize(0);

    lock.Unlock();

    m_cUIManager.GetPanel(2)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
}

// 0x69CB40
COLORREF CScreenWorldMap::sub_69CB40(COLORREF rgb)
{
    int v1 = (g_pBaldurChitin->nAUCounter / 2) & 7;
    short v2 = v1 < 4 ? 3 - v1 : v1 - 4;

    // TODO: Check, probably wrong.
    return RGB(GetRValue(rgb) + v2 * (191 - GetRValue(rgb)) / 3,
        GetGValue(rgb) - v2 * GetGValue(rgb) / 3,
        GetBValue(rgb) - v2 * GetBValue(rgb) / 3);
}

// 0x69CC10
CRect CScreenWorldMap::GetAreaRect(DWORD nMap, DWORD nArea)
{
    CString sLabel;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
    // __LINE__: 2768
    UTIL_ASSERT(pGame != NULL);

    CString sResArea;

    pGame->GetVisibleArea()->m_resRef.CopyToString(sResArea);

    CWorldMap* pWorldMap = pGame->GetWorldMap(sResArea);

    CWorldMapArea* pArea = pWorldMap->GetArea(nMap, nArea);

    CSize frameCenter;
    m_vcAreas.GetFrameCenterPoint(static_cast<SHORT>(pArea->m_sequence), 0, frameCenter, FALSE);

    CSize frameSize;
    m_vcAreas.GetFrameSize(static_cast<SHORT>(pArea->m_sequence), 0, frameSize, FALSE);

    CSize areaPos = pWorldMap->GetAreaPosition(pArea);

    CRect rArea;
    rArea.left = areaPos.cx;
    rArea.top = areaPos.cy;
    rArea.right = rArea.left + frameSize.cx;
    rArea.bottom = rArea.top + frameSize.cy;
    rArea.OffsetRect(-frameCenter.cx, -frameCenter.cy);

    if (pArea->m_strLabel != -1) {
        sLabel = FetchString(pArea->m_strLabel);
        LONG nLength = m_vfLabel.GetStringLength(sLabel, FALSE);
        LONG nHeight = m_vfLabel.GetFontHeight(FALSE) + 11;
        LONG nSideExpand = max(nLength - rArea.Width(), 0) / 2 + 1;
        rArea.InflateRect(nSideExpand,
            0,
            nSideExpand,
            nHeight);
    }

    return rArea;
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
        CRect rArea = m_aAreaRect[nArea];
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
    if (nArea != -1 && m_aAreaRect.GetCount() > 0) {
        CRect rArea = m_aAreaRect[nArea];
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
            CRect rArea = m_aAreaRect[nArea];
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
    m_nChatMessageCount = 0;
}

// NOTE: Inlined.
void CScreenWorldMap::FocusChatEditBox()
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
        if (m_lPopupStack.GetTailPosition() == NULL || m_lPopupStack.GetTail() == NULL) {
            CUIPanel* pPanel = m_cUIManager.GetPanel(3);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 4403
            UTIL_ASSERT(pPanel != NULL);

            CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(7));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorldMap.cpp
            // __LINE__: 4405
            UTIL_ASSERT(pEdit != NULL);

            m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
        }
    }
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

    CSingleLock renderLock(&(pWorldMap->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    pWorldMap->OnDoneButtonClick();

    renderLock.Unlock();
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

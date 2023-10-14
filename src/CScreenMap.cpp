#include "CScreenMap.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x63F960
CScreenMap::CScreenMap()
{
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    m_bShiftKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    m_bSelectWorldOnUp = FALSE;

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
    m_nLastPicked = -1;
    m_noteStrRef = -1;
}

// 0x49FC40
BOOL CScreenMap::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x640590
void CScreenMap::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x6405A0
BOOL CScreenMap::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x49FC40
BOOL CScreenMap::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x6405B0
void CScreenMap::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x6405C0
BOOL CScreenMap::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenMap::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x6405D0
void CScreenMap::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x6405E0
BOOL CScreenMap::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenMap::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenMap::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x686660
SHORT CScreenMap::GetNumVirtualKeys()
{
    return CSCREENMAP_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenMap::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x668C30
BYTE* CScreenMap::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x640610
CScreenMap::~CScreenMap()
{
}

// 0x6406B0
void CScreenMap::EngineActivated()
{
    if (m_cUIManager.m_bInitialized) {
        if (CChitin::byte_8FB950
            && g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }

        m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
        m_preLoadFontRealms.RegisterFont();

        m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
        m_preLoadFontTool.RegisterFont();

        m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
        m_preLoadFontStnSml.RegisterFont();

        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StartTime();
        }

        m_cUIManager.GetPanel(2)->m_bNeedMouseMove = TRUE;
        UpdateMainPanel();

        UpdateCursorShape(0);
        CheckEnablePortaits(1);
        CheckEnableLeftPanel();

        g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x640810
void CScreenMap::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    m_preLoadFontRealms.Unload();
    m_preLoadFontTool.Unload();
    m_preLoadFontStnSml.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
    }

    if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused
        && g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StopTime();
    }

    if (pPanel != NULL) {
        CUIControlButtonMapAreaMap* pButton = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));
        if (pButton != NULL) {
            pButton->SetMap(NULL);
        }
    }
}

// 0x640910
void CScreenMap::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIMAP"), g_pBaldurChitin->field_4A28);

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

    m_nSelectedCharacter = 0;
    m_pCurrentScrollBar = NULL;

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);

    m_bSelectWorldOnUp = FALSE;
    m_nLastPicked = -1;
    m_noteStrRef = -1;
}

// 0x5D72C0
void CScreenMap::EngineGameUninit()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x640A70
void CScreenMap::OnKeyDown(SHORT nKeysFlags)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_TAB:
                m_cUIManager.ForceToolTip();
                break;
            case VK_RETURN:
                if (GetTopPopup() != NULL) {
                    OnDoneButtonClick();
                }
                break;
            case VK_ESCAPE:
                if (GetTopPopup() != NULL) {
                    OnCancelButtonClick();
                } else {
                    SelectEngine(g_pBaldurChitin->m_pEngineWorld);
                }
                break;
            case VK_SNAPSHOT:
                g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
                if (GetTopPopup() == NULL) {
                    OnPortraitLClick(m_pVirtualKeysFlags[nKeyFlag] - '1');
                }
                break;
            default:
                if (GetTopPopup() == NULL) {
                    for (SHORT index = 0; index < CINFGAME_KEYMAP_SIZE; index) {
                        // NOTE: Uninline.
                        if (pGame->GetKeymap(index) == m_pVirtualKeysFlags[nKeyFlag]
                            && pGame->GetKeymapFlag(index) == m_bCtrlKeyDown) {
                            switch (index) {
                            case 0:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(5);
                                break;
                            case 1:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(8);
                                break;
                            case 2:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(0);
                                break;
                            case 3:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(6);
                                break;
                            case 4:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(7);
                                break;
                            case 5:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(4);
                                break;
                            case 6:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(9);
                                break;
                            case 7:
                                g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(13);
                                break;
                            case 29:
                                OnRestButtonClick();
                                break;
                            default:
                                break;
                            }
                            break;
                        }
                    }
                }
                break;
            }
        }
    }
}

// 0x49FC40
BOOL CScreenMap::CheckMouseLButton()
{
    return TRUE;
}

// 0x640D80
void CScreenMap::OnLButtonDblClk(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x636970
void CScreenMap::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x640E20
void CScreenMap::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);

    if (m_bSelectWorldOnUp) {
        m_bSelectWorldOnUp = FALSE;
        SelectEngine(g_pBaldurChitin->m_pEngineWorld);
    }
}

// 0x49FC40
BOOL CScreenMap::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenMap::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x640E80
void CScreenMap::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
    UpdateMainPanel();
    m_cUIManager.InvalidateRect(NULL);
}

// 0x640ED0
void CScreenMap::OnPortraitLClick(DWORD nPortrait)
{
    // TODO: Incomplete.
}

// 0x641130
void CScreenMap::OnPortraitLDblClick(DWORD nPortrait)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 938
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(static_cast<SHORT>(nPortrait));

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->GetArea() == pMapControl->m_pArea) {
            CPoint pt;
            pt.x = pSprite->GetPos().x - pMapControl->m_pArea->GetInfinity()->rViewPort.Width() / 2;
            pt.y = pSprite->GetPos().y - pMapControl->m_pArea->GetInfinity()->rViewPort.Height() / 2;
            pMapControl->CenterViewPort(pt);
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x641270
void CScreenMap::TimerAsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x63BAA0
void CScreenMap::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x6416A0
void CScreenMap::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1138
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1139
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1140
    UTIL_ASSERT(pRightPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }

    pMainPanel->SetEnabled(bEnable);
    pLeftPanel->SetEnabled(bEnable);
    pRightPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    CheckEnablePortaits(1);
    CheckEnableLeftPanel();
}

// 0x641800
void CScreenMap::UpdateMainPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1188
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButtonMapAreaMap* pAreaMap = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1192
    UTIL_ASSERT(pAreaMap != NULL);

    m_noteStrRef = -1;

    UpdateLabel(pPanel, 0x10000003, "%s", "");

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1203
        UTIL_ASSERT(FALSE);
    }

    CGameArea* pArea = pSprite->m_pArea;
    if (pArea == NULL) {
        pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
    }

    pGame->GetObjectArray()->ReleaseShare(nCharacterId,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    if (pArea != NULL) {
        pAreaMap->SetMap(pArea);
    }
}

// 0x641970
CUIPanel* CScreenMap::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenMap::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Inlined.
void CScreenMap::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1301
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Inlined.
void CScreenMap::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1328
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
    case 4:
    case 50:
        ResetErrorPanel(pPanel);
        break;
    case 5:
        ResetAreaNotePanel(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1344
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Inlined.
void CScreenMap::UpdatePopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1372
    UTIL_ASSERT(pPanel != NULL);
}

// 0x641990
void CScreenMap::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1450
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1456
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);

    // NOTE: Uninline.
    ResetPopupPanel(pPanel->m_nID);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    EnablePopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    UpdatePopupPanel(pPanel->m_nID);
}

// 0x641BA0
void CScreenMap::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1501
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    m_cUIManager.GetPanel(2)->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1518
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        UpdatePopupPanel(pPanel->m_nID);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel();
    }
}

// 0x641D00
void CScreenMap::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 3:
        m_nNumErrorButtons = 1;
        break;
    case 4:
        m_nNumErrorButtons = 2;
        break;
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1562
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(TRUE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1575
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1584
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1752
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENMAP_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x641F10
void CScreenMap::ResetAreaNotePanel(CUIPanel* pPanel)
{
    CUIControlButton* pButton;

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1610
    UTIL_ASSERT(pButton != NULL);

    pButton->SetText(FetchString(11973));

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1614
    UTIL_ASSERT(pButton != NULL);

    pButton->SetText(FetchString(13727));

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1618
    UTIL_ASSERT(pButton != NULL);

    pButton->SetText(FetchString(13957));

    CGameArea* pArea = static_cast<CUIControlButtonMapAreaMap*>(GetManager()->GetPanel(2)->GetControl(2))->m_pArea;
    CUIControlButtonMapNote* pNoteControl = static_cast<CUIControlButtonMapNote*>(GetManager()->GetPanel(2)->GetControl(pArea->m_cGameAreaNotes.field_74));

    SHORT nSequence;
    if (pNoteControl != NULL) {
        nSequence = pNoteControl->m_cVidCell.m_nCurrentSequence;
    } else {
        nSequence = 0;
    }

    for (DWORD nButtonID = 4; nButtonID < 12; nButtonID++) {
        CUIControlButtonMapNoteFlagChoice* pButton = static_cast<CUIControlButtonMapNoteFlagChoice*>(pPanel->GetControl(nButtonID));
        pButton->SetSelected(nButtonID - 4 == nSequence);
    }

    static_cast<CUIControlButtonMapAreaMap*>(GetManager()->GetPanel(2)->GetControl(2))->m_pArea->m_cGameAreaNotes.field_8D = min(static_cast<BYTE>(nSequence), 7);
}

// 0x642130
void CScreenMap::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1674
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    STRREF strError;
    if (pGame->CanRestParty(strError, 0, 0, 0)) {
        m_nErrorState = 1;
        m_dwErrorTextId = 15358;
        m_strErrorButtonText[0] = 17199;
        m_strErrorButtonText[1] = 11596;
        m_strErrorButtonText[2] = 13727;
        SummonPopup(50);
    } else {
        m_nErrorState = 0;
        m_dwErrorTextId = strError;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(3);
    }

    renderLock.Unlock();
}

// 0x642240
void CScreenMap::UpdateNoteText(STRREF strRef)
{
    if (m_noteStrRef != strRef) {
        m_noteStrRef = strRef;

        CString sString = FetchString(strRef);
        UpdateLabel(GetManager()->GetPanel(2), 0x10000003, "%s", sString);
    }
}

// 0x6422D0
void CScreenMap::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1805
    UTIL_ASSERT(0 <= nButton && nButton < GetNumErrorButtons());

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 1807
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nErrorState) {
    case 0:
        switch (nButton) {
        case 0:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
            // __LINE__: 1849
            UTIL_ASSERT(FALSE);
        }
        break;
    case 1:
        switch (nButton) {
        case 0:
            DismissPopup();

            CInfGame::m_bHealPartyOnRest = FALSE;
            pGame->RestParty(1, 0);
            break;
        case 1:
            DismissPopup();

            CInfGame::m_bHealPartyOnRest = TRUE;
            pGame->RestParty(1, 0);
            CInfGame::m_bHealPartyOnRest = FALSE;
            break;
        case 2:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
            // __LINE__: 1836
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 1855
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x642460
void CScreenMap::OnCancelButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();
}

// 0x6424D0
void CScreenMap::OnDoneButtonClick()
{
    if (GetTopPopup() != NULL) {
        switch (GetTopPopup()->m_nID) {
        case 3:
        case 4:
        case 50:
            OnErrorButtonClick(0);
            break;
        case 5:
            if (1) {
                CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(GetManager()->GetPanel(2)->GetControl(2));

                CGameArea* pArea = pMapControl->m_pArea;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 1936
                UTIL_ASSERT(pArea != NULL);

                CUIPanel* pPanel = GetTopPopup();

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 1938
                UTIL_ASSERT(pPanel != NULL);

                CUIControlEditMultiLineMapNote* pEdit = static_cast<CUIControlEditMultiLineMapNote*>(pPanel->GetControl(1));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 1940
                UTIL_ASSERT(pEdit != NULL);

                CGameAreaNotes* pNotes = pArea->GetAreaNotes();
                pNotes->SetStringBuffer(pEdit->GetText());
                pNotes->Add();

                DismissPopup();
            }
            break;
        }
    }
}

// 0x6426C0
void CScreenMap::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
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

// 0x6428D0
CUIControlButtonMapAreaMap::CUIControlButtonMapAreaMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON | RBUTTON, 0)
{
    // TODO: Incomplete.
}

// 0x642B80
CUIControlButtonMapAreaMap::~CUIControlButtonMapAreaMap()
{
    // TODO: Incomplete.
}

// 0x6436B0
CPoint CUIControlButtonMapAreaMap::ConvertScreenToWorldCoords(CPoint pt)
{
    // TODO: Incomplete.

    return CPoint(0, 0);
}

// 0x6437A0
void CUIControlButtonMapAreaMap::CenterViewPort(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x644CC0
void CUIControlButtonMapAreaMap::SetMap(CGameArea* pArea)
{
    // TODO: Incomplete.
}

// 0x645350
void CUIControlButtonMapAreaMap::SetActiveNotes(BOOL bActive)
{
    // TODO: Incomplete.
}

// 0x645610
void CUIControlButtonMapAreaMap::sub_645610(DWORD id)
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

// -----------------------------------------------------------------------------

// 0x645C40
CUIControlButtonMapNoteDelete::CUIControlButtonMapNoteDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x645C90
CUIControlButtonMapNoteDelete::~CUIControlButtonMapNoteDelete()
{
}

// 0x645D30
void CUIControlButtonMapNoteDelete::OnLButtonClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // NOTE: Original code is slightly different - it obtains same control
    // twice.
    CUIPanel* pPanel = pMap->GetManager()->GetPanel(2);
    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));
    pMapControl->m_pArea->m_cGameAreaNotes.DeleteANote(pMapControl->m_pArea->m_cGameAreaNotes.field_74);

    pMap->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x645DB0
CUIControlEditMultiLineMapNote::CUIControlEditMultiLineMapNote(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEditMultiLine(panel, controlInfo, 0)
{
    m_nTextCapitalization = 0;
}

// 0x645E00
CUIControlEditMultiLineMapNote::~CUIControlEditMultiLineMapNote()
{
}

// 0x645EC0
void CUIControlEditMultiLineMapNote::OnEditReturn(CString sText)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4382
    UTIL_ASSERT(pMap != NULL);

    pMap->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x645F30
CUIControlButtonMapShowNotes::CUIControlButtonMapShowNotes(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nToolTipStrRef = 21436;
    SetSelected(TRUE);
    m_nSelectedFrame = 0;
}

// 0x645FD0
CUIControlButtonMapShowNotes::~CUIControlButtonMapShowNotes()
{
}

// 0x646070
void CUIControlButtonMapShowNotes::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    pGame->m_bShowAreaNotes = !pGame->m_bShowAreaNotes;

    // NOTE: Original code is slightly different - it obtains same control
    // twice.
    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(m_pPanel->GetControl(2));
    pMapControl->SetActiveNotes(pGame->m_bShowAreaNotes);
    pMapControl->InvalidateRect();

    CUIControlButton3State::SetSelected(pGame->m_bShowAreaNotes);
}

// -----------------------------------------------------------------------------

// 0x6460D0
CUIControlButtonMapNote::CUIControlButtonMapNote(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, RBUTTON, 0)
{
    SetNeedMouseMove();
    field_666 = 0;
    field_668 = 0;
    m_nDisabledFrame = 0;
    m_nNormalFrame = 0;
    m_nPressedFrame = 1;
    m_cVidCell.FrameSet(0);
}

// 0x646190
CUIControlButtonMapNote::~CUIControlButtonMapNote()
{
}

// 0x646230
void CUIControlButtonMapNote::OnRButtonClick(CPoint pt)
{
    if (field_666) {
        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(m_pPanel->GetControl(2));
        CGameArea* pArea = pMapControl->m_pArea;

        CSingleLock renderLock(&(m_pPanel->m_pManager->field_36), FALSE);
        renderLock.Lock(INFINITE);

        pArea->m_cGameAreaNotes.field_70 = 0;

        CPoint ptWorld = pMapControl->ConvertScreenToWorldCoords(pt);
        pArea->m_cGameAreaNotes.m_cAreaNote.m_startX = static_cast<WORD>(ptWorld.x);
        pArea->m_cGameAreaNotes.m_cAreaNote.m_startY = static_cast<WORD>(ptWorld.y);
        pArea->m_cGameAreaNotes.m_cAreaNote.m_id = m_nID;

        CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

        CUIControlEditMultiLineMapNote* pEdit = static_cast<CUIControlEditMultiLineMapNote*>(pMap->GetManager()->GetPanel(5)->GetControl(1));

        STRREF strNote = pArea->m_cGameAreaNotes.GetNoteButtonText(m_nID);

        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(strNote, strRes);
        pEdit->SetText(strRes.szText);

        pArea->m_cGameAreaNotes.field_74 = m_nID;
        pMap->SummonPopup(5);

        pMap->GetManager()->SetCapture(pEdit, CUIManager::KEYBOARD);

        renderLock.Unlock();
    }
}

// 0x646410
void CUIControlButtonMapNote::SetInactiveRender(BOOL bInactiveRender)
{
    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(m_pPanel->GetControl(2));
    if (m_areaResRef == pMapControl->m_pArea->m_resRef) {
        if (g_pBaldurChitin->GetObjectGame()->m_bShowAreaNotes) {
            CUIControlBase::SetInactiveRender(bInactiveRender);
        }
    }
}

// 0x646470
BOOL CUIControlButtonMapNote::Render(BOOL bForce)
{
    if (field_666) {
        return CUIControlButton::Render(bForce);
    } else {
        return FALSE;
    }
}

// 0x646490
void CUIControlButtonMapNote::OnMouseMove(CPoint pt)
{
    if (field_666) {
        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(m_pPanel->GetControl(2));
        g_pBaldurChitin->m_pEngineMap->UpdateNoteText(pMapControl->m_pArea->m_cGameAreaNotes.GetNoteButtonText(m_nID));
    }
}

// -----------------------------------------------------------------------------

// 0x6464E0
CUIControlButtonMapNoteFlagChoice::CUIControlButtonMapNoteFlagChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    // NOTE: Uninline.
    m_cVidCell.SetResRef(CResRef("FLAG1"), m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

    BYTE nSequence = static_cast<BYTE>(m_nID - 4);
    BYTE nNumberSequences = static_cast<BYTE>(m_cVidCell.GetNumberSequences(FALSE));
    if (nNumberSequences > nSequence) {
        m_cVidCell.SequenceSet(nSequence);
        m_nNormalFrame = 0;
        m_nPressedFrame = 1;
        m_nDisabledFrame = 0;
        m_nSelectedFrame = 2;
        m_nNotSelectedFrame = 0;
        field_66E = TRUE;
    } else {
        field_66E = FALSE;
    }
}

// 0x646790
CUIControlButtonMapNoteFlagChoice::~CUIControlButtonMapNoteFlagChoice()
{
}

// 0x646830
BOOL CUIControlButtonMapNoteFlagChoice::Render(BOOL bForce)
{
    if (field_66E) {
        return CUIControlButton3State::Render(bForce);
    } else {
        return FALSE;
    }
}

// 0x646850
BOOL CUIControlButtonMapNoteFlagChoice::OnLButtonDown(CPoint pt)
{
    if (field_66E) {
        return CUIControlButton::OnLButtonDown(pt);
    } else {
        return FALSE;
    }
}

// 0x646880
void CUIControlButtonMapNoteFlagChoice::OnLButtonClick(CPoint pt)
{
    if (field_66E) {
        SHORT nSequence = m_cVidCell.m_nCurrentSequence;

        CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;
        CUIPanel* pPanel = pMap->GetManager()->GetPanel(2);
        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));
        pMapControl->m_pArea->m_cGameAreaNotes.field_8D = min(static_cast<BYTE>(nSequence), 7);
    }

    for (DWORD nButtonID = 4; nButtonID < 12; nButtonID++) {
        CUIControlButtonMapNoteFlagChoice* pButton = static_cast<CUIControlButtonMapNoteFlagChoice*>(m_pPanel->GetControl(nButtonID));
        pButton->SetSelected(nButtonID == m_nID);
    }

    g_pBaldurChitin->m_pEngineMap->GetManager()->SetCapture(m_pPanel->GetControl(1), CUIManager::KEYBOARD);
}

#include "CScreenMap.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CResWED.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

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

    for (int side = 0; side < 4; side++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->m_aBorderPanels[side]));
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
    m_cUIManager.OnLButtonDblClk(pt);

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 686
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));
    if (pMapControl->m_bActive
        && pMapControl->field_71E
        && pMapControl->IsOver(pt - pPanel->m_ptOrigin)) {
        m_bSelectWorldOnUp = TRUE;
    }
}

// 0x636970
void CScreenMap::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
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
    CGameSprite* pOldSprite;
    CGameSprite* pSelectedSprite;
    LONG iOldSprite;
    LONG iSelectedSprite;
    BYTE rc;

    // NOTE: Unsigned compare.
    if (nPortrait < static_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetNumCharacters())) {
        DWORD nOldSelectedCharacter = m_nSelectedCharacter;
        m_nSelectedCharacter = nPortrait;

        CUIPanel* pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
        // __LINE__: 862
        UTIL_ASSERT(pPanel != NULL);

        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));

        // NOTE: Uninline.
        iOldSprite = g_pBaldurChitin->GetObjectGame()->GetCharacterId(static_cast<SHORT>(nOldSelectedCharacter));

        if (iOldSprite != CGameObjectArray::INVALID_INDEX) {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(iOldSprite,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pOldSprite),
                INFINITE);
            if (rc != CGameObjectArray::SUCCESS) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 873
                UTIL_ASSERT(FALSE);
            }
        }

        // NOTE: Uninline.
        iSelectedSprite = g_pBaldurChitin->GetObjectGame()->GetCharacterId(static_cast<SHORT>(m_nSelectedCharacter));

        if (iSelectedSprite != CGameObjectArray::INVALID_INDEX) {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(iSelectedSprite,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSelectedSprite),
                INFINITE);
            if (rc != CGameObjectArray::SUCCESS) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 881
                UTIL_ASSERT(FALSE);
            }
        }

        if (pMapControl->m_bActive || pMapControl->m_bInactiveRender) {
            pMapControl->field_75A = CUIManager::RENDER_COUNT;
        }

        if (iOldSprite == CGameObjectArray::INVALID_INDEX
            || pOldSprite->GetArea() != pSelectedSprite->GetArea()) {
            UpdateMainPanel();
            pPanel->InvalidateRect(NULL);
        }

        if (iOldSprite != CGameObjectArray::INVALID_INDEX) {
            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(iOldSprite,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(iSelectedSprite,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        if (iOldSprite != CGameObjectArray::INVALID_INDEX) {
            m_cUIManager.GetPanel(1)->GetControl(nOldSelectedCharacter)->InvalidateRect();
        }

        m_cUIManager.GetPanel(1)->GetControl(m_nSelectedCharacter)->InvalidateRect();
    }
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
    CGameSprite* pSprite;
    BYTE rc;
    SHORT nPortrait;
    INT nPicked = -1;
    BOOL v1 = TRUE;

    if (GetTopPopup() == NULL) {
        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(m_cUIManager.GetPanel(2)->GetControl(2));
        CUIPanel* pLeftPanel = m_cUIManager.GetPanel(1);

        if (pLeftPanel->IsOver(g_pChitin->m_ptPointer)) {
            for (nPortrait = 0; nPortrait < g_pBaldurChitin->GetObjectGame()->GetNumCharacters(); nPortrait++) {
                if (pLeftPanel->GetControl(nPortrait)->IsOver(g_pChitin->m_ptPointer - pLeftPanel->m_ptOrigin)) {
                    do {
                        // FIXME: Character id should be outside of the loop.
                        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                            CGameObjectArray::THREAD_ASYNCH,
                            reinterpret_cast<CGameObject**>(&pSprite),
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        if (pSprite->GetArea() == pMapControl->m_pArea) {
                            SetPickedCharacter(nPortrait);
                            nPicked = nPortrait;

                            pLeftPanel->GetControl(nPortrait)->InvalidateRect();

                            if (pMapControl->m_bActive || pMapControl->m_bInactiveRender) {
                                pMapControl->field_75A = CUIManager::RENDER_COUNT;
                            }

                            v1 = FALSE;
                        }

                        // FIXME: Character id should be outside of the loop.
                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }

                    break;
                }
            }
        } else if (m_cUIManager.GetPanel(2)->IsOver(g_pChitin->m_ptPointer)) {
            for (nPortrait = 0; nPortrait < g_pBaldurChitin->GetObjectGame()->GetNumCharacters(); nPortrait++) {
                do {
                    // FIXME: Character id should be outside of the loop.
                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                        CGameObjectArray::THREAD_ASYNCH,
                        reinterpret_cast<CGameObject**>(&pSprite),
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc != CGameObjectArray::SUCCESS) {
                    break;
                }

                if (pSprite->GetArea() == pMapControl->m_pArea
                    && pMapControl->sub_642C90(pSprite, g_pChitin->m_ptPointer)) {
                    SetPickedCharacter(nPortrait);
                    nPicked = nPortrait;

                    pLeftPanel->GetControl(nPortrait)->InvalidateRect();

                    pMapControl->SetRenderCharacter(nPortrait, 0);

                    // FIXME: Character id should be outside of the loop.
                    g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }
        }

        if (m_nLastPicked != nPicked) {
            if (m_nLastPicked != -1) {
                pLeftPanel->GetControl(m_nLastPicked)->InvalidateRect();

                if (v1) {
                    pMapControl->SetRenderCharacter(m_nLastPicked, 0);
                }
            }

            if (nPicked == -1) {
                SetPickedCharacter(-1);
            }

            m_nLastPicked = nPicked;
        }

        pMapControl->InvalidateNotes();
    }

    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
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
    field_75B = 0;
    m_nCharInArea = 0;

    m_vmMap.SetResRef(CResRef(""), TRUE, TRUE);
    m_vmMap.m_bDoubleSize = FALSE;

    m_pArea = NULL;
    field_71E = 0;
    field_76C = 0;
    field_71F = 0;
    field_720 = 0;
    field_75A = 0;

    SetNeedAsyncUpdate();

    field_764.x = 0;
    field_75C.x = 0;
    field_764.y = 0;
    field_75C.y = 0;
    m_nUserNoteId = 10;

    // FIXME: Why not `SetNeedMouseMove` (which also sets flag on panel)?
    m_bNeedMouseMove = TRUE;

    field_7DA = 0;

    for (int index = 0; index < 6; index++) {
        m_charPositions[index].ptPos.x = -1;
        m_charPositions[index].ptPos.y = -1;
        m_charPositions[index].id = CGameObjectArray::INVALID_INDEX;
    }

    m_nToolTipStrRef = 16482;
}

// 0x642B30
BOOL CUIControlButtonMapAreaMap::NeedRender()
{
    return (m_bActive || m_bInactiveRender) && (m_nRenderCount > 0 || field_75A > 0);
}

// 0x642B80
CUIControlButtonMapAreaMap::~CUIControlButtonMapAreaMap()
{
}

// 0x642C90
BOOLEAN CUIControlButtonMapAreaMap::sub_642C90(CGameSprite* pSprite, const CPoint& pt)
{
    if (!field_71E) {
        return FALSE;
    }

    CSize mapSize;
    m_vmMap.GetSize(mapSize, FALSE);

    if (pSprite->GetArea() != m_pArea) {
        return FALSE;
    }

    CPoint ptWorld;
    ptWorld.x = 32 * (pt.x - m_ptOrigin.x - max(m_size.cx - mapSize.cx, 0) / 2 - m_pPanel->m_ptOrigin.x) / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    ptWorld.y = 32 * (pt.y - m_ptOrigin.y - max(m_size.cy - mapSize.cy, 0) / 2 - m_pPanel->m_ptOrigin.y) / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

    if (!pSprite->IsOver(ptWorld)) {
        return FALSE;
    }

    return TRUE;
}

// 0x642DA0
BOOL CUIControlButtonMapAreaMap::OnLButtonDown(CPoint pt)
{
    if (!field_71E
        || !m_bActive
        || (m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSELBUTTON);

    CSize mapSize;
    m_vmMap.GetSize(mapSize, FALSE);

    CRect r;
    r.left = m_pArea->GetInfinity()->nNewX;
    r.top = m_pArea->GetInfinity()->nNewY;
    r.right = r.left + m_pArea->GetInfinity()->rViewPort.Width();
    r.bottom = r.top + m_pArea->GetInfinity()->rViewPort.Height();

    // NOTE: Uninline.
    CPoint ptWorld = ConvertScreenToWorldCoords(pt);

    if (r.PtInRect(ptWorld)) {
        field_722 = ptWorld.x - r.left;
        field_726 = ptWorld.y - r.top;
        field_71F = TRUE;
    } else {
        field_71F = FALSE;
    }

    CUIManager* pManager = m_pPanel->m_pManager;
    pManager->field_2D = 0;
    pManager->field_32 = m_nID;
    pManager->field_1C = 0;
    static_cast<CBaldurEngine*>(pManager->m_pWarp)->PlayGUISound(CBaldurEngine::RESREF_SOUND_CLICKLEFT);

    return TRUE;
}

// 0x642F70
void CUIControlButtonMapAreaMap::OnLButtonUp(CPoint pt)
{
    if (field_71E && m_bActive && (m_nMouseButtons & LBUTTON) != 0) {
        if (IsOver(pt)) {
            OnLButtonClick(pt);
        }

        field_71F = FALSE;
        field_720 = FALSE;
    }
}

// 0x642FE0
void CUIControlButtonMapAreaMap::OnLButtonClick(CPoint pt)
{
    if (field_71E && m_pArea != NULL) {
        // NOTE: Uninline.
        CPoint ptWorld = ConvertScreenToWorldCoords(pt);

        if (field_71F && field_720) {
            ptWorld.x -= field_722;
            ptWorld.y -= field_726;
        } else {
            ptWorld.x -= m_pArea->GetInfinity()->rViewPort.Width() / 2;
            ptWorld.y -= m_pArea->GetInfinity()->rViewPort.Height() / 2;
        }

        CenterViewPort(ptWorld);

        if (m_pArea->GetAreaNotes() != NULL
            && m_pArea->GetAreaNotes()->m_areaNoteList.GetCount() != 0) {
            m_pArea->GetAreaNotes()->Invalidate();
        }
    }
}

// 0x643180
void CUIControlButtonMapAreaMap::OnMouseMove(CPoint pt)
{
    if (field_71E) {
        g_pBaldurChitin->m_pEngineMap->UpdateNoteText(-1);

        if (field_71F && m_pArea != NULL) {
            // NOTE: Uninline.
            CPoint ptWorld = ConvertScreenToWorldCoords(pt);

            ptWorld.x -= field_722;
            ptWorld.y -= field_726;

            CenterViewPort(ptWorld);

            field_720 = TRUE;
        }
    }
}

// 0x6432F0
void CUIControlButtonMapAreaMap::OnRButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// NOTE: Math looks similar to `GetStartPosition`.
//
// 0x6436B0
CPoint CUIControlButtonMapAreaMap::ConvertScreenToWorldCoords(CPoint pt)
{
    CSize mapSize;
    m_vmMap.GetSize(mapSize, FALSE);

    int v1 = max(m_size.cx - mapSize.cx, 0) / 2;

    int x;
    if (pt.x - m_ptOrigin.x - v1 >= mapSize.cx) {
        x = mapSize.cx;
    } else if (m_size.cx - mapSize.cx >= 0) {
        x = pt.x - m_ptOrigin.x - v1;
    } else {
        x = pt.x - m_ptOrigin.x;
    }

    int v2 = max(m_size.cy - mapSize.cy, 0) / 2;

    int y;
    if (pt.y - m_ptOrigin.y - v2 >= mapSize.cy) {
        y = mapSize.cy;
    } else if (m_size.cy - mapSize.cy >= 0) {
        y = pt.y - m_ptOrigin.y - v2;
    } else {
        y = pt.y - m_ptOrigin.y;
    }

    return CPoint(32 * x / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1),
        32 * y / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1));
}

// 0x6437A0
void CUIControlButtonMapAreaMap::CenterViewPort(const CPoint& pt)
{
    CSingleLock renderLock(&m_critSect, FALSE);
    if (field_71E) {
        if (m_nRenderCount == 0) {
            field_764 = pt;
            field_75C = pt;

            renderLock.Lock(INFINITE);

            INT x = max(min(m_pArea->GetInfinity()->nAreaX - field_72A.Width() - 1, pt.x), 0);
            INT y = max(min(m_pArea->GetInfinity()->nAreaY - field_72A.Height() - 1, pt.y), 0);
            m_pArea->GetInfinity()->SetViewPosition(x, y, TRUE);

            CRect rOld(field_72A);
            field_72A.SetRect(x, y, x + field_72A.Width(), y + field_72A.Height());

            CRect r;
            r.UnionRect(rOld, field_72A);

            CPoint ptLeft = m_pPanel->m_ptOrigin + m_ptOrigin;

            CSize mapSize;
            m_vmMap.GetSize(mapSize, FALSE);

            ptLeft.x += max(m_size.cx - mapSize.cx, 0) / 2;
            ptLeft.y += max(m_size.cy - mapSize.cy, 0) / 2;

            r.left = 4 * r.left / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
            r.top = 4 * r.top / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
            r.right = 4 * r.right / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1) + 1;
            r.bottom = 4 * r.bottom / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1) + 1;
            r.OffsetRect(ptLeft);

            m_pPanel->InvalidateRect(&r);
            renderLock.Unlock();
        } else {
            field_764 = pt;
        }
    }
}

// 0x643B00
void CUIControlButtonMapAreaMap::SetRenderCharacter(SHORT nPortrait, WORD nVisualRange)
{
    if (m_vmMap.pRes != NULL) {
        LONG nCharacterId = m_charPositions[nPortrait].id;
        if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
            CGameSprite* pSprite;

            BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_1,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);

            if (rc == CGameObjectArray::SUCCESS) {
                CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

                CSize mapSize;
                m_vmMap.GetSize(mapSize, FALSE);

                pt.x += max(m_size.cx - mapSize.cx, 0) / 2;
                pt.y += max(m_size.cy - mapSize.cy, 0) / 2;

                CRect r;
                r.left = (4 * (m_charPositions[nPortrait].ptPos.x - nVisualRange) / 32 - 3) * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                r.top = (4 * (m_charPositions[nPortrait].ptPos.y - nVisualRange) / 32 - 2) * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                r.right = (4 * (m_charPositions[nPortrait].ptPos.x + nVisualRange) / 32 + 4) * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                r.bottom = (4 * (m_charPositions[nPortrait].ptPos.y + nVisualRange) / 32 + 3) * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

                r.OffsetRect(pt);

                m_pPanel->InvalidateRect(&r);

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }
    }
}

// 0x643CC0
BOOL CUIControlButtonMapAreaMap::Render(BOOL bForce)
{
    CVidInf* pVidInf = static_cast<CVidInf*>(g_pBaldurChitin->GetCurrentVideoMode());

    CSingleLock renderLock(&m_critSect, FALSE);
    renderLock.Lock(INFINITE);

    if ((!m_bActive && !m_bInactiveRender)
        || !field_71E
        || m_vmMap.cResRef == "") {
        renderLock.Unlock();
        return FALSE;
    }

    if (field_7BC) {
        SetActiveNotes(TRUE);
        field_7BC = FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    CSize mapSize;
    m_vmMap.GetSize(mapSize, FALSE);

    pt.x += max(m_size.cx - mapSize.cx, 0) / 2;
    pt.y += max(m_size.cy - mapSize.cy, 0) / 2;

    CRect rMap;
    rMap.left = pt.x;
    rMap.top = pt.y;
    rMap.right = rMap.left + min(m_size.cx, mapSize.cx);
    rMap.bottom = rMap.top + min(m_size.cy, mapSize.cy);

    m_rDirty &= rMap;

    if (m_rDirty.IsRectNull()) {
        renderLock.Unlock();
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        renderLock.Unlock();
        return RenderCharactersOnly(pt);
    }

    if (field_75A != 0) {
        field_75A--;
    }

    if (m_nRenderCount > 0) {
        CSingleLock renderCountLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderCountLock.Lock(INFINITE);
        m_nRenderCount--;
        renderCountLock.Unlock();
    }

    BOOL bResult = m_vmMap.Render(CVIDINF_SURFACE_BACK,
        pt.x,
        pt.y,
        m_rDirty - pt,
        m_rDirty,
        0x20000,
        FALSE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 3021
    UTIL_ASSERT(bResult);

    RenderFogOfWar(pVidInf, pt, m_rDirty - pt);

    if (pVidInf->BKLock(m_rDirty)) {
        RenderCharacters(m_rDirty - pt);
        RenderViewRect(pVidInf, m_rDirty - pt, field_72A);

        pVidInf->BKUnlock();

        if (m_bActive) {
            InvalidateNotes();
        }

        renderLock.Unlock();

        CUIPanel* pPanel = g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(5);
        if (pPanel != NULL && pPanel->m_bActive == TRUE) {
            pPanel->InvalidateRect(NULL);
        }
    }

    renderLock.Unlock();

    return TRUE;
}

// 0x644190
BOOL CUIControlButtonMapAreaMap::RenderCharactersOnly(const CPoint& pt)
{
    CVidInf* pVidInf = static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode());

    if (field_75A == 0) {
        return FALSE;
    }

    field_75A -= 1;

    if (!field_71E) {
        return FALSE;
    }

    if (!pVidInf->BKLock(m_rDirty)) {
        return FALSE;
    }

    RenderCharacters(m_rDirty - pt);
    RenderViewRect(pVidInf, m_rDirty - pt, field_72A);

    pVidInf->BKUnlock();

    if (m_bActive) {
        InvalidateNotes();
    }

    return TRUE;
}

// 0x6442F0
void CUIControlButtonMapAreaMap::RenderCharacters(const CRect& rClip)
{

    for (int index = 0; index < 6; index++) {
        if (m_charPositions[index].id != CGameObjectArray::INVALID_INDEX) {
            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(m_charPositions[index].id,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pSprite->RenderToMapScreen(rClip, m_charPositions[index].ptPos);

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(m_charPositions[index].id,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }
}

// 0x643CC0
void CUIControlButtonMapAreaMap::RenderFogOfWar(CVidInf* pVidInf, const CPoint& pt, const CRect& rClip)
{
    // TODO: Incomplete.
}

// 0x644A50
void CUIControlButtonMapAreaMap::InvalidateRect()
{
    if (m_bActive || m_bInactiveRender) {
        CUIControlButton::InvalidateRect();
        InvalidateNotes();
    }
}

// 0x644A80
void CUIControlButtonMapAreaMap::InvalidateNotes()
{
    if (m_pArea != NULL
        && m_pArea->GetAreaNotes() != NULL
        && !m_pArea->GetAreaNotes()->m_areaNoteList.IsEmpty()
        && !field_7BE.IsEmpty()) {
        CUIPanel* pPanel = g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2);

        POSITION pos = field_7BE.GetHeadPosition();
        while (pos != NULL) {
            DWORD dwId = field_7BE.GetNext(pos);
            CUIControlButtonMapNote* pControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(dwId));
            if (pControl != NULL) {
                if (pControl->field_666) {
                    pControl->InvalidateRect();
                }
            }
        }
    }
}

// 0x644B00
void CUIControlButtonMapAreaMap::RenderViewRect(CVidInf* pVidInf, const CRect& a2, const CRect& a3)
{
    COLORREF rgb = pVidInf->ApplyBrightnessContrast(RGB(0, 255, 0));

    CRect rSurface = a2;

    CRect r;
    r.left = 4 * a3.left / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    r.top = 4 * a3.top / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    r.right = 4 * a3.right / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    r.bottom = 4 * a3.bottom / 32 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    r.OffsetRect(-rSurface.left, -rSurface.top);
    rSurface.OffsetRect(-rSurface.left, -rSurface.top);

    if (r.top != rSurface.bottom) {
        pVidInf->BKRenderLine(r.left, r.top, r.right, r.top, rSurface, rgb);
    }

    if (r.right != rSurface.right) {
        pVidInf->BKRenderLine(r.right, r.top, r.right, r.bottom, rSurface, rgb);
    }

    if (r.bottom != rSurface.bottom) {
        pVidInf->BKRenderLine(r.right, r.bottom, r.left, r.bottom, rSurface, rgb);
    }

    if (r.left != rSurface.right) {
        pVidInf->BKRenderLine(r.left, r.bottom, r.left, r.top, rSurface, rgb);
    }
}

// 0x644CC0
void CUIControlButtonMapAreaMap::SetMap(CGameArea* pArea)
{
    CResRef cResMap;

    // NOTE: Unused.
    CResRef v1;

    CSingleLock renderLock(&m_critSect, FALSE);
    renderLock.Lock(INFINITE);

    if (pArea != NULL) {
        cResMap = pArea->m_pResWED->GetResRef();
        m_pArea = pArea;

        if ((pArea->m_header.m_areaType & 0x40) != 0) {
            CString sResRef;
            CString sSuffix(CInfinity::NIGHT_RESREF_SUFFIX);

            cResMap.CopyToString(sResRef);

            sResRef.MakeUpper();
            sSuffix.MakeUpper();

            if (sResRef[sResRef.GetLength() - 1] == sSuffix[0]) {
                cResMap = sResRef.Left(sResRef.GetLength() - 1);
            }
        }

        if (g_pBaldurChitin->cDimm.m_cKeyTable.FindKey(cResMap, 1004, TRUE)) {
            if (m_vmMap.cResRef != cResMap) {
                m_vmMap.SetResRef(cResMap, FALSE, TRUE);
                m_vmMap.m_bDoubleSize = g_pBaldurChitin->field_4A28;
                field_71E = TRUE;
            }
        } else {
            if (m_vmMap.cResRef != "") {
                m_vmMap.SetResRef(CResRef(""), TRUE, TRUE);
                m_vmMap.m_bDoubleSize = FALSE;
                field_71E = FALSE;
            }
        }

        m_nCharInArea = 0;

        for (SHORT nPortrait = 0; nPortrait < 6; nPortrait++) {
            // NOTE: Uninlie.
            LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait);

            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pSprite->GetArea() == pArea) {
                    m_charPositions[nPortrait].ptPos = pSprite->GetPos();
                    m_charPositions[nPortrait].id = nCharacterId;
                    m_nCharInArea++;
                } else {
                    m_charPositions[nPortrait].ptPos.x = -1;
                    m_charPositions[nPortrait].ptPos.y = -1;
                    m_charPositions[nPortrait].id = CGameObjectArray::INVALID_INDEX;
                }

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }

        if (m_vmMap.pRes != NULL) {
            field_72A.left = m_pArea->GetInfinity()->nNewX;
            field_72A.top = m_pArea->GetInfinity()->nNewY;
            field_72A.right = field_72A.left + m_pArea->GetInfinity()->rViewPort.Width();
            field_72A.bottom = field_72A.top + m_pArea->GetInfinity()->rViewPort.Height();

            if (field_72A.left > m_pArea->GetInfinity()->nAreaY - field_72A.right + field_72A.left - 1) {
                field_72A.OffsetRect(-1, 0);
            }

            if (field_72A.top > field_72A.top - field_72A.bottom + m_pArea->GetInfinity()->nAreaY - 1) {
                field_72A.OffsetRect(0, -1);
            }

            m_pArea->m_cGameAreaNotes.IntrnlInitialize();
            m_pArea->m_cGameAreaNotes.m_rArea = pArea->m_resRef;
            field_7BC = TRUE;
            SetActiveNotes(TRUE);
            InvalidateRect();
        } else {
            SetActiveNotes(FALSE);
            InvalidateRect();
        }
    } else {
        m_vmMap.SetResRef(CResRef(""), TRUE, TRUE);
        m_vmMap.m_bDoubleSize = FALSE;
        field_71E = FALSE;
    }

    renderLock.Unlock();
}

// 0x645100
void CUIControlButtonMapAreaMap::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CUIControlBase::TimerAsynchronousUpdate(bInside);

    if (field_720 && field_75C != field_764) {
        CenterViewPort(field_764);
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        LONG nPortrait = g_pChitin->nAUCounter % 6;
        if (nPortrait < 6 && ((1 << nPortrait) & field_7DA) != 0) {
            SetRenderCharacter(static_cast<SHORT>(nPortrait), 0);

            LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterId(static_cast<SHORT>(nPortrait));

            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc != CGameObjectArray::SUCCESS) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
                // __LINE__: 3844
                UTIL_ASSERT(FALSE);
            }

            SHORT nVisualRange;
            if (pSprite->GetArea() == m_pArea) {
                m_charPositions[nPortrait].ptPos = pSprite->GetPos();
                nVisualRange = pSprite->GetVisualRange();
            } else {
                nVisualRange = 0;
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);

            SetRenderCharacter(static_cast<SHORT>(nPortrait), nVisualRange);

            field_7DA &= ~(1 << nPortrait);
        }
    }
}

// 0x6452E0
void CUIControlButtonMapAreaMap::GetStartPosition(CPoint& pt)
{
    CSize frameSize;
    m_vmMap.GetSize(frameSize, FALSE);

    pt.x = max(m_size.cx - frameSize.cx, 0) / 2 + m_ptOrigin.x;
    pt.y = max(m_size.cy - frameSize.cy, 0) / 2 + m_ptOrigin.y;
}

// 0x645350
void CUIControlButtonMapAreaMap::SetActiveNotes(BOOL bActive)
{
    CResRef areaResRef;
    POSITION pos;
    CUIControlButtonMapNote* pNote;
    DWORD nId;

    CVisibilityMap* pVisMap = &(m_pArea->m_visibility);
    CUIPanel* pPanel = g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2);

    areaResRef = m_pArea->m_resRef;

    if (bActive
        && g_pBaldurChitin->GetObjectGame()->m_bShowAreaNotes
        && m_vmMap.pRes != NULL) {
        CUIControlButtonMapAreaMap* pMap = static_cast<CUIControlButtonMapAreaMap*>(m_pPanel->GetControl(2));

        CPoint ptStart;

        // NOTE: Uninline.
        pMap->GetStartPosition(ptStart);

        pos = field_7BE.GetHeadPosition();
        while (pos != NULL) {
            nId = field_7BE.GetNext(pos);
            pNote = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(nId));
            if (pNote != NULL) {
                if (areaResRef == pNote->m_areaResRef) {
                    if (!pNote->field_668) {
                        pNote->m_ptOrigin += ptStart;
                        pNote->field_668 = TRUE;
                    }

                    CPoint ptScreen;
                    ptScreen.x = pNote->m_ptOrigin.x + pNote->m_size.cx / 2;
                    ptScreen.y = pNote->m_ptOrigin.y + pNote->m_size.cy / 2;

                    CPoint ptWorld;
                    if (pNote->field_668) {
                        ptWorld = ConvertScreenToWorldCoords(ptScreen);
                    } else {
                        ptWorld.x = 32 * ptScreen.x / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                        ptWorld.y = 32 * ptScreen.y / 4 / (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
                    }

                    if (pVisMap->IsTileExplored(pVisMap->PointToTile(ptWorld))) {
                        pNote->field_666 = TRUE;
                        pNote->SetActive(TRUE);
                        pNote->SetInactiveRender(TRUE);
                        pNote->m_bInactiveRender = TRUE;
                    } else {
                        pNote->SetActive(FALSE);
                        pNote->SetInactiveRender(FALSE);
                        pNote->m_bInactiveRender = FALSE;
                        pNote->field_666 = FALSE;
                    }
                } else {
                    pNote->SetActive(FALSE);
                    pNote->SetInactiveRender(FALSE);
                    pNote->m_bInactiveRender = FALSE;
                    pNote->field_666 = FALSE;
                }
            }
        }

        InvalidateNotes();
    } else {
        pos = field_7BE.GetHeadPosition();
        while (pos != NULL) {
            nId = field_7BE.GetNext(pos);
            pNote = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(nId));
            if (pNote != NULL) {
                pNote->SetActive(FALSE);
                pNote->SetInactiveRender(FALSE);
                pNote->m_bInactiveRender = FALSE;
                pNote->field_666 = 0;
            }
        }
    }
}

// 0x645610
void CUIControlButtonMapAreaMap::AddNote(DWORD id)
{
    CUIPanel* pPanel = g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4067
    UTIL_ASSERT_MSG(pPanel != NULL, "Invalid map panel");

    CUIControlButtonMapNote* pControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(id));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4071
    UTIL_ASSERT_MSG(pControl != NULL, "Invalid map note control.");

    POSITION pos = field_7BE.GetHeadPosition();
    while (pos != NULL) {
        DWORD nOtherId = field_7BE.GetAt(pos);
        CUIControlButtonMapNote* pOtherControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(nOtherId));
        if (pOtherControl != NULL
            && pOtherControl->m_nID == pControl->m_nID) {
            break;
        }

        field_7BE.GetNext(pos);
    }

    if (pos == NULL) {
        field_7BE.AddTail(id);
    }
}

// 0x645760
void CUIControlButtonMapAreaMap::RemoveNote(DWORD id)
{
    CUIPanel* pPanel = g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4102
    UTIL_ASSERT_MSG(pPanel != NULL, "Invalid map panel");

    CUIControlButtonMapNote* pControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(id));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMap.cpp
    // __LINE__: 4107
    UTIL_ASSERT_MSG(pControl != NULL, "Invalid map note control.");

    POSITION pos = field_7BE.GetHeadPosition();
    while (pos != NULL) {
        DWORD nOtherId = field_7BE.GetAt(pos);
        CUIControlButtonMapNote* pOtherControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(nOtherId));
        if (pOtherControl != NULL
            && pOtherControl->m_nID == pControl->m_nID) {
            break;
        }

        field_7BE.GetNext(pos);
    }

    if (pos != NULL) {
        field_7BE.RemoveAt(pos);
    }
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

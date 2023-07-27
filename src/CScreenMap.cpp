#include "CScreenMap.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
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
    // TODO: Incomplete.
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
                        // __FILE__: .\Include\InfGame.h
                        // __LINE__: 1486
                        UTIL_ASSERT(index >= 0 && index < CINFGAME_KEYMAP_SIZE);

                        if (pGame->m_pKeymap[index] == m_pVirtualKeysFlags[nKeyFlag]
                            && pGame->m_pKeymapFlags[index] == m_bCtrlKeyDown) {
                            switch (index) {
                            case 0:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(5);
                                break;
                            case 1:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(8);
                                break;
                            case 2:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(0);
                                break;
                            case 3:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(6);
                                break;
                            case 4:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(7);
                                break;
                            case 5:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(4);
                                break;
                            case 6:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(9);
                                break;
                            case 7:
                                static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(13);
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
}

// 0x641970
CUIPanel* CScreenMap::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x641990
void CScreenMap::SummonPopup(DWORD dwPopupId)
{
    // TODO: Incomplete.
}

// 0x641BA0
void CScreenMap::DismissPopup()
{
    // TODO: Incomplete.
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
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
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

// 0x644CC0
void CUIControlButtonMapAreaMap::SetMap(CGameArea* pArea)
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

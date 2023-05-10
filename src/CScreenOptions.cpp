#include "CScreenOptions.h"

#include "CBaldurChitin.h"
#include "CGameAnimationType.h"
#include "CGameOptions.h"
#include "CInfGame.h"
#include "CScreenConnection.h"
#include "CScreenKeymaps.h"
#include "CScreenLoad.h"
#include "CScreenMovies.h"
#include "CScreenSave.h"
#include "CScreenWorld.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x6530E0
CScreenOptions::CScreenOptions()
{
    m_dwErrorTextId = 0;
    m_dwErrorState = 0;
    m_nNumErrorButtons = 0;
    m_bSpriteMirror = FALSE;
    m_nBpp = 0;
    m_bFullscreen = 0;
    m_bSoftMirrorBlt = 0;
    m_bSoftSrcKeyBlt = 0;
    m_bSoftBlt = 0;
    m_bTranslucentBlts = 0;
    m_bStaticAnimations = 0;
    m_bFromMainMenu = FALSE;

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
    m_pVirtualKeys[39] = CKeyInfo('#', -1, 0);
    m_pVirtualKeys[40] = CKeyInfo('$', -1, 0);
    m_pVirtualKeys[41] = CKeyInfo('%', 0, 0);
    m_pVirtualKeys[42] = CKeyInfo('&', 0, 0);
    m_pVirtualKeys[43] = CKeyInfo('\\', 0, 0);
    m_pVirtualKeys[44] = CKeyInfo('(', 0, 0);
    m_pVirtualKeys[45] = CKeyInfo(',', -1, 0);
    m_pVirtualKeys[46] = CKeyInfo('-', -1, 0);
    m_pVirtualKeys[47] = CKeyInfo('.', 0, 0);
    m_pVirtualKeys[48] = CKeyInfo('`', -1, 0);
    m_pVirtualKeys[49] = CKeyInfo('a', -1, 0);
    m_pVirtualKeys[50] = CKeyInfo('b', -1, 0);
    m_pVirtualKeys[51] = CKeyInfo('c', -1, 0);
    m_pVirtualKeys[52] = CKeyInfo('d', -1, 0);
    m_pVirtualKeys[53] = CKeyInfo('e', -1, 0);
    m_pVirtualKeys[54] = CKeyInfo('f', -1, 0);
    m_pVirtualKeys[55] = CKeyInfo('g', -1, 0);
    m_pVirtualKeys[56] = CKeyInfo('h', -1, 0);
    m_pVirtualKeys[57] = CKeyInfo('i', -1, 0);
    m_pVirtualKeys[58] = CKeyInfo('j', -1, 0);
    m_pVirtualKeys[59] = CKeyInfo('k', -1, 0);
    m_pVirtualKeys[60] = CKeyInfo('l', -1, 0);
    m_pVirtualKeys[61] = CKeyInfo('m', -1, 0);
    m_pVirtualKeys[62] = CKeyInfo('n', -1, 0);
    m_pVirtualKeys[63] = CKeyInfo('o', -1, 0);
    m_pVirtualKeys[64] = CKeyInfo('p', -1, 0);
    m_pVirtualKeys[65] = CKeyInfo('q', -1, 0);
    m_pVirtualKeys[66] = CKeyInfo('r', -1, 0);
    m_pVirtualKeys[67] = CKeyInfo('s', -1, 0);
    m_pVirtualKeys[68] = CKeyInfo('t', -1, 0);
    m_pVirtualKeys[69] = CKeyInfo('u', -1, 0);
    m_pVirtualKeys[70] = CKeyInfo('v', -1, 0);
    m_pVirtualKeys[71] = CKeyInfo('w', -1, 0);
    m_pVirtualKeys[72] = CKeyInfo('x', -1, 0);
    m_pVirtualKeys[73] = CKeyInfo('y', -1, 0);
    m_pVirtualKeys[74] = CKeyInfo('z', -1, 0);
    m_pVirtualKeys[75] = CKeyInfo('{', -1, 0);
    m_pVirtualKeys[76] = CKeyInfo(VK_NUMLOCK, -1, 0);
    m_pVirtualKeys[77] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[78] = CKeyInfo(0xC0, 0, 0);
    m_pVirtualKeys[79] = CKeyInfo(0xBD, 0, 0);
    m_pVirtualKeys[80] = CKeyInfo(0xBB, 0, 0);
    m_pVirtualKeys[81] = CKeyInfo(0xDB, 0, 0);
    m_pVirtualKeys[82] = CKeyInfo(0xDD, 0, 0);
    m_pVirtualKeys[83] = CKeyInfo(0xDC, 0, 0);
    m_pVirtualKeys[84] = CKeyInfo(0xBA, 0, 0);
    m_pVirtualKeys[85] = CKeyInfo(0xDE, 0, 0);
    m_pVirtualKeys[86] = CKeyInfo(0xBC, 0, 0);
    m_pVirtualKeys[87] = CKeyInfo(0xBE, 0, 0);
    m_pVirtualKeys[88] = CKeyInfo(0xBF, 0, 0);
    m_pVirtualKeys[89] = CKeyInfo(VK_TAB, -1, 0);

    m_bCtrlKeyDown = FALSE;
    m_bExitProgram = FALSE;
}

// 0x49FC40
BOOL CScreenOptions::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseMove()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseLButton()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenOptions::CheckMouseRButton()
{
    return TRUE;
}

// 0x653D40
void CScreenOptions::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x653D80
CScreenOptions::~CScreenOptions()
{
}

// 0x654140
void CScreenOptions::EngineDeactivated()
{
    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.m_bConnectionEstablished == TRUE
            && g_pChitin->cNetwork.m_bIsHost == TRUE
            && g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL) {
            if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            }
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    g_pBaldurChitin->m_pObjectGame->SaveOptions();
    g_pBaldurChitin->SaveOptions();
}

// 0x6541D0
void CScreenOptions::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUIOPT"), g_pBaldurChitin->field_4A28);

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
    field_FA = NULL;
    m_bExitProgram = FALSE;
    m_bFromMainMenu = FALSE;

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(12)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(9)->SetActive(FALSE);
    m_cUIManager.GetPanel(10)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);
    m_cUIManager.GetPanel(13)->SetActive(FALSE);

    m_cUIManager.ReorderPanelAfter(13, 2);
}

// 0x6546B0
void CScreenOptions::OnPortraitLClick(DWORD nPortrait)
{
    if (nPortrait < g_pBaldurChitin->m_pObjectGame->m_nCharacters) {
        DWORD nOldSelectedCharacter = m_nSelectedCharacter;
        m_nSelectedCharacter = nPortrait;
        UpdateCursorShape(0);
        UpdateMainPanel();

        m_cUIManager.GetPanel(1)->GetControl(nOldSelectedCharacter)->InvalidateRect();
        m_cUIManager.GetPanel(1)->GetControl(m_nSelectedCharacter)->InvalidateRect();
    }
}

// 0x654730
void CScreenOptions::TimerSynchronousUpdate()
{
    if (m_bExitProgram) {
        g_pBaldurChitin->ShutDown(-1, NULL, NULL);
        return;
    }

    g_pBaldurChitin->m_pObjectGame->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x654780
void CScreenOptions::OnDoneButtonClick()
{
    CUIPanel* pPanel = m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 930
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
    case 4:
    case 50:
        OnErrorButtonClick(0);
        return;
    case 5:
        return;
    }

    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    switch (pPanel->m_nID) {
    case 6:
        CheckGraphicModeOptions(pPanel);

        // NOTE: Uninline.
        PopOptions(NULL);

        DismissPopup();
        g_pBaldurChitin->SaveOptions();
        lock.Unlock();

        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
        // NOTE: Uninline.
        PopOptions(NULL);

        DismissPopup();
        g_pBaldurChitin->SaveOptions();
        lock.Unlock();

        break;
    case 13:
        DismissPopup();

        m_bFromMainMenu = FALSE;
        lock.Unlock();

        g_pBaldurChitin->m_pObjectGame->ApplyVolumeSliders(TRUE);
        g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineConnection);

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 978
        UTIL_ASSERT(pPanel != NULL);
    }
}

// 0x654960
void CScreenOptions::OnCancelButtonClick()
{
    CGameOptions* pOptions = &(g_pBaldurChitin->m_pObjectGame->m_cOptions);

    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    CUIPanel* pPanel = m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1015
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
    case 4:
    case 5:
    case 50:
        DismissPopup();
        lock.Unlock();

        break;
    case 6:
        CGameAnimationType::MIRROR_BAM = m_bSpriteMirror;

        // NOTE: Uninline.
        PopOptions(pOptions);

        DismissPopup();
        lock.Unlock();

        break;
    case 7:
    case 8:
    case 9:
    case 10:
    case 12:
        // NOTE: Uninline.
        PopOptions(pOptions);

        DismissPopup();
        lock.Unlock();

        break;
    case 13:
        DismissPopup();
        lock.Unlock();

        if (m_bFromMainMenu) {
            g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineConnection);
        }

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1050
        UTIL_ASSERT(FALSE);
    }
}

// 0x654B40
void CScreenOptions::SummonPopup(DWORD dwPopupId)
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1133
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_lPopupStack.GetTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1139
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);
    ResetPopupPanel(pPanel->m_nID);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    UpdatePopupPanel(pPanel->m_nID, TRUE);
}

// 0x654CB0
void CScreenOptions::DismissPopup()
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1184
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1201
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        UpdatePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel();
    }
}

// 0x654E30
void CScreenOptions::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1233
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1234
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1235
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

// 0x654F90
void CScreenOptions::UpdateMainPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    if (g_pChitin->cNetwork.m_bConnectionEstablished == TRUE) {
        CUIControlButton* pButton;

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(5));
        pButton->SetEnabled(g_pChitin->cNetwork.m_bIsHost);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(6));
        pButton->SetEnabled(g_pChitin->cNetwork.m_bIsHost);
    }

    CString sFormattedVersion;
    CString sVersion = CChitin::versionString;
    CString sBuildNumber = CChitin::buildVersionString;

    int major;
    int minor;
    int patch;
    sscanf(sVersion, "%d, %d, %d", &major, &minor, &patch);

    sFormattedVersion.Format("v%d.%d%d (%s)", major, minor, patch, sBuildNumber);

    UpdateLabel(pPanel, 0x1000000B, "%s", sFormattedVersion);
}

// NOTE: Uninlined.
void CScreenOptions::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1325
    UTIL_ASSERT(FALSE);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Uninlined.
void CScreenOptions::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1370
    UTIL_ASSERT(FALSE);

    pPanel->SetEnabled(bEnable);
}

// 0x6550E0
void CScreenOptions::ResetPopupPanel(DWORD nID)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);
    switch (nID) {
    case 3:
    case 4:
    case 5:
    case 50:
        ResetErrorPanel(pPanel);
        break;
    case 6:
        UpdateHelp(pPanel->m_nID, 33, 18038);
        break;
    case 7:
        UpdateHelp(pPanel->m_nID, 14, 18040);
        break;
    case 8:
        UpdateHelp(pPanel->m_nID, 40, 18042);
        break;
    case 9:
        UpdateHelp(pPanel->m_nID, 28, 18043);
        break;
    case 10:
        UpdateHelp(pPanel->m_nID, 15, 18044);
        break;
    case 12:
        UpdateHelp(pPanel->m_nID, 16, 18041);
        break;
    case 13:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1443
        UTIL_ASSERT(FALSE);
    }
}

// 0x6551F0
void CScreenOptions::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 3:
        m_nNumErrorButtons = 1;
        break;
    case 4:
        m_nNumErrorButtons = 2;
        break;
    case 5:
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1494
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(TRUE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1507
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 1516
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2684
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENOPTIONS_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x655440
void CScreenOptions::UpdatePopupPanel(DWORD dwPanelId, BOOLEAN bInitialUpdate)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    switch (dwPanelId) {
    case 2:
    case 3:
    case 4:
    case 5:
    case 50:
        break;
    case 6:
        UpdateGraphicsPanel(bInitialUpdate);
        break;
    case 7:
        UpdateSoundPanel(bInitialUpdate);
        break;
    case 8:
        UpdateGamePlayPanel(bInitialUpdate);
        break;
    case 9:
        UpdateFeedbackPanel(bInitialUpdate);
        break;
    case 10:
        UpdateAutoPausePanel(bInitialUpdate);
        break;
    case 12:
        UpdateSelectSoundsPanel(bInitialUpdate);
        break;
    case 13:
        m_cUIManager.InvalidateRect(NULL);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 1583
        UTIL_ASSERT(FALSE);
    }
}

// 0x655570
void CScreenOptions::QuitGame()
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1611
    UTIL_ASSERT(pGame != NULL);

    m_bFromMainMenu = FALSE;
    SelectEngine(g_pBaldurChitin->m_pEngineConnection);

    if (g_pChitin->cNetwork.m_bConnectionEstablished == TRUE) {
        if (g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
        }

        g_pChitin->cNetwork.CloseSession(TRUE);
        g_pBaldurChitin->m_cBaldurMessage.field_7 = FALSE;
    }

    pGame->DestroyGame(1, 0);
}

// 0x655610
void CScreenOptions::SaveGraphicModeOptions()
{
    m_nBpp = g_pBaldurChitin->cVideo.m_nBpp;
    m_bFullscreen = g_pBaldurChitin->m_bFullscreen;
    m_bSoftMirrorBlt = g_pBaldurChitin->cVideo.cVidBlitter.m_bSoftMirrorBlt;
    m_bSoftSrcKeyBlt = g_pBaldurChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
        || g_pBaldurChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast;
    m_bSoftBlt = g_pBaldurChitin->cVideo.cVidBlitter.m_bSoftBlt
        || g_pBaldurChitin->cVideo.cVidBlitter.m_bSoftBltFast;
    m_bTranslucentBlts = g_pBaldurChitin->m_pObjectGame->m_cOptions.m_bTranslucentBlts;
    m_bStaticAnimations = g_pBaldurChitin->m_pObjectGame->m_cOptions.m_bStaticAnimations;
}

// 0x6556C0
void CScreenOptions::CheckGraphicModeOptions(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x655910
void CScreenOptions::LoadGame()
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1823
    UTIL_ASSERT(pGame != NULL);

    INT nLoadState;
    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        nLoadState = 3;

        if (g_pChitin->cNetwork.m_bConnectionEstablished == TRUE && !g_pBaldurChitin->m_pObjectGame->m_multiplayerSettings.m_bArbitrationLockStatus) {
            for (DWORD nIndex = 0; nIndex < 6; nIndex++) {
                // NOTE: Looks like inlining.
                LONG localObjectID;
                if (nIndex < 6) {
                    localObjectID = pGame->m_characters[nIndex];
                } else {
                    localObjectID = -1;
                }

                if (localObjectID != -1) {
                    g_pBaldurChitin->m_cBaldurMessage.ObjectControlRequest(localObjectID);
                }
            }
        }

        g_pBaldurChitin->m_cBaldurMessage.ObjectControl();
        pGame->m_multiplayerSettings.SetArbitrationLockAllowInput(FALSE);
        pGame->m_multiplayerSettings.SetArbitrationLockStatus(TRUE);
    } else {
        nLoadState = 2;
    }

    pGame->DestroyGame(1, 0);

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1856
    UTIL_ASSERT(pLoad != NULL);

    pLoad->StartLoad(nLoadState);
    SelectEngine(pLoad);
}

// 0x655A70
void CScreenOptions::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 1887
    UTIL_ASSERT(pGame != NULL);

    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    STRREF dwErrorTextId;
    if (pGame->CanRestParty(dwErrorTextId, 0, 0, 0)) {
        m_dwErrorState = 7;
        m_dwErrorTextId = 15358;
        m_strErrorButtonText[0] = 17199;
        m_strErrorButtonText[1] = 11596;
        m_strErrorButtonText[2] = 13727;
        SummonPopup(50);
    } else {
        m_dwErrorState = 6;
        m_dwErrorTextId = dwErrorTextId;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(3);
    }

    lock.Unlock();
}

// 0x655B80
void CScreenOptions::UpdateGraphicsPanel(BOOLEAN bInitialUpdate)
{
    // TODO: Incomplete.
}

// 0x656090
void CScreenOptions::UpdateSoundPanel(BOOLEAN bInitialUpdate)
{
    // TODO: Incomplete.
}

// 0x656360
void CScreenOptions::UpdateSelectSoundsPanel(BOOLEAN bInitialUpdate)
{
    CGameOptions* pOptions = &(g_pBaldurChitin->m_pObjectGame->m_cOptions);
    CUIPanel* pPanel = m_cUIManager.GetPanel(12);
    CUIControlButton3State* pButton;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2126
    UTIL_ASSERT(pPanel != NULL);

    field_FA = pPanel->GetControl(17);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(6));
    UTIL_ASSERT(pButton != NULL); // 2131
    pButton->SetSelected(pOptions->m_bAttackSounds);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(7));
    UTIL_ASSERT(pButton != NULL); // 2135
    pButton->SetSelected(pOptions->m_bFootStepsSounds);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(5));
    UTIL_ASSERT(pButton != NULL); // 2139
    pButton->SetSelected(pOptions->m_bSubtitles);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(8));
    UTIL_ASSERT(pButton != NULL); // 2143
    pButton->SetSelected(pOptions->m_nCommandSoundsFrequency == 3);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(9));
    UTIL_ASSERT(pButton != NULL); // 2147
    pButton->SetSelected(pOptions->m_nCommandSoundsFrequency == 2);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(10));
    UTIL_ASSERT(pButton != NULL); // 2151
    pButton->SetSelected(pOptions->m_nCommandSoundsFrequency == 1);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(58));
    UTIL_ASSERT(pButton != NULL); // 2155
    pButton->SetSelected(pOptions->m_nSelectionSoundsFrequency == 3);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(59));
    UTIL_ASSERT(pButton != NULL); // 2159
    pButton->SetSelected(pOptions->m_nSelectionSoundsFrequency == 2);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(60));
    UTIL_ASSERT(pButton != NULL); // 2163
    pButton->SetSelected(pOptions->m_nSelectionSoundsFrequency == 1);
}

// 0x6565B0
void CScreenOptions::UpdateGamePlayPanel(BOOLEAN bInitialUpdate)
{
    // TODO: Incomplete.
}

// 0x656B00
void CScreenOptions::UpdateFeedbackPanel(BOOLEAN bInitialUpdate)
{
    // TODO: Incomplete.
}

// 0x656D50
void CScreenOptions::UpdateAutoPausePanel(BOOLEAN bInitialUpdate)
{
    CGameOptions* pOptions = &(g_pBaldurChitin->m_pObjectGame->m_cOptions);
    CUIPanel* pPanel = m_cUIManager.GetPanel(10);
    CUIControlButton3State* pButton;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2383
    UTIL_ASSERT(pPanel != NULL);

    field_FA = pPanel->GetControl(16);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(1));
    UTIL_ASSERT(pButton != NULL); // 2388
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x4);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(2));
    UTIL_ASSERT(pButton != NULL); // 2392
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x8);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(3));
    UTIL_ASSERT(pButton != NULL); // 2396
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x10);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(4));
    UTIL_ASSERT(pButton != NULL); // 2400
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x2);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(5));
    UTIL_ASSERT(pButton != NULL); // 2404
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x1);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(13));
    UTIL_ASSERT(pButton != NULL); // 2408
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x20);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(25));
    UTIL_ASSERT(pButton != NULL); // 2412
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x40);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(26));
    UTIL_ASSERT(pButton != NULL); // 2416
    pButton->SetSelected(pOptions->m_bAutoPauseOnTrap);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(30));
    UTIL_ASSERT(pButton != NULL); // 2420
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x200);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(36));
    UTIL_ASSERT(pButton != NULL); // 2424
    pButton->SetSelected(pOptions->m_nAutoPauseState & 0x400);

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(33));
    UTIL_ASSERT(pButton != NULL); // 2428
    pButton->SetSelected(pOptions->m_bAutoPauseCenter);
}

// 0x656FF0
void CScreenOptions::OnErrorButtonClick(INT nButton)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CScreenOptions::PushOptions(CGameOptions* pOptions)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2710
    UTIL_ASSERT(pOptions != NULL);

    CGameOptions* pCopy = new CGameOptions();
    memcpy(pCopy, pOptions, sizeof(CGameOptions));
    m_lOptionsStack.AddTail(pCopy);
}

// NOTE: Inlined.
void CScreenOptions::PopOptions(CGameOptions* pOptions)
{
    CGameOptions* pRemoved = m_lOptionsStack.RemoveTail();
    if (pRemoved != NULL) {
        if (pOptions != NULL) {
            memcpy(pOptions, pRemoved, sizeof(CGameOptions));
        }

        delete pRemoved;
    }
}

// 0x657360
void CScreenOptions::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2777
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2779
    UTIL_ASSERT(pText != NULL);

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x657470
void CScreenOptions::CancelEngine()
{
    while (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        OnCancelButtonClick();
    }
}

// 0x657490
CUIControlButtonOptionsSelection::CUIControlButtonOptionsSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, 1, 0)
{
    m_nPressedFrame = 2;
    m_nDisabledFrame = 0;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 3;
}

// 0x657500
CUIControlButtonOptionsSelection::~CUIControlButtonOptionsSelection()
{
}

// 0x6575A0
void CUIControlButtonOptionsSelection::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2899
    UTIL_ASSERT(pGame != NULL);

    CGameOptions* pOptions = &(pGame->m_cOptions);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 2901
    UTIL_ASSERT(pOptions != NULL);

    CUIControlButton3State::OnLButtonClick(pt);

    DWORD dwTextId;
    DWORD dwStrId;
    switch (m_pPanel->m_nID) {
    case 6:
        dwTextId = 33;

        switch (m_nID) {
        case 9:
            dwStrId = 18000;
            break;
        case 40:
            dwStrId = 15135;
            break;
        case 41:
            dwStrId = 18006;
            break;
        case 42:
            dwStrId = 18007;
            break;
        case 51:
            dwStrId = 20620;
            pOptions->m_bTranslucentShadows = m_bSelected;
            CVidCell::TRANSLUCENT_SHADOWS_ON = m_bSelected;
            break;
        case 56:
            dwStrId = 15141;
            break;
        case 57:
            dwStrId = 18004;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 2947
            UTIL_ASSERT(FALSE);
        }

        break;
    case 8:
        dwTextId = 40;

        switch (m_nID) {
        case 14:
            dwStrId = 18021;
            pOptions->m_bAlwaysDither = m_bSelected;
            break;
        case 19:
            if (pOptions->field_4) {
                dwStrId = 18023;
                pOptions->m_bGore = m_bSelected;
            } else {
                m_bSelected = FALSE;
            }
            break;
        case 42:
            dwStrId = 11797;
            pOptions->m_bDarkvision = m_bSelected;
            break;
        case 47:
            dwStrId = 20619;
            pOptions->m_bWeatherEnabled = m_bSelected;
            break;
        case 50:
            dwStrId = 15136;
            pOptions->m_bMaxHP = m_bSelected;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 2987
            UTIL_ASSERT(FALSE);
        }

        break;
    case 12:
        dwTextId = 16;

        switch (m_nID) {
        case 5:
            dwStrId = 18015;
            pOptions->m_bSubtitles = m_bSelected;
            break;
        case 6:
            dwStrId = 18013;
            pOptions->m_bAttackSounds = m_bSelected;
            break;
        case 7:
            dwStrId = 18014;
            pOptions->m_bFootStepsSounds = m_bSelected;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3012
            UTIL_ASSERT(FALSE);
        }

        break;
    case 7:
        dwTextId = 14;

        switch (m_nID) {
        case 26:
            dwStrId = 18022;
            pOptions->m_bEnvironmentalAudio = m_bSelected;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3027
            UTIL_ASSERT(FALSE);
        }

        break;
    case 9:
        dwTextId = 28;

        switch (m_nID) {
        case 10:
            dwStrId = 18026;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x1;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x1;
            }
            break;
        case 11:
            dwStrId = 18027;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x2;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x2;
            }
            break;
        case 12:
            dwStrId = 18028;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x4;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x4;
            }
            break;
        case 13:
            dwStrId = 18029;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x8;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x8;
            }
            break;
        case 14:
            dwStrId = 18030;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x20;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x20;
            }
            break;
        case 15:
            dwStrId = 18031;
            if (m_bSelected) {
                pOptions->m_nEffectTextLevel |= 0x10;
            } else {
                pOptions->m_nEffectTextLevel &= ~0x10;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3109
            UTIL_ASSERT(FALSE);
        }

        break;
    case 10:
        dwTextId = 15;

        switch (m_nID) {
        case 1:
            dwStrId = 18032;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x4;
            } else {
                pOptions->m_nAutoPauseState &= ~0x4;
            }
            break;
        case 2:
            dwStrId = 18033;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x8;
            } else {
                pOptions->m_nAutoPauseState &= ~0x8;
            }
            break;
        case 3:
            dwStrId = 18034;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x10;
            } else {
                pOptions->m_nAutoPauseState &= ~0x10;
            }
            break;
        case 4:
            dwStrId = 18035;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x2;
            } else {
                pOptions->m_nAutoPauseState &= ~0x2;
            }
            break;
        case 5:
            dwStrId = 18036;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x1;
            } else {
                pOptions->m_nAutoPauseState &= ~0x1;
            }
            break;
        case 13:
            dwStrId = 18037;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x20;
            } else {
                pOptions->m_nAutoPauseState &= ~0x20;
            }
            break;
        case 25:
            dwStrId = 10640;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x40;
            } else {
                pOptions->m_nAutoPauseState &= ~0x40;
            }
            break;
        case 26:
            dwStrId = 23514;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x200;
            } else {
                pOptions->m_nAutoPauseState &= ~0x200;
            }
            break;
        case 33:
            dwStrId = 24888;
            pOptions->m_bAutoPauseCenter = m_bSelected;
            break;
        case 36:
            dwStrId = 26311;
            if (m_bSelected) {
                pOptions->m_nAutoPauseState |= 0x400;
            } else {
                pOptions->m_nAutoPauseState &= ~0x400;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3244
            UTIL_ASSERT(FALSE);
        }

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 3250
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_pEngineOptions->UpdateHelp(m_pPanel->m_nID, dwTextId, dwStrId);
    g_pBaldurChitin->m_pEngineOptions->UpdatePopupPanel(m_pPanel->m_nID, FALSE);
}

// 0x657C60
CUIControlButtonOptionsRadio::CUIControlButtonOptionsRadio(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, 1, 0)
{
    m_nNotSelectedFrame = 0;
    m_nPressedFrame = 1;
    m_nSelectedFrame = 3;
    m_nDisabledFrame = 2;
    m_nDisabledSelectedFrame = 4;
}

// 0x657CE0
CUIControlButtonOptionsRadio::~CUIControlButtonOptionsRadio()
{
}

// 0x6512D0
BOOL CUIControlButtonOptionsRadio::Render(BOOL bForce)
{
    if (!m_bPressed) {
        if (m_bEnabled) {
            if (m_bSelected) {
                m_cVidCell.FrameSet(m_nSelectedFrame);
            } else {
                m_cVidCell.FrameSet(m_nNotSelectedFrame);
            }
        } else {
            if (m_bSelected) {
                m_cVidCell.FrameSet(m_nDisabledSelectedFrame);
            } else {
                m_cVidCell.FrameSet(m_nDisabledFrame);
            }
        }
    }
    return CUIControlButton::Render(bForce);
}

// 0x657D80
void CUIControlButtonOptionsRadio::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 3318
    UTIL_ASSERT(pGame != NULL);

    CGameOptions* pOptions = &(pGame->m_cOptions);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 3320
    UTIL_ASSERT(pOptions != NULL);

    DWORD dwTextId;
    DWORD dwStrId;

    switch (m_pPanel->m_nID) {
    case 6:
        dwTextId = 33;

        switch (m_nID) {
        case 5:
            dwStrId = 17205;
            SetSelected(1);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(6))->SetSelected(0);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(7))->SetSelected(0);
            break;
        case 6:
            dwStrId = 17205;
            SetSelected(1);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(5))->SetSelected(0);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(7))->SetSelected(0);
            break;
        case 7:
            dwStrId = 17205;
            SetSelected(1);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(5))->SetSelected(0);
            static_cast<CUIControlButton3State*>(m_pPanel->GetControl(6))->SetSelected(0);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3355
            UTIL_ASSERT(FALSE);
        }

        break;
    case 12:
        dwTextId = 16;

        switch (m_nID) {
        case 8:
            dwStrId = 18016;
            pOptions->m_nCommandSoundsFrequency = 3;
            break;
        case 9:
            dwStrId = 18016;
            pOptions->m_nCommandSoundsFrequency = 2;
            break;
        case 10:
            dwStrId = 18016;
            pOptions->m_nCommandSoundsFrequency = 1;
            break;
        case 58:
            dwStrId = 11352;
            pOptions->m_nSelectionSoundsFrequency = 3;
            break;
        case 59:
            dwStrId = 11352;
            pOptions->m_nSelectionSoundsFrequency = 2;
            break;
        case 60:
            dwStrId = 11352;
            pOptions->m_nSelectionSoundsFrequency = 1;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3395
            UTIL_ASSERT(FALSE);
        }

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 3401
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_pEngineOptions->UpdateHelp(m_pPanel->m_nID, dwTextId, dwStrId);
    g_pBaldurChitin->m_pEngineOptions->UpdatePopupPanel(m_pPanel->m_nID, FALSE);
}

// 0x658A60
CUIControlButtonOptionsGameCommand::CUIControlButtonOptionsGameCommand(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    DWORD dwStrId;

    switch (m_pPanel->m_nID) {
    case 2:
    case 13:
        switch (m_nID) {
        case 5:
            dwStrId = 13729; // "Load Game"
            break;
        case 6:
            dwStrId = 13730; // "Save Game"
            break;
        case 7:
            dwStrId = 17162; // "Graphics"
            break;
        case 8:
            dwStrId = 17164; // "Sound"
            break;
        case 9:
            dwStrId = 17165; // "Game Play"
            break;
        case 10:
            dwStrId = 13731; // "Quit Game"
            break;
        case 11:
            dwStrId = 10308; // "Return"
            break;
        case 13:
            dwStrId = 33468; // "Keyboard"
            break;
        case 14:
            dwStrId = 15415; // "Movies"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3817
            UTIL_ASSERT(FALSE);
        }
        break;
    case 6:
        dwStrId = controlInfo->base.nID;
        break;
    case 7:
        switch (m_nID) {
        case 13:
            dwStrId = 17778; // "Character Sounds"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3834
            UTIL_ASSERT(FALSE);
        }
        break;
    case 8:
        switch (m_nID) {
        case 5:
            dwStrId = 17163; // "Feedback"
            break;
        case 6:
            dwStrId = 17166; // "Auto-Pause"
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 3852
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 3859
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    SetText(strRes.szText);
}

// 0x6589C0
CUIControlButtonOptionsGameCommand::~CUIControlButtonOptionsGameCommand()
{
}

// 0x658A60
void CUIControlButtonOptionsGameCommand::OnLButtonClick(CPoint pt)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 3893
    UTIL_ASSERT(pGame != NULL);

    CScreenOptions* pEngine = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 3895
    UTIL_ASSERT(pEngine != NULL);

    CSingleLock lock(&(pEngine->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    CUIManager* pManager = pEngine->GetManager();
    if (pManager->m_pFocusedControl != NULL) {
        pManager->m_pFocusedControl->KillFocus();
        pManager->m_pFocusedControl = NULL;
    }

    STRREF dwStrId;
    switch (m_pPanel->m_nID) {
    case 2:
    case 13:
        switch (m_nID) {
        case 5:
            pEngine->m_dwErrorState = 5;
            pEngine->m_dwErrorTextId = 19531;
            pEngine->m_strErrorButtonText[0] = 15590;
            pEngine->m_strErrorButtonText[1] = 13727;
            pEngine->SummonPopup(4);
            break;
        case 6:
            if (pGame->CanSaveGame(dwStrId, 0, 0)) {
                if (g_pChitin->cNetwork.m_nServiceProvider == CNetwork::SERV_PROV_NULL) {
                    pGame->field_366E = 1;
                    pGame->field_50DC = 0;

                    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
                        if (!pGame->field_50D8) {
                            pGame->SynchronousUpdate();
                        }
                        pGame->field_50D8 = TRUE;
                    }
                }

                CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
                // __LINE__: 1670
                UTIL_ASSERT(pSave != NULL);

                pSave->StartSave(0);
                pEngine->SelectEngine(pSave);
            } else {
                pEngine->m_dwErrorState = 0;
                pEngine->m_dwErrorTextId = dwStrId;
                pEngine->m_strErrorButtonText[0] = 11973;
                pEngine->SummonPopup(3);
            }
            break;
        case 7:
            pEngine->SaveGraphicModeOptions();

            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->m_bSpriteMirror = CGameAnimationType::MIRROR_BAM;
            pEngine->SummonPopup(6);
            break;
        case 8:
            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->SummonPopup(7);
            break;
        case 9:
            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->SummonPopup(8);
            break;
        case 10:
            if (pGame->field_4AA2 < pGame->m_worldTime.m_gameTime) {
                if (pGame->CanSaveGame(dwStrId, 0, 0)) {
                    pEngine->m_dwErrorState = 3;
                    pEngine->m_dwErrorTextId = 16456;
                    pEngine->m_strErrorButtonText[0] = 15589;
                    pEngine->m_strErrorButtonText[1] = 15417;
                    pEngine->m_strErrorButtonText[2] = 13727;
                    pEngine->SummonPopup(5);
                } else {
                    pEngine->m_dwErrorState = 1;
                    pEngine->m_dwErrorTextId = 16516;
                    pEngine->m_strErrorButtonText[0] = 15417;
                    pEngine->m_strErrorButtonText[1] = 13727;
                    pEngine->SummonPopup(4);
                }
            } else {
                pEngine->m_dwErrorState = 4;
                pEngine->m_dwErrorTextId = 19532;
                pEngine->m_strErrorButtonText[0] = 15417;
                pEngine->m_strErrorButtonText[1] = 13727;
                pEngine->SummonPopup(4);
            }
            break;
        case 11:
            if (m_pPanel->m_nID == 2) {
                pEngine->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
            } else {
                pEngine->m_bFromMainMenu = FALSE;
                pEngine->DismissPopup();
                pEngine->SelectEngine(g_pBaldurChitin->m_pEngineConnection);
            }
            break;
        case 13:
            if (1) {
                CScreenKeymaps* pKeymaps = g_pBaldurChitin->m_pEngineKeymaps;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
                // __LINE__: 4000
                UTIL_ASSERT(pKeymaps != NULL);

                pKeymaps->StartKeymaps();
                pEngine->SelectEngine(pKeymaps);
                pKeymaps->m_bFromMainMenu = pEngine->m_bFromMainMenu;
            }
            break;
        case 14:
            if (1) {
                CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
                // __LINE__: 4010
                UTIL_ASSERT(pMovies != NULL);

                pMovies->StartMovies(0);
                pEngine->SelectEngine(pMovies);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 4031
            UTIL_ASSERT(FALSE);
        }
        break;
    case 6:
        break;
    case 8:
        switch (m_nID) {
        case 5:
            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->SummonPopup(9);
            break;
        case 6:
            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->SummonPopup(10);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 4050
            UTIL_ASSERT(FALSE);
        }
        break;
    case 7:
        switch (m_nID) {
        case 13:
            // NOTE: Uninline.
            pEngine->PushOptions(&(pGame->m_cOptions));

            pEngine->SummonPopup(12);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
            // __LINE__: 4064
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
        // __LINE__: 4073
        UTIL_ASSERT(FALSE);
    }

    lock.Unlock();
}

// 0x659150
CUIControlButtonOptionsPopupDone::CUIControlButtonOptionsPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    SetText(CBaldurEngine::FetchString(11973));
}

// 0x659200
CUIControlButtonOptionsPopupDone::~CUIControlButtonOptionsPopupDone()
{
}

// 0x6592A0
void CUIControlButtonOptionsPopupDone::OnLButtonClick(CPoint pt)
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 4131
    UTIL_ASSERT(pOptions != NULL);

    pOptions->OnDoneButtonClick();
}

// 0x6592E0
CUIControlButtonOptionsPopupCancel::CUIControlButtonOptionsPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    SetText(CBaldurEngine::FetchString(13727));
}

// 0x659390
CUIControlButtonOptionsPopupCancel::~CUIControlButtonOptionsPopupCancel()
{
}

// 0x659430
void CUIControlButtonOptionsPopupCancel::OnLButtonClick(CPoint pt)
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 4185
    UTIL_ASSERT(pOptions != NULL);

    pOptions->OnCancelButtonClick();
}

// 0x659470
CUIControlButtonOptionsError::CUIControlButtonOptionsError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    SetText(CBaldurEngine::FetchString(13727));
}

// 0x6594C0
CUIControlButtonOptionsError::~CUIControlButtonOptionsError()
{
}

// 0x659560
void CUIControlButtonOptionsError::OnLButtonClick(CPoint pt)
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenOptions.cpp
    // __LINE__: 4237
    UTIL_ASSERT(pOptions != NULL);

    pOptions->OnErrorButtonClick(m_nID);
}

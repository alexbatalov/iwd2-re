#include "CScreenOptions.h"

#include "CBaldurChitin.h"
#include "CGameOptions.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x6530E0
CScreenOptions::CScreenOptions()
{
    m_dwErrorTextId = 0;
    m_dwErrorState = 0;
    m_nNumErrorButtons = 0;
    field_484 = 0;
    field_488 = 0;
    field_48A = 0;
    field_48B = 0;
    field_48C = 0;
    field_48D = 0;
    field_E90 = 0;
    field_E91 = 0;
    m_bFullScreenOptions = FALSE;

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
    m_bFullScreenOptions = FALSE;

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
    // TODO: Incomplete.
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

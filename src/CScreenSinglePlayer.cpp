#include "CScreenSinglePlayer.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenCharacter.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
#include "CSpell.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F7500
const CString CScreenSinglePlayer::TOKEN_GOLD("GOLD");

// 0x8F64BC
const CString CScreenSinglePlayer::PARTY("Party");

// 0x8F60B0
const CString CScreenSinglePlayer::DESCR("Descr");

// 0x8F7504
const CString CScreenSinglePlayer::CHAR("Char");

// 0x8F7508
const CString CScreenSinglePlayer::NAME("Name");

// 0x8B4828
int CScreenSinglePlayer::dword_8B4828 = -1;

// 0x8F64C0
char CScreenSinglePlayer::byte_8F64C0[20];

// 0x8F64E0
char CScreenSinglePlayer::byte_8F64E0[4096];

// 0x8F74E0
char CScreenSinglePlayer::byte_8F74E0[32];

// 0x65FAC0
CScreenSinglePlayer::CScreenSinglePlayer()
{
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    field_480 = 0;
    field_484 = 0;

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
    m_bCapsLockKeyOn = FALSE;
    field_458 = -1;
    field_45C = 0;
    field_460 = 0;
    m_nPartyCount = 0;
    m_nTopParty = 0;
    m_nParty = 0;
    field_139E = 0;
    m_bSinglePlayerStartup = FALSE;
    m_bLastLockAllowInput = 0;
    field_138E = 0;
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x660730
BOOL CScreenSinglePlayer::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x660740
void CScreenSinglePlayer::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x660750
void CScreenSinglePlayer::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x660770
void CScreenSinglePlayer::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x660780
BOOL CScreenSinglePlayer::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenSinglePlayer::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenSinglePlayer::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenSinglePlayer::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenSinglePlayer::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenSinglePlayer::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenSinglePlayer::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenSinglePlayer::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x686660
SHORT CScreenSinglePlayer::GetNumVirtualKeys()
{
    return CSCREENSINGLEPLAYER_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenSinglePlayer::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x668C30
BYTE* CScreenSinglePlayer::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x6607B0
CScreenSinglePlayer::~CScreenSinglePlayer()
{
}

// 0x660850
void CScreenSinglePlayer::EngineActivated()
{
    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    CheckEnableCharacters();

    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
    m_cUIManager.InvalidateRect(NULL);

    if (field_45C == 1) {
        if (!field_138E) {
            sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, 0);
            if (GetPrivateProfileStringA(byte_8F64C0, NAME, "", byte_8F64E0, sizeof(byte_8F64E0), ".\\Party.ini")) {
                CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

                BOOL v1 = TRUE;
                for (INT nSlot = 0; nSlot < 6 && v1; nSlot++) {
                    v1 = CMultiplayerSettings::CHARSTATUS_NO_CHARACTER == pSettings->GetCharacterStatus(nSlot);
                }

                if (v1) {
                    if (GetTopPopup() == NULL) {
                        SummonPopup(10);
                    }
                }
            }
        } else {
            field_138E = 0;
        }
    }
}

// 0x6609E0
void CScreenSinglePlayer::EngineDeactivated()
{
    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x660A20
void CScreenSinglePlayer::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUISP"), g_pBaldurChitin->field_4A28);

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

    m_pCurrentScrollBar = NULL;

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(10)->SetActive(FALSE);
}

// 0x5D72C0
void CScreenSinglePlayer::EngineDestroyed()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x660B90
void CScreenSinglePlayer::OnKeyDown(SHORT nKeysFlags)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 528
    UTIL_ASSERT(pGame != NULL);

    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                switch (m_pVirtualKeysFlags[nKeyFlag]) {
                case VK_TAB:
                    m_cUIManager.ForceToolTip();
                    break;
                case VK_RETURN:
                    if (GetTopPopup() != NULL) {
                        OnDoneButtonClick();
                    } else {
                        OnMainDoneButtonClick();
                    }
                    break;
                case VK_ESCAPE:
                    if (GetTopPopup() != NULL) {
                        OnCancelButtonClick();
                    } else {
                        if (field_45C != 1 && field_45C != 2) {
                            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
                            // __LINE__: 2626
                            UTIL_ASSERT(FALSE);
                        }

                        SelectEngine(g_pBaldurChitin->m_pEngineWorld);
                    }
                    break;
                case VK_SNAPSHOT:
                    g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                    break;
                }
            }
        }
    }
}

// 0x660D00
void CScreenSinglePlayer::TimerAsynchronousUpdate()
{
    CUIPanel* pPanel = GetTopPopup();

    BOOLEAN bDoMainButtonClick = FALSE;

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    if (pPanel != NULL) {
        // NOTE: Uninline.
        UpdatePopupPanel(pPanel->m_nID);
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (field_45C == 2) {
        g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    } else {
        m_bLastLockAllowInput = pGame->GetMultiplayerSettings()->m_bArbitrationLockAllowInput;

        if (g_pChitin->cNetwork.MakePlayersVisible() == TRUE) {
            g_pBaldurChitin->GetBaldurMessage()->SendFullSettingsToClients(CString(""));
        }

        if (pGame->GetMultiplayerSettings()->m_bFirstConnected == TRUE
            && pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE) {
            pGame->GetMultiplayerSettings()->m_bFirstConnected = FALSE;
            m_nErrorState = 1;
            m_dwErrorTextId = 10247;
            SummonPopup(6);

            pVidMode->m_bPointerEnabled = FALSE;
            renderLock.Unlock();

            g_pChitin->m_bDisplayStale = TRUE;
            pGame->sub_59FA00(TRUE);

            renderLock.Lock(INFINITE);

            BOOLEAN bError = FALSE;
            for (BYTE cnt = 0; cnt < 6 && !bError; cnt++) {
                BOOLEAN bFinishedCharacter = FALSE;
                INT nRetries = 0;

                while (!bFinishedCharacter) {
                    g_pBaldurChitin->GetBaldurMessage()->DemandCharacterSlot(cnt,
                        FALSE,
                        g_pChitin->cNetwork.m_nHostPlayer);

                    DWORD dwStartTickCount = GetTickCount();
                    BOOLEAN bFinished = FALSE;
                    CString sHostName;

                    if (g_pChitin->cNetwork.m_nHostPlayer != -1) {
                        sHostName = g_pChitin->cNetwork.m_psPlayerName[g_pChitin->cNetwork.m_nHostPlayer];
                    } else {
                        sHostName = "";
                    }

                    if (bError) {
                        bFinishedCharacter = TRUE;
                        break;
                    }

                    while (!bFinished) {
                        if (GetTickCount() >= dwStartTickCount
                            && GetTickCount() - dwStartTickCount < 5000) {

                        } else {
                            nRetries++;
                            if (nRetries < 3) {
                                break;
                            }

                            g_pChitin->cNetwork.CloseSession(TRUE);
                            bError = TRUE;
                            bFinishedCharacter = TRUE;
                            break;
                        }

                        g_pBaldurChitin->GetBaldurMessage()->HandleBlockingMessages();
                        g_pChitin->m_bDisplayStale = TRUE;
                        Sleep(60);

                        if (!g_pChitin->cNetwork.GetSessionOpen()) {
                            bError = TRUE;
                            bFinishedCharacter = TRUE;
                            break;
                        }

                        if (g_pChitin->cNetwork.PeekSpecificMessage(sHostName, CBaldurMessage::MSG_TYPE_PLAYERCHAR, CBaldurMessage::MSG_SUBTYPE_PLAYERCHAR_DEMAND_REPLY) == TRUE) {
                            DWORD dwSize;
                            BYTE* pMessage = g_pChitin->cNetwork.FetchSpecificMessage(sHostName,
                                CBaldurMessage::MSG_TYPE_PLAYERCHAR,
                                CBaldurMessage::MSG_SUBTYPE_PLAYERCHAR_DEMAND_REPLY,
                                dwSize);

                            g_pBaldurChitin->GetBaldurMessage()->OnDemandCharacterSlotReply(g_pChitin->cNetwork.m_nHostPlayer,
                                pMessage,
                                dwSize);

                            delete pMessage;

                            bFinished = TRUE;
                            bFinishedCharacter = TRUE;
                        }
                    }
                }
            }

            DismissPopup();

            pVidMode->m_bPointerEnabled = TRUE;
            renderLock.Unlock();

            if (bError == TRUE) {
                g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;
                SelectEngine(g_pBaldurChitin->m_pEngineConnection);

                if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                    g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
                }

                pGame->DestroyGame(TRUE, FALSE);

                return;
            }

            renderLock.Lock(INFINITE);
            pGame->GetMultiplayerSettings()->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer,
                TRUE,
                TRUE);
        }
    }

    // TODO: Check, lots of jumps and repeating conditions.
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 3:
            UpdateModifyCharacterPanel();
            break;
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        case 10:
            UpdatePartySelectionPanel();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
            // __LINE__: 1195
            UTIL_ASSERT(FALSE);
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()
            && field_45C == 1
            && IsMainDoneButtonClickable()) {
            while (GetTopPopup() != NULL) {
                OnCancelButtonClick();
            }

            bDoMainButtonClick = TRUE;
        }
    } else {
        UpdateMainPanel();

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()
            && field_45C == 1
            && IsMainDoneButtonClickable()) {
            bDoMainButtonClick = TRUE;
        }
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && field_45C == 2
        && pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE) {
        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            pGame->MultiplayerSetCharacterCreationLocation();
        }

        field_45C = 1;
        StartSinglePlayer(1);
    }

    renderLock.Unlock();

    if (bDoMainButtonClick) {
        OnMainDoneButtonClick();
    }

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x64A110
void CScreenSinglePlayer::TimerSynchronousUpdate()
{
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x6612D0
void CScreenSinglePlayer::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1120
    UTIL_ASSERT(pPanel != NULL);

    CheckEnableCharacters();

    switch (dwPanelId) {
    case 2:
        UpdateHelp(pPanel->m_nID, 14, 11323);
        break;
    case 3:
        break;
    case 5:
    case 6:
    case 7:
        ResetErrorPanel(pPanel);
        break;
    case 8:
        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(m_cUIManager.GetPanel(8)->GetControl(4));
        ResetViewCharacterPanel(pPanel);
        break;
    case 10:
        m_nParty = 0;
        m_nTopParty = 0;
        dword_8B4828 = -1;
        m_nPartyCount = 0;
        sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, m_nPartyCount);
        while (GetPrivateProfileStringA(byte_8F64C0, NAME, "", byte_8F64E0, sizeof(byte_8F64E0), ".\\Party.ini")) {
            m_nPartyCount++;
            sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, m_nPartyCount);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1149
        UTIL_ASSERT(FALSE);
    }
}

// 0x661480
CUIPanel* CScreenSinglePlayer::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenSinglePlayer::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
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
void CScreenSinglePlayer::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1093
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Uninline.
void CScreenSinglePlayer::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 3:
        UpdateModifyCharacterPanel();
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    case 10:
        UpdatePartySelectionPanel();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1195
        UTIL_ASSERT(FALSE);
    }
}

// 0x6614A0
void CScreenSinglePlayer::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1275
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1281
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);

    ResetPopupPanel(pPanel->m_nID);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    EnablePopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    UpdatePopupPanel(pPanel->m_nID);
}

// 0x661640
void CScreenSinglePlayer::DismissPopup()
{
    CUIPanel* pOldPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1318
    UTIL_ASSERT(pOldPanel != NULL);

    CUIPanel* pNewPanel = m_lPopupStack.GetCount() - 2 >= 0
        ? m_lPopupStack.GetAt(m_lPopupStack.FindIndex(m_lPopupStack.GetCount() - 2))
        : m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1327
    UTIL_ASSERT(pNewPanel != NULL);

    if (m_cUIManager.m_pFocusedControl != NULL
        && m_cUIManager.m_pFocusedControl->m_pPanel == pOldPanel) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1339
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1356
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

// 0x661860
BOOL CScreenSinglePlayer::IsMainDoneButtonClickable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1386
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1388
    UTIL_ASSERT(pSettings != NULL);

    BOOL bResult;
    if (field_45C == 1) {
        BOOL v1 = pSettings->m_bFirstConnected == FALSE;

        for (INT nPlayer = 0; nPlayer < 6; nPlayer++) {
            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && g_pChitin->cNetwork.GetRawPlayerID(nPlayer) != 0
                && !pSettings->GetPlayerReady(static_cast<SHORT>(nPlayer))) {
                v1 = FALSE;
            }
        }

        for (INT nCharacter = 0; nCharacter < 6; nCharacter++) {
            if (pSettings->GetCharacterStatus(nCharacter) == CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER) {
                v1 = FALSE;
            }

            if (pGame->GetCharacterSlot(nCharacter) != CGameObjectArray::INVALID_INDEX
                && !pSettings->GetCharacterReady(nCharacter)) {
                v1 = g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL;
            }
        }

        if (!g_pBaldurChitin->cNetwork.GetSessionHosting()
            && pSettings->m_bArbitrationLockStatus == 1) {
            v1 = FALSE;
        }

        if (pGame->GetCharacterSlot(0) == CGameObjectArray::INVALID_INDEX) {
            bResult = FALSE;
        } else {
            bResult = v1;
        }
    } else if (field_45C == 2) {
        bResult = TRUE;
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1454
        UTIL_ASSERT(FALSE);
    }

    return bResult;
}

// 0x6619C0
void CScreenSinglePlayer::OnDoneButtonClick()
{
    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1484
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 5:
        OnErrorButtonClick(0);
        return;
    case 6:
        return;
    case 7:
        OnErrorButtonClick(0);
        return;
    }

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (pPanel->m_nID) {
    case 0:
        renderLock.Unlock();
        break;
    case 3:
    case 8:
        DismissPopup();
        renderLock.Unlock();
        break;
    case 10:
        DismissPopup();
        renderLock.Unlock();
        OnPartySelectionDoneButtonClick();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1524
        UTIL_ASSERT(FALSE);
    }
}

// 0x661B30
void CScreenSinglePlayer::OnCancelButtonClick()
{
    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1555
    UTIL_ASSERT(pPanel != NULL);

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (pPanel->m_nID) {
    case 0:
        break;
    case 3:
    case 8:
        DismissPopup();
        break;
    case 5:
    case 7:
        DismissPopup();
        break;
    case 6:
        break;
    case 10:
        // NOTE: Uninline.
        OnLogoutButtonClick();
        break;
    }

    renderLock.Unlock();
}

// 0x661CC0
void CScreenSinglePlayer::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1618
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }
}

// 0x661D90
void CScreenSinglePlayer::UpdateMainPanel()
{
    CUIControlButton* pButton;
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1657
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        UpdateMainPanelCharacter(pPanel, nCharacterSlot);
    }

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1667
    UTIL_ASSERT(pSettings != NULL);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(43));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1672
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsModifyButtonClickable());

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(28));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1677
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsMainDoneButtonClickable());
}

// 0x661E80
void CScreenSinglePlayer::CheckEnableCharacters()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1710
    UTIL_ASSERT(pPanel != NULL);

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        BOOL bReadyActive;
        BOOL bModifyPlayerActive;
        BOOL bModifyCharacterActive;
        CheckCharacterButtons(nCharacterSlot, bReadyActive, bModifyPlayerActive, bModifyCharacterActive);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nCharacterSlot + 18));
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nCharacterSlot + 0x10000024));

        pButton->SetActive(bModifyCharacterActive);
        pButton->SetInactiveRender(bModifyCharacterActive);

        pLabel->SetActive(!bModifyCharacterActive);
        pLabel->SetInactiveRender(!bModifyCharacterActive);
    }
}

// 0x661F40
void CScreenSinglePlayer::CheckCharacterButtons(INT nCharacterSlot, BOOL& bReadyActive, BOOL& bModifyPlayerActive, BOOL& bModifyCharacterActive)
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1756
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1759
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1761
    UTIL_ASSERT(pSettings != NULL);

    LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);
    BOOL bSlotFree = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER;
    BOOL bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX;

    // FIXME: Calls `GetCharacterStatus` twice and result is ignored both times.
    pSettings->GetCharacterStatus(nCharacterSlot);
    pSettings->GetCharacterStatus(nCharacterSlot);

    INT nPlayerSlot = pSettings->GetCharacterControlledByPlayer(nCharacterSlot);
    if (nPlayerSlot == -1) {
        nPlayerSlot = 0;
    }

    PLAYER_ID idPlayer = pNetwork->GetPlayerID(nPlayerSlot);
    BOOL bPlayerExists = pNetwork->FindPlayerLocationByID(pNetwork->m_idLocalPlayer, FALSE) != -1;
    BOOL bIsHost = pNetwork->GetSessionHosting();

    // FIXME: Unused.
    pSettings->GetCharacterReady(nCharacterSlot);

    BOOL bIsLocalPlayer = idPlayer != 0 && idPlayer == pNetwork->m_idLocalPlayer;

    switch (field_45C) {
    case 1:
        bReadyActive = bIsLocalPlayer
            && bSlotFull
            && pSettings->m_bArbitrationLockAllowInput;
        bModifyPlayerActive = (bPlayerExists || bIsHost)
            && (bSlotFull || bSlotFree)
            && pSettings->m_bArbitrationLockAllowInput;
        bModifyCharacterActive = TRUE;
        break;
    case 2:
        bReadyActive = FALSE;
        bModifyPlayerActive = (bPlayerExists || bIsHost) && bSlotFull;
        bModifyCharacterActive = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 1812
        UTIL_ASSERT(FALSE);
    }
}

// 0x662170
void CScreenSinglePlayer::UpdateMainPanelCharacter(CUIPanel* pPanel, INT nCharacterSlot)
{
    // NOTE: Unused.
    CString v1;

    CString sPlayerName;
    CString sCharacterName;
    CResRef portraitResRef;

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1855
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1856
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1860
    UTIL_ASSERT(pSettings != NULL);

    BOOL bSlotFree;
    BOOL bSlotFull;
    BOOL bSlotLoading;
    BOOL bSlotCreating;
    BOOL bReadyActive;
    BOOL bModifyPlayerActive;
    BOOL bModifyCharacterActive;

    if (!pSettings->m_bFirstConnected) {
        LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);

        bSlotFree = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER;
        bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
            && nCharacterId != CGameObjectArray::INVALID_INDEX;
        bSlotLoading = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
            && nCharacterId == CGameObjectArray::INVALID_INDEX;
        bSlotCreating = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER;

        if (bSlotFull) {
            CGameSprite* pSprite;
            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                portraitResRef = pSprite->GetBaseStats()->m_portraitSmall;

                // NOTE: Uninline.
                sCharacterName = pSprite->GetName();

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            } else {
                sCharacterName = FetchString(10262); // "Error"
            }
        }

        INT nPlayerSlot = pSettings->GetCharacterControlledByPlayer(nCharacterSlot);
        if (nPlayerSlot == -1) {
            nPlayerSlot = 0;
        }

        pNetwork->GetPlayerName(nPlayerSlot, sPlayerName);

        // FIXME: Unused.
        pNetwork->GetPlayerID(nPlayerSlot);

        CheckCharacterButtons(nCharacterSlot,
            bReadyActive,
            bModifyPlayerActive,
            bModifyCharacterActive);
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nCharacterSlot + 18));
    CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nCharacterSlot + 0x10000024));

    if (!pSettings->m_bFirstConnected && pSettings->m_bArbitrationLockAllowInput) {
        BOOLEAN bOldActive = pButton->m_bActive;

        pButton->SetActive(bModifyCharacterActive);
        pButton->SetInactiveRender(bModifyCharacterActive);

        pLabel->SetActive(bModifyCharacterActive);
        pLabel->SetInactiveRender(bModifyCharacterActive);

        if (bModifyCharacterActive) {
            if (bSlotFree) {
                sCharacterName = FetchString(10264); // "Create Character"
            }

            pButton->m_nTextFlags |= 0x20;
            pButton->SetText(sCharacterName);
        } else {
            if (bSlotLoading) {
                sCharacterName = FetchString(10265); // "Loading Character..."
            }

            if (bSlotCreating) {
                sCharacterName = FetchString(10266); // "Creating Character..."
            }

            if (bSlotFree) {
                sCharacterName = FetchString(10267); // "No Character"
            }

            pLabel->SetText(sCharacterName);
        }

        if (bModifyCharacterActive != bOldActive) {
            CRect rButtonFrame(pPanel->m_ptOrigin + pButton->m_ptOrigin,
                pButton->m_size);
            pPanel->InvalidateRect(&rButtonFrame);

            CRect rLabelFrame(pPanel->m_ptOrigin + pLabel->m_ptOrigin,
                pButton->m_size);
            pPanel->InvalidateRect(&rLabelFrame);
        }
    } else {
        pButton->SetText(CString(""));
        pButton->SetActive(FALSE);
        pButton->SetInactiveRender(FALSE);

        pLabel->SetText(CString(""));
        pLabel->SetActive(FALSE);
        pLabel->SetInactiveRender(FALSE);
    }

    CUIControlButtonSinglePlayerPortrait* pPortrait = static_cast<CUIControlButtonSinglePlayerPortrait*>(pPanel->GetControl(nCharacterSlot + 6));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1983
    UTIL_ASSERT(pPortrait != NULL);

    pPortrait->SetEnabled(IsPortraitButtonClickable(nCharacterSlot));

    if (pSettings->m_bFirstConnected || !pSettings->m_bArbitrationLockAllowInput || !bSlotFull) {
        portraitResRef = "";
    }

    pPortrait->SetPortrait(portraitResRef);
}

// 0x6627C0
void CScreenSinglePlayer::UpdateModifyCharacterPanel()
{
    // FIXME: Unused.
    CString v1;
    CString v2;

    CUIControlButton* pButton;

    CUIPanel* pPanel = m_cUIManager.GetPanel(3);

    // __FILE__: C2033Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2033
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2036
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2038
    UTIL_ASSERT(pSettings != NULL);

    INT nCharacterSlot = field_458;
    BYTE v3 = static_cast<BYTE>(g_pBaldurChitin->cNetwork.m_nLocalPlayer);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2043
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    BOOL v4 = FALSE;
    if (pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && pGame->GetCharacterSlot(nCharacterSlot) != CGameObjectArray::INVALID_INDEX) {
        v4 = TRUE;
    }

    BOOL v5 = CMultiplayerSettings::CHARSTATUS_NO_CHARACTER == pSettings->GetCharacterStatus(nCharacterSlot);
    BOOL v6 = field_45C == 1 && v3 == pSettings->GetCharacterControlledByPlayer(nCharacterSlot);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2053
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(v6 && v5);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2057
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(v6 && v4);
}

// 0x6629E0
void CScreenSinglePlayer::OnMainDoneButtonClick()
{
    CString sDefault;
    INT nMsgFrom;
    DWORD dwSize;
    BYTE* pData;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2092
    UTIL_ASSERT(pGame != NULL);

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    CBaldurMessage* pMessage = g_pBaldurChitin->GetBaldurMessage();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2095
    UTIL_ASSERT(pMessage != NULL);

    CString sSaveGame = pGame->GetSaveGame();

    if (IsMainDoneButtonClickable()) {
        if (field_45C == 1) {
            sDefault = "default";
            pGame->m_sSaveGame = sDefault;
            CScreenCharacter::SAVE_NAME = sDefault;

            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
                CScreenCharacter::SAVE_NAME = sSaveGame;
            }

            pGame->m_nTravelScreenImageToUse = rand() % 5;
            pGame->sub_59FA00(TRUE);

            LONG nActionTarget = CInfGame::PROGRESSBAR_CACHING_ADDITIONAL
                + 2 * CInfGame::PROGRESSBAR_GAME_ADDITIONAL;
            if (pNetwork->GetSessionHosting() == TRUE) {
                nActionTarget += CInfGame::PROGRESSBAR_CACHING_ADDITIONAL
                    + CInfGame::PROGRESSBAR_GAME_ADDITIONAL;
            }

            m_bSinglePlayerStartup = TRUE;
            g_pChitin->SetProgressBar(TRUE,
                9887,
                0,
                0,
                FALSE,
                0,
                FALSE,
                0,
                FALSE,
                FALSE,
                255);
            g_pChitin->cProgressBar.m_nActionProgress = 0;
            g_pChitin->cProgressBar.m_nActionTarget = nActionTarget;

            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                pGame->UpdateCharacterSlots();

                BOOLEAN bListenToJoinOption = pGame->GetMultiplayerSettings()->GetListenToJoinOption();

                pGame->GetMultiplayerSettings()->SetListenToJoinOption(FALSE, FALSE);
                pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(FALSE, 0);
                pGame->SetupCharacters(TRUE);

                for (int area = 0; area < CINFGAME_MAX_AREAS; area++) {
                    if (pGame->m_gameAreas[area] != NULL) {
                        pGame->m_gameAreas[area]->SortLists();
                    }
                }

                pGame->SaveGame(0, 1, 0);

                // NOTE: Uninline.
                m_cUIManager.KillCapture();

                pMessage->SendSignal(CBaldurMessage::SIGNAL_ALL_CLIENTS, 64);

                INT nPlayerCount = 0;
                for (INT nPlayerNumber = 0; nPlayerNumber < 6; nPlayerNumber++) {
                    if (g_pChitin->cNetwork.GetPlayerID(nPlayerNumber) != 0) {
                        nPlayerCount++;
                    }
                }

                if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                    g_pChitin->cProgressBar.m_nWaitingReason = 16617;
                    g_pChitin->cProgressBar.m_bWaiting = TRUE;
                }

                int v1 = 100;
                int v2 = 0;
                while (v1 > 0 && v2 < 2 * nPlayerCount - 2) {
                    pData = pMessage->PollSpecificMessageType(CBaldurMessage::MSG_TYPE_RESOURCE,
                        CBaldurMessage::MSG_SUBTYPE_RESOURCE_DEMAND,
                        nMsgFrom,
                        dwSize);
                    if (pData != NULL) {
                        pMessage->OnResourceDemanded(nMsgFrom, pData, dwSize);
                        delete pData;
                        v2++;
                    }

                    g_pChitin->m_bDisplayStale = TRUE;
                    Sleep(60);

                    v1--;

                    nPlayerCount = 0;
                    for (INT nPlayerNumber = 0; nPlayerNumber < 6; nPlayerNumber++) {
                        if (g_pChitin->cNetwork.GetPlayerID(nPlayerNumber) != 0) {
                            nPlayerCount++;
                        }
                    }
                }

                if (nPlayerCount > 1) {
                    while (v2 > 0) {
                        g_pChitin->m_bDisplayStale = TRUE;
                        Sleep(60);
                        v2--;
                    }
                }

                g_pChitin->cProgressBar.m_bWaiting = FALSE;
                g_pBaldurChitin->m_cCachingStatus.InvalidateScreen();

                pGame->DestroyGame(FALSE, TRUE);
                pGame->LoadGame(FALSE, TRUE);

                g_pChitin->cProgressBar.m_nActionProgress = g_pChitin->cProgressBar.m_nActionTarget - 1;
                g_pChitin->m_bDisplayStale = TRUE;

                pGame->sub_59FA00(TRUE);

                g_pChitin->cProgressBar.m_bTimeoutVisible = TRUE;
                g_pChitin->cProgressBar.m_nSecondsToTimeout = pMessage->m_dwSignalSecondsToTimeout;

                DWORD dwStart = GetTickCount();

                g_pChitin->cProgressBar.m_nActionProgress = g_pChitin->cProgressBar.m_nActionTarget;
                if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                    pMessage->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
                        g_pChitin->cProgressBar.m_nActionTarget,
                        g_pChitin->cProgressBar.m_bWaiting,
                        g_pChitin->cProgressBar.m_nWaitingReason,
                        g_pChitin->cProgressBar.m_bTimeoutVisible,
                        g_pChitin->cProgressBar.m_nSecondsToTimeout);
                }

                while (!pMessage->NonBlockingWaitForSignal(CBaldurMessage::SIGNAL_SERVER, 65)) {
                    DWORD dwElapsedMillis = GetTickCount() - dwStart;

                    DWORD nSecondsToTimeout;
                    if (dwElapsedMillis < 1000 * pMessage->m_dwSignalSecondsToTimeout) {
                        nSecondsToTimeout = pMessage->m_dwSignalSecondsToTimeout - dwElapsedMillis / 1000;
                    } else {
                        nSecondsToTimeout = 0;
                        pMessage->KickOutWaitingForSignal(CBaldurMessage::SIGNAL_SERVER, 65);
                    }

                    if (g_pChitin->cProgressBar.m_nSecondsToTimeout != nSecondsToTimeout) {
                        g_pChitin->cProgressBar.m_nSecondsToTimeout = nSecondsToTimeout;
                        pMessage->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
                            g_pChitin->cProgressBar.m_nActionTarget,
                            g_pChitin->cProgressBar.m_bWaiting,
                            g_pChitin->cProgressBar.m_nWaitingReason,
                            g_pChitin->cProgressBar.m_bTimeoutVisible,
                            g_pChitin->cProgressBar.m_nSecondsToTimeout);
                    }

                    while (1) {
                        pData = pMessage->PollSpecificMessageType(CBaldurMessage::MSG_TYPE_PROGRESSBAR,
                            CBaldurMessage::MSG_SUBTYPE_PROGRESSBAR_STATUS,
                            nMsgFrom,
                            dwSize);
                        if (pData == NULL) {
                            break;
                        }

                        pMessage->OnProgressBarStatus(nMsgFrom, pData, dwSize);
                        delete pData;
                    }

                    pData = pMessage->PollSpecificMessageType(CBaldurMessage::MSG_TYPE_RESOURCE,
                        CBaldurMessage::MSG_SUBTYPE_RESOURCE_DEMAND,
                        nMsgFrom,
                        dwSize);
                    if (pData != NULL) {
                        pMessage->OnResourceDemanded(nMsgFrom, pData, dwSize);
                        delete pData;
                    }

                    g_pChitin->m_bDisplayStale = TRUE;
                    Sleep(60);
                }

                g_pChitin->cProgressBar.m_bTimeoutVisible = FALSE;

                pMessage->SendSignal(CBaldurMessage::SIGNAL_ALL_CLIENTS, 66);
                pGame->GetMultiplayerSettings()->SetListenToJoinOption(bListenToJoinOption, FALSE);
            } else {
                // NOTE: Uninline.
                m_cUIManager.KillCapture();

                if (pGame->m_bGameLoaded) {
                    pGame->DestroyGame(FALSE, TRUE);
                }

                CString v3 = pGame->sub_5C0B30();

                if (!g_pChitin->cDimm.DirectoryRemoveFiles(v3)) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
                    // __LINE__: 2385
                    UTIL_ASSERT(FALSE);
                }

                g_pChitin->cDimm.m_cKeyTable.RescanEverything();

                if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                    g_pChitin->cProgressBar.m_nWaitingReason = 16618;
                    g_pChitin->cProgressBar.m_bWaiting = TRUE;
                }

                pMessage->WaitForSignal(CBaldurMessage::SIGNAL_ALL_CLIENTS, 64);

                if (pMessage->DemandResourceFromServer(CString("ICEWIND2"), 1013, TRUE, TRUE, FALSE)
                    && pMessage->DemandResourceFromServer(CString("WORLDMAP"), 1015, TRUE, TRUE, FALSE)) {
                    pMessage->DemandResourceFromServer(CString("EXPMAP"), 1015, TRUE, TRUE, FALSE);

                    g_pChitin->cProgressBar.m_bWaiting = FALSE;
                    g_pBaldurChitin->m_cCachingStatus.InvalidateScreen();

                    pGame->LoadGame(FALSE, TRUE);

                    g_pChitin->cProgressBar.m_nActionProgress = g_pChitin->cProgressBar.m_nActionTarget - 1;
                    g_pChitin->m_bDisplayStale = TRUE;

                    pGame->sub_59FA00(TRUE);

                    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                        pMessage->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
                            g_pChitin->cProgressBar.m_nActionTarget,
                            g_pChitin->cProgressBar.m_bWaiting,
                            g_pChitin->cProgressBar.m_nWaitingReason,
                            g_pChitin->cProgressBar.m_bTimeoutVisible,
                            g_pChitin->cProgressBar.m_nSecondsToTimeout);
                    }

                    g_pChitin->cDimm.RemoveFromDirectoryList(v3, TRUE);

                    pMessage->SendSignal(CBaldurMessage::SIGNAL_SERVER, 65);
                    g_pChitin->cProgressBar.m_nActionProgress = g_pChitin->cProgressBar.m_nActionTarget;

                    while (!pMessage->NonBlockingWaitForSignal(CBaldurMessage::SIGNAL_ALL_CLIENTS, 66)) {
                        while (1) {
                            pData = pMessage->PollSpecificMessageType(CBaldurMessage::MSG_TYPE_PROGRESSBAR,
                                CBaldurMessage::MSG_SUBTYPE_PROGRESSBAR_STATUS,
                                nMsgFrom,
                                dwSize);
                            if (pData == NULL) {
                                break;
                            }

                            pMessage->OnProgressBarStatus(nMsgFrom, pData, dwSize);
                            delete pData;
                        }

                        g_pChitin->m_bDisplayStale = TRUE;
                        Sleep(60);
                    }
                } else {
                    g_pChitin->cProgressBar.m_bWaiting = FALSE;
                    g_pBaldurChitin->m_cCachingStatus.InvalidateScreen();
                    g_pChitin->cNetwork.CloseSession(TRUE);
                    g_pChitin->cDimm.RemoveFromDirectoryList(v3, TRUE);
                }
            }

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                while (1) {
                    pData = pMessage->PollSpecificMessageType(CBaldurMessage::MSG_TYPE_PROGRESSBAR,
                        CBaldurMessage::MSG_SUBTYPE_PROGRESSBAR_STATUS,
                        nMsgFrom,
                        dwSize);
                    if (pData == NULL) {
                        break;
                    }

                    pMessage->OnProgressBarStatus(nMsgFrom, pData, dwSize);
                    delete pData;
                }

                g_pChitin->m_bDisplayStale = TRUE;
                Sleep(200);
            }

            pGame->sub_59FA00(TRUE);

            g_pChitin->cProgressBar.m_bTimeoutVisible = FALSE;
            g_pChitin->SetProgressBar(FALSE,
                0,
                0,
                0,
                FALSE,
                0,
                FALSE,
                0,
                FALSE,
                FALSE,
                255);

            m_bSinglePlayerStartup = FALSE;

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                SelectEngine(g_pBaldurChitin->m_pEngineWorld);

                if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
                    pGame->SelectAll(FALSE);
                } else {
                    pGame->SelectCharacter(pGame->GetProtagonist(), FALSE);
                }

                pGame->SelectToolbar();
            } else {
                g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;
                SelectEngine(g_pBaldurChitin->m_pEngineConnection);

                if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                    g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
                }

                if (pGame->m_bGameLoaded) {
                    pGame->DestroyGame(TRUE, FALSE);
                }
            }
        } else if (field_45C == 2) {
            SelectEngine(g_pBaldurChitin->m_pEngineWorld);
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
            // __LINE__: 2587
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x663640
BOOL CScreenSinglePlayer::IsModifyButtonClickable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2656
    UTIL_ASSERT(pGame != NULL);

    return !pGame->GetMultiplayerSettings()->m_bFirstConnected
        && (g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE) != -1
            || g_pBaldurChitin->cNetwork.GetSessionHosting())
        && field_45C == 2
        && pGame->GetMultiplayerSettings()->m_bArbitrationLockAllowInput;
}

// 0x6636D0
void CScreenSinglePlayer::OnModifyButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2707
    UTIL_ASSERT(pGame != NULL);

    if (IsModifyButtonClickable()) {
        STRREF strError;
        if (pGame->CanSaveGame(strError, 0, 0)) {
            if (g_pBaldurChitin->cNetwork.GetSessionHosting()) {
                pGame->MultiplayerSetCharacterCreationLocation();
                pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(TRUE, 0);
            }
        } else {
            CSingleLock renderLock(&(GetManager()->field_36), FALSE);
            renderLock.Lock(INFINITE);

            m_nErrorState = 0;
            m_dwErrorTextId = 10133;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(5);

            renderLock.Unlock();
        }
    }
}

// 0x663810
void CScreenSinglePlayer::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }

    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.GetSectionPlaying();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.GetMusicPosition();
}

// 0x663860
void CScreenSinglePlayer::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2884
    UTIL_ASSERT(0 <= nButton && nButton < CSCREENSINGLEPLAYER_ERROR_BUTTONS);

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nErrorState) {
    case 0:
        switch (nButton) {
        case 0:
            DismissPopup();
            break;
        }
        break;
    case 2:
        switch (nButton) {
        case 0:
            if (1) {
                CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();
                if (g_pBaldurChitin->cNetwork.GetSessionHosting()) {
                    g_pBaldurChitin->GetObjectGame()->MultiplayerSetCharacterCreationLocation();
                    pSettings->SetArbitrationLockStatus(TRUE, 0);
                } else {
                    g_pBaldurChitin->m_cBaldurMessage.SendArbitrationLockRequestToServer(TRUE);
                }
                DismissPopup();
            }
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    case 3:
        switch (nButton) {
        case 0:
            if (1) {
                CString sPlayerName;
                g_pBaldurChitin->cNetwork.GetPlayerName(field_480, sPlayerName);
                g_pBaldurChitin->m_cBaldurMessage.KickPlayerRequest(sPlayerName);
                DismissPopup();
            }
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    case 4:
        switch (nButton) {
        case 0:
            do {
                DismissPopup();
            } while (m_lPopupStack.GetTailPosition() != NULL);

            g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;
            SelectEngine(g_pBaldurChitin->m_pEngineStart);
            g_pChitin->cNetwork.CloseSession(TRUE);
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    }

    renderLock.Unlock();
}

// 0x663A70
void CScreenSinglePlayer::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 5:
        m_nNumErrorButtons = 1;
        break;
    case 6:
        m_nNumErrorButtons = 0;
        break;
    case 7:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 2971
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(TRUE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 1551
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 2993
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 2816
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENSINGLEPLAYER_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x663C90
void CScreenSinglePlayer::StartSinglePlayer(INT nEngineState)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3021
    UTIL_ASSERT(pPanel != NULL);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3023
    UTIL_ASSERT(pSettings != NULL);

    if (pSettings->m_bFirstConnected) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 3031
        UTIL_ASSERT(pText != NULL);

        pText->DisplayString(CString(""),
            FetchString(10314),
            pText->m_rgbLabelColor,
            pText->m_rgbTextColor,
            -1,
            FALSE,
            TRUE);
    }

    if (nEngineState == 1) {
        m_bLastLockAllowInput = pSettings->m_bArbitrationLockAllowInput;
        if (!m_bLastLockAllowInput) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
            // __LINE__: 3042
            UTIL_ASSERT(pText != NULL);

            pText->DisplayString(CString(""),
                FetchString(11547),
                pText->m_rgbLabelColor,
                pText->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);
        }
    }
}

// 0x663EB0
void CScreenSinglePlayer::UpdateExperienceEntry(CUIControlTextDisplay* pText, const CAIObjectType& typeAI, CDerivedStats& DStats, DWORD nSpecialization, BYTE nBestClass, DWORD dwFlags)
{
    const CRuleTables& ruleTables = g_pBaldurChitin->GetObjectGame()->GetRuleTables();
    CTlkTable& tlk = g_pBaldurChitin->GetTlkTable();
    CString sValue;

    for (INT iClassType = 1; iClassType <= CAIOBJECT_CLASS_MAX; iClassType++) {
        BYTE nLevel = static_cast<BYTE>(DStats.GetClassLevel(iClassType));
        if (nLevel > 0) {

            ruleTables.GetClassStringMixed(static_cast<BYTE>(iClassType),
                nSpecialization,
                dwFlags,
                sValue,
                typeAI.m_nGender != CAIOBJECTTYPE_SEX_FEMALE);
            tlk.SetToken(CRuleTables::TOKEN_CLASS, sValue);

            sValue.Format("%d", nLevel);
            tlk.SetToken(CRuleTables::TOKEN_LEVEL, sValue);

            UpdateText(pText, "%s", FetchString(11293)); // "<CLASS>: Level <LEVEL>"
        }
    }
}

// NOTE: Inlined.
void CScreenSinglePlayer::UpdateExperience(CUIControlTextDisplay* pText, CGameSprite* pSprite)
{
    DWORD nSpecialization = pSprite->GetSpecialization();

    CDerivedStats* pDStats = pSprite->GetDerivedStats();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3230
    UTIL_ASSERT(pDStats != NULL);

    CCreatureFileHeader* pBStats = pSprite->GetBaseStats();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3232
    UTIL_ASSERT(pBStats != NULL);

    UpdateExperienceEntry(pText,
        pSprite->m_liveTypeAI,
        *pDStats,
        nSpecialization,
        pDStats->GetBestClass(),
        pBStats->m_flags);
}

// 0x664010
void CScreenSinglePlayer::UpdatePartySelectionPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(10);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(7));

    INT v1;
    for (INT nSlot = 0; nSlot < 6; nSlot++) {
        CUIControlButtonSinglePlayerPartySelection* pButton = static_cast<CUIControlButtonSinglePlayerPartySelection*>(pPanel->GetControl(nSlot));
        BOOLEAN bSelected = m_nParty == nSlot;
        sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, m_nTopParty + nSlot);

        DWORD nSize = GetPrivateProfileStringA(byte_8F64C0,
            NAME,
            "",
            byte_8F64E0,
            sizeof(byte_8F64E0),
            ".\\Party.ini");
        if (nSize != 0) {
            byte_8F64E0[20] = '\0';
            pButton->SetSelected(bSelected);
            pButton->SetEnabled(TRUE);
            pButton->SetText(CString(byte_8F64E0));

            if (bSelected) {
                v1 = m_nTopParty + nSlot;
            }
        } else {
            pButton->SetSelected(FALSE);
            pButton->SetEnabled(FALSE);
            pButton->SetActive(FALSE);
            pButton->SetInactiveRender(FALSE);
        }
    }

    CUIControlScrollBarSinglePlayerParties* pScroll = static_cast<CUIControlScrollBarSinglePlayerParties*>(pPanel->GetControl(8));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3334
    UTIL_ASSERT(pScroll != NULL);

    // NOTE: Uninline.
    pScroll->UpdateScrollBar();

    if (v1 != dword_8B4828) {
        CUIControlTextDisplay* pTextHelp = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(6));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 3341
        UTIL_ASSERT(pTextHelp != NULL);

        pTextHelp->RemoveAll();

        sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, v1);

        for (INT nLine = 1; nLine <= 10; nLine++) {
            sprintf(byte_8F74E0, "%s%i", (LPCSTR)DESCR, nLine);
            DWORD nSize = GetPrivateProfileStringA(byte_8F64C0,
                byte_8F74E0,
                "",
                byte_8F64E0,
                sizeof(byte_8F64E0),
                ".\\Party.ini");
            if (nSize != 0) {
                byte_8F64E0[sizeof(byte_8F64E0) - 1] = '\0';
                UpdateText(pTextHelp, "%s", byte_8F64E0);
                UpdateText(pTextHelp, "%s", " ");
            }
        }

        pTextHelp->SetTopString(pTextHelp->m_plstStrings->FindIndex(0));

        dword_8B4828 = v1;
    }

    pPanel->InvalidateRect(NULL);
}

// 0x6642C0
void CScreenSinglePlayer::OnPartySelectionDoneButtonClick()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(10);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3368
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CStringList* pCharacters = pGame->GetImportCharacters();

    sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, m_nTopParty + m_nParty);

    INT nCharacters = 0;
    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        sprintf(byte_8F74E0, "%s%i", (LPCSTR)CHAR, nCharacterSlot + 1);
        DWORD nSize = GetPrivateProfileStringA(byte_8F64C0,
            byte_8F74E0,
            "",
            byte_8F64E0,
            sizeof(byte_8F64E0),
            ".\\Party.ini");
        if (nSize != 0) {
            byte_8F64E0[sizeof(byte_8F64E0) - 1] = '\0';

            CString sFileName = byte_8F64E0;
            sFileName.MakeUpper();
            if (pCharacters->Find(sFileName) != NULL) {
                LONG nCharacterId = pGame->ImportCharacter(CString(byte_8F64E0), m_nTopParty + m_nParty);
                if (nCharacterId != 0) {
                    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
                    // __LINE__: 3398
                    UTIL_ASSERT(pSettings != NULL);

                    pSettings->SignalCharacterStatus(nCharacterSlot,
                        CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_COMPLETE,
                        TRUE,
                        TRUE);
                    pGame->SetCharacterSlot(nCharacterSlot, nCharacterId);

                    nCharacters++;
                }
            }
        }
    }

    delete pCharacters;

    if (m_nParty == 10 && nCharacters > 0) {
        OnMainDoneButtonClick();
    }
}

// 0x6644B0
void CScreenSinglePlayer::ResetViewCharacterPanel(CUIPanel* pPanel)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3444
    UTIL_ASSERT(pGame != NULL);

    const CRuleTables& ruleTables = pGame->GetRuleTables();

    CString sName;
    CString v1; // NOTE: Unused.
    CString sRace;
    CString sGender;
    CString sAlignment;

    CUIControlTextDisplay* pTextLeft = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3457
    UTIL_ASSERT(pTextLeft != NULL);

    pTextLeft->RemoveAll();

    CUIControlTextDisplay* pTextRight = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3460
    UTIL_ASSERT(pTextRight != NULL);

    pTextRight->RemoveAll();

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    LONG nCharacterId = pGame->GetCharacterSlot(field_484);

    BOOL bSlotFull = pSettings->GetCharacterStatus(field_484) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX;

    if (!pSettings->m_bFirstConnected && bSlotFull) {
        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            CCreatureFileHeader* pBStats = pSprite->GetBaseStats();
            CAIObjectType& typeAI = pSprite->m_startTypeAI;

            // NOTE: Uninline.
            sName = pSprite->GetName();

            UpdateText(pTextLeft,
                "%s: %s",
                FetchString(1047), // "Name"
                sName);

            ruleTables.GetGenderStringMixed(typeAI.m_nGender, sGender);
            UpdateText(pTextLeft,
                "%s: %s",
                FetchString(12135), // "Gender"
                sGender);

            ruleTables.GetRaceStringMixed(typeAI.m_nRace, sRace, typeAI.m_nSubRace);
            UpdateText(pTextLeft,
                "%s: %s",
                FetchString(1048), // "Race"
                sRace);

            ruleTables.GetAlignmentStringMixed(typeAI.m_nAlignment, sAlignment);
            UpdateText(pTextLeft,
                "%s: %s",
                FetchString(1049), // "Alignment"
                sRace);

            // NOTE: Uninline.
            UpdateExperience(pTextLeft, pSprite);

            UpdateText(pTextLeft, "");

            UpdateTextForceColor(pTextLeft,
                RGB(200, 200, 0),
                "%s",
                FetchString(17088)); // "Abilities"

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1145), // "Strength"
                pBStats->m_STRBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_STRBase));

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1151), // "Dexterity"
                pBStats->m_DEXBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_DEXBase));

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1178), // "Constitution"
                pBStats->m_CONBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_CONBase));

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1179), // "Intelligence"
                pBStats->m_INTBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_INTBase));

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1180), // "Wisdom"
                pBStats->m_WISBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_WISBase));

            UpdateText(pTextLeft,
                "%s: %d  (%+d)",
                FetchString(1181), // "Charisma"
                pBStats->m_CHRBase,
                ruleTables.GetAbilityScoreModifier(pBStats->m_CHRBase));

            UpdateTextForceColor(pTextRight,
                RGB(200, 200, 0),
                "%s",
                FetchString(36361)); // "Feats"

            pSprite->DisplayFeats(pTextRight);

            UpdateText(pTextRight, "");

            UpdateTextForceColor(pTextRight,
                RGB(200, 200, 0),
                "%s",
                FetchString(11983)); // "Skills"

            pSprite->DisplaySkills(pTextRight);

            UpdateText(pTextRight, "");

            UpdateTextForceColor(pTextRight,
                RGB(200, 200, 0),
                "%s",
                FetchString(11292)); // "Inventory"

            for (INT nSlot = 0; nSlot < 51; nSlot++) {
                if (nSlot != 10) {
                    if (pSprite->m_equipment.m_items[nSlot] != NULL) {
                        STRREF strItem = pSprite->m_equipment.m_items[nSlot]->GetGenericName();
                        UpdateText(pTextRight,
                            "%s",
                            FetchString(strItem));
                    }
                }
            }

            if (pSprite->GetNumSpells() > 0) {
                for (UINT nClassIndex = 0; nClassIndex < CSPELLLIST_NUM_CLASSES; nClassIndex++) {
                    if (pSprite->m_spells.m_spellsByClass[nClassIndex].GetNumSpells() > 0) {
                        STRREF strRef;
                        switch (nClassIndex) {
                        case 0:
                            strRef = 39341; // "Known Bard Spells"
                            break;
                        case 1:
                            strRef = 11028; // "Known Cleric Spells"
                            break;
                        case 2:
                            strRef = 39342; // "Known Druid Spells"
                            break;
                        case 3:
                            strRef = 39343; // "Known Paladin Spells"
                            break;
                        case 4:
                            strRef = 39344; // "Known Ranger Spells"
                            break;
                        case 5:
                            strRef = 39345; // "Known Sorcerer Spells"
                            break;
                        case 6:
                            strRef = 11027; // "Known Wizard Spells"
                            break;
                        default:
                            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
                            // __LINE__: 3583
                            UTIL_ASSERT(FALSE);
                        }

                        UpdateText(pTextRight, "");

                        UpdateTextForceColor(pTextRight,
                            RGB(200, 200, 0),
                            "%s",
                            FetchString(strRef));

                        for (UINT nLevel = 0; nLevel < CSPELLLIST_MAX_LEVELS; nLevel++) {
                            // NOTE: Uninline.
                            CGameSpriteSpellList* pSpells = pSprite->m_spells.GetSpellsAtLevel(nClassIndex, nLevel);

                            for (size_t index = 0; index < pSpells->m_List.size(); index++) {
                                // NOTE: Uninline.
                                CGameSpriteSpellListEntry* pEntry = pSpells->Get(index);

                                // NOTE: Uninline.
                                const CResRef& resRef = g_pBaldurChitin->GetObjectGame()->m_spells.Get636(pEntry->m_nID);

                                CSpell cSpell;
                                cSpell.SetResRef(resRef, TRUE, TRUE);

                                if (cSpell.GetRes() != NULL) {
                                    cSpell.Demand();
                                    STRREF name = cSpell.GetGenericName();
                                    cSpell.Release();

                                    UpdateText(pTextRight,
                                        "%d: %s",
                                        nLevel + 1,
                                        FetchString(name));
                                }
                            }
                        }
                    }
                }
            }

            pTextLeft->SetTopString(pTextLeft->m_plstStrings->FindIndex(0));
            pTextRight->SetTopString(pTextRight->m_plstStrings->FindIndex(0));

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x665280
BOOL CScreenSinglePlayer::IsPortraitButtonClickable(INT nCharacterSlot)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3649
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);

    BOOL bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX;

    // NOTE: Unused.
    g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);

    return !pSettings->m_bFirstConnected
        && bSlotFull
        && pSettings->m_bArbitrationLockStatus;
}

// 0x665340
void CScreenSinglePlayer::OnPortraitButtonClick(INT nButton)
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    field_484 = nButton;
    SummonPopup(8);

    renderLock.Unlock();
}

// 0x6653D0
void CScreenSinglePlayer::OnLogoutButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    m_nErrorState = 4;
    m_dwErrorTextId = 11329;
    m_strErrorButtonText[0] = 13906;
    m_strErrorButtonText[1] = 13727;
    SummonPopup(7);

    renderLock.Unlock();
}

// 0x665470
void CScreenSinglePlayer::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3820
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3822
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x665580
CUIControlButtonSinglePlayerReady::CUIControlButtonSinglePlayerReady(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nPressedFrame = 2;
    m_nDisabledFrame = 3;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 0;
}

// 0x6655F0
CUIControlButtonSinglePlayerReady::~CUIControlButtonSinglePlayerReady()
{
}

// 0x665690
void CUIControlButtonSinglePlayerReady::OnLButtonClick(CPoint pt)
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3919
    UTIL_ASSERT(pSettings != NULL);

    pSettings->SetCharacterReady(m_nID, !pSettings->GetCharacterReady(m_nID), TRUE);
}

// 0x6656E0
CUIControlButtonSinglePlayerPortrait::CUIControlButtonSinglePlayerPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_portraitResRef = "";
}

// 0x665780
CUIControlButtonSinglePlayerPortrait::~CUIControlButtonSinglePlayerPortrait()
{
}

// 0x665820
BOOL CUIControlButtonSinglePlayerPortrait::Render(BOOL bForce)
{
    CVidBitmap vbPortrait;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    if (m_portraitResRef != "") {
        vbPortrait.SetResRef(m_portraitResRef, TRUE, FALSE);
        vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;

        if (vbPortrait.pRes == NULL) {
            vbPortrait.SetResRef(CInfGame::SILHOUETTE_PORTRAIT_SM, TRUE, FALSE);
            vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
        }

        // FIXME: Calls `GetBitCount` two times.
        if (vbPortrait.GetBitCount(FALSE) != 24 && vbPortrait.GetBitCount(FALSE) != 8) {
            vbPortrait.SetResRef(CInfGame::SILHOUETTE_PORTRAIT_SM, TRUE, FALSE);
            vbPortrait.m_bDoubleSize = m_pPanel->m_pManager->m_bDoubleSize;
        }

        CRect rControlRect;
        rControlRect.left = m_pPanel->m_ptOrigin.x + m_ptOrigin.x;
        rControlRect.top = m_pPanel->m_ptOrigin.y + m_ptOrigin.y;
        rControlRect.right = rControlRect.left + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        rControlRect.bottom = rControlRect.top + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        vbPortrait.RenderDirect(0, rControlRect.left, rControlRect.top, rClip, 0, FALSE);
    }

    return TRUE;
}

// 0x665AA0
void CUIControlButtonSinglePlayerPortrait::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4069
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnPortraitButtonClick(m_nID - 6);
}

// 0x64F930
void CUIControlButtonSinglePlayerPortrait::SetPortrait(const CResRef& resRef)
{
    if (m_portraitResRef != resRef) {
        m_portraitResRef = resRef;
        InvalidateRect();
    }
}

// 0x665AE0
CUIControlButtonSinglePlayerCharacter::CUIControlButtonSinglePlayerCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_cVidFont.SetResRef(CResRef("NORMAL"), panel->m_pManager->m_bDoubleSize, TRUE);
    m_cVidFont.SetColor(RGB(210, 210, 210), RGB(30, 30, 30), FALSE);
}

// 0x665BA0
CUIControlButtonSinglePlayerCharacter::~CUIControlButtonSinglePlayerCharacter()
{
}

// 0x665C40
void CUIControlButtonSinglePlayerCharacter::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4125
    UTIL_ASSERT(pSinglePlayer != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4127
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4129
    UTIL_ASSERT(pSettings != NULL);

    CSingleLock renderLock(&(pSinglePlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pSinglePlayer->field_458 = m_nID - 18;

    if (pSinglePlayer->field_45C == 1
        && g_pBaldurChitin->cNetwork.m_nLocalPlayer == pSettings->GetCharacterControlledByPlayer(pSinglePlayer->field_458)
        && CMultiplayerSettings::CHARSTATUS_NO_CHARACTER == pSettings->GetCharacterStatus(pSinglePlayer->field_458)) {
        CUIPanel* pPanel = pSinglePlayer->GetManager()->GetPanel(3);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 4147
        UTIL_ASSERT(pPanel != NULL);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
        // __LINE__: 4150
        UTIL_ASSERT(pButton != NULL);

        pButton->OnLButtonClick(CPoint(0, 0));
    } else {
        pSinglePlayer->SummonPopup(3);
    }

    renderLock.Unlock();
}

// 0x665E10
CUIControlButtonSinglePlayerDone::CUIControlButtonSinglePlayerDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x665F00
CUIControlButtonSinglePlayerDone::~CUIControlButtonSinglePlayerDone()
{
}

// 0x665FA0
void CUIControlButtonSinglePlayerDone::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4216
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnMainDoneButtonClick();
}

// 0x665FE0
CUIControlButtonSinglePlayerLogout::CUIControlButtonSinglePlayerLogout(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13906, strRes);
    SetText(strRes.szText);
}

// 0x6660D0
CUIControlButtonSinglePlayerLogout::~CUIControlButtonSinglePlayerLogout()
{
}

// 0x666170
void CUIControlButtonSinglePlayerLogout::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4272
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnLogoutButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6661B0
CUIControlEditSinglePlayerChat::CUIControlEditSinglePlayerChat(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, 0)
{
    field_8A0 = 0;
}

// 0x666200
CUIControlEditSinglePlayerChat::~CUIControlEditSinglePlayerChat()
{
}

// 0x6662D0
void CUIControlEditSinglePlayerChat::OnEditReturn(CString sText)
{
    g_pBaldurChitin->GetBaldurMessage()->SendChatMessage(sText);
    field_868 = "";
    SetText(CString(""));
}

// -----------------------------------------------------------------------------

// 0x666360
CUIControlButtonSinglePlayerModifyCharacterCreate::CUIControlButtonSinglePlayerModifyCharacterCreate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13954, strRes);
    SetText(strRes.szText);
}

// 0x666450
CUIControlButtonSinglePlayerModifyCharacterCreate::~CUIControlButtonSinglePlayerModifyCharacterCreate()
{
}

// 0x6664F0
void CUIControlButtonSinglePlayerModifyCharacterCreate::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4636
    UTIL_ASSERT(pSinglePlayer != NULL);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4638
    UTIL_ASSERT(pCreateChar != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4640
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4642
    UTIL_ASSERT(pSettings != NULL);

    CNetwork& cNetwork = g_pBaldurChitin->cNetwork;

    CSingleLock renderLock(&(pSinglePlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nCharacterSlot = pSinglePlayer->field_458;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4650
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    if (pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER) {
        pSettings->SignalCharacterStatus(nCharacterSlot,
            CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_START,
            TRUE,
            TRUE);

        INT nLocalPlayer = cNetwork.m_nLocalPlayer;
        INT nHostPlayer = cNetwork.m_nHostPlayer;
        CString sPlayerName;

        if (nHostPlayer != -1) {
            sPlayerName = cNetwork.m_psPlayerName[nHostPlayer];
        } else {
            sPlayerName = "";
        }

        while (pSettings->GetCharacterControlledByPlayer(nCharacterSlot) == nLocalPlayer
            && pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER) {
            while (g_pChitin->cNetwork.PeekSpecificMessage(sPlayerName, CBaldurMessage::MSG_TYPE_MPSETTINGS, CBaldurMessage::MSG_SUBTYPE_MPSETTINGS_FULLSET) == TRUE) {
                g_pBaldurChitin->GetBaldurMessage()->HandleBlockingMessages();

                DWORD dwSize;
                BYTE* pData = g_pChitin->cNetwork.FetchSpecificMessage(sPlayerName,
                    CBaldurMessage::MSG_TYPE_MPSETTINGS,
                    CBaldurMessage::MSG_SUBTYPE_MPSETTINGS_FULLSET,
                    dwSize);
                g_pBaldurChitin->GetBaldurMessage()->OnSettingsFullSet(nHostPlayer, pData, dwSize);
                delete pData;
            }

            if (g_pChitin->cNetwork.GetSessionOpen() != TRUE) {
                break;
            }

            g_pChitin->m_bDisplayStale = TRUE;
            Sleep(60);
        }

        if (pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER) {
            renderLock.Unlock();

            if (pSinglePlayer->GetTopPopup() != NULL) {
                pSinglePlayer->OnDoneButtonClick();
            }

            pCreateChar->StartCreateChar(nCharacterSlot, 3);
            pSinglePlayer->SelectEngine(pCreateChar);

            renderLock.Lock();
        }
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x666850
CUIControlButtonSinglePlayerModifyCharacterDelete::CUIControlButtonSinglePlayerModifyCharacterDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13957, strRes);
    SetText(strRes.szText);
}

// 0x666940
CUIControlButtonSinglePlayerModifyCharacterDelete::~CUIControlButtonSinglePlayerModifyCharacterDelete()
{
}

// 0x6669E0
void CUIControlButtonSinglePlayerModifyCharacterDelete::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4764
    UTIL_ASSERT(pSinglePlayer != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4766
    UTIL_ASSERT(pGame != NULL);

    CNetwork& cNetwork = g_pBaldurChitin->cNetwork;

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4769
    UTIL_ASSERT(pSettings != NULL);

    CSingleLock renderLock(&(pSinglePlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nCharacterSlot = pSinglePlayer->field_458;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4778
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);

    if (pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX) {
        pSettings->SignalCharacterStatus(nCharacterSlot,
            CMultiplayerSettings::CHARSTATUS_SIGNAL_DELETED,
            TRUE,
            TRUE);

        INT nLocalPlayer = cNetwork.m_nLocalPlayer;
        INT nHostPlayer = cNetwork.m_nHostPlayer;
        CString sPlayerName;

        if (nHostPlayer != -1) {
            sPlayerName = cNetwork.m_psPlayerName[nHostPlayer];
        } else {
            sPlayerName = "";
        }

        while (pSettings->GetCharacterControlledByPlayer(nCharacterSlot) == nLocalPlayer
            && pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER) {
            while (g_pChitin->cNetwork.PeekSpecificMessage(sPlayerName, CBaldurMessage::MSG_TYPE_MPSETTINGS, CBaldurMessage::MSG_SUBTYPE_MPSETTINGS_FULLSET) == TRUE) {
                g_pBaldurChitin->GetBaldurMessage()->HandleBlockingMessages();

                DWORD dwSize;
                BYTE* pData = g_pChitin->cNetwork.FetchSpecificMessage(sPlayerName,
                    CBaldurMessage::MSG_TYPE_MPSETTINGS,
                    CBaldurMessage::MSG_SUBTYPE_MPSETTINGS_FULLSET,
                    dwSize);
                g_pBaldurChitin->GetBaldurMessage()->OnSettingsFullSet(nHostPlayer, pData, dwSize);
                delete pData;
            }

            if (g_pChitin->cNetwork.GetSessionOpen() != TRUE) {
                break;
            }

            g_pChitin->m_bDisplayStale = TRUE;
            Sleep(60);
        }

        if (pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER) {
            renderLock.Unlock();

            pSinglePlayer->OnDoneButtonClick();

            if (nCharacterSlot == 0) {
                pGame->sub_5BDBA0(-1, FALSE);
            }

            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                CMessagePartyGold* pPartyGold = new CMessagePartyGold(TRUE,
                    TRUE,
                    -static_cast<LONG>(pSprite->GetBaseStats()->m_gold),
                    nCharacterId,
                    nCharacterId);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(pPartyGold, FALSE);

                pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }

            pGame->ClearCharacterSlot(nCharacterSlot);

            do {
                rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }

            if (pGame->GetObjectArray()->Delete(nCharacterId, CGameObjectArray::THREAD_ASYNCH, NULL, INFINITE) == CGameObjectArray::SUCCESS) {
                delete pSprite;
            }

            renderLock.Lock(INFINITE);
        }
    }

    renderLock.Unlock();
}

// 0x666E50
CUIControlButtonSinglePlayerModifyCharacterCancel::CUIControlButtonSinglePlayerModifyCharacterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x666F40
CUIControlButtonSinglePlayerModifyCharacterCancel::~CUIControlButtonSinglePlayerModifyCharacterCancel()
{
}

// 0x666FE0
void CUIControlButtonSinglePlayerModifyCharacterCancel::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 4934
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnCancelButtonClick();
}

// 0x667020
CUIControlButtonSinglePlayerModify::CUIControlButtonSinglePlayerModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(18816, strRes);
    SetText(strRes.szText);
}

// 0x667110
CUIControlButtonSinglePlayerModify::~CUIControlButtonSinglePlayerModify()
{
}

// 0x6671B0
void CUIControlButtonSinglePlayerModify::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5120
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnModifyButtonClick();
}

// 0x6671F0
CUIControlButtonSinglePlayerError::CUIControlButtonSinglePlayerError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x667240
CUIControlButtonSinglePlayerError::~CUIControlButtonSinglePlayerError()
{
}

// 0x6672E0
void CUIControlButtonSinglePlayerError::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5172
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnErrorButtonClick(m_nID - 1);
}

// 0x667320
CUIControlButtonSinglePlayerViewCharacterDone::CUIControlButtonSinglePlayerViewCharacterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5201
    UTIL_ASSERT(pSinglePlayer != NULL);

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x6673F0
CUIControlButtonSinglePlayerViewCharacterDone::~CUIControlButtonSinglePlayerViewCharacterDone()
{
}

// 0x667490
void CUIControlButtonSinglePlayerViewCharacterDone::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5228
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->OnDoneButtonClick();
}

// 0x6674D0
CUIControlButtonSinglePlayerPartyCancel::CUIControlButtonSinglePlayerPartyCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x6675C0
CUIControlButtonSinglePlayerPartyCancel::~CUIControlButtonSinglePlayerPartyCancel()
{
}

// 0x667660
void CUIControlButtonSinglePlayerPartyCancel::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5313
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nErrorState = 4;
    pSinglePlayer->OnErrorButtonClick(0);
}

// 0x6676A0
CUIControlButtonSinglePlayerPartyDone::CUIControlButtonSinglePlayerPartyDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5327
    UTIL_ASSERT(pSinglePlayer != NULL);

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x667770
CUIControlButtonSinglePlayerPartyDone::~CUIControlButtonSinglePlayerPartyDone()
{
}

// 0x667810
void CUIControlButtonSinglePlayerPartyDone::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5336
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_139E = m_nID;
    pSinglePlayer->OnDoneButtonClick();
}

// 0x667850
CUIControlButtonSinglePlayerPartyModify::CUIControlButtonSinglePlayerPartyModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5348
    UTIL_ASSERT(pSinglePlayer != NULL);

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(10316, strRes);
    SetText(strRes.szText);
}

// 0x667920
CUIControlButtonSinglePlayerPartyModify::~CUIControlButtonSinglePlayerPartyModify()
{
}

// 0x667810
void CUIControlButtonSinglePlayerPartyModify::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5357
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_139E = m_nID;
    pSinglePlayer->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x667A00
CUIControlButtonSinglePlayerPartySelection::CUIControlButtonSinglePlayerPartySelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nSelectedFrame = 0;
}

// 0x667A60
CUIControlButtonSinglePlayerPartySelection::~CUIControlButtonSinglePlayerPartySelection()
{
}

// 0x667B00
void CUIControlButtonSinglePlayerPartySelection::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5376
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nParty = m_nID;
}

// -----------------------------------------------------------------------------

// 0x667B50
CUIControlScrollBarSinglePlayerParties::CUIControlScrollBarSinglePlayerParties(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarSinglePlayerParties::~CUIControlScrollBarSinglePlayerParties()
{
}

// NOTE: Inlined.
void CUIControlScrollBarSinglePlayerParties::UpdateScrollBar()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenCreateChar.cpp
    // __LINE__: 11289
    UTIL_ASSERT(pSinglePlayer != NULL);

    AdjustScrollBar(pSinglePlayer->m_nTopParty, pSinglePlayer->m_nPartyCount, 6);
}

// 0x667B70
void CUIControlScrollBarSinglePlayerParties::OnScrollUp()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5404
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nTopParty--;
    InvalidateItems();
}

// 0x667BC0
void CUIControlScrollBarSinglePlayerParties::OnScrollDown()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5415
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nTopParty++;
    InvalidateItems();
}

// 0x667C10
void CUIControlScrollBarSinglePlayerParties::OnPageUp(DWORD nLines)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5426
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nTopParty -= min(nLines, 5);
    InvalidateItems();
}

// 0x667C60
void CUIControlScrollBarSinglePlayerParties::OnPageDown(DWORD nLines)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5441
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nTopParty += min(nLines, 5);
    InvalidateItems();
}

// 0x667CB0
void CUIControlScrollBarSinglePlayerParties::OnScroll()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5456
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nTopParty = max(pSinglePlayer->m_nPartyCount * field_144, 0) / field_142;
    InvalidateItems();
}

// 0x667D10
void CUIControlScrollBarSinglePlayerParties::InvalidateItems()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5469
    UTIL_ASSERT(pSinglePlayer != NULL);

    CSingleLock renderLock(&(pSinglePlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pSinglePlayer->m_nTopParty = max(min(pSinglePlayer->m_nTopParty, pSinglePlayer->m_nPartyCount - 6), 0);

    // NOTE: Uninline.
    pSinglePlayer->UpdatePopupPanel(m_pPanel->m_nID);

    renderLock.Unlock();
}

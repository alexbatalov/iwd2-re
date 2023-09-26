#include "CScreenMultiPlayer.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CMessage.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
#include "CUIControlButton.h"
#include "CUIControlEdit.h"
#include "CUIControlFactory.h"
#include "CUIControlLabel.h"
#include "CUIControlScrollBar.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F5874
const CString CScreenMultiPlayer::TOKEN_GOLD("GOLD");

// 0x6481C0
CScreenMultiPlayer::CScreenMultiPlayer()
{
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    m_nKickPlayerSlot = 0;
    m_nCharacterSlot = 0;

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
    field_464 = 0;
    m_bMultiplayerStartup = 0;
    m_bLastLockAllowInput = FALSE;
    field_138E = 0;
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x660730
BOOL CScreenMultiPlayer::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x660740
void CScreenMultiPlayer::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x660750
void CScreenMultiPlayer::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x660770
void CScreenMultiPlayer::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x660780
BOOL CScreenMultiPlayer::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenMultiPlayer::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenMultiPlayer::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenMultiPlayer::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenMultiPlayer::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenMultiPlayer::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenMultiPlayer::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenMultiPlayer::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x699600
SHORT CScreenMultiPlayer::GetNumVirtualKeys()
{
    return CSCREENMULTIPLAYER_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenMultiPlayer::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x699620
BYTE* CScreenMultiPlayer::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x648E30
CScreenMultiPlayer::~CScreenMultiPlayer()
{
}

// 0x648ED0
void CScreenMultiPlayer::EngineActivated()
{
    CUIPanel* pPanel;
    CUIControlTextDisplay* pText;

    CChatBuffer* pChatBuffer = &(g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer);

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    CheckEnableCharacters();

    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
    m_cUIManager.InvalidateRect(NULL);

    pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 323
    UTIL_ASSERT(pPanel != NULL);

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 325
    UTIL_ASSERT(pText != NULL);

    field_460 = pChatBuffer->UpdateTextDisplay(pText, field_460);
    pText->ScrollToBottom();

    pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 331
    UTIL_ASSERT(pPanel != NULL);

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(72));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 333
    UTIL_ASSERT(pText != NULL);

    field_464 = pChatBuffer->UpdateTextDisplay(pText, field_464);
    pText->ScrollToBottom();
}

// 0x649080
void CScreenMultiPlayer::EngineDeactivated()
{
    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.GetSectionPlaying();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.GetMusicPosition();
}

// 0x6490F0
void CScreenMultiPlayer::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUIMP"), g_pBaldurChitin->field_4A28);

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

    m_pCurrentScrollBar = NULL;

    m_cUIManager.GetPanel(1)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(9)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 452
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    SetPermissionToolTips(pPanel, 64, 13, 18, 17565);
    SetPermissionToolTips(pPanel, 65, 19, 24, 17566);
    SetPermissionToolTips(pPanel, 66, 25, 30, 17567);
    SetPermissionToolTips(pPanel, 67, 31, 36, 17568);
    SetPermissionToolTips(pPanel, 68, 37, 42, 17569);
    SetPermissionToolTips(pPanel, 69, 49, 54, 17570);
    SetPermissionToolTips(pPanel, 70, 55, 60, 17571);
    SetPermissionToolTips(pPanel, -1, 0, 5, 17564);

    CUIPanel* pPanel0 = m_cUIManager.GetPanel(0);
    CUIPanel* pPanel4_1 = m_cUIManager.GetPanel(4);

    for (int v1 = 0; v1 < 6; v1++) {
        CUIControlLabel* pLabel;
        CUIControlButton* pButton;

        pLabel = static_cast<CUIControlLabel*>(pPanel0->GetControl(v1 + 12 + 0x10000012));
        pLabel->m_nTextFlags &= ~CUIControlLabel::TYPE_WORD_WRAP;

        pButton = static_cast<CUIControlButton*>(pPanel0->GetControl(v1 + 12));
        pButton->m_nTextFlags &= ~CUIControlButton::TYPE_WORD_WRAP;

        pButton = static_cast<CUIControlButton*>(pPanel4_1->GetControl(v1));
        pButton->m_nTextFlags &= ~CUIControlButton::TYPE_WORD_WRAP;
    }

    // FIXME: Unused.
    CUIPanel* pPanel9 = m_cUIManager.GetPanel(9);

    // FIXME: Obtains same panel second time.
    CUIPanel* pPanel4_2 = m_cUIManager.GetPanel(4);

    // NOTE: Looks like this whole loop is not needed as word wrap flag has
    // been removed in the loop above.
    for (int v2 = 0; v2 < 6; v2++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel4_2->GetControl(v2));
        pButton->m_nTextFlags &= ~CUIControlButton::TYPE_WORD_WRAP;
    }
}

// 0x649700
void CScreenMultiPlayer::OnKeyDown(SHORT nKeysFlags)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 593
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
                        if (g_pBaldurChitin->field_1A0) {
                            // FIXME: Unused.
                            g_pChitin->GetWnd();
                            if (g_pBaldurChitin->cImm.field_128) {
                                m_cUIManager.OnKeyDown(VK_RETURN);
                                break;
                            }
                        }
                        OnDoneButtonClick();
                    } else {
                        if (g_pBaldurChitin->field_1A0) {
                            // FIXME: Unused.
                            g_pChitin->GetWnd();
                            if (g_pBaldurChitin->cImm.field_128) {
                                m_cUIManager.OnKeyDown(VK_RETURN);
                                break;
                            }
                        }
                        OnMainDoneButtonClick();
                    }
                    break;
                case VK_ESCAPE:
                    if (GetTopPopup() != NULL) {
                        OnCancelButtonClick();
                    } else {
                        switch (field_45C) {
                        case 1:
                            break;
                        case 2:
                            SelectEngine(g_pBaldurChitin->m_pEngineWorld);
                            break;
                        default:
                            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
                            // __LINE__: 3288
                            UTIL_ASSERT(FALSE);
                        }
                    }
                    break;
                case VK_SNAPSHOT:
                    g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                    break;
                default:
                    for (SHORT index = 0; index < CINFGAME_KEYMAP_SIZE; index) {
                        if (pGame->m_pKeymap[index] == m_pVirtualKeysFlags[nKeyFlag]
                            && pGame->m_pKeymapFlags[index] == m_bCtrlKeyDown) {
                            switch (index) {
                            case 24:
                                FocusChatEditBox();
                                break;
                            default:
                                break;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
}

// 0x649990
void CScreenMultiPlayer::TimerAsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x64A110
void CScreenMultiPlayer::TimerSynchronousUpdate()
{
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x64A130
void CScreenMultiPlayer::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1225
    UTIL_ASSERT(pPanel != NULL);

    CheckEnableCharacters();

    CChatBuffer* pChatBuffer = &(g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer);

    switch (dwPanelId) {
    case 1:
        if (1) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(72));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
            // __LINE__: 1235
            UTIL_ASSERT(pText != NULL);

            field_464 = pChatBuffer->UpdateTextDisplay(pText, field_464);
        }
        break;
    case 2:
        UpdateHelp(pPanel->m_nID, 14, 11323);
        break;
    case 3:
    case 4:
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1260
        UTIL_ASSERT(FALSE);
    }
}

// 0x661480
CUIPanel* CScreenMultiPlayer::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenMultiPlayer::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
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
void CScreenMultiPlayer::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1198
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Uninline.
void CScreenMultiPlayer::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 1:
        UpdatePermissionsPanel();
        break;
    case 2:
        UpdateOptionsPanel();
        break;
    case 3:
        UpdateModifyCharacterPanel();
        break;
    case 4:
        UpdateModifyPlayerPanel();
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1314
        UTIL_ASSERT(FALSE);
    }
}
// 0x64A270
void CScreenMultiPlayer::SummonPopup(DWORD dwPopupId)
{
    CUIPanel* pOldPanel = GetTopPopup();
    if (pOldPanel == NULL) {
        pOldPanel = m_cUIManager.GetPanel(0);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1379
    UTIL_ASSERT(pOldPanel != NULL);

    CopyChatEditBox(pOldPanel, m_cUIManager.GetPanel(dwPopupId));

    if (m_cUIManager.m_pFocusedControl != NULL
        && m_cUIManager.m_pFocusedControl->m_pPanel == pOldPanel) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
    }

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1401
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1407
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

// 0x64A4B0
void CScreenMultiPlayer::DismissPopup()
{
    CUIPanel* pOldPanel = GetTopPopup();

    if (pOldPanel == NULL) {
        pOldPanel = m_cUIManager.GetPanel(0);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1444
    UTIL_ASSERT(pOldPanel != NULL);

    CUIPanel* pNewPanel = m_lPopupStack.GetCount() - 2 >= 0
        ? m_lPopupStack.GetAt(m_lPopupStack.FindIndex(m_lPopupStack.GetCount() - 2))
        : m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1453
    UTIL_ASSERT(pNewPanel != NULL);

    CopyChatEditBox(pOldPanel, pNewPanel);

    if (m_cUIManager.m_pFocusedControl != NULL
        && m_cUIManager.m_pFocusedControl->m_pPanel == pOldPanel) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1466
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1483
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

    if (g_pBaldurChitin->field_1A0) {
        // FIXME: Unused.
        g_pChitin->GetWnd();

        if (g_pBaldurChitin->cImm.field_128) {
            g_pBaldurChitin->cImm.sub_7C2E10(g_pChitin->GetWnd()->GetSafeHwnd());
        }
    }
}

// 0x64A750
BOOL CScreenMultiPlayer::IsMainDoneButtonClickable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1524
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1526
    UTIL_ASSERT(pSettings != NULL);

    BOOL bResult;
    switch (field_45C) {
    case 1:
        bResult = !pSettings->m_bFirstConnected;

        for (INT nPlayer = 0; nPlayer < 6; nPlayer++) {
            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && g_pChitin->cNetwork.GetRawPlayerID(nPlayer) != 0
                && !pSettings->GetPlayerReady(static_cast<SHORT>(nPlayer))) {
                bResult = FALSE;
            }
        }

        for (INT nCharacter = 0; nCharacter < 6; nCharacter++) {
            if (pSettings->GetCharacterStatus(nCharacter) == CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER) {
                bResult = FALSE;
            }

            if (pGame->GetCharacterSlot(nCharacter) != CGameObjectArray::INVALID_INDEX
                && !pSettings->GetCharacterReady(nCharacter)) {
                bResult = g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL;
            }
        }

        if (!g_pBaldurChitin->cNetwork.GetSessionHosting()
            && pSettings->m_bArbitrationLockStatus == TRUE) {
            bResult = FALSE;
        }

        if (pGame->GetCharacterSlot(0) == CGameObjectArray::INVALID_INDEX) {
            bResult = FALSE;
        }

        break;
    case 2:
        bResult = TRUE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1592
        UTIL_ASSERT(FALSE);
    }

    return bResult;
}

// 0x64A8B0
void CScreenMultiPlayer::OnDoneButtonClick()
{
    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1622
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
    case 9:
        break;
    case 1:
    case 2:
        g_pBaldurChitin->GetObjectGame()->SaveMultiPlayerPermissions();
        DismissPopup();
        break;
    case 3:
    case 4:
    case 8:
        DismissPopup();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1671
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x64AA10
void CScreenMultiPlayer::OnCancelButtonClick()
{
    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1702
    UTIL_ASSERT(pPanel != NULL);

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (pPanel->m_nID) {
    case 0:
    case 9:
        break;
    case 1:
    case 2:
        g_pBaldurChitin->GetObjectGame()->SaveMultiPlayerPermissions();
        DismissPopup();
        break;
    case 3:
    case 4:
    case 8:
        DismissPopup();
        break;
    case 5:
    case 7:
        DismissPopup();
        break;
    case 6:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1745
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x64AB40
void CScreenMultiPlayer::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1776
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

        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 1793
        UTIL_ASSERT(pPanel != NULL);

        field_460 = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(pText, field_460);

        pText->ScrollToBottom();
    }
}

// 0x64AC60
void CScreenMultiPlayer::UpdateOptionsPanel()
{
    CUIControlButton3State* pButton;

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1822
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(15));

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1827
    UTIL_ASSERT(pSettings != NULL);

    DWORD nSelectedButtonID;

    switch (pSettings->m_nImportingBitField) {
    case 1:
        nSelectedButtonID = 4;
        break;
    case 3:
        nSelectedButtonID = 3;
        break;
    case 7:
        nSelectedButtonID = 2;
        break;
    default:
        nSelectedButtonID = -1;
        break;
    }

    INT nPlayerNumber = g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);
    BOOLEAN bLeader = pSettings->GetPermission(nPlayerNumber, CGamePermission::LEADER);
    BOOLEAN bIsHost = g_pBaldurChitin->cNetwork.GetSessionHosting();
    for (DWORD nButtonID = 2; nButtonID <= 4; nButtonID++) {
        pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));
        pButton->SetEnabled(bIsHost || bLeader);
        pButton->SetSelected(nButtonID == nSelectedButtonID);
    }

    pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(18));
    pButton->SetEnabled(bIsHost || bLeader);
    pButton->SetSelected(pSettings->m_bRestrictStoreOption);
}

// 0x64ADB0
void CScreenMultiPlayer::UpdateMainPanel()
{
    CUIControlButton* pButton;
    CUIControlTextDisplay* pText;
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1901
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(26));

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        UpdateMainPanelCharacter(pPanel, nCharacterSlot);
    }

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1911
    UTIL_ASSERT(pSettings != NULL);

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1919
    UTIL_ASSERT(pText != NULL);

    field_460 = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(pText, field_460);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(29));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1925
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(!pSettings->m_bFirstConnected
        && pSettings->m_bArbitrationLockAllowInput);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(43));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 13930
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsModifyButtonClickable());

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(28));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1936
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsMainDoneButtonClickable());
}

// 0x64AF40
void CScreenMultiPlayer::CheckEnableCharacters()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 1969
    UTIL_ASSERT(pPanel != NULL);

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        CUIControlButton* pButton;
        CUIControlLabel* pLabel;

        BOOL bReadyActive;
        BOOL bModifyPlayerActive;
        BOOL bModifyCharacterActive;
        CheckCharacterButtons(nCharacterSlot, bReadyActive, bModifyPlayerActive, bModifyCharacterActive);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nCharacterSlot));
        pButton->SetActive(bReadyActive);
        pButton->SetInactiveRender(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nCharacterSlot + 12));
        pButton->SetActive(bModifyPlayerActive);
        pButton->SetInactiveRender(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nCharacterSlot + 18));
        pButton->SetActive(bModifyCharacterActive);
        pButton->SetInactiveRender(TRUE);

        pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nCharacterSlot + 0x10000024));
        pLabel->SetActive(!bModifyCharacterActive);
        pLabel->SetInactiveRender(!bModifyCharacterActive);
    }
}

// 0x64B090
void CScreenMultiPlayer::CheckCharacterButtons(INT nCharacterSlot, BOOL& bReadyActive, BOOL& bModifyPlayerActive, BOOL& bModifyCharacterActive)
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2031
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2034
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2036
    UTIL_ASSERT(pSettings != NULL);

    LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);
    BOOL bSlotFree = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_NO_CHARACTER;
    BOOL bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX;
    BOOL bSlotLoading = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId == CGameObjectArray::INVALID_INDEX;
    BOOL bSlotCreating = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER;

    INT nPlayerSlot = pSettings->GetCharacterControlledByPlayer(nCharacterSlot);
    if (nPlayerSlot == -1) {
        nPlayerSlot = 0;
    }

    PLAYER_ID idPlayer = pNetwork->GetPlayerID(nPlayerSlot);
    INT nLocalPlayer = pNetwork->FindPlayerLocationByID(pNetwork->m_idLocalPlayer, FALSE);
    BOOL bLeader = nLocalPlayer != -1
        ? pSettings->GetPermission(nLocalPlayer, CGamePermission::LEADER)
        : FALSE;
    BOOL bIsHost = pNetwork->GetSessionHosting();
    BOOLEAN bCharacterReady = pSettings->GetCharacterReady(nCharacterSlot);
    BOOL bIsLocalPlayer = idPlayer != 0 && idPlayer == pNetwork->m_idLocalPlayer;

    switch (field_45C) {
    case 1:
        bReadyActive = bIsLocalPlayer
            && bSlotFull
            && pSettings->m_bArbitrationLockAllowInput;
        bModifyPlayerActive = (bLeader || bIsHost)
            && (bSlotFull || bSlotFree)
            && pSettings->m_bArbitrationLockAllowInput;
        bModifyCharacterActive = bIsLocalPlayer
            && !bCharacterReady
            && !bSlotLoading
            && !bSlotCreating
            && pSettings->m_bArbitrationLockAllowInput;
        break;
    case 2:
        bReadyActive = FALSE;
        bModifyPlayerActive = (bLeader || bIsHost) && bSlotFull;
        bModifyCharacterActive = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 2087
        UTIL_ASSERT(FALSE);
    }
}

// 0x64B340
void CScreenMultiPlayer::UpdateMainPanelCharacter(CUIPanel* pPanel, INT nCharacterSlot)
{
    // TODO: Incomplete.
}

// 0x64BCF0
void CScreenMultiPlayer::UpdatePermissionsPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2378
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(73));

    for (INT nPlayerSlot = 0; nPlayerSlot < CINFGAME_MAXCHARACTERS; nPlayerSlot++) {
        UpdatePermissionsPanelPlayer(pPanel, nPlayerSlot);
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(72));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2389
    UTIL_ASSERT(pText != NULL);

    field_464 = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(pText, field_464);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2395
    UTIL_ASSERT(pSettings != NULL);

    INT nLocalPlayer = g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);
    BOOLEAN bLeader = pSettings->GetPermission(nLocalPlayer, CGamePermission::LEADER);
    BOOLEAN bIsHost = g_pBaldurChitin->cNetwork.GetSessionHosting();

    CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(61));
    pButton->SetEnabled(bLeader || bIsHost);
    pButton->SetSelected(pSettings->GetListenToJoinOption());
}

// 0x64BE30
void CScreenMultiPlayer::UpdatePermissionsPanelPlayer(CUIPanel* pPanel, INT nPlayerSlot)
{
    // FIXME: Unused
    CString v1;

    CString sPlayerName;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2438
    UTIL_ASSERT(0 <= nPlayerSlot && nPlayerSlot < CINFGAME_MAXCHARACTERS);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2439
    UTIL_ASSERT(pPanel != NULL);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2443
    UTIL_ASSERT(pPanel != NULL);

    INT nLocalPlayer = g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);

    BOOLEAN bLeader = pSettings->GetPermission(nLocalPlayer, CGamePermission::LEADER);
    BOOLEAN bIsHost = g_pBaldurChitin->cNetwork.GetSessionHosting();
    PLAYER_ID idPlayer = g_pBaldurChitin->cNetwork.GetPlayerID(nPlayerSlot);

    // TODO: Unclear.
    BOOL bEnabled = bIsHost || bLeader;

    // TODO: Unclear.
    BOOL bPortraitEnabled = (bIsHost || bLeader)
        && nLocalPlayer != nPlayerSlot
        && g_pBaldurChitin->cNetwork.GetHostPlayerID() != idPlayer;

    CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nPlayerSlot + 0x10000005));
    g_pBaldurChitin->cNetwork.GetPlayerName(nPlayerSlot, sPlayerName);
    pLabel->SetText(sPlayerName);

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nPlayerSlot));
    pButton->SetEnabled(bPortraitEnabled);

    BOOL bPermission;

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::PURCHASING);
    UpdatePermission(pPanel, nPlayerSlot + 19, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::AREA_TRANSITION);
    UpdatePermission(pPanel, nPlayerSlot + 25, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::DIALOG);
    UpdatePermission(pPanel, nPlayerSlot + 31, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::CHAR_RECORDS);
    UpdatePermission(pPanel, nPlayerSlot + 37, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::PAUSING);
    UpdatePermission(pPanel, nPlayerSlot + 49, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::LEADER);
    UpdatePermission(pPanel, nPlayerSlot + 55, bEnabled, bPermission);

    bPermission = pSettings->GetPermission(nPlayerSlot, CGamePermission::MODIFY_CHARS);
    UpdatePermission(pPanel, nPlayerSlot + 13, bEnabled, bPermission);
}

// 0x64C210
void CScreenMultiPlayer::UpdateModifyPlayerPanel()
{
    // FIXME: Unused.
    CString v1;

    CString sPlayerName;

    CUIPanel* pPanel = m_cUIManager.GetPanel(4);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2549
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2553
    UTIL_ASSERT(pSettings != NULL);

    BOOL bLeader = pSettings->GetPermission(g_pBaldurChitin->cNetwork.m_nLocalPlayer, CGamePermission::LEADER);
    BOOL bIsHost = g_pBaldurChitin->cNetwork.GetSessionHosting();

    for (INT nPlayerNumber = 0; nPlayerNumber < 6; nPlayerNumber++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nPlayerNumber));

        BOOL bWasActive = pButton->m_bActive;
        BOOL bActive = g_pBaldurChitin->cNetwork.GetPlayerID(nPlayerNumber) != 0;
        g_pBaldurChitin->cNetwork.GetPlayerName(nPlayerNumber, sPlayerName);

        pButton->SetText(sPlayerName);
        pButton->SetActive(bActive);
        pButton->SetInactiveRender(bActive);

        if (bActive != bWasActive) {
            pButton->InvalidateRect();
        }

        if (bActive) {
            pButton->SetEnabled(bLeader || bIsHost);
        }
    }
}

// 0x64C3B0
void CScreenMultiPlayer::UpdateModifyCharacterPanel()
{
    // FIXME: Unused.
    CString v1;
    CString v2;

    CUIControlButton* pButton;

    CUIPanel* pPanel = m_cUIManager.GetPanel(3);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2618
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2621
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2623
    UTIL_ASSERT(pSettings != NULL);

    INT nCharacterSlot = field_458;
    BYTE nLocalPlayer = static_cast<BYTE>(g_pBaldurChitin->cNetwork.m_nLocalPlayer);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2628
    UTIL_ASSERT(0 <= nCharacterSlot && nCharacterSlot < CINFGAME_MAXCHARACTERS);

    BOOL bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && pGame->GetCharacterSlot(nCharacterSlot) != CGameObjectArray::INVALID_INDEX;

    BOOL bSlotFree = CMultiplayerSettings::CHARSTATUS_NO_CHARACTER == pSettings->GetCharacterStatus(nCharacterSlot);
    BOOL bIsLocalPlayer = nLocalPlayer == pSettings->GetCharacterControlledByPlayer(nCharacterSlot);
    BOOL bModifyChars = pGame->m_singlePlayerPermissions.GetSinglePermission(CGamePermission::MODIFY_CHARS);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2638
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(field_45C == 1
        && bModifyChars
        && bIsLocalPlayer
        && bSlotFree);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 2642
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(field_45C == 1
        && bModifyChars
        && bIsLocalPlayer
        && bSlotFull);
}

// 0x64C600
void CScreenMultiPlayer::OnMainDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x64D690
void CScreenMultiPlayer::ClearChatMessages()
{
    CUIPanel* pPanel;
    CUIControlTextDisplay* pText;

    pPanel = m_cUIManager.GetPanel(0);
    if (pPanel != NULL) {
        pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3323
        UTIL_ASSERT(pText != NULL);

        pText->RemoveAll();
    }

    field_460 = 0;

    pPanel = m_cUIManager.GetPanel(1);
    if (pPanel != NULL) {
        pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(72));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3333
        UTIL_ASSERT(pText != NULL);

        pText->RemoveAll();
    }

    field_464 = 0;
}

// 0x64D730
BOOL CScreenMultiPlayer::IsModifyButtonClickable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3405
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    if (pSettings->m_bFirstConnected) {
        return FALSE;
    }

    INT nPlayerNumber = g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);
    if ((nPlayerNumber == -1 || !pSettings->GetPermission(nPlayerNumber, CGamePermission::LEADER))
        && !g_pBaldurChitin->cNetwork.GetSessionHosting()) {
        return FALSE;
    }

    if (field_45C != 2) {
        return FALSE;
    }

    if (!pSettings->m_bArbitrationLockAllowInput) {
        return FALSE;
    }

    return TRUE;
}

// 0x64D7F0
void CScreenMultiPlayer::OnModifyButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3459
    UTIL_ASSERT(pGame != NULL);

    if (IsModifyButtonClickable()) {
        CSingleLock renderLock(&(GetManager()->field_36), FALSE);
        renderLock.Lock(INFINITE);

        m_nErrorState = 2;
        m_dwErrorTextId = 101317;
        m_strErrorButtonText[0] = 10316;
        m_strErrorButtonText[1] = 13727;
        SummonPopup(7);

        renderLock.Unlock();
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

// 0x663810
void CScreenMultiPlayer::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// 0x64D970
void CScreenMultiPlayer::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3611
    UTIL_ASSERT(0 <= nButton && nButton < CSCREENMULTIPLAYER_ERROR_BUTTONS);

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
                g_pBaldurChitin->cNetwork.GetPlayerName(m_nKickPlayerSlot, sPlayerName);
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
            DismissPopup();
            g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;
            SelectEngine(g_pBaldurChitin->m_pEngineStart);
            g_pChitin->cNetwork.CloseSession(TRUE);
            g_pBaldurChitin->m_pEngineConnection->SetEliminateInitialize(TRUE);
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    }

    renderLock.Unlock();
}

// 0x64DB90
void CScreenMultiPlayer::ResetErrorPanel(CUIPanel* pPanel)
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
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3734
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3747
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3756
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3585
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENMULTIPLAYER_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x64DDB0
void CScreenMultiPlayer::StartMultiPlayer(INT nEngineState)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3784
    UTIL_ASSERT(pPanel != NULL);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 3786
    UTIL_ASSERT(pSettings != NULL);

    if (pSettings->m_bFirstConnected) {
        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3794
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

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
            // __LINE__: 3805
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

// 0x64DFD0
void CScreenMultiPlayer::FocusChatEditBox()
{
    CUIPanel* pPanel;
    CUIControlEdit* pEdit;

    if (GetTopPopup() != NULL && GetTopPopup()->m_nID == 1) {
        pPanel = m_cUIManager.GetPanel(1);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3882
        UTIL_ASSERT(pPanel != NULL);

        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(74));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3884
        UTIL_ASSERT(pEdit != NULL);

        m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
    } else {
        pPanel = m_cUIManager.GetPanel(0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3875
        UTIL_ASSERT(pPanel != NULL);

        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(27));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3877
        UTIL_ASSERT(pEdit != NULL);

        m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
    }
}

// 0x64E0B0
void CScreenMultiPlayer::OnKickPlayerButtonClick(INT nButton)
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    m_nKickPlayerSlot = nButton;
    m_nErrorState = 3;
    m_dwErrorTextId = 10916;
    m_strErrorButtonText[0] = 10918;
    m_strErrorButtonText[1] = 13727;
    SummonPopup(7);

    renderLock.Unlock();
}

// 0x64E160
void CScreenMultiPlayer::UpdateExperienceEntry(CUIControlTextDisplay* pText, const CAIObjectType& typeAI, CDerivedStats& DStats, DWORD nSpecialization, BYTE nBestClass, DWORD dwFlags)
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

// 0x64E2C0
void CScreenMultiPlayer::ResetViewCharacterPanel(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x64F090
BOOL CScreenMultiPlayer::IsPortraitButtonClickable(INT nCharacterSlot)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4311
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    LONG nCharacterId = pGame->GetCharacterSlot(nCharacterSlot);

    BOOL bSlotFull = pSettings->GetCharacterStatus(nCharacterSlot) == CMultiplayerSettings::CHARSTATUS_CHARACTER
        && nCharacterId != CGameObjectArray::INVALID_INDEX;

    INT nPlayerNumber = g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.m_idLocalPlayer, FALSE);
    BOOLEAN bLeader = pSettings->GetPermission(nPlayerNumber, CGamePermission::LEADER);
    BOOLEAN bIsHost = g_pBaldurChitin->cNetwork.GetSessionHosting();

    return !pSettings->m_bFirstConnected
        && bSlotFull
        && (bLeader || bIsHost)
        && pSettings->m_bArbitrationLockStatus;
}

// 0x64F170
void CScreenMultiPlayer::OnPortraitButtonClick(INT nButton)
{
    if (IsPortraitButtonClickable(nButton)) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        m_nCharacterSlot = nButton;
        SummonPopup(7);

        renderLock.Unlock();
    }
}

// 0x64F200
void CScreenMultiPlayer::OnLogoutButtonClick()
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

// 0x64F2A0
void CScreenMultiPlayer::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4485
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4487
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x64F3B0
void CScreenMultiPlayer::CopyChatEditBox(CUIPanel* pFrom, CUIPanel* pTo)
{
    DWORD dwFromTextId = -1;
    switch (pFrom->m_nID) {
    case 0:
    case 9:
        dwFromTextId = 27;
        break;
    case 1:
        dwFromTextId = 74;
        break;
    }

    DWORD dwToTextId = -1;
    switch (pTo->m_nID) {
    case 0:
    case 9:
        dwToTextId = 27;
        break;
    case 1:
        dwToTextId = 74;
        break;
    }

    CString sText;
    if (dwFromTextId != -1 && dwToTextId != -1) {
        CUIControlEdit* pFromEdit = static_cast<CUIControlEdit*>(pFrom->GetControl(dwFromTextId));
        CUIControlEdit* pToEdit = static_cast<CUIControlEdit*>(pTo->GetControl(dwToTextId));
        if (pFromEdit != NULL && pToEdit != NULL) {
            sText = pFromEdit->GetText();
            pToEdit->SetText(sText);

            if (m_cUIManager.m_pFocusedControl == pFromEdit) {
                m_cUIManager.SetCapture(pToEdit, CUIManager::KEYBOARD);
            }
        }
    }
}

// 0x64F4D0
void CScreenMultiPlayer::GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture)
{
    CUIPanel* pPanel = GetTopPopup();

    if (pPanel == NULL) {
        pPanel = m_cUIManager.GetPanel(0);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4683
    UTIL_ASSERT(pPanel != NULL);

    DWORD dwTextId = -1;
    switch (pPanel->m_nID) {
    case 0:
    case 9:
        dwTextId = 27;
        break;
    case 1:
        dwTextId = 74;
        break;
    }

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(dwTextId));
    if (pEdit != NULL) {
        sChatText = pEdit->GetText();
        bInputCapture = m_cUIManager.m_pFocusedControl == pEdit;
    } else {
        sChatText = "";
        bInputCapture = FALSE;
    }
}

// 0x64F5E0
void CScreenMultiPlayer::SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture)
{
    CUIPanel* pPanel = GetTopPopup();

    if (pPanel == NULL) {
        pPanel = m_cUIManager.GetPanel(0);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4683
    UTIL_ASSERT(pPanel != NULL);

    DWORD dwTextId = -1;
    switch (pPanel->m_nID) {
    case 0:
    case 9:
        dwTextId = 27;
        break;
    case 1:
        dwTextId = 74;
        break;
    }

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(dwTextId));
    if (pEdit != NULL) {
        pEdit->SetText(sChatText);

        if (bInputCapture) {
            m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
        }
    }
}

// NOTE: Inlined.
void CScreenMultiPlayer::SetPermissionToolTips(CUIPanel* pPanel, DWORD a3, DWORD a4, DWORD a5, STRREF strRef)
{
    CUIControlBase* pControl;

    if (a3 != -1) {
        pControl = pPanel->GetControl(a3);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3368
        UTIL_ASSERT(pControl != NULL);

        pControl->SetToolTipStrRef(strRef, -1, -1);
    }

    while (a4 <= a5) {
        pControl = pPanel->GetControl(a4);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 3376
        UTIL_ASSERT(pControl != NULL);

        pControl->SetToolTipStrRef(strRef, -1, -1);

        a4++;
    }
}

// NOTE: Inlined.
void CScreenMultiPlayer::UpdatePermission(CUIPanel* pPanel, DWORD nButtonID, BOOL bEnabled, BOOL bSelected)
{
    CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));
    BOOL bWasEnabled = pButton->m_bEnabled;
    pButton->SetEnabled(bEnabled);
    pButton->SetSelected(bSelected);
    if (bEnabled != bWasEnabled) {
        pButton->InvalidateRect();
    }
}

// -----------------------------------------------------------------------------

// 0x64F690
CUIControlButtonMultiPlayerReady::CUIControlButtonMultiPlayerReady(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nPressedFrame = 2;
    m_nDisabledFrame = 3;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 0;
}

// 0x64F700
CUIControlButtonMultiPlayerReady::~CUIControlButtonMultiPlayerReady()
{
}

// 0x64F7A0
void CUIControlButtonMultiPlayerReady::OnLButtonClick(CPoint pt)
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4756
    UTIL_ASSERT(pSettings != NULL);

    INT nSlot = m_nID;

    pSettings->SetCharacterReady(nSlot, !pSettings->GetCharacterReady(nSlot), TRUE);
}

// -----------------------------------------------------------------------------

// 0x64F7F0
CUIControlButtonMultiPlayerPortrait::CUIControlButtonMultiPlayerPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_portraitResRef = "";
}

// 0x64F890
CUIControlButtonMultiPlayerPortrait::~CUIControlButtonMultiPlayerPortrait()
{
}

// 0x64F930
void CUIControlButtonMultiPlayerPortrait::SetPortrait(const CResRef& resRef)
{
    if (m_portraitResRef != resRef) {
        m_portraitResRef = resRef;
        InvalidateRect();
    }
}

// 0x64F970
BOOL CUIControlButtonMultiPlayerPortrait::Render(BOOL bForce)
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

// 0x64FBF0
void CUIControlButtonMultiPlayerPortrait::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4921
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnPortraitButtonClick(m_nID - 6);
}

// -----------------------------------------------------------------------------

// 0x64FC30
CUIControlButtonMultiPlayerPlayer::CUIControlButtonMultiPlayerPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_cVidFont.SetResRef(CResRef("NORMAL"), m_pPanel->m_pManager->m_bDoubleSize, TRUE);
    m_cVidFont.SetColor(RGB(210, 210, 210), RGB(30, 30, 30), FALSE);
}

// 0x64FCF0
CUIControlButtonMultiPlayerPlayer::~CUIControlButtonMultiPlayerPlayer()
{
}

// 0x64FD90
void CUIControlButtonMultiPlayerPlayer::OnLButtonClick(CPoint pt)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4976
    UTIL_ASSERT(CRESUI_CONTROLBUTTONID_MULTIPLAYER_PLAYER0 <= m_nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4977
    UTIL_ASSERT(m_nID <= CRESUI_CONTROLBUTTONID_MULTIPLAYER_PLAYER5);

    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 4979
    UTIL_ASSERT(pMultiPlayer != NULL);

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pMultiPlayer->field_458 = m_nID - 12;
    pMultiPlayer->SummonPopup(4);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x64FE80
CUIControlButtonMultiPlayerCharacter::CUIControlButtonMultiPlayerCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_cVidFont.SetResRef(CResRef("NORMAL"), m_pPanel->m_pManager->m_bDoubleSize, TRUE);
    m_cVidFont.SetColor(RGB(210, 210, 210), RGB(30, 30, 30), FALSE);
}

// 0x64FF40
CUIControlButtonMultiPlayerCharacter::~CUIControlButtonMultiPlayerCharacter()
{
}

// 0x64FFE0
void CUIControlButtonMultiPlayerCharacter::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5044
    UTIL_ASSERT(pMultiPlayer != NULL);

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pMultiPlayer->field_458 = m_nID - 18;
    pMultiPlayer->SummonPopup(3);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x6500A0
CUIControlButtonMultiPlayerDone::CUIControlButtonMultiPlayerDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x650190
CUIControlButtonMultiPlayerDone::~CUIControlButtonMultiPlayerDone()
{
}

// 0x650230
void CUIControlButtonMultiPlayerDone::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5109
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnMainDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x650270
CUIControlButtonMultiPlayerOptions::CUIControlButtonMultiPlayerOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(10156, strRes);
    SetText(strRes.szText);
}

// 0x650360
CUIControlButtonMultiPlayerOptions::~CUIControlButtonMultiPlayerOptions()
{
}

// 0x650400
void CUIControlButtonMultiPlayerOptions::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5165
    UTIL_ASSERT(pMultiPlayer != NULL);

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pMultiPlayer->SummonPopup(1);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x6504B0
CUIControlButtonMultiPlayerLogout::CUIControlButtonMultiPlayerLogout(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13906, strRes);
    SetText(strRes.szText);
}

// 0x6505A0
CUIControlButtonMultiPlayerLogout::~CUIControlButtonMultiPlayerLogout()
{
}

// 0x650640
void CUIControlButtonMultiPlayerLogout::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5230
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnLogoutButtonClick();
}

// -----------------------------------------------------------------------------

// 0x650680
CUIControlEditMultiPlayerChat::CUIControlEditMultiPlayerChat(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, 0)
{
    field_8A0 = 0;
}

// 0x6506D0
CUIControlEditMultiPlayerChat::~CUIControlEditMultiPlayerChat()
{
}

// 0x6507A0
void CUIControlEditMultiPlayerChat::OnEditReturn(CString sText)
{
    g_pBaldurChitin->GetBaldurMessage()->SendChatMessage(sText);
    field_868 = sText;
    SetText(CString(""));
}

// -----------------------------------------------------------------------------

// 0x650830
CUIControlButtonMultiPlayerPermissionsPermission::CUIControlButtonMultiPlayerPermissionsPermission(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nPressedFrame = 2;
    m_nDisabledFrame = 0;
    field_66E = 4;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 3;
}

// 0x6508B0
CUIControlButtonMultiPlayerPermissionsPermission::~CUIControlButtonMultiPlayerPermissionsPermission()
{
}

// 0x650950
void CUIControlButtonMultiPlayerPermissionsPermission::OnLButtonClick(CPoint pt)
{
    INT nPlayer;
    INT nPermission;

    switch (m_nID) {
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        nPermission = CGamePermission::MODIFY_CHARS;
        nPlayer = m_nID - 13;
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
        nPermission = CGamePermission::PURCHASING;
        nPlayer = m_nID - 19;
        break;
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
        nPermission = CGamePermission::AREA_TRANSITION;
        nPlayer = m_nID - 25;
        break;
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
        nPermission = CGamePermission::DIALOG;
        nPlayer = m_nID - 31;
        break;
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
        nPermission = CGamePermission::CHAR_RECORDS;
        nPlayer = m_nID - 37;
        break;
    case 49:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
        nPermission = CGamePermission::PAUSING;
        nPlayer = m_nID - 49;
        break;
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 60:
        nPermission = CGamePermission::LEADER;
        nPlayer = m_nID - 55;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 5469
        UTIL_ASSERT(FALSE);
    }

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5474
    UTIL_ASSERT(pSettings != NULL);

    g_pBaldurChitin->cNetwork.GetPlayerID(nPlayer);
    pSettings->SetPermission(nPlayer, nPermission, m_bSelected == FALSE, TRUE);
}

// -----------------------------------------------------------------------------

// 0x650A90
CUIControlButtonMultiPlayerPermissionsKick::CUIControlButtonMultiPlayerPermissionsKick(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x650AE0
CUIControlButtonMultiPlayerPermissionsKick::~CUIControlButtonMultiPlayerPermissionsKick()
{
}

// 0x650B80
void CUIControlButtonMultiPlayerPermissionsKick::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5548
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnKickPlayerButtonClick(m_nID);
}

// -----------------------------------------------------------------------------

// 0x650BC0
CUIControlButtonMultiPlayerPermissionsOptions::CUIControlButtonMultiPlayerPermissionsOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13905, strRes);
    SetText(strRes.szText);
}

// 0x650CB0
CUIControlButtonMultiPlayerPermissionsOptions::~CUIControlButtonMultiPlayerPermissionsOptions()
{
}

// 0x650D50
void CUIControlButtonMultiPlayerPermissionsOptions::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5604
    UTIL_ASSERT(pMultiPlayer != NULL);

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pMultiPlayer->SummonPopup(2);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x650E00
CUIControlButtonMultiPlayerPermissionsListen::CUIControlButtonMultiPlayerPermissionsListen(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    // FIXME: Unused.
    STR_RES strRes;

    m_nPressedFrame = 2;
    m_nDisabledFrame = 0;
    field_66E = 4;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 3;
}

// 0x650EF0
CUIControlButtonMultiPlayerPermissionsListen::~CUIControlButtonMultiPlayerPermissionsListen()
{
}

// 0x650F90
void CUIControlButtonMultiPlayerPermissionsListen::OnLButtonClick(CPoint pt)
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5722
    UTIL_ASSERT(pSettings != NULL);

    pSettings->SetListenToJoinOption(m_bSelected == FALSE, TRUE);
}

// -----------------------------------------------------------------------------

// 0x650FE0
CUIControlButtonMultiPlayerPermissionsDone::CUIControlButtonMultiPlayerPermissionsDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x6510D0
CUIControlButtonMultiPlayerPermissionsDone::~CUIControlButtonMultiPlayerPermissionsDone()
{
}

// 0x651170
void CUIControlButtonMultiPlayerPermissionsDone::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5778
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6511B0
CUIControlButtonMultiPlayerOptionsImport::CUIControlButtonMultiPlayerOptionsImport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nNotSelectedFrame = 0;
    m_nPressedFrame = 1;
    m_nSelectedFrame = 3;
    m_nDisabledFrame = 2;
    field_66E = 4;
}

// 0x651230
CUIControlButtonMultiPlayerOptionsImport::~CUIControlButtonMultiPlayerOptionsImport()
{
}

// 0x651340
void CUIControlButtonMultiPlayerOptionsImport::OnLButtonClick(CPoint pt)
{
    DWORD strDescription;
    BYTE nImportingBitField;

    switch (m_nID) {
    case 2:
        strDescription = 11324;
        nImportingBitField = CMultiplayerSettings::IMPORT_STATISTICS | CMultiplayerSettings::IMPORT_EXPERIENCE | CMultiplayerSettings::IMPORT_ITEMS;
        break;
    case 3:
        strDescription = 11325;
        nImportingBitField = CMultiplayerSettings::IMPORT_STATISTICS | CMultiplayerSettings::IMPORT_EXPERIENCE;
        break;
    case 4:
        strDescription = 11326;
        nImportingBitField = CMultiplayerSettings::IMPORT_STATISTICS;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 5909
        UTIL_ASSERT(FALSE);
    }

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5916
    UTIL_ASSERT(pSettings != NULL);

    pSettings->SetImportingCharacterOption(nImportingBitField);

    g_pBaldurChitin->m_pEngineMultiPlayer->UpdateHelp(m_pPanel->m_nID, 14, strDescription);
}

// -----------------------------------------------------------------------------

// 0x651420
CUIControlButtonMultiPlayerOptionsCancel::CUIControlButtonMultiPlayerOptionsCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x651510
CUIControlButtonMultiPlayerOptionsCancel::~CUIControlButtonMultiPlayerOptionsCancel()
{
}

// 0x6515B0
void CUIControlButtonMultiPlayerOptionsCancel::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 5975
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6515F0
CUIControlButtonMultiPlayerOptionsDone::CUIControlButtonMultiPlayerOptionsDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x6516E0
CUIControlButtonMultiPlayerOptionsDone::~CUIControlButtonMultiPlayerOptionsDone()
{
}

// 0x651780
void CUIControlButtonMultiPlayerOptionsDone::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6031
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6517C0
CUIControlButtonMultiPlayerModifyCharacterCreate::CUIControlButtonMultiPlayerModifyCharacterCreate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13954, strRes);
    SetText(strRes.szText);
}

// 0x6518B0
CUIControlButtonMultiPlayerModifyCharacterCreate::~CUIControlButtonMultiPlayerModifyCharacterCreate()
{
}

// 0x651950
void CUIControlButtonMultiPlayerModifyCharacterCreate::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6087
    UTIL_ASSERT(pMultiPlayer != NULL);

    CScreenCreateChar* pCreateChar = g_pBaldurChitin->m_pEngineCreateChar;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6089
    UTIL_ASSERT(pCreateChar != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6091
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6093
    UTIL_ASSERT(pSettings != NULL);

    CNetwork& cNetwork = g_pBaldurChitin->cNetwork;

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nCharacterSlot = pMultiPlayer->field_458;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6101
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

            pMultiPlayer->OnDoneButtonClick();
            pCreateChar->StartCreateChar(nCharacterSlot, 3);
            pMultiPlayer->SelectEngine(pCreateChar);

            renderLock.Lock();
        }
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x651CA0
CUIControlButtonMultiPlayerModifyCharacterDelete::CUIControlButtonMultiPlayerModifyCharacterDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13957, strRes);
    SetText(strRes.szText);
}

// 0x651D90
CUIControlButtonMultiPlayerModifyCharacterDelete::~CUIControlButtonMultiPlayerModifyCharacterDelete()
{
}

// 0x651E30
void CUIControlButtonMultiPlayerModifyCharacterDelete::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6212
    UTIL_ASSERT(pMultiPlayer != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6214
    UTIL_ASSERT(pGame != NULL);

    CNetwork& cNetwork = g_pBaldurChitin->cNetwork;

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6217
    UTIL_ASSERT(pSettings != NULL);

    CSingleLock renderLock(&(pMultiPlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    INT nCharacterSlot = pMultiPlayer->field_458;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6226
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

            pMultiPlayer->OnDoneButtonClick();

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

// -----------------------------------------------------------------------------

// 0x6522A0
CUIControlButtonMultiPlayerModifyCharacterCancel::CUIControlButtonMultiPlayerModifyCharacterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x652390
CUIControlButtonMultiPlayerModifyCharacterCancel::~CUIControlButtonMultiPlayerModifyCharacterCancel()
{
}

// 0x652430
void CUIControlButtonMultiPlayerModifyCharacterCancel::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6382
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x652470
CUIControlButtonMultiPlayerModifyPlayerPlayer::CUIControlButtonMultiPlayerModifyPlayerPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_cVidFont.SetResRef(CResRef("NORMAL"), m_pPanel->m_pManager->m_bDoubleSize, TRUE);
    m_cVidFont.SetColor(RGB(210, 210, 210), RGB(30, 30, 30), FALSE);
}

// 0x652530
CUIControlButtonMultiPlayerModifyPlayerPlayer::~CUIControlButtonMultiPlayerModifyPlayerPlayer()
{
}

// 0x6525D0
void CUIControlButtonMultiPlayerModifyPlayerPlayer::OnLButtonClick(CPoint pt)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6438
    UTIL_ASSERT(m_nID <= CRESUI_CONTROLBUTTONID_MULTIPLAYER_MODIFYPLAYER_PLAYER5);

    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6440
    UTIL_ASSERT(pMultiPlayer != NULL);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6443
    UTIL_ASSERT(pSettings != NULL);

    pSettings->SetCharacterControlledByPlayer(pMultiPlayer->field_458,
        m_nID,
        TRUE,
        pMultiPlayer->field_45C != 1);

    pMultiPlayer->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x652690
CUIControlButtonMultiPlayerModifyPlayerCancel::CUIControlButtonMultiPlayerModifyPlayerCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x652780
CUIControlButtonMultiPlayerModifyPlayerCancel::~CUIControlButtonMultiPlayerModifyPlayerCancel()
{
}

// 0x652820
void CUIControlButtonMultiPlayerModifyPlayerCancel::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6512
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x652860
CUIControlButtonMultiPlayerModify::CUIControlButtonMultiPlayerModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(18816, strRes);
    SetText(strRes.szText);
}

// 0x652950
CUIControlButtonMultiPlayerModify::~CUIControlButtonMultiPlayerModify()
{
}

// 0x6529F0
void CUIControlButtonMultiPlayerModify::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6568
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnModifyButtonClick();
}

// -----------------------------------------------------------------------------

// 0x652A30
CUIControlButtonMultiPlayerError::CUIControlButtonMultiPlayerError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x652A80
CUIControlButtonMultiPlayerError::~CUIControlButtonMultiPlayerError()
{
}

// 0x652B20
void CUIControlButtonMultiPlayerError::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6620
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnErrorButtonClick(m_nID - 1);
}

// -----------------------------------------------------------------------------

// 0x652B60
CUIControlButtonMultiPlayerViewCharacterDone::CUIControlButtonMultiPlayerViewCharacterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6649
    UTIL_ASSERT(pMultiPlayer != NULL);

    SetText(CBaldurEngine::FetchString(11973));
}

// 0x652C30
CUIControlButtonMultiPlayerViewCharacterDone::~CUIControlButtonMultiPlayerViewCharacterDone()
{
}

// 0x652CD0
void CUIControlButtonMultiPlayerViewCharacterDone::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6676
    UTIL_ASSERT(pMultiPlayer != NULL);

    pMultiPlayer->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// NOTE: Unclear why this function is separated from constructor/destructor
// pair (originally in `CUIControlButtons.cpp`, now in `CUIControlFactory.cpp`).
//
// 0x652D10
void CUIControlButtonMultiPlayerHotArea::OnHotAreaClick(CPoint pt)
{
    STRREF strDescription;

    switch (m_pPanel->m_nID) {
    case 2:
        switch (m_nID) {
        case 11:
            strDescription = 11324;
            break;
        case 12:
            strDescription = 11325;
            break;
        case 13:
            strDescription = 11326;
            break;
        case 17:
            strDescription = 20717;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
            // __LINE__: 6728
            UTIL_ASSERT(FALSE);
        }

        g_pBaldurChitin->m_pEngineMultiPlayer->UpdateHelp(m_pPanel->m_nID, 14, strDescription);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 6734
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x652DD0
CUIControlButtonMultiPlayerSelection::CUIControlButtonMultiPlayerSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nPressedFrame = 2;
    m_nDisabledFrame = 0;
    m_nNotSelectedFrame = 1;
    m_nSelectedFrame = 3;
    field_66E = 4;
}

// 0x652E50
CUIControlButtonMultiPlayerSelection::~CUIControlButtonMultiPlayerSelection()
{
}

// 0x652EF0
void CUIControlButtonMultiPlayerSelection::OnLButtonClick(CPoint pt)
{
    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6849
    UTIL_ASSERT(pMultiPlayer != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
    // __LINE__: 6851
    UTIL_ASSERT(pGame != NULL);

    CMultiplayerSettings* pSettings = pGame->GetMultiplayerSettings();

    CUIControlButton3State::OnLButtonClick(pt);

    switch (m_pPanel->m_nID) {
    case 2:
        switch (m_nID) {
        case 18:
            pSettings->SetRestrictStoreOption(!pSettings->m_bRestrictStoreOption);
            pMultiPlayer->UpdateHelp(m_pPanel->m_nID, 14, 20717);

            // NOTE: Uninline.
            pMultiPlayer->UpdatePopupPanel(m_pPanel->m_nID);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
            // __LINE__: 6870
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMultiPlayer.cpp
        // __LINE__: 6876
        UTIL_ASSERT(FALSE);
    }
}

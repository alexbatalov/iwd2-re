#include "CScreenMultiPlayer.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CUIControlEdit.h"
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
    field_48A = 0;
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

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(25));

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

    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.sub_7AC840();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.sub_7AC890();
}

// 0x6490F0
void CScreenMultiPlayer::EngineInitialized()
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.

    return FALSE;
}

// 0x64A8B0
void CScreenMultiPlayer::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x64AA10
void CScreenMultiPlayer::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x64AB40
void CScreenMultiPlayer::EnableMainPanel(BOOL bEnable)
{
    // TODO: Incomplete.
}

// 0x64AC60
void CScreenMultiPlayer::UpdateOptionsPanel()
{
    // TODO: Incomplete.
}

// 0x64ADB0
void CScreenMultiPlayer::UpdateMainPanel()
{
    // TODO: Incomplete.
}

// 0x64AF40
void CScreenMultiPlayer::CheckEnableCharacters()
{
    // TODO: Incomplete.
}

// 0x64B090
void CScreenMultiPlayer::CheckCharacterButtons()
{
    // TODO: Incomplete.
}

// 0x64B340
void CScreenMultiPlayer::UpdateMainPanelCharacter()
{
    // TODO: Incomplete.
}

// 0x64BCF0
void CScreenMultiPlayer::UpdatePermissionsPanel()
{
    // TODO: Incomplete.
}

// 0x64BE30
void CScreenMultiPlayer::UpdatePermissionsPanelPlayer()
{
    // TODO: Incomplete.
}

// 0x64C210
void CScreenMultiPlayer::UpdateModifyPlayerPanel()
{
    // TODO: Incomplete.
}

// 0x64C3B0
void CScreenMultiPlayer::UpdateModifyCharacterPanel()
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.

    return FALSE;
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
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

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
    // TODO: Incomplete.
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
void CScreenMultiPlayer::sub_64E160()
{
    // TODO: Incomplete.
}

// 0x64E2C0
void CScreenMultiPlayer::ResetViewCharacterPanel(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x64F090
BOOL CScreenMultiPlayer::IsPortraitButtonClickable(INT nButton)
{
    // TODO: Incomplete.

    return FALSE;
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

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
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

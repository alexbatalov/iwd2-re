#include "CScreenSinglePlayer.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
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
    field_1392 = 0;
    field_1396 = 0;
    m_nParty = 0;
    field_139E = 0;
    field_488 = 0;
    field_48A = 0;
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

// 0x0x49FC40
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
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
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

    for (int index = 0; index < 4; index++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->field_49B4[index]));
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
    // TODO: Incomplete.
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
        sub_6644B0(pPanel);
        break;
    case 10:
        m_nParty = 0;
        field_1396 = 0;
        dword_8B4828 = -1;
        field_1392 = 0;
        sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, field_1392);
        while (GetPrivateProfileStringA(byte_8F64C0, NAME, "", byte_8F64E0, sizeof(byte_8F64E0), ".\\Party.ini")) {
            field_1392++;
            sprintf(byte_8F64C0, "%s %i", (LPCSTR)PARTY, field_1392);
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
        sub_664010();
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
    // TODO: Incomplete.

    return FALSE;
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
        sub_6642C0();
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
    // TODO: Incomplete.
}

// 0x662170
void CScreenSinglePlayer::UpdateMainPanelCharacter(CUIPanel* pPanel, INT nCharacterSlot)
{
    // TODO: Incomplete.
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
    BYTE v3 = static_cast<BYTE>(g_pBaldurChitin->cNetwork.field_78A);

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
    // TODO: Incomplete.
}

// 0x663640
BOOL CScreenSinglePlayer::IsModifyButtonClickable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 2656
    UTIL_ASSERT(pGame != NULL);

    return !pGame->GetMultiplayerSettings()->field_B8
        && (g_pBaldurChitin->cNetwork.FindPlayerLocationByID(g_pBaldurChitin->cNetwork.field_6FA, FALSE) != -1
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

    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.sub_7AC840();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.sub_7AC890();
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

            g_pBaldurChitin->m_pEngineStart->field_140 = 0;
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
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(TRUE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

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
    // TODO: Incomplete.
}

// 0x663EB0
void CScreenSinglePlayer::sub_663EB0()
{
    // TODO: Incomplete.
}

// 0x664010
void CScreenSinglePlayer::sub_664010()
{
    // TODO: Incomplete.
}

// 0x6642C0
void CScreenSinglePlayer::sub_6642C0()
{
    // TODO: Incomplete.
}

// 0x6644B0
void CScreenSinglePlayer::sub_6644B0(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x665280
BOOL CScreenSinglePlayer::sub_665280(INT nCharacterSlot)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 3649
    UTIL_ASSERT(pGame != NULL);

    // TODO: Incomplete.

    return FALSE;
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

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
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
    field_666 = "";
}

// 0x665780
CUIControlButtonSinglePlayerPortrait::~CUIControlButtonSinglePlayerPortrait()
{
}

// 0x665820
BOOL CUIControlButtonSinglePlayerPortrait::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
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
    // TODO: Incomplete.
}

// 0x665E10
CUIControlButtonSinglePlayerDone::CUIControlButtonSinglePlayerDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(13906, strRes);
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

// 0x666360
CUIControlButtonSinglePlayerModifyCharacterCreate::CUIControlButtonSinglePlayerModifyCharacterCreate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13954, strRes);
    SetText(strRes.szText);
}

// 0x666450
CUIControlButtonSinglePlayerModifyCharacterCreate::~CUIControlButtonSinglePlayerModifyCharacterCreate()
{
}

// 0x6664F0
void CUIControlButtonSinglePlayerModifyCharacterCreate::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x666850
CUIControlButtonSinglePlayerModifyCharacterDelete::CUIControlButtonSinglePlayerModifyCharacterDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13957, strRes);
    SetText(strRes.szText);
}

// 0x666940
CUIControlButtonSinglePlayerModifyCharacterDelete::~CUIControlButtonSinglePlayerModifyCharacterDelete()
{
}

// 0x6669E0
void CUIControlButtonSinglePlayerModifyCharacterDelete::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x666E50
CUIControlButtonSinglePlayerModifyCharacterCancel::CUIControlButtonSinglePlayerModifyCharacterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(18816, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
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
    g_pBaldurChitin->m_cTlkTable.Fetch(10316, strRes);
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

// 0x667810
void CUIControlButtonSinglePlayerPartySelection::OnLButtonClick(CPoint pt)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5376
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->m_nParty = m_nID;
}

// 0x667B50
CUIControlScrollBarSinglePlayerParties::CUIControlScrollBarSinglePlayerParties(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarSinglePlayerParties::~CUIControlScrollBarSinglePlayerParties()
{
}

// 0x667B70
void CUIControlScrollBarSinglePlayerParties::OnScrollUp()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5404
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_1396--;
    sub_667D10();
}

// 0x667BC0
void CUIControlScrollBarSinglePlayerParties::OnScrollDown()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5415
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_1396++;
    sub_667D10();
}

// 0x667C10
void CUIControlScrollBarSinglePlayerParties::OnPageUp(int a1)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5426
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_1396 -= min(a1, 5);
    sub_667D10();
}

// 0x667C60
void CUIControlScrollBarSinglePlayerParties::OnPageDown(int a1)
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5441
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_1396 += min(a1, 5);
    sub_667D10();
}

// 0x667CB0
void CUIControlScrollBarSinglePlayerParties::OnScroll()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5456
    UTIL_ASSERT(pSinglePlayer != NULL);

    pSinglePlayer->field_1396 = max(pSinglePlayer->field_1392 * field_144, 0) / field_142;
    sub_667D10();
}

// 0x667D10
void CUIControlScrollBarSinglePlayerParties::sub_667D10()
{
    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreensingleplayer.cpp
    // __LINE__: 5469
    UTIL_ASSERT(pSinglePlayer != NULL);

    CSingleLock renderLock(&(pSinglePlayer->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pSinglePlayer->field_1396 = max(min(pSinglePlayer->field_1396, pSinglePlayer->field_1392 - 6), 0);

    // NOTE: Uninline.
    pSinglePlayer->UpdatePopupPanel(m_pPanel->m_nID);

    renderLock.Unlock();
}

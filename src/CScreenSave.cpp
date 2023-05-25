#include "CScreenSave.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenOptions.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define GAME_SLOTS 5

// 0x659B10
CScreenSave::CScreenSave()
{
    m_nMaxSlotNumber = 0;

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
    m_pVirtualKeys[90] = CKeyInfo(VK_PROCESSKEY, -1, 0);
    m_pVirtualKeys[91] = CKeyInfo(VK_PRIOR, 0, 0);
    m_pVirtualKeys[92] = CKeyInfo(VK_NEXT, 0, 0);

    m_bCtrlKeyDown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    m_nTopGameSlot = 0;
    m_nNumGameSlots = 0;
    m_nEngineState = -1;
    m_dwErrorTextId = -1;
    m_strErrorButtonText[0] = -1;
    m_strErrorButtonText[1] = -1;
    m_strErrorButtonText[2] = -1;
    m_nNumErrorButtons = 0;
    m_nCurrentGameSlot = -1;
}

// 0x49FC40
BOOL CScreenSave::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x65A7B0
void CScreenSave::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x65A7C0
BOOL CScreenSave::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x49FC40
BOOL CScreenSave::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x65A7D0
void CScreenSave::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x65A7E0
BOOL CScreenSave::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenSave::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x65A7F0
void CScreenSave::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x65A800
BOOL CScreenSave::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenSave::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenSave::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenSave::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenSave::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenSave::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenSave::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenSave::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenSave::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenSave::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x65A810
SHORT CScreenSave::GetNumVirtualKeys()
{
    return CSCREENSAVE_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenSave::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x65A820
BYTE* CScreenSave::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x65A850
CScreenSave::~CScreenSave()
{
    FreeGameSlots();
}

// 0x65A8F0
void CScreenSave::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.m_bConnectionEstablished == TRUE
        && g_pChitin->cNetwork.m_bIsHost == TRUE
        && g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    UpdateMainPanel();
    UpdateCursorShape(0);
    m_cUIManager.InvalidateRect(NULL);
}

// 0x65A9C0
void CScreenSave::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.m_bConnectionEstablished == TRUE
        && g_pChitin->cNetwork.m_bIsHost == TRUE
        && g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL) {
        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x5D72C0
void CScreenSave::EngineDestroyed()
{
    m_cUIManager.fUninit();
}

// 0x65AA50
void CScreenSave::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUISAVE"), g_pBaldurChitin->field_4A28);

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
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    for (INT nSlot = 0; nSlot < GAME_SLOTS; nSlot++) {
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x10000005 + nSlot));
        pLabel->m_nTextFlags &= ~0x100;
    }
}

// 0x65ABC0
void CScreenSave::OnKeyDown(SHORT nKeysFlags)
{
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            if (m_pVirtualKeysFlags[nKeyFlag] == VK_ESCAPE) {
                if (GetTopPopup() != NULL) {
                    OnCancelButtonClick();
                } else {
                    // NOTE: Uninline.
                    OnMainCancelButtonClick();
                }
                continue;
            }

            if (m_pVirtualKeysFlags[nKeyFlag] == VK_RETURN) {
                // NOTE: Unused.
                g_pChitin->GetWnd();
                if (g_pChitin->cImm.field_128 == 0
                    || PRIMARYLANGID(GetSystemDefaultLangID()) != LANG_KOREAN) {
                    if (GetTopPopup() != NULL) {
                        OnDoneButtonClick();
                    }
                    continue;
                }
            }

            if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                switch (m_pVirtualKeysFlags[nKeyFlag]) {
                case VK_TAB:
                    m_cUIManager.ForceToolTip();
                    break;
                case VK_PRIOR:
                case VK_NUMPAD9:
                    if (GetTopPopup() == NULL) {
                        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
                        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(23));
                        pScrollBar->OnPageUp(3);
                    }
                    break;
                case VK_NEXT:
                case VK_NUMPAD3:
                    if (GetTopPopup() == NULL) {
                        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
                        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(23));
                        pScrollBar->OnPageDown(3);
                    }
                    break;
                case VK_END:
                case VK_NUMPAD1:
                    if (GetTopPopup() == NULL) {
                        m_nTopGameSlot = max(m_nNumGameSlots - GAME_SLOTS, 0);
                        UpdateMainPanel();
                    }
                    break;
                case VK_HOME:
                case VK_NUMPAD7:
                    if (GetTopPopup() == NULL) {
                        m_nTopGameSlot = 0;
                        UpdateMainPanel();
                    }
                    break;
                case VK_UP:
                case VK_NUMPAD8:
                    if (GetTopPopup() == NULL) {
                        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
                        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(23));
                        pScrollBar->OnScrollUp();
                    }
                    break;
                case VK_DOWN:
                case VK_NUMPAD2:
                    if (GetTopPopup() == NULL) {
                        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
                        CUIControlScrollBar* pScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(23));
                        pScrollBar->OnScrollDown();
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

// 0x63B9B0
void CScreenSave::TimerAsynchronousUpdate()
{
    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->m_pObjectCursor->CursorUpdate(pVidMode);
}

// 0x63BAA0
void CScreenSave::TimerSynchronousUpdate()
{
    g_pBaldurChitin->m_pObjectGame->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x65AEE0
void CScreenSave::UpdateMainPanel()
{
    // TODO: Incomplete.
}

// 0x65B320
void CScreenSave::OnSaveButtonClick(INT nSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 920
    UTIL_ASSERT(0 <= nSlot && nSlot < GAME_SLOTS);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    INT nGameSlot = m_nTopGameSlot + nSlot;
    if (nGameSlot < m_nNumGameSlots) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 927
        UTIL_ASSERT(pPanel != NULL);

        renderLock.Lock();

        m_nCurrentGameSlot = nGameSlot;
        SummonPopup(1);

        renderLock.Unlock();
    }
}

// 0x65B430
void CScreenSave::OnDeleteButtonClick(INT nSlot)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 991
    UTIL_ASSERT(0 <= nSlot && nSlot < GAME_SLOTS);

    INT nGameSlot = nSlot + m_nTopGameSlot;
    if (nGameSlot < m_nNumGameSlots && m_aGameSlots[nGameSlot]->m_sFileName != "") {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 997
        UTIL_ASSERT(pPanel != NULL);

        renderLock.Lock(INFINITE);

        m_nCurrentGameSlot = nGameSlot;
        m_dwErrorTextId = 15305;
        m_strErrorButtonText[0] = 13957;
        m_strErrorButtonText[1] = 13727;
        SummonPopup(2);

        renderLock.Unlock();
    }
}

// NOTE: Inlined.
void CScreenSave::OnMainCancelButtonClick()
{
    switch (m_nEngineState) {
    case 0:
    case 1:
    case 3:
        SelectEngine(g_pBaldurChitin->m_pEngineOptions);
        break;
    case 2:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__ 1055
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->m_pObjectGame->field_50D8 = FALSE;

    // NOTE: Uninline.
    StopSave();
}

// 0x65B580
BOOL CScreenSave::IsDoneButtonClickable()
{
    CUIPanel* pPanel = GetTopPopup();
    CString sString;

    BOOL bClickable;
    switch (pPanel->m_nID) {
    case 1:
        if (1) {
            CUIControlBase* pEdit = pPanel->GetControl(3);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
            // __LINE__ 1097
            UTIL_ASSERT(pEdit != NULL);

            // TODO: Incomplete.

            sString.TrimLeft();
            sString.TrimRight();
            bClickable = sString != "";
        }
        break;
    case 0:
    case 2:
    case 3:
        bClickable = TRUE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__ 1110
        UTIL_ASSERT(FALSE);
    }

    return bClickable;
}

// 0x65B6A0
void CScreenSave::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x65B920
void CScreenSave::OnCancelButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 1252
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 0:
    case 2:
    case 3:
        DismissPopup();
        break;
    case 1:
        DismissPopup();
        RefreshGameSlots();
        UpdateMainPanel();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 1268
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x65BA10
void CScreenSave::StartSave(INT nEngineState)
{
    m_nEngineState = nEngineState;
    RefreshGameSlots();
    m_nTopGameSlot = max(m_nNumGameSlots - 5, 0);
}

// 0x65BA40
void CScreenSave::StopSave()
{
    FreeGameSlots();
    m_aGameSlots.SetSize(0, -1);

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x65BA80
void CScreenSave::FreeGameSlots()
{
    // TODO: Incomplete.
}

// 0x65BCF0
void CScreenSave::RefreshGameSlots()
{
    // TODO: Incomplete.
}

// 0x65C850
void CScreenSave::DrawScreenShot()
{
    // TODO: Incomplete.
}

// 0x65CAB0
void CScreenSave::DrawPortrait()
{
    // TODO: Incomplete.
}

// 0x65CEA0
void CScreenSave::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 1834
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

// NOTE: Inlined.
CUIPanel* CScreenSave::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenSave::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
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
void CScreenSave::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 1916
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Inlined.
void CScreenSave::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 1943
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 1:
        ResetSaveAsPanel(pPanel);
        break;
    case 0:
    case 2:
    case 3:
        ResetErrorPanel(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 1957
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Uninline.
void CScreenSave::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 1:
        // NOTE: Uninline.
        UpdateSaveAsPanel();
        break;
    case 0:
    case 2:
    case 3:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 1995
        UTIL_ASSERT(FALSE);
    }
}

// 0x65CF70
void CScreenSave::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2075
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2081
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

// 0x65D1A0
void CScreenSave::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2126
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2143
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

// 0x65D360
void CScreenSave::ResetSaveAsPanel(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CScreenSave::UpdateSaveAsPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2278
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(7));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2283
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable());
}

// 0x65D760
void CScreenSave::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 2:
        m_nNumErrorButtons = 2;
        break;
    case 3:
        m_nNumErrorButtons = 1;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2320
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2333
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2342
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2469
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENSAVE_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x65D970
void CScreenSave::OnErrorButtonClick(INT nButton)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_dwErrorTextId) {
    case 15305:
        switch (nButton) {
        case 0:
            DismissPopup();

            // NOTE: Uninline.
            DeleteSave(m_nCurrentGameSlot);
            break;
        case 1:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
            // __LINE__: 2392
            UTIL_ASSERT(FALSE);
        }
    case 17132:
    case 17133:
        switch (nButton) {
        case 0:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
            // __LINE__: 2407
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
        // __LINE__: 2413
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x65DB30
void CScreenSave::SaveGame(INT nGameSlot, const CString& sSlotName)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CScreenSave::DeleteSave(INT nGameSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2495
    UTIL_ASSERT(0 <= nGameSlot && nGameSlot < m_nNumGameSlots);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2496
    UTIL_ASSERT(m_aGameSlots[nGameSlot]->m_sFileName != "");

    g_pBaldurChitin->m_pObjectGame->DeleteSaveGame(m_aGameSlots[nGameSlot]->m_sFileName);

    RefreshGameSlots();
    UpdateMainPanel();
}

// 0x65E0C0
void CScreenSave::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// -----------------------------------------------------------------------------

// 0x65E2C0
CUIControlButtonSaveDelete::CUIControlButtonSaveDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13957, strRes);
    SetText(strRes.szText);
}

// 0x65E3B0
CUIControlButtonSaveDelete::~CUIControlButtonSaveDelete()
{
}

// 0x65E450
void CUIControlButtonSaveDelete::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2856
    UTIL_ASSERT(pSave != NULL);

    pSave->OnDeleteButtonClick(m_nID - 60);
}

// -----------------------------------------------------------------------------

// 0x65E490
CUIControlButtonSaveSave::CUIControlButtonSaveSave(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15589, strRes);
    SetText(strRes.szText);
}

// 0x65E580
CUIControlButtonSaveSave::~CUIControlButtonSaveSave()
{
}

// 0x65E620
void CUIControlButtonSaveSave::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2912
    UTIL_ASSERT(pSave != NULL);

    pSave->OnSaveButtonClick(m_nID - 55);
}

// -----------------------------------------------------------------------------

// 0x65E660
CUIControlButtonSaveCancel::CUIControlButtonSaveCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x65E750
CUIControlButtonSaveCancel::~CUIControlButtonSaveCancel()
{
}

// 0x65E7F0
void CUIControlButtonSaveCancel::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 2968
    UTIL_ASSERT(pSave != NULL);

    // NOTE: Uninline.
    pSave->OnMainCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x65E8C0
CUIControlButtonSaveScreenShot::CUIControlButtonSaveScreenShot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x65E910
CUIControlButtonSaveScreenShot::~CUIControlButtonSaveScreenShot()
{
}

// 0x65E9B0
BOOL CUIControlButtonSaveScreenShot::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x65EB50
void CUIControlButtonSaveScreenShot::OnLButtonDoubleClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3086
    UTIL_ASSERT(pSave != NULL);

    if (m_pPanel->m_nID == 0) {
        pSave->OnSaveButtonClick(m_nID - 1);
    }
}

// -----------------------------------------------------------------------------

// 0x65EBA0
CUIControlButtonSavePortrait::CUIControlButtonSavePortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 1)
{
}

// 0x65EBF0
CUIControlButtonSavePortrait::~CUIControlButtonSavePortrait()
{
}

// 0x65EC90
BOOL CUIControlButtonSavePortrait::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x65EE30
CUIControlScrollBarSaveGames::CUIControlScrollBarSaveGames(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarSaveGames::~CUIControlScrollBarSaveGames()
{
}

// NOTE: Inlined.
void CUIControlScrollBarSaveGames::UpdateScrollBar()
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3236
    UTIL_ASSERT(pSave != NULL);

    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3238
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pSave->m_nTopGameSlot, pSave->m_nNumGameSlots, GAME_SLOTS);
}

// 0x65EE50
void CUIControlScrollBarSaveGames::OnScrollUp()
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3286
    UTIL_ASSERT(pSave != NULL);

    INT nNewTopGameSlot = max(pSave->m_nTopGameSlot - 1, 0);
    if (nNewTopGameSlot != pSave->m_nTopGameSlot) {
        pSave->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x65EF40
void CUIControlScrollBarSaveGames::OnScrollDown()
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3304
    UTIL_ASSERT(pSave != NULL);

    INT nNewTopGameSlot = max(min(pSave->m_nTopGameSlot + 1, pSave->m_nNumGameSlots - GAME_SLOTS), 0);
    if (nNewTopGameSlot != pSave->m_nTopGameSlot) {
        pSave->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x65F040
void CUIControlScrollBarSaveGames::OnPageUp(int a1)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3340
    UTIL_ASSERT(pSave != NULL);

    INT nStep = min(a1, GAME_SLOTS - 1);
    INT nNewTopGameSlot = max(pSave->m_nTopGameSlot - nStep, 0);
    if (nNewTopGameSlot != pSave->m_nTopGameSlot) {
        pSave->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x65F140
void CUIControlScrollBarSaveGames::OnPageDown(int a1)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3380
    UTIL_ASSERT(pSave != NULL);

    INT nStep = nStep = min(a1, GAME_SLOTS - 1);
    INT nNewTopGameSlot = max(min(pSave->m_nTopGameSlot + nStep, pSave->m_nNumGameSlots - GAME_SLOTS), 0);
    if (nNewTopGameSlot != pSave->m_nTopGameSlot) {
        pSave->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x65F250
void CUIControlScrollBarSaveGames::OnScroll()
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3420
    UTIL_ASSERT(pSave != NULL);

    pSave->m_nTopGameSlot = max(pSave->m_nNumGameSlots - GAME_SLOTS, 0) * field_144 / field_142;

    // NOTE: Uninline.
    UpdateMainPanel();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// NOTE: Inlined.
void CUIControlScrollBarSaveGames::UpdateMainPanel()
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3452
    UTIL_ASSERT(pSave != NULL);

    pSave->UpdateMainPanel();
}

// -----------------------------------------------------------------------------

// 0x065F350
CUIControlButtonSavePopupDone::CUIControlButtonSavePopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x65F440
CUIControlButtonSavePopupDone::~CUIControlButtonSavePopupDone()
{
}

// 0x65F4E0
void CUIControlButtonSavePopupDone::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3508
    UTIL_ASSERT(pSave != NULL);

    pSave->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x65F520
CUIControlButtonSavePopupCancel::CUIControlButtonSavePopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x65F610
CUIControlButtonSavePopupCancel::~CUIControlButtonSavePopupCancel()
{
}

// 0x65F6B0
void CUIControlButtonSavePopupCancel::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3564
    UTIL_ASSERT(pSave != NULL);

    pSave->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x65F6F0
CUIControlButtonSaveError::CUIControlButtonSaveError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CString(""));
}

// 0x65F7A0
CUIControlButtonSaveError::~CUIControlButtonSaveError()
{
}

// 0x65F840
void CUIControlButtonSaveError::OnLButtonClick(CPoint pt)
{
    CScreenSave* pSave = g_pBaldurChitin->m_pEngineSave;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSave.cpp
    // __LINE__: 3617
    UTIL_ASSERT(pSave != NULL);

    CSingleLock renderLock(&(pSave->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);
    pSave->OnErrorButtonClick(m_nID - 1);
    renderLock.Unlock();
}

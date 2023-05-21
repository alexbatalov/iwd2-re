#include "CScreenJournal.h"

#include "CBaldurChitin.h"
#include "CGameJournal.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUIControlScrollBar.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x635420
CScreenJournal::CScreenJournal()
{
    m_nChapter = 0;
    m_dwErrorState = 0;
    m_nNumErrorButtons = 0;
    field_E9C = 0;

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
    m_pVirtualKeys[90] = CKeyInfo('!', 0, 0);
    m_pVirtualKeys[91] = CKeyInfo('"', 0, 0);

    field_483 = 0;
    field_48C = "";
    field_484 = "";
    field_EA0 = 0;
    m_bShiftKeyDown = FALSE;
    m_bCtrlKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
}

// 0x49FC40
BOOL CScreenJournal::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x6360C0
void CScreenJournal::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x6360D0
BOOL CScreenJournal::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x49FC40
BOOL CScreenJournal::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x6360E0
void CScreenJournal::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x6360F0
BOOL CScreenJournal::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenJournal::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x636100
void CScreenJournal::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x636110
BOOL CScreenJournal::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenJournal::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenJournal::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenJournal::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenJournal::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenJournal::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenJournal::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenJournal::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenJournal::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenJournal::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x686660
SHORT CScreenJournal::GetNumVirtualKeys()
{
    return CSCREENJOURNAL_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenJournal::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x668C30
BYTE* CScreenJournal::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x636140
CScreenJournal::~CScreenJournal()
{
}

// 0x6361D0
void CScreenJournal::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.m_bConnectionEstablished == TRUE
        && g_pChitin->cNetwork.m_bIsHost == TRUE
        && g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    if (m_cUIManager.m_bInitialized) {
        UpdateMainPanel();
        UpdateCursorShape(0);
        CheckEnablePortaits(1);
        CheckEnableLeftPanel();
        g_pBaldurChitin->m_pObjectCursor->SetCursor(0, FALSE);
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x6362D0
void CScreenJournal::EngineDeactivated()
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
    m_preLoadFontTool.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }
}

// 0x636360
void CScreenJournal::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIJRNL"), g_pBaldurChitin->field_4A28);

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
    field_483 = 0;
    field_48C = "";
    field_484 = "";

    // NOTE: Calls `GetCurrentChapter` four times.
    m_nChapter = min(max(g_pBaldurChitin->m_pObjectGame->GetCurrentChapter(), 0), CGameJournal::NUM_CHAPTERS - 1);

    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);
}

// 0x5D72C0
void CScreenJournal::EngineGameUninit()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x636530
void CScreenJournal::OnKeyDown(SHORT nKeysFlags)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                if (m_bCtrlKeyDown) {
                    switch (m_pVirtualKeysFlags[nKeyFlag]) {
                    case 'A':
                        pGame->m_cJournal.SaveAll();
                        break;
                    case 'S':
                        pGame->m_cJournal.Save(m_nChapter);
                        break;
                    }
                } else {
                    switch (m_pVirtualKeysFlags[nKeyFlag]) {
                    case VK_TAB:
                        m_cUIManager.ForceToolTip();
                        break;
                    case VK_RETURN:
                        if (GetTopPopup() != NULL) {
                            switch (GetTopPopup()->m_nID) {
                            case 7:
                            case 8:
                            case 50:
                                OnErrorButtonClick(0);
                                break;
                            }
                        }
                        break;
                    case VK_ESCAPE:
                        if (GetTopPopup() != NULL) {
                            OnCancelButtonClick();
                        } else {
                            SelectEngine(g_pBaldurChitin->m_pEngineWorld);
                        }
                        break;
                    case VK_PRIOR:
                        if (GetTopPopup() == NULL) {
                            m_cUIManager.ClearTooltip();
                            if (m_nChapter > 0) {
                                m_nChapter--;
                                UpdateMainPanel();
                                PlayGUISound(RESREF_SOUND_PRIESTSCROLL);
                            }
                        }
                        break;
                    case VK_NEXT:
                        if (GetTopPopup() == NULL) {
                            m_cUIManager.ClearTooltip();
                            if (m_nChapter < CGameJournal::NUM_CHAPTERS - 1) {
                                m_nChapter++;
                                UpdateMainPanel();
                                PlayGUISound(RESREF_SOUND_PRIESTSCROLL);
                            }
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
    }
}

// 0x636AA0
void CScreenJournal::UpdateMainPanel()
{
    CUIControlTextDisplay* pText;

    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1101
    UTIL_ASSERT(pPanel != NULL);

    CString s1;
    CString s2;
    CResRef cResText;

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(2));

    s1 = "chapters";

    CList<STRREF, STRREF>* pList = pGame->m_ruleTables.GetChapterText(CResRef(s1), m_nChapter);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1117
    UTIL_ASSERT(pList != NULL);

    if (pList->GetCount() > 0) {
        s2 = FetchString(pList->GetHead());
    }

    if (pList != NULL) {
        delete pList;
    }

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(5));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1127
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_sLabelSuffix = CString(" ");

    CSize size;
    pText->m_labelFont.GetFrameSize(64, 0, size, FALSE);

    SHORT nFontHeight = pText->m_labelFont.GetFontHeight(FALSE);
    pText->field_AB4 = (nFontHeight - size.cy - 1) / nFontHeight;

    pText->DisplayString(CString(""),
        s2.Right(s2.GetLength()),
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        TRUE);

    pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1140
    UTIL_ASSERT(pText != NULL);

    pGame->m_cJournal.UpdateTextDisplay(m_nChapter, pText);
}

// 0x66A540
void CScreenJournal::TimerAsynchronousUpdate()
{
    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->m_pObjectCursor->CursorUpdate(pVidMode);
}

// 0x63BAA0
void CScreenJournal::TimerSynchronousUpdate()
{
    g_pBaldurChitin->m_pObjectGame->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x636A30
void CScreenJournal::OnPortraitLClick(DWORD nPortrait)
{
    if (nPortrait < g_pBaldurChitin->m_pObjectGame->m_nCharacters) {
        DWORD nOldPortrait = m_nSelectedCharacter;
        m_nSelectedCharacter = nPortrait;
        m_cUIManager.GetPanel(1)->GetControl(nOldPortrait)->InvalidateRect();
        m_cUIManager.GetPanel(1)->GetControl(m_nSelectedCharacter)->InvalidateRect();
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x636D40
void CScreenJournal::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1169
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1170
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1171
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

// 0x636EA0
CUIPanel* CScreenJournal::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenJournal::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1217
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Inlined.
void CScreenJournal::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1261
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Inlined.
void CScreenJournal::ResetPopupPanel(DWORD dwPanelId)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1288
    UTIL_ASSERT(pGame != NULL);

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1290
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 7:
    case 8:
    case 50:
        ResetErrorPanel(pPanel);
        break;
    case 9:
        ResetAnnotatePanel();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1305
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Uninline.
void CScreenJournal::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 7:
    case 8:
    case 9:
    case 50:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1346
        UTIL_ASSERT(FALSE);
    }
}

// 0x636EC0
void CScreenJournal::SummonPopup(DWORD dwPopupId)
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1426
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1432
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

// 0x637170
void CScreenJournal::DismissPopup()
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1477
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1494
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

// 0x637370
void CScreenJournal::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 7:
        m_nNumErrorButtons = 1;
        break;
    case 8:
        m_nNumErrorButtons = 2;
        break;
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1538
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(TRUE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1551
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1560
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1835
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENJOURNAL_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x637580
void CScreenJournal::ResetAnnotatePanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(9);

    // TODO: Incomplete.

    CUIControlButton* pBtDone = static_cast<CUIControlButton*>(pPanel->GetControl(1));
    CUIControlButton* pBtCancel = static_cast<CUIControlButton*>(pPanel->GetControl(2));
    CUIControlButton* pBtDelete = static_cast<CUIControlButton*>(pPanel->GetControl(4));
    CUIControlButton* pBtRevert = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1606
    UTIL_ASSERT(pBtDone != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1607
    UTIL_ASSERT(pBtCancel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1608
    UTIL_ASSERT(pBtDelete != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1609
    UTIL_ASSERT(pBtRevert != NULL);

    pBtDone->SetText(FetchString(11973));
    pBtCancel->SetText(FetchString(13727));
    pBtDelete->SetText(FetchString(13957));
    pBtRevert->SetText(FetchString(2240));

    pBtDone->SetEnabled(TRUE);
    pBtCancel->SetEnabled(TRUE);
    pBtDelete->SetEnabled(TRUE);
    pBtRevert->SetEnabled(TRUE);

    if (!field_EA0) {
        switch (g_pBaldurChitin->m_pObjectGame->m_cJournal.GetEntryType(field_E9C)) {
        case 0:
            pBtRevert->SetEnabled(FALSE);
            break;
        case 1:
            pBtDelete->SetEnabled(FALSE);
            // FALLTHROUGH
        case 2:
        case 4:
            if (!g_pBaldurChitin->m_pObjectGame->m_cJournal.IsEntryChanged(field_E9C)) {
                pBtRevert->SetEnabled(FALSE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
            // __LINE__: 1645
            UTIL_ASSERT(FALSE);
        }
    } else {
        pBtDelete->SetEnabled(FALSE);
        pBtRevert->SetEnabled(FALSE);
    }
}

// 0x6378B0
void CScreenJournal::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1667
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    STRREF strError;
    if (pGame->CanRestParty(strError, 0, 0, 0)) {
        m_dwErrorState = 1;
        m_dwErrorTextId = 15358;
        m_strErrorButtonText[0] = 17199;
        m_strErrorButtonText[1] = 11596;
        m_strErrorButtonText[2] = 13727;
        SummonPopup(50);
    } else {
        m_dwErrorState = 0;
        m_dwErrorTextId = strError;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(7);
    }

    renderLock.Unlock();
}

// 0x6379C0
void CScreenJournal::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1729
    UTIL_ASSERT(0 <= nButton && nButton < GetNumErrorButtons());

    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1731
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_dwErrorState) {
    case 0:
        switch (nButton) {
        case 0:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
            // __LINE__: 1773
            UTIL_ASSERT(FALSE);
        }
        break;
    case 1:
        switch (nButton) {
        case 0:
            DismissPopup();

            CInfGame::dword_8E7524 = FALSE;
            pGame->RestParty(1, 0);
            break;
        case 1:
            DismissPopup();

            CInfGame::dword_8E7524 = TRUE;
            pGame->RestParty(1, 0);
            CInfGame::dword_8E7524 = FALSE;
            break;
        case 2:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
            // __LINE__: 1760
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 1779
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x637B50
void CScreenJournal::OnCancelButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();
}

// 0x637BC0
void CScreenJournal::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// 0x637BE0
CUIControlButtonJournalScroll::CUIControlButtonJournalScroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
}

// 0x637C30
CUIControlButtonJournalScroll::~CUIControlButtonJournalScroll()
{
}

// 0x637CD0
void CUIControlButtonJournalScroll::OnLButtonClick(CPoint pt)
{
    CScreenJournal* pJournal = g_pBaldurChitin->m_pEngineJournal;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 1993
    UTIL_ASSERT(pJournal != NULL);

    switch (m_nID) {
    case 3:
        if (pJournal->m_nChapter > 0) {
            pJournal->m_nChapter--;
            pJournal->UpdateMainPanel();
            pJournal->PlayGUISound(CBaldurEngine::RESREF_SOUND_PRIESTSCROLL);
        }
        break;
    case 4:
        if (pJournal->m_nChapter <= CGameJournal::NUM_CHAPTERS - 1) {
            pJournal->m_nChapter++;
            pJournal->UpdateMainPanel();
            pJournal->PlayGUISound(CBaldurEngine::RESREF_SOUND_PRIESTSCROLL);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
        // __LINE__: 2006
        UTIL_ASSERT(pJournal != NULL);
    }
}

// 0x66EE20
void CUIControlButtonJournalScroll::OnLButtonDoubleClick(CPoint pt)
{
    OnLButtonClick(pt);
}

// 0x637D70
CUIControlButtonJournalError::CUIControlButtonJournalError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
}

// 0x637DC0
CUIControlButtonJournalError::~CUIControlButtonJournalError()
{
}

// 0x637E60
void CUIControlButtonJournalError::OnLButtonClick(CPoint pt)
{
    CScreenJournal* pJournal = g_pBaldurChitin->m_pEngineJournal;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\infscreenjournal.cpp
    // __LINE__: 2058
    UTIL_ASSERT(pJournal != NULL);

    pJournal->OnErrorButtonClick(m_nID);
}

#include "CScreenSpellbook.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUIControlScrollBar.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x667EC0
CScreenSpellbook::CScreenSpellbook()
{
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
    m_pVirtualKeys[90] = CKeyInfo(VK_PRIOR, -1, 0);
    m_pVirtualKeys[91] = CKeyInfo(VK_NEXT, -1, 0);

    m_nSpellLevel = 0;
    m_nClassIndex = 11;
    field_454 = 0;
    field_458 = 0;
    field_442 = 0;
    field_536 = 0;
    field_53A = 0;
    field_53E = 0;
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    field_57E = 0;
    field_582 = 0;
    m_bCtrlKeyDown = FALSE;
    field_446 = 0;
    field_44A = 0;
    field_1488 = 0;

    for (int index = 0; index < 24; index++) {
        field_148C[index] = CResRef();
        field_154C[index] = 0;
        field_15AC[index] = 0;
    }

    field_1670 = 0;

    for (int index = 0; index < CSPELLLIST_NUM_CLASSES; index++) {
        field_1654[index] = 0;
    }
}

// 0x668C60
CScreenSpellbook::~CScreenSpellbook()
{
}

// 0x49FC40
BOOL CScreenSpellbook::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x668C20
void CScreenSpellbook::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x668D10
void CScreenSpellbook::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESML"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    m_preLoadFontTool.SetResRef(CResRef("TOOLFONT"), FALSE, TRUE);
    m_preLoadFontTool.RegisterFont();

    UpdateMainPanel();
    UpdateCursorShape(0);
    CheckEnablePortaits(1);
    CheckEnableLeftPanel();
    m_cUIManager.InvalidateRect(NULL);
}

// 0x668E30
void CScreenSpellbook::EngineDeactivated()
{
    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            }
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x668ED0
void CScreenSpellbook::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUISPL"), g_pBaldurChitin->field_4A28);

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

    m_nSelectedCharacter = -1;
    m_pCurrentScrollBar = NULL;
    m_nSpellLevel = 0;
    field_536 = 0;
    field_53A = 0;
    field_53E = 0;
    field_442 = 0;
    field_55E = "";

    for (int index = 0; index < 24; index++) {
        field_148C[index] = CResRef();
        field_154C[index] = 0;
    }

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);

    // NOTE: Uninline.
    field_45C.SetResRef(CResRef("FLASH"), g_pBaldurChitin->field_4A28, TRUE);
}

// 0x49FC40
BOOL CScreenSpellbook::CheckMouseLButton()
{
    return TRUE;
}

// 0x6696D0
void CScreenSpellbook::OnLButtonDblClk(CPoint pt)
{
    if (!field_53E && !field_53A) {
        m_cUIManager.OnLButtonDblClk(pt);
    }
}

// 0x669700
void CScreenSpellbook::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;

    if (!field_53E && !field_53A) {
        m_cUIManager.OnLButtonDown(pt);
    }
}

// 0x669740
void CScreenSpellbook::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;

    if (!field_53E && !field_53A) {
        m_cUIManager.OnLButtonUp(pt);
    }
}

// 0x49FC40
BOOL CScreenSpellbook::CheckMouseMove()
{
    return TRUE;
}

// 0x669780
void CScreenSpellbook::OnMouseMove(CPoint pt)
{
    if (!field_53E && !field_53A) {
        m_cUIManager.OnMouseMove(pt);
    }
}

// 0x49FC40
BOOL CScreenSpellbook::CheckMouseRButton()
{
    return TRUE;
}

// 0x6697B0
void CScreenSpellbook::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;

    if (!field_53E && !field_53A) {
        m_cUIManager.OnRButtonDown(pt);
    }
}

// 0x6697F0
void CScreenSpellbook::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;

    if (!field_53E && !field_53A) {
        m_cUIManager.OnRButtonUp(pt);
    }
}

// 0x686660
SHORT CScreenSpellbook::GetNumVirtualKeys()
{
    return CSCREENSPELLBOOK_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenSpellbook::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x668C30
BYTE* CScreenSpellbook::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x66A010
int CScreenSpellbook::sub_66A010(DWORD nIndex)
{
    // __FILE__: .\Include\InfScreenSpellbook.h
    // __LINE__: 76
    UTIL_ASSERT(nIndex < CSPELLLIST_NUM_CLASSES);

    return field_1654[nIndex];
}

// 0x66A100
void CScreenSpellbook::SetSpellLevel(INT nLevel)
{
    if (nLevel < 0 && nLevel >= 9) {
        return;
    }

    m_nSpellLevel = nLevel;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 1182
    UTIL_ASSERT(pGame != NULL);

    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pSprite->m_nLastSpellbookSpellLevel = static_cast<BYTE>(nLevel);

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x66A1C0
void CScreenSpellbook::SetClassIndex(DWORD nNewClassIndex)
{
    DWORD nNumberOfSpellClasses = m_nNumberOfSpellClasses;
    DWORD nIndex = m_nClassIndex;

    // __FILE__: .\Include\InfScreenSpellbook.h
    // __LINE__: 76
    UTIL_ASSERT(nIndex < CSPELLLIST_NUM_CLASSES);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 1236
    UTIL_ASSERT(pGame != NULL);

    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 1252
        UTIL_ASSERT(nNewClassIndex < nNumberOfSpellClasses);

        pSprite->m_nLastSpellbookClassIndex = static_cast<BYTE>(nNewClassIndex);
        m_nClassIndex = static_cast<BYTE>(nNewClassIndex);

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x66A2D0
void CScreenSpellbook::sub_66A2D0()
{
    // TODO: Incomplete.
}

// 0x66A540
void CScreenSpellbook::TimerAsynchronousUpdate()
{
    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);
    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x66A580
void CScreenSpellbook::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();

    for (INT nIndex = 0; nIndex < m_lPopupStack.GetCount(); nIndex++) {
        POSITION pos = m_lPopupStack.FindIndex(nIndex);
        if (pos != NULL) {
            CUIPanel* pPanel = m_lPopupStack.GetAt(pos);
            pPanel->SetActive(TRUE);
            pPanel->SetInactiveRender(TRUE);
            pPanel->InvalidateRect(NULL);

            switch (pPanel->m_nID) {
            case 3:
                // NOTE: Inlining.
                if (1) {
                    CUIPanel* pPanel = m_cUIManager.GetPanel(3);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                    // __LINE__: 2638
                    UTIL_ASSERT(pPanel != NULL);

                    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(5));

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                    // __LINE__: 2641
                    UTIL_ASSERT(pDone != NULL);

                    // NOTE: Inlining.
                    if (1) {
                        CUIPanel* pPanel = GetTopPopup();

                        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                        // __LINE__: 2323
                        UTIL_ASSERT(pPanel != NULL);

                        switch (pPanel->m_nID) {
                        case 3:
                        case 4:
                        case 5:
                            pDone->SetEnabled(TRUE);
                            break;
                        default:
                            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                            // __LINE__: 2335
                            UTIL_ASSERT(pPanel != NULL);
                        }
                    }
                }
                break;
            case 4:
            case 5:
            case 50:
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                // __LINE__: 2145
                UTIL_ASSERT(FALSE);
            }
        }
    }

    pVidMode->Flip(TRUE);
    sub_66A2D0();
}

// 0x66A750
void CScreenSpellbook::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 4222
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 4223
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 4224
    UTIL_ASSERT(pRightPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pMainPanel->GetControl(54));
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

// 0x66A980
void CScreenSpellbook::UpdateMainPanel()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
CUIPanel* CScreenSpellbook::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x66B3C0
void CScreenSpellbook::SummonPopup(DWORD dwPopupId)
{
    // TODO: Incomplete.
}

// 0x66B6F0
void CScreenSpellbook::DismissPopup()
{
    // TODO: Incomplete.
}

// 0x66B960
void CScreenSpellbook::OnDoneButtonClick()
{
    CUIPanel* pPanel;

    pPanel = GetTopPopup();
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 4:
        case 5:
        case 50:
            OnErrorButtonClick(0);
            return;
        }
    }

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 2323
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
    case 4:
    case 5:
        // NOTE: Inlining.
        if (1) {
            CUIPanel* pPanel = GetTopPopup();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
            // __LINE__: 2388
            UTIL_ASSERT(pPanel != NULL);

            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
            // __LINE__: 2390
            UTIL_ASSERT(pGame != NULL);

            switch (pPanel->m_nID) {
            case 3:
                DismissPopup();
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
                // __LINE__: 2399
                UTIL_ASSERT(FALSE);
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 2335
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x66BB00
void CScreenSpellbook::OnCancelButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = GetTopPopup();

    switch (pPanel->m_nID) {
    case 3:
    case 4:
    case 5:
    case 50:
        DismissPopup();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 2447
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x66BBE0
void CScreenSpellbook::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 2485
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
        SummonPopup(4);
    }

    renderLock.Unlock();
}

// 0x66BEE0
void CScreenSpellbook::ResetErrorPanel(CUIPanel* pPanel)
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
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 2682
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 2695
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 2704
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
        // __LINE__: 2879
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENSPELLBOOK_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x66C0F0
void CScreenSpellbook::OnErrorButtonClick(INT nButton)
{
    // TODO: Incomplete.
}

// 0x66C360
void CScreenSpellbook::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// -----------------------------------------------------------------------------

// 0x66E9E0
CUIControlButtonSpellbookPopupDone::CUIControlButtonSpellbookPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    SetText(CBaldurEngine::FetchString(11973));
}

// 0x66EA90
CUIControlButtonSpellbookPopupDone::~CUIControlButtonSpellbookPopupDone()
{
}

// 0x66EB30
void CUIControlButtonSpellbookPopupDone::OnLButtonClick(CPoint pt)
{
    CScreenSpellbook* pSpellbook = g_pBaldurChitin->m_pEngineSpellbook;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 4398
    UTIL_ASSERT(pSpellbook != NULL);

    pSpellbook->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x66EB70
CUIControlButtonSpellbookError::CUIControlButtonSpellbookError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x66EBC0
CUIControlButtonSpellbookError::~CUIControlButtonSpellbookError()
{
}

// 0x66EC60
void CUIControlButtonSpellbookError::OnLButtonClick(CPoint pt)
{
    CScreenSpellbook* pSpellbook = g_pBaldurChitin->m_pEngineSpellbook;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenSpellbook.cpp
    // __LINE__: 4450
    UTIL_ASSERT(pSpellbook != NULL);

    pSpellbook->OnErrorButtonClick(m_nID);
}

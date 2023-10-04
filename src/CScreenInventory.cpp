#include "CScreenInventory.h"

#include "CBaldurChitin.h"
#include "CGameAnimationTypeCharacter.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CIcon.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define GROUND_SLOTS 5

// 0x855050
const DWORD CScreenInventory::SLOT_ID[] = {
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    5,
    6,
    7,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    68,
    69,
    70,
    71,
    72,
    81,
    22,
    24,
    25,
    23,
    21,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
};

// 0x855124
const INT CScreenInventory::NUM_SLOTS = 53;

// 0x855128
const USHORT CScreenInventory::PERSONAL_INVENTORY_SIZE = 24;

// 0x85512C
const LONG CScreenInventory::RANGE_SWAPITEM = 0x40000;

// 0x8F3FC0
const CString CScreenInventory::OPTION_PAUSE_WARNING("Inventory Pause Warning");

// 0x623EA0
CScreenInventory::CScreenInventory()
{
    m_animation.m_animation = NULL;
    field_11C = 0;
    field_11D = 0;
    m_nTopGroundItem = 0;
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    m_nAbilitiesButtonMode = 0;
    m_nUseButtonMode = 0;
    m_bMultiPlayerViewable = FALSE;

    SetVideoMode(FALSE);

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

    // FIXME: Buffer overrun.
    m_pVirtualKeys[90] = CKeyInfo(VK_PROCESSKEY, -1, 0);

    m_bCtrlKeyDown = FALSE;
    m_pTempItem = NULL;
    field_114 = 0;
    field_118 = -1;
    m_nRequesterButtonId = -1;
    m_nRequesterAmount = -1;
    field_11E = 0;
    field_11F = 0;
    field_4AC = 0;
    field_4EC = NULL;
    m_bPauseWarningDisplayed = FALSE;
    field_510 = -1;
    field_514 = -1;
    field_524 = 0;
    field_51C = 0;
    field_520 = 10;
    field_528 = 0;
}

// 0x49FC40
BOOL CScreenInventory::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x624D00
void CScreenInventory::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x699600
SHORT CScreenInventory::GetNumVirtualKeys()
{
    return CSCREENINVENTORY_VIRTUAL_KEYS;
}

// 0x624D10
CKeyInfo* CScreenInventory::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x624D20
BYTE* CScreenInventory::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x624D50
CScreenInventory::~CScreenInventory()
{
    if (m_pTempItem) {
        delete m_pTempItem;
        m_pTempItem = NULL;
    }
}

// 0x624F70
void CScreenInventory::EngineActivated()
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

    if (m_cUIManager.m_bInitialized) {
        CheckMultiPlayerViewable();

        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StartTime();
        }

        if (GetTopPopup() != NULL) {
            // NOTE: Uninline.
            UpdatePopupPanel(GetTopPopup()->m_nID);
        } else {
            UpdateMainPanel(TRUE);
        }

        if (field_528 != 0) {
            SetErrorString(11328, RGB(255, 255, 255));
            field_528 = 0;
        }

        UpdateCursorShape();
        CheckEnablePortaits(TRUE);
        CheckEnableLeftPanel();

        m_nTopGroundItem = 0;
        memset(m_nGroundPileQueried, 0, sizeof(m_nGroundPileQueried));
        m_cUIManager.InvalidateRect(NULL);

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 440
            UTIL_ASSERT(pGame != NULL);

            // NOTE: Uninline.
            LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

            CMessage103* pMessage = new CMessage103(TRUE,
                g_pChitin->cNetwork.m_idLocalPlayer,
                m_nSelectedCharacter,
                nCharacterId,
                nCharacterId);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        } else {
            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->sub_518580(g_pChitin->cNetwork.m_idLocalPlayer,
                    m_nSelectedCharacter);
            }
        }
    }
}

// 0x6252D0
void CScreenInventory::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && !g_pChitin->cNetwork.GetSessionHosting()
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 509
        UTIL_ASSERT(pGame != NULL);

        // NOTE: Uninline.
        LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

        CMessage103* pMessage = new CMessage103(FALSE,
            g_pChitin->cNetwork.m_idLocalPlayer,
            -1,
            nCharacterId,
            nCharacterId);

        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    } else {
        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->sub_518580(g_pChitin->cNetwork.m_idLocalPlayer,
                -1);
        }
    }

    if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused
        && g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StopTime();
    }
}

// 0x625490
void CScreenInventory::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIINV"), g_pBaldurChitin->field_4A28);

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

    if (m_pTempItem != NULL) {
        delete m_pTempItem;
        m_pTempItem = NULL;
    }

    m_pCurrentScrollBar = NULL;
    m_nSelectedCharacter = 0;
    m_pTempItem = NULL;
    field_114 = 0;
    field_118 = -1;
    m_nRequesterButtonId = -1;
    m_nRequesterAmount = -1;
    field_11E = 0;
    field_11F = 0;
    field_4AC = 0;
    field_4EC = NULL;
    m_bPauseWarningDisplayed = FALSE;
    field_510 = -1;
    field_514 = -1;
    field_524 = 0;
    field_51C = 0;
    field_520 = 10;
    field_528 = 0;

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(9)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 632
    UTIL_ASSERT(pPanel != NULL);

    CUIControlBase* pControl;

    pControl = pPanel->GetControl(0x10000038);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 636
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17183, -1, -1); // "Armor Class"

    pControl = pPanel->GetControl(0x10000039);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 640
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17184, -1, -1); // "Current Hit Points"

    pControl = pPanel->GetControl(0x1000003A);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 644
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17378, -1, -1); // "Maximum Hit Points"

    m_nUseButtonMode = -1;
    m_nAbilitiesButtonMode = -1;
    field_510 = -1;
    field_514 = -1;
    m_bPauseWarningDisplayed = GetPrivateProfileIntA("Game Options",
        OPTION_PAUSE_WARNING,
        0,
        g_pBaldurChitin->GetIniFileName());
}

// 0x5D72C0
void CScreenInventory::EngineGameUninit()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x6257C0
void CScreenInventory::OnKeyDown(SHORT nKeysFlags)
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseLButton()
{
    return TRUE;
}

// 0x625CD0
void CScreenInventory::OnLButtonDblClk(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x625D00
void CScreenInventory::OnLButtonDown(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonDown(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
}

// 0x625D40
void CScreenInventory::OnLButtonUp(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonUp(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseMove()
{
    return TRUE;
}

// 0x625D80
void CScreenInventory::OnMouseMove(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseRButton()
{
    return TRUE;
}

// 0x625DB0
void CScreenInventory::OnRButtonDown(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x625DE0
void CScreenInventory::OnRButtonUp(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x625E10
void CScreenInventory::TimerAsynchronousUpdate()
{
    g_pBaldurChitin->m_pEngineWorld->AsynchronousUpdate(FALSE);

    if (field_524 >= 0) {
        if (field_524 == 0) {
            CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
            renderLock.Lock(INFINITE);

            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1071
            UTIL_ASSERT(pGame != NULL);

            LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (field_520 <= CSPELLLIST_MAX_LEVELS) {
                    m_nErrorState = 4;

                    UINT nIndex = 0;
                    if (pSprite->GetSpellsAtLevel(5, field_520 - 1)->Find(field_51C, nIndex)) {
                        m_strErrorText = 10830;
                        PlayGUISound(CResRef("GAM_44"));
                    } else {
                        m_strErrorText = 10831;
                        PlayGUISound(CResRef("EFF_M10"));
                    }

                    m_strErrorButtonText[0] = 11973;
                    SummonPopup(7);
                }

                pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }

            renderLock.Unlock();
        }
        field_524--;
    }

    UpdateCursorShape();
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x626050
INT CScreenInventory::GetSlotByPosition(CPoint pt)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);
    CUIControlBase* pControl;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1151
    UTIL_ASSERT(pPanel != NULL);

    for (INT nIndex = 0; nIndex < NUM_SLOTS; nIndex++) {
        pControl = pPanel->GetControl(SLOT_ID[nIndex]);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1158
        UTIL_ASSERT(pControl != NULL);

        if (pControl->IsOver(pt)) {
            return pControl->m_nID;
        }
    }

    pControl = pPanel->GetControl(50);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1167
    UTIL_ASSERT(pControl != NULL);

    if (pControl->IsOver(pt)) {
        return pControl->m_nID;
    }

    return -1;
}

// 0x626140
INT CScreenInventory::GetPortraitByPosition(CPoint pt)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1200
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1202
    UTIL_ASSERT(pGame != NULL);

    for (INT nIndex = 0; nIndex < pGame->GetNumCharacters(); nIndex++) {
        CUIControlBase* pControl = pPanel->GetControl(nIndex);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1210
        UTIL_ASSERT(pControl != NULL);

        if (pControl->IsOver(pt)) {
            return pControl->m_nID;
        }
    }

    return -1;
}

// 0x626230
void CScreenInventory::TimerSynchronousUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    pGame->SynchronousUpdate();

    if (m_lPopupStack.GetCount() > 0 && m_cUIManager.field_2E == 1) {
        SHORT nPortrait;

        for (nPortrait = 0; nPortrait <= 5; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }

        for (nPortrait = 50; nPortrait <= 55; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }
    }

    m_cUIManager.Render();
    pVidMode->Flip(TRUE);

    if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineInventory) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        if (g_pBaldurChitin->m_pEngineInventory->GetTopPopup() == NULL) {
            CUIPanel* pPanel = m_cUIManager.GetPanel(2);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1272
            UTIL_ASSERT(pPanel != NULL);

            CUIControlBase* pControl = pPanel->GetControl(50);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1277
            UTIL_ASSERT(pControl != NULL);

            pControl->InvalidateRect();
        }

        renderLock.Unlock();
    }
}

// 0x626390
void CScreenInventory::OnPortraitLClick(DWORD nPortrait)
{
    // NOTE: Unsigned compare.
    if (nPortrait < static_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetNumCharacters())) {
        DWORD nOldSelectedCharacter = m_nSelectedCharacter;
        m_nSelectedCharacter = nPortrait;

        CheckMultiPlayerViewable();

        m_nTopGroundItem = 0;

        CUIPanel* pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1313
        UTIL_ASSERT(pPanel != NULL);

        CUIControlScrollBarInventoryGround* pScrollBar = static_cast<CUIControlScrollBarInventoryGround*>(pPanel->GetControl(66));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1315
        UTIL_ASSERT(pScrollBar != NULL);

        pScrollBar->UpdateScrollBar();

        UpdateCursorShape();

        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        UpdateMainPanel(TRUE);
        UpdateAppearance();

        renderLock.Unlock();

        pPanel->InvalidateRect(NULL);

        m_cUIManager.GetPanel(1)->GetControl(nOldSelectedCharacter)->InvalidateRect();
        m_cUIManager.GetPanel(1)->GetControl(m_nSelectedCharacter)->InvalidateRect();

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && !g_pChitin->cNetwork.GetSessionHosting()
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1340
            UTIL_ASSERT(pGame != NULL);

            // NOTE: Uninline.
            LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

            CMessage103* pMessage = new CMessage103(TRUE,
                g_pChitin->cNetwork.m_idLocalPlayer,
                m_nSelectedCharacter,
                nCharacterId,
                nCharacterId);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        } else {
            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->sub_518580(g_pChitin->cNetwork.m_idLocalPlayer,
                    m_nSelectedCharacter);
            }
        }
    }
}

// 0x6265E0
void CScreenInventory::SetErrorString(STRREF strError, COLORREF rgb)
{
    STR_RES strRes;

    if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineInventory) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(2);
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x1000003F));
        pLabel->SetForegroundColor(rgb);

        g_pBaldurChitin->GetTlkTable().Fetch(strError, strRes);
        pLabel->SetText(strRes.szText);

        strRes.cSound.SetChannel(0, 0);
        strRes.cSound.SetFireForget(TRUE);
        strRes.cSound.Play(FALSE);
    }
}

// 0x6266E0
void CScreenInventory::UpdatePersonalItemStatus(LONG nCharacterId)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = GetSelectedCharacter();
    if (pGame->GetCharacterId(nPortrait) == nCharacterId) {
        if (GetTopPopup() != NULL) {
            switch (GetTopPopup()->m_nID) {
            case 4:
                UpdateRequesterPanel();
                break;
            case 5:
                UpdateHistoryPanel(0);
                break;
            case 6:
                UpdateAbilitiesPanel();
                break;
            }
        } else {
            UpdateMainPanel(FALSE);
            m_cUIManager.GetPanel(2)->InvalidateRect(NULL);
        }
    }
}

// 0x626780
void CScreenInventory::UpdateContainerStatus(LONG nContainerId, SHORT nSlotNum)
{
    INT nButtonId = nSlotNum + 68;
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);

    CUIPanel* pPanel = GetTopPopup();
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 4:
            UpdateRequesterPanel();
            break;
        case 5:
            UpdateHistoryPanel(FALSE);
            break;
        case 6:
            UpdateAbilitiesPanel();
            break;
        }
    } else {
        if (nContainerId == FetchGroundPile(m_nSelectedCharacter, FALSE)) {
            if (nSlotNum != -1) {
                if (nButtonId >= 68 && nButtonId <= 81) {
                    CUIControlBase* pControl = pMainPanel->GetControl(nButtonId);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
                    // __LINE__: 1494
                    UTIL_ASSERT(pControl != NULL);

                    pControl->InvalidateRect();
                }
            } else {
                for (nButtonId = 68; nButtonId <= 81; nButtonId++) {
                    pMainPanel->GetControl(nButtonId)->InvalidateRect();
                }
            }
        }
    }
}

// 0x626880
void CScreenInventory::UpdateCursorShape()
{
    CInfCursor* pCursor = g_pBaldurChitin->GetObjectCursor();
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (pGame->m_tempCursor != 4) {
        pCursor->SetCursor(pGame->m_tempCursor, FALSE);
        return;
    }

    if (m_pTempItem == NULL) {
        pCursor->SetCursor(0, FALSE);
        return;
    }

    if (GetTopPopup() != NULL) {
        pCursor->SetCursor(0, FALSE);
        return;
    }

    INT nPointerNumber;
    if (m_pTempItem->GetMaxStackable() > 1) {
        nPointerNumber = m_pTempItem->GetUsageCount(0);
    } else {
        nPointerNumber = 0;
    }

    CResRef iconResRef = m_pTempItem->GetItemIcon();
    pCursor->SetCustomCursor(iconResRef, FALSE, nPointerNumber);
}

// 0x626940
LONG CScreenInventory::FetchGroundPile(SHORT nPortraitId, BOOL bEvenIfDead)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1593
    UTIL_ASSERT(0 <= nPortraitId && nPortraitId < CINFGAME_MAXCHARACTERS);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1595
    UTIL_ASSERT(pGame != NULL);

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        return CGameObjectArray::INVALID_INDEX;
    }

    INT nHP = pSprite->GetBaseStats()->m_hitPoints;
    CGameArea* pArea = pSprite->GetArea();

    pGame->GetObjectArray()->ReleaseShare(nCharacterId,
        CGameObjectArray::THREAD_ASYNCH,
        INFINITE);

    if (pArea == NULL || !bEvenIfDead && nHP <= 0) {
        return CGameObjectArray::INVALID_INDEX;
    }

    if (!m_nGroundPileQueried[nPortraitId]) {
        // NOTE: Looks like inlining.
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1629
        UTIL_ASSERT(pGame != NULL);

        // NOTE: Uninline.
        LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

        m_nGroundPile[nPortraitId] = pGame->GetGroundPile(nCharacterId);
        m_nGroundPileQueried[nPortraitId] = TRUE;
    }

    return m_nGroundPile[nPortraitId];
}

// 0x626AE0
void CScreenInventory::FlushGroundPiles()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1665
    UTIL_ASSERT(pGame != NULL);

    for (int index = 0; index < 6; index++) {
        if (m_nGroundPile[index] != 0
            && m_nGroundPile[index] != CGameObjectArray::INVALID_INDEX) {
            CMessageContainerAddItem* pMessage = new CMessageContainerAddItem(CItem(),
                SHORT_MAX,
                TRUE,
                m_nGroundPile[index],
                m_nGroundPile[index]);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

            m_nGroundPile[index] = 0;
        }
    }
}

// 0x626C70
void CScreenInventory::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1704
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1705
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1706
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

// 0x626DD0
void CScreenInventory::UpdateMainPanel(BOOL bClearError)
{
    CString sClass;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

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
        CAIObjectType& typeAI = pSprite->m_liveTypeAI;
        INT nHP = pSprite->GetBaseStats()->m_hitPoints;
        INT nPartyGold = pGame->m_nPartyGold;
        CCreatureFileHeader* pBStats = pSprite->GetBaseStats();
        CDerivedStats& DStats = *pSprite->GetDerivedStats();

        CUIPanel* pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1788
        UTIL_ASSERT(pPanel != NULL);

        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(66));

        if (pBStats->m_name != -1) {
            UpdateLabel(pPanel, 0x10000032, "%s", (LPCSTR)FetchString(pBStats->m_name));
        } else {
            UpdateLabel(pPanel, 0x10000032, "%s", (LPCSTR)pSprite->GetName());
        }

        pGame->GetRuleTables().GetClassStringLower(DStats.GetBestClass(),
            pBStats->m_specialization,
            pBStats->m_flags,
            sClass,
            1);

        UpdateLabel(pPanel, 0x10000040, "%d", nPartyGold);

        if (bClearError) {
            SetErrorString(-1, RGB(255, 255, 255));
        }

        CString sRace = pGame->GetRuleTables().GetRaceString(typeAI.m_nRace, 0);
        CString sSubRaceFile = pGame->GetRuleTables().m_tSrTable.GetAt(CString("SRFILE"), sRace);
        if (m_tSubRace.GetResRef() != sSubRaceFile) {
            m_tSubRace.Load(CResRef(sSubRaceFile));
        }

        INT nSubRaceListIndex = atol(m_tSubRace.GetAt(CPoint(0, typeAI.m_nSubRace)));

        CString sColorFile;

        sColorFile = pGame->GetRuleTables().m_tSrList.GetAt(CPoint(5, nSubRaceListIndex));
        if (m_tHairColor.GetResRef() != sColorFile) {
            m_tHairColor.Load(CResRef(sColorFile));
        }

        sColorFile = pGame->GetRuleTables().m_tSrList.GetAt(CPoint(6, nSubRaceListIndex));
        if (m_tSkinColor.GetResRef() != sColorFile) {
            m_tSkinColor.Load(CResRef(sColorFile));
        }

        if (m_bMultiPlayerViewable) {
            UpdateLabel(pPanel, 0x10000038, "%d", pSprite->GetAC());

            if (DStats.m_spellStates[SPLSTATE_SUPPRESS_HP_INFO]) {
                UpdateLabel(pPanel, 0x10000039, "%c", '?');
            } else {
                UpdateLabel(pPanel, 0x10000039, "%d", pBStats->m_hitPoints);
            }

            UpdateLabel(pPanel, 0x1000003A, "%d", DStats.m_nMaxHitPoints);
        } else {
            UpdateLabel(pPanel, 0x10000038, "");
            UpdateLabel(pPanel, 0x10000039, "");
            UpdateLabel(pPanel, 0x1000003A, "");
        }

        INT nCurrentWeight;
        INT nTotalWeight;
        INT nUsedSlots;
        INT nTotalSlots;
        if (m_bMultiPlayerViewable) {
            nCurrentWeight = pSprite->GetCarriedWeight();
            nTotalWeight = static_cast<INT>(static_cast<float>(pGame->GetRuleTables().GetEncumbranceMod(pSprite)) / 100.0f
                * static_cast<float>(atol(pGame->GetRuleTables().m_tStrengthMod.GetAt(CPoint(3, DStats.m_nSTR)))));
            pSprite->GetNumInventoryPersonalSlots(nUsedSlots, nTotalSlots);
        } else {
            nCurrentWeight = 0;
            nTotalWeight = 0;
            nUsedSlots = 0;
            nTotalSlots = 0;
        }

        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x10000042));

        UpdateLabel(pPanel,
            0x10000042,
            "%d / %d %s",
            nCurrentWeight,
            nTotalWeight,
            FetchString(39537)); // "lb."

        if (nCurrentWeight == 0) {
            pLabel->SetForegroundColor(RGB(255, 255, 255));
        } else {
            float fRatio = static_cast<float>(nCurrentWeight) / static_cast<float>(nTotalSlots);
            if (fRatio < 0.33f) {
                pLabel->SetForegroundColor(RGB(0, 255, 0));
            } else if (fRatio < 0.66f) {
                pLabel->SetForegroundColor(RGB(255, 255, 0));
            } else {
                pLabel->SetForegroundColor(RGB(255, 0, 0));
            }
        }

        CUIControlButtonCharacterPortrait* pPortrait = static_cast<CUIControlButtonCharacterPortrait*>(pPanel->GetControl(84));
        pPortrait->SetPortrait(CResRef(pBStats->m_portraitLarge));

        for (DWORD nButtonID = 109; nButtonID <= 112; nButtonID++) {
            CUIControlButton3State* pButton = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1914
            UTIL_ASSERT(pButton != NULL);

            pButton->SetSelected(pSprite->field_4C68 == nButtonID - 109);
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);

        if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
            && nHP < 0) {
            CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1932
            UTIL_ASSERT(pWorld != NULL);

            if (g_pBaldurChitin->GetActiveEngine() != pWorld) {
                g_pBaldurChitin->GetActiveEngine()->SelectEngine(pWorld);
            }
        }
    }
}

// 0x627560
void CScreenInventory::ResetPopupPanel(DWORD dwPanelId)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2042
    UTIL_ASSERT(pGame != NULL);

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2045
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
        if (1) {
            LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                field_11F = pSprite->GetBaseStats()->m_colors[field_11E];

                pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
        break;
    case 4:
        break;
    case 5:
        ResetHistoryPanel(pPanel);
        break;
    case 6:
        ResetAbilitiesPanel(pPanel);
        break;
    case 7:
    case 8:
    case 9:
    case 50:
        ResetErrorPanel(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 2088
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Inlined.
void CScreenInventory::UpdatePopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2116
    UTIL_ASSERT(pPanel != NULL);

    switch (dwPanelId) {
    case 3:
        break;
    case 4:
        UpdateRequesterPanel();
        break;
    case 5:
        UpdateHistoryPanel(1);
        break;
    case 6:
        UpdateAbilitiesPanel();
        break;
    case 7:
    case 8:
    case 9:
    case 50:
        // NOTE: Uninline.
        UpdateErrorPanel(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 2143
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Inlined.
CUIPanel* CScreenInventory::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenInventory::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1965
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetActive(bShow);
    pPanel->SetInactiveRender(bShow);

    if (bShow) {
        pPanel->InvalidateRect(NULL);
        PlayGUISound(RESREF_SOUND_WINDOWOPEN);
    }
}

// NOTE: Inlined.
void CScreenInventory::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2009
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);

    CheckEnableButtons();
}

// 0x627700
void CScreenInventory::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 2223
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        // NOTE: Uninline.
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2229
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

// 0x627990
void CScreenInventory::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2274
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2291
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        UpdatePopupPanel(pPanel->m_nID);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel(TRUE);
    }
}

// 0x627C20
void CScreenInventory::ResetHistoryPanel(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x627F20
void CScreenInventory::ResetAbilitiesPanel(CUIPanel* pPanel)
{
    // TODO: Incomplete.
}

// 0x628200
void CScreenInventory::SelectItemAbility()
{
    // TODO: Incomplete.
}

// 0x6285B0
void CScreenInventory::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x628D20
void CScreenInventory::OnCancelButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 2976
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 3:
    case 7:
    case 8:
    case 9:
        DismissPopup();
        break;
    case 4:
    case 5:
        m_nRequesterButtonId = -1;
        DismissPopup();
        break;
    case 6:
        if (field_4EC != NULL) {
            POSITION pos = field_4EC->GetHeadPosition();
            while (pos != NULL) {
                delete field_4EC->GetNext(pos);
            }
            field_4EC->RemoveAll();
            field_4EC = NULL;
        }
        field_4EC = NULL;
        DismissPopup();
        break;
    }

    renderLock.Unlock();
}

// 0x628E70
void CScreenInventory::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 7:
        m_nNumErrorButtons = 1;
        break;
    case 8:
        m_nNumErrorButtons = 2;
        break;
    case 9:
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3137
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_strErrorText, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3150
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3159
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3998
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENINVENTORY_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x6290C0
void CScreenInventory::UpdateErrorPanel(CUIPanel* pPanel)
{
    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3191
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(IsErrorButtonClickable(nButton));
    }
}

// 0x629120
void CScreenInventory::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3222
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    STRREF strError;
    if (pGame->CanRestParty(strError, 0, 0, 0)) {
        m_nErrorState = 1;
        m_strErrorText = 15358;
        m_strErrorButtonText[0] = 17199;
        m_strErrorButtonText[1] = 11596;
        m_strErrorButtonText[2] = 13727;
        SummonPopup(50);
    } else {
        m_nErrorState = 0;
        m_strErrorText = strError;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(7);
    }

    renderLock.Unlock();
}

// 0x629230
BOOL CScreenInventory::IsAbilitiesButtonActive()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x6294D0
void CScreenInventory::SetUseButtonMode(INT nMode)
{
    if (m_nUseButtonMode == nMode) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(5);
    if (pPanel == NULL) {
        return;
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(9));
    if (pButton == NULL) {
        return;
    }

    m_nUseButtonMode = nMode;
    switch (nMode) {
    case 0:
        pButton->SetText(FetchString(19392)); // "Drink Potion"
        break;
    case 1:
        pButton->SetText(FetchString(17104)); // "Write Magic"
        break;
    case 2:
        pButton->SetText(FetchString(10874)); // "eat berries"
        break;
    case 3:
        pButton->SetText(FetchString(24891)); // "Open Container"
        break;
    case 4:
        pButton->SetText(FetchString(32477)); // "Eat Rations"
        break;
    }
}

// 0x629660
void CScreenInventory::SetAbilitiesButtonMode(INT nMode)
{
    if (m_nAbilitiesButtonMode == nMode) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(5);
    if (pPanel == NULL) {
        return;
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(8));
    if (pButton == NULL) {
        return;
    }

    m_nAbilitiesButtonMode = nMode;
    switch (nMode) {
    case 0:
        pButton->SetText(FetchString(11960)); // "Abilities"
        break;
    case 1:
        pButton->SetText(FetchString(14133)); // "Identify"
        break;
    }
}

// 0x629740
BOOL CScreenInventory::IsUseButtonActive()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x629B90
void CScreenInventory::OnUseButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3688
    UTIL_ASSERT(pGame != NULL);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        if (IsUseButtonActive()) {
            switch (m_nUseButtonMode) {
            case 0:
            case 2:
            case 4:
                DrinkPotion();
                renderLock.Lock(INFINITE);
                DismissPopup();
                renderLock.Unlock();
                PlayGUISound(CResRef("GAM_07"));
                break;
            case 1:
                CopySpell();
                renderLock.Lock(INFINITE);
                DismissPopup();
                renderLock.Unlock();
                break;
            case 3:
                if (1) {
                    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

                    CGameSprite* pSprite;

                    BYTE rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        reinterpret_cast<CGameObject**>(&pSprite),
                        INFINITE);
                    if (rc == CGameObjectArray::SUCCESS) {
                        g_pBaldurChitin->m_pEngineWorld->StartStore(pSprite->m_liveTypeAI,
                            pSprite->m_liveTypeAI,
                            pItem->cResRef,
                            TRUE);

                        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }
                break;
            }
        }
    } else {
        renderLock.Lock(INFINITE);

        DismissPopup();
        SetErrorString(10161, RGB(255, 255, 255));

        renderLock.Unlock();
    }
}

// 0x629DB0
void CScreenInventory::OnAbilitiesButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3796
    UTIL_ASSERT(pGame != NULL);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        if (IsAbilitiesButtonActive()) {
            switch (m_nAbilitiesButtonMode) {
            case 0:
                renderLock.Lock(INFINITE);
                SummonPopup(6);
                renderLock.Unlock();
                break;
            case 1:
                renderLock.Lock(INFINITE);
                m_nErrorState = 3;
                m_strErrorText = 19394;
                m_strErrorButtonText[0] = 17105;
                m_strErrorButtonText[1] = 17106;
                m_strErrorButtonText[2] = 13727;
                SummonPopup(9);
                renderLock.Unlock();
                break;
            }
        }
    } else {
        renderLock.Lock(INFINITE);

        DismissPopup();
        SetErrorString(10161, RGB(255, 255, 255));

        renderLock.Unlock();
    }
}

// 0x629F20
void CScreenInventory::CheckEnableButtons()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(5);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        SetAbilitiesButtonMode((pItem->m_flags & 0x1) == 0);

        CUIControlButton* pAbilitiesButton = static_cast<CUIControlButton*>(pPanel->GetControl(8));
        if (pAbilitiesButton != NULL) {
            BOOLEAN bAbilitiesButtonActive = IsAbilitiesButtonActive();
            pAbilitiesButton->SetActive(bAbilitiesButtonActive);
            pAbilitiesButton->SetInactiveRender(bAbilitiesButtonActive);

            // FIXME: Calls `GetItemType` three times.
            if (pItem->GetItemType() == 9) {
                if (pItem->cResRef == "gberry") {
                    SetUseButtonMode(2);
                } else {
                    SetUseButtonMode(0);
                }
            } else if (pItem->GetItemType() == 71) {
                SetUseButtonMode(4);
            } else if (pItem->GetItemType() == 58) {
                SetUseButtonMode(3);
            } else {
                SetUseButtonMode(1);
            }

            CUIControlButton* pUseButton = static_cast<CUIControlButton*>(pPanel->GetControl(9));
            if (pUseButton != NULL) {
                BOOLEAN bUseButtonActive = IsUseButtonActive();
                pUseButton->SetActive(bUseButtonActive);
                pUseButton->SetInactiveRender(bUseButtonActive);
            }
        }
    }
}

// 0x62A060
BOOL CScreenInventory::IsErrorButtonClickable(INT nButton)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x62A2F0
void CScreenInventory::OnErrorButtonClick(INT nButton)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 4199
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    if (IsErrorButtonClickable(nButton)) {
        switch (m_nErrorState) {
        case 0:
        case 2:
        case 4:
            switch (nButton) {
            case 0:
                DismissPopup();
                break;
            }
            break;
        case 1:
            switch (nButton) {
            case 0:
                DismissPopup();

                CInfGame::m_bHealPartyOnRest = FALSE;
                pGame->RestParty(1, 0);

                break;
            case 1:
                DismissPopup();

                CInfGame::m_bHealPartyOnRest = TRUE;
                pGame->RestParty(1, 0);
                CInfGame::m_bHealPartyOnRest = FALSE;
                break;
            case 2:
                DismissPopup();
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
                // __LINE__: 4230
                UTIL_ASSERT(FALSE);
            }
            break;
        case 3:
            switch (nButton) {
            case 0:
                DismissPopup();
                IdentifyWithSpell();
                PlayGUISound(CResRef("CAS_P04"));
                break;
            case 1:
                DismissPopup();
                IdentifyWithScroll();
                PlayGUISound(CResRef("CAS_P04"));
                break;
            case 2:
                DismissPopup();
                break;
            }
            break;
        case 5:
            switch (nButton) {
            case 0:
                DismissPopup();
                break;
            }
            break;
        }
    }

    renderLock.Unlock();
}

// 0x62A4B0
void CScreenInventory::IdentifyWithSpell()
{
    // TODO: Incomplete.
}

// 0x62AE70
void CScreenInventory::IdentifyWithScroll()
{
    // TODO: Incomplete.
}

// 0x62B0B0
void CScreenInventory::CopySpell()
{
    // TODO: Incomplete.
}

// 0x62B4C0
void CScreenInventory::DrinkPotion()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 4698
    UTIL_ASSERT(pGame != NULL);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        // FIXME: Calls `GetItemType` two times.
        if (pItem->GetItemType() == 9 || pItem->GetItemType() == 71) {
            LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

            CAIObjectType drinker;
            drinker.m_nInstance = nCharacterId;

            CAIAction cUseItemAction(CAIAction::USEITEM, drinker, 0, 0, 0);
            cUseItemAction.m_specificID = MapButtonIdToInventoryId(m_nRequesterButtonId);

            CMessageAddAction* pMessage = new CMessageAddAction(cUseItemAction,
                nCharacterId,
                nCharacterId);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
}

// 0x62B7D0
void CScreenInventory::PlaySwapSound(CItem* pOldItem, CItem* pNewItem)
{
    WORD animationType;

    if (pOldItem != NULL) {
        switch (pOldItem->GetItemType()) {
        case 1:
            PlayGUISound(RESREF_SOUND_NECK2);
            break;
        case 3:
            PlayGUISound(RESREF_SOUND_BELT2);
            break;
        case 4:
            PlayGUISound(RESREF_SOUND_BOOT2);
            break;
        case 5:
            PlayGUISound(RESREF_SOUND_ARRW2);
            break;
        case 6:
            PlayGUISound(RESREF_SOUND_GLOVE2);
            break;
        case 7:
            PlayGUISound(RESREF_SOUND_HELM2);
            break;
        case 8:
            PlayGUISound(RESREF_SOUND_KEY2);
            break;
        case 9:
            PlayGUISound(RESREF_SOUND_POTN2);
            break;
        case 10:
            PlayGUISound(RESREF_SOUND_RING2);
            break;
        case 11:
            PlayGUISound(RESREF_SOUND_SCROL2);
            break;
        case 14:
            PlayGUISound(RESREF_SOUND_BULLT2);
            break;
        case 15:
            PlayGUISound(RESREF_SOUND_BOW2);
            break;
        case 16:
            PlayGUISound(RESREF_SOUND_DAGGR2);
            break;
        case 17:
            PlayGUISound(RESREF_SOUND_MACE2);
            break;
        case 18:
            PlayGUISound(RESREF_SOUND_SLING2);
            break;
        case 19:
            PlayGUISound(RESREF_SOUND_SMSWD2);
            break;
        case 20:
        case 57:
        case 69:
            PlayGUISound(RESREF_SOUND_LGSWD2);
            break;
        case 21:
            PlayGUISound(RESREF_SOUND_HAMMR2);
            break;
        case 22:
            PlayGUISound(RESREF_SOUND_MSTAR2);
            break;
        case 23:
            PlayGUISound(RESREF_SOUND_FLAIL2);
            break;
        case 24:
            PlayGUISound(RESREF_SOUND_DART2);
            break;
        case 25:
            PlayGUISound(RESREF_SOUND_AXE2);
            break;
        case 26:
            PlayGUISound(RESREF_SOUND_STAFF2);
            break;
        case 27:
            PlayGUISound(RESREF_SOUND_CROSB2);
            break;
        case 29:
            PlayGUISound(RESREF_SOUND_SPEAR2);
            break;
        case 30:
            PlayGUISound(RESREF_SOUND_HALB2);
            break;
        case 31:
            PlayGUISound(RESREF_SOUND_BOLT2);
            break;
        case 32:
            PlayGUISound(RESREF_SOUND_CLOAK2);
            break;
        case 33:
            PlayGUISound(RESREF_SOUND_GOLD2);
            break;
        case 34:
            PlayGUISound(RESREF_SOUND_GEM2);
            break;
        case 35:
            PlayGUISound(RESREF_SOUND_WAND2);
            break;
        case 36:
            PlayGUISound(RESREF_SOUND_BARM2);
            break;
        case 37:
            PlayGUISound(RESREF_SOUND_BSHD2);
            break;
        case 38:
            PlayGUISound(RESREF_SOUND_BWPN2);
            break;
        case 40:
            PlayGUISound(RESREF_SOUND_BROKN2);
            break;
        case 41:
            PlayGUISound(RESREF_SOUND_BUCKR2);
            break;
        case 42:
            PlayGUISound(RESREF_SOUND_CAND2);
            break;
        case 43:
            PlayGUISound(RESREF_SOUND_CHILD2);
            break;
        case 44:
            PlayGUISound(RESREF_SOUND_CLUB2);
            break;
        case 45:
            PlayGUISound(RESREF_SOUND_FEM2);
            break;
        case 46:
            PlayGUISound(RESREF_SOUND_KEYS2);
            break;
        case 47:
            PlayGUISound(RESREF_SOUND_LGSLD2);
            break;
        case 48:
            PlayGUISound(RESREF_SOUND_MALE2);
            break;
        case 49:
            PlayGUISound(RESREF_SOUND_MDSLD2);
            break;
        case 50:
            PlayGUISound(RESREF_SOUND_PAPR2);
            break;
        case 51:
            PlayGUISound(RESREF_SOUND_ROD2);
            break;
        case 52:
            PlayGUISound(RESREF_SOUND_SKULL2);
            break;
        case 53:
            PlayGUISound(RESREF_SOUND_SMSLD2);
            break;
        case 54:
            PlayGUISound(RESREF_SOUND_SPIDR2);
            break;
        case 55:
            PlayGUISound(RESREF_SOUND_TELE2);
            break;
        case 56:
            PlayGUISound(RESREF_SOUND_WINE2);
            break;
        case 59:
            PlayGUISound(RESREF_SOUND_8CB1D0);
            break;
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
            animationType = pOldItem->GetAnimationType();
            switch (animationType & 0xFF) {
            case 'A':
            case 'a':
                switch ((animationType >> 8) & 0xFF) {
                case '2':
                    PlayGUISound(RESREF_SOUND_LETHR2);
                    break;
                case '3':
                    PlayGUISound(RESREF_SOUND_CHAIN2);
                    break;
                case '4':
                    PlayGUISound(RESREF_SOUND_PLATE2);
                    break;
                default:
                    PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
                    break;
                }
                break;
            case 'W':
            case 'w':
                PlayGUISound(RESREF_SOUND_CLOAK2);
                break;
            default:
                PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
                break;
            }
            break;
        case 70:
            PlayGUISound(RESREF_SOUND_8CAD40);
            break;
        case 71:
            PlayGUISound(RESREF_SOUND_8CD260);
            break;
        case 72:
            PlayGUISound(RESREF_SOUND_8C8C80);
            break;
        case 73:
            PlayGUISound(RESREF_SOUND_8CD390);
            break;
        default:
            PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
            break;
        }
    } else if (pNewItem != NULL) {
        switch (pNewItem->GetItemType()) {
        case 1:
            PlayGUISound(RESREF_SOUND_NECK1);
            break;
        case 3:
            PlayGUISound(RESREF_SOUND_BELT1);
            break;
        case 4:
            PlayGUISound(RESREF_SOUND_BOOT1);
            break;
        case 5:
            PlayGUISound(RESREF_SOUND_ARRW1);
            break;
        case 6:
            PlayGUISound(RESREF_SOUND_GLOVE1);
            break;
        case 7:
            PlayGUISound(RESREF_SOUND_HELM1);
            break;
        case 8:
            PlayGUISound(RESREF_SOUND_KEY1);
            break;
        case 9:
            PlayGUISound(RESREF_SOUND_POTN1);
            break;
        case 10:
            PlayGUISound(RESREF_SOUND_RING1);
            break;
        case 11:
            PlayGUISound(RESREF_SOUND_SCROL1);
            break;
        case 14:
            PlayGUISound(RESREF_SOUND_BULLT1);
            break;
        case 15:
            PlayGUISound(RESREF_SOUND_BOW1);
            break;
        case 16:
            PlayGUISound(RESREF_SOUND_DAGGR1);
            break;
        case 17:
            PlayGUISound(RESREF_SOUND_MACE1);
            break;
        case 18:
            PlayGUISound(RESREF_SOUND_SLING1);
            break;
        case 19:
            PlayGUISound(RESREF_SOUND_SMSWD1);
            break;
        case 20:
        case 57:
        case 69:
            PlayGUISound(RESREF_SOUND_LGSWD1);
            break;
        case 21:
            PlayGUISound(RESREF_SOUND_HAMMR1);
            break;
        case 22:
            PlayGUISound(RESREF_SOUND_MSTAR1);
            break;
        case 23:
            PlayGUISound(RESREF_SOUND_FLAIL1);
            break;
        case 24:
            PlayGUISound(RESREF_SOUND_DART1);
            break;
        case 25:
            PlayGUISound(RESREF_SOUND_AXE1);
            break;
        case 26:
            PlayGUISound(RESREF_SOUND_STAFF1);
            break;
        case 27:
            PlayGUISound(RESREF_SOUND_CROSB1);
            break;
        case 29:
            PlayGUISound(RESREF_SOUND_SPEAR1);
            break;
        case 30:
            PlayGUISound(RESREF_SOUND_HALB1);
            break;
        case 31:
            PlayGUISound(RESREF_SOUND_BOLT1);
            break;
        case 32:
            PlayGUISound(RESREF_SOUND_CLOAK1);
            break;
        case 33:
            PlayGUISound(RESREF_SOUND_GOLD1);
            break;
        case 34:
            PlayGUISound(RESREF_SOUND_GEM1);
            break;
        case 35:
            PlayGUISound(RESREF_SOUND_WAND1);
            break;
        case 36:
            PlayGUISound(RESREF_SOUND_BARM1);
            break;
        case 37:
            PlayGUISound(RESREF_SOUND_BSHD1);
            break;
        case 38:
            PlayGUISound(RESREF_SOUND_BWPN1);
            break;
        case 40:
            PlayGUISound(RESREF_SOUND_BROKN1);
            break;
        case 41:
            PlayGUISound(RESREF_SOUND_BUCKR1);
            break;
        case 42:
            PlayGUISound(RESREF_SOUND_CAND1);
            break;
        case 43:
            PlayGUISound(RESREF_SOUND_CHILD1);
            break;
        case 44:
            PlayGUISound(RESREF_SOUND_CLUB1);
            break;
        case 45:
            PlayGUISound(RESREF_SOUND_FEM1);
            break;
        case 46:
            PlayGUISound(RESREF_SOUND_KEYS1);
            break;
        case 47:
            PlayGUISound(RESREF_SOUND_LGSLD1);
            break;
        case 48:
            PlayGUISound(RESREF_SOUND_MALE1);
            break;
        case 49:
            PlayGUISound(RESREF_SOUND_MDSLD1);
            break;
        case 50:
            PlayGUISound(RESREF_SOUND_PAPR1);
            break;
        case 51:
            PlayGUISound(RESREF_SOUND_ROD1);
            break;
        case 52:
            PlayGUISound(RESREF_SOUND_SKULL1);
            break;
        case 53:
            PlayGUISound(RESREF_SOUND_SMSLD1);
            break;
        case 54:
            PlayGUISound(RESREF_SOUND_SPIDR1);
            break;
        case 55:
            PlayGUISound(RESREF_SOUND_TELE1);
            break;
        case 56:
            PlayGUISound(RESREF_SOUND_WINE1);
            break;
        case 59:
            PlayGUISound(RESREF_SOUND_8CF680);
            break;
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
            animationType = pNewItem->GetAnimationType();
            switch (animationType & 0xFF) {
            case 'A':
            case 'a':
                switch ((animationType >> 8) & 0xFF) {
                case '2':
                    PlayGUISound(RESREF_SOUND_LETHR1);
                    break;
                case '3':
                    PlayGUISound(RESREF_SOUND_CHAIN1);
                    break;
                case '4':
                    PlayGUISound(RESREF_SOUND_PLATE1);
                    break;
                default:
                    PlayGUISound(RESREF_SOUND_EQUIP_TAKE_GENERIC);
                    break;
                }
                break;
            case 'W':
            case 'w':
                PlayGUISound(RESREF_SOUND_CLOAK1);
                break;
            default:
                PlayGUISound(RESREF_SOUND_EQUIP_TAKE_GENERIC);
                break;
            }
            break;
        case 70:
            PlayGUISound(RESREF_SOUND_8CF698);
            break;
        case 71:
            PlayGUISound(RESREF_SOUND_8CF628);
            break;
        case 72:
            PlayGUISound(RESREF_SOUND_8CAD98);
            break;
        case 73:
            PlayGUISound(RESREF_SOUND_8CB1B0);
            break;
        }
    }
}

// 0x62C4E0
void CScreenInventory::CancelEngine()
{
    // TODO: Incomplete.
}

// 0x62C900
void CScreenInventory::UpdateCharacterStatus(LONG nCharacterId)
{
    CBaldurEngine::UpdateCharacterStatus(nCharacterId);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if (pGame != NULL) {
        SHORT nPortrait = GetSelectedCharacter();
        if (pGame->GetCharacterId(nPortrait) == nCharacterId) {
            if (GetTopPopup() == NULL) {
                UpdateMainPanel(FALSE);
            }
        }
    }
}

// 0x62C970
void CScreenInventory::CheckMultiPlayerViewable()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5623
    UTIL_ASSERT(pGame != NULL);

    m_bMultiPlayerViewable = TRUE;

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
        if (pSprite->Orderable(1)) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID) {
                m_bMultiPlayerViewable = TRUE;
            } else {
                if (g_pChitin->cNetwork.GetSessionOpen()) {
                    m_bMultiPlayerViewable = g_pChitin->cNetwork.GetSessionHosting()
                        || pGame->m_singlePlayerPermissions.GetSinglePermission(CGamePermission::LEADER);
                }
            }
        } else {
            m_bMultiPlayerViewable = FALSE;
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x62CAA0
void CScreenInventory::UnPauseGame()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5754
    UTIL_ASSERT(pGame != NULL);

    if (g_pChitin->cNetwork.GetSessionOpen() != TRUE) {
        if (g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            if (pGame->m_singlePlayerPermissions.m_bPermissions[CGamePermission::PAUSING]) {
                if (m_bPauseWarningDisplayed) {
                    SetErrorString(19381, RGB(255, 0, 0));
                } else {
                    renderLock.Lock(INFINITE);

                    m_nErrorState = 2;
                    m_strErrorText = 19381;
                    m_strErrorButtonText[0] = 11973;
                    SummonPopup(7);

                    renderLock.Unlock();

                    m_bPauseWarningDisplayed = TRUE;

                    WritePrivateProfileStringA("Game Options",
                        OPTION_PAUSE_WARNING,
                        "1",
                        g_pBaldurChitin->GetIniFileName());
                }

                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            } else {
                renderLock.Lock(INFINITE);

                m_nErrorState = 5;
                m_strErrorText = 10920;
                m_strErrorButtonText[0] = 11973;
                SummonPopup(7);

                renderLock.Unlock();
            }
        } else {
            pGame->GetWorldTimer()->StartTime();
        }
    }
}

// 0x62CC50
void CScreenInventory::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5842
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5844
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x62CD60
void CScreenInventory::IsCharacterInRange()
{
    // TODO: Incomplete.
}

// 0x62CF50
void CScreenInventory::UpdatePartyGoldStatus()
{
    if (GetTopPopup() == NULL) {
        UpdateMainPanel(FALSE);
    }
}

// 0x631640
void CScreenInventory::UpdateRequesterPanel()
{
    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(4);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9306
        UTIL_ASSERT(pPanel != NULL);

        CUIControlButtonInventoryRequesterItem* pButton = static_cast<CUIControlButtonInventoryRequesterItem*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9308
        UTIL_ASSERT(pButton != NULL);

        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(6));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9310
        UTIL_ASSERT(pEdit != NULL);

        m_nRequesterAmount = min(m_nRequesterAmount, wCount);

        char buffer[80];
        sprintf(buffer, "%d", m_nRequesterAmount);

        pEdit->SetText(CString(buffer));
        pEdit->InvalidateRect();

        pButton->m_resRef = cResItem;
        pButton->InvalidateRect();
    }
}

// 0x631790
void CScreenInventory::UpdateHistoryPanel(BOOL a1)
{
    // TODO: Incomplete.
}

// 0x631A20
void CScreenInventory::UpdateAbilitiesPanel()
{
    // TODO: Incomplete.
}

// 0x630930
BOOL CScreenInventory::SwapWithAppearance()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x630BD0
INT CScreenInventory::MapButtonIdToInventoryId(INT nButton)
{
    switch (nButton) {
    case 5:
        return 15;
    case 6:
        return 16;
    case 7:
        return 17;
    case 11:
        return 1;
    case 12:
        return 5;
    case 13:
        return 6;
    case 14:
        return 0;
    case 15:
        return 11;
    case 16:
        return 12;
    case 17:
        return 13;
    case 21:
        return 2;
    case 22:
        return 7;
    case 23:
        return 8;
    case 24:
        return 4;
    case 25:
        return 3;
    case 30:
        return 18;
    case 31:
        return 19;
    case 32:
        return 20;
    case 33:
        return 21;
    case 34:
        return 22;
    case 35:
        return 23;
    case 36:
        return 24;
    case 37:
        return 25;
    case 38:
        return 26;
    case 39:
        return 27;
    case 40:
        return 28;
    case 41:
        return 29;
    case 42:
        return 30;
    case 43:
        return 31;
    case 44:
        return 32;
    case 45:
        return 33;
    case 73:
        return 34;
    case 74:
        return 35;
    case 75:
        return 36;
    case 76:
        return 37;
    case 77:
        return 38;
    case 78:
        return 39;
    case 79:
        return 40;
    case 80:
        return 41;
    case 101:
        return 43;
    case 102:
        return 44;
    case 103:
        return 45;
    case 104:
        return 46;
    case 105:
        return 47;
    case 106:
        return 48;
    case 107:
        return 49;
    case 108:
        return 50;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 8838
        UTIL_ASSERT(FALSE);
    }
}

// 0x630EB0
INT CScreenInventory::MapInventoryIdToButtonId(INT nInventoryId)
{
    switch (nInventoryId) {
    case 0:
        return 14;
    case 1:
        return 11;
    case 2:
        return 21;
    case 3:
        return 25;
    case 4:
        return 24;
    case 5:
        return 12;
    case 6:
        return 13;
    case 7:
        return 22;
    case 8:
        return 23;
    case 11:
        return 15;
    case 12:
        return 16;
    case 13:
        return 17;
    case 15:
        return 5;
    case 16:
        return 6;
    case 17:
        return 7;
    case 18:
        return 30;
    case 19:
        return 31;
    case 20:
        return 32;
    case 21:
        return 33;
    case 22:
        return 34;
    case 23:
        return 35;
    case 24:
        return 36;
    case 25:
        return 37;
    case 26:
        return 38;
    case 27:
        return 39;
    case 28:
        return 40;
    case 29:
        return 41;
    case 30:
        return 42;
    case 31:
        return 43;
    case 32:
        return 44;
    case 33:
        return 45;
    case 34:
        return 73;
    case 35:
        return 74;
    case 36:
        return 75;
    case 37:
        return 76;
    case 38:
        return 77;
    case 39:
        return 78;
    case 40:
        return 79;
    case 41:
        return 80;
    case 43:
        return 101;
    case 44:
        return 102;
    case 45:
        return 103;
    case 46:
        return 104;
    case 47:
        return 105;
    case 48:
        return 106;
    case 49:
        return 107;
    case 50:
        return 108;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9010
        UTIL_ASSERT(FALSE);
    }
}

// 0x631130
BOOL CScreenInventory::MapButtonIdToItemInfo(INT nButton, CItem*& pItem, STRREF& description, CResRef& cResIcon, CResRef& cResItem, WORD& wCount)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9042
    UTIL_ASSERT(pGame != NULL);

    description = -1;
    cResIcon = "";
    cResItem = "";
    wCount = 0;

    switch (nButton) {
    case 5:
    case 6:
    case 7:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 73:
    case 74:
    case 75:
    case 76:
    case 77:
    case 78:
    case 79:
    case 80:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
        pGame->InventoryInfoPersonal(m_nSelectedCharacter,
            MapButtonIdToInventoryId(nButton),
            pItem,
            description,
            cResIcon,
            cResItem,
            wCount,
            TRUE);
        return TRUE;
    case 68:
    case 69:
    case 70:
    case 71:
    case 72:
    case 81:
        if (1) {
            LONG nContainerId = FetchGroundPile(m_nSelectedCharacter, FALSE);
            if (nContainerId != CGameObjectArray::INVALID_INDEX) {
                pGame->InventoryInfoGround(nContainerId,
                    m_nTopGroundItem + nButton - 68,
                    pItem,
                    description,
                    cResIcon,
                    cResItem,
                    wCount);
            }
        }
        return TRUE;
    }

    pItem = NULL;
    return FALSE;
}

// 0x62EEA0
void CScreenInventory::UpdateAppearance()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = m_nSelectedCharacter;

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->m_derivedStats.m_generalState & STATE_DEAD) == 0) {
            CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
            renderLock.Lock(INFINITE);

            // NOTE: Uninline.
            m_animation.SetAnimationType(pSprite->GetBaseStats()->m_animationType,
                pSprite->GetBaseStats()->m_colors,
                2);

            // NOTE: Probably unsafe cast.
            static_cast<CGameAnimationTypeCharacter*>(m_animation.m_animation)->field_1444 = g_pBaldurChitin->field_4A28;

            CGameAnimationType* animation = pSprite->m_animation.m_animation;
            pSprite->m_animation.m_animation = m_animation.m_animation;
            pSprite->UnequipAll(TRUE);
            pSprite->EquipAll(TRUE);
            pSprite->m_animation.m_animation = animation;

            // FIXME: Unused.
            CString resBody;
            CString resWeapon;
            CString resShield;
            CString resHelmet;

            // NOTE: Uninline.
            m_animation.GetCurrentResRef(resBody, resWeapon, resShield, resHelmet);

            // NOTE: Uninline.
            m_animation.SetSequence(pSprite->GetIdleSequence());

            renderLock.Unlock();
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x62F100
void CScreenInventory::BeginSwap()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = m_nSelectedCharacter;

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->m_derivedStats.m_generalState & STATE_DEAD) == 0) {
            CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
            renderLock.Lock(INFINITE);

            CGameAnimationType* animation = pSprite->m_animation.m_animation;
            pSprite->m_animation.m_animation = m_animation.m_animation;
            pSprite->UnequipAll(TRUE);
            pSprite->m_animation.m_animation = animation;

            renderLock.Unlock();
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x62F230
void CScreenInventory::EndSwap()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = m_nSelectedCharacter;

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if ((pSprite->m_derivedStats.m_generalState & STATE_DEAD) == 0) {
            CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
            renderLock.Lock(INFINITE);

            CGameAnimationType* animation = pSprite->m_animation.m_animation;
            pSprite->m_animation.m_animation = m_animation.m_animation;
            pSprite->EquipAll(TRUE);
            pSprite->m_animation.m_animation = animation;

            renderLock.Unlock();
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x62F360
BOOL CScreenInventory::SwapWithSlot(INT nButtonId, BOOL bShowError, WORD wCount, BOOL bAutoStacking)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x6305B0
BOOL CScreenInventory::SwapWithPortrait(INT nButtonId, BOOL bShowError)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x6312D0
void CScreenInventory::SwapWithWeaponSet(UINT nIndex)
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
void CScreenInventory::OnRequesterMinusButtonClick()
{
    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        if (m_nRequesterAmount > 1) {
            m_nRequesterAmount = min(m_nRequesterAmount - 1, wCount);
            UpdateRequesterPanel();
        }
    }
}

// NOTE: Inlined.
void CScreenInventory::OnRequesterPlusButtonClick()
{
    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    MapButtonIdToItemInfo(m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);

    if (pItem != NULL) {
        if (m_nRequesterAmount < wCount) {
            m_nRequesterAmount = min(m_nRequesterAmount + 1, wCount);
            UpdateRequesterPanel();
        }
    }
}

// -----------------------------------------------------------------------------

// 0x62CF70
CUIControlButtonInventorySlot::CUIControlButtonInventorySlot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON | RBUTTON, 1)
{
    field_666 = FALSE;
    field_66A = FALSE;
    SetNeedAsyncUpdate();
}

// 0x62D010
CUIControlButtonInventorySlot::~CUIControlButtonInventorySlot()
{
}

// 0x62D760
void CUIControlButtonInventorySlot::OnMouseMove(CPoint pt)
{
    if (field_666) {
        if (!IsOver(pt)) {
            field_66A = TRUE;
        }
    }
}

// 0x62D7B0
BOOL CUIControlButtonInventorySlot::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    m_bPressed = TRUE;
    m_pPanel->m_pManager->SetCapture(this, CUIManager::MOUSELBUTTON);

    InvalidateRect();

    m_pPanel->m_pManager->field_2D = 0;
    m_pPanel->m_pManager->field_32 = m_nID;
    m_pPanel->m_pManager->field_1C = 0;

    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 6524
    UTIL_ASSERT(pInventory != NULL);

    if (!pInventory->m_bMultiPlayerViewable) {
        return FALSE;
    }

    pInventory->BeginSwap();
    pInventory->SwapWithSlot(m_nID, TRUE, -1, TRUE);
    pInventory->EndSwap();

    field_666 = TRUE;
    field_66A = FALSE;

    return TRUE;
}

// 0x62D890
void CUIControlButtonInventorySlot::OnLButtonUp(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 6585
    UTIL_ASSERT(pInventory != NULL);

    if (pInventory->m_bMultiPlayerViewable && field_666) {
        if (IsOver(pt)) {
            if (field_66A) {
                pInventory->BeginSwap();
                pInventory->SwapWithSlot(m_nID, TRUE, -1, TRUE);
                pInventory->EndSwap();
            }
        } else {
            INT nSlot = pInventory->GetSlotByPosition(pt);
            if (nSlot == -1) {
                INT nPortrait = pInventory->GetPortraitByPosition(m_pPanel->m_ptOrigin + pt);
                if (nPortrait != -1) {
                    pInventory->BeginSwap();
                    pInventory->SwapWithPortrait(nPortrait, TRUE);
                    pInventory->EndSwap();
                } else {
                    pInventory->BeginSwap();
                    pInventory->SwapWithSlot(m_nID, TRUE, -1, TRUE);
                    pInventory->EndSwap();
                }
            } else if (nSlot == 50) {
                pInventory->BeginSwap();
                if (!pInventory->SwapWithAppearance()) {
                    pInventory->SwapWithSlot(m_nID, FALSE, -1, TRUE);
                }
                pInventory->EndSwap();
            } else {
                pInventory->BeginSwap();
                if (!pInventory->SwapWithSlot(nSlot, TRUE, -1, TRUE)) {
                    pInventory->SwapWithSlot(m_nID, FALSE, -1, TRUE);
                }
                pInventory->EndSwap();
            }
        }
        field_666 = FALSE;
    }

    CUIControlButton::OnLButtonUp(pt);
}

// 0x62DA20
void CUIControlButtonInventorySlot::OnLButtonDoubleClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x62DBF0
void CUIControlButtonInventorySlot::OnRButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 6767
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 6769
    UTIL_ASSERT(pGame != NULL);

    if (pInventory->m_bMultiPlayerViewable == TRUE) {
        CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
        renderLock.Lock(INFINITE);

        LONG nCharacterId = pInventory->GetSelectedCharacter();

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_1,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            BOOLEAN bIsLocal;
            if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                bIsLocal = g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID;
            } else {
                bIsLocal = TRUE;
            }

            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_1,
                INFINITE);

            if (bIsLocal) {
                CItem* pItem;
                STRREF description;
                CResRef cResIcon;
                CResRef cResItem;
                WORD wCount;

                if ((m_nID < 68 || m_nID > 72) && m_nID != 81) {
                    pInventory->MapButtonIdToItemInfo(pInventory->m_nRequesterButtonId,
                        pItem,
                        description,
                        cResIcon,
                        cResItem,
                        wCount);

                    if (pItem != NULL) {
                        pInventory->m_nRequesterButtonId = m_nID;
                        pInventory->SummonPopup(5);
                    }
                }
            }
        }

        renderLock.Unlock();
    }
}

// 0x62DDE0
BOOL CUIControlButtonInventorySlot::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x7797B0
CUIControlButtonInventoryAppearance::CUIControlButtonInventoryAppearance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x779800
CUIControlButtonInventoryAppearance::~CUIControlButtonInventoryAppearance()
{
}

// 0x62E770
BOOL CUIControlButtonInventoryAppearance::OnLButtonDown(CPoint pt)
{
    if (!m_bActive) {
        return FALSE;
    }

    if ((m_nMouseButtons & LBUTTON) == 0) {
        return FALSE;
    }

    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    if (!pInventory->m_bMultiPlayerViewable) {
        return FALSE;
    }

    pInventory->BeginSwap();
    pInventory->SwapWithAppearance();
    pInventory->EndSwap();

    return TRUE;
}

// 0x62E7D0
BOOL CUIControlButtonInventoryAppearance::Render(BOOL bForce)
{
    // 0x8F3FC4
    static SHORT nPrevFrame;

    // FIXME: Unused.
    CVidCell v1;
    CVidCell v2;
    CVidCell v3;
    CVidCell v4;
    CString v5;
    CString v6;
    CString v7;
    CString v8;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderLock.Lock(INFINITE);
        m_nRenderCount--;
        renderLock.Unlock();
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 7364
    UTIL_ASSERT(pGame != NULL && pInventory != NULL);

    INT nCharacterId = pGame->GetCharacterId(pInventory->GetSelectedCharacter());

    CGameSprite* pSprite;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc != CGameObjectArray::SUCCESS) {
        return FALSE;
    }

    if (pInventory->m_bMultiPlayerViewable == TRUE && pSprite->m_animation.m_animation != NULL) {
        CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderLock.Lock(INFINITE);

        CPoint ptPos(m_pPanel->m_ptOrigin.x + m_ptOrigin.x + m_size.cx / 2,
            m_pPanel->m_ptOrigin.y + m_ptOrigin.y + m_size.cy / 2);
        CSize size(128 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1),
            160 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1));

        CRect rPreview(ptPos, size);

        CRect rClip;
        rClip.IntersectRect(rPreview, m_rDirty);

        // FIXME: Creates area on every render.
        CGameArea* pArea = new CGameArea(0);
        CInfinity* pInfinity = pArea->GetInfinity();
        pInfinity->pVidMode = g_pBaldurChitin->GetCurrentVideoMode();
        pInfinity->rViewPort.SetRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);

        SHORT nCurrentFrame = pSprite->m_animation.m_animation->GetCurrentFrame();
        if (nCurrentFrame != nPrevFrame) {
            pInventory->m_animation.m_animation->IncrementFrame();
            if (pInventory->m_animation.m_animation->IsEndOfSequence()) {
                pInventory->m_animation.SetSequence(pSprite->GetIdleSequence());
            }
        }
        nPrevFrame = nCurrentFrame;

        CRect rFx;
        CPoint ptReference;
        pInventory->m_animation.CalculateFxRect(rFx, ptReference, 0);

        ptPos.x += pInfinity->nCurrentX;
        ptPos.y += pInfinity->nCurrentY + 25;

        pInventory->m_animation.Render(pInfinity,
            pInfinity->pVidMode,
            0,
            rFx,
            ptPos,
            ptReference,
            0x20000,
            RGB(255, 255, 255),
            rClip,
            FALSE,
            FALSE,
            0,
            0);

        delete pArea;

        renderLock.Unlock();

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            INFINITE);
    }

    // NOTE: Always returns `FALSE` which is a bit odd.
    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x6314F0
CUIControlButtonInventoryWeaponSet::CUIControlButtonInventoryWeaponSet(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
}

// 0x631540
CUIControlButtonInventoryWeaponSet::~CUIControlButtonInventoryWeaponSet()
{
}

// 0x6315E0
void CUIControlButtonInventoryWeaponSet::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9262
    UTIL_ASSERT(pInventory != NULL);

    if (pInventory->m_bMultiPlayerViewable) {
        pInventory->BeginSwap();
        pInventory->SwapWithWeaponSet(m_nID - 109);
        pInventory->EndSwap();
    }
}

// -----------------------------------------------------------------------------

// 0x631E10
CUIControlButtonInventoryColor::CUIControlButtonInventoryColor(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_pDecal = new CVidCell(CResRef("COLGRAD"), m_pPanel->m_pManager->m_bDoubleSize);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9526
    UTIL_ASSERT(m_pDecal != NULL);

    m_pDecal->SequenceSet(0);

    m_pPalette = new CVidPalette(CVidPalette::TYPE_RANGE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9532
    UTIL_ASSERT(m_pPalette != NULL);

    switch (m_nID) {
    case 62:
        SetToolTipStrRef(12007, -1, -1);
        break;
    case 63:
        SetToolTipStrRef(12008, -1, -1);
        break;
    case 82:
        SetToolTipStrRef(37560, -1, -1);
        break;
    case 83:
        SetToolTipStrRef(37559, -1, -1);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9554
        UTIL_ASSERT(FALSE);
    }
}

// 0x632050
CUIControlButtonInventoryColor::~CUIControlButtonInventoryColor()
{
    if (m_pDecal != NULL) {
        delete m_pDecal;
        m_pDecal = NULL;
    }

    if (m_pPalette != NULL) {
        delete m_pPalette;
        m_pPalette = NULL;
    }
}

// 0x632140
void CUIControlButtonInventoryColor::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    if (pInventory->m_bMultiPlayerViewable == TRUE) {
        switch (m_nID) {
        case 62:
            pInventory->field_11E = 2;
            break;
        case 63:
            pInventory->field_11E = 1;
            break;
        case 82:
            pInventory->field_11E = 6;
            break;
        case 83:
            pInventory->field_11E = 3;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 9635
            UTIL_ASSERT(FALSE);
        }

        CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
        renderLock.Lock(INFINITE);

        pInventory->SummonPopup(3);

        renderLock.Unlock();
    }
}

// 0x632260
BOOL CUIControlButtonInventoryColor::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    if (m_bPressed) {
        m_pDecal->FrameSet(1);
    } else {
        m_pDecal->FrameSet(0);
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = g_pBaldurChitin->m_pEngineInventory->GetSelectedCharacter();

    // NOTE: Uninline.
    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        BYTE colorRange;
        switch (m_nID) {
        case 62:
            colorRange = pSprite->m_baseStats.m_colors[2];
            break;
        case 63:
            colorRange = pSprite->m_baseStats.m_colors[1];
            break;
        case 82:
            colorRange = pSprite->m_baseStats.m_colors[6];
            break;
        case 83:
            colorRange = pSprite->m_baseStats.m_colors[3];
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 9737
            UTIL_ASSERT(FALSE);
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_1,
            INFINITE);

        CRect rControlRect;
        rControlRect.left = pt.x;
        rControlRect.top = pt.y;
        rControlRect.right = rControlRect.left + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        rControlRect.bottom = rControlRect.top + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        m_pPalette->SetRange(0,
            colorRange,
            *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());

        m_pDecal->SetPalette(*m_pPalette);

        BOOL bResult = m_pDecal->Render(0, pt.x, pt.y, rClip, NULL, 0, 0, 0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9748
        UTIL_ASSERT(bResult);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x0632530
CUIControlButtonInventoryColorChoice::CUIControlButtonInventoryColorChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    if (m_nID == 35) {
        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(33479, strRes); // "Default"
        SetText(strRes.szText);

        m_pDecal = NULL;
        m_pPalette = NULL;
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9783
        UTIL_ASSERT(m_nID <= CRESUI_CONTROLBUTTONID_INVENTORYCOLOR_LASTCOLOR);

        m_pDecal = new CVidCell(CResRef("COLGRAD"), m_pPanel->m_pManager->m_bDoubleSize);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9789
        UTIL_ASSERT(m_pDecal != NULL);

        m_pPalette = new CVidPalette(CVidPalette::TYPE_RANGE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9795
        UTIL_ASSERT(m_pPalette != NULL);
    }
}

// 0x632740
CUIControlButtonInventoryColorChoice::~CUIControlButtonInventoryColorChoice()
{
    if (m_pDecal != NULL) {
        delete m_pDecal;
        m_pDecal = NULL;
    }

    if (m_pPalette != NULL) {
        delete m_pPalette;
        m_pPalette = NULL;
    }
}

// 0x632830
void CUIControlButtonInventoryColorChoice::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9850
    UTIL_ASSERT(pInventory != NULL);

    if (pInventory->m_bMultiPlayerViewable) {
        BYTE colorRange;
        if (GetColorRange(colorRange)) {
            pInventory->field_11F = colorRange;
            pInventory->OnDoneButtonClick();
        } else if (m_nID == 35) {
            pInventory->field_11F = pInventory->field_11E;
            pInventory->field_11E = 7;
            pInventory->OnDoneButtonClick();
        }
    }
}

// 0x6328C0
BOOL CUIControlButtonInventoryColorChoice::Render(BOOL bForce)
{
    if (m_nID == 35) {
        return CUIControlButton::Render(bForce);
    }

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    if (m_bPressed) {
        m_pDecal->FrameSet(3);
    } else {
        m_pDecal->FrameSet(2);
    }

    BYTE colorRange;
    if (GetColorRange(colorRange)) {
        CRect rControlRect;
        rControlRect.left = pt.x;
        rControlRect.top = pt.y;
        rControlRect.right = rControlRect.left + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        rControlRect.bottom = rControlRect.top + 42 * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        CRect rClip;
        rClip.IntersectRect(rControlRect, m_rDirty);

        m_pPalette->SetRange(0,
            colorRange,
            *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());

        m_pDecal->SetPalette(*m_pPalette);

        BOOL bResult = m_pDecal->Render(0, pt.x, pt.y, rClip, NULL, 0, 0, 0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 9938
        UTIL_ASSERT(bResult);
    }

    return TRUE;
}

// 0x632A70
BOOL CUIControlButtonInventoryColorChoice::GetColorRange(BYTE& colorRange)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 9964
    UTIL_ASSERT(pInventory != NULL);

    switch (pInventory->field_11E) {
    case 1:
    case 2:
        if (m_nID < 31) {
            colorRange = static_cast<BYTE>(m_nID) + 36;
            return TRUE;
        } else if (m_nID < 34) {
            colorRange = static_cast<BYTE>(m_nID) - 10;
            return TRUE;
        }
        return FALSE;
    case 3:
        colorRange = static_cast<BYTE>(atol(pInventory->m_tSkinColor.GetAt(CPoint(0, m_nID))));
        return TRUE;
    case 6:
        colorRange = static_cast<BYTE>(atol(pInventory->m_tHairColor.GetAt(CPoint(0, m_nID))));
        return TRUE;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 10006
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x632BE0
CUIControlScrollBarInventoryGround::CUIControlScrollBarInventoryGround(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x67F640
CUIControlScrollBarInventoryGround::~CUIControlScrollBarInventoryGround()
{
}

// 0x632C10
void CUIControlScrollBarInventoryGround::OnPageDown(DWORD nLines)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10061
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10063
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        INT nNumGroundSlots = pGame->GetNumGroundSlots(nContainerId);

        INT nStep = min(nLines, GROUND_SLOTS - 1);
        INT nNewTopGroundItem = max(pInventory->m_nTopGroundItem - nStep, 0);
        if (pInventory->m_nTopGroundItem != nNewTopGroundItem) {
            for (INT nButtonId = 68; nButtonId <= 81; nButtonId++) {
                m_pPanel->GetControl(nButtonId)->InvalidateRect();
            }

            UpdateScrollBar();
        }
    }
}

// 0x632CE0
void CUIControlScrollBarInventoryGround::OnPageUp(DWORD nLines)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10112
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10114
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        INT nNumGroundSlots = pGame->GetNumGroundSlots(nContainerId);

        INT nStep = min(nLines, GROUND_SLOTS - 1);
        INT nNewTopGroundItem = min(pInventory->m_nTopGroundItem + nStep, nNumGroundSlots);
        if (pInventory->m_nTopGroundItem != nNewTopGroundItem) {
            for (INT nButtonId = 68; nButtonId <= 81; nButtonId++) {
                m_pPanel->GetControl(nButtonId)->InvalidateRect();
            }

            UpdateScrollBar();
        }
    }
}

// 0x632DB0
void CUIControlScrollBarInventoryGround::OnScrollDown()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10163
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10165
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        INT nNumGroundSlots = pGame->GetNumGroundSlots(nContainerId);
        if (pInventory->m_nTopGroundItem > 0) {
            pInventory->m_nTopGroundItem--;
        }

        for (INT nButtonId = 68; nButtonId <= 81; nButtonId++) {
            m_pPanel->GetControl(nButtonId)->InvalidateRect();
        }

        UpdateScrollBar();
    }
}

// 0x632E60
void CUIControlScrollBarInventoryGround::OnScrollUp()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10209
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10211
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        INT nNumGroundSlots = pGame->GetNumGroundSlots(nContainerId);
        if (pInventory->m_nTopGroundItem < nNumGroundSlots) {
            pInventory->m_nTopGroundItem++;
        }

        for (INT nButtonId = 68; nButtonId <= 81; nButtonId++) {
            m_pPanel->GetControl(nButtonId)->InvalidateRect();
        }

        UpdateScrollBar();
    }
}

// 0x632F20
void CUIControlScrollBarInventoryGround::OnScroll()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10255
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10257
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        INT nNumGroundSlots = pGame->GetNumGroundSlots(nContainerId);
        pInventory->m_nTopGroundItem = max(nNumGroundSlots, 0) * field_144 / field_142;

        for (INT nButtonId = 68; nButtonId <= 81; nButtonId++) {
            m_pPanel->GetControl(nButtonId)->InvalidateRect();
        }

        UpdateScrollBar();
    }
}

// 0x632FF0
void CUIControlScrollBarInventoryGround::UpdateScrollBar()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10326
    UTIL_ASSERT(pInventory != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10328
    UTIL_ASSERT(pGame != NULL);

    LONG nContainerId = pInventory->FetchGroundPile(pInventory->GetSelectedCharacter(), FALSE);
    if (nContainerId != CGameObjectArray::INVALID_INDEX) {
        AdjustScrollBar(pInventory->m_nTopGroundItem,
            pGame->GetNumGroundSlots(nContainerId) + GROUND_SLOTS,
            GROUND_SLOTS);
    }
}

// -----------------------------------------------------------------------------

// 0x633090
CUIControlButtonInventoryRequesterItem::CUIControlButtonInventoryRequesterItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_resRef = "";
}

// 0x633130
CUIControlButtonInventoryRequesterItem::~CUIControlButtonInventoryRequesterItem()
{
}

// 0x6331D0
BOOL CUIControlButtonInventoryRequesterItem::Render(BOOL bForce)
{
    CVidCell vcIcon;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    CVidMode* pVidMode = g_pBaldurChitin->GetCurrentVideoMode();

    if (m_resRef == "") {
        return FALSE;
    }

    // NOTE: Uninline.
    vcIcon.SetResRef(m_resRef, m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

    vcIcon.SequenceSet(1);
    vcIcon.FrameSet(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10458
    UTIL_ASSERT(vcIcon.GetRes() != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10459
    UTIL_ASSERT(pVidMode != NULL);

    if (vcIcon.pRes == NULL) {
        return FALSE;
    }

    // NOTE: Original code is slightly different.
    INT x = m_pPanel->m_ptOrigin.x + m_ptOrigin.x;
    INT y = m_pPanel->m_ptOrigin.y + m_ptOrigin.y;
    LONG nWidth = CIcon::ICON_SIZE_SM.cx * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
    LONG nHeight = CIcon::ICON_SIZE_SM.cy * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

    if (m_size.cx > nWidth) {
        x += (m_size.cx - nWidth) / 2;
    }

    if (m_size.cy > nHeight) {
        y += (m_size.cy - nHeight) / 2;
    }

    CSize iconSize;
    vcIcon.GetCurrentFrameSize(iconSize, FALSE);

    CRect rFrame(x, y, x + nWidth, y + nHeight);

    CRect rClip;
    rClip.IntersectRect(rFrame, m_rDirty);

    vcIcon.Render(0, x, y, rClip, NULL, 0, 0, -1);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x6334E0
CUIControlButtonInventoryRequesterDone::CUIControlButtonInventoryRequesterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x6335D0
CUIControlButtonInventoryRequesterDone::~CUIControlButtonInventoryRequesterDone()
{
}

// 0x633670
void CUIControlButtonInventoryRequesterDone::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10533
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6336B0
CUIControlButtonInventoryRequesterCancel::CUIControlButtonInventoryRequesterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x6337A0
CUIControlButtonInventoryRequesterCancel::~CUIControlButtonInventoryRequesterCancel()
{
}

// 0x633840
void CUIControlButtonInventoryRequesterCancel::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10589
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x633880
CUIControlButtonInventoryRequesterPlusMinus::CUIControlButtonInventoryRequesterPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonPlusMinus(panel, controlInfo)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x6338C0
CUIControlButtonInventoryRequesterPlusMinus::~CUIControlButtonInventoryRequesterPlusMinus()
{
}

// 0x633960
void CUIControlButtonInventoryRequesterPlusMinus::AdjustValue()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10641
    UTIL_ASSERT(pInventory != NULL);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    pInventory->MapButtonIdToItemInfo(pInventory->m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);
    if (pItem != NULL) {
        switch (m_nID) {
        case 3:
            // NOTE: Uninline.
            pInventory->OnRequesterMinusButtonClick();
            break;
        case 4:
            // NOTE: Uninline.
            pInventory->OnRequesterPlusButtonClick();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 10678
            UTIL_ASSERT(pInventory != NULL);
        }
    } else {
        CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
        renderLock.Lock(INFINITE);

        CUIControlButtonPlusMinus::OnLButtonUp(CPoint(0, 0));

        pInventory->DismissPopup();
        pInventory->SetErrorString(10161, RGB(255, 255, 255));

        renderLock.Unlock();
    }
}

// -----------------------------------------------------------------------------

// 0x633B80
CUIControlEditInventoryRequesterAmount::CUIControlEditInventoryRequesterAmount(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, 0)
{
}

// 0x633BD0
CUIControlEditInventoryRequesterAmount::~CUIControlEditInventoryRequesterAmount()
{
}

// 0x633CA0
void CUIControlEditInventoryRequesterAmount::KillFocus()
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 10732
    UTIL_ASSERT(pInventory != NULL);

    CItem* pItem;
    STRREF description;
    CResRef cResIcon;
    CResRef cResItem;
    WORD wCount;

    pInventory->MapButtonIdToItemInfo(pInventory->m_nRequesterButtonId,
        pItem,
        description,
        cResIcon,
        cResItem,
        wCount);
    if (pItem != NULL) {
        INT nAmount = atol(m_sText);
        // NOTE: Signed compare.
        if (nAmount > 0 && nAmount <= static_cast<SHORT>(wCount)) {
            pInventory->m_nRequesterAmount = nAmount;
        }
        pInventory->UpdateRequesterPanel();
    }

    CUIControlEdit::KillFocus();
}

// -----------------------------------------------------------------------------

// 0x633D50
CUIControlButtonInventoryHistoryIcon::CUIControlButtonInventoryHistoryIcon(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    field_662 = 0;
    m_pItem = NULL;
}

// 0x633DF0
CUIControlButtonInventoryHistoryIcon::~CUIControlButtonInventoryHistoryIcon()
{
}

// 0x633EA0
void CUIControlButtonInventoryHistoryIcon::SetItem(CItem* pItem)
{
    if (m_item.GetResRef() != pItem->GetResRef()) {
        m_item.SetResRef(pItem->GetResRef(), TRUE);
        m_item.m_useCount1 = pItem->m_useCount1;
        m_item.m_useCount2 = pItem->m_useCount2;
        m_item.m_useCount3 = pItem->m_useCount3;
        m_item.m_flags = pItem->m_flags;
        m_item.m_wear = pItem->m_wear;

        m_pItem = &m_item;

        InvalidateRect();
    }
}

// 0x634950
BOOL CUIControlButtonInventoryHistoryIcon::Render(BOOL bForce)
{
    CVidCell vcIcon;
    CResRef iconResRef;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    CVidMode* pVidMode = g_pBaldurChitin->GetCurrentVideoMode();

    if (m_pItem == NULL) {
        return FALSE;
    }

    iconResRef = m_pItem->GetItemIcon();
    if (iconResRef == "") {
        return FALSE;
    }

    // NOTE: Uninline.
    vcIcon.SetResRef(iconResRef, m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

    vcIcon.SequenceSet(0);
    vcIcon.FrameSet(0);

    if (vcIcon.pRes != NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 10894
        UTIL_ASSERT(pVidMode != NULL);

        // NOTE: Original code is slightly different.
        INT x = m_pPanel->m_ptOrigin.x + m_ptOrigin.x;
        INT y = m_pPanel->m_ptOrigin.y + m_ptOrigin.y;

        CPoint ptCenter;
        vcIcon.GetCurrentCenterPoint(ptCenter, FALSE);

        CSize frameSize;
        vcIcon.GetCurrentFrameSize(frameSize, FALSE);

        LONG nWidth = CIcon::ICON_SIZE_LG.cx * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);
        LONG nHeight = CIcon::ICON_SIZE_LG.cy * (m_pPanel->m_pManager->m_bDoubleSize ? 2 : 1);

        if (m_size.cx > nWidth) {
            x += (m_size.cx - nWidth) / 2;
        }

        if (m_size.cy > nHeight) {
            y += (m_size.cy - nHeight) / 2;
        }

        CRect rFrame(x, y, x + nWidth, y + nHeight);

        CRect rClip;
        rClip.IntersectRect(rFrame, m_rDirty);

        vcIcon.Render(0,
            ptCenter.x + (m_size.cx - frameSize.cx) / 2,
            ptCenter.y + (m_size.cy - frameSize.cy) / 2,
            rClip,
            NULL,
            0,
            0x4,
            -1);
    }

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x634280
CUIControlButtonInventoryAbilitiesAbility::CUIControlButtonInventoryAbilitiesAbility(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nSelectedFrame = 0;
}

// 0x634280
CUIControlButtonInventoryAbilitiesAbility::~CUIControlButtonInventoryAbilitiesAbility()
{
}

// 0x634430
BOOL CUIControlButtonInventoryAbilitiesAbility::Render(BOOL bForce)
{
    CResRef iconResRef;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton3State::Render(bForce)) {
        return FALSE;
    }

    iconResRef = m_cButtonData.m_icon;
    if (iconResRef != "") {
        CRect rControlFrame(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

        if (m_bPressed) {
            rControlFrame.OffsetRect(field_63E, field_642);
        }

        CPoint pos = rControlFrame.TopLeft();

        CRect rClip;
        rClip.IntersectRect(rControlFrame, m_rDirty);

        CIcon::RenderIcon(0,
            pos,
            m_size,
            rClip,
            iconResRef,
            m_pPanel->m_pManager->m_bDoubleSize,
            m_bEnabled ? 0x1 : 0,
            0,
            FALSE,
            0,
            FALSE,
            0);
    }

    return TRUE;
}

// 0x6345A0
void CUIControlButtonInventoryAbilitiesAbility::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11120
    UTIL_ASSERT(pInventory != NULL);

    CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11126
    UTIL_ASSERT(m_cButtonData.m_icon != "");

    int v1;
    switch (m_nID) {
    case 1:
        v1 = 0;
        break;
    case 2:
        v1 = 1;
        break;
    case 3:
        v1 = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 11021
        UTIL_ASSERT(FALSE);
    }

    pInventory->field_4AC = v1;

    pInventory->UpdatePopupPanel(m_pPanel->m_nID);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x6347C0
CUIControlButtonInventoryHistoryDone::CUIControlButtonInventoryHistoryDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x6348B0
CUIControlButtonInventoryHistoryDone::~CUIControlButtonInventoryHistoryDone()
{
}

// 0x634950
void CUIControlButtonInventoryHistoryDone::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11187
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x634990
CUIControlButtonInventoryHistoryCancel::CUIControlButtonInventoryHistoryCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x634A80
CUIControlButtonInventoryHistoryCancel::~CUIControlButtonInventoryHistoryCancel()
{
}

// 0x634B20
void CUIControlButtonInventoryHistoryCancel::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11243
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x634B60
CUIControlButtonInventoryHistoryImage::CUIControlButtonInventoryHistoryImage(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_imageResRef = "";
}

// 0x634C00
CUIControlButtonInventoryHistoryImage::~CUIControlButtonInventoryHistoryImage()
{
}

// 0x799C90
BOOL CUIControlButtonInventoryHistoryImage::Render(BOOL bForce)
{
    return TRUE;
}

// 0x634CA0
void CUIControlButtonInventoryHistoryImage::SetImage(CResRef imageResRef)
{
    if (m_imageResRef != imageResRef) {
        m_imageResRef = imageResRef;
        InvalidateRect();
    }
}

// -----------------------------------------------------------------------------

// 0x634CE0
CUIControlButtonInventoryHistoryAbilities::CUIControlButtonInventoryHistoryAbilities(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x634D30
CUIControlButtonInventoryHistoryAbilities::~CUIControlButtonInventoryHistoryAbilities()
{
}

// 0x634DD0
void CUIControlButtonInventoryHistoryAbilities::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11508
    UTIL_ASSERT(pInventory != NULL);

    CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pInventory->OnAbilitiesButtonClick();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x634E70
CUIControlButtonInventoryHistoryUse::CUIControlButtonInventoryHistoryUse(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x634EC0
CUIControlButtonInventoryHistoryUse::~CUIControlButtonInventoryHistoryUse()
{
}

// 0x634F60
void CUIControlButtonInventoryHistoryUse::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11676
    UTIL_ASSERT(pInventory != NULL);

    CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pInventory->OnUseButtonClick();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x635000
CUIControlPortraitInventory::CUIControlPortraitInventory(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlPortraitGeneral(panel, controlInfo)
{
    field_666 = 0;
}

// 0x6350E0
CUIControlPortraitInventory::~CUIControlPortraitInventory()
{
}

// 0x635180
void CUIControlPortraitInventory::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    if (pInventory->m_pTempItem != NULL) {
        pInventory->BeginSwap();
        pInventory->SwapWithPortrait(m_nID, TRUE);
        pInventory->EndSwap();
        field_666 = 1;
    } else {
        CUIControlPortraitGeneral::OnLButtonClick(pt);
        field_666 = 0;
    }
}

// 0x635220
void CUIControlPortraitInventory::OnLButtonDoubleClick(CPoint pt)
{
    if (field_666) {
        OnLButtonClick(pt);
    } else {
        // NOTE: Uninline.
        CUIControlPortraitGeneral::OnLButtonDoubleClick(pt);
    }
}

// -----------------------------------------------------------------------------

// 0x635270
CUIControlButtonInventoryError::CUIControlButtonInventoryError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x6352C0
CUIControlButtonInventoryError::~CUIControlButtonInventoryError()
{
}

// 0x635360
void CUIControlButtonInventoryError::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11832
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnErrorButtonClick(m_nID);
}

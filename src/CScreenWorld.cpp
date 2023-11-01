#include "CScreenWorld.h"

#include "CBaldurChitin.h"
#include "CBaldurProjector.h"
#include "CDeathSound.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenChapter.h"
#include "CScreenConnection.h"
#include "CScreenInventory.h"
#include "CScreenLoad.h"
#include "CScreenMap.h"
#include "CScreenWorldMap.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x85A1EC
const LONG CScreenWorld::BORED_TIME = 3000;

// 0x8F85BC
int CScreenWorld::dword_8F85BC;

// 0x685610
CScreenWorld::CScreenWorld()
{
    field_11E = 0;
    m_bHardPaused = FALSE;
    field_14E = 0;
    m_bPausedBeforePickParty = FALSE;
    field_15C = 0;
    field_15D = 0;
    field_15E = 0;
    field_160 = 0;
    field_162 = 0;
    field_164 = 0;
    m_nTopContainerRow = 0;
    m_nTopGroupRow = 0;
    field_10CC = 0;
    m_ambianceForce = FALSE;
    m_bInControlOfDialog = FALSE;
    m_bInControlOfStore = FALSE;
    field_110C = 0;
    field_114C = 0;
    field_1150 = 0;
    m_nPendingMapWorldDirection = 0;
    m_nLeaveAreaLuaPanicDirection = 0;
    m_comingOutOfDialog = 0;

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
    m_pVirtualKeys[90] = CKeyInfo(VK_PRIOR, 0, 0);
    m_pVirtualKeys[91] = CKeyInfo(VK_NEXT, 0, 0);

    // FIXME: Buffer overrun.
    m_pVirtualKeys[92] = CKeyInfo(VK_PROCESSKEY, -1, 0);

    m_bored = FALSE;
    m_boredCount = 0;
    m_playerShutdown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_bCtrlKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    m_bMenuKeyDown = FALSE;
    m_bPaused = FALSE;
    field_142 = 0;
    field_14A = 0;
    m_pActiveDialogDisplay = NULL;
    m_pActiveChatDisplay = NULL;
    field_156 = 0;
    field_F37 = 0;
    field_15A = 1;
    m_newViewSize.left = 0;
    m_newViewSize.top = 0;
    m_newViewSize.right = 1;
    m_newViewSize.bottom = 1;
    m_bForceViewSize = FALSE;
    m_waitingOnResize = 0;
    field_F44 = 0;
    m_scrollLockId = CGameObjectArray::INVALID_INDEX;
    field_EA4 = -1;
    field_10B2 = -1;
    field_10B4 = 0;
    m_interactionIndex = CGameObjectArray::INVALID_INDEX;
    m_interactionTarget = CGameObjectArray::INVALID_INDEX;
    field_10C0 = "";
    field_10C4 = 0;
    field_10C8 = 0;
    field_10D0 = CGameObjectArray::INVALID_INDEX;
    m_deltaTime = 0;
    m_nChatMessageCount = 0;
    m_movie = "";
    field_1108 = 0;
    m_bGameOverPanel = 0;
    field_10F0 = 0;
    field_10F4 = -1;
    m_autoPauseId = CGameObjectArray::INVALID_INDEX;
    m_autoPauseRef = -1;
    m_nPickPartyNumCharacters = -1;
    m_bSetNightOnActivate = FALSE;
    m_bSetDayOnActivate = FALSE;
    m_bEndMajorEventListenToJoin = FALSE;
    m_bEndMajorEventPauseStatus = FALSE;
    m_bChapterTransitionPending = FALSE;
    m_nChapterTransition = 255;
    m_bMoviePending = FALSE;
    m_bRestPending = FALSE;
    m_bRestRenting = FALSE;
    m_nRestHP = 0;
    m_bRestMovie = FALSE;
    m_bPendingMapWorld = FALSE;
    m_bPendingReformParty = FALSE;
    field_119D = 0;
    InitializeCriticalSection(&field_106);
    m_nBattleCryTimeOut = 0;
    m_nPartySizeCheckStartDelay = 0;
    m_bLeaveAreaLuaPanicPending = FALSE;
    m_ulLeaveAreaLuaPanicTimer = -1;
    m_bPlayEndCredits = FALSE;
    field_11B6 = -1;
    field_11BA = -1;
    field_11BE = 0;
    m_lastAmbiance = CGameObjectArray::INVALID_INDEX;
    m_comingOutOfDialog = 0;
    m_nAutoHideInterface = 0;
    m_nAutoUnhideInterface = 0;
    field_11F0 = 1;
    field_11F4 = 1;
    field_11D0 = CInfinity::stru_8E79B8;
    m_nBlackOutCountDown = 0;
    field_1204 = 0;
}

// 0x49FC40
BOOL CScreenWorld::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x66F230
void CScreenWorld::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x686610
BOOL CScreenWorld::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x49FC40
BOOL CScreenWorld::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x686600
void CScreenWorld::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x6865F0
BOOL CScreenWorld::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenWorld::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x686620
void CScreenWorld::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x686630
BOOL CScreenWorld::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenWorld::CheckSystemKeyMenu()
{
    return TRUE;
}

// 0x686650
void CScreenWorld::SetSystemKeyMenu(BOOL bValue)
{
    m_bMenuKeyDown = bValue;
}

// 0x686640
BOOL CScreenWorld::GetMenuKey()
{
    return m_bMenuKeyDown;
}

// 0x686660
SHORT CScreenWorld::GetNumVirtualKeys()
{
    return CSCREENWORLD_VIRTUAL_KEYS;
}

// 0x686670
CKeyInfo* CScreenWorld::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x686680
BYTE* CScreenWorld::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x686690
void CScreenWorld::TimerAsynchronousUpdate()
{
    AsynchronousUpdate(TRUE);
}

// 0x6866C0
CScreenWorld::~CScreenWorld()
{
    DeleteCriticalSection(&field_106);

    while (!m_deathSoundList.IsEmpty()) {
        CDeathSound* pDeathSound = m_deathSoundList.RemoveHead();
        delete pDeathSound;
    }
}

// 0x686870
int CScreenWorld::GetSelectedCharacter()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    LONG iSprite = pGame->GetGroup()->GetGroupLeader();
    SHORT nCharacter;

    if (iSprite == CGameObjectArray::INVALID_INDEX) {
        BOOLEAN bFoundControlledCharacter = FALSE;

        for (nCharacter = 0; nCharacter < CINFGAME_MAXCHARACTERS; nCharacter++) {
            // NOTE: Uninline.
            LONG nCharacterId = pGame->GetCharacterId(nCharacter);

            if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
                CGameSprite* pSprite;

                BYTE rc;
                do {
                    rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        reinterpret_cast<CGameObject**>(&pSprite),
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc == CGameObjectArray::SUCCESS) {
                    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                        || g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID) {
                        bFoundControlledCharacter = TRUE;
                    }

                    pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }

            if (bFoundControlledCharacter) {
                break;
            }
        }

        if (!bFoundControlledCharacter) {
            nCharacter = 0;
        }
    } else {
        nCharacter = pGame->GetCharacterPortraitNum(iSprite);
    }

    m_nSelectedCharacter = nCharacter;

    return m_nSelectedCharacter;
}

// 0x6869C0
void CScreenWorld::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
        && field_142) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(1, 1, 0);
        field_142 = FALSE;
    }

    if (m_cUIManager.m_bInitialized) {
        if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded == TRUE) {
            g_pBaldurChitin->field_F9 = TRUE;
            g_pBaldurChitin->GetObjectGame()->WorldEngineActivated(pVidMode);
            field_119D = TRUE;

            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, TRUE);
            g_pBaldurChitin->GetObjectCursor()->m_bVisible = TRUE;

            m_cUIManager.InvalidateRect(NULL);

            if (m_waitingOnResize == 0) {
                if (g_pBaldurChitin->GetObjectGame()->GetVisibleArea() != NULL) {
                    m_newViewSize = g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->rViewPort;
                } else {
                    m_newViewSize = CInfinity::stru_8E79B8;
                }
            }

            m_waitingOnResize = 2;
            m_bForceViewSize = TRUE;

            if (m_bSetNightOnActivate) {
                g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->SetNight();
                m_bSetNightOnActivate = FALSE;
            }

            if (m_bSetDayOnActivate) {
                g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->SetDay();
                g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->GetInfinity()->SetDawn(CInfinity::TRUE_DAWNDUSK_INTENSITY, TRUE);
                m_bSetDayOnActivate = FALSE;
            }

            if (!m_bHardPaused
                && m_nAutoHideInterface != 0) {
                DWORD dwInputMode = g_pBaldurChitin->GetObjectGame()->field_43E2;
                if (dwInputMode != 0x182 && dwInputMode != 0x502) {
                    // NOTE: Uninline.
                    CancelPopup();
                }

                m_nAutoHideInterface--;
                HideInterface();
            }

            CUIControlTextDisplay* pText = m_pActiveChatDisplay;
            if (pText == NULL) {
                pText = m_pActiveDialogDisplay;
            }

            if (pText != NULL) {
                m_nChatMessageCount = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(pText,
                    m_nChatMessageCount);
            }
        }
    }
}

// 0x686D00
void CScreenWorld::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded == TRUE) {
        if (!m_bPaused && g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StopTime();
        }

        g_pBaldurChitin->GetObjectGame()->WorldEngineDeactivated();
        g_pBaldurChitin->field_F9 = 0;
    }
}

// 0x686DE0
void CScreenWorld::EngineGameInit()
{
    g_pBaldurChitin->GetObjectGame()->m_bForceDither = FALSE;

    m_cUIManager.fInit(this,
        CResRef(CString("GUIW") + CBaldurChitin::CHUI_GUIEXT),
        g_pBaldurChitin->field_4A2C);

    m_pCurrentScrollBar = NULL;
    m_bored = FALSE;
    m_boredCount = 0;
    m_playerShutdown = FALSE;
    m_bPaused = FALSE;
    field_14A = 0;
    m_pActiveDialogDisplay = NULL;
    m_pActiveChatDisplay = NULL;
    field_156 = 0;
    field_F37 = 0;
    field_15A = 1;
    m_newViewSize.left = 0;
    m_newViewSize.top = 0;
    m_newViewSize.right = 1;
    m_newViewSize.bottom = 1;
    m_bForceViewSize = 0;
    m_waitingOnResize = 0;
    field_F44 = 0;
    m_scrollLockId = CGameObjectArray::INVALID_INDEX;
    field_EA4 = -1;
    field_10B2 = -1;
    field_10B4 = 0;
    m_interactionIndex = CGameObjectArray::INVALID_INDEX;
    m_interactionTarget = CGameObjectArray::INVALID_INDEX;
    field_10C0 = "";
    field_10C4 = 0;
    field_10C8 = 0;
    field_10D8 = CGameObjectArray::INVALID_INDEX;
    m_deltaTime = 0;
    m_nChatMessageCount = 0;
    m_movie = "";
    field_1108 = 0;
    m_bGameOverPanel = FALSE;
    field_10F0 = 0;
    field_10F4 = -1;
    m_autoPauseId = CGameObjectArray::INVALID_INDEX;
    m_autoPauseRef = -1;
    m_nPickPartyNumCharacters = -1;
    m_bSetNightOnActivate = 0;
    m_bSetDayOnActivate = 0;
    m_bEndMajorEventListenToJoin = 0;
    m_bEndMajorEventPauseStatus = 0;
    m_bChapterTransitionPending = 0;
    m_nChapterTransition = 255;
    m_bMoviePending = 0;
    m_bRestPending = 0;
    m_bRestRenting = 0;
    m_nRestHP = 0;
    m_bRestMovie = 0;
    m_bPendingMapWorld = 0;
    m_bPendingReformParty = 0;
    field_119D = 0;
    m_nBattleCryTimeOut = 0;
    m_nPartySizeCheckStartDelay = 0;
    m_bLeaveAreaLuaPanicPending = 0;
    m_ulLeaveAreaLuaPanicTimer = -1;
    m_bPlayEndCredits = FALSE;
    field_11B6 = -1;
    field_11BA = -1;
    field_11BE = 0;

    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(19)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(21)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(7)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(6)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(8)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(9)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(17)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(22)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(0)->SetActive(FALSE);
    g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(GetPanel_22_0())->SetActive(TRUE);

    m_pActiveDialogDisplay = static_cast<CUIControlTextDisplay*>(g_pBaldurChitin->m_pEngineWorld->GetManager()->GetPanel(GetPanel_22_0())->GetControl(1));
    m_nAutoHideInterface = 0;
    m_nAutoUnhideInterface = 0;

    if (!field_11F0) {
        field_11F0 = TRUE;
        CInfinity::stru_8E79B8.bottom = field_11F8;
    }

    if (!field_11F4) {
        field_11F4 = TRUE;
        CInfinity::stru_8E79B8.bottom = field_11F8;
    }

    while (!m_deathSoundList.IsEmpty()) {
        CDeathSound* pDeathSound = m_deathSoundList.RemoveHead();
        if (pDeathSound != NULL) {
            delete pDeathSound;
        }
    }
    m_deathSoundList.RemoveAll();
}

// 0x5D72C0
void CScreenWorld::EngineGameUninit()
{
    m_cUIManager.fUninit();
}

// 0x49FC40
BOOL CScreenWorld::CheckMouseLButton()
{
    return TRUE;
}

// 0x68C020
void CScreenWorld::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);

    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x1) != 0) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if (pArea != NULL) {
            pArea->OnActionButtonDblClk(pt);
        }

        g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    }
}

// 0x68C080
void CScreenWorld::OnLButtonDown(CPoint pt)
{
    m_cUIManager.field_20 = m_bShiftKeyDown;
    m_cUIManager.field_24 = m_bCtrlKeyDown;
    m_cUIManager.OnLButtonDown(pt);

    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x1) != 0) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if (pArea != NULL) {
            pArea->OnActionButtonDown(pt);
        }

        g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    }
}

// 0x68C100
void CScreenWorld::OnLButtonUp(CPoint pt)
{
    if (g_pBaldurChitin->GetObjectGame()->field_43E2 == 0x142) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
    } else {
        m_cUIManager.field_20 = m_bShiftKeyDown;
        m_cUIManager.field_24 = m_bCtrlKeyDown;
        m_cUIManager.OnLButtonUp(pt);

        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if (pArea != NULL) {
            pArea->OnActionButtonUp(pt);
        }

        g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    }
}

// 0x49FC40
BOOL CScreenWorld::CheckMouseMove()
{
    return TRUE;
}

// 0x68C1A0
void CScreenWorld::OnMouseMove(CPoint pt)
{
    if (m_cUIManager.GetPanel(8)->m_bActive) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(8);
        CUIControlBase* pControl = pPanel->GetControl(52);

        if (pControl != NULL && pt.x - pPanel->m_ptOrigin.x < pControl->m_ptOrigin.x + pControl->m_size.cx) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(52));
        } else {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(53));
        }
    }

    m_cUIManager.OnMouseMove(pt);

    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
    if (pArea != NULL) {
        pArea->OnMouseMove(pt);
    }
}

// 0x49FC40
BOOL CScreenWorld::CheckMouseRButton()
{
    return TRUE;
}

// 0x68C250
void CScreenWorld::OnRButtonDblClk(CPoint pt)
{
    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x1) != 0) {
        g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    }
}

// 0x68C280
void CScreenWorld::OnRButtonDown(CPoint pt)
{
    m_cUIManager.OnRButtonDown(pt);

    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x1) != 0) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if (pArea != NULL) {
            pArea->OnFormationButtonDown(pt);
        }

        g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    }
}

// 0x68C2E0
void CScreenWorld::OnRButtonUp(CPoint pt)
{
    m_cUIManager.OnRButtonUp(pt);

    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x1) != 0) {
        CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
        if (pArea != NULL) {
            pArea->OnFormationButtonUp(pt);
        }

        g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    }
}

// 0x68C340
void CScreenWorld::StartScroll(CPoint dest, SHORT speed)
{
    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
    CInfinity* pInfinity = pArea->GetInfinity();

    pInfinity->m_ptScrollDest = dest;
    pInfinity->m_nLastTickCount = GetTickCount();
    pInfinity->m_autoScrollSpeed = static_cast<SHORT>(CChitin::TIMER_UPDATES_PER_SECOND * speed / 24);
}

// 0x68C3D0
void CScreenWorld::AsynchronousUpdate(BOOL bActiveEngine)
{
    CGameSprite* pSprite;
    BYTE rc;
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 2887
    UTIL_ASSERT(pGame != NULL);

    DWORD nTickCount = GetTickCount();
    g_pBaldurChitin->field_1AB2[0] += nTickCount - g_pBaldurChitin->field_1AF2[0];
    g_pBaldurChitin->field_1AF2[0] = nTickCount;

    if (m_bPlayEndCredits) {
        if (g_pBaldurChitin->GetBaldurMessage()->NonBlockingWaitForSignal(CBaldurMessage::SIGNAL_SERVER, CBaldurMessage::SIGNAL_END_GAME)) {
            g_pBaldurChitin->m_pEngineConnection->ReadyEndCredits();
            g_pBaldurChitin->m_pEngineConnection->field_FB0 = 0;
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineConnection);

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                    g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
                }

                g_pChitin->cNetwork.CloseSession(TRUE);
                g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown = FALSE;
            }

            pGame->DestroyGame(1, 0);
            m_bPlayEndCredits = FALSE;
        }
        return;
    }

    if (m_playerShutdown) {
        g_pBaldurChitin->m_pEngineConnection->field_FB0 = 0;
        SelectEngine(g_pBaldurChitin->m_pEngineConnection);
        pGame->DestroyGame(1, 0);
    }

    if (pGame->m_bGameLoaded) {
        if (pGame->GetWorldTimer()->m_active
            && field_EA4 != 0
            && m_nPartySizeCheckStartDelay <= 0
            && pGame->m_characterOverflow.GetCount() > 0) {
            if (!g_pChitin->cNetwork.GetSessionOpen()) {
                m_bPausedBeforePickParty = m_bPaused;
            }

            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                m_bPendingReformParty = TRUE;
            }
        }

        if (m_nPartySizeCheckStartDelay > 0) {
            m_nPartySizeCheckStartDelay -= 1;
        }

        pGame->GetWorldTimer()->UpdateTime(FALSE);

        if (g_pBaldurChitin->cNetwork.GetSessionOpen()
            && g_pBaldurChitin->cNetwork.GetSessionHosting()) {
            if ((pGame->GetWorldTimer()->m_gameTime % CTimerWorld::MULTIPLAYER_TIME_SYNCH_INTERVAL) == 0) {
                g_pBaldurChitin->GetBaldurMessage()->TimeSynchBroadcast(pGame->GetWorldTimer()->m_gameTime,
                    FALSE);
            }
        }

        if (bActiveEngine) {
            // NOTE: Uninline.
            CheckPanelInputMode(1, 0x20);

            // NOTE: Uninline.
            CheckPanelInputMode(GetPanel_22_0(), 0x8);

            // NOTE: Uninline.
            CheckPanelInputMode(6, 0x80);

            // NOTE: Uninline.
            CheckPanelInputMode(GetPanel_21_7(), 0x100);

            // NOTE: Uninline.
            CheckPanelInputMode(GetPanel_19_0(), 0x100);

            // NOTE: Uninline.
            CheckPanelInputMode(GetPanel_21_0(), 0x100);

            // NOTE: Uninline.
            CheckPanelInputMode(8, 0x200);

            // NOTE: Uninline.
            CheckPanelInputMode(17, 0x1000);

            CheckEnablePortaits(1);
            CheckEnableLeftPanel();
            m_cUIManager.TimerAsynchronousUpdate();
        }

        if (m_deltaTime != 0) {
            for (INT nArea = 0; nArea < CINFGAME_MAX_AREAS; nArea++) {
                CGameArea* pArea = pGame->m_gameAreas[nArea];
                if (pArea != NULL) {
                    pArea->CompressTime(m_deltaTime);

                    if (bActiveEngine) {
                        if (pArea == pGame->GetVisibleArea()) {
                            pArea->SortLists();
                        }
                    }
                }
            }

            m_deltaTime = 0;

            m_weather.CompressTime();
        }

        for (SHORT nPortrait = 0; nPortrait < pGame->GetNumCharacters(); nPortrait++) {
            LONG nCharacterId = pGame->m_characterPortraits[nPortrait];

            rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
            if (rc == CGameObjectArray::SUCCESS) {
                if (pSprite->GetArea() == NULL) {
                    CDerivedStats* pDStats = pSprite->GetDerivedStats();
                    if (!pSprite->m_bAllowEffectListCall) {
                        pDStats = &(pSprite->m_tempStats);
                    }

                    if ((pDStats->m_generalState & STATE_DEAD) != 0) {
                        if (pSprite->DoAIUpdate(pGame->GetWorldTimer()->m_active, g_pChitin->nAUCounter)) {
                            do {
                                rc = pGame->GetObjectArray()->GetDeny(nCharacterId,
                                    CGameObjectArray::THREAD_ASYNCH,
                                    reinterpret_cast<CGameObject**>(&pSprite),
                                    INFINITE);
                            } while (rc == CGameObjectArray::SHARED);

                            if (rc == CGameObjectArray::SUCCESS) {
                                pSprite->ProcessAI();

                                pGame->GetObjectArray()->ReleaseDeny(nCharacterId,
                                    CGameObjectArray::THREAD_ASYNCH,
                                    INFINITE);
                            }
                        }
                    }
                }

                pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }

        CGameAIGame* pAIGame;

        do {
            rc = pGame->GetObjectArray()->GetDeny(pGame->m_nAIIndex,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pAIGame),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pAIGame->GetVertListPos() == NULL) {
                if (pGame->GetVisibleArea() != NULL) {
                    pAIGame->AddToArea(pGame->GetVisibleArea(),
                        CPoint(0, 0),
                        0, CGameObject::LIST_FRONT);
                }
            }

            pAIGame->ProcessAI();

            pGame->GetObjectArray()->ReleaseDeny(pGame->m_nAIIndex,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        pGame->sub_5AC0D0();

        for (INT nArea = 0; nArea < CINFGAME_MAX_AREAS; nArea++) {
            CGameArea* pArea = pGame->GetArea(nArea);
            if (pArea != NULL) {
                if (pArea == pGame->GetVisibleArea()
                    && pArea->m_firstRender == 0) {
                    pArea->m_bPicked = FALSE;
                    CUIPanel* pPanel = m_cUIManager.GetPanel(1);
                    if (!m_cUIManager.field_0
                        && pPanel->m_bActive
                        && pPanel->IsOver(g_pChitin->m_ptPointer)) {
                        for (SHORT nPortrait = 0; nPortrait < pGame->GetNumCharacters(); nPortrait++) {
                            CUIControlBase* pPortrait = pPanel->GetControl(nPortrait);
                            if (pPortrait->IsOver(g_pChitin->m_ptPointer - pPanel->m_ptOrigin)) {
                                do {
                                    rc = pGame->GetObjectArray()->GetShare(pGame->GetCharacterId(nPortrait),
                                        CGameObjectArray::THREAD_ASYNCH,
                                        reinterpret_cast<CGameObject**>(&pSprite),
                                        INFINITE);
                                } while (rc == CGameObjectArray::SHARED);

                                if (rc == CGameObjectArray::SUCCESS) {
                                    if (pSprite->GetArea() == pArea) {
                                        CDerivedStats* pDStats = pSprite->m_bAllowEffectListCall
                                            ? &(pSprite->m_derivedStats)
                                            : &(pSprite->m_tempStats);
                                        if ((pDStats->m_generalState & STATE_DEAD) != 0) {
                                            pArea->m_iPicked = pGame->GetCharacterId(nPortrait);
                                            pArea->m_nToolTip = 0;

                                            if (pSprite->Orderable(FALSE)) {
                                                pArea->m_iPickedTarget = pSprite->GetTargetId();
                                            }

                                            pArea->m_bPicked = TRUE;
                                        }
                                    }
                                    pGame->GetObjectArray()->ReleaseShare(pGame->GetCharacterId(nPortrait),
                                        CGameObjectArray::THREAD_ASYNCH,
                                        INFINITE);
                                }
                                break;
                            }
                        }
                    }
                }

                pArea->AIUpdate();

                BOOL bAreaCanBeDeleted;
                if (pArea->m_nCharacters != 0
                    || pArea == pGame->m_pGameAreaMaster
                    || pGame->m_nCharacterTerminationSequenceDelay != 0) {
                    bAreaCanBeDeleted = FALSE;
                } else {
                    INT nAreas = 0;
                    for (INT nArea = 0; nArea < CINFGAME_MAX_AREAS; nArea++) {
                        if (pGame->GetArea(nArea) != NULL) {
                            nAreas++;
                        }
                    }

                    if (nAreas > 1) {
                        // NOTE: Calls unknown empty `CGameArea` function,
                        // probably `ForceChaseCode` which was likely
                        // superceeded by INI spawner.
                        // pArea->ForceChaseCode();

                        pArea->ExitSpawn();
                        pArea->sub_47A060();

                        if (g_pChitin->cNetwork.GetSessionOpen()) {
                            bAreaCanBeDeleted = FALSE;
                        } else {
                            bAreaCanBeDeleted = TRUE;
                        }
                    } else {
                        bAreaCanBeDeleted = FALSE;
                    }
                }

                if (!bAreaCanBeDeleted) {
                    if (m_waitingOnResize > 0) {
                        EnterCriticalSection(&(pArea->field_1FC));

                        if (!EqualRect(pArea->GetInfinity()->rViewPort, m_newViewSize)
                            || m_bForceViewSize) {
                            INT x;
                            INT y;
                            pArea->GetInfinity()->GetViewPosition(x, y);
                            pArea->GetInfinity()->SetViewPort(m_newViewSize);
                            pArea->GetInfinity()->SetViewPosition(x, y, TRUE);
                        }
                        m_cUIManager.InvalidateRect(NULL);

                        LeaveCriticalSection(&(pArea->field_1FC));
                    }
                } else {
                    DeleteArea(pArea);
                }
            }
        }

        if (m_waitingOnResize > 0) {
            m_waitingOnResize--;
        }

        if (m_waitingOnResize == 0) {
            m_bForceViewSize = FALSE;
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            DeleteAreaMultiplayer();
        }

        if (bActiveEngine) {
            g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

            if (m_bored) {
                if (pGame->GetWorldTimer()->m_active) {
                    m_boredCount++;
                }

                for (SHORT nAttempt = 0; m_boredCount > pGame->GetOptions()->m_nBoredTime && nAttempt < 2 * pGame->GetNumCharacters(); nAttempt++) {
                    SHORT nPortrait = pGame->GetNumCharacters() != 0
                        ? rand() % pGame->GetNumCharacters()
                        : 0;

                    do {
                        rc = pGame->GetObjectArray()->GetShare(pGame->GetCharacterId(nPortrait),
                            CGameObjectArray::THREAD_ASYNCH,
                            reinterpret_cast<CGameObject**>(&pSprite),
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        if (pSprite->Orderable(FALSE)) {
                            CMessagePlaySound* pPlaySound = new CMessagePlaySound(4,
                                TRUE,
                                TRUE,
                                pSprite->GetId(),
                                pSprite->GetId());
                            g_pBaldurChitin->GetMessageHandler()->AddMessage(pPlaySound, FALSE);
                            m_boredCount = pGame->GetOptions()->m_nBoredTime
                                - pGame->GetOptions()->m_nBoredTime / 4;
                        }

                        pGame->GetObjectArray()->ReleaseShare(pGame->GetCharacterId(nPortrait),
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    } else {
                        break;
                    }
                }
            } else {
                m_boredCount = 0;
                m_bored = TRUE;
            }
        }

        if (m_scrollLockId != CGameObjectArray::INVALID_INDEX) {
            CGameObject* pObject;

            // FIXME: Result is ignored.
            pGame->GetObjectArray()->GetShare(m_scrollLockId,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);

            CPoint ptPos = pObject->GetPos();
            CRect rViewPort = pObject->GetArea()->GetInfinity()->rViewPort;

            CGameArea* pVisibleArea = pGame->GetVisibleArea();
            pVisibleArea->GetInfinity()->m_ptScrollDest.x = ptPos.x - rViewPort.Width() / 2;
            pVisibleArea->GetInfinity()->m_ptScrollDest.y = ptPos.y - rViewPort.Height() / 2;
            pVisibleArea->GetInfinity()->m_nLastTickCount = GetTickCount();
            pVisibleArea->GetInfinity()->m_autoScrollSpeed = 0;

            pGame->GetObjectArray()->ReleaseShare(m_scrollLockId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }

        if (pGame->GetWorldTimer()->m_active) {
            pGame->m_cLimboList.AIUpdate();
        }

        m_internalLoadedDialog.AsynchronousUpdate();

        if (m_pActiveDialogDisplay != NULL) {
            CUIControlTextDisplay* pText;
            switch (m_pActiveDialogDisplay->m_pPanel->m_nID) {
            case 0:
            case 4:
            case 7:
            case 22:
                pText = m_pActiveDialogDisplay;
                break;
            case 19:
                pText = static_cast<CUIControlTextDisplay*>(m_pActiveDialogDisplay->m_pPanel->GetControl(3));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
                // __LINE__: 3288
                UTIL_ASSERT(pText == m_pActiveChatDisplay);

                break;
            case 21:
                pText = static_cast<CUIControlTextDisplay*>(m_pActiveDialogDisplay->m_pPanel->GetControl(3));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
                // __LINE__: 3293
                UTIL_ASSERT(pText == m_pActiveChatDisplay);

                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
                // __LINE__: 3297
                UTIL_ASSERT(FALSE);
            }

            if (pText != NULL) {
                m_nChatMessageCount = g_pBaldurChitin->GetBaldurMessage()->m_cChatBuffer.UpdateTextDisplay(pText,
                    m_nChatMessageCount);
            }
        }

        if (pGame->field_43E6 || !pGame->GetWorldTimer()->m_active) {
            m_interactionIndex = CGameObjectArray::INVALID_INDEX;
            m_interactionTarget = CGameObjectArray::INVALID_INDEX;
        } else {
            HandleAmbiance();
            HandleDeathReaction();
        }

        if (pGame->m_nCharacterTerminationSequenceDelay > 0) {
            if (--pGame->m_nCharacterTerminationSequenceDelay <= 0) {
                CInfGame::StartCharacterTerminationSequence();
            }
        }

        if (m_autoPauseId != CGameObjectArray::INVALID_INDEX) {
            if (!pGame->field_43E6) {
                if (m_autoPauseRef != -1) {
                    g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(m_autoPauseName,
                        m_autoPauseRef,
                        m_autoPauseColor,
                        RGB(215, 215, 190),
                        -1,
                        m_autoPauseId,
                        m_autoPauseId);
                }

                if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
                    if (!g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0)) {
                        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(m_autoPauseName,
                            17122,
                            m_autoPauseColor,
                            RGB(215, 215, 190),
                            -1,
                            m_autoPauseId,
                            m_autoPauseId);
                    }
                }

                if (pGame->GetOptions()->m_bAutoPauseCenter) {
                    SHORT nPortrait = pGame->GetCharacterPortraitNum(m_autoPauseId);
                    if (nPortrait != -1) {
                        pGame->OnPortraitLDblClick(nPortrait);
                    }
                }
            }
            m_autoPauseId = CGameObjectArray::INVALID_INDEX;
        }

        if (field_EA4 == 17) {
            CUIPanel* pPanel = m_cUIManager.GetPanel(17);

            if (m_bHardPaused) {
                static_cast<CUIControlButton*>(pPanel->GetControl(1))->SetEnabled(FALSE);
                static_cast<CUIControlButton*>(pPanel->GetControl(2))->SetEnabled(FALSE);
            } else {
                static_cast<CUIControlButton*>(pPanel->GetControl(1))->SetEnabled(TRUE);
                static_cast<CUIControlButton*>(pPanel->GetControl(2))->SetEnabled(TRUE);
            }

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && !g_pChitin->cNetwork.GetSessionHosting()) {
                static_cast<CUIControlButton*>(pPanel->GetControl(1))->SetEnabled(FALSE);
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bLeaveAreaLuaPanicPending == TRUE
            && pGame->GetWorldTimer()->m_gameTime >= m_ulLeaveAreaLuaPanicTimer) {
            m_bLeaveAreaLuaPanicPending = FALSE;
            m_ulLeaveAreaLuaPanicTimer = -1;
            LeaveAreaLuaPanic(m_ptLeaveAreaLuaPanicLocation,
                m_nLeaveAreaLuaPanicDirection,
                m_sLeaveAreaLuaPanicAreaName,
                m_sLeaveAreaLuaPanicParchment);
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bChapterTransitionPending == TRUE) {
            BOOLEAN bPermitted = TRUE;
            if (pGame->field_43E2 == 386 || pGame->field_43E2 == 1282) {
                bPermitted = FALSE;
            }
            if (pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
                bPermitted = FALSE;
            }

            if (m_bHardPaused != TRUE && bPermitted) {
                m_bChapterTransitionPending = FALSE;

                if (pGame->GetCurrentChapter() < m_nChapterTransition) {
                    g_pBaldurChitin->m_pEngineChapter->StartChapterMultiplayerHost(m_nChapterTransition,
                        m_szChapterTransitionResRef);
                    m_bChapterTransitionPending = FALSE;
                    m_nChapterTransition = 255;
                }
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bMoviePending == TRUE) {
            BOOLEAN bPermitted = TRUE;
            if (pGame->field_43E2 == 386 || pGame->field_43E2 == 1282) {
                bPermitted = FALSE;
            }
            if (pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
                bPermitted = FALSE;
            }

            if (m_bHardPaused != TRUE && bPermitted == TRUE) {
                StartMovieMultiplayerHost(m_szMovieResRef);
                m_bMoviePending = FALSE;
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bPendingMapWorld == TRUE) {
            BOOLEAN bPermitted = TRUE;
            if (pGame->field_43E2 == 386 || pGame->field_43E2 == 1282) {
                bPermitted = FALSE;
            }
            if (pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
                bPermitted = FALSE;
            }

            if (m_bHardPaused != TRUE && bPermitted == TRUE) {
                // NOTE: Uninline.
                StartMapWorldMultiplayerHost(m_idPendingMapWorldController,
                    m_nPendingMapWorldDirection);

                m_bPendingMapWorld = FALSE;
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bRestPending == TRUE) {
            BOOLEAN bPermitted = TRUE;
            if (pGame->field_43E2 == 386 || pGame->field_43E2 == 1282) {
                bPermitted = FALSE;
            }
            if (pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
                bPermitted = FALSE;
            }

            if (m_bHardPaused != TRUE && bPermitted == TRUE) {
                StartRestMultiplayerHost(m_nRestHP,
                    m_bRestRenting,
                    m_bRestMovie);
                m_bRestPending = FALSE;
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bPendingReformParty == TRUE) {
            BOOLEAN bPermitted = TRUE;
            if (pGame->field_43E2 == 386 || pGame->field_43E2 == 1282) {
                bPermitted = FALSE;
            }
            if (pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
                bPermitted = FALSE;
            }

            if (m_bHardPaused != TRUE && bPermitted == TRUE) {
                // NOTE: Uninline.
                StartReformPartyMultiplayerHost();

                m_bPendingReformParty = FALSE;
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && pGame->GetMultiplayerSettings()->m_bHostPermittedDialog == TRUE) {
            if (pGame->field_43E2 != 386 && pGame->field_43E2 != 1282) {
                if (++pGame->GetMultiplayerSettings()->m_nHostPermittedDialogDelay >= 30) {
                    g_pBaldurChitin->GetBaldurMessage()->DialogRequestKillOrUse();
                    pGame->GetMultiplayerSettings()->m_nHostPermittedDialogDelay = 0;
                }
            } else {
                pGame->GetMultiplayerSettings()->m_nHostPermittedDialogDelay = 0;
            }
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && m_bHardPaused) {
            // NOTE: Uninline.
            CheckEndOfHardPause();
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSynchServerPending == TRUE
            && g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSynchServerFinished == FALSE) {
            // NOTE: Uninline.
            CheckEndOfMultiplayerSynch();
        }

        m_weather.Update();

        if (m_bGameOverPanel && m_movie == "") {
            m_bGameOverPanel = FALSE;
            StartDeath();
            field_10F0 = 0;
        }

        if (m_nBattleCryTimeOut > 0) {
            m_nBattleCryTimeOut--;
        }

        DWORD nOtherTickCount = GetTickCount();
        g_pBaldurChitin->field_1A72[0] += nOtherTickCount - g_pBaldurChitin->field_1AF2[0];
        g_pBaldurChitin->field_1AF2[0] = nOtherTickCount;

        if (m_comingOutOfDialog > 0) {
            if (--m_comingOutOfDialog == 0) {
                if (pGame->field_43E2 != 322) {
                    pGame->field_43E6 = 0;
                }
            }
        }

        CVidMode* pCurrentVidMode1 = g_pChitin->GetCurrentVideoMode();

        if (pCurrentVidMode1->m_nFade != 0) {
            m_nBlackOutCountDown = 0;
        } else {
            if (m_nBlackOutCountDown == 0) {
                m_nBlackOutCountDown = 150;
            }
        }

        if (m_nBlackOutCountDown > 0) {
            if (pGame->GetWorldTimer()->m_active) {
                if (--m_nBlackOutCountDown == 0) {
                    if (pCurrentVidMode1->m_nFade == 0) {
                        CVidMode* pCurrentVidMode2 = g_pChitin->GetCurrentVideoMode();
                        CVidMode::NUM_FADE_FRAMES = 1;
                        pCurrentVidMode2->m_bFadeTo = FALSE;
                        pCurrentVidMode2->m_nFade = 0;

                        for (int frame = 0; frame < 20; frame++) {
                            CVidMode* pCurrentVidMode3 = g_pChitin->GetCurrentVideoMode();
                            if (!pCurrentVidMode3->m_bFadeTo) {
                                if (pCurrentVidMode3->m_nFade < CVidMode::NUM_FADE_FRAMES) {
                                    pCurrentVidMode3->m_nFade++;
                                }
                            } else {
                                if (pCurrentVidMode3->m_nFade > 0) {
                                    pCurrentVidMode3->m_nFade--;
                                }
                            }

                            g_pChitin->m_bDisplayStale = TRUE;
                            SleepEx(60, FALSE);
                        }
                    }
                }
            }
        }
    }
}

// 0x68DEC0
void CScreenWorld::TimerSynchronousUpdate()
{
    // 0x8B5480
    static BYTE byte_8B5480[3] = {
        7,
        0,
        22,
    };

    // 0x8B5484
    static BYTE byte_8B5484[3] = {
        2,
        2,
        0,
    };

    for (int index = 0; index < 3; index++) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(byte_8B5480[index]);
        if (pPanel->m_bActive) {
            m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(byte_8B5484[index]));
        }
    }

    if (field_119D) {
        pVidMode->LoadFogOWarSurfaces(CInfGame::FOGOWAR_RESREF);
        field_119D = FALSE;
    }

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    pGame->SynchronousUpdate();

    CGameArea* pArea = pGame->GetVisibleArea();
    if (pArea == NULL || pArea->m_firstRender < 2) {
        if (field_EA4 == 6) {
            SHORT nPortrait;

            for (nPortrait = 0; nPortrait <= 5; nPortrait++) {
                pGame->sub_5AF420(nPortrait, 1);
            }

            for (nPortrait = 50; nPortrait <= 55; nPortrait++) {
                pGame->sub_5AF420(nPortrait, 1);
            }
        }

        m_cUIManager.Render();

        CGameArea* pArea = pGame->GetVisibleArea();
        if (pArea != NULL) {
            pVidMode->EnableScissoring();
            pArea->Render(pVidMode, 0);
            pVidMode->DisableScissoring();
        }

        pVidMode->Flip(TRUE);
    }
}

// 0x68DFD0
BOOL CScreenWorld::TogglePauseGame(char a2, char a3, int a4)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x68E630
void CScreenWorld::UpdateContainerStatus(LONG nContainerId, SHORT nSlotNum)
{
    SHORT nIndex = nSlotNum - 5 * m_nTopContainerRow;
    CUIPanel* pPanel = m_cUIManager.GetPanel(8);
    if (pPanel->m_bActive) {
        if (nContainerId == g_pBaldurChitin->GetObjectGame()->m_iContainer) {
            if (nSlotNum == -1) {
                // NOTE: Signed compare.
                for (INT nButtonID = 0; nButtonID <= 9; nButtonID++) {
                    pPanel->GetControl(nButtonID)->InvalidateRect();
                }
            } else if (nSlotNum >= 0 && nSlotNum <= 9) {
                CUIControlBase* pControl = pPanel->GetControl(nSlotNum);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
                // __LINE__: 4044
                UTIL_ASSERT(pControl != NULL);

                pControl->InvalidateRect();
            }
        }
    }
}

// 0x68E6E0
BOOLEAN CScreenWorld::ReadyMovie(const CResRef& res, BOOLEAN bForcedFromServer)
{
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && !g_pChitin->cNetwork.GetSessionHosting()
        && !bForcedFromServer) {
        if (res != CInfinity::DAWN_MOVIE
            && res != CInfinity::DUSK_MOVIE
            && res != "DEATH1") {
            g_pBaldurChitin->GetBaldurMessage()->SendMovieRequestToServer(res);
        }
        return FALSE;
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        CString cResString;
        res.CopyToString(cResString);

        BYTE movieResRef[RESREF_SIZE];
        memcpy(movieResRef, cResString.GetBuffer(RESREF_SIZE), RESREF_SIZE);

        g_pBaldurChitin->m_pEngineWorld->StartMovieMultiplayerHost(movieResRef);
        return FALSE;
    }

    m_movie = res;
    if (m_movie == CInfinity::DAWN_MOVIE
        || m_movie == CInfinity::DUSK_MOVIE
        || m_movie == "DEATH1") {
        g_pBaldurChitin->m_pEngineProjector->field_145 = 1;
    }

    if (bForcedFromServer == TRUE) {
        if (m_movie == CInfinity::DAWN_MOVIE) {
            g_pBaldurChitin->m_pEngineWorld->m_bSetDayOnActivate = TRUE;
        } else if (m_movie == CInfinity::DUSK_MOVIE) {
            g_pBaldurChitin->m_pEngineWorld->m_bSetNightOnActivate = TRUE;
        }

        if (m_movie == "DEATH1") {
            g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
            g_pBaldurChitin->m_pEngineWorld->m_bGameOverPanel = TRUE;
        }
    }

    g_pBaldurChitin->GetObjectCursor()->m_bVisible = FALSE;
    g_pBaldurChitin->m_pEngineProjector->PlayMovie(m_movie);
    m_movie = "";

    return TRUE;
}

// 0x68E950
BOOLEAN CScreenWorld::ReadyEndCredits(BOOLEAN bForcedFromServer)
{
    // NOTE: Unused.
    CString v1;

    if (!g_pChitin->cNetwork.GetSessionOpen()
        || g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        g_pBaldurChitin->GetBaldurMessage()->RequestClientSignal(CBaldurMessage::SIGNAL_END_GAME);
        m_bPlayEndCredits = TRUE;
        return TRUE;
    } else {
        return FALSE;
    }
}

// 0x68F9D0
void CScreenWorld::EndDialog(BOOLEAN bForceExecution, BOOLEAN fullEnd)
{
    // TODO: Incomplete.
}

// FIXME: `areaName` should be reference.
//
// 0x690410
void CScreenWorld::MoveToArea(CString areaName)
{
    // NOTE: Uninline.
    CAIAction leave(CAIAction::LEAVEAREALUA, areaName, CPoint(0, 0), 0);
    leave.m_specificID2 = 0;

    g_pBaldurChitin->GetObjectGame()->GetGroup()->GroupAction(leave, TRUE, NULL);
}

// 0x690640
void CScreenWorld::SaveScreen()
{
    INT x;
    INT y;
    CRect rViewPort;

    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
    pArea->GetInfinity()->GetViewPosition(x, y);
    rViewPort.CopyRect(pArea->GetInfinity()->rViewPort);

    pArea->GetInfinity()->SetViewPort(CInfinity::stru_8E79A8);

    // NOTE: Some inlining, not sure which.
    if (pArea != NULL) {
        pArea->Render(pVidMode, 0);
    }

    pArea->GetInfinity()->SetViewPort(rViewPort);
    pArea->GetInfinity()->SetViewPosition(x, y, TRUE);
}

// 0x6906F0
void CScreenWorld::SetCurrentXP(DWORD dwCurrentXP)
{
    CAIGroup* pGroup = g_pBaldurChitin->GetObjectGame()->GetGroup();
    LONG* pSpriteList = pGroup->GetGroupList();
    INT nCount = pGroup->GetCount();

    CGameSprite* pSprite;

    for (INT nIndex = 0; nIndex < nCount; nIndex++) {
        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(pSpriteList[nIndex],
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pSprite->GetBaseStats()->m_xp = dwCurrentXP;
            pSprite->field_562C = 1;

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(pSpriteList[nIndex],
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    delete pSpriteList;
}

// 0x6907E0
void CScreenWorld::AddGold(DWORD dwGold)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 5054
    UTIL_ASSERT(pGame != NULL);

    pGame->AddPartyGold(dwGold);
}

// 0x690EB0
void CScreenWorld::StopContainer()
{
    if (GetManager()->field_0 == 0) {
        if (m_nAutoHideInterface > 0) {
            m_nAutoHideInterface++;
        }
    } else {
        m_nAutoHideInterface++;
        UnhideInterface();
    }

    m_newViewSize = CInfinity::stru_8E79B8;
    m_waitingOnResize = 2;
    m_bForceViewSize = FALSE;

    sub_695570(TRUE, FALSE);

    m_cUIManager.GetPanel(8)->SetActive(FALSE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 5353
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 5355
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    switch (pGame->GetContainerType(nContainer)) {
    case 1:
        PlayGUISound(CResRef("GAM_12A"));
        break;
    case 2:
        PlayGUISound(CResRef("AMB_D05B"));
        break;
    case 3:
        PlayGUISound(CResRef("AMB_D13"));
        break;
    case 9:
        PlayGUISound(CResRef("GAM_05"));
        break;
    case 11:
        PlayGUISound(CResRef("AMB_D13"));
        break;
    case 12:
        PlayGUISound(CResRef("AMB_D05B"));
        break;
    }

    pGame->CompressContainer(nContainer);

    if (m_nAutoHideInterface > 0) {
        m_nAutoHideInterface--;
        HideInterface();
    }

    field_EA4 = -1;
}

// 0x691090
void CScreenWorld::CancelPopup()
{
    switch (field_EA4) {
    case -1:
    case 0:
    case 7:
        break;
    case 6:
        StopCommand();
        field_EA4 = -1;
        break;
    case 8:
        StopContainer();
        field_EA4 = -1;
        break;
    case 15:
    case 17:
        StopDeath();
        field_EA4 = -1;
        break;
    case 19:
    case 21:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 5469
        UTIL_ASSERT(FALSE);
    }
}

// 0x691140
void CScreenWorld::StartCommand()
{
    // NOTE: Uninline.
    CancelPopup();

    field_EA4 = 6;
    m_cUIManager.ClearTooltip();

    for (INT nId = 6; nId <= 17; nId++) {
        // FIXME: `GetPanel` should be outside of the loop.
        CUIControlBase* pControl = m_cUIManager.GetPanel(1)->GetControl(nId);
        if (pControl != NULL) {
            pControl->SetActive(FALSE);
        }
    }

    m_cUIManager.GetPanel(GetPanel_22_0())->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(TRUE);
    m_cUIManager.SetCapture(m_cUIManager.GetPanel(6)->GetControl(0), CUIManager::KEYBOARD);
    m_cUIManager.GetPanel(6)->InvalidateRect(NULL);
}

// 0x6912A0
void CScreenWorld::StopCommand()
{
    field_F37 = 0;

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    m_cUIManager.GetPanel(6)->SetActive(FALSE);

    for (INT nId = 6; nId <= 17; nId++) {
        // FIXME: `GetPanel` should be outside of the loop.
        CUIControlBase* pControl = m_cUIManager.GetPanel(1)->GetControl(nId);
        if (pControl != NULL) {
            pControl->SetActive(TRUE);
        }
    }

    // FIXME: Global.
    if (g_pBaldurChitin->m_pEngineWorld->field_11F0) {
        m_cUIManager.GetPanel(1)->InvalidateRect(NULL);
    }

    // FIXME: Global.
    if (g_pBaldurChitin->m_pEngineWorld->field_11F4) {
        // FIXME: Repeats.
        m_cUIManager.GetPanel(GetPanel_22_0())->SetActive(TRUE);
        m_cUIManager.GetPanel(GetPanel_22_0())->InvalidateRect(NULL);
    }

    field_EA4 = -1;
}

// FIXME: `cResStore` should be reference.
//
// 0x6913C0
void CScreenWorld::StartStore(const CAIObjectType& cAIProprietor, const CAIObjectType& cAICustomer, CResRef cResStore, BOOLEAN bInitiate)
{
    // TODO: Incomplete.
}

// 0x691B50
void CScreenWorld::StopStore()
{
    // TODO: Incomplete.
}

// 0x691D10
void CScreenWorld::HandleAmbiance()
{
    // TODO: Incomplete.
}

// 0x692090
void CScreenWorld::HandleDeathReaction()
{
    if (!m_deathSoundList.IsEmpty()) {
        CDeathSound* pDeathSound = m_deathSoundList.GetHead();
        if (!pDeathSound->m_started) {
            pDeathSound->m_started = TRUE;
            if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(pDeathSound->m_characterId) != -1) {
                CMessageVerbalConstant* pVerbalConstant = new CMessageVerbalConstant(pDeathSound->m_soundNum,
                    pDeathSound->m_characterId,
                    pDeathSound->m_characterId);

                g_pBaldurChitin->GetMessageHandler()->AddMessage(pVerbalConstant, FALSE);

                if (pDeathSound->m_pTrigger != NULL) {
                    CMessageSetTrigger* pSetTrigger = new CMessageSetTrigger(*pDeathSound->m_pTrigger,
                        pDeathSound->m_characterId,
                        pDeathSound->m_characterId);

                    g_pBaldurChitin->GetMessageHandler()->AddMessage(pSetTrigger, FALSE);

                    delete pDeathSound->m_pTrigger;
                    pDeathSound->m_pTrigger = NULL;
                }
            }
        } else {
            if (pDeathSound->m_soundLength-- <= 0) {
                delete m_deathSoundList.RemoveHead();
            }
        }
    }
}

// 0x692290
POSITION CScreenWorld::DisplayText(const CString& sName, const CString& sText, COLORREF rgbNameColor, COLORREF rgbTextColor, LONG lMarker, BOOLEAN bMoveToTop)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
        return NULL;
    }

    POSITION pos = m_pActiveDialogDisplay->DisplayString(sName,
        sText,
        rgbNameColor,
        rgbTextColor,
        lMarker,
        bMoveToTop,
        TRUE);

    if (m_pActiveDialogDisplay->GetNumLines(pos) > 2) {
        if (GetManager()->GetPanel(GetPanel_22_0())->m_bActive
            && !m_cUIManager.field_0) {
            // FIXME: Same panels?
            CUIPanel* pPanel1 = GetManager()->GetPanel(GetPanel_22_0());
            CUIPanel* pPanel2 = GetManager()->GetPanel(GetPanel_22_0());

            pPanel2->SetActive(FALSE);
            pPanel1->SetActive(TRUE);

            CUIControlTextDisplay* pOldDialogDisplay = m_pActiveDialogDisplay;
            m_pActiveDialogDisplay = static_cast<CUIControlTextDisplay*>(pPanel1->GetControl(1));

            // FIXME: Obtains same control twice.
            static_cast<CUIControlTextDisplay*>(pPanel1->GetControl(1))->CopyDisplay(pOldDialogDisplay);

            m_pActiveDialogDisplay->SetTopString(pos);

            m_newViewSize = CInfinity::stru_8E79B8;
            m_waitingOnResize = 2;
            m_bForceViewSize = FALSE;
        }
    }

    return pos;
}

// 0x692460
POSITION CScreenWorld::DisplayText(const CString& sName, const CString& sText, LONG lMarker, BOOLEAN bMoveToTop)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
        return NULL;
    }

    POSITION pos = m_pActiveDialogDisplay->DisplayString(sName,
        sText,
        m_pActiveDialogDisplay->m_rgbLabelColor,
        m_pActiveDialogDisplay->m_rgbTextColor,
        lMarker,
        bMoveToTop,
        TRUE);

    if (m_pActiveDialogDisplay->GetNumLines(pos) > 2) {
        if (GetManager()->GetPanel(GetPanel_22_0())->m_bActive
            && !m_cUIManager.field_0) {
            // FIXME: Same panels?
            CUIPanel* pPanel1 = GetManager()->GetPanel(GetPanel_22_0());
            CUIPanel* pPanel2 = GetManager()->GetPanel(GetPanel_22_0());

            pPanel2->SetActive(FALSE);
            pPanel1->SetActive(TRUE);

            CUIControlTextDisplay* pOldDialogDisplay = m_pActiveDialogDisplay;
            m_pActiveDialogDisplay = static_cast<CUIControlTextDisplay*>(pPanel1->GetControl(1));

            // FIXME: Obtains same control twice.
            static_cast<CUIControlTextDisplay*>(pPanel1->GetControl(1))->CopyDisplay(pOldDialogDisplay);

            // NOTE: No `SetTopString` as in the function above.

            m_newViewSize = CInfinity::stru_8E79B8;
            m_waitingOnResize = 2;
            m_bForceViewSize = FALSE;
        }
    }

    return pos;
}

// 0x692630
void CScreenWorld::RemoveText(POSITION pos)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
        m_pActiveDialogDisplay->RemoveString(pos);
    }
}

// 0x692660
void CScreenWorld::SetItemMarker(POSITION pos, LONG lMarker)
{
    if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
        m_pActiveDialogDisplay->SetItemMarker(pos, lMarker);
    }
}

// 0x692690
void CScreenWorld::ClearChatMessages()
{
    m_nChatMessageCount = 0;
}

// 0x6926A0
void CScreenWorld::HideInterface()
{
    // TODO: Incomplete.
}

// 0x692850
void CScreenWorld::UnhideInterface()
{
    // TODO: Incomplete.
}

// 0x692A50
void CScreenWorld::StartDeath()
{
    // TODO: Incomplete.
}

// 0x692E80
void CScreenWorld::StopDeath()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 7935
    UTIL_ASSERT(pGame != NULL);

    pGame->SetTempCursor(4);

    pGame->GetWorldTimer()->StartTime();

    m_bPaused = FALSE;
    pGame->field_43E2 = -1;

    m_cUIManager.GetPanel(17)->SetActive(FALSE);
    m_cUIManager.GetPanel(1)->SetActive(TRUE);
    m_cUIManager.GetPanel(GetPanel_22_0())->SetActive(TRUE);
    m_cUIManager.GetPanel(1)->InvalidateRect(NULL);
    m_cUIManager.GetPanel(GetPanel_22_0())->InvalidateRect(NULL);

    field_EA4 = -1;

    if (m_cUIManager.m_pFocusedControl != NULL) {
        // NOTE: Uninline.
        m_cUIManager.KillCapture();
    }
}

// 0x692FD0
DWORD CScreenWorld::GetPanel_21_7()
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        return 21;
    } else {
        return 7;
    }
}

// 0x693000
DWORD CScreenWorld::GetPanel_22_0()
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        return 22;
    } else {
        return 0;
    }
}

// 0x693030
DWORD CScreenWorld::GetPanel_21_0()
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        return 21;
    } else {
        return 0;
    }
}

// 0x693060
DWORD CScreenWorld::GetPanel_19_0()
{
    if (g_pBaldurChitin->cNetwork.GetSessionOpen()
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        return 19;
    } else {
        return 0;
    }
}

// 0x693090
void CScreenWorld::SetPendingChapterChange(BYTE nChapter, BYTE* szChapterResRef)
{
    if (nChapter <= CGameJournal::NUM_CHAPTERS) {
        m_bChapterTransitionPending = TRUE;
        m_nChapterTransition = nChapter;
        memcpy(m_szChapterTransitionResRef, szChapterResRef, RESREF_SIZE);
    } else {
        m_bChapterTransitionPending = FALSE;
        m_nChapterTransition = -1;
        memset(m_szChapterTransitionResRef, 0, RESREF_SIZE);
    }
}

// 0x6930F0
void CScreenWorld::SetPendingMovie(BYTE* szMovieResRef)
{
    m_bMoviePending = TRUE;
    memcpy(m_szMovieResRef, szMovieResRef, RESREF_SIZE);
}

// 0x693110
void CScreenWorld::StartSaveGameMultiplayerHost()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // FIXME: What for?
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    BOOLEAN bListenToJoin = pGame->GetMultiplayerSettings()->GetListenToJoinOption();
    pGame->GetMultiplayerSettings()->SetListenToJoinOption(FALSE, TRUE);

    pWorld->m_bEndMajorEventListenToJoin = bListenToJoin;
    pWorld->m_bEndMajorEventPauseStatus = pWorld->m_bPaused;
    pWorld->m_bHardPaused = TRUE;

    if (!pWorld->m_bPaused) {
        // "Paused for saving game"
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(-1,
            19716,
            RGB(255, 0, 0),
            RGB(255, 0, 0),
            -1,
            CGameObjectArray::INVALID_INDEX,
            CGameObjectArray::INVALID_INDEX);

        pWorld->TogglePauseGame(0, 1, g_pChitin->cNetwork.m_idLocalPlayer);
    }
}

// 0x6931E0
void CScreenWorld::StartMovieMultiplayerHost(BYTE* cMovieResRef)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // FIXME: What for?
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    BOOLEAN bListenToJoin = pGame->GetMultiplayerSettings()->GetListenToJoinOption();
    pGame->GetMultiplayerSettings()->SetListenToJoinOption(FALSE, TRUE);

    pWorld->m_bEndMajorEventListenToJoin = bListenToJoin;
    pWorld->m_bEndMajorEventPauseStatus = pWorld->m_bPaused;
    pWorld->m_bHardPaused = TRUE;

    if (!pWorld->m_bPaused) {
        // "Paused for movie"
        g_pBaldurChitin->GetBaldurMessage()->DisplayTextRef(-1,
            17557,
            RGB(255, 0, 0),
            RGB(255, 0, 0),
            -1,
            CGameObjectArray::INVALID_INDEX,
            CGameObjectArray::INVALID_INDEX);

        pWorld->TogglePauseGame(0, 1, g_pChitin->cNetwork.m_idLocalPlayer);
    }

    g_pBaldurChitin->GetBaldurMessage()->MovieAnnounceStatus(CResRef(cMovieResRef));

    m_movie = cMovieResRef;

    if (m_movie == CInfinity::DAWN_MOVIE
        || m_movie == CInfinity::DUSK_MOVIE
        || m_movie == "DEATH1") {
        g_pBaldurChitin->m_pEngineProjector->field_145 = 1;
    }

    if (m_movie == CInfinity::DAWN_MOVIE) {
        pWorld->m_bSetDayOnActivate = TRUE;
    } else if (m_movie == CInfinity::DUSK_MOVIE) {
        pWorld->m_bSetNightOnActivate = TRUE;
    } else if (m_movie == "DEATH1") {
        g_pBaldurChitin->GetActiveEngine()->SelectEngine(pWorld);
        pWorld->m_bGameOverPanel = TRUE;
    }

    g_pBaldurChitin->GetObjectCursor()->m_bVisible = FALSE;

    g_pBaldurChitin->m_pEngineProjector->PlayMovie(m_movie);

    m_movie = "";
}

// 0x6933F0
void CScreenWorld::SetPendingMapWorld(PLAYER_ID idController, SHORT facingDirection)
{
    m_bPendingMapWorld = TRUE;
    m_idPendingMapWorldController = idController;
    m_nPendingMapWorldDirection = facingDirection;
}

// 0x693410
void CScreenWorld::StartMapWorldMultiplayerHost(PLAYER_ID idController, SHORT facingDirection)
{
    m_idPendingMapWorldController = idController;
    m_nPendingMapWorldDirection = facingDirection;

    g_pBaldurChitin->GetBaldurMessage()->SendMapWorldAnnounceStatus(1, idController, facingDirection);

    CScreenWorldMap* pWorldMap = g_pBaldurChitin->m_pEngineWorldMap;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 8748
    UTIL_ASSERT(pWorldMap != NULL);

    pWorldMap->StartWorldMap(1, facingDirection, idController == g_pChitin->cNetwork.m_idLocalPlayer);

    g_pBaldurChitin->GetActiveEngine()->SelectEngine(pWorldMap);
}

// 0x6934A0
void CScreenWorld::SetPendingReformParty()
{
    m_bPendingReformParty = TRUE;
}

// 0x6934B0
void CScreenWorld::StartReformPartyMultiplayerHost()
{
    g_pBaldurChitin->GetBaldurMessage()->SendReformPartyAnnounceStatus();

    m_bPausedBeforePickParty = m_bPaused;

    g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
}

// 0x6934F0
void CScreenWorld::SetPendingRest(INT nHP, BOOLEAN bRenting, BOOLEAN bMovie)
{
    m_bRestPending = TRUE;
    m_nRestHP = nHP;
    m_bRestRenting = bRenting;
    m_bRestMovie = bMovie;
}

// 0x693520
void CScreenWorld::StartRestMultiplayerHost(INT nHP, BOOLEAN bRenting, BOOLEAN bMovie)
{
    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
        BOOL bListenToJoin = pGame->GetMultiplayerSettings()->GetListenToJoinOption();
        pGame->GetMultiplayerSettings()->SetListenToJoinOption(FALSE, TRUE);
        g_pBaldurChitin->m_pEngineWorld->m_bEndMajorEventListenToJoin = bListenToJoin;
        g_pBaldurChitin->m_pEngineWorld->m_bEndMajorEventPauseStatus = g_pBaldurChitin->m_pEngineWorld->m_bPaused;
    }

    for (SHORT nPortrait = 0; nPortrait < g_pBaldurChitin->GetObjectGame()->GetNumCharacters(); nPortrait++) {
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait);

        CMessage101* pMessage = new CMessage101(FALSE,
            nCharacterId,
            nCharacterId,
            TRUE);

        g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
    }

    CInfGame::m_bHealPartyOnRest = bMovie;
    g_pBaldurChitin->GetObjectGame()->RestPartyPrivate(nHP, bRenting);
    CInfGame::m_bHealPartyOnRest = FALSE;

    m_bRestMovie = FALSE;

    if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        BOOL bListenToJoin = g_pBaldurChitin->m_pEngineWorld->m_bEndMajorEventPauseStatus;
        g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetListenToJoinOption(bListenToJoin, TRUE);
    }
}

// 0x693680
void CScreenWorld::CheckEndOfHardPause()
{
    if (g_pBaldurChitin->GetBaldurMessage()->NonBlockingWaitForSignal(CBaldurMessage::SIGNAL_SERVER, CBaldurMessage::SIGNAL_END_MAJOR_EVENT) == TRUE) {
        m_bHardPaused = FALSE;

        if (!m_bEndMajorEventPauseStatus
            && g_pBaldurChitin->m_pEngineWorld->m_bPaused == TRUE) {
            TogglePauseGame(0, 1, g_pBaldurChitin->cNetwork.m_idLocalPlayer);
        }

        g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetListenToJoinOption(m_bEndMajorEventListenToJoin, TRUE);
    }
}

// NOTE: Inlined.
void CScreenWorld::CheckEndOfMultiplayerSynch()
{
    if (g_pBaldurChitin->GetBaldurMessage()->NonBlockingWaitForSignal(CBaldurMessage::SIGNAL_SERVER, CBaldurMessage::SIGNAL_MPSYNCH) == TRUE) {
        g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSynchServerFinished = TRUE;
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSynchClientPending) {
            g_pBaldurChitin->GetBaldurMessage()->MultiplayerSynchReply();
        }
    }
}

// 0x693860
void CScreenWorld::CancelEngine()
{
    switch (field_EA4) {
    case -1:
    case 0:
    case 7:
        break;
    case 6:
        StopCommand();
        field_EA4 = -1;
        break;
    case 8:
        StopContainer();
        field_EA4 = -1;
        break;
    case 15:
    case 17:
        StopDeath();
        field_EA4 = -1;
        break;
    case 19:
    case 21:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 9124
        UTIL_ASSERT(FALSE);
    }
}

// 0x693910
void CScreenWorld::DeleteAreaMultiplayer()
{
    // TODO: Incomplete.
}

// 0x693C60
void CScreenWorld::DeleteArea(CGameArea* pArea)
{
    // TODO: Incomplete.
}

// 0x694210
void CScreenWorld::CopyChatEditBox(CUIPanel* pFrom, CUIPanel* pTo)
{
    DWORD dwFromEditId = -1;
    if (pFrom != NULL) {
        switch (pFrom->m_nID) {
        case 19:
        case 21:
            dwFromEditId = 5;
            break;
        case 22:
            dwFromEditId = 3;
            break;
        }
    }

    DWORD dwToEditId = -1;
    if (pTo != NULL) {
        switch (pTo->m_nID) {
        case 19:
        case 21:
            dwToEditId = 5;
            break;
        case 22:
            dwToEditId = 3;
            break;
        }
    }

    CString sText;
    CUIControlEdit* pToEdit = NULL;
    CUIControlEdit* pFromEdit = NULL;

    if (dwToEditId != -1) {
        pToEdit = static_cast<CUIControlEdit*>(pTo->GetControl(dwToEditId));
    }

    if (dwFromEditId != -1) {
        pFromEdit = static_cast<CUIControlEdit*>(pFrom->GetControl(dwFromEditId));
    }

    if (pToEdit != NULL) {
        if (pFromEdit != NULL) {
            sText = pFromEdit->GetText();
            pToEdit->SetText(sText);

            if (m_cUIManager.m_pFocusedControl == pFromEdit) {
                m_cUIManager.SetCapture(pToEdit, CUIManager::KEYBOARD);
            }
        } else {
            pToEdit->SetText(CString(""));
        }
    }
}

// 0x694350
void CScreenWorld::GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture)
{
    CUIPanel* pPanel = GetManager()->GetPanel(GetPanel_22_0());

    DWORD dwEditId = -1;
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 19:
        case 21:
            dwEditId = 5;
            break;
        case 22:
            dwEditId = 3;
            break;
        }
    }

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(dwEditId));
    if (pEdit != NULL) {
        sChatText = pEdit->GetText();
        bInputCapture = m_cUIManager.m_pFocusedControl == pEdit;
    } else {
        sChatText = "";
        bInputCapture = FALSE;
    }
}

// 0x694460
void CScreenWorld::SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture)
{
    CUIPanel* pPanel = GetManager()->GetPanel(GetPanel_22_0());

    DWORD dwEditId = -1;
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 19:
        case 21:
            dwEditId = 5;
            break;
        case 22:
            dwEditId = 3;
            break;
        }
    }

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(dwEditId));
    if (pEdit != NULL) {
        pEdit->SetText(sChatText);

        if (bInputCapture) {
            m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
        }
    }
}

// 0x694620
void CScreenWorld::LeaveAreaLuaPanic(CPoint ptLocation, SHORT nDirection, CString sAreaName, CString sParchment)
{
    // TODO: Incomplete.
}

// 0x694AE0
void CScreenWorld::UpdatePartyGoldStatus()
{
    CUIPanel* pPanel;

    switch (field_EA4) {
    case 7:
    case 19:
    case 21:
        pPanel = m_cUIManager.GetPanel(field_EA4);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 9851
        UTIL_ASSERT(pPanel != NULL);

        UpdateLabel(pPanel,
            0x10000009,
            "%d",
            g_pBaldurChitin->GetObjectGame()->m_nPartyGold);
        break;
    case 8:
        pPanel = m_cUIManager.GetPanel(field_EA4);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 9841
        UTIL_ASSERT(pPanel != NULL);

        UpdateLabel(pPanel,
            0x10000036,
            "%d",
            g_pBaldurChitin->GetObjectGame()->m_nPartyGold);
        break;
    }
}

// 0x694BD0
void CScreenWorld::SetDialogTokens(CGameSprite* pCharacter)
{
    STR_RES strRes;

    CTlkTable& tlk = g_pBaldurChitin->GetTlkTable();

    tlk.SetToken(CInfGame::TOKEN_GABBER, pCharacter->GetName());

    CGameSprite* pSprite;
    BYTE rc;

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[0],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER1, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[0],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[1],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER2, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[1],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[2],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER3, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[2],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[3],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER4, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[3],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[4],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER5, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[4],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    do {
        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->m_characters[5],
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        tlk.SetToken(CInfGame::TOKEN_PLAYER6, pSprite->GetName());

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->m_characters[5],
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    STRREF strRace;
    switch (pCharacter->GetAIType().m_nRace) {
    case CAIOBJECTTYPE_R_HUMAN:
        strRace = 7193;
        break;
    case CAIOBJECTTYPE_R_ELF:
        strRace = 7194;
        break;
    case CAIOBJECTTYPE_R_HALF_ELF:
        strRace = 7197;
        break;
    case CAIOBJECTTYPE_R_DWARF:
        strRace = 7182;
        break;
    case CAIOBJECTTYPE_R_HALFLING:
        strRace = 7195;
        break;
    case CAIOBJECTTYPE_R_GNOME:
        strRace = 7196;
        break;
    case CAIOBJECTTYPE_R_HALF_ORC:
        strRace = 22;
        break;
    default:
        strRace = -1;
        break;
    }

    tlk.Fetch(strRace, strRes);
    tlk.SetToken(CInfGame::TOKEN_GABBER_RACE, strRes.szText);

    if (pCharacter->GetAIType().m_nGender == CAIObjectType::SEX_FEMALE) {
        tlk.field_58 = byte_8BA28C;

        tlk.Fetch(27475, strRes); // "ma'am"
        tlk.SetToken(CInfGame::TOKEN_GABBER_SIRMAAM, strRes.szText);

        tlk.Fetch(27476, strRes); // "girl"
        tlk.SetToken(CInfGame::TOKEN_GABBER_GIRLBOY, strRes.szText);

        tlk.Fetch(27479, strRes); // "sister"
        tlk.SetToken(CInfGame::TOKEN_GABBER_BROTHERSISTER, strRes.szText);

        tlk.Fetch(27480, strRes); // "lady"
        tlk.SetToken(CInfGame::TOKEN_GABBER_LADYLORD, strRes.szText);

        tlk.Fetch(27483, strRes); // "female"
        tlk.SetToken(CInfGame::TOKEN_GABBER_MALEFEMALE, strRes.szText);

        tlk.Fetch(27485, strRes); // "she"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HESHE, strRes.szText);

        tlk.Fetch(27487, strRes); // "her"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HISHER, strRes.szText);

        tlk.Fetch(strRace, strRes);
        tlk.SetToken(CInfGame::TOKEN_GABBER_RACE, strRes.szText);

        tlk.Fetch(27487, strRes); // "her"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HIMHER, strRes.szText);

        tlk.Fetch(27490, strRes); // "woman"
        tlk.SetToken(CInfGame::TOKEN_GABBER_MANWOMAN, strRes.szText);
    } else {
        tlk.field_58 = byte_8FB954;

        tlk.Fetch(27473, strRes); // "sir"
        tlk.SetToken(CInfGame::TOKEN_GABBER_SIRMAAM, strRes.szText);

        tlk.Fetch(27477, strRes); // "boy"
        tlk.SetToken(CInfGame::TOKEN_GABBER_GIRLBOY, strRes.szText);

        tlk.Fetch(27478, strRes); // "brother"
        tlk.SetToken(CInfGame::TOKEN_GABBER_BROTHERSISTER, strRes.szText);

        tlk.Fetch(27481, strRes); // "lord"
        tlk.SetToken(CInfGame::TOKEN_GABBER_LADYLORD, strRes.szText);

        tlk.Fetch(27482, strRes); // "male"
        tlk.SetToken(CInfGame::TOKEN_GABBER_MALEFEMALE, strRes.szText);

        tlk.Fetch(27484, strRes); // "he"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HESHE, strRes.szText);

        tlk.Fetch(27486, strRes); // "his"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HISHER, strRes.szText);

        tlk.Fetch(27488, strRes); // "him"
        tlk.SetToken(CInfGame::TOKEN_GABBER_HIMHER, strRes.szText);

        tlk.Fetch(27489, strRes); // "man"
        tlk.SetToken(CInfGame::TOKEN_GABBER_MANWOMAN, strRes.szText);
    }
}

// 0x695570
void CScreenWorld::sub_695570(BOOL bActive, BOOL bInvalidate)
{
    CUIPanel* pActionPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10118
    UTIL_ASSERT(pActionPanel != NULL);

    CUIPanel* pCommandPanel = m_cUIManager.GetPanel(GetPanel_22_0());

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10120
    UTIL_ASSERT(pCommandPanel != NULL);

    if (field_11F0) {
        pActionPanel->SetActive(bActive);

        if (bInvalidate) {
            pActionPanel->InvalidateRect(NULL);
        }
    }

    if (field_11F4) {
        pCommandPanel->SetActive(bActive);

        if (bInvalidate) {
            pCommandPanel->InvalidateRect(NULL);
        }
    }
}

// 0x695650
void CScreenWorld::sub_695650(BOOL bEnable)
{
    CUIPanel* pActionPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10166
    UTIL_ASSERT(pActionPanel != NULL);

    CUIPanel* pCommandPanel = m_cUIManager.GetPanel(GetPanel_22_0());

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10168
    UTIL_ASSERT(pCommandPanel != NULL);

    pActionPanel->SetEnabled(bEnable);
    pCommandPanel->SetEnabled(bEnable);
}

// 0x6984F0
void CScreenWorld::OnRestButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12373
    UTIL_ASSERT(pGame != NULL);

    STRREF strError;
    if (pGame->CanRestParty(strError, 0, 0, 0)) {
        CInfGame::m_bHealPartyOnRest = GetPrivateProfileIntA("Game Options",
            "Heal Party on Rest",
            0,
            g_pBaldurChitin->GetIniFileName());
        pGame->RestParty(1, 0);
        CInfGame::m_bHealPartyOnRest = FALSE;
    } else {
        STR_RES strRes;
        g_pBaldurChitin->GetTlkTable().Fetch(strError, strRes);
        DisplayText(CString(""),
            strRes.szText,
            0,
            RGB(63, 255, 12),
            -1,
            FALSE);
    }

    renderLock.Unlock();
}

// 0x6986A0
void CScreenWorld::EnableKeyRepeat()
{
    m_pVirtualKeys[49].SetRepeat(1, 1);
    m_pVirtualKeys[50].SetRepeat(1, 1);
    m_pVirtualKeys[51].SetRepeat(1, 1);
    m_pVirtualKeys[52].SetRepeat(1, 1);
    m_pVirtualKeys[53].SetRepeat(1, 1);
    m_pVirtualKeys[54].SetRepeat(1, 1);
    m_pVirtualKeys[55].SetRepeat(1, 1);
    m_pVirtualKeys[56].SetRepeat(1, 1);
    m_pVirtualKeys[57].SetRepeat(1, 1);
}

// 0x698730
void CScreenWorld::DisableKeyRepeat()
{
    m_pVirtualKeys[49].SetRepeat(0, 0);
    m_pVirtualKeys[50].SetRepeat(0, 0);
    m_pVirtualKeys[51].SetRepeat(0, 0);
    m_pVirtualKeys[52].SetRepeat(0, 0);
    m_pVirtualKeys[53].SetRepeat(0, 0);
    m_pVirtualKeys[54].SetRepeat(0, 0);
    m_pVirtualKeys[55].SetRepeat(0, 0);
    m_pVirtualKeys[56].SetRepeat(0, 0);
    m_pVirtualKeys[57].SetRepeat(0, 0);
}

// NOTE: Inlined.
void CScreenWorld::CheckPanelInputMode(DWORD dwPanelId, DWORD dwinputModeMask)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 2820
    UTIL_ASSERT(pPanel != NULL);

    if (pPanel->m_bActive || pPanel->m_bInactiveRender) {
        pPanel->SetEnabled((g_pBaldurChitin->GetObjectGame()->field_43E2 & dwinputModeMask) != 0);
    }
}

// NOTE: Inlined.
INT CScreenWorld::GetNumContainerRows(LONG nContainer)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 6075
    UTIL_ASSERT(pGame != NULL);

    return (pGame->GetNumGroundSlots(nContainer) + 4) / 5 + 2;
}

// NOTE: Inlined.
INT CScreenWorld::GetNumGroupRows()
{
    return (CScreenInventory::PERSONAL_INVENTORY_SIZE + 1) / 2;
}

// -----------------------------------------------------------------------------

// 0x6956F0
CUIControlButtonWorldContainerSlot::CUIControlButtonWorldContainerSlot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x695740
CUIControlButtonWorldContainerSlot::~CUIControlButtonWorldContainerSlot()
{
}

// 0x6957E0
void CUIControlButtonWorldContainerSlot::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x696140
BOOL CUIControlButtonWorldContainerSlot::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x6967A0
CUIControlButtonDialog::CUIControlButtonDialog(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x6967F0
CUIControlButtonDialog::~CUIControlButtonDialog()
{
}

// 0x696890
void CUIControlButtonDialog::OnLButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10842
    UTIL_ASSERT(pWorld != NULL);

    if (GetTickCount() > pWorld->field_11BA + 600) {
        pWorld->field_1150 = 1;
        if (!pWorld->field_10B4) {
            pWorld->m_internalLoadedDialog.m_responseMarker = pWorld->field_10B2;
        }
        pWorld->field_11BA = GetTickCount();
    }

    SetActive(FALSE);
    m_pPanel->InvalidateRect(NULL);
}

// -----------------------------------------------------------------------------

// 0x696930
CUIControlScrollBarWorldContainer::CUIControlScrollBarWorldContainer(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
    // TODO: Incomplete.
}

// 0x632C00
CUIControlScrollBarWorldContainer::~CUIControlScrollBarWorldContainer()
{
}

// 0x696950
void CUIControlScrollBarWorldContainer::OnPageUp(DWORD nLines)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10907
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10909
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10912
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    INT nNewTopContainerRow;
    INT nNewTopGroupRow;

    // FIXME: What for?
    INT nStep = abs(static_cast<INT>(nLines));

    switch (m_nID) {
    case 52:
        // NOTE: Uninline.
        // NOTE: Unused.
        pWorld->GetNumContainerRows(nContainer);

        nNewTopContainerRow = max(pWorld->m_nTopGroupRow - (nStep != 0 ? nStep : 2), 0);

        if (pWorld->m_nTopContainerRow != nNewTopContainerRow) {
            pWorld->m_nTopContainerRow = nNewTopContainerRow;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    case 53:
        nNewTopGroupRow = max(pWorld->m_nTopGroupRow - (nStep != 0 ? nStep : 2), 0);
        if (pWorld->m_nTopGroupRow != nNewTopGroupRow) {
            pWorld->m_nTopGroupRow = nNewTopGroupRow;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 10945
        UTIL_ASSERT(FALSE);
    }
}

// 0x696B70
void CUIControlScrollBarWorldContainer::OnPageDown(DWORD nLines)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10977
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10979
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 10982
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    INT nNumContainerRows;
    INT nNewTopContainerRow;
    INT nNumGroupRows;
    INT nNewTopGroupRow;

    // FIXME: What for?
    INT nStep = abs(static_cast<INT>(nLines));

    switch (m_nID) {
    case 52:
        // NOTE: Uninline.
        nNumContainerRows = pWorld->GetNumContainerRows(nContainer);
        nNewTopContainerRow = min(nNumContainerRows,
            pWorld->m_nTopContainerRow + (nStep != 0 ? nStep : 2));

        if (pWorld->m_nTopContainerRow != nNewTopContainerRow) {
            pWorld->m_nTopContainerRow = nNewTopContainerRow;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    case 53:
        // NOTE: Uninline.
        nNumGroupRows = pWorld->GetNumGroupRows() - 2;
        nNewTopGroupRow = min(nNumGroupRows,
            pWorld->m_nTopGroupRow + (nStep != 0 ? nStep : 2));

        if (pWorld->m_nTopGroupRow != nNewTopGroupRow) {
            pWorld->m_nTopGroupRow = nNewTopGroupRow;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11015
        UTIL_ASSERT(FALSE);
    }
}

// 0x696DC0
void CUIControlScrollBarWorldContainer::OnScrollUp()
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11046
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11048
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11051
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    switch (m_nID) {
    case 52:
        if (pWorld->m_nTopContainerRow > 0) {
            pWorld->m_nTopContainerRow--;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    case 53:
        if (pWorld->m_nTopGroupRow > 0) {
            pWorld->m_nTopGroupRow -= 1;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11080
        UTIL_ASSERT(FALSE);
    }
}

// 0x696F80
void CUIControlScrollBarWorldContainer::OnScrollDown()
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11111
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11113
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11116
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    switch (m_nID) {
    case 52:
        // NOTE: Uninline.
        if (pWorld->m_nTopContainerRow < pWorld->GetNumContainerRows(nContainer)) {
            pWorld->m_nTopContainerRow++;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    case 53:
        // NOTE: Uninline.
        if (pWorld->m_nTopGroupRow < pWorld->GetNumGroupRows() - 2) {
            pWorld->m_nTopGroupRow++;

            // NOTE: Uninline.
            InvalidateSlots();

            UpdateScrollBar();
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11311
        UTIL_ASSERT(FALSE);
    }
}

// 0x697170
void CUIControlScrollBarWorldContainer::OnScroll()
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11177
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11179
    UTIL_ASSERT(pGame != NULL);

    LONG nContainer = pGame->m_iContainer;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 1182
    UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

    switch (m_nID) {
    case 52:
        // NOTE: Uninline.
        pWorld->m_nTopContainerRow = pWorld->GetNumContainerRows(nContainer) * field_144 / field_142;

        // NOTE: Uninline.
        InvalidateSlots();

        UpdateScrollBar();
        break;
    case 53:
        // NOTE: Uninline.
        pWorld->m_nTopGroupRow = (pWorld->GetNumGroupRows() - 2) * field_144 / field_142;

        // NOTE: Uninline.
        InvalidateSlots();

        UpdateScrollBar();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11311
        UTIL_ASSERT(FALSE);
    }
}

// 0x697380
void CUIControlScrollBarWorldContainer::UpdateScrollBar()
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11283
    UTIL_ASSERT(pWorld != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11285
    UTIL_ASSERT(pGame != NULL);

    switch (m_nID) {
    case 52:
        if (1) {
            LONG nContainer = pGame->m_iContainer;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
            // __LINE__: 11296
            UTIL_ASSERT(nContainer != CGameObjectArray::INVALID_INDEX);

            // NOTE: Uninline.
            AdjustScrollBar(pWorld->m_nTopContainerRow,
                pWorld->GetNumContainerRows(nContainer),
                2);
        }
        break;
    case 53:
        // NOTE: Uninline.
        AdjustScrollBar(pWorld->m_nTopGroupRow,
            pWorld->GetNumGroupRows(),
            2);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11311
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Inlined.
void CUIControlScrollBarWorldContainer::InvalidateSlots()
{
    DWORD nFirstID;
    DWORD nLastID;

    switch (m_nID) {
    case 52:
        nFirstID = 0;
        nLastID = 9;
        break;
    case 53:
        nFirstID = 10;
        nLastID = 13;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
        // __LINE__: 11245
        UTIL_ASSERT(FALSE);
    }

    for (DWORD nID = nFirstID; nID <= nLastID; nID++) {
        CUIControlBase* pControl = m_pPanel->GetControl(nID);
        pControl->InvalidateRect();
    }
}

// -----------------------------------------------------------------------------

// 0x6974B0
CUIControlButtonWorldContainerIcon::CUIControlButtonWorldContainerIcon(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    field_662 = 0;
}

// 0x697540
CUIControlButtonWorldContainerIcon::~CUIControlButtonWorldContainerIcon()
{
}

// 0x6975E0
BOOL CUIControlButtonWorldContainerIcon::Render(BOOL bForce)
{
    CVidCell vcIcon;

    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    CVidMode* pVidMode = g_pBaldurChitin->GetCurrentVideoMode();

    if (m_resRef == "") {
        return FALSE;
    }

    // NOTE: Uninline.
    vcIcon.SetResRef(m_resRef, m_pPanel->m_pManager->m_bDoubleSize, TRUE, TRUE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11411
    UTIL_ASSERT(vcIcon.GetRes() != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11412
    UTIL_ASSERT(pVidMode != NULL);

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    CSize size;
    vcIcon.GetCurrentFrameSize(size, FALSE);

    CRect rFrame(pt, size);

    CRect rClip;
    rClip.IntersectRect(rFrame, m_rDirty);

    vcIcon.Render(0, pt.x, pt.y, rClip, NULL, 0, 0, -1);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x6977E0
CUIControlButtonWorldContainerClose::CUIControlButtonWorldContainerClose(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x697830
CUIControlButtonWorldContainerClose::~CUIControlButtonWorldContainerClose()
{
}

// 0x6978D0
void CUIControlButtonWorldContainerClose::OnLButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11471
    UTIL_ASSERT(pWorld != NULL);

    CSingleLock renderLock(&(pWorld->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pWorld->StopContainer();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x697970
CUIControlButtonClock::CUIControlButtonClock(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    // NOTE: Uninline.
    m_vcGear.SetResRef(CResRef("CGEAR"), g_pBaldurChitin->field_4A28, TRUE, TRUE);

    SetNeedAsyncUpdate();

    m_bSelected = TRUE;
}

// 0x697C20
CUIControlButtonClock::~CUIControlButtonClock()
{
}

// 0x697D80
void CUIControlButtonClock::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_bActive) {
        if (bInside
            && !m_bToolTipActive
            && m_pPanel->m_pManager->field_1C >= g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nTooltips) {
            ActivateToolTip();
            m_bToolTipActive = TRUE;
        }

        CTimerWorld* pTimerWorld = g_pBaldurChitin->GetObjectGame()->GetWorldTimer();

        BYTE nSequenceLength = m_vcGear.GetSequenceLength(m_vcGear.m_nCurrentSequence, FALSE);
        m_vcGear.FrameSet(pTimerWorld->m_gameTime % nSequenceLength);

        InvalidateRect();

        m_bSelected = pTimerWorld->m_active;
    }
}

// 0x697CE0
void CUIControlButtonClock::ActivateToolTip()
{
    CString sTime;

    CTimerWorld::GetCurrentTimeString(g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime,
        16410,
        sTime);

    g_pBaldurChitin->GetObjectCursor()->SetToolTip(-1, this, sTime);
}

// NOTE: Always returns `TRUE` which is a bit unusual for `Render` function.
//
// 0x697E40
BOOL CUIControlButtonClock::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return TRUE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return TRUE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock lock(&(m_pPanel->m_pManager->field_56), FALSE);
        lock.Lock(INFINITE);
        m_nRenderCount--;
        lock.Unlock();
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    CRect rControlFrame(pt, m_size);

    CRect rClip;
    rClip.IntersectRect(rControlFrame, m_rDirty);

    m_vcGear.Render(0, pt.x, pt.y, rClip, NULL, 0, 0, -1);

    return TRUE;
}

// 0x697F90
void CUIControlButtonClock::OnLButtonClick(CPoint)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 11721
    UTIL_ASSERT(pWorld != NULL);

    if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineWorld
        || g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineInventory
        || g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineMap) {
        pWorld->TogglePauseGame(1, 1, 0);
    }
}

// -----------------------------------------------------------------------------

// 0x697FF0
CUIControlButtonWorldDeathLoad::CUIControlButtonWorldDeathLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CBaldurEngine::FetchString(15590)); // "Load"
}

// 0x6980A0
CUIControlButtonWorldDeathLoad::~CUIControlButtonWorldDeathLoad()
{
}

// 0x698140
void CUIControlButtonWorldDeathLoad::OnLButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12190
    UTIL_ASSERT(pWorld != NULL);

    pWorld->StopDeath();

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12195
    UTIL_ASSERT(pGame != NULL);

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12208
    UTIL_ASSERT(pLoad != NULL);

    pLoad->StartLoad(g_pChitin->cNetwork.GetSessionOpen() ? 3 : 2);
    pWorld->SelectEngine(pLoad);

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && !pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus) {

        for (BYTE nSlot = 0; nSlot < CINFGAME_MAXCHARACTERS; nSlot++) {
            // NOTE: Uninline.
            LONG nCharacterId = pGame->GetFixedOrderCharacterId(nSlot);

            if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
                g_pBaldurChitin->GetBaldurMessage()->ObjectControlRequest(nCharacterId);
            }
        }

        g_pBaldurChitin->GetBaldurMessage()->ObjectControl();
        pGame->GetMultiplayerSettings()->SetArbitrationLockAllowInput(FALSE);
        pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(TRUE, 1);
    }

    pGame->DestroyGame(1, 0);
}

// -----------------------------------------------------------------------------

// 0x6982C0
CUIControlButtonWorldDeathQuit::CUIControlButtonWorldDeathQuit(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CBaldurEngine::FetchString(15417)); // "Quit"
}

// 0x698370
CUIControlButtonWorldDeathQuit::~CUIControlButtonWorldDeathQuit()
{
}

// 0x698410
void CUIControlButtonWorldDeathQuit::OnLButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12285
    UTIL_ASSERT(pWorld != NULL);

    pWorld->StopDeath();

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenWorld.cpp
    // __LINE__: 12289
    UTIL_ASSERT(pGame != NULL);

    pWorld->SelectEngine(g_pBaldurChitin->m_pEngineConnection);

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
        }

        g_pChitin->cNetwork.CloseSession(TRUE);
        g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown = FALSE;
    }

    pGame->DestroyGame(1, 0);
}

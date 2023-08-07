#include "CScreenLoad.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenConnection.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

#define GAME_SLOTS 5

// 0x63E4B0
CScreenLoadGameSlot::CScreenLoadGameSlot()
{
    m_sFileName = "";
    m_sSlotName = "";
    m_cResScreenShot.m_pData = NULL;
    m_cBmpResPortrait0.m_pData = NULL;
    m_cBmpResPortrait1.m_pData = NULL;
    m_cBmpResPortrait2.m_pData = NULL;
    m_cBmpResPortrait3.m_pData = NULL;
    m_cBmpResPortrait4.m_pData = NULL;
    m_cBmpResPortrait5.m_pData = NULL;
    field_2FC = "";
    field_304 = "";
    field_308 = 0;
    field_30C = 0;
    field_310 = "";
    field_314 = "";
}

// 0x63C850
CScreenLoadGameSlot::~CScreenLoadGameSlot()
{
}

// 0x63AF80
CScreenLoad::CScreenLoad()
{
    m_nEngineState = 0;
    field_1E6 = 0;
    m_nNumErrorButtons = 0;
    field_21A = 0;

    SetVideoMode(0);

    m_pVirtualKeys[0] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[2] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[3] = CKeyInfo(VK_ESCAPE, -1, 0);
    m_pVirtualKeys[4] = CKeyInfo(VK_TAB, -1, 0);
    m_pVirtualKeys[5] = CKeyInfo(VK_PRIOR, 0, 0);
    m_pVirtualKeys[6] = CKeyInfo(VK_NEXT, 0, 0);
    m_pVirtualKeys[7] = CKeyInfo(VK_END, -1, 0);
    m_pVirtualKeys[8] = CKeyInfo(VK_HOME, -1, 0);
    m_pVirtualKeys[9] = CKeyInfo(VK_UP, 0, 0);
    m_pVirtualKeys[10] = CKeyInfo(VK_DOWN, 0, 0);
    m_pVirtualKeys[11] = CKeyInfo(VK_NUMPAD0, -1, 0);
    m_pVirtualKeys[12] = CKeyInfo(VK_NUMPAD1, -1, 0);
    m_pVirtualKeys[13] = CKeyInfo(VK_NUMPAD2, 0, 0);
    m_pVirtualKeys[14] = CKeyInfo(VK_NUMPAD3, 0, 0);
    m_pVirtualKeys[15] = CKeyInfo(VK_NUMPAD4, 0, 0);
    m_pVirtualKeys[16] = CKeyInfo(VK_NUMPAD5, -1, 0);
    m_pVirtualKeys[17] = CKeyInfo(VK_NUMPAD6, 0, 0);
    m_pVirtualKeys[18] = CKeyInfo(VK_NUMPAD7, -1, 0);
    m_pVirtualKeys[19] = CKeyInfo(VK_NUMPAD8, 0, 0);
    m_pVirtualKeys[20] = CKeyInfo(VK_NUMPAD9, 0, 0);

    m_bCtrlKeyDown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_nTopGameSlot = 0;
    m_nNumGameSlots = 0;
    field_C1E = 0;
}

// 0x49FC40
BOOL CScreenLoad::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenLoad::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenLoad::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenLoad::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenLoad::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenLoad::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenLoad::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenLoad::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenLoad::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenLoad::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenLoad::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x63B310
void CScreenLoad::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x63B320
void CScreenLoad::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x63B330
SHORT CScreenLoad::GetNumVirtualKeys()
{
    return CSCREENLOAD_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenLoad::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x63B340
BYTE* CScreenLoad::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x63B370
CScreenLoad::~CScreenLoad()
{
    FreeGameSlots();
}

// 0x63B410
void CScreenLoad::EngineActivated()
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

    UpdateMainPanel();
    UpdateCursorShape(0);
    m_cUIManager.InvalidateRect(NULL);

    switch (m_nEngineState) {
    case 2:
    case 3:
        g_pBaldurChitin->cSoundMixer.StartSong(1, 0);
        break;
    }
}

// 0x63B500
void CScreenLoad::EngineDeactivated()
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

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x5D72C0
void CScreenLoad::EngineDestroyed()
{
    m_cUIManager.fUninit();
}

// 0x63B590
void CScreenLoad::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUILOAD"), g_pBaldurChitin->field_4A28);

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

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    for (INT nSlot = 0; nSlot < GAME_SLOTS; nSlot++) {
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x10000005 + nSlot));
        pLabel->m_nTextFlags &= ~0x100;
    }
}

// 0x63B6D0
void CScreenLoad::OnKeyDown(SHORT nKeysFlags)
{
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_ESCAPE:
                if (GetTopPopup() != NULL) {
                    OnCancelButtonClick();
                } else {
                    OnMainCancelButtonClick();
                }
                break;
            case VK_RETURN:
                if (GetTopPopup() != NULL) {
                    switch (GetTopPopup()->m_nID) {
                    case 1:
                        OnErrorButtonClick(0);
                        break;
                    case 2:
                        sub_63E440(0);
                        break;
                    }
                }
                break;
            default:
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
}

// 0x63B9B0
void CScreenLoad::TimerAsynchronousUpdate()
{
    if (m_nEngineState == 3 || m_nEngineState == 1) {
        if (g_pChitin->cNetwork.MakePlayersVisible() == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
        }
    }

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
        if (!pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus) {
            pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(TRUE, 0);
        }
    }
}

// 0x63BAA0
void CScreenLoad::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x63BAD0
void CScreenLoad::UpdateMainPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 733
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Unused.
    CString v1;
    CString sTime;

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(23));

    CUIControlScrollBarLoadGames* pScrollBar = static_cast<CUIControlScrollBarLoadGames*>(pPanel->GetControl(23));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 746
    UTIL_ASSERT(pScrollBar != NULL);

    // NOTE: Uninline.
    pScrollBar->UpdateScrollBar();

    for (INT nSlot = 0; nSlot < GAME_SLOTS; nSlot++) {
        CUIControlButton* pButton;
        INT nGameSlot = nSlot + m_nTopGameSlot;

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(55 + nSlot));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 757
        UTIL_ASSERT(pButton != NULL);

        // NOTE: Inlining.

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 823
        UTIL_ASSERT(0 <= nSlot && nSlot < GAME_SLOTS);

        pButton->SetEnabled(nGameSlot < m_nNumGameSlots);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(60 + nSlot));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 763
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(nGameSlot < m_nNumGameSlots);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1 + nSlot));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 769
        UTIL_ASSERT(pButton != NULL);

        pButton->InvalidateRect();

        for (DWORD nPortrait = 0; nPortrait < 6; nPortrait++) {
            pButton = static_cast<CUIControlButton*>(pPanel->GetControl(25 + nSlot * 6 + nPortrait));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
            // __LINE__: 777
            UTIL_ASSERT(pButton != NULL);

            pButton->InvalidateRect();
        }

        if (nGameSlot < m_nNumGameSlots) {
            CTimerWorld::GetCurrentTimeString(m_aGameSlots[nGameSlot]->field_308, 20670, sTime);

            UpdateLabel(pPanel,
                0x10000005 + nSlot,
                "%s",
                m_aGameSlots[nGameSlot]->m_sSlotName);
            UpdateLabel(pPanel,
                0x1000000A + nSlot,
                "%s, %s",
                m_aGameSlots[nGameSlot]->field_310,
                sTime);
            UpdateLabel(pPanel,
                0x1000000F + nSlot,
                "%s",
                m_aGameSlots[nGameSlot]->field_314);
        } else {
            UpdateLabel(pPanel, 0x10000005 + nSlot, "");
            UpdateLabel(pPanel, 0x1000000A + nSlot, "");
            UpdateLabel(pPanel, 0x1000000F + nSlot, "");
        }
    }
}

// 0x63BE80
void CScreenLoad::LoadGame(INT nSlot)
{
    // TODO: Incomplete.
}

// 0x63C3E0
void CScreenLoad::OnDeleteButtonClick(INT nSlot)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 1097
    UTIL_ASSERT(0 <= nSlot && nSlot < GAME_SLOTS);

    if (nSlot + m_nTopGameSlot < m_nNumGameSlots) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1103
        UTIL_ASSERT(pPanel != NULL);

        renderLock.Lock(INFINITE);

        field_1E6 = m_nTopGameSlot + nSlot;
        m_dwErrorTextId = 15305;
        m_strErrorButtonText[0] = 13957;
        m_strErrorButtonText[1] = 13727;
        SummonPopup(1);

        renderLock.Unlock();
    }
}

// 0x63C500
void CScreenLoad::OnMainCancelButtonClick()
{
    switch (m_nEngineState) {
    case 0:
    case 2:
        FreeGameSlots();
        m_aGameSlots.SetSize(0, -1);

        if (m_cUIManager.m_pFocusedControl != NULL) {
            m_cUIManager.KillCapture();
        }

        g_pBaldurChitin->m_pEngineStart->m_nEngineState = 1;
        SelectEngine(g_pBaldurChitin->m_pEngineStart);

        break;
    case 1:
    case 3:
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
            if (pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE) {
                pGame->GetMultiplayerSettings()->SetArbitrationLockAllowInput(TRUE);
                pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(FALSE, 0);
            }
        }

        FreeGameSlots();
        m_aGameSlots.SetSize(0, -1);

        if (m_cUIManager.m_pFocusedControl != NULL) {
            m_cUIManager.KillCapture();
        }

        // NOTE: Repeats code block above.
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
            if (pGame->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE) {
                pGame->GetMultiplayerSettings()->SetArbitrationLockAllowInput(TRUE);
                pGame->GetMultiplayerSettings()->SetArbitrationLockStatus(FALSE, 0);
            }
        }

        g_pChitin->cNetwork.CloseSession(TRUE);

        SelectEngine(g_pBaldurChitin->m_pEngineConnection);

        if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
        }

        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1181
        UTIL_ASSERT(FALSE);
    }
}

// 0x63C6A0
void CScreenLoad::StartLoad(INT nEngineState)
{
    m_nEngineState = nEngineState;
    RefreshGameSlots();
    m_nTopGameSlot = max(m_nNumGameSlots - GAME_SLOTS, 0);
}

// 0x63C6D0
void CScreenLoad::FreeGameSlots()
{
    for (INT nSlot = 0; nSlot < m_nNumGameSlots; nSlot++) {
        if (m_aGameSlots[nSlot]->m_cResScreenShot.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cResScreenShot.m_pData);
            m_aGameSlots[nSlot]->m_cResScreenShot.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait0.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait0.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait0.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait1.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait1.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait1.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait2.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait2.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait2.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait3.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait3.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait3.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait4.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait4.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait4.m_pData = NULL;
        }

        if (m_aGameSlots[nSlot]->m_cBmpResPortrait5.m_pData != 0) {
            free(m_aGameSlots[nSlot]->m_cBmpResPortrait5.m_pData);
            m_aGameSlots[nSlot]->m_cBmpResPortrait5.m_pData = NULL;
        }

        delete m_aGameSlots[nSlot];
    }

    m_nNumGameSlots = 0;
}

// 0x63C940
void CScreenLoad::RefreshGameSlots()
{
    // TODO: Incomplete.
}

// 0x63D460
BOOL CScreenLoad::DrawScreenShot(INT nSlot, const CRect& rArea, const CRect& rClip)
{
    CVidBitmap vbScreenShot(CResRef(""), g_pBaldurChitin->field_4A28);

    INT nGameSlot = nSlot + m_nTopGameSlot;
    if (nGameSlot >= m_nNumGameSlots) {
        return FALSE;
    }

    BOOL bResult;
    if (m_aGameSlots[nGameSlot]->m_cResScreenShot.m_pData != NULL) {
        vbScreenShot.SetRes(&(m_aGameSlots[nGameSlot]->m_cResScreenShot));
        vbScreenShot.pRes->DemandLoadedBitmap();
        bResult = vbScreenShot.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbScreenShot.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1592
        UTIL_ASSERT(bResult);
    } else {
        vbScreenShot.SetResRef(CResRef("ICEWIND2"), TRUE, TRUE);
        vbScreenShot.m_bDoubleSize = g_pBaldurChitin->field_4A28;
        bResult = vbScreenShot.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1599
        UTIL_ASSERT(bResult);
    }

    return TRUE;
}

// 0x63D720
BOOL CScreenLoad::DrawPortrait(USHORT nPortrait, INT nSlot, const CRect& rArea, const CRect& rClip)
{
    CVidBitmap vbPortrait(CResRef(""), g_pBaldurChitin->field_4A28);

    INT nGameSlot = nSlot + m_nTopGameSlot;
    if (nGameSlot >= m_nNumGameSlots) {
        return FALSE;
    }

    BOOL bResult;
    switch (nPortrait) {
    case 0:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait0.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait0));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1646
        UTIL_ASSERT(bResult);

        return TRUE;
    case 1:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait1.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait1));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1658
        UTIL_ASSERT(bResult);

        return TRUE;
    case 2:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait2.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait2));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1670
        UTIL_ASSERT(bResult);

        return TRUE;
    case 3:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait2.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait2));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1682
        UTIL_ASSERT(bResult);

        return TRUE;
    case 4:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait4.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait4));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1694
        UTIL_ASSERT(bResult);

        return TRUE;
    case 5:
        if (m_aGameSlots[nGameSlot]->m_cBmpResPortrait5.m_pData == NULL) {
            return FALSE;
        }

        vbPortrait.SetRes(&(m_aGameSlots[nGameSlot]->m_cBmpResPortrait5));
        vbPortrait.pRes->DemandLoadedBitmap();
        bResult = vbPortrait.RenderDirect(0, rArea.left, rArea.top, rClip, 0, 1);
        vbPortrait.pRes->ReleaseLoadedBitmap();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1706
        UTIL_ASSERT(bResult);

        return TRUE;
    }

    return FALSE;
}

// 0x63DB40
void CScreenLoad::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 1740
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

// 0x63DC10
CUIPanel* CScreenLoad::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenLoad::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
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
void CScreenLoad::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 1822
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Inlined.
void CScreenLoad::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 1849
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 1:
        ResetErrorPanel(pPanel);
        break;
    case 2:
        sub_63E150(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1862
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Uninline.
void CScreenLoad::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 1:
    case 2:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1896
        UTIL_ASSERT(FALSE);
    }
}

// 0x63DC30
void CScreenLoad::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 1976
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        // NOTE: Uninline.
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 1982
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

// 0x63DDF0
void CScreenLoad::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2027
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2044
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

// 0x63DF50
void CScreenLoad::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 1:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2080
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2093
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2102
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2246
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENLOAD_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x63E150
void CScreenLoad::sub_63E150(CUIPanel* pPanel)
{
    m_nNumErrorButtons = 1;

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(24111, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2120
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(10));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2126
    UTIL_ASSERT(pButton != NULL);

    pButton->SetText(FetchString(24116));
}

// 0x63E2C0
void CScreenLoad::OnErrorButtonClick(INT nButton)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_dwErrorTextId) {
    case 15305:
        switch (nButton) {
        case 0:
            DismissPopup();

            // NOTE: Uninline.
            DeleteGame(field_1E6);
            break;
        case 1:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
            // __LINE__: 2176
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
        // __LINE__: 2182
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// 0x63E440
void CScreenLoad::sub_63E440(INT nButton)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();
}

// NOTE: Inlined.
void CScreenLoad::DeleteGame(INT nGameSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2272
    UTIL_ASSERT(0 <= nGameSlot && nGameSlot < m_nNumGameSlots);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2273
    UTIL_ASSERT(m_aGameSlots[nGameSlot]->m_sFileName != "");

    g_pBaldurChitin->GetObjectGame()->DeleteSaveGame(CString(m_aGameSlots[nGameSlot]->m_sFileName));

    RefreshGameSlots();
    UpdateMainPanel();
}

// 0x63E630
void CScreenLoad::OnCancelButtonClick()
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();
}

// 0x63E6A0
void CScreenLoad::CancelEngine()
{
    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }
}

// -----------------------------------------------------------------------------

// 0x63E6C0
CUIControlButtonLoadDelete::CUIControlButtonLoadDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13957, strRes);
    SetText(strRes.szText);
}

// 0x63E7B0
CUIControlButtonLoadDelete::~CUIControlButtonLoadDelete()
{
}

// 0x63E850
void CUIControlButtonLoadDelete::OnLButtonClick(CPoint pt)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2479
    UTIL_ASSERT(pLoad != NULL);

    pLoad->OnDeleteButtonClick(m_nID - 60);
}

// -----------------------------------------------------------------------------

// 0x63E890
CUIControlButtonLoadLoad::CUIControlButtonLoadLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15590, strRes);
    SetText(strRes.szText);
}

// 0x63E980
CUIControlButtonLoadLoad::~CUIControlButtonLoadLoad()
{
}

// 0x63EA20
void CUIControlButtonLoadLoad::OnLButtonClick(CPoint pt)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2535
    UTIL_ASSERT(pLoad != NULL);

    pLoad->LoadGame(m_nID - 55);
}

// -----------------------------------------------------------------------------

// 0x63EA60
CUIControlButtonLoadCancel::CUIControlButtonLoadCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes);
    SetText(strRes.szText);
}

// 0x63EB50
CUIControlButtonLoadCancel::~CUIControlButtonLoadCancel()
{
}

// 0x63EBF0
void CUIControlButtonLoadCancel::OnLButtonClick(CPoint pt)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2591
    UTIL_ASSERT(pLoad != NULL);

    pLoad->OnMainCancelButtonClick();
}

// -----------------------------------------------------------------------------

// 0x63EC30
CUIControlButtonLoadScreenShot::CUIControlButtonLoadScreenShot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x63EC80
CUIControlButtonLoadScreenShot::~CUIControlButtonLoadScreenShot()
{
}

// 0x63ED20
BOOL CUIControlButtonLoadScreenShot::Render(BOOL bForce)
{
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

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2672
    UTIL_ASSERT(pLoad != NULL);

    CRect rControlRect(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

    CRect rClip;
    rClip.IntersectRect(rControlRect, m_rDirty);

    // NOTE: Even though it's a rect, only top left corner is used.
    CRect rArea;
    rArea.left = m_pPanel->m_ptOrigin.x + m_ptOrigin.x;
    rArea.top = m_pPanel->m_ptOrigin.y + m_ptOrigin.y;

    return pLoad->DrawScreenShot(m_nID - 1, rArea, rClip);
}

// 0x63EE90
void CUIControlButtonLoadScreenShot::OnLButtonDoubleClick(CPoint pt)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2699
    UTIL_ASSERT(pLoad != NULL);

    pLoad->LoadGame(m_nID - 1);
}

// -----------------------------------------------------------------------------

// 0x63EED0
CUIControlButtonLoadPortrait::CUIControlButtonLoadPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 1)
{
}

// 0x63EF20
CUIControlButtonLoadPortrait::~CUIControlButtonLoadPortrait()
{
}

// 0x63EFC0
BOOL CUIControlButtonLoadPortrait::Render(BOOL bForce)
{
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

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2782
    UTIL_ASSERT(pLoad != NULL);

    CRect rControlRect(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);

    CRect rClip;
    rClip.IntersectRect(rControlRect, m_rDirty);

    // NOTE: Even though it's a rect, only top left corner is used.
    CRect rArea;
    rArea.left = m_pPanel->m_ptOrigin.x + m_ptOrigin.x;
    rArea.top = m_pPanel->m_ptOrigin.y + m_ptOrigin.y;

    return pLoad->DrawPortrait((m_nID - 25) % 6, (m_nID - 25) / 6, rArea, rClip);
}

// -----------------------------------------------------------------------------

// 0x63F150
CUIControlScrollBarLoadGames::CUIControlScrollBarLoadGames(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarLoadGames::~CUIControlScrollBarLoadGames()
{
}

// NOTE: Inlined.
void CUIControlScrollBarLoadGames::UpdateScrollBar()
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2836
    UTIL_ASSERT(pLoad != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2838
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pLoad->m_nTopGameSlot, pLoad->m_nNumGameSlots, GAME_SLOTS);
}

// 0x63F170
void CUIControlScrollBarLoadGames::OnScrollUp()
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2868
    UTIL_ASSERT(pLoad != NULL);

    INT nNewTopGameSlot = max(pLoad->m_nTopGameSlot - 1, 0);
    if (nNewTopGameSlot != pLoad->m_nTopGameSlot) {
        pLoad->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x63F260
void CUIControlScrollBarLoadGames::OnScrollDown()
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2904
    UTIL_ASSERT(pLoad != NULL);

    INT nNewTopGameSlot = max(min(pLoad->m_nTopGameSlot + 1, pLoad->m_nNumGameSlots - GAME_SLOTS), 0);
    if (nNewTopGameSlot != pLoad->m_nTopGameSlot) {
        pLoad->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x63F360
void CUIControlScrollBarLoadGames::OnPageUp(DWORD nLines)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2940
    UTIL_ASSERT(pLoad != NULL);

    INT nStep = min(nLines, GAME_SLOTS - 1);
    INT nNewTopGameSlot = max(pLoad->m_nTopGameSlot - nStep, 0);
    if (nNewTopGameSlot != pLoad->m_nTopGameSlot) {
        pLoad->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x63F460
void CUIControlScrollBarLoadGames::OnPageDown(DWORD nLines)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 2980
    UTIL_ASSERT(pLoad != NULL);

    INT nStep = nStep = min(nLines, GAME_SLOTS - 1);
    INT nNewTopGameSlot = max(min(pLoad->m_nTopGameSlot + nStep, pLoad->m_nNumGameSlots - GAME_SLOTS), 0);
    if (nNewTopGameSlot != pLoad->m_nTopGameSlot) {
        pLoad->m_nTopGameSlot = nNewTopGameSlot;

        // NOTE: Uninline.
        UpdateMainPanel();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x63F570
void CUIControlScrollBarLoadGames::OnScroll()
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 3020
    UTIL_ASSERT(pLoad != NULL);

    pLoad->m_nTopGameSlot = max(pLoad->m_nNumGameSlots - GAME_SLOTS, 0) * field_144 / field_142;

    // NOTE: Uninline.
    UpdateMainPanel();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// NOTE: Inlined.
void CUIControlScrollBarLoadGames::UpdateMainPanel()
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 3052
    UTIL_ASSERT(pLoad != NULL);

    pLoad->UpdateMainPanel();
}

// -----------------------------------------------------------------------------

// 0x63F670
CUIControlButtonLoadError::CUIControlButtonLoadError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CString(""));
}

// 0x63F720
CUIControlButtonLoadError::~CUIControlButtonLoadError()
{
}

// 0x63F7C0
void CUIControlButtonLoadError::OnLButtonClick(CPoint pt)
{
    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenLoad.cpp
    // __LINE__: 3105
    UTIL_ASSERT(pLoad != NULL);

    CSingleLock renderLock(&(pLoad->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = pLoad->GetTopPopup();
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 1:
            // NOTE: Inlining.
            if (1) {
                CSingleLock renderLock(&(pLoad->m_cUIManager.field_36), FALSE);
                renderLock.Lock(INFINITE);
                pLoad->DismissPopup();
                renderLock.Unlock();
            }
            break;
        default:
            pLoad->OnErrorButtonClick(m_nID - 1);
            break;
        }
    } else {
        pLoad->OnErrorButtonClick(m_nID - 1);
    }

    renderLock.Unlock();
}

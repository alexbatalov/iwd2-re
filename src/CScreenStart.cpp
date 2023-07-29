#include "CScreenStart.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CMultiplayerSettings.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenLoad.h"
#include "CScreenMovies.h"
#include "CUIControlBase.h"
#include "CUIControlScrollBar.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F7D3C
const CString CScreenStart::TOKEN_SERVERVERSION("SERVERVERSION");

// 0x8F7928
const CString CScreenStart::TOKEN_CLIENTVERSION("CLIENTVERSION");

// 0x66F0C0
CScreenStart::CScreenStart()
{
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    field_144 = 1;
    field_13F = 0;
    field_106 = 1;
    m_bExitProgram = FALSE;
    SetVideoMode(0);
    m_bCtrlKeyDown = FALSE;
    m_pVirtualKeys[0] = CKeyInfo(VK_ESCAPE, 0, 0);
    m_pVirtualKeys[1] = CKeyInfo(VK_TAB, -1, 0);
    m_pVirtualKeys[2] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[3] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[4] = CKeyInfo(VK_RETURN, 0, 0);
    m_nEngineState = 0;
    field_17C = 0;
}

// 0x66F2A0
CScreenStart::~CScreenStart()
{
}

// 0x66F230
void CScreenStart::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x66F250
SHORT CScreenStart::GetNumVirtualKeys()
{
    return CSCREENSTART_VIRTUAL_KEYS;
}

// 0x66F260
CKeyInfo* CScreenStart::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x66F270
BYTE* CScreenStart::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x66F320
void CScreenStart::OnKeyDown(SHORT nKeyFlags)
{
    for (SHORT index = 0; index < nKeyFlags; index++) {
        if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[index])) {
            switch (m_pVirtualKeysFlags[index]) {
            case VK_TAB:
                m_cUIManager.ForceToolTip();
                break;
            case VK_RETURN:
                if (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
                    CUIPanel* pPanel = m_lPopupStack.GetTail();
                    switch (pPanel->m_nID) {
                    case 2:
                    case 3:
                        OnErrorButtonClick(0);
                        break;
                    case 4:
                        sub_6702C0();
                        break;
                    }
                }
                break;
            case VK_ESCAPE:
                if (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
                    CUIPanel* pPanel = m_lPopupStack.GetTail();
                    switch (pPanel->m_nID) {
                    case 2:
                        OnErrorButtonClick(0);
                        break;
                    case 3:
                        OnErrorButtonClick(1);
                        break;
                    case 4:
                        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(m_cUIManager.GetPanel(4)->GetControl(1));
                        sub_6702C0();
                        break;
                    }
                } else {
                    if (m_nEngineState != 0) {
                        m_nEngineState = 0;
                        UpdateMainPanel();
                    }
                }
                break;
            case VK_SNAPSHOT:
                g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                break;
            }
        }
    }
}

// 0x66F4B0
void CScreenStart::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x66F4D0
void CScreenStart::TimerSynchronousUpdate()
{
    if (m_bExitProgram) {
        pChitin->ShutDown(-1, NULL, NULL);
        return;
    }

    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x66F510
void CScreenStart::UpdateMainPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    CUIControlButton* pButton;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 852
    UTIL_ASSERT(pPanel != NULL);

    switch (m_nEngineState) {
    case 0:
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
        pButton->SetText(FetchString(15413));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));
        pButton->SetText(FetchString(15414));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));
        pButton->SetText(FetchString(15415));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));
        pButton->SetText(FetchString(15417));
        pButton->SetEnabled(TRUE);

        break;
    case 1:
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
        pButton->SetText(FetchString(13728));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));
        pButton->SetText(FetchString(13728));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));
        pButton->SetText(FetchString(24110));
        pButton->SetEnabled(TRUE);

        break;
    case 2:
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
        pButton->SetText(FetchString(11825));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));
        pButton->SetText(FetchString(20642));
        pButton->SetEnabled(TRUE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));
        pButton->SetText(FetchString(15416));
        pButton->SetEnabled(TRUE);

        if (1) {
            // TODO: Figure out which.
            CUIControlBase* pControl = pPanel->GetControl(3);
            pControl->SetActive(FALSE);
            pControl->SetInactiveRender(FALSE);

            CRect rControlFrame(pControl->m_ptOrigin, pControl->m_size);
            pPanel->InvalidateRect(&rControlFrame);
        }

        break;
    }
}

// 0x66F8F0
void CScreenStart::OnQuitButtonClick()
{
    CSingleLock lock(&m_cUIManager.field_36, TRUE);

    m_nErrorState = 0;
    m_dwErrorTextId = 19532;
    m_strErrorButtonText[0] = 15417;
    m_strErrorButtonText[1] = 13727;
    SummonPopup(3);

    lock.Unlock();
}

// 0x66F990
void CScreenStart::sub_66F990()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1208
    UTIL_ASSERT(pConnection != NULL);

    if (g_pBaldurChitin->m_bIsAutoStarting && g_pBaldurChitin->field_130) {
        if (g_pBaldurChitin->cDimm.cResCache.m_nCacheSize >= 140000000) {
            pConnection->StartConnection(TRUE);
            SelectEngine(pConnection);
        } else {
            g_pBaldurChitin->cNetwork.CloseSession(TRUE);
            m_nErrorState = 2;
            m_dwErrorTextId = 20692;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(2);
        }
    } else {
        if (g_pBaldurChitin->cDimm.cResCache.m_nCacheSize >= 140000000) {
            pConnection->StartConnection(FALSE);
            SelectEngine(pConnection);
        } else {
            m_nErrorState = 2;
            m_dwErrorTextId = 20692;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(2);
        }
    }
}

// 0x66FA90
void CScreenStart::EnableMainPanel(BOOL bEnabled)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1273
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnabled);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 != 0 ? 2 : 1) != 800) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnabled);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnabled);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnabled);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnabled);
    }

    if (bEnabled) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }
}

// 0x66FB60
void CScreenStart::SummonPopup(DWORD nID)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (m_lPopupStack.GetCount() != 0) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 1513
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        SetPopupEnabled(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1519
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);

    // NOTE: Uninline.
    ResetPopupPanel(pPanel->m_nID);

    // NOTE: Likely some inlining, not sure which.
    if (1) {
        CUIPanel* pPopup = m_cUIManager.GetPanel(pPanel->m_nID);
        pPopup->SetActive(TRUE);
        pPopup->SetInactiveRender(TRUE);
        pPopup->InvalidateRect(NULL);
    }

    PlayGUISound(RESREF_SOUND_WINDOWOPEN);

    // NOTE: Uninline.
    SetPopupEnabled(pPanel->m_nID, TRUE);
}

// 0x66FCF0
void CScreenStart::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.GetTail();
    m_lPopupStack.RemoveAt(m_lPopupStack.GetTailPosition());

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1564
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Likely some inlining, not sure which.
    if (1) {
        CUIPanel* pPopup = m_cUIManager.GetPanel(pPanel->m_nID);
        pPopup->SetActive(FALSE);
        pPopup->SetInactiveRender(FALSE);

        CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
        pMainPanel->InvalidateRect(NULL);
    }

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 1581
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Likely some inlining, not sure which.
        if (1) {
            CUIPanel* pPopup = m_cUIManager.GetPanel(pPanel->m_nID);
            pPopup->SetActive(TRUE);
            pPopup->SetInactiveRender(TRUE);
            pPopup->InvalidateRect(NULL);
        }

        PlayGUISound(RESREF_SOUND_WINDOWOPEN);

        // NOTE: Uninline.
        SetPopupEnabled(pPanel->m_nID, TRUE);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel();
    }
}

// 0x66FE20
void CScreenStart::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 1:
        m_nNumErrorButtons = 0;
        break;
    case 2:
        m_nNumErrorButtons = 1;
        break;
    case 3:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 1626
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1639
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 1648
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 1701
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENSTART_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x670050
void CScreenStart::OnErrorButtonClick(DWORD nID)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1778
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nErrorState) {
    case 0:
        DismissPopup();
        break;
    case 1:
        switch (nID) {
        case 0:
            DismissPopup();

            // NOTE: Uninline.
            m_cUIManager.KillCapture();

            m_bExitProgram = TRUE;
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    case 2:
        DismissPopup();
        break;
    }

    renderLock.Unlock();
}

// 0x670140
void CScreenStart::ResetVersionMismatchPanel(CUIPanel* pPanel)
{
    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1853
    UTIL_ASSERT(pText != NULL);

    g_pBaldurChitin->m_cTlkTable.SetToken(TOKEN_SERVERVERSION,
        g_pBaldurChitin->GetBaldurMessage()->GetVersionControlShutdownServerString());

    g_pBaldurChitin->m_cTlkTable.SetToken(TOKEN_CLIENTVERSION,
        g_pBaldurChitin->GetBaldurMessage()->GetVersionControlShutdownClientString());

    STRREF strText;
    switch (g_pBaldurChitin->GetBaldurMessage()->m_nVersionControlShutdownReason) {
    case 1:
        strText = 11830;
        break;
    case 2:
        strText = 11832;
        break;
    case 3:
        strText = 1614;
        break;
    default:
        strText = -1;
        break;
    }

    UpdateText(pText, "%s", FetchString(strText));
}

// 0x6702C0
void CScreenStart::sub_6702C0()
{
    CSingleLock lock(&(m_cUIManager.field_36), TRUE);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();
        if (pPanel->m_nID == 4) {
            DismissPopup();
        }
    }

    lock.Unlock();
}

// NOTE: Inlined.
void CScreenStart::SetPopupEnabled(DWORD nID, BOOL bEnabled)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1355
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnabled);
}

// NOTE: Inlined.
void CScreenStart::ResetPopupPanel(DWORD nID)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1382
    UTIL_ASSERT(pPanel != NULL);

    switch (nID) {
    case 1:
    case 2:
    case 3:
        ResetErrorPanel(pPanel);
        break;
    case 4:
        ResetVersionMismatchPanel(pPanel);
        break;
    }
}

// NOTE: Inlined.
void CScreenStart::OnNewGameButtonClick()
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 959
    UTIL_ASSERT(pSettings != NULL);

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

    pSettings->SignalCharacterStatus(0,
        CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_START,
        TRUE,
        TRUE);

    g_pBaldurChitin->m_pEngineCreateChar->StartCreateChar(0, 1);
    SelectEngine(g_pBaldurChitin->m_pEngineCreateChar);

    m_nEngineState = 0;
}

// NOTE: Inlined.
void CScreenStart::OnLoadGameButtonClick()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 1002
    UTIL_ASSERT(pLoad != NULL);

    pLoad->StartLoad(0);
    SelectEngine(pLoad);

    m_nEngineState = 0;
}

// NOTE: Inlined.
void CScreenStart::OnPreGenerateButtonClick()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    g_pBaldurChitin->m_pEngineCreateChar->StartCreateChar(-1, 4);
    g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineCreateChar);
}

// -----------------------------------------------------------------------------

// 0x670350
CUIControlButtonStartMenu::CUIControlButtonStartMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x6703A0
CUIControlButtonStartMenu::~CUIControlButtonStartMenu()
{
}

// 0x670440
void CUIControlButtonStartMenu::OnLButtonClick(CPoint pt)
{
    CScreenStart* pStart = g_pBaldurChitin->m_pEngineStart;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
    // __LINE__: 2010
    UTIL_ASSERT(pStart != NULL);

    STR_RES strRes;

    switch (pStart->m_nEngineState) {
    case 0:
        switch (m_nID) {
        case 0:
            pStart->m_nEngineState = 1;
            pStart->UpdateMainPanel();
            g_pBaldurChitin->ClearChatMessages();
            break;
        case 1:
            pStart->m_nEngineState = 2;
            pStart->UpdateMainPanel();
            break;
        case 2:
            // NOTE: Some inlining, not sure which.
            if (1) {
                // NOTE: Uninline.
                pStart->m_cUIManager.KillCapture();

                CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
                // __LINE__: 1115
                UTIL_ASSERT(pMovies != NULL);

                pMovies->StartMovies(0);
                pStart->SelectEngine(pMovies);
            }
            break;
        case 3:
            pStart->OnQuitButtonClick();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
            // __LINE__: 2034
            UTIL_ASSERT(FALSE);
        }
        break;
    case 1:
        switch (m_nID) {
        case 0:
            // NOTE: Uninline.
            pStart->OnNewGameButtonClick();
            break;
        case 1:
            // NOTE: Uninline.
            pStart->OnLoadGameButtonClick();
            break;
        case 2:
            g_pBaldurChitin->GetObjectGame()->field_4B38 = 1;

            // NOTE: Uninline.
            pStart->OnLoadGameButtonClick();
            break;
        case 3:
            pStart->m_nEngineState = 0;
            pStart->UpdateMainPanel();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
            // __LINE__: 2061
            UTIL_ASSERT(FALSE);
        }
        break;
    case 2:
        switch (m_nID) {
        case 0:
            // NOTE: Uninline.
            pStart->OnPreGenerateButtonClick();
            break;
        case 1:
            pStart->sub_66F990();
            break;
        case 2:
            pStart->m_nEngineState = 0;
            pStart->UpdateMainPanel();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
            // __LINE__: 2083
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStart.cpp
        // __LINE__: 2089
        UTIL_ASSERT(FALSE);
    }
}

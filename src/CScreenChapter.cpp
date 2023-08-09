#include "CScreenChapter.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameJournal.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenConnection.h"
#include "CScreenMovies.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x5D2ED0
CScreenChapter::CScreenChapter()
{
    m_nLine = 0;
    m_bStarted = FALSE;
    m_nStartTime = 0;
    m_nTotalPlayTime = 0;
    m_nLineDelay = 0;
    m_nEndTime = 0;
    m_bEnded = FALSE;
    m_nEngineState = 0;

    SetVideoMode(0);
    m_pVirtualKeys[0] = CKeyInfo(VK_ESCAPE, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo(VK_RETURN, -1, 0);
    m_pVirtualKeys[2] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[3] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[4] = CKeyInfo(VK_TAB, 0, 0);

    m_nParagraph = -1;
    m_nChapter = -1;
    m_bCtrlKeyDown = FALSE;
    m_pMainPanel = NULL;
    m_pTextList = NULL;
    m_pTextControl = NULL;
    m_nSongCountDown = 10;
}

// 0x49FC40
BOOL CScreenChapter::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x5D3080
void CScreenChapter::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x49FC40
BOOL CScreenChapter::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenChapter::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenChapter::CheckMouseLButton()
{
    return TRUE;
}

// 0x5D76C0
void CScreenChapter::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x636970
void CScreenChapter::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x6369A0
void CScreenChapter::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenChapter::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenChapter::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenChapter::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x66F250
SHORT CScreenChapter::GetNumVirtualKeys()
{
    return CSCREENCHAPTER_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenChapter::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x5D3090
BYTE* CScreenChapter::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x5D30C0
CScreenChapter::~CScreenChapter()
{
    if (m_cVoiceSound.IsSoundPlaying()) {
        m_cVoiceSound.Stop();
        m_nParagraph = -1;
    }

    if (m_pTextList != NULL) {
        delete m_pTextList;
        m_pTextList = NULL;
    }

    m_bStarted = FALSE;
}

// 0x5D3180
void CScreenChapter::EngineActivated()
{
    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }
    }

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    UpdateCursorShape(0);
    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, TRUE);
    g_pBaldurChitin->GetObjectCursor()->m_bVisible = TRUE;
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
    m_cUIManager.InvalidateRect(NULL);

    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea();
    if (pArea != NULL) {
        if (pArea->m_nBattleSongCounter > 0) {
            pArea->m_nBattleSongCounter = 0;
            pArea->m_nCurrentSong = 256;
        }
    }

    m_nSongCountDown = 10;
    g_pBaldurChitin->cSoundMixer.StartSong(-1, 0x4 | 0x1);
}

// 0x5D32B0
void CScreenChapter::EngineDeactivated()
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

    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    g_pBaldurChitin->cSoundMixer.StopMusic(TRUE);
}

// 0x5D3350
void CScreenChapter::EngineDestroyed()
{
    m_pMainPanel = NULL;

    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x5D3370
void CScreenChapter::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUICHAP"), g_pBaldurChitin->field_4A28);

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
    m_bCtrlKeyDown = FALSE;
    m_pCurrentScrollBar = NULL;

    m_cUIManager.GetPanel(0)->SetActive(FALSE);
    m_cUIManager.GetPanel(1)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
}

// 0x5D3510
void CScreenChapter::EngineGameInit()
{
    m_nSelectedCharacter = 0;
    m_bCtrlKeyDown = FALSE;
    m_pCurrentScrollBar = NULL;
}

// 0x5D3530
void CScreenChapter::OnKeyDown(SHORT nKeysFlags)
{
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                switch (m_pVirtualKeysFlags[nKeyFlag]) {
                case VK_TAB:
                    m_cUIManager.ForceToolTip();
                    break;
                case VK_RETURN:
                    if (g_pBaldurChitin->cNetwork.GetSessionHosting() == TRUE) {
                        OnDoneButtonClick();
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

// 0x5D35C0
void CScreenChapter::OnPortraitLClick(DWORD nPortrait)
{
    DWORD nOldPortrait = m_nSelectedCharacter;
    m_nSelectedCharacter = nPortrait;
    UpdateMainPanel();

    m_cUIManager.GetPanel(1)->GetControl(nOldPortrait)->InvalidateRect();
    m_cUIManager.InvalidateRect(NULL);
}

// 0x5D3600
void CScreenChapter::TimerAsynchronousUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 681
    UTIL_ASSERT(pGame != NULL);

    STR_RES strRes;

    if (m_nSongCountDown >= 0) {
        if (m_nSongCountDown == 0 && m_nEngineState == 0) {
            INT nSong;
            switch (m_nChapter) {
            case 1:
            case 3:
            case 5:
            case 7:
                nSong = 42;
                break;
            default:
                nSong = 41;
                break;
            }

            g_pBaldurChitin->cSoundMixer.StartSong(nSong, 0x4 | 0x1);
        }
        m_nSongCountDown--;
    }

    if (m_bStarted && m_pTextList != NULL) {
        if (m_nParagraph > 0 && !m_cVoiceSound.IsSoundPlaying()) {
            if (m_nParagraph < m_pTextList->GetCount()) {
                STRREF dwStrId = m_pTextList->GetAt(m_pTextList->FindIndex(m_nParagraph));
                g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
                m_cVoiceSound.SetResRef(strRes.cSound.GetResRef(), TRUE, TRUE);
                m_cVoiceSound.SetChannel(0, 0);
                m_cVoiceSound.Play(FALSE);
                m_nParagraph++;
            } else {
                m_nParagraph = -1;
            }
        }

        if (!m_bEnded) {
            if (m_nLine >= m_pTextControl->m_plstStrings->GetCount() - m_pTextControl->field_A6A) {
                m_nEndTime = GetTickCount();
                m_bEnded = TRUE;
            }
        }

        m_pTextControl->OnScrollDown();
    }

    if (m_bEnded) {
        DWORD nTickCount = GetTickCount();
        DWORD nElapsed;
        if (nTickCount < m_nEndTime) {
            nElapsed = -1 - m_nEndTime + nTickCount;
        } else {
            nElapsed = nTickCount - m_nEndTime;
        }

        if (nElapsed > 2000 && g_pBaldurChitin->cNetwork.GetSessionOpen()) {
            OnDoneButtonClick();
        }
    }

    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);
}

// 0x5D3950
void CScreenChapter::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);

    if (!m_bStarted) {
        m_nStartTime = GetTickCount();
        m_bStarted = TRUE;
    }
}

// 0x5D39A0
void CScreenChapter::SwitchMainPanel(DWORD dwMainPanelId)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    if (m_pMainPanel != NULL) {
        m_pMainPanel->SetActive(FALSE);
    }

    m_pMainPanel = m_cUIManager.GetPanel(dwMainPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 866
    UTIL_ASSERT(m_pMainPanel != NULL);

    m_pMainPanel->SetActive(TRUE);
    m_pMainPanel->InvalidateRect(NULL);

    ResetMainPanel();
    UpdateMainPanel();

    renderLock.Unlock();
}

// 0x5D3A80
void CScreenChapter::ResetMainPanel()
{
    STR_RES strRes;
    int index;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 908
    UTIL_ASSERT(m_pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 909
    UTIL_ASSERT(m_pTextList != NULL && m_pTextList->GetCount() > 0);

    if (m_nEngineState == 0) {
        UpdateLabel(m_pMainPanel, 0x10000000, "%s", FetchString(m_pTextList->GetHead()));
    }

    m_pTextControl = static_cast<CUIControlTextDisplay*>(m_pMainPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 920
    UTIL_ASSERT(m_pTextControl != NULL);

    m_pTextControl->RemoveAll();
    m_pTextControl->m_sNameSeparator = CString(" ");

    // Add leading empty lines so that the text gracefully slide in from the
    // bottom.
    for (index = 0; index < m_pTextControl->field_A6A + 1; index++) {
        UpdateText(m_pTextControl, "");
    }

    m_nTotalPlayTime = 0;

    CSize size;
    m_pTextControl->m_labelFont.GetFrameSize(64, 0, size, FALSE);

    SHORT nFontHeight = m_pTextControl->m_labelFont.GetFontHeight(FALSE);

    m_pTextControl->field_AB4 = static_cast<SHORT>((nFontHeight + size.cy - 1) / nFontHeight);

    INT nLine = 0;
    INT nTextLength = 0;
    POSITION pos = m_pTextList->GetHeadPosition();
    while (pos != NULL) {
        g_pBaldurChitin->m_cTlkTable.Fetch(m_pTextList->GetAt(pos), strRes);

        if (nLine == 0) {
            // TODO: Check `Right`, doesn't make sense.
            m_pTextControl->DisplayString(CString(""),
                strRes.szText.Right(strRes.szText.GetLength()),
                m_pTextControl->m_rgbLabelColor,
                m_pTextControl->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);

            for (int n = strRes.szText.GetLength() - 1; n >= 0; n--) {
                if (!isspace(strRes.szText[n])) {
                    break;
                }

                m_pTextControl->DisplayString(CString(""),
                    CString(""),
                    m_pTextControl->m_rgbLabelColor,
                    m_pTextControl->m_rgbTextColor,
                    -1,
                    FALSE,
                    TRUE);
            }

            m_pTextControl->DisplayString(CString(""),
                CString(""),
                m_pTextControl->m_rgbLabelColor,
                m_pTextControl->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);
        } else {
            m_pTextControl->DisplayString(CString(""),
                strRes.szText,
                m_pTextControl->m_rgbLabelColor,
                m_pTextControl->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);

            m_pTextControl->DisplayString(CString(""),
                CString(""),
                m_pTextControl->m_rgbLabelColor,
                m_pTextControl->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);
        }

        m_nTotalPlayTime += strRes.cSound.GetPlayTime();
        nTextLength += strRes.szText.GetLength();
        nLine++;

        m_pTextList->GetNext(pos);
    }

    if (m_nTotalPlayTime == 0) {
        m_nTotalPlayTime = 50 * nTextLength;
    }

    // Add trailing empty lines so that the text gracefully slide out at the
    // top.
    for (index = 0; index < m_pTextControl->field_A6A; index++) {
        UpdateText(m_pTextControl, "");
    }

    m_nLineDelay = max(m_nTotalPlayTime / max(m_pTextControl->m_plstStrings->GetCount() - 7 * m_pTextControl->field_A6A / 4, 1), 833);

    m_pTextControl->SetTopString(m_pTextControl->m_plstStrings->FindIndex(0));

    m_nParagraph = 1;
    m_nLine = 1;
}

// 0x5D40B0
void CScreenChapter::UpdateMainPanel()
{
    CUIControlButton* pButton;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1023
    UTIL_ASSERT(m_pMainPanel != NULL);

    pButton = static_cast<CUIControlButton*>(m_pMainPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1027
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(!g_pBaldurChitin->cNetwork.GetSessionOpen()
        || g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL);

    pButton = static_cast<CUIControlButton*>(m_pMainPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1032
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(g_pChitin->cNetwork.GetSessionHosting() == TRUE);
}

// 0x5D4190
void CScreenChapter::OnDoneButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1086
    UTIL_ASSERT(pGame != NULL);

    switch (m_nEngineState) {
    case 0:
        StopText(TRUE);

        SelectEngine(g_pBaldurChitin->m_pEngineWorld);

        if (g_pBaldurChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
            && g_pBaldurChitin->cNetwork.GetSessionHosting() == TRUE) {
            // TODO: Incomplete.
            Sleep(25);
        }

        break;
    case 3:
        StopText(TRUE);

        // NOTE: Looks odd, sets something on start engine, but selects
        // connection (which is the main menu in IWD2).
        g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;

        SelectEngine(g_pBaldurChitin->m_pEngineConnection);

        if (g_pChitin->cNetwork.GetSessionOpen() == 1) {
            if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
            }

            g_pChitin->cNetwork.CloseSession(TRUE);
            g_pBaldurChitin->m_cBaldurMessage.m_bPlayerShutdown = 0;
        }

        pGame->DestroyGame(1, 0);

        break;
    case 4:
        // NOTE: Uninline.
        StopText(TRUE);

        SelectEngine(g_pBaldurChitin->m_pEngineMovies);

        break;
    }
}

// NOTE: Inlined.
void CScreenChapter::OnReplayButtonClick()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    m_cVoiceSound.Stop();
    m_pTextControl->SetTopString(m_pTextControl->m_plstStrings->FindIndex(0));
    m_nParagraph = 1;
    m_nLine = 1;
    m_bEnded = FALSE;
    m_nStartTime = GetTickCount();

    renderLock.Unlock();
}

// 0x5D4380
void CScreenChapter::StartChapter(const CResRef& cResText)
{
    m_nEngineState = 0;
    m_nChapter = g_pBaldurChitin->GetObjectGame()->GetCurrentChapter();

    m_nChapter = max(min(m_nChapter, CGameJournal::NUM_CHAPTERS + 1), 0);

    // NOTE: Uninline.
    StopText(FALSE);

    BOOL bResult = StartText(cResText);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__ 1232
    UTIL_ASSERT(bResult);

    SwitchMainPanel(m_nChapter);
}

// 0x5D4450
void CScreenChapter::StartChapterMultiplayerHost(BYTE nChapter, BYTE* resRef)
{
    g_pBaldurChitin->GetObjectGame()->SetCurrentChapter(nChapter);

    BOOLEAN bJoinRequests = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bJoinRequests;
    g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetListenToJoinOption(FALSE, TRUE);
    g_pBaldurChitin->m_pEngineWorld->m_bEndMajorEventListenToJoin = bJoinRequests;
    g_pBaldurChitin->m_pEngineWorld->m_bEndMajorEventPauseStatus = g_pBaldurChitin->m_pEngineWorld->m_bPaused;
    g_pBaldurChitin->m_pEngineWorld->m_bHardPaused = TRUE;

    if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
        g_pBaldurChitin->m_cBaldurMessage.sub_43E0E0(-1,
            17556,
            RGB(255, 0, 0),
            RGB(255, 0, 0),
            -1,
            CGameObjectArray::INVALID_INDEX,
            CGameObjectArray::INVALID_INDEX);

        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, g_pChitin->cNetwork.m_idLocalPlayer);
    }

    g_pBaldurChitin->GetBaldurMessage()->ChapterAnnounceStatus(nChapter, CResRef(resRef));

    // NOTE: Uninline.
    StartChapter(CResRef(resRef));
}

// 0x5D4650
BOOL CScreenChapter::StartText(const CResRef& cResText)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__ 1406
    UTIL_ASSERT(pGame != NULL);

    m_bStarted = FALSE;
    m_bEnded = FALSE;
    m_cResText = cResText;

    LONG id = pGame->GetCharacterId(0);

    CGameObject* pObject;
    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(id,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        pGame->GetObjectArray()->ReleaseShare(id,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__ 1440
    UTIL_ASSERT(m_pTextList == NULL);

    m_pTextList = pGame->GetRuleTables().GetChapterText(m_cResText, -1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__ 1443
    UTIL_ASSERT(m_pTextList != NULL);

    if (m_pTextList->IsEmpty()) {
        delete m_pTextList;
        m_pTextList = NULL;
        return FALSE;
    }

    return TRUE;
}

// 0x5D47A0
void CScreenChapter::StopText(BOOL bNotifyServer)
{
    if (m_pTextList != NULL) {
        delete m_pTextList;
        m_pTextList = NULL;

        if (bNotifyServer) {
            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && !g_pChitin->cNetwork.GetSessionHosting()) {
                g_pBaldurChitin->m_cBaldurMessage.SendSignal(CBaldurMessage::SIGNAL_SERVER,
                    CBaldurMessage::SIGNAL_END_MAJOR_EVENT);
            }
        }

        if (m_cVoiceSound.IsSoundPlaying()) {
            m_cVoiceSound.Stop();
            m_nParagraph = -1;
        }

        m_bStarted = FALSE;
    }
}

// 0x5D4840
void CScreenChapter::OnMixerInitialize()
{
    if (m_pTextList != NULL) {
        m_cVoiceSound.Stop();

        m_pTextControl->SetTopString(m_pTextControl->m_plstStrings->FindIndex(0));
        m_nParagraph = 1;
        m_nLine = 1;
        m_bEnded = FALSE;
        m_nStartTime = GetTickCount();
    }
}

// 0x5D48A0
void CScreenChapter::CancelEngine()
{
    // NOTE: Uninline.
    StopText(TRUE);
}

// 0x5D4930
CUIControlButtonChapterDone::CUIControlButtonChapterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x5D4A20
CUIControlButtonChapterDone::~CUIControlButtonChapterDone()
{
}

// 0x5D4AC0
void CUIControlButtonChapterDone::OnLButtonClick(CPoint pt)
{
    CScreenChapter* pChapter = g_pBaldurChitin->m_pEngineChapter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1680
    UTIL_ASSERT(pChapter != NULL);

    CSingleLock renderLock(&(pChapter->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pChapter->OnDoneButtonClick();

    renderLock.Unlock();
}

// 0x5D4B60
CUIControlButtonChapterReplay::CUIControlButtonChapterReplay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(16510, strRes);
    SetText(strRes.szText);
}

// 0x5D4C50
CUIControlButtonChapterReplay::~CUIControlButtonChapterReplay()
{
}

// 0x5D4CF0
void CUIControlButtonChapterReplay::OnLButtonClick(CPoint pt)
{
    CScreenChapter* pChapter = g_pBaldurChitin->m_pEngineChapter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1744
    UTIL_ASSERT(pChapter != NULL);

    CSingleLock renderLock(&(pChapter->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    // NOTE: Uninline.
    pChapter->OnReplayButtonClick();

    renderLock.Unlock();
}

// 0x5D4DE0
CUIControlTextDisplayChapter::CUIControlTextDisplayChapter(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
}

// 0x5D4E10
void CUIControlTextDisplayChapter::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    CScreenChapter* pChapter = g_pBaldurChitin->m_pEngineChapter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenChapter.cpp
    // __LINE__: 1833
    UTIL_ASSERT(pChapter != NULL);

    // NOTE: Rare case - bypasses direct superclass implementation, but still
    // calls one in inheritance chain.
    CUIControlBase::TimerAsynchronousUpdate(bInside);

    if (field_A65 != 0) {
        if (m_posTopString == m_plstStrings->GetTailPosition()) {
            field_A65 = 0;
        } else {
            DWORD nEnd = pChapter->m_nStartTime + pChapter->m_nLineDelay * (pChapter->m_nLine - 1);
            DWORD nTickCount = GetTickCount();
            DWORD nElapsed;
            if (nTickCount < nEnd) {
                nElapsed = -1 - nEnd + nTickCount;
            } else {
                nElapsed = nTickCount - nEnd;
            }

            field_A62 = -static_cast<SHORT>((nElapsed * m_nFontHeight) / pChapter->m_nLineDelay);

            if (field_A62 <= -m_nFontHeight) {
                field_A62 = 0;
                m_plstStrings->GetNext(m_posTopString);
                field_5A++;
                AdjustScrollBar();
                field_A65--;
                pChapter->m_nLine++;
            }

            CRect rDirty(m_pPanel->m_ptOrigin + m_ptOrigin, m_size);
            m_pPanel->InvalidateRect(&rDirty);
            InvalidateRect();
        }
    }
}

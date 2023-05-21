#include "CScreenMovies.h"

#include "CBaldurChitin.h"
#include "CBaldurProjector.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenOptions.h"
#include "CUIControlScrollBar.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x646A40
CScreenMovies::CScreenMovies()
{
    SetVideoMode(0);
    m_pVirtualKeys[0] = CKeyInfo(VK_SNAPSHOT, -1, 0);
    m_pVirtualKeys[1] = CKeyInfo(VK_RETURN, 0, 0);
    m_pVirtualKeys[2] = CKeyInfo(VK_END, 0, 0);
    m_pVirtualKeys[3] = CKeyInfo(VK_HOME, 0, 0);
    m_pVirtualKeys[4] = CKeyInfo(VK_LEFT, 0, 0);
    m_pVirtualKeys[5] = CKeyInfo(VK_RIGHT, 0, 0);
    m_pVirtualKeys[6] = CKeyInfo(VK_BACK, 0, 0);
    m_pVirtualKeys[7] = CKeyInfo(VK_DELETE, 0, 0);
    m_pVirtualKeys[8] = CKeyInfo(VK_SPACE, 0, 0);
    m_pVirtualKeys[9] = CKeyInfo('A', 0, 0);
    m_pVirtualKeys[10] = CKeyInfo('B', 0, 0);
    m_pVirtualKeys[11] = CKeyInfo('C', 0, 0);
    m_pVirtualKeys[12] = CKeyInfo('D', 0, 0);
    m_pVirtualKeys[13] = CKeyInfo('E', 0, 0);
    m_pVirtualKeys[14] = CKeyInfo('F', 0, 0);
    m_pVirtualKeys[15] = CKeyInfo('G', 0, 0);
    m_pVirtualKeys[16] = CKeyInfo('H', 0, 0);
    m_pVirtualKeys[17] = CKeyInfo('I', 0, 0);
    m_pVirtualKeys[18] = CKeyInfo('J', 0, 0);
    m_pVirtualKeys[19] = CKeyInfo('K', 0, 0);
    m_pVirtualKeys[20] = CKeyInfo('L', 0, 0);
    m_pVirtualKeys[21] = CKeyInfo('M', 0, 0);
    m_pVirtualKeys[22] = CKeyInfo('N', 0, 0);
    m_pVirtualKeys[23] = CKeyInfo('O', 0, 0);
    m_pVirtualKeys[24] = CKeyInfo('P', 0, 0);
    // FIXME: Overriding `P`.
    m_pVirtualKeys[24] = CKeyInfo(VK_ESCAPE, 0, 0);
    m_pVirtualKeys[25] = CKeyInfo('Q', 0, 0);
    m_pVirtualKeys[26] = CKeyInfo('R', 0, 0);
    m_pVirtualKeys[27] = CKeyInfo('S', 0, 0);
    m_pVirtualKeys[28] = CKeyInfo('T', 0, 0);
    m_pVirtualKeys[29] = CKeyInfo('U', 0, 0);
    m_pVirtualKeys[30] = CKeyInfo('V', 0, 0);
    m_pVirtualKeys[31] = CKeyInfo('W', 0, 0);
    m_pVirtualKeys[32] = CKeyInfo('X', 0, 0);
    m_pVirtualKeys[33] = CKeyInfo('Y', 0, 0);
    m_pVirtualKeys[34] = CKeyInfo('Z', 0, 0);
    m_pVirtualKeys[35] = CKeyInfo('0', 0, 0);
    m_pVirtualKeys[36] = CKeyInfo('1', 0, 0);
    m_pVirtualKeys[37] = CKeyInfo('2', 0, 0);
    m_pVirtualKeys[38] = CKeyInfo('3', 0, 0);
    m_pVirtualKeys[39] = CKeyInfo('4', 0, 0);
    m_pVirtualKeys[40] = CKeyInfo('5', 0, 0);
    m_pVirtualKeys[41] = CKeyInfo('6', 0, 0);
    m_pVirtualKeys[42] = CKeyInfo('7', 0, 0);
    m_pVirtualKeys[43] = CKeyInfo('8', 0, 0);
    m_pVirtualKeys[44] = CKeyInfo('9', 0, 0);
    m_pVirtualKeys[45] = CKeyInfo(VK_INSERT, 0, 0);
    // FIXME: Buffer overrun.
    m_pVirtualKeys[46] = CKeyInfo(VK_TAB, -1, 0);

    m_nEngineState = 0;
    m_pMovies = NULL;
    m_nMovieIndex = -1;
    field_7B0 = 0;
}

// 0x49FC40
BOOL CScreenMovies::CheckMouseMove()
{
    return TRUE;
}

// 0x66F4B0
void CScreenMovies::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenMovies::CheckMouseLButton()
{
    return TRUE;
}

// 0x6369A0
void CScreenMovies::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenMovies::CheckMouseRButton()
{
    return TRUE;
}

// 0x647090
SHORT CScreenMovies::GetNumVirtualKeys()
{
    return CSCREENMOVIES_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenMovies::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x6470A0
BYTE* CScreenMovies::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x6470D0
CScreenMovies::~CScreenMovies()
{
    if (m_pMovies != NULL) {
        delete m_pMovies;
        m_pMovies = NULL;
    }
}

// 0x647160
void CScreenMovies::EngineActivated()
{
    if (m_cUIManager.m_bInitialized) {
        m_preLoadFontRealms.SetResRef(CResRef("REALMS"), 0, TRUE);
        m_preLoadFontRealms.RegisterFont();

        CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
        CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 236
        UTIL_ASSERT(pLeftPanel != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 237
        UTIL_ASSERT(pRightPanel != NULL);

        pLeftPanel->SetEnabled(FALSE);
        pRightPanel->SetEnabled(FALSE);

        CUIPanel* pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 634
        UTIL_ASSERT(pPanel != NULL);

        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 640
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(m_nMovieIndex >= 0);

        g_pBaldurChitin->m_pObjectCursor->SetCursor(0, FALSE);
        g_pBaldurChitin->m_pObjectCursor->m_bVisible = TRUE;
        CheckEnablePortaits(1);
        CheckEnableLeftPanel();
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x647300
void CScreenMovies::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUIMOVIE"), g_pBaldurChitin->field_4A28);

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
}

// 0x6472D0
void CScreenMovies::EngineDeactivated()
{
    m_preLoadFontRealms.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }
}

// 0x647540
void CScreenMovies::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->field_1A2E = FALSE;
    g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);
}

// 0x647400
void CScreenMovies::OnKeyDown(SHORT nKeysFlags)
{
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_TAB:
                m_cUIManager.ForceToolTip();
                break;
            case VK_RETURN:
            case VK_ESCAPE:
                // NOTE: Uninline.
                StopMovies();

                // NOTE: Uninline.
                OnDoneButtonClick();
                break;
            case VK_SNAPSHOT:
                g_pBaldurChitin->GetCurrentVideoMode()->PrintScreen();
                break;
            }
        }
    }
}

// 0x647580
void CScreenMovies::TimerAsynchronousUpdate()
{
    UpdateCursorShape(0);
    g_pBaldurChitin->m_pObjectCursor->CursorUpdate(pVidMode);
    m_cUIManager.TimerAsynchronousUpdate();
}

// 0x64A110
void CScreenMovies::TimerSynchronousUpdate()
{
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x06475B0
void CScreenMovies::OnMovieItemSelect(INT nMovieIndex)
{
    CUIPanel* pPanel;

    if (nMovieIndex != m_nMovieIndex) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 678
        UTIL_ASSERT(m_pMovies != NULL);

        pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 682
        UTIL_ASSERT(pPanel != NULL);

        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 684
        UTIL_ASSERT(pText != NULL);

        if (m_nMovieIndex != -1) {
            pText->SetItemTextColor(pText->GetItemBossPosition(m_nMovieIndex),
                pText->m_rgbTextColor);
        }

        m_nMovieIndex = nMovieIndex;

        if (m_nMovieIndex != -1) {
            pText->SetItemTextColor(pText->GetItemBossPosition(m_nMovieIndex),
                CBaldurChitin::TEXTDISPLAY_COLOR_SELECT);
        }

        pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 634
        UTIL_ASSERT(pPanel != NULL);

        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(1));

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 640
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(m_nMovieIndex >= 0);
    }
}

// 0x647700
void CScreenMovies::OnPlayButtonClick()
{
    if (m_nMovieIndex >= 0) {
        CString sName;

        POSITION pos = m_pMovies->FindIndex(m_nMovieIndex);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 735
        UTIL_ASSERT(pos != NULL);

        sName = m_pMovies->GetAt(pos);

        CBaldurProjector::byte_8CFF2C = 1;
        g_pBaldurChitin->m_pEngineProjector->PlayMovie(CResRef(sName));

        CUIPanel* pPanel = m_cUIManager.GetPanel(2);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 745
        UTIL_ASSERT(pPanel != NULL);

        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
        // __LINE__: 747
        UTIL_ASSERT(pText != NULL);

        if (m_nMovieIndex != -1) {
            pText->SetItemTextColor(pText->GetItemBossPosition(m_nMovieIndex),
                pText->m_rgbTextColor);
        }

        m_nMovieIndex = -1;

        g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.sub_7AC840();
        g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.sub_7AC890();
    }
}

// 0x647E50
void CScreenMovies::OnCreditsButtonClick()
{
    g_pBaldurChitin->m_pEngineProjector->PlayMovie(CResRef("CREDITS"));
    g_pBaldurChitin->field_4F38 = g_pBaldurChitin->cSoundMixer.sub_7AC840();
    g_pBaldurChitin->field_4F3C = g_pBaldurChitin->cSoundMixer.sub_7AC890();
}

// NOTE: Inlined.
void CScreenMovies::OnDoneButtonClick()
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 838
    UTIL_ASSERT(pOptions != NULL);

    SelectEngine(pOptions);
}

// 0x647860
void CScreenMovies::StartMovies(INT nEngineState)
{
    CInfGame* pGame = g_pBaldurChitin->m_pObjectGame;

    m_nEngineState = nEngineState;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 866
    UTIL_ASSERT(m_pMovies == NULL);

    m_pMovies = g_pBaldurChitin->GetPlayedMovies();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 868
    UTIL_ASSERT(m_pMovies != NULL);

    m_nMovieIndex = -1;

    CUIPanel* pPanel = m_cUIManager.GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 873
    UTIL_ASSERT(pPanel != NULL);

    CString sName;
    CString sDescription;

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 880
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;

    POSITION pos = m_pMovies->GetHeadPosition();
    INT nIndex = 0;

    while (pos != NULL) {
        sName = m_pMovies->GetAt(pos);
        pGame->m_ruleTables.GetMovieDescription(sName, sDescription);
        if (sDescription.Compare("") != 0) {
            pText->DisplayString(CString(""),
                sDescription,
                pText->m_rgbLabelColor,
                pText->m_rgbTextColor,
                nIndex,
                FALSE,
                TRUE);
            m_pMovies->GetNext(pos);
            nIndex++;
        } else {
            POSITION prev = pos;
            m_pMovies->GetPrev(prev);
            m_pMovies->RemoveAt(pos);
            if (prev != NULL) {
                pos = prev;
            } else {
                pos = m_pMovies->GetHeadPosition();
            }
        }
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));
}

// NOTE: Inlined.
void CScreenMovies::StopMovies()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 941
    UTIL_ASSERT(m_pMovies != NULL);

    if (m_pMovies != NULL) {
        delete m_pMovies;
        m_pMovies = NULL;
    }
}

// 0x647A80
CUIControlTextDisplayMovies::CUIControlTextDisplayMovies(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603670
CUIControlTextDisplayMovies::~CUIControlTextDisplayMovies()
{
}

// 0x647AB0
void CUIControlTextDisplayMovies::OnItemSelected(LONG lMarker)
{
    CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 1002
    UTIL_ASSERT(pMovies != NULL);

    pMovies->OnMovieItemSelect(lMarker);
}

// 0x647AF0
CUIControlButtonMoviesPlay::CUIControlButtonMoviesPlay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(17318, strRes);
    SetText(strRes.szText);
}

// 0x647BE0
CUIControlButtonMoviesPlay::~CUIControlButtonMoviesPlay()
{
}

// 0x647C80
void CUIControlButtonMoviesPlay::OnLButtonClick(CPoint pt)
{
    CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 1058
    UTIL_ASSERT(pMovies != NULL);

    pMovies->OnPlayButtonClick();
}

// 0x647CC0
CUIControlButtonMoviesCredits::CUIControlButtonMoviesCredits(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15591, strRes);
    SetText(strRes.szText);
}

// 0x647DB0
CUIControlButtonMoviesCredits::~CUIControlButtonMoviesCredits()
{
}

// 0x647E50
void CUIControlButtonMoviesCredits::OnLButtonClick(CPoint pt)
{
    CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 1058
    UTIL_ASSERT(pMovies != NULL);

    // NOTE: Uninline.
    pMovies->OnCreditsButtonClick();
}

// 0x647ED0
CUIControlButtonMoviesDone::CUIControlButtonMoviesDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x647FC0
CUIControlButtonMoviesDone::~CUIControlButtonMoviesDone()
{
}

// 0x648060
void CUIControlButtonMoviesDone::OnLButtonClick(CPoint pt)
{
    CScreenMovies* pMovies = g_pBaldurChitin->m_pEngineMovies;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenMovies.cpp
    // __LINE__: 1170
    UTIL_ASSERT(pMovies != NULL);

    // NOTE: Uninline.
    pMovies->StopMovies();

    // NOTE: Uninline.
    pMovies->OnDoneButtonClick();
}

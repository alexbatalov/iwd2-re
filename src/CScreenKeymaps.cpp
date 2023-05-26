#include "CScreenKeymaps.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CScreenOptions.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8B3FE0
INT CScreenKeymaps::dword_8B3FE0[CSCREENKEYMAPS_PAGES][CSCREENKEYMAPS_PER_PAGE] = {
    {
        -1,
        0,
        1,
        3,
        4,
        5,
        6,
        7,
        2,
        -1,
        -1,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        21,
        -1,
        -1,
        25,
        26,
        22,
        23,
        28,
        24,
        27,
        29,
        30,
        31,
        32,
        33,
        34,
        35,
        36,
        37,
        -1,
        -1,
        41,
        42,
        43,
        44,
        38,
        39,
        40,
        45,
        46,
        47,
        48,
        49,
        50,
        51,
        52,
    },
};

// 0x8B40D0
STRREF CScreenKeymaps::dword_8B40D0[CSCREENKEYMAPS_PAGES][CSCREENKEYMAPS_PER_PAGE] = {
    {
        33478,
        16307,
        16306,
        16308,
        33505,
        17384,
        13696,
        13902,
        16313,
        (STRREF)-1,
        33501,
        15925,
        4974,
        4918,
        4688,
        4978,
        4933,
        4971,
        4968,
        4927,
        15924,
        4666,
        4954,
        30289,
        30290,
        (STRREF)-1,
        33500,
        33506,
        33507,
        33508,
        32050,
        40248,
        40249,
        33509,
        11942,
        40250,
        40251,
        40252,
        40253,
        40254,
        40255,
        40256,
        40273,
        (STRREF)-1,
        40257,
        40258,
        40259,
        40260,
        40261,
        40262,
        40263,
        40264,
        40265,
        40266,
        40267,
        40268,
        40269,
        40270,
        40271,
        40272,
    },
};

// 0x6380E0
CScreenKeymaps::CScreenKeymaps()
{
    m_nHighlightedKeymapIndex = 0;
    m_nConflictKey = 0;
    m_nConflictKeyFlag = 0;
    m_bFromMainMenu = FALSE;

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

    m_bSystemKeyCtrl = FALSE;
    m_bSystemKeyShift = FALSE;
    m_bSystemKeyCapsLock = FALSE;
    field_44A = -1;
    m_dwErrorTextId = -1;
    m_strErrorButtonText[0] = -1;
    m_strErrorButtonText[1] = -1;
    m_strErrorButtonText[2] = -1;
    m_nNumErrorButtons = 0;
    m_nPage = 0;
    m_nSelectedKeymapIndex = -1;
}

// #binary-identical
// 0x638D50
void CScreenKeymaps::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bSystemKeyCtrl = bValue;
}

// #binary-identical
// 0x638D60
BOOL CScreenKeymaps::GetCtrlKey()
{
    return m_bSystemKeyCtrl;
}

// #binary-identical
// 0x638D70
void CScreenKeymaps::SetSystemKeyShift(BOOL bValue)
{
    m_bSystemKeyShift = bValue;
}

// #binary-identical
// 0x638D80
BOOL CScreenKeymaps::GetShiftKey()
{
    return m_bSystemKeyShift;
}

// #binary-identical
// 0x638D90
void CScreenKeymaps::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bSystemKeyCapsLock = bValue;
}

// #binary-identical
// 0x638DA0
BOOL CScreenKeymaps::GetCapsLockKey()
{
    return m_bSystemKeyCapsLock;
}

// 0x49FC40
BOOL CScreenKeymaps::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenKeymaps::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenKeymaps::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenKeymaps::CheckMouseMove()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenKeymaps::CheckMouseLButton()
{
    return TRUE;
}

// #binary-identical
// 0x5D76C0
void CScreenKeymaps::OnLButtonDblClk(CPoint pt)
{
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x6369A0
void CScreenKeymaps::OnLButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnLButtonUp(pt);
}

// 0x49FC40
BOOL CScreenKeymaps::CheckMouseRButton()
{
    return TRUE;
}

// 0x6369D0
void CScreenKeymaps::OnRButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x636A00
void CScreenKeymaps::OnRButtonUp(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x686660
SHORT CScreenKeymaps::GetNumVirtualKeys()
{
    return CSCREENKEYMAPS_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenKeymaps::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x668C30
BYTE* CScreenKeymaps::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// #binary-identical
// 0x638DD0
CScreenKeymaps::~CScreenKeymaps()
{
}

// 0x638E40
void CScreenKeymaps::EngineActivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
    }

    if (m_cUIManager.m_bInitialized) {
        UpdateMainPanel();
        UpdateCursorShape(0);
        m_cUIManager.InvalidateRect(NULL);
    }
}

// 0x638EC0
void CScreenKeymaps::EngineDeactivated()
{
    if (CChitin::byte_8FB950
        && g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pChitin->cNetwork.GetSessionHosting() == TRUE
        && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
        }
    }

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x5D72C0
void CScreenKeymaps::EngineDestroyed()
{
    m_cUIManager.fUninit();
}

// 0x638F40
void CScreenKeymaps::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUIKEYS"), g_pBaldurChitin->field_4A28);

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

    // field_776 = 0;

    m_cUIManager.GetPanel(1)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    CUIControlButton* pDefaultButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));
    pDefaultButton->SetText(FetchString(33479)); // "Default"

    CUIControlButton* pDoneButton = static_cast<CUIControlButton*>(pPanel->GetControl(4));
    pDoneButton->SetText(FetchString(11973)); // "Done"

    CUIControlButton* pCancelButton = static_cast<CUIControlButton*>(pPanel->GetControl(5));
    pCancelButton->SetText(FetchString(13727)); // "Cancel"
}

// 0x639130
void CScreenKeymaps::OnKeyDown(SHORT nKeysFlags)
{
    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            HandleKeyDown(m_pVirtualKeysFlags[nKeyFlag]);
        }
    }
}

// 0x639160
void CScreenKeymaps::HandleKeyDown(BYTE nKey)
{
    switch (nKey) {
    case VK_ESCAPE:
        if (GetTopPopup() != NULL) {
            sub_639E70();
        } else {
            if (m_nSelectedKeymapIndex >= 0) {
                SelectKeymap(-1);
                sub_63A660(g_pBaldurChitin->m_ptPointer);
            } else {
                // NOTE: Uninline.
                OnCancelButtonClick();
            }
        }
        return;
    case VK_RETURN:
        if (GetTopPopup() == NULL) {
            if (m_nSelectedKeymapIndex >= 0) {
                SelectKeymap(-1);
                sub_63A660(g_pBaldurChitin->m_ptPointer);
            } else {
                // NOTE: Uninline.
                OnDoneButtonClick();
            }
        }
        return;
    }

    if (m_cUIManager.OnKeyDown(nKey)) {
        return;
    }

    if (m_bSystemKeyCtrl) {
        switch (nKey) {
        case VK_TAB:
            m_cUIManager.ForceToolTip();
            break;
        case VK_SNAPSHOT:
            g_pBaldurChitin->pActiveEngine->pVidMode->PrintScreen();
            break;
        }
    }

    CUIPanel* pPanel = GetTopPopup();
    if (pPanel != NULL) {
        switch (pPanel->m_nID) {
        case 1:
            switch (nKey) {
            case VK_RETURN:
            case 'Y':
                static_cast<CUIControlButton*>(pPanel->GetControl(1))->OnLButtonClick(CPoint(0, 0));
                break;
            case VK_ESCAPE:
            case 'N':
                static_cast<CUIControlButton*>(pPanel->GetControl(2))->OnLButtonClick(CPoint(0, 0));
                break;
            }
        }
        return;
    }

    if (m_nSelectedKeymapIndex < 0) {
        switch (nKey) {
        case VK_RETURN:
        case 'D':
            static_cast<CUIControlButton*>(m_cUIManager.GetPanel(0)->GetControl(4))->OnLButtonClick(CPoint(0, 0));
            break;
        case VK_ESCAPE:
        case 'C':
            static_cast<CUIControlButton*>(m_cUIManager.GetPanel(0)->GetControl(5))->OnLButtonClick(CPoint(0, 0));
            break;
        case VK_PRIOR:
        case VK_LEFT:
            static_cast<CUIControlButton*>(m_cUIManager.GetPanel(0)->GetControl(0))->OnLButtonClick(CPoint(0, 0));
            break;
        case VK_NEXT:
        case VK_RIGHT:
            static_cast<CUIControlButton*>(m_cUIManager.GetPanel(0)->GetControl(1))->OnLButtonClick(CPoint(0, 0));
            break;
        }
        return;
    }

    if (nKey == VK_DELETE || nKey == VK_BACK) {
        nKey = 0;
    } else if ((nKey >= 'A' && nKey <= 'Z') || (nKey >= '0' && nKey <= '9')) {
        nKey = nKey;
    } else {
        nKey = g_pBaldurChitin->GetObjectGame()->sub_5A97D0(g_pBaldurChitin->GetObjectGame()->sub_5A9780(nKey));
        if (nKey < 0) {
            return;
        }
    }

    if (m_bSystemKeyCtrl && nKey >= '0' && nKey <= '9') {
        return;
    }

    // NOTE: Original code is slightly different, but does the same thing.
    int conflict = -1;
    for (int index = 0; index < CSCREENKEYMAPS_PAGES * CSCREENKEYMAPS_PER_PAGE; index++) {
        if (nKey <= 0) {
            continue;
        }

        int nKeymap = dword_8B3FE0[index / CSCREENKEYMAPS_PER_PAGE][index % CSCREENKEYMAPS_PER_PAGE];
        if (nKeymap < 0
            || m_pKeymap[nKeymap] != nKey
            || m_pKeymapFlags[nKeymap] != m_bSystemKeyCtrl) {
            continue;
        }

        if (index % CSCREENKEYMAPS_PER_PAGE == m_nSelectedKeymapIndex + CSCREENKEYMAPS_PER_PAGE * m_nPage) {
            continue;
        }

        conflict = index;
        break;
    }

    if (conflict == -1) {
        SetKeymap(m_nPage, m_nSelectedKeymapIndex, nKey, m_bSystemKeyCtrl);
        SelectKeymap(-1);
        sub_63A660(g_pBaldurChitin->m_ptPointer);
        return;
    }

    m_nConflictKey = nKey;
    m_nConflictKeyFlag = m_bSystemKeyCtrl;

    CString sValue;
    if (m_bSystemKeyCtrl) {
        sValue.Format("%s%c", FetchString(24638), g_pBaldurChitin->GetObjectGame()->sub_5A9780(nKey));
    } else {
        sValue.Format("%c", g_pBaldurChitin->GetObjectGame()->sub_5A9780(nKey));
    }

    g_pBaldurChitin->m_cTlkTable.SetToken(CString("KEY"), sValue);

    g_pBaldurChitin->m_cTlkTable.SetToken(CString("OPERATION"), FetchString(dword_8B40D0[conflict / CSCREENKEYMAPS_PER_PAGE][conflict % CSCREENKEYMAPS_PER_PAGE]));

    m_dwErrorTextId = 33480;
    m_strErrorButtonText[0] = 33481;
    m_strErrorButtonText[1] = 33482;
    SummonPopup(1);
}

// 0x639790
void CScreenKeymaps::OnLButtonDown(CPoint pt)
{
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
    m_cUIManager.OnLButtonDown(pt);

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    pt -= pPanel->m_ptOrigin;

    if (GetTopPopup() == NULL && m_nSelectedKeymapIndex < 0) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);

        if (m_nSelectedKeymapIndex >= 0) {
            CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nSelectedKeymapIndex + 0x10000041));
            CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nSelectedKeymapIndex + 0x10000005));
            pNameLabel->SetForegroundColor(RGB(160, 160, 160));
            pKeyLabel->SetForegroundColor(RGB(160, 160, 160));
            SelectKeymap(-1);
        }

        for (int index = 0; index < CSCREENKEYMAPS_PER_PAGE; index++) {
            CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000041));
            CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000005));

            if (dword_8B3FE0[m_nPage][index] >= 0) {
                if (pNameLabel->IsOver(pt) || pKeyLabel->IsOver(pt)) {
                    SelectKeymap(index);
                    break;
                }
            }
        }

        sub_63A7A0(pt);
    }
}

// 0x639940
void CScreenKeymaps::OnMouseMove(CPoint pt)
{
    m_cUIManager.OnMouseMove(pt);

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    sub_63A7A0(pt - pPanel->m_ptOrigin);
}

// 0x639980
void CScreenKeymaps::TimerAsynchronousUpdate()
{
    UpdateCursorShape(0);
    m_cUIManager.TimerAsynchronousUpdate();
    g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

    if (m_nSelectedKeymapIndex >= 0) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
        CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nSelectedKeymapIndex + 0x10000005));

        if (GetTopPopup() != NULL) {
            pKeyLabel->SetForegroundColor(RGB(255, 240, 0));
        } else {
            INT nBlink = GetTickCount() & 0x1FF;
            if (nBlink < 256) {
                pKeyLabel->SetForegroundColor(RGB(nBlink & 0xFF, nBlink & 0xFF, 0));
            } else {
                pKeyLabel->SetForegroundColor(RGB(-1 - (nBlink & 0xFF), -1 - (nBlink & 0xFF), 0));
            }
        }
    }
}

// 0x63BAA0
void CScreenKeymaps::TimerSynchronousUpdate()
{
    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();
    pVidMode->Flip(TRUE);
}

// 0x639A50
void CScreenKeymaps::UpdateMainPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    CUIControlLabel* pPageLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x10000001));

    CString sValue;

    sValue.Format("%d", m_nPage + 1);
    g_pBaldurChitin->m_cTlkTable.SetToken(CString("PAGE"), sValue);

    sValue.Format("%d", 1);
    g_pBaldurChitin->m_cTlkTable.SetToken(CString("NUMPAGES"), sValue);

    pPageLabel->SetText(FetchString(33483));

    for (int index = 0; index < CSCREENKEYMAPS_PER_PAGE; index++) {
        CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000041));
        pNameLabel->SetText(FetchString(dword_8B40D0[m_nPage][index]));

        CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000005));
        if (dword_8B3FE0[m_nPage][index] >= 0) {
            int ch = g_pBaldurChitin->GetObjectGame()->sub_5A9780(m_pKeymap[dword_8B3FE0[m_nPage][index]]);
            if (ch > 0) {
                if (m_pKeymapFlags[dword_8B3FE0[m_nPage][index]] == 1) {
                    sValue.Format("%s%c", FetchString(24638), ch);
                    pKeyLabel->SetText(sValue);
                } else {
                    sValue.Format("%c", ch);
                    pKeyLabel->SetText(sValue);
                }
            } else {
                if (index == m_nSelectedKeymapIndex) {
                    pKeyLabel->SetText(CString("_"));
                } else {
                    pKeyLabel->SetText(CString(""));
                }
            }
        } else {
            if (index == m_nSelectedKeymapIndex) {
                pKeyLabel->SetText(CString("_"));
            } else {
                pKeyLabel->SetText(CString(""));
            }
        }
    }

    sub_63A660(g_pBaldurChitin->m_ptPointer);
}

// 0x639DC0
void CScreenKeymaps::StartKeymaps()
{
    g_pBaldurChitin->GetObjectGame()->LoadKeymap();

    for (SHORT index = 0; index < CINFGAME_KEYMAP_SIZE; index++) {
        // __FILE__: .\Include\InfGame.h
        // __LINE__: 1486
        UTIL_ASSERT(index >= 0 && index < CINFGAME_KEYMAP_SIZE);

        m_pKeymap[index] = g_pBaldurChitin->GetObjectGame()->m_pKeymap[index];
        m_pKeymapFlags[index] = g_pBaldurChitin->GetObjectGame()->m_pKeymapFlags[index];
    }
}

// 0x639E70
void CScreenKeymaps::sub_639E70()
{
    CSingleLock lock(&(GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1178
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 1:
        DismissPopup();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1187
        UTIL_ASSERT(FALSE);
    }

    lock.Unlock();
}

// NOTE: Inlined.
void CScreenKeymaps::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1375
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }
}

// NOTE: Inlined.
CUIPanel* CScreenKeymaps::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// NOTE: Inlined.
void CScreenKeymaps::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
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
void CScreenKeymaps::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1450
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);
}

// NOTE: Inlined.
void CScreenKeymaps::ResetPopupPanel(DWORD dwPanelId)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1477
    UTIL_ASSERT(pPanel != NULL);

    switch (pPanel->m_nID) {
    case 1:
        ResetErrorPanel(pPanel);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1486
        UTIL_ASSERT(FALSE);
    }
}

// NOTE: Uninline.
void CScreenKeymaps::UpdatePopupPanel(DWORD dwPanelId)
{
    switch (dwPanelId) {
    case 1:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1519
        UTIL_ASSERT(FALSE);
    }
}

// 0x639F40
void CScreenKeymaps::SummonPopup(DWORD dwPopupId)
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1599
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        // NOTE: Uninline.
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPopupId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1605
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

// 0x63A100
void CScreenKeymaps::DismissPopup()
{
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1650
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1667
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        UpdatePopupPanel(pPanel->m_nID);
    } else {
        // NOTE: Uninline.
        EnableMainPanel(TRUE);

        UpdateMainPanel();
    }
}

// 0x63A280
void CScreenKeymaps::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 1:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1704
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_dwErrorTextId, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 1717
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1726
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
        // __LINE__: 1865
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENKEYMAPS_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// NOTE: Inlined.
void CScreenKeymaps::OnPageButtonClick(INT nButton)
{
    m_nPage += nButton != 0 ? 1 : -1;
    if (m_nPage < 0) {
        m_nPage = 0;
    } else if (m_nPage >= CSCREENKEYMAPS_PAGES) {
        m_nPage = CSCREENKEYMAPS_PAGES - 1;
    }

    m_nSelectedKeymapIndex = -1;
    UpdateMainPanel();
}

// NOTE: Inlined.
void CScreenKeymaps::OnDefaultButtonClick()
{
    if (m_nSelectedKeymapIndex >= 0) {
        BYTE nKey = g_pBaldurChitin->GetObjectGame()->sub_5A9830(CScreenKeymaps::dword_8B3FE0[m_nPage][m_nSelectedKeymapIndex]);
        if (nKey != 0) {
            HandleKeyDown(nKey);
        } else {
            HandleKeyDown(0);
        }
    } else {
        m_dwErrorTextId = 33484;
        m_strErrorButtonText[0] = 33481;
        m_strErrorButtonText[1] = 33482;
        SummonPopup(1);
    }
}

// NOTE: Inlined.
void CScreenKeymaps::OnDoneButtonClick()
{
    m_nSelectedKeymapIndex = -1;

    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // FIXME: Does not assert `pOptions`.
    // FIXME: Does not restore `m_bFromMainMenu`.

    SelectEngine(pOptions);

    for (int index = 0; index < CINFGAME_KEYMAP_SIZE; index++) {
        g_pBaldurChitin->GetObjectGame()->SetKey(index,
            m_pKeymap[index],
            m_pKeymapFlags[index]);
    }
}

// NOTE: Inlined.
void CScreenKeymaps::OnCancelButtonClick()
{
    m_nSelectedKeymapIndex = -1;

    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: .\Include\InfGame.h
    // __LINE__: 1200
    UTIL_ASSERT(pOptions != NULL);

    pOptions->m_bFromMainMenu = m_bFromMainMenu;
    SelectEngine(pOptions);
}

// 0x63A480
void CScreenKeymaps::OnErrorButtonClick(INT nButton)
{
    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    switch (m_dwErrorTextId) {
    case 33480:
        switch (nButton) {
        case 0:
            DismissPopup();

            for (int index = 0; index < CSCREENKEYMAPS_PAGES * CSCREENKEYMAPS_PER_PAGE; index++) {
                INT nKeymap = dword_8B3FE0[index / CSCREENKEYMAPS_PER_PAGE][index % CSCREENKEYMAPS_PER_PAGE];
                if (m_pKeymap[nKeymap] == m_nConflictKey
                    && m_pKeymapFlags[nKeymap] == m_nConflictKeyFlag) {
                    SetKeymap(index / CSCREENKEYMAPS_PER_PAGE, index % CSCREENKEYMAPS_PER_PAGE, 0, 0);
                }
            }

            SetKeymap(m_nPage, m_nSelectedKeymapIndex, m_nConflictKey, m_nConflictKeyFlag);

            UpdateMainPanel();
            break;
        case 1:
            DismissPopup();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
            // __LINE__: 1784
            UTIL_ASSERT(FALSE);
        }
        break;
    case 33484:
        m_nSelectedKeymapIndex = -1;

        switch (nButton) {
        case 0:
            DismissPopup();

            for (int index = 0; index < CINFGAME_KEYMAP_SIZE; index++) {
                m_pKeymap[index] = g_pBaldurChitin->GetObjectGame()->sub_5A9830(index);
            }

            UpdateMainPanel();
            break;
        case 1:
            DismissPopup();
            break;
        }
    }

    lock.Unlock();

    SelectKeymap(-1);
    sub_63A660(g_pBaldurChitin->m_ptPointer);
}

// 0x63A640
void CScreenKeymaps::CancelEngine()
{
    // FIXME: Original code is an infinite loop. Other screens usually calls
    // `OnCancelButtonClick` to gracefully dismiss popups one by one.
    while (GetTopPopup() != NULL) {
    }
}

// 0x63A660
void CScreenKeymaps::sub_63A660(CPoint pt)
{
    if (GetTopPopup() != NULL) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    m_nHighlightedKeymapIndex = -1;

    for (int index = 0; index < CSCREENKEYMAPS_PER_PAGE; index++) {
        CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000041));
        CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000005));

        if (dword_8B3FE0[m_nPage][index] >= 0) {
            if (index == m_nSelectedKeymapIndex) {
                pNameLabel->SetForegroundColor(RGB(255, 240, 0));
            } else if (m_nSelectedKeymapIndex < 0) {
                if (pNameLabel->IsOver(pt) || pKeyLabel->IsOver(pt)) {
                    pNameLabel->SetForegroundColor(RGB(255, 255, 255));
                    pKeyLabel->SetForegroundColor(RGB(255, 255, 255));
                    m_nHighlightedKeymapIndex = index;
                } else {
                    pNameLabel->SetForegroundColor(RGB(160, 160, 160));
                    pKeyLabel->SetForegroundColor(RGB(160, 160, 160));
                }
            }
        } else {
            pNameLabel->SetForegroundColor(RGB(0, 240, 255));
            pKeyLabel->SetForegroundColor(RGB(0, 240, 255));
        }
    }
}

// 0x63A7A0
void CScreenKeymaps::sub_63A7A0(CPoint pt)
{
    if (GetTopPopup() != NULL) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    if (m_nHighlightedKeymapIndex >= 0) {
        if (m_nHighlightedKeymapIndex != m_nSelectedKeymapIndex) {
            CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nHighlightedKeymapIndex + 0x10000041));
            CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nHighlightedKeymapIndex + 0x10000005));
            pNameLabel->SetForegroundColor(RGB(160, 160, 160));
            pKeyLabel->SetForegroundColor(RGB(160, 160, 160));
        }

        m_nHighlightedKeymapIndex = -1;
    }

    for (int index = 0; index < CSCREENKEYMAPS_PER_PAGE; index++) {
        if (dword_8B3FE0[m_nPage][index] >= 0) {
            CUIControlLabel* pNameLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000041));
            CUIControlLabel* pKeyLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(index + 0x10000005));

            if (index == m_nSelectedKeymapIndex) {
                pNameLabel->SetForegroundColor(RGB(255, 240, 0));
            } else if (m_nSelectedKeymapIndex < 0) {
                if (pNameLabel->IsOver(pt) || pKeyLabel->IsOver(pt)) {
                    pNameLabel->SetForegroundColor(RGB(255, 255, 255));
                    pKeyLabel->SetForegroundColor(RGB(255, 255, 255));
                    m_nHighlightedKeymapIndex = index;
                    break;
                }
            }
        }
    }
}

// 0x63A910
void CScreenKeymaps::SetKeymap(INT nPage, INT nIndex, BYTE nKey, BYTE nKeyFlag)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);
    CString sKey;

    m_pKeymap[dword_8B3FE0[nPage][nIndex]] = nKey;
    m_pKeymapFlags[dword_8B3FE0[nPage][nIndex]] = nKeyFlag;

    CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(nIndex + 0x10000005));

    if (nKeyFlag != 0) {
        sKey.Format("%s%c",
            FetchString(24638),
            g_pBaldurChitin->GetObjectGame()->sub_5A9780(m_pKeymap[dword_8B3FE0[nPage][nIndex]]));
    } else {
        sKey.Format("%c", g_pBaldurChitin->GetObjectGame()->sub_5A9780(m_pKeymap[dword_8B3FE0[nPage][nIndex]]));
    }

    pLabel->SetText(sKey);
}

// 0x63AA60
void CScreenKeymaps::SelectKeymap(INT nIndex)
{
    if (m_nSelectedKeymapIndex >= 0) {
        SetKeymap(m_nPage,
            m_nSelectedKeymapIndex,
            m_pKeymap[dword_8B3FE0[m_nPage][m_nSelectedKeymapIndex]],
            m_pKeymapFlags[dword_8B3FE0[m_nPage][m_nSelectedKeymapIndex]]);
    }

    m_nSelectedKeymapIndex = nIndex;

    if (m_nSelectedKeymapIndex >= 0 && m_pKeymap[dword_8B3FE0[m_nPage][m_nSelectedKeymapIndex]] == 0) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(0);
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(m_nSelectedKeymapIndex + 0x10000005));
        pLabel->SetText(CString("_"));
    }
}

// 0x63AB50
CUIControlButtonKeymap::CUIControlButtonKeymap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    SetText(CString(""));
}

// 0x63AC00
CUIControlButtonKeymap::~CUIControlButtonKeymap()
{
}

// 0x63ACA0
void CUIControlButtonKeymap::OnLButtonClick(CPoint pt)
{
    CScreenKeymaps* pKeymaps = g_pBaldurChitin->m_pEngineKeymaps;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenKeymaps.cpp
    // __LINE__: 2107
    UTIL_ASSERT(pKeymaps != NULL);

    CSingleLock lock(&(pKeymaps->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    switch (m_pPanel->m_nID) {
    case 0:
        switch (m_nID) {
        case 0:
        case 1:
            // NOTE: Uninline.
            pKeymaps->OnPageButtonClick(m_nID);
            break;
        case 3:
            // NOTE: Uninline.
            pKeymaps->OnDefaultButtonClick();
            break;
        case 4:
            // NOTE: Uninline.
            pKeymaps->OnDoneButtonClick();
            break;
        case 5:
            // NOTE: Uninline.
            pKeymaps->OnCancelButtonClick();
            break;
        }
        break;
    case 1:
        if (m_nID != 0 && m_nID < CSCREENKEYMAPS_ERROR_BUTTONS + 1) {
            pKeymaps->OnErrorButtonClick(m_nID - 1);
        }
        break;
    }

    lock.Unlock();
}

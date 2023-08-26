#include "CScreenWorld.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CUIControlScrollBar.h"
#include "CUIPanel.h"

// 0x85A1EC
const LONG CScreenWorld::BORED_TIME = 3000;

// 0x685610
CScreenWorld::CScreenWorld()
{
    // TODO: Incomplete.

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

    // TODO: Incomplete.
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
    // TODO: Incomplete.
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

// 0x49FC40
BOOL CScreenWorld::CheckMouseLButton()
{
    return TRUE;
}

// 0x68C020
void CScreenWorld::OnLButtonDblClk(CPoint pt)
{
    OnLButtonDblClk(pt);

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

// 0x68C3D0
void CScreenWorld::AsynchronousUpdate(BOOL bActiveEngine)
{
    // TODO: Incomplete.
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
    }
}

// 0x68DFD0
BOOL CScreenWorld::TogglePauseGame(char a2, char a3, int a4)
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x68E6E0
BOOLEAN CScreenWorld::ReadyMovie(const CResRef& movieResRef, BOOLEAN bForcedFromServer)
{
    return FALSE;
}

// 0x691B50
void CScreenWorld::StopStore()
{
    // TODO: Incomplete.
}

// 0x692690
void CScreenWorld::ClearChatMessages()
{
    field_10DE = 0;
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

// 0x697970
CUIControlButtonClock::CUIControlButtonClock(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    // TODO: Incomplete.
}

// 0x697C20
CUIControlButtonClock::~CUIControlButtonClock()
{
}

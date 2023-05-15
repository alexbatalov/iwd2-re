#include "CScreenConnection.h"

#include "CBaldurChitin.h"
#include "CBaldurProjector.h"
#include "CInfCursor.h"
#include "CScreenStart.h"
#include "CUIPanel.h"
#include "CUIControlTextDisplay.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x8F375C
const CString CScreenConnection::TOKEN_SERVERVERSION("SERVERVERSION");

// 0x8F3748
const CString CScreenConnection::TOKEN_CLIENTVERSION("CLIENTVERSION");

// 0x8B3340
BOOLEAN CScreenConnection::byte_8B3340 = TRUE;

// 0x8B3341
BOOLEAN CScreenConnection::byte_8B3341 = TRUE;

// 0x8B3342
BOOLEAN CScreenConnection::byte_8B3342 = TRUE;

// 0x8F3768
int CScreenConnection::dword_8F3768;

// 0x8F376C
BOOLEAN CScreenConnection::byte_8F376C;

// 0x5F9BB0
CScreenConnection::CScreenConnection()
{
    field_106 = 0;
    m_nSerialPort = 0;
    m_nSerialBaudRate = 0;
    m_dwLastSessionRefresh = 0;
    m_nErrorState = 0;
    m_nNumErrorButtons = 0;
    m_bAllowInput = FALSE;
    field_FB0 = 0;
    field_FA8 = 1;
    field_FA6 = 0;
    m_bIsNight = FALSE;

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

    // FIXME: Where is key 90?

    m_bCtrlKeyDown = FALSE;
    m_bShiftKeyDown = FALSE;
    m_bCapsLockKeyOn = FALSE;
    m_nProtocol = 0;
    m_nSessionIndex = -1;
    m_nModemAddress = -1;
    m_strErrorText = -1;
    m_strErrorButtonText[0] = -1;
    m_strErrorButtonText[1] = -1;
    field_496 = 0;
    m_bEliminateInitialize = FALSE;
    m_nEnumServiceProvidersCountDown = -1;
    m_bDirectPlayLobby = FALSE;
    m_bStartedCountDown = FALSE;
    field_498 = 0;
    field_499 = 0;
    field_49A = 0;
    field_49B = 0;
    field_49C = 0;
    field_4B6 = 0;
    m_bJoinWaiting = FALSE;
    m_bJoinComplete = FALSE;
    m_nJoinEvent = 0;
    m_nJoinErrorCode = CNetwork::ERROR_NONE;
    m_bJoinReturnValue = FALSE;
    m_bExitProgram = FALSE;
    field_FAC = 1;
    field_FB4 = 1;
    field_FB8 = 0;
    m_bPlayEndCredits = FALSE;
}

// 0x49FC40
BOOL CScreenConnection::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x5FA8B0
void CScreenConnection::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x49FC40
BOOL CScreenConnection::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x638D70
void CScreenConnection::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x638D80
BOOL CScreenConnection::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenConnection::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x638D90
void CScreenConnection::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x638DA0
BOOL CScreenConnection::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenConnection::CheckMouseMove()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenConnection::CheckMouseLButton()
{
    return TRUE;
}

// 0x49FC40
BOOL CScreenConnection::CheckMouseRButton()
{
    return TRUE;
}

// 0x6717F0
SHORT CScreenConnection::GetNumVirtualKeys()
{
    return CSCREENCONNECTION_VIRTUAL_KEYS;
}

// 0x5FA8D0
CKeyInfo* CScreenConnection::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x5FA8D0
BYTE* CScreenConnection::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x5FA910
CScreenConnection::~CScreenConnection()
{
}

// 0x5FAD80
void CScreenConnection::EngineDeactivated()
{
    field_4C0.Unload();
    field_9C0.Unload();

    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    if (dword_8F3768 == 2) {
        dword_8F3768 = 1;
    }
}

// 0x5FADD0
void CScreenConnection::EngineInitialized()
{
    m_cUIManager.fInit(this, CResRef("GUICONN"), g_pBaldurChitin->field_4A28);

    CPoint pt;
    if (g_pBaldurChitin->field_4A28) {
        pt.x = CVideo::SCREENWIDTH / 2 - CBaldurChitin::DEFAULT_SCREEN_WIDTH;
        pt.y = CVideo::SCREENHEIGHT / 2 - CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
    } else {
        pt.x = (CVideo::SCREENWIDTH - CBaldurChitin::DEFAULT_SCREEN_WIDTH) / 2;
        pt.y = (CVideo::SCREENHEIGHT - CBaldurChitin::DEFAULT_SCREEN_HEIGHT) / 2;
    }

    m_cUIManager.ShiftPanels(pt);

    for (int n = 0; n < 4; n++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->field_49B4[n]));
    }

    field_FA = 0;

    m_cUIManager.GetPanel(1)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(11)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(12)->SetActive(FALSE);
    m_cUIManager.GetPanel(21)->SetActive(FALSE);
    m_cUIManager.GetPanel(19)->SetActive(FALSE);
    m_cUIManager.GetPanel(20)->SetActive(FALSE);
    m_cUIManager.GetPanel(22)->SetActive(FALSE);
    m_cUIManager.GetPanel(23)->SetActive(FALSE);
    m_cUIManager.GetPanel(24)->SetActive(FALSE);
    m_cUIManager.GetPanel(25)->SetActive(FALSE);

    g_pChitin->cNetwork.m_nApplicationGuid = CBaldurChitin::GUID_BALDUR_GATE;
    g_pChitin->cNetwork.m_bApplicationGuidDefined = TRUE;
}

// 0x5FB020
void CScreenConnection::RenderTorch()
{
    CVidInf* pVidMode = static_cast<CVidInf*>(g_pChitin->GetCurrentVideoMode());

    if (!m_bIsNight) {
        return;
    }

    if (m_bPlayEndCredits == TRUE) {
        return;
    }

    if (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 729
    UTIL_ASSERT(pPanel != NULL);

    CPoint pt(106, 383);

    if (g_pBaldurChitin->field_4A28) {
        pt.x *= 2;
        pt.y *= 2;
    }

    CPoint origin = pPanel->m_ptOrigin + pt;

    CSize size;
    m_vcTorch.GetCurrentFrameSize(size, FALSE);

    CRect rTorch(origin, size);
    pVidMode->BKLock(rTorch);

    BOOL bResult = pVidMode->BKRender(&m_vcTorch,
        origin.x - rTorch.left,
        origin.y - rTorch.top,
        0x80,
        -1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 766
    UTIL_ASSERT(bResult);

    pVidMode->BKUnlock();
}

// 0x5FB280
void CScreenConnection::OnLButtonDblClk(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            m_cUIManager.OnLButtonDblClk(pt);
        }
    }
}

// 0x5FB2B0
void CScreenConnection::OnLButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
            m_cUIManager.OnLButtonDown(pt);
        }
    }
}

// 0x5FB2F0
void CScreenConnection::OnLButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
            m_cUIManager.OnLButtonUp(pt);
        }
    }
}

// 0x5FB330
void CScreenConnection::OnMouseMove(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            m_cUIManager.OnMouseMove(pt);
        }
    }
}

// 0x5FB360
void CScreenConnection::OnRButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 1;
            m_cUIManager.OnRButtonDown(pt);
        }
    }
}

// 0x5FB3A0
void CScreenConnection::OnRButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!field_49A) {
            g_pBaldurChitin->m_pObjectCursor->m_nState = 0;
            m_cUIManager.OnRButtonUp(pt);
        }
    }
}

// 0x5FB3E0
void CScreenConnection::TimerAsynchronousUpdate()
{
    if (m_bPlayEndCredits) {
        g_pBaldurChitin->m_pEngineProjector->PlayMovie(CResRef("END"));
        g_pBaldurChitin->m_pEngineProjector->PlayMovieNext(CResRef("CREDITS"));
        m_bPlayEndCredits = FALSE;
    }

    // TODO: Incomplete.
}

// 0x5FBEF0
void CScreenConnection::TimerSynchronousUpdate()
{
    if (m_bExitProgram) {
        pChitin->ShutDown(-1, NULL, NULL);
        return;
    }

    if (m_bEliminateInitialize == TRUE) {
        // TODO: Incomplete.
        // g_pChitin->cNetwork.RemoveInitializeConnection();
        m_bEliminateInitialize = FALSE;
    }

    if (field_49A != TRUE || field_498) {
        // TODO: Incomplete.

        if (m_bPlayEndCredits == TRUE) {
            g_pChitin->pActiveEngine->pVidMode->EraseScreen(CVIDINF_SURFACE_BACK, RGB(0, 0, 0));
        } else {
            m_cUIManager.Render();
        }

        pVidMode->Flip(TRUE);

        // TODO: Incomplete.
    }
}

// NOTE: Inlined.
void CScreenConnection::EnablePopupPanel(DWORD dwPanelId, BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 1718
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(dwPanelId);
}

// NOTE: Inlined.
void CScreenConnection::ShowPopupPanel(DWORD dwPanelId, BOOL bShow)
{
    CUIPanel* pSamePanel = m_cUIManager.GetPanel(dwPanelId);
    pSamePanel->SetActive(bShow);
    pSamePanel->SetInactiveRender(bShow);

    if (bShow) {
        pSamePanel->InvalidateRect(NULL);

        if (byte_8B3341) {
            PlayGUISound(RESREF_SOUND_WINDOWOPEN);
        }
    }
}

// 0x5FC080
void CScreenConnection::ResetPopupPanel(DWORD nID)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 1745
    UTIL_ASSERT(pPanel != NULL);

    switch (nID) {
    case 0:
        break;
    case 1:
        ResetProtocolPanel();
        break;
    case 3:
        ResetModemPanel();
        break;
    case 4:
        ResetSerialPanel();
        break;
    case 5:
        ResetTCPIPPanel();
        break;
    case 6:
        ResetCreateGamePanel();
        break;
    case 7:
        // TODO: Incomplete.
        break;
    case 8:
        ResetPlayerNamePanel();
        break;
    case 11:
        // TODO: Incomplete.
        break;
    case 12:
        // TODO: Incomplete.
        break;
    case 19:
    case 20:
    case 22:
        ResetErrorPanel(pPanel);
        break;
    case 21:
        // TODO: Incomplete.
        break;
    case 23:
        // TODO: Incomplete.
        break;
    case 24:
        // TODO: Incomplete.
        break;
    case 25:
        // TODO: Incomplete.
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 1812
        UTIL_ASSERT(FALSE);
    }
}

// 0x5FC3A0
void CScreenConnection::UpdatePopupPanel(DWORD nID)
{
    switch (nID) {
    case 1:
        UpdateProtocolPanel();
        break;
    case 3:
        UpdateModemPanel();
        break;
    case 4:
        UpdateSerialPanel();
        break;
    case 5:
        UpdateTCPIPPanel();
        break;
    case 6:
        // TODO: Incomplete.
        break;
    case 7:
        // TODO: Incomplete.
        break;
    case 8:
        // TODO: Incomplete.
        break;
    case 11:
        // TODO: Incomplete.
        break;
    case 12:
        // TODO: Incomplete.
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        break;
    case 24:
        // TODO: Incomplete.
        break;
    case 25:
        // TODO: Incomplete.
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 1893
        UTIL_ASSERT(FALSE);
    }
}

// 0x5FC6F0
void CScreenConnection::SummonPopup(DWORD nID)
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    if (!m_lPopupStack.IsEmpty()) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 1973
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, FALSE);
    } else {
        EnableMainPanel(FALSE);
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(nID);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 1979
    UTIL_ASSERT(pPanel != NULL);

    m_lPopupStack.AddTail(pPanel);
    ResetPopupPanel(pPanel->m_nID);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, TRUE);

    // NOTE: Uninline.
    EnablePopupPanel(pPanel->m_nID, TRUE);

    UpdatePopupPanel(pPanel->m_nID);
}

// 0x5FC850
void CScreenConnection::DismissPopup()
{
    if (m_cUIManager.m_pFocusedControl != NULL) {
        m_cUIManager.m_pFocusedControl->KillFocus();
        m_cUIManager.m_pFocusedControl = NULL;
    }

    CUIPanel* pPanel = m_lPopupStack.RemoveTail();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2024
    UTIL_ASSERT(pPanel != NULL);

    // NOTE: Uninline.
    ShowPopupPanel(pPanel->m_nID, FALSE);

    CUIPanel* pMainPanel = m_cUIManager.GetPanel(0);
    pMainPanel->InvalidateRect(NULL);

    if (m_lPopupStack.GetTailPosition() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2041
        UTIL_ASSERT(pPanel != NULL);

        // NOTE: Uninline.
        ShowPopupPanel(pPanel->m_nID, TRUE);

        // NOTE: Uninline.
        EnablePopupPanel(pPanel->m_nID, TRUE);

        UpdatePopupPanel(pPanel->m_nID);
    } else {
        EnableMainPanel(TRUE);
        UpdateMainPanel();
    }

    if (g_pBaldurChitin->field_1A0) {
        // FIXME: Unused.
        g_pChitin->GetWnd();

        if (g_pBaldurChitin->cImm.field_128) {
            g_pBaldurChitin->cImm.sub_7C2E10(g_pChitin->GetWnd()->GetSafeHwnd());
        }
    }
}

// 0x5FCA00
void CScreenConnection::sub_5FCA00(int a1)
{
    // TODO: Incomplete.
}

// 0x5FDB20
void CScreenConnection::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x5FE930
void CScreenConnection::OnCancelButtonClick()
{
    if (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();

        CSingleLock lock(&(GetManager()->field_36), 0);
        lock.Lock(INFINITE);

        switch (pPanel->m_nID) {
        case 0:
        case 1:
        case 19:
        case 21:
            break;
        case 7:
            m_nSessionIndex = -1;
            m_bEliminateInitialize = TRUE;
            DismissPopup();
            break;
        case 8:
            g_pChitin->cNetwork.CloseSession(TRUE);
            m_bEliminateInitialize = TRUE;
            DismissPopup();
            break;
        default:
            DismissPopup();
            break;
        }

        lock.Unlock();
    }
}

// 0x5FEA60
void CScreenConnection::OnJoinGameButtonClick()
{
    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3531
    UTIL_ASSERT(GetSessionIndex() != -1);

    pNetwork->SelectSession(m_nSessionIndex);

    pVidMode->m_bPointerEnabled = TRUE;

    if (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        DismissPopup();
    }

    if (pNetwork->GetPasswordRequiredForSelectedSession()) {
        SummonPopup(7);
    } else {
        pNetwork->field_680 = 0;
        m_bJoinWaiting = TRUE;
        m_bJoinComplete = FALSE;
        m_nJoinEvent = 8;
        m_nJoinErrorCode = CNetwork::ERROR_NONE;
        m_bJoinReturnValue = FALSE;
    }

    lock.Unlock();
}

// 0x5FED80
void CScreenConnection::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3751
    UTIL_ASSERT(pPanel != NULL);

    pPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    if (bEnable) {
        if (byte_8B3341) {
            PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
        }
    }
}

// 0x5FEE50
void CScreenConnection::UpdateMainPanel()
{
    // TODO: Incomplete.
}

// 0x5FF690
void CScreenConnection::UpdateProtocolPanel()
{
    // TODO: Incomplete.
}

// 0x5FF960
void CScreenConnection::UpdateSerialPanel()
{
    // TODO: Incomplete.
}

// 0x5FFB90
void CScreenConnection::UpdateModemPanel()
{
    // TODO: Incomplete.
}

// 0x5FFD20
void CScreenConnection::UpdateTCPIPPanel()
{
    // TODO: Incomplete.
}

// 0x5FFF60
void CScreenConnection::ResetProtocolPanel()
{
    // TODO: Incomplete.
}

// 0x600100
void CScreenConnection::ResetSerialPanel()
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    UINT nSerialPort = GetPrivateProfileIntA("Multiplayer",
        "Serial Port",
        1,
        g_pBaldurChitin->GetIniFileName());
    if (pNetwork->m_nSerialPort != nSerialPort) {
        pNetwork->SetSerialPort(nSerialPort);
    }

    UINT nSerialBaudRate = GetPrivateProfileIntA("Multiplayer",
        "Serial Baud",
        38400,
        g_pBaldurChitin->GetIniFileName());
    if (pNetwork->m_nSerialBaudRate != nSerialBaudRate) {
        pNetwork->SetSerialBaudRate(nSerialBaudRate);
    }

    m_nSerialPort = pNetwork->m_nSerialPort;
    m_nSerialBaudRate = pNetwork->m_nSerialBaudRate;
}

// 0x6001B0
void CScreenConnection::ResetModemPanel()
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    CString sModemSelected;
    CString sDefaultModem("");

    GetPrivateProfileStringA("Multiplayer",
        "Modem Selected",
        sDefaultModem,
        sModemSelected.GetBuffer(128),
        128,
        g_pBaldurChitin->GetIniFileName());

    if (sModemSelected.Compare("") != 0) {
        if (pNetwork->m_nModemAddress != -1) {
            pNetwork->UnselectModemAddress();
        }

        pNetwork->SelectModemAddress(pNetwork->FindModemAddress(sModemSelected));
    }

    // FIXME: Missing `ReleaseBuffer`.

    m_nModemAddress = pNetwork->m_nModemAddress;

    UpdateHelp(3, 7, 11317);
}

// 0x6002C0
void CScreenConnection::ResetTCPIPPanel()
{
    // TODO: Incomplete.
}

// 0x600370
void CScreenConnection::ResetCreateGamePanel()
{
    // TODO: Incomplete.
}

// 0x600470
void CScreenConnection::ResetPlayerNamePanel()
{
    // TODO: Incomplete.
}

// 0x600770
void CScreenConnection::StartConnection(BOOLEAN bDirectPlayLobby)
{
    m_bAllowInput = TRUE;
    m_nProtocol = 0;
    if (bDirectPlayLobby) {
        m_bDirectPlayLobby = bDirectPlayLobby;
    } else {
        m_nEnumServiceProvidersCountDown = 2;
        m_bStartedCountDown = 0;
        m_bEliminateInitialize = TRUE;
        m_dwLastSessionRefresh = GetTickCount();
    }

    if (g_pBaldurChitin->m_bIsAutoStarting) {
        m_bAllowInput = FALSE;
    }
}

// 0x6007E0
void CScreenConnection::SetEliminateInitialize(BOOLEAN bEliminateInitialize)
{
    m_bEliminateInitialize = bEliminateInitialize;
}

// 0x600920
void CScreenConnection::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 19:
        m_nNumErrorButtons = 0;
        break;
    case 20:
    case 23:
        m_nNumErrorButtons = 1;
        break;
    case 22:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 5523
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_strErrorText, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5536
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 5546
        UTIL_ASSERT(pButton != NULL);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x602060
void CScreenConnection::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, STRREF dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 6834
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 6836
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x6024A0
void CScreenConnection::sub_6024A0()
{
    CSingleLock lock(&(m_cUIManager.field_36));
    lock.Lock();
    DismissPopup();
    lock.Unlock();

    g_pBaldurChitin->cNetwork.CloseSession(TRUE);

    g_pBaldurChitin->m_pEngineStart->field_140 = 0;
    SelectEngine(g_pBaldurChitin->m_pEngineStart);
}

// 0x602550
void CScreenConnection::CancelEngine()
{
    while (m_lPopupStack.GetTailPosition() != NULL && m_lPopupStack.GetTail() != NULL) {
        CUIPanel* pPanel = m_lPopupStack.GetTail();
        switch (pPanel->m_nID) {
        case 19:
        case 21:
            DismissPopup();
            break;
        default:
            OnCancelButtonClick();
            break;
        }
    }
}

// 0x602590
CUIControlButtonConnectionGameMode::CUIControlButtonConnectionGameMode(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(15413, strRes); // "Single Player"
    SetText(strRes.szText);
}

// 0x602680
CUIControlButtonConnectionGameMode::~CUIControlButtonConnectionGameMode()
{
}

// 0x602720
void CUIControlButtonConnectionGameMode::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7173
    UTIL_ASSERT(pConnection != NULL);

    CUIManager* pManager = pConnection->GetManager();
    CSingleLock lock(&(pManager->field_36), TRUE);
    pConnection->SummonPopup(1);
    lock.Unlock();
}

// 0x6027D0
CUIControlButtonConnectionQuitGame::CUIControlButtonConnectionQuitGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13731, strRes); // "Quit Game"
    SetText(strRes.szText);
}

// 0x6028C0
CUIControlButtonConnectionQuitGame::~CUIControlButtonConnectionQuitGame()
{
}

// 0x602960
void CUIControlButtonConnectionQuitGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x602A90
CUIControlButtonConnectionNewGame::CUIControlButtonConnectionNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13963, strRes); // "New Game"
    SetText(strRes.szText);
}

// 0x602B80
CUIControlButtonConnectionNewGame::~CUIControlButtonConnectionNewGame()
{
}

// 0x602C20
void CUIControlButtonConnectionNewGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x602E10
CUIControlButtonConnectionQuickLoad::CUIControlButtonConnectionQuickLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(33508, strRes); // "Quick Load"
    SetText(strRes.szText);
}

// 0x602F00
CUIControlButtonConnectionQuickLoad::~CUIControlButtonConnectionQuickLoad()
{
}

// 0x602FA0
void CUIControlButtonConnectionQuickLoad::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7434
    UTIL_ASSERT(pConnection != NULL);

    pConnection->sub_5FCA00(1);
}

// 0x602FE0
CUIControlButtonConnectionLoadGame::CUIControlButtonConnectionLoadGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13729, strRes); // "Load Game"
    SetText(strRes.szText);
}

// 0x6030D0
CUIControlButtonConnectionLoadGame::~CUIControlButtonConnectionLoadGame()
{
}

// 0x603170
void CUIControlButtonConnectionLoadGame::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x603380
CUIControlButtonConnectionJoinGame::CUIControlButtonConnectionJoinGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13964, strRes); // "Join Game"
    SetText(strRes.szText);
}

// 0x603470
CUIControlButtonConnectionJoinGame::~CUIControlButtonConnectionJoinGame()
{
}

// 0x603510
void CUIControlButtonConnectionJoinGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7620
    UTIL_ASSERT(pConnection != NULL);

    if (g_pChitin->cNetwork.m_nServiceProvider != CNetwork::SERV_PROV_NULL
        && g_pBaldurChitin->cDimm.cResCache.m_nCacheSize < 175000000) {
        pConnection->m_nErrorState = 2;
        pConnection->m_strErrorText = 20692;
        pConnection->m_strErrorButtonText[0] = 11973;
        pConnection->SummonPopup(20);
    } else {
        CSingleLock lock(&(m_pPanel->m_pManager->field_36), TRUE);
        pConnection->m_nErrorState = 7;
        pConnection->m_strErrorText = 20624;
        pConnection->m_strErrorButtonText[0] = 20625;
        pConnection->m_strErrorButtonText[1] = 13727;
        pConnection->SummonPopup(22);
        lock.Unlock();
    }
}

// 0x603750
CUIControlButtonConnectionPopupDone::CUIControlButtonConnectionPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(11973, strRes); // "Done"
    SetText(strRes.szText);
}

// 0x603840
CUIControlButtonConnectionPopupDone::~CUIControlButtonConnectionPopupDone()
{
}

// 0x6038E0
void CUIControlButtonConnectionPopupDone::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7836
    UTIL_ASSERT(pConnection != NULL);

    pConnection->OnDoneButtonClick();
}

// 0x603920
CUIControlButtonConnectionPopupCancel::CUIControlButtonConnectionPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 1, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13727, strRes); // "Cancel"
    SetText(strRes.szText);
}

// 0x603A10
CUIControlButtonConnectionPopupCancel::~CUIControlButtonConnectionPopupCancel()
{
}

// 0x603AB0
void CUIControlButtonConnectionPopupCancel::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7836
    UTIL_ASSERT(pConnection != NULL);

    pConnection->OnCancelButtonClick();
}

// 0x605850
void CScreenConnection::ShowSessionTerminatedMessage()
{
    // TODO: Incomplete.
}

#include "CScreenConnection.h"

#include "CBaldurChitin.h"
#include "CBaldurProjector.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenCharacter.h"
#include "CScreenCreateChar.h"
#include "CScreenLoad.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSinglePlayer.h"
#include "CScreenStart.h"
#include "CScreenWorld.h"
#include "CUIControlScrollBar.h"
#include "CUIPanel.h"
#include "CUtil.h"
#include "CVidInf.h"

// 0x852E98
const BYTE CScreenConnection::DEFAULT_SESSION_NAME = 0;

// 0x852E99
const BYTE CScreenConnection::DEFAULT_SESSION_PASSWORD = 1;

// 0x852E9A
const BYTE CScreenConnection::DEFAULT_PLAYER_NAME = 2;

// 0x852E9B
const BYTE CScreenConnection::DEFAULT_TCP_IP_ADDRESS = 3;

// 0x852E9C
const BYTE CScreenConnection::DEFAULT_PHONE_NUMBER = 4;

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
    m_bEMSwapped = FALSE;
    m_bEMValue = FALSE;
    m_bEMWaiting = FALSE;
    m_nEMEvent = 0;
    m_nEMEventStage = 0;
    m_bEnumeratingAsynchronous = FALSE;
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

// 0x5FA9B0
void CScreenConnection::EngineActivated()
{
    g_pBaldurChitin->GetObjectGame()->field_366E = 0;

    m_preLoadFontRealms.SetResRef(CResRef("REALMS"), FALSE, TRUE);
    m_preLoadFontRealms.RegisterFont();

    m_preLoadFontStnSml.SetResRef(CResRef("STONESM2"), FALSE, TRUE);
    m_preLoadFontStnSml.RegisterFont();

    // NOTE: Uninline.
    m_vcTorch.SetResRef(CResRef("MMTRCHB"), g_pBaldurChitin->field_4A28, TRUE, TRUE);

    if (field_FA8) {
        DWORD dwSectorsPerCluster;
        DWORD dwBytesPerSector;
        DWORD dwNumberOfFreeClusters;
        DWORD dwTotalNumberOfClusters;
        if (GetDiskFreeSpaceA(NULL, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters)) {
            if (dwNumberOfFreeClusters * dwSectorsPerCluster < CBaldurChitin::MINIMUM_DRIVE_SECTORS
                || dwNumberOfFreeClusters * dwSectorsPerCluster < CBaldurChitin::MINIMUM_DRIVE_SPACE / dwBytesPerSector
                || !g_pBaldurChitin->cDimm.cResCache.IsCacheSpaceAvailable()) {
                g_pBaldurChitin->m_dwCloseConfirmationStrId = 10248;
                g_pBaldurChitin->m_dwCloseConfirmationFlags = 0x10;
                PostMessageA(g_pBaldurChitin->cWnd.GetSafeHwnd(), WM_CLOSE, 0, 0);
                field_FA8 = FALSE;
                return;
            }
        }
    }

    UpdateMainPanel();
    g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
    m_cUIManager.InvalidateRect(NULL);

    if (!m_bStartedCountDown && m_nEnumServiceProvidersCountDown == 2) {
        m_bStartedCountDown = TRUE;

        CSingleLock lock(&(m_cUIManager.field_36), FALSE);
        lock.Lock(INFINITE);

        if (byte_8B3340) {
            byte_8B3340 = FALSE;
            byte_8B3341 = FALSE;
        } else {
            byte_8B3341 = TRUE;
        }

        m_nErrorState = 5;

        // "Finding the network devices on this host..."
        m_strErrorText = 20275;
        SummonPopup(19);

        pVidMode->m_bPointerEnabled = FALSE;

        lock.Unlock();
    }

    CString v1;
    g_pChitin->cDimm.WriteSetUp(CString(".\\temp\\foo.bar"), v1);

    g_pBaldurChitin->GetTlkTable().m_override.CloseFiles();
    g_pBaldurChitin->GetTlkTable().OpenOverride(CString("temp/default.toh"), CString("temp/default.tot"));

    switch (dword_8F3768) {
    case 0:
        dword_8F3768 = 1;
        break;
    case 1:
        if (g_pBaldurChitin->cSoundMixer.GetSongPlaying() != 1) {
            g_pBaldurChitin->cSoundMixer.StopMusic(TRUE);
        }

        g_pBaldurChitin->cSoundMixer.StartSong(1, 2);

        dword_8F3768 = 2;
        break;
    default:
        g_pBaldurChitin->cSoundMixer.GetSongPlaying();

        if (g_pBaldurChitin->cSoundMixer.GetSongPlaying() != 1
            && g_pBaldurChitin->cSoundMixer.m_nCurrentSong != 1) {
            dword_8F3768 = 1;
        }
    }
}

// 0x5FAD80
void CScreenConnection::EngineDeactivated()
{
    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();

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

    for (int side = 0; side < 4; side++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->m_aBorderPanels[side]));
    }

    m_pCurrentScrollBar = NULL;

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

    if (GetTopPopup() != NULL) {
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

// 0x5FB160
void CScreenConnection::OnKeyDown(SHORT nKeysFlags)
{
    if (!m_bAllowInput) {
        return;
    }

    if (m_bEMWaiting) {
        return;
    }

    if (nKeysFlags > 0) {
        for (SHORT nKeyFlag = 0; nKeyFlag < nKeysFlags; nKeyFlag++) {
            switch (m_pVirtualKeysFlags[nKeyFlag]) {
            case VK_ESCAPE:
                if (GetTopPopup() != NULL) {
                    OnCancelButtonClick();
                }
                break;
            case VK_RETURN:
                if (GetTopPopup() != NULL) {
                    if (g_pBaldurChitin->field_1A0) {
                        // FIXME: Unused.
                        g_pChitin->GetWnd();
                        if (g_pBaldurChitin->cImm.field_128) {
                            m_cUIManager.OnKeyDown(VK_RETURN);
                        } else {
                            OnDoneButtonClick();
                        }
                    } else {
                        OnDoneButtonClick();
                    }
                }
                break;
            default:
                if (!m_cUIManager.OnKeyDown(m_pVirtualKeysFlags[nKeyFlag])) {
                    switch (m_pVirtualKeysFlags[nKeyFlag]) {
                    case VK_TAB:
                        m_cUIManager.ForceToolTip();
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

// 0x5FB280
void CScreenConnection::OnLButtonDblClk(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            m_cUIManager.OnLButtonDblClk(pt);
        }
    }
}

// 0x5FB2B0
void CScreenConnection::OnLButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
            m_cUIManager.OnLButtonDown(pt);
        }
    }
}

// 0x5FB2F0
void CScreenConnection::OnLButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
            m_cUIManager.OnLButtonUp(pt);
        }
    }
}

// 0x5FB330
void CScreenConnection::OnMouseMove(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            m_cUIManager.OnMouseMove(pt);
        }
    }
}

// 0x5FB360
void CScreenConnection::OnRButtonDown(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
            m_cUIManager.OnRButtonDown(pt);
        }
    }
}

// 0x5FB3A0
void CScreenConnection::OnRButtonUp(CPoint pt)
{
    if (m_bAllowInput) {
        if (!m_bEMWaiting) {
            g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
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

    if (field_FA8) {
        // TODO: Incomplete (detecting/switching CD).

        srand(static_cast<unsigned int>(time(NULL)));
        rand();

        field_FA8 = FALSE;
        field_FA6 = TRUE;

        UpdateMainPanel();
        m_cUIManager.InvalidateRect(NULL);

        g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
        g_pBaldurChitin->GetObjectCursor()->m_bVisible = TRUE;
        g_pBaldurChitin->GetObjectCursor()->SetCursor(100, FALSE);
        g_pBaldurChitin->GetObjectCursor()->m_bVisible = FALSE;
        g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

        CString sResolvedFileName;

        BOOL bHaveLogo = FALSE;
        if (g_pChitin->lAliases.ResolveFileName(CString("hd0:\\data\\bislogo.mve"), sResolvedFileName) == TRUE) {
            CFileFind fileFind;
            if (fileFind.FindFile(sResolvedFileName)) {
                bHaveLogo = TRUE;
                g_pBaldurChitin->m_pEngineProjector->PlayMovie(CResRef("BISLOGO"));
                g_pBaldurChitin->m_pEngineProjector->PlayMovieNext(CResRef("WOTC"));
                g_pBaldurChitin->m_pEngineProjector->PlayMovieNext(CResRef("NVIDIA"));
            }
        }

        BOOL bHaveIntro = FALSE;
        if (g_pChitin->lAliases.ResolveFileName(CString("hd0:\\data\\intro.mve"), sResolvedFileName) == TRUE) {
            CFileFind fileFind;
            if (fileFind.FindFile(sResolvedFileName)) {
                bHaveIntro = TRUE;
            }
        }

        if (!bHaveIntro) {
            if (g_pChitin->lAliases.ResolveFileName(CString("cd2:\\data\\Intro.mve"), sResolvedFileName) == TRUE) {
                CFileFind fileFind;
                if (fileFind.FindFile(sResolvedFileName)) {
                    bHaveIntro = TRUE;
                }
            }
        }

        if (bHaveIntro) {
            if (!bHaveLogo) {
                g_pBaldurChitin->m_pEngineProjector->PlayMovie(CResRef("INTRO"));
            } else {
                g_pBaldurChitin->m_pEngineProjector->PlayMovieNext(CResRef("INTRO"));
            }
        }

        if (bHaveLogo || bHaveIntro) {
            byte_8F376C = TRUE;
        } else {
            byte_8F376C = FALSE;
        }
    }

    if (m_bDirectPlayLobby) {
        AutoStartDirectPlayLobby();
        m_bDirectPlayLobby = FALSE;
        return;
    }

    if (m_nEnumServiceProvidersCountDown == 0) {
        CSingleLock lock(&(m_cUIManager.field_36), FALSE);
        lock.Lock(INFINITE);
        if (!byte_8F376C) {
            DismissPopup();
        }
        lock.Unlock();

        UpdateMainPanel();

        m_nEnumServiceProvidersCountDown--;
        pVidMode->m_bPointerEnabled = TRUE;

        if (g_pBaldurChitin->m_bIsAutoStarting) {
            g_pBaldurChitin->m_bIsAutoStarting = FALSE;
            m_bAllowInput = TRUE;
            AutoSelectServiceProvider();
            UpdateMainPanel();
        } else {
            if (g_pBaldurChitin->field_110) {
                if (g_pChitin->field_131) {
                    WritePrivateProfileStringA("GameSpy",
                        "Location",
                        g_pChitin->GetStartUpGameSpyLocation(),
                        g_pBaldurChitin->GetIniFileName());
                }

                if (AutoStartInitialize()) {
                    UpdateMainPanel();
                }

                g_pBaldurChitin->m_bIsAutoStarting = FALSE;
                m_bAllowInput = TRUE;
            } else {
                if (g_pBaldurChitin->m_bStartUpConnect || g_pBaldurChitin->field_130) {
                    if (g_pBaldurChitin->m_bStartUpConnect) {
                        AutoStartConnect();
                    }
                } else {
                    g_pBaldurChitin->m_bIsAutoStarting = FALSE;
                    m_bAllowInput = TRUE;
                    AutoSelectServiceProvider();
                    UpdateMainPanel();
                }
            }
        }
    }

    if (m_bJoinWaiting == TRUE && m_bJoinComplete == TRUE) {
        m_bJoinComplete = FALSE;
        m_bJoinWaiting = FALSE;
        HandleJoinCompletion(m_nJoinEvent);
    }

    if (m_bEMWaiting == TRUE) {
        if (m_bEMSwapped == TRUE) {
            m_bEMWaiting = FALSE;
            HandleEMEvent(m_nEMEvent, m_nEMEventStage);
        }
    } else {
        if (m_lPopupStack.GetTailPosition() != NULL) {
            CUIPanel* pPanel = m_lPopupStack.GetTail();
            if (pPanel != NULL) {
                if (pPanel->m_nID == 11 || pPanel->m_nID == 5) {
                    if (GetTickCount() - m_dwLastSessionRefresh > 5000) {
                        CString sValue;
                        GetPrivateProfileStringA("Multiplayer",
                            "AsyncEnumeration",
                            "0",
                            sValue.GetBuffer(128),
                            128,
                            g_pBaldurChitin->GetIniFileName());

                        if (sValue.Compare("1") == 0 || pPanel->m_nID == 11) {
                            BOOL v1;
                            if (g_pChitin->cNetwork.m_bConnectionInitialized) {
                                v1 = TRUE;
                            } else {
                                g_pChitin->cNetwork.m_sIPAddress = CString("");
                                v1 = g_pChitin->cNetwork.InitializeConnectionToServiceProvider(FALSE);
                            }

                            if (v1) {
                                m_bEnumeratingAsynchronous = TRUE;

                                if (g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                                    g_pChitin->cNetwork.EnumerateSessions(TRUE, FALSE);
                                }

                                UpdatePopupPanel(pPanel->m_nID);
                                m_dwLastSessionRefresh = GetTickCount();
                            }
                        }
                    }
                }

                if (pPanel->m_nID == 21) {
                    if (g_pChitin->cNetwork.MakePlayersVisible() == 1) {
                        g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
                    }
                }
            }
        }

        if (field_FA6) {
            field_FA6 = FALSE;
            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, TRUE);
            g_pBaldurChitin->GetObjectCursor()->m_bVisible = TRUE;
        }

        UpdateCursorShape(0);

        m_cUIManager.TimerAsynchronousUpdate();
        g_pBaldurChitin->GetObjectCursor()->CursorUpdate(pVidMode);

        if (m_bExitProgram) {
            // TODO: Incomplete.
        }
    }
}

// 0x5FBEF0
void CScreenConnection::TimerSynchronousUpdate()
{
    if (m_bExitProgram) {
        pChitin->ShutDown(-1, NULL, NULL);
        return;
    }

    if (m_bEliminateInitialize == TRUE) {
        g_pChitin->cNetwork.RemoveInitializeConnection();
        m_bEliminateInitialize = FALSE;
    }

    if (m_bEMWaiting == TRUE && !m_bEMSwapped) {
        g_pChitin->cVideo.SetExclusiveMode(m_bEMValue);
        m_bEMSwapped = TRUE;
        return;
    }

    if (m_bJoinWaiting == TRUE && !m_bJoinComplete) {
        INT nErrorCode = CNetwork::ERROR_NONE;
        BOOLEAN bResult = g_pChitin->cNetwork.JoinSelectedSession(nErrorCode);
        m_nJoinErrorCode = nErrorCode;
        m_bJoinReturnValue = bResult;
        m_bJoinComplete = TRUE;
    }

    if (m_nEnumServiceProvidersCountDown >= 1) {
        if (m_nEnumServiceProvidersCountDown == 1) {
            g_pChitin->cNetwork.EnumerateServiceProviders();
        }
        m_nEnumServiceProvidersCountDown--;
    }

    if (m_bPlayEndCredits == TRUE) {
        g_pChitin->pActiveEngine->pVidMode->EraseScreen(CVIDINF_SURFACE_BACK, RGB(0, 0, 0));
    } else {
        m_cUIManager.Render();
    }

    pVidMode->Flip(TRUE);

    RenderTorch();

    if (m_bIsNight) {
        if (GetTopPopup() == NULL) {
            SHORT nCurrentFrame = m_vcTorch.m_nCurrentFrame;
            SHORT nCurrentSequence = m_vcTorch.m_nCurrentSequence;
            if (nCurrentFrame + 1 < m_vcTorch.GetSequenceLength(nCurrentSequence, FALSE)) {
                m_vcTorch.FrameAdvance();
            } else {
                m_vcTorch.FrameSet(0);
            }
        }
    }
}

// NOTE: Inlined.
CUIPanel* CScreenConnection::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
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
        // NOTE: Uninline.
        ResetPasswordPanel();
        break;
    case 8:
        ResetPlayerNamePanel();
        break;
    case 11:
        // NOTE: Uninline.
        ResetIPXPanel();
        break;
    case 12:
        // NOTE: Uninline.
        ResetPhoneNumberPanel();
        break;
    case 19:
    case 20:
    case 22:
        ResetErrorPanel(pPanel);
        break;
    case 21:
        // NOTE: Uninline.
        ResetLobbyPanel();
        break;
    case 23:
        ResetVersionMismatchPanel(pPanel);
        break;
    case 24:
        // NOTE: Uninline.
        ResetMissionPackPanel();
        break;
    case 25:
        ResetImportPanel();
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
        // NOTE: Uninline.
        UpdateCreateGamePanel();
        break;
    case 7:
        // NOTE: Uninline.
        UpdatePasswordPanel();
        break;
    case 8:
        // NOTE: Uninline.
        UpdatePlayerNamePanel();
        break;
    case 11:
        // NOTE: Uninline.
        UpdateIPXPanel();
        break;
    case 12:
        // NOTE: Uninline.
        UpdatePhoneNumberPanel();
        break;
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
        break;
    case 24:
        UpdateMissionPackPanel();
        break;
    case 25:
        // NOTE: Uninline.
        UpdateImportPanel();
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
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

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
    // NOTE: Uninline.
    m_cUIManager.KillCapture();

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
void CScreenConnection::OnLoadGameButtonClick(BOOL bQuick)
{
    CUIControlEdit* pEdit;
    CString sSessionName;
    CString sPassword;
    CString sPlayerName;

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(6);

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2102
    UTIL_ASSERT(pSettings != NULL);

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2105
    UTIL_ASSERT(pEdit != NULL);

    sSessionName = pEdit->GetText();
    sSessionName.TrimLeft();
    sSessionName.TrimRight();

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(4));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2111
    UTIL_ASSERT(pEdit != NULL);

    sPassword = pEdit->GetText();
    sPassword.TrimLeft();
    sPassword.TrimRight();

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2117
    UTIL_ASSERT(pEdit != NULL);

    sPlayerName = pEdit->GetText();
    sPlayerName.TrimLeft();
    sPlayerName.TrimRight();

    renderLock.Unlock();

    if (m_nProtocol != 0) {
        WritePrivateProfileStringA("Multiplayer",
            "Player Name",
            sPlayerName,
            g_pBaldurChitin->GetIniFileName());

        WritePrivateProfileStringA("Multiplayer",
            "Session Password",
            sPassword,
            g_pBaldurChitin->GetIniFileName());

        WritePrivateProfileStringA("Multiplayer",
            "Session Name",
            sSessionName,
            g_pBaldurChitin->GetIniFileName());
    } else {
        if (sPlayerName.IsEmpty()) {
            sPlayerName = "Player";
        }

        if (sSessionName.IsEmpty()) {
            sSessionName = "Session";
        }
    }

    if (!pNetwork->m_bConnectionInitialized) {
        pNetwork->InitializeConnectionToServiceProvider(TRUE);
        if (!pNetwork->m_bConnectionInitialized) {
            m_nErrorState = 1;
            m_strErrorText = 18986;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(20);
            return;
        }
    }

    pNetwork->m_sSessionNameToMake = sSessionName;
    pNetwork->m_bSessionNameToMake = TRUE;

    if (sPassword != "") {
        pNetwork->m_sSessionPassword = sPassword;
        pNetwork->m_bSessionPasswordEnabled = TRUE;
    } else {
        pNetwork->m_bSessionPasswordEnabled = FALSE;
    }

    pNetwork->SetMaxPlayers(CMultiplayerSettings::MAX_PLAYERS);
    pNetwork->SetApplicationOptions(TRUE, FALSE);
    pNetwork->m_sLocalPlayerName = sPlayerName;
    pNetwork->m_bPlayerNameToMake = TRUE;

    INT nServiceProviderType;
    pNetwork->GetServiceProviderType(pNetwork->m_nServiceProvider, nServiceProviderType);
    if (nServiceProviderType == CNetwork::SERV_PROV_MODEM
        || nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
        m_bEMSwapped = FALSE;
        m_bEMValue = FALSE;
        m_bEMWaiting = TRUE;
        m_nEMEvent = 0;
        m_nEMEventStage = 1;
    } else {
        if (pNetwork->HostNewSession()) {
            INT nErrorCode;
            if (pNetwork->CreatePlayer(nErrorCode)) {
                CSingleLock renderLock(&(GetManager()->field_36), FALSE);
                renderLock.Lock(INFINITE);

                if (m_nProtocol != 0) {
                    DismissPopup();
                }

                renderLock.Unlock();

                pSettings->InitializeSettings();

                for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
                    pSettings->SetCharacterControlledByPlayer(nCharacterSlot, 0, TRUE, FALSE);
                }

                pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, TRUE, TRUE);

                if (bQuick) {
                    QuickLoadGame();

                    // NOTE: Uninline.
                    GetManager()->KillCapture();

                    SelectEngine(g_pBaldurChitin->m_pEngineWorld);
                } else {
                    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
                    // __LINE__: 2257
                    UTIL_ASSERT(pLoad != NULL);

                    pLoad->StartLoad(1);
                    SelectEngine(pLoad);

                    g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();
                    pSettings->SetArbitrationLockAllowInput(FALSE);
                    pSettings->SetArbitrationLockStatus(TRUE, 0);
                }
            } else {
                pNetwork->CloseSession(TRUE);
                m_bEliminateInitialize = TRUE;
            }
        } else {
            m_bEliminateInitialize = TRUE;
        }
    }
}

// 0x5FCF80
void CScreenConnection::QuickLoadGame()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2295
    UTIL_ASSERT(pGame != NULL);

    BOOL bExists = FALSE;
    if (pGame->SaveGameExists(CInfGame::QUICK_SAVE_NAME)) {
        pGame->m_sSaveGame = CInfGame::QUICK_SAVE_NAME;
        CScreenCharacter::SAVE_NAME = CInfGame::QUICK_SAVE_NAME;
        bExists = TRUE;
    } else if (pGame->SaveGameExists(CInfGame::QUICK_SAVE_BACKUP_NAME)) {
        pGame->m_sSaveGame = CInfGame::QUICK_SAVE_BACKUP_NAME;
        CScreenCharacter::SAVE_NAME = CInfGame::QUICK_SAVE_BACKUP_NAME;
        bExists = TRUE;
    }

    if (bExists) {
        pGame->LoadGame(TRUE, FALSE);
        pGame->MultiplayerSetCharacterCreationLocation();
        pGame->SetupCharacters(FALSE);

        for (INT nSlot = 0; nSlot < 6; nSlot++) {
            if (pGame->GetCharacterId(nSlot) == CGameObjectArray::INVALID_INDEX) {
                pGame->GetMultiplayerSettings()->SignalCharacterStatus(nSlot,
                    CMultiplayerSettings::CHARSTATUS_SIGNAL_DELETED,
                    TRUE,
                    TRUE);
            } else {
                pGame->GetMultiplayerSettings()->SignalCharacterStatus(nSlot,
                    CMultiplayerSettings::CHARSTATUS_SIGNAL_IMPORTED,
                    TRUE,
                    TRUE);
            }
        }
    } else {
        m_nErrorState = 10;
        m_strErrorText = 37437;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(20);
    }
}

// 0x5FD0A0
void CScreenConnection::OnNewGameButtonClick()
{
    CString sSessionName;
    CString sSessionPassword;
    CString sPlayerName;

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(6);

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2380
    UTIL_ASSERT(pSettings != NULL);

    CUIControlEdit* pEdit;

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2383
    UTIL_ASSERT(pEdit != NULL);

    sSessionName = pEdit->GetText();
    sSessionName.TrimLeft();
    sSessionName.TrimRight();

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(4));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2389
    UTIL_ASSERT(pEdit != NULL);

    sSessionPassword = pEdit->GetText();
    sSessionPassword.TrimLeft();
    sSessionPassword.TrimRight();

    pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2389
    UTIL_ASSERT(pEdit != NULL);

    sPlayerName = pEdit->GetText();
    sPlayerName.TrimLeft();
    sPlayerName.TrimRight();

    renderLock.Unlock();

    if (m_nProtocol != 0) {
        WritePrivateProfileStringA("Multiplayer",
            "Player Name",
            sPlayerName,
            g_pBaldurChitin->GetIniFileName());

        WritePrivateProfileStringA("Multiplayer",
            "Session Password",
            sSessionPassword,
            g_pBaldurChitin->GetIniFileName());

        WritePrivateProfileStringA("Multiplayer",
            "Session Name",
            sSessionName,
            g_pBaldurChitin->GetIniFileName());

    } else {
        if (sPlayerName.IsEmpty()) {
            sPlayerName = "Player";
        }

        if (sSessionName.IsEmpty()) {
            sSessionName = "Session";
        }
    }

    if (!pNetwork->m_bConnectionInitialized) {
        pNetwork->InitializeConnectionToServiceProvider(TRUE);
        if (!pNetwork->m_bConnectionInitialized) {
            m_nErrorState = 1;
            m_strErrorText = 18986;
            m_strErrorButtonText[0] = 11973;
            SummonPopup(20);
            return;
        }
    }

    pNetwork->m_sSessionNameToMake = sSessionName;
    pNetwork->m_bSessionNameToMake = TRUE;

    if (sSessionPassword != "") {
        pNetwork->m_sSessionPassword = sSessionPassword;
        pNetwork->m_bSessionPasswordEnabled = TRUE;
    } else {
        pNetwork->m_bSessionPasswordEnabled = FALSE;
    }

    pNetwork->SetMaxPlayers(6);
    pNetwork->SetApplicationOptions(TRUE, FALSE);
    pNetwork->m_sLocalPlayerName = sPlayerName;
    pNetwork->m_bPlayerNameToMake = TRUE;

    INT nServiceProviderType;
    pNetwork->GetServiceProviderType(pNetwork->m_nServiceProvider, nServiceProviderType);
    if (nServiceProviderType == CNetwork::SERV_PROV_MODEM
        || nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
        m_bEMSwapped = FALSE;
        m_bEMValue = FALSE;
        m_bEMWaiting = TRUE;
        m_nEMEvent = 1;
        m_nEMEventStage = 1;
    } else {
        if (pNetwork->HostNewSession()) {
            INT nErrorCode;
            if (pNetwork->CreatePlayer(nErrorCode)) {
                CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
                renderLock.Lock(INFINITE);

                if (m_nProtocol != 0) {
                    DismissPopup();
                }

                renderLock.Unlock();

                pSettings->InitializeSettings();

                for (int nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
                    pSettings->SetCharacterControlledByPlayer(nCharacterSlot, 0, TRUE, FALSE);
                }

                pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, TRUE, TRUE);

                g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

                CResRef cResArea;
                CString sAreaName;
                CPoint pt;
                g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartArea(cResArea, pt);
                cResArea.CopyToString(sAreaName);

                CPoint ptStart = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartPoint(0);
                pSettings->SetCharacterCreationLocation(sAreaName, ptStart);

                g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();

                if (g_pChitin->cNetwork.m_nServiceProvider == CNetwork::SERV_PROV_NULL) {
                    CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;
                    pSinglePlayer->field_45C = 1;
                    pSinglePlayer->StartSinglePlayer(1);
                    SelectEngine(pSinglePlayer);
                } else {
                    CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;
                    pMultiPlayer->field_45C = 1;
                    pMultiPlayer->StartMultiPlayer(1);
                    SelectEngine(pMultiPlayer);
                }

                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetArbitrationLockStatus(TRUE, 0);
            } else {
                pNetwork->CloseSession(TRUE);
                m_bEliminateInitialize = TRUE;
            }
        } else {
            m_bEliminateInitialize = TRUE;
        }
    }
}

// 0x5FD670
BOOL CScreenConnection::IsDoneButtonClickable()
{
    CUIControlEdit* pEdit;

    CUIPanel* pPanel = GetTopPopup();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2581
    UTIL_ASSERT(pPanel != NULL);

    CString sSessionName;
    CString sPlayerName;
    CString sPassword;
    CString sPhoneNumber;
    CString sAddress;

    switch (pPanel->m_nID) {
    case 1:
    case 4:
    case 19:
    case 20:
    case 21:
    case 22:
    case 24:
    case 25:
        return TRUE;
    case 3:
        return m_nModemAddress != -1;
    case 5:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2657
        UTIL_ASSERT(pEdit != NULL);

        sAddress = pEdit->GetText();
        sAddress.TrimLeft();
        sAddress.TrimRight();

        return m_nSessionIndex != -1 || sAddress != "";
    case 6:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2615
        UTIL_ASSERT(pEdit != NULL);

        sSessionName = pEdit->GetText();
        sSessionName.TrimLeft();
        sSessionName.TrimRight();

        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2620
        UTIL_ASSERT(pEdit != NULL);

        sPlayerName = pEdit->GetText();
        sPlayerName.TrimLeft();
        sPlayerName.TrimRight();

        if (m_nProtocol == 0) {
            sSessionName = "Single Player";
            sPlayerName = "Player";
        }

        return sSessionName != "" && sPlayerName != "";
    case 7:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(2));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2615
        UTIL_ASSERT(pEdit != NULL);

        sPassword = pEdit->GetText();
        sPassword.TrimLeft();
        sPassword.TrimRight();

        return sPassword != "";
    case 8:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(5));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2648
        UTIL_ASSERT(pEdit != NULL);

        sPlayerName = pEdit->GetText();
        sPlayerName.TrimLeft();
        sPlayerName.TrimRight();

        return sPlayerName != "";
    case 11:
        return m_nSessionIndex != -1;
    case 12:
        pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2670
        UTIL_ASSERT(pEdit != NULL);

        sPhoneNumber = pEdit->GetText();
        sPhoneNumber.TrimLeft();
        sPhoneNumber.TrimRight();

        return sPhoneNumber != "";
    }

    return FALSE;
}

// 0x5FDB20
void CScreenConnection::OnDoneButtonClick()
{
    CString sPassword;
    CString sPlayerName;
    CString sAddress;
    CString sPhoneNumber;

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 2735
    UTIL_ASSERT(pSettings != NULL);

    CUIPanel* pPanel = GetTopPopup();
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    if (pPanel == NULL) {
        return;
    }

    switch (pPanel->m_nID) {
    case 19:
    case 20:
    case 22:
        OnErrorButtonClick(0);
        return;
    case 23:
        DismissPopup();
        return;
    }

    if (!IsDoneButtonClickable()) {
        return;
    }

    if (pPanel->m_nID == 1) {
        renderLock.Lock(INFINITE);

        INT nSelectedServiceProviderType;
        switch (m_nProtocol) {
        case 0:
            nSelectedServiceProviderType = CNetwork::SERV_PROV_NULL;
            break;
        case 1:
            nSelectedServiceProviderType = CNetwork::SERV_PROV_IPX;
            break;
        case 2:
            nSelectedServiceProviderType = CNetwork::SERV_PROV_TCP_IP;
            break;
        case 3:
            nSelectedServiceProviderType = CNetwork::SERV_PROV_MODEM;
            break;
        case 4:
            nSelectedServiceProviderType = CNetwork::SERV_PROV_SERIAL;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 2801
            UTIL_ASSERT(FALSE);
        }

        if (nSelectedServiceProviderType == CNetwork::SERV_PROV_NULL) {
            pNetwork->SelectServiceProvider(0);

            CString sLastProtocolUsed;
            sLastProtocolUsed.Format("%d", m_nProtocol);

            WritePrivateProfileStringA("Multiplayer",
                "Last Protocol Used",
                sLastProtocolUsed,
                g_pBaldurChitin->GetIniFileName());

            DismissPopup();
        } else {
            for (INT nIndex = 0; nIndex < pNetwork->m_nTotalServiceProviders; nIndex++) {
                INT nServiceProviderType;
                pNetwork->GetServiceProviderType(nIndex, nServiceProviderType);

                if (nServiceProviderType == nSelectedServiceProviderType) {
                    pNetwork->SelectServiceProvider(nIndex);

                    CString sLastProtocolUsed;
                    sLastProtocolUsed.Format("%d", m_nProtocol);

                    WritePrivateProfileStringA("Multiplayer",
                        "Last Protocol Used",
                        sLastProtocolUsed,
                        g_pBaldurChitin->GetIniFileName());

                    DismissPopup();
                }
            }
        }

        if (pNetwork->m_bConnectionInitialized == TRUE && m_bEnumeratingAsynchronous == TRUE) {
            pNetwork->sub_7A61D0();
            m_bEliminateInitialize = TRUE;
        }

        renderLock.Unlock();
    } else if (pPanel->m_nID == 3) {
        renderLock.Lock(INFINITE);

        pNetwork->SelectModemAddress(m_nModemAddress);

        CString sModemAddress;
        pNetwork->GetModemAddress(m_nModemAddress, sModemAddress);

        WritePrivateProfileStringA("Multiplayer",
            "Modem Selected",
            sModemAddress,
            g_pBaldurChitin->GetIniFileName());

        DismissPopup();

        renderLock.Unlock();
    } else if (pPanel->m_nID == 4) {
        renderLock.Lock(INFINITE);

        CString sValue;

        pNetwork->SetSerialPort(m_nSerialPort);
        pNetwork->SetSerialBaudRate(m_nSerialBaudRate);

        sValue.Format("%d", m_nSerialPort);
        WritePrivateProfileStringA("Multiplayer",
            "Serial Port",
            sValue,
            g_pBaldurChitin->GetIniFileName());

        sValue.Format("%d", m_nSerialBaudRate);
        WritePrivateProfileStringA("Multiplayer",
            "Serial Baud",
            sValue,
            g_pBaldurChitin->GetIniFileName());

        DismissPopup();

        renderLock.Unlock();
    } else if (pPanel->m_nID == 5) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 3054
        UTIL_ASSERT(pEdit != NULL);

        if (pEdit->GetText().GetLength() > 0) {
            if (IsValidAddress(pEdit->GetText())) {
                renderLock.Lock(INFINITE);

                DismissPopup();

                m_nErrorState = 4;
                m_strErrorText = 20274;
                SummonPopup(19);

                pVidMode->m_bPointerEnabled = FALSE;
                renderLock.Unlock();

                if (m_bEnumeratingAsynchronous == TRUE) {
                    pNetwork->sub_7A61D0();
                    m_bEliminateInitialize = TRUE;
                }

                g_pChitin->m_bDisplayStale = TRUE;
                g_pBaldurChitin->GetObjectGame()->sub_59FA00(TRUE);

                renderLock.Lock(INFINITE);

                sAddress = pEdit->GetText();
                sAddress.TrimLeft();
                sAddress.TrimRight();

                renderLock.Unlock();

                pNetwork->m_sIPAddress = sAddress;
                pNetwork->InitializeConnectionToServiceProvider(TRUE);

                WritePrivateProfileStringA("Multiplayer",
                    "TCP/IP Address",
                    sAddress,
                    g_pBaldurChitin->GetIniFileName());

                m_bEMSwapped = FALSE;
                m_bEMValue = FALSE;
                m_bEMWaiting = TRUE;
                m_nEMEvent = 2;
                m_nEMEventStage = 1;
            } else {
                renderLock.Lock(INFINITE);

                m_nErrorState = 8;
                m_strErrorText = 20681;
                m_strErrorButtonText[0] = 11973;
                SummonPopup(20);

                renderLock.Unlock();
            }
        } else {
            renderLock.Lock(INFINITE);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 3149
            UTIL_ASSERT(GetSessionIndex() != -1);

            pNetwork->SelectSession(m_nSessionIndex);

            DismissPopup();

            renderLock.Unlock();

            OnJoinGameButtonClick();
        }
    } else if (pPanel->m_nID == 7) {
        renderLock.Lock(INFINITE);

        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(2));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2903
        UTIL_ASSERT(pEdit != NULL);

        sPassword = pEdit->GetText();
        sPassword.TrimLeft();
        sPassword.TrimRight();

        WritePrivateProfileStringA("Multiplayer",
            "Session Password",
            sPassword,
            g_pBaldurChitin->GetIniFileName());

        if (sPassword != "") {
            pNetwork->m_sSessionPassword = sPassword;
            pNetwork->m_bSessionPasswordEnabled = TRUE;
        } else {
            pNetwork->m_bSessionPasswordEnabled = FALSE;
        }

        m_bJoinWaiting = TRUE;
        m_bJoinComplete = FALSE;
        m_nJoinEvent = 9;
        m_nJoinErrorCode = 0;
        m_bJoinReturnValue = FALSE;

        renderLock.Unlock();
    } else if (pPanel->m_nID == 8) {
        renderLock.Lock(INFINITE);

        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(5));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 2977
        UTIL_ASSERT(pEdit != NULL);

        sPlayerName = pEdit->GetText();
        sPlayerName.TrimLeft();
        sPlayerName.TrimRight();

        WritePrivateProfileStringA("Multiplayer",
            "Player Name",
            sPassword,
            g_pBaldurChitin->GetIniFileName());

        pNetwork->EnumeratePlayers(FALSE);
        pNetwork->m_sLocalPlayerName = sPlayerName;
        pNetwork->m_bPlayerNameToMake = TRUE;

        INT nErrorCode;
        if (pNetwork->CreatePlayer(nErrorCode)) {
            pSettings->InitializeSettings();
            pSettings->m_bFirstConnected = TRUE;
            pSettings->SetPlayerReady(pNetwork->m_idLocalPlayer, FALSE, TRUE);

            DismissPopup();

            renderLock.Unlock();

            g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

            renderLock.Lock();

            if (pNetwork->GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
                CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;
                pSinglePlayer->field_45C = 1;
                pSinglePlayer->StartSinglePlayer(1);
                SelectEngine(pSinglePlayer);
            } else {
                CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;
                pMultiPlayer->field_45C = 1;
                pMultiPlayer->StartMultiPlayer(1);
                SelectEngine(pMultiPlayer);
            }
        } else {
            if (nErrorCode == CNetwork::ERROR_CANNOTCONNECT) {
                m_nErrorState = 1;
                m_strErrorText = 18986;
            } else if (nErrorCode == CNetwork::ERROR_PLAYEREXISTS) {
                m_nErrorState = 2;
                m_strErrorText = 18987;
            } else {
                m_nErrorState = 2;
                m_strErrorText = 17193;
            }

            m_strErrorButtonText[0] = 11973;
            SummonPopup(20);
        }

        renderLock.Unlock();
    } else if (pPanel->m_nID == 11) {
        renderLock.Lock(INFINITE);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 3165
        UTIL_ASSERT(GetSessionIndex() != -1);

        pNetwork->SelectSession(m_nSessionIndex);

        DismissPopup();

        m_nErrorState = 4;
        m_strErrorText = 20273;
        SummonPopup(19);

        pVidMode->m_bPointerEnabled = FALSE;
        renderLock.Unlock();

        g_pChitin->m_bDisplayStale = TRUE;
        g_pBaldurChitin->GetObjectGame()->sub_59FA00(TRUE);

        OnJoinGameButtonClick();
    } else if (pPanel->m_nID == 12) {
        renderLock.Lock(INFINITE);

        DismissPopup();

        m_nErrorState = 3;
        m_strErrorText = 20273;
        SummonPopup(19);

        pVidMode->m_bPointerEnabled = FALSE;
        renderLock.Unlock();

        g_pChitin->m_bDisplayStale = TRUE;
        g_pBaldurChitin->GetObjectGame()->sub_59FA00(TRUE);

        renderLock.Lock(INFINITE);

        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 3210
        UTIL_ASSERT(pEdit != NULL);

        sPhoneNumber = pEdit->GetText();
        sPhoneNumber.TrimLeft();
        sPhoneNumber.TrimRight();

        renderLock.Unlock();

        pNetwork->m_sPhoneNumber = sPhoneNumber;
        pNetwork->InitializeConnectionToServiceProvider(FALSE);

        WritePrivateProfileStringA("Multiplayer",
            "Phone Number",
            sPhoneNumber,
            g_pBaldurChitin->GetIniFileName());

        m_bEMSwapped = FALSE;
        m_bEMValue = FALSE;
        m_bEMWaiting = TRUE;
        m_nEMEvent = 2;
        m_nEMEventStage = 1;
    } else if (pPanel->m_nID == 24) {
        // NOTE: Likely some inlining.
        CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

        if (pConnection->m_nProtocol == 0) {
            switch (field_FB4) {
            case 1:
                pConnection->field_106 = 0;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = FALSE;
                g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
                pConnection->OnNewGameButtonClick();
                break;
            case 2:
                pConnection->field_106 = 0;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = TRUE;
                DismissPopup();
                SummonPopup(25);
                break;
            case 3:
                pConnection->field_106 = 1;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = FALSE;
                g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
                OnLoadGameButtonClick(FALSE);
                break;
            }
        } else {
            CSingleLock renderLock(&(pConnection->GetManager()->field_36), FALSE);
            renderLock.Lock(INFINITE);

            switch (field_FB4) {
            case 1:
                pConnection->field_106 = 0;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = FALSE;
                g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
                DismissPopup();
                SummonPopup(6);
                break;
            case 2:
                pConnection->field_106 = 0;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = TRUE;
                g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
                DismissPopup();
                SummonPopup(6);
                break;
            case 3:
                pConnection->field_106 = 1;
                g_pBaldurChitin->GetObjectGame()->m_bExpansion = FALSE;
                g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
                DismissPopup();
                SummonPopup(6);
                break;
            }

            renderLock.Unlock();
        }
    }
}

// 0x5FE930
void CScreenConnection::OnCancelButtonClick()
{
    if (GetTopPopup() != NULL) {
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

    if (GetTopPopup() != NULL) {
        DismissPopup();
    }

    if (pNetwork->GetPasswordRequiredForSelectedSession()) {
        SummonPopup(7);
    } else {
        pNetwork->m_bSessionPasswordEnabled = FALSE;
        m_bJoinWaiting = TRUE;
        m_bJoinComplete = FALSE;
        m_nJoinEvent = 8;
        m_nJoinErrorCode = CNetwork::ERROR_NONE;
        m_bJoinReturnValue = FALSE;
    }

    lock.Unlock();
}

// 0x5FEB70
void CScreenConnection::sub_5FEB70()
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    INT nServiceProvider = pNetwork->GetServiceProvider();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3667
    UTIL_ASSERT(nServiceProvider != -1);

    INT nServiceProviderType;
    pNetwork->GetServiceProviderType(nServiceProvider, nServiceProviderType);

    if (nServiceProviderType == CNetwork::SERV_PROV_IPX) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);
        SummonPopup(11);
        renderLock.Unlock();
    } else if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);
        SummonPopup(5);
        renderLock.Unlock();
    } else if (nServiceProviderType == CNetwork::SERV_PROV_SERIAL) {
        if (!pNetwork->m_bConnectionInitialized) {
            pNetwork->InitializeConnectionToServiceProvider(TRUE);
        }

        if (pNetwork->m_bConnectionInitialized == TRUE) {
            if (pNetwork->m_bConnectionInitialized == TRUE) {
                pNetwork->EnumerateSessions(FALSE, FALSE);
            }

            m_nSessionIndex = 0;
            OnJoinGameButtonClick();
        }
    } else if (nServiceProviderType == CNetwork::SERV_PROV_MODEM) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);
        SummonPopup(12);
        renderLock.Unlock();
    } else {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 3724
        UTIL_ASSERT(FALSE);
    }
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
    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3801
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));

    CTime time = CTime::GetCurrentTime();
    if (time.GetHour() > 6 && time.GetHour() < 18) {
        if (pPanel->m_mosBackground.GetResRef() == "STARTN") {
            pPanel->SetBackgroundResRef(CResRef("START"), g_pBaldurChitin->field_4A28);
            m_bIsNight = FALSE;
            m_vcTorch.FrameSet(0);
        }
    } else {
        if (pPanel->m_mosBackground.GetResRef() == "START") {
            pPanel->SetBackgroundResRef(CResRef("STARTN"), g_pBaldurChitin->field_4A28);
            m_bIsNight = TRUE;
            m_vcTorch.FrameSet(0);
        }
    }

    if (byte_8B3342 == TRUE && g_pChitin->cNetwork.m_bServiceProviderEnumerated) {
        byte_8B3342 = FALSE;
        AutoSelectServiceProvider();
    }

    // FIXME: This value is uninitialized in the original code which leads to
    // annoying warnings in the debug console.
    INT nServiceProviderType = -1;

    if (g_pChitin->cNetwork.GetServiceProvider() == -1) {
        // "Single Player"
        pButton->SetText(FetchString(15413));
        g_pChitin->cNetwork.SelectServiceProvider(CNetwork::SERV_PROV_NULL);
    } else {
        g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.m_nServiceProvider, nServiceProviderType);
        if (nServiceProviderType == CNetwork::SERV_PROV_IPX) {
            // "ipx"
            pButton->SetText(FetchString(13967));
        } else if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
            // "tcp/ip"
            pButton->SetText(FetchString(13968));
        } else if (nServiceProviderType == CNetwork::SERV_PROV_MODEM) {
            // "Modem"
            pButton->SetText(FetchString(13969));
        } else if (nServiceProviderType == CNetwork::SERV_PROV_SERIAL) {
            // "Serial"
            pButton->SetText(FetchString(13970));
        } else if (nServiceProviderType == CNetwork::SERV_PROV_NULL) {
            // "Single Player"
            pButton->SetText(FetchString(15413));
        } else {
            pButton->SetText(CString("ERROR!"));
        }
    }

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));
    pButton->SetEnabled(nServiceProviderType == CNetwork::SERV_PROV_NULL
        && (g_pBaldurChitin->GetObjectGame()->SaveGameExists(CInfGame::QUICK_SAVE_NAME)
            || g_pBaldurChitin->GetObjectGame()->SaveGameExists(CInfGame::QUICK_SAVE_BACKUP_NAME)));

    if (nServiceProviderType == CNetwork::SERV_PROV_NULL) {
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(11));
        pButton->SetEnabled(FALSE);
    }

    if (g_pChitin->field_110) {
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(11));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));
        pButton->SetEnabled(FALSE);
    } else if (g_pChitin->m_bStartUpConnect) {
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(0));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(7));
        pButton->SetEnabled(FALSE);

        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(3));
        pButton->SetEnabled(FALSE);
    }

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(7));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3931
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(g_pChitin->cNetwork.m_bServiceProviderEnumerated && !g_pChitin->m_bStartUpConnect);

    if (nServiceProviderType != CNetwork::SERV_PROV_NULL && !g_pChitin->field_110) {
        pButton = static_cast<CUIControlButton*>(pPanel->GetControl(11));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 3931
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(g_pChitin->cNetwork.m_bServiceProviderEnumerated);
    }

    m_cUIManager.InvalidateRect(NULL);
}

// 0x5FF450
void CScreenConnection::UpdateSessionList(CUIPanel* pPanel, DWORD nTextId)
{
    CString sSessionName;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3971
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(nTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 3973
    UTIL_ASSERT(pText != NULL);

    int v1 = pText->field_5A;

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;

    BOOL bWasSelected = m_nSessionIndex >= 0;
    m_nSessionIndex = -1;

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    for (INT nIndex = 0; nIndex < pNetwork->m_nTotalSessions; nIndex++) {
        if (bWasSelected && m_nSessionIndex < 0) {
            GUID sessionGuid;
            if (pNetwork->GetSessionGUID(nIndex, sessionGuid)) {
                if (IsEqualGUID(m_sessionGuid, sessionGuid)) {
                    m_nSessionIndex = nIndex;
                }
            }
        }

        COLORREF rgbTextColor;
        if (m_nSessionIndex == nIndex) {
            rgbTextColor = CBaldurChitin::TEXTDISPLAY_COLOR_SELECT;
        } else {
            rgbTextColor = pText->m_rgbTextColor;
        }

        pNetwork->GetSessionName(nIndex, sSessionName);

        pText->DisplayString(CString(""),
            sSessionName,
            pText->m_rgbLabelColor,
            rgbTextColor,
            nIndex,
            FALSE,
            TRUE);
    }

    INT nNewIndex = max(min(v1, pText->m_plstStrings->GetCount() - pText->field_A6A), 0);
    pText->SetTopString(pText->m_plstStrings->FindIndex(nNewIndex));
}

// 0x5FF690
void CScreenConnection::UpdateProtocolPanel()
{
    CUIPanel* pPanel;
    CUIControlButton* pButton;
    CUIControlButton3State* pButton3;
    DWORD nButtonID;

    pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4046
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(8));

    for (nButtonID = 0; nButtonID < 2; nButtonID++) {
        pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4063
        UTIL_ASSERT(pButton3 != NULL);

        pButton3->SetEnabled(FALSE);
    }

    for (INT nServiceProviderNumber = 0; nServiceProviderNumber < g_pBaldurChitin->cNetwork.m_nTotalServiceProviders; nServiceProviderNumber++) {
        INT nServiceProviderType;
        g_pBaldurChitin->cNetwork.GetServiceProviderType(nServiceProviderNumber, nServiceProviderType);

        if (nServiceProviderType == CNetwork::SERV_PROV_IPX) {
            nButtonID = 0;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
            nButtonID = 1;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_MODEM) {
            continue;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_SERIAL) {
            continue;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_NULL) {
            nButtonID = 10;
        } else {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 4105
            UTIL_ASSERT(FALSE);
        }

        pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4110
        UTIL_ASSERT(pButton3 != NULL);

        pButton3->SetEnabled(TRUE);
    }

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(10));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4121
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(TRUE);

    DWORD nSelectedButtonID;
    switch (m_nProtocol) {
    case 0:
        nSelectedButtonID = 10;
        break;
    case 1:
        nSelectedButtonID = 0;
        break;
    case 2:
        nSelectedButtonID = 1;
        break;
    case 3:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4142
        UTIL_ASSERT(FALSE);
    case 4:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4148
        UTIL_ASSERT(FALSE);
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4152
        UTIL_ASSERT(FALSE);
    }

    for (nButtonID = 0; nButtonID < 2; nButtonID++) {
        pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4163
        UTIL_ASSERT(pButton3 != NULL);

        pButton3->SetSelected(nSelectedButtonID == nButtonID);
    }

    pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(10));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4168
    UTIL_ASSERT(pButton3 != NULL);

    pButton3->SetSelected(nSelectedButtonID == 10);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(6));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4179
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(IsDoneButtonClickable());
}

// 0x5FF960
void CScreenConnection::UpdateSerialPanel()
{
    DWORD nButtonID;

    CUIPanel* pPanel = m_cUIManager.GetPanel(4);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4212
    UTIL_ASSERT(pPanel != NULL);

    UINT nOldSerialPort = m_nSerialPort;
    UINT nOldSerialBaudRate = m_nSerialBaudRate;

    for (nButtonID = 0; nButtonID < 4; nButtonID++) {
        CUIControlButton3State* pPort = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4220
        UTIL_ASSERT(pPort != NULL);

        UINT nNewSerialPort;
        switch (pPort->m_nID) {
        case 0:
            nNewSerialPort = 1;
            break;
        case 1:
            nNewSerialPort = 2;
            break;
        case 2:
            nNewSerialPort = 3;
            break;
        case 3:
            nNewSerialPort = 4;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 8232
            UTIL_ASSERT(FALSE);
        }

        pPort->SetSelected(nOldSerialPort != nNewSerialPort);
    }

    for (nButtonID = 4; nButtonID < 12; nButtonID++) {
        CUIControlButton3State* pBaud = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4227
        UTIL_ASSERT(pBaud != NULL);

        UINT nNewSerialBaudRate;
        switch (pBaud->m_nID) {
        case 4:
            nNewSerialBaudRate = 14400;
            break;
        case 5:
            nNewSerialBaudRate = 19200;
            break;
        case 6:
            nNewSerialBaudRate = 38400;
            break;
        case 7:
            nNewSerialBaudRate = 56000;
            break;
        case 8:
            nNewSerialBaudRate = 57600;
            break;
        case 9:
            nNewSerialBaudRate = 115200;
            break;
        case 10:
            nNewSerialBaudRate = 128000;
            break;
        case 11:
            nNewSerialBaudRate = 256000;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 8368
            UTIL_ASSERT(FALSE);
        }

        pBaud->SetSelected(nOldSerialBaudRate != nNewSerialBaudRate);
    }

    for (nButtonID = 10; nButtonID < 12; nButtonID++) {
        CUIControlButton3State* pBaud = static_cast<CUIControlButton3State*>(pPanel->GetControl(nButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4236
        UTIL_ASSERT(pBaud != NULL);

        pBaud->SetEnabled(FALSE);
    }

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(15));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4244
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x5FFB90
void CScreenConnection::UpdateModemPanel()
{
    CString sModemAddress;

    CUIPanel* pPanel = m_cUIManager.GetPanel(3);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4277
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(3));

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(2));

    pText->RemoveAll();
    pText->m_rgbHighlightColor = CBaldurChitin::TEXTDISPLAY_COLOR_HIGHLIGHT;

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    for (INT nIndex = 0; nIndex < pNetwork->m_nTotalModemAddresses; nIndex++) {
        COLORREF rgbTextColor;
        if (m_nModemAddress == nIndex) {
            rgbTextColor = CBaldurChitin::TEXTDISPLAY_COLOR_SELECT;
        } else {
            rgbTextColor = pText->m_rgbTextColor;
        }

        pNetwork->GetModemAddress(nIndex, sModemAddress);

        pText->DisplayString(CString(""),
            sModemAddress,
            pText->m_rgbLabelColor,
            rgbTextColor,
            nIndex,
            FALSE,
            TRUE);
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(6));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4313
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// NOTE: Inlined.
void CScreenConnection::UpdateIPXPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(11);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4340
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(2));

    UpdateSessionList(pPanel, 1);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(4));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4348
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// NOTE: Inlined.
void CScreenConnection::UpdatePlayerNamePanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(8);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4375
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(4));

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(7));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4381
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x5FFD20
void CScreenConnection::UpdateTCPIPPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(5);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4408
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(7));

    if (m_nSessionIndex >= 0) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 4415
        UTIL_ASSERT(pEdit != NULL);

        pEdit->SetText(CString(""));
    }

    UpdateSessionList(pPanel, 6);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4424
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// NOTE: Inlined.
void CScreenConnection::UpdateCreateGamePanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(6);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4451
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(14));

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(10));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4459
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// NOTE: Inlined.
void CScreenConnection::UpdatePasswordPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(7);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4494
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4496
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// NOTE: Inlined.
void CScreenConnection::UpdatePhoneNumberPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(12);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4526
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4531
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());
}

// 0x5FFDF0
void CScreenConnection::UpdateMissionPackPanel()
{
    CUIControlButton3State* pButton3;

    CUIPanel* pPanel = m_cUIManager.GetPanel(24);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4563
    UTIL_ASSERT(pPanel != NULL);

    CUIControlButton* pDone = static_cast<CUIControlButton*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4568
    UTIL_ASSERT(pDone != NULL);

    pDone->SetEnabled(IsDoneButtonClickable());

    pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(4));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4573
    UTIL_ASSERT(pButton3 != NULL);

    pButton3->SetEnabled(TRUE);

    pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(5));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4578
    UTIL_ASSERT(pButton3 != NULL);

    pButton3->SetEnabled(TRUE);

    DWORD dwSelectedButtonID;
    switch (field_FB4) {
    case 1:
        UpdateHelp(pPanel->m_nID, 3, 24870);
        dwSelectedButtonID = 4;
        break;
    case 2:
        UpdateHelp(pPanel->m_nID, 3, 24872);
        dwSelectedButtonID = 5;
        break;
    case 3:
        UpdateHelp(pPanel->m_nID, 3, 24874);
        dwSelectedButtonID = 6;
        break;
    }

    // NOTE: Probably wrong, button 6 is out of the loop.
    for (DWORD dwButtonID = 4; dwButtonID <= 5; dwButtonID++) {
        pButton3 = static_cast<CUIControlButton3State*>(pPanel->GetControl(dwButtonID));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 45617
        UTIL_ASSERT(pButton3 != NULL);

        pButton3->SetSelected(dwButtonID == dwSelectedButtonID);
    }
}

// NOTE: Inlined.
void CScreenConnection::UpdateImportPanel()
{
    CUIControlButton* pButton;

    CUIPanel* pPanel = m_cUIManager.GetPanel(25);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4645
    UTIL_ASSERT(pPanel != NULL);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4651
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(TRUE);

    pButton = static_cast<CUIControlButton*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4656
    UTIL_ASSERT(pButton != NULL);

    pButton->SetEnabled(TRUE);
}

// 0x5FFF60
void CScreenConnection::ResetProtocolPanel()
{
    m_nProtocol = 0;

    if (g_pChitin->cNetwork.GetServiceProvider() != -1) {
        INT nServiceProviderType;
        g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.m_nServiceProvider, nServiceProviderType);

        if (nServiceProviderType == CNetwork::SERV_PROV_NULL) {
            m_nProtocol = 0;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_IPX) {
            m_nProtocol = 1;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
            m_nProtocol = 2;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_MODEM) {
            m_nProtocol = 3;
        } else if (nServiceProviderType == CNetwork::SERV_PROV_SERIAL) {
            m_nProtocol = 4;
        }
    } else {
        CString sLastProtocol;
        GetPrivateProfileStringA("Multiplayer",
            "Last Protocol Used",
            "",
            sLastProtocol.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        sLastProtocol.ReleaseBuffer();

        switch (sLastProtocol.GetBuffer(1)[0]) {
        case '1':
            m_nProtocol = 1;
            break;
        case '2':
            m_nProtocol = 2;
            break;
        case '3':
            m_nProtocol = 3;
            break;
        case '4':
            m_nProtocol = 4;
            break;
        default:
            m_nProtocol = 0;
            break;
        }

        // FIXME: Missing `ReleaseBuffer`.
    }

    UpdateHelp(1, 7, 11316);
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

// NOTE: Inlined.
void CScreenConnection::ResetIPXPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(11);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4862
    UTIL_ASSERT(pPanel != NULL);

    if (g_pBaldurChitin->cNetwork.m_bSessionSelected == TRUE) {
        m_nSessionIndex = g_pBaldurChitin->cNetwork.m_nSession;
    } else {
        m_nSessionIndex = -1;
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4869
    UTIL_ASSERT(pText != NULL);

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));

    UpdateHelp(pPanel->m_nID, 5, 11321);
}

// 0x6002C0
void CScreenConnection::ResetTCPIPPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(5);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4900
    UTIL_ASSERT(pPanel != NULL);

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4902
    UTIL_ASSERT(pEdit != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(6));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4906
    UTIL_ASSERT(pText != NULL);

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));
    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
}

// 0x600370
void CScreenConnection::ResetCreateGamePanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(6);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4936
    UTIL_ASSERT(pPanel != NULL);

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4938
    UTIL_ASSERT(pEdit != NULL);

    if (g_pBaldurChitin->GetStartUpSession() != "") {
        pEdit->SetText(g_pBaldurChitin->GetStartUpSession());
    }

    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);

    UpdateHelp(pPanel->m_nID, 13, 11320);
}

// NOTE: Inlined.
void CScreenConnection::ResetPasswordPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(7);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4975
    UTIL_ASSERT(pPanel != NULL);

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(2));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 4977
    UTIL_ASSERT(pEdit != NULL);

    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
}

// NOTE: Inlined.
void CScreenConnection::ResetPhoneNumberPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(12);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5005
    UTIL_ASSERT(pPanel != NULL);

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(1));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5007
    UTIL_ASSERT(pEdit != NULL);

    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
}

// 0x600470
void CScreenConnection::ResetPlayerNamePanel()
{
    CString sPlayerName;

    CUIPanel* pPanel = m_cUIManager.GetPanel(8);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5040
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5042
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    pNetwork->CheckSessionStatus(FALSE);

    for (INT nPlayerNumber = 0; nPlayerNumber < pNetwork->m_nMaxPlayers; nPlayerNumber++) {
        if (pNetwork->GetRawPlayerID(nPlayerNumber) != 0) {
            pNetwork->GetRawPlayerName(nPlayerNumber, sPlayerName);

            pText->DisplayString(CString(""),
                sPlayerName,
                pText->m_rgbLabelColor,
                pText->m_rgbTextColor,
                -1,
                FALSE,
                TRUE);
        }
    }

    pText->SetTopString(pText->m_plstStrings->FindIndex(0));

    CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(5));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5067
    UTIL_ASSERT(pEdit != NULL);

    m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
}

// NOTE: Inlined.
void CScreenConnection::ResetLobbyPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(21);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(5));

    UpdateHelp(21, 4, 11699);
}

// NOTE: Inlined.
void CScreenConnection::ResetMissionPackPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(24);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5094
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(7));
    field_FB4 = 1;
}

// 0x600600
void CScreenConnection::ResetImportPanel()
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(25);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5123
    UTIL_ASSERT(pPanel != NULL);

    m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(pPanel->GetControl(4));

    CString sPath;
    char szFileName[16];
    HANDLE hFindFile;
    WIN32_FIND_DATAA findFileData;

    for (int index = 0; index < 6; index++) {
        sprintf(szFileName, "iwd%01d.chr", index);
        sPath = g_pBaldurChitin->GetObjectGame()->GetDirCharacters() + szFileName;

        hFindFile = FindFirstFileA(sPath, &findFileData);
        if (hFindFile != INVALID_HANDLE_VALUE) {
            field_FB8 = 1;
            UpdateHelp(pPanel->m_nID, 0, 26318);

            // FIXME: Leaking `hFindFile`.
            return;
        }
    }

    field_FB8 = 0;
    UpdateHelp(pPanel->m_nID, 0, 26317);
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

// 0x6007F0
void CScreenConnection::OnErrorButtonClick(INT nButton)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5414
    UTIL_ASSERT(0 <= nButton && nButton < CSCREENCONNECTION_ERROR_BUTTONS);

    CSingleLock lock(&(GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    switch (m_nErrorState) {
    case 0:
    case 1:
    case 2:
    case 6:
    case 8:
    case 10:
    case 23:
        DismissPopup();
        break;
    case 7:
        switch (nButton) {
        case 0:
            DismissPopup();
            sub_5FEB70();
            break;
        case 1:
            DismissPopup();
            break;
        }
        break;
    case 9:
        switch (nButton) {
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
    }

    lock.Unlock();
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
    g_pBaldurChitin->GetTlkTable().Fetch(m_strErrorText, strRes);

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

// 0x600B50
void CScreenConnection::HandleEMEvent(BYTE nEvent, BYTE nEventStage)
{
    INT nServiceProviderType;
    INT nErrorCode;
    INT nCharacterSlot;

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    switch (nEvent) {
    case 0:
        switch (nEventStage) {
        case 1:
            g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.GetServiceProvider(),
                nServiceProviderType);
            if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP
                && g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                g_pChitin->cNetwork.EnumerateSessions(FALSE, FALSE);
            }

            if (!g_pChitin->cNetwork.HostNewSession()) {
                m_bEliminateInitialize = TRUE;
            }

            m_bEMSwapped = FALSE;
            m_bEMValue = TRUE;
            m_bEMWaiting = TRUE;
            m_nEMEvent = 0;
            m_nEMEventStage = 2;
            break;
        case 2:
            if (g_pChitin->cNetwork.GetSessionHosting()) {
                renderLock.Lock(INFINITE);

                CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

                if (g_pChitin->cNetwork.CreatePlayer(nErrorCode)) {
                    DismissPopup();
                    pSettings->InitializeSettings();

                    for (nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
                        pSettings->SetCharacterControlledByPlayer(nCharacterSlot,
                            0,
                            TRUE,
                            FALSE);
                    }

                    pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer,
                        TRUE,
                        TRUE);

                    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
                    // __LINE__: 5670
                    UTIL_ASSERT(pLoad != NULL);

                    pLoad->StartLoad(1);
                    SelectEngine(pLoad);

                    g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();

                    pSettings->SetArbitrationLockAllowInput(FALSE);
                    pSettings->SetArbitrationLockStatus(TRUE, 0);

                    renderLock.Unlock();
                } else {
                    m_bEliminateInitialize = TRUE;
                    g_pChitin->cNetwork.CloseSession(TRUE);

                    // FIXME: Missing `renderLock.Unlock` (which is called
                    // implicitly anyway).
                }
            }
            break;
        }
        break;
    case 1:
        switch (nEventStage) {
        case 1:
            g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.GetServiceProvider(),
                nServiceProviderType);
            if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP
                && g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                g_pChitin->cNetwork.EnumerateSessions(FALSE, FALSE);
            }

            if (!g_pChitin->cNetwork.HostNewSession()) {
                m_bEliminateInitialize = TRUE;
            }

            m_bEMSwapped = FALSE;
            m_bEMValue = TRUE;
            m_bEMWaiting = TRUE;
            m_nEMEvent = 1;
            m_nEMEventStage = 2;
            break;
        case 2:
            if (g_pChitin->cNetwork.GetSessionHosting()) {
                renderLock.Lock(INFINITE);

                CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

                if (g_pChitin->cNetwork.CreatePlayer(nErrorCode)) {
                    DismissPopup();

                    renderLock.Unlock();

                    pSettings->InitializeSettings();

                    for (nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
                        pSettings->SetCharacterControlledByPlayer(nCharacterSlot,
                            0,
                            TRUE,
                            FALSE);
                    }

                    pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, TRUE, TRUE);

                    g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

                    renderLock.Lock(INFINITE);

                    CResRef cResArea;
                    CString sAreaName;
                    CPoint ptView;
                    g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartArea(cResArea, ptView);
                    cResArea.CopyToString(sAreaName);

                    CPoint ptAreaStart = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartPoint(0);
                    pSettings->SetCharacterCreationLocation(sAreaName, ptAreaStart);

                    g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();

                    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
                        CScreenSinglePlayer* pSinglePlayer = g_pBaldurChitin->m_pEngineSinglePlayer;
                        pSinglePlayer->field_45C = 1;
                        pSinglePlayer->StartSinglePlayer(1);
                        SelectEngine(pSinglePlayer);
                    } else {
                        CScreenMultiPlayer* pMultiPlayer = g_pBaldurChitin->m_pEngineMultiPlayer;
                        pMultiPlayer->field_45C = 1;
                        pMultiPlayer->StartMultiPlayer(1);
                        SelectEngine(pMultiPlayer);
                    }

                    pSettings->SetArbitrationLockStatus(TRUE, 0);

                    renderLock.Unlock();
                } else {
                    g_pChitin->cNetwork.CloseSession(TRUE);
                    m_bEliminateInitialize = TRUE;

                    // FIXME: Missing `renderLock.Unlock` (which is called
                    // implicitly anyway).
                }
            }
            break;
        }
        break;
    case 2:
        switch (nEventStage) {
        case 1:
            g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.GetServiceProvider(),
                nServiceProviderType);
            if (nServiceProviderType == CNetwork::SERV_PROV_TCP_IP) {
                CString sAsyncEnum;
                GetPrivateProfileStringA("Multiplayer",
                    "AsyncEnumeration",
                    "0",
                    sAsyncEnum.GetBuffer(128),
                    128,
                    g_pBaldurChitin->GetIniFileName());

                if (sAsyncEnum != "0") {
                    m_bEnumeratingAsynchronous = TRUE;
                } else {
                    m_bEnumeratingAsynchronous = FALSE;
                }

                if (g_pChitin->cGameSpy.field_0 == 1) {
                    // TODO: Incomplete.
                }

                CString sIPAddress = g_pChitin->cNetwork.m_sIPAddress;

                if (g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                    g_pChitin->cNetwork.EnumerateSessions(FALSE, FALSE);
                }

                int v1 = 10;
                if (sIPAddress != "") {
                    v1 = 60;
                }

                if (m_bEnumeratingAsynchronous == TRUE || sIPAddress != "") {
                    // NOTE: Original code is slightly different (loop body
                    // inlined a couple of times).
                    while (v1 > 0) {
                        for (int v2 = 0; v2 < 10; v2++) {
                            SleepEx(500, FALSE);
                        }

                        if (g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                            g_pChitin->cNetwork.EnumerateSessions(m_bEnumeratingAsynchronous,
                                FALSE);
                        }

                        if (g_pChitin->cNetwork.m_nTotalSessions != 0) {
                            break;
                        }

                        v1 -= 10;
                    }
                }
            } else {
                if (g_pChitin->cNetwork.m_bConnectionInitialized == TRUE) {
                    g_pChitin->cNetwork.EnumerateSessions(FALSE, FALSE);
                }
            }

            m_bEMSwapped = FALSE;
            m_bEMValue = TRUE;
            m_bEMWaiting = TRUE;
            m_nEMEvent = 2;
            m_nEMEventStage = 2;
            break;
        case 2:
            m_nSessionIndex = 0;
            OnJoinGameButtonClick();
            break;
        }
        break;
    }
}

// 0x6014A0
void CScreenConnection::HandleJoinCompletion(BYTE nEvent)
{
    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);

    if (nEvent == 8) {
        renderLock.Lock(INFINITE);

        if (m_bJoinReturnValue == TRUE) {
            m_nSessionIndex = -1;
            SummonPopup(8);

            if (g_pBaldurChitin->m_bIsAutoStarting
                && g_pBaldurChitin->GetStartUpPlayer() != "") {
                CUIPanel* pPanel = m_cUIManager.GetPanel(8);
                CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(5));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
                // __LINE__: 6156
                UTIL_ASSERT(pEdit != NULL);

                pEdit->SetText(g_pBaldurChitin->GetStartUpPlayer());
                renderLock.Unlock();

                OnDoneButtonClick();

                renderLock.Lock(INFINITE);
                g_pBaldurChitin->m_bIsAutoStarting = FALSE;
            }
        } else {
            INT nProviderType;
            g_pChitin->cNetwork.GetServiceProviderType(g_pChitin->cNetwork.m_nServiceProvider, nProviderType);
            if (nProviderType == CNetwork::SERV_PROV_TCP_IP) {
                g_pChitin->cNetwork.sub_7A61D0();
            }

            m_nSessionIndex = -1;
            m_bEliminateInitialize = TRUE;

            if (m_nJoinErrorCode == CNetwork::ERROR_INVALIDPASSWORD) {
                m_nErrorState = 0;
                m_strErrorText = 18985;
            } else {
                m_nErrorState = 1;
                m_strErrorText = 18986;
            }

            m_strErrorButtonText[0] = 11973;
            SummonPopup(20);
        }

        renderLock.Unlock();
    } else if (nEvent == 9) {
        renderLock.Lock(INFINITE);

        if (m_bJoinReturnValue) {
            DismissPopup();
            SummonPopup(8);

            if (g_pBaldurChitin->m_bIsAutoStarting
                && g_pBaldurChitin->GetStartUpPlayer() != "") {
                CUIPanel* pPanel = m_cUIManager.GetPanel(8);
                CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(pPanel->GetControl(5));

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
                // __LINE__: 6238
                UTIL_ASSERT(pEdit != NULL);

                pEdit->SetText(g_pBaldurChitin->GetStartUpPlayer());
                renderLock.Unlock();

                OnDoneButtonClick();

                renderLock.Lock(INFINITE);
                g_pBaldurChitin->m_bIsAutoStarting = FALSE;
            }
        } else {
            if (m_nJoinErrorCode == CNetwork::ERROR_INVALIDPASSWORD) {
                m_nErrorState = 0;
                m_strErrorText = 18985;
            } else {
                m_nErrorState = 1;
                m_strErrorText = 18986;
            }

            m_strErrorButtonText[0] = 11973;
            SummonPopup(20);
        }

        renderLock.Unlock();
    }
}

// 0x601790
BOOL CScreenConnection::AutoStartInitialize()
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    CString sLastProtocolUsed;

    for (INT nIndex = 0; nIndex < pNetwork->m_nTotalServiceProviders; nIndex++) {
        INT nProvider;
        pNetwork->GetServiceProviderType(nIndex, nProvider);
        if (nProvider == CNetwork::SERV_PROV_TCP_IP) {
            pNetwork->SelectServiceProvider(nIndex);
            m_nProtocol = 2;

            sLastProtocolUsed.Format("%d", m_nProtocol);
            WritePrivateProfileStringA("Multiplayer",
                "Last Protocol Used",
                sLastProtocolUsed,
                g_pBaldurChitin->GetIniFileName());

            return TRUE;
        }
    }

    CSingleLock renderLock(&(GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    m_nErrorState = 6;
    m_strErrorText = 20276;
    m_strErrorButtonText[0] = 11973;
    SummonPopup(20);

    renderLock.Unlock();

    return FALSE;
}

// 0x6018E0
void CScreenConnection::AutoStartConnect()
{
    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);

    if (AutoStartInitialize()) {
        g_pBaldurChitin->m_bIsAutoStarting = FALSE;

        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        CString sStartUpAddress = g_pBaldurChitin->GetStartUpAddress();
        sStartUpAddress.TrimLeft();
        sStartUpAddress.TrimRight();

        m_nErrorState = 4;
        m_strErrorText = 20274;
        SummonPopup(19);
        pVidMode->m_bPointerEnabled = FALSE;

        renderLock.Unlock();

        g_pChitin->m_bDisplayStale = TRUE;

        g_pBaldurChitin->GetObjectGame()->sub_59FA00(TRUE);

        renderLock.Lock();
        if (pNetwork->m_bConnectionInitialized == TRUE) {
            pNetwork->EnumerateSessions(TRUE, FALSE);
        }
        renderLock.Unlock();

        pNetwork->m_sIPAddress = sStartUpAddress;
        pNetwork->InitializeConnectionToServiceProvider(TRUE);

        WritePrivateProfileStringA("Multiplayer",
            "TCP/IP Address",
            sStartUpAddress,
            g_pBaldurChitin->GetIniFileName());

        m_bEMSwapped = FALSE;
        m_bEMValue = FALSE;
        m_bEMWaiting = TRUE;
        m_nEMEvent = 2;
        m_nEMEventStage = 1;

        m_bAllowInput = TRUE;
    } else {
        g_pBaldurChitin->m_bIsAutoStarting = FALSE;
        m_bAllowInput = TRUE;
    }
}

// 0x601AE0
void CScreenConnection::AutoStartDirectPlayLobby()
{
    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        SummonPopup(21);
        m_bAllowInput = TRUE;

        renderLock.Unlock();
    } else {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        m_nErrorState = 4;
        m_strErrorText = 20274;
        SummonPopup(19);

        renderLock.Unlock();

        g_pChitin->m_bDisplayStale = TRUE;

        g_pBaldurChitin->GetObjectGame()->sub_59FA00(TRUE);

        CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();
        pSettings->InitializeSettings();
        pSettings->m_bFirstConnected = TRUE;
        pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, FALSE, TRUE);

        renderLock.Lock();
        DismissPopup();
        renderLock.Unlock();

        g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

        g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 1;
        g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(1);
        SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);
    }

    g_pBaldurChitin->m_bIsAutoStarting = FALSE;
}

// 0x601CB0
void CScreenConnection::AutoSelectServiceProvider()
{
    m_nProtocol = 0;

    CNetwork* pNetwork = &(g_pBaldurChitin->cNetwork);
    CString sLastProtocolUsed;

    if (g_pChitin->field_110 || g_pChitin->m_bStartUpConnect) {
        sLastProtocolUsed = "2";
    } else {
        GetPrivateProfileStringA("Multiplayer",
            "Last Protocol Used",
            "0",
            sLastProtocolUsed.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        sLastProtocolUsed.ReleaseBuffer();
    }

    switch (sLastProtocolUsed[0] - '0') {
    case 0:
        m_nProtocol = 0;
        break;
    case 1:
        m_nProtocol = 1;
        break;
    case 2:
        m_nProtocol = 2;
        break;
    case 3:
        m_nProtocol = 3;
        break;
    case 4:
        m_nProtocol = 4;
        break;
    }

    if (m_nProtocol != 0) {
        INT nNewProvider = 0;
        switch (m_nProtocol) {
        case 1:
            nNewProvider = CNetwork::SERV_PROV_IPX;
            break;
        case 2:
            nNewProvider = CNetwork::SERV_PROV_TCP_IP;
            break;
        case 3:
            if (1) {
                CString sModemSelected;
                CString sDefaultModemName("");

                GetPrivateProfileStringA("Multiplayer",
                    "Modem Selected",
                    sDefaultModemName,
                    sModemSelected.GetBuffer(128),
                    128,
                    g_pBaldurChitin->GetIniFileName());

                if (sModemSelected != "") {
                    if (pNetwork->m_nModemAddress != -1) {
                        pNetwork->UnselectModemAddress();
                    }

                    INT nModemAddress = pNetwork->FindModemAddress(sModemSelected);
                    pNetwork->SelectModemAddress(nModemAddress);
                } else {
                    m_nProtocol = 0;
                    nNewProvider = 0;
                }

                if (pNetwork->m_nModemAddress != -1) {
                    m_nModemAddress = pNetwork->m_nModemAddress;
                    nNewProvider = CNetwork::SERV_PROV_MODEM;
                }
            }
            break;
        case 4:
            if (1) {
                UINT nSerialPort = GetPrivateProfileIntA("Multiplayer",
                    "Serial Port",
                    1,
                    g_pBaldurChitin->GetIniFileName());
                pNetwork->SetSerialPort(nSerialPort);
                if (pNetwork->m_nSerialPort != nSerialPort) {
                    pNetwork->SetSerialPort(1);
                }

                UINT nBaudRate = GetPrivateProfileIntA("Multiplayer",
                    "Serial Baud",
                    38400,
                    g_pBaldurChitin->GetIniFileName());
                pNetwork->SetSerialBaudRate(nBaudRate);
                if (pNetwork->m_nSerialBaudRate != nBaudRate) {
                    pNetwork->SetSerialBaudRate(38400);
                }

                m_nSerialPort = pNetwork->m_nSerialPort;
                m_nSerialBaudRate = pNetwork->m_nSerialBaudRate;
                nNewProvider = CNetwork::SERV_PROV_SERIAL;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
            // __LINE__: 6749
            UTIL_ASSERT(FALSE);
        }

        for (INT nIndex = 0; nIndex < pNetwork->m_nTotalServiceProviders; nIndex++) {
            INT nProvider;
            pNetwork->GetServiceProviderType(nIndex, nProvider);
            if (nProvider == nNewProvider) {
                pNetwork->SelectServiceProvider(nIndex);

                CString sNewLastProtocolUsed;
                sNewLastProtocolUsed.Format("%d", m_nProtocol);

                WritePrivateProfileStringA("Multiplayer",
                    "Last Protocol Used",
                    sNewLastProtocolUsed,
                    g_pBaldurChitin->GetIniFileName());
            }
        }
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

    g_pBaldurChitin->GetTlkTable().Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x602170
void CScreenConnection::OnLobbyNewGameButtonClick()
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();

    pSettings->InitializeSettings();

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        pSettings->SetCharacterControlledByPlayer(nCharacterSlot, 0, TRUE, FALSE);
    }

    pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, TRUE, TRUE);

    g_pBaldurChitin->GetObjectGame()->NewGame(TRUE, FALSE);

    CResRef areaResRef;
    CString sAreaName;
    CPoint ptView;

    g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartArea(areaResRef, ptView);
    areaResRef.CopyToString(sAreaName);

    CPoint ptStart = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetStartPoint(0);
    pSettings->SetCharacterCreationLocation(sAreaName, ptStart);

    g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();

    if (g_pBaldurChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL) {
        g_pBaldurChitin->m_pEngineSinglePlayer->field_45C = 1;
        g_pBaldurChitin->m_pEngineSinglePlayer->StartSinglePlayer(1);
        SelectEngine(g_pBaldurChitin->m_pEngineSinglePlayer);
    } else {
        g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 1;
        g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(1);
        SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);
    }

    pSettings->SetArbitrationLockStatus(TRUE, 0);
}

// 0x602360
void CScreenConnection::OnLobbyLoadGameButtonClick()
{
    CMultiplayerSettings* pSettings = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings();

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);
    DismissPopup();
    renderLock.Unlock();

    pSettings->InitializeSettings();

    for (INT nCharacterSlot = 0; nCharacterSlot < 6; nCharacterSlot++) {
        pSettings->SetCharacterControlledByPlayer(nCharacterSlot, 0, TRUE, FALSE);
    }

    pSettings->SetPlayerReady(g_pChitin->cNetwork.m_idLocalPlayer, TRUE, TRUE);

    CScreenLoad* pLoad = g_pBaldurChitin->m_pEngineLoad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 6967
    UTIL_ASSERT(pLoad != NULL);

    pLoad->StartLoad(1);
    SelectEngine(pLoad);

    g_pBaldurChitin->GetObjectGame()->LoadMultiPlayerPermissions();

    pSettings->SetArbitrationLockAllowInput(0);
    pSettings->SetArbitrationLockStatus(TRUE, 0);
}

// 0x6024A0
void CScreenConnection::OnLobbyExitButtonClick()
{
    CSingleLock lock(&(m_cUIManager.field_36));
    lock.Lock();
    DismissPopup();
    lock.Unlock();

    g_pBaldurChitin->cNetwork.CloseSession(TRUE);

    g_pBaldurChitin->m_pEngineStart->m_nEngineState = 0;
    SelectEngine(g_pBaldurChitin->m_pEngineStart);
}

// 0x602550
void CScreenConnection::CancelEngine()
{
    while (GetTopPopup() != NULL) {
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
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(15413, strRes); // "Single Player"
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
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13731, strRes); // "Quit Game"
    SetText(strRes.szText);
}

// 0x6028C0
CUIControlButtonConnectionQuitGame::~CUIControlButtonConnectionQuitGame()
{
}

// 0x602960
void CUIControlButtonConnectionQuitGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7237
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock lock(&(pConnection->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    g_pBaldurChitin->cNetwork.UnselectSession();
    g_pBaldurChitin->cNetwork.m_bSessionPasswordEnabled = FALSE;
    g_pBaldurChitin->cNetwork.UnselectModemAddress();
    pConnection->m_bEliminateInitialize = TRUE;

    // NOTE: Obtaining same lock twice, likely some inlining.
    CSingleLock sameLock(&(pConnection->GetManager()->field_36), FALSE);
    sameLock.Lock(INFINITE);
    pConnection->m_nErrorState = 9;
    pConnection->m_strErrorText = 19532;
    pConnection->m_strErrorButtonText[0] = 15417;
    pConnection->m_strErrorButtonText[1] = 13727;
    pConnection->SummonPopup(22);
    sameLock.Unlock();

    lock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x602A90
CUIControlButtonConnectionNewGame::CUIControlButtonConnectionNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13963, strRes); // "New Game"
    SetText(strRes.szText);
}

// 0x602B80
CUIControlButtonConnectionNewGame::~CUIControlButtonConnectionNewGame()
{
}

// 0x602C20
void CUIControlButtonConnectionNewGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7301
    UTIL_ASSERT(pConnection != NULL);

    STR_RES strRes;

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
        || g_pBaldurChitin->cDimm.cResCache.m_nCacheSize >= 175000000) {
        CUIPanel* pPanel = pConnection->GetManager()->GetPanel(6);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7328
        UTIL_ASSERT(pPanel != NULL);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(10));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7330
        UTIL_ASSERT(pButton != NULL);

        pConnection->field_106 = 0;

        g_pBaldurChitin->GetTlkTable().Fetch(13728, strRes);
        pButton->SetText(strRes.szText);

        if (pConnection->m_nProtocol != 0) {
            CSingleLock renderLock(&(pConnection->GetManager()->field_36), FALSE);
            renderLock.Lock(INFINITE);
            pConnection->SummonPopup(6);
            renderLock.Unlock();
        } else {
            pConnection->OnNewGameButtonClick();
        }
    } else {
        pConnection->m_nErrorState = 2;
        pConnection->m_strErrorText = 20692;
        pConnection->m_strErrorButtonText[0] = 11973;
        pConnection->SummonPopup(20);
    }
}

// -----------------------------------------------------------------------------

// 0x602E10
CUIControlButtonConnectionQuickLoad::CUIControlButtonConnectionQuickLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(33508, strRes); // "Quick Load"
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

    pConnection->OnLoadGameButtonClick(TRUE);
}

// -----------------------------------------------------------------------------

// 0x602FE0
CUIControlButtonConnectionLoadGame::CUIControlButtonConnectionLoadGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13729, strRes); // "Load Game"
    SetText(strRes.szText);
}

// 0x6030D0
CUIControlButtonConnectionLoadGame::~CUIControlButtonConnectionLoadGame()
{
}

// 0x603170
void CUIControlButtonConnectionLoadGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7491
    UTIL_ASSERT(pConnection != NULL);

    STR_RES strRes;

    if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
        || g_pBaldurChitin->cDimm.cResCache.m_nCacheSize >= 175000000) {
        CUIPanel* pPanel = pConnection->GetManager()->GetPanel(6);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7518
        UTIL_ASSERT(pPanel != NULL);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(10));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7520
        UTIL_ASSERT(pButton != NULL);

        pConnection->field_106 = 1;

        g_pBaldurChitin->GetTlkTable().Fetch(13729, strRes);
        pButton->SetText(strRes.szText);

        pConnection->field_106 = m_nID == 7;

        if (pConnection->m_nProtocol != 0) {
            CSingleLock renderLock(&(pConnection->GetManager()->field_36), FALSE);
            renderLock.Lock(INFINITE);
            pConnection->SummonPopup(6);
            renderLock.Unlock();
        } else {
            pConnection->OnLoadGameButtonClick(FALSE);
        }
    } else {
        pConnection->m_nErrorState = 2;
        pConnection->m_strErrorText = 20692;
        pConnection->m_strErrorButtonText[0] = 11973;
        pConnection->SummonPopup(20);
    }
}

// -----------------------------------------------------------------------------

// 0x603380
CUIControlButtonConnectionJoinGame::CUIControlButtonConnectionJoinGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13964, strRes); // "Join Game"
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

    if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
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

// 0x603640
CUIControlTextDisplayConnectionTCPIPSessions::CUIControlTextDisplayConnectionTCPIPSessions(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayConnectionTCPIPSessions::~CUIControlTextDisplayConnectionTCPIPSessions()
{
}

// 0x603690
void CUIControlTextDisplayConnectionTCPIPSessions::OnItemSelected(LONG lMarker)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7780
    UTIL_ASSERT(pConnection != NULL);

    CUIPanel* pPanel = pConnection->m_cUIManager.GetPanel(11);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 6795
    UTIL_ASSERT(pConnection != NULL);

    pConnection->m_nSessionIndex = lMarker;

    GUID guid;
    if (g_pBaldurChitin->cNetwork.GetSessionGUID(pConnection->m_nSessionIndex, guid)) {
        pConnection->m_sessionGuid = guid;
    }

    pConnection->UpdatePopupPanel(pPanel->m_nID);
}

// 0x603750
CUIControlButtonConnectionPopupDone::CUIControlButtonConnectionPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes); // "Done"
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
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes); // "Cancel"
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

// 0x603AF0
CUIControlButtonConnectionProtocolProtocol::CUIControlButtonConnectionProtocolProtocol(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;

    DWORD strId;
    switch (m_nID) {
    case 0:
        // "ipx"
        strId = 13967;
        break;
    case 1:
        // "tcp/ip"
        strId = 13968;
        break;
    case 2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7936
        UTIL_ASSERT(FALSE);
    case 3:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7942
        UTIL_ASSERT(FALSE);
    case 10:
        // "Single Player"
        strId = 15413;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 7950
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strId, strRes);
    SetText(strRes.szText);

    m_nSelectedFrame = 0;
    m_nNotSelectedFrame = 1;
}

// 0x603C90
CUIControlButtonConnectionProtocolProtocol::~CUIControlButtonConnectionProtocolProtocol()
{
}

// 0x603D30
void CUIControlButtonConnectionProtocolProtocol::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 7986
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock lock(&(pConnection->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    switch (m_nID) {
    case 0:
        pConnection->m_nProtocol = 1;
        pConnection->UpdatePopupPanel(m_pPanel->m_nID);
        break;
    case 1:
        pConnection->m_nProtocol = 2;
        pConnection->UpdatePopupPanel(m_pPanel->m_nID);
        break;
    case 2:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8010
        UTIL_ASSERT(FALSE);
    case 3:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8018
        UTIL_ASSERT(FALSE);
    case 10:
        pConnection->m_nProtocol = 0;
        pConnection->UpdatePopupPanel(m_pPanel->m_nID);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8027
        UTIL_ASSERT(FALSE);
    }

    lock.Unlock();
}

// 0x603EA0
CUIControlTextDisplayConnectionModems::CUIControlTextDisplayConnectionModems(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x603ED0
void CUIControlTextDisplayConnectionModems::OnItemSelected(LONG lMarker)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8151
    UTIL_ASSERT(pConnection != NULL);

    pConnection->m_nModemAddress = lMarker;

    pConnection->UpdatePopupPanel(m_pPanel->m_nID);
}

// 0x603F20
CUIControlButtonConnectionSerialPort::CUIControlButtonConnectionSerialPort(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    INT nPort;
    switch (m_nID) {
    case 0:
        nPort = 1;
        break;
    case 1:
        nPort = 2;
        break;
    case 2:
        nPort = 3;
        break;
    case 3:
        nPort = 4;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8232
        UTIL_ASSERT(FALSE);
    }

    char buffer[80];
    sprintf(buffer, "COM%d", nPort);
    SetText(CString(buffer));

    m_nSelectedFrame = 1;
    m_nNotSelectedFrame = 0;
}

// 0x604050
CUIControlButtonConnectionSerialPort::~CUIControlButtonConnectionSerialPort()
{
}

// 0x6040F0
void CUIControlButtonConnectionSerialPort::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8263
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock lock(&(pConnection->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    INT nPort;
    switch (m_nID) {
    case 0:
        nPort = 1;
        break;
    case 1:
        nPort = 2;
        break;
    case 2:
        nPort = 3;
        break;
    case 3:
        nPort = 4;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8232
        UTIL_ASSERT(FALSE);
    }

    pConnection->m_nSerialPort = nPort;

    pConnection->UpdatePopupPanel(pConnection->GetTopPopup()->m_nID);

    lock.Unlock();
}

// 0x604210
CUIControlButtonConnectionSerialBaudRate::CUIControlButtonConnectionSerialBaudRate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    INT nBaudRate;
    switch (m_nID) {
    case 4:
        nBaudRate = 14400;
        break;
    case 5:
        nBaudRate = 19200;
        break;
    case 6:
        nBaudRate = 38400;
        break;
    case 7:
        nBaudRate = 56000;
        break;
    case 8:
        nBaudRate = 57600;
        break;
    case 9:
        nBaudRate = 115200;
        break;
    case 10:
        nBaudRate = 128000;
        break;
    case 11:
        nBaudRate = 256000;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8368
        UTIL_ASSERT(FALSE);
    }

    char buffer[80];
    sprintf(buffer, "%d", nBaudRate);
    SetText(CString(buffer));

    m_nSelectedFrame = 1;
    m_nNotSelectedFrame = 0;
}

// 0x604370
CUIControlButtonConnectionSerialBaudRate::~CUIControlButtonConnectionSerialBaudRate()
{
}

// 0x604410
void CUIControlButtonConnectionSerialBaudRate::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8399
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock lock(&(pConnection->GetManager()->field_36), FALSE);
    lock.Lock(INFINITE);

    INT nBaudRate;
    switch (m_nID) {
    case 4:
        nBaudRate = 14400;
        break;
    case 5:
        nBaudRate = 19200;
        break;
    case 6:
        nBaudRate = 38400;
        break;
    case 7:
        nBaudRate = 56000;
        break;
    case 8:
        nBaudRate = 57600;
        break;
    case 9:
        nBaudRate = 115200;
        break;
    case 10:
        nBaudRate = 128000;
        break;
    case 11:
        nBaudRate = 256000;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8368
        UTIL_ASSERT(FALSE);
    }

    pConnection->m_nSerialBaudRate = nBaudRate;

    pConnection->UpdatePopupPanel(pConnection->GetTopPopup()->m_nID);

    lock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x604560
CUIControlEditConnectionWithDefault::CUIControlEditConnectionWithDefault(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo, BYTE nField)
    : CUIControlEdit(panel, controlInfo, 0)
{
    CString sValue;

    switch (nField) {
    case 0:
        GetPrivateProfileStringA("Multiplayer",
            "Session Name",
            "",
            sValue.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 1:
        GetPrivateProfileStringA("Multiplayer",
            "Session Password",
            "",
            sValue.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 2:
        GetPrivateProfileStringA("Multiplayer",
            "Player Name",
            "",
            sValue.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 3:
        if (g_pChitin->m_bStartUpConnect) {
            sValue = g_pChitin->GetStartUpAddress();
        } else {
            GetPrivateProfileStringA("Multiplayer",
                "TCP/IP Address",
                "",
                sValue.GetBuffer(128),
                128,
                g_pBaldurChitin->GetIniFileName());
        }
        break;
    case 4:
        GetPrivateProfileStringA("Multiplayer",
            "Phone Number",
            "",
            sValue.GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8543
        UTIL_ASSERT(FALSE);
    }

    sValue.ReleaseBuffer();

    if (sValue.GetLength() > 0) {
        m_sText = sValue;
    }

    m_nField = nField;
}

// 0x6047D0
CUIControlEditConnectionWithDefault::~CUIControlEditConnectionWithDefault()
{
}

// 0x6048A0
void CUIControlEditConnectionWithDefault::OnKeyDown(SHORT nKey)
{
    CUIControlEdit::OnKeyDown(nKey);

    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8581
    UTIL_ASSERT(pConnection != NULL);

    switch (m_nField) {
    case 5:
        pConnection->m_nSessionIndex = -1;
        break;
    }

    pConnection->UpdatePopupPanel(m_pPanel->m_nID);
}

// 0x604900
void CUIControlEditConnectionWithDefault::OnEditReturn(CString sText)
{
    switch (m_nField) {
    case 0:
        WritePrivateProfileStringA("Multiplayer",
            "Session Name",
            sText,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 1:
        WritePrivateProfileStringA("Multiplayer",
            "Session Password",
            sText,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 2:
        WritePrivateProfileStringA("Multiplayer",
            "Player Name",
            sText,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 3:
        WritePrivateProfileStringA("Multiplayer",
            "TCP/IP Address",
            sText,
            g_pBaldurChitin->GetIniFileName());
        break;
    case 4:
        WritePrivateProfileStringA("Multiplayer",
            "Phone Number",
            sText,
            g_pBaldurChitin->GetIniFileName());
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 8633
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x604A50
CUIControlButtonConnectionCreateGameNewGame::CUIControlButtonConnectionCreateGameNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13728, strRes); // "New Game"
    SetText(strRes.szText);
}

// 0x604B40
CUIControlButtonConnectionCreateGameNewGame::~CUIControlButtonConnectionCreateGameNewGame()
{
}

// 0x604BE0
void CUIControlButtonConnectionCreateGameNewGame::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8691
    UTIL_ASSERT(pConnection != NULL);

    if (pConnection->field_106) {
        pConnection->OnLoadGameButtonClick(FALSE);
    } else {
        pConnection->OnNewGameButtonClick();
    }
}

// -----------------------------------------------------------------------------

// 0x604C30
CUIControlButtonConnection604C30::CUIControlButtonConnection604C30(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11825, strRes); // "Pre-generate Character"
    SetText(strRes.szText);
}

// 0x604D20
CUIControlButtonConnection604C30::~CUIControlButtonConnection604C30()
{
}

// 0x604DC0
void CUIControlButtonConnection604C30::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->m_pEngineCreateChar->StartCreateChar(-1, 4);

    g_pBaldurChitin->GetTlkTable().m_override.CloseFiles();
    g_pBaldurChitin->GetTlkTable().OpenOverride(CString("temp/default.toh"), CString("temp/default.tot"));

    g_pBaldurChitin->GetActiveEngine()->SelectEngine(g_pBaldurChitin->m_pEngineCreateChar);
}

// -----------------------------------------------------------------------------

// 0x604E90
CUIControlTextDisplayConnection604E90::CUIControlTextDisplayConnection604E90(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayConnection604E90::~CUIControlTextDisplayConnection604E90()
{
}

// 0x604EC0
void CUIControlTextDisplayConnection604E90::OnItemSelected(LONG lMarker)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8876
    UTIL_ASSERT(pConnection != NULL);

    CUIPanel* pPanel = pConnection->m_cUIManager.GetPanel(5);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 5291
    UTIL_ASSERT(pConnection != NULL);

    pConnection->m_nSessionIndex = lMarker;

    GUID guid;
    if (g_pBaldurChitin->cNetwork.GetSessionGUID(pConnection->m_nSessionIndex, guid)) {
        pConnection->m_sessionGuid = guid;
    }

    pConnection->UpdatePopupPanel(pPanel->m_nID);
}

// -----------------------------------------------------------------------------

// 0x604F80
CUIControlButtonConnectionErrorButton::CUIControlButtonConnectionErrorButton(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x604FD0
CUIControlButtonConnectionErrorButton::~CUIControlButtonConnectionErrorButton()
{
}

// 0x605070
void CUIControlButtonConnectionErrorButton::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8928
    UTIL_ASSERT(pConnection != NULL);

    pConnection->OnErrorButtonClick(m_nID - 1);
}

// 0x6050B0
CUIControlButtonConnectionLobbyMenu::CUIControlButtonConnectionLobbyMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 8956
    UTIL_ASSERT(pConnection != NULL);

    STRREF dwStrId;
    switch (m_nID) {
    case 1:
        dwStrId = 13728; // "New Game"
        break;
    case 2:
        dwStrId = 13729; // "Load Game"
        break;
    case 3:
        dwStrId = 13906; // "Exit"
        break;
    }

    SetText(CBaldurEngine::FetchString(dwStrId));
}

// 0x6051A0
CUIControlButtonConnectionLobbyMenu::~CUIControlButtonConnectionLobbyMenu()
{
}

// 0x605240
void CUIControlButtonConnectionLobbyMenu::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 9006
    UTIL_ASSERT(pConnection != NULL);

    switch (m_nID) {
    case 1:
        pConnection->OnLobbyNewGameButtonClick();
        break;
    case 2:
        pConnection->OnLobbyLoadGameButtonClick();
        break;
    case 3:
        pConnection->OnLobbyExitButtonClick();
        break;
    }
}

// -----------------------------------------------------------------------------

// 0x6052A0
CUIControlButtonConnection6052A0::CUIControlButtonConnection6052A0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;

    DWORD strId;
    switch (m_nID) {
    case 4:
        strId = 24869; // "Full Game"
        break;
    case 5:
        strId = 24871; // "Expansion Only"
        break;
    case 6:
        strId = 24873; // "Load Game"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 9070
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strId, strRes);
    SetText(strRes.szText);

    m_nSelectedFrame = 0;
    m_nNotSelectedFrame = 1;
}

// 0x6053D0
CUIControlButtonConnection6052A0::~CUIControlButtonConnection6052A0()
{
}

// 0x605470
void CUIControlButtonConnection6052A0::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 9106
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock renderLock(&(pConnection->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nID) {
    case 4:
        pConnection->field_FB4 = 1;
        break;
    case 5:
        pConnection->field_FB4 = 2;
        break;
    case 6:
        pConnection->field_FB4 = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 9130
        UTIL_ASSERT(FALSE);
    }

    pConnection->UpdatePopupPanel(m_pPanel->m_nID);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x605570
CUIControlButtonConnection605570::CUIControlButtonConnection605570(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;

    DWORD strId;
    switch (m_nID) {
    case 1:
        strId = 13912; // "Yes"
        break;
    case 2:
        strId = 13913; // "No"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 9176
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strId, strRes);
    SetText(strRes.szText);
}

// 0x605680
CUIControlButtonConnection605570::~CUIControlButtonConnection605570()
{
}

// 0x605720
void CUIControlButtonConnection605570::OnLButtonClick(CPoint pt)
{
    CScreenConnection* pConnection = g_pBaldurChitin->m_pEngineConnection;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 9208
    UTIL_ASSERT(pConnection != NULL);

    CSingleLock renderLock(&(pConnection->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    switch (m_nID) {
    case 1:
        if (pConnection->field_FB8) {
            g_pBaldurChitin->GetObjectGame()->field_4BD6 = TRUE;
            pConnection->OnNewGameButtonClick();
        } else {
            g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
            pConnection->OnNewGameButtonClick();
        }
        break;
    case 2:
        if (pConnection->field_FB8) {
            g_pBaldurChitin->GetObjectGame()->field_4BD6 = FALSE;
            pConnection->OnNewGameButtonClick();
        } else {
            pConnection->OnCancelButtonClick();
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
        // __LINE__: 9246
        UTIL_ASSERT(FALSE);
    }

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x605840
void CScreenConnection::ReadyEndCredits()
{
    m_bPlayEndCredits = TRUE;
}

// 0x605850
void CScreenConnection::ShowSessionTerminatedMessage()
{
    CSingleLock lock(&(m_cUIManager.field_36), FALSE);
    lock.Lock(INFINITE);

    if (g_pBaldurChitin->m_cBaldurMessage.m_bVersionControlShutdown) {
        SummonPopup(23);
        g_pBaldurChitin->m_cBaldurMessage.m_bVersionControlShutdown = FALSE;
    } else {
        m_nErrorState = 0;
        m_strErrorText = 10803;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(20);
    }

    pVidMode->m_bPointerEnabled = TRUE;

    lock.Unlock();
}

// 0x605920
void CScreenConnection::ResetVersionMismatchPanel(CUIPanel* pPanel)
{
    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(0));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenConnection.cpp
    // __LINE__: 9313
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_SERVERVERSION,
        g_pBaldurChitin->GetBaldurMessage()->GetVersionControlShutdownServerString());

    g_pBaldurChitin->GetTlkTable().SetToken(TOKEN_CLIENTVERSION,
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

// NOTE: Inlined.
BOOL CScreenConnection::IsValidAddress(const CString& sAddress)
{
    INT nByte1;
    INT nByte2;
    INT nByte3;
    INT nByte4;
    INT nCharsScanned;
    INT nFieldsScanned = sscanf(sAddress, "%d.%d.%d.%d%n", &nByte1, &nByte2, &nByte3, &nByte4, &nCharsScanned);

    return nFieldsScanned == 4
        && nCharsScanned == sAddress.GetLength()
        && nByte1 >= 0 && nByte1 <= 255
        && nByte2 >= 0 && nByte2 <= 255
        && nByte3 >= 0 && nByte3 <= 255
        && nByte4 >= 0 && nByte4 <= 255;
}

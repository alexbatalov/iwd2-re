#include "CChitin.h"

#include <direct.h>
#include <process.h>
#include <winver.h>

#include "CAlias.h"
#include "CKeyInfo.h"
#include "CResBinary.h"
#include "CResBitmap.h"
#include "CResCell.h"
#include "CResCellHeader.h"
#include "CResMosaic.h"
#include "CResPLT.h"
#include "CResTile.h"
#include "CResWave.h"
#include "CUtil.h"
#include "CVidFont.h"
#include "CWarp.h"

static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
static void MessageThreadMain(void* userInfo);
static void RSThreadMain(void* userInfo);
static void MainAIThread(void* userInfo);
static void MusicThreadMain(void* userInfo);
static void CALLBACK TimerFunction(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);

// 0x8B9E48
DWORD CChitin::TIMER_UPDATES_PER_SECOND = 30;

// 0x8FB934
const CString CChitin::ICON_RES_ID("");

// 0x8FB938
CString CChitin::buildVersionString;

// 0x8FB93C
const CString CChitin::DEFAULT_PRINTSCREEN_FILE_NAME("Scrn");

// 0x8FB940
CString CChitin::versionString;

// 0x8FB944
CString CChitin::name;

// #guess
// 0x8FB948
BOOL CChitin::SCREEN_SAVE_ACTIVE;

// #guess
// 0x8FB94C
BOOL CChitin::SCREEN_SAVE_ACTIVE_LOADED;

// 0x8FB950
BOOLEAN CChitin::byte_8FB950;

// 0x8FB974
int CChitin::dword_8FB974;

// 0x8FB978
int CChitin::dword_8FB978;

// 0x8FB97C
int CChitin::dword_8FB97C;

// 0x78D960
static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    if (g_pChitin->field_16C && Msg == g_pChitin->field_170) {
        if (!g_pChitin->m_bInMouseWheelQueue) {
            g_pChitin->m_bInMouseWheelQueue = TRUE;
            g_pChitin->m_lMouseWheel.AddTail(reinterpret_cast<void*>(wParam));
            g_pChitin->m_bInMouseWheelQueue = FALSE;
        }
        return 0;
    }

    switch (Msg) {
    case WM_DESTROY:
        if (!g_pChitin->field_F8) {
            g_pChitin->ShutDown(-1, NULL, NULL);
            return 0;
        }
        break;
    case WM_MOVE:
    case WM_SIZE:
        if (g_pChitin->m_bFullscreen) {
            SetRect(&(g_pChitin->field_E8),
                0,
                0,
                GetSystemMetrics(SM_CXSCREEN),
                GetSystemMetrics(SM_CYSCREEN));
        } else {
            GetClientRect(hWnd, &(g_pChitin->field_E8));
            ClientToScreen(hWnd, reinterpret_cast<LPPOINT>(&(g_pChitin->field_E8.left)));
            ClientToScreen(hWnd, reinterpret_cast<LPPOINT>(&(g_pChitin->field_E8.right)));
            g_pChitin->RedrawScreen();

            RECT rect;
            GetClientRect(hWnd, &rect);

            if (rect.right == rect.left && rect.bottom == rect.top) {
                if (CChitin::byte_8FB950 == 0) {
                    g_pChitin->OnAltTab(hWnd, FALSE);
                }
            } else {
                if (CChitin::byte_8FB950 == 1) {
                    g_pChitin->OnAltTab(hWnd, TRUE);
                }
            }
        }
        break;
    case WM_KILLFOCUS:
        SetCursor(LoadCursorA(NULL, IDC_ARROW));
        return 0;
    case WM_PAINT:
        if (GetUpdateRect(hWnd, NULL, FALSE)) {
            PAINTSTRUCT paint;
            BeginPaint(hWnd, &paint);
            EndPaint(hWnd, &paint);
        }
        return 1;
    case WM_ERASEBKGND:
        return 1;
    case WM_ACTIVATEAPP:
        if (g_pChitin->field_F8 || g_pChitin->field_1932) {
            return 0;
        }

        SetCursor(NULL);
        g_pChitin->OnAltTab(hWnd, wParam);
        break;
    case WM_SETCURSOR:
        return 1;
    case WM_INPUTLANGCHANGE:
        return 0;
    case WM_DISPLAYCHANGE:
        g_pChitin->OnDisplayChange();
        break;
    case WM_IME_STARTCOMPOSITION:
        if (g_pChitin->field_1A4) {
            g_pChitin->cImm.OnStartComposition();
            return 0;
        }
        break;
    case WM_IME_ENDCOMPOSITION:
        if (g_pChitin->field_1A4) {
            g_pChitin->cImm.OnEndComposition();
            return 0;
        }
        break;
    case WM_IME_COMPOSITION:
        if (g_pChitin->field_1A4) {
            g_pChitin->cImm.OnComposition(hWnd, wParam, lParam);
            return 0;
        }
        break;
    case WM_IME_NOTIFY:
        if (g_pChitin->field_1A4) {
            g_pChitin->cImm.OnNotify(hWnd, wParam, lParam);
            return 0;
        }
        break;
    case WM_IME_SETCONTEXT:
    case WM_IME_CONTROL:
    case WM_IME_COMPOSITIONFULL:
        if (g_pChitin->field_1A4) {
            return 0;
        }
        break;
    }

    // TODO: Incomplete.

    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}

// TODO: Check generated assembly once memory layout is complete.
//
// 0x78E2A0
CChitin::CChitin()
{
    m_nTickCount = 0;
    m_nAIPerSec = 0;
    m_nAIElasped = 0;
    m_nRenderTickCount = 0;
    m_nRenderPerSec = 0;
    m_nRenderElasped = 0;
    m_nThreads = 0;
    field_1A28 = 0;
    m_dwThreadIds[m_nThreads] = GetCurrentThreadId();

    HANDLE currentProcess = GetCurrentProcess();
    HANDLE currentThread = GetCurrentThread();
    if (DuplicateHandle(currentProcess, currentThread, currentProcess, &(m_hThreadHandles[m_nThreads]), 0, TRUE, DUPLICATE_SAME_ACCESS)) {
        m_nThreads++;
    }

    InitializeCriticalSection(&field_2FC);
    InitializeCriticalSection(&field_32C);
    InitializeCriticalSection(&field_314);
    InitializeCriticalSection(&field_344);
    InitializeCriticalSection(&field_C4);
    InitializeCriticalSection(&field_35C);
    InitializeCriticalSection(&field_394);
    InitializeCriticalSection(&field_3AC);
    InitializeCriticalSection(&field_1C32);

    InitializeVariables();
    InitVariables3D();

    OSVERSIONINFOA versionInfo;
    memset(&versionInfo, 0, sizeof(OSVERSIONINFOA));
    versionInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    GetVersionExA(&versionInfo);

    dwPlatformId = versionInfo.dwPlatformId;

    if (versionInfo.dwPlatformId == VER_PLATFORM_WIN32_NT) {
        cDimm.field_D6 = cDimm.dwTotalPhysicalMemory - 0x1000000;
    } else {
        cDimm.field_D6 = cDimm.dwTotalPhysicalMemory - 0x800000;
    }

    field_FE = 0;
    field_1C4C = 0;
    field_1A2A = 0;
    field_1A2E = 0;

    for (int i = 0; i < 16; i++) {
        field_1A32[i] = 1000;
    }

    memset(field_1A72, 0, sizeof(field_1A72));
    memset(field_1AB2, 0, sizeof(field_1AB2));
    memset(field_1AF2, 0, sizeof(field_1AF2));
    memset(field_1B32, 0, sizeof(field_1B32));

    field_110 = 0;
    field_114 = 0;

    field_118 = "";
    field_120 = "";
    field_11C = "";
    field_124 = 0;
    field_128 = 0;
    field_12C = "";
    field_131 = 0;
    field_132 = "";
    field_130 = 0;
    field_136 = 6;
    dword_8FB974 = 0;
    dword_8FB978 = 0;
    dword_8FB97C = 0;
    field_180 = 0;
    field_19C = 0;
    field_1C4A = 1;
    field_2EC = 0;
}

// TODO: Check generated assembly once memory layout is complete.
//
// 0x78E930
CChitin::~CChitin()
{
    if (cVideo.m_bIs3dAccelerated) {
        Shutdown3D();
    }

    m_lMouseWheel.RemoveAll();

    cDimm.DestroyKeyTable();
    cDimm.DumpAll();

    DeleteCriticalSection(&field_2FC);
    DeleteCriticalSection(&field_32C);
    DeleteCriticalSection(&field_314);
    DeleteCriticalSection(&field_C4);
    DeleteCriticalSection(&field_35C);

    if (m_eventTimer != NULL) {
        CloseHandle(m_eventTimer);
    }

    if (field_B4 != NULL) {
        CloseHandle(field_B4);
    }

    DeleteCriticalSection(&field_394);
    DeleteCriticalSection(&field_3AC);
    DeleteCriticalSection(&field_1C32);
}

// BINARY IDENTICAL
// 0x78FDF0
void CChitin::GetGameVersionInfo(HINSTANCE hInstance)
{
    char filename[256] = "Oct 16 2002";
    GetModuleFileNameA(hInstance, filename, 256);

    DWORD handle;
    DWORD size = GetFileVersionInfoSizeA(filename, &handle);
    if (size != 0) {
        BYTE* fileVersionInfo = new BYTE[size];
        GetFileVersionInfoA(filename, handle, size, fileVersionInfo);

        LPVOID buffer;
        UINT len;
        if (VerQueryValueA(fileVersionInfo, "\\StringFileInfo\\040904B0\\PrivateBuild", &buffer, &len)) {
            char buildDate[] = "Oct 16 2002";
            char buildTime[] = "15:36:32";
            char months[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
            buildDate[3] = '\0';

            int month = (strstr(months, buildDate) - months) / 3 + 1;
            buildVersionString.Format("%-2.2i%-2.2i%2.2s",
                month,
                atoi(&(buildDate[4])),
                buildTime);
        } else {
            buildVersionString = "";
        }

        if (VerQueryValueA(fileVersionInfo, "\\StringFileInfo\\040904B0\\ProductVersion", &buffer, &len)) {
            versionString = CString(reinterpret_cast<char*>(buffer));
        } else {
            versionString = "";
        }

        if (VerQueryValueA(fileVersionInfo, "\\StringFileInfo\\040904B0\\ProductName", &buffer, &len)) {
            name = CString(reinterpret_cast<char*>(buffer));
        } else {
            name = "";
        }

        if (fileVersionInfo != NULL) {
            delete[] fileVersionInfo;
        }
    }
}

// 0x790040
void CChitin::InitResources()
{
    ReadIniFiles();
    if (!cDimm.CreateKeyTable()) {
        UTIL_ASSERT_MSG(FALSE, "Error initializing key table, bad key file");
    }
}

// #binary-identical
// 0x790080
BOOL CChitin::InitInstance()
{
    POSITION pos = lEngines.GetHeadPosition();
    while (pos != NULL) {
        CWarp* pEngine = static_cast<CWarp*>(lEngines.GetNext(pos));
        if (pEngine != NULL) {
            pEngine->EngineInitialized();
        }
    }

    if (m_pStartingEngine != NULL) {
        SelectEngine(m_pStartingEngine);
    } else {
        ShutDown(-1, NULL, NULL);
    }

    m_hRSThread = reinterpret_cast<HANDLE>(_beginthread(::RSThreadMain, 0, NULL));
    field_4C = 1;
    m_hMessageThread = reinterpret_cast<HANDLE>(_beginthread(::MessageThreadMain, 0, NULL));
    m_hMusicThread = reinterpret_cast<HANDLE>(_beginthread(::MusicThreadMain, 0, NULL));

    TIMER_UPDATES_PER_SECOND = GetPrivateProfileIntA("Program Options",
        "Maximum Frame Rate",
        30,
        GetIniFileName());

    if (TIMER_UPDATES_PER_SECOND < 10 || TIMER_UPDATES_PER_SECOND > 60) {
        TIMER_UPDATES_PER_SECOND = 30;
    }

    TIMECAPS tc;
    timeGetDevCaps(&tc, sizeof(tc));

    field_C0 = min(max(tc.wPeriodMin, 5), tc.wPeriodMax);
    timeBeginPeriod(field_C0);

    SECURITY_ATTRIBUTES attrs;
    attrs.nLength = sizeof(attrs);
    attrs.lpSecurityDescriptor = NULL;
    attrs.bInheritHandle = FALSE;
    m_eventTimer = CreateEventA(&attrs, TRUE, TRUE, "BaldurTimerEvent");

    // __FILE__: C:\Projects\Icewind2\src\chitin\Chitin.cpp
    // __LINE__: 1808
    UTIL_ASSERT(m_eventTimer != NULL);

    field_BC = timeSetEvent(1000 / TIMER_UPDATES_PER_SECOND, 5, ::TimerFunction, 0, 1);

    m_hMainAIThread = reinterpret_cast<HANDLE>(_beginthread(::MainAIThread, 0, NULL));

    SCREEN_SAVE_ACTIVE_LOADED = SystemParametersInfoA(SPI_GETSCREENSAVEACTIVE, 0, &SCREEN_SAVE_ACTIVE, 0);
    if (SCREEN_SAVE_ACTIVE_LOADED) {
        SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE, FALSE, NULL, 0);
    }

    return TRUE;
}

// 0x790240
BOOL CChitin::InitializeServices(HWND hWnd)
{
    BOOL initialized;

    if (cVideo.m_bIs3dAccelerated) {
        initialized = cVideo.Initialize3d(hWnd, m_bFullscreen, 0);
    } else {
        initialized = cVideo.Initialize(hWnd, m_bFullscreen);
    }

    if (initialized) {
        cSoundMixer.Initialize(&cWnd, 16, GetNumberSoundChannels());
        field_142 = 1;
    }

    return initialized;
}

// 0x791610
void CChitin::OnDisplayChange()
{
    // TODO: Incomplete.
}

// 0x7917F0
void CChitin::ParseCommandLine()
{
    // TODO: Incomplete.
}

// 0x7926B0
int CChitin::WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    m_nQueryCancelAutoPlayMsgID = RegisterWindowMessageA("QueryCancelAutoPlay");

    m_sCommandLine = lpCmdLine;
    ParseCommandLine();

    if (!m_bFullscreen) {
        int nBpp = CUtil::GetCurrentBitsPerPixels();
        if (nBpp != 16 && nBpp != 24 && nBpp != 32) {
            CString s;
            s.LoadStringA(GetIDSInvalidVideoMode());
            MessageBoxA(NULL, s, name, 0);
            return 0;
        }
    }

    if (!InitApplication(hInstance, nCmdShow)) {
        field_1932 = 1;
        cWnd.Detach();
        return 0;
    }

    CoInitialize(NULL);

    HANDLE hCopy;
    HANDLE hCurrentThread = GetCurrentThread();
    HANDLE hCurrentProcess = GetCurrentProcess();
    DuplicateHandle(hCurrentProcess, hCurrentThread, hCurrentProcess, &hCopy, 0, FALSE, DUPLICATE_SAME_ACCESS);
    field_B4 = hCopy;

    InitInstance();

    MSG msg;
    while (1) {
        while (!PeekMessageA(&msg, NULL, 0, 0, 0)) {
            if (field_1932 == 0) {
                if (field_193A == 1) {
                    field_193A = 0;
                    m_bSynchronousUpdate = TRUE;
                    SynchronousUpdate();
                    m_bSynchronousUpdate = FALSE;
                    field_1936 = 1;
                }
            }
        }

        if (!GetMessageA(&msg, NULL, 0, 0)) {
            break;
        }

        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    CoUninitialize();

    if (SCREEN_SAVE_ACTIVE_LOADED) {
        SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE, SCREEN_SAVE_ACTIVE, NULL, 0);
    }

    return msg.wParam;
}

// Removes `readonly` file attribute on all files in special directories.
//
// BINARY IDENTICAL
// 0x792940
void CChitin::FixReadonlyPermissions()
{
    CString cache;
    CString mpsave;
    CString mptemp;
    CString save;
    CString temp;
    CString tempsave;

    char cwd[MAX_PATH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        cache = cwd;
        cache += "\\cache";

        mpsave = cwd;
        mpsave += "\\mpsave";

        mptemp = cwd;
        mptemp += "\\mptemp";

        save = cwd;
        save += "\\save";

        temp = cwd;
        temp += "\\temp";

        tempsave = cwd;
        tempsave += "\\tempsave";

        DoFixReadonlyPermissions(cache);
        DoFixReadonlyPermissions(mpsave);
        DoFixReadonlyPermissions(mptemp);
        DoFixReadonlyPermissions(save);
        DoFixReadonlyPermissions(temp);
        DoFixReadonlyPermissions(tempsave);
    }
}

// NOTE: Passing object produces unncessary copies at call sites.
//
// BINARY IDENTICAL
// 0x792B50
void CChitin::DoFixReadonlyPermissions(CString path)
{
    CFileFind fileFind;

    BOOLEAN exists = fileFind.FindFile(path);
    if (exists) {
        DWORD attrs = GetFileAttributes(path);
        attrs &= ~FILE_ATTRIBUTE_READONLY;
        SetFileAttributes(path, attrs);
    }

    path += "\\*.*";

    BOOLEAN working = fileFind.FindFile(path);
    while (working) {
        working = fileFind.FindNextFile();
        if (!fileFind.IsDots()) {
            if (fileFind.IsDirectory()) {
                DoFixReadonlyPermissions(fileFind.GetFilePath());
            }

            DWORD attrs = GetFileAttributes(fileFind.GetFilePath());
            attrs &= ~FILE_ATTRIBUTE_READONLY;
            SetFileAttributes(fileFind.GetFilePath(), attrs);
        }
    }
}

// #binary-identical
// 0x7902C0
void CChitin::InitializeVariables()
{
    m_bSynchronousUpdate = FALSE;
    field_1A0 = 0;
    field_1A4 = 0;
    field_13A = -1;
    field_13E = 0;
    field_142 = 0;
    field_E0 = 0;
    m_bFullscreen = TRUE;
    field_E2 = 1;
    field_E4 = 0;
    m_ptScreen.x = 0;
    m_ptScreen.y = 0;
    field_F8 = 0;
    m_nScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    m_nScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    field_F9 = 0;
    field_174 = 0;
    m_bMouseLButtonDown = FALSE;
    m_bMouseRButtonDown = FALSE;
    m_bMouseMButtonDown = FALSE;
    m_mouseDblClickTime = GetDoubleClickTime();
    if (m_mouseDblClickTime == 0) {
        m_mouseDblClickTime = 500;
    }

    m_mouseDblClickTime = 10 * m_mouseDblClickTime / (10000 / TIMER_UPDATES_PER_SECOND) + 1;
    m_mouseLDblClickCount = m_mouseDblClickTime;
    m_mouseMDblClickCount = m_mouseDblClickTime;
    m_mouseRDblClickCount = m_mouseDblClickTime;
    m_mouseDblClickSize.cx = GetSystemMetrics(SM_CXDOUBLECLK);
    m_mouseDblClickSize.cy = GetSystemMetrics(SM_CYDOUBLECLK);

    if (!SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &m_nKeyboardDelay, 0)) {
        m_nKeyboardDelay = 1;
    }

    m_nKeyboardDelay = 15 * (m_nKeyboardDelay + 1);

    if (!SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &m_nKeyboardSpeed, 0)) {
        m_nKeyboardSpeed = 8;
    }

    m_nKeyboardSpeed = TIMER_UPDATES_PER_SECOND / (m_nKeyboardSpeed + 1) + 1;

    if (GetSystemMetrics(SM_SWAPBUTTON)) {
        m_mouseLButton = VK_RBUTTON;
        m_mouseRButton = VK_LBUTTON;
    } else {
        m_mouseLButton = VK_LBUTTON;
        m_mouseRButton = VK_RBUTTON;
    }

    if (!SystemParametersInfo(SPI_GETWHEELSCROLLLINES, 0, &m_nWheelScrollLines, 0)) {
        m_nWheelScrollLines = 3;
    }

    field_16C = 0;
    field_170 = WM_MOUSEWHEEL;

    HWND hWnd = FindWindowA("MouseZ", "Magellan MSWHEEL");
    field_170 = RegisterWindowMessageA("MSWHEEL_ROLLMSG");

    UINT v1 = RegisterWindowMessageA("MSH_WHEELSUPPORT_MSG");
    UINT v2 = RegisterWindowMessageA("MSH_SCROLL_LINES_MSG");
    if (v1 != 0) {
        field_16C = SendMessage(hWnd, v1, 0, 0);
    } else {
        field_16C = 0;
    }

    int scrollLines;
    if (v2 != 0) {
        scrollLines = SendMessage(hWnd, v2, 0, 0);
    } else {
        scrollLines = 3;
    }

    if (hWnd != NULL && field_16C != 0) {
        m_nWheelScrollLines = scrollLines;
    }

    m_bInMouseWheelQueue = FALSE;
    field_1932 = 0;
    field_1936 = 1;
    field_193A = 0;
    field_1902 = 0;
    m_bEngineActive = FALSE;
    m_bInAsynchronousUpdate = FALSE;
    field_4C = 0;
    m_bExitRSThread = FALSE;
    m_bExitMainAIThread = FALSE;
    field_50 = 0;
    m_bExitMessageThread = FALSE;
    field_1906.x = 0;
    field_1906.y = 0;
    m_eventTimer = NULL;
    field_B4 = 0;
    m_hRSThread = NULL;
    m_hMusicThread = NULL;
    m_bExitMusicThread = FALSE;
    nAUCounter = 0;
    field_70 = 0;
    field_BC = 0;
    field_C0 = 0;
    pActiveEngine = NULL;
    m_pStartingEngine = NULL;

    srand(static_cast<unsigned int>(time(NULL)));
    rand();
}

// #binary-identical
// 0x7C8980
void CChitin::InitVariables3D()
{
    field_2F0 = 0;
    field_2F4 = 0;
}

// 0x7C8990
BOOL CChitin::Init3d()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x790860
void CChitin::SelectEngine(CWarp* pNewEngine)
{
    CVidMode* pPrevVidMode = NULL;
    if (pNewEngine != NULL) {
        EnterCriticalSection(&field_3AC);

        m_bEngineActive = FALSE;
        if (pActiveEngine != NULL) {
            pActiveEngine->EngineDeactivated();

            if (pActiveEngine->pVidMode != NULL) {
                pPrevVidMode = pActiveEngine->pVidMode;
                pActiveEngine->pVidMode->DeactivateVideoMode(pNewEngine->pVidMode);
            }

            if (!m_bInMouseWheelQueue) {
                m_bInMouseWheelQueue = TRUE;
                m_lMouseWheel.RemoveAll();
                m_bInMouseWheelQueue = FALSE;
            }

            m_mouseLDblClickCount = m_mouseDblClickTime;
            GetAsyncKeyState(m_mouseLButton);

            m_mouseRDblClickCount = m_mouseDblClickTime;
            GetAsyncKeyState(m_mouseRButton);

            m_mouseMDblClickCount = m_mouseDblClickTime;
            GetAsyncKeyState(VK_MBUTTON);

            SHORT nKeys = pNewEngine->GetNumVirtualKeys();
            if (nKeys > 0) {
                CKeyInfo* keys = pNewEngine->GetVirtualKeys();
                for (SHORT nKey = 0; nKey < nKeys; nKey++) {
                    keys[nKey].m_repeatCount = GetAsyncKeyState(keys[nKey].m_keyCode) != 0;
                }
            }
        }

        pNewEngine->pLastEngine = pActiveEngine;
        pActiveEngine = pNewEngine;
        pActiveEngine->pVidMode->ActivateVideoMode(pPrevVidMode, cWnd.GetSafeHwnd(), m_bFullscreen);
        cVideo.cVidBlitter.Init();
        pActiveEngine->EngineActivated();

        m_bEngineActive = TRUE;
        LeaveCriticalSection(&field_3AC);
    }
}

// #guess
// 0x7C8B10
void CChitin::Shutdown3D()
{
    // TODO: Incomplete.
}

// 0x790E10
void CChitin::TranslateType(int nType, CString& sRes)
{
    switch (nType) {
    case 1:
        sRes = "BMP";
        break;
    case 4:
        sRes = "WAV";
        break;
    case 5:
        sRes = "WFX";
        break;
    case 6:
        sRes = "PLT";
        break;
    case 1000:
        sRes = "BAM";
        break;
    case 1003:
        sRes = "TIS";
        break;
    case 1004:
        sRes = "MOS";
        break;
    case 1100:
        sRes = "BAH";
        break;
    default:
        sRes = "RES";
        break;
    }
}

// 0x790EF0
int CChitin::TranslateType(const CString& sRes)
{
    if (sRes.CompareNoCase("TIS") == 0)
        return 1003;
    if (sRes.CompareNoCase("BAM") == 0)
        return 1000;
    if (sRes.CompareNoCase("BAH") == 0)
        return 1100;
    if (sRes.CompareNoCase("BMP") == 0)
        return 1;
    if (sRes.CompareNoCase("MOS") == 0)
        return 1004;
    if (sRes.CompareNoCase("WAV") == 0)
        return 4;
    if (sRes.CompareNoCase("WFX") == 0)
        return 5;
    if (sRes.CompareNoCase("PLT") == 0)
        return 6;

    return 0xFFFF;
}

// 0x790FE0
int CChitin::InitApplication(HINSTANCE hInstance, int nCmdShow)
{
    CString sIcon = GetIconRes();

    WNDCLASSEXA wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = WS_EX_TOPMOST;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    if (sIcon.Compare("") != 0) {
        wc.hIcon = LoadIconA(hInstance, sIcon);
    }
    wc.hCursor = LoadCursorA(NULL, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(4));
    wc.lpszClassName = "ChitinClass";

    if (!RegisterClassExA(&wc)) {
        return 0;
    }

    m_hInstance = hInstance;

    if (cVideo.m_bIs3dAccelerated) {
        if (!Init3d()) {
            return 0;
        }
    }

    int rc = InitGraphics();
    if (rc != 0) {
        LoadOptions();
    }

    return rc;
}

// 0x791150
BOOL CChitin::InitGraphics()
{
    if (m_ptScreen.x < 0 || m_ptScreen.x >= GetSystemMetrics(SM_CXFULLSCREEN) - CVideo::SCREENWIDTH) {
        m_ptScreen.x = (GetSystemMetrics(SM_CXFULLSCREEN) - CVideo::SCREENWIDTH) / 2;
    }

    if (m_ptScreen.y < 0 || m_ptScreen.y >= GetSystemMetrics(SM_CYFULLSCREEN) - CVideo::SCREENHEIGHT) {
        m_ptScreen.y = (GetSystemMetrics(SM_CYFULLSCREEN) - CVideo::SCREENHEIGHT) / 2;
    }

    HWND hWnd = CreateWindowExA(WS_EX_TOPMOST,
        "ChitinClass",
        name,
        WS_POPUP | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU,
        m_ptScreen.x,
        m_ptScreen.y,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        m_hInstance,
        NULL);
    if (dwPlatformId == VER_PLATFORM_WIN32_NT) {
        HMODULE hKernel32 = GetModuleHandleA("Kernel32");
        if (hKernel32 != NULL) {
            typedef BOOL(__stdcall SetProcessAffinityMaskFunc)(HANDLE, DWORD);

            SetProcessAffinityMaskFunc* pfnSetProcessAffinityMask = reinterpret_cast<SetProcessAffinityMaskFunc*>(GetProcAddress(hKernel32, "SetProcessAffinityMask"));
            if (pfnSetProcessAffinityMask != NULL) {
                HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
                pfnSetProcessAffinityMask(hProcess, 1);
                CloseHandle(hProcess);
            }
        }
    }

    if (hWnd == NULL) {
        return FALSE;
    }

    cWnd.Attach(hWnd);

    if (!InitializeServices(hWnd)) {
        return FALSE;
    }

    UpdateWindow(hWnd);
    SetCursor(NULL);

    return TRUE;
}

// 0x7912B0
void CChitin::EnginesGameInit()
{
    POSITION pos = lEngines.GetHeadPosition();
    while (pos != NULL) {
        CWarp* pEngine = static_cast<CWarp*>(lEngines.GetNext(pos));
        if (pEngine != NULL) {
            pEngine->EngineGameInit();
        }
    }
}

// 0x7912D0
void CChitin::EnginesGameUninit()
{
    POSITION pos = lEngines.GetHeadPosition();
    while (pos != NULL) {
        CWarp* pEngine = static_cast<CWarp*>(lEngines.GetNext(pos));
        if (pEngine != NULL) {
            pEngine->EngineGameUninit();
        }
    }
}

// 0x7912F0
BOOLEAN CChitin::OnAltEnter(BOOLEAN a1)
{
    if (m_bFullscreen) {
        if (field_E4) {
            return TRUE;
        }
    } else {
        RECT rect;
        GetWindowRect(cWnd.GetSafeHwnd(), &rect);
        m_ptScreen.x = rect.left;
        m_ptScreen.y = rect.top;
    }

    field_F8 = 1;
    field_E0 = 1;

    if (pActiveEngine != NULL) {
        pActiveEngine->EngineDeactivated();
    }

    INT nCurrentSong = cSoundMixer.m_nCurrentSong;
    cSoundMixer.StopMusic(TRUE);

    CVidMode* pCurrentVidMode = cVideo.m_pCurrentVidMode;
    field_142 = 0;

    cSoundMixer.CleanUp();
    cVideo.CleanUp();

    HWND hWnd = cWnd.Detach();
    DestroyWindow(hWnd);

    int nBpp = CUtil::GetCurrentBitsPerPixels();
    if (nBpp != 16 && nBpp != 24 && nBpp != 32) {
        CString s;
        s.LoadStringA(GetIDSInvalidVideoMode());
        MessageBoxA(NULL, s, name, 0);
        ShutDown(-1, NULL, NULL);
        return FALSE;
    }

    FlipFullScreenMode(a1);

    cVideo.m_pCurrentVidMode = pCurrentVidMode;
    if (!InitGraphics()) {
        ShutDown(-1, NULL, NULL);
        return FALSE;
    }

    SetSoundVolumes();
    cSoundMixer.StartSong(nCurrentSong, 1);

    if (cDimm.field_294) {
        SetCDSwitchActivateEngine(TRUE);
    } else if (cProgressBar.m_bProgressBarActivated) {
        SetProgressBarActivateEngine(TRUE);
    } else {
        if (pActiveEngine != NULL) {
            pActiveEngine->EngineActivated();
        }
    }

    Resume();
    field_F8 = 0;

    return TRUE;
}

// 0x7914D0
void CChitin::OnAltTab(HWND hWnd, BOOL a2)
{
    if (a2 == 1) {
        field_1C4A = 1;
        if (pActiveEngine != NULL) {
            CVidMode* pVidMode = pActiveEngine->pVidMode;
            if (pVidMode != NULL) {
                field_F8 = 1;
                if (cVideo.m_bIs3dAccelerated) {
                    if (m_bFullscreen) {
                        cVideo.m_pCurrentVidMode = pVidMode;
                        cVideo.Initialize3d(hWnd, TRUE, 1);
                    }
                } else {
                    pVidMode->RestoreSurfaces();
                }
                field_F8 = 0;

                if (cDimm.field_294) {
                    SetCDSwitchActivateEngine(TRUE);
                    Resume();
                    byte_8FB950 = 0;
                } else if (cProgressBar.m_bProgressBarActivated) {
                    SetProgressBarActivateEngine(TRUE);
                    Resume();
                    byte_8FB950 = 0;
                } else {
                    if (pActiveEngine != NULL) {
                        pActiveEngine->EngineActivated();
                    }
                    Resume();
                    byte_8FB950 = 0;
                }
            }
        }
    } else {
        byte_8FB950 = 1;
        field_1C4A = 0;
        field_E0 = 1;

        if (pActiveEngine != NULL) {
            pActiveEngine->EngineDeactivated();
        }

        if (cVideo.m_bIs3dAccelerated) {
            if (m_bFullscreen) {
                cVideo.CleanUp();
                CloseWindow(hWnd);
            }
        }
    }
}

// 0x78EBA0
void CChitin::RegisterThread()
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\Chitin.cpp
    // __LINE__: 670
    UTIL_ASSERT(m_nThreads < CHITIN_MAX_THREADS);

    m_dwThreadIds[m_nThreads] = GetCurrentThreadId();

    HANDLE hProcess = GetCurrentProcess();
    HANDLE hThread = GetCurrentThread();
    if (DuplicateHandle(hProcess, hThread, hProcess, &(m_hThreadHandles[m_nThreads]), 0, TRUE, DUPLICATE_SAME_ACCESS)) {
        m_nThreads++;
    }
}

// 0x78EC20
void CChitin::SuspendThreads()
{
    DWORD currentThreadId = GetCurrentThreadId();
    for (USHORT k = 0; k < m_nThreads; k++) {
        if (m_dwThreadIds[k] != currentThreadId) {
            SuspendThread(m_hThreadHandles[k]);
        }
    }
}

// 0x78EC70
void CChitin::AddEngine(CWarp* pNewEngine)
{
    if (pNewEngine != NULL) {
        lEngines.AddTail(pNewEngine);
    }
}

// 0x78EC90
CRes* CChitin::AllocResObject(int nType)
{
    switch (nType) {
    case 1:
        return new CResBitmap();
    case 4:
        return new CResWave();
    case 5:
        return new CResBinary();
    case 6:
        return new CResPLT();
    case 1000:
        return new CResCell();
    case 1004:
        return new CResMosaic();
    case 1100:
        return new CResCellHeader();
    case 1003:
        return new CResTile();
    default:
        return new CRes();
    }
}

// 0x78FC90
void CChitin::DestroyServices()
{
    DWORD dwSuspendCount;

    // NOTE: Uninline.
    cImm.CleanUp();

    m_bExitRSThread = TRUE;
    if (m_hRSThread != NULL) {
        do {
            dwSuspendCount = ResumeThread(m_hRSThread);
            if (dwSuspendCount == -1) {
                GetLastError();
                break;
            }
        } while (dwSuspendCount > 1);
    }

    m_bExitMessageThread = TRUE;
    if (m_hMessageThread != NULL) {
        do {
            dwSuspendCount = ResumeThread(m_hMessageThread);
            if (dwSuspendCount == -1) {
                GetLastError();
                break;
            }
        } while (dwSuspendCount > 1);
    }

    m_bExitMainAIThread = TRUE;
    if (m_hMainAIThread != NULL) {
        do {
            dwSuspendCount = ResumeThread(m_hMainAIThread);
            if (dwSuspendCount == -1) {
                GetLastError();
                break;
            }
        } while (dwSuspendCount > 1);
    }

    m_bExitMusicThread = TRUE;
    if (m_hMusicThread != NULL) {
        do {
            dwSuspendCount = ResumeThread(m_hMusicThread);
            if (dwSuspendCount == -1) {
                GetLastError();
                break;
            }
        } while (dwSuspendCount > 1);
    }

    field_142 = 0;
    cSoundMixer.CleanUp();
    cVideo.CleanUp();

    // NOTE: Ugly, probably `CVideo` has additional `CleanUp`-like method
    // inlined into destructor.
    cVideo.~CVideo();

    for (USHORT nIndex = 0; nIndex < m_nThreads; nIndex++) {
        CloseHandle(m_hThreadHandles[nIndex]);
    }
}

// 0x78F0E0
void CChitin::AsynchronousUpdate(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    int v1 = 0;
    CSingleLock lock(&field_194A, FALSE);

    if (!field_E0) {
        nAUCounter++;

        if (field_4C && !m_bExitRSThread) {
            cDimm.ResumeServicing();
        }

        m_nAIElasped++;

        DWORD nTickCount = GetTickCount();
        if (nTickCount - m_nTickCount > 1000) {
            m_nAIPerSec = m_nAIElasped;
            m_nAIElasped = 0;
            m_nTickCount = nTickCount;
        }

        if (m_bEngineActive && pActiveEngine != NULL) {
            if (!m_bInMouseWheelQueue) {
                m_bInMouseWheelQueue = TRUE;

                WPARAM wParam;
                LONG nDelta = 0;

                if (!m_lMouseWheel.IsEmpty()) {
                    do {
                        wParam = reinterpret_cast<WPARAM>(m_lMouseWheel.RemoveHead());
                        nDelta += HIWORD(wParam);
                    } while (!m_lMouseWheel.IsEmpty());
                } else {
                    wParam = 0;
                }

                BOOL bForward;
                LONG nTicks;
                LONG nRemainder;
                if (nDelta < 0) {
                    bForward = FALSE;
                    nTicks = -(-nDelta / WHEEL_DELTA);
                    nRemainder = -(-nDelta % WHEEL_DELTA);
                } else {
                    bForward = TRUE;
                    nTicks = nDelta / WHEEL_DELTA;
                    nRemainder = nDelta % WHEEL_DELTA;
                }

                if (nRemainder != 0) {
                    m_lMouseWheel.AddTail(reinterpret_cast<void*>(MAKEWPARAM(LOWORD(wParam), nRemainder)));
                }

                m_bInMouseWheelQueue = FALSE;

                if (nTicks > 0) {
                    if (pActiveEngine->CheckMouseWheel()) {
                        pActiveEngine->OnMouseWheel(bForward,
                            nTicks,
                            m_nWheelScrollLines,
                            wParam);
                    }
                }
            }

            CVidMode* pVidMode = GetCurrentVideoMode();

            CPoint pt;
            GetCursorPos(&pt);
            if (m_bFullscreen || PtInRect(&field_E8, pt)) {
                ScreenToClient(cWnd, &pt);

                if (!field_F9
                    || m_bFullscreen
                    || (pt.x != 0
                        && pt.x != CVideo::SCREENWIDTH - 1
                        && pt.y != 0
                        && pt.y != CVideo::SCREENHEIGHT - 1)) {
                    if (pVidMode != NULL) {
                        pVidMode->field_D8 = 1;
                    }
                } else {
                    pt.x = -1;
                    pt.y = -1;

                    if (pVidMode != NULL) {
                        pVidMode->field_D8 = 0;
                    }
                }

                if (pt.x == field_1906.x && pt.y == field_1906.y) {
                    if (v1 > 0) {
                        if (pActiveEngine->CheckMouseMove()) {
                            pActiveEngine->OnMouseMove(pt);
                        }
                    }
                } else {
                    lock.Lock();
                    field_1906 = pt;
                    lock.Unlock();

                    field_1902 = 0;

                    if (pActiveEngine->CheckMouseMove()) {
                        pActiveEngine->OnMouseMove(pt);
                    }
                }
            } else {
                if (field_F9 && (pt.x == 0 || pt.x == m_nScreenWidth - 1)) {
                    pt.x = min(max(pt.x, 0), m_nScreenWidth - 1);

                    if (pVidMode != NULL) {
                        pVidMode->field_D8 = 1;
                    }
                    pt.y = pt.y * (CVideo::SCREENHEIGHT - 1) / (m_nScreenHeight - 1);
                } else if (field_F9 && (pt.y == 0 || pt.y == m_nScreenHeight - 1)) {
                    pt.x = pt.x * (CVideo::SCREENWIDTH - 1) / (m_nScreenWidth - 1);
                    pt.y = min(max(pt.y, 0), m_nScreenHeight - 1);

                    if (pVidMode != NULL) {
                        pVidMode->field_D8 = 1;
                    }
                } else {
                    pt.x = -1;
                    pt.y = -1;

                    if (pVidMode != NULL) {
                        pVidMode->field_D8 = 0;
                    }
                }

                if (pt.x == field_1906.x && pt.y == field_1906.y) {
                    if (v1 > 0) {
                        if (pActiveEngine->CheckMouseMove()) {
                            pActiveEngine->OnMouseMove(pt);
                        }
                    }
                } else {
                    lock.Lock();
                    field_1906 = pt;
                    lock.Unlock();

                    field_1902 = 0;

                    if (pActiveEngine->CheckMouseMove()) {
                        pActiveEngine->OnMouseMove(pt);
                    }
                }
            }

            if (pActiveEngine->CheckSystemKeyCtrl()) {
                if (GetAsyncKeyState(VK_CONTROL)) {
                    pActiveEngine->SetSystemKeyCtrl(TRUE);
                } else {
                    pActiveEngine->SetSystemKeyCtrl(FALSE);
                }
            }

            if (pActiveEngine->CheckSystemKeyShift()) {
                if (GetAsyncKeyState(VK_SHIFT)) {
                    pActiveEngine->SetSystemKeyShift(TRUE);
                } else {
                    pActiveEngine->SetSystemKeyShift(FALSE);
                }
            }

            SHORT nMenuState = GetAsyncKeyState(VK_MENU);
            if (pActiveEngine->CheckSystemKeyMenu()) {
                if (nMenuState) {
                    pActiveEngine->SetSystemKeyMenu(TRUE);
                } else {
                    pActiveEngine->SetSystemKeyMenu(FALSE);
                }
            }

            if (pActiveEngine->CheckSystemKeyCapsLock()) {
                if ((field_FE & 1) != 0) {
                    pActiveEngine->SetSystemKeyCapsLock(TRUE);
                } else {
                    pActiveEngine->SetSystemKeyCapsLock(FALSE);
                }
            }

            if (pActiveEngine->CheckSystemKeyMenu() || nMenuState == 0) {
                if (field_1906.x != -1) {
                    if (pActiveEngine->CheckMouseLButton()) {
                        SHORT nLButtonState = GetAsyncKeyState(m_mouseLButton);
                        m_mouseLDblClickCount++;

                        if (m_bMouseLButtonDown) {
                            if (nLButtonState >= 0) {
                                m_bMouseLButtonDown = FALSE;
                                pActiveEngine->OnLButtonUp(field_1906);
                            }
                        } else {
                            if (nLButtonState >= 0) {
                                if ((nLButtonState & 1) != 0) {
                                    if (m_mouseLDblClickCount >= m_mouseDblClickTime
                                        || abs(field_1906.x - m_mouseLDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                        || abs(field_1906.y - m_mouseLDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                        pActiveEngine->OnLButtonDown(field_1906);
                                        m_mouseLDblClickPoint = field_1906;
                                        m_mouseLDblClickCount = 0;
                                    } else {
                                        pActiveEngine->OnLButtonDblClk(field_1906);
                                        m_mouseLDblClickCount = m_mouseDblClickTime;
                                    }

                                    pActiveEngine->OnLButtonUp(field_1906);
                                }
                            } else {
                                m_bMouseLButtonDown = TRUE;
                                if (m_mouseLDblClickCount >= m_mouseDblClickTime
                                    || abs(field_1906.x - m_mouseLDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                    || abs(field_1906.y - m_mouseLDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                    pActiveEngine->OnLButtonDown(field_1906);
                                    m_mouseLDblClickPoint = field_1906;
                                    m_mouseLDblClickCount = 0;
                                } else {
                                    pActiveEngine->OnLButtonDblClk(field_1906);
                                    m_mouseLDblClickCount = m_mouseDblClickTime;
                                }
                            }
                        }
                    }

                    if (pActiveEngine->CheckMouseRButton()) {
                        SHORT nRButtonState = GetAsyncKeyState(m_mouseRButton);
                        m_mouseRDblClickCount++;

                        if (m_bMouseRButtonDown) {
                            if (nRButtonState >= 0) {
                                m_bMouseRButtonDown = FALSE;
                                pActiveEngine->OnRButtonUp(field_1906);
                            }
                        } else {
                            if (nRButtonState >= 0) {
                                if ((nRButtonState & 1) != 0) {
                                    if (m_mouseRDblClickCount >= m_mouseDblClickTime
                                        || abs(field_1906.x - m_mouseRDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                        || abs(field_1906.y - m_mouseRDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                        pActiveEngine->OnRButtonDown(field_1906);
                                        m_mouseRDblClickPoint = field_1906;
                                        m_mouseRDblClickCount = 0;
                                    } else {
                                        pActiveEngine->OnRButtonDblClk(field_1906);
                                        m_mouseRDblClickCount = m_mouseDblClickTime;
                                    }

                                    pActiveEngine->OnRButtonUp(field_1906);
                                }
                            } else {
                                m_bMouseRButtonDown = TRUE;
                                if (m_mouseRDblClickCount >= m_mouseDblClickTime
                                    || abs(field_1906.x - m_mouseRDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                    || abs(field_1906.y - m_mouseRDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                    pActiveEngine->OnRButtonDown(field_1906);
                                    m_mouseRDblClickPoint = field_1906;
                                    m_mouseRDblClickCount = 0;
                                } else {
                                    pActiveEngine->OnRButtonDblClk(field_1906);
                                    m_mouseRDblClickCount = m_mouseDblClickTime;
                                }
                            }
                        }
                    }

                    if (pActiveEngine->CheckMouseMButton()) {
                        SHORT nMButtonState = GetAsyncKeyState(VK_MBUTTON);
                        m_mouseMDblClickCount++;

                        if (m_bMouseMButtonDown) {
                            if (nMButtonState >= 0) {
                                m_bMouseMButtonDown = FALSE;
                                pActiveEngine->OnMButtonUp(field_1906);
                            }
                        } else {
                            if (nMButtonState >= 0) {
                                if ((nMButtonState & 1) != 0) {
                                    if (m_mouseMDblClickCount >= m_mouseDblClickTime
                                        || abs(field_1906.x - m_mouseMDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                        || abs(field_1906.y - m_mouseMDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                        pActiveEngine->OnMButtonDown(field_1906);
                                        m_mouseMDblClickPoint = field_1906;
                                        m_mouseMDblClickCount = 0;
                                    } else {
                                        pActiveEngine->OnMButtonDblClk(field_1906);
                                        m_mouseMDblClickCount = m_mouseDblClickTime;
                                    }

                                    pActiveEngine->OnMButtonUp(field_1906);
                                }
                            } else {
                                m_bMouseMButtonDown = TRUE;
                                if (m_mouseMDblClickCount >= m_mouseDblClickTime
                                    || abs(field_1906.x - m_mouseMDblClickPoint.x) > m_mouseDblClickSize.cx / 2
                                    || abs(field_1906.y - m_mouseMDblClickPoint.y) > m_mouseDblClickSize.cy / 2) {
                                    pActiveEngine->OnMButtonDown(field_1906);
                                    m_mouseMDblClickPoint = field_1906;
                                    m_mouseMDblClickCount = 0;
                                } else {
                                    pActiveEngine->OnMButtonDblClk(field_1906);
                                    m_mouseMDblClickCount = m_mouseDblClickTime;
                                }
                            }
                        }
                    }
                }
            }

            SHORT nKeys = pActiveEngine->GetNumVirtualKeys();
            SHORT nKeysFlags = 0;
            if (nKeys > 0) {
                CKeyInfo* pKeys = pActiveEngine->GetVirtualKeys();
                BYTE* pKeysFlags = pActiveEngine->GetVirtualKeysFlags();

                for (SHORT nKey = 0; nKey < nKeys; nKey++) {
                    SHORT nState = GetAsyncKeyState(pKeys[nKey].m_keyCode);
                    if (nState == 0) {
                        pKeys[nKey].m_repeatCount = 0;
                    } else if (nState == 0x8000) {
                        pKeys[nKey].m_repeatCount++;
                    } else {
                        BOOL bFirstPress = pKeys[nKey].m_repeatCount == 0;
                        pKeys[nKey].m_repeatCount++;
                        if (bFirstPress) {
                            pKeysFlags[nKeysFlags++] = pKeys[nKey].m_keyCode;
                        } else {
                            if (pKeys[nKey].m_repeatCount >= pKeys[nKey].m_repeatDelay
                                && ((pKeys[nKey].m_repeatCount - pKeys[nKey].m_repeatDelay) % pKeys[nKey].m_repeatRate) == 0) {
                                pKeysFlags[nKeysFlags++] = pKeys[nKey].m_keyCode;
                            }
                        }

                        if ((nState & 0x8000) == 0) {
                            pKeys[nKey].m_repeatCount = 0;
                        }
                    }
                }

                if (nKeysFlags != 0) {
                    pActiveEngine->OnKeyDown(nKeysFlags);
                }
            }

            pActiveEngine->TimerUpdate();
            pActiveEngine->TimerAsynchronousUpdate();
        }
    }
}

// #guess
// 0x78FDE0
CWnd* CChitin::GetWnd()
{
    return &cWnd;
}

// 0x790570
void CChitin::Resume()
{
    m_mouseLDblClickCount = m_mouseDblClickTime;
    GetAsyncKeyState(m_mouseLButton);

    m_mouseRDblClickCount = m_mouseDblClickTime;
    GetAsyncKeyState(m_mouseRButton);

    m_mouseMDblClickCount = m_mouseDblClickTime;
    GetAsyncKeyState(VK_MBUTTON);

    if (pActiveEngine != NULL) {
        SHORT nKeys = pActiveEngine->GetNumVirtualKeys();
        if (nKeys > 0) {
            CKeyInfo* keys = pActiveEngine->GetVirtualKeys();
            for (SHORT nKey = 0; nKey < nKeys; nKey++) {
                keys[nKey].m_repeatCount = GetAsyncKeyState(keys[nKey].m_keyCode) != 0;
            }
        }
    }

    field_E0 = 0;
}

// #not-binary-identical
// 0x790600
void CChitin::ReadIniFiles()
{
    CString temp;
    char buffer[256];

    if (field_4C == 0) {
        GetPrivateProfileStringA("Alias", "HD0:", "", buffer, sizeof(buffer), GetIniFileName());
        if (strlen(buffer) == 0) {
            temp = "path:=.\\";

            CAlias* alias = new CAlias(temp);
            if (!lAliases.AddAlias(alias)) {
                delete alias;
            }
        } else {
            temp = "HD0:=";
            temp += buffer;
            temp.MakeLower();

            CAlias* alias = new CAlias(temp);
            if (!lAliases.AddAlias(alias)) {
                delete alias;
            }

            for (unsigned char cd = 1;; cd++) {
                temp.Format("CD%d:", cd);

                memset(buffer, 0, sizeof(buffer));
                GetPrivateProfileStringA("Alias", temp, "", buffer, sizeof(buffer), GetIniFileName());
                if (strlen(buffer) == 0) {
                    break;
                }

                temp += "=";
                temp += buffer;
                temp.MakeLower();

                CAlias* alias = new CAlias(temp);
                if (!lAliases.AddAlias(alias)) {
                    delete alias;
                }
            }
        }
    }
}

// 0x78E6E0
DWORD CChitin::GetIDSInvalidVideoMode()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSOpenGLDll()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSExclusiveMode()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSChoosePixelFormat()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSSetPixelFormat()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSSetGameResolution()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSSetGameBitDepth()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSBadDeskTopBitDepth()
{
    return 0;
}

// 0x78E6E0
DWORD CChitin::GetIDSWindowsFonts()
{
    return 0;
}

// 0x78E6F0
const CString& CChitin::GetIconRes()
{
    return ICON_RES_ID;
}

// 0x78E700
void CChitin::GetScreenShotFilePrefix(CString& szGameFileName)
{
    szGameFileName = DEFAULT_PRINTSCREEN_FILE_NAME;
}

// 0x78E720
void CChitin::SetProgressBar(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
}

// 0x78E6E0
BOOL CChitin::FontRectOutline()
{
    return FALSE;
}

// 0x799E60
void CChitin::SetProgressBarActivateEngine(BOOL bValue)
{
}

// 0x799E60
void CChitin::SetCDSwitchActivateEngine(BOOL bValue)
{
}

// 0x78E730
void CChitin::OnMultiplayerSessionToClose()
{
}

// 0x78E770
void CChitin::FlipFullScreenMode(BOOLEAN a2)
{
    BOOL bWasFullscreen = m_bFullscreen;
    m_bFullscreen = bWasFullscreen == FALSE;
    field_E2 = bWasFullscreen == FALSE;
}

// 0x78E790
const char* CChitin::GetIniFileName()
{
    return "Chitin.ini";
}

// 0x78E7A0
const char* CChitin::GetKeyFileName()
{
    return "Chitin.key";
}

// 0x78E7B0
const char* CChitin::GetLogFileName()
{
    return "Chitin.log";
}

// 0x78E7C0
const char* CChitin::GetErrFileName()
{
    return "Chitin.err";
}

// 0x799E60
void CChitin::SaveBitsPerPixel(USHORT nBpp)
{
}

// 0x78E7D0
UINT CChitin::GetSavedBitsPerPixel()
{
    return GetPrivateProfileIntA("Program Options", "BitsPerPixel", CVideo::word_85DE2C, GetIniFileName());
}

// 0x78E800
BYTE CChitin::GetNumberSoundChannels()
{
    return 16;
}

// 0x78E810
void CChitin::UnloadFonts()
{
    CVidFont::UnloadAllFonts();
}

// 0x78E830
DWORD CChitin::GetCloseConfirmationFlags()
{
    return 0x24;
}

// 0x78E840
void CChitin::GetCloseConfirmationStr(CString& sString)
{
    sString = "";
}

// 0x78E840
void CChitin::GetGameSpyGameName(CString& sGameSpyName)
{
    sGameSpyName = "";
}

// 0x78E840
void CChitin::GetGameSpyCode(CString& sGameSpyCode)
{
    sGameSpyCode = "";
}

// 0x78E860
void CChitin::GetPanicCDStrings(CString& sMediaRemoved, CString& sPlaceCD, CString& sInDrive)
{
    sMediaRemoved = "";
    sPlaceCD = "";
    sInDrive = "";
}

// 0x78E730
void CChitin::OnMixerInitialize()
{
}

// 0x799E20
BOOL CChitin::Is3DSound(int nSoundChannel)
{
    return FALSE;
}

// 0x78E890
float CChitin::GetSoundReverbMix(int nSoundChannel, int nReverb)
{
    return 0.0;
}

// 0x78E6E0
LONG CChitin::GetMovieVolume()
{
    return 0;
}

// 0x78E6E0
BOOL CChitin::GetEAXActive()
{
    return FALSE;
}

// 0x4051C0
int CChitin::GetSoundEnvironment(EAXPRESET& preset, int environment)
{
    return EAX_ENVIRONMENT_GENERIC;
}

// 0x78E730
void CChitin::RedrawScreen()
{
}

// 0x78E820
WORD CChitin::GetMultiplayerGameSpyPort()
{
    return 0;
}

// 0x78E820
WORD CChitin::GetMultiplayerDirectPlayPort()
{
    return 0;
}

// 0x799E60
void CChitin::SetRenderCount(BYTE nCount)
{
}

// 0x78E730
void CChitin::LoadOptions()
{
}

// 0x78E730
void CChitin::PreLoadFonts()
{
}

// 0x78E730
void CChitin::SetSoundVolumes()
{
}

// 0x7909C0
void CChitin::ShutDown(int nLineNumber, const char* szFileName, const char* text)
{
    CString sString;

    if (!field_1932) {
        field_1932 = TRUE;

        field_E0 = 1;
        if (field_BC != 0) {
            field_BC = timeKillEvent(field_BC);
        }
        timeEndPeriod(field_C0);

        POSITION pos = lEngines.GetHeadPosition();
        while (pos != NULL) {
            CWarp* pEngine = static_cast<CWarp*>(lEngines.GetAt(pos));
            if (pEngine != NULL) {
                pEngine->EngineDestroyed();
            }

            lEngines.RemoveAt(pos);
            pos = lEngines.GetHeadPosition();
        }

        DestroyServices();

        if (nLineNumber != -1) {
            const char* szFileNameOnly = szFileName;
            if (strrchr(szFileName, '\\') != NULL) {
                szFileNameOnly = strrchr(szFileName, '\\') + 1;
            }

            if (text != NULL) {
                sString.Format("An Assertion failed in %s at line number %d \n Programmer says: %s",
                    szFileNameOnly,
                    nLineNumber,
                    text);
            } else {
                sString.Format("An Assertion failed in %s at line number %d",
                    szFileNameOnly,
                    nLineNumber);
            }

            if (name.Compare("") != 0) {
                MessageBoxA(NULL, sString, name, MB_SYSTEMMODAL | MB_ICONERROR);
            } else {
                MessageBoxA(NULL, sString, "Assertion", MB_SYSTEMMODAL | MB_ICONERROR);
            }
        }

        RECT windowRect;
        GetWindowRect(cWnd.GetSafeHwnd(), &windowRect);
        m_ptScreen.x = windowRect.left;
        m_ptScreen.y = windowRect.top;

        HWND hWnd = cWnd.Detach();
        if (hWnd != NULL) {
            DestroyWindow(hWnd);
        }

        PostQuitMessage(0);
    }
}

// 0x790B70
void CChitin::SynchronousUpdate()
{
    // TODO: Incomplete.

    if (m_bEngineActive && pActiveEngine != NULL && !field_E0) {
        if (cDimm.field_294 == 1) {
            // TODO: Incomplete.
        } else if (cProgressBar.m_bProgressBarActivated == 1) {
            // TODO: Incomplete.
        } else {
            m_nRenderElasped++;

            DWORD nTickCount = GetTickCount();
            if (nTickCount - m_nRenderTickCount > 1000) {
                m_nRenderPerSec = m_nRenderElasped;
                m_nRenderElasped = 0;
                m_nRenderTickCount = nTickCount;
            }

            pActiveEngine->TimerSynchronousUpdate();
        }
    }
}

// NOTE: Inlined in many places.
//
// 0x597E00
CVidMode* CChitin::GetCurrentVideoMode()
{
    if (pActiveEngine != NULL) {
        return pActiveEngine->pVidMode;
    }
    return NULL;
}

// 0x793540
CString CChitin::GetFontName()
{
    return m_sFontName;
}

// 0x7928A0
static void MessageThreadMain(void* userInfo)
{
    g_pChitin->MessageThreadMain(userInfo);
}

// 0x7928C0
static void RSThreadMain(void* userInfo)
{
    g_pChitin->RSThreadMain(userInfo);
}

// 0x7928E0
static void MainAIThread(void* userInfo)
{
    g_pChitin->MainAIThread(userInfo);
}

// 0x792900
static void MusicThreadMain(void* userInfo)
{
    g_pChitin->MusicThreadMain(userInfo);
}

// 0x792920
static void CALLBACK TimerFunction(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    SetEvent(g_pChitin->m_eventTimer);
}

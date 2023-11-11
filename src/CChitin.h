#ifndef CCHITIN_H_
#define CCHITIN_H_

#include "mfc.h"

#include "CAliasList.h"
#include "CDimm.h"
#include "CGameSpy.h"
#include "CImm.h"
#include "CNetwork.h"
#include "CProgressBar.h"
#include "CSoundMixer.h"
#include "CUnknown1.h"
#include "CVideo.h"

#define CHITIN_MAX_THREADS 10

class CRes;
class CVidMode;
class CWarp;

class CChitin {
public:
    CChitin();
    virtual ~CChitin();
    static void GetGameVersionInfo(HINSTANCE hInstance);
    void InitResources();
    BOOL InitInstance();
    void OnDisplayChange();
    void ParseCommandLine();
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static void FixReadonlyPermissions();
    static void DoFixReadonlyPermissions(CString path);
    void InitializeVariables();
    void InitVariables3D();
    BOOL Init3d();
    void Shutdown3D();
    void RegisterThread();
    void SuspendThreads();
    void AddEngine(CWarp* pNewEngine);
    int AskCloseConfirmation();
    void DestroyServices();
    CWnd* GetWnd();
    void Resume();
    void ReadIniFiles();
    CVidMode* GetCurrentVideoMode();
    void EnginesGameInit();
    void EnginesGameUninit();
    CString GetFontName();
    CString GetStartUpGameSpyLocation();
    CString GetStartUpAddress();
    CString GetStartUpSession();
    CString GetStartUpPlayer();

    // NOTE: Inlined in `CVidInf::SetClipper`.
    BOOL FullScreen() { return m_bFullscreen; }

    /* 0000 */ virtual void SynchronousUpdate();
    /* 0004 */ virtual int InitApplication(HINSTANCE hInstance, int nShowCmd);
    /* 0008 */ virtual DWORD GetIDSInvalidVideoMode();
    /* 000C */ virtual DWORD GetIDSOpenGLDll();
    /* 0010 */ virtual DWORD GetIDSExclusiveMode();
    /* 0014 */ virtual DWORD GetIDSChoosePixelFormat();
    /* 0018 */ virtual DWORD GetIDSSetPixelFormat();
    /* 001C */ virtual DWORD GetIDSSetGameResolution();
    /* 0020 */ virtual DWORD GetIDSSetGameBitDepth();
    /* 0024 */ virtual DWORD GetIDSBadDeskTopBitDepth();
    /* 0028 */ virtual DWORD GetIDSWindowsFonts();
    /* 002C */ virtual void MessageThreadMain(void* userInfo) = 0;
    /* 0030 */ virtual void RSThreadMain(void* userInfo) = 0;
    /* 0034 */ virtual void MainAIThread(void* userInfo) = 0;
    /* 0038 */ virtual void MusicThreadMain(void* userInfo) = 0;
    /* 003C */ virtual CRes* AllocResObject(int nType);
    /* 0040 */ virtual const CString& GetIconRes();
    /* 0044 */ virtual void GetScreenShotFilePrefix(CString& szGameFileName);
    /* 0048 */ virtual int TranslateType(const CString& sRes);
    /* 004C */ virtual void TranslateType(int nType, CString& sRes);
    /* 0050 */ virtual BOOL InitGraphics();
    /* 0054 */ virtual BOOL FontRectOutline();
    /* 0058 */ virtual BOOL InitializeServices(HWND hWnd);
    /* 005C */ virtual void SetProgressBar(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout);
    /* 0060 */ virtual void SetProgressBarActivateEngine(BOOL bValue);
    /* 0064 */ virtual void BroadcastMultiplayerProgressBarInfo();
    /* 0068 */ virtual void SetCDSwitchStatus(BOOLEAN a1, BOOLEAN a2, BYTE a3, const CString& a4, BOOLEAN a5, BOOLEAN a6, BOOLEAN a7);
    /* 006C */ virtual void SetCDSwitchActivateEngine(BOOL bValue);
    /* 0070 */ virtual void OnMultiplayerSessionOpen(CString& sJoinedGame, CString& sDroppedGame, CString& sLeftGame);
    /* 0074 */ virtual void OnMultiplayerSessionToClose();
    /* 0078 */ virtual void OnMultiplayerSessionClose();
    /* 007C */ virtual void OnMultiplayerPlayerJoin(PLAYER_ID playerID, const CString& sPlayerName);
    /* 0080 */ virtual void OnMultiplayerPlayerVisible(PLAYER_ID playerID);
    /* 0084 */ virtual void OnMultiplayerPlayerLeave(PLAYER_ID playerID, const CString& sPlayerName);
    /* 0088 */ virtual BOOL MessageCallback(BYTE* pData, DWORD dwSize);
    /* 0090 */ virtual void AsynchronousUpdate(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
    /* 0094 */ virtual BOOLEAN FlipFullScreenMode(BOOLEAN bSave);
    /* 00A0 */ virtual const char* GetIniFileName();
    /* 00A4 */ virtual const char* GetKeyFileName();
    /* 00A8 */ virtual const char* GetLogFileName();
    /* 00A8 */ virtual const char* GetErrFileName();
    /* 00B0 */ virtual void SaveBitsPerPixel(USHORT nBpp);
    /* 00B4 */ virtual UINT GetSavedBitsPerPixel();
    /* 00B8 */ virtual BYTE GetNumberSoundChannels();
    /* 00BC */ virtual LONG GetMovieVolume();
    /* 00C0 */ virtual void LoadOptions();
    /* 00C4 */ virtual void PreLoadFonts();
    /* 00C8 */ virtual void UnloadFonts();
    /* 00CC */ virtual void SetSoundVolumes();
    /* 0098 */ virtual void SelectEngine(CWarp* pNewEngine);
    /* 009C */ virtual void ShutDown(int nLineNumber, const char* szFileName, const char* text);
    /* 00D0 */ virtual WORD GetMultiplayerGameSpyPort();
    /* 00D4 */ virtual WORD GetMultiplayerDirectPlayPort();
    /* 00D8 */ virtual void SetRenderCount(BYTE nCount);
    /* 00DC */ virtual DWORD GetCloseConfirmationFlags();
    /* 00E0 */ virtual void GetCloseConfirmationStr(CString& sString);
    /* 00E4 */ virtual BOOLEAN OnAltEnter(BOOLEAN bSave);
    /* 00E8 */ virtual void OnAltTab(HWND hWnd, BOOL a2);
    /* 00EC */ virtual void GetGameSpyGameName(CString& sGameSpyName);
    /* 00F0 */ virtual void GetGameSpyCode(CString& sGameSpyCode);
    /* 00F4 */ virtual void GetPanicCDStrings(CString& sMediaRemoved, CString& sPlaceCD, CString& sInDrive);
    /* 00F8 */ virtual void OnMixerInitialize();
    /* 00FC */ virtual BOOL Is3DSound(int nSoundChannel);
    /* 0100 */ virtual float GetSoundReverbMix(int nSoundChannel, int nReverb);
    /* 0104 */ virtual BOOL GetEAXActive();
    /* 0108 */ virtual int GetSoundEnvironment(EAXPRESET& preset, int environment);
    /* 010C */ virtual void RedrawScreen();

    static DWORD TIMER_UPDATES_PER_SECOND;
    static const CString ICON_RES_ID;
    static CString m_sBuildNumber;
    static const CString DEFAULT_PRINTSCREEN_FILE_NAME;
    static CString m_sVersionNumber;
    static CString m_sGameName;
    static BOOL SCREEN_SAVE_ACTIVE;
    static BOOL SCREEN_SAVE_ACTIVE_LOADED;
    static BOOLEAN byte_8FB950;
    static int dword_8FB974;
    static int dword_8FB978;
    static int dword_8FB97C;

    /* 0004 */ INT m_mouseLButton;
    /* 0008 */ INT m_mouseRButton;
    /* 000C */ BOOL m_bMouseLButtonDown;
    /* 0010 */ CPoint m_mouseLDblClickPoint;
    /* 0018 */ UINT m_mouseLDblClickCount;
    /* 001C */ BOOL m_bMouseRButtonDown;
    /* 0020 */ CPoint m_mouseRDblClickPoint;
    /* 0028 */ UINT m_mouseRDblClickCount;
    /* 002C */ BOOL m_bMouseMButtonDown;
    /* 0030 */ CPoint m_mouseMDblClickPoint;
    /* 0038 */ UINT m_mouseMDblClickCount;
    /* 003C */ UINT m_mouseDblClickTime;
    /* 0040 */ CSize m_mouseDblClickSize;
    /* 0048 */ BOOL m_bEngineActive;
    /* 004C */ int field_4C;
    /* 0050 */ int field_50;
    /* 0054 */ CObList lEngines;
    /* 0070 */ int field_70;
    /* 0074 */ CWarp* m_pStartingEngine;
    /* 0078 */ CWnd cWnd; // #guess
    /* 00B4 */ HANDLE field_B4;
    /* 00B8 */ HINSTANCE m_hInstance; // #guess
    /* 00BC */ int field_BC;
    /* 00C0 */ int field_C0;
    /* 00C4 */ CRITICAL_SECTION field_C4;
    /* 00DC */ CString m_sCommandLine;
    /* 00E0 */ BOOLEAN m_bReInitializing;
    /* 00E1 */ BOOLEAN m_bFullscreen;
    /* 00E2 */ BOOLEAN m_nNextFullscreen;
    /* 00E4 */ int field_E4;
    /* 00E8 */ RECT field_E8;
    /* 00F8 */ unsigned char field_F8;
    /* 00F9 */ unsigned char field_F9;
    /* 00FA */ DWORD dwPlatformId; // #guess
    /* 00FE */ short field_FE;
    /* 0100 */ int m_nScreenWidth; // #guess
    /* 0104 */ int m_nScreenHeight; // #guess
    /* 0108 */ CPoint m_ptScreen;
    /* 0110 */ int field_110;
    /* 0114 */ BOOL m_bStartUpConnect;
    /* 0118 */ CString m_sStartUpAddress;
    /* 011C */ CString field_11C;
    /* 0120 */ CString m_sStartUpPlayer;
    /* 0124 */ int field_124;
    /* 0128 */ int field_128;
    /* 012C */ CString m_sStartUpSession;
    /* 0130 */ unsigned char field_130;
    /* 0131 */ unsigned char field_131;
    /* 0132 */ CString m_sStartUpGameSpyLocation;
    /* 0136 */ int field_136;
    /* 013A */ int field_13A;
    /* 01E3 */ int field_13E;
    /* 0142 */ int field_142;
    /* 0148 */ int m_bInMouseWheelQueue;
    // FIXME: Looks like this list stores `wParam` values of `WM_MOUSEWHEEL`
    // disguised as pointers. There are more specialized collections for such
    // case.
    /* 014C */ CPtrList m_lMouseWheel;
    /* 0168 */ int m_nWheelScrollLines; // #guess
    /* 016C */ int field_16C;
    /* 0170 */ int field_170;
    /* 0174 */ int field_174;
    /* 0178 */ BOOL m_bUseMirrorFX; // #guess
    /* 017C */ UINT m_nQueryCancelAutoPlayMsgID; // #guess
    /* 0180 */ HANDLE field_180;
    /* 0184 */ DWORD m_nTickCount;
    /* 0188 */ int m_nAIPerSec;
    /* 018C */ int m_nAIElasped;
    /* 0190 */ int m_nRenderTickCount;
    /* 0194 */ int m_nRenderPerSec;
    /* 0198 */ int m_nRenderElasped;
    /* 019C */ int field_19C;
    /* 01A0 */ int field_1A0;
    /* 01A4 */ int field_1A4;
    /* 01A8 */ CImm cImm; // #guess
    /* 02E8 */ CString m_sFontName;
    /* 02EC */ int field_2EC;
    /* 02F0 */ HMODULE m_hOpenGL;
    /* 02F4 */ int field_2F4;
    /* 02F8 */ HANDLE m_eventTimer;
    /* 02FC */ CRITICAL_SECTION field_2FC;
    /* 0314 */ CRITICAL_SECTION field_314;
    /* 032C */ CRITICAL_SECTION field_32C;
    /* 0344 */ CRITICAL_SECTION field_344;
    /* 035C */ CRITICAL_SECTION field_35C;
    /* 0374 */ BOOL m_bExitRSThread;
    /* 0378 */ HANDLE m_hRSThread;
    /* 037C */ BOOL m_bExitMessageThread;
    /* 0380 */ HANDLE m_hMessageThread;
    /* 0384 */ HANDLE m_hMainAIThread;
    /* 0388 */ BOOL m_bExitMainAIThread;
    /* 038C */ HANDLE m_hMusicThread;
    /* 0390 */ BOOL m_bExitMusicThread;
    /* 0394 */ CRITICAL_SECTION field_394;
    /* 03AC */ CRITICAL_SECTION field_3AC;
    /* 03C4 */ CWarp* pActiveEngine;
    /* 03C8 */ CSoundMixer cSoundMixer; // #guess
    /* 0542 */ CDimm cDimm; // #guess
    /* 07EA */ CVideo cVideo;
    /* 0952 */ CNetwork cNetwork;
    /* 18D4 */ CGameSpy cGameSpy; // #guess
    /* 1900 */ CUnknown1 field_1900;
    /* 1902 */ BOOL m_bPointerUpdated;
    /* 1906 */ CPoint m_ptPointer;
    /* 190E */ LONG nAUCounter;
    /* 1912 */ BOOL m_bInAsynchronousUpdate;
    /* 1916 */ CAliasList lAliases; // #guess
    /* 1932 */ int field_1932;
    /* 1936 */ BOOL m_bAIStale;
    /* 193A */ BOOL m_bDisplayStale;
    /* 193E */ BOOL m_bInSynchronousUpdate;
    /* 1942 */ int m_nKeyboardDelay; // #guess
    /* 1946 */ int m_nKeyboardSpeed; // #guess
    /* 194A */ CCriticalSection m_csPointerPosition;
    /* 196A */ CProgressBar cProgressBar;
    /* 19D6 */ DWORD m_dwThreadIds[CHITIN_MAX_THREADS]; // #guess
    /* 19FE */ HANDLE m_hThreadHandles[CHITIN_MAX_THREADS]; // #guess
    /* 1A26 */ USHORT m_nThreads;
    /* 1A28 */ short field_1A28;
    /* 1A2A */ int field_1A2A;
    /* 1A2E */ int field_1A2E;
    /* 1A32 */ int field_1A32[16];
    /* 1A72 */ DWORD field_1A72[16];
    /* 1AB2 */ DWORD field_1AB2[16];
    /* 1AF2 */ DWORD field_1AF2[16];
    /* 1B32 */ unsigned char field_1B32[64];
    /* 1C32 */ CRITICAL_SECTION field_1C32;
    /* 1C4A */ unsigned char field_1C4A;
    /* 1C4C */ int field_1C4C;
};

extern CChitin* g_pChitin;

#endif /* CCHITIN_H_ */

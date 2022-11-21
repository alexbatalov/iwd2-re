#ifndef CCHITIN_H_
#define CCHITIN_H_

#include <afxmt.h>
#include <afxwin.h>

#include "CAliasList.h"
#include "CDimm.h"
#include "CGameSpy.h"
#include "CImm.h"
#include "CNetwork.h"
#include "CProgressBar.h"
#include "CSoundMixer.h"
#include "CUnknown1.h"
#include "CVideo.h"

class CChitin {
public:
    CChitin();
    virtual ~CChitin();
    static void GetGameVersionInfo(HINSTANCE hInstance);
    int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
    static void FixReadonlyPermissions();
    static void DoFixReadonlyPermissions(CString path);
    void InitializeVariables();
    void InitVariables3D();
    void Shutdown3D();

    static UINT MAXIMUM_FRAME_RATE;
    static CString buildVersionString;
    static CString versionString;
    static CString name;
    static int dword_8FB974;
    static int dword_8FB978;
    static int dword_8FB97C;

    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0028 */ int field_28;
    /* 002C */ int field_2C;
    /* 0038 */ int field_38;
    /* 003C */ UINT m_nDoubleClickTime; // #guess
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ int field_48;
    /* 004C */ int field_4C;
    /* 0050 */ int field_50;
    /* 0054 */ CObList lEngines;
    /* 0070 */ int field_70;
    /* 0074 */ int field_74;
    /* 0078 */ CWnd cWnd; // #guess
    /* 00B4 */ HANDLE field_B4;
    /* 00BC */ int field_BC;
    /* 00C0 */ int field_C0;
    /* 00C4 */ CRITICAL_SECTION field_C4;
    /* 00DC */ CString field_DC;
    /* 00E0 */ unsigned char field_E0;
    /* 00E1 */ unsigned char field_E1;
    /* 00E2 */ unsigned char field_E2;
    /* 00E4 */ int field_E4;
    /* 00F8 */ unsigned char field_F8;
    /* 00F9 */ unsigned char field_F9;
    /* 00FA */ DWORD dwPlatformId; // #guess
    /* 00FE */ short field_FE;
    /* 0100 */ int m_nScreenWidth; // #guess
    /* 0104 */ int m_nScreenHeight; // #guess
    /* 0108 */ int field_108;
    /* 010C */ int field_10C;
    /* 0110 */ int field_110;
    /* 0114 */ int field_114;
    /* 0118 */ CString field_118;
    /* 011C */ CString field_11C;
    /* 0120 */ CString field_120;
    /* 0124 */ int field_124;
    /* 0128 */ int field_128;
    /* 012C */ CString field_12C;
    /* 0130 */ unsigned char field_130;
    /* 0131 */ unsigned char field_131;
    /* 0132 */ CString field_132;
    /* 0136 */ int field_136;
    /* 013A */ int field_13A;
    /* 01E3 */ int field_13E;
    /* 0142 */ int field_142;
    /* 0148 */ int field_148;
    /* 014C */ CPtrList field_14C;
    /* 0168 */ int m_nWheelScrollLines; // #guess
    /* 016C */ int field_16C;
    /* 0170 */ int field_170;
    /* 0174 */ int field_174;
    /* 0180 */ int field_180;
    /* 0184 */ int field_184;
    /* 0188 */ int field_188;
    /* 018C */ int field_18C;
    /* 0190 */ int field_190;
    /* 0194 */ int field_194;
    /* 0198 */ int field_198;
    /* 019C */ int field_19C;
    /* 01A0 */ int field_1A0;
    /* 01A4 */ int field_1A4;
    /* 01A8 */ CImm cImm; // #guess
    /* 02E8 */ CString field_2E8;
    /* 02EC */ int field_2EC;
    /* 028F */ HANDLE m_eventTimer;
    /* 02FC */ CRITICAL_SECTION field_2FC;
    /* 0314 */ CRITICAL_SECTION field_314;
    /* 032C */ CRITICAL_SECTION field_32C;
    /* 0344 */ CRITICAL_SECTION field_344;
    /* 035C */ CRITICAL_SECTION field_35C;
    /* 0374 */ int field_374;
    /* 0378 */ int field_378;
    /* 037C */ int field_37C;
    /* 0388 */ int field_388;
    /* 038C */ int field_38C;
    /* 0390 */ int field_390;
    /* 0394 */ CRITICAL_SECTION field_394;
    /* 03AC */ CRITICAL_SECTION field_3AC;
    /* 03C4 */ int field_3C4;
    /* 03C8 */ CSoundMixer cSoundMixer; // #guess
    /* 0542 */ CDimm cDimm; // #guess
    /* 07EA */ CVideo cVideo;
    /* 0952 */ CNetwork cNetwork;
    /* 18D4 */ CGameSpy cGameSpy; // #guess
    /* 1900 */ CUnknown1 field_1900;
    /* 1902 */ int field_1902;
    /* 1906 */ int field_1906;
    /* 190A */ int field_190A;
    /* 190E */ int field_190E;
    /* 1912 */ int field_1912;
    /* 1916 */ CAliasList lAliases; // #guess
    /* 1932 */ int field_1932;
    /* 1936 */ int field_1936;
    /* 193A */ int field_193A;
    /* 193E */ int field_193E;
    /* 1942 */ int m_nKeyboardDelay; // #guess
    /* 1946 */ int m_nKeyboardSpeed; // #guess
    /* 194A */ CCriticalSection field_194A;
    /* 196A */ CProgressBar cProgressBar;
    /* 19D6 */ DWORD m_dwThreadIds[10]; // #guess
    /* 19FE */ HANDLE m_hThreadHandles[10]; // #guess
    /* 1A26 */ USHORT m_nThreads;
    /* 1A28 */ short field_1A28;
    /* 1A2A */ int field_1A2A;
    /* 1A2E */ int field_1A2E;
    /* 1A32 */ int field_1A32[16];
    /* 1A72 */ unsigned char field_1A72[64];
    /* 1AB2 */ unsigned char field_1AB2[64];
    /* 1AF2 */ unsigned char field_1AF2[64];
    /* 1B32 */ unsigned char field_1B32[64];
    /* 1C32 */ CRITICAL_SECTION field_1C32;
    /* 1C4A */ unsigned char field_1C4A;
    /* 1C4C */ int field_1C4C;
};

#endif /* CCHITIN_H_ */

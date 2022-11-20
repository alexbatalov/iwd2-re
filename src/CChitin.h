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

    static CString buildVersionString;
    static CString versionString;
    static CString name;
    static int dword_8FB974;
    static int dword_8FB978;
    static int dword_8FB97C;

    /* 0054 */ CObList lEngines;
    /* 0078 */ CWnd cWnd; // #guess
    /* 00B4 */ HANDLE field_B4;
    /* 00C4 */ CRITICAL_SECTION field_C4;
    /* 00DC */ CString field_DC;
    /* 00FA */ DWORD dwPlatformId; // #guess
    /* 00FE */ short field_FE;
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
    /* 014C */ CPtrList field_14C;
    /* 0180 */ int field_180;
    /* 0184 */ int field_184;
    /* 0188 */ int field_188;
    /* 018C */ int field_18C;
    /* 0190 */ int field_190;
    /* 0194 */ int field_194;
    /* 0198 */ int field_198;
    /* 019C */ int field_19C;
    /* 01A8 */ CImm cImm; // #guess
    /* 02E8 */ CString field_2E8;
    /* 02EC */ int field_2EC;
    /* 028F */ HANDLE m_eventTimer;
    /* 02FC */ CRITICAL_SECTION field_2FC;
    /* 0314 */ CRITICAL_SECTION field_314;
    /* 032C */ CRITICAL_SECTION field_32C;
    /* 0344 */ CRITICAL_SECTION field_344;
    /* 035C */ CRITICAL_SECTION field_35C;
    /* 0394 */ CRITICAL_SECTION field_394;
    /* 03AC */ CRITICAL_SECTION field_3AC;
    /* 03C8 */ CSoundMixer cSoundMixer; // #guess
    /* 0542 */ CDimm cDimm; // #guess
    /* 07EA */ CVideo cVideo;
    /* 0952 */ CNetwork cNetwork;
    /* 18D4 */ CGameSpy cGameSpy; // #guess
    /* 1900 */ CUnknown1 field_1900;
    /* 1916 */ CAliasList lAliases; // #guess
    /* 1932 */ int field_1932;
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

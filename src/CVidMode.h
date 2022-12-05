#ifndef CVIDMODE_H_
#define CVIDMODE_H_

#include "mfc.h"

#include <ddraw.h>

class CVidMode {
public:
    struct Entry {
        unsigned char dummy[1];
    };

    static BYTE NUM_FADE_FRAMES;
    static BOOL bInitialized;

    BOOL CheckResults(HRESULT hr);
    BOOL LockSurface(UINT nIndex, LPDDSURFACEDESC pSurfaceDesc, const CRect& rect);
    BOOL UnLockSurface(UINT nIndex, LPVOID lpSurfaceData);
    static void SetWindowedMode(HWND hWnd);

    CVidMode();
    /* 005C */ virtual BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen) = 0;
    /* 0068 */ virtual BOOL CreateSurface(IDirectDrawSurface** lplpDirectDrawSurface, const CSize& cSize);
    /* 006C */ virtual BOOL DeactivateVideoMode(int a2) = 0;
    /* 0070 */ virtual void DestroySurface(IDirectDrawSurface** lplpDirectDrawSurface);
    /* 0074 */ virtual void DestroySurfaces();
    /* 0080 */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color);
    /* 00E8 */ virtual void LoadFogOWarSurfaces(const CString& a2);
    /* 0100 */ virtual void RestoreSurfaces();
    /* 011C */ virtual ~CVidMode();

    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ CCriticalSection field_28;
    /* 0048 */ BOOLEAN m_bFadeTo;
    /* 0049 */ BYTE m_nFade;
    /* 004A */ CCriticalSection field_4A;
    /* 006A */ CTypedPtrList<CPtrList, Entry*> field_6A;
    /* 0086 */ int field_86;
    /* 008A */ int field_8A;
    /* 008E */ unsigned char field_8E;
    /* 008F */ unsigned char field_8F;
    /* 0090 */ DWORD nTickCount;
    /* 0094 */ int field_94;
    /* 0098 */ int field_98;
    /* 009C */ UINT m_nSurfaces;
    /* 00A0 */ IDirectDrawSurface** m_pSurfaces;
    /* 00A4 */ COLORREF rgbGlobalTint;
    /* 00A8 */ BYTE m_nBrightnessCorrection;
    /* 00A9 */ BYTE m_nGammaCorrection;
    /* 00C2 */ int field_C2;
    /* 00C6 */ int field_C6;
    /* 00CA */ int field_CA;
    /* 00D2 */ short field_D2;
    /* 00D4 */ int field_D4;
    /* 00D8 */ int field_D8;
    /* 00DC */ int field_DC;
    /* 00E0 */ int field_E0;
    /* 00E4 */ int field_E4;
    /* 00E8 */ int field_E8;
    /* 00EC */ int field_EC;
    /* 00F0 */ int field_F0;
};

#endif /* CVIDMODE_H_ */

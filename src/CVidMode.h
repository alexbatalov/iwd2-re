#ifndef CVIDMODE_H_
#define CVIDMODE_H_

#include "mfc.h"

#include <ddraw.h>

#include "CResRef.h"

class CVidCell;

typedef struct {
    CPoint ptCenter;
    SHORT xAxis;
    SHORT yAxis;
    SHORT piePiecePtXOffset;
    SHORT piePiecePtYOffset;
    SHORT piePieceXOffset;
    SHORT piePieceYOffset;
    SHORT xGap;
    SHORT yGap;
} CVIDMODE_RECTICLE_DESCRIPTION;

class CVidMode {
public:
    struct Entry {
        unsigned char dummy[1];
    };

    static BYTE NUM_FADE_FRAMES;
    static BOOL bInitialized;

    static BOOL ClipLine(INT& nXFrom, INT& nYFrom, INT& nXTo, INT& nYTo, const CRect& rClip);
    COLORREF GetGlobalTintColor();
    BOOL CheckResults(HRESULT hr);
    BOOL LockSurface(UINT nIndex, LPDDSURFACEDESC pSurfaceDesc, const CRect& rect);
    BOOL UnLockSurface(UINT nIndex, LPVOID lpSurfaceData);
    static void SetWindowedMode(HWND hWnd);
    BOOL DrawLine3d(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const CRect& rSurface, COLORREF rgbColor);
    BOOL DrawEllipse3d(const CPoint& ptCenter, const CSize& axis, const CRect& rClip, COLORREF rgbColor);
    BOOL DrawRecticle3d(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const CRect& rClip, COLORREF rgbColor);

    CVidMode();
    /* 0000 */ virtual BOOLEAN SaveScreen();
    /* 0004 */ virtual void DrawEllipse16(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0008 */ virtual LONG DrawEllipseHOctant16(LONG x, LONG y, INT nArcLength, WORD* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, WORD color);
    /* 000C */ virtual LONG DrawEllipseVOctant16(LONG x, LONG y, INT nArcLength, WORD* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, WORD color);
    /* 0010 */ virtual LONG DrawEllipse24(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0014 */ virtual LONG DrawEllipseHOctant24(LONG x, LONG y, INT nArcLength, BYTE* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color);
    /* 0018 */ virtual LONG DrawEllipseVOctant24(LONG x, LONG y, INT nArcLength, BYTE* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color);
    /* 001C */ virtual LONG DrawEllipse32(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0020 */ virtual LONG DrawEllipseHOctant32(LONG x, LONG y, INT nArcLength, DWORD* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color);
    /* 0024 */ virtual LONG DrawEllipseVOctant32(LONG x, LONG y, INT nArcLength, DWORD* pSurface, LONG lpitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color);
    /* 0028 */ virtual void DrawLightingEffect16(WORD* pSurface, LONG lpitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7);
    /* 002C */ virtual void DrawLightingEffect24(BYTE* pSurface, LONG lpitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7);
    /* 0030 */ virtual void DrawLightingEffect32(DWORD* pSurface, LONG lpitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7);
    /* 0034 */ virtual BOOL DrawRecticle(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const CRect& rClip, COLORREF rgbColor);
    /* 0038 */ virtual void DrawRecticle(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 003C */ virtual void DrawRecticle16(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0040 */ virtual void DrawRecticle24(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0044 */ virtual void DrawRecticle32(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0048 */ virtual BOOL DrawThickLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, UINT nSurface, CRect& rSurface, int a8, COLORREF rgbColor);
    /* 004C */ virtual BOOL DrawThickLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const DDSURFACEDESC& ddsd, CRect& rSurface, int a8, COLORREF rgbColor, BOOLEAN bClipped);
    /* 0050 */ virtual BOOL DrawThickLine16(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, WORD* pSurface, LONG lpitch, CRect& rSurface, int a8, unsigned short color, BOOLEAN bClipped);
    /* 0054 */ virtual BOOL DrawThickLine24(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, BYTE* pSurface, LONG lpitch, CRect& rSurface, int a8, unsigned long color, BOOLEAN bClipped);
    /* 0058 */ virtual BOOL DrawThickLine32(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, DWORD* pSurface, LONG lpitch, CRect& rSurface, int a8, unsigned long color, BOOLEAN bClipped);
    /* 005C */ virtual BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen);
    /* 0060 */ virtual BOOLEAN SetClipper(IDirectDrawClipper* lpDirectDrawClipper);
    /* 0064 */ virtual BOOL CreateSurfaces(BOOLEAN a2);
    /* 0068 */ virtual BOOL CreateSurface(IDirectDrawSurface** lplpDirectDrawSurface, const CSize& cSize);
    /* 006C */ virtual BOOL DeactivateVideoMode(int a2);
    /* 0070 */ virtual void DestroySurface(IDirectDrawSurface** lplpDirectDrawSurface);
    /* 0074 */ virtual void DestroySurfaces();
    /* 0078 */ virtual void DisplayFrameRate(UINT nSurface);
    /* 007C */ virtual void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height);
    /* 0080 */ virtual void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color);
    /* 0084 */ virtual void DrawEllipse(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor);
    /* 0088 */ virtual BOOL DrawEllipse(const CPoint& ptCenter, const CSize& axis, const CRect& rClip, COLORREF rgbColor);
    /* 008C */ virtual void DrawLightingEffect(const DDSURFACEDESC& ddsd, const CPoint& a3, const CSize& a4, unsigned long a5, unsigned long a6);
    /* 0090 */ virtual BOOL DrawPoints(CPoint* pPoints, INT nPoints, WORD* pSurface, LONG lPitch, const CRect& rSurface, COLORREF rgbColor, BOOL bClipped);
    /* 0094 */ virtual BOOL DrawLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, UINT nSurface, const CRect& rSurface, COLORREF rgbColor);
    /* 0098 */ virtual BOOL DrawLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const DDSURFACEDESC& ddsd, const CRect& rSurface, unsigned long, BOOLEAN bClipped);
    /* 009C */ virtual BOOL DrawLine16(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, WORD* pSurface, LONG lpitch, const CRect& rSurface, unsigned short color, BOOLEAN bClipped);
    /* 00A0 */ virtual BOOL DrawLine24(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, BYTE* pSurface, LONG lpitch, const CRect& rSurface, unsigned long color, BOOLEAN bClipped);
    /* 00A4 */ virtual BOOL DrawLine32(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, DWORD* pSurface, LONG lpitch, const CRect& rSurface, unsigned long color, BOOLEAN bClipped);
    /* 00A8 */ virtual BOOL DrawRect(const CRect& r, UINT nSurface, const CRect& rClip, COLORREF rgbColor);
    /* 00B0 */ virtual BOOL OutlinePoly(const CPoint* pPoly, SHORT nVertices, const CRect& rSurface, COLORREF rgbColor, const CPoint& ptOffset);
    /* 00B4 */ virtual BOOL EraseScreen(UINT nSurface, COLORREF rgbColor);
    /* 00B8 */ virtual BOOL Flip(int a2);
    /* 00BC */ virtual int GetColorDepth();
    /* 00C0 */ virtual int GetEllipseArcPixelList(LONG a2, LONG a3, BYTE* a4);
    /* 00C4 */ virtual BOOL GetFXSurface(INT& nSurface, DWORD dwFlags);
    /* 00C8 */ virtual IDirectDrawSurface* GetFXSurfacePtr(DWORD dwFlags);
    /* 00CC */ virtual BOOL GetCursorSurfaceSize(CSize& size);
    /* 00D0 */ virtual BOOL GetFXSize(CSize& size);
    /* 00D4 */ virtual RGBQUAD* GetPalette();
    /* 00D8 */ virtual CVidCell* GetPointer();
    /* 00DC */ virtual COLORREF GetTransparentColor();
    /* 00E0 */ virtual int GetType();
    /* 00E4 */ virtual int GetNumVRamSurfaces();
    /* 00E8 */ virtual void LoadFogOWarSurfaces(const CString& a2);
    /* 00EC */ virtual void PrintScreen();
    /* 00F0 */ virtual void RenderFlash(UINT nSurface, COLORREF rgbColor, unsigned char a4, const CRect& a5);
    /* 00F4 */ virtual BOOL RenderPoly(UINT nSurface, CRect& a3, POINT* apt, int cpt, COLORREF rgbColor);
    /* 00F8 */ virtual BOOL RenderPointer(unsigned int);
    /* 00FC */ virtual BOOL RenderPointer();
    /* 0100 */ virtual void RestoreSurfaces();
    /* 0104 */ virtual BOOL SetPointer(CVidCell* pVidCell, CResRef cResRef, BOOLEAN bAnimating, INT nPointerNumber);
    /* 0108 */ virtual BOOL SetPointer(CVidCell* pVidCell, BOOLEAN bAnimating, INT nPointerNumber);
    /* 010C */ virtual void ParsePixelFormat(const DDPIXELFORMAT& ddpf);
    /* 0110 */ virtual BOOLEAN PrintSurfaceToBmp(LPBYTE& data, int a3, const CRect& r, LONG& size, short a6);
    /* 0114 */ virtual int GetPointerNumber();
    /* 0118 */ virtual DWORD ReduceColor(COLORREF rgbColor);
    /* 011C */ virtual ~CVidMode();
    /* 0120 */ virtual BOOL CreateSurfaces3d();
    /* 0124 */ virtual BOOL DestroySurfaces3d();
    /* 0128 */ virtual int GetTextureId();
    /* 012C */ virtual BOOL ActivateVideoMode3d(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen);

    /* 0004 */ int field_4;
    /* 0008 */ int m_nPointerNumber; // #guess
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ DWORD m_dwRBitMask; // #guess
    /* 001C */ DWORD m_dwGBitMask; // #guess
    /* 0020 */ DWORD m_dwBBitMask; // #guess
    /* 0024 */ int field_24;
    /* 0028 */ CCriticalSection field_28;
    /* 0048 */ BOOLEAN m_bFadeTo;
    /* 0049 */ BYTE m_nFade;
    /* 004A */ CCriticalSection field_4A;
    /* 006A */ CTypedPtrList<CPtrList, Entry*> field_6A;
    /* 0086 */ int m_nColorDepth; // #guess
    /* 008A */ CVidCell* m_pPointerVidCell; // #guess
    /* 008E */ BOOLEAN m_bPointerAnimating; // #guess
    /* 008F */ BOOLEAN m_bPrintScreen; // #guess
    /* 0090 */ DWORD nTickCount;
    /* 0094 */ int field_94;
    /* 0098 */ int field_98;
    /* 009C */ UINT m_nSurfaces;
    /* 00A0 */ IDirectDrawSurface** m_pSurfaces;
    /* 00A4 */ COLORREF rgbGlobalTint;
    /* 00A8 */ BYTE m_nBrightnessCorrection;
    /* 00A9 */ BYTE m_nGammaCorrection;
    /* 00AA */ DWORD m_dwRBitShift; // #guess
    /* 00AE */ DWORD m_dwGBitShift; // #guess
    /* 00B2 */ DWORD m_dwBBitShift; // #guess
    /* 00B6 */ DWORD m_dwRBitCount; // #guess
    /* 00BA */ DWORD m_dwGBitCount; // #guess
    /* 00BE */ DWORD m_dwBBitCount; // #guess
    /* 00C2 */ DWORD field_C2;
    /* 00C6 */ DWORD field_C6;
    /* 00CA */ DWORD field_CA;
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

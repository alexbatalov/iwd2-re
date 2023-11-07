#ifndef CVIDINF_H_
#define CVIDINF_H_

#include "CVidBitmap.h"
#include "CVidFont.h"
#include "CVidMode.h"

#define CVIDINF_SURFACE_BACK 0
#define CVIDINF_SURFACE_FRONT 1
#define CVIDINF_SURFACE_2 2
#define CVIDINF_SURFACE_3 3
#define CVIDINF_SURFACE_4 4
#define CVIDINF_SURFACE_5 5
#define CVIDINF_SURFACE_6 6
#define CVIDINF_SURFACE_7 7
#define CVIDINF_SURFACE_8 8

#define CVIDCELL_FXPREP_COPYFROMBACK 0x80
#define CVIDCELL_FXPREP_CLEARFILL 0x100

class CParticle;

class CVidInf : public CVidMode {
public:
    CVidInf();
    /* 0000 */ BOOLEAN SaveScreen() override;
    /* 005C */ BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen) override;
    /* 0060 */ BOOLEAN SetClipper(IDirectDrawClipper* lpDirectDrawClipper) override;
    /* 0064 */ BOOL CreateSurfaces(BOOLEAN bFullscreen) override;
    /* 006C */ BOOL DeactivateVideoMode(CVidMode* pNextVidMode) override;
    /* 0074 */ void DestroySurfaces() override;
    /* 007C */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height) override;
    /* 0080 */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color) override;
    /* 00B8 */ BOOL Flip(BOOL bRenderCursor) override;
    /* 00C4 */ BOOL GetFXSurface(INT& nSurface, DWORD dwFlags) override;
    /* 00C8 */ IDirectDrawSurface* GetFXSurfacePtr(DWORD dwFlags) override;
    /* 00CC */ BOOL GetCursorSurfaceSize(CSize& size) override;
    /* 00D0 */ BOOL GetFXSize(CSize& size) override;
    /* 00E0 */ int GetType() override;
    /* 00E4 */ int GetNumVRamSurfaces() override;
    /* 00E8 */ void LoadFogOWarSurfaces(const CString& a2) override;
    /* 00F8 */ BOOL RenderPointer(UINT nSurface) override;
    /* 00FC */ BOOL RenderPointer() override;
    /* 0100 */ void RestoreSurfaces() override;
    /* 010C */ void ParsePixelFormat(const DDPIXELFORMAT& ddpf) override;
    /* 011C */ ~CVidInf() override;
    /* 0124 */ BOOL DestroySurfaces3d(CVidMode* pNextVidMode) override;

    BOOL FullScreenFlip(BOOL bRenderCursor);
    BOOL WindowedFlip(BOOL bRenderCursor);
    LPVOID GetLockedSurface();
    LONG GetSurfacePitch();
    BOOL FXPrep(CRect& rFXRect, DWORD dwFlags, const CPoint& ptPos, const CPoint& ptReference, const CRect& rClip);
    void FXBltBackTo(const CPoint& ptTopLeft, const CRect& rFXRect, const CRect& rClip, DWORD dwFlags);
    BOOL FXBltToBack(CRect& rFXRect, INT x, INT y, INT nRefPointX, INT nRefPointY, const CRect& rClip, DWORD dwFlags);
    void FXClear(LPVOID pSurface, INT nSize);
    BOOL FXLock(CRect& rFXRect, DWORD dwFlags);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPtX, INT nRefPtY, const CRect& rClip, BOOLEAN a5, DWORD dwFlags);
    BOOL FXRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize);
    BOOL FXRender(CPoint* pPoints, INT nPoints, const CRect& rSurface, COLORREF rgbColor, BOOL bClipped);
    BOOL FXTextOut(CVidFont* pFont, const CString& sString, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef);
    BOOL BKLock(CRect& rBack);
    BOOL BKUnlock();
    BOOL BKRender(CVidCell* pVidCell, INT x, INT y, const CRect& rClip, BOOLEAN bDemanded, DWORD dwFlags);
    BOOL BKRender(CVidCell* pVidCell, INT x, INT y, DWORD dwFlags, INT nTransVal);
    BOOL BKRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize);
    BOOL BKRenderEllipse(const CPoint& ptCenter, const CSize& axes, const CRect& rClip, COLORREF rgbColor);
    BOOL BKRenderLine(int nXFrom, int nYFrom, int nXTo, int nYTo, const CRect& rSurface, COLORREF rgbColor);
    BOOL BKRenderConvexPoly(CVidPoly* pPoly, const CRect& rClipRect, DWORD dwColor, DWORD dwFlags, const CPoint& ptRef);
    BOOL BKTextOut(CVidFont* pFont, const CString& sString, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    void GetFogOWarTileRect(unsigned char a2, CRect& rTileRect);
    void RenderPointerImage(CVidCell* pPointerVidCell, INT nSurface, INT nPointerNumber, INT x, INT y, CRect rClip);
    BOOL WindowedFlip3d(BOOL bRenderCursor);
    BOOL RenderPointer3d(UINT nSurface);
    void DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color);

    /* 00F4 */ DDSURFACEDESC m_SurfaceDesc;
    /* 0160 */ CRect m_rLockedRect;
    /* 0170 */ int field_170;
    /* 0174 */ int field_174;
    /* 0178 */ CVidFont field_178;
    /* 0678 */ IDirectDrawSurface** m_pVRamSurfaces;
    /* 067C */ int m_nVRamSurfaces;
    /* 0680 */ CVidBitmap field_680;
    /* 073A */ CString field_73A;
};

#endif /* CVIDINF_H_ */

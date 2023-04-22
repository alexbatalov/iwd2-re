#ifndef CVIDINF_H_
#define CVIDINF_H_

#include "CVidBitmap.h"
#include "CVidFont.h"
#include "CVidMode.h"

#define CVIDINF_SURFACE_FRONT 1

class CParticle;

class CVidInf : public CVidMode {
public:
    CVidInf();
    /* 005C */ BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen) override;
    /* 0060 */ BOOLEAN SetClipper(IDirectDrawClipper* lpDirectDrawClipper) override;
    /* 006C */ BOOL DeactivateVideoMode(int a2) override;
    /* 0074 */ void DestroySurfaces() override;
    /* 007C */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height) override;
    /* 0080 */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color) override;
    /* 00B8 */ BOOL Flip(BOOL bRenderCursor) override;
    /* 00C4 */ BOOL GetFXSurface(INT& nSurface, DWORD dwFlags) override;
    /* 00C8 */ IDirectDrawSurface* GetFXSurfacePtr(DWORD dwFlags) override;
    /* 00CC */ BOOL GetCursorSurfaceSize(CSize& size) override;
    /* 00D0 */ BOOL GetFXSize(CSize& size) override;
    /* 00E4 */ int GetNumVRamSurfaces() override;
    /* 00E8 */ void LoadFogOWarSurfaces(const CString& a2) override;
    /* 0100 */ void RestoreSurfaces() override;
    /* 010C */ void ParsePixelFormat(const DDPIXELFORMAT& ddpf) override;
    /* 011C */ ~CVidInf() override;

    BOOL FullScreenFlip(BOOL bRenderCursor);
    BOOL WindowedFlip(BOOL bRenderCursor);
    LPVOID GetLockedSurface();
    LONG GetSurfacePitch();
    void FXClear(LPVOID pSurface, INT nSize);
    BOOL FXLock(CRect& rFXRect, DWORD dwFlags);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue);
    BOOL FXRender(CVidCell* pVidCell, INT nRefPtX, INT nRefPtY, const CRect& rClip, BOOLEAN a5, DWORD dwFlags);
    BOOL FXRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize);
    BOOL FXRender(CPoint* pPoints, INT nPoints, const CRect& rSurface, COLORREF rgbColor, BOOL bClipped);
    BOOL BKLock(CRect& rBack);
    BOOL BKUnlock();
    BOOL BKRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize);
    BOOL BKRenderEllipse(const CPoint& ptCenter, const CSize& axes, const CRect& rClip, COLORREF rgbColor);
    BOOL BKRenderLine(int nXFrom, int nYFrom, int nXTo, int nYTo, const CRect& rSurface, COLORREF rgbColor);
    void GetFogOWarTileRect(unsigned char a2, CRect& rTileRect);
    void DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color);

    static unsigned char dword_907B20[512 * 512 * 4];

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

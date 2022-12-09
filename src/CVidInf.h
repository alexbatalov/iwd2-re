#ifndef CVIDINF_H_
#define CVIDINF_H_

#include "CVidBitmap.h"
#include "CVidFont.h"
#include "CVidMode.h"

class CVidInf : public CVidMode {
public:
    CVidInf();
    /* 005C */ BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen) override;
    /* 006C */ BOOL DeactivateVideoMode(int a2) override;
    /* 0074 */ void DestroySurfaces() override;
    /* 007C */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height) override;
    /* 0080 */ void DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color) override;
    /* 00E8 */ void LoadFogOWarSurfaces(const CString& a2) override;
    /* 0100 */ void RestoreSurfaces() override;
    /* 011C */ ~CVidInf() override;

    void DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color);

    /* 00F4 */ DDSURFACEDESC m_SurfaceDesc;
    /* 0160 */ RECT field_160;
    /* 0170 */ int field_170;
    /* 0174 */ int field_174;
    /* 0178 */ CVidFont field_178;
    /* 0678 */ IDirectDrawSurface** field_678;
    /* 067C */ int field_67C;
    /* 0680 */ CVidBitmap field_680;
    /* 073A */ CString field_73A;
};

#endif /* CVIDINF_H_ */

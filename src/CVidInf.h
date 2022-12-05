#ifndef CVIDINF_H_
#define CVIDINF_H_

#include "CVidBitmap.h"
#include "CVidFont.h"
#include "CVidMode.h"

class CVidInf : public CVidMode {
public:
    CVidInf();
    /* 005C */ BOOL ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen);
    /* 006C */ BOOL DeactivateVideoMode(int a2);
    /* 0074 */ void DestroySurfaces();
    /* 00E8 */ void LoadFogOWarSurfaces(const CString& a2);
    /* 0100 */ void RestoreSurfaces();
    /* 011C */ ~CVidInf();

    /* 00F4 */ unsigned char field_F4[108];
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

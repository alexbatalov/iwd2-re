#ifndef CVIDEO_H_
#define CVIDEO_H_

#include "mfc.h"

#include <ddraw.h>

#include "CResRef.h"
#include "CVidBlitter.h"

class CVidMode;

class CVideo {
public:
    static const USHORT word_85DE2C;
    static const USHORT word_85DE2E;
    static DWORD FPS;
    static USHORT SCREENWIDTH;
    static USHORT SCREENHEIGHT;

    CVideo();
    ~CVideo();

    void SetDoubleSizeData(size_t size);
    void ResetDoubleSizeData();
    void CleanUp();
    CVidMode* GetVidMode(int a1);
    BOOL Initialize(HWND hWnd, BOOLEAN bFullscreen);
    void SetExclusiveMode(BOOLEAN bExclusiveMode);
    void ChangeBppValue();
    BOOL SetNextBpp(USHORT nNewBpp);
    void SetBitsPerPixels(USHORT nNewBpp, BOOLEAN a3);
    void CleanUp3d();
    BOOL Initialize3d(HWND hWnd, BOOLEAN bFullscreen, int a4);
    void InitializeRenderEnv();
    BOOL SetPixelFormat(HDC hDC);

    // NOTE: Can be seen via assertion in `CVidMode::LockSurface`.
    USHORT GetBitsPerPixels() { return m_nBpp; }

    // NOTE: Can be seen via assertion in `CVidFont::SetTextFontEx`.
    BOOL Is3dAccelerated() { return m_bIs3dAccelerated; }

    /* 0000 */ USHORT m_nBpp; // #guess
    /* 0002 */ USHORT m_nNextBpp; // #guess
    /* 0004 */ BOOLEAN m_bSupports16bpp; // #guess
    /* 0005 */ BOOLEAN m_bSupports24bpp; // #guess
    /* 0006 */ BOOLEAN m_bSupports32bpp; // #guess
    /* 0008 */ CVidBlitter cVidBlitter; // #guess
    /* 0108 */ DWORD m_dwMipMapCount16; // #guess
    /* 010C */ DWORD m_dwMipMapCount24; // #guess
    /* 0110 */ DWORD m_dwMipMapCount32; // #guess
    /* 0114 */ CResRef field_114;
    /* 011C */ short field_11C;
    /* 011E */ int field_11E;
    /* 0122 */ void* m_doubleSizeData;
    /* 0126 */ size_t m_doubleSizeDataSize; // #guess
    /* 012A */ HDC m_hDC;
    /* 012E */ HGLRC m_hGLRC;
    /* 0132 */ BOOL m_bIs3dAccelerated;
    /* 0136 */ int field_136;
    /* 013A */ int field_13A;
    /* 013E */ int field_13E;
    /* 0142 */ IDirectDraw* m_pDirectDraw; // #guess
    /* 0146 */ IDirectDraw2* m_pDirectDraw2; // #guess
    /* 014A */ IDirectDrawClipper* m_pDirectDrawClipper; // #guess
    /* 014E */ CVidMode* m_pVidModes[4];
    /* 015E */ CVidMode* m_pCurrentVidMode;
    /* 0162 */ BOOLEAN m_bExclusiveMode;
    /* 0162 */ BOOLEAN m_bFullscreen;
    /* 0164 */ HWND m_hWnd; // #guess
};

#endif /* CVIDEO_H_ */

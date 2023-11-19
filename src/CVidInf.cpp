#include "CVidInf.h"

#include "CChitin.h"
#include "CParticle.h"
#include "CUtil.h"
#include "CVidImage.h"
#include "CVidPoly.h"
#include "CVideo3d.h"

#define SEVEN_EIGHT_ZERO 780

// 0x85DE50
const INT CVidInf::FX_HEIGHT = CVIDINF_FX_HEIGHT;

// 0x85DE54
const INT CVidInf::FX_WIDTH = CVIDINF_FX_WIDTH;

// #binary-identical
// 0x79AF00
CVidInf::CVidInf()
{
    m_nSurfaces = 0;
    pSurfaces = NULL;
    m_pVRamSurfaces = NULL;
    field_E0 = 4;
    m_nVRamSurfaces = 0;
    field_98 = 0;
    field_94 = 0;
    field_73A = "";
    memset(&m_SurfaceDesc, 0, sizeof(m_SurfaceDesc));
    SetRect(&m_rLockedRect, 0, 0, 0, 0);
    field_170 = 0;
    field_174 = 1;
}

// 0x7ABB90
int CVidInf::GetType()
{
    return 0;
}

// 0x79AFE0
int CVidInf::GetNumVRamSurfaces()
{
    return m_nVRamSurfaces;
}

// NOTE: Parent destructor is not inlined. Even when it's inlined there is some
// difference in unwind stack, not sure how to replicate it one-to-one.
//
// 0x79B010
CVidInf::~CVidInf()
{
    if (pSurfaces != NULL) {
        free(pSurfaces);
        pSurfaces = NULL;
    }

    m_nSurfaces = 0;
}

// 0x79B100
BOOL CVidInf::ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return ActivateVideoMode3d(pPrevVidMode, hWnd, bFullscreen);
    }

    if (pPrevVidMode != NULL && pPrevVidMode->GetType() == 0) {
        return TRUE;
    }

    m_nSurfaces = 9;
    if (pSurfaces != NULL) {
        free(pSurfaces);
    }

    pSurfaces = reinterpret_cast<IDirectDrawSurface**>(malloc(sizeof(IDirectDrawSurface*) * m_nSurfaces));
    memset(pSurfaces, 0, sizeof(IDirectDrawSurface*) * m_nSurfaces);

    if (m_pVRamSurfaces != NULL) {
        free(m_pVRamSurfaces);
    }

    m_pVRamSurfaces = reinterpret_cast<IDirectDrawSurface**>(malloc(sizeof(IDirectDrawSurface*) * SEVEN_EIGHT_ZERO));
    memset(m_pVRamSurfaces, 0, sizeof(IDirectDrawSurface*) * SEVEN_EIGHT_ZERO);

    if (!bFullscreen) {
        int nBpp = CUtil::GetCurrentBitsPerPixels();
        switch (nBpp) {
        case 16:
        case 24:
        case 32:
            g_pChitin->cVideo.m_nBpp = nBpp;
            g_pChitin->cVideo.m_nNextBpp = nBpp;
            break;
        default:
            g_pChitin->cVideo.m_nBpp = 16;
            g_pChitin->cVideo.m_nNextBpp = 16;
            break;
        }

        for (int index = 0; index < 256; index++) {
            CVidImage::rgbTempPal[index] = -1;
        }

        SetWindowedMode(hWnd);
    } else {
        int nBpp = CUtil::GetCurrentBitsPerPixels();
        switch (nBpp) {
        case 16:
        case 24:
        case 32:
            g_pChitin->cVideo.m_nBpp = nBpp;
            g_pChitin->cVideo.m_nNextBpp = nBpp;
            break;
        default:
            g_pChitin->cVideo.m_nBpp = 16;
            g_pChitin->cVideo.m_nNextBpp = 16;
            break;
        }

        if ((g_pChitin->cVideo.m_nBpp == 16 && !g_pChitin->cVideo.m_bSupports16bpp)
            || (g_pChitin->cVideo.m_nBpp == 24 && !g_pChitin->cVideo.m_bSupports24bpp)
            || (g_pChitin->cVideo.m_nBpp == 32 && !g_pChitin->cVideo.m_bSupports32bpp)) {
            g_pChitin->cVideo.m_nBpp = 16;
            g_pChitin->cVideo.m_nNextBpp = 16;

            if (g_pChitin != NULL) {
                g_pChitin->SaveBitsPerPixel(16);
            }
        }

        if ((g_pChitin->cVideo.m_nBpp == 16 && !g_pChitin->cVideo.m_bSupports16bpp)
            || (g_pChitin->cVideo.m_nBpp == 24 && !g_pChitin->cVideo.m_bSupports24bpp)
            || (g_pChitin->cVideo.m_nBpp == 32 && !g_pChitin->cVideo.m_bSupports32bpp)) {
            g_pChitin->m_bReInitializing = TRUE;
            PostMessageA(g_pChitin->GetWnd()->GetSafeHwnd(), WM_DESTROY, 0, 0);
            return FALSE;
        }

        switch (g_pChitin->cVideo.m_nBpp) {
        case 16:
            g_pChitin->cVideo.m_pDirectDraw2->SetDisplayMode(CVideo::SCREENWIDTH,
                CVideo::SCREENHEIGHT,
                16,
                g_pChitin->cVideo.m_dwMipMapCount16,
                0);
            break;
        case 24:
            g_pChitin->cVideo.m_pDirectDraw2->SetDisplayMode(CVideo::SCREENWIDTH,
                CVideo::SCREENHEIGHT,
                24,
                g_pChitin->cVideo.m_dwMipMapCount24,
                0);
            break;
        case 32:
            g_pChitin->cVideo.m_pDirectDraw2->SetDisplayMode(CVideo::SCREENWIDTH,
                CVideo::SCREENHEIGHT,
                32,
                g_pChitin->cVideo.m_dwMipMapCount32,
                0);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
            // __LINE__: 6137
            UTIL_ASSERT(FALSE);
        }

        for (int index = 0; index < 256; index++) {
            CVidImage::rgbTempPal[index] = -1;
        }
    }

    CreateSurfaces(bFullscreen);

    if (!bFullscreen) {
        SetClipper(g_pChitin->cVideo.m_pDirectDrawClipper);
    }

    g_pChitin->cVideo.m_pCurrentVidMode = this;

    return TRUE;
}

// 0x79B420
BOOLEAN CVidInf::SetClipper(IDirectDrawClipper* lpDirectDrawClipper)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 6203
    UTIL_ASSERT(pSurfaces[CVIDINF_SURFACE_FRONT] != NULL && !g_pChitin->FullScreen());

    if (pSurfaces[CVIDINF_SURFACE_FRONT]->SetClipper(lpDirectDrawClipper) != DD_OK) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 6208
        UTIL_ASSERT(FALSE);
    }

    return TRUE;
}

// 0x79B4A0
BOOL CVidInf::CreateSurfaces(BOOLEAN bFullscreen)
{
    CString v1;
    DDSURFACEDESC surfaceDesc = { 0 };
    HRESULT hr;

    field_14 = FALSE;
    surfaceDesc.dwSize = sizeof(surfaceDesc);

    if (bFullscreen) {
        surfaceDesc.dwFlags = DDSD_BACKBUFFERCOUNT | DDSD_CAPS;
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
        surfaceDesc.dwBackBufferCount = 1;
    } else {
        surfaceDesc.dwFlags = DDSD_CAPS;
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_PRIMARYSURFACE;
    }

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_FRONT]), NULL);
    if (hr != DD_OK) {
        if (bFullscreen) {
            field_14 = TRUE;
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX;
        } else {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
        }

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_FRONT]), NULL);
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_FRONT] = NULL;
            return FALSE;
        }
    }

    g_pChitin->cVideo.m_pDirectDraw2->GetDisplayMode(&surfaceDesc);

    g_pChitin->m_nScreenWidth = surfaceDesc.dwWidth;
    g_pChitin->m_nScreenHeight = surfaceDesc.dwHeight;

    if (!bFullscreen || field_14) {
        g_pChitin->SetRenderCount(1);
    } else {
        g_pChitin->SetRenderCount(2);
    }

    if (bFullscreen) {
        DDSCAPS caps;
        caps.dwCaps = DDSCAPS_BACKBUFFER;

        hr = pSurfaces[CVIDINF_SURFACE_FRONT]->GetAttachedSurface(&caps, &(pSurfaces[CVIDINF_SURFACE_BACK]));
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_BACK] = NULL;
            return FALSE;
        }
    } else {
        surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
        surfaceDesc.dwWidth = CVideo::SCREENWIDTH;
        surfaceDesc.dwHeight = CVideo::SCREENHEIGHT;

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_BACK]), NULL);
        if (hr != DD_OK) {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

            hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_BACK]), NULL);
            if (hr != DD_OK) {
                CheckResults(hr);
                pSurfaces[CVIDINF_SURFACE_BACK] = NULL;
                return FALSE;
            }
        }
    }

    surfaceDesc.ddpfPixelFormat.dwFlags = sizeof(surfaceDesc.ddpfPixelFormat);

    hr = pSurfaces[CVIDINF_SURFACE_BACK]->GetPixelFormat(&(surfaceDesc.ddpfPixelFormat));
    if (hr != DD_OK) {
        return FALSE;
    }

    ParsePixelFormat(surfaceDesc.ddpfPixelFormat);

    DDCOLORKEY colorKey;
    colorKey.dwColorSpaceLowValue = m_dwGBitMask;
    colorKey.dwColorSpaceLowValue = m_dwGBitMask;

    surfaceDesc.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;

    if (g_pChitin->cVideo.m_nBpp == 16
        && (g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
            || g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast)) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
    } else {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
    }

    surfaceDesc.dwWidth = 256;
    surfaceDesc.dwHeight = 64;

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_4]), NULL);
    if (hr != DD_OK) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_4]), NULL);
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_4] = NULL;
            return FALSE;
        }
    }

    pSurfaces[CVIDINF_SURFACE_4]->SetColorKey(DDCKEY_SRCBLT, &colorKey);

    if (!bFullscreen || field_14) {
        pSurfaces[CVIDINF_SURFACE_5] = NULL;
    } else {
        if (g_pChitin->cVideo.m_nBpp == 16
            && (g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
                || g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast)) {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
        } else {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
        }

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_5]), NULL);
        if (hr != DD_OK) {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

            hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_5]), NULL);
            if (hr != DD_OK) {
                pSurfaces[CVIDINF_SURFACE_5] = NULL;
                return FALSE;
            }
        }

        pSurfaces[CVIDINF_SURFACE_5]->SetColorKey(DDCKEY_SRCBLT, &colorKey);
    }

    if (g_pChitin->cVideo.m_nBpp == 16
        && (g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
            || g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast
            || g_pChitin->cVideo.cVidBlitter.m_bSoftMirrorBlt)) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
    } else {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
    }

    surfaceDesc.dwWidth = CVIDINF_FX_WIDTH;
    surfaceDesc.dwHeight = CVIDINF_FX_HEIGHT;

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_2]), NULL);
    if (hr == DD_OK) {
        if (g_pChitin->cVideo.m_nBpp != 16
            || (!g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
                && !g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast
                && !g_pChitin->cVideo.cVidBlitter.m_bSoftMirrorBlt)) {
            pSurfaces[CVIDINF_SURFACE_3] = NULL;

            if (g_pChitin->m_bUseMirrorFX) {
                surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
                surfaceDesc.dwWidth = CVIDINF_FX_WIDTH;
                surfaceDesc.dwHeight = CVIDINF_FX_HEIGHT;

                hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_3]), NULL);
                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_3]->SetColorKey(DDCKEY_SRCBLT, &colorKey);
                } else {
                    pSurfaces[CVIDINF_SURFACE_3] = NULL;
                }
            }
        }
    } else {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_2]), NULL);
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_2] = NULL;
            return FALSE;
        }
    }

    pSurfaces[CVIDINF_SURFACE_2]->SetColorKey(DDCKEY_SRCBLT, &colorKey);

    if (g_pChitin->cVideo.m_nBpp == 16
        && (g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
            || g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast
            || g_pChitin->cVideo.cVidBlitter.m_bSoftMirrorBlt)) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
    } else {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;
    }

    surfaceDesc.dwWidth = 64;
    surfaceDesc.dwHeight = 64;

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_6]), NULL);
    if (hr != DD_OK) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_6]), NULL);
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_6] = NULL;
            return FALSE;
        }
    }

    pSurfaces[CVIDINF_SURFACE_6]->SetColorKey(DDCKEY_SRCBLT, &colorKey);

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_7]), NULL);
    if (hr != DD_OK) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;

        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_7]), NULL);
        if (hr != DD_OK) {
            pSurfaces[CVIDINF_SURFACE_7] = NULL;
            return FALSE;
        }
    }

    pSurfaces[CVIDINF_SURFACE_7]->SetColorKey(DDCKEY_SRCBLT, &colorKey);

    if (g_pChitin->cVideo.m_nBpp == 16
        && (g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
            || g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast)) {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
    } else {
        surfaceDesc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    }

    surfaceDesc.dwWidth = 64;
    surfaceDesc.dwHeight = 64;

    for (m_nVRamSurfaces = 0; m_nVRamSurfaces < word_8BA320 && m_nVRamSurfaces < SEVEN_EIGHT_ZERO && hr == DD_OK; m_nVRamSurfaces++) {
        hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(m_pVRamSurfaces[m_nVRamSurfaces]), NULL);
        if (hr != DD_OK) {
            m_pVRamSurfaces[m_nVRamSurfaces--] = NULL;
        }
    }

    if (m_nVRamSurfaces == word_8BA320) {
        if (g_pChitin->cVideo.m_nBpp != 16
            || (!g_pChitin->cVideo.cVidBlitter.m_bSoftBlt
                && !g_pChitin->cVideo.cVidBlitter.m_bSoftBltFast)) {
            surfaceDesc.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY | DDSCAPS_OFFSCREENPLAIN;

            for (; m_nVRamSurfaces < SEVEN_EIGHT_ZERO && hr == DD_OK; m_nVRamSurfaces++) {
                hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(m_pVRamSurfaces[m_nVRamSurfaces]), NULL);
                if (hr != DD_OK) {
                    m_pVRamSurfaces[m_nVRamSurfaces--] = NULL;
                }
            }
        }
    }

    LoadFogOWarSurfaces(CString(""));

    return TRUE;
}

// 0x79BDF0
BOOL CVidInf::DeactivateVideoMode(CVidMode* pNextVidMode)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return DestroySurfaces3d(pNextVidMode);
    }

    if (pNextVidMode != NULL && pNextVidMode->GetType() == 0) {
        return TRUE;
    }

    if (!g_pChitin->m_bFullscreen) {
        SetClipper(NULL);
    }

    DestroySurfaces();

    m_nSurfaces = 0;

    if (pSurfaces != NULL) {
        free(pSurfaces);
        pSurfaces = NULL;
    }

    if (m_pVRamSurfaces != NULL) {
        free(m_pVRamSurfaces);
        m_pVRamSurfaces = NULL;
    }

    return TRUE;
}

// 0x79BE90
void CVidInf::DestroySurfaces()
{
    if (pSurfaces != NULL) {
        if (pSurfaces[CVIDINF_SURFACE_FRONT] != NULL) {
            pSurfaces[CVIDINF_SURFACE_FRONT]->Release();
            pSurfaces[CVIDINF_SURFACE_FRONT] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_BACK] != NULL) {
            pSurfaces[CVIDINF_SURFACE_BACK]->Release();
            pSurfaces[CVIDINF_SURFACE_BACK] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_2] != NULL) {
            pSurfaces[CVIDINF_SURFACE_2]->Release();
            pSurfaces[CVIDINF_SURFACE_2] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_3] != NULL) {
            pSurfaces[CVIDINF_SURFACE_3]->Release();
            pSurfaces[CVIDINF_SURFACE_3] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_6] != NULL) {
            pSurfaces[CVIDINF_SURFACE_6]->Release();
            pSurfaces[CVIDINF_SURFACE_6] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_7] != NULL) {
            pSurfaces[CVIDINF_SURFACE_7]->Release();
            pSurfaces[CVIDINF_SURFACE_7] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_4] != NULL) {
            pSurfaces[CVIDINF_SURFACE_4]->Release();
            pSurfaces[CVIDINF_SURFACE_4] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_5] != NULL) {
            pSurfaces[CVIDINF_SURFACE_5]->Release();
            pSurfaces[CVIDINF_SURFACE_5] = NULL;
        }

        if (pSurfaces[CVIDINF_SURFACE_8] != NULL) {
            pSurfaces[CVIDINF_SURFACE_8]->Release();
            pSurfaces[CVIDINF_SURFACE_8] = NULL;
        }
    }

    if (m_pVRamSurfaces != NULL) {
        for (int k = 0; k < m_nVRamSurfaces; k++) {
            m_pVRamSurfaces[k]->Release();
            m_pVRamSurfaces[k] = NULL;
        }
    }

    m_nVRamSurfaces = 0;
}

// #binary-identical
// 0x79BFF0
void CVidInf::DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        DoTextOut3d(nSurface, sText, x, y, color);
        return;
    }

    if (nSurface < m_nSurfaces) {
        IDirectDrawSurface* pSurface = pSurfaces[nSurface];
        if (pSurface != NULL) {
            HRESULT hr;
            HDC hdc;

            do {
                hr = pSurface->GetDC(&hdc);
                CheckResults(hr);
            } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

            if (hr == DD_OK) {
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, color);
                TextOutA(hdc, x, y, sText, sText.GetLength());

                do {
                    hr = pSurface->ReleaseDC(hdc);
                    CheckResults(hr);
                } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
            }
        }
    }
}

// #binary-identical
// 0x79C0E0
void CVidInf::DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height)
{
    if (nSurface < m_nSurfaces) {
        IDirectDrawSurface* pSurface = pSurfaces[nSurface];
        if (pSurface != NULL) {
            HRESULT hr;
            HDC hdc;

            do {
                hr = pSurface->GetDC(&hdc);
                CheckResults(hr);
            } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

            if (hr == DD_OK) {
                HFONT hFont = CreateFontA(height,
                    0,
                    0,
                    0,
                    FW_NORMAL,
                    FALSE,
                    FALSE,
                    FALSE,
                    DEFAULT_CHARSET,
                    OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS,
                    DEFAULT_QUALITY,
                    DEFAULT_PITCH,
                    FF_DONTCARE);

                HGDIOBJ hPrev = SelectObject(hdc, hFont);

                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, color);
                TextOutA(hdc, x, y, sText, sText.GetLength());

                HGDIOBJ hFontToRemove = SelectObject(hdc, hPrev);
                DeleteObject(hFontToRemove);

                do {
                    hr = pSurface->ReleaseDC(hdc);
                    CheckResults(hr);
                } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
            }
        }
    }
}

// #binary-identical
// 0x79C1E0
BOOL CVidInf::Flip(BOOL bRenderCursor)
{
    if (m_bPrintScreen) {
        SaveScreen();
        m_bPrintScreen = FALSE;
    }

    DisplayFrameRate(0);

    if (g_pChitin->FullScreen()) {
        return FullScreenFlip(bRenderCursor);
    } else {
        return WindowedFlip(bRenderCursor);
    }
}

// 0x79C230
BOOL CVidInf::FullScreenFlip(BOOL bRenderCursor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return WindowedFlip3d(bRenderCursor);
    }

    CRect rOldPointerStorage;
    BOOL bPointerRendered;
    if (bRenderCursor) {
        RECT src;
        src.left = 0;
        src.top = 0;
        src.right = 256;
        src.bottom = 64;

        if (!field_14) {
            do {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(pSurfaces[CVIDINF_SURFACE_5],
                    0,
                    0,
                    g_pChitin->GetCurrentVideoMode()->pSurfaces[CVIDINF_SURFACE_4],
                    &src,
                    DDBLTFAST_WAIT);
                CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            } while (!g_pChitin->field_1932);
        }

        rOldPointerStorage = m_rPointerStorage;
        m_rPointerStorage.left = 0;
        m_rPointerStorage.top = 0;
        m_rPointerStorage.right = 0;
        m_rPointerStorage.bottom = 0;

        g_pChitin->m_bPointerUpdated = FALSE;
        bPointerRendered = RenderPointer(CVIDINF_SURFACE_BACK);
    } else {
        bPointerRendered = FALSE;
    }

    do {
        HRESULT hr = pSurfaces[CVIDINF_SURFACE_FRONT]->Flip(NULL, DDFLIP_WAIT);
        CheckResults(hr);
        if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
            break;
        }
    } while (!g_pChitin->field_1932);

    if (bRenderCursor) {
        if (field_14) {
            if (bPointerRendered
                && rOldPointerStorage.Width() > 0
                && rOldPointerStorage.Height() > 0) {
                m_pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_4, CVIDINF_SURFACE_BACK, rOldPointerStorage);
            }
        } else {
            if (bPointerRendered
                && rOldPointerStorage.Width() > 0
                && rOldPointerStorage.Height() > 0) {
                m_pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_5, CVIDINF_SURFACE_BACK, rOldPointerStorage);
            }
        }
    }

    return TRUE;
}

// 0x79C400
BOOL CVidInf::WindowedFlip(BOOL bRenderCursor)
{
    if (CChitin::byte_8FB950) {
        return TRUE;
    }

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return WindowedFlip3d(bRenderCursor);
    }

    BOOL bPointerRendered;
    if (bRenderCursor) {
        m_rPointerStorage.left = 0;
        m_rPointerStorage.top = 0;
        m_rPointerStorage.right = 0;
        m_rPointerStorage.bottom = 0;
        g_pChitin->m_bPointerUpdated = FALSE;
        bPointerRendered = RenderPointer(CVIDINF_SURFACE_BACK);
    } else {
        bPointerRendered = FALSE;
    }

    do {
        RECT srcRect;
        srcRect.left = 0;
        srcRect.top = 0;
        srcRect.right = CVideo::SCREENWIDTH;
        srcRect.bottom = CVideo::SCREENHEIGHT;

        RECT destRect = g_pChitin->field_E8;

        HRESULT hr = g_pChitin->cVideo.cVidBlitter.Blt(pSurfaces[CVIDINF_SURFACE_FRONT],
            &destRect,
            pSurfaces[CVIDINF_SURFACE_BACK],
            &srcRect,
            DDBLT_WAIT,
            NULL);
        CheckResults(hr);
        if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
            break;
        }
    } while (!g_pChitin->field_1932);

    if (bRenderCursor && bPointerRendered) {
        if (m_rPointerStorage.Width() > 0 && m_rPointerStorage.Height() > 0) {
            m_pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_4, CVIDINF_SURFACE_BACK, m_rPointerStorage);
        }
    }

    return TRUE;
}

// #binary-identical
// 0x79C580
BOOL CVidInf::GetCursorSurfaceSize(CSize& size)
{
    if (pSurfaces[CVIDINF_SURFACE_4] != NULL) {
        size.cx = 256;
        size.cy = 64;
        return TRUE;
    }
    return FALSE;
}

// #binary-identical
// 0x79C5B0
BOOL CVidInf::GetFXSize(CSize& size)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated || pSurfaces[CVIDINF_SURFACE_2] != NULL) {
        size.cx = CVIDINF_FX_WIDTH;
        size.cy = CVIDINF_FX_HEIGHT;
        return TRUE;
    }
    return FALSE;
}

// 0x79C5F0
BOOL CVidInf::GetFXSurface(INT& nSurface, DWORD dwFlags)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        nSurface = 0;
        return FALSE;
    }

    if (g_pChitin->m_bUseMirrorFX) {
        if (pSurfaces[CVIDINF_SURFACE_3] != NULL) {
            if ((dwFlags & 0x30) != 0) {
                nSurface = 3;
                return TRUE;
            }
        }
    }

    if (pSurfaces[CVIDINF_SURFACE_2] != NULL) {
        nSurface = 2;
        return TRUE;
    }

    nSurface = -1;
    return FALSE;
}

// 0x79C680
IDirectDrawSurface* CVidInf::GetFXSurfacePtr(DWORD dwFlags)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return NULL;
    }

    if (g_pChitin->m_bUseMirrorFX) {
        if (pSurfaces[CVIDINF_SURFACE_3] != NULL) {
            if ((dwFlags & 0x30) != 0) {
                return pSurfaces[CVIDINF_SURFACE_3];
            }
        }
    }

    return pSurfaces[CVIDINF_SURFACE_2];
}

// 0x79C6D0
LPVOID CVidInf::GetLockedSurface()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return CVideo3d::texImageData;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 7398
    UTIL_ASSERT(m_SurfaceDesc.lpSurface != NULL);

    return m_SurfaceDesc.lpSurface;
}

// 0x79C720
LONG CVidInf::GetSurfacePitch()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        if (g_pChitin->cVideo.field_13A) {
            return CVidTile::BYTES_PER_TEXEL << 9;
        } else {
            return CVidTile::BYTES_PER_TEXEL * m_rLockedRect.Width();
        }
    } else {
        if (m_SurfaceDesc.lpSurface != NULL) {
            return m_SurfaceDesc.lPitch;
        } else {
            return 0;
        }
    }
}

// 0x79C770
BOOL CVidInf::FXPrep(CRect& rFXRect, DWORD dwFlags, const CPoint& ptPos, const CPoint& ptReference, const CRect& rClip)
{
    CPoint pt = ptReference;

    if (g_pChitin->cVideo.Is3dAccelerated()) {
        memset(CVideo3d::texImageData, 0, rFXRect.Height() * 2048);
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 7486
    UTIL_ASSERT(!((dwFlags & CVIDCELL_FXPREP_COPYFROMBACK) && (dwFlags & CVIDCELL_FXPREP_CLEARFILL)));

    DDBLTFX fx;
    fx.dwSize = sizeof(fx);
    fx.dwFillColor = field_24;

    if (GetFXSurfacePtr(dwFlags) == NULL) {
        return FALSE;
    }

    if ((dwFlags & 0x10) != 0) {
        pt.x = rFXRect.Width() - pt.x;
    }

    if ((dwFlags & 0x20) != 0) {
        pt.y = rFXRect.Height() - pt.y;
    }

    pt.x = ptPos.x - pt.x;
    pt.y = ptPos.y - pt.y;

    if ((dwFlags & CVIDCELL_FXPREP_COPYFROMBACK) != 0) {
        FXBltBackTo(pt, rFXRect, rClip, dwFlags);
    } else if ((dwFlags & CVIDCELL_FXPREP_CLEARFILL) != 0) {
        do {
            HRESULT hr = g_pChitin->cVideo.cVidBlitter.Blt(GetFXSurfacePtr(dwFlags),
                rFXRect,
                NULL,
                NULL,
                DDBLT_WAIT | DDBLT_COLORFILL,
                &fx);
            if (!CheckResults(hr)) {
                return FALSE;
            }

            if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                break;
            }
        } while (1);
    }

    if (field_170) {
        INT nSurface;
        if (!GetFXSurface(nSurface, dwFlags)) {
            return FALSE;
        }

        DrawLine(rFXRect.left,
            rFXRect.top,
            rFXRect.right - 1,
            rFXRect.top,
            nSurface,
            rFXRect,
            RGB(255, 255, 0));
        DrawLine(rFXRect.right - 1,
            rFXRect.top,
            rFXRect.right - 1,
            rFXRect.bottom - 1,
            nSurface,
            rFXRect,
            RGB(255, 255, 0));
        DrawLine(rFXRect.right - 1,
            rFXRect.bottom - 1,
            rFXRect.left,
            rFXRect.bottom - 1,
            nSurface,
            rFXRect,
            RGB(255, 255, 0));
        DrawLine(rFXRect.left,
            rFXRect.bottom - 1,
            rFXRect.left,
            rFXRect.top,
            nSurface,
            rFXRect,
            RGB(255, 255, 0));
    }

    return TRUE;
}

// 0x79CA10
void CVidInf::FXBltBackTo(const CPoint& ptTopLeft, const CRect& rFXRect, const CRect& rClip, DWORD dwFlags)
{
    CRect rSrc(ptTopLeft, rFXRect.Size());

    if (g_pChitin->cVideo.Is3dAccelerated()) {
        return;
    }

    CPoint pt(0, 0);
    BOOL bUseFX = FALSE;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 7588
    UTIL_ASSERT(GetFXSurfacePtr(dwFlags) != NULL);

    DDBLTFX fx;
    fx.dwDDFX = 0;

    if ((dwFlags & 0x20) != 0) {
        if (rSrc.top < rClip.top) {
            rSrc.top = rClip.top;
        }

        if (rSrc.bottom >= rClip.bottom) {
            pt.y = rSrc.bottom - rClip.bottom;
            rSrc.bottom = rClip.bottom;
        }

        fx.dwDDFX |= DDBLTFX_MIRRORUPDOWN;
        bUseFX = TRUE;
    } else {
        if (rSrc.top < rClip.top) {
            pt.y = rClip.top - rSrc.top;
            rSrc.top = rClip.top;
        }

        if (rSrc.bottom >= rClip.bottom) {
            rSrc.bottom = rClip.bottom;
        }
    }

    if ((dwFlags & 0x10) != 0) {
        if (rSrc.left < rClip.left) {
            rSrc.left = rClip.left;
        }

        if (rSrc.right >= rClip.right) {
            pt.x = rSrc.right - rClip.right;
            rSrc.right = rClip.right;
        }

        fx.dwDDFX |= DDBLTFX_MIRRORLEFTRIGHT;
        bUseFX = TRUE;
    } else {
        if (rSrc.left < rClip.left) {
            pt.x = rClip.left - rSrc.left;
            rSrc.left = rClip.left;
        }

        if (rSrc.right >= rClip.right) {
            rSrc.right = rClip.right;
        }
    }

    if (rSrc.bottom > rSrc.top && rSrc.right > rSrc.left) {
        if (bUseFX) {
            fx.dwSize = sizeof(fx);
            while (1) {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.Blt(GetFXSurfacePtr(dwFlags),
                    CRect(pt, rSrc.Size()),
                    pSurfaces[CVIDINF_SURFACE_BACK],
                    rSrc,
                    DDBLT_WAIT | DDBLT_DDFX,
                    &fx);
                CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            }
        } else {
            while (1) {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(GetFXSurfacePtr(dwFlags),
                    pt.x,
                    pt.y,
                    pSurfaces[CVIDINF_SURFACE_BACK],
                    rSrc,
                    DDBLTFAST_WAIT);
                CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            }
        }
    }
}

// 0x79CC90
BOOL CVidInf::FXBltToBack(CRect& rFXRect, INT x, INT y, INT nRefPointX, INT nRefPointY, const CRect& rClip, DWORD dwFlags)
{
    BOOL bUseFX = FALSE;
    CRect rSrc(rFXRect);

    if (!g_pChitin->cVideo.Is3dAccelerated()) {
        if (GetFXSurfacePtr(dwFlags) == NULL) {
            return FALSE;
        }
    }

    LONG v1;
    if ((dwFlags & 0x10) != 0) {
        v1 = rFXRect.Width() - nRefPointX;
    } else {
        v1 = nRefPointX;
    }

    LONG v2;
    if ((dwFlags & 0x20) != 0) {
        v2 = rFXRect.Height() - nRefPointY;
    } else {
        v2 = nRefPointY;
    }

    CPoint pt(x - v1, y - v2);

    if (g_pChitin->cVideo.Is3dAccelerated()) {
        CVidCell::RenderTexture(pt.x,
            pt.y,
            rFXRect,
            m_rLockedRect.Size(),
            rClip,
            dwFlags | 0x1);
        return TRUE;
    }

    DDBLTFX fx;
    fx.dwDDFX = 0;

    if ((dwFlags & 0x20) != 0) {
        if (pt.y < rClip.top) {
            rSrc.bottom += pt.y - rClip.top;
            pt.y = rClip.top;
        }

        if (rSrc.Height() + pt.y - 1 >= rClip.bottom) {
            rSrc.top = pt.y + rSrc.bottom - rClip.bottom;
        }

        fx.dwDDFX |= DDBLTFX_MIRRORUPDOWN;
        bUseFX = TRUE;
    } else {
        if (pt.y < rClip.top) {
            rSrc.top += rClip.top - pt.y;
            pt.y = rClip.top;
        }

        if (rSrc.Height() + pt.y - 1 >= rClip.bottom) {
            rSrc.bottom = rSrc.top + rClip.bottom - pt.y;
        }
    }

    if ((dwFlags & 0x10) != 0) {
        if (pt.x < rClip.left) {
            rSrc.right += pt.x - rClip.left;
            pt.x = rClip.left;
        }

        if (rSrc.Width() + pt.x - 1 >= rClip.right) {
            rSrc.left = pt.x + rSrc.right - rClip.right;
        }

        fx.dwDDFX |= DDBLTFX_MIRRORLEFTRIGHT;
        bUseFX = TRUE;
    } else {
        if (pt.x < rClip.left) {
            rSrc.left += rClip.left - pt.x;
        }

        if (rSrc.Width() + pt.x - 1 >= rClip.right) {
            rSrc.right = rSrc.left + rClip.right - pt.x;
        }
    }

    if (rSrc.bottom > rSrc.top && rSrc.right > rSrc.left) {
        if (bUseFX) {
            while (1) {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.Blt(pSurfaces[CVIDINF_SURFACE_BACK],
                    CRect(pt, rSrc.Size()),
                    GetFXSurfacePtr(dwFlags),
                    rSrc,
                    DDBLT_WAIT | DDBLT_KEYSRC | DDBLT_DDFX,
                    &fx);
                CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            }
        } else {
            while (1) {
                HRESULT hr = g_pChitin->cVideo.cVidBlitter.BltFast(pSurfaces[CVIDINF_SURFACE_BACK],
                    pt.x,
                    pt.y,
                    GetFXSurfacePtr(dwFlags),
                    rSrc,
                    DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
                CheckResults(hr);
                if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                    break;
                }
            }
        }
    }

    return TRUE;
}

// 0x79D030
void CVidInf::FXClear(LPVOID pSurface, INT nSize)
{
    memset(pSurface, 0, 4 * nSize);
}

// 0x79D100
BOOL CVidInf::FXRender(CVidCell* pVidCell, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return pVidCell->FXRender3d(nRefPointX, nRefPointY, m_rLockedRect, dwFlags | 0x40, nTransValue, 0);
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        return pVidCell->Render(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface), m_SurfaceDesc.lPitch, nRefPointX, nRefPointY, dwFlags, nTransValue);
    }

    return FALSE;
}

// 0x79D180
BOOL CVidInf::FXRender(CVidCell* pVidCell, INT nRefPtX, INT nRefPtY, const CRect& rClip, BOOLEAN a5, DWORD dwFlags)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return pVidCell->FXRender3d(nRefPtX,
            nRefPtY,
            m_rLockedRect,
            rClip,
            a5,
            dwFlags | 0x40,
            FALSE);
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        return pVidCell->Render(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            nRefPtX,
            nRefPtY,
            rClip,
            a5,
            dwFlags,
            CPoint(0, 0));
    }

    return FALSE;
}

// 0x79D220
BOOL CVidInf::FXRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CVideo3d::glEnable(GL_TEXTURE_2D);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        g_pChitin->cVideo.field_13E = 2;

        CVideo3d::glBindTexture(GL_TEXTURE_2D, 2);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glColor4f(1.0, 1.0, 1.0, 1.0);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        if (g_pChitin->cVideo.field_13A) {
            pParticle->Render(CVideo3d::texImageData,
                CVidTile::BYTES_PER_TEXEL * CVIDINF_FX_WIDTH,
                rClip,
                nFlag,
                nBlobSize);
        } else {
            pParticle->Render(CVideo3d::texImageData,
                CVidTile::BYTES_PER_TEXEL * rClip.Width(),
                rClip,
                nFlag,
                nBlobSize);
        }
        return TRUE;
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        pParticle->Render(m_SurfaceDesc.lpSurface, m_SurfaceDesc.lPitch, rClip, nFlag, nBlobSize);
        return TRUE;
    }

    return FALSE;
}

// 0x79D450
BOOL CVidInf::FXRender(CPoint* pPoints, INT nPoints, const CRect& rSurface, COLORREF rgbColor, BOOL bClipped)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CVideo3d::glEnable(GL_TEXTURE_2D);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        g_pChitin->cVideo.field_13E = 2;

        CVideo3d::glBindTexture(GL_TEXTURE_2D, 2);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        CVideo3d::glColor4f(1.0, 1.0, 1.0, 1.0);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        if (g_pChitin->cVideo.field_13A) {
            return DrawPoints(pPoints,
                nPoints,
                reinterpret_cast<WORD*>(CVideo3d::texImageData),
                CVidTile::BYTES_PER_TEXEL * CVIDINF_FX_WIDTH,
                rSurface,
                rgbColor,
                bClipped);
        } else {
            return DrawPoints(pPoints,
                nPoints,
                reinterpret_cast<WORD*>(CVideo3d::texImageData),
                CVidTile::BYTES_PER_TEXEL * rSurface.Width(),
                rSurface,
                rgbColor,
                bClipped);
        }
        return TRUE;
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        return DrawPoints(pPoints,
            nPoints,
            reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            rSurface,
            rgbColor,
            bClipped);
    }

    return FALSE;
}

// #binary-identical
// 0x79D050
BOOL CVidInf::FXLock(CRect& rFXRect, DWORD dwFlags)
{
    m_rLockedRect = rFXRect;

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 7905
    UTIL_ASSERT(m_SurfaceDesc.lpSurface == NULL);

    INT nSurface;
    if (!GetFXSurface(nSurface, dwFlags)) {
        return FALSE;
    }

    m_SurfaceDesc.dwSize = sizeof(m_SurfaceDesc);
    return !!LockSurface(nSurface, &m_SurfaceDesc, rFXRect);
}

// 0x79D970
BOOL CVidInf::FXTextOut(CVidFont* pFont, const CString& sString, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        LONG lPitch = g_pChitin->cVideo.field_13A
            ? CVidTile::BYTES_PER_TEXEL * CVIDINF_FX_WIDTH
            : CVidTile::BYTES_PER_TEXEL * m_rLockedRect.Width();
        return pFont->TextOut3d(sString,
            reinterpret_cast<WORD*>(CVideo3d::texImageData),
            lPitch,
            x,
            y,
            rClip,
            dwFlags,
            bDemanded);
    }

    if (m_SurfaceDesc.lpSurface == NULL) {
        return FALSE;
    }

    if (g_pChitin->GetFontName() == "" || pFont->GetResRef() == "STATES2") {
        return pFont->TextOut(sString,
            reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            x,
            y,
            rClip,
            dwFlags,
            bDemanded);
    }

    INT nSurface;
    g_pChitin->GetCurrentVideoMode()->GetFXSurface(nSurface, dwFlags);

    return pFont->TextOutEx(nSurface,
        sString,
        x,
        y,
        rClip,
        dwFlags,
        bDemanded);
}

// 0x79DB10
BOOL CVidInf::FXUnlock(DWORD dwFlags, const CRect* pFxRect, const CPoint& ptRef)
{
    DWORD dwPolyFlags = 0;

    if ((dwFlags & 0x10) != 0) {
        dwPolyFlags |= 0x4;
    }

    if ((dwFlags & 0x20) != 0) {
        dwPolyFlags |= 0x8;
    }

    if (g_pChitin->cVideo.Is3dAccelerated()) {
        if (pFxRect != NULL) {
            dwPolyFlags |= 0x2;

            CVidPoly cVidPoly;

            WORD vertices[8];
            vertices[0] = static_cast<WORD>(pFxRect->left);
            vertices[1] = static_cast<WORD>(pFxRect->top);
            vertices[2] = static_cast<WORD>(pFxRect->right);
            vertices[3] = vertices[1];
            vertices[4] = vertices[2];
            vertices[5] = static_cast<WORD>(pFxRect->bottom);
            vertices[6] = vertices[0];
            vertices[7] = vertices[5];
            cVidPoly.SetPoly(vertices, 4);

            if (g_pChitin->cVideo.field_13A) {
                cVidPoly.FillPoly(reinterpret_cast<WORD*>(CVideo3d::texImageData),
                    CVidTile::BYTES_PER_TEXEL * CVIDINF_FX_WIDTH,
                    pFxRect,
                    field_24,
                    dwPolyFlags,
                    ptRef);
            } else {
                cVidPoly.FillPoly(reinterpret_cast<WORD*>(CVideo3d::texImageData),
                    CVidTile::BYTES_PER_TEXEL * m_rLockedRect.Width(),
                    pFxRect,
                    field_24,
                    dwPolyFlags,
                    ptRef);
            }
        }
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 8369
    UTIL_ASSERT(m_SurfaceDesc.lpSurface != NULL);

    if (pFxRect != NULL) {
        CVidPoly cVidPoly;

        WORD vertices[8];
        vertices[0] = static_cast<WORD>(pFxRect->left);
        vertices[1] = static_cast<WORD>(pFxRect->top);
        vertices[2] = static_cast<WORD>(pFxRect->right);
        vertices[3] = vertices[1];
        vertices[4] = vertices[2];
        vertices[5] = static_cast<WORD>(pFxRect->bottom);
        vertices[6] = vertices[0];
        vertices[7] = vertices[5];
        cVidPoly.SetPoly(vertices, 4);

        cVidPoly.FillPoly(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            pFxRect,
            field_24,
            dwPolyFlags | 0x2,
            ptRef);
    }

    INT nSurface;
    if (!GetFXSurface(nSurface, dwFlags)) {
        return FALSE;
    }

    // NOTE: Uninline.
    UnLockSurface(nSurface, m_SurfaceDesc.lpSurface);
    m_SurfaceDesc.lpSurface = NULL;

    return TRUE;
}

// #binary-identical
// 0x79DD50
BOOL CVidInf::BKLock(CRect& rBack)
{
    m_rLockedRect = rBack;

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 8425
    UTIL_ASSERT(m_SurfaceDesc.lpSurface == NULL);

    m_SurfaceDesc.dwSize = sizeof(m_SurfaceDesc);
    return !!LockSurface(0, &m_SurfaceDesc, rBack);
}

// 0x79DDE0
BOOL CVidInf::BKUnlock()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 8466
    UTIL_ASSERT(m_SurfaceDesc.lpSurface != NULL);

    // NOTE: Uninline.
    UnLockSurface(0, m_SurfaceDesc.lpSurface);

    m_SurfaceDesc.lpSurface = NULL;

    return TRUE;
}

// 0x79DE50
BOOL CVidInf::BKRender(CVidCell* pVidCell, INT x, INT y, const CRect& rClip, BOOLEAN bDemanded, DWORD dwFlags)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        memset(CVideo3d::texImageData, 0, sizeof(DWORD) * CVIDINF_FX_WIDTH * CVIDINF_FX_HEIGHT);

        CRect rNewClip(rClip);
        rNewClip.OffsetRect(m_rLockedRect.left, m_rLockedRect.top);

        return pVidCell->Render3d(m_rLockedRect.left + x,
            m_rLockedRect.top + y,
            rNewClip,
            bDemanded,
            dwFlags | 0x1);
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 8512
    UTIL_ASSERT(m_SurfaceDesc.lpSurface != NULL);

    return pVidCell->Render(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
        m_SurfaceDesc.lPitch,
        x,
        y,
        rClip,
        bDemanded,
        dwFlags,
        CPoint(0, 0));
}

// 0x79DF60
BOOL CVidInf::BKRender(CVidCell* pVidCell, INT x, INT y, DWORD dwFlags, INT nTransVal)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        if (g_pChitin->cVideo.field_13A) {
            memset(CVideo3d::texImageData, 0, sizeof(DWORD) * CVIDINF_FX_WIDTH * m_rLockedRect.Height());
        } else {
            memset(CVideo3d::texImageData, 0, sizeof(DWORD) * m_rLockedRect.Width() * m_rLockedRect.Height());
        }

        return pVidCell->Render3d(m_rLockedRect.left + x,
            m_rLockedRect.top + y,
            dwFlags | 0x1,
            nTransVal);
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 8561
    UTIL_ASSERT(m_SurfaceDesc.lpSurface != NULL);

    return pVidCell->Render(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
        m_SurfaceDesc.lPitch,
        x,
        y,
        dwFlags,
        nTransVal);
}

// 0x79E060
BOOL CVidInf::BKRender(CParticle* pParticle, const CRect& rClip, USHORT nFlag, USHORT nBlobSize)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        pParticle->Render3d(rClip, m_rLockedRect, nFlag, nBlobSize);
        return TRUE;
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        pParticle->Render(m_SurfaceDesc.lpSurface, m_SurfaceDesc.lPitch, rClip, nFlag, nBlobSize);
    }

    return FALSE;
}

// 0x79E0D0
BOOL CVidInf::BKRenderEllipse(const CPoint& ptCenter, const CSize& axes, const CRect& rClip, COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CRect rNewClip(rClip);
        rNewClip.OffsetRect(m_rLockedRect.TopLeft());
        DrawEllipse3d(ptCenter + m_rLockedRect.TopLeft(), axes, &rNewClip, rgbColor);
        return TRUE;
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        DrawEllipse(ptCenter, axes, m_SurfaceDesc, &rClip, rgbColor);
        return TRUE;
    }

    return FALSE;
}

// 0x79E1D0
BOOL CVidInf::BKRenderLine(int nXFrom, int nYFrom, int nXTo, int nYTo, const CRect& rSurface, COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CRect rNewSurface(rSurface);
        rNewSurface.OffsetRect(m_rLockedRect.TopLeft());
        return DrawLine3d(nXFrom + m_rLockedRect.left,
            nYFrom + m_rLockedRect.top,
            nXTo + m_rLockedRect.left,
            nYTo + m_rLockedRect.top,
            rNewSurface,
            rgbColor);
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        return DrawLine(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            m_SurfaceDesc,
            rSurface,
            rgbColor,
            FALSE);
    }

    return FALSE;
}

// 0x79E2D0
BOOL CVidInf::BKRenderConvexPoly(CVidPoly* pPoly, const CRect& rClipRect, DWORD dwColor, DWORD dwFlags, const CPoint& ptRef)
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        return pPoly->FillConvexPoly3d(rClipRect, dwColor, dwFlags, ptRef);
    }

    if (m_SurfaceDesc.lpSurface != NULL) {
        return pPoly->FillConvexPoly(reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            rClipRect,
            dwColor,
            dwFlags,
            ptRef);
    }

    return FALSE;
}

// 0x79E340
BOOL CVidInf::BKTextOut(CVidFont* pFont, const CString& sString, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        CRect rNewClip;
        rNewClip.left = m_rLockedRect.left + rClip.left;
        rNewClip.top = m_rLockedRect.top + rClip.top;
        rNewClip.right = m_rLockedRect.left + rClip.right;
        rNewClip.bottom = m_rLockedRect.top + rClip.bottom;

        return pFont->TextOut3d(sString,
            x + m_rLockedRect.left,
            y + m_rLockedRect.top,
            rNewClip,
            dwFlags,
            bDemanded);
    }

    if (g_pChitin->m_sFontName.Compare("") == 0 || pFont->GetResRef() == "STATES2") {
        return pFont->TextOut(sString,
            reinterpret_cast<WORD*>(m_SurfaceDesc.lpSurface),
            m_SurfaceDesc.lPitch,
            x,
            y,
            rClip,
            dwFlags,
            bDemanded);
    }

    CRect rNewClip;
    rNewClip.left = m_rLockedRect.left + rClip.left;
    rNewClip.top = m_rLockedRect.top + rClip.top;
    rNewClip.top = m_rLockedRect.left + rClip.right;
    rNewClip.bottom = m_rLockedRect.top + rClip.bottom;

    return pFont->TextOutEx(CVIDINF_SURFACE_BACK,
        sString,
        x + m_rLockedRect.left,
        y + m_rLockedRect.top,
        rNewClip,
        dwFlags,
        bDemanded);
}

// #binary-identical
// 0x79E4A0
void CVidInf::GetFogOWarTileRect(unsigned char a2, CRect& rTileRect)
{
    switch (a2) {
    case 0:
    case 4:
        rTileRect.SetRect(0, 0, 32, 32);
        break;
    case 1:
    case 5:
        rTileRect.SetRect(32, 0, 64, 32);
        break;
    case 2:
    case 6:
        rTileRect.SetRect(0, 32, 32, 64);
        break;
    case 3:
    case 7:
        rTileRect.SetRect(32, 32, 64, 64);
        break;
    default:
        rTileRect.SetRect(0, 0, 0, 0);
        break;
    }
}

// 0x79E550
void CVidInf::LoadFogOWarSurfaces(const CString& a2)
{
    CVidCell tileVidCell;
    CRect rTileRect(0, 0, 64, 64);
    DDBLTFX fx;
    DDSURFACEDESC surfaceDesc;
    BOOL bSurfaceLocked;

    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
        if (g_pChitin->field_F8 != 1) {
            if (!a2.IsEmpty()) {
                field_73A = a2;
            } else {
                if (field_73A.IsEmpty()) {
                    return;
                }
            }

            // NOTE: Uninline.
            tileVidCell.SetResRef(CResRef(field_73A), FALSE, TRUE, TRUE);

            tileVidCell.SequenceSet(0);
            tileVidCell.pRes->Demand();
            tileVidCell.RealizePalette(1);

            fx.dwSize = sizeof(fx);
            fx.dwFillColor = m_dwGBitMask;

            if (pSurfaces[CVIDINF_SURFACE_6] != NULL) {
                g_pChitin->cVideo.cVidBlitter.Blt(pSurfaces[CVIDINF_SURFACE_6], &rTileRect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &fx);

                surfaceDesc.dwSize = sizeof(surfaceDesc);

                field_174 = FALSE;
                bSurfaceLocked = LockSurface(6, &surfaceDesc, rTileRect);
                field_174 = TRUE;

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                // __LINE__: 8995
                UTIL_ASSERT(surfaceDesc.lpSurface != NULL);

                if (bSurfaceLocked) {
                    tileVidCell.FrameSet(0);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 0, 0, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(1);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 32, 0, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(2);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 0, 32, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(2);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 32, 32, rTileRect, TRUE, 0, CPoint(0, 0));

                    // NOTE: Uninline.
                    UnLockSurface(6, surfaceDesc.lpSurface);
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_7] != NULL) {
                g_pChitin->cVideo.cVidBlitter.Blt(pSurfaces[CVIDINF_SURFACE_7], &rTileRect, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &fx);

                surfaceDesc.dwSize = sizeof(surfaceDesc);

                bSurfaceLocked = LockSurface(7, &surfaceDesc, rTileRect);

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                // __LINE__: 9017
                UTIL_ASSERT(surfaceDesc.lpSurface != NULL);

                if (bSurfaceLocked) {
                    tileVidCell.FrameSet(4);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 0, 0, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(5);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 32, 0, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(6);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 0, 32, rTileRect, TRUE, 0, CPoint(0, 0));

                    tileVidCell.FrameSet(7);
                    tileVidCell.Render(reinterpret_cast<WORD*>(surfaceDesc.lpSurface), surfaceDesc.lPitch, 32, 32, rTileRect, TRUE, 0, CPoint(0, 0));

                    // NOTE: Uninline.
                    UnLockSurface(7, surfaceDesc.lpSurface);
                }
            }
        }
    }
}

// 0x79E9F0
BOOLEAN CVidInf::SaveScreen()
{
    CString sPath;
    CString sPrefix;
    CFile cFile;
    WIN32_FIND_DATAA fileFindData;
    HANDLE hFileFind;

    hFileFind = FindFirstFileA(SCREEN_SHOT_DIR_NAME, &fileFindData);
    if (hFileFind != INVALID_HANDLE_VALUE) {
        if ((fileFindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0) {
            return FALSE;
        }
    } else {
        if (!CreateDirectoryA(SCREEN_SHOT_DIR_NAME, NULL)) {
            return FALSE;
        }
    }

    FindClose(hFileFind);

    g_pChitin->GetScreenShotFilePrefix(sPrefix);

    BOOL bFound;
    do {
        bFound = FALSE;

        sPath.Format("%s\\%s%03d.%s",
            SCREEN_SHOT_DIR_NAME,
            sPrefix,
            m_nPrintFile,
            SCREEN_SHOT_EXTENSION);

        hFileFind = FindFirstFileA(sPath, &fileFindData);
        if (hFileFind != INVALID_HANDLE_VALUE) {
            bFound = TRUE;
            m_nPrintFile++;
        }
        FindClose(hFileFind);
    } while (bFound);

    CRect rClip(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    LPBYTE data;
    LONG size;

    if (!PrintSurfaceToBmp(data, 0, rClip, size, 1)) {
        if (data != NULL) {
            delete data;
        }

        return FALSE;
    }

    if (data == NULL) {
        return FALSE;
    }

    if (!cFile.Open(sPath, CFile::OpenFlags::modeCreate | CFile::OpenFlags::modeWrite, NULL)) {
        delete data;
        return FALSE;
    }

    cFile.Write(data, size);
    cFile.Close();

    delete data;
    return TRUE;
}

// 0x79F6A0
BOOL CVidInf::RenderPointer()
{
    if (m_bPointerAnimating) {
        return TRUE;
    }

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return TRUE;
    }

    if (g_pChitin->m_bFullscreen) {
        return RenderPointer(CVIDINF_SURFACE_FRONT);
    }

    CRect rPointer(m_rPointerStorage);

    CSingleLock positionLock(&(g_pChitin->m_csPointerPosition));
    CSingleLock renderLock(&m_csRenderPointer);
    rPointer.OffsetRect(g_pChitin->field_E8.left, g_pChitin->field_E8.top);

    if (g_pChitin->m_bPointerUpdated) {
        return FALSE;
    }

    renderLock.Lock(INFINITE);
    CVidCell* pPointerVidCell = m_pPointerVidCell;
    renderLock.Unlock();

    if (!m_bPointerInside || pPointerVidCell == NULL || !m_bPointerEnabled) {
        field_10 = FALSE;
        return FALSE;
    }

    g_pChitin->m_bPointerUpdated = TRUE;

    positionLock.Lock(INFINITE);
    CPoint pt = g_pChitin->m_ptPointer;
    positionLock.Unlock();

    if (field_10 && rPointer.Width() > 0 && rPointer.Height() > 0) {
        pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_4,
            CVIDINF_SURFACE_FRONT,
            rPointer);
    }

    field_10 = TRUE;

    g_pChitin->GetWnd()->ClientToScreen(&pt);

    renderLock.Lock(INFINITE);
    pPointerVidCell->StoreBackground(CVIDINF_SURFACE_FRONT,
        CVIDINF_SURFACE_4,
        pt.x,
        pt.y,
        g_pChitin->field_E8,
        m_rPointerStorage,
        m_nPointerNumber > 0);
    g_pChitin->GetWnd()->ScreenToClient(&m_rPointerStorage);
    RenderPointerImage(pPointerVidCell,
        CVIDINF_SURFACE_FRONT,
        m_nPointerNumber,
        pt.x,
        pt.y,
        g_pChitin->field_E8);
    renderLock.Unlock();

    return TRUE;
}

// 0x79F520
void CVidInf::RenderFlash(UINT nSurface, COLORREF rgbColor, unsigned char a4, const CRect& rClip)
{
    if (g_pChitin->cVideo.Is3dAccelerated()) {
        RenderFlash3d(rgbColor, rClip);
        return;
    }

    // FIXME: Unnecessary.
    RECT destRect = rClip;

    if (pSurfaces[nSurface] != NULL) {
        DDBLTFX fx;
        fx.dwSize = sizeof(fx);

        // NOTE: Uninline.
        fx.dwFillColor = ConvertToSurfaceRGB(rgbColor);

        do {
            HRESULT hr = g_pChitin->cVideo.cVidBlitter.Blt(pSurfaces[CVIDINF_SURFACE_FRONT],
                &destRect,
                NULL,
                NULL,
                DDBLT_WAIT | DDBLT_COLORFILL,
                NULL);
            CheckResults(hr);
            if (hr != DDERR_SURFACELOST && hr != DDERR_WASSTILLDRAWING) {
                break;
            }
        } while (!g_pChitin->field_1932);
    }
}

// 0x79F950
BOOL CVidInf::RenderPointer(UINT nSurface)
{
    CSingleLock positionLock(&(g_pChitin->m_csPointerPosition), FALSE);
    CSingleLock renderLock(&m_csRenderPointer);

    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return RenderPointer3d(nSurface);
    }

    if (g_pChitin->m_bPointerUpdated) {
        return FALSE;
    }

    renderLock.Lock(INFINITE);
    CVidCell* pPointerVidCell = m_pPointerVidCell;
    renderLock.Unlock();

    if (!m_bPointerInside || pPointerVidCell == NULL || !m_bPointerEnabled) {
        field_10 = FALSE;
        return FALSE;
    }

    g_pChitin->m_bPointerUpdated = TRUE;

    positionLock.Lock(INFINITE);
    CPoint pt = g_pChitin->m_ptPointer;
    positionLock.Unlock();

    CRect rClip(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);

    if (field_10 && m_rPointerStorage.Width() > 0 && m_rPointerStorage.Height() > 0) {
        pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_4, nSurface, m_rPointerStorage);
    }

    field_10 = TRUE;

    renderLock.Lock(INFINITE);
    pPointerVidCell->StoreBackground(nSurface,
        CVIDINF_SURFACE_4,
        pt.x,
        pt.y,
        rClip,
        m_rPointerStorage,
        m_nPointerNumber > 0);
    RenderPointerImage(pPointerVidCell, nSurface, m_nPointerNumber, pt.x, pt.y, rClip);
    renderLock.Unlock();

    return TRUE;
}

// NOTE: `rClip` can be reference.
//
// 0x79FBA0
void CVidInf::RenderPointerImage(CVidCell* pPointerVidCell, INT nSurface, INT nNumber, INT x, INT y, CRect rClip)
{
    CVidCell numberVidCell;

    BOOL bResult = pPointerVidCell->Render(nSurface,
        x,
        y,
        rClip,
        NULL,
        0,
        m_dwCursorRenderFlags,
        -1);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 9646
    UTIL_ASSERT(bResult);

    if (nNumber > 0) {
        // NOTE: Uninline.
        numberVidCell.SetResRef(CResRef("NUMBER"), FALSE, TRUE, TRUE);

        numberVidCell.SequenceSet(0);
        numberVidCell.SetTintColor(pPointerVidCell->GetTintColor());

        CSize frameSize;
        pPointerVidCell->GetCurrentFrameSize(frameSize, FALSE);

        CPoint ptCenter;
        pPointerVidCell->GetCurrentCenterPoint(ptCenter, FALSE);

        CPoint pt(max(frameSize.cx - ptCenter.x - 7, 9) + x,
            max(frameSize.cy - ptCenter.y - 7, 9) + y);

        INT nCurr = nNumber;
        if (pt.y >= y - ptCenter.y) {
            while (nCurr > 0 && pt.x >= x - ptCenter.x) {
                INT nDigit = nCurr % 10;
                nCurr /= 10;
                if (nDigit > 0 || nCurr > 0) {
                    numberVidCell.FrameSet(nDigit);

                    BOOL bResult = numberVidCell.Render(nSurface,
                        pt.x,
                        pt.y,
                        rClip,
                        NULL,
                        0,
                        m_dwCursorRenderFlags,
                        -1);

                    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
                    // __LINE__: 9686
                    UTIL_ASSERT(bResult);
                }
                pt.x -= 5;
            }
        }
    }
}

// 0x79FFA0
void CVidInf::RestoreSurfaces()
{
    HRESULT hr;
    BOOLEAN v1 = TRUE;

    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
        if (!g_pChitin->field_1932) {
            if (pSurfaces[CVIDINF_SURFACE_FRONT] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_FRONT]->Restore();
                CheckResults(hr);
            }

            DDCOLORKEY ddck;
            ddck.dwColorSpaceLowValue = m_dwGBitMask;
            ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;

            if (!g_pChitin->m_bFullscreen) {
                hr = pSurfaces[CVIDINF_SURFACE_BACK]->Restore();
                CheckResults(hr);
            }

            if (pSurfaces[CVIDINF_SURFACE_2] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_2]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_2]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_3] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_3]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_3]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_6] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_6]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_6]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                } else {
                    v1 = FALSE;
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_7] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_7]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_7]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                } else {
                    v1 = FALSE;
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_4] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_4]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_4]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (pSurfaces[CVIDINF_SURFACE_5] != NULL) {
                hr = pSurfaces[CVIDINF_SURFACE_5]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    pSurfaces[CVIDINF_SURFACE_5]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            for (int k = 0; k < m_nVRamSurfaces; k++) {
                if (m_pVRamSurfaces[k] == NULL) {
                    break;
                }

                hr = m_pVRamSurfaces[k]->Restore();
                CheckResults(hr);
            }

            if (v1 == TRUE && field_174 == 1) {
                LoadFogOWarSurfaces(CString(""));
            }
        }
    }
}

// #binary-identical
// 0x7A0210
void CVidInf::ParsePixelFormat(const DDPIXELFORMAT& ddpf)
{
    USHORT bit;
    DWORD dwRBitMask;
    DWORD dwGBitMask;
    DWORD dwBBitMask;

    m_dwRBitMask = ddpf.dwRBitMask;
    m_dwGBitMask = ddpf.dwGBitMask;
    m_dwBBitMask = ddpf.dwBBitMask;

    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        dwRBitMask = m_dwRBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwRBitMask & 1) != 0) {
                break;
            }
            dwRBitMask >>= 1;
        }

        if (dwRBitMask == 15) {
            m_dwRBitCount = 4;
        } else if (dwRBitMask == 31) {
            m_dwRBitCount = 5;
        } else {
            m_dwRBitCount = 6;
        }

        m_dwRBitShift = bit;

        dwGBitMask = m_dwGBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwGBitMask & 1) != 0) {
                break;
            }

            dwGBitMask >>= 1;
        }

        if (dwGBitMask == 15) {
            m_dwGBitCount = 4;
        } else if (dwGBitMask == 31) {
            m_dwGBitCount = 5;
        } else {
            m_dwGBitCount = 6;
        }

        m_dwGBitShift = bit;

        dwBBitMask = m_dwBBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwBBitMask & 1) != 0) {
                break;
            }

            dwBBitMask >>= 1;
        }

        if (dwBBitMask == 15) {
            m_dwBBitCount = 4;
        } else if (dwBBitMask == 31) {
            m_dwBBitCount = 5;
        } else {
            m_dwBBitCount = 6;
        }

        m_dwBBitShift = bit;

        field_C2 = 8 - m_dwRBitCount;
        field_C6 = 8 - m_dwGBitCount;
        field_CA = 8 - m_dwBBitCount;
        break;
    case 24:
    case 32:
        dwRBitMask = m_dwRBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwRBitMask & 1) != 0) {
                break;
            }
            dwRBitMask >>= 1;
        }

        m_dwRBitShift = bit;

        dwGBitMask = m_dwGBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwGBitMask & 1) != 0) {
                break;
            }

            dwGBitMask >>= 1;
        }

        m_dwGBitShift = bit;

        dwBBitMask = m_dwBBitMask;
        for (bit = 0; bit < 16; bit++) {
            if ((dwBBitMask & 1) != 0) {
                break;
            }

            dwBBitMask >>= 1;
        }

        m_dwBBitShift = bit;

        m_dwRBitCount = 8;
        m_dwGBitCount = 8;
        m_dwBBitCount = 8;
        field_C2 = 0;
        field_C6 = 0;
        field_CA = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 9962
        UTIL_ASSERT(FALSE);
    }
}

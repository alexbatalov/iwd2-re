#include "CVidInf.h"

#include <gl/gl.h>

#include "CChitin.h"
#include "CParticle.h"
#include "CUtil.h"
#include "CVidImage.h"

#define SEVEN_EIGHT_ZERO 780

// 0x907B20
unsigned char CVidInf::dword_907B20[512 * 512 * 4];

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
            g_pChitin->field_E0 = TRUE;
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

    surfaceDesc.dwWidth = 512;
    surfaceDesc.dwHeight = 512;

    hr = g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&surfaceDesc, &(pSurfaces[CVIDINF_SURFACE_2]), NULL);
    if (hr == DD_OK) {
        if (g_pChitin->cVideo.m_nBpp != 16
            || (!g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBlt
                && !g_pChitin->cVideo.cVidBlitter.m_bSoftSrcKeyBltFast
                && !g_pChitin->cVideo.cVidBlitter.m_bSoftMirrorBlt)) {
            pSurfaces[CVIDINF_SURFACE_3] = NULL;

            if (g_pChitin->m_bUseMirrorFX) {
                surfaceDesc.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY | DDSCAPS_OFFSCREENPLAIN;
                surfaceDesc.dwWidth = 512;
                surfaceDesc.dwHeight = 512;

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

// 0x7BE210
BOOL CVidInf::DestroySurfaces3d(CVidMode* pNextVidMode)
{
    if (pNextVidMode != NULL && pNextVidMode->GetType() == 0) {
        return TRUE;
    }

    field_178.Unload();

    GLuint texture1 = 2;
    glDeleteTextures(1, &texture1);
    CheckResults3d(0);

    GLuint texture2 = 5;
    glDeleteTextures(1, &texture2);

    GLuint texture3 = 6;
    glDeleteTextures(1, &texture3);

    for (int index = 0; index < m_nVRamSurfaces; index++) {
        GLuint texture = static_cast<GLuint>(index);
        glDeleteTextures(1, &texture);
        CheckResults3d(0);
    }

    sub_7BEDE0();

    return TRUE;
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
    // TODO: Incomplete.

    return FALSE;
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
        field_E4.left = 0;
        field_E4.top = 0;
        field_E4.right = 0;
        field_E4.bottom = 0;
        g_pChitin->field_1902 = 0;
        bPointerRendered = RenderPointer(0);
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
        if (field_E4.Width() > 0 && field_E4.Height() > 0) {
            m_pPointerVidCell->RestoreBackground(CVIDINF_SURFACE_4, CVIDINF_SURFACE_BACK, field_E4);
        }
    }

    return FALSE;
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
        size.cx = 512;
        size.cy = 512;
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
        return dword_907B20;
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

    if (m_SurfaceDesc.lpSurface == NULL) {
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
        // TODO: Replace with function pointers.
        glEnable(GL_TEXTURE_2D);
        CheckResults3d(0);

        g_pChitin->cVideo.field_13E = 2;

        glBindTexture(GL_TEXTURE_2D, 2);
        CheckResults3d(0);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        CheckResults3d(0);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        CheckResults3d(0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        CheckResults3d(0);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        CheckResults3d(0);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        CheckResults3d(0);

        if (g_pChitin->cVideo.field_13A) {
            pParticle->Render(dword_907B20,
                CVidTile::BYTES_PER_TEXEL * 512,
                rClip,
                nFlag,
                nBlobSize);
        } else {
            pParticle->Render(dword_907B20,
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
        // TODO: Replace with function pointers.
        glEnable(GL_TEXTURE_2D);
        CheckResults3d(0);

        g_pChitin->cVideo.field_13E = 2;

        glBindTexture(GL_TEXTURE_2D, 2);
        CheckResults3d(0);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        CheckResults3d(0);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        CheckResults3d(0);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        CheckResults3d(0);

        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        CheckResults3d(0);

        glColor4f(1.0, 1.0, 1.0, 1.0);
        CheckResults3d(0);

        if (g_pChitin->cVideo.field_13A) {
            return DrawPoints(pPoints,
                nPoints,
                reinterpret_cast<WORD*>(dword_907B20),
                CVidTile::BYTES_PER_TEXEL * 512,
                rSurface,
                rgbColor,
                bClipped);
        } else {
            return DrawPoints(pPoints,
                nPoints,
                reinterpret_cast<WORD*>(dword_907B20),
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
        memset(dword_907B20, 0, 4 * 512 * 512);

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
            memset(dword_907B20, 0, m_rLockedRect.Height() * (4 * 512));
        } else {
            memset(dword_907B20, 0, 4 * m_rLockedRect.Width() * m_rLockedRect.Height());
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

            CResRef resRef(field_73A);
            tileVidCell.SetResRef(resRef, TRUE, TRUE);
            tileVidCell.m_header.SetResRef(resRef, TRUE, FALSE);

            if (tileVidCell.pRes != NULL) {
                tileVidCell.pRes->field_7E = tileVidCell.m_header.GetResRef() == "";
            }

            tileVidCell.m_bDoubleSize = FALSE;
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

// 0x7BE4E0
BOOL CVidInf::WindowedFlip3d(BOOL bRenderCursor)
{
    // TODO: Incomplete.

    return TRUE;
}

// #binary-identical
// 0x7BE530
void CVidInf::DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
    field_178.SetColor(color, 0, 0);

    CRect screenRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    field_178.TextOut3d(sText, x, y + 16, screenRect, 0, 0);
}

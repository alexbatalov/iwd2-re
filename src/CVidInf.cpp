#include "CVidInf.h"

#include "CChitin.h"
#include "CUtil.h"

// #binary-identical
// 0x79AF00
CVidInf::CVidInf()
{
    m_nSurfaces = 0;
    m_pSurfaces = NULL;
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
    if (m_pSurfaces != NULL) {
        delete m_pSurfaces;
        m_pSurfaces = NULL;
    }

    m_nSurfaces = 0;
}

// 0x79B100
BOOL CVidInf::ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x79B420
BOOLEAN CVidInf::SetClipper(IDirectDrawClipper* lpDirectDrawClipper)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 6203
    UTIL_ASSERT(m_pSurfaces[CVIDINF_SURFACE_FRONT] != NULL && !g_pChitin->FullScreen());

    if (m_pSurfaces[CVIDINF_SURFACE_FRONT]->SetClipper(lpDirectDrawClipper) != DD_OK) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 6208
        UTIL_ASSERT(FALSE);
    }

    return TRUE;
}

// 0x79BDF0
BOOL CVidInf::DeactivateVideoMode(int a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x79BE90
void CVidInf::DestroySurfaces()
{
    if (m_pSurfaces != NULL) {
        if (m_pSurfaces[1] != NULL) {
            m_pSurfaces[1]->Release();
            m_pSurfaces[1] = NULL;
        }

        if (m_pSurfaces[0] != NULL) {
            m_pSurfaces[0]->Release();
            m_pSurfaces[0] = NULL;
        }

        if (m_pSurfaces[2] != NULL) {
            m_pSurfaces[2]->Release();
            m_pSurfaces[2] = NULL;
        }

        if (m_pSurfaces[3] != NULL) {
            m_pSurfaces[3]->Release();
            m_pSurfaces[3] = NULL;
        }

        if (m_pSurfaces[6] != NULL) {
            m_pSurfaces[6]->Release();
            m_pSurfaces[6] = NULL;
        }

        if (m_pSurfaces[7] != NULL) {
            m_pSurfaces[7]->Release();
            m_pSurfaces[7] = NULL;
        }

        if (m_pSurfaces[4] != NULL) {
            m_pSurfaces[4]->Release();
            m_pSurfaces[4] = NULL;
        }

        if (m_pSurfaces[5] != NULL) {
            m_pSurfaces[5]->Release();
            m_pSurfaces[5] = NULL;
        }

        if (m_pSurfaces[8] != NULL) {
            m_pSurfaces[8]->Release();
            m_pSurfaces[8] = NULL;
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
        IDirectDrawSurface* pSurface = m_pSurfaces[nSurface];
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
        IDirectDrawSurface* pSurface = m_pSurfaces[nSurface];
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
BOOL CVidInf::Flip(int a2)
{
    if (m_bPrintScreen) {
        SaveScreen();
        m_bPrintScreen = FALSE;
    }

    DisplayFrameRate(0);

    if (g_pChitin->FullScreen()) {
        return FullScreenFlip(a2);
    } else {
        return WindowedFlip(a2);
    }
}

// 0x79C230
BOOL CVidInf::FullScreenFlip(int a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x79C400
BOOL CVidInf::WindowedFlip(int a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// #binary-identical
// 0x79C580
BOOL CVidInf::GetCursorSurfaceSize(CSize& size)
{
    if (m_pSurfaces[4] != NULL) {
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
    if (g_pChitin->cVideo.m_bIs3dAccelerated || m_pSurfaces[2] != NULL) {
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
        if (m_pSurfaces[3] != NULL) {
            if ((dwFlags & 0x30) != 0) {
                nSurface = 3;
                return TRUE;
            }
        }
    }

    if (m_pSurfaces[2] != NULL) {
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
        if (m_pSurfaces[3] != NULL) {
            if ((dwFlags & 0x30) != 0) {
                return m_pSurfaces[3];
            }
        }
    }

    return m_pSurfaces[2];
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
    // TODO: Incomplete.
}

// 0x79FFA0
void CVidInf::RestoreSurfaces()
{
    HRESULT hr;
    BOOLEAN v1 = TRUE;

    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
        if (!g_pChitin->field_1932) {
            if (m_pSurfaces[1] != NULL) {
                hr = m_pSurfaces[1]->Restore();
                CheckResults(hr);
            }

            DDCOLORKEY ddck;
            ddck.dwColorSpaceLowValue = m_dwGBitMask;
            ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;

            if (!g_pChitin->m_bFullscreen) {
                hr = m_pSurfaces[0]->Restore();
                CheckResults(hr);
            }

            if (m_pSurfaces[2] != NULL) {
                hr = m_pSurfaces[2]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[2]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (m_pSurfaces[3] != NULL) {
                hr = m_pSurfaces[3]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[3]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (m_pSurfaces[6] != NULL) {
                hr = m_pSurfaces[6]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[6]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                } else {
                    v1 = FALSE;
                }
            }

            if (m_pSurfaces[7] != NULL) {
                hr = m_pSurfaces[7]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[7]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                } else {
                    v1 = FALSE;
                }
            }

            if (m_pSurfaces[4] != NULL) {
                hr = m_pSurfaces[4]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[4]->SetColorKey(DDCKEY_SRCBLT, &ddck);
                }
            }

            if (m_pSurfaces[5] != NULL) {
                hr = m_pSurfaces[5]->Restore();
                CheckResults(hr);

                if (hr == DD_OK) {
                    m_pSurfaces[5]->SetColorKey(DDCKEY_SRCBLT, &ddck);
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

// #binary-identical
// 0x7BE530
void CVidInf::DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
    field_178.SetColor(color, 0, 0);

    CRect screenRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    field_178.TextOut3d(sText, x, y + 16, screenRect, 0, 0);
}

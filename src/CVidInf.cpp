#include "CVidInf.h"

#include "CChitin.h"

// #binary-identical
// 0x79AF00
CVidInf::CVidInf()
{
    m_nSurfaces = 0;
    m_pSurfaces = NULL;
    field_678 = NULL;
    field_E0 = 4;
    field_67C = 0;
    field_98 = 0;
    field_94 = 0;
    field_73A = "";
    memset(&m_SurfaceDesc, 0, sizeof(m_SurfaceDesc));
    SetRect(&field_160, 0, 0, 0, 0);
    field_170 = 0;
    field_174 = 1;
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

    if (field_678 != NULL) {
        for (int k = 0; k < field_67C; k++) {
            field_678[k]->Release();
            field_678[k] = NULL;
        }
    }

    field_67C = 0;
}

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
            }

            do {
                hr = pSurface->ReleaseDC(hdc);
                CheckResults(hr);
            } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
        }
    }
}

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
            }

            do {
                hr = pSurface->ReleaseDC(hdc);
                CheckResults(hr);
            } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
        }
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
            ddck.dwColorSpaceLowValue = field_1C;
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

            for (int k = 0; k < field_67C; k++) {
                if (field_678[k] == NULL) {
                    break;
                }

                hr = field_678[k]->Restore();
                CheckResults(hr);
            }

            if (v1 == TRUE && field_174 == 1) {
                LoadFogOWarSurfaces(CString(""));
            }
        }
    }
}

// 0x7BE530
void CVidInf::DoTextOut3d(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
    field_178.SetColor(color, 0, 0);

    CRect screenRect(0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);
    field_178.TextOut3d(sText, x, y + 16, screenRect, 0, 0);
}

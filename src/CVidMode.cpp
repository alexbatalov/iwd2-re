#include "CVidMode.h"

#include "CChitin.h"
#include "CUtil.h"

// 0x8BA322
BYTE CVidMode::NUM_FADE_FRAMES = 20;

// #guess
// 0x8FB968
BOOL CVidMode::bInitialized;

// #binary-identical
// 0x799CB0
CVidMode::CVidMode()
{
    field_18 = 0;
    field_1C = 0;
    field_20 = 0;
    field_24 = 0;
    field_98 = 0;
    field_C2 = 0;
    field_C6 = 0;
    field_CA = 0;
    field_D2 = 0;
    field_DC = 0;
    field_D4 = 0;
    field_D8 = 1;
    field_86 = 0;
    field_E0 = 0;
    m_nSurfaces = 0;
    nTickCount = GetTickCount();
    field_94 = 0;
    field_8A = 0;
    field_8E = 0;
    m_pSurfaces = NULL;
    field_E4 = 0;
    field_EC = 0;
    field_E8 = 0;
    field_F0 = 0;
    rgbGlobalTint = 0xFFFFFF;
    field_4 = 0;
    field_8F = 0;
    m_nBrightnessCorrection = 0;
    m_nGammaCorrection = 0;
    field_8 = 0;
    field_C = 0;
    field_10 = 1;
    field_14 = 0;
    m_bFadeTo = 0;
    m_nFade = NUM_FADE_FRAMES;

    bInitialized = TRUE;
}

// #binary-identical
// 0x799EB0
CVidMode::~CVidMode()
{
    bInitialized = FALSE;
}

// 0x799F40
BOOL CVidMode::CheckResults(HRESULT hr)
{
    switch (hr) {
    case DD_OK:
        return TRUE;
    case DDERR_SURFACELOST:
        RestoreSurfaces();
        return FALSE;
    default:
        return FALSE;
    }
}

// 0x795BB0
BOOL CVidMode::CreateSurface(IDirectDrawSurface** lplpDirectDrawSurface, const CSize& cSize)
{
    DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue = field_1C;
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;

    DDSURFACEDESC ddsd = { 0 };
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDCAPS_BLT;
    ddsd.dwWidth = cSize.cx;
    ddsd.dwHeight = cSize.cy;

    if (g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&ddsd, lplpDirectDrawSurface, NULL) != DD_OK) {
        *lplpDirectDrawSurface = NULL;
        return FALSE;
    }

    (*lplpDirectDrawSurface)->SetColorKey(DDCKEY_SRCBLT, &ddck);

    return TRUE;
}

// 0x795C50
void CVidMode::DestroySurface(IDirectDrawSurface** lplpDirectDrawSurface)
{
    if (lplpDirectDrawSurface != NULL) {
        if (*lplpDirectDrawSurface != NULL) {
            (*lplpDirectDrawSurface)->Release();
        }
    }
}

// 0x799CA0
void CVidMode::DestroySurfaces()
{
}

// 0x799E30
void CVidMode::DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
}

// 0x799E60
void CVidMode::LoadFogOWarSurfaces(const CString& a2)
{
}

// 0x799CA0
void CVidMode::RestoreSurfaces()
{
}

// 0x799FA0
BOOL CVidMode::LockSurface(UINT nIndex, LPDDSURFACEDESC pSurfaceDesc, const CRect& rect)
{
    RECT r = static_cast<RECT>(rect);

    if (nIndex >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = m_pSurfaces[nIndex];
    if (pSurface == NULL) {
        return FALSE;
    }

    HRESULT hr;
    do {
        pSurfaceDesc->dwSize = sizeof(*pSurfaceDesc);
        hr = pSurface->Lock(&r, pSurfaceDesc, DDLOCK_WAIT, NULL);
        if (hr == DDERR_SURFACELOST) {
            RestoreSurfaces();
            continue;
        } else {
            CheckResults(hr);
        }
    } while (hr == DDERR_SURFACEBUSY);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 5071
    UTIL_ASSERT(g_pChitin->cVideo.GetBitsPerPixels() == 24 || !((LONG)(pSurfaceDesc->lpSurface) & 0x00000001));

    return hr == DD_OK;
}

// 0x79A820
BOOL CVidMode::UnLockSurface(UINT nIndex, LPVOID lpSurfaceData)
{
    if (nIndex >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = m_pSurfaces[nIndex];
    if (pSurface == NULL) {
        return FALSE;
    }

    return pSurface->Unlock(lpSurfaceData) == DD_OK;
}

// 0x79AC20
void CVidMode::SetWindowedMode(HWND hWnd)
{
    LONG windowStyle = GetWindowLongA(hWnd, GWL_STYLE);
    windowStyle &= ~(WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX);
    windowStyle |= (WS_CAPTION | WS_MINIMIZEBOX);
    SetWindowLongA(hWnd, GWL_STYLE, windowStyle);

    RECT windowRect;
    SetRect(&windowRect, 0, 0, CVideo::SCREENWIDTH, CVideo::SCREENHEIGHT);

    AdjustWindowRectEx(&windowRect,
        GetWindowLongA(hWnd, GWL_STYLE),
        GetMenu(hWnd) != NULL,
        GetWindowLongA(hWnd, GWL_EXSTYLE));

    SetWindowPos(hWnd,
        HWND_TOP,
        0,
        0,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);

    SetWindowPos(hWnd,
        HWND_NOTOPMOST,
        0,
        0,
        0,
        0,
        SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);

    RECT workRect;
    SystemParametersInfoA(SPI_GETWORKAREA, 0, &workRect, 0);

    GetWindowRect(hWnd, &windowRect);

    SetWindowPos(hWnd,
        HWND_TOP,
        min(windowRect.left, workRect.left),
        min(windowRect.top, workRect.top),
        0,
        0,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

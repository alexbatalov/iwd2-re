#include "CVidBlitter.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CWarp.h"

// 0x7B6780
CVidBlitter::CVidBlitter()
{
    m_bSoftSrcKeyBltFast = FALSE;
    m_bSoftBltFast = FALSE;
    m_bSoftSrcKeyBlt = FALSE;
    m_bSoftBlt = FALSE;
    m_bSoftMirrorBlt = FALSE;
    field_E6 = 0;
    field_DE = 0;
    field_E2 = 0;
    m_pfnBltFast = &CVidBlitter::DxBltFast;
    m_pfnBltNoFX = &CVidBlitter::DxBlt;
    m_pfnSrcKeyBltFast = &CVidBlitter::DxBltFast;
    m_pfnSrcKeyBltNoFX = &CVidBlitter::DxBlt;
    m_pfnBltFX = &CVidBlitter::DxBlt;
    m_pfnSrcKeyBltFX = &CVidBlitter::DxBlt;
}

// #binary-identical
// 0x7B67E0
HRESULT CVidBlitter::DxBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    return lpDDSurface->Blt(lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
}

// #binary-identical
// 0x7B6810
HRESULT CVidBlitter::DxBltFast(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    return lpDDSurface->BltFast(lpDestRect->left, lpDestRect->top, lpDDSrcSurface, lpSrcRect, dwFlags);
}

// #binary-identical
// 0x7B6960
void CVidBlitter::Init()
{
    if (g_pChitin->cVideo.m_nBpp != 16) {
        m_pfnBltNoFX = &CVidBlitter::DxBlt;
        m_pfnSrcKeyBltNoFX = &CVidBlitter::DxBlt;
        m_pfnBltFX = &CVidBlitter::DxBlt;
        m_pfnSrcKeyBltFX = &CVidBlitter::DxBlt;
        m_pfnBltFast = &CVidBlitter::DxBltFast;
        m_pfnSrcKeyBltFast = &CVidBlitter::DxBltFast;
    } else {
        if (m_bSoftMirrorBlt) {
            m_pfnBltFX = &CVidBlitter::SoftBlt;
            m_pfnSrcKeyBltFX = &CVidBlitter::SoftSrcKeyBlt;
        } else {
            if (m_bSoftSrcKeyBlt) {
                m_pfnBltFX = &CVidBlitter::DxBlt;
                m_pfnSrcKeyBltFX = &CVidBlitter::SoftSrcKeyBlt;
            } else {
                m_pfnBltFX = &CVidBlitter::DxBlt;
                m_pfnSrcKeyBltFX = &CVidBlitter::DxBlt;
            }
        }

        if (m_bSoftSrcKeyBltFast) {
            m_pfnSrcKeyBltFast = &CVidBlitter::SoftSrcKeyBlt;
        } else {
            m_pfnSrcKeyBltFast = &CVidBlitter::DxBltFast;
        }

        if (m_bSoftSrcKeyBlt) {
            m_pfnSrcKeyBltNoFX = &CVidBlitter::SoftSrcKeyBlt;
        } else {
            m_pfnSrcKeyBltNoFX = &CVidBlitter::DxBlt;
        }

        if (m_bSoftBltFast) {
            m_pfnBltFast = &CVidBlitter::SoftBlt;
        } else {
            m_pfnBltFast = &CVidBlitter::DxBltFast;
        }

        if (m_bSoftBlt) {
            m_pfnBltNoFX = &CVidBlitter::SoftBlt;
        } else {
            m_pfnBltNoFX = &CVidBlitter::DxBlt;
        }
    }
}

// 0x7B6A40
void CVidBlitter::Reset()
{
    if (g_pChitin->pActiveEngine != NULL) {
        g_pChitin->pActiveEngine->EngineDeactivated();
    }

    g_pChitin->field_E0 = 1;

    CVidMode* pVidMode = g_pChitin->cVideo.m_pCurrentVidMode;
    g_pChitin->cVideo.CleanUp();
    g_pChitin->cVideo.m_pCurrentVidMode = pVidMode;

    if (!g_pChitin->cVideo.Initialize(g_pChitin->cWnd.GetSafeHwnd(), g_pChitin->m_bFullscreen)) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidSoftBlt.cpp
        // __LINE__: 342
        UTIL_ASSERT_MSG(FALSE, "Software Blitter re-initialization failed.");
    }

    g_pChitin->Resume();

    if (g_pChitin->pActiveEngine != NULL) {
        g_pChitin->pActiveEngine->EngineActivated();
    }

    field_E6 = 0;
}

// 0x7B6840
HRESULT CVidBlitter::Blt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    if ((dwFlags & DDBLT_DDFX) != 0) {
        if ((dwFlags & DDBLT_KEYSRC) != 0) {
            return (this->*m_pfnSrcKeyBltFX)(lpDDSurface, lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        } else {
            return (this->*m_pfnBltFX)(lpDDSurface, lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        }
    } else {
        if ((dwFlags & DDBLT_KEYSRC) != 0) {
            return (this->*m_pfnSrcKeyBltNoFX)(lpDDSurface, lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        } else {
            return (this->*m_pfnBltNoFX)(lpDDSurface, lpDestRect, lpDDSrcSurface, lpSrcRect, dwFlags, lpDDBltFx);
        }
    }
}

// 0x7B68B0
HRESULT CVidBlitter::BltFast(IDirectDrawSurface* lpDDSurface, DWORD dwX, DWORD dwY, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwTrans)
{
    if ((dwTrans & DDBLTFAST_SRCCOLORKEY) != 0) {
        RECT dest;
        dest.left = dwX;
        dest.top = dwY;
        dest.right = dwX + lpSrcRect->right - lpSrcRect->left;
        dest.bottom = dwY + lpSrcRect->bottom - lpSrcRect->top;
        return (this->*m_pfnSrcKeyBltFast)(lpDDSurface, &dest, lpDDSrcSurface, lpSrcRect, dwTrans, NULL);
    } else {
        RECT dest;
        dest.left = dwX;
        dest.top = dwY;
        dest.right = dwX + lpSrcRect->right - lpSrcRect->left;
        dest.bottom = dwY + lpSrcRect->bottom - lpSrcRect->top;
        return (this->*m_pfnBltFast)(lpDDSurface, &dest, lpDDSrcSurface, lpSrcRect, dwTrans, NULL);
    }
}

// 0x7B7280
HRESULT CVidBlitter::SoftBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    // TODO: Incomplete.

    return S_OK;
}

// 0x7B74F0
HRESULT CVidBlitter::SoftSrcKeyBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx)
{
    // TODO: Incomplete.

    return S_OK;
}

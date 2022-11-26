#ifndef CVIDBLITTER_H_
#define CVIDBLITTER_H_

#include <afx.h>
#include <ddraw.h>

class CVidBlitter {
public:
    typedef HRESULT (CVidBlitter::*BltFunc)(IDirectDrawSurface*, LPRECT, IDirectDrawSurface*, LPRECT, DWORD, LPDDBLTFX);

    CVidBlitter();
    HRESULT DxBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT DxBltFast(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT Blt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT BltFast(IDirectDrawSurface* lpDDSurface, DWORD dwX, DWORD dwY, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwTrans);
    void Init();
    void Reset();
    HRESULT SoftBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
    HRESULT SoftSrcKeyBlt(IDirectDrawSurface* lpDDSurface, LPRECT lpDestRect, IDirectDrawSurface* lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);

    /* 0000 */ BOOLEAN m_bSoftSrcKeyBltFast; // #guess
    /* 0001 */ BOOLEAN m_bSoftBltFast; // #guess
    /* 0002 */ BOOLEAN m_bSoftSrcKeyBlt; // #guess
    /* 0003 */ BOOLEAN m_bSoftBlt; // #guess
    /* 0004 */ BOOLEAN m_bSoftMirrorBlt; // #guess
    /* 00DE */ int field_DE;
    /* 00E2 */ int field_E2;
    /* 00E6 */ unsigned char field_E6;
    /* 00E8 */ BltFunc m_pfnBltNoFX; // #guess
    /* 00EC */ BltFunc m_pfnSrcKeyBltNoFX; // #guess
    /* 00F0 */ BltFunc m_pfnBltFX; // #guess
    /* 00F4 */ BltFunc m_pfnSrcKeyBltFX; // #guess
    /* 00F8 */ BltFunc m_pfnBltFast; // #guess
    /* 00FC */ BltFunc m_pfnSrcKeyBltFast; // #guess
};

#endif /* CVIDBLITTER_H_ */

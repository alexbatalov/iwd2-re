#include "CVidMode.h"

#include <gl/gl.h>

#include "CChitin.h"
#include "CUtil.h"
#include "CVidCell.h"

typedef struct CVIDMODE_CLIP_OUTCODE {
    unsigned int all;
    unsigned int left : 4;
    unsigned int right : 4;
    unsigned int bottom : 4;
    unsigned int top : 4;
} CVIDMODE_CLIP_OUTCODE;

// 0x8FB964
const CString CVidMode::SCREEN_SHOT_EXTENSION("bmp");

// 0x8FB95C
const CString CVidMode::SCREEN_SHOT_DIR_NAME(".\\ScrnShot");

// 0x8BA320
short CVidMode::word_8BA320 = 100;

// 0x8BA322
BYTE CVidMode::NUM_FADE_FRAMES = 20;

// #guess
// 0x8FB968
BOOL CVidMode::bInitialized;

// 0x799C70
BOOLEAN CVidMode::SaveScreen()
{
    return FALSE;
}

// 0x799C80
BOOL CVidMode::RenderPointer()
{
    return TRUE;
}

// #binary-identical
// 0x799CB0
CVidMode::CVidMode()
{
    m_dwRBitMask = 0;
    m_dwGBitMask = 0;
    m_dwBBitMask = 0;
    field_24 = 0;
    field_98 = 0;
    field_C2 = 0;
    field_C6 = 0;
    field_CA = 0;
    field_D2 = 0;
    field_DC = 0;
    m_bPointerEnabled = FALSE;
    m_bPointerInside = TRUE;
    m_nColorDepth = 0;
    field_E0 = 0;
    m_nSurfaces = 0;
    nTickCount = GetTickCount();
    field_94 = 0;
    m_pPointerVidCell = NULL;
    m_bPointerAnimating = FALSE;
    pSurfaces = NULL;
    m_rPointerStorage.left = 0;
    m_rPointerStorage.top = 0;
    m_rPointerStorage.right = 0;
    m_rPointerStorage.bottom = 0;
    rgbGlobalTint = 0xFFFFFF;
    m_nPrintFile = 0;
    m_bPrintScreen = FALSE;
    m_nBrightnessCorrection = 0;
    m_nGammaCorrection = 0;
    m_nPointerNumber = 0;
    m_dwCursorRenderFlags = 0;
    field_10 = 1;
    field_14 = 0;
    m_bFadeTo = 0;
    m_nFade = NUM_FADE_FRAMES;

    bInitialized = TRUE;
}

// 0x799E10
BOOLEAN CVidMode::SetClipper(IDirectDrawClipper* lpDirectDrawClipper)
{
    return FALSE;
}

// #binary-identical
// 0x799EB0
CVidMode::~CVidMode()
{
    bInitialized = FALSE;
}

// #binary-identical
// 0x799E50
COLORREF CVidMode::GetTransparentColor()
{
    return 65280;
}

// #binary-identical
// 0x799E70
void CVidMode::PrintScreen()
{
    m_bPrintScreen = TRUE;
}

// 0x799E80
int CVidMode::GetPointerNumber()
{
    return m_nPointerNumber;
}

// #binary-identical
// 0x799F40
BOOL CVidMode::CheckResults(HRESULT hr)
{
    if (hr != DD_OK) {
        switch (hr) {
        case DDERR_SURFACELOST:
            RestoreSurfaces();
            break;
        }

        return FALSE;
    }

    return TRUE;
}

// 0x799F70
COLORREF CVidMode::GetGlobalTintColor()
{
    return rgbGlobalTint;
}

// 0x795980
BOOL CVidMode::ClipLine(INT& nXFrom, INT& nYFrom, INT& nXTo, INT& nYTo, const CRect& rClip)
{
    CVIDMODE_CLIP_OUTCODE fromCode;
    CVIDMODE_CLIP_OUTCODE toCode;
    CVIDMODE_CLIP_OUTCODE finalCode;
    INT x;
    INT y;

    while (1) {
        memset(&fromCode, 0, sizeof(fromCode));
        memset(&toCode, 0, sizeof(toCode));

        if (nYFrom < rClip.top) {
            fromCode.top |= 1;
            fromCode.all += 8;
        } else if (nYFrom > rClip.bottom) {
            fromCode.bottom |= 1;
            fromCode.all += 4;
        }

        if (nXFrom < rClip.left) {
            fromCode.left |= 1;
            fromCode.all += 1;
        } else if (nXFrom > rClip.right) {
            fromCode.right |= 1;
            fromCode.all += 2;
        }

        if (nYTo < rClip.top) {
            toCode.top |= 1;
            toCode.all += 8;
        } else if (nYTo > rClip.bottom) {
            toCode.bottom |= 1;
            toCode.all += 4;
        }

        if (nXTo < rClip.left) {
            toCode.left |= 1;
            toCode.all += 1;
        } else if (nXTo > rClip.right) {
            toCode.right |= 1;
            toCode.all += 2;
        }

        if (fromCode.all == 0 && toCode.all == 0) {
            return TRUE;
        }

        if ((fromCode.all & toCode.all) != 0) {
            return FALSE;
        }

        finalCode = fromCode.all != 0 ? fromCode : toCode;

        if (finalCode.top) {
            y = rClip.top;
            x = nXFrom + (nXTo - nXFrom) * (y - nYFrom) / (nYTo - nYFrom);
        } else if (finalCode.bottom) {
            y = rClip.bottom;
            x = nXFrom + (nXTo - nXFrom) * (y - nYFrom) / (nYTo - nYFrom);
        } else if (finalCode.right) {
            x = rClip.right;
            y = nYFrom + (nYTo - nYFrom) * (x - nXFrom) / (nXTo - nXFrom);
        } else if (finalCode.left) {
            x = rClip.left;
            y = nYFrom + (nYTo - nYFrom) * (x - nXFrom) / (nXTo - nXFrom);
        }

        if (finalCode.all == fromCode.all) {
            nXFrom = x;
            nYFrom = y;
        } else {
            nXTo = x;
            nYTo = y;
        }
    }
}

// #binary-identical
// 0x795BB0
BOOL CVidMode::CreateSurface(IDirectDrawSurface** lplpDirectDrawSurface, const CSize& cSize)
{
    DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue = m_dwGBitMask;
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

// 0x795C70
void CVidMode::DisplayFrameRate(UINT nSurface)
{
    if (g_pChitin->field_1A2A) {
        CString sFrameRate;
        sFrameRate.Format("%02d %02d %d ",
            g_pChitin->m_nRenderPerSec,
            g_pChitin->m_nAIPerSec,
            GetNumVRamSurfaces());

        CString v3;
        DoTextOut(nSurface, sFrameRate, (CVideo::SCREENWIDTH >> 1) - 240, 4, 255);
    }
}

// 0x795D50
DWORD CVidMode::ConvertToSurfaceRGB(COLORREF rgb)
{
    if (g_pChitin->cVideo.m_nBpp == 16) {
        return ((GetRValue(rgb) >> field_C2) << m_dwRBitShift) | ((GetGValue(rgb) >> field_C6) << m_dwGBitShift) | ((GetBValue(rgb) >> field_CA) << m_dwBBitShift);
    } else {
        return (GetRValue(rgb) << m_dwRBitShift) | (GetGValue(rgb) << m_dwGBitShift) | (GetBValue(rgb) << m_dwBBitShift);
    }
}

// 0x795E00
COLORREF CVidMode::ApplyBrightnessContrast(COLORREF rgb)
{
    if (m_nBrightnessCorrection != 0) {
        BYTE v1 = ~m_nBrightnessCorrection;
        rgb = RGB(~((v1 * ~GetRValue(rgb)) >> 8),
            ~((v1 * ~GetGValue(rgb)) >> 8),
            ~((v1 * ~GetBValue(rgb)) >> 8));
    }

    if (m_nGammaCorrection != 0) {
        BYTE v2 = m_nGammaCorrection + (1 << CVidPalette::LIGHT_SCALE);
        rgb = RGB(min((v2 * GetRValue(rgb)) >> CVidPalette::LIGHT_SCALE, 255),
            min((v2 * GetGValue(rgb)) >> CVidPalette::LIGHT_SCALE, 255),
            min((v2 * GetBValue(rgb)) >> CVidPalette::LIGHT_SCALE, 255));
    }

    return rgb;
}

// 0x795F10
void CVidMode::ApplyFadeAmount(CVIDPALETTE_COLOR* pColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return;
    }

    pColor->rgbRed = pColor->rgbRed * m_nFade / NUM_FADE_FRAMES;

    // NOTE: Strange check for 3D, probably result of some inlining
    pColor->rgbGreen = g_pChitin->cVideo.m_bIs3dAccelerated
        ? pColor->rgbGreen
        : pColor->rgbGreen * m_nFade / NUM_FADE_FRAMES;

    // NOTE: Same as above.
    pColor->rgbBlue = g_pChitin->cVideo.m_bIs3dAccelerated
        ? pColor->rgbBlue
        : pColor->rgbBlue * m_nFade / NUM_FADE_FRAMES;
}

// 0x795FB0
COLORREF CVidMode::ApplyFadeAmount(COLORREF rgb)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return rgb;
    }

    return RGB(GetRValue(rgb) * m_nFade / NUM_FADE_FRAMES,
        GetGValue(rgb) * m_nFade / NUM_FADE_FRAMES,
        GetBValue(rgb) * m_nFade / NUM_FADE_FRAMES);
}

// 0x796020
INT CVidMode::ApplyFadeAmount(INT nColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return nColor;
    }

    return nColor * m_nFade / NUM_FADE_FRAMES;
}

// #binary-identical
// 0x796050
BOOL CVidMode::DrawEllipse(const CPoint& ptCenter, const CSize& axis, const CRect& rClip, COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return DrawEllipse3d(ptCenter, axis, rClip, rgbColor);
    }

    CRect r;
    r.SetRect(ptCenter.x - axis.cx - 1,
        ptCenter.y - axis.cy - 1,
        ptCenter.x + axis.cx + 1,
        ptCenter.y + axis.cy + 1);

    CRect rClipped;
    if (rClipped.IntersectRect(&r, rClip)) {
        DDSURFACEDESC ddsd;
        ddsd.dwSize = sizeof(ddsd);

        if (!LockSurface(0, &ddsd, rClipped)) {
            return FALSE;
        }

        CRect* pTemp;
        CRect rTemp;
        if (rClip.EqualRect(r)) {
            pTemp = NULL;
        } else {
            // NOTE: Looks like inlined OffsetRect.
            rTemp.left = rClipped.left - r.left;
            rTemp.top = rClipped.top - r.top;
            rTemp.right = rClipped.right - r.left;
            rTemp.bottom = rClipped.bottom - r.top;
            pTemp = &rTemp;
        }

        DrawEllipse(CPoint(axis.cx, axis.cy), axis, ddsd, pTemp, rgbColor);

        // NOTE: Uninline.
        UnLockSurface(0, ddsd.lpSurface);
    }

    return TRUE;
}

// #binary-identical
// 0x7961D0
void CVidMode::DrawEllipse(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        DrawEllipse16(ptCenter, axis, ddsd, rClip, rgbColor);
        break;
    case 24:
        DrawEllipse24(ptCenter, axis, ddsd, rClip, rgbColor);
        break;
    case 32:
        DrawEllipse32(ptCenter, axis, ddsd, rClip, rgbColor);
        break;
    }
}

// 0x796260
void CVidMode::DrawEllipse16(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.
}

// 0x796550
LONG CVidMode::DrawEllipseHOctant16(LONG x, LONG y, INT nArcLength, WORD* pSurface, LONG lPitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, WORD color)
{
    // TODO: Incomplete.

    return 0;
}

// 0x7966B0
LONG CVidMode::DrawEllipseVOctant16(LONG x, LONG y, INT nArcLength, WORD* pSurface, LONG lPitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, WORD color)
{
    // TODO: Incomplete.

    return 0;
}

// #binary-identical
// 0x7967F0
void CVidMode::DrawLightingEffect(const DDSURFACEDESC& ddsd, const CPoint& a3, const CSize& a4, unsigned long a5, unsigned long a6)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return;
    }

    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        DrawLightingEffect16(reinterpret_cast<WORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 1,
            a3,
            a4,
            a5,
            a6);
        break;
    case 24:
        DrawLightingEffect24(reinterpret_cast<BYTE*>(ddsd.lpSurface),
            ddsd.lPitch,
            a3,
            a4,
            a5,
            a6);
        break;
    case 32:
        DrawLightingEffect32(reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 2,
            a3,
            a4,
            a5,
            a6);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
        // __LINE__: 1826
        UTIL_ASSERT(FALSE);
        break;
    }
}

// 0x7968C0
void CVidMode::DrawLightingEffect16(WORD* pSurface, LONG lPitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7)
{
    // TODO: Incomplete.
}

// 0x7977D0
BOOL CVidMode::DrawPoints(CPoint* pPoints, INT nPoints, WORD* pSurface, LONG lPitch, const CRect& rSurface, COLORREF rgbColor, BOOL bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// #binary-identical
// 0x797A30
BOOL CVidMode::DrawLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, UINT nSurface, const CRect& rSurface, COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return DrawLine3d(nXFrom, nYFrom, nXTo, nYTo, rSurface, rgbColor);
    }

    if (!ClipLine(nXFrom, nYFrom, nXTo, nYTo, rSurface)) {
        return FALSE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 2391
    UTIL_ASSERT(nSurface != -1);

    DDSURFACEDESC ddsd;
    ddsd.dwSize = sizeof(ddsd);

    if (!LockSurface(nSurface, &ddsd, rSurface)) {
        return FALSE;
    }

    BOOL rc = DrawLine(nXFrom, nYFrom, nXTo, nYTo, ddsd, rSurface, rgbColor, TRUE);

    // NOTE: Uninline.
    UnLockSurface(nSurface, ddsd.lpSurface);

    return rc;
}

// #binary-identical
// 0x797B80
BOOL CVidMode::DrawLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const DDSURFACEDESC& ddsd, const CRect& rSurface, COLORREF rgbColor, BOOLEAN bClipped)
{
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        return DrawLine16(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<WORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 1,
            rSurface,
            ((GetRValue(rgbColor) >> field_C2) << m_dwRBitShift) | ((GetGValue(rgbColor) >> field_C6) << m_dwGBitShift) | ((GetBValue(rgbColor) >> field_CA) << m_dwBBitShift),
            bClipped);
    case 24:
        return DrawLine24(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<BYTE*>(ddsd.lpSurface),
            ddsd.lPitch,
            rSurface,
            (GetBValue(rgbColor) << m_dwBBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetRValue(rgbColor) << m_dwRBitShift),
            bClipped);
    case 32:
        return DrawLine32(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 2,
            rSurface,
            (GetBValue(rgbColor) << m_dwBBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetRValue(rgbColor) << m_dwRBitShift),
            bClipped);
    default:
        return FALSE;
    }
}

// 0x797D30
BOOL CVidMode::DrawLine16(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, WORD* pSurface, LONG lPitch, const CRect& rSurface, WORD color, BOOLEAN bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7980E0
BOOL CVidMode::DrawRect(const CRect& r, UINT nSurface, const CRect& rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.

    return FALSE;
}

// #binary-identical
// 0x798780
BOOL CVidMode::DrawRecticle(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const CRect& rClip, COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return DrawRecticle3d(rd, rClip, rgbColor);
    }

    CRect r;
    r.SetRect(rd.ptCenter.x - rd.xAxis - rd.piePieceXOffset - 1,
        rd.ptCenter.y - rd.yAxis - rd.piePieceYOffset - 1,
        rd.ptCenter.x + rd.xAxis + rd.piePieceXOffset + 1,
        rd.ptCenter.y + rd.yAxis + rd.piePieceYOffset + 1);

    CRect rClipped;
    if (rClipped.IntersectRect(r, rClip)) {
        DDSURFACEDESC ddsd;
        ddsd.dwSize = sizeof(ddsd);

        if (!LockSurface(0, &ddsd, rClipped)) {
            return FALSE;
        }

        CVIDMODE_RECTICLE_DESCRIPTION copy;
        memcpy(&copy, &rd, sizeof(copy));
        copy.ptCenter.x = rd.xAxis + rd.piePieceXOffset;
        copy.ptCenter.y = rd.yAxis + rd.piePieceYOffset;

        CRect* pTemp;
        CRect rTemp;
        if (rClip.EqualRect(r)) {
            pTemp = NULL;
        } else {
            // NOTE: Looks like inlined OffsetRect.
            rTemp.left = rClipped.left - r.left;
            rTemp.top = rClipped.top - r.top;
            rTemp.right = rClipped.right - r.left;
            rTemp.bottom = rClipped.bottom - r.top;
            pTemp = &rTemp;
        }

        DrawRecticle(copy, ddsd, pTemp, rgbColor);

        // NOTE: Uninline.
        UnLockSurface(0, ddsd.lpSurface);
    }

    return TRUE;
}

// #binary-identical
// 0x798930
void CVidMode::DrawRecticle(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        DrawRecticle16(rd, ddsd, rClip, rgbColor);
        break;
    case 24:
        DrawRecticle24(rd, ddsd, rClip, rgbColor);
        break;
    case 32:
        DrawRecticle32(rd, ddsd, rClip, rgbColor);
        break;
    }
}

// 0x7989B0
void CVidMode::DrawRecticle16(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x798F90
BOOL CVidMode::DrawThickLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, UINT nSurface, CRect& rSurface, int a8, COLORREF rgbColor)
{
    SHORT v1 = (a8 + 1) >> 1;

    CRect rClip;
    rClip.left = rSurface.left + v1;
    rClip.top = rSurface.top + v1;
    rClip.right = rSurface.right - v1;
    rClip.bottom = rSurface.bottom - v1;

    if (!ClipLine(nXFrom, nYFrom, nXTo, nYTo, rClip)) {
        return FALSE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 3191
    UTIL_ASSERT(nSurface != -1);

    DDSURFACEDESC ddsd;
    ddsd.dwSize = sizeof(ddsd);

    if (!LockSurface(nSurface, &ddsd, rSurface)) {
        return FALSE;
    }

    BOOL rc = DrawThickLine(nXFrom, nYFrom, nXTo, nYTo, ddsd, rSurface, a8, rgbColor, TRUE);

    // NOTE: Uninline.
    UnLockSurface(nSurface, ddsd.lpSurface);

    return rc;
}

// #binary-identical
// 0x7990D0
BOOL CVidMode::DrawThickLine(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const DDSURFACEDESC& ddsd, CRect& rSurface, int a8, COLORREF rgbColor, BOOLEAN bClipped)
{
    switch (g_pChitin->cVideo.m_nBpp) {
    case 16:
        return DrawThickLine16(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<WORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 1,
            rSurface,
            a8,
            ((GetRValue(rgbColor) >> field_C2) << m_dwRBitShift) | ((GetGValue(rgbColor) >> field_C6) << m_dwGBitShift) | ((GetBValue(rgbColor) >> field_CA) << m_dwBBitShift),
            bClipped);
    case 24:
        return DrawThickLine24(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<BYTE*>(ddsd.lpSurface),
            ddsd.lPitch,
            rSurface,
            a8,
            (GetBValue(rgbColor) << m_dwBBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetRValue(rgbColor) << m_dwRBitShift),
            bClipped);
    case 32:
        return DrawThickLine32(nXFrom,
            nYFrom,
            nXTo,
            nYTo,
            reinterpret_cast<DWORD*>(ddsd.lpSurface),
            ddsd.lPitch >> 2,
            rSurface,
            a8,
            (GetBValue(rgbColor) << m_dwBBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetRValue(rgbColor) << m_dwRBitShift),
            bClipped);
    default:
        return FALSE;
    }
}

// 0x799280
BOOL CVidMode::DrawThickLine16(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, WORD* pSurface, LONG lPitch, CRect& rSurface, int a8, WORD color, BOOLEAN bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x799540
BOOL CVidMode::OutlinePoly(const CPoint* pPoly, SHORT nVertices, const CRect& rSurface, COLORREF rgbColor, const CPoint& ptOffset)
{
    // TODO: Incomplete.

    return FALSE;
}

// #binary-identical
// 0x7999B0
BOOL CVidMode::EraseScreen(UINT nSurface, COLORREF rgbColor)
{
    if (nSurface >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = pSurfaces[nSurface];
    if (pSurface == NULL) {
        return FALSE;
    }

    DDBLTFX fx;
    fx.dwSize = sizeof(fx);
    fx.dwFillColor = ((GetRValue(rgbColor) >> field_C2) << m_dwRBitShift) | ((GetGValue(rgbColor) >> field_C6) << m_dwGBitShift) | ((GetBValue(rgbColor) >> field_CA) << m_dwBBitShift);

    HRESULT hr;
    do {
        hr = g_pChitin->cVideo.cVidBlitter.Blt(pSurface, NULL, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &fx);
        CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    return TRUE;
}

// 0x799A90
int CVidMode::GetColorDepth()
{
    return m_nColorDepth;
}

// 0x799AA0
LONG CVidMode::GetEllipseArcPixelList(LONG nMajorAxis, LONG nMinorAxis, BYTE* pPixelList)
{
    INT nMajorAxisSqrd = nMajorAxis * nMajorAxis;
    INT nMinorAxisSqrd = nMinorAxis * nMinorAxis;
    INT nMajorAxisAdjust = 0;
    INT nMinorAxisAdjust = nMinorAxis * nMajorAxisSqrd * 2;
    INT nThreshold = nMajorAxisSqrd / 4 - nMinorAxis * nMajorAxisSqrd;
    LONG nArcLength = 0;

    do {
        nThreshold += nMajorAxisAdjust + nMinorAxisSqrd;
        if (nThreshold < 0) {
            pPixelList[nArcLength] = 0;
        } else {
            pPixelList[nArcLength] = 1;
            nMinorAxisAdjust -= 2 * nMajorAxisSqrd;
            nThreshold -= nMinorAxisAdjust;
        }

        nMajorAxisAdjust += 2 * nMinorAxisSqrd;

        nArcLength++;
    } while (nMajorAxisAdjust < nMinorAxisAdjust);

    return nArcLength;
}

// #binary-identical
// 0x799B00
BOOL CVidMode::GetCursorSurfaceSize(CSize& size)
{
    size.cx = 0;
    size.cy = 0;
    return FALSE;
}

// #binary-identical
// 0x799B00
BOOL CVidMode::GetFXSize(CSize& size)
{
    size.cx = 0;
    size.cy = 0;
    return FALSE;
}

// #binary-identical
// 0x799B20
BOOL CVidMode::GetFXSurface(INT& nSurface, DWORD dwFlags)
{
    nSurface = 0;
    return FALSE;
}

// #binary-identical
// 0x799B30
int CVidMode::GetType()
{
    return 255;
}

// #binary-identical
// 0x799B40
BOOL CVidMode::RenderPoly(UINT nSurface, CRect& a3, POINT* apt, int cpt, COLORREF rgbColor)
{
    if (nSurface >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = pSurfaces[nSurface];
    if (pSurface == NULL) {
        return FALSE;
    }

    HRESULT hr;
    HDC hdc;

    do {
        hr = pSurface->GetDC(&hdc);
        CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    if (hr != DD_OK) {
        return FALSE;
    }

    HPEN hPen = CreatePen(PS_SOLID, 1, rgbColor);
    HBRUSH hBrush = CreateSolidBrush(rgbColor);
    HGDIOBJ hPrevPen = SelectObject(hdc, hPen);
    HGDIOBJ hPrevBrush = SelectObject(hdc, hBrush);
    Polygon(hdc, apt, cpt);
    SelectObject(hdc, hPrevPen);
    SelectObject(hdc, hPrevBrush);
    DeleteObject(hPen);
    DeleteObject(hBrush);

    do {
        hr = pSurface->ReleaseDC(hdc);
        CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    return TRUE;
}

// 0x799C60
BOOLEAN CVidMode::PrintSurfaceToBmp(LPBYTE& data, int a3, const CRect& r, LONG& size, short a6)
{
    return FALSE;
}

// 0x799CA0
void CVidMode::DestroySurfaces()
{
}

// 0x799E30
void CVidMode::DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color)
{
}

// 0x799E40
void CVidMode::DoTextOut(UINT nSurface, const CString& sText, int x, int y, COLORREF color, int height)
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

// 0x799F90
CVidCell* CVidMode::GetPointer()
{
    return m_pPointerVidCell;
}

// #binary-identical
// 0x799FA0
BOOL CVidMode::LockSurface(UINT nIndex, LPDDSURFACEDESC pSurfaceDesc, const CRect& rect)
{
    RECT r = static_cast<RECT>(rect);

    if (nIndex >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = pSurfaces[nIndex];
    if (pSurface == NULL) {
        return FALSE;
    }

    HRESULT hr;
    do {
        while (TRUE) {
            pSurfaceDesc->dwSize = sizeof(*pSurfaceDesc);
            hr = pSurface->Lock(&r, pSurfaceDesc, DDLOCK_WAIT, NULL);
            if (hr != DDERR_SURFACELOST) {
                break;
            }
            RestoreSurfaces();
        }

        CheckResults(hr);
    } while (hr == DDERR_SURFACEBUSY);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 5071
    UTIL_ASSERT(g_pChitin->cVideo.GetBitsPerPixels() == 24 || !((LONG)(pSurfaceDesc->lpSurface) & 0x00000001));

    return hr == DD_OK;
}

// 0x79A080
BOOL CVidMode::PolyLine(INT nSurface, CRect& rSurface, LPPOINT lpPoints, int nCount, COLORREF rgbColor, int nThickness)
{
    BOOL bResult;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo.cpp
    // __LINE__: 5104
    UTIL_ASSERT(nSurface != -1 && (nThickness > 0));

    DDSURFACEDESC ddsd;
    if (!LockSurface(nSurface, &ddsd, rSurface)) {
        return FALSE;
    }

    switch (g_pChitin->cVideo.GetBitsPerPixels()) {
    case 16:
        // TODO: Incomplete.
        break;
    case 24:
        // TODO: Incomplete.
        break;
    case 32:
        if (nThickness == 1) {
            while (nCount - 1 > 0) {
                bResult = DrawLine32(lpPoints[0].x,
                    lpPoints[0].y,
                    lpPoints[1].x,
                    lpPoints[1].y,
                    reinterpret_cast<DWORD*>(ddsd.lpSurface),
                    ddsd.lPitch / 4,
                    rSurface,
                    (GetRValue(rgbColor) << m_dwRBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetBValue(rgbColor) << m_dwBBitShift),
                    FALSE);
                lpPoints++;
                nCount--;
            }
        } else {
            while (nCount - 1 > 0) {
                bResult = DrawThickLine32(lpPoints[0].x,
                    lpPoints[0].y,
                    lpPoints[1].x,
                    lpPoints[1].y,
                    reinterpret_cast<DWORD*>(ddsd.lpSurface),
                    ddsd.lPitch / 4,
                    rSurface,
                    nThickness,
                    (GetRValue(rgbColor) << m_dwRBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetBValue(rgbColor) << m_dwBBitShift),
                    FALSE);
                lpPoints++;
                nCount--;
            }
        }
        break;
    }

    // NOTE: Uninline.
    UnLockSurface(nSurface, ddsd.lpSurface);

    return bResult;
}

// #binary-identical
// 0x79A670
BOOL CVidMode::SetPointer(CVidCell* pVidCell, BOOLEAN bAnimating, INT nPointerNumber)
{
    CSingleLock lock(&m_csRenderPointer, FALSE);
    lock.Lock(INFINITE);

    m_nPointerNumber = nPointerNumber;
    m_pPointerVidCell = pVidCell;
    m_bPointerAnimating = bAnimating;

    lock.Unlock();

    return TRUE;
}

// 0x79A700
BOOL CVidMode::SetPointer(CVidCell* pVidCell, CResRef cResRef, BOOLEAN bAnimating, INT nPointerNumber)
{
    CSingleLock lock(&m_csRenderPointer, FALSE);
    lock.Lock(INFINITE);

    // NOTE: Uninline.
    pVidCell->SetResRef(cResRef, FALSE, TRUE, TRUE);

    if (pVidCell->pRes == NULL) {
        lock.Unlock();
        return NULL;
    }

    m_bPointerAnimating = bAnimating;
    m_nPointerNumber = m_nPointerNumber;
    m_pPointerVidCell = pVidCell;

    lock.Unlock();

    return TRUE;
}

// #binary-identical
// 0x79A820
BOOL CVidMode::UnLockSurface(UINT nIndex, LPVOID lpSurfaceData)
{
    if (nIndex >= m_nSurfaces) {
        return FALSE;
    }

    IDirectDrawSurface* pSurface = pSurfaces[nIndex];
    if (pSurface == NULL) {
        return FALSE;
    }

    return pSurface->Unlock(lpSurfaceData) == DD_OK;
}

// #binary-identical
// 0x79AB50
DWORD CVidMode::ReduceColor(COLORREF rgbColor)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        return rgbColor | 0xFF000000;
    }

    if (g_pChitin->cVideo.m_nBpp == 16) {
        return ((GetRValue(rgbColor) >> field_C2) << m_dwRBitShift) | ((GetGValue(rgbColor) >> field_C6) << m_dwGBitShift) | ((GetBValue(rgbColor) >> field_CA) << m_dwBBitShift);
    } else {
        return (GetBValue(rgbColor) << m_dwBBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetRValue(rgbColor) << m_dwRBitShift);
    }
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

    if (windowRect.left < workRect.left) {
        windowRect.left = workRect.left;
    }

    if (windowRect.top < workRect.top) {
        windowRect.top = workRect.top;
    }

    SetWindowPos(hWnd,
        HWND_TOP,
        windowRect.left,
        windowRect.top,
        0,
        0,
        SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

// 0x7BC100
BOOL CVidMode::ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen)
{
    return TRUE;
}

// 0x7BC100
BOOL CVidMode::ActivateVideoMode3d(CVidMode* pPrevVidMode, HWND hWnd, BOOLEAN bFullscreen)
{
    return TRUE;
}

// 0x7BC200
int CVidMode::GetTextureId()
{
    // TODO: Incomplete.

    return 0;
}

// 0x7BC250
BOOL CVidMode::DrawLine3d(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, const CRect& rSurface, COLORREF rgbColor)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7BC580
BOOL CVidMode::DrawEllipse3d(const CPoint& ptCenter, const CSize& axis, const CRect& rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7BC7A0
BOOL CVidMode::DrawRecticle3d(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const CRect& rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7BEA80
void CVidMode::CheckResults3d(int a1)
{
    // TODO: Incomplete.
}

// 0x7BC110
void CVidMode::Set3dClipRect(const CRect& rClip)
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        // TODO: Replace with function pointers.
        glScissor(rClip.left,
            CVideo::SCREENHEIGHT - rClip.bottom,
            rClip.Width(),
            rClip.Height());
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }
}

// 0x7BC180
void CVidMode::EnableScissoring()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        // TODO: Replace with function pointers.
        glEnable(GL_SCISSOR_TEST);
        CheckResults3d(0);
    }
}

// 0x7BC1C0
void CVidMode::DisableScissoring()
{
    if (g_pChitin->cVideo.m_bIs3dAccelerated) {
        // TODO: Replace with function pointers.
        glDisable(GL_SCISSOR_TEST);
        CheckResults3d(0);
    }
}

// 0x7BD270
void CVidMode::RenderTint3d(COLORREF rgbTint, const CRect& rClip)
{
    // TODO: Incomplete.
}

// 0x7C8B40
LONG CVidMode::DrawEllipse24(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.

    return 0;
}

// 0x7C8E10
LONG CVidMode::DrawEllipseVOctant24(LONG x, LONG y, INT nArcLength, BYTE* pSurface, LONG lPitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color)
{
    // TODO: Incomplete.

    return 0;
}

// 0x7C8F70
void CVidMode::DrawLightingEffect24(BYTE* pSurface, LONG lPitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7)
{
    // TODO: Incomplete.
}

// 0x7C9990
LONG CVidMode::DrawEllipseHOctant24(LONG x, LONG y, INT nArcLength, BYTE* pSurface, LONG lPitch, BOOLEAN clockwise, unsigned char* pArcData, const CRect* rClip, DWORD color)
{
    // TODO: Incomplete.

    return 0;
}

// 0x7C9B10
void CVidMode::DrawRecticle24(const CVIDMODE_RECTICLE_DESCRIPTION& rd, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    // TODO: Incomplete.
}

// 0x7CA0D0
BOOL CVidMode::DrawLine24(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, BYTE* pSurface, LONG lPitch, const CRect& rSurface, DWORD color, BOOLEAN bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7CA330
BOOL CVidMode::DrawThickLine24(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, BYTE* pSurface, LONG lPitch, CRect& rSurface, int a8, DWORD color, BOOLEAN bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7CA840
LONG CVidMode::DrawEllipse32(const CPoint& ptCenter, const CSize& axis, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    BYTE* pPixelList = new BYTE[max(axis.cx, axis.cy)];
    LONG lPitch = ddsd.lPitch / 4;
    DWORD color = (GetRValue(rgbColor) << m_dwRBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetBValue(rgbColor) << m_dwBBitShift);
    LONG nArcLength = GetEllipseArcPixelList(axis.cx, axis.cy, pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo24.cpp
    // __LINE__: 1474
    UTIL_ASSERT(nArcLength <= max(axis.cx, axis.cy));

    DrawEllipseHOctant32(ptCenter.x,
        ptCenter.y - axis.cy,
        nArcLength,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawEllipseHOctant32(ptCenter.x + 1,
        ptCenter.y + pPixelList[0] - axis.cy,
        nArcLength - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    DrawEllipseHOctant32(ptCenter.x,
        ptCenter.y + axis.cy,
        nArcLength,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawEllipseHOctant32(ptCenter.x + 1,
        ptCenter.y - pPixelList[0] + axis.cy,
        nArcLength - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    nArcLength = GetEllipseArcPixelList(axis.cy, axis.cx, pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo24.cpp
    // __LINE__: 1497
    UTIL_ASSERT(nArcLength < max(axis.cx, axis.cy));

    DrawEllipseVOctant32(ptCenter.x - axis.cx,
        ptCenter.y,
        nArcLength,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        TRUE,
        pPixelList,
        rClip,
        color);

    DrawEllipseVOctant32(ptCenter.x + pPixelList[0] - axis.cx,
        ptCenter.y + 1,
        nArcLength - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    DrawEllipseVOctant32(ptCenter.x + axis.cx,
        ptCenter.y,
        nArcLength,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawEllipseVOctant32(ptCenter.x - pPixelList[0] + axis.cx,
        ptCenter.y + 1,
        nArcLength - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        FALSE,
        pPixelList + 1,
        rClip,
        color);

    delete pPixelList;

    return 0;
}

// 0x7CAB20
LONG CVidMode::DrawEllipseVOctant32(LONG x, LONG y, INT nArcLength, DWORD* pSurface, LONG lPitch, BOOLEAN clockwise, BYTE* pPixelList, const CRect* rClip, DWORD color)
{
    INT nStep;

    if (rClip != NULL) {
        if (lPitch < 0) {
            pSurface += -lPitch * (y - rClip->top) - rClip->left + x;
            nStep = -1;
        } else {
            pSurface += lPitch * (y - rClip->top) - rClip->left + x;
            nStep = 1;
        }

        while (nArcLength != 0) {
            if (rClip->PtInRect({ x, y })) {
                *pSurface = color;
            }

            if (*pPixelList++ != 0) {
                if (clockwise) {
                    pSurface++;
                    x++;
                } else {
                    pSurface--;
                    x--;
                }
            }

            pSurface += lPitch;
            y += nStep;

            nArcLength--;
        }
    } else {
        if (lPitch < 0) {
            pSurface += -lPitch * y + x;
        } else {
            pSurface += lPitch * y + x;
        }

        while (nArcLength != 0) {
            *pSurface = color;

            if (*pPixelList++ != 0) {
                if (clockwise) {
                    pSurface++;
                    x++;
                } else {
                    pSurface--;
                    x--;
                }
            }

            pSurface += lPitch;
            nArcLength--;
        }
    }

    return x;
}

// 0x7CAC60
void CVidMode::DrawLightingEffect32(DWORD* pSurface, LONG lPitch, const CPoint& a4, const CSize& a5, unsigned long a6, unsigned long a7)
{
    // TODO: Incomplete.
}

// 0x7CB510
LONG CVidMode::DrawEllipseHOctant32(LONG x, LONG y, INT nArcLength, DWORD* pSurface, LONG lPitch, BOOLEAN clockwise, BYTE* pPixelList, const CRect* rClip, DWORD color)
{
    INT nStep;

    if (rClip != NULL) {
        if (lPitch < 0) {
            pSurface += -lPitch * (y - rClip->top) - rClip->left + x;
            nStep = -1;
        } else {
            pSurface += lPitch * (y - rClip->top) - rClip->left + x;
            nStep = 1;
        }

        while (nArcLength != 0) {
            if (rClip->PtInRect({ x, y })) {
                *pSurface = color;
            }

            if (*pPixelList++ != 0) {
                pSurface += lPitch;
                y += nStep;
            }

            if (clockwise) {
                pSurface++;
                x++;
            } else {
                pSurface--;
                x--;
            }

            nArcLength--;
        }
    } else {
        if (lPitch < 0) {
            pSurface += -lPitch * y + x;
            nStep = -1;
        } else {
            pSurface += lPitch * y + x;
            nStep = 1;
        }

        while (nArcLength != 0) {
            *pSurface = color;

            if (*pPixelList++ != 0) {
                pSurface += lPitch;
                y += nStep;
            }

            if (clockwise) {
                pSurface++;
            } else {
                pSurface--;
            }

            nArcLength--;
        }
    }

    return y;
}

// 0x7CB670
void CVidMode::DrawRecticle32(const CVIDMODE_RECTICLE_DESCRIPTION& recticleDesc, const DDSURFACEDESC& ddsd, const CRect* rClip, COLORREF rgbColor)
{
    BYTE* pPixelList = new BYTE[max(recticleDesc.xAxis, recticleDesc.yAxis)];
    LONG lPitch = ddsd.lPitch / 4;
    DWORD color = (GetRValue(rgbColor) << m_dwRBitShift) | (GetGValue(rgbColor) << m_dwGBitShift) | (GetBValue(rgbColor) << m_dwBBitShift);

    INT v1 = recticleDesc.xAxis + recticleDesc.piePieceXOffset;
    INT v2 = recticleDesc.yAxis + recticleDesc.piePieceYOffset;
    INT v3;

    CRect rLineClip;
    BOOLEAN bLineClipped;

    if (rClip != NULL) {
        rLineClip.SetRect(rClip->left, rClip->top, rClip->right - 1, rClip->bottom - 1);
        bLineClipped = TRUE;
    } else {
        rLineClip.SetRect(0, 0, 0, 0);
        bLineClipped = FALSE;
    }

    LONG nArcLength = GetEllipseArcPixelList(recticleDesc.xAxis,
        recticleDesc.yAxis,
        pPixelList);

    nArcLength -= 1;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo24.cpp
    // __LINE__: 2097
    UTIL_ASSERT(nArcLength < max(recticleDesc.xAxis, recticleDesc.yAxis));

    v3 = DrawEllipseHOctant32(recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - v2,
        nArcLength - recticleDesc.xGap,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawLine32(recticleDesc.ptCenter.x + recticleDesc.xGap - nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + recticleDesc.piePiecePtYOffset - v2,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseHOctant32(recticleDesc.ptCenter.x + 1,
        recticleDesc.ptCenter.y + pPixelList[0] - v2,
        nArcLength - recticleDesc.xGap - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    DrawLine32(recticleDesc.ptCenter.x - recticleDesc.xGap + nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + recticleDesc.piePiecePtYOffset - v2,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseHOctant32(recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y + v2,
        nArcLength - recticleDesc.xGap,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawLine32(recticleDesc.ptCenter.x + recticleDesc.xGap - nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - recticleDesc.piePiecePtYOffset + v2,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseHOctant32(recticleDesc.ptCenter.x + 1,
        recticleDesc.ptCenter.y - pPixelList[0] + v2,
        nArcLength - recticleDesc.xGap - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    DrawLine32(recticleDesc.ptCenter.x - recticleDesc.xGap + nArcLength,
        v3,
        recticleDesc.ptCenter.x,
        recticleDesc.ptCenter.y - recticleDesc.piePiecePtYOffset + v2,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    nArcLength = GetEllipseArcPixelList(recticleDesc.yAxis,
        recticleDesc.xAxis,
        pPixelList);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVideo24.cpp
    // __LINE__: 2097
    UTIL_ASSERT(nArcLength < max(recticleDesc.xAxis, recticleDesc.yAxis));

    v3 = DrawEllipseVOctant32(recticleDesc.ptCenter.x - v1,
        recticleDesc.ptCenter.y,
        nArcLength - recticleDesc.yGap,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        TRUE,
        pPixelList,
        rClip,
        color);

    DrawLine32(v3,
        recticleDesc.ptCenter.y + recticleDesc.yGap - nArcLength,
        recticleDesc.ptCenter.x + recticleDesc.piePiecePtXOffset - v1,
        recticleDesc.ptCenter.y,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseVOctant32(recticleDesc.ptCenter.x + pPixelList[0] - v1,
        recticleDesc.ptCenter.y + 1,
        nArcLength - recticleDesc.yGap - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        TRUE,
        pPixelList + 1,
        rClip,
        color);

    DrawLine32(v3,
        recticleDesc.ptCenter.y - recticleDesc.yGap + nArcLength,
        recticleDesc.ptCenter.x + recticleDesc.piePiecePtXOffset - v1,
        recticleDesc.ptCenter.y,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseVOctant32(recticleDesc.ptCenter.x + v1,
        recticleDesc.ptCenter.y,
        nArcLength - recticleDesc.yGap,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        -lPitch,
        FALSE,
        pPixelList,
        rClip,
        color);

    DrawLine32(v3,
        recticleDesc.ptCenter.y + recticleDesc.yGap - nArcLength,
        recticleDesc.ptCenter.x - recticleDesc.piePiecePtXOffset + v1,
        recticleDesc.ptCenter.y,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    v3 = DrawEllipseVOctant32(recticleDesc.ptCenter.x - pPixelList[0] + v1,
        recticleDesc.ptCenter.y + 1,
        nArcLength - recticleDesc.yGap - 1,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        FALSE,
        pPixelList + 1,
        rClip,
        color);

    DrawLine32(v3,
        recticleDesc.ptCenter.y - recticleDesc.yGap + nArcLength,
        recticleDesc.ptCenter.x - recticleDesc.piePiecePtXOffset + v1,
        recticleDesc.ptCenter.y,
        reinterpret_cast<DWORD*>(ddsd.lpSurface),
        lPitch,
        rLineClip,
        color,
        bLineClipped);

    delete pPixelList;
}

// 0x7CBC40
BOOL CVidMode::DrawLine32(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, DWORD* pSurface, LONG lPitch, const CRect& rSurface, DWORD color, BOOLEAN bClipped)
{
    INT nDeltaX;
    INT nDeltaY;
    INT nStep;

    if (!bClipped) {
        if (!ClipLine(nXFrom, nYFrom, nXTo, nYTo, rSurface)) {
            return FALSE;
        }
    }

    if (nYFrom > nYTo) {
        INT t;

        t = nXTo;
        nXTo = nXFrom;
        nXFrom = t;

        t = nYTo;
        nYTo = nYFrom;
        nYFrom = t;
    }

    if (nXTo - nXFrom < 0) {
        nDeltaX = nXFrom - nXTo;
        nStep = -1;
    } else {
        nDeltaX = nXTo - nXFrom;
        nStep = 1;
    }

    nDeltaY = nYTo - nYFrom;

    pSurface += lPitch * (nYFrom - rSurface.top) - rSurface.left + nXFrom;

    if (nDeltaX == 0) {
        while (nDeltaY >= 0) {
            *pSurface = color;
            pSurface += lPitch;
            nDeltaY--;
        }
        return TRUE;
    }

    if (nDeltaY == 0) {
        while (nDeltaX >= 0) {
            *pSurface = color;
            pSurface += nStep;
            nDeltaX--;
        }
        return TRUE;
    }

    if (nDeltaX == nDeltaY) {
        while (nDeltaX >= 0) {
            *pSurface = color;
            pSurface += lPitch + nStep;
            nDeltaX--;
        }
        return TRUE;
    }

    if (nDeltaX < nDeltaY) {
        ScanLine32(pSurface, nDeltaY, nDeltaX, lPitch, nStep, color);
    } else {
        ScanLine32(pSurface, nDeltaX, nDeltaY, nStep, lPitch, color);
    }

    return TRUE;
}

// 0x7CBD80
void CVidMode::ScanLine32(DWORD* pSurface, UINT nMajorAxis, UINT nMinorAxis, INT nMajorAxisAdjust, INT nMinorAxisAdjust, DWORD color)
{
    int v1 = nMajorAxis / nMinorAxis;
    int v2 = 2 * nMinorAxis;
    int v3 = 2 * (nMajorAxis % nMinorAxis);
    int v4 = v3 / 2 - v2;
    int v5 = v1 / 2 + 1;
    int v6 = nMinorAxis - 1;
    int v7 = v1 / 2 + 1;

    if (v3 != 0) {
        if ((v1 & 1) != 0) {
            v4 += nMinorAxis;
        }
    } else {
        if ((v1 & 1) != 0) {
            v4 += nMinorAxis;
        } else {
            v5 -= 1;
        }
    }

    while (v5 > 0) {
        *pSurface = color;
        pSurface += nMajorAxisAdjust;
        v5--;
    }

    pSurface += nMinorAxisAdjust;
    while (v6 > 0) {
        v4 += v3;

        int v8 = v1;
        if (v4 > 0) {
            v8 += 1;
            v4 -= v2;
        }

        while (v8 > 0) {
            *pSurface = color;
            pSurface += nMajorAxisAdjust;
            v8--;
        }

        pSurface += nMinorAxisAdjust;

        v6--;
    }

    while (v7 > 0) {
        *pSurface = color;
        pSurface += nMajorAxisAdjust;
        v7--;
    }
}

// 0x7CBE70
BOOL CVidMode::DrawThickLine32(INT nXFrom, INT nYFrom, INT nXTo, INT nYTo, DWORD* pSurface, LONG lPitch, CRect& rSurface, int a8, DWORD color, BOOLEAN bClipped)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x799E20
BOOL CVidMode::CreateSurfaces(BOOLEAN bFullscreen)
{
    return FALSE;
}

// 0x799C90
BOOL CVidMode::DeactivateVideoMode(CVidMode* pNextVidMode)
{
    return TRUE;
}

// 0x799E20
IDirectDrawSurface* CVidMode::GetFXSurfacePtr(DWORD dwFlags)
{
    return NULL;
}

// 0x7ABB90
RGBQUAD* CVidMode::GetPalette()
{
    return NULL;
}

// 0x78E6E0
int CVidMode::GetNumVRamSurfaces()
{
    return 0;
}

// 0x7B5450
void CVidMode::RenderFlash(UINT nSurface, COLORREF rgbColor, unsigned char a4, const CRect& a5)
{
}

// 0x799C90
BOOL CVidMode::RenderPointer(UINT nSurface)
{
    return TRUE;
}

// 0x799C90
BOOL CVidMode::Flip(BOOL bRenderCursor)
{
    return TRUE;
}

// 0x799E60
void CVidMode::ParsePixelFormat(const DDPIXELFORMAT& ddpf)
{
}

// 0x78E6E0
BOOL CVidMode::CreateSurfaces3d()
{
    return FALSE;
}

// 0x78E6E0
BOOL CVidMode::DestroySurfaces3d(CVidMode* pNextVidMode)
{
    return FALSE;
}

// 0x7BEDE0
void CVidMode::sub_7BEDE0()
{
    CSingleLock lock(&field_4A, FALSE);
    lock.Lock(INFINITE);

    while (!field_6A.IsEmpty()) {
        GLuint texture = static_cast<GLuint>(field_6A.RemoveHead());
        glDeleteTextures(1, &texture);
        CheckResults3d(0);
    }

    lock.Unlock();
}

// 0x5CEDE0
void CVidMode::RenderBlackFade3d()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
BOOL CVidMode::GetFullyFaded()
{
    return m_nFade == 0;
}

// NOTE: Inlined.
void CVidMode::UpdateFade()
{
    if (m_bFadeTo) {
        if (m_nFade > 0) {
            m_nFade--;
        }
    } else {
        if (m_nFade < NUM_FADE_FRAMES) {
            m_nFade++;
        }
    }
}

// FIXME: `rgbFade` is misleading (both type and meaning). This function is
// usually called via inlined non-static `CInfinity::SetFade`, but I'm not sure
// how `CInfinity` instance is obtained in the first place.
//
// NOTE: Inlined.
void CVidMode::SetFade(BOOL bFadeTo, COLORREF rgbFade)
{
    if (rgbFade != 0) {
        NUM_FADE_FRAMES = static_cast<BYTE>(rgbFade);
    }

    m_bFadeTo = bFadeTo;

    if (m_bFadeTo) {
        m_nFade = NUM_FADE_FRAMES;
    } else {
        m_nFade = 0;
    }
}

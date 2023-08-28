#include "CVidFont.h"

#include "CUtil.h"
#include "CVidInf.h"

// 0x8FB980
CTypedPtrList<CPtrList, CVidFontRegistryEntry*> CVidFont::REGISTRY;

// 0x8FB9A0
CCriticalSection CVidFont::REGISTRY_CRITICAL_SECTION;

// 0x792CA0
CVidFont::CVidFont()
{
    field_4E2 = 0;
    field_4F4 = 0;
    m_rgbPaletteForegroundColor = 0;
    m_rgbPaletteBackgroundColor = 0;
    m_bFontSet = FALSE;
    m_hFont = NULL;
    field_4E6 = -1;
    m_nBaseLineHeight = -1;
    m_nFontHeight = -1;
    m_rgbForegroundColor = RGB(255, 255, 255);
    m_rgbBackgroundColor = RGB(255, 255, 255);
}

// 0x792D10
CVidFont::~CVidFont()
{
    if (m_hFont != NULL) {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
}

// 0x792D40
LONG CVidFont::GetStringLength(const CString& sString, BOOLEAN bDemanded)
{
    if (g_pChitin->m_sFontName.Compare("") != 0) {
        return GetStringLengthEx(CVIDINF_SURFACE_BACK, sString, bDemanded);
    }

    LONG nStringLength = 0;

    if (pRes == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
        // __LINE__: 168
        UTIL_ASSERT(FALSE);
    }

    int length = sString.GetLength();
    for (int index = 0; index < length; index++) {
        char ch = sString.GetAt(index);
        SHORT nSequence = ch < 0 ? ch + 256 : ch;
        SequenceSet(nSequence - 1);

        if (g_pChitin->field_1A0 & IsDBCSLeadByte(sString.GetAt(index))) {
            index++;
            FrameSet(sString.GetAt(index) - 1);
        } else {
            FrameSet(0);
        }

        CSize size;
        GetCurrentFrameSize(size, bDemanded);

        nStringLength += size.cx;
    }

    return nStringLength;
}

// 0x792E60
LONG CVidFont::GetStringLengthEx(INT nSurface, const CString& sString, BOOLEAN bDemanded)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
    // __LINE__: 227
    UTIL_ASSERT(!g_pChitin->cVideo.Is3dAccelerated());

    if (pRes == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
        // __LINE__: 242
        UTIL_ASSERT(FALSE);
    }

    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();
    if (pVidMode == NULL) {
        return -1;
    }

    HRESULT hr;
    HDC hDC;
    LPDIRECTDRAWSURFACE pSurface = pVidMode->pSurfaces[nSurface];
    do {
        hr = pSurface->GetDC(&hDC);
        pVidMode->CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    if (hr != DD_OK) {
        return 0;
    }

    if (!m_bFontSet) {
        SetTextFontEx(nSurface, hDC);
    }

    SIZE size;
    HGDIOBJ hPrev = SelectObject(hDC, m_hFont);
    GetTextExtentPoint32A(hDC, sString, sString.GetLength(), &size);
    SelectObject(hDC, hPrev);

    do {
        hr = pSurface->ReleaseDC(hDC);
        pVidMode->CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    return size.cx;
}

// 0x792FB0
SHORT CVidFont::GetBaseLineHeight(BOOLEAN bDemanded)
{
    if (g_pChitin->m_sFontName.Compare("") != 0) {
        if (!m_bFontSet) {
            SetTextFontEx(CVIDINF_SURFACE_BACK, NULL);
        }

        if (m_nBaseLineHeight != -1) {
            return m_nBaseLineHeight;
        }
    }

    if (pRes == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
        // __LINE__: 333
        UTIL_ASSERT(FALSE);
    }

    CSize size;
    GetFrameSize(0, 0, size, bDemanded);

    // TODO: Check.
    return static_cast<SHORT>(size.cy);
}

// 0x793050
SHORT CVidFont::GetFontHeight(BOOLEAN bDemanded)
{
    if (g_pChitin->m_sFontName.Compare("") != 0) {
        if (!m_bFontSet) {
            SetTextFontEx(CVIDINF_SURFACE_BACK, NULL);
        }

        if (m_nFontHeight != -1) {
            return m_nFontHeight;
        }
    }

    if (pRes == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
        // __LINE__: 379
        UTIL_ASSERT(FALSE);
    }

    CSize size;
    GetFrameSize(1, 0, size, bDemanded);

    // TODO: Check.
    return static_cast<SHORT>(size.cy);
}

// 0x7930F0
void CVidFont::SetColor(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor, BOOL bForce)
{
    BOOL bChanged = FALSE;

    if (m_rgbForegroundColor != rgbForegroundColor) {
        m_rgbForegroundColor = rgbForegroundColor;
        bChanged = TRUE;
    }

    if (m_rgbBackgroundColor != rgbBackgroundColor) {
        m_rgbBackgroundColor = rgbBackgroundColor;
        bChanged = TRUE;
    }

    if (!g_pChitin->cVideo.m_bIs3dAccelerated || bForce) {
        if (bChanged) {
            RealizePalette(m_rgbForegroundColor, m_rgbBackgroundColor);
        }
    } else {
        m_bPaletteChanged = TRUE;
    }
}

// 0x793170
void CVidFont::SetResRef(const CResRef& cNewResRef, BOOL bDoubleSize, BOOL bSetAutoRequest)
{
    // NOTE: Uninline.
    CVidCell::SetResRef(cNewResRef, bDoubleSize, bSetAutoRequest, TRUE);

    m_rgbForegroundColor = RGB(255, 255, 255);
    m_rgbBackgroundColor = RGB(255, 255, 255);
    m_nBaseLineHeight = -1;
    m_nFontHeight = -1;
    m_bFontSet = FALSE;
}

// 0x793390
BOOL CVidFont::SetTextFontEx(INT nSurface, HDC hDC)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
    // __LINE__: 489
    UTIL_ASSERT(!g_pChitin->cVideo.Is3dAccelerated());

    LONG nHeight;
    if (field_4E6 == -1) {
        CSize size;
        GetFrameSize(0, 0, size, FALSE);
        nHeight = size.cy;
    } else {
        nHeight = -1;
    }

    nHeight = -nHeight;

    if (m_hFont != NULL) {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }

    m_hFont = CreateFontA(nHeight,
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
        FF_DONTCARE,
        g_pChitin->GetFontName());
    m_bFontSet = TRUE;

    LPDIRECTDRAWSURFACE pSurface = NULL;

    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();
    if (pVidMode == NULL) {
        return TRUE;
    }

    HRESULT hr;

    if (hDC == NULL) {
        pSurface = pVidMode->pSurfaces[nSurface];

        do {
            hr = pSurface->GetDC(&hDC);
            pVidMode->CheckResults(hr);
        } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

        if (hr != DD_OK) {
            return TRUE;
        }
    }

    TEXTMETRICA tm;
    HGDIOBJ hPrev = SelectObject(hDC, m_hFont);
    GetTextMetricsA(hDC, &tm);
    SelectObject(hDC, hPrev);

    if (pSurface != NULL) {
        do {
            hr = pVidMode->pSurfaces[nSurface]->ReleaseDC(hDC);
            pVidMode->CheckResults(hr);
        } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);
    }

    // TODO: Check cast.
    m_nFontHeight = static_cast<SHORT>(tm.tmHeight);
    m_nBaseLineHeight = static_cast<SHORT>(tm.tmHeight - tm.tmDescent);

    return TRUE;
}

// 0x793570
void CVidFont::RealizePalette(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor)
{
    if (g_pChitin->m_sFontName.Compare("") == 0) {
        int v1 = 100 * (GetRValue(rgbForegroundColor) - GetRValue(rgbBackgroundColor)) / 256;
        int v2 = 100 * (GetGValue(rgbForegroundColor) - GetGValue(rgbBackgroundColor)) / 256;
        int v3 = 100 * (GetBValue(rgbForegroundColor) - GetBValue(rgbBackgroundColor)) / 256;
        int v4 = v1 + 100 * GetRValue(rgbBackgroundColor);
        int v5 = v2 + 100 * GetGValue(rgbBackgroundColor);
        int v6 = v3 + 100 * GetBValue(rgbBackgroundColor);

        for (int index = 1; index < 256; index++) {
            m_palette[index].rgbRed = v4 / 100;
            m_palette[index].rgbGreen = v5 / 100;
            m_palette[index].rgbBlue = v6 / 100;

            v4 += v1;
            v5 += v2;
            v6 += v3;
        }

        m_palette[0].rgbRed = 0;
        m_palette[0].rgbGreen = -1;
        m_palette[0].rgbBlue = 0;

        SetPalette(m_palette, 256, CVidPalette::TYPE_RESOURCE);
        m_rgbPaletteForegroundColor = rgbForegroundColor;
        m_rgbPaletteBackgroundColor = rgbBackgroundColor;
    }
}

// 0x793720
BOOL CVidFont::TextOut(const CString& sString, int x, int y, const CRect& rClip, INT nSurface)
{
    int length = sString.GetLength();
    for (int index = 0; index < length; index++) {
        SequenceSet(sString.GetAt(index) - 1);

        char ch = sString.GetAt(index);
        SHORT nSequence = ch < 0 ? ch + 256 : ch;
        SequenceSet(nSequence - 1);

        if (g_pChitin->field_1A0 && IsDBCSLeadByte(sString.GetAt(index))) {
            FrameSet(sString.GetAt(index) - 1);
        } else {
            FrameSet(0);
        }

        CSize size;
        GetCurrentFrameSize(size, FALSE);

        CPoint ptCenter;
        GetCurrentCenterPoint(ptCenter, FALSE);

        Render(nSurface,
            x + ptCenter.x,
            y,
            rClip,
            NULL,
            0,
            0,
            -1);

        x += size.cx;
    }

    return TRUE;
}

// 0x793820
BOOL CVidFont::TextOut(const CString& sString, WORD* pSurface, LONG lPitch, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (pSurface == NULL) {
        return FALSE;
    }

    if (!bDemanded) {
        if (pRes->Demand() == NULL) {
            return FALSE;
        }
    }

    g_pChitin->FontRectOutline();

    if (!m_bPaletteChanged) {
        m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    }

    if (dwFlags != 0) {
        m_cPalette.Realize(CVidImage::rgbTempPal,
            g_pChitin->cVideo.m_nBpp,
            dwFlags,
            &m_paletteAffects,
            255);
    } else {
        m_cPalette.Realize(CVidImage::rgbTempPal,
            g_pChitin->cVideo.m_nBpp,
            0,
            NULL,
            255);
    }

    int length = sString.GetLength();
    for (int index = 0; index < length; index++) {
        SequenceSet(sString.GetAt(index) - 1);

        char ch = sString.GetAt(index);
        SHORT nSequence = ch < 0 ? ch + 256 : ch;
        SequenceSet(nSequence - 1);

        if (g_pChitin->field_1A0 && IsDBCSLeadByte(sString.GetAt(index))) {
            index++;
            FrameSet(sString.GetAt(index) - 1);
        } else {
            FrameSet(0);
        }

        CSize size;
        GetCurrentFrameSize(size, TRUE);

        CPoint ptCenter;
        GetCurrentCenterPoint(ptCenter, TRUE);

        CRect rChar(x, y - ptCenter.y, x + size.cx, y + size.cy - ptCenter.y);

        CRect rClampedChar;
        if (rClampedChar.IntersectRect(rChar, rClip)) {
            Render(pSurface,
                lPitch,
                x + ptCenter.x,
                max(ptCenter.y, y),
                rClip,
                TRUE,
                dwFlags,
                CPoint(0, max(ptCenter.y - y, 0)));
        }

        x += size.cx;
    }

    if (!bDemanded) {
        pRes->Release();
    }

    return TRUE;
}

// 0x793A70
BOOL CVidFont::TextOutEx(INT nSurface, const CString& sString, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A0490
BOOL CVidFont::Load(BOOL bDemanded)
{
    CSingleLock renderLock(&REGISTRY_CRITICAL_SECTION, FALSE);

    if (!g_pChitin->cVideo.m_bIs3dAccelerated) {
        return TRUE;
    }

    if (g_pChitin->field_1A0) {
        return TRUE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
    // __LINE__: 75
    UTIL_ASSERT(renderLock.Lock(INFINITE) != 0);

    int rc = RegisterFont();
    if (rc == 2) {
        renderLock.Unlock();
        return FALSE;
    }

    if (rc != 3 && LoadToTexture(bDemanded) == 2) {
        Unload();
        renderLock.Unlock();
        return FALSE;
    }

    renderLock.Unlock();
    return TRUE;
}

// 0x7A05A0
int CVidFont::RegisterFont()
{
    // TODO: Incomplete.

    return 0;
}

// 0x7A0880
void CVidFont::Unload()
{
    // TODO: Incomplete.
}

// 0x7A0A40
void CVidFont::UnloadAllFonts()
{
    // TODO: Incomplete.
}

// 0x7A0B20
INT CVidFont::LoadToTexture(BOOL bDemanded)
{
    // TODO: Incomplete.

    return 2;
}

// 0x7A1090
BOOL CVidFont::TextOut3d(const CString& sText, WORD* pSurface, LONG lPitch, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A1210
BOOL CVidFont::TextOut3d(const CString& sText, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    // TODO: Incomplete.

    return FALSE;
}

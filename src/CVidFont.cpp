#include "CVidFont.h"

#include "CUtil.h"
#include "CVidInf.h"
#include "CVideo3d.h"

// 0x8FB974
BOOLEAN CVidFont::byte_8FB974[12];

// 0x8FB980
CTypedPtrList<CPtrList, CVidFontRegistryEntry*> CVidFont::REGISTRY;

// 0x8FB9A0
CCriticalSection CVidFont::REGISTRY_CRITICAL_SECTION;

// 0x792CA0
CVidFont::CVidFont()
{
    field_4E2 = 0;
    m_posRegistryList = NULL;
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
    HDC hDC;
    HRESULT hr;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont.cpp
    // __LINE__: 808
    UTIL_ASSERT(!g_pChitin->cVideo.Is3dAccelerated());

    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();
    if (pVidMode == NULL) {
        return -1;
    }

    do {
        hr = pVidMode->pSurfaces[nSurface]->GetDC(&hDC);
        pVidMode->CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

    if (hr != DD_OK) {
        return FALSE;
    }

    if (!m_bFontSet) {
        SetTextFontEx(nSurface, NULL);
    }

    HGDIOBJ hPrev = SelectObject(hDC, m_hFont);
    SetBkMode(hDC, TRANSPARENT);

    COLORREF rgbColor = m_rgbForegroundColor;
    if (m_rgbForegroundColor == m_rgbBackgroundColor) {
        const CResRef cResRef = pRes->GetResRef();
        if (cResRef == "REALMS") {
            rgbColor = RGB(255, 240, 5);
        } else if (cResRef == "STONESML") {
            rgbColor = RGB(190, 125, 0);
        } else if (cResRef == "STONEBIG") {
            rgbColor = RGB(190, 125, 0);
        } else {
            rgbColor = RGB(255, 255, 255);
        }
    }

    rgbColor = g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(rgbColor);

    if ((dwFlags & 0x20000) != 0) {
        rgbColor = RGB((GetRValue(rgbColor) * GetRValue(GetTintColor())) >> 8,
            (GetGValue(rgbColor) * GetGValue(GetTintColor())) >> 8,
            (GetBValue(rgbColor) * GetBValue(GetTintColor())) >> 8);
    }

    SetTextColor(hDC, rgbColor);

    ExtTextOutA(hDC,
        x,
        y - GetBaseLineHeight(TRUE), // NOTE: Uninline.
        ETO_CLIPPED,
        rClip,
        sString,
        sString.GetLength(),
        NULL);

    SelectObject(hDC, hPrev);

    do {
        hr = pVidMode->pSurfaces[nSurface]->ReleaseDC(hDC);
        pVidMode->CheckResults(hr);
    } while (hr == DDERR_SURFACELOST || hr == DDERR_WASSTILLDRAWING);

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
    CSingleLock renderLock(&REGISTRY_CRITICAL_SECTION, FALSE);

    if (g_pChitin->cVideo.Is3dAccelerated() && !g_pChitin->field_1A0) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
        // __LINE__: 141
        UTIL_ASSERT(renderLock.Lock(INFINITE) != 0);

        POSITION pos = REGISTRY.GetHeadPosition();
        while (pos != NULL) {
            POSITION curr = pos;
            CVidFontRegistryEntry* node = REGISTRY.GetNext(pos);
            if (node->m_fontResRef == cResRef) {
                node->m_nRefCount++;
                m_posRegistryList = curr;
                renderLock.Unlock();
                return 3;
            }
        }

        CVidFontRegistryEntry* newNode = new CVidFontRegistryEntry();
        if (newNode == NULL) {
            m_posRegistryList = NULL;
            renderLock.Unlock();
            return 2;
        }

        newNode->m_fontResRef = cResRef;
        newNode->m_bLoaded = FALSE;
        newNode->m_nRefCount = 1;
        memset(newNode->m_aTextureIds, -1, sizeof(newNode->m_aTextureIds));
        memset(newNode->m_aFirstGlyph, -1, sizeof(newNode->m_aFirstGlyph));
        newNode->m_aGlyphWidths = NULL;
        newNode->m_aGlyphCoords = 0;
        newNode->m_nSequences = 0;
        m_posRegistryList = REGISTRY.AddTail(newNode);

        renderLock.Unlock();
    }

    return 1;
}

// 0x7A0770
int CVidFont::CheckIfLoaded(BOOL bDemanded)
{
    CSingleLock renderLock(&REGISTRY_CRITICAL_SECTION, FALSE);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
    // __LINE__: 141
    UTIL_ASSERT(renderLock.Lock(INFINITE) != 0);

    POSITION pos = REGISTRY.GetHeadPosition();
    while (pos != NULL) {
        POSITION curr = pos;
        CVidFontRegistryEntry* node = REGISTRY.GetNext(pos);
        if (node->m_fontResRef == cResRef) {
            m_posRegistryList = curr;
            if (!node->m_bLoaded) {
                if (LoadToTexture(bDemanded) == 2) {
                    m_posRegistryList = NULL;
                    renderLock.Unlock();
                    return 2;
                }
            }

            // FIXME: Missing explicit `Unlock`.
            return 3;
        }
    }

    renderLock.Unlock();
    return 2;
}

// 0x7A0880
void CVidFont::Unload()
{
    CSingleLock renderLock(&REGISTRY_CRITICAL_SECTION, FALSE);

    if (g_pChitin->cVideo.Is3dAccelerated() && !g_pChitin->field_1A0) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
        // __LINE__: 284
        UTIL_ASSERT(renderLock.Lock(INFINITE) != 0);

        POSITION pos = REGISTRY.GetHeadPosition();
        while (pos != NULL && pos != m_posRegistryList) {
            REGISTRY.GetNext(pos);
        }

        if (pos == NULL) {
            m_posRegistryList = NULL;
        }

        if (m_posRegistryList != NULL) {
            CVidFontRegistryEntry* node = REGISTRY.GetAt(m_posRegistryList);
            if (node != NULL) {
                if (--node->m_nRefCount == 0) {
                    REGISTRY.RemoveAt(m_posRegistryList);
                    if (node->m_bLoaded) {
                        INT nTextureId = node->m_aTextureIds[0];
                        INT nIndex;

                        if (nTextureId >= 789) {
                            nIndex = (nTextureId - 789) / 8;
                            if (nIndex < 12) {
                                byte_8FB974[nIndex] = FALSE;
                            }
                        }

                        for (nIndex = 0; nIndex < 8; nIndex++) {
                            nTextureId = node->m_aTextureIds[nIndex];
                            if (nTextureId != -1) {
                                g_pChitin->GetCurrentVideoMode()->AddDisposableTexture(nTextureId);
                            }
                        }

                        if (node->m_aGlyphWidths != NULL) {
                            delete node->m_aGlyphWidths;
                            node->m_aGlyphWidths = NULL;
                        }

                        if (node->m_aGlyphCoords != NULL) {
                            delete node->m_aGlyphCoords;
                            node->m_aGlyphCoords = NULL;
                        }
                    }
                    delete node;
                }

                m_posRegistryList = NULL;
            }
        }

        renderLock.Unlock();
    }
}

// 0x7A0A40
void CVidFont::UnloadAllFonts()
{
    if (g_pChitin->cVideo.Is3dAccelerated() && !g_pChitin->field_1A0) {
        while (!REGISTRY.IsEmpty()) {
            CVidFontRegistryEntry* node = REGISTRY.RemoveHead();
            if (node->m_bLoaded) {
                INT nTextureId = node->m_aTextureIds[0];
                INT nIndex;

                if (nTextureId >= 789) {
                    nIndex = (nTextureId - 789) / 8;
                    if (nIndex < 12) {
                        byte_8FB974[nIndex] = FALSE;
                    }
                }

                for (nIndex = 0; nIndex < 8; nIndex++) {
                    nTextureId = node->m_aTextureIds[nIndex];
                    if (nTextureId != -1) {
                        g_pChitin->GetCurrentVideoMode()->AddDisposableTexture(nTextureId);
                    }
                }

                if (node->m_aGlyphWidths != NULL) {
                    delete node->m_aGlyphWidths;
                    node->m_aGlyphWidths = NULL;
                }

                if (node->m_aGlyphCoords != NULL) {
                    delete node->m_aGlyphCoords;
                    node->m_aGlyphCoords = NULL;
                }
            }
            delete node;
        }
    }
}

// 0x7A0B20
INT CVidFont::LoadToTexture(BOOL bDemanded)
{
    if (m_posRegistryList == NULL) {
        return 2;
    }

    if (REGISTRY.IsEmpty()) {
        return 2;
    }

    CVidFontRegistryEntry* node = REGISTRY.GetAt(m_posRegistryList);
    if (node == NULL) {
        return 2;
    }

    INT nIndex;
    for (nIndex = 0; nIndex < 12; nIndex++) {
        if (!byte_8FB974[nIndex]) {
            break;
        }
    }

    if (nIndex >= 12) {
        return 2;
    }

    byte_8FB974[nIndex] = TRUE;

    // FIXME: Will never be true, probably some inlining.
    if (nIndex == -1) {
        return -2;
    }

    if (!bDemanded) {
        if (pRes->Demand() == NULL) {
            byte_8FB974[nIndex] = FALSE;
            return 2;
        }
    }

    BOOL bOldDoubleSize = m_bDoubleSize;
    m_bDoubleSize = FALSE;
    node->m_texSize.cx = 256;
    node->m_texSize.cy = 256;
    node->m_nFontHeight = GetFontHeight(TRUE);
    node->m_nBaseLineHeight = GetBaseLineHeight(TRUE);
    node->m_nSequences = GetNumberSequences(TRUE);
    node->m_aGlyphWidths = new INT[node->m_nSequences];
    node->m_aGlyphCoords = new CPoint[node->m_nSequences];

    CRect rClip(0, 0, 256, 256);

    if (m_bPaletteChanged) {
        for (INT nColorIndex = 0; nColorIndex < 256; nColorIndex++) {
            rgbTempPal[nColorIndex] = (nColorIndex << 24) | RGB(255, 255, 255);
        }
    } else {
        m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
        m_cPalette.Realize(rgbTempPal, 32, 0, NULL, 255);
    }

    DWORD* pData = new DWORD[node->m_texSize.cx * node->m_texSize.cy];

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
    // __LINE__: 521
    UTIL_ASSERT(pData != NULL);

    INT nSequence = 0;
    for (INT nTextureIndex = 0; nTextureIndex < 8; nTextureIndex++) {
        node->m_aTextureIds[nTextureIndex] = nTextureIndex + 8 * nIndex + 789;
        memset(pData, 0, sizeof(DWORD) * node->m_texSize.cx * node->m_texSize.cy);

        INT x = 0;
        INT y = node->m_nBaseLineHeight;
        while (nSequence < node->m_nSequences) {
            if (!SequenceSet(nSequence)) {
                m_bDoubleSize = bOldDoubleSize;
                byte_8FB974[nIndex] = FALSE;
                delete pData;
                delete node->m_aGlyphWidths;
                node->m_aGlyphWidths = NULL;
                delete node->m_aGlyphCoords;
                node->m_aGlyphCoords = NULL;

                if (!bDemanded) {
                    pRes->Release();
                }

                return 2;
            }

            FrameSet(0);

            CSize frameSize;
            GetCurrentFrameSize(frameSize, TRUE);

            node->m_aGlyphWidths[nSequence] = frameSize.cx;

            if (x + frameSize.cx > node->m_texSize.cx) {
                y += node->m_nFontHeight;
                x = 0;
                if (y >= node->m_texSize.cy) {
                    node->m_aFirstGlyph[nTextureIndex] = --nSequence;
                    break;
                }
            }

            node->m_aGlyphCoords[nSequence].x = x;
            node->m_aGlyphCoords[nSequence].y = y - node->m_nBaseLineHeight;

            if (m_pFrame != NULL || GetFrame(TRUE)) {
                Blt8To32(pData,
                    CVidTile::BYTES_PER_TEXEL * node->m_texSize.cx,
                    CPoint(x, y - m_pFrame->nCenterY),
                    rClip,
                    0,
                    CPoint(0, 0),
                    0);
                m_pFrame = NULL;
            }

            x += frameSize.cx;
            nSequence++;
        }

        CreateTexture(pData, node->m_aTextureIds[nTextureIndex], node->m_texSize);
    }

    delete pData;

    if (!bDemanded) {
        pRes->Release();
    }

    node->m_bLoaded = TRUE;
    m_bDoubleSize = bOldDoubleSize;

    return 1;
}

// 0x7A0F00
void CVidFont::CreateTexture(DWORD* pData, INT nTextureId, const CSize& size)
{
    GLuint textures[1];
    textures[0] = nTextureId;
    CVideo3d::glDeleteTextures(1, textures);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    g_pChitin->cVideo.field_13E = nTextureId;
    CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glTexImage2D(GL_TEXTURE_2D,
        0,
        g_pChitin->cVideo.field_136,
        size.cx,
        size.cy,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        pData);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
}

// 0x7A1090
BOOL CVidFont::TextOut3d(const CString& sText, WORD* pSurface, LONG lPitch, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    BOOL bSuccess;

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

    bSuccess = TextOut(sText, pSurface, lPitch, x, y, rClip, dwFlags, bDemanded);
    SetPolyColor(dwFlags);

    return bSuccess;
}

// 0x7A1210
BOOL CVidFont::TextOut3d(const CString& sText, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    BOOL bTemporary = FALSE;
    BOOL bResult;

    CSingleLock renderLock(&REGISTRY_CRITICAL_SECTION, FALSE);

    if (!g_pChitin->cVideo.Is3dAccelerated()) {
        return FALSE;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidFont3d.cpp
    // __LINE__: 861
    UTIL_ASSERT(renderLock.Lock(INFINITE) != 0);

    if (m_posRegistryList == NULL) {
        bTemporary = TRUE;
    }

    if (m_bDoubleSize || CheckIfLoaded(bDemanded) != 3) {
        bResult = TextOutEx3d(sText, x, y, rClip, dwFlags, bDemanded);
        renderLock.Unlock();
        return bResult;
    }

    CVidFontRegistryEntry* node = REGISTRY.GetAt(m_posRegistryList);

    CVideo3d::glEnable(GL_TEXTURE_2D);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    if (m_bPaletteChanged || (dwFlags & 0x20000) != 0) {
        CVideo3d::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

        COLORREF rgbColor = m_rgbForegroundColor;
        if (m_bPaletteChanged) {
            g_pChitin->GetCurrentVideoMode()->ApplyBrightnessContrast(rgbColor);
        } else {
            rgbColor = RGB(255, 255, 255);
        }

        if ((dwFlags & 0x20000) != 0) {
            rgbColor = RGB((GetRValue(rgbColor) * GetRValue(GetTintColor())) >> 8,
                (GetGValue(rgbColor) * GetGValue(GetTintColor())) >> 8,
                (GetBValue(rgbColor) * GetBValue(GetTintColor())) >> 8);
        }

        CVideo3d::glColor4f(static_cast<float>(GetRValue(rgbColor)) / 255.0f,
            static_cast<float>(GetGValue(rgbColor)) / 255.0f,
            static_cast<float>(GetBValue(rgbColor)) / 255.0f,
            1.0f);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    } else {
        CVideo3d::glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
    }

    CVideo3d::glEnable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    CVideo3d::glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    RenderCharacters(sText, x, y, node, rClip);

    CVideo3d::glDisable(GL_BLEND);
    g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

    if (bTemporary) {
        // NOTE: Probably should also decrement refcount.
        m_posRegistryList = NULL;
    }

    return TRUE;
}

// 0x7A1660
void CVidFont::RenderCharacters(const CString& sString, INT x, INT y, CVidFontRegistryEntry* node, const CRect& rClip)
{
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;
    float x4;
    float y4;

    INT nTextureIndex;
    INT nTextureId = -1;
    BYTE ch;

    INT nScale = 1;
    if (m_bDoubleSize) {
        nScale = 2;
    }

    y -= nScale * node->m_nBaseLineHeight;

    if (y > rClip.bottom
        || y + node->m_nFontHeight * nScale < rClip.top) {
        return;
    }

    // Skip left.
    INT nIndex = 0;
    while (nIndex < sString.GetLength()) {
        ch = sString[nIndex] - 1;
        if (x + node->m_aGlyphWidths[ch] * nScale >= rClip.left) {
            break;
        }

        x += node->m_aGlyphWidths[ch] * nScale;
        nIndex++;
    }

    while (nIndex < sString.GetLength()) {
        if (x > rClip.right) {
            break;
        }

        ch = sString[nIndex] - 1;
        if (ch <= 0xFF) {
            if (x < rClip.left) {
                x1 = static_cast<float>(rClip.left);
                x3 = static_cast<float>(rClip.left - x) / static_cast<float>(nScale) + static_cast<float>(node->m_aGlyphCoords[ch].x);
                x3 /= static_cast<float>(node->m_texSize.cx);
            } else {
                x1 = static_cast<float>(x);
                x3 = static_cast<float>(node->m_aGlyphCoords[ch].x);
                x3 /= static_cast<float>(node->m_texSize.cx);
            }

            if (x + node->m_aGlyphWidths[ch] * nScale > rClip.right) {
                x2 = static_cast<float>(rClip.right);
                x4 = static_cast<float>(node->m_aGlyphCoords[ch].x + node->m_aGlyphWidths[ch] - (x + node->m_aGlyphWidths[ch] * nScale - rClip.right) / nScale);
                x4 /= static_cast<float>(node->m_texSize.cx);
            } else {
                x2 = static_cast<float>(x + node->m_aGlyphWidths[ch] * nScale);
                x4 = static_cast<float>(node->m_aGlyphCoords[ch].x + node->m_aGlyphWidths[ch]);
                x4 /= static_cast<float>(node->m_texSize.cx);
            }

            if (y < rClip.top) {
                y1 = static_cast<float>(rClip.top);
                y3 = static_cast<float>(rClip.top - y) / static_cast<float>(nScale) + static_cast<float>(node->m_aGlyphCoords[ch].y);
                y3 /= static_cast<float>(node->m_texSize.cy);
            } else {
                y1 = static_cast<float>(y);
                y3 = static_cast<float>(node->m_aGlyphCoords[ch].y);
                y3 /= static_cast<float>(node->m_texSize.cy);
            }

            if (y + node->m_nFontHeight * nScale > rClip.bottom) {
                y2 = static_cast<float>(rClip.bottom);
                y4 = static_cast<float>(node->m_aGlyphCoords[ch].y + node->m_nFontHeight - (y + node->m_nFontHeight * nScale - rClip.bottom) / nScale);
                y4 /= static_cast<float>(node->m_texSize.cy);
            } else {
                y2 = static_cast<float>(y + node->m_nFontHeight * nScale);
                y4 = static_cast<float>(node->m_aGlyphCoords[ch].y + node->m_nFontHeight);
                y4 /= static_cast<float>(node->m_texSize.cy);
            }

            nTextureIndex = 0;
            while (nTextureIndex < 8 && ch > node->m_aFirstGlyph[nTextureIndex]) {
                nTextureIndex++;
            }

            if (node->m_aTextureIds[nTextureIndex] != nTextureId) {
                nTextureId = node->m_aTextureIds[nTextureIndex];
                g_pChitin->cVideo.field_13E = nTextureId;
                CVideo3d::glBindTexture(GL_TEXTURE_2D, nTextureId);
                g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);
            }

            if (nTextureIndex != 8) {
                x1 += CVideo3d::SUB_PIXEL_SHIFT;
                y1 += CVideo3d::SUB_PIXEL_SHIFT;
                x2 += CVideo3d::SUB_PIXEL_SHIFT;
                y2 += CVideo3d::SUB_PIXEL_SHIFT;

                CVideo3d::glBegin(GL_TRIANGLE_STRIP);
                CVideo3d::glTexCoord2f(x3, y3);
                CVideo3d::glVertex3f(x1, y1, 0.0f);
                CVideo3d::glTexCoord2f(x3, y4);
                CVideo3d::glVertex3f(x1, y2, 0.0f);
                CVideo3d::glTexCoord2f(x4, y3);
                CVideo3d::glVertex3f(x2, y1, 0.0f);
                CVideo3d::glTexCoord2f(x4, y4);
                CVideo3d::glVertex3f(x2, y2, 0.0f);
                CVideo3d::glEnd();
                g_pChitin->GetCurrentVideoMode()->CheckResults3d(0);

                x += nScale * node->m_aGlyphWidths[ch];
            }
        } else {
            CString sMessage;
            sMessage.Format("The String %s has a bad character at position %d", sString, nIndex);
        }
        nIndex++;
    }
}

// 0x7A1BB0
BOOL CVidFont::TextOutEx3d(const CString& sString, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded)
{
    if (!bDemanded) {
        if (pRes->Demand() == NULL) {
            return FALSE;
        }
    }

    if (m_bPaletteChanged) {
        if (m_cPalette.m_pPalette == NULL
            || m_rgbForegroundColor != m_rgbPaletteForegroundColor
            || m_rgbBackgroundColor != m_rgbPaletteBackgroundColor) {
            RealizePalette(m_rgbForegroundColor, m_rgbBackgroundColor);
        }
    } else {
        m_cPalette.SetPalette(pRes->m_pPalette, 256, CVidPalette::TYPE_RESOURCE);
    }

    dwFlags |= 0x1;

    m_cPalette.Realize(rgbTempPal,
        g_pChitin->cVideo.GetBitsPerPixels(),
        dwFlags,
        &m_paletteAffects,
        255);

    for (int index = 0; index < sString.GetLength(); index++) {
        SequenceSet(sString[index] - 1);

        char ch = sString[index];
        SHORT nSequence = ch < 0 ? ch + 256 : ch;
        SequenceSet(nSequence - 1);

        if (g_pChitin->field_1A0 && IsDBCSLeadByte(sString[index])) {
            FrameSet(sString[index] - 1);
        } else {
            FrameSet(0);
        }

        CSize size;
        GetCurrentFrameSize(size, FALSE);

        CPoint ptCenter;
        GetCurrentCenterPoint(ptCenter, FALSE);

        CRect rChar(x, y - ptCenter.y, x + size.cx, y + size.cy - ptCenter.y);

        CRect rClampedChar;
        if (rClampedChar.IntersectRect(rChar, rClip)) {
            if (g_pChitin->cVideo.field_13A) {
                CVidInf::FXClear(CVideo3d::texImageData, size.cy * CVidInf::FX_WIDTH);
            } else {
                CVidInf::FXClear(CVideo3d::texImageData, size.cx * size.cy);
            }

            Render3d(x + ptCenter.x, y, rClip, TRUE, dwFlags);
        }

        x += size.cx;
    }

    if (!bDemanded) {
        pRes->Release();
    }

    return TRUE;
}

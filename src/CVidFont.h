#ifndef CHVIDFONT_H_
#define CHVIDFONT_H_

#include "mfc.h"

#include "CResRef.h"
#include "CVidCell.h"

class CVidFontRegistryEntry {
public:
    /* 0000 */ CResRef m_fontResRef;
    /* 0008 */ BOOL m_bLoaded;
    /* 000C */ INT m_nRefCount;
    /* 0010 */ INT m_aTextureIds[8];
    /* 0030 */ BYTE m_aFirstGlyph[8];
    /* 0038 */ CSize m_texSize;
    /* 0040 */ INT m_nFontHeight;
    /* 0044 */ INT m_nBaseLineHeight;
    /* 0048 */ INT m_nSequences;
    /* 004C */ INT* m_aGlyphWidths;
    /* 0050 */ CPoint* m_aGlyphCoords;
};

class CVidFont : public CVidCell {
public:
    static BOOLEAN byte_8FB974[12];
    static CTypedPtrList<CPtrList, CVidFontRegistryEntry*> REGISTRY;
    static CCriticalSection REGISTRY_CRITICAL_SECTION;

    CVidFont();
    ~CVidFont();
    LONG GetStringLength(const CString& sString, BOOLEAN bDemanded);
    LONG GetStringLengthEx(INT nSurface, const CString& sString, BOOLEAN bDemanded);
    SHORT GetBaseLineHeight(BOOLEAN bDemanded);
    SHORT GetFontHeight(BOOLEAN bDemanded);
    void SetColor(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor, BOOL bForce);
    void SetResRef(const CResRef& cNewResRef, BOOL bDoubleSize, BOOL bSetAutoRequest);
    BOOL SetTextFontEx(INT nSurface, HDC hDC);
    void RealizePalette(COLORREF rgbForegroundColor, COLORREF rgbBackgroundColor);
    BOOL TextOut(const CString& sString, int x, int y, const CRect& rClip, INT nSurface);
    BOOL TextOut(const CString& sString, WORD* pSurface, LONG lPitch, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL TextOutEx(INT nSurface, const CString& sString, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL Load(BOOL bDemanded);
    int RegisterFont();
    int CheckIfLoaded(BOOL bDemanded);
    void Unload();
    INT LoadToTexture(BOOL bDemanded);
    void CreateTexture(DWORD* pData, INT nTextureId, const CSize& size);
    BOOL TextOut3d(const CString& sText, WORD* pSurface, LONG lPitch, INT x, INT y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    BOOL TextOut3d(const CString& sText, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);
    void RenderCharacters(const CString& sString, INT x, INT y, CVidFontRegistryEntry* node, const CRect& rClip);
    BOOL TextOutEx3d(const CString& sText, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);

    static void UnloadAllFonts();

    /* 00DA */ RGBQUAD m_palette[256];
    /* 04DA */ HFONT m_hFont;
    /* 04DE */ BOOL m_bFontSet;
    /* 04E2 */ int field_4E2;
    /* 04E6 */ short field_4E6;
    /* 04E8 */ SHORT m_nBaseLineHeight;
    /* 04EA */ SHORT m_nFontHeight;
    /* 04EC */ COLORREF m_rgbForegroundColor;
    /* 04F0 */ COLORREF m_rgbBackgroundColor;
    /* 04F4 */ POSITION m_posRegistryList;
    /* 04F8 */ COLORREF m_rgbPaletteForegroundColor;
    /* 04FC */ COLORREF m_rgbPaletteBackgroundColor;
};

#endif /* CHVIDFONT_H_ */

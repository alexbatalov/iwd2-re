#ifndef CHVIDFONT_H_
#define CHVIDFONT_H_

#include "mfc.h"

#include "CResRef.h"
#include "CVidCell.h"

class CVidFont : public CVidCell {
public:
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
    int RegisterFont();
    void Unload();
    BOOL TextOut3d(const CString& sText, int x, int y, const CRect& rClip, DWORD dwFlags, BOOL bDemanded);

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
    /* 04F4 */ int field_4F4;
    /* 04F8 */ COLORREF m_rgbPaletteForegroundColor;
    /* 04FC */ COLORREF m_rgbPaletteBackgroundColor;
};

#endif /* CHVIDFONT_H_ */

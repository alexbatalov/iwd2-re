#include "CVidPalette.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x85E840
const RGBQUAD CVidPalette::CLEAR_RGBQUAD = { 0, 0xFF, 0, 0 };

// 0x85E844
const RGBQUAD CVidPalette::SHADOW_RGBQUAD = { 0, 0, 0, 0 };

// 0x85E848
const USHORT CVidPalette::TYPE_RESOURCE = 0;

// 0x85E84A
const USHORT CVidPalette::TYPE_RANGE = 1;

// 0x85E84E
const USHORT CVidPalette::NUM_RANGES = 7;

// 0x85E856
const BYTE CVidPalette::LIGHT_SCALE = 3;

// #binary-identical
// 0x7BEEA0
CVidPalette::CVidPalette(USHORT nType)
{
    m_nEntries = 0;
    m_bPaletteOwner = FALSE;
    m_bSubRangesCalculated = FALSE;
    m_pPalette = NULL;

    SetType(nType);

    rgbGlobalTint = 0xFFFFFF;
    m_nAUCounterBase = 0;
    m_nAUCounter = 0;

    memset(m_rangeColors, 0, sizeof(m_rangeColors));
}

// #binary-identical
// 0x7BEEE0
CVidPalette::~CVidPalette()
{
    if (m_nType == TYPE_RANGE) {
        if (m_bPaletteOwner) {
            delete m_pPalette;
        }
    }
}

// 0x7BEF30
void CVidPalette::SetType(USHORT nType)
{
    COLORREF transparentColor;

    m_nType = nType;
    m_bSubRangesCalculated = FALSE;
    m_bPaletteOwner = TRUE;

    switch (nType) {
    case TYPE_RESOURCE:
        m_pPalette = NULL;
        m_nEntries = -1;
        break;
    case TYPE_RANGE:
        m_nEntries = 256;
        if (m_pPalette != NULL) {
            delete m_pPalette;
        }

        m_pPalette = new RGBQUAD[m_nEntries];

        transparentColor = g_pChitin->GetCurrentVideoMode()->GetTransparentColor();
        m_pPalette[0].rgbRed = GetRValue(transparentColor);
        m_pPalette[0].rgbGreen = GetGValue(transparentColor);
        m_pPalette[0].rgbBlue = GetBValue(transparentColor);

        m_pPalette[1].rgbRed = 0;
        m_pPalette[1].rgbGreen = 0;
        m_pPalette[1].rgbBlue = 0;

        m_pPalette[2].rgbRed = 0;
        m_pPalette[2].rgbGreen = 0;
        m_pPalette[2].rgbBlue = 0;

        m_pPalette[3].rgbRed = 0;
        m_pPalette[3].rgbGreen = 0;
        m_pPalette[3].rgbBlue = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidPal.cpp
        // __LINE__: 454
        UTIL_ASSERT(FALSE);
    }
}

// #binary-identical
// 0x7BF100
INT CVidPalette::GetReservedEntries(DWORD dwFlags)
{
    if ((dwFlags & 0x400000) != 0) {
        return memcmp(&m_pPalette[0], &CLEAR_RGBQUAD, sizeof(RGBQUAD)) == 0 ? 1 : 0;
    }

    if ((dwFlags & 0x800000) != 0) {
        return 0;
    }

    return memcmp(&m_pPalette[1], &SHADOW_RGBQUAD, sizeof(RGBQUAD)) == 0 ? 2 : 1;
}

// #binary-identical
// 0x7BF390
void CVidPalette::SetPalette(RGBQUAD* pPalette, int nEntries, USHORT nType)
{
    m_pPalette = pPalette;
    m_nEntries = nEntries;
    m_nType = nType;
}

// #binary-identical
// 0x7BF3B0
void CVidPalette::SetPalette(const CVidPalette& cPalette)
{
    m_pPalette = cPalette.m_pPalette;
    m_nEntries = cPalette.m_nEntries;
    m_nType = cPalette.m_nType;
    m_bPaletteOwner = FALSE;
    memcpy(m_rangeColors, cPalette.m_rangeColors, sizeof(m_rangeColors));
}

// #binary-identical
// 0x7BF3F0
RGBQUAD CVidPalette::SetPaletteEntry(USHORT nEntry, COLORREF rgbColor)
{
    RGBQUAD old = m_pPalette[nEntry];
    m_pPalette[nEntry].rgbRed = GetRValue(rgbColor);
    m_pPalette[nEntry].rgbGreen = GetGValue(rgbColor);
    m_pPalette[nEntry].rgbBlue = GetBValue(rgbColor);
    return old;
}

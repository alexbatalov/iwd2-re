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

// 0x85E857
const BYTE CVidPalette::NO_TINT = 255;

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

// 0x7BEF00
void CVidPalette::SetAUCounter()
{
    int nBase = m_nAUCounterBase;
    if (nBase == 0) {
        nBase = reinterpret_cast<int>(m_pPalette);
    }
    m_nAUCounter = nBase + g_pChitin->nAUCounter;
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

// 0x7BF150
void CVidPalette::Realize(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal)
{
    // TODO: Incomplete.
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

// 0x7BF430
BOOL CVidPalette::GetTint(CVIDPALETTE_COLOR& rgbTint, CVIDIMG_PALETTEAFFECT* pAffectArgs, INT& nShiftBack, INT& nMaxValue, DWORD dwFlags)
{
    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();
    COLORREF rgbGlobalTintColor = pVidMode->GetGlobalTintColor();

    if ((dwFlags & 0x20000) != 0) {
        if ((dwFlags & 0x10000) != 0) {
            rgbTint.rgbRed = GetRValue(rgbGlobalTintColor) * GetRValue(pAffectArgs->rgbTintColor);
            rgbTint.rgbGreen = GetGValue(rgbGlobalTintColor) * GetGValue(pAffectArgs->rgbTintColor);
            rgbTint.rgbBlue = GetBValue(rgbGlobalTintColor) * GetBValue(pAffectArgs->rgbTintColor);
            nShiftBack = 16;
            nMaxValue = 255 * 255;
            return TRUE;
        } else {
            rgbTint.rgbRed = GetRValue(pAffectArgs->rgbTintColor);
            rgbTint.rgbGreen = GetGValue(pAffectArgs->rgbTintColor);
            rgbTint.rgbBlue = GetBValue(pAffectArgs->rgbTintColor);
            nShiftBack = 8;
            nMaxValue = 255;
            return TRUE;
        }
    } else {
        if ((dwFlags & 0x10000) != 0) {
            rgbTint.rgbRed = GetRValue(rgbGlobalTintColor);
            rgbTint.rgbGreen = GetGValue(rgbGlobalTintColor);
            rgbTint.rgbBlue = GetBValue(rgbGlobalTintColor);
            nShiftBack = 8;
            nMaxValue = 255;
            return TRUE;
        } else {
            rgbTint.rgbRed = 1;
            rgbTint.rgbGreen = 1;
            rgbTint.rgbBlue = 1;
            nShiftBack = 0;
            nMaxValue = 1;
            return FALSE;
        }
    }
}

// 0x7BF590
BOOL CVidPalette::GetAdd(CVIDPALETTE_COLOR& rgbInv, CVIDIMG_PALETTEAFFECT* pAffectArgs, INT& nShiftBack, DWORD dwFlags)
{
    BYTE nBrightnessCorrection;
    if (g_pChitin->cVideo.m_bIs3dAccelerated && (dwFlags & 0x8) != 0) {
        nBrightnessCorrection = 0;
    } else {
        nBrightnessCorrection = g_pChitin->GetCurrentVideoMode()->m_nBrightnessCorrection;
    }

    if ((dwFlags & 0x40000) != 0) {
        if (nBrightnessCorrection != 0) {
            rgbInv.rgbRed = nBrightnessCorrection * GetRValue(pAffectArgs->rgbAddColor);
            rgbInv.rgbGreen = nBrightnessCorrection * GetGValue(pAffectArgs->rgbAddColor);
            rgbInv.rgbBlue = nBrightnessCorrection * GetBValue(pAffectArgs->rgbAddColor);
            nShiftBack = 16;
            return TRUE;
        } else {
            rgbInv.rgbRed = GetRValue(pAffectArgs->rgbAddColor);
            rgbInv.rgbGreen = GetGValue(pAffectArgs->rgbAddColor);
            rgbInv.rgbBlue = GetBValue(pAffectArgs->rgbAddColor);
            nShiftBack = 8;
            return TRUE;
        }
    } else {
        if (nBrightnessCorrection != 0) {
            rgbInv.rgbRed = ~nBrightnessCorrection;
            rgbInv.rgbGreen = ~nBrightnessCorrection;
            rgbInv.rgbBlue = ~nBrightnessCorrection;
            nShiftBack = 8;
            return TRUE;
        } else {
            rgbInv.rgbRed = 1;
            rgbInv.rgbGreen = 1;
            rgbInv.rgbBlue = 1;
            nShiftBack = 0;
            return FALSE;
        }
    }
}

// 0x7BF6C0
BOOL CVidPalette::GetLight(CVIDPALETTE_COLOR& rgbLight, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD dwFlags)
{
    BYTE nGammaCorrection = g_pChitin->GetCurrentVideoMode()->m_nGammaCorrection;

    if ((dwFlags & 0x200000) != 0) {
        if (nGammaCorrection != 0) {
            rgbLight.rgbRed = GetRValue(pAffectArgs->rgbLightColor) + nGammaCorrection + 8;
            rgbLight.rgbGreen = GetGValue(pAffectArgs->rgbLightColor) + nGammaCorrection + 8;
            rgbLight.rgbBlue = GetBValue(pAffectArgs->rgbLightColor) + nGammaCorrection + 8;
            return TRUE;
        } else {
            rgbLight.rgbRed = GetRValue(pAffectArgs->rgbLightColor) + 8;
            rgbLight.rgbGreen = GetGValue(pAffectArgs->rgbLightColor) + 8;
            rgbLight.rgbBlue = GetBValue(pAffectArgs->rgbLightColor) + 8;
            return TRUE;
        }
    } else {
        if (nGammaCorrection != 0) {
            rgbLight.rgbRed = nGammaCorrection + 8;
            rgbLight.rgbGreen = nGammaCorrection + 8;
            rgbLight.rgbBlue = nGammaCorrection + 8;
            return TRUE;
        } else {
            rgbLight.rgbRed = 8;
            rgbLight.rgbGreen = 8;
            rgbLight.rgbBlue = 8;
            return FALSE;
        }
    }
}

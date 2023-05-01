#include "CVidPalette.h"

#include "CChitin.h"
#include "CUtil.h"
#include "CVidBitmap.h"
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

// 0x85E854
const BYTE CVidPalette::SHADOW_ENTRY = 1;

// 0x85E855
const BYTE CVidPalette::CLEAR_ENTRY = 0;

// 0x85E856
const BYTE CVidPalette::LIGHT_SCALE = 3;

// 0x85E857
const BYTE CVidPalette::NO_TINT = 255;

// 0x8BD6D8
BYTE CVidPalette::m_SuppressTintMasks[7] = {
    0x1,
    0x2,
    0x4,
    0x8,
    0x10,
    0x20,
    0x40,
};

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
    switch (m_nType) {
    case TYPE_RESOURCE:
        if (g_pChitin->cVideo.m_bIs3dAccelerated) {
            RealizeResource3d(pDestPalette, dwFlags, pAffectArgs, nTransVal);
        } else {
            if (pAffectArgs != NULL
                || g_pChitin->GetCurrentVideoMode()->m_nBrightnessCorrection != 0
                || g_pChitin->GetCurrentVideoMode()->m_nGammaCorrection != 0) {
                RealizeResource(pDestPalette, nBpp, dwFlags, pAffectArgs);
            } else {
                QuickRealizeResource(pDestPalette, nBpp);
            }
        }
        break;
    case TYPE_RANGE:
        if (g_pChitin->cVideo.m_bIs3dAccelerated) {
            RealizeRange3d(pDestPalette, dwFlags, pAffectArgs, nTransVal);
        } else {
            RealizeRange(pDestPalette, nBpp, dwFlags, pAffectArgs, 0xFF000000);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidPal.cpp
        // __LINE__: 631
        UTIL_ASSERT(FALSE);
    }
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

// 0x7BF7D0
void CVidPalette::SetRange(USHORT nRange, USHORT nValue, CVidBitmap& bmpMasterPalette)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidPal.cpp
    // __LINE__: 934
    UTIL_ASSERT(m_nType == TYPE_RANGE);

    // TODO: Check.
    m_rangeColors[nRange] = static_cast<BYTE>(nValue);

    RGBQUAD* pTmpPalette = m_pPalette + 12 * nRange + 1;
    bmpMasterPalette.pRes->Demand();
    for (int nIndex = 0; nIndex < 12; nIndex++) {
        bmpMasterPalette.GetPixelColor(*pTmpPalette++, nIndex, nValue, TRUE);
    }
    bmpMasterPalette.pRes->Release();

    m_bSubRangesCalculated = FALSE;
}

// 0x7BF870
void CVidPalette::RealizeRange(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal)
{
    // TODO: Incomplete.
}

// 0x7C04B0
void CVidPalette::RealizeResource(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs)
{
    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();

    // NOTE: Uninline.
    SetAUCounter();

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidPal.cpp
    // __LINE__: 1386
    UTIL_ASSERT(m_pPalette != NULL);

    // NOTE: Uninline.
    INT nReservedEntries = GetReservedEntries(dwFlags);

    BOOL bIs16 = nBpp == 16;
    DWORD v1 = pVidMode->field_C2;
    DWORD v2 = pVidMode->field_C6;
    DWORD v3 = pVidMode->field_CA;
    DWORD dwRBitShift = pVidMode->m_dwRBitShift;
    DWORD dwGBitShift = pVidMode->m_dwGBitShift;
    DWORD dwBBitShift = pVidMode->m_dwBBitShift;

    CVIDPALETTE_COLOR rgbTint;
    INT nTintShift;
    INT nTintMax;
    USHORT nTintPercentage = 0;
    BOOL bTint = GetTint(rgbTint, pAffectArgs, nTintShift, nTintMax, dwFlags);
    if (pAffectArgs != NULL) {
        if (pAffectArgs->pRangeTints[0] != NULL) {
            if (pAffectArgs->aRangeTintPeriods[0] == 1) {
                rgbTint.rgbRed *= GetRValue(*pAffectArgs->pRangeTints[0]);
                rgbTint.rgbGreen *= GetGValue(*pAffectArgs->pRangeTints[0]);
                rgbTint.rgbBlue *= GetBValue(*pAffectArgs->pRangeTints[0]);
            } else {
                nTintPercentage = m_nAUCounter % (2 * pAffectArgs->aRangeTintPeriods[0]);
                if (nTintPercentage > pAffectArgs->aRangeTintPeriods[0]) {
                    nTintPercentage = 2 * pAffectArgs->aRangeTintPeriods[0] - nTintPercentage;
                }

                rgbTint.rgbRed *= NO_TINT - nTintPercentage * (NO_TINT - GetRValue(*pAffectArgs->pRangeTints[0])) / pAffectArgs->aRangeTintPeriods[0];
                rgbTint.rgbGreen *= NO_TINT - nTintPercentage * (NO_TINT - GetGValue(*pAffectArgs->pRangeTints[0])) / pAffectArgs->aRangeTintPeriods[0];
                rgbTint.rgbBlue *= NO_TINT - nTintPercentage * (NO_TINT - GetBValue(*pAffectArgs->pRangeTints[0])) / pAffectArgs->aRangeTintPeriods[0];
            }

            bTint = TRUE;
            nTintShift += 8;
            nTintMax *= 255;
        }
    }

    CVIDPALETTE_COLOR rgbInv;
    INT nAddShift;
    USHORT nAddPercentage = 0;
    BOOL bAdd = GetAdd(rgbInv, pAffectArgs, nAddShift, dwFlags);
    if (pAffectArgs != NULL) {
        if (pAffectArgs->pRangeAdds[0] != NULL) {
            if (pAffectArgs->aRangeAddPeriods[0] == 1 || pAffectArgs->aRangeAddPeriods[0] == 0) {
                rgbInv.rgbRed *= ~GetRValue(*pAffectArgs->pRangeAdds[0]);
                rgbInv.rgbGreen *= ~GetGValue(*pAffectArgs->pRangeAdds[0]);
                rgbInv.rgbBlue *= ~GetBValue(*pAffectArgs->pRangeAdds[0]);
            } else {
                nAddPercentage = m_nAUCounter % (2 * pAffectArgs->aRangeAddPeriods[0]);
                if (nAddPercentage > pAffectArgs->aRangeAddPeriods[0]) {
                    nAddPercentage = 2 * pAffectArgs->aRangeAddPeriods[0] - nAddPercentage;
                }

                rgbInv.rgbRed *= ~(nAddPercentage * GetRValue(*pAffectArgs->pRangeAdds[0]) / pAffectArgs->aRangeAddPeriods[0]);
                rgbInv.rgbGreen *= ~(nAddPercentage * GetGValue(*pAffectArgs->pRangeAdds[0]) / pAffectArgs->aRangeAddPeriods[0]);
                rgbInv.rgbBlue *= ~(nAddPercentage * GetBValue(*pAffectArgs->pRangeAdds[0]) / pAffectArgs->aRangeAddPeriods[0]);
            }

            bAdd = TRUE;
            nAddShift += 8;
        }
    }

    CVIDPALETTE_COLOR rgbLight;
    USHORT nLightPercentage = 0;
    BOOL bLight = GetLight(rgbLight, pAffectArgs, dwFlags);
    if (pAffectArgs != NULL) {
        if (pAffectArgs->pRangeLights[0] != NULL) {
            if (pAffectArgs->aRangeLightPeriods[0] == 1) {
                rgbLight.rgbRed += GetRValue(*pAffectArgs->pRangeLights[0]);
                rgbLight.rgbGreen += GetGValue(*pAffectArgs->pRangeLights[0]);
                rgbLight.rgbBlue += GetBValue(*pAffectArgs->pRangeLights[0]);
                nLightPercentage = 1;
            } else {
                nLightPercentage = m_nAUCounter % (2 * pAffectArgs->aRangeLightPeriods[0]);
                if (nLightPercentage > pAffectArgs->aRangeLightPeriods[0]) {
                    nLightPercentage = 2 * pAffectArgs->aRangeLightPeriods[0] - nLightPercentage;
                }

                rgbLight.rgbRed += nLightPercentage * GetRValue(*pAffectArgs->pRangeLights[0]) / pAffectArgs->aRangeLightPeriods[0];
                rgbLight.rgbGreen += nLightPercentage * GetGValue(*pAffectArgs->pRangeLights[0]) / pAffectArgs->aRangeLightPeriods[0];
                rgbLight.rgbBlue += nLightPercentage * GetBValue(*pAffectArgs->pRangeLights[0]) / pAffectArgs->aRangeLightPeriods[0];
            }

            bLight = TRUE;
        }

        if ((pAffectArgs->suppressTints & CVidPalette::m_SuppressTintMasks[0]) != 0) {
            if (nLightPercentage != 0 || nAddPercentage != 0) {
                if (nLightPercentage > nAddPercentage) {
                    rgbTint.rgbRed += nLightPercentage * (nTintMax - rgbTint.rgbRed) / pAffectArgs->aRangeLightPeriods[0];
                    rgbTint.rgbGreen += nLightPercentage * (nTintMax - rgbTint.rgbGreen) / pAffectArgs->aRangeLightPeriods[0];
                    rgbTint.rgbBlue += nLightPercentage * (nTintMax - rgbTint.rgbBlue) / pAffectArgs->aRangeLightPeriods[0];
                } else {
                    rgbTint.rgbRed += nAddPercentage * (nTintMax - rgbTint.rgbRed) / pAffectArgs->aRangeAddPeriods[0];
                    rgbTint.rgbGreen += nAddPercentage * (nTintMax - rgbTint.rgbGreen) / pAffectArgs->aRangeAddPeriods[0];
                    rgbTint.rgbBlue += nAddPercentage * (nTintMax - rgbTint.rgbBlue) / pAffectArgs->aRangeAddPeriods[0];
                }

                if (pVidMode->m_nFade != CVidMode::NUM_FADE_FRAMES) {
                    rgbTint.rgbRed = pVidMode->ApplyFadeAmount(rgbTint.rgbRed);
                    rgbTint.rgbGreen = pVidMode->ApplyFadeAmount(rgbTint.rgbGreen);
                    rgbTint.rgbBlue = pVidMode->ApplyFadeAmount(rgbTint.rgbBlue);
                }
            }
        }
    }

    DWORD v10;
    DWORD v11;
    if (bIs16) {
        for (INT nIndex = 0; nIndex < nReservedEntries; nIndex++) {
            if (nIndex == CVidPalette::SHADOW_ENTRY) {
                COLORREF rgb = pVidMode->ApplyBrightnessContrast(RGB(0, 0, 0));
                *pDestPalette++ = ((GetRValue(rgb) >> v1) << dwRBitShift) | ((GetGValue(rgb) >> v2) << dwGBitShift) | ((GetBValue(rgb) >> v3) << dwBBitShift);
            } else {
                *pDestPalette++ = ((m_pPalette[nIndex].rgbRed >> v1) << dwRBitShift) | ((m_pPalette[nIndex].rgbGreen >> v2) << dwGBitShift) | ((m_pPalette[nIndex].rgbBlue >> v3) << dwBBitShift);
            }
        }
        v10 = (255 >> v2) << dwGBitShift;
        v11 = ((255 >> v2) - 1) << dwGBitShift;
    } else {
        for (INT nIndex = 0; nIndex < nReservedEntries; nIndex++) {
            if (nIndex == CVidPalette::SHADOW_ENTRY) {
                COLORREF rgb = pVidMode->ApplyBrightnessContrast(RGB(0, 0, 0));
                *pDestPalette++ = (GetRValue(rgb) << dwRBitShift) | (GetGValue(rgb) << dwGBitShift) | (GetBValue(rgb) << dwBBitShift);
            } else {
                *pDestPalette++ = (m_pPalette[nIndex].rgbRed << dwRBitShift) | (m_pPalette[nIndex].rgbGreen << dwGBitShift) | (m_pPalette[nIndex].rgbBlue << dwBBitShift);
            }
        }
        v10 = 255 << dwGBitShift;
        v11 = 254 << dwGBitShift;
    }

    for (INT nIndex = nReservedEntries; nIndex < 256; nIndex++) {
        RGBQUAD rgb = m_pPalette[nIndex];

        if ((dwFlags & 0x80000) != 0) {
            rgb.rgbRed = (rgb.rgbRed + rgb.rgbGreen + rgb.rgbBlue) / 4;
            rgb.rgbGreen = rgb.rgbRed;
            rgb.rgbBlue = rgb.rgbBlue;
        }

        if ((dwFlags & 0x2000000) != 0) {
            rgb.rgbGreen = (rgb.rgbRed + rgb.rgbGreen + rgb.rgbBlue) / 4;
            rgb.rgbBlue = rgb.rgbGreen;
            rgb.rgbRed = rgb.rgbGreen + 21;
        }

        if (bTint) {
            rgb.rgbRed = (rgbTint.rgbRed * rgb.rgbRed) >> nTintShift;
            rgb.rgbGreen = (rgbTint.rgbGreen * rgb.rgbGreen) >> nTintShift;
            rgb.rgbBlue = (rgbTint.rgbBlue * rgb.rgbBlue) >> nTintShift;
        }

        if (bAdd) {
            rgb.rgbRed = ~rgb.rgbRed;
            rgb.rgbGreen = ~rgb.rgbGreen;
            rgb.rgbBlue = ~rgb.rgbBlue;

            rgb.rgbRed = (rgbInv.rgbRed * rgb.rgbRed) >> nAddShift;
            rgb.rgbGreen = (rgbInv.rgbGreen * rgb.rgbGreen) >> nAddShift;
            rgb.rgbBlue = (rgbInv.rgbBlue * rgb.rgbBlue) >> nAddShift;

            rgb.rgbRed = ~rgb.rgbRed;
            rgb.rgbGreen = ~rgb.rgbGreen;
            rgb.rgbBlue = ~rgb.rgbBlue;
        }

        if (bLight) {
            rgb.rgbRed = min(rgbLight.rgbRed * rgb.rgbRed / 8, 255);
            rgb.rgbGreen = min(rgbLight.rgbGreen * rgb.rgbGreen / 8, 255);
            rgb.rgbBlue = min(rgbLight.rgbBlue * rgb.rgbBlue / 8, 255);
        }

        if (bIs16) {
            WORD color = ((rgb.rgbRed >> v1) << dwRBitShift) | ((rgb.rgbGreen >> v2) << dwGBitShift) | ((rgb.rgbBlue >> v3) << dwBBitShift);
            if (color == v10) {
                // TODO: Check.
                color = static_cast<WORD>(v11);
            }
            *pDestPalette++ = color;
        } else {
            DWORD color = (rgb.rgbRed << dwRBitShift) | (rgb.rgbGreen << dwGBitShift) | (rgb.rgbBlue << dwBBitShift);
            if (color == v10) {
                color = v11;
            }
            *pDestPalette++ = color;
        }
    }
}

// NOTE: Inlined in `CVidPalette::Realize`.
void CVidPalette::QuickRealizeResource(DWORD* pDestPalette, INT nBpp)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidPal.cpp
    // __LINE__: 1849
    UTIL_ASSERT(m_pPalette != NULL);

    CVidMode* pVidMode = g_pChitin->GetCurrentVideoMode();
    BOOL bIs16 = nBpp == 16;
    DWORD v1 = pVidMode->field_C2;
    DWORD v2 = pVidMode->field_C6;
    DWORD v3 = pVidMode->field_CA;
    DWORD dwRBitShift = pVidMode->m_dwRBitShift;
    DWORD dwGBitShift = pVidMode->m_dwGBitShift;
    DWORD dwBBitShift = pVidMode->m_dwBBitShift;

    if (bIs16) {
        for (int index = 0; index < m_nEntries; index++) {
            pDestPalette[index] = ((m_pPalette[index].rgbRed >> v1) << dwRBitShift) | ((m_pPalette[index].rgbGreen >> v2) << dwGBitShift) | ((m_pPalette[index].rgbBlue >> v3) << dwBBitShift);
        }
    } else {
        for (int index = 0; index < m_nEntries; index++) {
            pDestPalette[index] = (m_pPalette[index].rgbRed << dwRBitShift) | (m_pPalette[index].rgbGreen << dwGBitShift) | (m_pPalette[index].rgbBlue << dwBBitShift);
        }
    }
}

// 0x7D6240
void CVidPalette::RealizeResource3d(DWORD* pDestPalette, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal)
{
    // TODO: Incomplete.
}

// 0x7D6900
void CVidPalette::RealizeRange3d(DWORD* pDestPalette, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal)
{
    DWORD nNewTransVal;
    if ((dwFlags & 0x2) != 0) {
        nNewTransVal = nTransVal << 24;
    } else {
        nNewTransVal = 0xFF000000;
    }

    RealizeRange(pDestPalette, 32, dwFlags, pAffectArgs, nNewTransVal);

    pDestPalette[SHADOW_ENTRY] &= 0xFFFFFF;
    pDestPalette[SHADOW_ENTRY] |= ((nTransVal * 128) / 255) << 24;
}

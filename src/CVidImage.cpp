#include "CVidImage.h"

// 0x7ACA60
CVidImage::CVidImage()
{
    m_nFxSurface = -1;
    m_paletteAffects.rgbTintColor = 0xFFFFFF;
    m_paletteAffects.rgbAddColor = 0;
    m_paletteAffects.rgbLightColor = (1 << CVidPalette::LIGHT_SCALE) | ((1 << CVidPalette::LIGHT_SCALE) << 8) | ((1 << CVidPalette::LIGHT_SCALE) << 16);
    memset(m_paletteAffects.pRangeTints, 0, sizeof(m_paletteAffects.pRangeTints[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.pRangeAdds, 0, sizeof(m_paletteAffects.pRangeAdds[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.pRangeLights, 0, sizeof(m_paletteAffects.pRangeLights[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeTintPeriods, 0, sizeof(m_paletteAffects.aRangeTintPeriods[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeAddPeriods, 0, sizeof(m_paletteAffects.aRangeAddPeriods[0]) * CVidPalette::NUM_RANGES);
    memset(m_paletteAffects.aRangeLightPeriods, 0, sizeof(m_paletteAffects.aRangeLightPeriods[0]) * CVidPalette::NUM_RANGES);
    m_paletteAffects.suppressTints = 0;

    // TODO: Incomplete.
}

// 0x7ACC40
CVidImage::~CVidImage()
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x7ACD40
COLORREF CVidImage::GetTintColor()
{
    sizeof(m_cPalette);
    return m_paletteAffects.rgbTintColor;
}

// #binary-identical
// 0x7ACD50
void CVidImage::SetAddColor(COLORREF rgbNewColor)
{
    m_paletteAffects.rgbAddColor = rgbNewColor;
}

// #binary-identical
// 0x7ACD60
void CVidImage::SetTintColor(COLORREF rgbNewColor)
{
    m_paletteAffects.rgbTintColor = rgbNewColor;
}

#include "CVidCell.h"

#include "CUtil.h"

// 0x8BAC8C
BOOL CVidCell::TRANSLUCENT_SHADOWS_ON = TRUE;

// #binary-identical
// 0x7ACD70
CVidCell::CVidCell()
{
    m_nCurrentFrame = 0;
    m_nCurrentSequence = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D6 = 0;
    field_C8 = 1;
    field_D4 = 1;
}

// 0x7AD0F0
CVidCell::~CVidCell()
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x7AD280
void CVidCell::AddRangeAffect(USHORT nAffectType, USHORT nRangeId, COLORREF rgbAffectColor, BYTE pulsePeriod)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 523
    UTIL_ASSERT(nRangeId < CVidPalette::NUM_RANGES);

    switch (nAffectType) {
    case 0:
        if (m_paletteAffects.pRangeTints[nRangeId] == NULL) {
            m_paletteAffects.pRangeTints[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeTints[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeTintPeriods[nRangeId] = pulsePeriod;
        break;
    case 1:
    case 3:
        if (m_paletteAffects.pRangeAdds[nRangeId] == NULL) {
            m_paletteAffects.pRangeAdds[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeAdds[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeAddPeriods[nRangeId] = pulsePeriod;
        break;
    case 2:
        if (m_paletteAffects.pRangeLights[nRangeId] == NULL) {
            m_paletteAffects.pRangeLights[nRangeId] = new COLORREF;
        }
        *m_paletteAffects.pRangeLights[nRangeId] = rgbAffectColor;
        m_paletteAffects.aRangeLightPeriods[nRangeId] = pulsePeriod;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 523
        UTIL_ASSERT(FALSE);
    }
}

// #binary-identical
// 0x7AD3A0
void CVidCell::DeleteResPaletteAffect()
{
    if (m_paletteAffects.pRangeTints[0] != NULL) {
        delete m_paletteAffects.pRangeTints[0];
        m_paletteAffects.pRangeTints[0] = NULL;
        m_paletteAffects.aRangeTintPeriods[0] = 0;
    }

    if (m_paletteAffects.pRangeAdds[0] != NULL) {
        delete m_paletteAffects.pRangeAdds[0];
        m_paletteAffects.pRangeAdds[0] = NULL;
        m_paletteAffects.aRangeAddPeriods[0] = 0;
    }

    if (m_paletteAffects.pRangeLights[0] != NULL) {
        delete m_paletteAffects.pRangeLights[0];
        m_paletteAffects.pRangeLights[0] = NULL;
        m_paletteAffects.aRangeLightPeriods[0] = 0;
    }
}

// #binary-identical
// 0x7AD400
void CVidCell::DeleteRangeAffects(USHORT nRangeId)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
    // __LINE__: 635
    UTIL_ASSERT(nRangeId < CVidPalette::NUM_RANGES);

    if (m_paletteAffects.pRangeTints[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeTints[nRangeId];
        m_paletteAffects.pRangeTints[nRangeId] = NULL;
    }

    if (m_paletteAffects.pRangeAdds[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeAdds[nRangeId];
        m_paletteAffects.pRangeAdds[nRangeId] = NULL;
    }

    if (m_paletteAffects.pRangeLights[nRangeId] != NULL) {
        delete m_paletteAffects.pRangeLights[nRangeId];
        m_paletteAffects.pRangeLights[nRangeId] = NULL;
    }
}

// #binary-identical
// 0x7ADFE0
BOOL CVidCell::FrameAdvance()
{
    m_nCurrentFrame++;
    return TRUE;
}

// #binary-identical
// 0x7ADFF0
BOOL CVidCell::FrameSet(SHORT nFrame)
{
    m_nCurrentFrame = nFrame;
    return TRUE;
}

// #binary-identical
// 0x7AE290
BOOL CVidCell::SequenceSet(SHORT nSequence)
{
    m_nCurrentSequence = nSequence;
    return TRUE;
}

// #binary-identical
// 0x7AE320
void CVidCell::AddResPaletteAffect(USHORT nAffectType, COLORREF rgbAffectColor, BYTE pulsePeriod)
{
    switch (nAffectType) {
    case 0:
        if (m_paletteAffects.pRangeTints[0] == NULL) {
            m_paletteAffects.pRangeTints[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeTints[0] = rgbAffectColor;
        m_paletteAffects.aRangeTintPeriods[0] = pulsePeriod;
        break;
    case 1:
    case 3:
        if (m_paletteAffects.pRangeAdds[0] == NULL) {
            m_paletteAffects.pRangeAdds[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeAdds[0] = rgbAffectColor;
        m_paletteAffects.aRangeAddPeriods[0] = pulsePeriod;
        break;
    case 2:
        if (m_paletteAffects.pRangeLights[0] == NULL) {
            m_paletteAffects.pRangeLights[0] = new COLORREF;
        }
        *m_paletteAffects.pRangeLights[0] = rgbAffectColor;
        m_paletteAffects.aRangeLightPeriods[0] = pulsePeriod;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChVidImage.cpp
        // __LINE__: 1704
        UTIL_ASSERT(FALSE);
    }
}

// 0x7AE590
void CVidCell::SuppressTint(SHORT nRange)
{
    m_paletteAffects.suppressTints |= 1 << nRange;
}

// 0x7AE5B0
void CVidCell::UnsuppressTint(SHORT nRange)
{
    m_paletteAffects.suppressTints &= ~(1 << nRange);
}

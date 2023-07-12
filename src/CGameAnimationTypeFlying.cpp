#include "CGameAnimationTypeFlying.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6A3950
CGameAnimationTypeFlying::CGameAnimationTypeFlying(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    CString v1;

    m_animationID = animationID;
    m_falseColor = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
    m_colorChunks = -1;
    m_pSndDeath = "";

    switch (animationID & 0xF00) {
    case 0x0:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AEAG";
        break;
    case 0x100:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AGUL";
        break;
    case 0x200:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AVUL";
        break;
    case 0x300:
    case 0x400:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "ABIR";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1273
        UTIL_ASSERT(FALSE);
    }

    m_falseColor = FALSE;

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(v1 + "G1"), FALSE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (USHORT nRange = 0; nRange < CVidPalette::NUM_RANGES; nRange++) {
            m_charPalette.SetRange(nRange, *colorRangeValues++, g_pBaldurChitin->GetObjectGame()->m_rgbMasterBitmap);
        }
        m_g1VidCellBase.SetPalette(m_charPalette);
    }

    m_currentBamSequence = 1;
    if (m_falseColor) {
        m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
    } else {
        m_g1VidCellBase.m_bShadowOn = FALSE;
    }

    m_extendDirectionTest = CGameSprite::DIR_N;

    // NOTE: Uninline.
    ChangeDirection(facing);
}

// 0x6A3E10
CGameAnimationTypeFlying::~CGameAnimationTypeFlying()
{
}

// 0x6A3E90
void CGameAnimationTypeFlying::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1318
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6A3F00
void CGameAnimationTypeFlying::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if (m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6A3F60
void CGameAnimationTypeFlying::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1379
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;
    m_currentVidCell = m_currentVidCellBase;

    if (m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet((16 - m_currentBamDirection) % 16 + 9 * m_currentBamSequence);
    } else {
        m_currentVidCell->SequenceSet(m_currentBamDirection + 9 * m_currentBamSequence);
    }
}

// 0x6A3C70
BYTE CGameAnimationTypeFlying::GetListType()
{
    return CGAMEOBJECT_LIST_FLIGHT;
}

// 0x6A4EA0
BOOL CGameAnimationTypeFlying::IsFalseColor()
{
    return m_falseColor;
}

// 0x6A3C80
BOOL CGameAnimationTypeFlying::IsMirroring()
{
    return m_currentBamDirection > m_extendDirectionTest;
}

// 0x6A3CA0
BOOL CGameAnimationTypeFlying::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 785
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6A3CE0
BOOL CGameAnimationTypeFlying::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 786
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6A3D20
void CGameAnimationTypeFlying::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 787
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6A3D60
void CGameAnimationTypeFlying::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 788
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6A4000
void CGameAnimationTypeFlying::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1410
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g1VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1433
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A4110
void CGameAnimationTypeFlying::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1458
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g1VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
    }
}

// 0x6A41A0
void CGameAnimationTypeFlying::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1498
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellBase.SuppressTint(0);
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1528
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A42E0
void CGameAnimationTypeFlying::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1553
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g1VidCellBase.SuppressTint(0);
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
        }
    }
}
#include "CGameAnimationTypeFlying.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CInfinity.h"
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
            m_charPalette.SetRange(nRange, *colorRangeValues++, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
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

// 0x6A3DA0
SHORT CGameAnimationTypeFlying::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 798
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
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

// 0x6A43A0
void CGameAnimationTypeFlying::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1601
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1611
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6A4490
void CGameAnimationTypeFlying::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1637
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6A44F0
void CGameAnimationTypeFlying::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1668
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1669
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (m_currentBamDirection > m_extendDirectionTest) {
        dwRenderFlags |= CInfinity::MIRROR_FX;
    }

    if (transparency) {
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
        dwRenderFlags |= 0x2;
    } else {
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
        dwRenderFlags |= 0x1;
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        COLORREF oldTintColor;
        if (m_animationID == 0xD400) {
            oldTintColor = m_currentVidCell->GetTintColor();
            BYTE b = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
                ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
                : 0;
            BYTE g = GetGValue(oldTintColor) + GetGValue(rgbTintColor) - 255 >= 0
                ? GetGValue(oldTintColor) + GetGValue(rgbTintColor) + 1
                : 0;
            BYTE r = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
                ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
                : 0;
            m_currentVidCell->SetTintColor(RGB(r, g, b));
        }

        pInfinity->FXRender(m_currentVidCell,
            ptReference.x,
            ptReference.y,
            dwRenderFlags,
            transparency);

        if (m_animationID == 0xD400) {
            m_currentVidCell->SetTintColor(oldTintColor);

            pInfinity->FXRenderClippingPolys(ptPos.x,
                ptPos.y - posZ,
                posZ,
                ptReference,
                CRect(rGCBounds.left, rGCBounds.top - posZ, rGCBounds.right, rGCBounds.bottom - posZ),
                bDithered,
                dwRenderFlags);
        }

        if (bFadeOut) {
            pInfinity->FXUnlock(dwRenderFlags, &rFXRect, ptPos + ptReference);
        } else {
            pInfinity->FXUnlock(dwRenderFlags, &rFXRect, CPoint(0, 0));
        }

        pInfinity->FXBltFrom(nSurface,
            rFXRect,
            ptPos.x,
            ptPos.y,
            ptReference.x,
            ptReference.y,
            dwRenderFlags);
    }
}

// 0x6A47B0
SHORT CGameAnimationTypeFlying::SetSequence(SHORT nSequence)
{
    switch (nSequence) {
    case 1:
    case 4:
    case 5:
    case 6:
    case 8:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 17:
        nSequence = 7;
        break;
    case 2:
    case 3:
    case 7:
    case 9:
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;

        switch (m_animationID & 0xF00) {
        case 0x0:
            if (rand() % 3 != 0) {
                m_currentBamSequence = 1;
            } else {
                m_currentBamSequence = 0;
            }
            break;
        case 0x100:
            if (rand() % 5 != 0) {
                m_currentBamSequence = 1;
            } else {
                m_currentBamSequence = 0;
            }
            break;
        case 0x200:
            if (rand() % 4 != 0) {
                m_currentBamSequence = 1;
            } else {
                m_currentBamSequence = 0;
            }
            break;
        case 0x300:
            if (rand() % 6 != 0) {
                m_currentBamSequence = 1;
            } else {
                m_currentBamSequence = 0;
            }
            break;
        case 0x400:
            m_currentBamSequence = 1;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1800
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1805
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);
    m_currentVidCell->FrameSet(0);

    return nSequence;
}

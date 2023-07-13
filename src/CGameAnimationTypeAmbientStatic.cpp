#include "CGameAnimationTypeAmbientStatic.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6A5A10
CGameAnimationTypeAmbientStatic::CGameAnimationTypeAmbientStatic(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    CString sName;

    m_animationID = animationID;
    m_currentBamSequence = 0;
    m_falseColor = TRUE;
    m_bInvulnerable = FALSE;
    m_moveScale = 0;
    m_moveScaleCurrent = 0;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        sName = "ACOW";
        m_colorChunks = -1;
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_falseColor = FALSE;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";
        break;
    case 0x100:
        sName = "AHRS";
        m_colorChunks = -1;
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_falseColor = FALSE;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";
        break;
    case 0x200:
        if ((animationID & 0xF0) != 0) {
            sName = "NPROL";
        } else {
            sName = "NBEGL";
        }
        break;
    case 0x300:
        m_bInvulnerable = TRUE;

        if ((animationID & 0xF0) != 0) {
            sName = "NGRLL";
        } else {
            sName = "NBOYL";
        }

        m_pSndDeath = "FAL_01B";
        break;
    case 0x400:
        if ((animationID & 0xF0) != 0) {
            sName = "NFAWL";
        } else {
            sName = "NFAML";
        }
        break;
    case 0x500:
        if ((animationID & 0xF0) != 0) {
            sName = "NSIWL";
        } else {
            sName = "NSIML";
        }
        break;
    case 0x600:
        if ((animationID & 0xF0) != 0) {
            sName = "NNOWL";
        } else {
            sName = "NNOML";
        }
        break;
    case 0x700:
        sName = "NSLVL";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2569
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(sName + "G1"), FALSE, TRUE);

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetResRef(CResRef(sName + "G1E"), FALSE, TRUE);
    }

    m_currentVidCellExtend = &m_g1VidCellExtend;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], g_pBaldurChitin->GetObjectGame()->m_rgbMasterBitmap);
        }

        m_g1VidCellBase.SetPalette(m_charPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetPalette(m_charPalette);
        }
    }

    m_currentBamSequence = 0;

    if (MIRROR_BAM) {
        if (m_falseColor) {
            m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
        } else {
            m_g1VidCellBase.m_bShadowOn = FALSE;
        }
    }

    m_extendDirectionTest = CGameSprite::DIR_NNW;
    ChangeDirection(facing);
}

// 0x6A6190
CGameAnimationTypeAmbientStatic::~CGameAnimationTypeAmbientStatic()
{
}

// 0x6A5FE0
BOOL CGameAnimationTypeAmbientStatic::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 879
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6A6020
BOOL CGameAnimationTypeAmbientStatic::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 880
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6A6060
BOOL CGameAnimationTypeAmbientStatic::IsFalseColor()
{
    return m_falseColor;
}

// 0x6A6070
BOOL CGameAnimationTypeAmbientStatic::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6A60A0
void CGameAnimationTypeAmbientStatic::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 884
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6A60E0
void CGameAnimationTypeAmbientStatic::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 885
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6A6120
SHORT CGameAnimationTypeAmbientStatic::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 894
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6A6220
void CGameAnimationTypeAmbientStatic::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2631
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6A6290
void CGameAnimationTypeAmbientStatic::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6A6300
void CGameAnimationTypeAmbientStatic::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2692
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + ((15 - m_currentBamDirection) % 16) / 2);
    } else {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
    }
}

// 0x6A63E0
void CGameAnimationTypeAmbientStatic::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2726
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_g1VidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_g1VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2763
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A6560
void CGameAnimationTypeAmbientStatic::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2788
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellExtend.UnsuppressTintAllRanges();
        }
    }
}

// 0x6A6630
void CGameAnimationTypeAmbientStatic::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2838
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellBase.SuppressTint(0);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g1VidCellExtend.SuppressTint(0);
                }
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.SetTintColor(tintColor);
                }
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2885
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A67E0
void CGameAnimationTypeAmbientStatic::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2910
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g1VidCellBase.SuppressTint(0);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellExtend.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(tintColor);
            }
        }
    }
}

// 0x6A68E0
void CGameAnimationTypeAmbientStatic::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 2967
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, g_pBaldurChitin->GetObjectGame()->m_rgbMasterBitmap);
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 2977
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6A69D0
void CGameAnimationTypeAmbientStatic::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3003
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6A6CF0
SHORT CGameAnimationTypeAmbientStatic::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 2:
    case 3:
    case 7:
        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 6:
        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 8:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        nSequence = 7;

        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 9:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 4;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 3155
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);

    if (bRandomFrame) {
        BYTE nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            m_currentVidCell->FrameSet(rand() % nSequenceLength);
        } else {
            m_currentVidCell->FrameSet(0);
        }
    } else {
        m_currentVidCell->FrameSet(0);
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

// 0x6A6EE0
void CGameAnimationTypeAmbientStatic::GetAnimationResRef(CString& resRef, BYTE range)
{
    if (m_animationID == 0xB000) {
        resRef = "ACOW";
    } else {
        resRef = "";
    }
}

// 0x6A7750
BOOL CGameAnimationTypeAmbientStatic::IsInvulnerable()
{
    return m_bInvulnerable;
}

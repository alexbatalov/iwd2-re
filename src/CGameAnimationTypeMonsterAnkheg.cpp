#include "CGameAnimationTypeMonsterAnkheg.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CUtil.h"

// 0x8F8E00
const CRect CGameAnimationTypeMonsterAnkheg::ELLIPSE_EMPTY(0, 0, 0, 0);

// 0x6C2340
CGameAnimationTypeMonsterAnkheg::CGameAnimationTypeMonsterAnkheg(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    m_animationID = animationID;
    m_bAboveGround = FALSE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0:
        m_colorChunks = -1;
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_resRef = "MAKH";
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 15501
        UTIL_ASSERT(m_currentVidCell != NULL && m_currentVidCellHole != NULL);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE);
    m_g3VidCellBase.SetResRef(CResRef(m_resRef + "G3"), FALSE, TRUE);

    if (!MIRROR_BAM) {
        // NOTE: Uninline.
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE);
        m_g2VidCellExtend.SetResRef(CResRef(m_resRef + "G2E"), FALSE, TRUE);
        m_g3VidCellExtend.SetResRef(CResRef(m_resRef + "G3E"), FALSE, TRUE);
    }

    m_currentVidCellExtend = &m_g1VidCellExtend;
    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    // NOTE: Uninline.
    m_g1VidCellHoleBase.SetResRef(CResRef(m_resRef + "DG1"), FALSE, TRUE);
    m_g2VidCellHoleBase.SetResRef(CResRef(m_resRef + "DG2"), FALSE, TRUE);
    m_g3VidCellHoleBase.SetResRef(CResRef(m_resRef + "DG3"), FALSE, TRUE);

    if (!MIRROR_BAM) {
        // NOTE: Uninline.
        m_g1VidCellHoleExtend.SetResRef(CResRef(m_resRef + "DG1E"), FALSE, TRUE);
        m_g2VidCellHoleExtend.SetResRef(CResRef(m_resRef + "DG2E"), FALSE, TRUE);
        m_g3VidCellHoleExtend.SetResRef(CResRef(m_resRef + "DG3E"), FALSE, TRUE);
    }

    m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
    m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
    m_currentVidCellHole = &m_g1VidCellHoleBase;

    m_currentBamSequence = 3;

    if (MIRROR_BAM) {
        m_g1VidCellBase.m_bShadowOn = FALSE;
        m_g2VidCellBase.m_bShadowOn = FALSE;
        m_g3VidCellBase.m_bShadowOn = FALSE;
        m_g1VidCellHoleBase.m_bShadowOn = FALSE;
        m_g2VidCellHoleBase.m_bShadowOn = FALSE;
        m_g3VidCellHoleBase.m_bShadowOn = FALSE;
    }

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6C2EA0
CGameAnimationTypeMonsterAnkheg::~CGameAnimationTypeMonsterAnkheg()
{
}

// 0x6C2B80
const CRect& CGameAnimationTypeMonsterAnkheg::GetEllipseRect()
{
    if (m_bAboveGround) {
        return m_rEllipse;
    } else {
        return ELLIPSE_EMPTY;
    }
}

// 0x6C2BA0
BYTE CGameAnimationTypeMonsterAnkheg::GetMoveScale()
{
    if (m_bAboveGround) {
        return 0;
    } else {
        return m_moveScaleCurrent;
    }
}

// 0x6C2BC0
BYTE CGameAnimationTypeMonsterAnkheg::GetMoveScaleDefault()
{
    if (m_bAboveGround) {
        return 0;
    } else {
        return m_moveScale;
    }
}

// 0x6C2BE0
BOOL CGameAnimationTypeMonsterAnkheg::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1621
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6C2C20
BOOL CGameAnimationTypeMonsterAnkheg::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1622
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6C2C60
BOOL CGameAnimationTypeMonsterAnkheg::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6C2C90
void CGameAnimationTypeMonsterAnkheg::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1625
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1625
    UTIL_ASSERT(m_currentVidCellHole != NULL);

    m_currentVidCellHole->FrameAdvance();
}

// 0x6C2CF0
void CGameAnimationTypeMonsterAnkheg::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1626
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1626
    UTIL_ASSERT(m_currentVidCellHole != NULL);

    m_currentVidCellHole->m_nCurrentFrame--;
}

// 0x6C2D60
BOOL CGameAnimationTypeMonsterAnkheg::GetAboveGround()
{
    return m_bAboveGround;
}

// 0x6C2D70
BOOLEAN CGameAnimationTypeMonsterAnkheg::GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame)
{
    nSequence = m_currentVidCell->m_nCurrentSequence;
    nFrame = m_currentVidCell->m_nCurrentFrame;
    return TRUE;
}

// 0x6C2DA0
BOOLEAN CGameAnimationTypeMonsterAnkheg::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();
    resWeapon = "";
    resShield = "";
    resHelmet = "";
    return TRUE;
}

// 0x6C2E30
SHORT CGameAnimationTypeMonsterAnkheg::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1636
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6C2FD0
void CGameAnimationTypeMonsterAnkheg::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15563
    UTIL_ASSERT(m_currentVidCell != NULL && m_currentVidCellHole != NULL);

    CPoint ptChar;
    m_currentVidCell->GetCurrentCenterPoint(ptChar, FALSE);
    ptReference = ptChar;

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    CPoint ptHole;
    m_currentVidCellHole->GetCurrentCenterPoint(ptHole, FALSE);

    ptReference.x = max(ptHole.x, ptReference.x);
    ptReference.y = max(ptHole.y, ptReference.y);

    frameSize.cx += ptChar.x - ptReference.x;
    frameSize.cy += ptChar.y - ptReference.y;
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);

    m_currentVidCellHole->GetCurrentFrameSize(frameSize, FALSE);

    rFx.right = max(frameSize.cx + ptReference.x - ptHole.x, rFx.right);
    rFx.bottom = max(frameSize.cy + ptReference.y - ptHole.y, rFx.bottom);
}

// 0x6C30E0
void CGameAnimationTypeMonsterAnkheg::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6C3150
void CGameAnimationTypeMonsterAnkheg::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15642
    UTIL_ASSERT(m_currentVidCell != NULL && m_currentVidCellHole != NULL);

    m_currentBamDirection = nDirection;

    if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
        m_currentVidCellHole = m_currentVidCellHoleExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
        m_currentVidCellHole = m_currentVidCellHoleBase;
    }

    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
        m_currentVidCellHole->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
    } else {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
        m_currentVidCellHole->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
    }
}

// 0x6C3290
void CGameAnimationTypeMonsterAnkheg::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15688
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_g2VidCellBase.DeleteResPaletteAffect();
        m_g3VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_g2VidCellBase.UnsuppressTintAllRanges();
        m_g3VidCellBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.DeleteResPaletteAffect();
            m_g2VidCellExtend.DeleteResPaletteAffect();
            m_g3VidCellExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellExtend.UnsuppressTintAllRanges();
            m_g2VidCellExtend.UnsuppressTintAllRanges();
            m_g3VidCellExtend.UnsuppressTintAllRanges();
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 15724
        UTIL_ASSERT(FALSE);
    }
}

// 0x6C3470
void CGameAnimationTypeMonsterAnkheg::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15749
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
    m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
    m_g3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
    }

    m_g1VidCellBase.DeleteResPaletteAffect();
    m_g2VidCellBase.DeleteResPaletteAffect();
    m_g3VidCellBase.DeleteResPaletteAffect();

    // NOTE: Uninline.
    m_g1VidCellBase.UnsuppressTintAllRanges();
    m_g2VidCellBase.UnsuppressTintAllRanges();
    m_g3VidCellBase.UnsuppressTintAllRanges();

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.DeleteResPaletteAffect();
        m_g2VidCellExtend.DeleteResPaletteAffect();
        m_g3VidCellExtend.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellExtend.UnsuppressTintAllRanges();
        m_g2VidCellExtend.UnsuppressTintAllRanges();
        m_g3VidCellExtend.UnsuppressTintAllRanges();
    }
}

// 0x6C35D0
void CGameAnimationTypeMonsterAnkheg::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 15800
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_g1VidCellBase.SuppressTint(0);
            m_g2VidCellBase.SuppressTint(0);
            m_g3VidCellBase.SuppressTint(0);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellExtend.SuppressTint(0);
                m_g2VidCellExtend.SuppressTint(0);
                m_g3VidCellExtend.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
            m_g2VidCellBase.SetTintColor(tintColor);
            m_g3VidCellBase.SetTintColor(tintColor);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(tintColor);
                m_g2VidCellExtend.SetTintColor(tintColor);
                m_g3VidCellExtend.SetTintColor(tintColor);
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 15840
        UTIL_ASSERT(FALSE);
    }
}

// 0x6C37B0
void CGameAnimationTypeMonsterAnkheg::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15865
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (effectType != 0) {
        m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
        m_g2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
        m_g3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

        m_g1VidCellBase.SuppressTint(0);
        m_g2VidCellBase.SuppressTint(0);
        m_g3VidCellBase.SuppressTint(0);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_g1VidCellExtend.SuppressTint(0);
            m_g2VidCellExtend.SuppressTint(0);
            m_g3VidCellExtend.SuppressTint(0);
        }
    } else {
        m_g1VidCellBase.SetTintColor(tintColor);
        m_g2VidCellBase.SetTintColor(tintColor);
        m_g3VidCellBase.SetTintColor(tintColor);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(tintColor);
            m_g2VidCellExtend.SetTintColor(tintColor);
            m_g3VidCellExtend.SetTintColor(tintColor);
        }
    }
}

// 0x6C3910
void CGameAnimationTypeMonsterAnkheg::Render(CInfinity* pInfinity, CVidMode* pVidMode, int a3, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // TODO: Incomplete.
}

// 0x6C3D10
SHORT CGameAnimationTypeMonsterAnkheg::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    if (m_bAboveGround) {
        switch (nSequence) {
        case 1:
        case 5:
        case 17:
            m_currentVidCellBase = &m_g1VidCellBase;
            m_currentVidCellExtend = &m_g1VidCellExtend;
            m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
            m_currentBamSequence = 1;
            break;
        case 2:
        case 3:
        case 7:
            if (m_currentBamSequence != 3 || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentVidCellBase = &m_g1VidCellBase;
            m_currentVidCellExtend = &m_g1VidCellExtend;
            m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
            m_currentBamSequence = 3;
            break;
        case 4:
        case 6:
        case 8:
        case 10:
        case 14:
            nSequence = 7;

            if (m_currentBamSequence != 3 || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentVidCellBase = &m_g1VidCellBase;
            m_currentVidCellExtend = &m_g1VidCellExtend;
            m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
            m_currentBamSequence = 3;
            break;
        case 9:
            m_currentVidCellBase = &m_g1VidCellBase;
            m_currentVidCellExtend = &m_g1VidCellExtend;
            m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
            m_currentBamSequence = 0;
            break;
        case 11:
        case 13:
            m_currentVidCellBase = &m_g3VidCellBase;
            m_currentVidCellExtend = &m_g3VidCellExtend;
            m_currentVidCellHoleBase = &m_g3VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g3VidCellHoleExtend;
            m_currentBamSequence = 0;
            nSequence = 0;
            break;
        case 12:
            m_currentVidCellBase = &m_g3VidCellBase;
            m_currentVidCellExtend = &m_g3VidCellExtend;
            m_currentVidCellHoleBase = &m_g3VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g3VidCellHoleExtend;
            m_currentBamSequence = 1;
            nSequence = 0;
            break;
        case 15:
            m_currentVidCellBase = &m_g2VidCellBase;
            m_currentVidCellExtend = &m_g2VidCellExtend;
            m_currentVidCellHoleBase = &m_g2VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g2VidCellHoleExtend;
            m_currentBamSequence = 2;
            m_bAboveGround = FALSE;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 16089
            UTIL_ASSERT(FALSE);
        }
    } else {
        switch (nSequence) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 7:
        case 8:
        case 11:
        case 12:
        case 13:
        case 15:
            nSequence = 7;

            if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g2VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentVidCellBase = &m_g2VidCellBase;
            m_currentVidCellExtend = &m_g2VidCellExtend;
            m_currentVidCellHoleBase = &m_g2VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g2VidCellHoleExtend;
            m_currentBamSequence = 0;
            break;
        case 5:
        case 9:
        case 10:
        case 17:
            m_currentVidCellBase = &m_g1VidCellBase;
            m_currentVidCellExtend = &m_g1VidCellExtend;
            m_currentVidCellHoleBase = &m_g1VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g1VidCellHoleExtend;
            m_currentBamSequence = 0;
            break;
        case 6:
            if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g2VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentVidCellBase = &m_g2VidCellBase;
            m_currentVidCellExtend = &m_g2VidCellExtend;
            m_currentVidCellHoleBase = &m_g2VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g2VidCellHoleExtend;
            m_currentBamSequence = 0;
            break;
        case 14:
            m_currentVidCellBase = &m_g2VidCellBase;
            m_currentVidCellExtend = &m_g2VidCellExtend;
            m_currentVidCellHoleBase = &m_g2VidCellHoleBase;
            m_currentVidCellHoleExtend = &m_g2VidCellHoleExtend;
            m_currentBamSequence = 1;
            m_bAboveGround = TRUE;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 16140
            UTIL_ASSERT(FALSE);
        }
    }

    ChangeDirection(m_currentBamDirection);

    SHORT nFrame = 0;
    if (bRandomFrame) {
        BYTE nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            nFrame = rand() % nSequenceLength;
        }
    }
    m_currentVidCell->FrameSet(nFrame);
    m_currentVidCellHole->FrameSet(nFrame);

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

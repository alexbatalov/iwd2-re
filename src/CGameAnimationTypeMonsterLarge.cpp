#include "CGameAnimationTypeMonsterLarge.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6B0A00
CGameAnimationTypeMonsterLarge::CGameAnimationTypeMonsterLarge(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_falseColor = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    if ((animationID & 0xF00) != 0) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8149
        UTIL_ASSERT(FALSE);
    }

    m_rEllipse.left = -24;
    m_rEllipse.top = -18;
    m_rEllipse.right = 24;
    m_rEllipse.bottom = 18;
    m_moveScale = 6;
    m_moveScaleCurrent = 6;
    m_resRef = "MOGR";
    m_nSndFreq = 8;
    m_personalSpace = 5;
    m_pSndDeath = "FAL_03B";

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
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
        m_g2VidCellBase.SetPalette(m_charPalette);
        m_g3VidCellBase.SetPalette(m_charPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetPalette(m_charPalette);
            m_g2VidCellExtend.SetPalette(m_charPalette);
            m_g3VidCellExtend.SetPalette(m_charPalette);
        }
    }

    m_currentBamSequence = 1;

    if (MIRROR_BAM) {
        if (m_falseColor) {
            m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
        } else {
            m_g1VidCellBase.m_bShadowOn = FALSE;
            m_g2VidCellBase.m_bShadowOn = FALSE;
            m_g3VidCellBase.m_bShadowOn = FALSE;
        }
    }

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6B1150
CGameAnimationTypeMonsterLarge::~CGameAnimationTypeMonsterLarge()
{
}

// 0x6B0FE0
BOOL CGameAnimationTypeMonsterLarge::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1161
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6B1020
BOOL CGameAnimationTypeMonsterLarge::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1162
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6B1060
void CGameAnimationTypeMonsterLarge::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1165
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6B10A0
void CGameAnimationTypeMonsterLarge::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1166
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6B10E0
SHORT CGameAnimationTypeMonsterLarge::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1175
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6B1230
void CGameAnimationTypeMonsterLarge::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8216
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6B12A0
void CGameAnimationTypeMonsterLarge::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6B1310
void CGameAnimationTypeMonsterLarge::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8279
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
    } else {
        m_currentVidCell->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
    }
}

// 0x6B13F0
CVidPalette* CGameAnimationTypeMonsterLarge::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8316
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            return &m_charPalette;
        }

        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8331
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6B14B0
void CGameAnimationTypeMonsterLarge::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8361
        UTIL_ASSERT(m_currentVidCell != NULL);

        resRef = m_resRef;
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        resRef = "";
        break;
    }
}

// 0x6B1580
const char* CGameAnimationTypeMonsterLarge::GetSndWalk(SHORT a1)
{
    const char* v1;
    switch (a1) {
    case 1:
        v1 = "FS_Dirt ";
        break;
    case 2:
        v1 = "FS_WdSn ";
        break;
    case 3:
    case 9:
        v1 = "FS_WOOD ";
        break;
    case 4:
        v1 = "FS_Tomb ";
        break;
    case 7:
        v1 = "FS_Ston ";
        break;
    case 11:
        v1 = "FS_Snow ";
        break;
    case 15:
        v1 = "FS_Gras ";
        break;
    default:
        return NULL;
    }

    char* szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 3699
    UTIL_ASSERT(szTemp != NULL);

    memcpy(szTemp, v1, 9);

    szTemp[7] = rand() % 6 + '1';
    szTemp[8] = '\0';

    if (strcmp(szTemp, m_walkRef) == 0) {
        if (szTemp[7] == '6') {
            szTemp[7] = '1';
        } else {
            szTemp[7]++;
        }
    }

    memcpy(m_walkRef, szTemp, 9);

    // FIXME: Leaks `szTemp`.
    return szTemp;
}

// 0x6B16E0
void CGameAnimationTypeMonsterLarge::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8537
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g3VidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_g2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_g3VidCellBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_g2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_g3VidCellExtend.DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_g2VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_g3VidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8579
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B1910
void CGameAnimationTypeMonsterLarge::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8604
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }
    }
}

// 0x6B1A30
void CGameAnimationTypeMonsterLarge::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8650
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_g2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_g3VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
                m_g2VidCellBase.SuppressTint(colorRange & 0xF);
                m_g3VidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g3VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_g2VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_g3VidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType == 0) {
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
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8699
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B1C50
void CGameAnimationTypeMonsterLarge::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8724
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType == 0) {
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
}

// 0x6B1D20
void CGameAnimationTypeMonsterLarge::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 8775
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 8785
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6B1E10
void CGameAnimationTypeMonsterLarge::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 8811
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6B2130
SHORT CGameAnimationTypeMonsterLarge::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 2:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 3:
    case 7:
        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 4:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 6:
        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 8:
    case 14:
    case 15:
        nSequence = 7;

        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 9:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 11:
    case 13:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 12:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 1;
        nSequence = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8995
        UTIL_ASSERT(FALSE);
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

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

// 0x6B2A50
BOOL CGameAnimationTypeMonsterLarge::IsFalseColor()
{
    return m_falseColor;
}

// 0x6B2A60
BOOL CGameAnimationTypeMonsterLarge::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

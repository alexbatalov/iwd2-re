#include "CGameAnimationTypeMonsterLarge16.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6B23B0
CGameAnimationTypeMonsterLarge16::CGameAnimationTypeMonsterLarge16(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_falseColor = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_falseColor = FALSE;
        m_nSndFreq = 8;
        m_personalSpace = 3;
        m_resRef = "MWYV";
        break;
    case 0x100:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_falseColor = FALSE;
        m_nSndFreq = 16;
        m_personalSpace = 5;
        m_colorBlood = 56;
        m_resRef = "MWYV";
        m_colorChunks = -1;
        m_resRef = "MCAR";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9066
        UTIL_ASSERT(FALSE);
    }

    m_pSndDeath = "FAL_03B";

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE, TRUE);
    m_g3VidCellBase.SetResRef(CResRef(m_resRef + "G3"), FALSE, TRUE, TRUE);

    if (!MIRROR_BAM) {
        // NOTE: Uninline.
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE, TRUE);
        m_g2VidCellExtend.SetResRef(CResRef(m_resRef + "G2E"), FALSE, TRUE, TRUE);
        m_g3VidCellExtend.SetResRef(CResRef(m_resRef + "G3E"), FALSE, TRUE, TRUE);
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

// 0x6B2C10
CGameAnimationTypeMonsterLarge16::~CGameAnimationTypeMonsterLarge16()
{
}

// 0x6B29D0
BOOL CGameAnimationTypeMonsterLarge16::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1223
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6B2A10
BOOL CGameAnimationTypeMonsterLarge16::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1224
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6B2A50
BOOL CGameAnimationTypeMonsterLarge16::IsFalseColor()
{
    return m_falseColor;
}

// 0x6B2A60
BOOL CGameAnimationTypeMonsterLarge16::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6B2A90
void CGameAnimationTypeMonsterLarge16::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1227
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6B2AD0
void CGameAnimationTypeMonsterLarge16::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1166
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6B2B10
BOOLEAN CGameAnimationTypeMonsterLarge16::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();
    resWeapon = "";
    resShield = "";
    resHelmet = "";
    return TRUE;
}

// 0x6B2BA0
SHORT CGameAnimationTypeMonsterLarge16::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1175
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6B2CF0
void CGameAnimationTypeMonsterLarge16::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9134
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6B12A0
void CGameAnimationTypeMonsterLarge16::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6B2D60
void CGameAnimationTypeMonsterLarge16::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9197
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        if (m_currentVidCellBase != &m_g1VidCellBase || m_currentBamSequence != 0) {
            m_currentVidCell->SequenceSet(16 * m_currentBamSequence + (17 - m_currentBamDirection) % 16);
        } else {
            m_currentVidCell->SequenceSet((16 - m_currentBamDirection) % 16);
        }
    } else {
        m_currentVidCell->SequenceSet(16 * m_currentBamSequence + m_currentBamDirection);
    }
}

// 0x6B2E80
CVidPalette* CGameAnimationTypeMonsterLarge16::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9238
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
        // __LINE__: 9253
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6B2F40
void CGameAnimationTypeMonsterLarge16::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9284
        UTIL_ASSERT(m_currentVidCell != NULL);

        // FIXME: What for?
        if (resRef == "") {
            resRef = m_resRef;
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9301
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B3020
char* CGameAnimationTypeMonsterLarge16::GetSndReady()
{
    switch (m_animationID & 0xF00) {
    case 0x000:
    case 0x100:
        return "";
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9344
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B3090
char* CGameAnimationTypeMonsterLarge16::GetSndWalk(SHORT tableIndex)
{
    char* szTemp;

    if ((m_animationID & 0xF00) == 0) {
        return NULL;
    }

    if ((m_animationID & 0xF00) == 0x100) {
        szTemp = new char[8];

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9404
        UTIL_ASSERT(szTemp != NULL);

        strcpy(szTemp, "WAL_13 ");
        szTemp[6] = rand() % 4 + 'a';
        if (szTemp[6] == 'd') {
            szTemp[6] = '\0';
        }

        return szTemp;
    }

    const char* v1;
    switch (tableIndex) {
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

    szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9470
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

    return szTemp;
}

// 0x6B3260
void CGameAnimationTypeMonsterLarge16::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9539
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
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9596
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B3500
void CGameAnimationTypeMonsterLarge16::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9621
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
}

// 0x6B3690
void CGameAnimationTypeMonsterLarge16::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9682
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
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 9749
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B3970
void CGameAnimationTypeMonsterLarge16::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7792
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
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
}

// 0x6B3B10
void CGameAnimationTypeMonsterLarge16::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 9843
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 9853
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6B3C00
void CGameAnimationTypeMonsterLarge16::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9879
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6B3C60
void CGameAnimationTypeMonsterLarge16::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9910
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 9911
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (MIRROR_BAM) {
        if (m_currentBamDirection > m_extendDirectionTest) {
            dwRenderFlags |= CInfinity::MIRROR_FX;
        }

        if (transparency != 0) {
            dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
            dwRenderFlags |= 0x2;
        } else {
            dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
            dwRenderFlags |= 0x1;
        }
    } else {
        dwRenderFlags |= 0x4;

        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;

        if (transparency != 0) {
            dwRenderFlags |= 0x2;
        }
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        COLORREF oldTintColor = m_currentVidCell->GetTintColor();
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

        pInfinity->FXRender(m_currentVidCell,
            ptReference.x,
            ptReference.y,
            dwRenderFlags,
            transparency);

        m_currentVidCell->SetTintColor(oldTintColor);

        pInfinity->FXRenderClippingPolys(ptPos.x,
            ptPos.y - posZ,
            posZ,
            ptReference,
            CRect(rGCBounds.left, rGCBounds.top - posZ, rGCBounds.right, rGCBounds.bottom - posZ),
            bDithered,
            dwRenderFlags);

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

// 0x6B3F20
SHORT CGameAnimationTypeMonsterLarge16::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 2:
    case 3:
    case 7:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 4:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 6:
        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g2VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 8:
    case 14:
    case 15:
        nSequence = 7;

        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 9:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 4;
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 11:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 1;
        nSequence = 0;
        break;
    case 12:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 1;
        nSequence = 0;
        break;
    case 13:
        m_currentVidCellBase = &m_g3VidCellBase;
        m_currentVidCellExtend = &m_g3VidCellExtend;
        m_currentBamSequence = 2;
        nSequence = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10050
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

#include "CGameAnimationTypeMonsterOld.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6ADA70
CGameAnimationTypeMonsterOld::CGameAnimationTypeMonsterOld(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    field_7A6 = FALSE;
    m_translucent = FALSE;
    m_bDetectedByInfravision = TRUE;
    m_nSndFreq = -1;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        switch (animationID & 0xF) {
        case 0:
            m_moveScale = 7;
            m_moveScaleCurrent = 7;
            m_resRef = "MOGH";
            m_nSndFreq = 5;
            m_pSndDeath = "FAL_03B";
            break;
        case 1:
            m_moveScale = 6;
            m_moveScaleCurrent = 6;
            m_resRef = "MOGN";
            m_nSndFreq = 8;
            m_pSndDeath = "FAL_03B";
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 6516
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x100:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_resRef = "MBAS";
        m_falseColor = FALSE;
        m_nSndFreq = 70;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";

        if ((animationID & 0xF) == 1) {
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MBAS_GR"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
        }
        break;
    case 0x200:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 10;
        m_moveScaleCurrent = 10;
        m_resRef = "MBER";
        m_falseColor = FALSE;
        m_nSndFreq = 60;
        m_personalSpace = 3;
        m_pSndDeath = "FAL_03B";

        switch (animationID & 0xF) {
        case 0:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MBER_BL"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MBER_CA"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MBER_PO"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x400:
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_resRef = "MDOG";
        m_falseColor = FALSE;
        m_nSndFreq = 150;
        m_pSndDeath = "FAL_01B";

        switch (animationID & 0xF) {
        case 0:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MDOG_WI"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 1:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MDOG_WA"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MDOG_MO"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x500:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;
        m_resRef = "MDOP";
        m_falseColor = FALSE;
        m_colorBlood = 60;

        if ((animationID & 0xF) == 1) {
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MDOP_GR"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
        }
        break;
    case 0x600:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 8;
        m_resRef = "METT";
        m_falseColor = FALSE;
        m_colorBlood = 50;
        break;
    case 0x700:
        m_falseColor = FALSE;
        m_colorBlood = 66;
        m_bDetectedByInfravision = FALSE;

        switch (animationID & 0xF) {
        case 0:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            break;
        case 1:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MGHL_RE"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 2:
            m_moveScale = 4;
            m_moveScaleCurrent = 4;
            m_resRef = "MGHL";
            m_nSndFreq = 48;
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MGHL_GA"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0x800:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 8;
        m_resRef = "MGIB";
        m_falseColor = FALSE;
        m_pSndDeath = "FAL_01B";
        break;
    case 0x900:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 2;
        m_moveScaleCurrent = 2;
        m_resRef = "MSLI";
        m_falseColor = FALSE;
        m_translucent = TRUE;
        m_bDetectedByInfravision = FALSE;
        m_nSndFreq = 24;
        m_personalSpace = 3;
        m_pSndDeath = "";

        switch (animationID & 0xF) {
        case 0:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSLI_GR"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            m_colorBlood = 7;
            break;
        case 1:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSLI_OL"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            m_colorBlood = 36;
            break;
        case 2:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSLI_MU"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            m_colorBlood = 51;
            break;
        case 3:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSLI_OC"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            m_colorBlood = 37;
            break;
        case 4:
            m_colorBlood = 27;
            break;
        }
        break;
    case 0xA00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_resRef = "MSPI";
        m_falseColor = FALSE;
        m_nSndFreq = 20;
        m_personalSpace = 3;
        m_colorBlood = 51;

        switch (animationID & 0xF) {
        case 0:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSPI_GI"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 1:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSPI_HU"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSPI_PH"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSPI_SW"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 4:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MSPI_WR"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0xB00:
        m_colorChunks = -1;
        m_moveScale = 15;
        m_moveScaleCurrent = 15;
        m_resRef = "MWLF";
        m_falseColor = 0;
        m_nSndFreq = 150;
        m_pSndDeath = "FAL_01B";

        switch (animationID & 0xF) {
        case 1:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MWLF_WO"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 2:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MWLF_DI"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 3:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MWLF_WI"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 4:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MWLF_VA"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        case 5:
            field_7A6 = TRUE;
            field_7AA.SetResRef(CResRef("MWLF_DR"), TRUE, TRUE);
            field_7AA.m_bDoubleSize = FALSE;
            break;
        }
        break;
    case 0xC00:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 4;
        m_pSndDeath = "FAL_01B";

        switch (animationID & 0xF) {
        case 0:
            m_resRef = "MXVT";
            break;
        case 1:
            m_resRef = "MTAS";
            m_falseColor = FALSE;
            break;
        }
        break;
    case 0xD00:
        m_moveScale = 3;
        m_moveScaleCurrent = 3;
        m_resRef = "MZOM";
        m_falseColor = TRUE;
        m_colorBlood = 37;
        m_bDetectedByInfravision = FALSE;
        m_nSndFreq = 8;

        m_combatRounds[0].SetResRef(CResRef("rbzomb1"), TRUE, TRUE);
        m_combatRounds[0].m_bDoubleSize = FALSE;

        m_combatRounds[1].SetResRef(CResRef("rbzomb2"), TRUE, TRUE);
        m_combatRounds[1].m_bDoubleSize = FALSE;
        break;
    case 0xE00:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_moveScale = 10;
        m_moveScaleCurrent = 10;

        switch (animationID & 0xF) {
        case 0:
            m_resRef = "MWER";
            break;
        case 1:
            m_resRef = "MGWE";
            break;
        }

        m_nSndFreq = 5;
        m_falseColor = FALSE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 6839
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;

    if (!MIRROR_BAM) {
        // NOTE: Uninline.
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE);
        m_g2VidCellExtend.SetResRef(CResRef(m_resRef + "G2E"), FALSE, TRUE);
    }

    m_currentVidCellExtend = &m_g1VidCellExtend;
    m_currentVidCell = m_currentVidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
        m_g2VidCellBase.SetPalette(m_charPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetPalette(m_charPalette);
            m_g2VidCellExtend.SetPalette(m_charPalette);
        }
    }

    m_currentBamSequence = 1;

    if (MIRROR_BAM) {
        if (m_falseColor) {
            m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
        } else {
            m_g1VidCellBase.m_bShadowOn = FALSE;
            m_g2VidCellBase.m_bShadowOn = FALSE;
        }
    }

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6AF3D0
CGameAnimationTypeMonsterOld::~CGameAnimationTypeMonsterOld()
{
}

// 0x6AF4A0
BOOL CGameAnimationTypeMonsterOld::NewSupport(USHORT animationID)
{
    switch (animationID & 0xF00) {
    case 0x000:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x100:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x200:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x300:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x400:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x500:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x600:
        return FALSE;
    case 0x700:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0x800:
        return FALSE;
    case 0x900:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0xA00:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0xB00:
        switch (animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0xC00:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    case 0xD00:
        return FALSE;
    case 0xE00:
        switch (animationID & 0xF) {
        case 0:
        case 1:
            return FALSE;
        default:
            return TRUE;
        }
        break;
    }

    return TRUE;
}

// 0x6AF210
BOOLEAN CGameAnimationTypeMonsterOld::DetectedByInfravision()
{
    return m_bDetectedByInfravision;
}

// 0x6AF220
BOOL CGameAnimationTypeMonsterOld::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1101
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6AF260
BOOL CGameAnimationTypeMonsterOld::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1102
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6AF2A0
BOOL CGameAnimationTypeMonsterOld::IsFalseColor()
{
    return m_falseColor;
}

// 0x6AF2B0
BOOL CGameAnimationTypeMonsterOld::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6AF2E0
void CGameAnimationTypeMonsterOld::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1105
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6AF320
void CGameAnimationTypeMonsterOld::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1106
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6AF360
SHORT CGameAnimationTypeMonsterOld::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1115
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6AF5F0
void CGameAnimationTypeMonsterOld::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7138
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6AF660
void CGameAnimationTypeMonsterOld::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6AF6D0
void CGameAnimationTypeMonsterOld::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7199
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

// 0x6AF7B0
CVidPalette* CGameAnimationTypeMonsterOld::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 7236
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
        // __LINE__: 7251
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6AF870
void CGameAnimationTypeMonsterOld::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 7281
        UTIL_ASSERT(m_currentVidCell != NULL);

        if ((m_animationID & 0xF00) <= 0xA00
            || (m_animationID & 0xF00) != 0xB00
            || (m_animationID & 0xF) == 0
            || (m_animationID & 0xF) == 3) {
            resRef = m_resRef;
        }
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

// 0x6AFBB0
void CGameAnimationTypeMonsterOld::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7583
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g2VidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_g2VidCellBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_g2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_g2VidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_g1VidCellBase.DeleteResPaletteAffect();
            m_g2VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
            m_g2VidCellBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteResPaletteAffect();
                m_g2VidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellExtend.UnsuppressTintAllRanges();
                m_g2VidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 7630
        UTIL_ASSERT(FALSE);
    }
}

// 0x6AFDC0
void CGameAnimationTypeMonsterOld::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7655
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_g2VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_g2VidCellBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.DeleteResPaletteAffect();
            m_g2VidCellExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellExtend.UnsuppressTintAllRanges();
            m_g2VidCellExtend.UnsuppressTintAllRanges();
        }
    }
}

// 0x6AFEF0
void CGameAnimationTypeMonsterOld::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 7710
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_g2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
                m_g2VidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_g2VidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellBase.SuppressTint(0);
                m_g2VidCellBase.SuppressTint(0);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellExtend.SuppressTint(0);
                    m_g2VidCellExtend.SuppressTint(0);
                }
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
                m_g2VidCellBase.SetTintColor(tintColor);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.SetTintColor(tintColor);
                    m_g2VidCellExtend.SetTintColor(tintColor);
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
        // __LINE__: 7767
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B0140
void CGameAnimationTypeMonsterOld::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
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

            m_g1VidCellBase.SuppressTint(0);
            m_g2VidCellBase.SuppressTint(0);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellExtend.SuppressTint(0);
                m_g2VidCellExtend.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
            m_g2VidCellBase.SetTintColor(tintColor);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(tintColor);
                m_g2VidCellExtend.SetTintColor(tintColor);
            }
        }
    }
}

// 0x6B0290
void CGameAnimationTypeMonsterOld::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 7855
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 7865
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6B0380
void CGameAnimationTypeMonsterOld::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 7891
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6B0780
SHORT CGameAnimationTypeMonsterOld::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 4;
        break;
    case 2:
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
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 6:
        if (m_currentBamSequence != 2 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 8:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 9:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 5;
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;
        m_currentBamSequence = 0;
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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 8084
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

#include "CGameAnimationTypeMonsterMulti.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6B4180
CGameAnimationTypeMonsterMulti::CGameAnimationTypeMonsterMulti(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    field_800 = 0;
    m_bDoubleBlit = FALSE;
    m_colorChunks = -1;
    m_falseColor = FALSE;
    field_446 = 0;
    m_nQuadrants = 1;
    m_bSplitBams = FALSE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
    m_extendDirectionTest = CGameSprite::DIR_N;

    switch (animationID & 0xF00) {
    case 0:
        m_rEllipse.left = -36;
        m_rEllipse.top = -24;
        m_rEllipse.right = 36;
        m_rEllipse.bottom = 24;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_nSndFreq = 8;
        m_personalSpace = 5;
        m_resRef = "MWYV";
        m_pSndDeath = "FAL_03B";
        break;
    case 0x100:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_nSndFreq = 8;
        m_personalSpace = 5;
        m_resRef = "MTAN";
        m_pSndDeath = "FAL_03B";
        break;
    case 0x200:
        m_rEllipse.left = -72;
        m_rEllipse.top = -54;
        m_rEllipse.right = 72;
        m_rEllipse.bottom = 54;
        m_moveScale = 14;
        m_moveScaleCurrent = 14;
        m_nSndFreq = 8;
        m_pSndDeath = "FAL_03B";
        m_personalSpace = 5;
        m_castFrame = 9;
        m_bSplitBams = TRUE;
        m_nQuadrants = 9;

        switch (animationID & 0xF) {
        case 0:
            m_resRef = "MDR1";
            break;
        case 1:
            m_resRef = "MDR2";
            break;
        case 2:
            m_resRef = "MDR3";
            break;
        case 3:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_GR1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_GR2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_GR3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_GR4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_GR5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        case 4:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_AQ1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_AQ2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_AQ3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_AQ4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_AQ5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        case 5:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_BL1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_BL2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_BL3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_BL4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_BL5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        case 6:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_BR1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_BR2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_BR3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_BR4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_BR5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        case 7:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_MC1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_MC2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_MC3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_MC4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_MC5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        case 8:
            m_resRef = "MDR1";
            field_446 = 1;

            field_44E.SetResRef(CResRef("MDR1_PU1"), TRUE, TRUE);
            field_44E.m_bDoubleSize = FALSE;

            field_508.SetResRef(CResRef("MDR1_PU2"), TRUE, TRUE);
            field_508.m_bDoubleSize = FALSE;

            field_5C2.SetResRef(CResRef("MDR1_PU3"), TRUE, TRUE);
            field_5C2.m_bDoubleSize = FALSE;

            field_67C.SetResRef(CResRef("MDR1_PU4"), TRUE, TRUE);
            field_67C.m_bDoubleSize = FALSE;

            field_736.SetResRef(CResRef("MDR1_PU5"), TRUE, TRUE);
            field_736.m_bDoubleSize = FALSE;

            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 10245
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10250
        UTIL_ASSERT(FALSE);
    }

    m_g1VidCellBase = new CVidCell[5 * m_nQuadrants];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 10260
    UTIL_ASSERT(m_g1VidCellBase != NULL);

    m_g2VidCellBase = &(m_g1VidCellBase[m_nQuadrants]);
    m_g3VidCellBase = &(m_g1VidCellBase[2 * m_nQuadrants]);
    m_g4VidCellBase = &(m_g1VidCellBase[3 * m_nQuadrants]);
    m_g5VidCellBase = &(m_g1VidCellBase[4 * m_nQuadrants]);

    m_splitBamChar = '0';
    m_splitDirectionBamChar = '0';

    if (m_bSplitBams) {
        for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
            CString sSuffix = static_cast<char>(quad + '1');

            m_g2VidCellBase[quad].SetResRef(CResRef(m_resRef + '2' + sSuffix + m_splitBamChar + m_splitDirectionBamChar), m_bDoubleBlit, TRUE);

            m_g2VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g2VidCellBase);
        }
    } else {
        for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
            CString sSuffix = static_cast<char>(quad + '1');

            m_g1VidCellBase[quad].SetResRef(CResRef(m_resRef + "G1" + sSuffix), m_bDoubleBlit, TRUE);
            m_g2VidCellBase[quad].SetResRef(CResRef(m_resRef + "G2" + sSuffix), m_bDoubleBlit, TRUE);
            m_g3VidCellBase[quad].SetResRef(CResRef(m_resRef + "G3" + sSuffix), m_bDoubleBlit, TRUE);
            m_g4VidCellBase[quad].SetResRef(CResRef(m_resRef + "G4" + sSuffix), m_bDoubleBlit, TRUE);
            m_g5VidCellBase[quad].SetResRef(CResRef(m_resRef + "G5" + sSuffix), m_bDoubleBlit, TRUE);

            m_g1VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g1VidCellBase);
            m_g2VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g2VidCellBase);
            m_g3VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g3VidCellBase);
            m_g4VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g4VidCellBase);
            m_g5VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g5VidCellBase);
        }
    }

    m_currentVidCellBase = m_g2VidCellBase;
    m_currentVidCell = m_g2VidCellBase;

    field_44A = &field_508;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
            m_g1VidCellBase[quad].SetPalette(m_charPalette);
            m_g2VidCellBase[quad].SetPalette(m_charPalette);
            m_g3VidCellBase[quad].SetPalette(m_charPalette);
            m_g4VidCellBase[quad].SetPalette(m_charPalette);
            m_g5VidCellBase[quad].SetPalette(m_charPalette);
        }
    }

    m_currentBamSequence = 0;
    ChangeDirection(facing);
}

// 0x6B5A80
CGameAnimationTypeMonsterMulti::~CGameAnimationTypeMonsterMulti()
{
    delete[] m_g1VidCellBase;
}

// 0x6B57D0
void CGameAnimationTypeMonsterMulti::CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    return CalculateFxRect(rFx, ptReference, posZ);
}

// 0x6B57F0
BOOL CGameAnimationTypeMonsterMulti::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1318
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6B5830
BOOL CGameAnimationTypeMonsterMulti::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1319
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6B5870
BOOL CGameAnimationTypeMonsterMulti::IsFalseColor()
{
    return m_falseColor;
}

// 0x6B5880
BOOL CGameAnimationTypeMonsterMulti::IsMirroring()
{
    return m_currentBamDirection > m_extendDirectionTest;
}

// 0x6B58A0
void CGameAnimationTypeMonsterMulti::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1322
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE n = 0; n < m_nQuadrants; n++) {
        m_currentVidCell[n].FrameAdvance();
    }
}

// 0x6B5910
void CGameAnimationTypeMonsterMulti::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1166
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE n = 0; n < m_nQuadrants; n++) {
        m_currentVidCell[n].m_nCurrentFrame--;
    }
}

// 0x6B5980
BOOLEAN CGameAnimationTypeMonsterMulti::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();
    resWeapon = "";
    resShield = "";
    resHelmet = "";
    return TRUE;
}

// 0x6B5A10
SHORT CGameAnimationTypeMonsterMulti::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1337
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6B5B80
void CGameAnimationTypeMonsterMulti::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 10336
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint pt;
    m_currentVidCell->GetCurrentCenterPoint(pt, FALSE);
    ptReference = pt;

    for (BYTE quad = 1; quad < m_nQuadrants; quad++) {
        CPoint ptTemp;
        m_currentVidCell[quad].GetCurrentCenterPoint(ptTemp, FALSE);
        ptReference.x = max(ptTemp.x, ptReference.x);
        ptReference.y = max(ptTemp.y, ptReference.y);
    }

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    frameSize.cx += ptReference.x - pt.x;
    frameSize.cy += ptReference.y - pt.y;
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);

    for (BYTE quad = 1; quad < m_nQuadrants; quad++) {
        m_currentVidCell[quad].GetCurrentFrameSize(frameSize, FALSE);

        CPoint ptTemp;
        m_currentVidCell[quad].GetCurrentCenterPoint(pt, FALSE);

        rFx.right = max(frameSize.cx + ptReference.x - ptTemp.x, rFx.right);
        rFx.bottom = max(frameSize.cy + ptReference.y - ptTemp.y, rFx.bottom);
    }
}

// 0x6B5D20
void CGameAnimationTypeMonsterMulti::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6B61E0
const char* CGameAnimationTypeMonsterMulti::GetSndReady()
{
    switch (m_animationID & 0xF00) {
    case 0x000:
        break;
    case 0x100:
    case 0x200:
        return "";
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10500
        UTIL_ASSERT(FALSE);
    }

    char* szTemp = new char[8];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 10507
    UTIL_ASSERT(szTemp != NULL);

    strcpy(szTemp, "WAL_77");

    szTemp[6] = rand() % 2 + 'a';
    if (szTemp[6] == 'b') {
        szTemp[6] = '\0';
    }

    // FIXME: Leaking `szTemp`.
    return szTemp;
}

// 0x6B63C0
SHORT CGameAnimationTypeMonsterMulti::GetCastHeight()
{
    switch (m_animationID & 0xF00) {
    case 0x000:
    case 0x100:
        return 35;
    case 0x200:
        switch (m_animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            return 144;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 10641
            UTIL_ASSERT(FALSE);
        }
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10646
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B6430
void CGameAnimationTypeMonsterMulti::GetCastingOffset(CPoint& ptOffset)
{
    SHORT nDirection = m_currentBamDirection;
    if (nDirection > m_extendDirectionTest) {
        nDirection = 16 - nDirection;
    }

    switch (m_animationID & 0xF00) {
    case 0x000:
    case 0x100:
        break;
    case 0x200:
        switch (m_animationID & 0xF) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            switch (nDirection) {
            case 0:
                ptOffset.x = 12;
                ptOffset.y = 163;
                break;
            case 1:
                ptOffset.x = -96;
                ptOffset.y = 151;
                break;
            case 2:
                ptOffset.x = -180;
                ptOffset.y = 115;
                break;
            case 3:
                ptOffset.x = -225;
                ptOffset.y = 59;
                break;
            case 4:
                ptOffset.x = -233;
                ptOffset.y = 0;
                break;
            case 5:
                ptOffset.x = -212;
                ptOffset.y = -58;
                break;
            case 6:
                ptOffset.x = -159;
                ptOffset.y = -101;
                break;
            case 7:
                ptOffset.x = -93;
                ptOffset.y = -128;
                break;
            case 8:
                ptOffset.x = -13;
                ptOffset.y = -144;
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 10739
                UTIL_ASSERT(FALSE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 10744
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10749
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B65C0
void CGameAnimationTypeMonsterMulti::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 10778
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g2VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g3VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g4VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g5VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g2VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g3VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g4VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g5VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
            }
        } else {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g3VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g4VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g5VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

                m_g1VidCellBase[quad].DeleteResPaletteAffect();
                m_g2VidCellBase[quad].DeleteResPaletteAffect();
                m_g3VidCellBase[quad].DeleteResPaletteAffect();
                m_g4VidCellBase[quad].DeleteResPaletteAffect();
                m_g5VidCellBase[quad].DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellBase[quad].UnsuppressTintAllRanges();
                m_g2VidCellBase[quad].UnsuppressTintAllRanges();
                m_g3VidCellBase[quad].UnsuppressTintAllRanges();
                m_g4VidCellBase[quad].UnsuppressTintAllRanges();
                m_g5VidCellBase[quad].UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10830
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B68C0
void CGameAnimationTypeMonsterMulti::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 10855
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
            m_g1VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g3VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g4VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g5VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            m_g1VidCellBase[quad].DeleteResPaletteAffect();
            m_g2VidCellBase[quad].DeleteResPaletteAffect();
            m_g3VidCellBase[quad].DeleteResPaletteAffect();
            m_g4VidCellBase[quad].DeleteResPaletteAffect();
            m_g5VidCellBase[quad].DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase[quad].UnsuppressTintAllRanges();
            m_g2VidCellBase[quad].UnsuppressTintAllRanges();
            m_g3VidCellBase[quad].UnsuppressTintAllRanges();
            m_g4VidCellBase[quad].UnsuppressTintAllRanges();
            m_g5VidCellBase[quad].UnsuppressTintAllRanges();
        }
    }
}

// 0x6B6A90
void CGameAnimationTypeMonsterMulti::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 10915
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g3VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g4VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g5VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            }

            if (effectType != 0) {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g2VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g3VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g4VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g5VidCellBase[quad].SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g3VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g4VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g5VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellBase[quad].SuppressTint(0);
                    m_g2VidCellBase[quad].SuppressTint(0);
                    m_g3VidCellBase[quad].SuppressTint(0);
                    m_g4VidCellBase[quad].SuppressTint(0);
                    m_g5VidCellBase[quad].SuppressTint(0);
                }
            } else {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].SetTintColor(tintColor);
                    m_g2VidCellBase[quad].SetTintColor(tintColor);
                    m_g3VidCellBase[quad].SetTintColor(tintColor);
                    m_g4VidCellBase[quad].SetTintColor(tintColor);
                    m_g5VidCellBase[quad].SetTintColor(tintColor);
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
        // __LINE__: 10977
        UTIL_ASSERT(FALSE);
    }
}

// 0x6B6E80
void CGameAnimationTypeMonsterMulti::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 11002
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g2VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g3VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g4VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g5VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellBase[quad].SuppressTint(0);
                m_g2VidCellBase[quad].SuppressTint(0);
                m_g3VidCellBase[quad].SuppressTint(0);
                m_g4VidCellBase[quad].SuppressTint(0);
                m_g5VidCellBase[quad].SuppressTint(0);
            }
        } else {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].SetTintColor(tintColor);
                m_g2VidCellBase[quad].SetTintColor(tintColor);
                m_g3VidCellBase[quad].SetTintColor(tintColor);
                m_g4VidCellBase[quad].SetTintColor(tintColor);
                m_g5VidCellBase[quad].SetTintColor(tintColor);
            }
        }
    }
}

// 0x6B70A0
void CGameAnimationTypeMonsterMulti::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 11071
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 11081
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6B7190
void CGameAnimationTypeMonsterMulti::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 11107
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6B9CA0
void CGameAnimationTypeMonsterMulti::GetAnimationResRef(CString& resRef, BYTE range)
{
    if (m_animationID == 0x1201) {
        resRef = "MDR2";
    } else {
        resRef = "";
    }
}

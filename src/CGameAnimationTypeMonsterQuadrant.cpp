#include "CGameAnimationTypeMonsterQuadrant.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6B9CD0
CGameAnimationTypeMonsterQuadrant::CGameAnimationTypeMonsterQuadrant(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    CString v1;
    BYTE quad;

    m_animationID = animationID;
    m_falseColor = TRUE;
    m_nQuadrants = 1;
    m_bCaster = FALSE;
    m_bExtendDir = TRUE;
    m_pathSmooth = FALSE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
    m_extendDirectionTest = CGameSprite::DIR_NNE;

    switch (animationID & 0xF00) {
    case 0x000:
        m_falseColor = FALSE;
        m_bExtendDir = FALSE;
        m_rEllipse.left = -36;
        m_rEllipse.top = -24;
        m_rEllipse.right = 36;
        m_rEllipse.bottom = 24;
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_nQuadrants = 4;
        m_pathSmooth = 1;
        m_nSndFreq = 8;
        m_personalSpace = 5;

        if ((animationID & 0xF) == 1) {
            m_resRef = "MWY2";
        } else {
            m_resRef = "MWYV";
        }

        m_pSndDeath = "FAL_03B";
        break;
    case 0x100:
        m_falseColor = FALSE;
        m_rEllipse.left = -32;
        m_rEllipse.top = -24;
        m_rEllipse.right = 32;
        m_rEllipse.bottom = 24;
        m_colorChunks = -1;
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        m_bCaster = TRUE;
        m_nQuadrants = 4;
        m_nSndFreq = 8;
        m_personalSpace = 7;
        m_resRef = "MTAN";
        m_pSndDeath = "FAL_03B";
        break;
    case 0x200:
        m_colorChunks = -1;
        m_falseColor = FALSE;
        m_bCaster = TRUE;
        m_nQuadrants = 6;
        m_nSndFreq = 8;
        m_pSndDeath = "FAL_03B";
        v1 = "0";
        m_bExtendDir = FALSE;
        m_rEllipse.left = -36;
        m_rEllipse.top = -24;
        m_rEllipse.right = 36;
        m_rEllipse.bottom = 24;
        m_moveScale = 14;
        m_moveScaleCurrent = 14;
        m_personalSpace = 7;
        m_resRef = "MDR1";
        m_extendDirectionTest = CGameSprite::DIR_N;
        m_pathSmooth = TRUE;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 11647
        UTIL_ASSERT(FALSE);
    }

    m_g1VidCellBase = new CVidCell[3 * m_nQuadrants];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 11650
    UTIL_ASSERT(m_g1VidCellBase != NULL);

    m_g2VidCellBase = &(m_g1VidCellBase[m_nQuadrants]);
    m_g3VidCellBase = &(m_g1VidCellBase[2 * m_nQuadrants]);

    for (quad = 0; quad < m_nQuadrants; quad++) {
        CString sSuffix = static_cast<char>(quad + '1');

        m_g1VidCellBase[quad].SetResRef(CResRef(m_resRef + "G1" + v1 + sSuffix), FALSE, TRUE);
        m_g2VidCellBase[quad].SetResRef(CResRef(m_resRef + "G2" + v1 + sSuffix), FALSE, TRUE);
        m_g3VidCellBase[quad].SetResRef(CResRef(m_resRef + "G3" + v1 + sSuffix), FALSE, TRUE);

        m_g1VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g1VidCellBase);
        m_g2VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g2VidCellBase);
        m_g3VidCellBase[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g3VidCellBase);
    }

    m_currentVidCellBase = m_g2VidCellBase;
    m_currentVidCell = m_g2VidCellBase;

    if (m_bExtendDir && !MIRROR_BAM) {
        m_g1VidCellExtend = new CVidCell[3 * m_nQuadrants];

        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 11650
        UTIL_ASSERT(m_g1VidCellExtend != NULL);

        m_g2VidCellExtend = &(m_g1VidCellExtend[m_nQuadrants]);
        m_g3VidCellExtend = &(m_g1VidCellExtend[2 * m_nQuadrants]);

        for (quad = 0; quad < m_nQuadrants; quad++) {
            CString sSuffix = static_cast<char>(quad + '1');

            m_g1VidCellExtend[quad].SetResRef(CResRef(m_resRef + "G1" + v1 + sSuffix + "E"), FALSE, TRUE);
            m_g2VidCellExtend[quad].SetResRef(CResRef(m_resRef + "G2" + v1 + sSuffix + "E"), FALSE, TRUE);
            m_g3VidCellExtend[quad].SetResRef(CResRef(m_resRef + "G3" + v1 + sSuffix + "E"), FALSE, TRUE);

            m_g1VidCellExtend[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g1VidCellExtend);
            m_g2VidCellExtend[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g2VidCellExtend);
            m_g3VidCellExtend[quad].m_cPalette.m_nAUCounterBase = reinterpret_cast<int>(m_g3VidCellExtend);
        }
    }

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        for (quad = 0; quad < m_nQuadrants; quad++) {
            m_g1VidCellBase[quad].SetPalette(m_charPalette);
            m_g2VidCellBase[quad].SetPalette(m_charPalette);
            m_g3VidCellBase[quad].SetPalette(m_charPalette);

            if (m_bExtendDir && !MIRROR_BAM) {
                m_g1VidCellExtend[quad].SetPalette(m_charPalette);
                m_g2VidCellExtend[quad].SetPalette(m_charPalette);
                m_g3VidCellExtend[quad].SetPalette(m_charPalette);
            }
        }
    }

    m_currentBamSequence = 1;

    if (!m_bExtendDir) {
        if (m_falseColor) {
            m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
        } else {
            for (quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].m_bShadowOn = FALSE;
                m_g2VidCellBase[quad].m_bShadowOn = FALSE;
                m_g3VidCellBase[quad].m_bShadowOn = FALSE;

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].m_bShadowOn = FALSE;
                    m_g2VidCellExtend[quad].m_bShadowOn = FALSE;
                    m_g3VidCellExtend[quad].m_bShadowOn = FALSE;
                }
            }
        }
    }

    ChangeDirection(facing);
}

// 0x6BAF00
CGameAnimationTypeMonsterQuadrant::~CGameAnimationTypeMonsterQuadrant()
{
    delete[] m_g1VidCellBase;

    if (m_bExtendDir) {
        if (!MIRROR_BAM) {
            delete[] m_g1VidCellExtend;
        }
    }
}

// 0x6BAC50
BOOL CGameAnimationTypeMonsterQuadrant::GetPathSmooth()
{
    return m_pathSmooth;
}

// 0x6BAC60
BOOL CGameAnimationTypeMonsterQuadrant::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1395
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6BACA0
BOOL CGameAnimationTypeMonsterQuadrant::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1396
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6BACE0
BOOL CGameAnimationTypeMonsterQuadrant::IsFalseColor()
{
    return m_falseColor;
}

// 0x6BACF0
BOOL CGameAnimationTypeMonsterQuadrant::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6BAD20
void CGameAnimationTypeMonsterQuadrant::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1399
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
        m_currentVidCell[quad].FrameAdvance();
    }
}

// 0x6BAD90
void CGameAnimationTypeMonsterQuadrant::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1400
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
        m_currentVidCell[quad].m_nCurrentFrame--;
    }
}

// 0x6BAE00
BOOLEAN CGameAnimationTypeMonsterQuadrant::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();
    resWeapon = "";
    resShield = "";
    resHelmet = "";
    return TRUE;
}

// 0x6BAE90
SHORT CGameAnimationTypeMonsterQuadrant::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1411
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6BAFF0
void CGameAnimationTypeMonsterQuadrant::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    BYTE quad;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 11746
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint pt;
    m_currentVidCell->GetCurrentCenterPoint(pt, FALSE);
    ptReference = pt;

    for (quad = 1; quad < m_nQuadrants; quad++) {
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

    for (quad = 1; quad < m_nQuadrants; quad++) {
        m_currentVidCell[quad].GetCurrentFrameSize(frameSize, FALSE);

        CPoint ptTemp;
        m_currentVidCell[quad].GetCurrentCenterPoint(ptTemp, FALSE);

        rFx.right = max(frameSize.cx + ptReference.x - ptTemp.x, rFx.right);
        rFx.bottom = max(frameSize.cy + ptReference.y - ptTemp.y, rFx.bottom);
    }
}

// 0x6BB190
void CGameAnimationTypeMonsterQuadrant::CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    ptReference.x = 512;
    ptReference.y = 512;

    rFx.left = 0;
    rFx.top = 0;
    rFx.right = 1024;
    rFx.bottom = 1024;
}

// 0x6BB1C0
void CGameAnimationTypeMonsterQuadrant::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if ((!m_bExtendDir || MIRROR_BAM)
        && m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6BB240
void CGameAnimationTypeMonsterQuadrant::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 11859
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    if (m_bExtendDir && !MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell = m_currentVidCellExtend;
    } else {
        m_currentVidCell = m_currentVidCellBase;
    }

    if ((!m_bExtendDir || MIRROR_BAM) && m_currentBamDirection > m_extendDirectionTest) {
        if (m_currentVidCellBase != m_g1VidCellBase || m_currentBamSequence != 0) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_currentVidCell[quad].SequenceSet(16 * m_currentBamSequence + (17 - m_currentBamDirection) % 16);
            }
        } else {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_currentVidCell[quad].SequenceSet(16 * m_currentBamSequence + (16 - m_currentBamDirection) % 16);
            }
        }
    } else {
        for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
            m_currentVidCell[quad].SequenceSet(16 * m_currentBamSequence + m_currentBamDirection);
        }
    }
}

// 0x6BB430
CVidPalette* CGameAnimationTypeMonsterQuadrant::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 11905
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
        // __LINE__: 11920
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6BB4F0
void CGameAnimationTypeMonsterQuadrant::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 11950
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
        // __LINE__: 11967
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BB5D0
const char* CGameAnimationTypeMonsterQuadrant::GetSndReady()
{
    if ((m_animationID & 0xF00) != 0) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 12005
        UTIL_ASSERT(FALSE);
    }

    char* szTemp = new char[8];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 12012
    UTIL_ASSERT(szTemp != NULL);

    strcpy(szTemp, "WAL_77 ");

    szTemp[6] = rand() % 2 + 'a';
    if (szTemp[6] == 'b') {
        szTemp[6] = '\0';
    }

    // FIXME: Leaking `szTemp`.
    return szTemp;
}

// 0x6BB670
const char* CGameAnimationTypeMonsterQuadrant::GetSndWalk(SHORT a1)
{
    if ((m_animationID & 0xF00) == 0) {
        return NULL;
    }

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

// 0x6BB7D0
void CGameAnimationTypeMonsterQuadrant::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 12179
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g2VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);
                m_g3VidCellBase[quad].DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g2VidCellBase[quad].UnsuppressTint(colorRange & 0xF);
                m_g3VidCellBase[quad].UnsuppressTint(colorRange & 0xF);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].DeleteRangeAffects(colorRange & 0xF);
                    m_g2VidCellExtend[quad].DeleteRangeAffects(colorRange & 0xF);
                    m_g3VidCellExtend[quad].DeleteRangeAffects(colorRange & 0xF);

                    m_g1VidCellExtend[quad].UnsuppressTint(colorRange & 0xF);
                    m_g2VidCellExtend[quad].UnsuppressTint(colorRange & 0xF);
                    m_g3VidCellExtend[quad].UnsuppressTint(colorRange & 0xF);
                }
            }
        } else {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g3VidCellBase[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

                m_g1VidCellBase[quad].DeleteResPaletteAffect();
                m_g2VidCellBase[quad].DeleteResPaletteAffect();
                m_g3VidCellBase[quad].DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellBase[quad].UnsuppressTintAllRanges();
                m_g2VidCellBase[quad].UnsuppressTintAllRanges();
                m_g3VidCellBase[quad].UnsuppressTintAllRanges();

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                    m_g2VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                    m_g3VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

                    m_g1VidCellExtend[quad].DeleteResPaletteAffect();
                    m_g2VidCellExtend[quad].DeleteResPaletteAffect();
                    m_g3VidCellExtend[quad].DeleteResPaletteAffect();

                    // NOTE: Uninline.
                    m_g1VidCellExtend[quad].UnsuppressTintAllRanges();
                    m_g2VidCellExtend[quad].UnsuppressTintAllRanges();
                    m_g3VidCellExtend[quad].UnsuppressTintAllRanges();
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
        // __LINE__: 12242
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BBB60
void CGameAnimationTypeMonsterQuadrant::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 12267
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

            m_g1VidCellBase[quad].DeleteResPaletteAffect();
            m_g2VidCellBase[quad].DeleteResPaletteAffect();
            m_g3VidCellBase[quad].DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase[quad].UnsuppressTintAllRanges();
            m_g2VidCellBase[quad].UnsuppressTintAllRanges();
            m_g3VidCellBase[quad].UnsuppressTintAllRanges();

            if (m_bExtendDir && !MIRROR_BAM) {
                m_g1VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g3VidCellExtend[quad].SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

                m_g1VidCellExtend[quad].DeleteResPaletteAffect();
                m_g2VidCellExtend[quad].DeleteResPaletteAffect();
                m_g3VidCellExtend[quad].DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellExtend[quad].UnsuppressTintAllRanges();
                m_g2VidCellExtend[quad].UnsuppressTintAllRanges();
                m_g3VidCellExtend[quad].UnsuppressTintAllRanges();
            }
        }
    }
}

// 0x6BBD80
void CGameAnimationTypeMonsterQuadrant::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 12333
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g3VidCellBase[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                    m_g2VidCellExtend[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                    m_g3VidCellExtend[quad].AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                }
            }

            if (effectType != 0) {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g2VidCellBase[quad].SuppressTint(colorRange & 0xF);
                    m_g3VidCellBase[quad].SuppressTint(colorRange & 0xF);

                    if (m_bExtendDir && !MIRROR_BAM) {
                        m_g1VidCellExtend[quad].SuppressTint(colorRange & 0xF);
                        m_g2VidCellExtend[quad].SuppressTint(colorRange & 0xF);
                        m_g3VidCellExtend[quad].SuppressTint(colorRange & 0xF);
                    }
                }
            }
        } else {
            if (effectType != 0) {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g3VidCellBase[quad].AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellBase[quad].SuppressTint(0);
                    m_g2VidCellBase[quad].SuppressTint(0);
                    m_g3VidCellBase[quad].SuppressTint(0);

                    if (m_bExtendDir && !MIRROR_BAM) {
                        m_g1VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                        m_g2VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                        m_g3VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);

                        m_g1VidCellExtend[quad].SuppressTint(0);
                        m_g2VidCellExtend[quad].SuppressTint(0);
                        m_g3VidCellExtend[quad].SuppressTint(0);
                    }
                }
            } else {
                for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                    m_g1VidCellBase[quad].SetTintColor(tintColor);
                    m_g2VidCellBase[quad].SetTintColor(tintColor);
                    m_g3VidCellBase[quad].SetTintColor(tintColor);

                    if (m_bExtendDir && !MIRROR_BAM) {
                        m_g1VidCellExtend[quad].SetTintColor(tintColor);
                        m_g2VidCellExtend[quad].SetTintColor(tintColor);
                        m_g3VidCellExtend[quad].SetTintColor(tintColor);
                    }
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
        // __LINE__: 12412
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BC220
void CGameAnimationTypeMonsterQuadrant::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 12437
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

                m_g1VidCellBase[quad].SuppressTint(0);
                m_g2VidCellBase[quad].SuppressTint(0);
                m_g3VidCellBase[quad].SuppressTint(0);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g3VidCellExtend[quad].AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellExtend[quad].SuppressTint(0);
                    m_g2VidCellExtend[quad].SuppressTint(0);
                    m_g3VidCellExtend[quad].SuppressTint(0);
                }
            }
        } else {
            for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
                m_g1VidCellBase[quad].SetTintColor(tintColor);
                m_g2VidCellBase[quad].SetTintColor(tintColor);
                m_g3VidCellBase[quad].SetTintColor(tintColor);

                if (m_bExtendDir && !MIRROR_BAM) {
                    m_g1VidCellExtend[quad].SetTintColor(tintColor);
                    m_g2VidCellExtend[quad].SetTintColor(tintColor);
                    m_g3VidCellExtend[quad].SetTintColor(tintColor);
                }
            }
        }
    }
}

// 0x6BC4A0
void CGameAnimationTypeMonsterQuadrant::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 12515
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 12525
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6BC590
void CGameAnimationTypeMonsterQuadrant::SetColorRangeAll(BYTE rangeValue)
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

// 0x6BC970
SHORT CGameAnimationTypeMonsterQuadrant::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 3;
        break;
    case 2:
        if (m_bCaster) {
            m_currentVidCellBase = m_g3VidCellBase;
            m_currentVidCellExtend = m_g3VidCellExtend;
            m_currentBamSequence = 2;
        } else {
            m_currentVidCellBase = m_g2VidCellBase;
            m_currentVidCellExtend = m_g2VidCellExtend;
            m_currentBamSequence = 1;
        }
        break;
    case 3:
    case 7:
        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 4:
        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 2;
        break;
    case 6:
        if (m_currentBamSequence != 0 || m_currentVidCellBase != m_g2VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 8:
    case 14:
    case 15:
        nSequence = 7;

        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 1;
        break;
    case 9:
        m_currentVidCellBase = m_g2VidCellBase;
        m_currentVidCellExtend = m_g2VidCellExtend;
        m_currentBamSequence = 4;
        break;
    case 10:
        m_currentVidCellBase = m_g1VidCellBase;
        m_currentVidCellExtend = m_g1VidCellExtend;
        m_currentBamSequence = 0;
        break;
    case 11:
        m_currentVidCellBase = m_g3VidCellBase;
        m_currentVidCellExtend = m_g3VidCellExtend;
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 12:
        m_currentVidCellBase = m_g3VidCellBase;
        m_currentVidCellExtend = m_g3VidCellExtend;
        m_currentBamSequence = 1;
        nSequence = 0;
        break;
    case 13:
        m_currentVidCellBase = m_g3VidCellBase;
        m_currentVidCellExtend = m_g3VidCellExtend;

        if (m_bCaster) {
            m_currentBamSequence = 0;
        } else {
            m_currentBamDirection = 2;
        }

        nSequence = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 12798
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

    for (BYTE quad = 0; quad < m_nQuadrants; quad++) {
        m_currentVidCell[quad].FrameSet(nFrame);
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

// 0x6C2D70
BOOLEAN CGameAnimationTypeMonsterQuadrant::GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame)
{
    nSequence = m_currentVidCell->m_nCurrentSequence;
    nFrame = m_currentVidCell->m_nCurrentFrame;
    return TRUE;
}

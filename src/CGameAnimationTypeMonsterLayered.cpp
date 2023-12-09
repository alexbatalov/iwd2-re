#include "CGameAnimationTypeMonsterLayered.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6BCCA0
CGameAnimationTypeMonsterLayered::CGameAnimationTypeMonsterLayered(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
    , m_weaponPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_nMeleeWeaponReady = 0;
    m_renderWeapons = TRUE;
    m_weaponLeftHand = FALSE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 7;
        m_resRef = "MGNL";
        m_weaponResRef[0] = "S1";
        m_weaponResRef[1] = "HB";
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_pSndDeath = "FAL_03B";
        break;
    case 0x100:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 7;
        m_resRef = "MHOB";
        m_weaponResRef[0] = "S1";
        m_weaponResRef[1] = "BW";
        break;
    case 0x200:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 9;
        m_resRef = "MKOB";
        m_weaponResRef[0] = "SS";
        m_weaponResRef[1] = "BW";
        m_pSndDeath = "FAL_01B";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 12891
        UTIL_ASSERT(m_currentVidCell != NULL);
    }

    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE, TRUE);

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE, TRUE);
        m_g2VidCellExtend.SetResRef(CResRef(m_resRef + "G2E"), FALSE, TRUE, TRUE);
    }

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
    }

    m_g1VidCellBase.SetPalette(m_charPalette);
    m_g2VidCellBase.SetPalette(m_charPalette);

    m_currentVidCellBase = &m_g1VidCellBase;

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetPalette(m_charPalette);
        m_g2VidCellExtend.SetPalette(m_charPalette);
    }

    m_currentVidCell = m_currentVidCellBase;
    m_currentVidCellExtend = &m_g1VidCellExtend;

    m_g1VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_g2VidCellWeaponBase.SetPalette(m_weaponPalette);

    m_currentVidCellWeaponBase = NULL;

    if (!MIRROR_BAM) {
        m_g1VidCellWeaponExtend.SetPalette(m_weaponPalette);
        m_g2VidCellWeaponExtend.SetPalette(m_weaponPalette);
    }

    m_currentVidCellWeaponExtend = NULL;
    m_currentVidCellWeapon = m_currentVidCellWeaponBase;

    m_currentBamSequence = 1;

    if (MIRROR_BAM) {
        m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
    }

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6BD830
CGameAnimationTypeMonsterLayered::~CGameAnimationTypeMonsterLayered()
{
}

// 0x6BD570
BOOL CGameAnimationTypeMonsterLayered::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1472
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6BD5B0
BOOL CGameAnimationTypeMonsterLayered::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1473
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6BD5F0
BOOL CGameAnimationTypeMonsterLayered::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6BD620
void CGameAnimationTypeMonsterLayered::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1475
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->FrameAdvance();
    }
}

// 0x6BD660
void CGameAnimationTypeMonsterLayered::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1476
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }
}

// 0x6BD6B0
BOOLEAN CGameAnimationTypeMonsterLayered::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();

    if (m_currentVidCellWeapon != NULL) {
        resWeapon = m_currentVidCellWeapon->GetResRef().GetResRefStr();
    } else {
        resWeapon = "";
    }

    resShield = "";
    resHelmet = "";
    return TRUE;
}

// 0x6BD7C0
SHORT CGameAnimationTypeMonsterLayered::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1487
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6BD950
void CGameAnimationTypeMonsterLayered::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 12951
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptChar;
    m_currentVidCell->GetCurrentCenterPoint(ptChar, FALSE);
    ptReference = ptChar;

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    if (m_renderWeapons && m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
        CPoint ptWeapon;
        m_currentVidCellWeapon->GetCurrentCenterPoint(ptWeapon, FALSE);

        ptReference.x = max(ptWeapon.x, ptReference.x);
        ptReference.y = max(ptWeapon.y, ptReference.y);

        frameSize.cx += ptReference.x - ptChar.x;
        frameSize.cy += ptReference.y - ptChar.y;
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);

        m_currentVidCellWeapon->GetCurrentFrameSize(frameSize, FALSE);

        rFx.right = max(frameSize.cx + ptReference.x - ptWeapon.x, rFx.right);
        rFx.bottom = max(frameSize.cy + ptReference.y - ptWeapon.y, rFx.bottom);
    } else {
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
    }
}

// 0x6BDAB0
void CGameAnimationTypeMonsterLayered::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6BDB20
void CGameAnimationTypeMonsterLayered::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13038
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

    if (m_currentVidCellWeapon != NULL) {
        if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellWeapon = m_currentVidCellWeaponExtend;
        } else {
            m_currentVidCellWeapon = m_currentVidCellWeaponBase;
        }

        if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellWeapon->SequenceSet(8 * m_currentBamDirection + ((17 - m_currentBamDirection) % 16) / 2);
        } else {
            m_currentVidCellWeapon->SequenceSet(8 * m_currentBamDirection + m_currentBamDirection / 2);
        }
    }
}

// 0x6BDCB0
void CGameAnimationTypeMonsterLayered::EquipWeapon(const CString& resRef, BYTE* colorRangeValues, DWORD itemFlags, const WORD* pAttackProb)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13086
    UTIL_ASSERT(pAttackProb != NULL);

    m_weaponLeftHand = FALSE;

    ClearColorEffects(21);
    ClearColorEffects(20);
    ClearColorEffects(16);

    if (resRef != "") {
        BYTE cnt = 0;
        while (cnt < 2) {
            if (m_weaponResRef[cnt] == resRef) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 13113
                UTIL_ASSERT(colorRangeValues != NULL);

                if (m_currentVidCellBase == &m_g1VidCellBase) {
                    m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
                } else {
                    m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
                }

                m_nMeleeWeaponReady = cnt;

                if ((itemFlags & 0x80) != 0) {
                    m_weaponLeftHand = TRUE;
                }

                m_g1VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef + "G1"), FALSE, TRUE, TRUE);
                m_g2VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef + "G2"), FALSE, TRUE, TRUE);

                if (!MIRROR_BAM) {
                    m_g1VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef + "G1E"), FALSE, TRUE, TRUE);
                    m_g2VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef + "G2E"), FALSE, TRUE, TRUE);
                }

                break;
            }
            cnt++;
        }

        if (cnt != 2) {
            for (BYTE colorRange = 0; colorRange < 7; colorRange++) {
                m_weaponPalette.SetRange(colorRange,
                    colorRangeValues[colorRange],
                    *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            }

            if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
                m_currentVidCellWeapon = m_currentVidCellWeaponExtend;
            } else {
                m_currentVidCellWeapon = m_currentVidCellWeaponBase;
            }

            SHORT nSequence;
            if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
                nSequence = 8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2;
            } else {
                nSequence = 8 * m_currentBamSequence + m_currentBamDirection / 2;
            }

            m_currentVidCellWeapon->SequenceSet(nSequence);
            m_currentVidCellWeapon->FrameSet(m_currentVidCell->GetCurrentFrameId());
        } else {
            m_nMeleeWeaponReady = 0;

            m_currentVidCellWeaponBase = NULL;
            m_g1VidCellWeaponBase.CancelRequest();
            m_g2VidCellWeaponBase.CancelRequest();

            m_currentVidCellWeaponExtend = NULL;
            m_g1VidCellWeaponExtend.CancelRequest();
            m_g2VidCellWeaponExtend.CancelRequest();

            m_currentVidCellWeapon = NULL;
        }
    } else {
        m_nMeleeWeaponReady = 0;

        m_currentVidCellWeaponBase = NULL;
        m_g1VidCellWeaponBase.CancelRequest();
        m_g2VidCellWeaponBase.CancelRequest();

        m_currentVidCellWeaponExtend = NULL;
        m_g1VidCellWeaponExtend.CancelRequest();
        m_g2VidCellWeaponExtend.CancelRequest();

        m_currentVidCellWeapon = NULL;
    }
}

// 0x6BE260
CVidPalette* CGameAnimationTypeMonsterLayered::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13189
        UTIL_ASSERT(m_currentVidCell != NULL);

        return &m_charPalette;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13203
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6BE310
void CGameAnimationTypeMonsterLayered::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13233
        UTIL_ASSERT(m_currentVidCell != NULL);

        resRef = m_resRef;
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13259
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BE3E0
char* CGameAnimationTypeMonsterLayered::GetSndWalk(SHORT tableIndex)
{
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

    char* szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13346
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

// 0x6BE540
void CGameAnimationTypeMonsterLayered::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13420
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
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
        break;
    case 0x10:
        m_g1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_g2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);

        m_g1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_g2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);

        if (!MIRROR_BAM) {
            m_g1VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_g2VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_g2VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13456
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BE6C0
void CGameAnimationTypeMonsterLayered::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13481
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        ClearColorEffects(colorRange);
    }
}

// 0x6BE720
void CGameAnimationTypeMonsterLayered::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13513
        UTIL_ASSERT(m_currentVidCell != NULL);

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
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            m_g1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_g2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_g2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_g2VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                    m_g2VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                }
            }
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13565
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BE940
void CGameAnimationTypeMonsterLayered::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13590
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        SetColorEffect(effectType, colorRange, tintColor, periodLength);
    }

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange | 0x10, tintColor, periodLength);
        }
    }
}

// 0x6BE9F0
void CGameAnimationTypeMonsterLayered::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13631
        UTIL_ASSERT(m_currentVidCell != NULL);

        m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_weaponPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 13648
        UTIL_ASSERT(FALSE);
    }
}

// 0x6BEB20
void CGameAnimationTypeMonsterLayered::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13675
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        SetColorRange(colorRange, rangeValue);
    }

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange | 0x10, rangeValue);
        }
    }
}

// 0x6BEBB0
void CGameAnimationTypeMonsterLayered::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13707
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13708
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (MIRROR_BAM) {
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
    } else {
        dwRenderFlags |= 0x4;

        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;

        if (transparency) {
            dwRenderFlags |= 0x2;
        }
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        m_currentVidCell->SetTintColor(rgbTintColor);

        if (m_renderWeapons) {
            if (m_currentVidCellWeapon != NULL
                && m_currentVidCellWeapon->GetResRef().IsValid()) {
                m_currentVidCellWeapon->SetTintColor(rgbTintColor);
            }
        }

        SHORT nDirection;
        if (MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
            nDirection = (16 - m_currentBamDirection) % 16;
        } else {
            nDirection = m_currentBamDirection;
        }

        switch (nDirection) {
        case 0:
        case 1:
        case 2:
            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);

            if (m_renderWeapons) {
                if (m_currentVidCellWeapon != NULL
                    && m_currentVidCellWeapon->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellWeapon,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }
            }

            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (m_renderWeapons) {
                if (!m_weaponLeftHand) {
                    if (m_currentVidCellWeapon != NULL
                        && m_currentVidCellWeapon->GetResRef().IsValid()) {
                        pInfinity->FXRender(m_currentVidCellWeapon,
                            ptReference.x,
                            ptReference.y,
                            dwRenderFlags,
                            transparency);
                    }
                }
            }

            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);

            if (m_renderWeapons) {
                if (m_weaponLeftHand) {
                    if (m_currentVidCellWeapon != NULL
                        && m_currentVidCellWeapon->GetResRef().IsValid()) {
                        pInfinity->FXRender(m_currentVidCellWeapon,
                            ptReference.x,
                            ptReference.y,
                            dwRenderFlags,
                            transparency);
                    }
                }
            }

            break;
        case 8:
            if (m_renderWeapons) {
                if (m_currentVidCellWeapon != NULL
                    && m_currentVidCellWeapon->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellWeapon,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }
            }

            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);

            break;
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            if (m_renderWeapons) {
                if (m_weaponLeftHand) {
                    if (m_currentVidCellWeapon != NULL
                        && m_currentVidCellWeapon->GetResRef().IsValid()) {
                        pInfinity->FXRender(m_currentVidCellWeapon,
                            ptReference.x,
                            ptReference.y,
                            dwRenderFlags,
                            transparency);
                    }
                }
            }

            pInfinity->FXRender(m_currentVidCell,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                transparency);

            if (m_renderWeapons) {
                if (!m_weaponLeftHand) {
                    if (m_currentVidCellWeapon != NULL
                        && m_currentVidCellWeapon->GetResRef().IsValid()) {
                        pInfinity->FXRender(m_currentVidCellWeapon,
                            ptReference.x,
                            ptReference.y,
                            dwRenderFlags,
                            transparency);
                    }
                }
            }

            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 13810
            UTIL_ASSERT(FALSE);
        }

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

// 0x6BF0F0
SHORT CGameAnimationTypeMonsterLayered::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    m_renderWeapons = TRUE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_renderWeapons = FALSE;
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

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

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 1;
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 3;
        break;
    case 6:
        if (m_currentBamSequence != 2 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 2;
        break;
    case 8:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        m_currentBamSequence = 2;
        break;
    case 9:
        m_renderWeapons = FALSE;
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 5;
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentVidCellExtend = &m_g1VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 0;
        break;
    case 11:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        if (m_nMeleeWeaponReady != 0) {
            m_currentBamSequence = 2;
        } else {
            m_currentBamSequence = 0;
        }

        nSequence = 0;
        break;
    case 12:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        if (m_nMeleeWeaponReady != 0) {
            m_currentBamSequence = 2;
        } else {
            m_currentBamSequence = 1;
        }

        nSequence = 0;
        break;
    case 13:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        if (m_nMeleeWeaponReady != 0) {
            m_currentBamSequence = 2;
        } else {
            m_currentBamSequence = rand() % 2;
        }

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

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g1VidCellWeaponExtend;
        }

        m_currentBamSequence = 1;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 14024
        UTIL_ASSERT(FALSE);
    }

    ChangeDirection(m_currentBamDirection);

    SHORT nFrame = 0;
    if (bRandomFrame) {
        SHORT nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            nFrame = rand() % nSequenceLength;
        }
    }
    m_currentVidCell->FrameSet(nFrame);

    if (m_renderWeapons) {
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_currentVidCellWeapon->FrameSet(nFrame);
        }
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

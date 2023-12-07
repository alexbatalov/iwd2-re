#include "CGameAnimationTypeMonsterLayeredSpell.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6BF560
CGameAnimationTypeMonsterLayeredSpell::CGameAnimationTypeMonsterLayeredSpell(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
    , m_weaponPalette(CVidPalette::TYPE_RANGE)
{
    m_falseColor = TRUE;
    m_renderWeapons = TRUE;
    m_animationID = animationID;
    m_weaponLeftHand = FALSE;
    m_bInvulnerable = FALSE;
    m_bDualAttack = FALSE;
    m_nSndFreq = -1;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID) {
    case 0x000:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 5;
        m_resRef = "MSIR";
        m_weaponResRef[0] = "";
        m_weaponResRef[1] = "BW";
        break;
    case 0x100:
        m_bInvulnerable = 1;
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_resRef = "UVOL";
        m_falseColor = 0;
        m_nSndFreq = 5;
        m_weaponResRef[0] = "MS";
        m_weaponResRef[1] = "";
        break;
    case 0x200:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_resRef = "MOGM";
        m_bDualAttack = 1;
        m_nSndFreq = 7;
        m_weaponResRef[0] = "S1";
        m_weaponResRef[1] = "";
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";
        break;
    case 0x300:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_resRef = "MDKN";
        m_falseColor = 0;
        m_bDualAttack = 1;
        m_nSndFreq = 7;
        m_weaponResRef[0] = "";
        m_weaponResRef[1] = "";
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_personalSpace = 5;
        m_pSndDeath = "FAL_03B";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 14138
        UTIL_ASSERT(m_currentVidCell != NULL);
    }

    m_g1VidCellBase.SetResRef(CResRef(m_resRef + "G1"), FALSE, TRUE, TRUE);
    m_g2VidCellBase.SetResRef(CResRef(m_resRef + "G2"), FALSE, TRUE, TRUE);

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + "G1E"), FALSE, TRUE, TRUE);
        m_g2VidCellExtend.SetResRef(CResRef(m_resRef + "G2E"), FALSE, TRUE, TRUE);
    }

    m_currentVidCellBase = &m_g1VidCellBase;

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

    m_currentVidCell = m_currentVidCellBase;
    m_currentVidCellExtend = &m_g1VidCellExtend;

    m_currentVidCellWeaponBase = NULL;

    if (m_falseColor) {
        m_g1VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_g2VidCellWeaponBase.SetPalette(m_weaponPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_g2VidCellWeaponExtend.SetPalette(m_weaponPalette);
        }
    }

    m_currentVidCellWeaponExtend = NULL;
    m_currentVidCellWeapon = m_currentVidCellWeaponBase;

    m_currentBamSequence = 2;

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

// 0x6C00D0
CGameAnimationTypeMonsterLayeredSpell::~CGameAnimationTypeMonsterLayeredSpell()
{
    // TODO: Incomplete.
}

// 0x6BFF00
BOOL CGameAnimationTypeMonsterLayeredSpell::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1548
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6BFF40
BOOL CGameAnimationTypeMonsterLayeredSpell::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1549
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6BFF80
BOOL CGameAnimationTypeMonsterLayeredSpell::IsFalseColor()
{
    return m_falseColor;
}

// 0x6BFF90
BOOL CGameAnimationTypeMonsterLayeredSpell::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6BFFC0
BOOL CGameAnimationTypeMonsterLayeredSpell::IsInvulnerable()
{
    return m_bInvulnerable;
}

// 0x6BFFD0
void CGameAnimationTypeMonsterLayeredSpell::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1553
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->FrameAdvance();
    }
}

// 0x6C0010
void CGameAnimationTypeMonsterLayeredSpell::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1554
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }
}

// 0x6C0060
SHORT CGameAnimationTypeMonsterLayeredSpell::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1563
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6C01F0
void CGameAnimationTypeMonsterLayeredSpell::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 14214
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

// 0x6C0350
void CGameAnimationTypeMonsterLayeredSpell::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6C03C0
void CGameAnimationTypeMonsterLayeredSpell::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 14301
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

// 0x6C0B00
char* CGameAnimationTypeMonsterLayeredSpell::GetSndWalk(SHORT tableIndex)
{
    if ((m_animationID & 0xF00) == 0x300) {
        return NULL;
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

    char* szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 14514
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

// 0x6C0C70
void CGameAnimationTypeMonsterLayeredSpell::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 14642
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

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

            m_g1VidCellBase.UnsuppressTintAllRanges();
            m_g2VidCellBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteResPaletteAffect();
                m_g2VidCellExtend.DeleteResPaletteAffect();

                m_g1VidCellExtend.UnsuppressTintAllRanges();
                m_g2VidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
        if (m_falseColor) {
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
        } else {
            m_g1VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellWeaponExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_g2VidCellWeaponExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_g1VidCellWeaponBase.DeleteResPaletteAffect();
            m_g2VidCellWeaponBase.DeleteResPaletteAffect();

            m_g1VidCellWeaponBase.UnsuppressTintAllRanges();
            m_g2VidCellWeaponBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellWeaponExtend.DeleteResPaletteAffect();
                m_g2VidCellWeaponExtend.DeleteResPaletteAffect();

                m_g1VidCellWeaponExtend.UnsuppressTintAllRanges();
                m_g2VidCellWeaponExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 14726
        UTIL_ASSERT(FALSE);
    }
}

// 0x6C0FC0
void CGameAnimationTypeMonsterLayeredSpell::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 13481
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
            ClearColorEffects(colorRange | 0x10);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        m_g1VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g2VidCellWeaponBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            m_g1VidCellWeaponExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g2VidCellWeaponExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_g2VidCellBase.DeleteResPaletteAffect();

        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_g2VidCellBase.UnsuppressTintAllRanges();

        m_g1VidCellWeaponBase.DeleteResPaletteAffect();
        m_g2VidCellWeaponBase.DeleteResPaletteAffect();

        m_g1VidCellWeaponBase.UnsuppressTintAllRanges();
        m_g2VidCellWeaponBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellWeaponExtend.DeleteResPaletteAffect();
            m_g2VidCellWeaponExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellWeaponExtend.UnsuppressTintAllRanges();
            m_g2VidCellWeaponExtend.UnsuppressTintAllRanges();
        }
    }
}

// 0x6C11A0
void CGameAnimationTypeMonsterLayeredSpell::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 14815
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
        if (m_currentVidCellWeapon != NULL) {
            if (m_falseColor) {
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
            } else {
                if (effectType != 0) {
                    m_g1VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_g2VidCellWeaponBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellWeaponBase.SuppressTint(0);
                    m_g2VidCellWeaponBase.SuppressTint(0);

                    if (!MIRROR_BAM) {
                        m_g1VidCellWeaponExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                        m_g2VidCellWeaponExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                        m_g1VidCellWeaponExtend.SuppressTint(0);
                        m_g2VidCellWeaponExtend.SuppressTint(0);
                    }
                } else {
                    m_g1VidCellWeaponBase.SetTintColor(tintColor);
                    m_g2VidCellWeaponBase.SetTintColor(tintColor);

                    if (!MIRROR_BAM) {
                        m_g1VidCellWeaponExtend.SetTintColor(tintColor);
                        m_g2VidCellWeaponExtend.SetTintColor(tintColor);
                    }
                }
            }
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 14924
        UTIL_ASSERT(FALSE);
    }
}

// 0x6C15A0
void CGameAnimationTypeMonsterLayeredSpell::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 14949
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

// 0x6C17E0
void CGameAnimationTypeMonsterLayeredSpell::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 15049
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
            if (m_currentVidCellWeapon != NULL) {
                m_weaponPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            }
            break;
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 15063
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6C1910
void CGameAnimationTypeMonsterLayeredSpell::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 15091
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }

        if (m_currentVidCellWeapon != NULL) {
            for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
                SetColorRange(colorRange | 0x10, rangeValue);
            }
        }
    }
}

// 0x6C1EE0
SHORT CGameAnimationTypeMonsterLayeredSpell::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    if (m_bDualAttack && nSequence == 8) {
        nSequence = 7;
    }

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
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        m_currentBamSequence = 1;
        break;
    case 3:
    case 7:
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
    case 12:
    case 13:
        m_currentVidCellBase = &m_g2VidCellBase;
        m_currentVidCellExtend = &m_g2VidCellExtend;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g2VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_g2VidCellWeaponExtend;
        }

        if (rand() % 2 == 0) {
            m_currentBamSequence = 2;
        } else {
            m_currentBamSequence = 0;
        }

        nSequence = 0;
        break;
    case 14:
    case 15:
        nSequence = 7;

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
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 15416
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

// 0x6C22F0
void CGameAnimationTypeMonsterLayeredSpell::GetAnimationResRef(CString& resRef, BYTE range)
{
    if (m_animationID == 0x2300) {
        resRef = "MDKN";
    } else {
        resRef = "";
    }
}

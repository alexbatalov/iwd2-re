#include "CGameAnimationTypeCharacter.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6C40B0
CGameAnimationTypeCharacter::CGameAnimationTypeCharacter(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    // TODO: Incomplete.
}

// 0x6C5D70
CGameAnimationTypeCharacter::~CGameAnimationTypeCharacter()
{
}

// 0x6C59F0
BOOLEAN CGameAnimationTypeCharacter::CanLieDown()
{
    return m_bCanLieDown;
}

// 0x6C5A00
BOOLEAN CGameAnimationTypeCharacter::DetectedByInfravision()
{
    return m_bDetectedByInfravision;
}

// 0x6C5A10
BOOL CGameAnimationTypeCharacter::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1846
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6C5A50
BOOL CGameAnimationTypeCharacter::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1847
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6C5A90
BOOL CGameAnimationTypeCharacter::IsFalseColor()
{
    return m_falseColor;
}

// 0x6C5AA0
BOOL CGameAnimationTypeCharacter::IsInvulnerable()
{
    return m_bInvulnerable;
}

// 0x6C5AB0
BOOL CGameAnimationTypeCharacter::IsMirroring()
{
    return m_currentBamDirection > m_extendDirectionTest;
}

// 0x6C5AD0
BOOLEAN CGameAnimationTypeCharacter::GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame)
{
    nSequence = m_currentVidCell->m_nCurrentSequence;
    nFrame = m_currentVidCell->m_nCurrentFrame;
    return TRUE;
}

// 0x6C5B00
BOOLEAN CGameAnimationTypeCharacter::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    resBody = m_currentVidCell->GetResRef().GetResRefStr();

    if (m_currentVidCellWeapon != NULL) {
        resWeapon = m_currentVidCellWeapon->GetResRef().GetResRefStr();
    } else {
        resWeapon = "";
    }

    if (m_currentVidCellShield != NULL) {
        resShield = m_currentVidCellShield->GetResRef().GetResRefStr();
    } else {
        resShield = "";
    }

    if (m_currentVidCellHelmet != NULL) {
        resHelmet = m_currentVidCellHelmet->GetResRef().GetResRefStr();
    } else {
        resHelmet = "";
    }

    return TRUE;
}

// 0x6C5D00
SHORT CGameAnimationTypeCharacter::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 1866
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6C62C0
void CGameAnimationTypeCharacter::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6CBD40
CVidPalette* CGameAnimationTypeCharacter::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 19185
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (!m_falseColor) {
            return &m_charPalette;
        }

        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            return &m_weaponPalette;
        }
        break;
    case 0x20:
        if (m_currentVidCellShield != NULL) {
            return &m_shieldPalette;
        }
        break;
    case 0x30:
        if (m_bEquipHelmet && m_currentVidCellHelmet != NULL) {
            return &m_helmetPalette;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 19211
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6CC490
void CGameAnimationTypeCharacter::IncrementFrame()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19630
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->FrameAdvance();
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield->FrameAdvance();
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellHelmet->FrameAdvance();
    }
}

// 0x6CC4F0
void CGameAnimationTypeCharacter::DecrementFrame()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19662
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield->m_nCurrentFrame--;
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellHelmet->m_nCurrentFrame--;
    }
}

// 0x6CC560
void CGameAnimationTypeCharacter::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19694
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellBase.UnsuppressTint(colorRange & 0xF);
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            m_g1VidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();
        }
        break;
    case 0x10:
        m_g1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);

        m_g1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);

        break;
    case 0x20:
        m_g1VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a1VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);

        m_g1VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a1VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellShieldBase.UnsuppressTint(colorRange & 0xF);

        break;
    case 0x30:
        if (m_bEquipHelmet) {
            m_g1VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 19769
        UTIL_ASSERT(FALSE);
    }
}

// 0x6CC910
void CGameAnimationTypeCharacter::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19694
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_caVidCellBase.DeleteResPaletteAffect();
        m_a1VidCellBase.DeleteResPaletteAffect();
        m_a2VidCellBase.DeleteResPaletteAffect();
        m_a3VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_caVidCellBase.UnsuppressTintAllRanges();
        m_a1VidCellBase.UnsuppressTintAllRanges();
        m_a2VidCellBase.UnsuppressTintAllRanges();
        m_a3VidCellBase.UnsuppressTintAllRanges();
    }

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        ClearColorEffects(colorRange | 0x10);
        ClearColorEffects(colorRange | 0x20);

        if (m_bEquipHelmet) {
            ClearColorEffects(colorRange | 0x30);
        }
    }
}

// 0x6CCAB0
void CGameAnimationTypeCharacter::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19850
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
                m_caVidCellBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellBase.SuppressTint(colorRange & 0xF);
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellBase.SuppressTint(0);
                m_caVidCellBase.SuppressTint(0);
                m_a1VidCellBase.SuppressTint(0);
                m_a2VidCellBase.SuppressTint(0);
                m_a3VidCellBase.SuppressTint(0);
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
                m_caVidCellBase.SetTintColor(tintColor);
                m_a1VidCellBase.SetTintColor(tintColor);
                m_a2VidCellBase.SetTintColor(tintColor);
                m_a3VidCellBase.SetTintColor(tintColor);
            }
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            m_g1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            }
        }
        break;
    case 0x20:
        if (m_currentVidCellShield != NULL) {
            m_g1VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellShieldBase.SuppressTint(colorRange & 0xF);
            }
        }
        break;
    case 0x30:
        if (m_bEquipHelmet && m_currentVidCellHelmet != NULL) {
            m_g1VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_caVidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellHelmetBase.SuppressTint(colorRange & 0xF);
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 19952
        UTIL_ASSERT(FALSE);
    }
}

// 0x6CCF80
void CGameAnimationTypeCharacter::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19977
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_g1VidCellBase.SuppressTint(0);
            m_caVidCellBase.SuppressTint(0);
            m_a1VidCellBase.SuppressTint(0);
            m_a2VidCellBase.SuppressTint(0);
            m_a3VidCellBase.SuppressTint(0);
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
            m_caVidCellBase.SetTintColor(tintColor);
            m_a1VidCellBase.SetTintColor(tintColor);
            m_a2VidCellBase.SetTintColor(tintColor);
            m_a3VidCellBase.SetTintColor(tintColor);
        }
    }

    if (m_currentVidCellWeapon != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange | 0x10, tintColor, periodLength);
        }
    }

    if (m_currentVidCellShield != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange | 0x20, tintColor, periodLength);
        }
    }

    if (m_currentVidCellHelmet != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange | 0x30, tintColor, periodLength);
        }
    }
}

// 0x6CD160
void CGameAnimationTypeCharacter::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20052
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL) {
            m_weaponPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    case 0x20:
        if (m_currentVidCellShield != NULL) {
            m_shieldPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    case 0x30:
        if (m_bEquipHelmet && m_currentVidCellHelmet != NULL) {
            m_helmetPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20081
        UTIL_ASSERT(FALSE);
    }
}

// 0x6CD320
void CGameAnimationTypeCharacter::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 20108
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }

    if (m_currentVidCellWeapon != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange | 0x10, rangeValue);
        }
    }

    if (m_currentVidCellShield != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange | 0x20, rangeValue);
        }
    }

    if (m_currentVidCellHelmet != NULL) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange | 0x30, rangeValue);
        }
    }
}

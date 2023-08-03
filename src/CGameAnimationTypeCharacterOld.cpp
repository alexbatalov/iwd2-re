#include "CGameAnimationTypeCharacterOld.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6D0520
CGameAnimationTypeCharacterOld::CGameAnimationTypeCharacterOld(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
    , m_weaponPalette(CVidPalette::TYPE_RANGE)
    , m_shieldPalette(CVidPalette::TYPE_RANGE)
    , m_helmetPalette(CVidPalette::TYPE_RANGE)
{
    m_animationID = animationID;
    m_falseColor = TRUE;
    m_shadowResRef = "CSHD";
    m_moveScale = 9;
    m_moveScaleCurrent = 9;
    m_renderWeapons = TRUE;
    m_renderHelmet = TRUE;
    m_bEquipHelmet = TRUE;
    m_weaponLeftHand = FALSE;
    m_armorCode = '1';
    m_bDetectedByInfravision = TRUE;
    m_bInvulnerable = FALSE;
    m_bCanLieDown = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF) {
    case 0:
    case 1:
    case 5:
        m_nSndFreq = 5;
        break;
    default:
        m_nSndFreq = 4;
        m_pSndDeath = "FAL_01B";
        break;
    }

    switch (animationID & 0xF00) {
    case 0x000:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20812
        UTIL_ASSERT_MSG(FALSE, "Old animation code");
    case 0x100:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20866
        UTIL_ASSERT_MSG(FALSE, "Old animation code");
    case 0x200:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20911
        UTIL_ASSERT_MSG(FALSE, "Old animation code");
    case 0x300:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20952
        UTIL_ASSERT_MSG(FALSE, "Old animation code");
    case 0x400:
        m_armorMaxCode = '1';
        switch (animationID & 0xF) {
        case 0:
            m_resRef = "UDRZ";
            m_heightCodeHelmet = "WPM";
            m_heightCode = m_heightCodeHelmet;
            m_shadowResRef = "CSHD";
            m_nSndFreq = 5;
            break;
        case 1:
            m_falseColor = FALSE;
            m_bEquipHelmet = FALSE;
            m_resRef = "UELM";
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 4;
            break;
        case 2:
            m_bEquipHelmet = FALSE;
            m_resRef = "CMNK";
            m_heightCodeHelmet = "WPM";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 5;
            break;
        case 3:
            m_colorChunks = -1;
            m_resRef = "MSKL";
            m_heightCodeHelmet = "WPM";
            m_heightCode = m_heightCodeHelmet;
            m_colorBlood = 37;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 5;
            break;
        case 4:
            m_colorChunks = -1;
            m_falseColor = FALSE;
            m_bEquipHelmet = FALSE;
            m_bCanLieDown = FALSE;
            m_resRef = "USAR";
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_shadowResRef = "SSHD";
            m_nSndFreq = 5;
            break;
        case 5:
            m_colorChunks = -1;
            m_resRef = "MDGU";
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_colorBlood = 34;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 5;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 21059
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 21064
        UTIL_ASSERT(FALSE);
    }

    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1"), FALSE, TRUE);
    m_w2VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "W2"), FALSE, TRUE);
    m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA"), FALSE, TRUE);
    m_a1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A1"), FALSE, TRUE);
    m_a2VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A3"), FALSE, TRUE);
    m_a3VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A5"), FALSE, TRUE);

    if (!MIRROR_BAM) {
        m_g1VidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "G1E"), FALSE, TRUE);
        m_w2VidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "W2E"), FALSE, TRUE);
        m_caVidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "CAE"), FALSE, TRUE);
        m_a1VidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A1E"), FALSE, TRUE);
        m_a2VidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A3E"), FALSE, TRUE);
        m_a3VidCellExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A5E"), FALSE, TRUE);
    }

    m_g1VidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1"), FALSE, TRUE);
    m_w2VidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "W2"), FALSE, TRUE);
    m_caVidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA"), FALSE, TRUE);
    m_a1VidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "A1"), FALSE, TRUE);
    m_a2VidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "A3"), FALSE, TRUE);
    m_a3VidCellShadowBase.SetResRef(CResRef(m_resRef + m_armorCode + "A5"), FALSE, TRUE);

    if (MIRROR_BAM) {
        m_g1VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "G1X"), FALSE, TRUE);
        m_w2VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "W2X"), FALSE, TRUE);
        m_caVidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "CAX"), FALSE, TRUE);
        m_a1VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A1X"), FALSE, TRUE);
        m_a2VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A3X"), FALSE, TRUE);
        m_a3VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A5X"), FALSE, TRUE);
    } else {
        m_g1VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "G1E"), FALSE, TRUE);
        m_w2VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "W2E"), FALSE, TRUE);
        m_caVidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "CAE"), FALSE, TRUE);
        m_a1VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A1E"), FALSE, TRUE);
        m_a2VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A3E"), FALSE, TRUE);
        m_a3VidCellShadowExtend.SetResRef(CResRef(m_resRef + m_armorCode + "A5E"), FALSE, TRUE);
    }

    m_currentVidCellBase = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
        m_w2VidCellBase.SetPalette(m_charPalette);
        m_caVidCellBase.SetPalette(m_charPalette);
        m_a1VidCellBase.SetPalette(m_charPalette);
        m_a2VidCellBase.SetPalette(m_charPalette);
        m_a3VidCellBase.SetPalette(m_charPalette);

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetPalette(m_charPalette);
            m_w2VidCellExtend.SetPalette(m_charPalette);
            m_caVidCellExtend.SetPalette(m_charPalette);
            m_a1VidCellExtend.SetPalette(m_charPalette);
            m_a2VidCellExtend.SetPalette(m_charPalette);
            m_a3VidCellExtend.SetPalette(m_charPalette);
        }
    }

    m_currentVidCellExtend = &m_g1VidCellExtend;
    m_currentVidCell = m_currentVidCellBase;

    m_weaponCode = 28;

    m_g1VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_w2VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a1VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a2VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a3VidCellWeaponBase.SetPalette(m_weaponPalette);

    m_currentVidCellWeaponBase = NULL;

    if (!MIRROR_BAM) {
        m_g1VidCellWeaponExtend.SetPalette(m_weaponPalette);
        m_w2VidCellWeaponExtend.SetPalette(m_weaponPalette);
        m_a1VidCellWeaponExtend.SetPalette(m_weaponPalette);
        m_a2VidCellWeaponExtend.SetPalette(m_weaponPalette);
        m_a3VidCellWeaponExtend.SetPalette(m_weaponPalette);
    }

    m_currentVidCellWeaponExtend = NULL;
    m_currentVidCellWeapon = m_currentVidCellWeaponBase;

    m_g1VidCellShieldBase.SetPalette(m_shieldPalette);
    m_w2VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a1VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a2VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a3VidCellShieldBase.SetPalette(m_shieldPalette);

    m_currentVidCellShieldBase = NULL;

    if (!MIRROR_BAM) {
        m_g1VidCellShieldExtend.SetPalette(m_shieldPalette);
        m_w2VidCellShieldExtend.SetPalette(m_shieldPalette);
        m_a1VidCellShieldExtend.SetPalette(m_shieldPalette);
        m_a2VidCellShieldExtend.SetPalette(m_shieldPalette);
        m_a3VidCellShieldExtend.SetPalette(m_shieldPalette);
    }

    m_currentVidCellShieldExtend = NULL;
    m_currentVidCellShield = m_currentVidCellShieldBase;

    m_g1VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_w2VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_caVidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a1VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a2VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a3VidCellHelmetBase.SetPalette(m_helmetPalette);

    m_currentVidCellHelmetBase = NULL;

    if (!MIRROR_BAM) {
        m_g1VidCellHelmetExtend.SetPalette(m_helmetPalette);
        m_w2VidCellHelmetExtend.SetPalette(m_helmetPalette);
        m_caVidCellHelmetExtend.SetPalette(m_helmetPalette);
        m_a1VidCellHelmetExtend.SetPalette(m_helmetPalette);
        m_a2VidCellHelmetExtend.SetPalette(m_helmetPalette);
        m_a3VidCellHelmetExtend.SetPalette(m_helmetPalette);
    }

    m_currentVidCellHelmetExtend = NULL;
    m_currentVidCellHelmet = m_currentVidCellHelmetBase;

    m_currentVidCellShadowBase = &m_g1VidCellBase;
    m_currentVidCellShadowExtend = &m_g1VidCellExtend;
    m_currentVidCellShadow = m_currentVidCellShadowBase;

    m_currentBamSequence = 1;

    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6D4050
CGameAnimationTypeCharacterOld::~CGameAnimationTypeCharacterOld()
{
}

// 0x6D3CC0
BOOLEAN CGameAnimationTypeCharacterOld::CanLieDown()
{
    return m_bCanLieDown;
}

// 0x6D3CD0
BOOLEAN CGameAnimationTypeCharacterOld::DetectedByInfravision()
{
    return m_bDetectedByInfravision;
}

// 0x6D3CE0
BOOL CGameAnimationTypeCharacterOld::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2024
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6D3D20
BOOL CGameAnimationTypeCharacterOld::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2025
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6D3D60
BOOL CGameAnimationTypeCharacterOld::IsFalseColor()
{
    return m_falseColor;
}

// 0x6D3D70
BOOL CGameAnimationTypeCharacterOld::IsInvulnerable()
{
    return m_bInvulnerable;
}

// 0x6D3D80
BOOL CGameAnimationTypeCharacterOld::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6D3DB0
BOOLEAN CGameAnimationTypeCharacterOld::GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame)
{
    nSequence = m_currentVidCell->m_nCurrentSequence;
    nFrame = m_currentVidCell->m_nCurrentFrame;
    return TRUE;
}

// 0x6D3DE0
BOOLEAN CGameAnimationTypeCharacterOld::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
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

// 0x6D3FE0
SHORT CGameAnimationTypeCharacterOld::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2041
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6D49C0
void CGameAnimationTypeCharacterOld::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6DD150
CVidPalette* CGameAnimationTypeCharacterOld::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 22615
        UTIL_ASSERT(m_currentVidCell != NULL);

        return &m_charPalette;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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
        // __LINE__: 22641
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6DD8C0
void CGameAnimationTypeCharacterOld::IncrementFrame()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23060
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
    m_currentVidCellShadow->FrameAdvance();

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
        m_currentVidCellWeapon->FrameAdvance();
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield->FrameAdvance();
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellHelmet->FrameAdvance();
    }
}

// 0x6DD940
void CGameAnimationTypeCharacterOld::DecrementFrame()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23096
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield->m_nCurrentFrame--;
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellHelmet->m_nCurrentFrame--;
    }
}

// 0x6DD9D0
void CGameAnimationTypeCharacterOld::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23132
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_w2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_w2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_w2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_caVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a3VidCellExtend.DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_w2VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_caVidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a1VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a2VidCellExtend.UnsuppressTint(colorRange & 0xF);
                m_a3VidCellExtend.UnsuppressTint(colorRange & 0xF);
            }
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_w2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_w2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
                m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            }

            m_g1VidCellBase.DeleteResPaletteAffect();
            m_w2VidCellBase.DeleteResPaletteAffect();
            m_caVidCellBase.DeleteResPaletteAffect();
            m_a1VidCellBase.DeleteResPaletteAffect();
            m_a2VidCellBase.DeleteResPaletteAffect();
            m_a3VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
            m_w2VidCellBase.UnsuppressTintAllRanges();
            m_caVidCellBase.UnsuppressTintAllRanges();
            m_a1VidCellBase.UnsuppressTintAllRanges();
            m_a2VidCellBase.UnsuppressTintAllRanges();
            m_a3VidCellBase.UnsuppressTintAllRanges();

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.DeleteResPaletteAffect();
                m_w2VidCellExtend.DeleteResPaletteAffect();
                m_caVidCellExtend.DeleteResPaletteAffect();
                m_a1VidCellExtend.DeleteResPaletteAffect();
                m_a2VidCellExtend.DeleteResPaletteAffect();
                m_a3VidCellExtend.DeleteResPaletteAffect();

                // NOTE: Uninline.
                m_g1VidCellExtend.UnsuppressTintAllRanges();
                m_w2VidCellExtend.UnsuppressTintAllRanges();
                m_caVidCellExtend.UnsuppressTintAllRanges();
                m_a1VidCellExtend.UnsuppressTintAllRanges();
                m_a2VidCellExtend.UnsuppressTintAllRanges();
                m_a3VidCellExtend.UnsuppressTintAllRanges();
            }
        }
        break;
    case 0x10:
        m_g1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_w2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);

        m_g1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_w2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);

        if (!MIRROR_BAM) {
            m_g1VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_w2VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_w2VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x20:
        m_g1VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_w2VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a1VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellShieldBase.DeleteRangeAffects(colorRange & 0xF);

        m_g1VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_w2VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a1VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellShieldBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellShieldBase.UnsuppressTint(colorRange & 0xF);

        if (!MIRROR_BAM) {
            m_g1VidCellShieldExtend.DeleteRangeAffects(colorRange & 0xF);
            m_w2VidCellShieldExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellShieldExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellShieldExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellShieldExtend.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellShieldExtend.UnsuppressTint(colorRange & 0xF);
            m_w2VidCellShieldExtend.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellShieldExtend.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellShieldExtend.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellShieldExtend.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x30:
        if (m_bEquipHelmet) {
            m_g1VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_w2VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a1VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellHelmetBase.DeleteRangeAffects(colorRange & 0xF);

            m_g1VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_w2VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_caVidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a1VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellHelmetBase.UnsuppressTint(colorRange & 0xF);

            if (!MIRROR_BAM) {
                m_g1VidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);
                m_w2VidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);
                m_caVidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a1VidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a2VidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);
                m_a3VidCellHelmetExtend.DeleteRangeAffects(colorRange & 0xF);

                m_g1VidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
                m_w2VidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
                m_caVidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
                m_a1VidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
                m_a2VidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
                m_a3VidCellHelmetExtend.UnsuppressTint(colorRange & 0xF);
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 23298
        UTIL_ASSERT(FALSE);
    }
}

// 0x6DE1A0
void CGameAnimationTypeCharacterOld::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23323
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_w2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_caVidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a2VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_a3VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_w2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_caVidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a1VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a2VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_a3VidCellExtend.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        }

        m_g1VidCellBase.DeleteResPaletteAffect();
        m_w2VidCellBase.DeleteResPaletteAffect();
        m_caVidCellBase.DeleteResPaletteAffect();
        m_a1VidCellBase.DeleteResPaletteAffect();
        m_a2VidCellBase.DeleteResPaletteAffect();
        m_a3VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
        m_w2VidCellBase.UnsuppressTintAllRanges();
        m_caVidCellBase.UnsuppressTintAllRanges();
        m_a1VidCellBase.UnsuppressTintAllRanges();
        m_a2VidCellBase.UnsuppressTintAllRanges();
        m_a3VidCellBase.UnsuppressTintAllRanges();

        if (!MIRROR_BAM) {
            m_g1VidCellExtend.DeleteResPaletteAffect();
            m_w2VidCellExtend.DeleteResPaletteAffect();
            m_caVidCellExtend.DeleteResPaletteAffect();
            m_a1VidCellExtend.DeleteResPaletteAffect();
            m_a2VidCellExtend.DeleteResPaletteAffect();
            m_a3VidCellExtend.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellExtend.UnsuppressTintAllRanges();
            m_w2VidCellExtend.UnsuppressTintAllRanges();
            m_caVidCellExtend.UnsuppressTintAllRanges();
            m_a1VidCellExtend.UnsuppressTintAllRanges();
            m_a2VidCellExtend.UnsuppressTintAllRanges();
            m_a3VidCellExtend.UnsuppressTintAllRanges();
        }
    }

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        ClearColorEffects(colorRange | 0x10);
        ClearColorEffects(colorRange | 0x20);

        if (m_bEquipHelmet) {
            ClearColorEffects(colorRange | 0x30);
        }
    }
}

// 0x6DE4B0
void CGameAnimationTypeCharacterOld::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23406
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_w2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
                m_w2VidCellBase.SuppressTint(colorRange & 0xF);
                m_caVidCellBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_w2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_caVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a3VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_w2VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_caVidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a1VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a2VidCellExtend.SuppressTint(colorRange & 0xF);
                    m_a3VidCellExtend.SuppressTint(colorRange & 0xF);
                }
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_w2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellBase.SuppressTint(0);
                m_w2VidCellBase.SuppressTint(0);
                m_caVidCellBase.SuppressTint(0);
                m_a1VidCellBase.SuppressTint(0);
                m_a2VidCellBase.SuppressTint(0);
                m_a3VidCellBase.SuppressTint(0);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_w2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_caVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                    m_a3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                    m_g1VidCellExtend.SuppressTint(0);
                    m_w2VidCellExtend.SuppressTint(0);
                    m_caVidCellExtend.SuppressTint(0);
                    m_a1VidCellExtend.SuppressTint(0);
                    m_a2VidCellExtend.SuppressTint(0);
                    m_a3VidCellExtend.SuppressTint(0);
                }
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
                m_w2VidCellBase.SetTintColor(tintColor);
                m_caVidCellBase.SetTintColor(tintColor);
                m_a1VidCellBase.SetTintColor(tintColor);
                m_a2VidCellBase.SetTintColor(tintColor);
                m_a3VidCellBase.SetTintColor(tintColor);

                if (!MIRROR_BAM) {
                    m_g1VidCellExtend.SetTintColor(tintColor);
                    m_w2VidCellExtend.SetTintColor(tintColor);
                    m_caVidCellExtend.SetTintColor(tintColor);
                    m_a1VidCellExtend.SetTintColor(tintColor);
                    m_a2VidCellExtend.SetTintColor(tintColor);
                    m_a3VidCellExtend.SetTintColor(tintColor);
                }
            }
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_g1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_w2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_w2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_w2VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a1VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a2VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a3VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                    m_w2VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                    m_a1VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                    m_a2VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                    m_a3VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                }
            }
        }
        break;
    case 0x20:
        if (m_currentVidCellShield != NULL) {
            m_g1VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_w2VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellShieldBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_w2VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellShieldBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellShieldBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellShieldExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_w2VidCellShieldExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a1VidCellShieldExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a2VidCellShieldExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a3VidCellShieldExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellShieldExtend.SuppressTint(colorRange & 0xF);
                    m_w2VidCellShieldExtend.SuppressTint(colorRange & 0xF);
                    m_a1VidCellShieldExtend.SuppressTint(colorRange & 0xF);
                    m_a2VidCellShieldExtend.SuppressTint(colorRange & 0xF);
                    m_a3VidCellShieldExtend.SuppressTint(colorRange & 0xF);
                }
            }
        }
        break;
    case 0x30:
        if (m_bEquipHelmet && m_currentVidCellHelmet != NULL) {
            m_g1VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_w2VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a1VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellHelmetBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_w2VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_caVidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a1VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a2VidCellHelmetBase.SuppressTint(colorRange & 0xF);
                m_a3VidCellHelmetBase.SuppressTint(colorRange & 0xF);
            }

            if (!MIRROR_BAM) {
                m_g1VidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_w2VidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_caVidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a1VidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a2VidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
                m_a3VidCellHelmetExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

                if (effectType != 0) {
                    m_g1VidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                    m_w2VidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                    m_caVidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                    m_a1VidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                    m_a2VidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                    m_a3VidCellHelmetExtend.SuppressTint(colorRange & 0xF);
                }
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 23614
        UTIL_ASSERT(FALSE);
    }
}

// 0x6DEE50
void CGameAnimationTypeCharacterOld::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23639
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_w2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_caVidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a2VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_a3VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);

            m_g1VidCellBase.SuppressTint(0);
            m_w2VidCellBase.SuppressTint(0);
            m_caVidCellBase.SuppressTint(0);
            m_a1VidCellBase.SuppressTint(0);
            m_a2VidCellBase.SuppressTint(0);
            m_a3VidCellBase.SuppressTint(0);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_w2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_caVidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a1VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a2VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_a3VidCellExtend.AddResPaletteAffect(effectType, tintColor, periodLength);

                m_g1VidCellExtend.SuppressTint(0);
                m_w2VidCellExtend.SuppressTint(0);
                m_caVidCellExtend.SuppressTint(0);
                m_a1VidCellExtend.SuppressTint(0);
                m_a2VidCellExtend.SuppressTint(0);
                m_a3VidCellExtend.SuppressTint(0);
            }
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
            m_w2VidCellBase.SetTintColor(tintColor);
            m_caVidCellBase.SetTintColor(tintColor);
            m_a1VidCellBase.SetTintColor(tintColor);
            m_a2VidCellBase.SetTintColor(tintColor);
            m_a3VidCellBase.SetTintColor(tintColor);

            if (!MIRROR_BAM) {
                m_g1VidCellExtend.SetTintColor(tintColor);
                m_w2VidCellExtend.SetTintColor(tintColor);
                m_caVidCellExtend.SetTintColor(tintColor);
                m_a1VidCellExtend.SetTintColor(tintColor);
                m_a2VidCellExtend.SetTintColor(tintColor);
                m_a3VidCellExtend.SetTintColor(tintColor);
            }
        }
    }

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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

// 0x6DF170
void CGameAnimationTypeCharacterOld::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 23744
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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
        // __LINE__: 23776
        UTIL_ASSERT(FALSE);
    }
}

// 0x6DF350
void CGameAnimationTypeCharacterOld::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 23803
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }

    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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

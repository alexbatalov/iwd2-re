#include "CGameAnimationTypeCharacter.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CInfinity.h"
#include "CUtil.h"

// 0x6C40B0
CGameAnimationTypeCharacter::CGameAnimationTypeCharacter(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
    , m_weaponPalette(CVidPalette::TYPE_RANGE)
    , m_shieldPalette(CVidPalette::TYPE_RANGE)
    , m_helmetPalette(CVidPalette::TYPE_RANGE)
{
    field_144D = 0;
    m_animationID = animationID;
    field_1444 = 0;
    m_falseColor = TRUE;
    m_moveScale = 9;
    m_moveScaleCurrent = 9;
    m_renderWeapons = TRUE;
    m_renderHelmet = TRUE;
    m_bEquipHelmet = TRUE;
    field_1434 = 0;
    m_armorCode = '1';
    field_1441 = 66;
    m_bDetectedByInfravision = TRUE;
    field_144C = 0;
    m_bInvulnerable = FALSE;
    m_bCanLieDown = TRUE;
    field_1448 = 0;

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
        m_armorMaxCode = '4';
        field_1442 = 67;
        field_1448 = 1;

        switch (animationID & 0xF) {
        case 0:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        case 1:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CEFB";
            } else {
                m_resRef = "CEMB";
            }
            m_resRefPaperDoll = m_resRef;
            m_heightCodeHelmet = "WQM";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 2:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = "CDFB";
                m_heightCodeHelmet = "WQS";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CDMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQS";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        case 3:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = m_resRef;
            } else {
                m_resRef = "CIMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeShieldPaperDoll = "WQH";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 4:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = "CGFB";
            } else {
                m_resRef = "CDMB";
                m_resRefPaperDoll = "CGMB";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            m_heightCodeShieldPaperDoll = "WQH";
            break;
        case 5:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMB";
                m_resRefPaperDoll = "COMB";
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFB";
                m_resRefPaperDoll = "COFB";
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 17851
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x100:
        m_armorMaxCode = '4';
        field_1442 = 70;
        field_1448 = 1;

        switch (animationID & 0xF) {
        case 0:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        case 1:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CEFB";
            } else {
                m_resRef = "CEMB";
            }
            m_resRefPaperDoll = m_resRef;
            m_heightCodeHelmet = "WQM";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 2:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = "CDFB";
                m_heightCodeHelmet = "WQS";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CDMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQS";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        case 3:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = m_resRef;
            } else {
                m_resRef = "CIMB";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeShieldPaperDoll = "WQH";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 4:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFB";
                m_resRefPaperDoll = "CGFB";
            } else {
                m_resRef = "CDMB";
                m_resRefPaperDoll = "CGMB";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            m_heightCodeShieldPaperDoll = "WQH";
            break;
        case 5:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMB";
                m_resRefPaperDoll = "COMB";
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFB";
                m_resRefPaperDoll = "COFB";
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 17946
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x200:
        m_armorMaxCode = '4';
        field_1441 = 87;
        field_1442 = 87;
        field_1448 = 1;

        switch (animationID & 0xF) {
        case 0:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMW";
            } else {
                m_resRef = "CHFW";
            }
            m_resRefPaperDoll = m_resRef;
            m_heightCodeHelmet = "WQN";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 1:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CEFW";
            } else {
                m_resRef = "CEMW";
            }
            m_resRefPaperDoll = m_resRef;
            m_heightCodeHelmet = "WQM";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 2:
        case 3:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CDMW";
                m_resRefPaperDoll = m_resRef;
            } else {
                m_resRef = "CDMW";
                m_resRefPaperDoll = "CDFW";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 4:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CDMW";
                m_resRefPaperDoll = "CGMW";
            } else {
                m_resRef = "CDMW";
                m_resRefPaperDoll = "CGFW";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            m_heightCodeShieldPaperDoll = "WQH";
            break;
        case 5:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMW";
                m_resRefPaperDoll = "COMW";
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFW";
                m_resRefPaperDoll = "COFW";
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 18029
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x300:
        m_bEquipHelmet = TRUE;
        m_armorMaxCode = '4';
        field_1441 = 84;
        field_1442 = 67;
        field_1448 = 1;

        switch (animationID & 0xF) {
        case 0:
            if ((animationID & 0xF0) == 0) {
                m_resRef = "CHMT";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHFT";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        case 1:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CEFT";
            } else {
                m_resRef = "CEMT";
            }
            m_resRefPaperDoll = m_resRef;
            m_heightCodeHelmet = "WQM";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 2:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFT";
                m_resRefPaperDoll = "CDFT";
            } else {
                m_resRef = "CDMT";
                m_resRefPaperDoll = m_resRef;
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 3:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFT";
                m_resRefPaperDoll = m_resRef;
            } else {
                m_resRef = "CIMT";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeShieldPaperDoll = "WQH";
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            break;
        case 4:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CIFT";
                m_resRefPaperDoll = "CDFT";
            } else {
                m_resRefPaperDoll = "CDMT";
                m_resRef = m_resRefPaperDoll;
            }
            m_heightCodeHelmet = "WQS";
            m_heightCode = m_heightCodeHelmet;
            m_heightCodeShieldPaperDoll = "WQH";
            break;
        case 5:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CHFT";
                m_resRefPaperDoll = "COFB";
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHMT";
                m_resRefPaperDoll = "COMB";
            }
            m_heightCodeHelmet = "WQL";
            m_heightCode = m_heightCodeHelmet;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 18121
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x400:
        m_armorMaxCode = '1';

        switch (animationID & 0xF) {
        case 0:
            m_resRef = "UDRZ";
            field_1441 = 90;
            field_1442 = 90;
            m_heightCodeHelmet = "WPM";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 5;
            break;
        case 1:
            m_bInvulnerable = TRUE;
            m_resRef = "CTES";
            field_1441 = 83;
            field_1442 = 83;
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 4;
            break;
        case 2:
            m_bEquipHelmet = FALSE;
            m_resRef = "CMNK";
            m_resRefPaperDoll = m_resRef;
            field_1441 = 75;
            field_1442 = 75;
            m_heightCodeHelmet = "WPM";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 5;
            break;
        case 3:
            m_colorChunks = -1;
            m_resRef = "MSKL";
            m_resRefPaperDoll = m_resRef;
            field_1441 = 76;
            field_1442 = 76;
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
            m_resRefPaperDoll = m_resRef;
            field_1441 = 82;
            field_1442 = 82;
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_nSndFreq = 5;
            break;
        case 5:
            m_colorChunks = -1;
            m_resRef = "MDGU";
            m_resRefPaperDoll = m_resRef;
            field_1441 = 85;
            field_1442 = 85;
            m_heightCodeHelmet = "WPL";
            m_heightCode = m_heightCodeHelmet;
            m_colorBlood = 34;
            m_bDetectedByInfravision = FALSE;
            m_nSndFreq = 5;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 18218
            UTIL_ASSERT(FALSE);
        }
        break;
    case 0x500:
        m_armorMaxCode = '1';
        field_1441 = 77;
        field_1442 = 77;
        field_1448 = 1;

        switch (animationID & 0xF) {
        case 0:
            if ((animationID & 0xF0) != 0) {
                m_resRef = "CHFM";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQN";
                m_heightCode = m_heightCodeHelmet;
            } else {
                m_resRef = "CHMM";
                m_resRefPaperDoll = m_resRef;
                m_heightCodeHelmet = "WQL";
                m_heightCode = m_heightCodeHelmet;
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 18146
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 18223
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1"), field_1444, TRUE, TRUE);
    m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA"), field_1444, TRUE, TRUE);
    m_a1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A1"), field_1444, TRUE, TRUE);
    m_a2VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A3"), field_1444, TRUE, TRUE);
    m_a3VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A5"), field_1444, TRUE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < 7; colorRange++) {
            m_charPalette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
        m_caVidCellBase.SetPalette(m_charPalette);
        m_a1VidCellBase.SetPalette(m_charPalette);
        m_a2VidCellBase.SetPalette(m_charPalette);
        m_a3VidCellBase.SetPalette(m_charPalette);
    }

    m_weaponCode = 4;

    m_g1VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a1VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a2VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_a3VidCellWeaponBase.SetPalette(m_weaponPalette);
    m_currentVidCellWeaponBase = NULL;
    m_currentVidCellWeapon = NULL;

    m_g1VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a1VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a2VidCellShieldBase.SetPalette(m_shieldPalette);
    m_a3VidCellShieldBase.SetPalette(m_shieldPalette);
    m_currentVidCellShieldBase = NULL;
    m_currentVidCellShield = NULL;

    m_g1VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_caVidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a1VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a2VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_a3VidCellHelmetBase.SetPalette(m_helmetPalette);
    m_currentVidCellHelmetBase = NULL;
    m_currentVidCellHelmet = NULL;

    m_currentBamSequence = 1;
    m_extendDirectionTest = CGameSprite::DIR_N;
    ChangeDirection(facing);
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

// 0x6C5FB0
void CGameAnimationTypeCharacter::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 18293
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint charCenter;
    m_currentVidCell->GetCurrentCenterPoint(charCenter, FALSE);
    ptReference = charCenter;

    if (m_renderWeapons) {
        if (m_currentVidCellWeapon != NULL
            && m_currentVidCellWeapon->GetResRef().IsValid()) {
            CPoint weaponCenter;
            m_currentVidCellWeapon->GetCurrentCenterPoint(weaponCenter, FALSE);

            if (weaponCenter.x > ptReference.x) {
                ptReference.x = weaponCenter.x;
            }

            if (weaponCenter.y > ptReference.y) {
                ptReference.y = weaponCenter.y;
            }
        }

        // FIXME: Redundant.
        if (m_renderWeapons) {
            if (m_currentVidCellShield != NULL
                && m_currentVidCellShield->GetResRef().IsValid()) {
                CPoint shieldCenter;
                m_currentVidCellShield->GetCurrentCenterPoint(shieldCenter, FALSE);

                if (shieldCenter.x > ptReference.x) {
                    ptReference.x = shieldCenter.x;
                }

                if (shieldCenter.y > ptReference.y) {
                    ptReference.y = shieldCenter.y;
                }
            }
        }
    }

    if (m_renderHelmet) {
        if (m_currentVidCellHelmet != NULL
            && m_currentVidCellHelmet->GetResRef().IsValid()) {
            CPoint helmetCenter;
            m_currentVidCellHelmet->GetCurrentCenterPoint(helmetCenter, FALSE);

            if (helmetCenter.x > ptReference.x) {
                ptReference.x = helmetCenter.x;
            }

            if (helmetCenter.y > ptReference.y) {
                ptReference.y = helmetCenter.y;
            }
        }
    }

    CSize charSize;
    m_currentVidCell->GetCurrentFrameSize(charSize, FALSE);

    charSize.cx += ptReference.x - charCenter.x;
    charSize.cy += ptReference.y - charCenter.y;
    rFx.SetRect(0, 0, charSize.cx, charSize.cy);

    if (m_renderWeapons) {
        if (m_currentVidCellWeapon != NULL
            && m_currentVidCellWeapon->GetResRef().IsValid()) {
            CSize weaponSize;
            m_currentVidCellWeapon->GetCurrentFrameSize(weaponSize, FALSE);

            CPoint weaponCenter;
            m_currentVidCellWeapon->GetCurrentCenterPoint(weaponCenter, FALSE);

            if (weaponCenter.x > ptReference.x) {
                ptReference.x = weaponCenter.x;
            }

            rFx.right = max(rFx.right, ptReference.x - weaponCenter.x + weaponSize.cx);
            rFx.bottom = max(rFx.bottom, ptReference.y - weaponCenter.y + weaponSize.cy);
        }

        // FIXME: Redundant.
        if (m_renderWeapons) {
            if (m_currentVidCellShield != NULL
                && m_currentVidCellShield->GetResRef().IsValid()) {
                CSize shieldSize;
                m_currentVidCellShield->GetCurrentFrameSize(shieldSize, FALSE);

                CPoint shieldCenter;
                m_currentVidCellShield->GetCurrentCenterPoint(shieldCenter, FALSE);

                if (shieldCenter.x > ptReference.x) {
                    ptReference.x = shieldCenter.x;
                }

                rFx.right = max(rFx.right, ptReference.x - shieldCenter.x + shieldSize.cx);
                rFx.bottom = max(rFx.bottom, ptReference.y - shieldCenter.y + shieldSize.cy);
            }
        }
    }

    if (m_renderHelmet) {
        if (m_currentVidCellHelmet != NULL
            && m_currentVidCellHelmet->GetResRef().IsValid()) {
            CSize helmetSize;
            m_currentVidCellHelmet->GetCurrentFrameSize(helmetSize, FALSE);

            CPoint helmetCenter;
            m_currentVidCellHelmet->GetCurrentCenterPoint(helmetCenter, FALSE);

            if (helmetCenter.x > ptReference.x) {
                ptReference.x = helmetCenter.x;
            }

            rFx.right = max(rFx.right, ptReference.x - helmetCenter.x + helmetSize.cx);
            rFx.bottom = max(rFx.bottom, ptReference.y - helmetCenter.y + helmetSize.cy);
        }
    }
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

// 0x6C6320
void CGameAnimationTypeCharacter::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 18436
    UTIL_ASSERT(m_currentVidCell != NULL && m_currentVidCellBase != NULL);

    SHORT nFrame = m_currentVidCell->m_nCurrentFrame;
    m_currentBamDirection = nDirection;
    m_currentVidCell = m_currentVidCellBase;

    if (m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
    } else {
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
    }

    m_currentVidCell->FrameSet(nFrame);

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon = m_currentVidCellWeaponBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
        } else {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }

        m_currentVidCellWeapon->FrameSet(nFrame);
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield = m_currentVidCellShieldBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
        } else {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }

        m_currentVidCellShield->FrameSet(nFrame);
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellShield = m_currentVidCellShieldBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
        } else {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }

        m_currentVidCellShield->FrameSet(nFrame);
    }
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

// 0x6CC180
char* CGameAnimationTypeCharacter::GetSndArmor()
{
    char* szTemp;
    int cnt;
    char ch;

    if (m_armorCode == '1') {
        return "";
    }

    szTemp = new char[9];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 19332
    UTIL_ASSERT(szTemp != NULL);

    strcpy(szTemp, "A_      ");

    switch (m_armorCode) {
    case '2':
        strcpy(&(szTemp[2]), "Lthr");
        cnt = 6;
        break;
    case '3':
        strcpy(&(szTemp[2]), "Chain");
        cnt = 6;
        break;
    case '4':
        strcpy(&(szTemp[2]), "Plate");
        cnt = 8;
        break;
    default:
        // FIXME: Leaking `szTemp`.
        return NULL;
    }

    ch = rand() % cnt + '1';
    if (m_armorCode == '2') {
        szTemp[6] = ch;
        szTemp[7] = '\0';
        szTemp[8] = '\0';
        if (strcmp(szTemp, field_3F2) == 0) {
            if (szTemp[6] - '1' == cnt - 1) {
                szTemp[6] = '1';
            } else {
                szTemp[6]++;
            }
        }
    } else {
        szTemp[7] = ch;
        szTemp[8] = '\0';
        if (strcmp(szTemp, field_3F2) == 0) {
            if (szTemp[7] - '1' == cnt - 1) {
                szTemp[7] = '1';
            } else {
                szTemp[7]++;
            }
        }
    }

    memcpy(field_3F2, szTemp, 9);

    return szTemp;
}

// 0x6CC330
const char* CGameAnimationTypeCharacter::GetSndWalk(SHORT a1)
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
    // __LINE__: 19522
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

// 0x6CD400
void CGameAnimationTypeCharacter::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 20146
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 20147
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (m_currentBamDirection > m_extendDirectionTest) {
        dwRenderFlags |= CInfinity::MIRROR_FX;
    }

    dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
    dwRenderFlags |= 0x4;

    if (transparency) {
        dwRenderFlags |= 0x2;
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        m_currentVidCell->SetTintColor(rgbTintColor);

        if (m_renderHelmet) {
            if (m_currentVidCellHelmet != NULL) {
                m_currentVidCellHelmet->SetTintColor(rgbTintColor);
            }
        }

        if (m_renderWeapons) {
            if (m_currentVidCellShield != NULL) {
                m_currentVidCellShield->SetTintColor(rgbTintColor);
            }

            // FIXME: Redunant.
            if (m_renderWeapons) {
                if (m_currentVidCellWeapon != NULL) {
                    m_currentVidCellWeapon->SetTintColor(rgbTintColor);
                }
            }
        }

        SHORT nDirection;
        if (m_currentBamDirection > m_extendDirectionTest) {
            nDirection = 16 - m_currentBamDirection;
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

            if (m_renderHelmet) {
                if (m_currentVidCellHelmet != NULL && m_currentVidCellHelmet->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellHelmet,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }
            }

            if (m_renderWeapons) {
                if (m_currentVidCellShield != NULL && m_currentVidCellShield->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellShield,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }

                // FIXME: Redunant.
                if (m_renderWeapons) {
                    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
                        pInfinity->FXRender(m_currentVidCellWeapon,
                            ptReference.x,
                            ptReference.y,
                            dwRenderFlags,
                            transparency);
                    }
                }
            }

            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if (m_renderWeapons) {
                if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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

            if (m_renderHelmet) {
                if (m_currentVidCellHelmet != NULL && m_currentVidCellHelmet->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellHelmet,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }
            }

            if (m_renderWeapons) {
                if (m_currentVidCellShield != NULL && m_currentVidCellShield->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellShield,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }

                // FIXME: Redunant.
                if (m_renderWeapons) {
                    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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
                if (m_currentVidCellShield != NULL && m_currentVidCellShield->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellShield,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }

                // FIXME: Redunant.
                if (m_renderWeapons) {
                    if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
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

            if (m_renderHelmet) {
                if (m_currentVidCellHelmet != NULL && m_currentVidCellHelmet->GetResRef().IsValid()) {
                    pInfinity->FXRender(m_currentVidCellHelmet,
                        ptReference.x,
                        ptReference.y,
                        dwRenderFlags,
                        transparency);
                }
            }

            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 20263
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

// 0x6CDA00
SHORT CGameAnimationTypeCharacter::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    m_renderWeapons = TRUE;
    m_renderHelmet = TRUE;

    switch (nSequence) {
    case 1:
        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }

        m_currentBamSequence = 9;

        if (field_1448 != 0) {
            field_144C = '9';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    case 2:
        m_currentVidCellBase = &m_caVidCellBase;
        m_renderWeapons = FALSE;

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_caVidCellHelmetBase;
        }

        switch (rand() % 4) {
        case 0:
            m_currentBamSequence = 1;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 1:
            m_currentBamSequence = 3;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 2:
            m_currentBamSequence = 5;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 3:
            m_currentBamSequence = 7;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 20415
            UTIL_ASSERT(FALSE);
        }
        break;
    case 3:
        m_currentVidCellBase = &m_caVidCellBase;
        m_renderWeapons = FALSE;

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_caVidCellHelmetBase;
        }

        switch (rand() % 4) {
        case 0:
            m_currentBamSequence = 0;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 1:
            m_currentBamSequence = 2;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 2:
            m_currentBamSequence = 4;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        case 3:
            m_currentBamSequence = 6;
            if (field_1448 != 0) {
                field_144C = 0;
                m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA" + field_144C), field_1444, TRUE, TRUE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 20465
            UTIL_ASSERT(FALSE);
        }
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }

        m_currentBamSequence = 4;

        if (field_1448 != 0) {
            field_144C = '4';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    case 5:
        m_currentVidCellBase = &m_g1VidCellBase;

        m_renderWeapons = FALSE;
        m_renderHelmet = FALSE;
        m_currentBamSequence = 5;

        if (field_1448 != 0) {
            field_144C = '5';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    case 6:
        if (1) {
            INT nChance = rand() % 100;
            if (nChance < 60) {
                if ((m_currentBamSequence != 2
                        && m_currentBamSequence != 7
                        && m_currentBamSequence != 8)
                    || m_currentVidCellBase != &m_g1VidCellBase) {
                    bRandomFrame = TRUE;
                }

                m_currentBamSequence = 2;

                if (field_1448 != 0) {
                    field_144C = '2';
                    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
                }
            } else if (nChance < 97) {
                m_currentBamSequence = 7;

                if (field_1448 != 0) {
                    field_144C = '7';
                    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
                }
            } else {
                m_currentBamSequence = 0;

                if (field_1448 != 0) {
                    field_144C = '8';
                    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
                }
            }

            m_currentVidCellBase = &m_g1VidCellBase;

            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
            }

            if (m_currentVidCellShield != NULL) {
                m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
            }

            if (m_currentVidCellHelmet != NULL) {
                m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
            }
        }
        break;
    case 7:
        if (m_weaponCode == 5) {
            if (m_currentBamSequence != 3
                || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentBamSequence = 3;

            if (field_1448 != 0) {
                field_144C = '3';
                m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
            }

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 20618
            UTIL_ASSERT(m_currentVidCellShield == NULL);
        } else {
            if (m_currentBamSequence != 1
                || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentBamSequence = 1;

            if (field_1448 != 0) {
                field_144C = 0;
                m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
            }

            if (m_currentVidCellShield != NULL) {
                m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
            }
        }

        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }
        break;
    case 8:
        m_currentVidCellBase = &m_a1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_a1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_a1VidCellHelmetBase;
        }

        m_currentBamSequence = 0;

        if (field_1448 != 0) {
            field_144C = 0;
        }
        break;
    case 9:
        m_currentVidCellBase = &m_g1VidCellBase;

        m_renderWeapons = FALSE;
        m_renderHelmet = FALSE;
        m_currentBamSequence = 6;

        if (field_1448 != 0) {
            field_144C = '6';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    case 10:
        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }

        m_currentBamSequence = 0;

        if (field_1448 != 0) {
            field_144C = '1';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    case 11:
        m_currentVidCellBase = &m_a1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_a1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_a1VidCellHelmetBase;
        }

        m_currentBamSequence = 0;
        nSequence = 0;

        if (field_1448 != 0) {
            field_144C = 0;
        }
        break;
    case 12:
        m_currentVidCellBase = &m_a2VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_a2VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_a2VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_a2VidCellHelmetBase;
        }

        m_currentBamSequence = 0;
        nSequence = 0;

        if (field_1448 != 0) {
            field_144C = 0;
        }
        break;
    case 13:
        m_currentVidCellBase = &m_a3VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_a3VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_a3VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_a3VidCellHelmetBase;
        }

        m_currentBamSequence = 0;
        nSequence = 0;

        if (field_1448 != 0) {
            field_144C = 0;
        }
        break;
    case 14:
    case 15:
        nSequence = 7;

        if (m_weaponCode == 5) {
            if (m_currentBamSequence != 3
                || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentBamSequence = 3;

            if (field_1448 != 0) {
                field_144C = '3';
                m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
            }

            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 20618
            UTIL_ASSERT(m_currentVidCellShield == NULL);
        } else {
            if (m_currentBamSequence != 1
                || m_currentVidCellBase != &m_g1VidCellBase) {
                bRandomFrame = TRUE;
            }

            m_currentBamSequence = 1;

            if (field_1448 != 0) {
                field_144C = 0;
                m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
            }

            if (m_currentVidCellShield != NULL) {
                m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
            }
        }

        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }
        break;
    case 17:
        m_currentVidCellBase = &m_g1VidCellBase;

        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_g1VidCellWeaponBase;
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShieldBase = &m_g1VidCellShieldBase;
        }

        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmetBase = &m_g1VidCellHelmetBase;
        }

        m_currentBamSequence = 10;

        if (field_1448 != 0) {
            field_144C = '9';
            m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1" + field_144C), field_1444, TRUE, TRUE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 20708
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

    if (m_renderWeapons) {
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeapon->FrameSet(nFrame);
        }

        if (m_currentVidCellShield != NULL) {
            m_currentVidCellShield->FrameSet(nFrame);
        }
    }

    if (m_renderHelmet) {
        if (m_currentVidCellHelmet != NULL) {
            m_currentVidCellHelmet->FrameSet(nFrame);
        }
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    field_144D = static_cast<unsigned char>(nSequence);

    return nSequence;
}

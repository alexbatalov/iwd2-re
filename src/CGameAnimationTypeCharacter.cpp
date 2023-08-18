#include "CGameAnimationTypeCharacter.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
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
    field_1428 = 1;
    field_142C = 1;
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
    m_g1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "G1"), field_1444, TRUE);
    m_caVidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "CA"), field_1444, TRUE);
    m_a1VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A1"), field_1444, TRUE);
    m_a2VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A3"), field_1444, TRUE);
    m_a3VidCellBase.SetResRef(CResRef(m_resRef + m_armorCode + "A5"), field_1444, TRUE);

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
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence - m_currentBamSequence + 16);
    } else {
        m_currentVidCell->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
    }

    m_currentVidCell->FrameSet(nFrame);

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon = m_currentVidCellWeaponBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamSequence - m_currentBamSequence + 16);
        } else {
            m_currentVidCellWeapon->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }

        m_currentVidCellWeapon->FrameSet(nFrame);
    }

    if (m_currentVidCellShield != NULL) {
        m_currentVidCellShield = m_currentVidCellShieldBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence - m_currentBamSequence + 16);
        } else {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }

        m_currentVidCellShield->FrameSet(nFrame);
    }

    if (m_currentVidCellHelmet != NULL) {
        m_currentVidCellShield = m_currentVidCellShieldBase;

        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCellShield->SequenceSet(9 * m_currentBamSequence - m_currentBamSequence + 16);
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

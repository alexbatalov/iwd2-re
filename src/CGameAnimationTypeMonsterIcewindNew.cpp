#include "CGameAnimationTypeMonsterIcewindNew.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6E8180
CGameAnimationTypeMonsterIcewindNew::CGameAnimationTypeMonsterIcewindNew(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    field_34E6 = 0;
    m_renderWeapons = TRUE;
    field_34E2 = 0;
    field_3416 = 0;
    field_341E = 0;
    field_341A = 0;
    field_34DC = 1;
    field_34F4 = 23;
    field_34F8 = -1;

    switch (animationID & 0xF00) {
    case 0x000:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_colorChunks = -1;
        m_colorBlood = 63;
        field_34DC = 0;
        m_pSndDeath = "FAL_03B";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

        switch (animationID & 0xF0) {
        case 0x00:
            m_nSndFreq = 10;
            m_resRef = "MSKA";
            field_34E8[0] = "AX";
            field_34E8[1] = "MS";
            field_34E8[2] = "S1";
            break;
        case 0x10:
            m_nSndFreq = 8;
            m_resRef = "MSKT";
            field_34E8[0] = "AX";
            field_34E8[1] = "S1";
            break;
        case 0x20:
            m_moveScale = 15;
            m_moveScaleCurrent = 15;
            m_nSndFreq = 8;
            m_resRef = "MWI4";
            m_rEllipse.left = -16;
            m_rEllipse.top = -12;
            m_rEllipse.right = 16;
            m_rEllipse.bottom = 12;
            m_colorBlood = 63;
            field_34E8[0] = "AX";
            field_34E8[1] = "MC";
            field_34E8[2] = "S1";
            break;
        }
        break;
    case 0x100:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 7;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MYU1";
            field_34F4 = 23;
            break;
        case 0x10:
            m_rEllipse.left = -24;
            m_rEllipse.top = -18;
            m_rEllipse.right = 24;
            m_rEllipse.bottom = 18;
            m_resRef = "MYU2";
            field_34F4 = 23;
            break;
        }
        field_34E8[0] = "AX";
        field_34E8[1] = "CL";
        field_34E8[2] = "S1";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
        break;
    case 0x200:
        m_moveScale = 6;
        m_moveScaleCurrent = 6;
        m_nSndFreq = 9;
        m_colorBlood = 37;

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MLIZ";
            field_34E8[0] = "QS";
            field_34E8[1] = "HB";
            field_34E8[2] = "CL";
            break;
        case 0x10:
            m_resRef = "MLI2";
            field_34E8[0] = "AX";
            field_34E8[1] = "MS";
            field_34E8[2] = "HB";
            break;
        }
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_pSndDeath = "FAL_03B";
        m_personalSpace = 3;
        break;
    case 0x300:
        m_moveScale = 5;
        m_moveScaleCurrent = 5;
        m_nSndFreq = 10;
        m_resRef = "MGFI";
        field_34E8[0] = "SS";
        field_34E8[1] = "WH";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
        m_rEllipse.left = -48;
        m_rEllipse.top = -36;
        m_rEllipse.right = 48;
        m_rEllipse.bottom = 36;
        m_pSndDeath = "FAL_03B";
        m_personalSpace = 3;
        m_colorChunks = -1;
        break;
    case 0x400:
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_colorChunks = -1;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 9;
        m_pSndDeath = "FAL_03B";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MSAH";
            break;
        case 0x10:
            m_resRef = "MSAT";
            break;
        }

        field_34E8[0] = "CB";
        field_34E8[1] = "SP";
        break;
    case 0x500:
        m_rEllipse.left = -48;
        m_rEllipse.top = -36;
        m_rEllipse.right = 48;
        m_rEllipse.bottom = 36;
        m_colorChunks = -1;
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 9;
        m_pSndDeath = "FAL_03B";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

        switch (animationID & 0xF0) {
        case 0x00:
            m_resRef = "MDRM";
            field_34E8[0] = "MC";
            field_34E8[1] = "S1";
            break;
        case 0x10:
            m_resRef = "MDRF";
            field_34E8[0] = "AX";
            field_34E8[1] = "S1";
            field_34E8[2] = "MC";
            break;
        }
        break;
    case 0x700:
        m_moveScale = 7;
        m_moveScaleCurrent = 7;
        m_nSndFreq = 8;
        m_resRef = "MBA";
        SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
        m_rEllipse.left = -16;
        m_rEllipse.top = -12;
        m_rEllipse.right = 16;
        m_rEllipse.bottom = 12;
        m_pSndDeath = "FAL_03B";
        m_personalSpace = 3;
        m_colorChunks = -1;

        switch (animationID & 0xF0) {
        case 0x70:
            field_34E8[0] = "AX";
            field_34E8[1] = "MC";
            field_34E8[2] = "S1";
            m_resRef += "1";
            break;
        case 0x80:
            field_34E8[0] = "AX";
            field_34E8[1] = "WH";
            field_34E8[2] = "S1";
            m_resRef += "2";
            break;
        case 0x90:
            field_34E8[0] = "AX";
            field_34E8[1] = "MC";
            field_34E8[2] = "S1";
            m_resRef += "3";
            break;
        default:
            if (1) {
                CString sError;
                sError.Format("Barbarian has a bad animation id %h", animationID);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 27580
                UTIL_ASSERT_MSG(FALSE, (LPCSTR)sError);
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 27587
        UTIL_ASSERT(FALSE);
    }

    m_a1VidCellBase.SetResRef(CResRef(m_resRef + "A1"), FALSE, TRUE, TRUE);
    m_a2VidCellBase.SetResRef(CResRef(m_resRef + "A2"), FALSE, TRUE, TRUE);
    m_a3VidCellBase.SetResRef(CResRef(m_resRef + "A3"), FALSE, TRUE, TRUE);
    m_a4VidCellBase.SetResRef(CResRef(m_resRef + "A4"), FALSE, TRUE, TRUE);
    m_deVidCellBase.SetResRef(CResRef(m_resRef + "De"), FALSE, TRUE, TRUE);
    m_ghVidCellBase.SetResRef(CResRef(m_resRef + "Gh"), FALSE, TRUE, TRUE);
    m_slVidCellBase.SetResRef(CResRef(m_resRef + "Sl"), FALSE, TRUE, TRUE);
    m_guVidCellBase.SetResRef(CResRef(m_resRef + "Gu"), FALSE, TRUE, TRUE);
    m_spVidCellBase.SetResRef(CResRef(m_resRef + "Sp"), FALSE, TRUE, TRUE);
    m_caVidCellBase.SetResRef(CResRef(m_resRef + "Ca"), FALSE, TRUE, TRUE);
    m_scVidCellBase.SetResRef(CResRef(m_resRef + "Sc"), FALSE, TRUE, TRUE);
    m_sdVidCellBase.SetResRef(CResRef(m_resRef + "Sd"), FALSE, TRUE, TRUE);
    m_twVidCellBase.SetResRef(CResRef(m_resRef + "Tw"), FALSE, TRUE, TRUE);
    m_wkVidCellBase.SetResRef(CResRef(m_resRef + "Wk"), FALSE, TRUE, TRUE);

    m_currentVidCellBase = &m_wkVidCellBase;

    if (!MIRROR_BAM) {
        m_a1VidCellExtend.SetResRef(CResRef(m_resRef + "A1E"), FALSE, TRUE, TRUE);
        m_a2VidCellExtend.SetResRef(CResRef(m_resRef + "A2E"), FALSE, TRUE, TRUE);
        m_a3VidCellExtend.SetResRef(CResRef(m_resRef + "A3E"), FALSE, TRUE, TRUE);
        m_a4VidCellExtend.SetResRef(CResRef(m_resRef + "A4E"), FALSE, TRUE, TRUE);
        m_deVidCellExtend.SetResRef(CResRef(m_resRef + "DeE"), FALSE, TRUE, TRUE);
        m_ghVidCellExtend.SetResRef(CResRef(m_resRef + "GhE"), FALSE, TRUE, TRUE);
        m_slVidCellExtend.SetResRef(CResRef(m_resRef + "SlE"), FALSE, TRUE, TRUE);
        m_guVidCellExtend.SetResRef(CResRef(m_resRef + "GuE"), FALSE, TRUE, TRUE);
        m_spVidCellExtend.SetResRef(CResRef(m_resRef + "SpE"), FALSE, TRUE, TRUE);
        m_caVidCellExtend.SetResRef(CResRef(m_resRef + "CaE"), FALSE, TRUE, TRUE);
        m_scVidCellExtend.SetResRef(CResRef(m_resRef + "ScE"), FALSE, TRUE, TRUE);
        m_sdVidCellExtend.SetResRef(CResRef(m_resRef + "SdE"), FALSE, TRUE, TRUE);
        m_twVidCellExtend.SetResRef(CResRef(m_resRef + "TwE"), FALSE, TRUE, TRUE);
        m_wkVidCellExtend.SetResRef(CResRef(m_resRef + "WkE"), FALSE, TRUE, TRUE);
    }

    m_currentVidCellExtend = &m_wkVidCellExtend;
    m_currentVidCell = m_currentVidCellBase;

    if (field_3416) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_a1VidCellBase.SetPalette(m_charPalette);
        m_a2VidCellBase.SetPalette(m_charPalette);
        m_a3VidCellBase.SetPalette(m_charPalette);
        m_a4VidCellBase.SetPalette(m_charPalette);
        m_deVidCellBase.SetPalette(m_charPalette);
        m_ghVidCellBase.SetPalette(m_charPalette);
        m_slVidCellBase.SetPalette(m_charPalette);
        m_guVidCellBase.SetPalette(m_charPalette);
        m_spVidCellBase.SetPalette(m_charPalette);
        m_caVidCellBase.SetPalette(m_charPalette);
        m_scVidCellBase.SetPalette(m_charPalette);
        m_sdVidCellBase.SetPalette(m_charPalette);
        m_twVidCellBase.SetPalette(m_charPalette);
        m_wkVidCellBase.SetPalette(m_charPalette);
        m_currentVidCellBase = &m_a1VidCellBase;

        if (!MIRROR_BAM) {
            m_a1VidCellExtend.SetPalette(m_charPalette);
            m_a2VidCellExtend.SetPalette(m_charPalette);
            m_a3VidCellExtend.SetPalette(m_charPalette);
            m_a4VidCellExtend.SetPalette(m_charPalette);
            m_deVidCellExtend.SetPalette(m_charPalette);
            m_ghVidCellExtend.SetPalette(m_charPalette);
            m_slVidCellExtend.SetPalette(m_charPalette);
            m_guVidCellExtend.SetPalette(m_charPalette);
            m_spVidCellExtend.SetPalette(m_charPalette);
            m_caVidCellExtend.SetPalette(m_charPalette);
            m_scVidCellExtend.SetPalette(m_charPalette);
            m_sdVidCellExtend.SetPalette(m_charPalette);
            m_twVidCellExtend.SetPalette(m_charPalette);
            m_wkVidCellExtend.SetPalette(m_charPalette);
        }

        m_a1VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_a2VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_a3VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_a4VidCellWeaponBase.SetPalette(m_weaponPalette);
        m_deVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_ghVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_slVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_guVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_spVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_caVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_scVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_sdVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_twVidCellWeaponBase.SetPalette(m_weaponPalette);
        m_wkVidCellWeaponBase.SetPalette(m_weaponPalette);

        if (!MIRROR_BAM) {
            m_a1VidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_a2VidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_a3VidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_a4VidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_deVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_ghVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_slVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_guVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_spVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_caVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_scVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_sdVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_twVidCellWeaponExtend.SetPalette(m_weaponPalette);
            m_wkVidCellWeaponExtend.SetPalette(m_weaponPalette);
        }
    }

    m_currentVidCellWeaponBase = 0;
    m_currentVidCellWeaponExtend = NULL;
    m_currentVidCellWeapon = NULL;
    m_currentBamSequence = 0;
    m_extendDirectionTest = CGameSprite::DIR_NNE;
    ChangeDirection(facing);
}

// 0x6EB410
CGameAnimationTypeMonsterIcewindNew::~CGameAnimationTypeMonsterIcewindNew()
{
}

// 0x6EB260
BOOL CGameAnimationTypeMonsterIcewindNew::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2341
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6EB2A0
BOOL CGameAnimationTypeMonsterIcewindNew::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2342
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6EB2E0
BOOL CGameAnimationTypeMonsterIcewindNew::IsMirroring()
{
    return MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest;
}

// 0x6EB310
void CGameAnimationTypeMonsterIcewindNew::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2344
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->FrameAdvance();
    }
}

// 0x6EB350
void CGameAnimationTypeMonsterIcewindNew::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2345
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;

    if (m_currentVidCellWeapon != NULL) {
        m_currentVidCellWeapon->m_nCurrentFrame--;
    }
}

// 0x6EB3A0
SHORT CGameAnimationTypeMonsterIcewindNew::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2354
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6EB840
void CGameAnimationTypeMonsterIcewindNew::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27725
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptChar;
    m_currentVidCell->GetCurrentCenterPoint(ptChar, FALSE);
    ptReference = ptChar;

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    if (m_renderWeapons
        && m_currentVidCellWeapon != NULL
        && m_currentVidCellWeapon->GetResRef().IsValid()) {
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

// 0x6EB9A0
void CGameAnimationTypeMonsterIcewindNew::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6EBA10
void CGameAnimationTypeMonsterIcewindNew::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27812
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
            m_currentVidCellWeapon->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
        } else {
            m_currentVidCellWeapon->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
        }
    }
}

// 0x6EBBA0
void CGameAnimationTypeMonsterIcewindNew::EquipWeapon(const CString& resRef, BYTE* colorRangeValues, DWORD itemFlags, const WORD* pAttackProb)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 27860
    UTIL_ASSERT(pAttackProb != NULL);

    field_34E2 = 0;
    ClearColorEffects(21);
    ClearColorEffects(20);
    ClearColorEffects(16);

    if (!resRef.IsEmpty()) {
        BYTE cnt = 0;
        while (cnt < 3) {
            if (field_34E8[cnt] == resRef) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
                // __LINE__: 27911
                UTIL_ASSERT(colorRangeValues != NULL);

                if (m_currentVidCellBase == &m_a1VidCellBase) {
                    m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_a1VidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_a2VidCellBase) {
                    m_currentVidCellWeaponBase = &m_a2VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_a2VidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_a3VidCellBase) {
                    m_currentVidCellWeaponBase = &m_a3VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_a3VidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_a4VidCellBase) {
                    m_currentVidCellWeaponBase = &m_a4VidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_a4VidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_deVidCellBase) {
                    m_currentVidCellWeaponBase = &m_deVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_deVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_ghVidCellBase) {
                    m_currentVidCellWeaponBase = &m_ghVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_ghVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_slVidCellBase) {
                    m_currentVidCellWeaponBase = &m_slVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_slVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_guVidCellBase) {
                    m_currentVidCellWeaponBase = &m_guVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_guVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_spVidCellBase) {
                    m_currentVidCellWeaponBase = &m_spVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_spVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_caVidCellBase) {
                    m_currentVidCellWeaponBase = &m_caVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_caVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_scVidCellBase) {
                    m_currentVidCellWeaponBase = &m_scVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_scVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_sdVidCellBase) {
                    m_currentVidCellWeaponBase = &m_sdVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_sdVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_twVidCellBase) {
                    m_currentVidCellWeaponBase = &m_twVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_twVidCellWeaponExtend;
                } else if (m_currentVidCellBase == &m_wkVidCellBase) {
                    m_currentVidCellWeaponBase = &m_wkVidCellWeaponBase;
                    m_currentVidCellWeaponExtend = &m_wkVidCellWeaponExtend;
                }

                field_34E6 = cnt;

                if ((itemFlags & 0x80) != 0) {
                    field_34E2 = 1;
                }

                m_a1VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "A1"), FALSE, TRUE, TRUE);
                if ((m_animationID & 0x8) != 0) {
                    m_a2VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "A2"), FALSE, TRUE, TRUE);
                }
                if ((m_animationID & 0x4) != 0) {
                    m_a3VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "A3"), FALSE, TRUE, TRUE);
                }
                if ((m_animationID & 0x2) != 0) {
                    m_a4VidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "A4"), FALSE, TRUE, TRUE);
                }
                m_sdVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "SDe"), FALSE, TRUE, TRUE);
                m_ghVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "GH"), FALSE, TRUE, TRUE);
                m_slVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Sl"), FALSE, TRUE, TRUE);
                m_guVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Gu"), FALSE, TRUE, TRUE);
                if ((m_animationID & 0x1) != 0) {
                    m_spVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Sp"), FALSE, TRUE, TRUE);
                    m_caVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Ca"), FALSE, TRUE, TRUE);
                }
                m_scVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Sc"), FALSE, TRUE, TRUE);
                m_sdVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Sd"), FALSE, TRUE, TRUE);
                m_twVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Tw"), FALSE, TRUE, TRUE);
                m_wkVidCellWeaponBase.SetResRef(CResRef(m_resRef + resRef[0] + "Wk"), FALSE, TRUE, TRUE);

                if (!MIRROR_BAM) {
                    m_a1VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "A1E"), FALSE, TRUE, TRUE);
                    if ((m_animationID & 0x8) != 0) {
                        m_a2VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "A2E"), FALSE, TRUE, TRUE);
                    }
                    if ((m_animationID & 0x4) != 0) {
                        m_a3VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "A3E"), FALSE, TRUE, TRUE);
                    }
                    if ((m_animationID & 0x2) != 0) {
                        m_a4VidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "A4E"), FALSE, TRUE, TRUE);
                    }
                    m_sdVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "DeE"), FALSE, TRUE, TRUE);
                    m_ghVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "GHE"), FALSE, TRUE, TRUE);
                    m_slVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "SlE"), FALSE, TRUE, TRUE);
                    m_guVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "GuE"), FALSE, TRUE, TRUE);
                    if ((m_animationID & 0x1) != 0) {
                        m_spVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "SpE"), FALSE, TRUE, TRUE);
                        m_caVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "CaE"), FALSE, TRUE, TRUE);
                    }
                    m_scVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "ScE"), FALSE, TRUE, TRUE);
                    m_sdVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "SdE"), FALSE, TRUE, TRUE);
                    m_twVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "TwE"), FALSE, TRUE, TRUE);
                    m_wkVidCellWeaponExtend.SetResRef(CResRef(m_resRef + resRef[0] + "WkE"), FALSE, TRUE, TRUE);
                }

                break;
            }
        }

        if (cnt != 3) {
            for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
                m_weaponPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            }

            if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
                m_currentVidCellWeapon = m_currentVidCellWeaponExtend;
            } else {
                m_currentVidCellWeapon = m_currentVidCellBase;
            }

            if (!MIRROR_BAM && m_currentBamDirection > m_extendDirectionTest) {
                m_currentVidCellWeapon->SequenceSet(8 * m_currentBamSequence + ((17 - m_currentBamDirection) % 16) / 2);
            } else {
                m_currentVidCellWeapon->SequenceSet(8 * m_currentBamSequence + m_currentBamDirection / 2);
            }
            m_currentVidCellWeapon->FrameSet(m_currentVidCell->GetCurrentFrameId());
        } else {
            field_34E6 = 0;
            m_currentVidCellWeaponBase = NULL;

            m_a1VidCellWeaponBase.CancelRequest();
            m_a2VidCellWeaponBase.CancelRequest();
            m_a3VidCellWeaponBase.CancelRequest();
            m_a4VidCellWeaponBase.CancelRequest();
            m_deVidCellWeaponBase.CancelRequest();
            m_ghVidCellWeaponBase.CancelRequest();
            m_slVidCellWeaponBase.CancelRequest();
            m_guVidCellWeaponBase.CancelRequest();
            m_spVidCellWeaponBase.CancelRequest();
            m_caVidCellWeaponBase.CancelRequest();
            m_scVidCellWeaponBase.CancelRequest();
            m_sdVidCellWeaponBase.CancelRequest();
            m_twVidCellWeaponBase.CancelRequest();
            m_wkVidCellWeaponBase.CancelRequest();

            if (!MIRROR_BAM) {
                m_a1VidCellWeaponExtend.CancelRequest();
                m_a2VidCellWeaponExtend.CancelRequest();
                m_a3VidCellWeaponExtend.CancelRequest();
                m_a4VidCellWeaponExtend.CancelRequest();
                m_deVidCellWeaponExtend.CancelRequest();
                m_ghVidCellWeaponExtend.CancelRequest();
                m_slVidCellWeaponExtend.CancelRequest();
                m_guVidCellWeaponExtend.CancelRequest();
                m_spVidCellWeaponExtend.CancelRequest();
                m_caVidCellWeaponExtend.CancelRequest();
                m_scVidCellWeaponExtend.CancelRequest();
                m_sdVidCellWeaponExtend.CancelRequest();
                m_twVidCellWeaponExtend.CancelRequest();
                m_wkVidCellWeaponExtend.CancelRequest();
                m_currentVidCellWeaponExtend = NULL;
            }
            m_currentVidCellWeapon = NULL;
        }
    } else {
        field_34E6 = 0;
        m_currentVidCellWeaponBase = NULL;

        m_a1VidCellWeaponBase.CancelRequest();
        m_a2VidCellWeaponBase.CancelRequest();
        m_a3VidCellWeaponBase.CancelRequest();
        m_a4VidCellWeaponBase.CancelRequest();
        m_deVidCellWeaponBase.CancelRequest();
        m_ghVidCellWeaponBase.CancelRequest();
        m_slVidCellWeaponBase.CancelRequest();
        m_guVidCellWeaponBase.CancelRequest();
        m_spVidCellWeaponBase.CancelRequest();
        m_caVidCellWeaponBase.CancelRequest();
        m_scVidCellWeaponBase.CancelRequest();
        m_sdVidCellWeaponBase.CancelRequest();
        m_twVidCellWeaponBase.CancelRequest();
        m_wkVidCellWeaponBase.CancelRequest();

        if (!MIRROR_BAM) {
            m_a1VidCellWeaponExtend.CancelRequest();
            m_a2VidCellWeaponExtend.CancelRequest();
            m_a3VidCellWeaponExtend.CancelRequest();
            m_a4VidCellWeaponExtend.CancelRequest();
            m_deVidCellWeaponExtend.CancelRequest();
            m_ghVidCellWeaponExtend.CancelRequest();
            m_slVidCellWeaponExtend.CancelRequest();
            m_guVidCellWeaponExtend.CancelRequest();
            m_spVidCellWeaponExtend.CancelRequest();
            m_caVidCellWeaponExtend.CancelRequest();
            m_scVidCellWeaponExtend.CancelRequest();
            m_sdVidCellWeaponExtend.CancelRequest();
            m_twVidCellWeaponExtend.CancelRequest();
            m_wkVidCellWeaponExtend.CancelRequest();
            m_currentVidCellWeaponExtend = NULL;
        }
        m_currentVidCellWeapon = NULL;
    }
}

// 0x6ED720
CVidPalette* CGameAnimationTypeMonsterIcewindNew::GetAnimationPalette(BYTE range)
{
    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28129
        UTIL_ASSERT(m_currentVidCell != NULL);

        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28143
        UTIL_ASSERT(FALSE);
    }

    return NULL;
}

// 0x6ED7D0
void CGameAnimationTypeMonsterIcewindNew::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";

    switch (range) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28173
        UTIL_ASSERT(m_currentVidCell != NULL);

        resRef = m_resRef;
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28199
        UTIL_ASSERT(FALSE);
    }
}

// 0x6ED8A0
char* CGameAnimationTypeMonsterIcewindNew::GetSndWalk(SHORT tableIndex)
{
    if ((m_animationID & 0xFFF0) == 0xF100
        || (m_animationID & 0xFFF0) == 0xF110) {
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

    return szTemp;
}

// 0x6EDA20
void CGameAnimationTypeMonsterIcewindNew::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28375
    UTIL_ASSERT(FALSE);

    switch (colorRange & 0xF0) {
    case 0x00:
        m_a1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_a4VidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_deVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_ghVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_slVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_guVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_spVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_caVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_scVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_sdVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_twVidCellBase.DeleteRangeAffects(colorRange & 0xF);
        m_wkVidCellBase.DeleteRangeAffects(colorRange & 0xF);

        m_a1VidCellBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellBase.UnsuppressTint(colorRange & 0xF);
        m_a4VidCellBase.UnsuppressTint(colorRange & 0xF);
        m_deVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_ghVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_slVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_guVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_spVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_caVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_scVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_sdVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_twVidCellBase.UnsuppressTint(colorRange & 0xF);
        m_wkVidCellBase.UnsuppressTint(colorRange & 0xF);

        if (!MIRROR_BAM) {
            m_a1VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a4VidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_deVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_ghVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_slVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_guVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_spVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_scVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_sdVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_twVidCellExtend.DeleteRangeAffects(colorRange & 0xF);
            m_wkVidCellExtend.DeleteRangeAffects(colorRange & 0xF);

            m_a1VidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_a4VidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_deVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_ghVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_slVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_guVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_spVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_caVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_scVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_sdVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_twVidCellExtend.UnsuppressTint(colorRange & 0xF);
            m_wkVidCellExtend.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x10:
        m_a1VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a2VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a3VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_a4VidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_deVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_ghVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_slVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_guVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_spVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_caVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_scVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_sdVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_twVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);
        m_wkVidCellWeaponBase.DeleteRangeAffects(colorRange & 0xF);

        m_a1VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a2VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a3VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_a4VidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_deVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_ghVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_slVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_guVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_spVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_caVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_scVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_sdVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_twVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);
        m_wkVidCellWeaponBase.UnsuppressTint(colorRange & 0xF);

        if (!MIRROR_BAM) {
            m_a1VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a2VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a3VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_a4VidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_deVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_ghVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_slVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_guVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_spVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_caVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_scVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_sdVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_twVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);
            m_wkVidCellWeaponExtend.DeleteRangeAffects(colorRange & 0xF);

            m_a1VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a2VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a3VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_a4VidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_deVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_ghVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_slVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_guVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_spVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_caVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_scVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_sdVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_twVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
            m_wkVidCellWeaponExtend.UnsuppressTint(colorRange & 0xF);
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28511
        UTIL_ASSERT(FALSE);
    }
}

// 0x6EE070
void CGameAnimationTypeMonsterIcewindNew::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28536
    UTIL_ASSERT(m_currentVidCell != NULL);

    for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
        ClearColorEffects(colorRange);
        ClearColorEffects(colorRange | 0x10);
    }
}

// 0x6EE0D0
void CGameAnimationTypeMonsterIcewindNew::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28568
        UTIL_ASSERT(m_currentVidCell != NULL);

        m_a1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a2VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a3VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a4VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_deVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_ghVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_slVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_guVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_spVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_caVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_scVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_sdVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_twVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_wkVidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

        if (effectType != 0) {
            m_a1VidCellBase.SuppressTint(colorRange & 0xF);
            m_a2VidCellBase.SuppressTint(colorRange & 0xF);
            m_a3VidCellBase.SuppressTint(colorRange & 0xF);
            m_a4VidCellBase.SuppressTint(colorRange & 0xF);
            m_deVidCellBase.SuppressTint(colorRange & 0xF);
            m_ghVidCellBase.SuppressTint(colorRange & 0xF);
            m_slVidCellBase.SuppressTint(colorRange & 0xF);
            m_guVidCellBase.SuppressTint(colorRange & 0xF);
            m_spVidCellBase.SuppressTint(colorRange & 0xF);
            m_caVidCellBase.SuppressTint(colorRange & 0xF);
            m_scVidCellBase.SuppressTint(colorRange & 0xF);
            m_sdVidCellBase.SuppressTint(colorRange & 0xF);
            m_twVidCellBase.SuppressTint(colorRange & 0xF);
            m_wkVidCellBase.SuppressTint(colorRange & 0xF);
        }

        if (!MIRROR_BAM) {
            m_a1VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a4VidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_deVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_ghVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_slVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_guVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_spVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_scVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_sdVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_twVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_wkVidCellExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_a1VidCellExtend.SuppressTint(colorRange & 0xF);
                m_a2VidCellExtend.SuppressTint(colorRange & 0xF);
                m_a3VidCellExtend.SuppressTint(colorRange & 0xF);
                m_a4VidCellExtend.SuppressTint(colorRange & 0xF);
                m_deVidCellExtend.SuppressTint(colorRange & 0xF);
                m_ghVidCellExtend.SuppressTint(colorRange & 0xF);
                m_slVidCellExtend.SuppressTint(colorRange & 0xF);
                m_guVidCellExtend.SuppressTint(colorRange & 0xF);
                m_spVidCellExtend.SuppressTint(colorRange & 0xF);
                m_caVidCellExtend.SuppressTint(colorRange & 0xF);
                m_scVidCellExtend.SuppressTint(colorRange & 0xF);
                m_sdVidCellExtend.SuppressTint(colorRange & 0xF);
                m_twVidCellExtend.SuppressTint(colorRange & 0xF);
                m_wkVidCellExtend.SuppressTint(colorRange & 0xF);
            }
        }
        break;
    case 0x10:
        m_a1VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a2VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a3VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_a4VidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_deVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_ghVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_slVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_guVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_spVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_caVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_scVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_sdVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_twVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
        m_wkVidCellWeaponBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

        if (effectType != 0) {
            m_a1VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_a2VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_a3VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_a4VidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_deVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_ghVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_slVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_guVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_spVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_caVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_scVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_sdVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_twVidCellWeaponBase.SuppressTint(colorRange & 0xF);
            m_wkVidCellWeaponBase.SuppressTint(colorRange & 0xF);
        }

        if (!MIRROR_BAM) {
            m_a1VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a2VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a3VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_a4VidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_deVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_ghVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_slVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_guVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_spVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_caVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_scVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_sdVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_twVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);
            m_wkVidCellWeaponExtend.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_a1VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_a2VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_a3VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_a4VidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_deVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_ghVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_slVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_guVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_spVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_caVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_scVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_sdVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_twVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
                m_wkVidCellWeaponExtend.SuppressTint(colorRange & 0xF);
            }
        }
        break;
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28716
        UTIL_ASSERT(m_currentVidCell != NULL);
    }
}

// 0x6EE930
void CGameAnimationTypeMonsterIcewindNew::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28741
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

// 0x6EE9E0
void CGameAnimationTypeMonsterIcewindNew::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28782
        UTIL_ASSERT(m_currentVidCell != NULL);

        m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        break;
    case 0x10:
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_weaponPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 28799
        UTIL_ASSERT(FALSE);
    }
}

// 0x6EEB10
void CGameAnimationTypeMonsterIcewindNew::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28826
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

// 0x6EEBA0
void CGameAnimationTypeMonsterIcewindNew::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28858
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 28859
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (!MIRROR_BAM) {
        dwRenderFlags |= 0x4;
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
    } else {
        if (m_currentBamDirection > m_extendDirectionTest) {
            dwRenderFlags |= CInfinity::MIRROR_FX;
        }
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
        if (transparency != 0) {
            dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
        }
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        m_currentVidCell->SetTintColor(rgbTintColor);

        if (m_renderWeapons
            && m_currentVidCellWeapon != NULL
            && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_currentVidCellWeapon->SetTintColor(rgbTintColor);
        }

        if (transparency != 0) {
            dwRenderFlags |= 0x2;
        }

        pInfinity->FXRender(m_currentVidCell,
            ptReference.x,
            ptReference.y,
            dwRenderFlags | 0x2,
            transparency);

        if (m_renderWeapons
            && m_currentVidCellWeapon != NULL
            && m_currentVidCellWeapon->GetResRef().IsValid()) {
            pInfinity->FXRender(m_currentVidCellWeapon,
                ptReference.x,
                ptReference.y,
                dwRenderFlags | 0x2,
                transparency);
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

// 0x6EEE20
SHORT CGameAnimationTypeMonsterIcewindNew::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;
    m_renderWeapons = TRUE;

    switch (nSequence) {
    case 1:
        m_currentVidCellBase = &m_guVidCellBase;
        m_currentVidCellExtend = &m_guVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_guVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_guVidCellWeaponExtend;
        }
        break;
    case 2:
        if ((m_animationID & 0x1) != 0) {
            m_currentVidCellBase = &m_caVidCellBase;
            m_currentVidCellExtend = &m_caVidCellExtend;
            m_currentBamSequence = 0;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_caVidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_caVidCellWeaponExtend;
            }
        }
        break;
    case 3:
        if ((m_animationID & 0x1) != 0) {
            m_currentVidCellBase = &m_spVidCellBase;
            m_currentVidCellExtend = &m_spVidCellExtend;
            m_currentBamSequence = 0;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_spVidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_spVidCellWeaponExtend;
            }
        }
        break;
    case 4:
        m_currentVidCellBase = &m_ghVidCellBase;
        m_currentVidCellExtend = &m_ghVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_ghVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_ghVidCellWeaponExtend;
        }
        break;
    case 5:
        m_currentVidCellBase = &m_deVidCellBase;
        m_currentVidCellExtend = &m_deVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_deVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_deVidCellWeaponExtend;
        }
    case 6:
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_sdVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_sdVidCellBase;
        m_currentVidCellExtend = &m_sdVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_sdVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_sdVidCellWeaponExtend;
        }
        break;
    case 7:
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_scVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_scVidCellBase;
        m_currentVidCellExtend = &m_scVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_scVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_scVidCellWeaponExtend;
        }
        break;
    case 8:
        if ((m_animationID & 2) != 0) {
            m_currentVidCellBase = &m_a4VidCellBase;
            m_currentVidCellExtend = &m_a4VidCellExtend;
            m_currentBamSequence = 0;
            nSequence = 8;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_a4VidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_a4VidCellWeaponExtend;
            }
        }
        break;
    case 9:
        m_currentVidCellBase = &m_twVidCellBase;
        m_currentVidCellExtend = &m_twVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_twVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_twVidCellWeaponExtend;
        }
        break;
    case 10:
        m_currentVidCellBase = &m_wkVidCellBase;
        m_currentVidCellExtend = &m_wkVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_wkVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_wkVidCellWeaponExtend;
        }
        break;
    case 11:
        m_currentVidCellBase = &m_a1VidCellBase;
        m_currentVidCellExtend = &m_a1VidCellExtend;
        m_currentBamSequence = 0;
        nSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_a1VidCellWeaponExtend;
        }
        break;
    case 12:
        if ((m_animationID & 4) != 0) {
            m_currentVidCellBase = &m_a3VidCellBase;
            m_currentVidCellExtend = &m_a3VidCellExtend;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_a3VidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_a3VidCellWeaponExtend;
            }
        } else {
            m_currentVidCellBase = &m_a1VidCellBase;
            m_currentVidCellExtend = &m_a1VidCellExtend;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_a1VidCellWeaponExtend;
            }
        }
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 13:
        if ((m_animationID & 8) != 0) {
            m_currentVidCellBase = &m_a2VidCellBase;
            m_currentVidCellExtend = &m_a2VidCellExtend;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_a2VidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_a2VidCellWeaponExtend;
            }
        } else {
            m_currentVidCellBase = &m_a1VidCellBase;
            m_currentVidCellExtend = &m_a1VidCellExtend;
            if (m_currentVidCellWeapon != NULL) {
                m_currentVidCellWeaponBase = &m_a1VidCellWeaponBase;
                m_currentVidCellWeaponExtend = &m_a1VidCellWeaponExtend;
            }
        }
        m_currentBamSequence = 0;
        nSequence = 0;
        break;
    case 14:
    case 15:
        nSequence = 7;
        if (m_currentBamSequence != 0
            || m_currentVidCellBase != &m_scVidCellBase) {
            bRandomFrame = TRUE;
        }
        m_currentVidCellBase = &m_scVidCellBase;
        m_currentVidCellExtend = &m_scVidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_scVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_scVidCellWeaponExtend;
        }
        break;
    case 17:
        m_currentVidCellBase = &m_a1VidCellBase;
        m_currentVidCellExtend = &m_a1VidCellExtend;
        m_currentBamSequence = 0;
        if (m_currentVidCellWeapon != NULL) {
            m_currentVidCellWeaponBase = &m_slVidCellWeaponBase;
            m_currentVidCellWeaponExtend = &m_slVidCellWeaponExtend;
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 29268
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
        if (m_currentVidCellWeapon != NULL && m_currentVidCellWeapon->GetResRef().IsValid()) {
            m_currentVidCellWeapon->FrameSet(nFrame);
        }
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

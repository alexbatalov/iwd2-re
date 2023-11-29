#include "CGameAnimationType.h"

#include "CGameAnimationTypeAmbient.h"
#include "CGameAnimationTypeAmbientStatic.h"
#include "CGameAnimationTypeCharacter.h"
#include "CGameAnimationTypeCharacterOld.h"
#include "CGameAnimationTypeFlying.h"
#include "CGameAnimationTypeMonster.h"
#include "CGameAnimationTypeMonsterAnkheg.h"
#include "CGameAnimationTypeMonsterIcewind.h"
#include "CGameAnimationTypeMonsterLarge.h"
#include "CGameAnimationTypeMonsterLarge16.h"
#include "CGameAnimationTypeMonsterLayered.h"
#include "CGameAnimationTypeMonsterLayeredSpell.h"
#include "CGameAnimationTypeMonsterMulti.h"
#include "CGameAnimationTypeMonsterOld.h"
#include "CGameAnimationTypeMonsterQuadrant.h"
#include "CGameAnimationTypeTownStatic.h"

// 0x8F8E10
const CString CGameAnimationType::ROUND_BASE("RNDBASE");

// 0x85AB48
const BYTE CGameAnimationType::RANGE_BODY = 0x0;

// 0x85AB49
const BYTE CGameAnimationType::RANGE_WEAPON = 0x10;

// 0x85AB4A
const BYTE CGameAnimationType::RANGE_SHIELD = 0x20;

// 0x85ABAB
const BYTE CGameAnimationType::RANGE_HELMET = 0x30;

// 0x8F8E14
BOOL CGameAnimationType::MIRROR_BAM;

// 0x6A15F0
CGameAnimationType::CGameAnimationType()
{
    m_rEllipse.left = -16;
    m_rEllipse.top = -12;
    m_rEllipse.right = 16;
    m_rEllipse.bottom = 12;
    m_animationID = 0;
    field_3E8 = 0;
    field_3FB = 0;
    field_3FC = 0;
    m_moveScale = 0;
    m_moveScaleCurrent = 0;
    m_colorBlood = 47;
    m_colorChunks = 0;
    m_nSndFreq = -1;
    m_pSndDeath = "FAL_02B";
    memset(m_neckOffsets, 0, sizeof(m_neckOffsets));
    m_personalSpace = 3;
    m_castFrame = 4;

    CString sName;
    for (char c = '1'; c < '6'; c++) {
        sName = ROUND_BASE + c;
        m_combatRounds[c - '1'].SetResRef(CResRef(sName), TRUE, TRUE);
    }
}

// 0x6A1800
CGameAnimationType* CGameAnimationType::SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    CGameAnimationType* pAnimation;

    switch (animationID & 0xF000) {
    case 0x1000:
        switch (animationID & 0xF00) {
        case 0x000:
        case 0x100:
            pAnimation = new CGameAnimationTypeMonsterQuadrant(animationID, colorRangeValues, facing & 0xF);
            break;
        default:
            pAnimation = new CGameAnimationTypeMonsterMulti(animationID, colorRangeValues, facing & 0xF);
            break;
        }
        break;
    case 0x2000:
        // TODO: Incomplete.
        break;
    case 0x3000:
        pAnimation = new CGameAnimationTypeMonsterAnkheg(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0x4000:
        pAnimation = new CGameAnimationTypeTownStatic(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0x5000:
    case 0x6000:
        if (CGameAnimationTypeCharacterOld::NewSupport(animationID)) {
            pAnimation = new CGameAnimationTypeCharacter(animationID, colorRangeValues, facing & 0xF);
        } else {
            pAnimation = new CGameAnimationTypeCharacterOld(animationID, colorRangeValues, facing & 0xF);
        }
        break;
    case 0x7000:
        if (CGameAnimationTypeMonsterOld::NewSupport(animationID)) {
            pAnimation = new CGameAnimationTypeMonster(animationID, colorRangeValues, facing & 0xF);
        } else {
            pAnimation = new CGameAnimationTypeMonsterOld(animationID, colorRangeValues, facing & 0xF);
        }
        break;
    case 0x8000:
        pAnimation = new CGameAnimationTypeMonsterLayered(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0x9000:
        pAnimation = new CGameAnimationTypeMonsterLarge(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xA000:
        pAnimation = new CGameAnimationTypeMonsterLarge16(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xB000:
        pAnimation = new CGameAnimationTypeAmbientStatic(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xC000:
        pAnimation = new CGameAnimationTypeAmbient(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xD000:
        pAnimation = new CGameAnimationTypeFlying(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xE000:
        pAnimation = new CGameAnimationTypeMonsterIcewind(animationID, colorRangeValues, facing & 0xF);
        break;
    case 0xF000:
        // TODO: Incomplete.
        break;
    }

    pAnimation->m_animationID = animationID;

    return pAnimation;
}

// 0x55D060
CGameAnimationType::~CGameAnimationType()
{
}

// 0x78E750
void CGameAnimationType::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
}

// 0x799E40
void CGameAnimationType::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
}

// 0x799E60
void CGameAnimationType::ChangeDirection(SHORT nDirection)
{
}

// 0x778900
void CGameAnimationType::EquipArmor(CHAR armorLevel, BYTE* colorRangeValues)
{
}

// 0x799E20
CVidPalette* CGameAnimationType::GetAnimationPalette(BYTE range)
{
    return NULL;
}

// 0x55D080
void CGameAnimationType::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";
}

// 0x6A3130
BOOLEAN CGameAnimationType::CanLieDown()
{
    return TRUE;
}

// 0x6A3130
BOOLEAN CGameAnimationType::DetectedByInfravision()
{
    return TRUE;
}

// 0x55D0A0
WORD CGameAnimationType::GetCastFrame()
{
    return m_castFrame;
}

// 0x55D0B0
BYTE CGameAnimationType::GetColorBlood()
{
    return m_colorBlood;
}

// 0x55D0C0
BYTE CGameAnimationType::GetColorChunks()
{
    return m_colorChunks;
}

// 0x6A3C60
BYTE CGameAnimationType::GetListType()
{
    return 0;
}

// 0x55D0D0
BYTE CGameAnimationType::GetMoveScale()
{
    return m_moveScaleCurrent;
}

// 0x55D0E0
void CGameAnimationType::SetMoveScale(BYTE scale)
{
    m_moveScaleCurrent = scale;
}

// 0x55D0F0
void CGameAnimationType::ResetMoveScale()
{
    m_moveScaleCurrent = m_moveScale;
}

// 0x45B3A0
BYTE CGameAnimationType::GetMoveScaleDefault()
{
    return m_moveScale;
}

// 0x55D100
NECK_POINTS CGameAnimationType::GetNeckOffsets(SHORT nDirection)
{
    return m_neckOffsets[nDirection / 2];
}

// 0x4699E0
const CRect& CGameAnimationType::GetEllipseRect()
{
    return m_rEllipse;
}

// 0x78E6E0
BOOL CGameAnimationType::GetPathSmooth()
{
    return FALSE;
}

// 0x55D120
BYTE CGameAnimationType::GetPersonalSpace()
{
    return m_personalSpace;
}

// 0x55D140
char* CGameAnimationType::GetSndArmor()
{
    return "";
}

// 0x55D130
const char* CGameAnimationType::GetSndDeath()
{
    return m_pSndDeath;
}

// 0x55D140
char* CGameAnimationType::GetSndReady()
{
    return "";
}

// 0x55D150
const char* CGameAnimationType::GetSndWalk(SHORT a1)
{
    return "";
}

// 0x55D160
DWORD CGameAnimationType::GetSndWalkFreq()
{
    return m_nSndFreq;
}

// 0x55D170
void CGameAnimationType::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
}

// 0x49FC40
BOOL CGameAnimationType::IsFalseColor()
{
    return TRUE;
}

// 0x78E6E0
BOOL CGameAnimationType::IsInvulnerable()
{
    return FALSE;
}

// 0x78E6E0
BOOL CGameAnimationType::IsMirroring()
{
    return FALSE;
}

// 0x49FC40
BOOL CGameAnimationType::IsBeginningOfSequence()
{
    return TRUE;
}

// 0x49FC40
BOOL CGameAnimationType::IsEndOfSequence()
{
    return TRUE;
}

// 0x78E730
void CGameAnimationType::IncrementFrame()
{
}

// 0x78E730
void CGameAnimationType::DecrementFrame()
{
}

// 0x799E60
void CGameAnimationType::ClearColorEffects(BYTE colorRange)
{
}

// 0x78E730
void CGameAnimationType::ClearColorEffectsAll()
{
}

// 0x7B5450
void CGameAnimationType::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
}

// 0x78E750
void CGameAnimationType::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
}

// 0x778900
void CGameAnimationType::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
}

// 0x799E60
void CGameAnimationType::SetColorRangeAll(BYTE rangeValue)
{
}

// 0x55D180
SHORT CGameAnimationType::SetSequence(SHORT nSequence)
{
    return nSequence;
}

// 0x55D190
BYTE CGameAnimationType::GetAttackFrameType(BYTE numAttacks, BYTE speedFactor, BYTE combatFrame)
{
    if (numAttacks > 5 || speedFactor > 10) {
        return 0;
    }

    if (combatFrame > 100) {
        return 15;
    }

    return m_combatRounds[numAttacks - 1].GetPixelValue(combatFrame, speedFactor, FALSE);
}

// 0x49FC40
BOOL CGameAnimationType::GetAboveGround()
{
    return TRUE;
}

// 0x55D1F0
SHORT CGameAnimationType::GetAwakePlayInReverse()
{
    return 1;
}

// 0x55D200
SHORT CGameAnimationType::GetCastHeight()
{
    return 35;
}

// 0x55D210
SHORT CGameAnimationType::GetCurrentFrame()
{
    return -1;
}

// 0x55D220
BOOLEAN CGameAnimationType::GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame)
{
    return FALSE;
}

// 0x6A1E80
void CGameAnimationType::SetNeckOffsets(SHORT Sx, SHORT Sy, SHORT SWx, SHORT SWy, SHORT Wx, SHORT Wy, SHORT NWx, SHORT NWy, SHORT Nx, SHORT Ny, SHORT NEx, SHORT NEy, SHORT Ex, SHORT Ey, SHORT SEx, SHORT SEy)
{
    m_neckOffsets[0].x = Sx;
    m_neckOffsets[0].y = Sy;
    m_neckOffsets[1].x = SWx;
    m_neckOffsets[1].y = SWy;
    m_neckOffsets[2].x = Wx;
    m_neckOffsets[2].y = Wy;
    m_neckOffsets[3].x = NWx;
    m_neckOffsets[3].y = NWy;
    m_neckOffsets[4].x = Nx;
    m_neckOffsets[4].y = Ny;
    m_neckOffsets[5].x = NEx;
    m_neckOffsets[5].y = NEy;
    m_neckOffsets[6].x = Ex;
    m_neckOffsets[6].y = Ey;
    m_neckOffsets[7].x = SEx;
    m_neckOffsets[7].y = SEy;
}

// 0x6A1F20
void CGameAnimationType::CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    ptReference.x = 256;
    ptReference.y = 256;

    rFx.left = 0;
    rFx.top = 0;
    rFx.right = 512;
    rFx.bottom = 512;
}

// 0x55D230
BOOLEAN CGameAnimationType::GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet)
{
    return FALSE;
}

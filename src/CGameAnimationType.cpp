#include "CGameAnimationType.h"

// 0x8F8E10
const CString CGameAnimationType::ROUND_BASE("RNDBASE");

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

// 0x55D080
void CGameAnimationType::GetAnimationResRef(CString& resRef, BYTE range)
{
    resRef = "";
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

// 0x55D120
BYTE CGameAnimationType::GetPersonalSpace()
{
    return m_personalSpace;
}

// 0x55D140
const char* CGameAnimationType::GetSndArmor()
{
    return "";
}

// 0x55D130
const char* CGameAnimationType::GetSndDeath()
{
    return m_pSndDeath;
}

// 0x55D140
const char* CGameAnimationType::GetSndReady()
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

// 0x49FC40
BOOL CGameAnimationType::IsFalseColor()
{
    return TRUE;
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

// 0x55D200
SHORT CGameAnimationType::GetCastHeight()
{
    return 35;
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

#include "CGameAnimationType.h"

// 0x8F8E14
BOOL CGameAnimationType::MIRROR_BAM;

// 0x55D060
CGameAnimationType::~CGameAnimationType()
{
}

// 0x799E40
void CGameAnimationType::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
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

// 0x55D200
SHORT CGameAnimationType::GetCastHeight()
{
    return 35;
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

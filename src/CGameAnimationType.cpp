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

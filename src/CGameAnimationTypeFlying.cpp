#include "CGameAnimationTypeFlying.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x6A3950
CGameAnimationTypeFlying::CGameAnimationTypeFlying(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    CString v1;

    m_animationID = animationID;
    m_falseColor = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);
    m_colorChunks = -1;
    m_pSndDeath = "";

    switch (animationID & 0xF00) {
    case 0x0:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AEAG";
        break;
    case 0x100:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AGUL";
        break;
    case 0x200:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "AVUL";
        break;
    case 0x300:
    case 0x400:
        m_moveScale = 8;
        m_moveScaleCurrent = 8;
        v1 = "ABIR";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1273
        UTIL_ASSERT(FALSE);
    }

    m_falseColor = FALSE;

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(v1 + "G1"), FALSE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (USHORT nRange = 0; nRange < CVidPalette::NUM_RANGES; nRange++) {
            m_charPalette.SetRange(nRange, *colorRangeValues++, g_pBaldurChitin->GetObjectGame()->m_rgbMasterBitmap);
        }
        m_g1VidCellBase.SetPalette(m_charPalette);
    }

    m_currentBamSequence = 1;
    if (m_falseColor) {
        m_charPalette.SetPaletteEntry(CVidPalette::SHADOW_ENTRY, g_pBaldurChitin->GetCurrentVideoMode()->GetTransparentColor());
    } else {
        m_g1VidCellBase.m_bShadowOn = FALSE;
    }

    m_extendDirectionTest = CGameSprite::DIR_N;

    // NOTE: Uninline.
    ChangeDirection(facing);
}

// 0x6A3E10
CGameAnimationTypeFlying::~CGameAnimationTypeFlying()
{
}

// 0x6A3E90
void CGameAnimationTypeFlying::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1318
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6A3F00
void CGameAnimationTypeFlying::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    if (m_currentBamDirection > m_extendDirectionTest) {
        rGCBounds.left = ptReference.x + pos.x - nWidth;
    } else {
        rGCBounds.left = pos.x - ptReference.x;
    }

    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6A3F60
void CGameAnimationTypeFlying::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1379
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;
    m_currentVidCell = m_currentVidCellBase;

    if (m_currentBamDirection > m_extendDirectionTest) {
        m_currentVidCell->SequenceSet((16 - m_currentBamDirection) % 16 + 9 * m_currentBamSequence);
    } else {
        m_currentVidCell->SequenceSet(m_currentBamDirection + 9 * m_currentBamSequence);
    }
}

// 0x6A3C70
BYTE CGameAnimationTypeFlying::GetListType()
{
    return CGAMEOBJECT_LIST_FLIGHT;
}

// 0x6A4EA0
BOOL CGameAnimationTypeFlying::IsFalseColor()
{
    return m_falseColor;
}

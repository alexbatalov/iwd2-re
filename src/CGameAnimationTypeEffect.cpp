#include "CGameAnimationTypeEffect.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x6A1F50
CGameAnimationTypeEffect::CGameAnimationTypeEffect(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_palette(CVidPalette::TYPE_RANGE)
{
    BYTE colorRange;
    BYTE cnt;
    SHORT nFrame;

    m_animationID = animationID;
    field_5E7 = 0;
    m_translucent = 0;
    field_5E1 = 0;
    m_colorChunks = -1;
    m_bRender = TRUE;
    m_pSndDeath = "";

    switch (animationID & 0xF00) {
    case 0x000:
        m_g1VidCell.SetResRef(CResRef("SPFLAMES"), FALSE, TRUE, TRUE);
        m_g1VidCell.SequenceSet(0);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 1;
        field_5E1 = 1;
        break;
    case 0x100:
        m_g1VidCell.SetResRef(CResRef("SPCHUNKS"), FALSE, TRUE, TRUE);
        m_g1VidCellShadow.SetResRef(CResRef("SPSHADOW"), FALSE, TRUE, TRUE);
        for (colorRange = 0; colorRange < 7; colorRange++) {
            m_palette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        m_g1VidCell.SetPalette(m_palette);
        cnt = static_cast<BYTE>(m_g1VidCell.GetNumberSequences(FALSE));
        if (cnt != 0) {
            m_currentBamSequence = rand() % cnt;
        } else {
            m_currentBamSequence = 0;
        }
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        m_g1VidCellShadow.SequenceSet(0);
        cnt = m_g1VidCell.GetSequenceLength(m_g1VidCell.m_nCurrentSequence, FALSE);
        if (cnt != 0) {
            nFrame = rand() % cnt;
        } else {
            nFrame = 0;
        }
        m_g1VidCell.FrameSet(nFrame);
        m_g1VidCellShadow.FrameSet(nFrame);
        m_currentVidCellShadow = &m_g1VidCellShadow;
        field_5DE = 0;
        break;
    case 0x200:
        m_g1VidCell.SetResRef(CResRef("SPBLOOD"), FALSE, TRUE, TRUE);
        m_g1VidCellShadow.SetResRef(CResRef("SPSHADOW"), FALSE, TRUE, TRUE);
        switch (animationID & 0xF0) {
        case 0x00:
            m_currentBamSequence = 0;
            break;
        case 0x10:
            m_currentBamSequence = 1;
            break;
        case 0x20:
            m_currentBamSequence = 2;
            break;
        case 0x30:
            m_currentBamSequence = 3;
            break;
        case 0x40:
            m_currentBamSequence = 4;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 655
            UTIL_ASSERT(FALSE);
        }
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        m_g1VidCellShadow.SequenceSet(0);
        cnt = m_g1VidCell.GetSequenceLength(m_g1VidCell.m_nCurrentSequence, FALSE);
        if (cnt != 0) {
            nFrame = rand() % cnt;
        } else {
            nFrame = 0;
        }
        m_g1VidCell.FrameSet(nFrame);
        m_g1VidCellShadow.FrameSet(nFrame);
        m_currentVidCellShadow = &m_g1VidCellShadow;
        field_5DE = 0;
        break;
    case 0x300:
        m_g1VidCell.SetResRef(CResRef("SPSMPUFF"), FALSE, TRUE, TRUE);
        for (colorRange = 0; colorRange < 7; colorRange++) {
            m_palette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        m_currentBamSequence = animationID & 0xF;
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 0;
        m_translucent = 1;
        break;
    case 0x400:
        switch (m_animationID & 0xF0) {
        case 0x00:
            m_g1VidCell.SetResRef(CResRef("SKLH"), FALSE, TRUE, TRUE);
            m_currentBamSequence = 1;
            break;
        case 0x10:
            m_g1VidCell.SetResRef(CResRef("GLPHWRDH"), FALSE, TRUE, TRUE);
            field_5E7 = 1;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 694
            UTIL_ASSERT(FALSE);
        }
        m_g1VidCellShadow.SetResRef(CResRef("SPSHADOW"), FALSE, TRUE, TRUE);
        cnt = static_cast<BYTE>(m_g1VidCell.GetNumberSequences(FALSE));
        if (cnt != 0) {
            m_currentBamSequence = rand() % cnt;
        } else {
            m_currentBamSequence = 0;
        }
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        m_g1VidCellShadow.SequenceSet(0);
        cnt = m_g1VidCell.GetSequenceLength(m_g1VidCell.m_nCurrentSequence, FALSE);
        if (cnt != 0) {
            nFrame = rand() % cnt;
        } else {
            nFrame = 0;
        }
        m_g1VidCell.FrameSet(nFrame);
        m_g1VidCellShadow.FrameSet(nFrame);
        m_currentVidCellShadow = &m_g1VidCellShadow;
        field_5DE = 0;
        break;
    case 0x500:
        switch (m_animationID & 0xF0) {
        case 0x00:
            m_g1VidCell.SetResRef(CResRef("STNKCLDD"), FALSE, TRUE, TRUE);
            m_currentBamSequence = 1;
            break;
        case 0x10:
            m_g1VidCell.SetResRef(CResRef("STNKCLDD"), FALSE, TRUE, TRUE);
            m_currentBamSequence = 0;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 721
            UTIL_ASSERT(FALSE);
        }
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        for (colorRange = 0; colorRange < 7; colorRange++) {
            m_palette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        m_g1VidCell.SetPalette(m_palette);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 1;
        break;
    case 0x600:
        switch (m_animationID & 0xF0) {
        case 0x00:
            m_g1VidCell.SetResRef(CResRef("STNKCLDD"), FALSE, TRUE, TRUE);
            m_currentBamSequence = 1;
            break;
        case 0x10:
            m_g1VidCell.SetResRef(CResRef("STNKCLDD"), FALSE, TRUE, TRUE);
            m_currentBamSequence = 0;
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 746
            UTIL_ASSERT(FALSE);
        }
        m_g1VidCell.SequenceSet(m_currentBamSequence);
        for (colorRange = 0; colorRange < 7; colorRange++) {
            m_palette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        m_g1VidCell.SetPalette(m_palette);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 1;
        break;
    case 0x700:
        switch (m_animationID & 0xF0) {
        case 0x00:
            m_g1VidCell.SetResRef(CResRef("GREASEH"), FALSE, TRUE, TRUE);
            break;
        case 0x10:
            m_g1VidCell.SetResRef(CResRef("GREASED"), FALSE, TRUE, TRUE);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 769
            UTIL_ASSERT(FALSE);
        }
        m_currentBamSequence = 0;
        m_g1VidCell.SequenceSet(0);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 0;
        break;
    case 0x800:
        switch (m_animationID & 0xF0) {
        case 0x00:
            m_g1VidCell.SetResRef(CResRef("WEBENTH"), FALSE, TRUE, TRUE);
            break;
        case 0x10:
            m_g1VidCell.SetResRef(CResRef("WEBENTD"), FALSE, TRUE, TRUE);
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 790
            UTIL_ASSERT(FALSE);
        }
        m_currentBamSequence = 0;
        m_g1VidCell.SequenceSet(0);
        for (colorRange = 0; colorRange < 7; colorRange++) {
            m_palette.SetRange(colorRange,
                colorRangeValues[colorRange],
                *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }
        m_g1VidCell.SetPalette(m_palette);
        m_g1VidCell.FrameSet(0);
        m_currentVidCellShadow = NULL;
        field_5DE = 0;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 803
        UTIL_ASSERT(FALSE);
    }

    m_currentVidCell = &m_g1VidCell;
    m_extendDirectionTest = CGameSprite::DIR_N;
    ChangeDirection(facing);
}

// 0x6A3140
BOOL CGameAnimationTypeEffect::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 746
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6A3180
SHORT CGameAnimationTypeEffect::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 751
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6A31F0
CGameAnimationTypeEffect::~CGameAnimationTypeEffect()
{
}

// 0x6A3280
void CGameAnimationTypeEffect::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 831
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptChar;
    m_currentVidCell->GetCurrentCenterPoint(ptChar, FALSE);

    if (m_currentVidCellShadow != NULL) {
        ptChar.y += posZ;
    }

    ptReference = ptChar;

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);

    if (m_currentVidCellShadow != NULL) {
        CPoint ptShadow;
        m_currentVidCellShadow->GetCurrentCenterPoint(ptShadow, FALSE);

        ptReference.x = max(ptShadow.x, ptReference.x);
        ptReference.y = max(ptShadow.y, ptReference.y);

        frameSize.cx += ptReference.x - ptChar.x;
        frameSize.cy += ptReference.y - ptChar.y;
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);

        m_currentVidCellShadow->GetCurrentFrameSize(frameSize, FALSE);

        rFx.right = max(frameSize.cx + ptReference.x - ptShadow.x, rFx.right);
        rFx.bottom = max(frameSize.cy + ptReference.y - ptShadow.y, rFx.bottom);

        if (m_currentVidCellShadow != NULL) {
            ptReference.y = max(ptChar.y - posZ, ptShadow.y + posZ);
        }
    } else {
        rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
    }
}

// 0x6A33F0
void CGameAnimationTypeEffect::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
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

// 0x6A3C60
BOOLEAN CGameAnimationTypeEffect::DetectedByInfravision()
{
    return FALSE;
}

// 0x6A3450
void CGameAnimationTypeEffect::ChangeDirection(SHORT nDirection)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 927
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentBamDirection = nDirection;

    switch (m_animationID & 0xF00) {
    case 0x000:
        if (m_currentBamDirection > m_extendDirectionTest) {
            m_currentVidCell->SequenceSet(9 * m_currentBamSequence - m_currentBamDirection + 16);
        } else {
            m_currentVidCell->SequenceSet(9 * m_currentBamSequence + m_currentBamDirection);
        }
        break;
    case 0x100:
    case 0x200:
    case 0x300:
    case 0x400:
    case 0x500:
    case 0x600:
    case 0x700:
    case 0x800:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 950
        UTIL_ASSERT(FALSE);
    }
}

// 0x55D2A0
BOOL CGameAnimationTypeEffect::IsMirroring()
{
    return m_currentBamSequence > m_extendDirectionTest;
}

// 0x6A3550
void CGameAnimationTypeEffect::IncrementFrame()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 975
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (m_animationID & 0xF00) {
    case 0x000:
        if (m_currentBamSequence == 0 && m_currentVidCell->IsEndOfSequence(FALSE)) {
            m_currentBamSequence++;
            m_currentVidCell->SequenceSet(m_currentBamSequence);
            m_currentVidCell->FrameSet(0);
        } else {
            m_currentVidCell->FrameAdvance();
        }
        break;
    case 0x100:
    case 0x200:
    case 0x300:
    case 0x400:
        m_currentVidCell->FrameAdvance();
        if (m_currentVidCellShadow != NULL) {
            m_currentVidCellShadow->FrameAdvance();
        }
        break;
    case 0x500:
    case 0x600:
    case 0x700:
    case 0x800:
        switch (m_animationID & 0xF0) {
        case 0x00:
        case 0x10:
            m_currentVidCell->FrameAdvance();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1056
            UTIL_ASSERT(FALSE);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1061
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A36A0
void CGameAnimationTypeEffect::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1086
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1087
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (!m_bRender) {
        return;
    }

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    if (m_currentBamDirection > m_extendDirectionTest) {
        dwRenderFlags |= CInfinity::MIRROR_FX;
    }

    if (field_5E7 == 1) {
        dwRenderFlags |= 0x200;
    }

    if (field_5E1) {
        dwRenderFlags |= 0x8;
    }

    if (m_currentVidCellShadow != NULL
        || m_translucent
        || transparency != 0
        || (dwRenderFlags & 0x8) != 0) {
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
    } else {
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
        dwRenderFlags |= 0x1;
    }

    if (transparency) {
        dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
        dwRenderFlags |= 0x2;
    } else {
        dwRenderFlags |= CInfinity::FXPREP_CLEARFILL;
        dwRenderFlags |= 0x1;
    }

    if (m_currentVidCellShadow != NULL) {
        dwRenderFlags |= 0x4;
    }

    if (m_translucent || transparency != 0) {
        dwRenderFlags |= 0x2;
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        if (!field_5DE) {
            m_currentVidCell->SetTintColor(rgbTintColor);
        }

        if (m_currentVidCellShadow != NULL) {
            pInfinity->FXRender(m_currentVidCellShadow,
                ptReference.x,
                ptReference.y,
                dwRenderFlags,
                0);
        }

        if (m_translucent) {
            if (transparency != 0) {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags,
                    (transparency * 128) / 255 + 128);
            } else {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags,
                    128);
            }
        } else {
            if (transparency != 0) {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags,
                    transparency);
            } else {
                pInfinity->FXRender(m_currentVidCell,
                    ptReference.x,
                    ptReference.y,
                    dwRenderFlags,
                    0);
            }
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

// 0x55DBC0
SHORT CGameAnimationTypeEffect::SetSequence(SHORT nSequence)
{
    return CGameSprite::SEQ_READY;
}

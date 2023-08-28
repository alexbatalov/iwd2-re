#include "CGameAnimationTypeTownStatic.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CInfinity.h"
#include "CUtil.h"

// 0x6A48E0
CGameAnimationTypeTownStatic::CGameAnimationTypeTownStatic(USHORT animationID, BYTE* colorRangeValues, WORD facing)
    : m_charPalette(CVidPalette::TYPE_RANGE)
{
    CString sName;

    m_animationID = animationID;
    m_falseColor = TRUE;
    m_bCanLieDown = TRUE;
    SetNeckOffsets(0, 10, -10, 10, -10, 0, -10, -10, 0, -10, 10, -10, 10, 0, 10, 10);

    switch (animationID & 0xF00) {
    case 0x000:
        switch (animationID & 0xF) {
        case 0:
            m_colorChunks = -1;

            if ((animationID & 0xF0) != 0) {
                sName = "SNOWC";
            } else {
                sName = "SNOMC";
            }

            break;
        case 2:
            if ((animationID & 0xF0) != 0) {
                sName = "SNOWM";
            } else {
                sName = "SNOMM";
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1873
            UTIL_ASSERT(FALSE);
        }

        m_pSndDeath = "";
        m_bCanLieDown = FALSE;
        break;
    case 0x100:
        switch (animationID & 0xF) {
        case 0:
            m_colorChunks = -1;

            if ((animationID & 0xF0) != 0) {
                sName = "SSIWC";
            } else {
                sName = "SSIMC";
            }

            break;
        case 1:
            m_colorChunks = -1;

            sName = "SSIMS";
            break;
        case 2:
            if ((animationID & 0xF0) != 0) {
                sName = "SSIWM";
            } else {
                sName = "SSIMM";
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 1903
            UTIL_ASSERT(FALSE);
        }

        m_pSndDeath = "";
        m_bCanLieDown = FALSE;
        break;
    case 0x200:
        sName = "SHMCM";
        m_pSndDeath = "";
        m_bCanLieDown = FALSE;
        break;
    case 0x300:
        sName = "MSPLG1";
        m_falseColor = FALSE;
        m_rEllipse.left = -24;
        m_rEllipse.top = -18;
        m_rEllipse.right = 24;
        m_rEllipse.bottom = 18;
        m_personalSpace = 5;
        m_colorChunks = -1;
        m_colorBlood = 45;
        m_pSndDeath = "";
        m_bCanLieDown = FALSE;
        break;
    case 0x400:
        if ((animationID & 0xF0) != 0) {
            sName = "LHFC";
        } else {
            sName = "LHMC";
        }
        break;
    case 0x500:
        sName = "LFAM";
        break;
    case 0x600:
        sName = "LDMF";
        break;
    case 0x700:
        if ((animationID & 0xF0) != 0) {
            sName = "LEFF";
        } else {
            sName = "LEMF";
        }
        break;
    case 0x800:
        sName = "LIMC";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 1958
        UTIL_ASSERT(FALSE);
    }

    // NOTE: Uninline.
    m_g1VidCellBase.SetResRef(CResRef(sName), FALSE, TRUE, TRUE);

    m_currentVidCellBase = &m_g1VidCellBase;
    m_currentVidCell = &m_g1VidCellBase;

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            m_charPalette.SetRange(colorRange, colorRangeValues[colorRange], *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
        }

        m_g1VidCellBase.SetPalette(m_charPalette);
    }

    m_currentBamSequence = 0;
    m_currentBamDirection = facing;
}

// 0x6A4FA0
CGameAnimationTypeTownStatic::~CGameAnimationTypeTownStatic()
{
}

// 0x6A4E10
BOOLEAN CGameAnimationTypeTownStatic::CanLieDown()
{
    return m_bCanLieDown;
}

// 0x6A4E20
BOOL CGameAnimationTypeTownStatic::IsBeginningOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 831
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame == 0;
}

// 0x6A4E60
BOOL CGameAnimationTypeTownStatic::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 832
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->IsEndOfSequence(FALSE);
}

// 0x6A4EA0
BOOL CGameAnimationTypeTownStatic::IsFalseColor()
{
    return m_falseColor;
}

// 0x6A4EB0
void CGameAnimationTypeTownStatic::IncrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 834
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->FrameAdvance();
}

// 0x6A4EF0
void CGameAnimationTypeTownStatic::DecrementFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 835
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->m_nCurrentFrame--;
}

// 0x6A4F30
SHORT CGameAnimationTypeTownStatic::GetCurrentFrame()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 844
    UTIL_ASSERT(m_currentVidCell != NULL);

    return m_currentVidCell->m_nCurrentFrame;
}

// 0x6A5020
void CGameAnimationTypeTownStatic::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 1994
    UTIL_ASSERT(m_currentVidCell != NULL);

    m_currentVidCell->GetCurrentCenterPoint(ptReference, FALSE);

    CSize frameSize;
    m_currentVidCell->GetCurrentFrameSize(frameSize, FALSE);
    rFx.SetRect(0, 0, frameSize.cx, frameSize.cy);
}

// 0x6A5090
void CGameAnimationTypeTownStatic::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    rGCBounds.left = pos.x - ptReference.x;
    rGCBounds.right = rGCBounds.left + nWidth;
    rGCBounds.top = posZ + pos.y - ptReference.y;
    rGCBounds.bottom = rGCBounds.top + nHeight;
}

// 0x6A50D0
void CGameAnimationTypeTownStatic::ClearColorEffects(BYTE colorRange)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2081
    UTIL_ASSERT(m_currentVidCell != NULL);

    switch (colorRange & 0xF0) {
    case 0x00:
        if (m_falseColor) {
            m_g1VidCellBase.DeleteRangeAffects(colorRange & 0xF);
            m_g1VidCellBase.UnsuppressTint(colorRange & 0xF);
        } else {
            m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
            m_g1VidCellBase.DeleteResPaletteAffect();

            // NOTE: Uninline.
            m_g1VidCellBase.UnsuppressTintAllRanges();
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2104
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A51E0
void CGameAnimationTypeTownStatic::ClearColorEffectsAll()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2129
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            ClearColorEffects(colorRange);
        }
    } else {
        m_g1VidCellBase.SetTintColor(RGB(CVidPalette::NO_TINT, CVidPalette::NO_TINT, CVidPalette::NO_TINT));
        m_g1VidCellBase.DeleteResPaletteAffect();

        // NOTE: Uninline.
        m_g1VidCellBase.UnsuppressTintAllRanges();
    }
}

// 0x6A5270
void CGameAnimationTypeTownStatic::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    switch (colorRange & 0xF0) {
    case 0x00:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2170
        UTIL_ASSERT(m_currentVidCell != NULL);

        if (m_falseColor) {
            m_g1VidCellBase.AddRangeAffect(effectType, colorRange & 0xF, tintColor, periodLength);

            if (effectType != 0) {
                m_g1VidCellBase.SuppressTint(colorRange & 0xF);
            }
        } else {
            if (effectType != 0) {
                m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
                m_g1VidCellBase.SuppressTint(0);
            } else {
                m_g1VidCellBase.SetTintColor(tintColor);
            }
        }
        break;
    case 0x10:
    case 0x20:
    case 0x30:
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2200
        UTIL_ASSERT(FALSE);
    }
}

// 0x6A53B0
void CGameAnimationTypeTownStatic::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2225
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorEffect(effectType, colorRange, tintColor, periodLength);
        }
    } else {
        if (effectType != 0) {
            m_g1VidCellBase.AddResPaletteAffect(effectType, tintColor, periodLength);
            m_g1VidCellBase.SuppressTint(0);
        } else {
            m_g1VidCellBase.SetTintColor(tintColor);
        }
    }
}

// 0x6A5470
void CGameAnimationTypeTownStatic::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    if (m_falseColor) {
        switch (colorRange & 0xF0) {
        case 0x00:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 2273
            UTIL_ASSERT(m_currentVidCell != NULL);

            m_charPalette.SetRange(colorRange & 0xF, rangeValue, *g_pBaldurChitin->GetObjectGame()->GetMasterBitmap());
            break;
        case 0x10:
        case 0x20:
        case 0x30:
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
            // __LINE__: 2283
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6A5560
void CGameAnimationTypeTownStatic::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2309
    UTIL_ASSERT(m_currentVidCell != NULL);

    if (m_falseColor) {
        for (BYTE colorRange = 0; colorRange < CVidPalette::NUM_RANGES; colorRange++) {
            SetColorRange(colorRange, rangeValue);
        }
    }
}

// 0x6A55C0
void CGameAnimationTypeTownStatic::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2340
    UTIL_ASSERT(pInfinity != NULL && pVidMode != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
    // __LINE__: 2341
    UTIL_ASSERT(m_currentVidCell != NULL);

    CPoint ptPos(ptNewPos.x, ptNewPos.y + posZ);
    CRect rFXRect(rectFX);

    dwRenderFlags |= CInfinity::FXPREP_COPYFROMBACK;
    dwRenderFlags |= 0x4;

    if (m_animationID >= 0x4400) {
        dwRenderFlags |= CInfinity::CLIPPING_IGNORE_VERTICAL;
    }

    if (transparency) {
        dwRenderFlags |= 0x2;
    }

    pInfinity->FXPrep(rFXRect, dwRenderFlags, nSurface, ptPos, ptReference);

    if (pInfinity->FXLock(rFXRect, dwRenderFlags)) {
        COLORREF oldTintColor = m_currentVidCell->GetTintColor();
        BYTE b = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
            ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
            : 0;
        BYTE g = GetGValue(oldTintColor) + GetGValue(rgbTintColor) - 255 >= 0
            ? GetGValue(oldTintColor) + GetGValue(rgbTintColor) + 1
            : 0;
        BYTE r = GetBValue(oldTintColor) + GetBValue(rgbTintColor) - 255 >= 0
            ? GetBValue(oldTintColor) + GetBValue(rgbTintColor) + 1
            : 0;
        m_currentVidCell->SetTintColor(RGB(r, g, b));

        pInfinity->FXRender(m_currentVidCell,
            ptReference.x,
            ptReference.y,
            dwRenderFlags,
            transparency);

        m_currentVidCell->SetTintColor(oldTintColor);

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

// 0x6A5850
SHORT CGameAnimationTypeTownStatic::SetSequence(SHORT nSequence)
{
    BOOL bRandomFrame = FALSE;

    switch (nSequence) {
    case 1:
    case 5:
    case 17:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 3;
        break;
    case 2:
    case 3:
    case 7:
        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 0;
        break;
    case 4:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 2;
        break;
    case 6:
        if (m_currentBamSequence != 1 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 1;
        break;
    case 8:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        nSequence = 7;

        if (m_currentBamSequence != 0 || m_currentVidCellBase != &m_g1VidCellBase) {
            bRandomFrame = TRUE;
        }

        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 0;
        break;
    case 9:
        m_currentVidCellBase = &m_g1VidCellBase;
        m_currentBamSequence = 4;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\ObjAnimation.cpp
        // __LINE__: 2453
        UTIL_ASSERT(FALSE);
    }

    m_currentVidCell->SequenceSet(m_currentBamDirection + 16 * m_currentBamSequence);

    if (bRandomFrame) {
        BYTE nSequenceLength = m_currentVidCell->GetSequenceLength(m_currentVidCell->m_nCurrentSequence, FALSE);
        if (nSequenceLength != 0) {
            m_currentVidCell->FrameSet(rand() % nSequenceLength);
        } else {
            m_currentVidCell->FrameSet(0);
        }
    } else {
        m_currentVidCell->FrameSet(0);
    }

    if (nSequence == 1) {
        DecrementFrame();
    }

    return nSequence;
}

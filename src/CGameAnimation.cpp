#include "CGameAnimation.h"

#include "CGameAnimationType.h"
#include "CUtil.h"

// NOTE: Inlined.
CGameAnimation::CGameAnimation()
{
    m_animation = NULL;
    m_nSequence = 0;
}

// NOTE: Inlined.
CGameAnimation::~CGameAnimation()
{
    if (m_animation != NULL) {
        delete m_animation;
    }
}

// NOTE: Inlined.
void CGameAnimation::CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2071
    UTIL_ASSERT(m_animation != NULL);

    m_animation->CalculateFxRect(rFx, ptReference, posZ);
}

// 0x56E210
void CGameAnimation::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2073
    UTIL_ASSERT(m_animation != NULL);

    m_animation->CalculateGCBoundsRect(rGCBounds, pos, ptReference, posZ, nWidth, nHeight);
}

// NOTE: Inlined.
void CGameAnimation::ChangeDirection(SHORT nDirection)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2074
    UTIL_ASSERT(m_animation != NULL);

    m_animation->ChangeDirection(nDirection);
}

// 0x45B690
USHORT CGameAnimation::GetAnimationId()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2115
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->m_animationID;
}

// NOTE: Inlined.
void CGameAnimation::GetAnimationResRef(CString& resRef, BYTE range)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2080
    UTIL_ASSERT(m_animation != NULL);

    m_animation->GetAnimationResRef(resRef, range);
}

// NOTE: Inlined.
void CGameAnimation::SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing)
{
    if (m_animation != NULL) {
        delete m_animation;
    }

    m_animation = CGameAnimationType::SetAnimationType(animationID, colorRangeValues, facing);

    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2086
    UTIL_ASSERT(m_animation != NULL);
}

// NOTE: Inlined.
BYTE CGameAnimation::GetMoveScale()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2087
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->GetMoveScale();
}

// NOTE: Inlined.
BYTE CGameAnimation::GetMoveScaleDefault()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2088
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->GetMoveScaleDefault();
}

// NOTE: Inlined.
void CGameAnimation::SetMoveScale(BYTE scale)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2089
    UTIL_ASSERT(m_animation != NULL);

    m_animation->SetMoveScale(scale);
}

// NOTE: Inlined.
void CGameAnimation::ResetMoveScale()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2090
    UTIL_ASSERT(m_animation != NULL);

    m_animation->ResetMoveScale();
}

// NOTE: Inlined.
const CRect& CGameAnimation::GetEllipseRect()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2091
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->GetEllipseRect();
}

// NOTE: Inlined.
BOOL CGameAnimation::IsEndOfSequence()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2103
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->IsEndOfSequence();
}

// NOTE: Inlined.
void CGameAnimation::Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2106
    UTIL_ASSERT(m_animation != NULL);

    m_animation->Render(pInfinity,
        pVidMode,
        nSurface,
        rectFX,
        ptNewPos,
        ptReference,
        dwRenderFlags,
        rgbTintColor,
        rGCBounds,
        bDithered,
        bFadeOut,
        posZ,
        transparency);
}

// NOTE: Uninline.
void CGameAnimation::ClearColorEffectsAll()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2108
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->ClearColorEffectsAll();
}

// NOTE: Inlined.
void CGameAnimation::SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2109
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->SetColorEffect(effectType, colorRange, tintColor, periodLength);
}

// NOTE: Inlined.
void CGameAnimation::SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2110
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->SetColorEffectAll(effectType, tintColor, periodLength);
}

// NOTE: Inlined.
void CGameAnimation::SetColorRange(BYTE colorRange, BYTE rangeValue)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2111
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->SetColorRange(colorRange, rangeValue);
}

// NOTE: Inlined.
void CGameAnimation::SetColorRangeAll(BYTE rangeValue)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2112
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->SetColorRangeAll(rangeValue);
}

// NOTE: Inlined.
void CGameAnimation::SetSequence(SHORT nSequence)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2113
    UTIL_ASSERT(m_animation != NULL);

    m_nSequence = nSequence;

    m_animation->SetSequence(nSequence);
}

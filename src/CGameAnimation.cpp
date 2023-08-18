#include "CGameAnimation.h"

#include "CGameAnimationType.h"
#include "CUtil.h"

// NOTE: Inlined.
CGameAnimation::CGameAnimation()
{
    m_animation = NULL;
    field_8 = 0;
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
const CRect& CGameAnimation::GetEllipseRect()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2091
    UTIL_ASSERT(m_animation != NULL);

    return m_animation->GetEllipseRect();
}

// NOTE: Inlined.
void CGameAnimation::Render(CInfinity* pInfinity, CVidMode* pVidMode, int a3, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2106
    UTIL_ASSERT(m_animation != NULL);

    m_animation->Render(pInfinity,
        pVidMode,
        a3,
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

// NOTE: Inlined.
CGameAnimationType* CGameAnimation::GetAnimation()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2111
    UTIL_ASSERT(m_animation != NULL);

    return m_animation;
}

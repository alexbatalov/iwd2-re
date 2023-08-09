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

// 0x56E210
void CGameAnimation::CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight)
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2073
    UTIL_ASSERT(m_animation != NULL);

    m_animation->CalculateGCBoundsRect(rGCBounds, pos, ptReference, posZ, nWidth, nHeight);
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
CGameAnimationType* CGameAnimation::GetAnimation()
{
    // __FILE__: .\Include\ObjAnimation.h
    // __LINE__: 2111
    UTIL_ASSERT(m_animation != NULL);

    return m_animation;
}

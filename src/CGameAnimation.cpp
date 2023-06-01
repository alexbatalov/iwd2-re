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

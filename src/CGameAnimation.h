#ifndef CGAMEANIMATION_H_
#define CGAMEANIMATION_H_

#include "mfc.h"

class CGameAnimationType;

class CGameAnimation {
public:
    CGameAnimation();
    ~CGameAnimation();
    /* 0000 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);

    /* 0004 */ CGameAnimationType* m_animation;
    /* 0008 */ short field_8;
};

#endif /* CGAMEANIMATION_H_ */

#ifndef CGAMEANIMATION_H_
#define CGAMEANIMATION_H_

#include "mfc.h"

class CGameAnimationType;

class CGameAnimation {
public:
    CGameAnimation();
    ~CGameAnimation();
    /* 0000 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);

    USHORT GetAnimationId();

    void ChangeDirection(SHORT nDirection);
    void GetAnimationResRef(CString& resRef, BYTE range);
    const CRect& GetEllipseRect();
    void SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    CGameAnimationType* GetAnimation();

    /* 0004 */ CGameAnimationType* m_animation;
    /* 0008 */ short field_8;
};

#endif /* CGAMEANIMATION_H_ */

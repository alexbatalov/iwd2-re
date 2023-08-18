#ifndef CGAMEANIMATION_H_
#define CGAMEANIMATION_H_

#include "mfc.h"

class CGameAnimationType;
class CInfinity;
class CVidMode;

class CGameAnimation {
public:
    CGameAnimation();
    ~CGameAnimation();
    /* 0000 */ virtual void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight);

    USHORT GetAnimationId();

    void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ);
    void ChangeDirection(SHORT nDirection);
    void GetAnimationResRef(CString& resRef, BYTE range);
    const CRect& GetEllipseRect();
    void SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    CGameAnimationType* GetAnimation();
    void Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency);

    /* 0004 */ CGameAnimationType* m_animation;
    /* 0008 */ short field_8;
};

#endif /* CGAMEANIMATION_H_ */

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
    void EquipArmor(CHAR armorLevel, BYTE* colorRangeValues);
    void GetAnimationResRef(CString& resRef, BYTE range);
    BOOLEAN CanLieDown();
    BOOLEAN DetectedByInfravision();
    BYTE GetColorBlood();
    BYTE GetListType();
    BYTE GetMoveScale();
    BYTE GetMoveScaleDefault();
    void SetMoveScale(BYTE scale);
    void ResetMoveScale();
    const CRect& GetEllipseRect();
    BOOL GetPathSmooth();
    BYTE GetPersonalSpace();
    char* GetSndArmor();
    char* GetSndReady();
    char* GetSndWalk(SHORT tableIndex);
    DWORD GetSndWalkFreq();
    BOOL IsFalseColor();
    void SetAnimationType(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    void ClearColorEffectsAll();
    void SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength);
    void SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength);
    void SetColorRange(BYTE colorRange, BYTE rangeValue);
    void SetColorRangeAll(BYTE rangeValue);
    BOOL IsBeginningOfSequence();
    BOOL IsEndOfSequence();
    void IncrementFrame();
    void DecrementFrame();
    void Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency);
    SHORT SetSequence(SHORT nSequence);
    BYTE GetAttackFrameType(BYTE numAttacks, BYTE speedFactor, BYTE combatFrame);
    BOOL GetAboveGround();
    SHORT GetCastHeight();
    SHORT GetCurrentFrame();
    BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet);

    /* 0004 */ CGameAnimationType* m_animation;
    /* 0008 */ SHORT m_nSequence;
};

#endif /* CGAMEANIMATION_H_ */

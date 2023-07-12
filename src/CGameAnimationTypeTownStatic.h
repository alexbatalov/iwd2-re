#ifndef CGAMEANIMATIONTYPETOWNSTATIC_H_
#define CGAMEANIMATIONTYPETOWNSTATIC_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeTownStatic : public CGameAnimationType {
public:
    CGameAnimationTypeTownStatic(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeTownStatic() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 0028 */ BOOLEAN CanLieDown() override;
    /* 0074 */ BOOL IsFalseColor() override;
    /* 0080 */ BOOL IsBeginningOfSequence() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 008C */ void DecrementFrame() override;
    /* 0094 */ void ClearColorEffects(BYTE colorRange) override;
    /* 0098 */ void ClearColorEffectsAll() override;
    /* 009C */ void SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength) override;
    /* 00A0 */ void SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength) override;
    /* 00A4 */ void SetColorRange(BYTE colorRange, BYTE rangeValue) override;
    /* 00A8 */ void SetColorRangeAll(BYTE rangeValue) override;
    /* 00AC */ SHORT SetSequence(SHORT nSequence) override;
    /* 00C8 */ SHORT GetCurrentFrame() override;

    /* 03FE */ CVidCell* m_currentVidCell;
    /* 0402 */ CVidCell* m_currentVidCellBase;
    /* 0406 */ CVidCell m_g1VidCellBase;
    /* 04E0 */ CVidPalette m_charPalette;
    /* 0504 */ SHORT m_currentBamSequence;
    /* 0506 */ SHORT m_currentBamDirection;
    /* 0508 */ BOOL m_falseColor;
    /* 050C */ BOOLEAN m_bCanLieDown;
};

#endif /* CGAMEANIMATIONTYPETOWNSTATIC_H_ */

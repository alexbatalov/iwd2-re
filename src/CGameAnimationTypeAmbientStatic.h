#ifndef CGAMEANIMATIONTYPEAMBIENTSTATIC_H_
#define CGAMEANIMATIONTYPEAMBIENTSTATIC_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeAmbientStatic : public CGameAnimationType {
public:
    CGameAnimationTypeAmbientStatic(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeAmbientStatic() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0074 */ BOOL IsFalseColor() override;
    /* 0078 */ BOOL IsInvulnerable() override;
    /* 007C */ BOOL IsMirroring() override;
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
    /* 0406 */ CVidCell* m_currentVidCellExtend;
    /* 040A */ CVidCell m_g1VidCellBase;
    /* 04E4 */ CVidCell m_g1VidCellExtend;
    /* 05BE */ CVidPalette m_charPalette;
    /* 05E2 */ SHORT m_currentBamSequence;
    /* 05E4 */ SHORT m_currentBamDirection;
    /* 05E6 */ BOOL m_falseColor;
    /* 05EA */ BOOL m_bInvulnerable;
    /* 05EE */ BOOLEAN m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEAMBIENTSTATIC_H_ */

#ifndef CGAMEANIMATIONTYPEFLYING_H_
#define CGAMEANIMATIONTYPEFLYING_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeFlying : public CGameAnimationType {
public:
    CGameAnimationTypeFlying(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeFlying() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 003C */ BYTE GetListType() override;
    /* 0074 */ BOOL IsFalseColor() override;
    /* 007C */ BOOL IsMirroring() override;
    /* 0080 */ BOOL IsBeginningOfSequence() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 008C */ void DecrementFrame() override;
    /* 0094 */ void ClearColorEffects(BYTE colorRange) override;

    /* 03FE */ CVidCell* m_currentVidCell;
    /* 0402 */ CVidCell* m_currentVidCellBase;
    /* 0406 */ CVidCell m_g1VidCellBase;
    /* 04E0 */ CVidPalette m_charPalette;
    /* 0504 */ SHORT m_currentBamSequence;
    /* 0506 */ SHORT m_currentBamDirection;
    /* 0508 */ BOOL m_falseColor;
    /* 050C */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEFLYING_H_ */

#ifndef CGAMEANIMATIONTYPEMONSTEROLD_H_
#define CGAMEANIMATIONTYPEMONSTEROLD_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeMonsterOld : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterOld(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterOld() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 0074 */ BOOL IsFalseColor() override;
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

    static BOOL NewSupport(USHORT animationID);

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_currentVidCellExtend;
    /* 040E */ CVidCell m_g1VidCellBase;
    /* 04E8 */ CVidCell m_g1VidCellExtend;
    /* 05C2 */ CVidCell m_g2VidCellBase;
    /* 069C */ CVidCell m_g2VidCellExtend;
    /* 0776 */ CVidPalette m_charPalette;
    /* 079A */ SHORT m_currentBamSequence;
    /* 079C */ SHORT m_currentBamDirection;
    /* 079E */ BOOL m_falseColor;
    /* 07A2 */ BOOL m_translucent;
    /* 07A6 */ BOOL field_7A6;
    /* 07AA */ CVidBitmap field_7AA;
    /* 0864 */ BOOLEAN m_bDetectedByInfravision;
    /* 0865 */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEMONSTEROLD_H_ */

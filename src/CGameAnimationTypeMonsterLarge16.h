#ifndef CGAMEANIMATIONTYPEMONSTERLARGE16_H_
#define CGAMEANIMATIONTYPEMONSTERLARGE16_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeMonsterLarge16 : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterLarge16(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterLarge16() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0068 */ const char* GetSndReady() override;
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
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_currentVidCellExtend;
    /* 040E */ CVidCell m_g1VidCellBase;
    /* 04E8 */ CVidCell m_g1VidCellExtend;
    /* 05C2 */ CVidCell m_g2VidCellBase;
    /* 069C */ CVidCell m_g2VidCellExtend;
    /* 0776 */ CVidCell m_g3VidCellBase;
    /* 0850 */ CVidCell m_g3VidCellExtend;
    /* 092A */ CVidPalette m_charPalette;
    /* 094E */ SHORT m_currentBamSequence;
    /* 0950 */ SHORT m_currentBamDirection;
    /* 0952 */ BOOL m_falseColor;
    /* 0956 */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEMONSTERLARGE16_H_ */

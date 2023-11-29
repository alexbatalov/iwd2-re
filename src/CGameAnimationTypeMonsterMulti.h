#ifndef CGAMEANIMATIONTYPEMONSTERMULTI_H_
#define CGAMEANIMATIONTYPEMONSTERMULTI_H_

#include "CGameAnimationType.h"

class CVidCell;

class CGameAnimationTypeMonsterMulti : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterMulti(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterMulti() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0068 */ char* GetSndReady() override;
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
    /* 00B0 */ void CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 00C4 */ SHORT GetCastHeight() override;
    /* 00C8 */ SHORT GetCurrentFrame() override;
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;
    /* 00D4 */ virtual void GetCastingOffset(CPoint& ptOffset);

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_g1VidCellBase;
    /* 040E */ CVidCell* m_g2VidCellBase;
    /* 0412 */ CVidCell* m_g3VidCellBase;
    /* 0416 */ CVidCell* m_g4VidCellBase;
    /* 041A */ CVidCell* m_g5VidCellBase;
    /* 041E */ CVidPalette m_charPalette;
    /* 0442 */ SHORT m_currentBamSequence;
    /* 0444 */ SHORT m_currentBamDirection;
    /* 0446 */ int field_446;
    /* 044A */ CVidBitmap* field_44A;
    /* 044E */ CVidBitmap field_44E;
    /* 0508 */ CVidBitmap field_508;
    /* 05C2 */ CVidBitmap field_5C2;
    /* 067C */ CVidBitmap field_67C;
    /* 0736 */ CVidBitmap field_736;
    /* 07F0 */ BOOL m_falseColor;
    /* 07F4 */ BYTE m_extendDirectionTest;
    /* 07F5 */ BYTE m_nQuadrants;
    /* 07F6 */ BOOL m_bDoubleBlit;
    /* 07FA */ BOOL m_bSplitBams;
    /* 07FE */ CHAR m_splitBamChar;
    /* 07FF */ CHAR m_splitDirectionBamChar;
    /* 0800 */ unsigned char field_800;
};

#endif /* CGAMEANIMATIONTYPEMONSTERMULTI_H_ */

#ifndef CGAMEANIMATIONTYPEMONSTERQUADRANT_H_
#define CGAMEANIMATIONTYPEMONSTERQUADRANT_H_

#include "CGameAnimationType.h"

class CVidCell;

class CGameAnimationTypeMonsterQuadrant : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterQuadrant(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterQuadrant() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0058 */ BOOL GetPathSmooth() override;
    /* 0068 */ char* GetSndReady() override;
    /* 006C */ char* GetSndWalk(SHORT tableIndex) override;
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
    /* 00B0 */ void CalculateFxRectMax(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 00C8 */ SHORT GetCurrentFrame() override;
    /* 00CC */ BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame) override;
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_g1VidCellBase;
    /* 040E */ CVidCell* m_g2VidCellBase;
    /* 0412 */ CVidCell* m_g3VidCellBase;
    /* 0416 */ CVidCell* m_currentVidCellExtend;
    /* 041A */ CVidCell* m_g1VidCellExtend;
    /* 041E */ CVidCell* m_g2VidCellExtend;
    /* 0422 */ CVidCell* m_g3VidCellExtend;
    /* 0426 */ CVidPalette m_charPalette;
    /* 044A */ SHORT m_currentBamSequence;
    /* 044C */ SHORT m_currentBamDirection;
    /* 044E */ BOOL m_falseColor;
    /* 0452 */ BYTE m_extendDirectionTest;
    /* 0453 */ BYTE m_nQuadrants;
    /* 0454 */ BOOL m_bCaster;
    /* 0458 */ BOOL m_bExtendDir;
    /* 045C */ BOOL m_pathSmooth;
};

#endif /* CGAMEANIMATIONTYPEMONSTERQUADRANT_H_ */

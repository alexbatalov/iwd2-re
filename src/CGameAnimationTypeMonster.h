#ifndef CGAMEANIMATIONTYPEMONSTER_H_
#define CGAMEANIMATIONTYPEMONSTER_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeMonster : public CGameAnimationType {
public:
    CGameAnimationTypeMonster(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonster() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0028 */ BOOLEAN CanLieDown() override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 0058 */ BOOL GetPathSmooth() override;
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

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell m_g1VidCellBase;
    /* 04E4 */ CVidCell m_g2VidCellBase;
    /* 05BE */ CVidPalette m_charPalette;
    /* 05E2 */ CVidCell* m_currentVidCellWeapon;
    /* 05E6 */ CVidCell* m_currentVidCellWeaponBase;
    /* 05EA */ CVidCell m_g1VidCellWeaponBase;
    /* 06C4 */ CVidCell m_g2VidCellWeaponBase;
    /* 079E */ CVidPalette m_weaponPalette;
    /* 07C2 */ SHORT m_currentBamSequence;
    /* 07C4 */ SHORT m_currentBamDirection;
    /* 07C6 */ SHORT m_currentShootSequence;
    /* 07C8 */ BOOL m_falseColor;
    /* 07CC */ BOOL m_translucent;
    /* 07D0 */ BOOL field_7D0;
    /* 07D4 */ CVidBitmap field_7D4;
    /* 088E */ BOOL m_renderWeapons;
    /* 0892 */ BOOL m_bHideWeapons;
    /* 0896 */ BOOLEAN m_bDetectedByInfravision;
    /* 0897 */ BYTE m_extendDirectionTest;
    /* 0898 */ BOOL m_bCanLieDown;
    /* 089C */ BOOL m_bPathSmooth;
    /* 08A0 */ BOOL m_bSplitBams;
    /* 08A4 */ CHAR m_splitBamChar;
    /* 08A5 */ CHAR m_currentShootSplit;
};

#endif /* CGAMEANIMATIONTYPEMONSTER_H_ */

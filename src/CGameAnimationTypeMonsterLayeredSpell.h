#ifndef CGAMEANIMATIONTYPEMONSTERLAYEREDSPELL_H_
#define CGAMEANIMATIONTYPEMONSTERLAYEREDSPELL_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeMonsterLayeredSpell : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterLayeredSpell(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterLayeredSpell() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 006C */ char* GetSndWalk(SHORT tableIndex) override;
    /* 0074 */ BOOL IsFalseColor() override;
    /* 0078 */ BOOL IsInvulnerable() override;
    /* 007C */ BOOL IsMirroring() override;
    /* 0080 */ BOOL IsBeginningOfSequence() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 008C */ void DecrementFrame() override;
    /* 0090 */ void Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency) override;
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
    /* 040A */ CVidCell* m_currentVidCellExtend;
    /* 040E */ CVidCell m_g1VidCellBase;
    /* 04E8 */ CVidCell m_g1VidCellExtend;
    /* 05C2 */ CVidCell m_g2VidCellBase;
    /* 069C */ CVidCell m_g2VidCellExtend;
    /* 0776 */ CVidPalette m_charPalette;
    /* 079A */ CVidCell* m_currentVidCellWeapon;
    /* 079E */ CVidCell* m_currentVidCellWeaponBase;
    /* 07A2 */ CVidCell* m_currentVidCellWeaponExtend;
    /* 07A6 */ CVidCell m_g1VidCellWeaponBase;
    /* 0880 */ CVidCell m_g1VidCellWeaponExtend;
    /* 095A */ CVidCell m_g2VidCellWeaponBase;
    /* 0A34 */ CVidCell m_g2VidCellWeaponExtend;
    /* 0B0E */ CVidPalette m_weaponPalette;
    /* 0B32 */ SHORT m_currentBamSequence;
    /* 0B34 */ SHORT m_currentBamDirection;
    /* 0B36 */ BOOL m_renderWeapons;
    /* 0B3A */ BOOL m_weaponLeftHand;
    /* 0B3E */ BOOL m_falseColor;
    /* 0B42 */ CString m_weaponResRef[2];
    /* 0B4A */ BOOLEAN m_bInvulnerable;
    /* 0B4C */ BOOL m_bDualAttack;
    /* 0B50 */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEMONSTERLAYEREDSPELL_H_ */

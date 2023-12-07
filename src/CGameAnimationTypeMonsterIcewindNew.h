#ifndef CGAMEANIMATIONTYPEMONSTERICEWINDNEW_H_
#define CGAMEANIMATIONTYPEMONSTERICEWINDNEW_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"
#include "CVidPalette.h"

class CGameAnimationTypeMonsterIcewindNew : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterIcewindNew(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterIcewindNew() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 001C */ void EquipWeapon(const CString& resRef, BYTE* colorRangeValues, DWORD itemFlags, const WORD* pAttackProb) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 006C */ char* GetSndWalk(SHORT tableIndex) override;
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
    /* 040E */ CVidCell m_a1VidCellBase;
    /* 04E8 */ CVidCell m_a1VidCellExtend;
    /* 05C2 */ CVidCell m_a2VidCellBase;
    /* 069C */ CVidCell m_a2VidCellExtend;
    /* 0776 */ CVidCell m_a3VidCellBase;
    /* 0850 */ CVidCell m_a3VidCellExtend;
    /* 092A */ CVidCell m_a4VidCellBase;
    /* 0A04 */ CVidCell m_a4VidCellExtend;
    /* 0ADE */ CVidCell m_deVidCellBase;
    /* 0BB8 */ CVidCell m_deVidCellExtend;
    /* 0C92 */ CVidCell m_ghVidCellBase;
    /* 0D6C */ CVidCell m_ghVidCellExtend;
    /* 0E46 */ CVidCell m_slVidCellBase;
    /* 0F20 */ CVidCell m_slVidCellExtend;
    /* 0FFA */ CVidCell m_guVidCellBase;
    /* 10D4 */ CVidCell m_guVidCellExtend;
    /* 11AE */ CVidCell m_spVidCellBase;
    /* 1288 */ CVidCell m_spVidCellExtend;
    /* 1362 */ CVidCell m_caVidCellBase;
    /* 143C */ CVidCell m_caVidCellExtend;
    /* 1516 */ CVidCell m_scVidCellBase;
    /* 15F0 */ CVidCell m_scVidCellExtend;
    /* 16CA */ CVidCell m_sdVidCellBase;
    /* 17A4 */ CVidCell m_sdVidCellExtend;
    /* 187E */ CVidCell m_twVidCellBase;
    /* 1958 */ CVidCell m_twVidCellExtend;
    /* 1A32 */ CVidCell m_wkVidCellBase;
    /* 1B0C */ CVidCell m_wkVidCellExtend;
    /* 1BE6 */ CVidPalette m_charPalette;
    /* 1C0A */ CVidCell* m_currentVidCellWeapon;
    /* 1C0E */ CVidCell* m_currentVidCellWeaponBase;
    /* 1C12 */ CVidCell* m_currentVidCellWeaponExtend;
    /* 1C16 */ CVidCell m_a1VidCellWeaponBase;
    /* 1CF0 */ CVidCell m_a1VidCellWeaponExtend;
    /* 1DCA */ CVidCell m_a2VidCellWeaponBase;
    /* 1EA4 */ CVidCell m_a2VidCellWeaponExtend;
    /* 1F7E */ CVidCell m_a3VidCellWeaponBase;
    /* 2058 */ CVidCell m_a3VidCellWeaponExtend;
    /* 2132 */ CVidCell m_a4VidCellWeaponBase;
    /* 220C */ CVidCell m_a4VidCellWeaponExtend;
    /* 22E6 */ CVidCell m_deVidCellWeaponBase;
    /* 23C0 */ CVidCell m_deVidCellWeaponExtend;
    /* 249A */ CVidCell m_ghVidCellWeaponBase;
    /* 2574 */ CVidCell m_ghVidCellWeaponExtend;
    /* 264E */ CVidCell m_slVidCellWeaponBase;
    /* 2728 */ CVidCell m_slVidCellWeaponExtend;
    /* 2802 */ CVidCell m_guVidCellWeaponBase;
    /* 28DC */ CVidCell m_guVidCellWeaponExtend;
    /* 29B6 */ CVidCell m_spVidCellWeaponBase;
    /* 2A90 */ CVidCell m_spVidCellWeaponExtend;
    /* 2B6A */ CVidCell m_caVidCellWeaponBase;
    /* 2C44 */ CVidCell m_caVidCellWeaponExtend;
    /* 2D1E */ CVidCell m_scVidCellWeaponBase;
    /* 2DF8 */ CVidCell m_scVidCellWeaponExtend;
    /* 2ED2 */ CVidCell m_sdVidCellWeaponBase;
    /* 2FAC */ CVidCell m_sdVidCellWeaponExtend;
    /* 3086 */ CVidCell m_twVidCellWeaponBase;
    /* 3160 */ CVidCell m_twVidCellWeaponExtend;
    /* 323A */ CVidCell m_wkVidCellWeaponBase;
    /* 3314 */ CVidCell m_wkVidCellWeaponExtend;
    /* 33EE */ CVidPalette m_weaponPalette;
    /* 3412 */ SHORT m_currentBamSequence;
    /* 3414 */ SHORT m_currentBamDirection;
    /* 3416 */ int field_3416;
    /* 341A */ int field_341A;
    /* 341E */ int field_341E;
    /* 3422 */ CVidBitmap m_bitmap;
    /* 34DC */ unsigned char field_34DC;
    /* 34DD */ unsigned char field_34DD;
    /* 34DE */ BOOL m_renderWeapons;
    /* 34E2 */ int field_34E2;
    /* 34E6 */ BYTE field_34E6;
    /* 34E7 */ BYTE m_extendDirectionTest;
    /* 34E8 */ CString field_34E8[3];
    /* 34F4 */ int field_34F4;
    /* 34F8 */ int field_34F8;
};

#endif /* CGAMEANIMATIONTYPEMONSTERICEWINDNEW_H_ */

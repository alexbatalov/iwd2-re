#ifndef CGAMEANIMATIONTYPECHARACTEROLD_H_
#define CGAMEANIMATIONTYPECHARACTEROLD_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeCharacterOld : public CGameAnimationType {
public:
    CGameAnimationTypeCharacterOld(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeCharacterOld() override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0010 */ void EquipArmor(CHAR armorLevel, BYTE* colorRangeValues) override;
    /* 0014 */ void EquipHelmet(const CString& resRef, BYTE* colorRangeValues) override;
    /* 0018 */ void EquipShield(const CString& resRef, BYTE* colorRangeValues) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 0028 */ BOOLEAN CanLieDown() override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 0060 */ char* GetSndArmor() override;
    /* 006C */ char* GetSndWalk(SHORT tableIndex) override;
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
    /* 00CC */ BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame) override;
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;

    static BOOL NewSupport(USHORT animationID);

    /* 03FE */ CString m_resRef;
    /* 0402 */ CString m_shadowResRef;
    /* 0406 */ CString m_heightCode;
    /* 040A */ CString m_heightCodeHelmet;
    /* 040E */ CHAR m_armorCode;
    /* 040F */ CHAR m_armorMaxCode;
    /* 0410 */ CVidCell* m_currentVidCell;
    /* 0414 */ CVidCell* m_currentVidCellBase;
    /* 0418 */ CVidCell* m_currentVidCellExtend;
    /* 041C */ CVidCell m_g1VidCellBase;
    /* 04F6 */ CVidCell m_g1VidCellExtend;
    /* 05D0 */ CVidCell m_w2VidCellBase;
    /* 06AA */ CVidCell m_w2VidCellExtend;
    /* 0784 */ CVidCell m_caVidCellBase;
    /* 085E */ CVidCell m_caVidCellExtend;
    /* 0938 */ CVidCell m_a1VidCellBase;
    /* 0A12 */ CVidCell m_a1VidCellExtend;
    /* 0AEC */ CVidCell m_a2VidCellBase;
    /* 0BC6 */ CVidCell m_a2VidCellExtend;
    /* 0CA0 */ CVidCell m_a3VidCellBase;
    /* 0D7A */ CVidCell m_a3VidCellExtend;
    /* 0E54 */ CVidPalette m_charPalette;
    /* 0E78 */ CString m_weaponResRef;
    /* 0E7C */ CVidCell* m_currentVidCellWeapon;
    /* 0E80 */ CVidCell* m_currentVidCellWeaponBase;
    /* 0E84 */ CVidCell* m_currentVidCellWeaponExtend;
    /* 0E88 */ CVidCell m_g1VidCellWeaponBase;
    /* 0F62 */ CVidCell m_g1VidCellWeaponExtend;
    /* 103C */ CVidCell m_w2VidCellWeaponBase;
    /* 1116 */ CVidCell m_w2VidCellWeaponExtend;
    /* 11F0 */ CVidCell m_a1VidCellWeaponBase;
    /* 12CA */ CVidCell m_a1VidCellWeaponExtend;
    /* 13A4 */ CVidCell m_a2VidCellWeaponBase;
    /* 147E */ CVidCell m_a2VidCellWeaponExtend;
    /* 1558 */ CVidCell m_a3VidCellWeaponBase;
    /* 1632 */ CVidCell m_a3VidCellWeaponExtend;
    /* 170C */ CVidPalette m_weaponPalette;
    /* 1730 */ CString m_shieldResRef;
    /* 1734 */ CVidCell* m_currentVidCellShield;
    /* 1738 */ CVidCell* m_currentVidCellShieldBase;
    /* 173C */ CVidCell* m_currentVidCellShieldExtend;
    /* 1740 */ CVidCell m_g1VidCellShieldBase;
    /* 181A */ CVidCell m_g1VidCellShieldExtend;
    /* 18F4 */ CVidCell m_w2VidCellShieldBase;
    /* 19CE */ CVidCell m_w2VidCellShieldExtend;
    /* 1AA8 */ CVidCell m_a1VidCellShieldBase;
    /* 1B82 */ CVidCell m_a1VidCellShieldExtend;
    /* 1C5C */ CVidCell m_a2VidCellShieldBase;
    /* 1D36 */ CVidCell m_a2VidCellShieldExtend;
    /* 1E10 */ CVidCell m_a3VidCellShieldBase;
    /* 1EEA */ CVidCell m_a3VidCellShieldExtend;
    /* 1FC4 */ CVidPalette m_shieldPalette;
    /* 1FE8 */ CString m_helmetResRef;
    /* 1FEC */ CVidCell* m_currentVidCellHelmet;
    /* 1FF0 */ CVidCell* m_currentVidCellHelmetBase;
    /* 1FF4 */ CVidCell* m_currentVidCellHelmetExtend;
    /* 1FF8 */ CVidCell m_g1VidCellHelmetBase;
    /* 20D2 */ CVidCell m_g1VidCellHelmetExtend;
    /* 21AC */ CVidCell m_w2VidCellHelmetBase;
    /* 2286 */ CVidCell m_w2VidCellHelmetExtend;
    /* 2360 */ CVidCell m_caVidCellHelmetBase;
    /* 243A */ CVidCell m_caVidCellHelmetExtend;
    /* 2514 */ CVidCell m_a1VidCellHelmetBase;
    /* 25EE */ CVidCell m_a1VidCellHelmetExtend;
    /* 26C8 */ CVidCell m_a2VidCellHelmetBase;
    /* 27A2 */ CVidCell m_a2VidCellHelmetExtend;
    /* 287C */ CVidCell m_a3VidCellHelmetBase;
    /* 2956 */ CVidCell m_a3VidCellHelmetExtend;
    /* 2A30 */ CVidPalette m_helmetPalette;
    /* 2A54 */ CVidCell* m_currentVidCellShadow;
    /* 2A58 */ CVidCell* m_currentVidCellShadowBase;
    /* 2A5C */ CVidCell* m_currentVidCellShadowExtend;
    /* 2A60 */ CVidCell m_g1VidCellShadowBase;
    /* 2B3A */ CVidCell m_g1VidCellShadowExtend;
    /* 2C14 */ CVidCell m_w2VidCellShadowBase;
    /* 2CEE */ CVidCell m_w2VidCellShadowExtend;
    /* 2DC8 */ CVidCell m_caVidCellShadowBase;
    /* 2EA2 */ CVidCell m_caVidCellShadowExtend;
    /* 2F7C */ CVidCell m_a1VidCellShadowBase;
    /* 3056 */ CVidCell m_a1VidCellShadowExtend;
    /* 3130 */ CVidCell m_a2VidCellShadowBase;
    /* 320A */ CVidCell m_a2VidCellShadowExtend;
    /* 32E4 */ CVidCell m_a3VidCellShadowBase;
    /* 33BE */ CVidCell m_a3VidCellShadowExtend;
    /* 3498 */ SHORT m_currentBamSequence;
    /* 349A */ SHORT m_currentBamDirection;
    /* 349C */ BOOL m_renderWeapons;
    /* 34A0 */ BOOL m_renderHelmet;
    /* 34A4 */ BOOL m_bEquipHelmet;
    /* 34A8 */ BOOL m_weaponLeftHand;
    /* 34AC */ BOOL m_falseColor;
    /* 34B0 */ BYTE m_weaponCode;
    /* 34B1 */ BYTE m_extendDirectionTest;
    /* 34B2 */ BOOLEAN m_bDetectedByInfravision;
    /* 34B3 */ BOOLEAN m_bInvulnerable;
    /* 34B4 */ BOOLEAN m_bCanLieDown;
};

#endif /* CGAMEANIMATIONTYPECHARACTEROLD_H_ */

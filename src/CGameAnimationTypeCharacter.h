#ifndef CGAMEANIMATIONTYPECHARACTER_H_
#define CGAMEANIMATIONTYPECHARACTER_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"
#include "CVidPalette.h"

class CGameAnimationTypeCharacter : public CGameAnimationType {
public:
    CGameAnimationTypeCharacter(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeCharacter() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0028 */ BOOLEAN CanLieDown() override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 0060 */ char* GetSndArmor() override;
    /* 006C */ const char* GetSndWalk(SHORT a1) override;
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
    /* 00CC */ BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame) override;
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;

    /* 03FE */ CString m_resRefPaperDoll;
    /* 0402 */ CString m_resRef;
    /* 0406 */ CString m_heightCode;
    /* 040A */ CString m_heightCodeHelmet;
    /* 040E */ CString m_heightCodeShieldPaperDoll;
    /* 0412 */ CHAR m_armorCode;
    /* 0413 */ CHAR m_armorMaxCode;
    /* 0414 */ CVidCell* m_currentVidCell;
    /* 0418 */ CVidCell* m_currentVidCellBase;
    /* 041C */ CVidCell m_g1VidCellBase;
    /* 04F6 */ CVidCell m_caVidCellBase;
    /* 05D0 */ CVidCell m_a1VidCellBase;
    /* 06AA */ CVidCell m_a2VidCellBase;
    /* 0784 */ CVidCell m_a3VidCellBase;
    /* 085E */ CVidPalette m_charPalette;
    /* 0882 */ CString m_weaponResRef;
    /* 0886 */ CVidCell* m_currentVidCellWeapon;
    /* 088A */ CVidCell* m_currentVidCellWeaponBase;
    /* 088E */ CVidCell m_g1VidCellWeaponBase;
    /* 0968 */ CVidCell m_a1VidCellWeaponBase;
    /* 0A42 */ CVidCell m_a2VidCellWeaponBase;
    /* 0B1C */ CVidCell m_a3VidCellWeaponBase;
    /* 0BF6 */ CVidPalette m_weaponPalette;
    /* 0C1A */ CString m_shieldResRef;
    /* 0C1E */ CVidCell* m_currentVidCellShield;
    /* 0C22 */ CVidCell* m_currentVidCellShieldBase;
    /* 0C26 */ CVidCell m_g1VidCellShieldBase;
    /* 0D00 */ CVidCell m_a1VidCellShieldBase;
    /* 0DDA */ CVidCell m_a2VidCellShieldBase;
    /* 0EB4 */ CVidCell m_a3VidCellShieldBase;
    /* 0F8E */ CVidPalette m_shieldPalette;
    /* 0FB2 */ CString m_helmetResRef;
    /* 0FB6 */ CVidCell* m_currentVidCellHelmet;
    /* 0FBA */ CVidCell* m_currentVidCellHelmetBase;
    /* 0FBE */ CVidCell m_g1VidCellHelmetBase;
    /* 1098 */ CVidCell m_caVidCellHelmetBase;
    /* 1172 */ CVidCell m_a1VidCellHelmetBase;
    /* 124C */ CVidCell m_a2VidCellHelmetBase;
    /* 1326 */ CVidCell m_a3VidCellHelmetBase;
    /* 1400 */ CVidPalette m_helmetPalette;
    /* 1424 */ SHORT m_currentBamSequence;
    /* 1426 */ SHORT m_currentBamDirection;
    /* 1428 */ BOOLEAN m_renderWeapons;
    /* 142C */ BOOLEAN m_renderHelmet;
    /* 1430 */ BOOL m_bEquipHelmet;
    /* 1434 */ unsigned char field_1434;
    /* 1438 */ BOOL m_falseColor;
    /* 143C */ BYTE m_weaponCode;
    /* 143D */ BYTE m_extendDirectionTest;
    /* 143E */ BOOLEAN m_bDetectedByInfravision;
    /* 143F */ BOOLEAN m_bInvulnerable;
    /* 1440 */ BOOLEAN m_bCanLieDown;
    /* 1441 */ unsigned char field_1441;
    /* 1442 */ unsigned char field_1442;
    /* 1443 */ unsigned char field_1443;
    /* 1444 */ int field_1444;
    /* 1448 */ unsigned char field_1448;
    /* 144C */ CHAR field_144C;
    /* 144D */ unsigned char field_144D;
};

#endif /* CGAMEANIMATIONTYPECHARACTER_H_ */

#ifndef CGAMEANIMATIONTYPEMONSTERICEWIND_H_
#define CGAMEANIMATIONTYPEMONSTERICEWIND_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"
#include "CVidPalette.h"

class CGameAnimationTypeMonsterIcewind : public CGameAnimationType {
public:
    CGameAnimationTypeMonsterIcewind(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterIcewind() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
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
    /* 1BE6 */ CVidPalette m_palette;
    /* 1C0A */ SHORT m_currentBamSequence;
    /* 1C0C */ SHORT m_currentBamDirection;
    /* 1C0E */ BOOL m_falseColor;
    /* 1C12 */ CVidCell* m_currentVidCellWeaponBase;
    /* 1C16 */ CVidCell* m_currentVidCellWeaponExtend;
    /* 1C1A */ CVidBitmap m_bitmap;
    /* 1CD4 */ BOOLEAN m_bDetectedByInfravision;
    /* 1CD5 */ BYTE m_extendDirectionTest;
    /* 1CD6 */ BOOL m_bExtendDir;
    /* 1CDA */ int field_1CDA;
    /* 1CDE */ int field_1CDE;
};

#endif /* CGAMEANIMATIONTYPEMONSTERICEWIND_H_ */

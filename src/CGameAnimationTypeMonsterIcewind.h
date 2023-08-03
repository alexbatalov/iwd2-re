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
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 007C */ BOOL IsMirroring() override;
    /* 0080 */ BOOL IsBeginningOfSequence() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 008C */ void DecrementFrame() override;
    /* 0094 */ void ClearColorEffects(BYTE colorRange) override;
    /* 0098 */ void ClearColorEffectsAll() override;
    /* 00A4 */ void SetColorRange(BYTE colorRange, BYTE rangeValue) override;
    /* 00A8 */ void SetColorRangeAll(BYTE rangeValue) override;
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
    /* 092A */ CVidCell m_shVidCellBase;
    /* 0A04 */ CVidCell m_shVidCellExtend;
    /* 0ADE */ CVidCell m_awVidCellBase;
    /* 0BB8 */ CVidCell m_awVidCellExtend;
    /* 0C92 */ CVidCell m_slVidCellBase;
    /* 0D6C */ CVidCell m_slVidCellExtend;
    /* 0E46 */ CVidCell m_deVidCellBase;
    /* 0F20 */ CVidCell m_deVidCellExtend;
    /* 0FFA */ CVidCell m_daVidCellBase;
    /* 10D4 */ CVidCell m_daVidCellExtend;
    /* 11AE */ CVidCell m_paVidCellBase;
    /* 1288 */ CVidCell m_paVidCellExtend;
    /* 1362 */ CVidCell m_reVidCellBase;
    /* 143C */ CVidCell m_reVidCellExtend;
    /* 1516 */ CVidCell m_coVidCellBase;
    /* 15F0 */ CVidCell m_coVidCellExtend;
    /* 16CA */ CVidCell m_caVidCellBase;
    /* 17A4 */ CVidCell m_caVidCellExtend;
    /* 187E */ CVidCell m_twVidCellBase;
    /* 1958 */ CVidCell m_twVidCellExtend;
    /* 1A32 */ CVidCell m_waVidCellBase;
    /* 1B0C */ CVidCell m_waVidCellExtend;
    /* 1BE6 */ CVidPalette m_palette;
    /* 1C0A */ SHORT m_currentBamSequence;
    /* 1C0C */ SHORT m_currentBamDirection;
    /* 1C0E */ BOOL m_falseColor;
    /* 1C12 */ int field_1C12;
    /* 1C16 */ int field_1C16;
    /* 1C1A */ CVidBitmap m_bitmap;
    /* 1CD4 */ BOOLEAN m_bDetectedByInfravision;
    /* 1CD5 */ BYTE m_extendDirectionTest;
    /* 1CD6 */ BOOL m_bExtendDir;
    /* 1CDA */ int field_1CDA;
    /* 1CDE */ int field_1CDE;
};

#endif /* CGAMEANIMATIONTYPEMONSTERICEWIND_H_ */

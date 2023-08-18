#ifndef CGAMEANIMATIONTYPEAMBIENT_H_
#define CGAMEANIMATIONTYPEAMBIENT_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeAmbient : public CGameAnimationType {
public:
    CGameAnimationTypeAmbient(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeAmbient() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0020 */ CVidPalette* GetAnimationPalette(BYTE range) override;
    /* 0024 */ void GetAnimationResRef(CString& resRef, BYTE range) override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 003C */ BYTE GetListType() override;
    /* 0058 */ BOOL GetPathSmooth() override;
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

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_currentVidCellExtend;
    /* 040E */ CVidCell m_g1VidCellBase;
    /* 04E8 */ CVidCell m_g1VidCellExtend;
    /* 05C2 */ CVidPalette m_charPalette;
    /* 05E6 */ SHORT m_currentBamSequence;
    /* 05E8 */ SHORT m_currentBamDirection;
    /* 05EA */ BOOL m_falseColor;
    /* 05EE */ BOOL m_bInvulnerable;
    /* 05F2 */ BOOL m_pathSmooth;
    /* 05F6 */ BYTE m_listType;
    /* 05F7 */ BOOLEAN m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEAMBIENT_H_ */

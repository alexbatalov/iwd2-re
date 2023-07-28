#ifndef CGAMEANIMATIONTYPEMONSTERANKHEG_H_
#define CGAMEANIMATIONTYPEMONSTERANKHEG_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeMonsterAnkheg : public CGameAnimationType {
public:
    static const CRect ELLIPSE_EMPTY;

    CGameAnimationTypeMonsterAnkheg(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeMonsterAnkheg() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 0040 */ BYTE GetMoveScale() override;
    /* 004C */ BYTE GetMoveScaleDefault() override;
    /* 0054 */ const CRect& GetEllipseRect() override;
    /* 007C */ BOOL IsMirroring() override;
    /* 0080 */ BOOL IsBeginningOfSequence() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 008C */ void DecrementFrame() override;
    /* 0090 */ void Render(CInfinity* pInfinity, CVidMode* pVidMode, int a3, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency) override;
    /* 0094 */ void ClearColorEffects(BYTE colorRange) override;
    /* 0098 */ void ClearColorEffectsAll() override;
    /* 009C */ void SetColorEffect(BYTE effectType, BYTE colorRange, COLORREF tintColor, BYTE periodLength) override;
    /* 00A0 */ void SetColorEffectAll(BYTE effectType, COLORREF tintColor, BYTE periodLength) override;
    /* 00AC */ SHORT SetSequence(SHORT nSequence) override;
    /* 00BC */ BOOL GetAboveGround() override;
    /* 00C8 */ SHORT GetCurrentFrame() override;
    /* 00CC */ BOOLEAN GetCurrentSequenceAndFrame(SHORT nSequence, SHORT nFrame) override;
    /* 00D0 */ BOOLEAN GetCurrentResRef(CString& resBody, CString& resWeapon, CString& resShield, CString& resHelmet) override;

    /* 03FE */ CString m_resRef;
    /* 0402 */ CVidCell* m_currentVidCell;
    /* 0406 */ CVidCell* m_currentVidCellBase;
    /* 040A */ CVidCell* m_currentVidCellExtend;
    /* 040E */ CVidCell m_g1VidCellBase;
    /* 04E8 */ CVidCell m_g1VidCellExtend;
    /* 05C2 */ CVidCell m_g2VidCellBase;
    /* 069C */ CVidCell m_g2VidCellExtend;
    /* 0776 */ CVidCell m_g3VidCellBase;
    /* 0850 */ CVidCell m_g3VidCellExtend;
    /* 092A */ CVidCell* m_currentVidCellHole;
    /* 092E */ CVidCell* m_currentVidCellHoleBase;
    /* 0932 */ CVidCell* m_currentVidCellHoleExtend;
    /* 0936 */ CVidCell m_g1VidCellHoleBase;
    /* 0A10 */ CVidCell m_g1VidCellHoleExtend;
    /* 0AEA */ CVidCell m_g2VidCellHoleBase;
    /* 0BC4 */ CVidCell m_g2VidCellHoleExtend;
    /* 0C9E */ CVidCell m_g3VidCellHoleBase;
    /* 0D78 */ CVidCell m_g3VidCellHoleExtend;
    /* 0E52 */ SHORT m_currentBamSequence;
    /* 0E54 */ SHORT m_currentBamDirection;
    /* 0E56 */ BOOL m_bAboveGround;
    /* 0E5A */ BYTE m_extendDirectionTest;
};

#endif /* CGAMEANIMATIONTYPEMONSTERANKHEG_H_ */

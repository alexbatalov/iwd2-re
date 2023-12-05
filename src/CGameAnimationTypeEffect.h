#ifndef CGAMEANIMATIONTYPEEFFECT_H_
#define CGAMEANIMATIONTYPEEFFECT_H_

#include "CGameAnimationType.h"
#include "CVidCell.h"

class CGameAnimationTypeEffect : public CGameAnimationType {
public:
    CGameAnimationTypeEffect(USHORT animationID, BYTE* colorRangeValues, WORD facing);
    /* 0000 */ ~CGameAnimationTypeEffect() override;
    /* 0004 */ void CalculateFxRect(CRect& rFx, CPoint& ptReference, LONG posZ) override;
    /* 0008 */ void CalculateGCBoundsRect(CRect& rGCBounds, const CPoint& pos, const CPoint& ptReference, LONG posZ, LONG nWidth, LONG nHeight) override;
    /* 002C */ BOOLEAN DetectedByInfravision() override;
    /* 000C */ void ChangeDirection(SHORT nDirection) override;
    /* 007C */ BOOL IsMirroring() override;
    /* 0084 */ BOOL IsEndOfSequence() override;
    /* 0088 */ void IncrementFrame() override;
    /* 0090 */ void Render(CInfinity* pInfinity, CVidMode* pVidMode, INT nSurface, const CRect& rectFX, const CPoint& ptNewPos, const CPoint& ptReference, DWORD dwRenderFlags, COLORREF rgbTintColor, const CRect& rGCBounds, BOOL bDithered, BOOL bFadeOut, LONG posZ, BYTE transparency) override;
    /* 00AC */ SHORT SetSequence(SHORT nSequence) override;
    /* 00C8 */ SHORT GetCurrentFrame() override;

    /* 03FE */ CVidCell* m_currentVidCell;
    /* 0402 */ CVidCell* m_currentVidCellShadow;
    /* 0406 */ CVidCell m_g1VidCell;
    /* 04E0 */ CVidCell m_g1VidCellShadow;
    /* 05BA */ CVidPalette m_palette;
    /* 05DE */ unsigned char field_5DE;
    /* 05DF */ BOOLEAN m_translucent;
    /* 05E0 */ BOOLEAN m_bRender;
    /* 05E1 */ unsigned char field_5E1;
    /* 05E2 */ SHORT m_currentBamSequence;
    /* 05E4 */ SHORT m_currentBamDirection;
    /* 05E6 */ BYTE m_extendDirectionTest;
    /* 05E7 */ unsigned char field_5E7;
};

#endif /* CGAMEANIMATIONTYPEEFFECT_H_ */

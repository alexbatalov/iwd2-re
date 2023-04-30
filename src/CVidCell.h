#ifndef CVIDCELL_H_
#define CVIDCELL_H_

#include "CResCell.h"
#include "CResCellHeader.h"
#include "CVidImage.h"

class CVidPoly;

class CVidCell : public CVidImage, public CResHelper<CResCell, 1000> {
public:
    static BOOL TRANSLUCENT_SHADOWS_ON;

    CVidCell();
    ~CVidCell();
    void AddRangeAffect(USHORT nAffectType, USHORT nRangeId, COLORREF rgbAffectColor, BYTE pulsePeriod);
    void DeleteResPaletteAffect();
    void DeleteRangeAffects(USHORT nRangeId);
    BOOL FrameAdvance();
    BOOL FrameSet(SHORT nFrame);
    void RestoreBackground(INT nFrom, INT nTo, const CRect& rClip);
    void RealizePalette(DWORD dwFlags);
    BOOL SequenceSet(SHORT nSequence);
    void AddResPaletteAffect(USHORT nAffectType, COLORREF rgbAffectColor, BYTE pulsePeriod);
    void SuppressTint(SHORT nRange);
    void UnsuppressTint(SHORT nRange);

    /* 0004 */ virtual BOOL Render(WORD* pSurface, LONG lPitch, INT nRefPtX, INT nRefPtY, const CRect& rClip, BOOLEAN a6, DWORD dwFlags, const CPoint& ptSource);
    /* 000C */ virtual BOOL Render(WORD* pSurface, LONG lPitch, INT nRefPointX, INT nRefPointY, DWORD dwFlags, INT nTransValue);

    BOOL Render3d(INT x, INT y, const CRect& rClip, CVidPoly* pClipPoly, int nPolys, DWORD dwFlags, INT nTransVal, BOOL bDemanded);
    BOOL Render3d(INT x, INT y, const CRect& rClip, BOOLEAN bDemanded, DWORD dwFlags);
    BOOL FXRender3d(INT nRefPtX, INT nRefPtY, const CRect& rFXRect, DWORD dwFlags, INT nTransVal, BOOL bAlphaValues);
    BOOL FXRender3d(INT nRefPtX, INT nRefPtY, const CRect& rFXRect, const CRect& rClip, BOOLEAN a5, DWORD dwFlags, BOOL bAlphaValues);

    /* 00B4 */ CResHelper<CResCellHeader, 1100> field_B4;
    /* 00C4 */ SHORT m_nCurrentFrame;
    /* 00C6 */ SHORT m_nCurrentSequence; // #guess
    /* 00C8 */ int field_C8;
    /* 00CC */ int field_CC;
    /* 00D0 */ int field_D0;
    /* 00D4 */ unsigned char field_D4;
    /* 00D6 */ int field_D6;
};

#endif /* CVIDCELL_H_ */

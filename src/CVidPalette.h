#ifndef CVIDPALETTE_H_
#define CVIDPALETTE_H_

#include "mfc.h"

typedef struct {
    /* 0000 */ COLORREF rgbTintColor;
    /* 0004 */ COLORREF rgbAddColor;
    /* 0008 */ COLORREF rgbLightColor;
    /* 000C */ COLORREF* pRangeTints[7];
    /* 0028 */ BYTE aRangeTintPeriods[8];
    /* 0030 */ COLORREF* pRangeAdds[7];
    /* 004C */ BYTE aRangeAddPeriods[8];
    /* 0054 */ COLORREF* pRangeLights[7];
    /* 0070 */ BYTE aRangeLightPeriods[7];
    /* 0077 */ BYTE suppressTints;
} CVIDIMG_PALETTEAFFECT;

typedef struct {
    INT rgbRed;
    INT rgbGreen;
    INT rgbBlue;
} CVIDPALETTE_COLOR;

class CVidBitmap;

class CVidPalette {
public:
    CVidPalette(USHORT nType = TYPE_RESOURCE);
    ~CVidPalette();
    void SetAUCounter();
    void SetType(USHORT nType);
    void CalculateSubRanges();
    INT GetReservedEntries(DWORD dwFlags);
    void Realize(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal);
    void SetPalette(RGBQUAD* pPalette, int nEntries, USHORT nType);
    void SetPalette(const CVidPalette& cPalette);
    RGBQUAD SetPaletteEntry(USHORT nEntry, COLORREF rgbColor);
    BOOL GetTint(CVIDPALETTE_COLOR& rgbTint, CVIDIMG_PALETTEAFFECT* pAffectArgs, INT& nShiftBack, INT& nMaxValue, DWORD dwFlags);
    BOOL GetAdd(CVIDPALETTE_COLOR& rgbInv, CVIDIMG_PALETTEAFFECT* pAffectArgs, INT& nShiftBack, DWORD dwFlags);
    BOOL GetLight(CVIDPALETTE_COLOR& rgbLight, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD dwFlags);
    void SetRange(USHORT nRange, USHORT nValue, CVidBitmap& bmpMasterPalette);
    void RealizeRange(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal);
    void RealizeResource(DWORD* pDestPalette, INT nBpp, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs);
    void QuickRealizeResource(DWORD* pDestPalette, INT nBpp);

    void RealizeResource3d(DWORD* pDestPalette, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal);
    void RealizeRange3d(DWORD* pDestPalette, DWORD dwFlags, CVIDIMG_PALETTEAFFECT* pAffectArgs, DWORD nTransVal);

    static const RGBQUAD CLEAR_RGBQUAD;
    static const RGBQUAD SHADOW_RGBQUAD;
    static const USHORT TYPE_RESOURCE;
    static const USHORT TYPE_RANGE;
    static const USHORT NUM_RANGES;
    static const BYTE SHADOW_ENTRY;
    static const BYTE CLEAR_ENTRY;
    static const BYTE LIGHT_SCALE;
    static const BYTE NO_TINT;
    static BYTE m_SuppressTintMasks[7];

    int m_nAUCounter;
    int m_nAUCounterBase;
    RGBQUAD* m_pPalette;
    int m_nEntries;
    COLORREF rgbGlobalTint;
    USHORT m_nType;
    BOOLEAN m_bPaletteOwner;
    BOOL m_bSubRangesCalculated;
    BYTE m_rangeColors[7];
};

#endif /* CVIDPALETTE_H_ */

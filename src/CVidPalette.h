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

class CVidPalette {
public:
    CVidPalette(USHORT nType = TYPE_RESOURCE);
    ~CVidPalette();
    void SetType(USHORT nType);
    INT GetReservedEntries(DWORD dwFlags);
    void SetPalette(RGBQUAD* pPalette, int nEntries, USHORT nType);
    void SetPalette(const CVidPalette& cPalette);
    RGBQUAD SetPaletteEntry(USHORT nEntry, COLORREF rgbColor);

    static const RGBQUAD CLEAR_RGBQUAD;
    static const RGBQUAD SHADOW_RGBQUAD;
    static const USHORT TYPE_RESOURCE;
    static const USHORT TYPE_RANGE;
    static const USHORT NUM_RANGES;
    static const BYTE LIGHT_SCALE;

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

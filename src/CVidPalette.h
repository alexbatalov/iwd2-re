#ifndef CVIDPALETTE_H_
#define CVIDPALETTE_H_

#include "mfc.h"

#define CVIDPALETTE_RANGE_METAL 0
#define CVIDPALETTE_RANGE_MAIN_CLOTH 2
#define CVIDPALETTE_RANGE_MINOR_CLOTH 1
#define CVIDPALETTE_RANGE_SKIN 3
#define CVIDPALETTE_RANGE_LEATHER 4
#define CVIDPALETTE_RANGE_ARMOR 5
#define CVIDPALETTE_RANGE_HAIR 6

#define CVIDPALETTE_HAIR_BLACK 0
#define CVIDPALETTE_HAIR_LT_BROWN 1
#define CVIDPALETTE_HAIR_DK_BROWN 2
#define CVIDPALETTE_HAIR_BLONDE 3
#define CVIDPALETTE_HAIR_RED 4
#define CVIDPALETTE_HAIR_LT_GREY 5
#define CVIDPALETTE_HAIR_DK_GREY 6
#define CVIDPALETTE_HAIR_LT_GREEN 7
#define CVIDPALETTE_SKIN_EBONY 8
#define CVIDPALETTE_SKIN_DK_BROWN 9
#define CVIDPALETTE_SKIN_OLIVE 10
#define CVIDPALETTE_SKIN_RED 11
#define CVIDPALETTE_SKIN_PINK 12
#define CVIDPALETTE_SKIN_WHITE 13
#define CVIDPALETTE_SKIN_GREY 14
#define CVIDPALETTE_SKIN_LT_GREEN 15
#define CVIDPALETTE_SKIN_YELLOW 16
#define CVIDPALETTE_SKIN_LT_BLUE 17
#define CVIDPALETTE_SKIN_M_BLUE 18
#define CVIDPALETTE_SKIN_M_RED 19
#define CVIDPALETTE_SKIN_M_GREEN 20
#define CVIDPALETTE_LEATHER_BLACK 21
#define CVIDPALETTE_LEATHER_LT_BROWN 22
#define CVIDPALETTE_LEATHER_DK_BROWN 23
#define CVIDPALETTE_METAL_BRONZE 24
#define CVIDPALETTE_METAL_GOLD 25
#define CVIDPALETTE_METAL_COPPER 26
#define CVIDPALETTE_METAL_SILVER 27
#define CVIDPALETTE_METAL_ALUMINUM 28
#define CVIDPALETTE_METAL_OBSIDIAN 29
#define CVIDPALETTE_METAL_IRON 30
#define CVIDPALETTE_METAL_BLUE 31
#define CVIDPALETTE_METAL_GREEN 32
#define CVIDPALETTE_METAL_RED 33
#define CVIDPALETTE_METAL_RAINBOW_1 34
#define CVIDPALETTE_METAL_RAINBOW_2 35
#define CVIDPALETTE_CLOTH_LT_OLIVE 36
#define CVIDPALETTE_CLOTH_DK_OLIVE 37
#define CVIDPALETTE_CLOTH_LT_BROWN_1 38
#define CVIDPALETTE_CLOTH_DK_BROWN_1 39
#define CVIDPALETTE_CLOTH_LT_BROWN_2 40
#define CVIDPALETTE_CLOTH_DK_BROWN_2 41
#define CVIDPALETTE_CLOTH_LT_KHAKI 42
#define CVIDPALETTE_CLOTH_DK_KHAKI 43
#define CVIDPALETTE_CLOTH_LT_MAGENTA 44
#define CVIDPALETTE_CLOTH_DK_MAGENTA 45
#define CVIDPALETTE_CLOTH_LT_RED 46
#define CVIDPALETTE_CLOTH_DK_RED 47
#define CVIDPALETTE_CLOTH_LT_ORANGE 48
#define CVIDPALETTE_CLOTH_DK_ORANGE 49
#define CVIDPALETTE_CLOTH_LT_YELLOW 50
#define CVIDPALETTE_CLOTH_DK_YELLOW 51
#define CVIDPALETTE_CLOTH_LT_GREEN 52
#define CVIDPALETTE_CLOTH_MED_GREEN 53
#define CVIDPALETTE_CLOTH_DK_GREEN 54
#define CVIDPALETTE_CLOTH_LT_AQUA 55
#define CVIDPALETTE_CLOTH_DK_AQUA 56
#define CVIDPALETTE_CLOTH_LT_BLUE 57
#define CVIDPALETTE_CLOTH_DK_BLUE 58
#define CVIDPALETTE_CLOTH_LT_INDIGO 59
#define CVIDPALETTE_CLOTH_DK_INDIGO 60
#define CVIDPALETTE_CLOTH_LT_VIOLET 61
#define CVIDPALETTE_CLOTH_DK_VIOLET 62
#define CVIDPALETTE_CLOTH_WHITE 63
#define CVIDPALETTE_CLOTH_LT_GREY 64
#define CVIDPALETTE_CLOTH_DK_GREY 65
#define CVIDPALETTE_CLOTH_BLACK 66
#define CVIDPALETTE_FIRE_NORMAL 67
#define CVIDPALETTE_FIRE_BLUE 68
#define CVIDPALETTE_FIRE_GREEN 69
#define CVIDPALETTE_FLESH_RENDERED 70
#define CVIDPALETTE_ICE 71
#define CVIDPALETTE_STONE 72
#define CVIDPALETTE_ACID 73
#define CVIDPALETTE_WHITE_0_0_0 74
#define CVIDPALETTE_BLACK_0_0_0 75
#define CVIDPALETTE_RED_255_0_0 76
#define CVIDPALETTE_GREEN_0_255_0 77
#define CVIDPALETTE_BLUE_0_0_255 78
#define CVIDPALETTE_HAIR_WHITE 79
#define CVIDPALETTE_HAIR_ORANGE 80
#define CVIDPALETTE_HAIR_GOLD 81
#define CVIDPALETTE_HAIR_LT_BLUE 82
#define CVIDPALETTE_SKIN_INDIGO 83
#define CVIDPALETTE_SKIN_HARDY 84
#define CVIDPALETTE_SKIN_RUGGED 85
#define CVIDPALETTE_SKIN_MERMAN 86
#define CVIDPALETTE_SKIN_NUBIAN 87
#define CVIDPALETTE_SKIN_SUNBURN 88
#define CVIDPALETTE_SKIN_PALE 89
#define CVIDPALETTE_SKIN_ORIENTAL 90
#define CVIDPALETTE_LEATHER_DK_BROWN2 91
#define CVIDPALETTE_LEATHERLT_BROWN2 92
#define CVIDPALETTE_LEATHER_LEATHER_UMBER 93
#define CVIDPALETTE_LEATHER_LEATHER_SIENNA 94
#define CVIDPALETTE_LEATHER_LEATHER_LIGHT_TAN 95
#define CVIDPALETTE_METAL_STEEL 96
#define CVIDPALETTE_METAL_MITHRAL 97
#define CVIDPALETTE_METAL_ANTIQUE 98
#define CVIDPALETTE_METAL_DARK_GOLD 99
#define CVIDPALETTE_METAL_BURNISHED 100
#define CVIDPALETTE_METAL_CHERRY 101
#define CVIDPALETTE_METAL_SLATE 102
#define CVIDPALETTE_METAL_EMERALD 103
#define CVIDPALETTE_METAL_VIOLET 104
#define CVIDPALETTE_SKIN_ALABASTER 105
#define CVIDPALETTE_SKIN_LT_GREY 106
#define CVIDPALETTE_SKIN_DK_GREY 107
#define CVIDPALETTE_SKIN_PINKPALE 108
#define CVIDPALETTE_SKIN_COPPER 109
#define CVIDPALETTE_HAIR_SILVER 110
#define CVIDPALETTE_HAIR_COPPER 111
#define CVIDPALETTE_SKIN_GREYGREEN 112
#define CVIDPALETTE_SKIN_BROWNGREY 113
#define CVIDPALETTE_SKIN_RICHBROWN 114

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
    static const RGBQUAD CLEAR_RGBQUAD;
    static const RGBQUAD SHADOW_RGBQUAD;
    static const USHORT TYPE_RESOURCE;
    static const USHORT TYPE_RANGE;
    static const USHORT NUM_RANGES;
    static const BYTE SHADOW_ENTRY;
    static const BYTE CLEAR_ENTRY;
    static const BYTE LIGHT_SCALE;
    static const BYTE NO_TINT;
    static const BYTE RANGE_METAL;
    static const BYTE RANGE_MAIN_CLOTH;
    static const BYTE RANGE_MINOR_CLOTH;
    static const BYTE RANGE_SKIN;
    static const BYTE RANGE_LEATHER;
    static const BYTE RANGE_ARMOR;
    static const BYTE RANGE_HAIR;
    static const BYTE HAIR_BLACK;
    static const BYTE HAIR_LT_BROWN;
    static const BYTE HAIR_DK_BROWN;
    static const BYTE HAIR_BLONDE;
    static const BYTE HAIR_RED;
    static const BYTE HAIR_LT_GREY;
    static const BYTE HAIR_DK_GREY;
    static const BYTE HAIR_LT_GREEN;
    static const BYTE SKIN_EBONY;
    static const BYTE SKIN_DK_BROWN;
    static const BYTE SKIN_OLIVE;
    static const BYTE SKIN_RED;
    static const BYTE SKIN_PINK;
    static const BYTE SKIN_WHITE;
    static const BYTE SKIN_GREY;
    static const BYTE SKIN_LT_GREEN;
    static const BYTE SKIN_YELLOW;
    static const BYTE SKIN_LT_BLUE;
    static const BYTE SKIN_M_BLUE;
    static const BYTE SKIN_M_RED;
    static const BYTE SKIN_M_GREEN;
    static const BYTE LEATHER_BLACK;
    static const BYTE LEATHER_LT_BROWN;
    static const BYTE LEATHER_DK_BROWN;
    static const BYTE METAL_BRONZE;
    static const BYTE METAL_GOLD;
    static const BYTE METAL_COPPER;
    static const BYTE METAL_SILVER;
    static const BYTE METAL_ALUMINUM;
    static const BYTE METAL_OBSIDIAN;
    static const BYTE METAL_IRON;
    static const BYTE METAL_BLUE;
    static const BYTE METAL_GREEN;
    static const BYTE METAL_RED;
    static const BYTE METAL_RAINBOW_1;
    static const BYTE METAL_RAINBOW_2;
    static const BYTE CLOTH_LT_OLIVE;
    static const BYTE CLOTH_DK_OLIVE;
    static const BYTE CLOTH_LT_BROWN_1;
    static const BYTE CLOTH_DK_BROWN_1;
    static const BYTE CLOTH_LT_BROWN_2;
    static const BYTE CLOTH_DK_BROWN_2;
    static const BYTE CLOTH_LT_KHAKI;
    static const BYTE CLOTH_DK_KHAKI;
    static const BYTE CLOTH_LT_MAGENTA;
    static const BYTE CLOTH_DK_MAGENTA;
    static const BYTE CLOTH_LT_RED;
    static const BYTE CLOTH_DK_RED;
    static const BYTE CLOTH_LT_ORANGE;
    static const BYTE CLOTH_DK_ORANGE;
    static const BYTE CLOTH_LT_YELLOW;
    static const BYTE CLOTH_DK_YELLOW;
    static const BYTE CLOTH_LT_GREEN;
    static const BYTE CLOTH_MED_GREEN;
    static const BYTE CLOTH_DK_GREEN;
    static const BYTE CLOTH_LT_AQUA;
    static const BYTE CLOTH_DK_AQUA;
    static const BYTE CLOTH_LT_BLUE;
    static const BYTE CLOTH_DK_BLUE;
    static const BYTE CLOTH_LT_INDIGO;
    static const BYTE CLOTH_DK_INDIGO;
    static const BYTE CLOTH_LT_VIOLET;
    static const BYTE CLOTH_DK_VIOLET;
    static const BYTE CLOTH_WHITE;
    static const BYTE CLOTH_LT_GREY;
    static const BYTE CLOTH_DK_GREY;
    static const BYTE CLOTH_BLACK;
    static const BYTE FIRE_NORMAL;
    static const BYTE FIRE_BLUE;
    static const BYTE FIRE_GREEN;
    static const BYTE FLESH_RENDERED;
    static const BYTE ICE;
    static const BYTE STONE;
    static const BYTE ACID;
    static const BYTE WHITE_0_0_0;
    static const BYTE BLACK_0_0_0;
    static const BYTE RED_255_0_0;
    static const BYTE GREEN_0_255_0;
    static const BYTE BLUE_0_0_255;
    static const BYTE HAIR_WHITE;
    static const BYTE HAIR_ORANGE;
    static const BYTE HAIR_GOLD;
    static const BYTE HAIR_LT_BLUE;
    static const BYTE SKIN_INDIGO;
    static const BYTE SKIN_HARDY;
    static const BYTE SKIN_RUGGED;
    static const BYTE SKIN_MERMAN;
    static const BYTE SKIN_NUBIAN;
    static const BYTE SKIN_SUNBURN;
    static const BYTE SKIN_PALE;
    static const BYTE SKIN_ORIENTAL;
    static const BYTE LEATHER_DK_BROWN2;
    static const BYTE LEATHERLT_BROWN2;
    static const BYTE LEATHER_LEATHER_UMBER;
    static const BYTE LEATHER_LEATHER_SIENNA;
    static const BYTE LEATHER_LEATHER_LIGHT_TAN;
    static const BYTE METAL_STEEL;
    static const BYTE METAL_MITHRAL;
    static const BYTE METAL_ANTIQUE;
    static const BYTE METAL_DARK_GOLD;
    static const BYTE METAL_BURNISHED;
    static const BYTE METAL_CHERRY;
    static const BYTE METAL_SLATE;
    static const BYTE METAL_EMERALD;
    static const BYTE METAL_VIOLET;
    static const BYTE SKIN_ALABASTER;
    static const BYTE SKIN_LT_GREY;
    static const BYTE SKIN_DK_GREY;
    static const BYTE SKIN_PINKPALE;
    static const BYTE SKIN_COPPER;
    static const BYTE HAIR_SILVER;
    static const BYTE HAIR_COPPER;
    static const BYTE SKIN_GREYGREEN;
    static const BYTE SKIN_BROWNGREY;
    static const BYTE SKIN_RICHBROWN;
    static const COLORREF RANGE_COLORS[];

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

#ifndef BALDATATYPES_H_
#define BALDATATYPES_H_

#include "ChDataTypes.h"

typedef DWORD STRREF;

typedef struct UI_Header_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ DWORD nPanels;
    /* 000C */ DWORD nOffsetToControlTable;
    /* 0010 */ DWORD nOffsetToPanelTable;
} UI_HEADER;

typedef struct UI_ControlTableEntry_st {
    /* 0000 */ DWORD nControlOffset;
    /* 0004 */ DWORD nControlSize;
} UI_CONTROLTABLEENTRY;

typedef struct UI_PanelHeader_st {
    /* 0000 */ DWORD nPanelID;
    /* 0004 */ WORD x;
    /* 0006 */ WORD y;
    /* 0008 */ WORD nWidth;
    /* 000A */ WORD nHeight;
    /* 000C */ WORD nType;
    /* 000E */ WORD nControls;
    /* 0010 */ RESREF refMosaic;
    /* 0018 */ WORD nFirstControl;
    /* 001A */ WORD wFlags;
} UI_PANELHEADER;

typedef struct UI_Control_st {
    /* 0000 */ DWORD nID;
    /* 0004 */ WORD x;
    /* 0006 */ WORD y;
    /* 0008 */ WORD nWidth;
    /* 000A */ WORD nHeight;
    /* 000C */ WORD nType;
} UI_CONTROL;

typedef struct WED_WedHeader_st {
    /* 0000 */ DWORD nFileType;
    /* 0004 */ DWORD nFileVersion;
    /* 0008 */ DWORD nLayers;
    /* 000C */ DWORD nTiledObjects;
    /* 0010 */ DWORD nOffsetToLayerHeaders;
    /* 0014 */ DWORD nOffsetToPolyHeader;
    /* 0018 */ DWORD nOffsetToTiledObjects;
    /* 001C */ DWORD nOffsetToObjectTileList;
    /* 0020 */ WORD nVisiblityRange;
    /* 0022 */ WORD nChanceOfRain;
    /* 0024 */ WORD nChanceOfFog;
    /* 0026 */ WORD nChanceOfSnow;
    /* 0028 */ DWORD dwFlags;
} WED_WEDHEADER;

typedef struct WED_LayerHeader_st {
    /* 0000 */ WORD nTilesAcross;
    /* 0002 */ WORD nTilesDown;
    /* 0004 */ RESREF rrTileSet;
    /* 000C */ WORD nNumUniqueTiles;
    /* 000E */ WORD nLayerFlags;
    /* 0010 */ DWORD nOffsetToTileData;
    /* 0014 */ DWORD nOffsetToTileList;
} WED_LAYERHEADER;

typedef struct WED_PolyHeader_st {
    /* 0000 */ DWORD nPolys;
    /* 0004 */ DWORD nOffsetToPolyList;
    /* 0008 */ DWORD nOffsetToPointList;
    /* 000C */ DWORD nOffsetToScreenSectionList;
    /* 0010 */ DWORD nOffsetToScreenPolyList;
} WED_POLYHEADER;

typedef struct WED_ScreenSectionList {
    /* 0000 */ WORD nStartingPoly;
    /* 0002 */ WORD nNumPolys;
} WED_SCREENSECTIONLIST;

typedef struct WED_PolyList_st {
    /* 0000 */ DWORD nStartingPoint;
    /* 0004 */ DWORD nNumPoints;
    /* 0008 */ BYTE nType;
    /* 0009 */ BYTE nHeight;
    /* 000A */ WORD nLeft;
    /* 000C */ WORD nRight;
    /* 000E */ WORD nTop;
    /* 0010 */ WORD nBottom;
} WED_POLYLIST;

typedef struct WED_PolyPoint_st {
    /* 0000 */ WORD x;
    /* 0002 */ WORD y;
} WED_POLYPOINT;

typedef struct WED_TileData_st {
    /* 0000 */ WORD nStartingTile;
    /* 0002 */ WORD nNumTiles;
    /* 0004 */ WORD nSecondary;
    /* 0006 */ BYTE bFlags;
    /* 0007 */ BYTE bAnimSpeed;
    /* 0008 */ WORD wFlags;
} WED_TILEDATA;

typedef struct WED_TiledObject_st {
    /* 0000 */ RESREF resID;
    /* 0008 */ WORD bType;
    /* 000A */ WORD nStartingTile;
    /* 000C */ WORD nNumTiles;
    /* 000E */ WORD nNumPrimaryPolys;
    /* 0010 */ WORD nNumSecondaryPolys;
    /* 0012 */ DWORD nOffsetToPrimaryPolys;
    /* 0016 */ DWORD nOffsetToSecondaryPolys;
} WED_TILEDOBJECT;

#endif /* BALDATATYPES_H_ */

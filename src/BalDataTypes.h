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

#endif /* BALDATATYPES_H_ */

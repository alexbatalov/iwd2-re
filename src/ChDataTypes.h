#ifndef CHDATATYPES_H_
#define CHDATATYPES_H_

#include "mfc.h"

#define RESREF_SIZE 8

typedef BYTE RESREF[RESREF_SIZE];

typedef DWORD RESID;

typedef struct KeyFileHeader_st {
    DWORD nFileType;
    DWORD nFileVersion;
    DWORD nResFiles;
    DWORD nKeys;
    DWORD nOffsetToFileTable;
    DWORD nOffsetToKeyTable;
} KEYFILE_HEADER;

typedef struct KeyFileResFileName_st {
    DWORD nFileSize;
    DWORD nFileNameOffset;
    WORD nFileNameSize;
    WORD bDrives;
} KEYFILE_RESFILENAME;

#pragma pack(push)
#pragma pack(2)

typedef struct KeyFileKeyEntry_st {
    RESREF resRef;
    WORD nType;
    RESID nID;
} KEYFILE_KEYENTRY;

#pragma pack(pop)

typedef struct biffHeader_st {
    DWORD dwFileType;
    DWORD dwVersion;
    DWORD nVarRes;
    DWORD nFixedRes;
    DWORD nTableOffset;
} BIFF_HEADER;

typedef struct biffVarTableEntry_st {
    RESID nID;
    DWORD nOffset;
    DWORD nSize;
    DWORD nType;
} BIFF_VARTABLEENTRY;

typedef struct biffFixedTableEntry_st {
    RESID nID;
    DWORD nOffset;
    DWORD nNumber;
    DWORD nSize;
    DWORD nType;
} BIFF_FIXEDTABLEENTRY;

typedef struct {
    DWORD nFileType;
    DWORD nFileVersion;
    WORD nLanguage;
    DWORD nStrEntries;
    DWORD nStrEntriesOffset;
} TLK_FILE_HEADER;

typedef struct mosHeader_st {
    DWORD nFileType;
    DWORD nFileVersion;
    WORD nWidth;
    WORD nHeight;
    WORD nXTiles;
    WORD nYTiles;
    WORD nTileSize;
    BYTE nTransparentColor;
    BYTE nCompressed;
    DWORD nPaletteOffset;
} MOSAICHEADER;

typedef struct bamHeader_st {
    DWORD nFileType;
    DWORD nFileVersion;
    WORD nFrames;
    BYTE nSequences;
    BYTE nTransparentColor;
    DWORD nTableOffset;
    DWORD nPaletteOffset;
    DWORD nFrameListOffset;
} BAMHEADER;

typedef struct frameTableEntry_st {
    WORD nWidth;
    WORD nHeight;
    short nCenterX;
    short nCenterY;
    DWORD nOffset;
} FRAMEENTRY;

typedef struct sequenceTableEntry_st {
    SHORT nFrames;
    WORD nStartingFrame;
} SEQUENCEENTRY;

#endif /* CHDATATYPES_H_ */

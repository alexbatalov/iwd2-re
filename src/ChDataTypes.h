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

typedef struct KeyFileKeyEntry_st {
    RESREF resRef;
    WORD nType;
    RESID nID;
} KEYFILE_KEYENTRY;

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

#endif /* CHDATATYPES_H_ */

#ifndef CTLKTABLE_H_
#define CTLKTABLE_H_

#include "mfc.h"

#include "CTlkFileOverride.h"
#include "ChDataTypes.h"
#include "CSound.h"

typedef struct {
    CString szText;
    CSound cSound;
} STR_RES;

extern unsigned char byte_8FB954;

class CTlkFile : public CFile {
public:
    CTlkFile();

    /* 0010 */ BOOLEAN m_bOpened; // #guess
    /* 0012 */ TLK_FILE_HEADER m_header; // #guess
};

class CTlkTable {
public:
    static BOOLEAN STRREF_ON;

    CTlkTable();
    ~CTlkTable();
    BOOL AddTlkFile(const CString& filePath, BYTE a3, BYTE a4, BOOLEAN a5);
    BOOL CloseFile(BYTE a2, BYTE a3);
    BOOLEAN Fetch(DWORD dwStrId, STR_RES& strRes);
    BOOL OpenFile(BYTE a2, BYTE a3);

    CTypedPtrMap<CMapWordToPtr, USHORT, CTlkFile*> field_0;
    CMapStringToString field_1C;
    CCriticalSection field_38;
    unsigned char field_58;
    CTlkFileOverride m_override;
    unsigned char field_A4;
};

#endif /* CTLKTABLE_H_ */

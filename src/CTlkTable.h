#ifndef CTLKTABLE_H_
#define CTLKTABLE_H_

#include "mfc.h"

#include "CStrRes.h"
#include "CTlkFileOverride.h"

#pragma pack(push)
#pragma pack(2)

typedef struct {
    DWORD nFileType;
    DWORD nFileVersion;
    WORD nLanguage;
    DWORD nStrEntries;
    DWORD nStrEntriesOffset;
} TLK_FILE_HEADER;

typedef struct {
    WORD wFlags;
    RESREF sndResRef;
    DWORD volumeVariance;
    DWORD pitchVariance;
    DWORD offsetToStr;
    DWORD strSize;
} STR_RES_HEADER;

#pragma pack(pop)

extern unsigned char byte_8FB954;

class CTlkFile : public CFile {
public:
    CTlkFile();

    /* 0010 */ BOOLEAN m_bOpened; // #guess
    /* 0012 */ TLK_FILE_HEADER m_header; // #guess
};

class CTlkTable {
public:
    static const DWORD dword_85DD64;
    static const BYTE byte_85DD68;
    static const DWORD dword_85DD6C;
    static BOOLEAN STRREF_ON;

    CTlkTable();
    BOOL OpenOverride(const CString& a1, const CString& a2);
    ~CTlkTable();
    BOOL AddTlkFile(const CString& filePath, BYTE a3, BYTE a4, BOOLEAN bOpen);
    BOOL CloseFile(BYTE a2, BYTE a3);
    BOOLEAN Fetch(DWORD dwStrId, STR_RES& strRes);
    BOOL OpenFile(BYTE a2, BYTE a3);
    void ParseStr(CString& sText);
    void SetToken(const CString& sKey, const CString& sValue);

    CTypedPtrMap<CMapWordToPtr, USHORT, CTlkFile*> m_mapTlkFiles;
    CMapStringToString m_mapTokens;
    CCriticalSection field_38;
    unsigned char field_58;
    CTlkFileOverride m_override;
    unsigned char field_A4;
};

#endif /* CTLKTABLE_H_ */

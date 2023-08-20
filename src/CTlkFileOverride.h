#ifndef CTLKFILEOVERRIDE_H_
#define CTLKFILEOVERRIDE_H_

#include "mfc.h"

#include "CStrRes.h"

class CTlkFileOverrideTextEntry {
public:
    CTlkFileOverrideTextEntry();

    DWORD m_nNextFreeOffset;
    DWORD m_nPrevOffset;
    char m_text[512];
    DWORD m_nNextOffset;
};

class CTlkFileOverrideText : public CFile {
public:
    CTlkFileOverrideText();
    DWORD AddString(const CString& sString);
    void RemoveString(DWORD nOffset);
    void GetString(DWORD nOffset, CString& sString);

    /* 0010 */ DWORD m_nNextFreeOffset;
    /* 0014 */ BOOLEAN m_bOpen;
};

class CTlkFileOverrideHeaderFileHeader {
public:
    DWORD nFileType;
    int field_4;
    int field_8;
    DWORD nEntryCount;
    int field_10;
};

class CTlkFileOverrideHeaderEntry {
public:
    DWORD strId;
    DWORD dwFlags;
    RESREF sndResRef;
    DWORD volumeVariance;
    DWORD pitchVariance;
    DWORD offsetToStr;
};

class CTlkFileOverrideHeader : public CFile {
public:
    CTlkFileOverrideHeader();
    ~CTlkFileOverrideHeader();

    BOOLEAN Unmarshal();
    BOOL AddKey(CTlkFileOverrideHeaderEntry* pKey);
    CTlkFileOverrideHeaderEntry* FindKey(DWORD strId);
    void Marshal();

    /* 0010 */ BOOLEAN m_bOpen;
    /* 0012 */ CTlkFileOverrideHeaderEntry** m_ppEntries;
    /* 0016 */ int m_nEntryCount;
    /* 001A */ CTlkFileOverrideHeaderFileHeader m_header;
};

class CTlkFileOverride {
public:
    static const WORD ENTRY_HAVE_TEXT;
    static const WORD ENTRY_HAVE_SOUND;

    // Constructor is inlined in `CTlkTable`.
    CTlkFileOverride() { }

    // Destructor is inlined in `CTlkTable`.
    ~CTlkFileOverride() { }

    BOOLEAN Fetch(DWORD strId, STR_RES& strRes);
    void AddUserEntry(DWORD strId, STR_RES& strRes);
    void Remove(DWORD strId);
    void Save();
    void Open(const CString& sHeaderFileName, const CString& sTextFileName);
    DWORD Add(const CString& sString);
    void CloseFiles();

    /* 0000 */ CString field_0;
    /* 0004 */ CString field_4;
    /* 0008 */ CTlkFileOverrideHeader m_header;
    /* 0036 */ CTlkFileOverrideText m_text;
};

#endif /* CTLKFILEOVERRIDE_H_ */

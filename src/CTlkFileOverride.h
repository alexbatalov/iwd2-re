#ifndef CTLKFILEOVERRIDE_H_
#define CTLKFILEOVERRIDE_H_

#include "mfc.h"

#include "CStrRes.h"

class CTlkFileOverrideText : public CFile {
public:
};

class CTlkFileOverrideHeader : public CFile {
public:
    struct Entry {
        unsigned char dummy[1];
    };

    struct S1A {
        int field_0;
        int field_4;
        int field_8;
        int field_C;
        int field_10;
    };

    CTlkFileOverrideHeader();
    ~CTlkFileOverrideHeader();

    /* 0010 */ unsigned char field_10;
    /* 0012 */ Entry** m_ppEntries; // #guess
    /* 0016 */ int m_nEntryCount; // #guess
    /* 001A */ S1A field_1A;
};

class CTlkFileOverride {
public:
    // Constructor is inlined in `CTlkTable`.
    CTlkFileOverride() { }

    // Destructor is inlined in `CTlkTable`.
    ~CTlkFileOverride() { }

    BOOLEAN Fetch(DWORD strId, STR_RES& strRes);
    void Remove(DWORD strId);
    void CloseFiles();

    /* 0000 */ CString field_0;
    /* 0004 */ CString field_4;
    /* 0008 */ CTlkFileOverrideHeader m_header; // #guess
    /* 0036 */ CTlkFileOverrideText m_text; // #guess
};

#endif /* CTLKFILEOVERRIDE_H_ */

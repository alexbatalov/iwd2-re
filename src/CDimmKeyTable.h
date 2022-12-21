#ifndef CDIMMKEYTABLE_H_
#define CDIMMKEYTABLE_H_

#include "CResRef.h"
#include "ChDataTypes.h"

class CDimm;
class CRes;

// #guess
struct CDimmKeyTableEntry {
    CResRef resRef;
    CRes* pRes;
    int field_C;
    short field_10;
    short field_12;
    int field_14;
};

class CDimmKeyTable {
public:
    CDimmKeyTable()
    {
        m_nNewEntries = 0;
        m_pNewEntries = NULL;
        m_bInitialized = FALSE;
        m_pResFileNameEntries = NULL;
        m_nResFiles = 0;
        m_nEntries = 0;
        m_pEntries = NULL;
        field_1C = 0;
        field_20 = 0;
    }

    BOOL AddKey(CResRef cResRef, USHORT nResType, RESID nID);
    BOOL BuildNewTable(int a2);
    void DestroyTable(CDimm* dimm);
    BOOL ExtendTable();
    CDimmKeyTableEntry* FindKey(const CResRef& resRef, USHORT nResType, BOOL bWarningIfMissing);
    unsigned int Hash(const CResRef& a2, int a3);
    void RemoveNonUpdatedEntries();
    void RescanDirectoryNumberAndName(int nDirNumber, const CString& sDirName);

    /* 0000 */ int m_bInitialized; // #guess
    /* 0004 */ KEYFILE_RESFILENAME* m_pResFileNameEntries; // #guess
    /* 0008 */ UINT m_nResFiles;
    /* 000C */ int m_nEntries; // #guess
    /* 0010 */ CDimmKeyTableEntry* m_pEntries; // #guess
    /* 0014 */ int m_nNewEntries; // #guess
    /* 0018 */ CDimmKeyTableEntry* m_pNewEntries; // #guess
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
};

#endif /* CDIMMKEYTABLE_H_ */

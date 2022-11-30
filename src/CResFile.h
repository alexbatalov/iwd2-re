#ifndef CRESFILE_H_
#define CRESFILE_H_

#include "ChDataTypes.h"

class CResFile : public CObject {
public:
    CResFile();
    ~CResFile();

    BOOL AddCacheCount();
    BOOL CloseFile();
    DWORD GetFileSize(RESID resID);
    BOOL OpenFile();
    UINT ReadResource(RESID resID, LPVOID lpBuf, UINT nCount, UINT nOffset);
    void UnCache();

    /* 0004 */ int field_4;
    /* 0008 */ UINT m_nRefCount; // #guess
    /* 000C */ UINT m_nCacheCount; // #guess
    /* 0010 */ UINT m_nIndex; // #guess
    /* 0014 */ BIFF_HEADER* m_pHeader; // #guess
    /* 0018 */ BIFF_VARTABLEENTRY* m_pVarEntries; // #guess
    /* 001C */ BIFF_FIXEDTABLEENTRY* m_pFixedEntries; // #guess
    /* 0020 */ void* field_20;
    /* 0024 */ BOOL m_bOpen; // #guess
    /* 0028 */ CFile m_cFile; // #guess
    /* 0038 */ BOOLEAN field_38;
};

#endif /* CRESFILE_H_ */

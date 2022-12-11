#ifndef CRESCACHE_H_
#define CRESCACHE_H_

#include "mfc.h"

typedef BOOL(WINAPI GetDiskFreeSpaceExAFunc)(LPCSTR lpDirectoryName, PULARGE_INTEGER lpFreeBytesAvailableToCaller, PULARGE_INTEGER lpTotalNumberOfBytes, PULARGE_INTEGER lpTotalNumberOfFreeBytes);

class CResCache {
public:
    struct Entry {
        UINT nIndex;
        CTime cTime;
        DWORD nSize;
    };

    CResCache();
    ~CResCache();

    void AccessFileInCache(UINT nIndex);
    void AddFileToCache(UINT nIndex, const CTime& cTime, DWORD nSize);
    BOOL CopyFile(UINT nIndex, const CString& a3, const CString& a4, const CString& a5);
    void FlushCache(int a2);
    BOOL IsCacheSpaceAvailable();
    int GetUnusedSize();
    BOOL RefreshStatus(const CString& a2);

    static GetDiskFreeSpaceExAFunc* pfnGetDiskFreeSpaceExA;
    static CString DEFAULT_CACHE_DIRECTORY; // #guess

    /* 0000 */ int field_0;
    /* 0004 */ char workingDirectory[260]; // #guess
    /* 0108 */ CString field_108;
    /* 010C */ CString field_10C;
    /* 0110 */ int field_110;
    /* 0114 */ int field_114;
    /* 0118 */ int field_118;
    /* 011C */ int field_11C;
    /* 0120 */ int field_120;
    /* 0124 */ int field_124;
    /* 0128 */ CTypedPtrList<CPtrList, Entry*> field_128;
    /* 0144 */ CRITICAL_SECTION criticalSection; // #guess
};

#endif /* CRESCACHE_H_ */

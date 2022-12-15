#include "CResCache.h"

#include <direct.h>

#include "CChitin.h"
#include "CUtil.h"

// 0x8E7514
GetDiskFreeSpaceExAFunc* CResCache::pfnGetDiskFreeSpaceExA;

// 0x8FB928
CString CResCache::DEFAULT_CACHE_DIRECTORY("hd0:\\cache\\");

// #binary-identical
// 0x78BF50
CResCache::CResCache()
{
    getcwd(workingDirectory, sizeof(workingDirectory));
    field_108 = DEFAULT_CACHE_DIRECTORY;
    field_110 = 0;
    field_11C = 175000000;
    field_120 = 175000000;
    field_114 = 0;
    field_118 = 0;
    field_124 = 0;
    field_0 = 0;
    InitializeCriticalSection(&criticalSection);
}

// #binary-identical
// 0x78C020
CResCache::~CResCache()
{
    EnterCriticalSection(&criticalSection);

    POSITION pos = field_128.GetHeadPosition();
    while (pos != NULL) {
        POSITION curr = pos;
        Entry* pEntry = field_128.GetNext(pos);
        field_128.RemoveAt(curr);

        UINT nIndex = pEntry->nIndex;
        if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
            if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
                if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                    g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives &= ~0x200;
                }
            }
        }

        delete pEntry;
    }

    field_124 = 0;
    field_120 = field_11C;

    LeaveCriticalSection(&criticalSection);
    DeleteCriticalSection(&criticalSection);
}

// 0x78C130
void CResCache::AccessFileInCache(UINT nIndex)
{
    CString v1;
    CString v2;
    CString v3;
    CFile cFile;

    if (field_0) {
        v1 = field_108;
        if (g_pChitin->cDimm.FindDirectoryInDirectoryList(v1) == DIMM_NOT_IN_DIRECTORY_LIST) {
            if (!g_pChitin->cDimm.AddToDirectoryList(v1, FALSE)) {
                return;
            }
        }

        if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
            if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
                v2 = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileNameOffset;

                if (!g_pChitin->lAliases.ResolveFileName(v1 + v2, v3)) {
                    v3 = v1 + v2;
                }

                if (cFile.Open(v3, CFile::OpenFlags::modeRead, NULL)) {
                    cFile.Close();

                    CFileStatus cFileStatus;
                    if (!CFile::GetStatus(v3, cFileStatus)) {
                        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                        // __LINE__: 10722
                        UTIL_ASSERT(FALSE);
                    }

                    cFileStatus.m_mtime = CTime::GetCurrentTime();

                    // NOTE: There is unknown unwind stack changes around
                    // `SetStatus`, not sure how to replicate it.
                    CFile::SetStatus(v3, cFileStatus);

                    AddFileToCache(nIndex, cFileStatus.m_mtime, cFileStatus.m_size);
                }
            }
        }
    }
}

// #binary-identical
// 0x78C350
void CResCache::AddFileToCache(UINT nIndex, const CTime& cTime, DWORD nSize)
{
    BOOL existingEntryFound = FALSE;
    BOOL prevEntryFound = FALSE;
    POSITION existingEntryPos;
    POSITION previousEntryPos;

    EnterCriticalSection(&(criticalSection));

    POSITION pos = field_128.GetHeadPosition();
    while (pos != NULL) {
        if (prevEntryFound && existingEntryFound) {
            break;
        }

        POSITION curr = pos;
        Entry* pEntry = field_128.GetNext(pos);
        if (nIndex == pEntry->nIndex) {
            existingEntryFound = TRUE;
            existingEntryPos = pos;
        } else {
            if (!prevEntryFound) {
                if (pEntry->cTime < cTime) {
                    prevEntryFound = TRUE;
                    previousEntryPos = curr;
                }
            }
        }
    }

    Entry* pEntry;
    if (existingEntryFound == TRUE) {
        pEntry = field_128.GetAt(existingEntryPos);
        field_128.RemoveAt(existingEntryPos);
        pEntry->cTime = cTime;
        if (pEntry->nSize != nSize) {
            field_120 += pEntry->nSize - nSize;
        }
    } else {
        pEntry = new Entry;
        pEntry->nIndex = nIndex;
        pEntry->cTime = cTime;
        pEntry->nSize = nSize;

        field_124 += 1;
        field_120 -= nSize;
    }

    if (field_120 >= field_11C) {
        field_120 = field_11C;
    }

    if (!prevEntryFound) {
        field_128.AddTail(pEntry);
    } else {
        field_128.InsertBefore(previousEntryPos, pEntry);
    }

    if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
        if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives |= 0x200;
            }
        }
    }

    LeaveCriticalSection(&(criticalSection));
}

// 0x78C4F0
BOOL CResCache::CopyFile(UINT nIndex, const CString& a3, const CString& a4, const CString& a5)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x78CAC0
BOOL CResCache::DeleteFileFromCache(UINT nIndex)
{
    // TODO: Incomplete.

    return FALSE;
}

// #binary-identical
// 0x78CD90
void CResCache::FlushCache(int a2)
{
    _chdir(workingDirectory);

    int v1 = a2;
    if (v1 <= 0) {
        v1 = field_11C;
    }

    EnterCriticalSection(&criticalSection);

    POSITION pos = field_128.GetTailPosition();

    EnterCriticalSection(&(g_pChitin->field_35C));

    int nUnusedSize = GetUnusedSize();

    if (!g_pChitin->cNetwork.field_6E0 && v1 <= 10000000) {
        while (pos != NULL && nUnusedSize < v1) {
            POSITION curr = pos;
            Entry* pEntry = field_128.GetPrev(pos);
            if (pEntry->nSize <= 10000000) {
                if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                    field_120 += pEntry->nSize;
                    field_124 -= 1;

                    nUnusedSize = GetUnusedSize();

                    field_128.RemoveAt(curr);
                    delete pEntry;
                }
            }
        }
    }

    if (nUnusedSize < v1) {
        POSITION pos = field_128.GetTailPosition();
        while (pos != NULL) {
            if (nUnusedSize >= v1) {
                break;
            }

            POSITION curr = pos;
            Entry* pEntry = field_128.GetPrev(pos);
            if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                field_120 += pEntry->nSize;
                field_124 -= 1;

                nUnusedSize = GetUnusedSize();

                field_128.RemoveAt(curr);
                delete pEntry;
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_35C));

    if (field_120 >= field_11C) {
        field_120 = field_11C;
    }

    LeaveCriticalSection(&criticalSection);
}

// #binary-identical
// 0x78CF40
BOOL CResCache::IsCacheSpaceAvailable()
{
    return GetUnusedSize() == field_120;
}

// #binary-identical
// 0x78CF60
int CResCache::GetUnusedSize()
{
    int v1;
    DWORD dwSectorsPerCluster;
    DWORD dwBytesPerSector;
    DWORD dwNumberOfFreeClusters;
    DWORD dwTotalNumberOfClusters;
    if (GetDiskFreeSpaceA(NULL, &dwSectorsPerCluster, &dwBytesPerSector, &dwNumberOfFreeClusters, &dwTotalNumberOfClusters) && dwNumberOfFreeClusters != 0) {
        if (static_cast<int>(dwSectorsPerCluster * (dwNumberOfFreeClusters / 128) * (dwBytesPerSector / 8)) >= 0x200000) {
            v1 = INT_MAX;
        } else {
            v1 = dwNumberOfFreeClusters * dwBytesPerSector * dwSectorsPerCluster - 10000000;
        }

        if (field_120 < v1) {
            v1 = field_120;
        }

        return v1;
    } else {
        HMODULE hModule = LoadLibraryA("kernel32.dll");
        if (hModule == NULL) {
            return field_120;
        }

        BOOL bHaveGetDiskFreeSpaceExA = GetProcAddress(hModule, "GetDiskFreeSpaceExA") != NULL;
        pfnGetDiskFreeSpaceExA = reinterpret_cast<GetDiskFreeSpaceExAFunc*>(GetProcAddress(hModule, "GetDiskFreeSpaceExA"));

        if (bHaveGetDiskFreeSpaceExA) {
            ULARGE_INTEGER nFreeBytesAvailable;
            ULARGE_INTEGER nTotalNumberOfBytes;
            if (pfnGetDiskFreeSpaceExA(NULL, &nFreeBytesAvailable, &nTotalNumberOfBytes, NULL)) {
                FreeLibrary(hModule);

                if (nFreeBytesAvailable.HighPart == 0 && nFreeBytesAvailable.LowPart - 10000000 <= INT_MAX) {
                    v1 = static_cast<int>(nFreeBytesAvailable.LowPart - 10000000);
                    if (field_120 < v1) {
                        v1 = field_120;
                    }
                    return v1;
                } else {
                    v1 = field_120;
                    if (v1 >= INT_MAX) {
                        v1 = INT_MAX;
                    }
                    return v1;
                }
            }
        }

        FreeLibrary(hModule);
        return field_120;
    }
}

// 0x78D090
BOOL CResCache::RefreshStatus(const CString& a2)
{
    CString v1;
    CString v2;
    CFile cFile;
    CString v3;

    field_11C = GetPrivateProfileIntA("Config", "CacheSize", 175, g_pChitin->GetConfigFileName());
    if (field_11C < 125 || field_11C > 2147) {
        field_11C = 175;
    }

    field_11C *= 1000000;
    field_120 = field_11C;

    if (a2.Compare("") != 0) {
        field_108 = a2;
    }

    v1 = field_108;

    if (g_pChitin->cDimm.FindDirectoryInDirectoryList(v1) == DIMM_NOT_IN_DIRECTORY_LIST) {
        if (!g_pChitin->cDimm.AddToDirectoryList(v1, FALSE)) {
            return FALSE;
        }
    }

    EnterCriticalSection(&criticalSection);

    POSITION pos = field_128.GetHeadPosition();
    while (pos != NULL) {
        POSITION curr = pos;
        Entry* pEntry = field_128.GetNext(pos);
        field_128.RemoveAt(curr);

        unsigned int nIndex = pEntry->nIndex;
        if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
            if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
                if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                    g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives &= ~0x200;
                }
            }
        }

        delete pEntry;
    }

    field_120 = field_11C;
    field_124 = 0;
    LeaveCriticalSection(&criticalSection);

    for (unsigned int k = 0; k < g_pChitin->cDimm.m_nResFiles; k++) {
        if (!g_pChitin->cDimm.m_cKeyTable.m_bInitialized && k >= g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
    return FALSE;
        }

        v2 = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[k].nFileNameOffset;

        if (g_pChitin->lAliases.ResolveFileName(v1 + v2, v3) == FALSE) {
            v3 = v1 + v2;
        }

        if (cFile.Open(v3, CFile::OpenFlags::modeRead, NULL)) {
            cFile.Close();

            CFileStatus cFileStatus;
            if (!CFile::GetStatus(v3, cFileStatus)) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                // __LINE__: 11872
                UTIL_ASSERT(FALSE);
            }

            AddFileToCache(k, cFileStatus.m_mtime, cFileStatus.m_size);
        } else {
            if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
                if (k < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
                    if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                        g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[k].bDrives &= ~0x200;
                    }
                }
            }
        }
    }

    field_0 = 1;

    return TRUE;
}

// 0x78D470
BOOL CResCache::ValidateFile(UINT nResFileID, LONG a3)
{
    CString v1;
    CString v2;
    CFile cFile;
    CString v3;

    UINT nIndex = nResFileID >> 20;

    v1 = field_108;

    if (g_pChitin->cDimm.FindDirectoryInDirectoryList(v1) != DIMM_NOT_IN_DIRECTORY_LIST) {
        if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized && nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            v2 = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileNameOffset;

            if (g_pChitin->lAliases.ResolveFileName(v1 + v2, v3) == FALSE) {
                v3 = v1 + v2;
            }

            CFileStatus cFileStatus;
            if (CFile::GetStatus(v3, cFileStatus)) {
                if (static_cast<DWORD>(cFileStatus.m_size) != g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileSize) {
                    EnterCriticalSection(&criticalSection);

                    POSITION pos = field_128.GetTailPosition();
                    while (pos != NULL) {
                        POSITION curr = pos;
                        Entry* pEntry = field_128.GetPrev(pos);
                        if (pEntry->nIndex == nIndex) {
                            if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                                field_120 += pEntry->nSize;
                                field_124 -= 1;
                                field_128.RemoveAt(curr);
                                delete pEntry;
                            }
                        }
                    }

                    LeaveCriticalSection(&criticalSection);
                }
            }

            return TRUE;
        }
    }

    return FALSE;
}

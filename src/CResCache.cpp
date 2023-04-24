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
    m_sDirName = DEFAULT_CACHE_DIRECTORY;
    field_110 = 0;
    m_nCacheSize = 175000000;
    m_nAvailableCacheSize = 175000000;
    field_114 = 0;
    field_118 = 0;
    m_nEntries = 0;
    m_bInitialized = FALSE;
    InitializeCriticalSection(&m_criticalSection);
}

// #binary-identical
// 0x78C020
CResCache::~CResCache()
{
    EnterCriticalSection(&m_criticalSection);

    POSITION pos = m_lEntries.GetHeadPosition();
    while (pos != NULL) {
        POSITION curr = pos;
        Entry* pEntry = m_lEntries.GetNext(pos);
        m_lEntries.RemoveAt(curr);

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

    m_nEntries = 0;
    m_nAvailableCacheSize = m_nCacheSize;

    LeaveCriticalSection(&m_criticalSection);
    DeleteCriticalSection(&m_criticalSection);
}

// 0x78C130
void CResCache::AccessFileInCache(UINT nIndex)
{
    CString v1;
    CString v2;
    CString v3;
    CFile cFile;

    if (m_bInitialized) {
        v1 = m_sDirName;
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

    EnterCriticalSection(&(m_criticalSection));

    POSITION pos = m_lEntries.GetHeadPosition();
    while (pos != NULL) {
        if (prevEntryFound && existingEntryFound) {
            break;
        }

        POSITION curr = pos;
        Entry* pEntry = m_lEntries.GetNext(pos);
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
        pEntry = m_lEntries.GetAt(existingEntryPos);
        m_lEntries.RemoveAt(existingEntryPos);
        pEntry->cTime = cTime;
        if (pEntry->nSize != nSize) {
            m_nAvailableCacheSize += pEntry->nSize - nSize;
        }
    } else {
        pEntry = new Entry;
        pEntry->nIndex = nIndex;
        pEntry->cTime = cTime;
        pEntry->nSize = nSize;

        m_nEntries += 1;
        m_nAvailableCacheSize -= nSize;
    }

    if (m_nAvailableCacheSize >= m_nCacheSize) {
        m_nAvailableCacheSize = m_nCacheSize;
    }

    if (!prevEntryFound) {
        m_lEntries.AddTail(pEntry);
    } else {
        m_lEntries.InsertBefore(previousEntryPos, pEntry);
    }

    if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
        if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives |= 0x200;
            }
        }
    }

    LeaveCriticalSection(&(m_criticalSection));
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
        v1 = m_nCacheSize;
    }

    EnterCriticalSection(&m_criticalSection);

    POSITION pos = m_lEntries.GetTailPosition();

    EnterCriticalSection(&(g_pChitin->field_35C));

    int nUnusedSize = GetUnusedSize();

    if (!g_pChitin->cNetwork.m_bConnectionEstablished && v1 <= 10000000) {
        while (pos != NULL && nUnusedSize < v1) {
            POSITION curr = pos;
            Entry* pEntry = m_lEntries.GetPrev(pos);
            if (pEntry->nSize <= 10000000) {
                if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                    m_nAvailableCacheSize += pEntry->nSize;
                    m_nEntries -= 1;

                    nUnusedSize = GetUnusedSize();

                    m_lEntries.RemoveAt(curr);
                    delete pEntry;
                }
            }
        }
    }

    if (nUnusedSize < v1) {
        POSITION pos = m_lEntries.GetTailPosition();
        while (pos != NULL) {
            if (nUnusedSize >= v1) {
                break;
            }

            POSITION curr = pos;
            Entry* pEntry = m_lEntries.GetPrev(pos);
            if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                m_nAvailableCacheSize += pEntry->nSize;
                m_nEntries -= 1;

                nUnusedSize = GetUnusedSize();

                m_lEntries.RemoveAt(curr);
                delete pEntry;
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_35C));

    if (m_nAvailableCacheSize >= m_nCacheSize) {
        m_nAvailableCacheSize = m_nCacheSize;
    }

    LeaveCriticalSection(&m_criticalSection);
}

// #binary-identical
// 0x78CF40
BOOL CResCache::IsCacheSpaceAvailable()
{
    return GetUnusedSize() == m_nAvailableCacheSize;
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

        if (m_nAvailableCacheSize < v1) {
            v1 = m_nAvailableCacheSize;
        }

        return v1;
    } else {
        HMODULE hModule = LoadLibraryA("kernel32.dll");
        if (hModule == NULL) {
            return m_nAvailableCacheSize;
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
                    if (m_nAvailableCacheSize < v1) {
                        v1 = m_nAvailableCacheSize;
                    }
                    return v1;
                } else {
                    v1 = m_nAvailableCacheSize;
                    if (v1 >= INT_MAX) {
                        v1 = INT_MAX;
                    }
                    return v1;
                }
            }
        }

        FreeLibrary(hModule);
        return m_nAvailableCacheSize;
    }
}

// 0x78D090
BOOL CResCache::RefreshStatus(const CString& sDirName)
{
    CString v1;
    CString v2;
    CFile cFile;
    CString v3;

    m_nCacheSize = GetPrivateProfileIntA("Config", "CacheSize", 175, g_pChitin->GetIniFileName());
    if (m_nCacheSize < 125 || m_nCacheSize > 2147) {
        m_nCacheSize = 175;
    }

    m_nCacheSize *= 1000000;
    m_nAvailableCacheSize = m_nCacheSize;

    if (sDirName.Compare("") != 0) {
        m_sDirName = sDirName;
    }

    v1 = m_sDirName;

    if (g_pChitin->cDimm.FindDirectoryInDirectoryList(v1) == DIMM_NOT_IN_DIRECTORY_LIST) {
        if (!g_pChitin->cDimm.AddToDirectoryList(v1, FALSE)) {
            return FALSE;
        }
    }

    EnterCriticalSection(&m_criticalSection);

    POSITION pos = m_lEntries.GetHeadPosition();
    while (pos != NULL) {
        POSITION curr = pos;
        Entry* pEntry = m_lEntries.GetNext(pos);
        m_lEntries.RemoveAt(curr);

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

    m_nAvailableCacheSize = m_nCacheSize;
    m_nEntries = 0;
    LeaveCriticalSection(&m_criticalSection);

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

    m_bInitialized = TRUE;

    return TRUE;
}

// 0x78D470
BOOL CResCache::ValidateFile(UINT nResFileID, LONG a3)
{
    CString sDirName;
    CString sFileName;
    CFile cFile;
    CString sResolvedFileName;

    UINT nIndex = nResFileID >> 20;

    sDirName = m_sDirName;

    if (g_pChitin->cDimm.FindDirectoryInDirectoryList(sDirName) != DIMM_NOT_IN_DIRECTORY_LIST) {
        if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized && nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            sFileName = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileNameOffset;

            if (g_pChitin->lAliases.ResolveFileName(sDirName + sFileName, sResolvedFileName) == FALSE) {
                sResolvedFileName = sDirName + sFileName;
            }

            CFileStatus cFileStatus;
            if (CFile::GetStatus(sResolvedFileName, cFileStatus)) {
                if (static_cast<DWORD>(cFileStatus.m_size) != g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileSize) {
                    EnterCriticalSection(&m_criticalSection);

                    POSITION pos = m_lEntries.GetTailPosition();
                    while (pos != NULL) {
                        POSITION curr = pos;
                        Entry* pEntry = m_lEntries.GetPrev(pos);
                        if (pEntry->nIndex == nIndex) {
                            if (DeleteFileFromCache(pEntry->nIndex) == TRUE) {
                                m_nAvailableCacheSize += pEntry->nSize;
                                m_nEntries -= 1;
                                m_lEntries.RemoveAt(curr);
                                delete pEntry;
                            }
                        }
                    }

                    LeaveCriticalSection(&m_criticalSection);
                }
            }

            return TRUE;
        }
    }

    return FALSE;
}

#include "CResCache.h"

#include <direct.h>

#include "CChitin.h"
#include "CUtil.h"

// 0x8E7514
GetDiskFreeSpaceExAFunc* CResCache::pfnGetDiskFreeSpaceExA;

// 0x8FB92C
int CResCache::dword_8FB92C;

// 0x8FB90C
CString CResCache::stru_8FB90C[7];

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

                    // NOTE: `m_size` is `LONG` in VC6, but `ULONGLONG` in
                    // more modern versions.
                    AddFileToCache(nIndex, cFileStatus.m_mtime, static_cast<DWORD>(cFileStatus.m_size));
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
            existingEntryPos = curr;
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
BOOL CResCache::CopyFile(UINT nIndex, const CString& sName, const CString& sSrcFileName, const CString& sDstFileName)
{
    CFile input;
    CFile output;
    BOOL bCompressed = FALSE;

    if (!input.Open(sSrcFileName, CFile::OpenFlags::modeRead | CFile::OpenFlags::shareDenyWrite | CFile::OpenFlags::typeBinary, NULL)) {
        return FALSE;
    }

    char header[12];
    if (input.Read(header, sizeof(header)) != sizeof(header)) {
        input.Close();
        return FALSE;
    }

    INT nSize;
    INT nTotalBytesToRead;
    if (_strnicmp(header, "BIFCV1.0", 8) == 0) {
        nSize = *(reinterpret_cast<INT*>(header + 8));
        bCompressed = TRUE;
        nTotalBytesToRead = nSize;
    } else {
        nTotalBytesToRead = static_cast<INT>(input.GetLength());
        input.Seek(CFile::SeekPosition::begin, 0);
        nSize = nTotalBytesToRead;
    }

    INT nTotalBytesRead = 0;

    field_118 = 0;

    if (GetUnusedSize() < nSize) {
        FlushCache(nSize);
        if (GetUnusedSize() < nSize) {
            int v1 = nSize - GetUnusedSize();
            m_nCacheSize += v1 + m_nAvailableCacheSize;
            m_nAvailableCacheSize += v1;
            if (GetUnusedSize() < nSize) {
                m_nCacheSize -= v1;
                m_nAvailableCacheSize -= v1;
                input.Close();
                return FALSE;
            }
        }
    }

    DWORD nCompressedBufferSize = 0;
    BYTE* pCompressedBuffer = NULL;

    DWORD nBufferSize = 1024;
    BYTE* pBuffer = new BYTE[nBufferSize];
    if (pBuffer == NULL) {
        input.Close();
        return FALSE;
    }

    if (!output.Open(sDstFileName, CFile::OpenFlags::modeWrite | CFile::OpenFlags::modeCreate | CFile::OpenFlags::typeBinary, NULL)) {
        delete pBuffer;
        input.Close();
        return FALSE;
    }

    // FIXME: Unused.
    GetTickCount();

    DWORD nLastDisplayRefreshTime = GetTickCount();
    DWORD nLastBroadcastTime = GetTickCount();

    field_114 = 1;

    if (bCompressed) {
        nTotalBytesToRead = static_cast<INT>(input.GetLength()) - sizeof(header);
    }

    INT nBytesRead;
    while (nTotalBytesRead < nTotalBytesToRead) {
        if (bCompressed) {
            DWORD chunkHeader[2];
            if (input.Read(chunkHeader, sizeof(chunkHeader)) == sizeof(chunkHeader)) {
                nTotalBytesRead += sizeof(chunkHeader);

                DWORD nUncompressedChunkSize = chunkHeader[0];
                DWORD nCompressedChunkSize = chunkHeader[1];

                if (nBufferSize < nUncompressedChunkSize) {
                    delete pBuffer;

                    nBufferSize = nUncompressedChunkSize;
                    pBuffer = new BYTE[nBufferSize];
                    if (pBuffer == NULL) {
                        if (pCompressedBuffer != NULL) {
                            delete pCompressedBuffer;
                        }
                        return FALSE;
                    }
                }

                if (nCompressedBufferSize < nCompressedChunkSize) {
                    if (pCompressedBuffer != NULL) {
                        delete pCompressedBuffer;
                    }

                    nCompressedBufferSize = max(nCompressedChunkSize, 1024);
                    pCompressedBuffer = new BYTE[nCompressedBufferSize];
                    if (pBuffer == NULL) {
                        delete pBuffer;
                        return FALSE;
                    }
                }

                nBytesRead = input.Read(pCompressedBuffer, nCompressedChunkSize);
                if (nBytesRead != nCompressedChunkSize) {
                    field_118 = 1;

                    delete pCompressedBuffer;
                    delete pBuffer;

                    return FALSE;
                }

                int err = CUtil::Uncompress(pBuffer, &nUncompressedChunkSize, pCompressedBuffer, nCompressedChunkSize);

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                // __LINE__: 11308
                UTIL_ASSERT(err == 0);

                output.Write(pBuffer, nUncompressedChunkSize);
            } else {
                field_118 = 1;
            }
        } else {
            nBytesRead = input.Read(pBuffer, nBufferSize);
            output.Write(pBuffer, nBytesRead);
        }

        if (field_118 == 1) {
            nTotalBytesRead = nTotalBytesToRead;
            g_pChitin->cProgressBar.m_nActionProgress = nTotalBytesRead;
        } else {
            nTotalBytesRead += nBytesRead;
            g_pChitin->cProgressBar.m_nActionProgress += nBytesRead;
        }

        if (GetTickCount() - nLastDisplayRefreshTime) {
            g_pChitin->m_bDisplayStale = TRUE;
            nLastDisplayRefreshTime = GetTickCount();
            SleepEx(10, 0);
        }

        if (GetTickCount() - nLastBroadcastTime >= 2000) {
            nLastBroadcastTime = GetTickCount();
            g_pChitin->BroadcastMultiplayerProgressBarInfo();
        }
    }

    field_114 = 0;

    input.Close();
    output.Close();

    if (pCompressedBuffer != NULL) {
        delete pCompressedBuffer;
    }

    delete pBuffer;

    if (field_118 == 1) {
        CFile::Remove(sDstFileName);
        return FALSE;
    }

    AddFileToCache(nIndex, CTime::GetTickCount(), nSize);

    return TRUE;
}

// 0x78CAC0
BOOL CResCache::DeleteFileFromCache(UINT nIndex)
{
    CString sDirName;
    CString sFileName;
    CString sResolvedFileName;
    CFile file;

    if (!m_bInitialized) {
        return FALSE;
    }

    sDirName = m_sDirName;
    if (g_pChitin->cDimm.FindDirectoryInDirectoryList(sDirName) == DIMM_NOT_IN_DIRECTORY_LIST) {
        if (!g_pChitin->cDimm.AddToDirectoryList(sDirName, FALSE)) {
            return FALSE;
        }
    }

    if (!(g_pChitin->cDimm.m_cKeyTable.m_bInitialized && nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles)) {
        return FALSE;
    }

    sFileName = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].nFileNameOffset;

    CString sBaseName = sFileName.Mid(sFileName.ReverseFind('\\') + 1);
    sBaseName.SetAt(sBaseName.Find('.'), '\0');

    for (int index = 0; index < dword_8FB92C; index++) {
        if (stru_8FB90C[index] == sBaseName) {
            return FALSE;
        }
    }

    if (!g_pChitin->lAliases.ResolveFileName(sDirName + sFileName, sResolvedFileName)) {
        sResolvedFileName = sDirName + sFileName;
    }

    if (!file.Open(sResolvedFileName, CFile::OpenFlags::shareDenyWrite, NULL)) {
        return FALSE;
    }

    file.Close();

    CFile::Remove(sResolvedFileName);

    if (g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
        if (nIndex < g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            if (g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries != NULL) {
                g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives &= ~0x200;
            }
        }
    }

    return TRUE;
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

    if (!g_pChitin->cNetwork.GetSessionOpen() && v1 <= 10000000) {
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

            // NOTE: `m_size` is `LONG` in VC6, but `ULONGLONG` in more modern
            // versions.
            AddFileToCache(k, cFileStatus.m_mtime, static_cast<DWORD>(cFileStatus.m_size));
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

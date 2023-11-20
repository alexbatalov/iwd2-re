#include "CDimm.h"

#include <direct.h>

#include "CChitin.h"
#include "CRes.h"
#include "CResFile.h"
#include "CUtil.h"

// #binary-identical
// 0x781E60
CDimm::CDimm()
{
    field_2A4 = FALSE;
    field_295 = FALSE;
    field_296 = FALSE;
    field_297 = FALSE;

    MEMORYSTATUS memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUS);

    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
    field_DA = 0;
    field_CE = NULL;
    field_274 = NULL;
    field_270 = NULL;
    field_D2 = 0;
    field_E6 = 0;

    GlobalMemoryStatus(&memoryStatus);

    field_EA = 1;
    field_2A0 = 0;
    dwTotalPhysicalMemory = memoryStatus.dwTotalPhys;

    field_D6 = 12000000;
    field_29C = 0;
    m_ppResFiles = NULL;
    m_nResFiles = 0;
    m_bTemporaryKeyAdd = FALSE;
    m_bTemporaryDirAdd = FALSE;
    m_bCDSwitchActivated = FALSE;
}

// 0x782020
CDimm::~CDimm()
{
    m_lDirectories.RemoveAll();

    // TODO: Likely `CDimmKeyTable` destructor.
    if (m_cKeyTable.m_pResFileNameEntries != NULL) {
        free(m_cKeyTable.m_pResFileNameEntries);
        m_cKeyTable.m_pResFileNameEntries = NULL;
    }
}

// 0x782240
BOOL CDimm::AddToDirectoryList(const CString& sDirName, BOOL bRescan)
{
    CString sResolvedDirName;
    CString sExistingDirName;

    if (!g_pChitin->lAliases.ResolveFileName(sDirName, sResolvedDirName)) {
        sResolvedDirName = sDirName;
    }

    int index = 0;
    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL) {
        sExistingDirName = m_lDirectories.GetAt(pos);
        if (sResolvedDirName.CompareNoCase(sExistingDirName) == 0) {
            // NOTE: Not sure why it returns false.
            return FALSE;
        }

        index++;
        m_lDirectories.GetNext(pos);
    }

    if (index < 64) {
        m_lDirectories.AddTail(sResolvedDirName);
        if (m_cKeyTable.m_bInitialized) {
            if (bRescan) {
                CString v3;
                // NOTE: Strange code, unclear why `GetElementInDirectoryList`
                // is called on global obtained via `CChitin`, while subsequent
                // call to `RescanDirectoryNumberAndName` is called on `this`.
                if (g_pChitin->cDimm.GetElementInDirectoryList(index, v3) == TRUE) {
                    m_cKeyTable.RescanDirectoryNumberAndName(index, v3);
                }
            }
        }
        return TRUE;
    }

    return FALSE;
}

// #design-flaw: Accepting `cResRef` object produces unncessary copies at call sites.
// 0x7823C0
BOOL CDimm::AddTemporaryKey(const CString& sDirName, CResRef cResRef, USHORT nType)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 236
    UTIL_ASSERT(m_bTemporaryKeyAdd == FALSE);

    if (FindDirectoryInDirectoryList(sDirName) == DIMM_NOT_IN_DIRECTORY_LIST) {
        m_bTemporaryDirAdd = TRUE;
        AddToDirectoryList(sDirName, FALSE);
    } else {
        m_bTemporaryDirAdd = FALSE;
    }

    int dirValue = FindDirectoryInDirectoryList(sDirName);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 249
    UTIL_ASSERT(dirValue != DIMM_NOT_IN_DIRECTORY_LIST);

    m_cKeyTable.AddKey(cResRef, nType, ~dirValue << 20);

    m_bTemporaryKeyAdd = TRUE;

    return TRUE;
}

// #design-flaw: Accepting `cResRef` object produces unncessary copies at call sites.
// 0x782470
BOOL CDimm::RemoveTemporaryKey(const CString& sDirName, CResRef cResRef, USHORT nType)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 285
    UTIL_ASSERT(m_bTemporaryKeyAdd == TRUE);

    CDimmKeyTableEntry* pKey = m_cKeyTable.FindKey(cResRef, nType, 1);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 9884
    UTIL_ASSERT(pKey != NULL);

    // NOTE: Huge distance in line numbers implies inlining.

    pKey->resRef = "";
    pKey->pRes = NULL;
    pKey->nID = -1;
    pKey->field_10 = 0;
    pKey->nResType = -1;
    pKey->bUpdated = 0;
    if (m_bTemporaryDirAdd == TRUE) {
        m_bTemporaryDirAdd = FALSE;
        RemoveFromDirectoryList(sDirName, 0);
    }

    m_bTemporaryKeyAdd = FALSE;

    return TRUE;
}

// 0x782550
int CDimm::CancelRequest(CRes* pRes)
{
    if (pRes->field_44 > 0) {
        pRes->field_44--;
        if (pRes->field_44 == 0 && pRes->field_40 == 0) {
            EnterCriticalSection(&(g_pChitin->field_2FC));

            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x08) == 0) {
                if (pRes->m_pCurrentList != NULL) {
                    pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                    pRes->m_pCurrentList = NULL;
                    pRes->m_pCurrentListPos = NULL;
                }

                if ((pRes->dwFlags & (CRes::Flags::RES_FLAG_0x04 | CRes::Flags::RES_FLAG_0x10)) != 0) {
                    pRes->m_pCurrentList = &m_lFreed;
                    pRes->m_pCurrentListPos = m_lFreed.AddTail(pRes);
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x08;
                }
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));
        }

        if ((pRes->m_nID >> 20) < m_nResFiles && (pRes->m_nID & 0xFFF00000) < 0xFC000000) {
            CResFile* pResFile = m_ppResFiles[pRes->m_nID >> 20];

            EnterCriticalSection(&(g_pChitin->field_35C));

            if (pResFile->m_nRefCount > 1) {
                pResFile->m_nRefCount--;
            } else {
                pResFile->CloseFile();
                pResFile->m_nRefCount = 0;
            }

            LeaveCriticalSection(&(g_pChitin->field_35C));
        }
    } else {
        pRes->field_44 = 0;
    }

    return 0;
}

// 0x782650
BOOL CDimm::CDScan(USHORT a2)
{
    char szCurrentDirectory[260];
    char buffer[8];
    CString sResolvedFilePath;

    if (_getcwd(szCurrentDirectory, sizeof(szCurrentDirectory)) == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
        // __LINE__: 439
        UTIL_ASSERT(FALSE);
    }

    for (int v1 = 0; v1 < 8; v1++) {
        USHORT v2;
        switch (v1) {
        case 0:
            v2 = 2;
            break;
        case 1:
            v2 = 4;
            break;
        case 2:
            v2 = 8;
            break;
        case 3:
            v2 = 16;
            break;
        default:
            v2 = 0;
            break;
        }

        if ((a2 & v2) != 0) {
            sprintf(buffer, "cd%01d:\\", v1);
            if (g_pChitin->lAliases.ResolveFileName(CString(buffer), sResolvedFilePath) == TRUE) {
                if (_chdir(sResolvedFilePath) == 0) {
                    USHORT v3;
                    switch (v1) {
                    case 0:
                        v3 = 2;
                        break;
                    case 1:
                        v3 = 4;
                        break;
                    case 2:
                        v3 = 8;
                        break;
                    case 3:
                        v3 = 16;
                        break;
                    default:
                        v3 = 0;
                        break;
                    }

                    field_EA |= v3;
                } else {
                    USHORT v4;
                    switch (v1) {
                    case 0:
                        v4 = 2;
                        break;
                    case 1:
                        v4 = 4;
                        break;
                    case 2:
                        v4 = 8;
                        break;
                    case 3:
                        v4 = 16;
                        break;
                    default:
                        v4 = 0;
                        break;
                    }

                    field_EA &= ~v4;
                }

                // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                // __LINE__: 463
                UTIL_ASSERT(_chdir(szCurrentDirectory) == 0);
            } else {
                USHORT v5;
                switch (v1) {
                case 0:
                    v5 = 2;
                    break;
                case 1:
                    v5 = 4;
                    break;
                case 2:
                    v5 = 8;
                    break;
                case 3:
                    v5 = 16;
                    break;
                default:
                    v5 = 0;
                    break;
                }

                field_EA &= ~v5;
            }
        }
    }

    return TRUE;
}

// 0x7828D0
WORD CDimm::CDSwitch(WORD drive, CString& sDrive, BOOLEAN a3)
{
    // TODO: Incomplete.

    return 0;
}

// 0x783920
BOOL CDimm::CreateKeyTable()
{
    CFile keyFile;
    CString v1;

    if (!keyFile.Open(g_pChitin->GetKeyFileName(), CFile::OpenFlags::modeRead, NULL)) {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    KEYFILE_HEADER keyFileHeader;
    keyFile.Read(&keyFileHeader, sizeof(keyFileHeader));

    if (memcmp(&(keyFileHeader.nFileType), "KEY ", 4) != 0) {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    if (memcmp(&(keyFileHeader.nFileVersion), "V1  ", 4) != 0) {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    if (keyFileHeader.nResFiles == 0 && keyFileHeader.nKeys == 0) {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    if (m_cKeyTable.BuildNewTable(1024 - static_cast<int>(static_cast<double>(keyFileHeader.nKeys) / -0.85)) != 1) {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    size_t fileTableSize = keyFileHeader.nOffsetToKeyTable - keyFileHeader.nOffsetToFileTable;
    m_cKeyTable.m_nEntries = m_cKeyTable.m_nNewEntries;
    m_cKeyTable.m_pEntries = m_cKeyTable.m_pNewEntries;

    m_cKeyTable.m_pResFileNameEntries = reinterpret_cast<KEYFILE_RESFILENAME*>(malloc(fileTableSize));
    if (m_cKeyTable.m_pResFileNameEntries == NULL) {
        m_cKeyTable.m_bInitialized = FALSE;
        m_cKeyTable.m_nResFiles = 0;
        m_cKeyTable.DestroyTable(this);
        return FALSE;
    }

    m_cKeyTable.m_nResFiles = keyFileHeader.nResFiles;

    keyFile.Seek(keyFileHeader.nOffsetToFileTable, CFile::SeekPosition::begin);
    keyFile.Read(m_cKeyTable.m_pResFileNameEntries, fileTableSize);

    for (UINT k = 0; k < m_cKeyTable.m_nResFiles; k++) {
        m_cKeyTable.m_pResFileNameEntries[k].nFileNameOffset -= keyFileHeader.nOffsetToFileTable;
    }

    m_nResFiles = m_cKeyTable.m_nResFiles;
    m_ppResFiles = reinterpret_cast<CResFile**>(malloc(sizeof(m_ppResFiles) * m_cKeyTable.m_nResFiles));
    if (m_ppResFiles == NULL) {
        free(m_cKeyTable.m_pResFileNameEntries);
        m_nResFiles = 0;
        m_cKeyTable.m_nResFiles = 0;
        m_cKeyTable.m_bInitialized = FALSE;
        m_cKeyTable.DestroyTable(this);
        return FALSE;
    }

    for (UINT n = 0; n < m_nResFiles; n++) {
        m_ppResFiles[n] = new CResFile();
        m_ppResFiles[n]->m_nIndex = n;
    }

    keyFile.Seek(keyFileHeader.nOffsetToKeyTable, CFile::SeekPosition::begin);

    for (DWORD m = 0; m < keyFileHeader.nKeys; m++) {
        KEYFILE_KEYENTRY keyEntry;
        keyFile.Read(&keyEntry, sizeof(keyEntry));
        m_cKeyTable.AddKey(CResRef(keyEntry.resRef), keyEntry.nType, keyEntry.nID);
    }

    for (int nDirIndex = 0; GetElementInDirectoryList(nDirIndex, v1) == TRUE; nDirIndex++) {
        CString sDirName;
        if (g_pChitin->cDimm.GetElementInDirectoryList(nDirIndex, sDirName) == TRUE) {
            m_cKeyTable.RescanDirectoryNumberAndName(nDirIndex, sDirName);
        }
    }

    m_cKeyTable.m_bInitialized = TRUE;

    keyFile.Close();

    cResCache.RefreshStatus(CString(""));

    return TRUE;
}

// 0x783D00
void* CDimm::Demand(CRes* pRes)
{
    void* pData = InternalDemand(pRes);

    int v1 = 5;
    while (field_CE == pRes) {
        Release(pRes);
        Dump(pRes, 1, 0);
        pData = InternalDemand(pRes);

        if (field_CE != pRes) {
            break;
        }

        if (--v1 <= 0) {
            return NULL;
        }
    }

    if (pData != NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
        // __LINE__: 1255
        UTIL_ASSERT(pRes != NULL);

        if (pRes->nSize >= 4) {
            BYTE* pBytes = reinterpret_cast<BYTE*>(pData) + pRes->nSize - 4;

            int v2 = 5;
            while (pBytes[0] == 'Y' && pBytes[1] == 'u' && pBytes[2] == 'k' && pBytes[3] == 'i') {
                Release(pRes);
                Dump(pRes, 1, 0);
                pData = InternalDemand(pRes);

                pBytes = reinterpret_cast<BYTE*>(pData) + pRes->nSize - 4;
                if (pBytes[0] != 'Y' || pBytes[1] != 'u' || pBytes[2] != 'k' || pBytes[3] != 'i') {
                    break;
                }

                if (--v2 <= 0) {
                    return NULL;
                }
            }
        }
    }

    return pData;
}

// 0x783E00
void* CDimm::InternalDemand(CRes* pRes)
{
    pRes->field_40++;
    field_8++;
    field_4 = 1;

    RESID nResID = pRes->GetID();
    if ((nResID >> 20) < m_nResFiles && (nResID & 0xFFF00000) < 0xFC000000) {
        CResFile* pResFile = m_ppResFiles[nResID >> 20];
        EnterCriticalSection(&(g_pChitin->field_35C));
        while (g_pChitin->cDimm.cResCache.field_110 == 1) {
            LeaveCriticalSection(&(g_pChitin->field_35C));
            while (g_pChitin->cDimm.cResCache.field_110 == 1) {
                SleepEx(50, 0);
            }
            EnterCriticalSection(&(g_pChitin->field_35C));
        }

        if (pResFile->m_nRefCount <= 0) {
            pResFile->m_nRefCount = 0;
            pResFile->OpenFile();
        }

        pResFile->m_nRefCount++;
        LeaveCriticalSection(&(g_pChitin->field_35C));
    }

    if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
        && pRes != field_CE
        && (pRes->dwFlags & CRes::Flags::RES_FLAG_0x10) != 0) {
        if (pRes != NULL) {
            if ((pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
            }
        }

        if (pRes->field_40 == 1) {
            field_29C += pRes->nSize;
        }

        return pRes->m_pData;
    }

    EnterCriticalSection(&(g_pChitin->field_314));

    if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x10) != 0) {
        field_0 = 1;
        if (pRes == field_CE) {
            field_270 = field_CE;
            PartialServiceRequest(field_CE, field_CE->nSize);
        }

        field_8--;
        field_0 = 0;
        field_4 = 0;
        LeaveCriticalSection(&(g_pChitin->field_314));

        EnterCriticalSection(&(g_pChitin->field_2FC));
        if (field_270 == pRes) {
            if (pRes != NULL) {
                if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                    && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                    pRes->OnResourceServiced();
                    pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                }
            }
        }
        LeaveCriticalSection(&(g_pChitin->field_2FC));
        if (pRes->field_40 == 1) {
            field_29C += pRes->nSize;
        }
        return pRes->m_pData;
    } else if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0) {
        field_8--;
        field_4 = 0;
        LeaveCriticalSection(&(g_pChitin->field_314));

        if (pRes != NULL) {
            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                pRes->OnResourceFreed();
                pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
            }
        }

        if (pRes->field_40 == 1) {
            field_29C += pRes->nSize;
        }

        return pRes->m_pData;
    } else {
        field_270 = pRes;
        ServiceRequest(pRes);

        field_8--;
        field_4 = 0;
        LeaveCriticalSection(&(g_pChitin->field_314));

        EnterCriticalSection(&(g_pChitin->field_2FC));
        if (field_270 == pRes) {
            if (pRes != NULL) {
                if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                    && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                    pRes->OnResourceServiced();
                    pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                }
            }
        }
        LeaveCriticalSection(&(g_pChitin->field_2FC));

        if (pRes->field_40 == 1) {
            field_29C += pRes->nSize;
        }

        return pRes->m_pData;
    }
}

// 0x7840E0
void CDimm::DestroyKeyTable()
{
    if (m_cKeyTable.m_bInitialized == TRUE) {
        m_cKeyTable.DestroyTable(this);
    }

    if (m_ppResFiles != NULL) {
        for (unsigned int k = 0; k < m_nResFiles; k++) {
            CResFile* pResFile = m_ppResFiles[k];
            if (pResFile != NULL) {
                delete pResFile;
            }
            m_ppResFiles[k] = NULL;
        }

        delete m_ppResFiles;
        m_ppResFiles = NULL;
        m_nResFiles = 0;
    }
}

// 0x784170
BOOL CDimm::DirectoryCopyFiles(const CString& sSource, const CString& sDest)
{
    CString sResolvedSource;
    CString sResolvedDest;
    CString sExistingFileName;
    CString sNewFileName;
    CString sTemp;
    CString sPattern;

    if (!g_pChitin->lAliases.ResolveFileName(sSource, sResolvedSource)) {
        sResolvedSource = sSource;
    }

    if (!g_pChitin->lAliases.ResolveFileName(sDest, sResolvedDest)) {
        sResolvedDest = sDest;
    }

    if (!WriteSetUp(sResolvedDest + "foo.bar", sTemp)) {
        return FALSE;
    }

    sPattern = sResolvedSource + "*.*";

    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    BOOL bResult = TRUE;
    do {
        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
            sExistingFileName = sResolvedSource + findFileData.cFileName;
            sNewFileName = sResolvedDest + findFileData.cFileName;

            if (!CopyFileA(sExistingFileName, sNewFileName, FALSE)) {
                bResult = FALSE;
            }
        }
    } while (FindNextFileA(hFindFile, &findFileData));

    FindClose(hFindFile);

    return bResult;
}

// 0x784880
BOOL CDimm::DirectoryRemoveFiles(const CString& sDirectoryName)
{
    CString sResolvedDirectoryName;
    CString sPath;
    CString sPattern;

    if (!g_pChitin->lAliases.ResolveFileName(sDirectoryName, sResolvedDirectoryName)) {
        sResolvedDirectoryName = sDirectoryName;
    }

    sPattern = sResolvedDirectoryName + "*.*";

    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile == INVALID_HANDLE_VALUE) {
        // Directory does not exists - OK.
        return TRUE;
    }

    BOOL bResult = TRUE;
    do {
        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
            sPath = sResolvedDirectoryName + findFileData.cFileName;
            if (!DeleteFileA(sPath)) {
                bResult = FALSE;
            }
        }
    } while (FindNextFileA(hFindFile, &findFileData));

    FindClose(hFindFile);

    return bResult;
}

// 0x785190
BOOL CDimm::UncompressDirectory(const CString& sTempDir, const CString& sSaveDir)
{
    CString sResolvedTempDir;
    CString sSaveFileName;
    CString sMainSaveFileName("ICEWIND2.SAV");
    CString sFileName;
    CString sPattern;

    CFile input;
    CFile output;
    CFileStatus cFileStatus;

    BYTE* pDest = NULL;
    BYTE* pSrc = NULL;
    DWORD nMaxDestSize = 0;

    sSaveFileName = sSaveDir;
    if (sSaveFileName.ReverseFind('\\') == sSaveFileName.GetLength() - 1) {
        sSaveFileName = sSaveFileName.Left(sSaveFileName.GetLength() - 1);
    }

    if (sSaveFileName.ReverseFind('\\') != -1) {
        sSaveFileName = sSaveFileName.Right(sSaveFileName.GetLength() - sSaveFileName.ReverseFind('\\') - 1);
    }

    INT nPrefixLength = 0;
    while (nPrefixLength < sSaveFileName.GetLength()
        && sSaveFileName[nPrefixLength] >= '0'
        && sSaveFileName[nPrefixLength] <= '9') {
        nPrefixLength++;
    }

    if (nPrefixLength != 0 && sSaveFileName.Find('-') == nPrefixLength) {
        sSaveFileName = sSaveFileName.Right(sSaveFileName.GetLength() - nPrefixLength - 1);
    }

    sSaveFileName += ".SAV";

    if (!g_pChitin->lAliases.ResolveFileName(sTempDir, sResolvedTempDir)) {
        sResolvedTempDir = sTempDir;
    }

    sPattern = sResolvedTempDir + "*.*";

    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile == INVALID_HANDLE_VALUE) {
        return FALSE;
    }

    do {
        if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
            sFileName = findFileData.cFileName;
            if (sFileName != sSaveFileName
                && sFileName != sMainSaveFileName
                && strnicmp(findFileData.cFileName, "ICEWIND2.GAM", 10) != 0
                && strnicmp(sFileName.Right(3), "BMP", 3) != 0
                && strnicmp(findFileData.cFileName, "WORLDMAP.WMP", 12) != 0
                && strncmp(findFileData.cFileName, "EXPMAP.WMP", 10) != 0) {
                sFileName = sResolvedTempDir + findFileData.cFileName;
                DeleteFileA(sFileName);
            }
        }
    } while (FindNextFileA(hFindFile, &findFileData));

    FindClose(hFindFile);

    BOOL bNotExists = FALSE;
    if (!input.Open(sResolvedTempDir + sSaveFileName, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary | CFile::OpenFlags::shareExclusive, NULL)) {
        if (!input.Open(sResolvedTempDir + sMainSaveFileName, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary | CFile::OpenFlags::shareExclusive, NULL)) {
            bNotExists = TRUE;
        }
    }

    if (bNotExists) {
        if (sSaveFileName == "default.SAV") {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    input.Seek(0, CFile::SeekPosition::begin);

    char szHeader[8];
    input.Read(szHeader, sizeof(szHeader));
    if (strnicmp(szHeader, "SAV V1.0", 8) != 0) {
        return FALSE;
    }

    BOOL bResult = TRUE;

    while (input.GetPosition() < input.GetLength()) {
        DWORD nFileNameLength;
        input.Read(&nFileNameLength, 4);
        input.Read(sFileName.GetBuffer(nFileNameLength), nFileNameLength);
        sFileName.ReleaseBuffer();

        if (output.Open(sResolvedTempDir + sFileName, CFile::OpenFlags::modeWrite | CFile::OpenFlags::typeBinary | CFile::OpenFlags::shareExclusive | CFile::OpenFlags::modeCreate, NULL)) {
            DWORD nDestSize;
            input.Read(&nDestSize, 4);

            DWORD nSrcSize;
            input.Read(&nSrcSize, 4);

            if (nDestSize > nMaxDestSize) {
                if (pDest != NULL) {
                    delete pDest;
                }

                if (pSrc != NULL) {
                    delete pSrc;
                }

                nMaxDestSize = max(nDestSize, 65536);

                pDest = new BYTE[nMaxDestSize];
                if (pDest == NULL) {
                    bResult = FALSE;

                    output.Close();
                    break;
                }

                pSrc = new BYTE[max(nMaxDestSize, nSrcSize)];
                if (pSrc == NULL) {
                    bResult = FALSE;

                    output.Close();
                    break;
                }
            }

            input.Read(pSrc, nSrcSize);

            int err = CUtil::Uncompress(pDest, &nDestSize, pSrc, nSrcSize);
            if (err != 0) {
                if (err != -5) {
                    CString sErr;
                    sErr.Format("z_uncompress returned %d", err);
                    sErr.Format("Uncompress in load game failed.  Error code %d.\n", err);
                    sErr += "Please report this error and look at icewind2.log file, too!";

                    bResult = FALSE;

                    output.Close();
                    break;
                }

                if (pDest != NULL) {
                    delete pDest;
                }

                nMaxDestSize *= 2;

                pDest = new BYTE[nMaxDestSize];
                if (pDest == NULL) {
                    bResult = FALSE;

                    output.Close();
                    break;
                }

                err = CUtil::Uncompress(pDest, &nDestSize, pSrc, nSrcSize);
                if (err != 0) {
                    CString sErr;
                    sErr.Format("z_uncompress returned %d", err);
                    sErr.Format("After expansion, uncompress in load game failed.  Error code %d.\n", err);
                    sErr += "Please report this error and look at icewind2.log file, too!";

                    bResult = FALSE;

                    output.Close();
                    break;
                }

                if (pSrc != NULL) {
                    delete pSrc;
                }

                pSrc = new BYTE[max(nMaxDestSize, nSrcSize)];
                if (pSrc == NULL) {
                    bResult = FALSE;

                    output.Close();
                    break;
                }
            }

            output.Seek(0, CFile::SeekPosition::begin);
            output.Write(pDest, nDestSize);
            output.Close();
        } else {
            bResult = FALSE;
            break;
        }
    }

    if (pDest != NULL) {
        delete pDest;
    }

    if (pSrc != NULL) {
        delete pSrc;
    }

    input.Close();

    if (CFile::GetStatus(sResolvedTempDir + sSaveFileName, cFileStatus)) {
        CFile::Remove(sResolvedTempDir + sSaveFileName);
    }

    if (CFile::GetStatus(sResolvedTempDir + sMainSaveFileName, cFileStatus)) {
        CFile::Remove(sResolvedTempDir + sMainSaveFileName);
    }

    return bResult;
}

// 0x785C10
int CDimm::Dump(CRes* pRes, int a2, int a3)
{
    if (pRes->field_40 > 0 && pRes->m_pCurrentList == NULL) {
        pRes->field_40 = 0;
    }

    EnterCriticalSection(&(g_pChitin->field_2FC));

    if (field_274 == pRes) {
        EnterCriticalSection(&(g_pChitin->field_32C));
        field_274 = NULL;
        LeaveCriticalSection(&(g_pChitin->field_32C));
    }

    if (field_270 == pRes) {
        EnterCriticalSection(&(g_pChitin->field_32C));
        field_270 = 0;
        LeaveCriticalSection(&(g_pChitin->field_32C));
    }

    if ((pRes->dwFlags & CRes::RES_FLAG_0x10) != 0) {
        field_D2 = 0;
        field_CE = NULL;
    }

    if ((pRes->dwFlags & (CRes::RES_FLAG_0x10 | CRes::RES_FLAG_0x04)) != 0) {
        if ((pRes->dwFlags & CRes::RES_FLAG_0x08) != 0) {
            pRes->dwFlags &= ~0x5C;

            if (pRes->m_pCurrentList != NULL) {
                pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                pRes->m_pCurrentList = NULL;
                pRes->m_pCurrentListPos = NULL;
            }

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
            // __LINE__: 7095
            UTIL_ASSERT_MSG(pRes != NULL, "Attempting to free invalid resource.");

            if (pRes->m_pData != NULL) {
                delete pRes->m_pData;
                pRes->m_pData = NULL;
            }

            field_DA -= pRes->nSize;

            pRes->m_pData = NULL;
            if (pRes->OnResourceFreed()) {
                // NOTE: Not sure why it uses bare `free`, but it's definitely
                // not `delete`.
                free(pRes);
            }
        } else {
            if ((pRes->dwFlags & CRes::RES_FLAG_0x10) != 0) {
                field_D2 = 0;
                field_CE = NULL;
            }

            if (pRes->m_pCurrentListPos != NULL) {
                if (pRes->m_pCurrentList != NULL) {
                    pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                    pRes->m_pCurrentList = NULL;
                    pRes->m_pCurrentListPos = NULL;
                }
            }

            pRes->dwFlags &= ~(CRes::RES_FLAG_0x10 | CRes::RES_FLAG_0x04);

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
            // __LINE__: 7095
            UTIL_ASSERT_MSG(pRes != NULL, "Attempting to free invalid resource.");

            if (pRes->m_pData != NULL) {
                delete pRes->m_pData;
                pRes->m_pData = NULL;
            }

            field_DA -= pRes->nSize;
            pRes->m_pData = NULL;

            if (a2 != 0 || pRes->field_44 <= 0) {
                if ((pRes->m_nID >> 20) < m_nResFiles && (pRes->m_nID & 0xFFF00000) < 0xFC000000) {
                    for (int v1 = 0; v1 < pRes->field_44; v1++) {
                        CResFile* pResFile = m_ppResFiles[pRes->m_nID >> 20];
                        EnterCriticalSection(&(g_pChitin->field_35C));

                        if (pResFile->m_nRefCount <= 1) {
                            pResFile->CloseFile();
                            pResFile->m_nRefCount = 0;
                        } else {
                            pResFile->m_nRefCount -= 1;
                        }

                        LeaveCriticalSection(&(g_pChitin->field_35C));
                    }
                }

                pRes->field_44 = 0;
                pRes->m_pCurrentListPos = NULL;
            } else {
                if (a3 == 1) {
                    pRes->dwFlags &= ~0x3;
                    pRes->m_pCurrentList = &m_lRequestedLow;
                    pRes->m_pCurrentListPos = m_lRequestedLow.AddTail(pRes);
                } else {
                    switch (pRes->dwFlags & 3) {
                    case PRIORITY_MEDIUM:
                        pRes->m_pCurrentList = &m_lRequestedMedium;
                        pRes->m_pCurrentListPos = m_lRequestedMedium.AddTail(pRes);
                        break;
                    case PRIORITY_HIGH:
                        pRes->m_pCurrentList = &m_lRequestedHigh;
                        pRes->m_pCurrentListPos = m_lRequestedHigh.AddTail(pRes);
                        break;
                    default:
                        pRes->m_pCurrentList = &m_lRequestedLow;
                        pRes->m_pCurrentListPos = m_lRequestedLow.AddTail(pRes);
                        break;
                    }
                }
            }
        }
    } else {
        if (a2 != 0 && pRes->field_44 > 0 && pRes->m_pCurrentListPos != NULL) {
            if (pRes->m_pCurrentList != NULL) {
                pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                pRes->m_pCurrentList = NULL;
                pRes->m_pCurrentListPos = NULL;
            }

            if ((pRes->m_nID >> 20) < m_nResFiles && (pRes->m_nID & 0xFFF00000) < 0xFC000000) {
                for (int v1 = 0; v1 < pRes->field_44; v1++) {
                    CResFile* pResFile = m_ppResFiles[pRes->m_nID >> 20];
                    EnterCriticalSection(&(g_pChitin->field_35C));

                    if (pResFile->m_nRefCount <= 1) {
                        pResFile->CloseFile();
                        pResFile->m_nRefCount = 0;
                    } else {
                        pResFile->m_nRefCount -= 1;
                    }

                    LeaveCriticalSection(&(g_pChitin->field_35C));
                }
            }

            pRes->m_pCurrentListPos = NULL;
            pRes->field_44 = 0;
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    return 0;
}

// 0x785FB0
int CDimm::DumpAll()
{
    POSITION pos;

    pos = m_lFreed.GetHeadPosition();
    while (pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lFreed.GetNext(pos));
        if (pRes != NULL) {
            AfxIsValidAddress(pRes, sizeof(CRes), TRUE);
        }
    }
    m_lFreed.RemoveAll();

    pos = m_lServicedHigh.GetHeadPosition();
    while (pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedHigh.GetNext(pos));
        if (pRes != NULL) {
            AfxIsValidAddress(pRes, sizeof(CRes), TRUE);
        }
    }
    m_lServicedHigh.RemoveAll();

    pos = m_lServicedMedium.GetHeadPosition();
    while (pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedMedium.GetNext(pos));
        if (pRes != NULL) {
            AfxIsValidAddress(pRes, sizeof(CRes), TRUE);
        }
    }
    m_lServicedMedium.RemoveAll();

    pos = m_lServicedLow.GetHeadPosition();
    while (pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedLow.GetNext(pos));
        if (pRes != NULL) {
            AfxIsValidAddress(pRes, sizeof(CRes), TRUE);
        }
    }
    m_lServicedLow.RemoveAll();

    m_lRequestedHigh.RemoveAll();
    m_lRequestedMedium.RemoveAll();
    m_lRequestedLow.RemoveAll();

    return 0;
}

// 0x786080
int CDimm::FindDirectoryInDirectoryList(const CString& sDirName)
{
    CString v1;
    CString v2;
    if (!g_pChitin->lAliases.ResolveFileName(sDirName, v1)) {
        v1 = sDirName;
    }

    int v3 = 0;
    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL) {
        v2 = m_lDirectories.GetAt(pos);
        if (v1.Compare(v2) == 0) {
            return v3;
        }

        v3++;

        m_lDirectories.GetNext(pos);
    }

    return DIMM_NOT_IN_DIRECTORY_LIST;
}

// 0x786180
BOOL CDimm::FindFileInDirectoryList(const CString& sDirName, CString& sFileName)
{
    CFileFind fileFind;
    CString v1;

    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL) {
        v1 = m_lDirectories.GetAt(pos);
        if (fileFind.FindFile(sDirName + v1)) {
            sFileName = v1;
            return TRUE;
        }

        m_lDirectories.GetNext(pos);
    }

    return FALSE;
}

// 0x786290
BOOL CDimm::GetElementInDirectoryList(int nIndex, CString& sDirName)
{
    CString v1;
    CString v2;

    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL && nIndex > 0) {
        nIndex--;
        m_lDirectories.GetNext(pos);
    }

    if (pos != NULL) {
        v1 = m_lDirectories.GetAt(pos);
        if (!g_pChitin->lAliases.ResolveFileName(v1, v2)) {
            v2 = v1;
        }

        sDirName = v2;

        return TRUE;
    }

    return FALSE;
}

// 0x786390
int CDimm::GetMemoryAmount()
{
    if (g_pChitin->dwPlatformId == VER_PLATFORM_WIN32_NT) {
        if (dwTotalPhysicalMemory < 23 * 1024 * 1024) {
            return 2;
        }

        if (dwTotalPhysicalMemory < 31 * 1024 * 1024) {
            return 1;
        }
    } else {
        if (dwTotalPhysicalMemory < 15 * 1024 * 1024) {
            return 2;
        }

        if (dwTotalPhysicalMemory < 23 * 1024 * 1024) {
            return 1;
        }
    }

    return 0;
}

// #binary-identical
// 0x7863E0
UINT CDimm::GetResFileID(const CString& sName)
{
    CString sFileName = sName + ".BIF";
    sFileName.MakeUpper();

    CString v1;
    for (unsigned int k = 0; k < m_cKeyTable.m_nResFiles; k++) {
        v1 = reinterpret_cast<char*>(m_cKeyTable.m_pResFileNameEntries) + m_cKeyTable.m_pResFileNameEntries[k].nFileNameOffset;
        v1.MakeUpper();
        if (v1.FindOneOf(sFileName) != -1) {
            return k << 20;
        }
    }

    return -1;
}

// 0x7864F0
CResFile* CDimm::GetResFilePtr(UINT a2)
{
    UINT nIndex = a2 >> 20;
    if (m_cKeyTable.m_bInitialized) {
        if (nIndex < m_cKeyTable.m_nResFiles) {
            return m_ppResFiles[nIndex];
        }
    }

    return NULL;
}

// 0x786520
BOOL CDimm::GetResFileName(UINT nIndex, CString& sResFileName, WORD& nDrive, BOOLEAN a5)
{
    CFileFind fileFind;
    CString sDrive("");
    CString sFileName;
    CString sResolvedFileName;

    nDrive = 0;

    if (!m_cKeyTable.m_bInitialized || nIndex >= m_cKeyTable.m_nResFiles) {
        nDrive = 0;
        return FALSE;
    }

    sFileName = reinterpret_cast<char*>(m_cKeyTable.m_pResFileNameEntries) + m_cKeyTable.m_pResFileNameEntries[nIndex].nFileNameOffset;

    WORD drives = m_cKeyTable.m_pResFileNameEntries[nIndex].bDrives;
    if ((drives & 1) != 0) {
        CString sTemp;

        sDrive = "hd0:";
        sTemp = sDrive + "\\" + sFileName;
        if (!g_pChitin->lAliases.ResolveFileName(sTemp, sResolvedFileName)) {
            sResolvedFileName = sTemp;
        }

        if (fileFind.FindFile(sResolvedFileName)) {
            nDrive = 1;
        } else {
            fileFind.Close();
            sDrive = "";
        }
    }

    if (sDrive.Compare("") == 0) {
        if ((drives & 0x200) != 0) {
            if (FindFileInDirectoryList(sFileName, sDrive) == TRUE) {
                nDrive = 0x200;
            }
        }
    }

    if (sDrive.Compare("") == 0) {
        BOOLEAN bFound = FALSE;

        CDScan(drives);

        WORD nDriveCandidate;
        WORD v4 = drives & field_EA;
        if ((v4 & 2) != 0) {
            sDrive = "cd0:";
            nDriveCandidate = 2;
        } else if ((v4 & 4) != 0) {
            sDrive = "cd1:";
            nDriveCandidate = 4;
        } else if ((v4 & 8) != 0) {
            sDrive = "cd2:";
            nDriveCandidate = 8;
        } else if ((v4 & 16) != 0) {
            sDrive = "cd3:";
            nDriveCandidate = 16;
        } else {
            nDriveCandidate = 0;
        }

        if (nDriveCandidate != 0) {
            if (!g_pChitin->lAliases.ResolveFileName(sDrive + "\\" + sFileName, sResolvedFileName)) {
                sResolvedFileName = sFileName;
            }

            if (fileFind.FindFile(sResolvedFileName)) {
                bFound = TRUE;
                nDrive = nDriveCandidate;
            } else {
                CString sCopy(sResolvedFileName);

                int pos = sCopy.ReverseFind('.');
                sCopy.SetAt(++pos, 'c');
                sCopy.SetAt(++pos, 'b');
                sCopy.SetAt(++pos, 'f');

                if (fileFind.FindFile(sCopy)) {
                    pos = sFileName.ReverseFind('.');
                    sFileName.SetAt(++pos, 'c');
                    sFileName.SetAt(++pos, 'b');
                    sFileName.SetAt(++pos, 'f');

                    bFound = TRUE;
                    nDrive = nDriveCandidate;
                } else {
                    fileFind.Close();
                    sDrive = "";
                }
            }
        }

        if (!bFound) {
            switch (CDSwitch(drives, sFileName, a5)) {
            case 0:
                exit(EXIT_SUCCESS);
            case 2:
                sDrive = "cd0:";
                break;
            case 4:
                sDrive = "cd1:";
                break;
            case 8:
                sDrive = "cd2:";
                break;
            case 16:
                sDrive = "cd3:";
                break;
            }
        }
    }

    if (sFileName.GetAt(0) == '\\' || sDrive.Right(1).Compare("\\") == 0) {
        sResFileName.Format("%s%s", sDrive, sFileName);
    } else {
        sResFileName.Format("%s\\%s", sDrive, sFileName);
    }

    return TRUE;
}

// FIXME: `resRef` should be reference.
//
// 0x786A80
INT CDimm::GetResNumber(RESID nResID, CResRef resRef, USHORT nResType)
{
    CString sFilePath;
    CString sBaseName;
    CString sExtension;
    CFile file;

    INT nCount = 0;

    if ((nResID & 0xFFF00000) < 0xFC000000) {
        if ((nResID >> 20) < m_nResFiles) {
            CResFile* pResFile = m_ppResFiles[nResID >> 20];

            CResCache* pResCache = &(g_pChitin->cDimm.cResCache);
            EnterCriticalSection(&(g_pChitin->field_35C));
            while (pResCache->field_110 == 1) {
                LeaveCriticalSection(&(g_pChitin->field_35C));

                while (pResCache->field_110 == 1) {
                    SleepEx(50, FALSE);
                }

                EnterCriticalSection(&(g_pChitin->field_35C));
            }

            if (pResFile->m_nRefCount <= 0) {
                pResFile->m_nRefCount = 0;
                pResFile->OpenFile();
            }

            pResFile->m_nRefCount += 1;

            LeaveCriticalSection(&(g_pChitin->field_35C));

            if (pResFile->m_bOpen) {
                if ((nResID & 0xFC000) != 0) {
                    UINT nIndex = (nResID >> 14) & 0x3F;
                    if (nIndex - 1 < pResFile->m_pHeader->nFixedRes) {
                        nCount = pResFile->m_pFixedEntries[nIndex - 1].nNumber;
                    } else {
                        nCount = 0;
                    }
                } else {
                    nCount = 1;
                }
            }

            EnterCriticalSection(&(g_pChitin->field_35C));

            if (pResFile->m_nRefCount <= 1) {
                pResFile->CloseFile();
                pResFile->m_nRefCount = 0;
            } else {
                pResFile->m_nRefCount -= 1;
            }

            LeaveCriticalSection(&(g_pChitin->field_35C));
        }
    } else {
        if (resRef != "") {
            resRef.CopyToString(sBaseName);
            g_pChitin->TranslateType(nResType, sExtension);
            GetElementInDirectoryList(~nResID >> 20, sFilePath);

            sFilePath += sBaseName + "." + sExtension;

            if (file.Open(sFilePath, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary, NULL)) {
                // NOTE: I'm not sure what type of header we're reading here. It
                // is assumed to have an integer right after the file signature.
                unsigned char header[20];
                file.Read(header, sizeof(header));
                file.Close();

                nCount = *reinterpret_cast<int*>(header + 8);
            }
        }
    }

    return nCount;
}

// 0x786DF0
CRes* CDimm::GetResObject(const CResRef& cResRef, USHORT nResType, BOOL bWarningIfMissing)
{
    CDimmKeyTableEntry* pKey = m_cKeyTable.FindKey(cResRef, nResType, bWarningIfMissing);
    if (pKey == NULL) {
        return NULL;
    }

    if (pKey->pRes != NULL) {
        pKey->field_10++;
        return pKey->pRes;
    }

    pKey->pRes = g_pChitin->AllocResObject(nResType);
    if (pKey->pRes == NULL) {
        return NULL;
    }

    pKey->pRes->SetID(pKey->nID);
    pKey->pRes->m_pDimmKeyTableEntry = pKey;
    pKey->field_10++;
    return pKey->pRes;
}

// 0x786E50
RESID CDimm::GetResID(CResRef cResRef, USHORT nResType)
{
    CDimmKeyTableEntry* pKey = m_cKeyTable.FindKey(cResRef, nResType, TRUE);
    if (pKey != NULL) {
        return pKey->nID;
    }

    return -1;
}

// #guess
// 0x786E90
BOOL CDimm::LocalGetFileStatus(const CString& sFileName, CFileStatus& rStatus)
{
    BOOL rc = FALSE;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 3820
    UTIL_ASSERT(sFileName.GetLength() > 0);

    CFile file;
    if (file.Open(sFileName, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary, NULL)) {
        rc = file.GetStatus(rStatus);
    }

    return rc;
}

// 0x786F30
DWORD CDimm::LocalGetResourceSize(CRes* pRes)
{
    CString sFilePath;
    CString sBaseName;
    CString sExtension;
    CFile file;

    if (pRes == NULL) {
        return 0;
    }

    DWORD size = pRes->GetFixedResourceSize();
    if (size != -1) {
        return size;
    }

    if (pRes->m_pDimmKeyTableEntry == NULL) {
        return 0;
    }

    pRes->GetResRef().CopyToString(sBaseName);
    g_pChitin->TranslateType(pRes->m_pDimmKeyTableEntry->nResType, sExtension);
    GetElementInDirectoryList(~pRes->GetID() >> 20, sFilePath);

    sFilePath += sBaseName + "." + sExtension;
    if (file.Open(sFilePath, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary, NULL)) {
        size = static_cast<DWORD>(file.GetLength());
        file.Close();
    } else {
        size = 0;
    }

    return size;
}

// 0x787180
int CDimm::LocalReadResource(CRes* pRes, DWORD nNumberOfBytesToRead, DWORD nOffset)
{
    INT nBytesRead = 0;

    // NOTE: Unused.
    CString sDirName;

    CString sExt;
    CString sFileName;
    CFile file;
    CResRef resRef;

    if (pRes != NULL && pRes->m_pData != NULL) {
        resRef = pRes->GetResRef();
        if (resRef != "") {
            BYTE szRes[RESREF_SIZE + 1];
            resRef.GetResRef(szRes);
            szRes[RESREF_SIZE] = '\0';

            g_pChitin->TranslateType(pRes->GetType(), sExt);

            RESID nResID = pRes->GetID();
            GetElementInDirectoryList(~nResID >> 20, sFileName);

            sFileName = sFileName + szRes + "." + sExt;

            int nFixedOffset = pRes->GetFixedResourceDataOffset();
            int nFixedSize = pRes->GetFixedResourceSize();
            if (nFixedSize >= 0) {
                nFixedOffset += nFixedSize * (pRes->GetID() & 0x3FFF);
            }

            if (file.Open(sFileName, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary)) {
                file.Seek(nOffset + nFixedOffset, CFile::SeekPosition::begin);
                nBytesRead = file.Read(reinterpret_cast<BYTE*>(pRes->m_pData) + nOffset, nNumberOfBytesToRead);
                file.Close();
            }
        }
    }

    return nBytesRead;
}

// #binary-identical
// 0x787740
BOOL CDimm::MemoryAlmostFull()
{
    return field_DA + 1200000 > field_D6;
}

// #binary-identical
// 0x787760
void CDimm::MoveRequests(int nOldPriority, int nNewPriority, int nCount)
{
    POSITION pos;
    int nRemaining = nCount;

    switch (nOldPriority) {
    case PRIORITY_HIGH:
        pos = m_lRequestedHigh.GetHeadPosition();
        while (pos != NULL && nRemaining > 0) {
            CRes* pRes = static_cast<CRes*>(m_lRequestedHigh.GetNext(pos));
            nRemaining--;
            if (pRes != NULL) {
                SetNewPriority(pRes, nNewPriority);
            }
        }
        break;
    case PRIORITY_MEDIUM:
        pos = m_lRequestedMedium.GetHeadPosition();
        while (pos != NULL && nRemaining > 0) {
            CRes* pRes = static_cast<CRes*>(m_lRequestedMedium.GetNext(pos));
            nRemaining--;
            if (pRes != NULL) {
                SetNewPriority(pRes, nNewPriority);
            }
        }
        break;
    case PRIORITY_LOW:
        pos = m_lRequestedLow.GetHeadPosition();
        while (pos != NULL && nRemaining > 0) {
            CRes* pRes = static_cast<CRes*>(m_lRequestedLow.GetNext(pos));
            nRemaining--;
            if (pRes != NULL) {
                SetNewPriority(pRes, nNewPriority);
            }
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
        // __LINE__: 4365
        UTIL_ASSERT(FALSE);
    }
}

// 0x787830
void CDimm::PartialServiceRequest(CRes* pRes, DWORD nBytesToRead)
{
    EnterCriticalSection(&(g_pChitin->field_32C));

    if (field_274 != NULL) {
        RESID nResID = pRes->GetID();
        if ((nResID >> 20) < m_nResFiles || (nResID & 0xFFF00000) >= 0xFC000000) {
            DWORD nResSize = (nResID & 0xFFF00000) < 0xFC000000
                ? m_ppResFiles[nResID >> 20]->GetFileSize(pRes->GetID())
                : LocalGetResourceSize(pRes);
            DWORD nRemaining = nResSize - field_D2;
            if (nResSize != field_D2) {
                if (nBytesToRead < nRemaining) {
                    UINT nBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                        ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, nBytesToRead, field_D2)
                        : LocalReadResource(pRes, nBytesToRead, field_D2);
                    if (field_CE == pRes || field_CE == NULL) {
                        field_CE = pRes;
                        field_D2 += nBytesRead;
                    }
                } else {
                    UINT nBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                        ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, nRemaining, field_D2)
                        : LocalReadResource(pRes, nRemaining, field_D2);
                    if (nBytesRead < nRemaining) {
                        if (field_CE == pRes || field_CE == NULL) {
                            field_CE = pRes;
                            field_D2 += nBytesRead;
                        }
                    } else {
                        if (field_CE == pRes || field_CE == NULL) {
                            field_CE = NULL;
                            field_D2 = nRemaining;

                            pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                            pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                        }
                    }
                }
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_32C));
}

// 0x7879C0
void CDimm::ReduceFreedList(UINT a2)
{
    if (a2 != 0) {
        EnterCriticalSection(&(g_pChitin->field_2FC));

        POSITION pos = m_lFreed.GetHeadPosition();
        while (field_DA + a2 > field_D6 && pos != NULL) {
            CRes* pRes = static_cast<CRes*>(m_lFreed.GetNext(pos));
            if (pRes != NULL) {
                if (pRes->field_40 == 0) {
                    if (pRes->OnResourceFreed()) {
                        Dump(pRes, 1, 0);
                        delete pRes;
                    } else {
                        Dump(pRes, 0, 0);
                    }
                }
            }
        }

        LeaveCriticalSection(&(g_pChitin->field_2FC));
    }
}

// #binary-identical
// 0x787A70
BOOL CDimm::ReduceServicedList()
{
    POSITION pos;

    EnterCriticalSection(&(g_pChitin->field_2FC));

    ReduceFreedList(1200000);

    pos = m_lServicedLow.GetHeadPosition();
    // NOTE: Uninline `MemoryAlmostFull`.
    while (MemoryAlmostFull() && pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedLow.GetNext(pos));
        if (pRes != NULL && pRes->field_40 == 0) {
            if (pRes->OnResourceFreed()) {
                Dump(pRes, 1, 0);
                // NOTE: Not sure why it uses bare `free`, but it's definitely
                // not `delete`.
                free(pRes);
            } else {
                Dump(pRes, 0, 0);
            }
        }
    }

    pos = m_lServicedMedium.GetHeadPosition();
    // NOTE: Uninline `MemoryAlmostFull`.
    while (MemoryAlmostFull() && pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedLow.GetNext(pos));
        if (pRes != NULL && pRes->field_40 == 0) {
            if (pRes->OnResourceFreed()) {
                Dump(pRes, 1, 0);
                // NOTE: Not sure why it uses bare `free`, but it's definitely
                // not `delete`.
                free(pRes);
            } else {
                Dump(pRes, 0, 0);
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    // NOTE: Uninline.
    return !MemoryAlmostFull();
}

// #binary-identical
// 0x787BA0
int CDimm::Release(CRes* pRes)
{
    pRes->field_40 -= 1;

    if (pRes->field_40 == 0) {
        field_29C -= pRes->nSize;
    }

    if (pRes->field_40 != 0 || (pRes->dwFlags & CRes::RES_FLAG_0x100) == 0) {
        if (pRes->field_44 == 0 && pRes->field_40 == 0) {
            EnterCriticalSection(&(g_pChitin->field_2FC));

            if ((pRes->dwFlags & CRes::RES_FLAG_0x08) == 0) {
                if (pRes->m_pCurrentList != NULL) {
                    pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                    pRes->m_pCurrentList = NULL;
                    pRes->m_pCurrentListPos = NULL;
                }

                if ((pRes->dwFlags & (CRes::RES_FLAG_0x04 | CRes::RES_FLAG_0x10)) != 0) {
                    pRes->m_pCurrentList = &m_lFreed;
                    pRes->m_pCurrentListPos = m_lFreed.AddTail(pRes);
                    pRes->dwFlags |= CRes::RES_FLAG_0x08;
                }
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));
        }

        if ((pRes->m_nID >> 20) < m_nResFiles && (pRes->m_nID & 0xFFF00000) < 0xFC000000) {
            CResFile* pResFile = m_ppResFiles[pRes->m_nID >> 20];
            EnterCriticalSection(&(g_pChitin->field_35C));

            if (pResFile->m_nRefCount <= 1) {
                pResFile->CloseFile();
                pResFile->m_nRefCount = 0;
            } else {
                pResFile->m_nRefCount -= 1;
            }

            LeaveCriticalSection(&(g_pChitin->field_35C));
        }

        return 0;
    } else {
        pRes->dwFlags &= ~0x100;

        Dump(pRes, 1, 0);

        if (pRes->m_pDimmKeyTableEntry != NULL) {
            pRes->SetID(pRes->m_pDimmKeyTableEntry->nID);
        }

        return 0;
    }
}

// #binary-identical
// 0x787CE0
void CDimm::ReleaseResObject(CRes* pRes)
{
    if (pRes != NULL) {
        CDimmKeyTableEntry* pKey = pRes->m_pDimmKeyTableEntry;
        if (pKey != NULL) {
            pKey->field_10 -= 1;
            if (pKey->field_10 <= 0) {
                pKey->field_10 = 0;
                Dump(pRes, 1, 0);
                pRes->m_pDimmKeyTableEntry = NULL;

                if (pKey->pRes != NULL) {
                    delete pKey->pRes;
                }
                pKey->pRes = NULL;
            }
        }
    }
}

// 0x787D30
BOOL CDimm::RemoveFromDirectoryList(const CString& sDirName, BOOL bRescan)
{
    CString sResolvedDirName;
    CString sCurrentDirName;

    if (!g_pChitin->lAliases.ResolveFileName(sDirName, sResolvedDirName)) {
        sResolvedDirName = sDirName;
    }

    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL) {
        sCurrentDirName = m_lDirectories.GetAt(pos);
        if (sResolvedDirName == sCurrentDirName) {
            break;
        }

        m_lDirectories.GetNext(pos);
    }

    if (pos == NULL) {
        return NULL;
    }

    m_lDirectories.RemoveAt(pos);

    if (m_cKeyTable.m_bInitialized) {
        if (bRescan) {
            EnterCriticalSection(&(g_pChitin->field_314));
            m_cKeyTable.RescanEverything();
            LeaveCriticalSection(&(g_pChitin->field_314));
        }
    }

    return FALSE;
}

// #binary-identical
// 0x787F20
int CDimm::Request(CRes* pRes)
{
    if (pRes->field_44 == 0 && pRes->field_40 == 0) {
        EnterCriticalSection(&(g_pChitin->field_2FC));

        if ((pRes->dwFlags & CRes::RES_FLAG_0x08) == CRes::RES_FLAG_0x08) {
            if (pRes->m_pCurrentList != NULL) {
                pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                pRes->m_pCurrentList = NULL;
                pRes->m_pCurrentListPos = NULL;
            }

            pRes->dwFlags &= ~CRes::RES_FLAG_0x08;
        }

        if ((pRes->dwFlags & CRes::RES_FLAG_0x04) == CRes::RES_FLAG_0x04) {
            if (pRes->m_pCurrentListPos != NULL) {
                if (pRes->m_pCurrentList != NULL) {
                    pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                    pRes->m_pCurrentList = NULL;
                    pRes->m_pCurrentListPos = NULL;
                }
            }

            switch (pRes->dwFlags & 3) {
            case PRIORITY_HIGH:
                pRes->m_pCurrentList = &m_lServicedHigh;
                pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
                break;
            case PRIORITY_MEDIUM:
                pRes->m_pCurrentList = &m_lServicedMedium;
                pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
                break;
            default:
                pRes->m_pCurrentList = &m_lServicedLow;
                pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
                break;
            }
        } else {
            if ((pRes->dwFlags & CRes::RES_FLAG_0x10) != CRes::RES_FLAG_0x10) {
                switch (pRes->dwFlags & 3) {
                case PRIORITY_HIGH:
                    pRes->m_pCurrentList = &m_lRequestedHigh;
                    pRes->m_pCurrentListPos = m_lRequestedHigh.AddTail(pRes);
                    break;
                case PRIORITY_MEDIUM:
                    pRes->m_pCurrentList = &m_lRequestedMedium;
                    pRes->m_pCurrentListPos = m_lRequestedMedium.AddTail(pRes);
                    break;
                default:
                    pRes->m_pCurrentList = &m_lRequestedLow;
                    pRes->m_pCurrentListPos = m_lRequestedLow.AddTail(pRes);
                    break;
                }
            }
        }

        LeaveCriticalSection(&(g_pChitin->field_2FC));
    }

    pRes->field_44 += 1;

    if ((pRes->m_nID >> 20) < m_nResFiles && (pRes->m_nID & 0xFFF00000) < 0xFC000000) {
        CResFile* pResFile = m_ppResFiles[pRes->m_nID >> 20];

        CResCache* pResCache = &(g_pChitin->cDimm.cResCache);
        EnterCriticalSection(&(g_pChitin->field_35C));
        while (pResCache->field_110 == 1) {
            LeaveCriticalSection(&(g_pChitin->field_35C));

            while (pResCache->field_110 == 1) {
                SleepEx(50, FALSE);
            }

            EnterCriticalSection(&(g_pChitin->field_35C));
        }

        if (pResFile->m_nRefCount <= 0) {
            pResFile->m_nRefCount = 0;
            pResFile->OpenFile();
        }

        pResFile->m_nRefCount += 1;

        LeaveCriticalSection(&(g_pChitin->field_35C));
    }

    return 0;
}

// 0x7880E0
BOOL CDimm::RequestsPending(int nPriority)
{
    BOOL rc = FALSE;

    EnterCriticalSection(&(g_pChitin->field_2FC));

    switch (nPriority) {
    case PRIORITY_LOW:
        if (!m_lRequestedLow.IsEmpty()) {
            rc = TRUE;
        }
        break;
    case PRIORITY_MEDIUM:
        if (!m_lRequestedMedium.IsEmpty()) {
            rc = TRUE;
        }
        break;
    case PRIORITY_HIGH:
        if (!m_lRequestedHigh.IsEmpty()) {
            rc = TRUE;
        }
        break;
    default:
        if (!m_lRequestedHigh.IsEmpty() || !m_lRequestedMedium.IsEmpty() || !m_lRequestedLow.IsEmpty()) {
            rc = TRUE;
        }
        break;
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    return rc;
}

// 0x788160
INT CDimm::RequestsPendingCount()
{
    EnterCriticalSection(&(g_pChitin->field_2FC));

    INT low = m_lRequestedLow.GetCount();
    INT medium = m_lRequestedMedium.GetCount();
    INT high = m_lRequestedHigh.GetCount();

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    return low + medium + high;
}

// 0x7881B0
INT CDimm::RequestsPendingCount(int nPriority)
{
    INT count;

    EnterCriticalSection(&(g_pChitin->field_2FC));

    switch (nPriority) {
    case PRIORITY_LOW:
        count = m_lRequestedLow.GetCount();
        break;
    case PRIORITY_MEDIUM:
        count = m_lRequestedMedium.GetCount();
        break;
    case PRIORITY_HIGH:
        count = m_lRequestedHigh.GetCount();
        break;
    default:
        count = m_lRequestedHigh.GetCount() + m_lRequestedLow.GetCount() + m_lRequestedMedium.GetCount();
        break;
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    return count;
}

// 0x788220
BOOL CDimm::Resume()
{
    if (field_E6 > 0) {
        field_E6--;
        if (field_E6 <= 0) {
            field_E6 = 0;
            field_4 = 0;
            field_8 = 0;
            return TRUE;
        }
    }
    return FALSE;
}

// 0x788250
BOOL CDimm::ResumeServicing()
{
    if (!RequestsPending(PRIORITY_ANY)) {
        return FALSE;
    }

    if (field_DA > field_D6) {
        ReduceFreedList(1200000);
        if (field_DA >= field_D6) {
            return FALSE;
        }
    }

    ResumeThread(g_pChitin->m_hRSThread);

    return TRUE;
}

// 0x7882D0
BOOL CDimm::ServiceFromFile(CRes* pRes, CString a3)
{
    CFile cFile;
    CString v1;

    if (!g_pChitin->lAliases.ResolveFileName(a3, v1)) {
        v1 = a3;
    }

    if (!cFile.Open(v1, CFile::OpenFlags::modeRead | CFile::OpenFlags::typeBinary, NULL)) {
        return FALSE;
    }

    UINT nSize = static_cast<UINT>(cFile.GetLength());
    if (nSize <= 0) {
        return FALSE;
    }

    pRes->m_pData = malloc(nSize);
    if (pRes->m_pData == NULL) {
        cFile.Close();
        return FALSE;
    }

    EnterCriticalSection(&(g_pChitin->field_32C));
    pRes->nSize = cFile.Read(pRes->m_pData, nSize);
    pRes->dwFlags |= CRes::RES_FLAG_0x04;
    LeaveCriticalSection(&(g_pChitin->field_32C));

    cFile.Close();

    if (pRes != NULL) {
        if ((pRes->dwFlags & CRes::RES_FLAG_0x04) != 0 && (pRes->dwFlags & (CRes::RES_FLAG_0x20 | CRes::RES_FLAG_0x40)) == 0) {
            pRes->dwFlags |= CRes::RES_FLAG_0x20;
            pRes->OnResourceServiced();
            pRes->dwFlags &= ~CRes::RES_FLAG_0x20;
            pRes->dwFlags |= CRes::RES_FLAG_0x40;
        }
    }

    pRes->nSize = 0;
    pRes->m_nID = -1;

    return TRUE;
}

// 0x788480
void CDimm::ServiceRequest(CRes* pRes, DWORD nBytesToRead)
{
    if (field_274 == NULL) {
        return;
    }

    if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) == 0) {
        EnterCriticalSection(&(g_pChitin->field_2FC));

        if (field_274 != NULL) {
            RESID nResID = pRes->GetID();
            if ((nResID >> 20) >= m_nResFiles
                && ((nResID & 0xFFF00000) < 0xFC000000
                    || (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x04 | CRes::Flags::RES_FLAG_0x10)) != 0)) {
                pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                field_274 = NULL;
            } else {
                DWORD nSize = (nResID & 0xFFF00000) < 0xFC000000
                    ? m_ppResFiles[nResID >> 20]->GetFileSize(pRes->GetID())
                    : LocalGetResourceSize(pRes);

                if (nSize != 0) {
                    pRes->nSize = nSize;
                    if (Alloc(pRes, pRes->nSize)) {
                        if (pRes->m_pCurrentListPos != NULL && pRes->m_pCurrentList != NULL) {
                            pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                            pRes->m_pCurrentList = NULL;
                            pRes->m_pCurrentListPos = NULL;
                        }

                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x10;

                        switch (pRes->dwFlags & 3) {
                        case PRIORITY_MEDIUM:
                            pRes->m_pCurrentList = &m_lServicedMedium;
                            pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
                            break;
                        case PRIORITY_HIGH:
                            pRes->m_pCurrentList = &m_lServicedHigh;
                            pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
                            break;
                        default:
                            pRes->m_pCurrentList = &m_lServicedLow;
                            pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
                            break;
                        }

                        LeaveCriticalSection(&(g_pChitin->field_2FC));

                        EnterCriticalSection(&(g_pChitin->field_32C));
                        if (field_274 != NULL) {
                            if (nBytesToRead < pRes->nSize) {
                                UINT nBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                                    ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, nBytesToRead, 0)
                                    : LocalReadResource(pRes, nBytesToRead, 0);
                                if (field_CE == pRes || field_CE == NULL) {
                                    field_CE = pRes;
                                    field_D2 = nBytesRead;
                                } else {
                                    if (nBytesRead < pRes->nSize) {
                                        if ((nResID & 0xFFF00000) < 0xFC000000) {
                                            m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, pRes->nSize - nBytesRead, 0);
                                        } else {
                                            LocalReadResource(pRes, pRes->nSize - nBytesRead, 0);
                                        }

                                        pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                                    }
                                }
                            } else {
                                UINT nBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                                    ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, pRes->nSize, 0)
                                    : LocalReadResource(pRes, pRes->nSize, 0);
                                if (nBytesRead < pRes->nSize) {
                                    if (field_CE == pRes || field_CE == NULL) {
                                        field_CE = pRes;
                                        field_D2 = nBytesRead;
                                    } else {
                                        UINT nMoreBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                                            ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, pRes->nSize - nBytesRead, 0)
                                            : LocalReadResource(pRes, pRes->nSize - nBytesRead, 0);
                                        pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                                    }
                                } else {
                                    if (field_CE == pRes || field_CE == NULL) {
                                        field_CE = NULL;
                                        field_D2 = nBytesRead;
                                        pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                                    }
                                }
                            }
                        }
                        LeaveCriticalSection(&(g_pChitin->field_32C));
                        return;
                    }
                }
            }
        }

        LeaveCriticalSection(&(g_pChitin->field_2FC));
    } else {
        if (pRes->m_pCurrentList == &m_lRequestedHigh
            || pRes->m_pCurrentList == &m_lRequestedMedium
            || pRes->m_pCurrentList == &m_lRequestedLow) {
            EnterCriticalSection(&(g_pChitin->field_2FC));

            if (field_274 != NULL) {
                if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0) {
                    if (pRes->m_pData != NULL) {
                        if (pRes->m_pCurrentList == &m_lRequestedLow
                            || pRes->m_pCurrentList == &m_lRequestedMedium
                            || pRes->m_pCurrentList == &m_lRequestedLow) {
                            if (pRes->m_pCurrentListPos != NULL && pRes->m_pCurrentList != NULL) {
                                pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                                pRes->m_pCurrentList = NULL;
                                pRes->m_pCurrentListPos = NULL;
                            }

                            switch (pRes->dwFlags & 3) {
                            case PRIORITY_MEDIUM:
                                pRes->m_pCurrentList = &m_lServicedMedium;
                                pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
                                break;
                            case PRIORITY_HIGH:
                                pRes->m_pCurrentList = &m_lServicedHigh;
                                pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
                                break;
                            default:
                                pRes->m_pCurrentList = &m_lServicedLow;
                                pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
                                break;
                            }
                        }
                    }
                }
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));
        }
    }
}

// 0x788860
void CDimm::ServiceRequest(CRes* pRes)
{
    if (field_270 == NULL) {
        return;
    }

    if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) == 0) {
        EnterCriticalSection(&(g_pChitin->field_2FC));

        if (field_270 == NULL) {
            LeaveCriticalSection(&(g_pChitin->field_2FC));
            return;
        }

        RESID nResID = pRes->GetID();
        if ((nResID >> 20) >= m_nResFiles
            && ((nResID & 0xFFF00000) < 0xFC000000
                || (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x04 | CRes::Flags::RES_FLAG_0x10)) != 0)) {
            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x10) != 0) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                // __LINE__: 6079
                UTIL_ASSERT(FALSE);
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));
            field_270 = NULL;
            return;
        }

        pRes->nSize = (nResID & 0xFFF00000) < 0xFC000000
            ? m_ppResFiles[nResID >> 20]->GetFileSize(pRes->GetID())
            : LocalGetResourceSize(pRes);

        if (pRes->nSize == 0 || !Alloc(pRes, pRes->nSize)) {
            LeaveCriticalSection(&(g_pChitin->field_2FC));
            field_270 = NULL;
            return;
        }

        if (pRes->m_pCurrentListPos != NULL && pRes->m_pCurrentList != NULL) {
            pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
            pRes->m_pCurrentList = NULL;
            pRes->m_pCurrentListPos = NULL;
        }

        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x10;

        switch (pRes->dwFlags & 3) {
        case PRIORITY_MEDIUM:
            pRes->m_pCurrentList = &m_lServicedMedium;
            pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
            break;
        case PRIORITY_HIGH:
            pRes->m_pCurrentList = &m_lServicedHigh;
            pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
            break;
        default:
            pRes->m_pCurrentList = &m_lServicedLow;
            pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
            break;
        }

        LeaveCriticalSection(&(g_pChitin->field_2FC));

        EnterCriticalSection(&(g_pChitin->field_32C));
        if (field_270 != NULL) {
            UINT nBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, pRes->nSize, 0)
                : LocalReadResource(pRes, pRes->nSize, 0);
            if (nBytesRead < pRes->nSize) {
                if (field_CE == pRes || field_CE == NULL) {
                    field_CE = pRes;
                    field_D2 = nBytesRead;
                } else {
                    UINT nMoreBytesRead = (nResID & 0xFFF00000) < 0xFC000000
                        ? m_ppResFiles[nResID >> 20]->ReadResource(nResID, pRes->m_pData, pRes->nSize - nBytesRead, 0)
                        : LocalReadResource(pRes, pRes->nSize - nBytesRead, 0);
                    pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                }
            } else {
                if (field_CE == pRes || field_CE == NULL) {
                    field_CE = NULL;
                    field_D2 = nBytesRead;
                    pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x10;
                    pRes->dwFlags |= CRes::Flags::RES_FLAG_0x04;
                }
            }
        }
        LeaveCriticalSection(&(g_pChitin->field_32C));
    } else {
        if (pRes->m_pCurrentList == &m_lRequestedHigh
            || pRes->m_pCurrentList == &m_lRequestedMedium
            || pRes->m_pCurrentList == &m_lRequestedLow) {
            EnterCriticalSection(&(g_pChitin->field_2FC));

            if (field_270 != NULL) {
                if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0) {
                    if (pRes->m_pData != NULL) {
                        if (pRes->m_pCurrentList == &m_lRequestedLow
                            || pRes->m_pCurrentList == &m_lRequestedMedium
                            || pRes->m_pCurrentList == &m_lRequestedLow) {
                            if (pRes->m_pCurrentListPos != NULL && pRes->m_pCurrentList != NULL) {
                                pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                                pRes->m_pCurrentList = NULL;
                                pRes->m_pCurrentListPos = NULL;
                            }

                            switch (pRes->dwFlags & 3) {
                            case PRIORITY_MEDIUM:
                                pRes->m_pCurrentList = &m_lServicedMedium;
                                pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
                                break;
                            case PRIORITY_HIGH:
                                pRes->m_pCurrentList = &m_lServicedHigh;
                                pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
                                break;
                            default:
                                pRes->m_pCurrentList = &m_lServicedLow;
                                pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
                                break;
                            }
                        }
                    }
                }
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));
        }
    }
}

// #binary-identical
// 0x788BE0
void CDimm::SetNewPriority(CRes* pRes, unsigned int nNewPriority)
{
    EnterCriticalSection(&(g_pChitin->field_2FC));

    if (pRes->field_44 > 0) {
        if (nNewPriority != (pRes->dwFlags & 3)) {
            if ((pRes->dwFlags & (CRes::RES_FLAG_0x10 | CRes::RES_FLAG_0x04)) == 0) {
                if (pRes->m_pCurrentListPos != NULL) {
                    if (pRes->m_pCurrentList != NULL) {
                        pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                        pRes->m_pCurrentList = NULL;
                        pRes->m_pCurrentListPos = NULL;
                    }
                }

                switch (nNewPriority) {
                case PRIORITY_HIGH:
                    pRes->m_pCurrentList = &m_lRequestedHigh;
                    pRes->m_pCurrentListPos = m_lRequestedHigh.AddTail(pRes);
                    break;
                case PRIORITY_MEDIUM:
                    pRes->m_pCurrentList = &m_lRequestedMedium;
                    pRes->m_pCurrentListPos = m_lRequestedMedium.AddTail(pRes);
                    break;
                default:
                    pRes->m_pCurrentList = &m_lRequestedLow;
                    pRes->m_pCurrentListPos = m_lRequestedLow.AddTail(pRes);
                    break;
                }
            } else {
                if (pRes->m_pCurrentListPos != NULL) {
                    if (pRes->m_pCurrentList != NULL) {
                        pRes->m_pCurrentList->RemoveAt(pRes->m_pCurrentListPos);
                        pRes->m_pCurrentList = NULL;
                        pRes->m_pCurrentListPos = NULL;
                    }
                }

                switch (nNewPriority) {
                case PRIORITY_HIGH:
                    pRes->m_pCurrentList = &m_lServicedHigh;
                    pRes->m_pCurrentListPos = m_lServicedHigh.AddTail(pRes);
                    break;
                case PRIORITY_MEDIUM:
                    pRes->m_pCurrentList = &m_lServicedMedium;
                    pRes->m_pCurrentListPos = m_lServicedMedium.AddTail(pRes);
                    break;
                default:
                    pRes->m_pCurrentList = &m_lServicedLow;
                    pRes->m_pCurrentListPos = m_lServicedLow.AddTail(pRes);
                    break;
                }
            }
        }
    }

    switch (nNewPriority) {
    case PRIORITY_HIGH:
        pRes->dwFlags &= ~0x1;
        pRes->dwFlags |= 0x2;
        break;
    case PRIORITY_MEDIUM:
        pRes->dwFlags &= ~0x2;
        pRes->dwFlags |= 0x1;
        break;
    default:
        pRes->dwFlags &= ~0x3;
        break;
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));
}

// 0x788CD0
BOOL CDimm::Suspend()
{
    field_E6++;
    if (field_E6 > 0) {
        field_8++;
        field_4 = 1;
    }
    return TRUE;
}

// 0x788CF0
void CDimm::Update()
{
    CRes* pRes = NULL;
    BOOL bContinue = TRUE;
    BOOL bStop = FALSE;

    if (!field_4) {
        field_8++;
        field_4 = 1;

        while (bContinue && !g_pChitin->m_bExitRSThread && !field_0 && !bStop) {
            EnterCriticalSection(&(g_pChitin->field_314));

            DWORD nBytesRead = 0;
            if (field_CE != NULL) {
                field_274 = pRes;
                PartialServiceRequest(field_CE, 310048);
                nBytesRead = field_D2;
            }

            LeaveCriticalSection(&(g_pChitin->field_314));

            EnterCriticalSection(&(g_pChitin->field_2FC));

            if (field_274 == pRes) {
                if (pRes != NULL) {
                    if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                        && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                        pRes->OnResourceServiced();
                        pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                        pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                    }
                }
            }

            while (nBytesRead < 30000 && !g_pChitin->m_bExitRSThread && !field_0 && field_DA < field_D6) {
                if (!m_lRequestedHigh.IsEmpty()) {
                    pRes = static_cast<CRes*>(m_lRequestedHigh.GetHead());
                    field_274 = pRes;
                    LeaveCriticalSection(&(g_pChitin->field_2FC));
                    EnterCriticalSection(&(g_pChitin->field_314));
                    if (field_274 == pRes) {
                        ServiceRequest(pRes, 310048 - nBytesRead);
                    }
                    LeaveCriticalSection(&(g_pChitin->field_314));
                    EnterCriticalSection(&(g_pChitin->field_2FC));
                    nBytesRead += field_D2;
                    if (field_274 == pRes) {
                        if (pRes != NULL) {
                            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                                && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                                pRes->OnResourceServiced();
                                pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                            }
                        }
                    }
                } else if (!m_lRequestedMedium.IsEmpty()) {
                    pRes = static_cast<CRes*>(m_lRequestedMedium.GetHead());
                    field_274 = pRes;
                    LeaveCriticalSection(&(g_pChitin->field_2FC));
                    EnterCriticalSection(&(g_pChitin->field_314));
                    if (field_274 == pRes) {
                        ServiceRequest(pRes, 310048 - nBytesRead);
                    }
                    LeaveCriticalSection(&(g_pChitin->field_314));
                    EnterCriticalSection(&(g_pChitin->field_2FC));
                    nBytesRead += field_D2;
                    if (field_274 == pRes) {
                        if (pRes != NULL) {
                            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                                && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                                pRes->OnResourceServiced();
                                pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                            }
                        }
                    }
                } else if (!m_lRequestedLow.IsEmpty()) {
                    pRes = static_cast<CRes*>(m_lRequestedLow.GetHead());
                    field_274 = pRes;
                    LeaveCriticalSection(&(g_pChitin->field_2FC));
                    EnterCriticalSection(&(g_pChitin->field_314));
                    if (field_274 == pRes) {
                        ServiceRequest(pRes, 310048 - nBytesRead);
                    }
                    LeaveCriticalSection(&(g_pChitin->field_314));
                    EnterCriticalSection(&(g_pChitin->field_2FC));
                    nBytesRead += field_D2;
                    if (field_274 == pRes) {
                        if (pRes != NULL) {
                            if ((pRes->dwFlags & CRes::Flags::RES_FLAG_0x04) != 0
                                && (pRes->dwFlags & (CRes::Flags::RES_FLAG_0x20 | CRes::Flags::RES_FLAG_0x40)) == 0) {
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x20;
                                pRes->OnResourceServiced();
                                pRes->dwFlags &= ~CRes::Flags::RES_FLAG_0x20;
                                pRes->dwFlags |= CRes::Flags::RES_FLAG_0x40;
                            }
                        }
                    }
                } else {
                    bContinue = FALSE;
                    break;
                }
            }

            LeaveCriticalSection(&(g_pChitin->field_2FC));

            if (field_DA > field_D6) {
                ReduceFreedList(1200000);
                if (field_DA > field_D6) {
                    bStop = TRUE;
                }
            }
        }

        field_8--;
        field_4 = 0;
    }
}

// 0x789090
BOOL CDimm::WriteFile(const CString& sDirName, const CString& sFileName, LPVOID lpBuf, DWORD dwSize)
{
    CString v1;
    CString sResolvedFileName;
    CFile cFile;

    char path[MAX_PATH];
    if (_getcwd(path, MAX_PATH) == NULL) {
        return FALSE;
    }

    if (!WriteSetUp(sDirName + sFileName, sResolvedFileName)) {
        return FALSE;
    }

    EnterCriticalSection(&(g_pChitin->field_344));

    BOOL bResult = FALSE;

    DWORD dwAttrs = GetFileAttributesA(sResolvedFileName);
    if (dwAttrs != -1 && (dwAttrs & FILE_ATTRIBUTE_READONLY) != 0) {
        SetFileAttributesA(sResolvedFileName, dwAttrs & ~FILE_ATTRIBUTE_READONLY);
    }

    if (cFile.Open(sResolvedFileName, CFile::OpenFlags::modeCreate | CFile::OpenFlags::typeBinary | CFile::OpenFlags::modeWrite, NULL)) {
        bResult = TRUE;
        cFile.Write(lpBuf, dwSize);
        cFile.Close();
    }

    LeaveCriticalSection(&(g_pChitin->field_344));

    _chdir(path);

    return bResult;
}

// 0x789250
BOOL CDimm::WriteResourceWithData(const CString& sDirName, CRes* pRes, LPVOID lpBuf, DWORD dwSize)
{
    CString sFileName;
    CString sBaseName;
    CString sExtension;

    if (pRes == NULL) {
        return FALSE;
    }

    if (FindDirectoryInDirectoryList(sDirName) == DIMM_NOT_IN_DIRECTORY_LIST) {
        if (!AddToDirectoryList(sDirName, FALSE)) {
            return FALSE;
        }
    }

    RESID nID = (pRes->GetID() & 0xFFFFF) | (~FindDirectoryInDirectoryList(sDirName) << 20);
    CResRef cResRef = pRes->GetResRef();
    USHORT nType = pRes->GetType();

    sBaseName = cResRef.GetResRef();
    g_pChitin->TranslateType(nType, sExtension);
    sFileName = sBaseName + "." + sExtension;

    if (WriteFile(sDirName, sFileName, lpBuf, dwSize) != TRUE) {
        return FALSE;
    }

    if (pRes->m_pDimmKeyTableEntry != NULL && pRes->m_pDimmKeyTableEntry->nID != nID) {
        pRes->m_pDimmKeyTableEntry->nID = nID;

        if (pRes->GetDemands() > 0) {
            pRes->dwFlags |= CRes::RES_FLAG_0x100;
        } else {
            g_pChitin->cDimm.Dump(pRes, 1, 0);
            pRes->SetID(nID);
        }
    }

    return TRUE;
}

// 0x789480
BOOL CDimm::WriteSetUp(const CString& sFileName, CString& sResolvedFileName)
{
    CString sResolvedFileNameTemp;
    CString sDirName;
    CString sTemp;

    char path[MAX_PATH];
    _getcwd(path, MAX_PATH);

    if (!g_pChitin->lAliases.ResolveFileName(sFileName, sResolvedFileNameTemp)) {
        sResolvedFileNameTemp = sFileName;
    }

    INT nSlash = sResolvedFileNameTemp.ReverseFind('\\');
    if (nSlash == -1) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
        // __LINE__: 6809
        UTIL_ASSERT(FALSE);
    }

    sDirName = sResolvedFileNameTemp.Left(nSlash);

    if (_chdir(sDirName) != 0) {
        for (INT nPos = 2; nPos < sDirName.GetLength(); nPos++) {
            if (sDirName[nPos - 1] == '\\'
                && sDirName[nPos - 2] != '\\'
                && sDirName[nPos] != '\\') {
                sTemp = sDirName[nPos - 1];

                if (_chdir(sTemp) != 0) {
                    if (_mkdir(sTemp) != 0) {
                        _chdir(path);
                        return FALSE;
                    }
                }
            }
        }

        // Last path component (without trailing slash).
        if (_mkdir(sDirName) != 0) {
            _chdir(path);
            return FALSE;
        }
    }

    _chdir(path);

    sResolvedFileName = sResolvedFileNameTemp;
    return TRUE;
}

// 0x789710
BOOL CDimm::Alloc(CRes* pRes, DWORD nSize)
{
    POSITION pos;

    EnterCriticalSection(&(g_pChitin->field_2FC));

    if (pRes->m_pData != NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
        // __LINE__: 7095
        UTIL_ASSERT_MSG(pRes != NULL, "Attempting to free invalid resource.");

        free(pRes->m_pData);
        pRes->m_pData = NULL;
        field_DA -= pRes->nSize;
    }

    ReduceFreedList(1200000);

    pos = m_lServicedLow.GetHeadPosition();
    while (field_DA > field_D6 && pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedLow.GetNext(pos));
        if (pRes != NULL) {
            if (pRes->field_40 == 0) {
                if (pRes->OnResourceFreed()) {
                    Dump(pRes, 1, 0);
                    free(pRes);
                } else {
                    Dump(pRes, 0, 0);
                }
            }
        }
    }

    pos = m_lServicedMedium.GetHeadPosition();
    while (field_DA > field_D6 && pos != NULL) {
        CRes* pRes = static_cast<CRes*>(m_lServicedMedium.GetNext(pos));
        if (pRes != NULL) {
            if (pRes->field_40 == 0) {
                if (pRes->OnResourceFreed()) {
                    Dump(pRes, 1, 0);
                    free(pRes);
                } else {
                    Dump(pRes, 0, 0);
                }
            }
        }
    }

    LeaveCriticalSection(&(g_pChitin->field_2FC));

    if (field_DA > field_D6) {
        return FALSE;
    }

    pRes->m_pData = malloc(nSize);
    field_DA += nSize;
    if (pRes->m_pData == NULL) {
        return FALSE;
    }

    if (nSize >= 4) {
        memcpy(reinterpret_cast<BYTE*>(pRes->m_pData) + nSize - 4, "Yuki", 4);
    }

    return TRUE;
}

// 0x790DE0
CString CDimm::GetCDSwitchDriveLetter()
{
    return m_sCDSwitchDriveLetter;
}

// FIXME: `sDrive` should be reference.
//
// 0x5FBE70
void CDimm::SetCDSwitchDriveLetter(CString sDrive)
{
    m_sCDSwitchDriveLetter = sDrive;
}

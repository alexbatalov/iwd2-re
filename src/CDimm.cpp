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
    field_2A4 = 0;
    field_295 = 0;
    field_296 = 0;
    field_297 = 0;

    MEMORYSTATUS memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUS);

    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
    field_DA = 0;
    field_CE = 0;
    field_274 = 0;
    field_270 = 0;
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
    field_294 = 0;
}

// 0x782020
CDimm::~CDimm()
{
    // TODO: Incomplete.
}

// 0x782240
BOOL CDimm::AddToDirectoryList(const CString& sDirName, BOOL a3)
{
    CString v1;
    CString v2;

    if (g_pChitin->lAliases.ResolveFileName(sDirName, v1)) {
        v1 = sDirName;
    }

    int index = 0;
    POSITION pos = m_lDirectories.GetHeadPosition();
    while (pos != NULL) {
        v2 = m_lDirectories.GetAt(pos);
        if (v1.CompareNoCase(v2) == 0) {
            break;
        }

        index++;
        m_lDirectories.GetNext(pos);
    }

    if (index < 64) {
        m_lDirectories.AddTail(v1);
        if (m_cKeyTable.m_bInitialized) {
            if (a3) {
                CString v3;
                if (GetElementInDirectoryList(index, v3) == TRUE) {
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
    pKey->field_C = -1;
    pKey->field_10 = 0;
    pKey->field_12 = -1;
    pKey->field_14 = 0;
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

    if (keyFileHeader.nFileType != 'KEY ') {
        m_cKeyTable.m_bInitialized = FALSE;
        return FALSE;
    }

    if (keyFileHeader.nFileVersion != 'V1  ') {
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

    for (DWORD l = 0;; l++) {
        if (GetElementInDirectoryList(l, v1) != TRUE) {
            break;
        }

        m_cKeyTable.RescanDirectoryNumberAndName(l, v1);
    }

    m_cKeyTable.m_bInitialized = TRUE;

    keyFile.Close();

    cResCache.RefreshStatus(CString(""));

    return TRUE;
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

// 0x785C10
int CDimm::Dump(CRes* pRes, int a2, int a3)
{
    // TODO: Incomplete.

    return 0;
}

// 0x785FB0
int CDimm::DumpAll()
{
    // TODO: Incomplete.

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
BOOL CDimm::GetResFileName(UINT nIndex, CString& sResFileName, USHORT& nResType, BOOLEAN a5)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x786DF0
CRes* CDimm::GetResObject(const CResRef& cResRef, USHORT nResType, BOOLEAN a3)
{
    CDimmKeyTableEntry* pKey = m_cKeyTable.FindKey(cResRef, nResType, a3);
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

    pKey->pRes->SetID(pKey->field_C);
    pKey->pRes->m_pDimmKeyTableEntry = pKey;
    pKey->field_10++;
    return pKey->pRes;
}

// 0x786E50
RESID CDimm::GetResID(CResRef cResRef, USHORT nResType)
{
    CDimmKeyTableEntry* pKey = m_cKeyTable.FindKey(cResRef, nResType, TRUE);
    if (pKey != NULL) {
        return pKey->field_C;
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

// 0x787740
BOOL CDimm::MemoryAlmostFull()
{
    return field_D6 < field_DA + 1200000;
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
                    if (pRes->func_C()) {
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

// 0x787BA0
int CDimm::Release(CRes* pRes)
{
    // TODO: Incomplete.

    return 0;
}

// 0x787CE0
void CDimm::ReleaseResObject(CRes* pRes)
{
    // TODO: Incomplete.
}

// 0x787D30
BOOL CDimm::RemoveFromDirectoryList(const CString& sDirName, BOOL a3)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x787F20
int CDimm::Request(CRes* pRes)
{
    // TODO: Incomplete.

    return 0;
}

//
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

// 0x788BE0
void CDimm::SetNewPriority(CRes* pRes, int nNewPriority)
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.
}

// 0x789250
BOOL CDimm::WriteResourceWithData(const CString& sFileName, CRes* pRes, LPVOID lpBuf, DWORD dwSize)
{
    // TODO: Incomplete.

    return FALSE;
}

BOOL CDimm::WriteSetUp(const CString& a2, CString& a3)
{
    // TODO: Incomplete.

    return FALSE;
}

#include "CResFile.h"

#include "CChitin.h"

// NOTE: Inlined in `CDimm::CreateKeyTable`.
CResFile::CResFile()
{
    m_nIndex = 0;
    m_pHeader = NULL;
    m_pVarEntries = NULL;
    m_pFixedEntries = NULL;
    field_20 = NULL;
    m_bOpen = FALSE;
    field_4 = 0;
    m_nCacheCount = 0;
    m_nRefCount = 0;
    field_38 = 0;
}

// 0x7898F0
CResFile::~CResFile()
{
    if (m_bOpen) {
        CloseFile();
    }
}

// 0x789950
BOOL CResFile::AddCacheCount()
{
    EnterCriticalSection(&(g_pChitin->field_35C));

    while (g_pChitin->cDimm.cResCache.field_110 == 1) {
        LeaveCriticalSection(&(g_pChitin->field_35C));
        while (g_pChitin->cDimm.cResCache.field_110 == 1) {
            SleepEx(50, FALSE);
        }
        EnterCriticalSection(&(g_pChitin->field_35C));
    }

    if (m_nRefCount != 0) {
        LeaveCriticalSection(&(g_pChitin->field_35C));
        return FALSE;
    }

    if (m_nCacheCount == 0) {
        m_nCacheCount = 0;
    }
    m_nCacheCount++;

    g_pChitin->cDimm.cResCache.field_110 = 1;
    LeaveCriticalSection(&(g_pChitin->field_35C));

    return TRUE;
}

// 0x78A080
BOOL CResFile::CloseFile()
{
    if (m_bOpen) {
        if (m_pHeader != NULL) {
            delete m_pHeader;
            m_pHeader = NULL;
        }

        if (m_pVarEntries != NULL) {
            delete m_pVarEntries;
            m_pVarEntries = NULL;
        }

        if (m_pFixedEntries != NULL) {
            delete m_pFixedEntries;
            m_pFixedEntries = NULL;
        }

        if (field_20 != NULL) {
            delete field_20;
            field_20 = NULL;
        }

        m_cFile.Close();
        m_bOpen = FALSE;
        field_38 = 0;
    }

    return TRUE;
}

// #guess
// 0x78A280
DWORD CResFile::GetFileSize(RESID resID)
{
    if (!m_bOpen) {
        return 0;
    }

    if (m_pHeader != NULL) {
        if ((resID & 0xFC000) != 0) {
            UINT nIndex = (resID >> 14) & 0x3F;
            if (nIndex <= m_pHeader->nFixedRes) {
                return m_pFixedEntries[nIndex - 1].nSize;
            }
        } else {
            UINT nIndex = resID & 0x3FFF;
            if (nIndex < m_pHeader->nVarRes) {
                return m_pVarEntries[nIndex].nSize;
            }
        }
    }

    if (field_20 != NULL) {
        // TODO: Object/structure?
        return reinterpret_cast<DWORD>(reinterpret_cast<unsigned char*>(field_20) + 2);
    }

    return 0;
}

// 0x78A2F0
BOOL CResFile::OpenFile()
{
    CString sResFileName;
    WORD nDrive = 0;
    CString sResolvedResFileName;

    if (m_bOpen) {
        CloseFile();
    }

    if (!g_pChitin->cDimm.GetResFileName(m_nIndex, sResFileName, nDrive, FALSE)) {
        return FALSE;
    }

    if (!g_pChitin->lAliases.ResolveFileName(sResFileName, sResolvedResFileName)) {
        sResolvedResFileName = sResFileName;
    }

    if (!m_cFile.Open(sResolvedResFileName, CFile::OpenFlags::typeBinary | CFile::OpenFlags::shareDenyWrite, NULL)) {
        return FALSE;
    }

    m_pHeader = new BIFF_HEADER;
    if (m_pHeader == NULL) {
        m_cFile.Close();
        return FALSE;
    }

    if (m_cFile.Read(m_pHeader, sizeof(BIFF_HEADER)) != sizeof(BIFF_HEADER)) {
        m_cFile.Close();
        delete m_pHeader;
        return FALSE;
    }

    if (memcmp(&(m_pHeader->dwFileType), "BIFF", 4) != 0 || memcmp(&(m_pHeader->dwVersion), "V1  ", 4) != 0) {
        if (memcmp(&(m_pHeader->dwFileType), "BIFC", 4) != 0) {
            m_cFile.Close();
            delete m_pHeader;
            return FALSE;
        }

        CString v34;
        CString v36;
        CString v37;
        CString v35;

        m_cFile.Close();

        v35 = g_pChitin->cDimm.cResCache.m_sDirName;

        if (!g_pChitin->cDimm.m_cKeyTable.m_bInitialized) {
            // NOTE: Leaking `m_pHeader`.
            return FALSE;
        }

        if (m_nIndex >= g_pChitin->cDimm.m_cKeyTable.m_nResFiles) {
            // NOTE: Leaking `m_pHeader`.
            return FALSE;
        }

        v34 = reinterpret_cast<char*>(g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries) + g_pChitin->cDimm.m_cKeyTable.m_pResFileNameEntries[m_nIndex].nFileNameOffset;
        if (!g_pChitin->cDimm.WriteSetUp(v35 + v34, v36)) {
            // NOTE: Leaking `m_pHeader`.
            return FALSE;
        }

        if (!g_pChitin->lAliases.ResolveFileName(sResFileName, sResolvedResFileName)) {
            sResolvedResFileName = sResFileName;
        }

        if (!g_pChitin->cDimm.cResCache.CopyFile(m_nIndex, v34, sResolvedResFileName, v36)) {
            // NOTE: Leaking `m_pHeader`.
            return FALSE;
        }

        sResFileName = v35 + v34;
        if (!g_pChitin->lAliases.ResolveFileName(sResFileName, sResolvedResFileName)) {
            sResolvedResFileName = sResFileName;
        }

        if (!m_cFile.Open(sResolvedResFileName, CFile::OpenFlags::typeBinary | CFile::OpenFlags::shareDenyWrite, NULL)) {
            // NOTE: Leaking `m_pHeader`.
            return FALSE;
        }

        if (m_cFile.Read(m_pHeader, sizeof(BIFF_HEADER)) != sizeof(BIFF_HEADER)) {
            m_cFile.Close();
            delete m_pHeader;
            m_pHeader = NULL;
            return FALSE;
        }
    }

    m_cFile.Seek(m_pHeader->nTableOffset, CFile::SeekPosition::begin);

    if (m_pHeader->nVarRes != 0) {
        m_pVarEntries = new BIFF_VARTABLEENTRY[m_pHeader->nVarRes];
        if (m_pVarEntries == NULL) {
            m_cFile.Close();
            delete m_pHeader;
            return FALSE;
        }

        if (m_cFile.Read(m_pVarEntries, sizeof(BIFF_VARTABLEENTRY) * m_pHeader->nVarRes) < sizeof(BIFF_VARTABLEENTRY) * m_pHeader->nVarRes) {
            m_cFile.Close();
            delete m_pHeader;
            m_pHeader = NULL;
            delete m_pVarEntries;
            m_pVarEntries = NULL;
            return FALSE;
        }
    }

    if (m_pHeader->nFixedRes != 0) {
        m_pFixedEntries = new BIFF_FIXEDTABLEENTRY[m_pHeader->nFixedRes];
        if (m_pFixedEntries == NULL) {
            m_cFile.Close();
            delete m_pHeader;
            m_pHeader = NULL;

            if (m_pVarEntries != NULL) {
                delete m_pVarEntries;
                m_pVarEntries = NULL;
            }

            return FALSE;
        }

        if (m_cFile.Read(m_pFixedEntries, sizeof(BIFF_FIXEDTABLEENTRY) * m_pHeader->nFixedRes) < sizeof(BIFF_FIXEDTABLEENTRY) * m_pHeader->nFixedRes) {
            m_cFile.Close();
            delete m_pHeader;
            m_pHeader = NULL;

            if (m_pVarEntries != NULL) {
                delete m_pVarEntries;
                m_pVarEntries = NULL;
            }

            delete m_pFixedEntries;
            m_pFixedEntries = NULL;

            return FALSE;
        }
    }

    m_bOpen = TRUE;

    if (sResFileName.Left(2).Compare("cd") == 0) {
        field_38 = TRUE;
    }

    return TRUE;
}

// 0x78A7E0
UINT CResFile::ReadResource(RESID resID, LPVOID lpBuf, UINT nCount, UINT nOffset)
{
    if (lpBuf == NULL) {
        return 0;
    }

    if (!m_bOpen) {
        return 0;
    }

    if (m_pHeader != NULL) {
        if ((resID & 0xFC000) != 0) {
            UINT nIndex = (resID >> 14) & 0x3F;
            if (nIndex < m_pHeader->nFixedRes) {
                BIFF_FIXEDTABLEENTRY* pEntry = &(m_pFixedEntries[nIndex]);
                if (nCount > pEntry->nSize) {
                    nCount = pEntry->nSize;
                }

                m_cFile.Seek(nOffset + pEntry->nOffset, CFile::SeekPosition::begin);
                return m_cFile.Read(static_cast<unsigned char*>(lpBuf) + nOffset, nCount);
            }
            return 0;
        } else {
            UINT nIndex = resID & 0x3FFF;
            if (nIndex < m_pHeader->nVarRes) {
                BIFF_VARTABLEENTRY* pEntry = &(m_pVarEntries[nIndex]);
                if (nCount > pEntry->nSize) {
                    nCount = pEntry->nSize;
                }

                m_cFile.Seek(nOffset + pEntry->nOffset, CFile::SeekPosition::begin);
                return m_cFile.Read(static_cast<unsigned char*>(lpBuf) + nOffset, nCount);
            }
            return 0;
        }
    }

    if (field_20 != NULL) {
        m_cFile.Seek(0, CFile::SeekPosition::begin);
        return m_cFile.Read(static_cast<unsigned char*>(lpBuf) + nOffset, nCount);
    }

    return 0;
}

// 0x78A900
void CResFile::UnCache()
{
    EnterCriticalSection(&(g_pChitin->field_35C));

    if (m_nCacheCount > 1) {
        m_nCacheCount -= 1;
    } else {
        m_nCacheCount = 0;
    }

    LeaveCriticalSection(&(g_pChitin->field_35C));

    g_pChitin->cDimm.cResCache.AccessFileInCache(m_nIndex);
}

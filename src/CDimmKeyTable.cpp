#include "CDimmKeyTable.h"

#include "CChitin.h"
#include "CDimm.h"
#include "CRes.h"
#include "CResRef.h"
#include "CUtil.h"

// 0x78AEF0
BOOL CDimmKeyTable::AddKey(CResRef cResRef, USHORT nResType, RESID nID)
{
    BOOL bNotFound = FALSE;
    unsigned int hash = Hash(cResRef, nResType);

    if (cResRef == "") {
        return FALSE;
    }

    // TODO: Refactor, looks ugly.
    int n = static_cast<int>(hash);
    while (1) {
        if (bNotFound) {
            if (!ExtendTable()) {
                return FALSE;
            }

            bNotFound = FALSE;
            hash = Hash(cResRef, nResType);

            if (cResRef == "") {
                return FALSE;
            }
        }

        if (m_pEntries[n].resRef == "") {
            break;
        }

        if (m_pEntries[n].resRef == cResRef && m_pEntries[n].nResType == nResType) {
            break;
        }

        n++;
        if (n >= m_nEntries) {
            n = 0;
        }

        if (n == hash) {
            bNotFound = TRUE;
        }
    }

    if (m_pEntries[n].nID != nID) {
        if (m_pEntries[n].resRef != "") {
            m_pEntries[n].nID = nID;
            if (m_bInitialized == TRUE) {
                if (m_pEntries[n].pRes != NULL) {
                    if (m_pEntries[n].pRes->GetDemands() > 0) {
                        m_pEntries[n].pRes->dwFlags |= CRes::Flags::RES_FLAG_0x100;
                    } else {
                        g_pChitin->cDimm.Dump(m_pEntries[n].pRes, 1, 0);
                        m_pEntries[n].pRes->SetID(nID);
                    }
                }
            }
        }
    }

    m_pEntries[n].nID = nID;
    m_pEntries[n].resRef = cResRef;
    m_pEntries[n].nResType = nResType;
    m_pEntries[n].bUpdated = TRUE;

    return TRUE;
}

// 0x78B0C0
BOOL CDimmKeyTable::BuildNewTable(int nLength)
{
    m_nNewEntries = nLength;

    if (nLength <= 0) {
        return FALSE;
    }

    m_pNewEntries = new CDimmKeyTableEntry[nLength];
    if (m_pNewEntries == NULL) {
        m_nNewEntries = 0;
        return FALSE;
    }

    for (int k = 0; k < m_nNewEntries; k++) {
        CDimmKeyTableEntry* pEntry = &(m_pNewEntries[k]);
        if (pEntry != NULL) {
            pEntry->resRef = "";
            pEntry->pRes = NULL;
            pEntry->nID = -1;
            pEntry->field_10 = 0;
            pEntry->nResType = -1;
            pEntry->bUpdated = FALSE;
        }
    }

    return TRUE;
}

// 0x78B190
void CDimmKeyTable::DestroyTable(CDimm* dimm)
{
    if (m_pEntries != NULL && m_nEntries > 0) {
        for (int k = 0; k < m_nEntries; k++) {
            CDimmKeyTableEntry* pEntry = &(m_pEntries[k]);
            if (pEntry != NULL) {
                pEntry->resRef = "";

                if (pEntry->pRes != NULL) {
                    dimm->Dump(pEntry->pRes, 1, 0);
                    pEntry->pRes->m_pDimmKeyTableEntry = 0;
                    delete pEntry->pRes;
                }

                pEntry->nID = -1;
                pEntry->field_10 = 0;
                pEntry->nResType = -1;
            }
        }

        delete m_pEntries;
        m_pEntries = NULL;
        m_nEntries = 0;
    }
}

// 0x78B260
BOOL CDimmKeyTable::ExtendTable()
{
    if (m_pEntries == NULL) {
        return FALSE;
    }

    if (m_nEntries <= 0) {
        return FALSE;
    }

    if (!BuildNewTable(m_nEntries + 128)) {
        return FALSE;
    }

    int length = m_nEntries;

    for (int k = 0; k < length; k++) {
        CDimmKeyTableEntry* pEntry = &(m_pEntries[k]);
        if (pEntry != NULL) {
            m_nEntries = m_nNewEntries;

            unsigned int hash = Hash(pEntry->resRef, pEntry->nResType);
            m_nEntries = length;

            BOOL bFull = FALSE;
            int n = static_cast<int>(hash);
            while (1) {
                // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
                // __LINE__: 9446
                UTIL_ASSERT(bFull == FALSE);

                if (m_pNewEntries[n].resRef == "") {
                    break;
                }

                n++;
                if (n >= m_nNewEntries) {
                    n = 0;
                }

                if (n == hash) {
                    bFull = TRUE;
                }
            }

            m_pNewEntries[n] = m_pEntries[k];

            if (m_pNewEntries[n].pRes != NULL) {
                if (m_pNewEntries[n].pRes->m_pDimmKeyTableEntry != NULL) {
                    m_pNewEntries[n].pRes->m_pDimmKeyTableEntry = &(m_pNewEntries[n]);
                }
            }
        }
    }

    delete m_pEntries;

    m_pEntries = m_pNewEntries;
    m_nEntries = m_nNewEntries;
    m_pNewEntries = NULL;
    m_nNewEntries = 0;

    return TRUE;
}

// 0x78B410
CDimmKeyTableEntry* CDimmKeyTable::FindKey(const CResRef& resRef, USHORT nResType, BOOL bWarningIfMissing)
{
    BOOL done = FALSE;

    if (resRef == "") {
        return NULL;
    }

    unsigned int hash = Hash(resRef, nResType);
    int k = hash;

    while (!done) {
        if (m_pEntries[k].nResType == nResType && m_pEntries[k].resRef == resRef) {
            return &(m_pEntries[k]);
        }

        if (m_pEntries[k].resRef == "") {
            if (bWarningIfMissing) {
                // TODO: Some kind of unused error logging code.
            }
            return NULL;
        }

        k++;
        if (k >= m_nEntries) {
            k = 0;
        }

        if (k == hash) {
            done = TRUE;
        }
    }

    return FALSE;
}

// 0x78B650
unsigned int CDimmKeyTable::Hash(const CResRef& a2, int a3)
{
    unsigned int v1 = 1;
    unsigned int v2 = 27 * a3;

    for (int k = 0; k < 8; k++) {
        if (a2.GetAt(k) == '\0') {
            break;
        }

        unsigned int v3 = a2.GetAt(k) % 47;
        switch (k) {
        case 1:
            v3 <<= 3;
            break;
        case 2:
            v3 <<= 6;
            break;
        case 3:
            v3 <<= 9;
            break;
        case 4:
            v3 <<= 12;
            break;
        case 5:
            v3 <<= 15;
            break;
        case 6:
            v3 <<= 18;
            break;
        case 7:
            v3 <<= 21;
            break;
        default:
            break;
        }

        v2 += v3;
        v1 *= v3 % m_nEntries;
    }
    return (v1 + v2) % m_nEntries;
}

// 0x78B6F0
void CDimmKeyTable::RemoveNonUpdatedEntries()
{
    if (m_pEntries != NULL) {
        for (int index = 0; index < m_nEntries; index++) {
            CDimmKeyTableEntry* pEntry = &(m_pEntries[index]);
            if (pEntry != NULL) {
                if (!pEntry->bUpdated) {
                    if (pEntry->pRes != NULL) {
                        pEntry->nID = -1;
                        if (pEntry->pRes->GetDemands() > 0) {
                            pEntry->pRes->dwFlags |= CRes::Flags::RES_FLAG_0x100;
                        } else {
                            g_pChitin->cDimm.Dump(pEntry->pRes, 1, 0);
                            pEntry->pRes->SetID(-1);
                        }
                    }
                }
            }
        }
    }
}

// 0x78B780
void CDimmKeyTable::RescanDirectoryNumberAndName(int nDirNumber, const CString& sDirName)
{
    CString sPattern = sDirName + "*.*";

    WIN32_FIND_DATAA findFileData;
    HANDLE hFindFile = FindFirstFileA(sPattern, &findFileData);
    if (hFindFile != INVALID_HANDLE_VALUE) {
        do {
            if ((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY) {
                size_t pos = 0;
                while (pos < 32 && findFileData.cFileName[pos] != '\0') {
                    pos++;
                }

                while (pos > 1 && findFileData.cFileName[pos] != '.') {
                    pos--;
                }

                int nType = g_pChitin->TranslateType(CString(&(findFileData.cFileName[pos + 1])));

                // FIXME: Probably wrong, `TranslateType` returns -1 to indicate
                // error.
                if (nType != 0) {
                    char temp[RESREF_SIZE] = { 0 };
                    memcpy(temp, findFileData.cFileName, min(pos, RESREF_SIZE));
                    AddKey(CResRef(temp), nType, (~nDirNumber) << 20);
                }
            }
        } while (FindNextFileA(hFindFile, &findFileData));
        FindClose(hFindFile);
    }
}

// 0x78B940
BOOL CDimmKeyTable::RescanEverything()
{
    CFile keyFile;
    CString v1;
    CResRef resRef;

    if (m_pEntries != NULL) {
        for (int index = 0; index < m_nEntries; index++) {
            CDimmKeyTableEntry* entry = &(m_pEntries[index]);
            if (entry != NULL) {
                entry->bUpdated = FALSE;
            }
        }
    }

    if (!keyFile.Open(g_pChitin->GetKeyFileName(), CFile::OpenFlags::modeRead)) {
        return FALSE;
    }

    KEYFILE_HEADER keyFileHeader;
    if (!keyFile.Read(&keyFileHeader, sizeof(keyFileHeader))) {
        return FALSE;
    }

    if (memcmp(&(keyFileHeader.nFileType), "KEY ", 4) != 0) {
        return FALSE;
    }

    if (memcmp(&(keyFileHeader.nFileVersion), "V1  ", 4) != 0) {
        return FALSE;
    }

    if (keyFileHeader.nResFiles == 0 && keyFileHeader.nKeys == 0) {
        return FALSE;
    }

    keyFile.Seek(keyFileHeader.nOffsetToKeyTable, CFile::SeekPosition::begin);

    for (DWORD index = 0; index < keyFileHeader.nKeys; index++) {
        KEYFILE_KEYENTRY keyEntry;
        keyFile.Read(&keyEntry, sizeof(keyEntry));
        AddKey(CResRef(keyEntry.resRef), keyEntry.nType, keyEntry.nID);
    }

    for (int nDirNumber = 0; g_pChitin->cDimm.GetElementInDirectoryList(nDirNumber, v1) == TRUE; nDirNumber++) {
        // FIXME: Should be outside of the loop.
        CString sDirName;
        if (g_pChitin->cDimm.GetElementInDirectoryList(nDirNumber, sDirName) == TRUE) {
            RescanDirectoryNumberAndName(nDirNumber, sDirName);
        }
    }

    m_bInitialized = TRUE;
    keyFile.Close();
    RemoveNonUpdatedEntries();

    return TRUE;
}

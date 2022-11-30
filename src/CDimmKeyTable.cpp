#include "CDimmKeyTable.h"

#include "CChitin.h"
#include "CDimm.h"
#include "CRes.h"
#include "CResRef.h"
#include "CUtil.h"

// 0x78AEF0
BOOL CDimmKeyTable::AddKey(CResRef cResRef, USHORT nResType, RESID nID)
{
    BOOL v1 = FALSE;
    unsigned int hash = Hash(cResRef, nResType);

    if (cResRef == "") {
        return FALSE;
    }

    int n = static_cast<int>(hash);
    while (1) {
        while (v1) {
            if (ExtendTable()) {
                v1 = FALSE;
                hash = Hash(cResRef, nResType);
            }
        }
    }

    // TODO: Incomplete.
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
            pEntry->field_C = -1;
            pEntry->field_10 = 0;
            pEntry->field_12 = -1;
            pEntry->field_14 = 0;
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

                pEntry->field_C = -1;
                pEntry->field_10 = 0;
                pEntry->field_12 = -1;
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

            unsigned int hash = Hash(pEntry->resRef, pEntry->field_12);
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
CDimmKeyTableEntry* CDimmKeyTable::FindKey(const CResRef& resRef, USHORT nResType, BOOL a4)
{
    BOOL done = FALSE;

    if (resRef == "") {
        return NULL;
    }

    unsigned int hash = Hash(resRef, nResType);
    int k = hash;

    while (!done) {
        if (m_pEntries[k].field_12 == nResType && m_pEntries[k].resRef == resRef) {
            return &(m_pEntries[k]);
        }

        if (m_pEntries[k].resRef == "") {
            if (a4) {
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
    if (m_pEntries != NULL && m_nEntries > 0) {
        for (int k = 0; k < m_nEntries; k++) {
            CDimmKeyTableEntry* pEntry = &(m_pEntries[k]);
            if (pEntry != NULL) {
                if (!pEntry->field_14) {
                    if (pEntry->pRes != NULL) {
                        pEntry->field_C = -1;
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
    // TODO: Incomplete.
}

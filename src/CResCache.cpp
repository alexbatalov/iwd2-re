#include "CResCache.h"

#include <direct.h>

#include "CChitin.h"

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

// 0x78C020
CResCache::~CResCache()
{
    EnterCriticalSection(&criticalSection);

    // TODO: Incomplete.

    LeaveCriticalSection(&criticalSection);
    DeleteCriticalSection(&criticalSection);
}

// 0x78C130
void CResCache::AccessFileInCache(UINT nIndex)
{
    // TODO: Incomplete.
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

// 0x78D090
BOOL CResCache::RefreshStatus(const CString& a2)
{
    // TODO: Incomplete.

    return FALSE;
}

#include "CTlkFileOverride.h"

#include "CTlkTable.h"

// #binary-identical
// 0x7B5CA0
CTlkFileOverrideHeader::CTlkFileOverrideHeader()
{
    memset(&field_1A, 0, sizeof(field_1A));

    field_10 = 0;

    m_nEntryCount = 60;
    m_ppEntries = new Entry*[m_nEntryCount];

    for (int k = 0; k < m_nEntryCount; k++) {
        m_ppEntries[k] = 0;
    }
}

// #binary-identical
// 0x7B5D50
CTlkFileOverrideHeader::~CTlkFileOverrideHeader()
{
    if (m_ppEntries != NULL) {
        for (int k = 0; k < m_nEntryCount; k++) {
            if (m_ppEntries[k] != NULL) {
                delete m_ppEntries[k];
            }
        }

        delete m_ppEntries;
        m_ppEntries = NULL;
    }
}

// 0x7B5690
BOOLEAN CTlkFileOverride::Fetch(DWORD strId, STR_RES& strRes)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7B5A00
void CTlkFileOverride::Remove(DWORD strId)
{
    // TODO: Incomplete.
}

// 0x7B5A50
BOOL CTlkFileOverride::Open(const CString& a1, const CString& a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7B5C30
void CTlkFileOverride::CloseFiles()
{
    // TODO: Incomplete.
}

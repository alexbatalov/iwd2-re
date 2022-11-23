#include "CTlkFileOverride.h"

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

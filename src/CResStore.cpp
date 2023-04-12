#include "CResStore.h"

// 0x402660
CResStore::CResStore()
{
    m_bParsed = FALSE;
}

// 0x4026A0
CResStore::~CResStore()
{
}

// 0x4026B0
void* CResStore::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        // NOTE: Uninline.
        Parse(pData);

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// NOTE: Inlined in `CResStore::Demand`.
BOOL CResStore::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    DWORD* header = reinterpret_cast<DWORD*>(pData);
    if ((header[0] != 'STOR' && header[0] != 'STOO') || header[1] != 'V9.0') {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

#include "CResWorldMap.h"

// 0x4027B0
CResWorldMap::CResWorldMap()
{
    m_bParsed = FALSE;
}

// 0x4027F0
CResWorldMap::~CResWorldMap()
{
}

// 0x402800
void* CResWorldMap::Demand()
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

// NOTE: Inlined in `CResWorldMap::Demand`.
BOOL CResWorldMap::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    DWORD* header = reinterpret_cast<DWORD*>(pData);
    if (header[0] != 'WMAP' || header[1] != 'V1.0') {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

#include "CResDLG.h"

// 0x402710
CResDLG::CResDLG()
{
    m_bParsed = FALSE;
}

// 0x402750
CResDLG::~CResDLG()
{
}

// 0x402760
void* CResDLG::Demand()
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

// NOTE: Inlined in `CResDLG::Demand`.
BOOL CResDLG::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    DWORD* header = reinterpret_cast<DWORD*>(pData);
    if (header[0] != 'DLG ' || header[1] != 'V1.0') {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

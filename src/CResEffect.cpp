#include "CResEffect.h"

// 0x402850
CResEffect::CResEffect()
{
    m_bParsed = FALSE;
}

// 0x402890
CResEffect::~CResEffect()
{
}

// 0x4028A0
void* CResEffect::Demand()
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

// NOTE: Inlined in `CResEffect::Demand`.
BOOL CResEffect::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    DWORD* header = reinterpret_cast<DWORD*>(pData);
    if (header[0] != 'EFF ' || header[1] != 'V2.0') {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

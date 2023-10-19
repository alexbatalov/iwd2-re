#include "CResINI.h"

// NOTE: Inlined.
CResINI::CResINI()
{
    m_bParsed = FALSE;
}

// NOTE: Inlined.
CResINI::~CResINI()
{
}

// 0x4029B0
void* CResINI::Demand()
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

// NOTE: Inlined.
BOOL CResINI::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

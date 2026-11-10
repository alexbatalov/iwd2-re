#include "CResBIO.h"

// NOTE: Inlined in `CBaldurChitin::AllocResObject`.
CResBIO::CResBIO()
{
    m_bParsed = FALSE;
}

// 0x423790
CResBIO::~CResBIO()
{
}

// 0x4029F0
void* CResBIO::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        if (pData != NULL) {
            m_bParsed = TRUE;
        }

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x4022B0
int CResBIO::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
    }
    return rc;
}

#include "CResArea.h"

// 0x4024E0
CResArea::CResArea()
{
    m_bParsed = FALSE;
}

// 0x402520
CResArea::~CResArea()
{
}

// 0x402530
void* CResArea::Demand()
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

// NOTE: Inlined in `CResArea::Demand`.
BOOL CResArea::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    AREA_HEADER* header = reinterpret_cast<AREA_HEADER*>(pData);
    if (memcmp(&(header->nFileType), "AREA", 4) != 0
        || memcmp(&(header->nFileVersion), "V9.1", 4) != 0) {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

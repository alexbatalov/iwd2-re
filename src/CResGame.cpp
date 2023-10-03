#include "CResGame.h"

// 0x402580
CResGame::CResGame()
{
    m_bParsed = FALSE;
}

// 0x4025C0
CResGame::~CResGame()
{
}

// 0x4025D0
void* CResGame::Demand()
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

// NOTE: Inlined in `CResGame::Demand`.
BOOL CResGame::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    if (memcmp(pData, "GAME", 4) != 0
        || (memcmp(pData, "GAMEV2.2", 8) != 0
            && memcmp(pData, "GAMEV2.1", 8) != 0
            && memcmp(pData, "GAMEV2.0", 8) != 0
            && memcmp(pData, "GAMEV9.1", 8) != 0)) {
        return FALSE;
    }

    m_bParsed = TRUE;

    return m_bParsed;
}

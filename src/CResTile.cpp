#include "CResTile.h"

// 0x780650
CResTile::CResTile()
{
    m_bParsed = FALSE;
    m_pTileData = NULL;
    field_50 = NULL;
}

// 0x7806D0
CResTile::~CResTile()
{
    m_bParsed = FALSE;
    m_pTileData = NULL;
    field_50 = NULL;
}

// 0x780750
int CResTile::GetFixedResourceDataOffset()
{
    return 24;
}

// 0x780760
int CResTile::GetFixedResourceSize()
{
    return 5120;
}

void* CResTile::GetTileData()
{
    if (m_bParsed) {
        return m_pTileData;
    }

    return NULL;
}

// 0x780780
int CResTile::GetTileSize()
{
    return 64;
}

// 0x780790
void* CResTile::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        Parse(pData);

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x7807D0
int CResTile::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pTileData = NULL;
        field_50 = NULL;
    }
    return rc;
}

// 0x5CBD40
CResRef CResTile::GetResRef()
{
    return field_58;
}

// 0x5CBD60
USHORT CResTile::GetType()
{
    return 1003;
}

// NOTE: Inlined in `CResTile::Demand`.
BOOL CResTile::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    field_50 = pData;
    m_pTileData = reinterpret_cast<unsigned char*>(pData) + 1024;

    m_bParsed = TRUE;

    return m_bParsed;
}

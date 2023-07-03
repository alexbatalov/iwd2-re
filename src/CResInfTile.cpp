#include "CResInfTile.h"

// 0x5CBC80
CResInfTile::CResInfTile(BOOLEAN a1, BOOLEAN a2)
{
    m_nVRamTile = -1;

    // TODO: Wrong.
    m_nVRamFlags = 0;

    field_68 = 0;

    if (a1) {
        m_pDualTileRes = new CResTile();
    } else {
        m_pDualTileRes = NULL;
    }

    dwFlags &= 0x2;
    dwFlags |= 0x1;
}

// 0x5CBD90
CResInfTile::~CResInfTile()
{
    if (m_pDualTileRes != NULL) {
        delete m_pDualTileRes;
    }
}

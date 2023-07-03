#include "CVRamPool.h"

#include "CInfTileSet.h"
#include "CResInfTile.h"
#include "CVidInf.h"

// 0x5CBDF0
CVRamPool::CVRamPool()
{
    m_nVTiles = 0;
    m_pTileDefs = NULL;
    m_pSurfaces = NULL;
}

// 0x5CBE00
CVRamPool::~CVRamPool()
{
    // NOTE: Uninline.
    DetachSurfaces();
}

// 0x5CBE70
BOOL CVRamPool::AttachSurfaces(CVidMode* pVidMode)
{
    if (pVidMode->GetType() != 0) {
        return FALSE;
    }

    if (pVidMode == NULL) {
        return FALSE;
    }

    CVidInf* pVidInf = static_cast<CVidInf*>(pVidMode);

    if (pVidInf->m_nVRamSurfaces <= 0) {
        return FALSE;
    }

    if (!g_pChitin->cVideo.Is3dAccelerated() && pVidInf->m_pVRamSurfaces == NULL) {
        return FALSE;
    }

    m_pSurfaces = pVidInf->m_pVRamSurfaces;
    m_nVTiles = pVidInf->m_nVRamSurfaces;
    m_pTileDefs = reinterpret_cast<TileDefinition*>(malloc(sizeof(TileDefinition) * m_nVTiles));

    for (int index = 0; index < m_nVTiles; index++) {
        m_pTileDefs[index].nTile = -1;
        m_pTileDefs[index].pTileSet = NULL;
        m_pTileDefs[index].nRefCount = 0;
    }

    return TRUE;
}

// 0x5CBF30
void CVRamPool::ClearAll()
{
    for (int index = 0; index < m_nVTiles; index++) {
        if (m_pTileDefs[index].pTileSet != NULL) {
            m_pTileDefs[index].pTileSet->m_pResTiles[m_pTileDefs[index].nTile]->m_nVRamTile = -1;
        }

        m_pTileDefs[index].nTile = -1;
        m_pTileDefs[index].pTileSet = NULL;
        m_pTileDefs[index].nRefCount = 0;
    }
}

// 0x5CBF90
BOOL CVRamPool::DetachSurfaces()
{
    // NOTE: Uninline.
    ClearAll();

    if (m_pTileDefs != NULL) {
        free(m_pTileDefs);
        m_pTileDefs = NULL;
    }

    m_pSurfaces = NULL;
    m_nVTiles = 0;

    return TRUE;
}

// 0x5CC010
void CVRamPool::InvalidateAll()
{
    for (int index = 0; index < m_nVTiles; index++) {
        if (m_pTileDefs[index].pTileSet != NULL) {
            m_pTileDefs[index].pTileSet->m_pResTiles[m_pTileDefs[index].nTile]->m_nVRamFlags &= ~0x2;
        }
    }
}

// NOTE: Inlined.
int CVRamPool::AssociateTile(CInfTileSet* pTileSet, int nTile)
{
    if (pTileSet != NULL) {
        for (int index = 0; index < m_nVTiles; index++) {
            if (m_pTileDefs[index].nTile == -1) {
                m_pTileDefs[index].nTile = nTile;
                m_pTileDefs[index].pTileSet = pTileSet;
                m_pTileDefs[index].nRefCount = 1;
                pTileSet->m_pResTiles[nTile]->m_nVRamTile = index;
                return index;
            }
        }
    }

    return -1;
}

// NOTE: Inlined.
BOOL CVRamPool::EmptyTile(int nVTile)
{
    if (nVTile < 0 || nVTile >= m_nVTiles) {
        return FALSE;
    }

    TileDefinition* pTileDef = &(m_pTileDefs[nVTile]);

    if (pTileDef->pTileSet != NULL) {
        pTileDef->pTileSet->m_pResTiles[pTileDef->nTile]->m_nVRamTile = -1;
    }

    pTileDef->nTile = -1;
    pTileDef->pTileSet = NULL;
    pTileDef->nRefCount = 0;

    return TRUE;
}

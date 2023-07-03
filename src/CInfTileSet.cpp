#include "CInfTileSet.h"

#include "CChitin.h"
#include "CResInfTile.h"
#include "CVRamPool.h"

// 0x5CAF50
CInfTileSet::~CInfTileSet()
{
    if (m_pResTiles != NULL) {
        for (int index = 0; index < m_nTiles; index++) {
            CResInfTile* pTile = m_pResTiles[index];
            if (pTile != NULL) {
                // NOTE: Uninline.
                m_pVRamPool->EmptyTile(pTile->m_nVRamTile);

                g_pChitin->cDimm.Dump(m_pResTiles[index], 1, 0);

                if (m_pResTiles[index] != NULL) {
                    delete m_pResTiles[index];
                    m_pResTiles[index] = NULL;
                }
            }

            if (index % 700 == 699) {
                SleepEx(60, FALSE);
            }
        }

        free(m_pResTiles);
    }

    m_nTiles = 0;
}

// 0x5CB090
int CInfTileSet::AttachToVRam(int nTile)
{
    if (m_pVRamPool == NULL) {
        return -1;
    }

    if (nTile < 0 || nTile >= m_nTiles) {
        return -1;
    }

    CResInfTile* pTile = m_pResTiles[nTile];
    if (pTile == NULL) {
        return -1;
    }

    if (pTile->m_nVRamTile < 0) {
        int nVRamTile = m_pVRamPool->AssociateTile(this, nTile);
        m_pResTiles[nTile]->m_nVRamFlags &= 0x2;
        if (nVRamTile == -1) {
            return 0;
        }
    } else {
        m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount++;
    }

    return m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount;
}

// 0x5CB190
int CInfTileSet::DetachFromVRam(int nTile)
{
    if (m_pVRamPool == NULL) {
        return -1;
    }

    if (nTile < 0 || nTile >= m_nTiles) {
        return -1;
    }

    CResInfTile* pTile = m_pResTiles[nTile];
    if (pTile == NULL) {
        return -1;
    }

    if (pTile->m_nVRamTile < 0) {
        return -1;
    }

    m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount--;

    if (m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount > 0) {
        return m_pVRamPool->m_pTileDefs[pTile->m_nVRamTile].nRefCount;
    }

    m_pVRamPool->EmptyTile(pTile->m_nVRamTile);

    return 0;
}

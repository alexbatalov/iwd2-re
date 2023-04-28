#include "CResMosaic.h"

// #binary-identical
// 0x780240
CResMosaic::CResMosaic()
{
    m_bParsed = FALSE;
    m_pTileData = NULL;
    m_pHeader = NULL;
    m_pPalettes = NULL;
    m_pOffsets = NULL;
    field_18 = 1;
}

// 0x780290
CResMosaic::~CResMosaic()
{
}

// 0x780310
WORD CResMosaic::GetMosaicWidth(BOOL bDoubleSize)
{
    if (bDoubleSize) {
        return 2 * m_pHeader->nWidth;
    }

    return m_pHeader->nWidth;
}

// 0x780340
WORD CResMosaic::GetMosaicHeight(BOOL bDoubleSize)
{
    if (bDoubleSize) {
        return 2 * m_pHeader->nHeight;
    }

    return m_pHeader->nHeight;
}

// 0x780340
WORD CResMosaic::GetTileSize(BOOL bDoubleSize)
{
    if (bDoubleSize) {
        return 2 * m_pHeader->nTileSize;
    }

    return m_pHeader->nTileSize;
}

// 0x7803A0
BYTE* CResMosaic::GetTileData(UINT nTile, BOOL bDoubleSize)
{
    if (nTile >= m_pHeader->nXTiles * m_pHeader->nYTiles) {
        return NULL;
    }

    if (!bDoubleSize) {
        return m_pTileData + m_pOffsets[nTile];
    }

    if (m_pDimmKeyTableEntry->resRef == g_pChitin->cVideo.field_114
        && m_pDimmKeyTableEntry->nResType == g_pChitin->cVideo.field_11C
        && nTile == g_pChitin->cVideo.field_11E) {
        return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
    }

    g_pChitin->cVideo.field_114 = m_pDimmKeyTableEntry->resRef;
    g_pChitin->cVideo.field_11C = m_pDimmKeyTableEntry->nResType;
    g_pChitin->cVideo.field_11E = nTile;
    g_pChitin->cVideo.SetDoubleSizeData(4 * m_pHeader->nTileSize * m_pHeader->nTileSize);

    BYTE* pTileData = m_pTileData + m_pOffsets[nTile];
    BYTE* pDoubleSizeTileData = reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);

    WORD nTileWidth = m_pHeader->nWidth - m_pHeader->nTileSize * (nTile % m_pHeader->nXTiles);
    if (nTileWidth >= m_pHeader->nTileSize) {
        nTileWidth = m_pHeader->nTileSize;
    }

    WORD nTileHeight = m_pHeader->nHeight - m_pHeader->nTileSize * (nTile / m_pHeader->nXTiles);
    if (nTileHeight >= m_pHeader->nTileSize) {
        nTileHeight = m_pHeader->nTileSize;
    }

    WORD nOffset = 2 * nTileWidth;
    for (WORD y = 0; y < nTileHeight; y++) {
        for (WORD x = 0; x < nTileWidth; x++) {
            BYTE byte = *pTileData++;
            pDoubleSizeTileData[0] = byte;
            pDoubleSizeTileData[nOffset] = byte;
            pDoubleSizeTileData[1] = byte;
            pDoubleSizeTileData[nOffset] = byte;
            pDoubleSizeTileData += 2;
        }
    }

    return reinterpret_cast<BYTE*>(g_pChitin->cVideo.m_doubleSizeData);
}

// 0x780530
RGBQUAD* CResMosaic::GetTilePalette(UINT nTile)
{
    if (nTile < m_pHeader->nXTiles * m_pHeader->nYTiles) {
        return &(m_pPalettes[nTile * 256]);
    }

    return NULL;
}

// 0x780560
void* CResMosaic::Demand()
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

// 0x7805A0
int CResMosaic::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pHeader = NULL;
        m_pPalettes = NULL;
        m_pOffsets = NULL;
    }
    return rc;
}

// 0x7805D0
BOOL CResMosaic::Parse(void* pData)
{
    if (pData == NULL) {
        return FALSE;
    }

    m_pHeader = reinterpret_cast<MOSAICHEADER*>(pData);
    if (memcmp(&(m_pHeader->nFileType), "MOS ", 4) != 0) {
        return FALSE;
    }

    if (memcmp(&(m_pHeader->nFileVersion), "V1  ", 4) != 0) {
        return FALSE;
    }

    m_pPalettes = reinterpret_cast<RGBQUAD*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nPaletteOffset);
    m_pOffsets = reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(m_pPalettes) + sizeof(RGBQUAD) * 256 * m_pHeader->nXTiles * m_pHeader->nYTiles);
    m_pTileData = reinterpret_cast<BYTE*>(reinterpret_cast<unsigned char*>(m_pOffsets) + sizeof(DWORD) * m_pHeader->nXTiles * m_pHeader->nYTiles);

    m_bParsed = TRUE;

    return m_bParsed;
}

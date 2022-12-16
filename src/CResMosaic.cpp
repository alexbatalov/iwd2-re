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
WORD CResMosaic::GetMosaicWidth(BOOL a2)
{
    if (a2) {
        return 2 * m_pHeader->nWidth;
    }

    return m_pHeader->nWidth;
}

// 0x780340
WORD CResMosaic::GetMosaicHeight(BOOL a2)
{
    if (a2) {
        return 2 * m_pHeader->nHeight;
    }

    return m_pHeader->nHeight;
}

// 0x780340
WORD CResMosaic::GetTileSize(BOOL a2)
{
    if (a2) {
        return 2 * m_pHeader->nTileSize;
    }

    return m_pHeader->nTileSize;
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
    if (m_pHeader->nFileType != 'MOS ') {
        return FALSE;
    }

    if (m_pHeader->nFileVersion != 'V1  ') {
        return FALSE;
    }

    m_pPalettes = reinterpret_cast<RGBQUAD*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nPaletteOffset);
    m_pOffsets = reinterpret_cast<DWORD*>(reinterpret_cast<unsigned char*>(pData) + 1024 * m_pHeader->nXTiles * m_pHeader->nYTiles);
    m_pTileData = reinterpret_cast<BYTE*>(reinterpret_cast<unsigned char*>(m_pOffsets) + 4 * m_pHeader->nXTiles * m_pHeader->nYTiles);

    m_bParsed = TRUE;

    return m_bParsed;
}

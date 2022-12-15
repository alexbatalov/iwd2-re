#include "CResWED.h"

// 0x401090
CResWED::CResWED()
{
    m_bParsed = FALSE;
    m_pHeader = NULL;
    m_pLayers = NULL;
    m_pPolyHeader = NULL;
    m_pPolyList = NULL;
    m_pPolyPoints = NULL;
    m_pScreenSectionList = NULL;
}

// #binary-identical
// 0x4010F0
CResWED::~CResWED()
{
    m_bParsed = FALSE;
    m_pHeader = NULL;
    m_pLayers = NULL;
    m_pPolyHeader = NULL;
    m_pPolyList = NULL;
    m_pPolyPoints = NULL;
}

// #binary-identical
// 0x401110
void* CResWED::Demand()
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

// 0x401150
ULONG CResWED::GetNumTiledObjects()
{
    if (m_bParsed) {
        return m_pHeader->nTiledObjects;
    }

    return 0;
}

// 0x401170
WORD* CResWED::GetScreenPolyData()
{
    if (m_bParsed) {
        if (m_pPolyHeader != NULL) {
            return reinterpret_cast<WORD*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pPolyHeader->nOffsetToScreenPolyList);
        }
    }

    return NULL;
}

// 0x401190
WED_LAYERHEADER* CResWED::GetLayerHeader(UINT nLayer)
{
    if (m_bParsed) {
        if (nLayer < m_pHeader->nLayers) {
            return &(m_pLayers[nLayer]);
        }
    }

    return NULL;
}

// 0x4011C0
WED_TILEDATA* CResWED::GetTileData(UINT nLayer, int nXTile, int nYTile)
{
    if (m_bParsed) {
        if (nLayer < m_pHeader->nLayers) {
            if (nXTile >= 0 && nXTile < m_pLayers[nLayer].nTilesAcross && nYTile >= 0 && nYTile < m_pLayers[nLayer].nTilesDown) {
                return reinterpret_cast<WED_TILEDATA*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pLayers[nLayer].nOffsetToTileData + sizeof(WED_TILEDATA) * nXTile + sizeof(WED_TILEDATA) * nYTile);
            }
        }
    }

    return NULL;
}

// 0x401220
WED_TILEDATA* CResWED::GetTileData(UINT nLayer, int nTile)
{
    if (m_bParsed) {
        if (nLayer < m_pHeader->nLayers) {
            if (nTile >= 0 && nTile < m_pLayers[nLayer].nTilesAcross * m_pLayers[nLayer].nTilesDown) {
                return reinterpret_cast<WED_TILEDATA*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pLayers[nLayer].nOffsetToTileData + sizeof(WED_TILEDATA) * nTile);
            }
        }
    }

    return NULL;
}

// 0x401270
WED_TILEDOBJECT* CResWED::GetTiledObject(USHORT nTile)
{
    if (m_bParsed) {
        if (nTile < m_pHeader->nTiledObjects) {
            return reinterpret_cast<WED_TILEDOBJECT*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pHeader->nOffsetToTiledObjects + sizeof(WED_TILEDOBJECT) * nTile);
        }
    }

    return NULL;
}

// 0x4012A0
WED_TILEDOBJECT* CResWED::GetTiledObjects()
{
    if (m_bParsed) {
        return reinterpret_cast<WED_TILEDOBJECT*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pHeader->nOffsetToTiledObjects);
    }

    return NULL;
}

// 0x4012C0
WORD* CResWED::GetTiledObjectList()
{
    if (m_bParsed) {
        return reinterpret_cast<WORD*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pHeader->nOffsetToObjectTileList);
    }

    return NULL;
}

// 0x4012E0
WORD* CResWED::GetTileList(UINT nLayer)
{
    if (m_bParsed) {
        if (nLayer < m_pHeader->nLayers) {
            return reinterpret_cast<WORD*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pLayers[nLayer].nOffsetToTileList);
        }
    }

    return NULL;
}

// 0x401310
int CResWED::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pHeader = NULL;
        m_pLayers = NULL;
        m_pPolyHeader = NULL;
        m_pPolyList = NULL;
        m_pPolyPoints = NULL;
    }
    return rc;
}

// 0x401340
BOOL CResWED::Parse(void* pData)
{
    m_pLayers = NULL;
    if (pData == NULL) {
        return m_bParsed;
    }

    m_pHeader = reinterpret_cast<WED_WEDHEADER*>(pData);
    if (m_pHeader->nFileType != 'WED ' || m_pHeader->nFileVersion != 'V1.3') {
        return FALSE;
    }

    m_pLayers = reinterpret_cast<WED_LAYERHEADER*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nOffsetToLayerHeaders);
    m_pPolyHeader = reinterpret_cast<WED_POLYHEADER*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nOffsetToPolyHeader);
    m_pScreenSectionList = reinterpret_cast<WED_SCREENSECTIONLIST*>(reinterpret_cast<unsigned char*>(pData) + m_pPolyHeader->nOffsetToScreenSectionList);
    m_pPolyList = reinterpret_cast<WED_POLYLIST*>(reinterpret_cast<unsigned char*>(pData) + m_pPolyHeader->nOffsetToPolyList);
    m_pPolyPoints = reinterpret_cast<WED_POLYPOINT*>(reinterpret_cast<unsigned char*>(pData) + m_pPolyHeader->nOffsetToPointList);

    m_bParsed = TRUE;

    return m_bParsed;
}

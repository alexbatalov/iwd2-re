#include "CWorldMap.h"

#include "CUtil.h"

// 0x558870
CWorldMap::CWorldMap()
{
    m_cHeader.m_nMapCount = 0;
    m_cHeader.m_nMapOffset = 0;
    m_cHeader.m_nMapCount = 0;
    m_cHeader.m_nMapOffset = 0;
    m_pData = NULL;
    m_ppAreas = NULL;
    m_ppLinks = NULL;
}

// 0x5588A0
CWorldMap::~CWorldMap()
{
    ClearData();
}

// 0x5588B0
void CWorldMap::ClearData()
{
    if (m_ppAreas != NULL) {
        for (DWORD nIndex = 0; nIndex < m_cHeader.m_nMapCount; nIndex++) {
            if (m_ppAreas != NULL) {
                delete m_ppAreas[nIndex];
                m_ppAreas[nIndex] = NULL;
            }
        }

        delete m_ppAreas;
        m_ppAreas = NULL;
    }

    if (m_ppLinks != NULL) {
        for (DWORD nIndex = 0; nIndex < m_cHeader.m_nMapCount; nIndex++) {
            if (m_ppLinks != NULL) {
                delete m_ppLinks[nIndex];
                m_ppLinks[nIndex] = NULL;
            }
        }

        delete m_ppLinks;
        m_ppLinks = NULL;
    }

    if (m_pData != NULL) {
        delete m_pData;
        m_pData = NULL;
    }

    m_cHeader.m_nMapCount = 0;
    m_cHeader.m_nMapOffset = 0;
}

// 0x558960
void CWorldMap::SetResRef(const CResRef& cResRef)
{
    // TODO: Incomplete.
}

// 0x559490
CWorldMapData* CWorldMap::GetMap(DWORD nMap)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 453
    UTIL_ASSERT(nMap < m_cHeader.m_nMapCount);

    return &(m_pData[nMap]);
}

// 0x559580
DWORD CWorldMap::GetNumAreas(DWORD nMap)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 533
    UTIL_ASSERT(nMap < m_cHeader.m_nMapCount);

    return m_pData[nMap].m_nAreas;
}

// 0x5595C0
CWorldMapArea* CWorldMap::GetArea(DWORD nMap, DWORD nArea)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 559
    UTIL_ASSERT(nMap < m_cHeader.m_nMapCount);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 560
    UTIL_ASSERT(nArea < m_pData[nMap].m_nAreas);

    return &(m_ppAreas[nMap][nArea]);
}

// 0x559630
CWorldMapLinks* CWorldMap::GetLink(DWORD nMap, DWORD nLink)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 586
    UTIL_ASSERT(nMap < m_cHeader.m_nMapCount);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CWorldMap.cpp
    // __LINE__: 587
    UTIL_ASSERT(nLink < m_pData[nMap].m_nLinks);

    return &(m_ppLinks[nMap][nLink]);
}

// 0x55A550
void* CWorldMapFile::GetData()
{
    if (pRes != NULL) {
        return pRes->Demand();
    } else {
        return NULL;
    }
}

// 0x55A560
DWORD CWorldMapFile::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

#include "CWorldMap.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
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

// 0x5594D0
CSize CWorldMap::GetMapSize(DWORD nMap)
{
    // NOTE: Uninline.
    CWorldMapData* pData = GetMap(nMap);

    return CSize(pData->m_nWidth * (g_pBaldurChitin->field_4A28 ? 2 : 1),
        pData->m_nHeight * (g_pBaldurChitin->field_4A28 ? 2 : 1));
}

// 0x559540
CSize CWorldMap::GetAreaPosition(CWorldMapArea* pArea)
{
    return CSize(pArea->m_mapLocationX * (g_pBaldurChitin->field_4A28 ? 2 : 1),
        pArea->m_mapLocationY * (g_pBaldurChitin->field_4A28 ? 2 : 1));
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

// 0x5596A0
BOOL CWorldMap::GetAreaIndex(DWORD nMap, const CResRef& cResArea, DWORD& nArea)
{
    CString v1;

    CPoint pt;
    if (g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tAreaLoad.Find(CString(cResArea.GetResRef()), pt, TRUE) != TRUE) {
        return FALSE;
    }

    v1 = g_pBaldurChitin->GetObjectGame()->GetRuleTables().m_tAreaLoad.GetAt(pt);

    for (DWORD nIndex = 0; nIndex < m_pData[nMap].m_nAreas; nIndex++) {
        if (v1 == CString(m_ppAreas[nMap][nIndex].m_resCurrentArea)) {
            nArea = nIndex;
            return TRUE;
        }
    }

    return FALSE;
}

// 0x559840
CWorldMapList* CWorldMap::GetAllLinks(DWORD nMap, DWORD nArea)
{
    CWorldMapList* pLinks = new CWorldMapList();
    DWORD nLinkStart;
    DWORD nLinkCount;
    DWORD nLink;

    nLinkStart = m_ppAreas[nMap][nArea].m_nNorthEdgeStartingLink;
    nLinkCount = nLinkStart + m_ppAreas[nMap][nArea].m_nNorthEdgeCount;

    for (nLink = nLinkStart; nLink < nLinkCount; nLink++) {
        pLinks->AddTail(nLink);
    }

    nLinkStart = m_ppAreas[nMap][nArea].m_nSouthEdgeStartingLink;
    nLinkCount = nLinkStart + m_ppAreas[nMap][nArea].m_nSouthEdgeCount;

    for (nLink = nLinkStart; nLink < nLinkCount; nLink++) {
        pLinks->AddTail(nLink);
    }

    nLinkStart = m_ppAreas[nMap][nArea].m_nWestEdgeStartingLink;
    nLinkCount = nLinkStart + m_ppAreas[nMap][nArea].m_nWestEdgeCount;

    for (nLink = nLinkStart; nLink < nLinkCount; nLink++) {
        pLinks->AddTail(nLink);
    }

    nLinkStart = m_ppAreas[nMap][nArea].m_nEastEdgeStartingLink;
    nLinkCount = nLinkStart + m_ppAreas[nMap][nArea].m_nEastEdgeCount;

    for (nLink = nLinkStart; nLink < nLinkCount; nLink++) {
        pLinks->AddTail(nLink);
    }

    return pLinks;
}

// 0x559A70
DWORD CWorldMap::GetLinkIndex(DWORD nMap, DWORD nSrcArea, DWORD nDstArea)
{
    CWorldMapList* pLinks = GetAllLinks(nMap, nSrcArea);
    CWorldMapLinks* pLink;
    DWORD nFoundLink = -1;
    DWORD nLink;

    POSITION pos = pLinks->GetHeadPosition();
    while (pos != NULL) {
        nLink = pLinks->GetNext(pos);

        // NOTE: Uninline.
        pLink = GetLink(nMap, nLink);

        if (pLink->m_nArea == nDstArea) {
            nFoundLink = nLink;
            break;
        }
    }

    delete pLinks;

    return nFoundLink;
}

// 0x55A230
DWORD CWorldMap::FindSourceAreaIndex(DWORD nMap, DWORD nLink)
{
    DWORD nArea;
    CWorldMapList* pLinks;
    POSITION pos;

    for (nArea = 0; nArea < m_pData[nMap].m_nAreas; nArea++) {
        pLinks = GetAllLinks(nMap, nArea);

        pos = pLinks->Find(nLink);

        delete pLinks;

        if (pos != NULL) {
            return nArea;
        }
    }

    return -1;
}

// 0x55A2C0
void CWorldMap::SetExplorable(DWORD nMap, const CResRef& cResArea, BOOL bExplorable)
{
    DWORD nArea;
    if (GetAreaIndex(nMap, cResArea, nArea)) {
        if (bExplorable) {
            m_ppAreas[nMap][nArea].m_dwFlags |= 0x4 | 0x1;
        } else {
            m_ppAreas[nMap][nArea].m_dwFlags &= ~0x4;
        }
    }
}

// 0x55A320
void CWorldMap::EnableArea(DWORD nMap, const CResRef& cResArea, BOOL bEnable)
{
    DWORD nArea;
    if (GetAreaIndex(nMap, cResArea, nArea)) {
        if (bEnable) {
            m_ppAreas[nMap][nArea].m_dwFlags |= 0x2 | 0x1;
        } else {
            m_ppAreas[nMap][nArea].m_dwFlags &= ~0x2;
        }
    }
}

// 0x55A3A0
DWORD CWorldMap::sub_55A3A0()
{
    CResRef cResArea = g_pBaldurChitin->GetObjectGame()->GetVisibleArea()->m_resRef;
    CString sResArea;
    cResArea.CopyToString(sResArea);
    return sub_55A450(sResArea);
}

// 0x55A450
DWORD CWorldMap::sub_55A450(CString sResArea)
{
    if (sResArea.GetLength() <= 3
        || sResArea[0] == '\0'
        || sResArea[1] == '\0'
        || sResArea[2] == '\0') {
        return 0;
    }

    INT nNumber = atoi(sResArea.Mid(2));
    if (nNumber < 4000) {
        return 0;
    }

    if (nNumber < 6000) {
        return 1;
    }

    return 2;
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

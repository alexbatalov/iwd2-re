#include "CVisibility.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameObjectArray.h"
#include "CInfGame.h"
#include "CPathSearch.h"
#include "CSearchBitmap.h"
#include "CUtil.h"
#include "CVidMode.h"

// 0x84EDCF
const BYTE CVisibilityMap::EXPLORED_RANGE_0 = 4;

// 0x84EDD0
const BYTE CVisibilityMap::EXPLORED_RANGE_1 = 8;

// 0x84EDD1
const BYTE CVisibilityMap::EXPLORED_RANGE_2 = 12;

// 0x84EDD2
const BYTE CVisibilityMap::EXPLORED_RANGE_3 = 14;

// 0x84EDD3
const BYTE CVisibilityMap::EXPLORED_RANGE_4 = 16;

// 0x84EDD4
const BYTE CVisibilityMap::EXPLORED_RANGE_5 = 20;

// 0x84EDD5
const BYTE CVisibilityMap::EXPLORED_RANGE_6 = 24;

// 0x84EDD6
const BYTE CVisibilityMap::SQUARE_SIZEX = 32;

// 0x84EDD7
const BYTE CVisibilityMap::SQUARE_SIZEY = 32;

// 0x84EDDB
const BYTE CVisibilityMap::EXPLORED = 0;

// 0x84EDD8
const BYTE CVisibilityMap::EXPLORED_FLAG = 0x80;

// 0x84EDD9
const BYTE CVisibilityMap::VISIBILITY_MASK = 0x3F;

// 0x84EDDA
const BYTE CVisibilityMap::UNEXPLORED = 0xF;

// 0x84EDDC
const TILE_CODE CVisibilityMap::EXPLORED_FULL = { 0, 0, 0, 0 };

// 0x84EDE0
const BYTE CVisibilityMap::UNEXPLORED_N = 9;

// 0x84EDE1
const BYTE CVisibilityMap::UNEXPLORED_NE = 13;

// 0x84EDE2
const BYTE CVisibilityMap::UNEXPLORED_E = 12;

// 0x84EDE3
const BYTE CVisibilityMap::UNEXPLORED_SE = 14;

// 0x84EDE4
const BYTE CVisibilityMap::UNEXPLORED_S = 6;

// 0x84EDE5
const BYTE CVisibilityMap::UNEXPLORED_SW = 7;

// 0x84EDE6
const BYTE CVisibilityMap::UNEXPLORED_W = 3;

// 0x84EDE7
const BYTE CVisibilityMap::UNEXPLORED_NW = 11;

// 0x84EDE8
const TILE_CODE CVisibilityMap::UNEXPLORED_FULL = { 0xF, 0xF, 0xF, 0xF };

// 0x84EDEC
const BYTE CVisibilityMap::FOGOWAR_EXPLORED_MASK = 0xF;

// 0x84EDED
const BYTE CVisibilityMap::FOGOWAR_EXPLORED_SHIFT = 0;

// 0x84EDEE
const BYTE CVisibilityMap::FOGOWAR_MASK = 0xF0;

// 0x84EDEF
const BYTE CVisibilityMap::FOGOWAR_SHIFT = 4;

// 0x551770
CVisibilityMap::CVisibilityMap()
{
    field_4 = 0;
    m_nWidth = 0;
    m_nHeight = 0;
    field_1A = 0;
    memset(m_aCharacterIds, 0, sizeof(m_aCharacterIds));
    m_pMap = NULL;
    m_pSearchMap = NULL;
    field_12 = 0;
    field_16 = 0;
    field_E = 14;
    field_10 = 10;
    sub_5518A0();
    m_bOutDoor = FALSE;
}

// 0x551800
CVisibilityMap::~CVisibilityMap()
{
    if (field_12) {
        delete field_12;
    }

    if (field_16) {
        delete field_16;
    }
}

// 0x551840
BOOL CVisibilityMap::AddCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable)
{
    for (SHORT nIndex = 0; nIndex < 6; nIndex++) {
        if (m_aCharacterIds[nIndex] == CGameObjectArray::INVALID_INDEX) {
            m_aCharacterIds[nIndex] = charId;
            PrivateAddCharacter(charId, 1 << nIndex, pVisibleTerrainTable);
            return TRUE;
        }
    }
    return FALSE;
}

// 0x5518A0
void CVisibilityMap::sub_5518A0()
{
    if (field_12 != NULL) {
        delete field_12;
    }

    if (field_16 != NULL) {
        delete field_16;
    }

    field_12 = new BYTE[field_E];
    field_16 = new BYTE[field_10];

    field_4 = static_cast<BYTE>(g_pBaldurChitin->GetCurrentVideoMode()->GetEllipseArcPixelList(field_E,
        field_10,
        field_12));

    field_1A = static_cast<BYTE>(g_pBaldurChitin->GetCurrentVideoMode()->GetEllipseArcPixelList(field_10,
        field_E,
        field_16));
}

// 0x551950
void CVisibilityMap::ClimbWall(const CPoint& ptStart, const CPoint& ptEnd, BYTE charId, const BYTE* pVisibileTerrainTable, SHORT nHighest)
{
    LONG nTopYValue = max(ptEnd.y, 0);
    LONG nCurrTile = ptStart.x + m_nWidth * ptStart.y;

    switch (nHighest) {
    case 3:
        if (ptStart.y - 2 >= nTopYValue) {
            // NOTE: Uninline.
            SetTileVisible(nCurrTile - 2 * m_nWidth, charId);
        }
        // FALLTHROUGH
    case 2:
        if (ptStart.y - 1 >= nTopYValue) {
            // NOTE: Uninline.
            SetTileVisible(nCurrTile - m_nWidth, charId);
        }
        // FALLTHROUGH
    case 1:
        if (ptStart.y >= nTopYValue) {
            // NOTE: Uninline.
            SetTileVisible(nCurrTile, charId);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
        // __LINE__: 333
        UTIL_ASSERT(FALSE);
    }
}

// 0x551A90
void CVisibilityMap::BltDitherPattern(LPDIRECTDRAWSURFACE pSurface, const TILE_CODE& tileCode)
{
    // TODO: Incomplete.
}

// 0x551FF0
void CVisibilityMap::BltFogOWar(LPDIRECTDRAWSURFACE pSurface, const TILE_CODE& tileCode)
{
    // TODO: Incomplete.
}

// 0x552590
BOOL CVisibilityMap::IsCharacterIdOnMap(LONG charId)
{
    for (SHORT nIndex = 0; nIndex < 6; nIndex++) {
        if (m_aCharacterIds[nIndex] == charId) {
            return TRUE;
        }
    }
    return FALSE;
}

// 0x5525C0
BYTE CVisibilityMap::GetSubTileCode(LONG nTile)
{
    BYTE code = 0;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 857
    UTIL_ASSERT(nTile >= 0 && nTile < (m_nWidth * m_nHeight));

    if (!IsTileVisible(nTile)) {
        code |= 0x1;
    }

    if (!IsTileVisible(m_nWidth + nTile)) {
        code |= 0x2;
    }

    if (!IsTileVisible(m_nWidth + nTile + 1)) {
        code |= 0x4;
    }

    if (!IsTileVisible(nTile + 1)) {
        code |= 0x8;
    }

    code <<= 8;

    if (!IsTileExplored(nTile)) {
        code |= 0x1;
    }

    if (!IsTileExplored(m_nWidth + nTile)) {
        code |= 0x2;
    }

    if (!IsTileExplored(m_nWidth + nTile + 1)) {
        code |= 0x4;
    }

    if (!IsTileExplored(nTile + 1)) {
        code |= 0x8;
    }

    return code;
}

// 0x5526E0
void CVisibilityMap::GetTileCode(SHORT n64x64Tile, TILE_CODE& tileCode)
{
    // NOTE: Uninline.
    LONG nBossTile = GetBossTile(n64x64Tile);
    LONG nSecondRowTile = m_nWidth + nBossTile;

    BOOLEAN bCheckRight = (nBossTile + 1) % m_nWidth != 0;
    BOOLEAN bCheckDown = nSecondRowTile < m_nWidth * m_nHeight;

    CSingleLock mapLock(&m_critSect, FALSE);
    mapLock.Lock(INFINITE);

    tileCode.tileNW = GetSubTileCode(nBossTile);

    if (bCheckRight) {
        tileCode.tileNE = GetSubTileCode(nBossTile + 1);
    }

    if (bCheckDown) {
        tileCode.tileSW = GetSubTileCode(nSecondRowTile);

        if (bCheckRight) {
            tileCode.tileSE = GetSubTileCode(nSecondRowTile + 1);
        }
    }

    mapLock.Unlock();
}

// 0x5527E0
void CVisibilityMap::Init(CGameArea* pArea)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 988
    UTIL_ASSERT(m_pMap == NULL);

    m_pSearchMap = &(pArea->m_search);
    m_nWidth = static_cast<SHORT>(pArea->GetInfinity()->nAreaX / 32 + 1);
    m_nHeight = static_cast<SHORT>(pArea->GetInfinity()->nAreaY / 32 + 1);
    m_nMapSize = m_nWidth * m_nHeight;

    if (m_pMap != NULL) {
        delete m_pMap;
    }

    m_pMap = new BYTE[m_nMapSize];
    memset(m_pMap, 0, m_nMapSize);

    for (SHORT nIndex = 0; nIndex < 6; nIndex++) {
        m_aCharacterIds[nIndex] = CGameObjectArray::INVALID_INDEX;
    }

    m_bOutDoor = (pArea->m_header.m_areaType & 0x1) != 0;
}

// 0x5528B0
void CVisibilityMap::Marshal(BYTE** pData, DWORD* pnData)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 1045
    UTIL_ASSERT(pData != NULL && pnData != NULL);

    *pnData = (m_nMapSize + 7) / 8;
    *pData = new BYTE[*pnData];
    if (*pData == NULL) {
        *pnData = NULL;
        return;
    }

    LONG nTile = 0;
    LONG nByte = 0;
    BYTE byte;
    BYTE byteMask;
    BYTE nMaxBit;

    while (nTile < m_nMapSize) {
        nMaxBit = static_cast<BYTE>(min(m_nMapSize - nTile, 8));
        byte = 0;
        byteMask = 1;
        while (nMaxBit > 0) {
            // NOTE: Uninline.
            if (IsTileExplored(nTile)) {
                byte |= byteMask;
            }
            byteMask <<= 1;
            nTile++;
            nMaxBit--;
        }
        (*pData)[nByte++] = byte;
    }
}

// 0x552990
void CVisibilityMap::Unmarshal(BYTE* pData, DWORD nData)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 1100
    UTIL_ASSERT(pData != NULL && nData > 0);

    LONG nTile = 0;
    LONG nByte = 0;
    BYTE byte;
    BYTE byteMask;
    BYTE nMaxBit;

    while (nTile < m_nMapSize) {
        nMaxBit = static_cast<BYTE>(min(m_nMapSize - nTile, 8));
        byte = pData[nByte++];
        byteMask = 1;
        while (nMaxBit > 0) {
            if ((byte & byteMask) != 0) {
                // NOTE: Uninline.
                SetTileExplored(nTile);
            }
            byteMask <<= 1;
            nTile++;
            nMaxBit--;
        }
    }
}

// 0x552A50
void CVisibilityMap::MarkTileLine(const CPoint& ptView, const CPoint& ptSearchMapView, LONG nDestX, LONG nDestY, const CPoint& ptOffset, BYTE charId, const BYTE* pVisibleTerrainTable, BOOLEAN bLookingUp)
{
    // TODO: Incomplete.
}

// 0x553290
void CVisibilityMap::PrivateAddCharacter(const CPoint& ptPos, BYTE visId, const BYTE* pVisibleTerrainTable)
{
    CPoint ptEar;
    LONG earZ;

    CPoint ptView;
    ptView.x = ptPos.x / 32;
    ptView.y = ptPos.y / 32;

    CPoint ptOffset;
    ptOffset.x = ptPos.x % 32;
    ptOffset.y = ptPos.y % 32;

    CPoint ptSearchMapView;
    ptSearchMapView.x = ptPos.x / CPathSearch::GRID_SQUARE_SIZEX;
    ptSearchMapView.y = ptPos.y / CPathSearch::GRID_SQUARE_SIZEY;

    sub_553800(ptView, ptOffset, ptSearchMapView, visId, pVisibleTerrainTable);
    sub_553990(ptView, ptOffset, ptSearchMapView, visId, pVisibleTerrainTable);

    g_pBaldurChitin->cSoundMixer.GetListenPosition(ptEar, earZ);
    if (ptEar.x == -1 && ptEar.y == -1) {
        if (m_pSearchMap->GetArea() == g_pBaldurChitin->GetObjectGame()->GetVisibleArea()) {
            m_pSearchMap->GetArea()->GetInfinity()->UpdateListenPosition();
        }
    }
}

// 0x5533B0
void CVisibilityMap::RemoveCharacter(const CPoint& pos, LONG charId, const BYTE* pVisibleTerrainTable)
{
    CPoint pt;
    pt.x = pos.x / 32;
    pt.y = pos.y / 32;

    for (SHORT nIndex = 0; nIndex < 6; nIndex++) {
        if (m_aCharacterIds[nIndex] == charId) {
            m_aCharacterIds[nIndex] = CGameObjectArray::INVALID_INDEX;

            BYTE visId = 1 << nIndex;
            if (visId != -1) {
                sub_553440(pt, visId);
                sub_5535D0(pt, visId);
            }

            break;
        }
    }
}

// 0x553440
void CVisibilityMap::sub_553440(const CPoint& pt, BYTE charId)
{
    // TODO: Incomplete.
}

// 0x5535D0
void CVisibilityMap::sub_5535D0(const CPoint& pt, BYTE charId)
{
    // TODO: Incomplete.
}

// 0x553740
void CVisibilityMap::SetAreaExplored()
{
    for (LONG nTile = 0; nTile < m_nWidth * m_nHeight; nTile++) {
        // NOTE: Uninline.
        SetTileExplored(nTile);
    }
}

// 0x5537A0
void CVisibilityMap::SetAreaUnexplored()
{
    for (LONG nTile = 0; nTile < m_nWidth * m_nHeight; nTile++) {
        // NOTE: Uninline.
        SetTileUnexplored(nTile);
    }
}

// 0x553800
void CVisibilityMap::sub_553800(const CPoint& ptView, const CPoint& ptOffset, const CPoint& ptSearchMapView, BYTE charId, const BYTE* pVisibleTerrainTable)
{
    // TODO: Incomplete.
}

// 0x553990
void CVisibilityMap::sub_553990(const CPoint& ptView, const CPoint& ptOffset, const CPoint& ptSearchMapView, BYTE charId, const BYTE* pVisibleTerrainTable)
{
    // TODO: Incomplete.
}

// 0x553B10
void CVisibilityMap::Uninit()
{
    if (m_pMap != NULL) {
        delete m_pMap;
        m_pMap = NULL;
    }

    for (SHORT nIndex = 0; nIndex < 6; nIndex++) {
        m_aCharacterIds[nIndex] = CGameObjectArray::INVALID_INDEX;
    }
}

// 0x553B40
void CVisibilityMap::UpDate(const CPoint& ptOldPos, const CPoint& ptNewPos, LONG charId, const BYTE* pVisibleTerrainTable)
{
    CPoint pt;
    pt.x = ptNewPos.x / 32;
    pt.y = ptNewPos.y / 32;

    // NOTE: Uninline.
    BYTE visId = GetCharacterPos(charId);

    if (visId != -1) {
        sub_553440(pt, visId);
        sub_5535D0(pt, visId);
        PrivateAddCharacter(charId, visId, pVisibleTerrainTable);
    }
}

// 0x553BD0
BOOLEAN CVisibilityMap::IsTileExplored(LONG nIndex)
{
    if (nIndex >= 0 && nIndex < m_nMapSize) {
        return (m_pMap[nIndex] & EXPLORED_FLAG) != 0;
    } else {
        return FALSE;
    }
}

// 0x553C00
BOOLEAN CVisibilityMap::IsTileVisible(LONG nIndex)
{
    if (nIndex >= 0 && nIndex < m_nMapSize) {
        return (m_pMap[nIndex] & VISIBILITY_MASK) != 0;
    } else {
        return FALSE;
    }
}

// 0x553C30
void CVisibilityMap::SetAreaVisible(BOOLEAN bVisible)
{
    for (INT nIndex = 0; nIndex < m_nWidth * m_nHeight; nIndex++) {
        if (bVisible == TRUE) {
            m_pMap[nIndex] |= VISIBILITY_MASK;
        } else {
            m_pMap[nIndex] &= ~VISIBILITY_MASK;
        }
    }
}

// 0x553D00
void CVisibilityMap::BltFogOWar3d(INT x, INT y, const CRect& rDest, const TILE_CODE& tileCode)
{
    // TODO: Incomplete.
}

// 0x76B120
SHORT CVisibilityMap::PointToTile(const CPoint& pos)
{
    return static_cast<SHORT>(pos.x / SQUARE_SIZEX + m_nWidth * (pos.y / SQUARE_SIZEY));
}

// NOTE: Inlined.
LONG CVisibilityMap::GetBossTile(LONG n64x64Tile)
{
    return 2 * (n64x64Tile % (m_nWidth / 2) + m_nWidth * (n64x64Tile / (m_nWidth / 2)));
}

// NOTE: Inlined.
BYTE CVisibilityMap::GetCharacterPos(LONG charId)
{
    for (SHORT index = 0; index < 6; index++) {
        if (m_aCharacterIds[index] == charId) {
            return 1 << static_cast<BYTE>(index);
        }
    }
    return -1;
}

// NOTE: Inlined.
void CVisibilityMap::SetTileExplored(LONG nIndex)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 2281
    UTIL_ASSERT_MSG((nIndex >= 0 && nIndex < m_nMapSize), "Index into vis map out of range in SetTileExplored");

    m_pMap[nIndex] |= EXPLORED_FLAG;
}

// NOTE: Inlined.
void CVisibilityMap::SetTileUnexplored(LONG nIndex)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 2288
    UTIL_ASSERT_MSG((nIndex >= 0 && nIndex < m_nMapSize), "Index into vis map out of range in SetTileUnexplored");

    m_pMap[nIndex] &= ~EXPLORED_FLAG;
}

// NOTE: Inlined.
void CVisibilityMap::SetTileVisible(LONG nIndex, BYTE charId)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CVisibility.cpp
    // __LINE__: 2295
    UTIL_ASSERT_MSG((nIndex >= 0 && nIndex < m_nMapSize), "Index into vis map out of range in SetTileVisible");

    m_pMap[nIndex] |= charId | EXPLORED_FLAG;
}

#include "CGameTiledObject.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x4CC270
CGameTiledObject::CGameTiledObject(CGameArea* pArea, CAreaFileTiledObject* pTiledObject, CAreaPoint* pPoints, WORD maxPts)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
    // __LINE__: 105
    UTIL_ASSERT(pArea != NULL && pTiledObject != NULL && pPoints != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
    // __LINE__: 106
    UTIL_ASSERT(pTiledObject->m_primarySearchSquaresStart + pTiledObject->m_primarySearchSquaresCount <= maxPts);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
    // __LINE__: 107
    UTIL_ASSERT(pTiledObject->m_secondarySearchSquaresStart + pTiledObject->m_secondarySearchSquaresCount <= maxPts);

    m_pPrimarySearch = NULL;
    m_nPrimarySearch = 0;
    m_pSecondarySearch = NULL;
    m_nSecondarySearch = 0;
    m_objectType = TYPE_TILED_OBJECT;
    m_resID = pTiledObject->m_tileID;
    m_dwFlags = pTiledObject->m_dwFlags;
    strncpy(reinterpret_cast<char*>(m_scriptRes), pTiledObject->m_scriptName, 32);

    POSITION pos = pArea->m_lTiledObjects.AddTail(&m_tiledObject);
    WORD wInitialState = (m_dwFlags & 0x1) != 0
        ? CTiledObject::STATE_SECONDARY_TILE
        : CTiledObject::STATE_PRIMARY_TILE;
    m_tiledObject.Initialize(pArea->m_pResWED,
        m_resID,
        pos,
        wInitialState);

    m_nPrimarySearch = pTiledObject->m_primarySearchSquaresCount;
    if (m_nPrimarySearch != 0) {
        m_pPrimarySearch = new CPoint[m_nPrimarySearch];

        if (m_pPrimarySearch == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
            // __LINE__: 139
            UTIL_ASSERT(FALSE);
        }

        // FIXME: Calculated but unused.
        CRect rBounds(INT_MAX, INT_MAX, 0, 0);

        for (WORD cnt = 0; cnt < m_nPrimarySearch; cnt++) {
            m_pPrimarySearch[cnt].x = pPoints[pTiledObject->m_primarySearchSquaresStart + cnt].m_xPos;
            m_pPrimarySearch[cnt].y = pPoints[pTiledObject->m_primarySearchSquaresStart + cnt].m_yPos;

            if (m_pPrimarySearch[cnt].x < rBounds.left) {
                rBounds.left = m_pPrimarySearch[cnt].x;
            }

            if (m_pPrimarySearch[cnt].x > rBounds.right) {
                rBounds.right = m_pPrimarySearch[cnt].x;
            }

            if (m_pPrimarySearch[cnt].y < rBounds.top) {
                rBounds.top = m_pPrimarySearch[cnt].y;
            }

            if (m_pPrimarySearch[cnt].y > rBounds.bottom) {
                rBounds.bottom = m_pPrimarySearch[cnt].y;
            }
        }

        if ((m_dwFlags & 0x1) == 0) {
            pArea->m_search.AddDoor(m_pPrimarySearch,
                m_nPrimarySearch,
                FALSE);
        }
    } else {
        m_pPrimarySearch = NULL;
    }

    m_nSecondarySearch = pTiledObject->m_secondarySearchSquaresCount;
    if (m_nSecondarySearch != 0) {
        m_pSecondarySearch = new CPoint[m_nSecondarySearch];

        if (m_pSecondarySearch == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
            // __LINE__: 173
            UTIL_ASSERT(FALSE);
        }

        // FIXME: Calculated but unused.
        CRect rBounds(INT_MAX, INT_MAX, 0, 0);

        for (WORD cnt = 0; cnt < m_nSecondarySearch; cnt++) {
            m_pSecondarySearch[cnt].x = pPoints[pTiledObject->m_secondarySearchSquaresStart + cnt].m_xPos;
            m_pSecondarySearch[cnt].y = pPoints[pTiledObject->m_secondarySearchSquaresStart + cnt].m_yPos;

            if (m_pSecondarySearch[cnt].x < rBounds.left) {
                rBounds.left = m_pSecondarySearch[cnt].x;
            }

            if (m_pSecondarySearch[cnt].x > rBounds.right) {
                rBounds.right = m_pSecondarySearch[cnt].x;
            }

            if (m_pSecondarySearch[cnt].y < rBounds.top) {
                rBounds.top = m_pSecondarySearch[cnt].y;
            }

            if (m_pSecondarySearch[cnt].y > rBounds.bottom) {
                rBounds.bottom = m_pSecondarySearch[cnt].y;
            }
        }

        if ((m_dwFlags & 0x1) != 0) {
            pArea->m_search.AddDoor(m_pSecondarySearch,
                m_nSecondarySearch,
                FALSE);
        }
    } else {
        m_pSecondarySearch = NULL;
    }

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id,
        this,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        AddToArea(pArea, CPoint(0, 0), 0, LIST_FRONT);

        CVariable name;
        name.SetName(CString(m_scriptRes));
        name.m_intValue = m_id;
        pArea->GetNamedCreatures()->AddKey(name);
    } else {
        delete this;
    }
}

// 0x4CC7D0
CGameTiledObject::~CGameTiledObject()
{
    if (m_pPrimarySearch != NULL) {
        delete m_pPrimarySearch;
    }

    if (m_pSecondarySearch != NULL) {
        delete m_pSecondarySearch;
    }
}

// 0x4CC810
void CGameTiledObject::RemoveFromArea()
{
    m_pArea->m_lTiledObjects.RemoveAt(m_tiledObject.m_posAreaList);

    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\cgametiledObject.cpp
        // __LINE__: 273
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x4CC890
void CGameTiledObject::ToggleState()
{
    if ((m_dwFlags & 0x1) != 0) {
        m_dwFlags &= ~0x1;
        m_tiledObject.m_wAIState = CTiledObject::STATE_PRIMARY_TILE;

        if (m_pSecondarySearch != NULL) {
            m_pArea->m_search.RemoveDoor(m_pSecondarySearch, m_nSecondarySearch);
        }

        if (m_pPrimarySearch != NULL) {
            m_pArea->m_search.AddDoor(m_pPrimarySearch, m_nPrimarySearch, FALSE);
        }
    } else {
        m_dwFlags |= 0x1;
        m_tiledObject.m_wAIState = CTiledObject::STATE_SECONDARY_TILE;

        if (m_pPrimarySearch != NULL) {
            m_pArea->m_search.RemoveDoor(m_pPrimarySearch, m_nPrimarySearch);
        }

        if (m_pSecondarySearch != NULL) {
            m_pArea->m_search.AddDoor(m_pSecondarySearch, m_nSecondarySearch, FALSE);
        }
    }
}

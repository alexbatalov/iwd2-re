#include "CGameTiledObject.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CUtil.h"

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

#include "CObjectMarker.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfGame.h"

// 0x766620
CObjectMarker::CObjectMarker()
{
    m_objectType = CGameObject::TYPE_OBJECT_MARKER;
}

// 0x766690
CObjectMarker::~CObjectMarker()
{
}

// 0x766660
BOOLEAN CObjectMarker::CompressTime(DWORD deltaTime)
{
    return TRUE;
}

// 0x766730
void CObjectMarker::AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType)
{
    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id,
        this,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        CGameObject::AddToArea(pNewArea, pos, posZ, listType);
    }
}

// 0x766780
void CObjectMarker::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        delete this;
    }
}

// 0x7667D0
void CObjectMarker::Render(CGameArea* pArea, CVidMode* pVidMode, int a3)
{
    POSITION pos = m_lstObjectIds.GetHeadPosition();
    while (pos != NULL) {
        LONG nSpriteId = m_lstObjectIds.GetNext(pos);

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nSpriteId,
                CGameObjectArray::THREAD_1,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pSprite->m_active
                && pSprite->m_activeAI
                && pSprite->m_activeImprisonment
                && pSprite->m_canBeSeen > 0
                && pSprite->m_pArea == pArea) {
                pSprite->RenderMarkers(pVidMode, a3);
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nSpriteId,
                CGameObjectArray::THREAD_1,
                INFINITE);
        }
    }
}

// NOTE: Inlined.
void CObjectMarker::AddObject(LONG id)
{
    m_lstObjectIds.AddTail(id);
}

// NOTE: Inlined.
void CObjectMarker::RemoveObject(LONG id)
{
    POSITION pos = m_lstObjectIds.Find(id);
    if (pos != NULL) {
        m_lstObjectIds.RemoveAt(pos);
    }
}

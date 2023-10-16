#include "CMoveList.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
#include "CInfGame.h"

// 0x5170A0
CMoveListEntry::CMoveListEntry()
{
    m_nSpriteId = CGameObjectArray::INVALID_INDEX;
    m_areaResRef = "";
    m_ptDestination.x = 0;
    m_ptDestination.y = 0;
    m_nFacing = 0;
    m_nDelay = 0;
}

// NOTE: Inlined.
CMoveList::CMoveList()
{
}

// 0x59EAD0
CMoveList::~CMoveList()
{
    ClearAll();
}

// 0x4E71B0
void CMoveList::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMoveListEntry* pEntry = GetNext(pos);
        delete pEntry;
    }
    RemoveAll();
}

// 0x517210
void CMoveList::CheckLoad(CGameArea* pArea)
{
    CResRef areaResRef = pArea->m_resRef;

    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMoveListEntry* pNode = GetNext(pos);
        if (pNode->m_areaResRef == areaResRef) {
            CGameSprite* pSprite;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(pNode->m_nSpriteId,
                    CGameObjectArray::THREAD_ASYNCH,
                    reinterpret_cast<CGameObject**>(&pSprite),
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pSprite->MoveOntoArea(pArea, pNode->m_ptDestination, pNode->m_nFacing);

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(pNode->m_nSpriteId,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }
}

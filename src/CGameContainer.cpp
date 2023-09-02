#include "CGameContainer.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CResRef.h"
#include "CUtil.h"

// 0x47FE10
void CGameContainer::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
        // __LINE__: 1597
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x481750
void CGameContainer::SetFlags(DWORD dwFlags)
{
    m_dwFlags = dwFlags;
}

// 0x481760
void CGameContainer::SetTrapActivated(WORD active)
{
    m_trapActivated = active;
}

// 0x481770
void CGameContainer::SetTrapDetected(WORD state)
{
    m_trapDetected = state;
}

// 0x481780
void CGameContainer::SetDrawPoly(SHORT time)
{
    if (m_drawPoly != time) {
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly) {
            CMessageSetDrawPoly* pMessage = new CMessageSetDrawPoly(time, GetId(), GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
    m_drawPoly = time;
}

// 0x4817F0
SHORT CGameContainer::FindItemSlot(const CResRef& res)
{
    POSITION pos = m_lstItems.GetHeadPosition();

    SHORT nSlot = 0;
    while (pos != NULL) {
        CItem* pItem = m_lstItems.GetNext(pos);
        if (pItem->GetResRef() == res) {
            return nSlot;
        }

        nSlot++;
    }

    return -1;
}

// 0x481830
SHORT CGameContainer::CountItem(const CResRef& res)
{
    POSITION pos = m_lstItems.GetHeadPosition();

    SHORT nCount = 0;
    while (pos != NULL) {
        CItem* pItem = m_lstItems.GetNext(pos);
        if (pItem->GetResRef() == res) {
            if (pItem->GetMaxStackable() > 1) {
                nCount += pItem->GetUsageCount(0);
            } else {
                nCount++;
            }
        }
    }

    return nCount;
}

#include "CGameContainer.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CResRef.h"
#include "CScreenWorld.h"
#include "CUtil.h"

// 0x47C890
CGameContainer::CGameContainer(CGameArea* pArea, const CRect& rBound)
{
    // TODO: Incomplete.
}

// 0x47D7F0
BOOLEAN CGameContainer::DoAIUpdate(BOOLEAN active, LONG counter)
{
    return active && (counter & m_AISpeed) == (m_AISpeed & m_id);
}

// 0x47D820
void CGameContainer::AIUpdate()
{
    if (m_bDeleteMe) {
        RemoveFromArea();
        return;
    }

    if (m_drawPoly > 0) {
        m_drawPoly--;
    }

    ProcessAI();
}

// 0x47E040
void CGameContainer::DebugDump(const CString& message, BOOLEAN bEchoToScreen)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    CString sTemp;
    CString sType;

    switch (m_containerType) {
    case 1:
        sType = "BAG";
        break;
    case 2:
        sType = "CHEST";
        break;
    case 3:
        sType = "DRAWER";
        break;
    case 4:
        sType = "PILE";
        break;
    case 5:
        sType = "TABLE";
        break;
    case 6:
        sType = "SHELF";
        break;
    case 7:
        sType = "ALTAR";
        break;
    case 8:
        sType = "NONVISIBLE";
        break;
    case 9:
        sType = "SPELLBOOK";
        break;
    case 10:
        sType = "BODY";
        break;
    case 11:
        sType = "BARREL";
        break;
    case 12:
        sType = "CRATE";
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
        // __LINE__: 899
        UTIL_ASSERT(FALSE);
    }

    if (bEchoToScreen) {
        pWorld->DisplayText(CString(""),
            CString("DEBUG DUMP: CGameContainer"),
            -1,
            FALSE);

        pWorld->DisplayText(CString(""),
            message,
            -1,
            FALSE);

        sTemp.Format("Current Area: %.*s", RESREF_SIZE, m_pArea->m_resRef.GetResRef());
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Current Position: x=%d y=%d", m_pos.x, m_pos.y);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Container Type: %s", (LPCSTR)sType);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Locked: %s\n", (m_dwFlags & 0x1) != 0 ? "TRUE" : "FALSE");
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Lock Difficulty: %d%%\n", m_lockDifficulty);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Key Type: %.*s", RESREF_SIZE, m_keyType.GetResRef());
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trapped: %s", m_trapActivated != 0 ? "TRUE" : "FALSE");
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Detected: %s", m_trapDetected != 0 ? "TRUE" : "FALSE");
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Reset Trap: %s", (m_dwFlags & 0x8) != 0 ? "TRUE" : "FALSE");
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Detection Difficulty: %d%%", m_trapDetectionDifficulty);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Removal Difficulty: %d%%", m_trapRemovalDifficulty);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Script: %.*s", RESREF_SIZE, m_scriptRes);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Launching Point: x=%d y=%d", m_posTrapOrigin.x, m_posTrapOrigin.y);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        pWorld->DisplayText(CString(""),
            CString("Contents:"),
            -1,
            FALSE);

        POSITION pos = m_lstItems.GetHeadPosition();
        while (pos != NULL) {
            CItem* pItem = m_lstItems.GetNext(pos);
            if (pItem != NULL) {
                if ((pItem->m_flags & 0x1) != 0) {
                    sTemp.Format("    %.*s, %d, %d, %d, IDENTIFIED\n",
                        RESREF_SIZE,
                        pItem->GetResRef().GetResRef(),
                        pItem->GetUsageCount(0),
                        pItem->GetUsageCount(1),
                        pItem->GetUsageCount(2));
                    pWorld->DisplayText(CString(""),
                        sTemp,
                        -1,
                        FALSE);
                } else {
                    sTemp.Format("    %.*s, %d, %d, %d\n",
                        RESREF_SIZE,
                        pItem->GetResRef().GetResRef(),
                        pItem->GetUsageCount(0),
                        pItem->GetUsageCount(1),
                        pItem->GetUsageCount(2));
                    pWorld->DisplayText(CString(""),
                        sTemp,
                        -1,
                        FALSE);
                }
            }
        }
    }
}

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

// 0x4802B0
CItem* CGameContainer::GetItem(SHORT nSlotNum)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
    // __LINE__: 1791
    UTIL_ASSERT(nSlotNum >= 0);

    POSITION pos = m_lstItems.FindIndex(nSlotNum);
    if (pos != NULL) {
        return m_lstItems.GetAt(pos);
    }

    return NULL;
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

// FIXME: `scriptRes` should be reference.
//
// 0x45FE90
void CGameContainer::SetScriptRes(CString scriptRes)
{
    memset(m_scriptRes, 0, RESREF_SIZE);

    for (int index = 0; index < RESREF_SIZE && index < scriptRes.GetLength(); index++) {
        m_scriptRes[index] = scriptRes[index];
    }
}

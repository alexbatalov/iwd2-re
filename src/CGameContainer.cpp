#include "CGameContainer.h"

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CPathSearch.h"
#include "CResRef.h"
#include "CScreenWorld.h"
#include "CUtil.h"

// 0x8D3988
const CResRef CGameContainer::RESREF_AR6051("AR6051");

// 0x47BFA0
CGameContainer::CGameContainer(CGameArea* pArea, CAreaFileContainer* pContainerObject, CAreaPoint* pPoints, WORD maxPts, CCreatureFileItem* pItems, DWORD maxItems)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
    // __LINE__: 113
    UTIL_ASSERT(pArea != NULL && pContainerObject != NULL && pPoints != NULL && pContainerObject->m_pickPointStart + pContainerObject->m_pickPointCount <= maxPts);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
    // __LINE__: 114
    UTIL_ASSERT(pItems != NULL && pContainerObject->m_startingItem + pContainerObject->m_itemCount <= maxItems);

    // FIXME: Probably should reuse `RESREF_AR6051`.
    //
    // 0x8D3998
    static CResRef stru_8D3998("AR6051");

    BOOL bIsAR6051 = FALSE;
    if (pArea->m_resRef == stru_8D3998) {
        bIsAR6051 = TRUE;
    }

    m_objectType = TYPE_CONTAINER;

    if (pContainerObject->m_containerType == 4
        && pContainerObject->m_boundingRectLeft == 0
        && pContainerObject->m_boundingRectTop == 0
        && pContainerObject->m_boundingRectRight == 0
        && pContainerObject->m_boundingRectBottom == 0) {
        pContainerObject->m_boundingRectLeft = CPathSearch::GRID_SQUARE_SIZEX * (pContainerObject->m_posX / CPathSearch::GRID_SQUARE_SIZEX);
        pContainerObject->m_boundingRectRight = CPathSearch::GRID_SQUARE_SIZEX * (pContainerObject->m_posX / (CPathSearch::GRID_SQUARE_SIZEX + 1)) - 1;
        pContainerObject->m_boundingRectTop = CPathSearch::GRID_SQUARE_SIZEY * (pContainerObject->m_posY / CPathSearch::GRID_SQUARE_SIZEY);
        pContainerObject->m_boundingRectBottom = CPathSearch::GRID_SQUARE_SIZEY * (pContainerObject->m_posY / (CPathSearch::GRID_SQUARE_SIZEY + 1)) - 1;
    }

    m_rBounding.left = pContainerObject->m_boundingRectLeft;
    m_rBounding.top = pContainerObject->m_boundingRectTop;
    m_rBounding.right = pContainerObject->m_boundingRectRight + 1;
    m_rBounding.bottom = pContainerObject->m_boundingRectBottom + 1;
    m_nPolygon = pContainerObject->m_pickPointCount;

    memcpy(m_scriptRes, pContainerObject->m_script, RESREF_SIZE);

    strncpy(m_scriptName, pContainerObject->m_scriptName, SCRIPTNAME_SIZE);

    CAIScript* pScript = new CAIScript(CResRef(pContainerObject->m_script));
    SetScript(0, pScript);

    m_lockDifficulty = pContainerObject->m_lockDifficulty;
    m_dwFlags = pContainerObject->m_dwFlags;
    m_trapDetectionDifficulty = pContainerObject->m_trapDetectionDifficulty;
    m_trapRemovalDifficulty = pContainerObject->m_trapRemovalDifficulty;
    m_trapActivated = pContainerObject->m_trapActivated;
    m_trapDetected = pContainerObject->m_trapDetected;
    m_posTrapOrigin.x = pContainerObject->m_posXTrapOrigin;
    m_posTrapOrigin.y = pContainerObject->m_posYTrapOrigin;
    m_triggerRange = pContainerObject->m_triggerRange;
    strncpy(m_ownedBy, pContainerObject->m_ownedBy, SCRIPTNAME_SIZE);
    m_keyType = pContainerObject->m_keyType;
    m_breakDifficulty = pContainerObject->m_breakDifficulty;
    m_drawPoly = 0;

    if (m_nPolygon != 0) {
        m_pPolygon = new CPoint[m_nPolygon];

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameTrigger.cpp
        // __LINE__: 169
        UTIL_ASSERT(FALSE);

        WORD adjust = 0;
        for (WORD cnt = 0; cnt < m_nPolygon; cnt++) {
            m_pPolygon[cnt - adjust].x = pPoints[cnt + pContainerObject->m_pickPointStart].m_xPos;
            m_pPolygon[cnt - adjust].y = pPoints[cnt + pContainerObject->m_pickPointStart].m_yPos;
            if (cnt >= 2) {
                int x2 = m_pPolygon[cnt - adjust - 2].x;
                int y2 = m_pPolygon[cnt - adjust - 2].y;

                int x1 = m_pPolygon[cnt - adjust - 1].x;
                int y1 = m_pPolygon[cnt - adjust - 1].y;

                int x0 = m_pPolygon[cnt - adjust].x;
                int y0 = m_pPolygon[cnt - adjust].y;

                if ((x2 == x1 && x1 == x0)
                    || (y2 == y1 && y1 == y0)
                    || (x2 != x1
                        && x1 != x0
                        && 1000 * (y2 - y1) / (x2 - x1) != 1000 * (y1 - y0) / (x1 - x0))) {
                    m_pPolygon[cnt - adjust - 1] = m_pPolygon[cnt - adjust];
                    adjust++;
                }
            }
        }

        m_nPolygon -= adjust;
    } else {
        m_pPolygon = NULL;
    }

    for (DWORD nItem = pContainerObject->m_startingItem; nItem < pContainerObject->m_startingItem + pContainerObject->m_itemCount; nItem++) {
        CItem* pItem = new CItem(CResRef(pItems[nItem].m_itemId),
            pItems[nItem].m_usageCount[0],
            pItems[nItem].m_usageCount[1],
            pItems[nItem].m_usageCount[2],
            pItems[nItem].m_wear,
            pItems[nItem].m_dynamicFlags);

        if (pItem->cResRef != "") {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameContainer.cpp
            // __LINE__: 225
            m_lstItems.AddTail(pItem);
        } else {
            delete pItem;
        }
    }

    m_containerType = pContainerObject->m_containerType;

    if (m_containerType == 4) {
        m_ptWalkToUse.x = (pContainerObject->m_boundingRectLeft + pContainerObject->m_boundingRectRight) / 2;
        m_ptWalkToUse.y = (pContainerObject->m_boundingRectTop + pContainerObject->m_boundingRectBottom) / 2;
        RefreshRenderPile();
    } else {
        m_ptWalkToUse.x = pContainerObject->m_posX;
        m_ptWalkToUse.y = pContainerObject->m_posY;
    }

    m_pArea = pArea;

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id,
        this,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        m_pArea = NULL;

        m_typeAI.m_nInstance = m_id;
        AddToArea(pArea, m_ptWalkToUse, 0, LIST_BACK);
        m_bDeleteMe = FALSE;

        if (bIsAR6051 == TRUE) {
            SHORT nSlotNum = 0;
            POSITION pos = m_lstItems.GetHeadPosition();
            while (pos != NULL) {
                CItem* pItem = m_lstItems.GetNext(pos);
                if (pItem != NULL) {
                    sub_480480(nSlotNum, pItem);
                }
                nSlotNum++;
            }
        }

        CVariable name;
        CString sScriptName(m_scriptName);

        m_typeAI.SetName(CString(m_scriptName));

        sScriptName.TrimLeft();
        if (sScriptName != "") {
            name.SetName(CString(m_scriptName));
            name.m_intValue = m_id;
            pArea->GetNamedCreatures()->AddKey(name);
        }

        sub_481890(&m_rBounding, field_8D6);

        field_8EA = NULL;

        if (m_nPolygon != 0) {
            field_8EA = new CAreaPoint[m_nPolygon];

            for (WORD cnt = 0; cnt < m_nPolygon; cnt++) {
                field_8EA[cnt].m_xPos = static_cast<WORD>(m_pPolygon[cnt].x);
                field_8EA[cnt].m_yPos = static_cast<WORD>(m_pPolygon[cnt].y);
            }
        } else {
            field_8EA = NULL;
        }

        field_8D2 = 0;
    } else {
        delete this;
    }
}

// 0x47C890
CGameContainer::CGameContainer(CGameArea* pArea, const CRect& rBound)
{
    m_objectType = TYPE_CONTAINER;
    m_rBounding = rBound;
    m_nPolygon = 0;
    m_pPolygon = NULL;
    m_containerType = 4;
    m_ptWalkToUse.x = (rBound.left + rBound.right) / 2;
    m_ptWalkToUse.y = (rBound.top + rBound.bottom) / 2;
    m_posTrapOrigin.x = 0;
    m_posTrapOrigin.y = 0;
    m_nPileVidCell = 0;
    m_lockDifficulty = 0;
    m_dwFlags = 0;
    m_trapDetectionDifficulty = 0;
    m_trapRemovalDifficulty = 0;
    m_trapActivated = 0;
    m_trapDetected = 0;
    m_posTrapOrigin.y = 0;
    m_triggerRange = 0;
    memset(m_ownedBy, 0, SCRIPTNAME_SIZE);
    memset(m_scriptRes, 0, RESREF_SIZE);
    memset(m_scriptName, 0, SCRIPTNAME_SIZE);
    m_keyType = "";
    m_breakDifficulty = 0;
    m_drawPoly = 0;

    m_pArea = pArea;

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id,
        this,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        m_pArea = NULL;

        AddToArea(pArea, m_ptWalkToUse, 0, LIST_BACK);
        m_bDeleteMe = FALSE;
        field_8EA = NULL;
        field_8D2 = 0;
    } else {
        delete this;
    }
}

// 0x47CAC0
CGameContainer::~CGameContainer()
{
    POSITION pos = m_lstItems.GetHeadPosition();
    while (pos != NULL) {
        CItem* pItem = m_lstItems.GetNext(pos);
        if (pItem != NULL) {
            delete pItem;
        }
    }
    m_lstItems.RemoveAll();

    if (m_pPolygon != NULL) {
        delete m_pPolygon;
    }

    if (field_8EA != NULL) {
        delete field_8EA;
        field_8EA = NULL;
    }

    // When there is only one element its an unowned pointer to `m_rBounding`.
    if (field_8D6.GetCount() > 1) {
        for (INT nIndex = 0; nIndex < field_8D6.GetCount(); nIndex++) {
            delete field_8D6[nIndex];
        }
    }
    field_8D6.SetSize(0);
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

// 0x4801A0
void CGameContainer::CompressContainer()
{
    // TODO: Incomplete.
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

// 0x480300
void CGameContainer::SetItem(SHORT nSlotNum, CItem* pItem)
{
    // TODO: Incomplete.
}

// 0x480480
void CGameContainer::sub_480480(SHORT nSlotNum, CItem* pItem)
{
    // TODO: Incomplete.
}

// 0x481160
void CGameContainer::RefreshRenderPile()
{
    if (m_containerType == 4) {
        m_nPileVidCell = 0;

        POSITION pos = m_lstItems.GetHeadPosition();
        while (pos != NULL && m_nPileVidCell < 3) {
            CItem* pItem = m_lstItems.GetNext(pos);
            if (pItem != NULL) {
                m_pileVidCell[m_nPileVidCell].SetResRef(pItem->GetGroundIcon(), FALSE, TRUE, TRUE);

                if (m_pileVidCell[m_nPileVidCell].cResRef != "") {
                    m_pileVidCell[m_nPileVidCell].SequenceSet(0);
                    m_pileVidCell[m_nPileVidCell].FrameSet(0);
                    m_nPileVidCell++;
                }
            }
        }
    }
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

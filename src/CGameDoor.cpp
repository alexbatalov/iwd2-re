#include "CGameDoor.h"

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CPathSearch.h"
#include "CScreenWorld.h"
#include "CUtil.h"
#include "CVidPoly.h"

// 0x8D41D8
const LONG CGameDoor::RANGE_DOOR = 16
    * CPathSearch::GRID_SQUARE_SIZEX
    * CPathSearch::GRID_SQUARE_SIZEX;

// 0x485AC0
CGameDoor::CGameDoor(CGameArea* pArea, CAreaFileDoorObject* pDoorObject, CAreaPoint* pPoints, WORD maxPts)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
    // __LINE__: 107
    UTIL_ASSERT(pArea != NULL && pDoorObject != NULL && pPoints != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
    // __LINE__: 108
    UTIL_ASSERT(pDoorObject->m_openSelectionPointStart + pDoorObject->m_openSelectionPointCount <= maxPts);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
    // __LINE__: 109
    UTIL_ASSERT(pDoorObject->m_closedSelectionPointStart + pDoorObject->m_closedSelectionPointCount <= maxPts);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
    // __LINE__: 110
    UTIL_ASSERT(pDoorObject->m_openSearchSquaresStart + pDoorObject->m_openSearchSquaresCount <= maxPts);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
    // __LINE__: 111
    UTIL_ASSERT(pDoorObject->m_closedSearchSquaresStart + pDoorObject->m_closedSearchSquaresCount <= maxPts);

    m_objectType = TYPE_DOOR;
    m_resID = pDoorObject->m_doorID;

    m_rOpenBounding.left = pDoorObject->m_openBoundingRectLeft;
    m_rOpenBounding.top = pDoorObject->m_openBoundingRectTop;
    m_rOpenBounding.right = pDoorObject->m_openBoundingRectRight;
    m_rOpenBounding.bottom = pDoorObject->m_openBoundingRectBottom;

    m_rClosedBounding.left = pDoorObject->m_closedBoundingRectLeft;
    m_rClosedBounding.top = pDoorObject->m_closedBoundingRectTop;
    m_rClosedBounding.right = pDoorObject->m_closedBoundingRectRight;
    m_rClosedBounding.bottom = pDoorObject->m_closedBoundingRectBottom;

    m_cursorType = pDoorObject->m_cursorType;
    m_dwFlags = pDoorObject->m_dwFlags;
    m_nOpenPolygon = pDoorObject->m_openSelectionPointCount;
    m_nClosedPolygon = pDoorObject->m_closedSelectionPointCount;

    m_ptDest1.x = pDoorObject->m_posXWalkTo1;
    m_ptDest1.y = pDoorObject->m_posYWalkTo1;

    m_ptDest2.x = pDoorObject->m_posXWalkTo2;
    m_ptDest2.y = pDoorObject->m_posYWalkTo2;

    m_strNotPickable = pDoorObject->m_strNotPickable;

    POSITION pos = pArea->m_lTiledObjects.AddTail(&m_tiledObject);
    WORD wInitialState = (m_dwFlags & 0x1) != 0
        ? CTiledObject::STATE_PRIMARY_TILE
        : CTiledObject::STATE_SECONDARY_TILE;
    m_tiledObject.Initialize(pArea->m_pResWED,
        m_resID,
        pos,
        wInitialState);

    memcpy(m_scriptRes, pDoorObject->m_script, RESREF_SIZE);

    strncpy(m_scriptName, pDoorObject->m_scriptName, SCRIPTNAME_SIZE);

    CAIScript* pScript = new CAIScript(CResRef(pDoorObject->m_script));
    SetScript(0, pScript);

    m_hitPoints = pDoorObject->m_hitPoints != 0 ? pDoorObject->m_hitPoints : 20;
    m_armourClass = pDoorObject->m_armourClass;
    m_openSound = pDoorObject->m_openSound;
    m_closeSound = pDoorObject->m_closeSound;
    m_trapDetectionDifficulty = pDoorObject->m_trapDetectionDifficulty;
    m_trapDisarmingDifficulty = pDoorObject->m_trapDisarmingDifficulty;
    m_trapActivated = pDoorObject->m_trapActivated;
    m_trapDetected = pDoorObject->m_trapDetected;
    m_posXTrapOrigin = pDoorObject->m_posXTrapOrigin;
    m_posYTrapOrigin = pDoorObject->m_posYTrapOrigin;
    m_keyType = pDoorObject->m_keyType;
    m_detectionDifficulty = pDoorObject->m_detectionDifficulty;
    m_lockDifficulty = pDoorObject->m_lockDifficulty;
    m_drawPoly = 0;

    if (m_nOpenPolygon != 0) {
        m_pOpenPolygon = new CPoint[m_nOpenPolygon];

        if (m_pOpenPolygon == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
            // __LINE__: 170
            UTIL_ASSERT(FALSE);
        }

        WORD adjust = 0;
        for (WORD cnt = 0; cnt < m_nOpenPolygon; cnt++) {
            m_pOpenPolygon[cnt - adjust].x = pPoints[cnt + pDoorObject->m_openSelectionPointStart].m_xPos;
            m_pOpenPolygon[cnt - adjust].y = pPoints[cnt + pDoorObject->m_openSelectionPointStart].m_yPos;
            if (cnt >= 2) {
                int x2 = m_pOpenPolygon[cnt - adjust - 2].x;
                int y2 = m_pOpenPolygon[cnt - adjust - 2].y;

                int x1 = m_pOpenPolygon[cnt - adjust - 1].x;
                int y1 = m_pOpenPolygon[cnt - adjust - 1].y;

                int x0 = m_pOpenPolygon[cnt - adjust].x;
                int y0 = m_pOpenPolygon[cnt - adjust].y;

                if ((x2 == x1 && x1 == x0)
                    || (y2 == y1 && y1 == y0)
                    || (x2 != x1
                        && x1 != x0
                        && 1000 * (y2 - y1) / (x2 - x1) != 1000 * (y1 - y0) / (x1 - x0))) {
                    m_pOpenPolygon[cnt - adjust - 1] = m_pOpenPolygon[cnt - adjust];
                    adjust++;
                }
            }
        }

        m_nOpenPolygon -= adjust;
    } else {
        m_pOpenPolygon = NULL;
    }

    if (m_nClosedPolygon != 0) {
        m_pClosedPolygon = new CPoint[m_nClosedPolygon];

        if (m_pClosedPolygon == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
            // __LINE__: 206
            UTIL_ASSERT(FALSE);
        }

        WORD adjust = 0;
        for (WORD cnt = 0; cnt < m_nClosedPolygon; cnt++) {
            m_pClosedPolygon[cnt - adjust].x = pPoints[cnt + pDoorObject->m_closedSelectionPointStart].m_xPos;
            m_pClosedPolygon[cnt - adjust].y = pPoints[cnt + pDoorObject->m_closedSelectionPointStart].m_yPos;
            if (cnt >= 2) {
                int x2 = m_pClosedPolygon[cnt - adjust - 2].x;
                int y2 = m_pClosedPolygon[cnt - adjust - 2].y;

                int x1 = m_pClosedPolygon[cnt - adjust - 1].x;
                int y1 = m_pClosedPolygon[cnt - adjust - 1].y;

                int x0 = m_pClosedPolygon[cnt - adjust].x;
                int y0 = m_pClosedPolygon[cnt - adjust].y;

                if ((x2 == x1 && x1 == x0)
                    || (y2 == y1 && y1 == y0)
                    || (x2 != x1
                        && x1 != x0
                        && 1000 * (y2 - y1) / (x2 - x1) != 1000 * (y1 - y0) / (x1 - x0))) {
                    m_pClosedPolygon[cnt - adjust - 1] = m_pClosedPolygon[cnt - adjust];
                    adjust++;
                }
            }
        }

        m_nClosedPolygon -= adjust;
    } else {
        m_pClosedPolygon = NULL;
    }

    m_nOpenSearch = pDoorObject->m_openSearchSquaresCount;
    if (m_nOpenSearch != 0) {
        m_pOpenSearch = new CPoint[m_nOpenSearch];

        if (m_pOpenSearch == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
            // __LINE__: 243
            UTIL_ASSERT(FALSE);
        }

        for (WORD cnt = 0; cnt < m_nOpenSearch; cnt++) {
            m_pOpenSearch[cnt].x = pPoints[pDoorObject->m_openSearchSquaresStart + cnt].m_xPos;
            m_pOpenSearch[cnt].y = pPoints[pDoorObject->m_openSearchSquaresStart + cnt].m_yPos;
        }

        if ((m_dwFlags & 0x1) != 0) {
            pArea->m_search.AddDoor(m_pOpenSearch,
                m_nOpenSearch,
                (m_dwFlags & 0x400) != 0);
        }
    } else {
        m_pOpenSearch = NULL;
    }

    m_ptOpenDest.x = (pDoorObject->m_openBoundingRectLeft + pDoorObject->m_openBoundingRectRight) / 2;
    m_ptOpenDest.y = pDoorObject->m_openBoundingRectBottom;

    m_nClosedSearch = pDoorObject->m_openSearchSquaresCount;
    if (m_nClosedSearch != 0) {
        m_pClosedSearch = new CPoint[m_nClosedSearch];

        if (m_pClosedSearch == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
            // __LINE__: 270
            UTIL_ASSERT(FALSE);
        }

        for (WORD cnt = 0; cnt < m_nClosedSearch; cnt++) {
            m_pClosedSearch[cnt].x = pPoints[pDoorObject->m_closedSearchSquaresStart + cnt].m_xPos;
            m_pClosedSearch[cnt].y = pPoints[pDoorObject->m_closedSearchSquaresStart + cnt].m_yPos;
        }

        if ((m_dwFlags & 0x1) == 0) {
            pArea->m_search.AddDoor(m_pClosedSearch,
                m_nClosedSearch,
                (m_dwFlags & 0x400) != 0);
        }
    } else {
        m_pClosedSearch = NULL;
    }

    m_ptClosedDest.x = (pDoorObject->m_closedBoundingRectLeft + pDoorObject->m_closedBoundingRectRight) / 2;
    m_ptClosedDest.y = pDoorObject->m_closedBoundingRectBottom;

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id,
        this,
        INFINITE);
    if (rc == CGameObjectArray::SUCCESS) {
        if ((m_dwFlags & 0x1) != 0) {
            AddToArea(pArea, m_ptOpenDest, 0, LIST_FRONT);
        } else {
            AddToArea(pArea, m_ptClosedDest, 0, LIST_FRONT);
        }

        m_typeAI.SetName(CString(m_scriptName));

        CVariable name;
        name.SetName(CString(m_scriptName));
        name.m_intValue = m_id;
        pArea->GetNamedCreatures()->AddKey(name);

        sub_481890(&m_rClosedBounding, field_6DA);
        sub_481890(&m_rOpenBounding, field_6F2);

        field_6EE = NULL;
        field_706 = NULL;

        if (m_nClosedPolygon != 0) {
            field_6EE = new CAreaPoint[m_nClosedPolygon];

            for (WORD cnt = 0; cnt < m_nClosedPolygon; cnt++) {
                field_6EE[cnt].m_xPos = static_cast<WORD>(m_pClosedPolygon[cnt].x);
                field_6EE[cnt].m_yPos = static_cast<WORD>(m_pClosedPolygon[cnt].y);
            }
        } else {
            field_6EE = NULL;
        }

        if (m_nOpenPolygon != 0) {
            field_706 = new CAreaPoint[m_nOpenPolygon];

            for (WORD cnt = 0; cnt < m_nOpenPolygon; cnt++) {
                field_706[cnt].m_xPos = static_cast<WORD>(m_pOpenPolygon[cnt].x);
                field_706[cnt].m_yPos = static_cast<WORD>(m_pOpenPolygon[cnt].y);
            }
        } else {
            field_706 = NULL;
        }

        m_nAICounter = 0;
    } else {
        delete this;
    }
}

// 0x4866E0
CGameDoor::~CGameDoor()
{
    if (m_pOpenPolygon != NULL) {
        delete m_pOpenPolygon;
    }

    if (m_pClosedPolygon != NULL) {
        delete m_pClosedPolygon;
    }

    if (m_pOpenSearch != NULL) {
        delete m_pOpenSearch;
    }

    if (m_pClosedSearch != NULL) {
        delete m_pClosedSearch;
    }

    if (field_6EE != NULL) {
        delete field_6EE;
        field_6EE = NULL;
    }

    // When there is only one element its an unowned pointer to
    // `m_rClosedBounding`.
    if (field_6DA.GetCount() > 1) {
        for (INT nIndex = 0; nIndex < field_6DA.GetCount(); nIndex++) {
            delete field_6DA[nIndex];
        }
    }
    field_6DA.SetSize(0);

    if (field_706 != NULL) {
        delete field_706;
        field_706 = NULL;
    }

    // When there is only one element its an unowned pointer to
    // `m_rOpenBounding`.
    if (field_6F2.GetCount() > 1) {
        for (INT nIndex = 0; nIndex < field_6F2.GetCount(); nIndex++) {
            delete field_6F2[nIndex];
        }
    }
    field_6F2.SetSize(0);
}

// 0x487460
void CGameDoor::AIUpdate()
{
    if (m_drawPoly > 0) {
        m_drawPoly--;
    }

    ProcessAI();

    if (g_pBaldurChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
        && g_pBaldurChitin->cNetwork.GetSessionHosting() == TRUE) {
        if (m_nAICounter++ == 225) {
            m_nAICounter = 0;

            CMessageDoorStatus* pMessage = new CMessageDoorStatus(this, m_id, m_id);

            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
}

// 0x47E040
void CGameDoor::DebugDump(const CString& message, BOOLEAN bEchoToScreen)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    CString sTemp;

    if (bEchoToScreen) {
        pWorld->DisplayText(CString(""),
            CString("DEBUG DUMP: CGameDoor"),
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

        sTemp.Format("Locked: %s\n", (m_dwFlags & 0x2) != 0 ? "TRUE" : "FALSE");
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

        sTemp.Format("Trap Detection Difficulty: %d%%", m_trapDetectionDifficulty);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Removal Difficulty: %d%%", m_trapDisarmingDifficulty);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Script: %.*s", RESREF_SIZE, m_scriptRes);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);

        sTemp.Format("Trap Launching Point: x=%d y=%d", m_posXTrapOrigin, m_posYTrapOrigin);
        pWorld->DisplayText(CString(""),
            sTemp,
            -1,
            FALSE);
    }
}

// 0x487C10
BOOL CGameDoor::IsOver(const CPoint& pt)
{
    if ((m_dwFlags & 0x2000) != 0) {
        return FALSE;
    }

    if ((m_dwFlags & 0x1) != 0) {
        if (!m_rOpenBounding.PtInRect(pt)) {
            return FALSE;
        }

        if (!g_pBaldurChitin->GetObjectGame()->GetGroup()->IsPartyLeader()) {
            return FALSE;
        }

        if (m_pOpenPolygon != NULL) {
            return CVidPoly::IsPtInPoly(m_pOpenPolygon, m_nOpenPolygon, pt);
        }
    } else {
        if (!m_rClosedBounding.PtInRect(pt)) {
            return FALSE;
        }

        if (!g_pBaldurChitin->GetObjectGame()->GetGroup()->IsPartyLeader()) {
            return FALSE;
        }

        if (m_pClosedPolygon != NULL) {
            return CVidPoly::IsPtInPoly(m_pClosedPolygon, m_nClosedPolygon, pt);
        }
    }

    return TRUE;
}

// 0x4892B0
void CGameDoor::RemoveFromArea()
{
    m_pArea->m_lTiledObjects.RemoveAt(m_tiledObject.m_posAreaList);

    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
        // __LINE__: 1269
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x489330
void CGameDoor::SetCursor(LONG nToolTip)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if ((m_dwFlags & 0x80) == 0 || (m_dwFlags & 0x100) != 0) {
        switch (pGame->GetState()) {
        case 0:
            if (pGame->GetGroup()->GetCount() != 0) {
                g_pBaldurChitin->GetObjectCursor()->SetCursor(m_cursorType, FALSE);
            } else {
                g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
            }
            break;
        case 1:
        case 3:
            CGameObject::SetCursor(nToolTip);
            break;
        case 2:
            switch (pGame->GetIconIndex()) {
            case 12:
                if ((m_dwFlags & 0x1) == 0 && (m_dwFlags & 0x2) != 0) {
                    g_pBaldurChitin->GetObjectCursor()->SetCursor(12, FALSE);
                } else {
                    CGameObject::SetCursor(nToolTip);
                }
                break;
            case 18:
            case 40:
            case 255:
                CGameObject::SetCursor(nToolTip);
                break;
            case 36:
                if (1) {
                    INT nNewCursor;
                    if (m_trapActivated != 0 && m_trapDetected != 0) {
                        nNewCursor = 38;
                    } else {
                        if ((m_dwFlags & 0x2) == 0) {
                            CGameObject::SetCursor(nToolTip);
                            break;
                        }

                        nNewCursor = 26;
                    }

                    SHORT nPortrait = g_pBaldurChitin->m_pEngineWorld->GetSelectedCharacter();

                    // NOTE: Uninline.
                    LONG nCharacterId = pGame->GetCharacterId(nPortrait);

                    CGameSprite* pSprite;

                    BYTE rc;
                    do {
                        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            reinterpret_cast<CGameObject**>(&pSprite),
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        if (nNewCursor == 26) {
                            if (pSprite->GetBaseStats()->m_skills[CGAMESPRITE_SKILL_OPEN_LOCK] == 0) {
                                g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                            }
                        } else {
                            if (pSprite->GetBaseStats()->m_skills[CGAMESPRITE_SKILL_DISABLE_DEVICE] == 0) {
                                g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                            }
                        }

                        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }
                break;
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
                // __LINE__: 1370
                UTIL_ASSERT(FALSE);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDoor.cpp
            // __LINE__: 1380
            UTIL_ASSERT(FALSE);
        }
    } else {
        CGameObject::SetCursor(nToolTip);
    }
}

// 0x48AC80
void CGameDoor::OnDoorStatusUpdate(BOOLEAN bDoorOpened, DWORD dwFlags, WORD nTrapActivated, WORD nTrapDetected)
{
    if ((m_dwFlags & 0x1) == 0 || bDoorOpened) {
        if ((m_dwFlags & 0x1) == 0 && bDoorOpened == TRUE) {
            m_dwFlags |= 0x1;
            m_pos = m_ptClosedDest;
            m_tiledObject.m_wAIState = CTiledObject::STATE_PRIMARY_TILE;

            if (m_pClosedSearch != NULL) {
                m_pArea->m_search.RemoveDoor(m_pClosedSearch, m_nClosedSearch);
            }

            if (m_pOpenSearch != NULL) {
                m_pArea->m_search.AddDoor(m_pOpenSearch,
                    m_nOpenSearch,
                    (m_dwFlags & 0x400) != 0);
            }
        }
    } else {
        m_dwFlags &= ~0x1;
        m_pos = m_ptOpenDest;
        m_tiledObject.m_wAIState = CTiledObject::STATE_SECONDARY_TILE;

        if (m_pOpenSearch != NULL) {
            m_pArea->m_search.RemoveDoor(m_pOpenSearch, m_nOpenSearch);
        }

        if (m_pClosedSearch != NULL) {
            m_pArea->m_search.AddDoor(m_pClosedSearch,
                m_nClosedSearch,
                (m_dwFlags & 0x400) != 0);
        }
    }

    m_dwFlags = dwFlags;
    m_trapDetected = nTrapDetected;
    m_trapActivated = nTrapActivated;
}

// 0x48B350
void CGameDoor::SetDrawPoly(SHORT time)
{
    if (m_drawPoly != time) {
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly) {
            CMessageSetDrawPoly* pMessage = new CMessageSetDrawPoly(time, GetId(), GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
    m_drawPoly = time;
}

// 0x453140
DWORD CGameDoor::GetFlags()
{
    return m_dwFlags;
}

// 0x453150
void CGameDoor::SetFlags(DWORD dwFlags)
{
    m_dwFlags = dwFlags;
}

// 0x45B700
BOOL CGameDoor::sub_45B700()
{
    return m_dwFlags & 0x1;
}

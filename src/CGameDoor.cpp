#include "CGameDoor.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUtil.h"
#include "CVidPoly.h"

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
void CGameDoor::SetCursor(int nToolTip)
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
                            if (pSprite->GetBaseStats()->m_skills[10] == 0) {
                                g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                            }
                        } else {
                            if (pSprite->GetBaseStats()->m_skills[5] == 0) {
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

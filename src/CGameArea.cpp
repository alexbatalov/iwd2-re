#include "CGameArea.h"

#include "CAIScript.h"
#include "CBaldurChitin.h"
#include "CChitin.h"
#include "CCreatureFile.h"
#include "CGameContainer.h"
#include "CGameDoor.h"
#include "CGameObject.h"
#include "CGameSound.h"
#include "CGameSpawning.h"
#include "CGameSprite.h"
#include "CGameStatic.h"
#include "CGameTiledObject.h"
#include "CGameTrigger.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CObjectMarker.h"
#include "CPathSearch.h"
#include "CProjectile.h"
#include "CResWED.h"
#include "CScreenLoad.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CSpawn.h"
#include "CTiledObject.h"
#include "CUtil.h"

// 0x8D212C
INT CGameArea::dword_8D212C;

// 0x8D2138
BOOLEAN CGameArea::byte_8D2138;

// 0x469B60
CGameArea::CGameArea(BYTE id)
{
    field_B0E = 0;
    m_bPicked = FALSE;
    m_pObjectMarker = NULL;
    m_firstRender = 0;
    m_dwLastProgressRenderTickCount = 0;
    m_dwLastProgressMsgTickCount = 0;
    m_sndAmbientDayVolume = 0;
    m_sndAmbientNightVolume = 0;
    field_3EC = 0;
    m_nAIIndex = 0;
    m_nCurrentSong = 0;
    m_id = id;
    m_nCharacters = 0;
    field_1EE = 0;
    m_pResWED = NULL;
    m_bAreaLoaded = 0;
    InitializeCriticalSection(&field_1FC);
    InitializeCriticalSection(&field_214);
    m_nListManipulationThreadCounter = 0;
    m_ListManipulationThreadId = 0;

    // NOTE: Inlining.
    if (m_nListManipulationThreadCounter > 0) {
        m_nListManipulationThreadCounter = m_nListManipulationThreadCounter - 1;
    }

    if (m_nListManipulationThreadCounter == 0) {
        m_ListManipulationThreadId = 0;
    }

    m_pGame = NULL;
    m_nScrollState = 0;
    m_nKeyScrollState = 0;
    m_bTravelSquare = FALSE;
    m_iPicked = CGameObjectArray::INVALID_INDEX;
    m_iPickedTarget = CGameObjectArray::INVALID_INDEX;
    m_nToolTip = 0;
    m_visibility.m_pDynamicHeight = NULL;
    memset(&m_header, 0, sizeof(m_header));
    m_groupMove = FALSE;
    field_432 = 0;
    field_434 = 0;
    m_pbmLumNight = NULL;
    field_41E = 0;
    m_nInitialAreaID = 0;
    m_nBattleSongCounter = 0;
    m_selectSquare.left = -1;
    m_selectSquare.top = -1;
    m_selectSquare.right = -1;
    m_selectSquare.bottom = -1;
    m_ptOldViewPos.x = -1;
    m_ptOldViewPos.y = -1;
    m_moveDest.x = -1;
    m_moveDest.y = -1;
    field_426 = -1;
    field_241 = 0;
    field_242 = CGameObjectArray::INVALID_INDEX;
    m_sndAmbientVolume = 100;
    m_cInfinity.m_pArea = this;
    m_nCurrentSong = -1;
    field_438 = 0;
    field_436 = 0;
    m_startedMusic = FALSE;
    field_AE6 = 1;
    m_startedMusicCounter = 10;

    // NOTE: This assignment is slightly incorrect. Original code refers to
    // other offsets (0x8A8168 and 0x8A8154 respectively). It can mean two
    // things:
    // - There was second set of terrain table defaults, which is exactly the
    // same as in `CGameObject`.
    // - Such split was a result of some compiler optimization.
    //
    // Since both sets have the same values, there is no harm to reuse what's
    // already present.
    memcpy(&m_terrainTable, CGameObject::DEFAULT_TERRAIN_TABLE, 16);
    memcpy(&m_visibleTerrainTable, CGameObject::DEFAULT_VISIBLE_TERRAIN_TABLE, 16);

    mpSpawner = NULL;

    dword_8D212C = 0;
    byte_8D2138 = 0;

    field_B16 = 0;
}

// 0x46A070
CGameArea::~CGameArea()
{
    EnterCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));

    if (mpSpawner != NULL) {
        delete mpSpawner;
        mpSpawner = NULL;
    }

    if (m_bAreaLoaded) {
        ClearMarshal();
    }

    DeleteCriticalSection(&field_1FC);

    if (m_nListManipulationThreadCounter > 0) {
        m_nListManipulationThreadCounter--;
    }

    if (m_nListManipulationThreadCounter == 0) {
        m_ListManipulationThreadId = 0;
    }

    DeleteCriticalSection(&field_214);

    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
}

// 0x46A2E0
INT CGameArea::SetListManipulationThreadId(DWORD ThreadID)
{
    if (ThreadID != 0) {
        if (m_nListManipulationThreadCounter > 0) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 295
            UTIL_ASSERT(m_ListManipulationThreadId == ThreadID);
        } else {
            m_ListManipulationThreadId = ThreadID;
        }

        m_nListManipulationThreadCounter++;
    } else {
        if (m_nListManipulationThreadCounter > 0) {
            m_nListManipulationThreadCounter--;
        }

        if (m_nListManipulationThreadCounter == 0) {
            m_ListManipulationThreadId = 0;
        }
    }

    return m_nListManipulationThreadCounter;
}

// 0x46A360
void CGameArea::AddObject(LONG id, BYTE listType)
{
    CTypedPtrList<CPtrList, int*>* pList;
    switch (listType) {
    case CGAMEOBJECT_LIST_FRONT:
        pList = &m_lVertSortAdd;
        break;
    case CGAMEOBJECT_LIST_BACK:
        pList = &m_lVertSortBackAdd;
        break;
    case CGAMEOBJECT_LIST_FLIGHT:
        pList = &m_lVertSortFlightAdd;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 358
        UTIL_ASSERT(FALSE);
    }

    pList->AddTail(reinterpret_cast<int*>(id));
}

// 0x46A7B0
void CGameArea::ApplyWindToAmbients(BYTE nPercentVolume)
{
    m_sndAmbientVolume = nPercentVolume;
    m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
    m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
}

// 0x46AF40
LONG CGameArea::GetGroundPile(const CPoint& ptPos)
{
    POSITION pos;
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;

    LONG iGroundPile = CGameObjectArray::INVALID_INDEX;

    CPoint ptGridPos;
    ptGridPos.x = ptPos.x / CPathSearch::GRID_SQUARE_SIZEX;
    ptGridPos.y = ptPos.y / CPathSearch::GRID_SQUARE_SIZEY;

    pos = m_lVertSortBack.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortBack.GetPrev(pos));

        rc = m_pGame->GetObjectArray()->GetShare(iObject,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pObject->GetObjectType() == CGameObject::TYPE_CONTAINER
                && static_cast<CGameContainer*>(pObject)->m_containerType == 4) {
                if (ptGridPos.x == pObject->GetPos().x / CPathSearch::GRID_SQUARE_SIZEX
                    && ptGridPos.y == pObject->GetPos().y / CPathSearch::GRID_SQUARE_SIZEY) {
                    iGroundPile = iObject;

                    m_pGame->GetObjectArray()->ReleaseShare(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);

                    break;
                }
            }

            m_pGame->GetObjectArray()->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    if (iGroundPile == CGameObjectArray::INVALID_INDEX) {
        pos = m_lVertSortBackAdd.GetTailPosition();
        while (pos != NULL) {
            iObject = reinterpret_cast<LONG>(m_lVertSortBackAdd.GetPrev(pos));

            rc = m_pGame->GetObjectArray()->GetShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pObject->GetObjectType() == CGameObject::TYPE_CONTAINER
                    && static_cast<CGameContainer*>(pObject)->m_containerType == 4) {
                    if (ptGridPos.x == pObject->GetPos().x / CPathSearch::GRID_SQUARE_SIZEX
                        && ptGridPos.y == pObject->GetPos().y / CPathSearch::GRID_SQUARE_SIZEY) {
                        iGroundPile = iObject;

                        m_pGame->GetObjectArray()->ReleaseShare(iObject,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);

                        break;
                    }
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }
    }

    return iGroundPile;
}

// 0x46F5A0
BOOLEAN CGameArea::CanSaveGame(STRREF& strError)
{
    CGameObjectArray* pObjectArray = m_pGame->GetObjectArray();
    POSITION pos;
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;

    if ((m_header.m_flags & 0x1) != 0) {
        strError = 16502;
        return FALSE;
    }

    pos = m_lVertSortFlight.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortFlight.GetPrev(pos));

        rc = pObjectArray->GetShare(iObject,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if (!pObject->CanSaveGame(strError)) {
                pObjectArray->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
                return FALSE;
            }

            pObjectArray->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSort.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSort.GetPrev(pos));

        rc = pObjectArray->GetShare(iObject,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if (!pObject->CanSaveGame(strError)) {
                pObjectArray->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
                return FALSE;
            }

            pObjectArray->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSortBack.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortBack.GetPrev(pos));

        rc = pObjectArray->GetShare(iObject,
            CGameObjectArray::THREAD_ASYNCH,
            &pObject,
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if (!pObject->CanSaveGame(strError)) {
                pObjectArray->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
                return FALSE;
            }

            pObjectArray->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    strError = -1;
    return TRUE;
}

// 0x46E3D0
void CGameArea::AIUpdate()
{
    POSITION pos;
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;

    if (!m_bAreaLoaded) {
        return;
    }

    SortLists();

    if (m_firstRender > 0) {
        if (m_firstRender <= 1 && m_pGame->GetVisibleArea() == this) {
            return;
        }

        m_firstRender--;
    }

    if (field_241 > 0) {
        field_241--;
    } else {
        field_242 = CGameObjectArray::INVALID_INDEX;
    }

    INT x;
    INT y;
    m_cInfinity.GetViewPosition(x, y);

    BOOL bMouseInPlayArea = g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineWorld
        && m_ptMousePos.x >= m_cInfinity.rViewPort.left
        && m_ptMousePos.x < m_cInfinity.rViewPort.right
        && m_ptMousePos.y >= m_cInfinity.rViewPort.top
        && m_ptMousePos.y < m_cInfinity.rViewPort.bottom;

    CPoint ptWorldMouse = m_cInfinity.GetWorldCoordinates(m_ptMousePos);

    if ((g_pBaldurChitin->GetObjectGame()->field_43E2 & 0x4000) != 0) {
        if (m_pGame->GetVisibleArea() == this
            && g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineWorld) {
            m_bTravelSquare = FALSE;
            if (m_ptOldViewPos.x != x || m_ptOldViewPos.y != y) {
                if (m_firstRender == 0) {
                    if (m_ptMousePos.x == 0 && x <= 0) {
                        if (m_nScrollState == 7
                            || (m_nScrollState == 8 && y <= 0)
                            || (m_nScrollState == 6 && y >= m_cInfinity.nAreaY - m_cInfinity.rViewPort.Height() - 1)) {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                            g_pBaldurChitin->GetObjectCursor()->m_nDirection = 6;
                            m_nScrollState = 9;
                        }
                    } else if (m_ptMousePos.x == CVideo::SCREENWIDTH - 1
                        && x >= m_cInfinity.nAreaX - m_cInfinity.rViewPort.Width() - 1) {
                        if (m_nScrollState == 3
                            || (m_nScrollState == 2 && y <= 0)
                            || (m_nScrollState == 4 && y >= m_cInfinity.nAreaY - m_cInfinity.rViewPort.Height() - 1)) {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                            g_pBaldurChitin->GetObjectCursor()->m_nDirection = 2;
                            m_nScrollState = 9;
                        }
                    } else if (m_ptMousePos.y == 0 && y <= 0) {
                        if (m_nScrollState == 1
                            || (m_nScrollState == 8 && x <= 0)
                            || (m_nScrollState == 2 && x >= m_cInfinity.nAreaX - m_cInfinity.rViewPort.Width() - 1)) {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                            g_pBaldurChitin->GetObjectCursor()->m_nDirection = 0;
                            m_nScrollState = 9;
                        }
                    } else if (m_ptMousePos.y == CVideo::SCREENHEIGHT - 1
                        && y >= m_cInfinity.nAreaY - m_cInfinity.rViewPort.Height() - 1) {
                        if (m_nScrollState == 5
                            || (m_nScrollState == 6 && x <= 0)
                            || (m_nScrollState == 4 && x >= m_cInfinity.nAreaX - m_cInfinity.rViewPort.Width() - 1)) {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                            g_pBaldurChitin->GetObjectCursor()->m_nDirection = 0;
                            m_nScrollState = 4;
                        }
                    }
                } else {
                    m_nScrollState = 0;
                    m_cInfinity.m_nScrollDelay = CInfinity::SCROLL_DELAY;
                }
            }

            if (m_groupMove) {
                if (abs(ptWorldMouse.x - m_moveDest.x) > 8
                    || abs(ptWorldMouse.y - m_moveDest.y) > 8) {
                    CPoint ptCursor;
                    if (bMouseInPlayArea) {
                        ptCursor.x = 2 * m_moveDest.x - ptWorldMouse.x;
                        ptCursor.y = 2 * m_moveDest.y - ptWorldMouse.y;
                    } else {
                        CPoint ptScreen;
                        ptScreen.x = min(max(m_cInfinity.rViewPort.left, m_ptMousePos.x), m_cInfinity.rViewPort.right - 1);
                        ptScreen.y = min(max(m_cInfinity.rViewPort.top, m_ptMousePos.y), m_cInfinity.rViewPort.bottom - 1);

                        CPoint ptWorld = m_cInfinity.GetWorldCoordinates(ptScreen);
                        ptCursor.x = 2 * m_moveDest.x - ptWorld.x;
                        ptCursor.y = 2 * m_moveDest.y - ptWorld.y;
                    }

                    m_pGame->GetGroup()->GroupDrawMove(m_moveDest,
                        m_pGame->m_curFormation,
                        ptCursor);

                    if (m_pGame->GetState() == 0) {
                        m_pGame->SetTempCursor(8);
                    }

                    if (m_pGame->GetState() == 3) {
                        if (m_selectSquare.left != -1) {
                            m_selectSquare.right += x - m_ptOldViewPos.x;
                            m_selectSquare.bottom += y - m_ptOldViewPos.y;
                        }
                    }
                } else {
                    m_pGame->GetGroup()->GroupCancelMove();
                    if (m_pGame->GetState() == 0) {
                        m_pGame->SetTempCursor(4);
                    }
                }
            } else {
                if (m_selectSquare.left != -1) {
                    m_selectSquare.right += x - m_ptOldViewPos.x;
                    m_selectSquare.bottom += y - m_ptOldViewPos.y;

                    if (m_pGame->GetState() == 0) {
                        m_pGame->SetTempCursor(0);
                    }
                }
            }

            m_ptOldViewPos.x = x;
            m_ptOldViewPos.y = y;

            if (m_nScrollState == 0) {
                if (bMouseInPlayArea) {
                    if (m_pGame->m_tempCursor == 4) {
                        BOOL bSquareVisible = m_visibility.IsTileExplored(m_visibility.PointToTile(ptWorldMouse));
                        if (m_iPicked != CGameObjectArray::INVALID_INDEX
                            && bSquareVisible) {
                            rc = m_pGame->GetObjectArray()->GetShare(m_iPicked,
                                CGameObjectArray::THREAD_ASYNCH,
                                &pObject,
                                INFINITE);
                            if (rc == CGameObjectArray::SUCCESS) {
                                pObject->SetCursor(m_nToolTip);
                                m_pGame->GetObjectArray()->ReleaseShare(m_iPicked,
                                    CGameObjectArray::THREAD_ASYNCH,
                                    INFINITE);
                            } else {
                                g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                            }
                        } else {
                            if (m_pGame->GetGroup()->GetCount() != 0) {
                                if (bSquareVisible) {
                                    SHORT searchSquareCode;
                                    CPoint mouseSearchSquare;
                                    mouseSearchSquare.x = ptWorldMouse.x / CPathSearch::GRID_SQUARE_SIZEX;
                                    mouseSearchSquare.y = ptWorldMouse.y / CPathSearch::GRID_SQUARE_SIZEY;
                                    if (m_search.GetLOSCost(mouseSearchSquare, m_terrainTable, searchSquareCode, 0) != CPathSearch::COST_IMPASSABLE) {
                                        switch (m_pGame->GetState()) {
                                        case 0:
                                            if (searchSquareCode == 14) {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(34, FALSE);
                                                m_bTravelSquare = TRUE;
                                            } else {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                                            }
                                            break;
                                        case 1:
                                        case 2:
                                            if (g_pBaldurChitin->GetObjectGame()->GetIconIndex() != -1) {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                                            } else {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(102, FALSE);
                                                g_pBaldurChitin->GetObjectCursor()->SetCustomCursor(g_pBaldurChitin->GetObjectGame()->m_iconResRef, FALSE, -1);
                                            }
                                            break;
                                        case 3:
                                            g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                                            break;
                                        default:
                                            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                                            // __LINE__: 2809
                                            UTIL_ASSERT(!"Invalid Game State");
                                        }
                                    } else {
                                        switch (m_pGame->GetState()) {
                                        case 0:
                                            g_pBaldurChitin->GetObjectCursor()->SetCursor(4, FALSE);
                                            break;
                                        case 1:
                                            if (g_pBaldurChitin->GetObjectGame()->GetIconIndex() != -1) {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(g_pBaldurChitin->GetObjectGame()->GetIconIndex(), FALSE);
                                            } else {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(20, FALSE);
                                            }
                                            break;
                                        case 2:
                                            if (g_pBaldurChitin->GetObjectGame()->GetIconIndex() != -1) {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(g_pBaldurChitin->GetObjectGame()->GetIconIndex(), FALSE);
                                                g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
                                            } else {
                                                g_pBaldurChitin->GetObjectCursor()->SetCursor(102, FALSE);
                                                g_pBaldurChitin->GetObjectCursor()->SetCustomCursor(g_pBaldurChitin->GetObjectGame()->m_iconResRef, FALSE, -1);
                                            }
                                            break;
                                        case 3:
                                            g_pBaldurChitin->GetObjectCursor()->SetCursor(16, FALSE);
                                            break;
                                        default:
                                            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                                            // __LINE__: 2845
                                            UTIL_ASSERT(!"Invalid Game State");
                                        }
                                    }
                                } else {
                                    g_pBaldurChitin->GetObjectCursor()->SetCursor(6, FALSE);
                                }
                            } else {
                                g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                            }
                        }
                    } else {
                        g_pBaldurChitin->GetObjectCursor()->SetCursor(m_pGame->m_tempCursor, FALSE);
                    }
                } else {
                    if (m_pGame->m_tempCursor == 4) {
                        rc = m_pGame->GetObjectArray()->GetShare(m_iPicked,
                            CGameObjectArray::THREAD_ASYNCH,
                            &pObject,
                            INFINITE);
                        if (rc == CGameObjectArray::SUCCESS) {
                            pObject->SetCursor(m_nToolTip);
                            m_pGame->GetObjectArray()->ReleaseShare(m_iPicked,
                                CGameObjectArray::THREAD_ASYNCH,
                                INFINITE);
                        } else {
                            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
                        }
                    } else {
                        g_pBaldurChitin->GetObjectCursor()->SetCursor(m_pGame->m_tempCursor, FALSE);
                    }
                }
            }
        }
    } else {
        m_nScrollState = 0;
        m_nKeyScrollState = 0;
        if (m_pGame->m_tempCursor != 4) {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(m_pGame->m_tempCursor, FALSE);
        } else {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
        }
    }

    BOOL bActive = m_pGame->GetWorldTimer()->m_active;

    m_nToolTip++;

    if (mpSpawner != NULL) {
        mpSpawner->Execute(this);
    }

    pos = m_lVertSortFlight.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortFlight.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pObject->DoAIUpdate(bActive, g_pChitin->nAUCounter)) {
                do {
                    rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED);

                if (rc == CGameObjectArray::SUCCESS) {
                    pObject->AIUpdate();

                    m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }

            m_pGame->GetObjectArray()->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSort.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSort.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (!m_bPicked
                && bMouseInPlayArea
                && m_pGame->GetVisibleArea() == this
                && pObject->IsOver(ptWorldMouse)) {
                if (m_iPicked != iObject) {
                    if (m_pGame->m_tempCursor == 101) {
                        m_pGame->m_tempCursor = 4;
                    }
                    m_nToolTip = 0;
                }

                m_iPicked = iObject;

                if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                    CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);
                    if (pSprite->Orderable(FALSE)) {
                        m_iPickedTarget = pSprite->GetTargetId();
                    }
                }

                m_bPicked = TRUE;
            }

            if (pObject->DoAIUpdate(bActive, g_pChitin->nAUCounter)) {
                do {
                    rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED);

                if (rc == CGameObjectArray::SUCCESS) {
                    pObject->AIUpdate();

                    m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }

            m_pGame->GetObjectArray()->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSortBack.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortBack.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (!m_bPicked
                && bMouseInPlayArea
                && m_pGame->GetVisibleArea() == this
                && pObject->IsOver(ptWorldMouse)) {
                if (m_iPicked != iObject) {
                    if (m_pGame->m_tempCursor == 101) {
                        m_pGame->m_tempCursor = 4;
                    }
                    m_nToolTip = 0;
                }

                m_iPicked = iObject;

                if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                    CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);
                    if (pSprite->Orderable(FALSE)) {
                        m_iPickedTarget = pSprite->GetTargetId();
                    }
                }

                m_bPicked = TRUE;
            }

            if (pObject->DoAIUpdate(bActive, g_pChitin->nAUCounter)) {
                do {
                    rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED);

                if (rc == CGameObjectArray::SUCCESS) {
                    pObject->AIUpdate();

                    m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                }
            }

            m_pGame->GetObjectArray()->ReleaseShare(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    if (m_pGame->GetVisibleArea() == this) {
        if (!m_bPicked) {
            if (bMouseInPlayArea) {
                if (m_pGame->m_tempCursor == 101) {
                    m_pGame->m_tempCursor = 4;
                }
            }

            m_nToolTip = 0;
            m_iPicked = CGameObjectArray::INVALID_INDEX;
            m_iPickedTarget = CGameObjectArray::INVALID_INDEX;
        }

        m_cInfinity.AIUpdate();
    }

    if (g_pBaldurChitin->nAUCounter % 2 == 0) {
        g_pBaldurChitin->cSoundMixer.UpdateSoundList();

        CGameAIArea* pAIArea;

        do {
            rc = m_pGame->GetObjectArray()->GetDeny(m_nAIIndex,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pAIArea),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED);

        if (rc == CGameObjectArray::SUCCESS) {
            pAIArea->ProcessAI();

            m_pGame->GetObjectArray()->ReleaseDeny(m_nAIIndex,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    INT nDeadCharacters = 0;
    for (SHORT nPortrait = 0; nPortrait < g_pBaldurChitin->GetObjectGame()->GetNumCharacters(); nPortrait++) {
        CGameSprite* pSprite;

        rc = m_pGame->GetObjectArray()->GetShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
        if (rc == CGameObjectArray::SUCCESS) {
            if ((pSprite->GetDerivedStats()->m_generalState & STATE_DEAD) != 0) {
                nDeadCharacters++;
            }

            m_pGame->GetObjectArray()->ReleaseShare(g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait),
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    if (nDeadCharacters == g_pBaldurChitin->GetObjectGame()->GetNumCharacters()) {
        if (m_nCurrentSong != 1) {
            g_pBaldurChitin->cSoundMixer.StartSong(1, 0x4 | 0x1);
            m_nCurrentSong = 1;
        }
    } else if (m_pGame->GetVisibleArea() == this
        && g_pBaldurChitin->GetActiveEngine() != g_pBaldurChitin->m_pEngineStore) {
        if (m_startedMusicCounter > 0) {
            m_startedMusicCounter--;
        }

        if (!m_startedMusic) {
            if (m_startedMusicCounter == 0) {
                m_startedMusic = TRUE;
                if (m_nCurrentSong != -1) {
                    INT nBattleSongCounter = m_nBattleSongCounter;
                    g_pBaldurChitin->cSoundMixer.StartSong(-1, 0x4 | 0x1);
                    SleepEx(500, FALSE);
                    PlaySong(m_nCurrentSong, 0x1);
                    m_nBattleSongCounter = nBattleSongCounter;
                } else {
                    g_pBaldurChitin->cSoundMixer.StartSong(-1, 0x4 | 0x1);
                }
            }
        } else {
            if (m_startedMusicCounter == 0) {
                if (m_nBattleSongCounter > 0) {
                    if (bActive) {
                        m_nBattleSongCounter--;
                    }

                    if (m_nBattleSongCounter > 0) {
                        if (m_nCurrentSong != 3) {
                            PlaySong(3, 0x2 | 0x1);
                        }
                    } else {
                        if ((m_header.m_flags & 0x4) == 0) {
                            if (m_nCurrentSong == 3) {
                                PlaySong(256, 0x2);
                            }
                        }
                    }
                }

                if ((m_header.m_flags & 0x4) == 0) {
                    if (m_pGame->GetVisibleArea() == this
                        && g_pChitin->cSoundMixer.m_nCurrentSong == -1) {
                        if (!g_pBaldurChitin->GetActiveEngine()->StopMusic()) {
                            m_nCurrentSong = -1;
                        }
                    }

                    if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDay()) {
                        PlaySong(-1, 0x4 | 0x2);
                        m_nCurrentSong = 0;
                        m_startedMusic = FALSE;
                        m_startedMusicCounter = 600;
                    } else if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsNight()) {
                        PlaySong(-1, 0x4 | 0x2);
                        m_nCurrentSong = 1;
                        m_startedMusic = FALSE;
                        m_startedMusicCounter = 600;
                    }
                }
            }
        }
    }
}

// 0x46F750
void CGameArea::CompressTime(DWORD deltaTime)
{
    LONG iObject;
    CGameObject* pObject;
    POSITION pos;
    BYTE rc;

    pos = m_lVertSortFlight.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortFlight.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                pObject->CompressTime(deltaTime);
            }

            m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSort.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSort.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                pObject->CompressTime(deltaTime);
            }

            m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    pos = m_lVertSortBack.GetTailPosition();
    while (pos != NULL) {
        iObject = reinterpret_cast<LONG>(m_lVertSortBack.GetPrev(pos));

        do {
            rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pObject->m_remotePlayerID) {
                pObject->CompressTime(deltaTime);
            }

            m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x46FE30
void CGameArea::ClearInput()
{
    m_nToolTip = 0;
    m_iPicked = CGameObjectArray::INVALID_INDEX;
    m_pGame->m_tempCursor = 0;
    m_pGame->GetGroup()->GroupCancelMove();
    m_pGame->m_tempCursor = 4;
    m_groupMove = FALSE;
    m_selectSquare.left = -1;
    m_selectSquare.top = -1;
    m_selectSquare.right = -1;
    m_selectSquare.bottom = -1;
}

// 0x470960
void CGameArea::ClearMarshal()
{
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;

    EnterCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
    g_pBaldurChitin->GetObjectGame()->BeginListManipulation(this);
    EnterCriticalSection(&field_1FC);

    if (m_pResWED != NULL) {
        m_nCharacters = -1;

        while (!m_lVertSortFlight.IsEmpty()) {
            iObject = reinterpret_cast<LONG>(m_lVertSortFlight.RemoveHead());

            do {
                rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pObject->IsProjectile()) {
                    static_cast<CProjectile*>(pObject)->RemoveSelf();
                } else {
                    pObject->RemoveFromArea();
                }

                m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }

        while (!m_lVertSort.IsEmpty()) {
            iObject = reinterpret_cast<LONG>(m_lVertSort.RemoveHead());

            do {
                rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pObject->IsProjectile()) {
                    static_cast<CProjectile*>(pObject)->RemoveSelf();
                } else {
                    pObject->RemoveFromArea();
                }

                m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }

        while (!m_lVertSortBack.IsEmpty()) {
            iObject = reinterpret_cast<LONG>(m_lVertSortBack.RemoveHead());

            do {
                rc = m_pGame->GetObjectArray()->GetDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (pObject->IsProjectile()) {
                    static_cast<CProjectile*>(pObject)->RemoveSelf();
                } else {
                    pObject->RemoveFromArea();
                }

                m_pGame->GetObjectArray()->ReleaseDeny(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        }

        m_lVertSortFlightRemove.RemoveAll();
        m_lVertSortRemove.RemoveAll();
        m_lVertSortBackRemove.RemoveAll();

        m_nCharacters = 0;

        m_cInfinity.FreeWED();
        g_pChitin->cDimm.ReleaseResObject(m_pResWED);
        m_pResWED = NULL;
    }

    while (field_41E) {
        Sleep(1);
    }

    m_sndAmbientDay.Stop();
    m_sndAmbientNight.Stop();
    m_visibility.Uninit();
    m_search.Uninit();
    m_bmHeight.GetRes()->Release();
    m_bmLum.GetRes()->Release();

    if (m_pbmLumNight != NULL) {
        m_pbmLumNight->GetRes()->Release();
        delete m_pbmLumNight;
        m_pbmLumNight = NULL;
    }

    if (m_visibility.m_pDynamicHeight != NULL) {
        delete m_visibility.m_pDynamicHeight;
        m_visibility.m_pDynamicHeight = NULL;
    }

    POSITION pos = m_entryPoints.GetHeadPosition();
    while (pos != NULL) {
        CAreaFileCharacterEntryPoint* pEntryPoint = m_entryPoints.GetNext(pos);
        delete pEntryPoint;
    }
    m_entryPoints.RemoveAll();

    m_bAreaLoaded = FALSE;

    LeaveCriticalSection(&field_1FC);
    g_pBaldurChitin->GetObjectGame()->EndListManipulation(this);
    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
}

// 0x470D20
BOOLEAN CGameArea::GetEntryPoint(const CString& sName, CPoint& ptEnter, SHORT& facing)
{
    POSITION pos = m_entryPoints.GetHeadPosition();
    while (pos != NULL) {
        CAreaFileCharacterEntryPoint* pEntryPoint = m_entryPoints.GetNext(pos);
        if (_strnicmp(pEntryPoint->m_entryName, sName, SCRIPTNAME_SIZE) == 0) {
            ptEnter.x = pEntryPoint->m_startX;
            ptEnter.y = pEntryPoint->m_startY;
            facing = static_cast<SHORT>(pEntryPoint->m_facing);
            return TRUE;
        }
    }
    return FALSE;
}

// 0x470D80
int CGameArea::GetHeightOffset(const CPoint& pt, BYTE listType)
{
    BYTE value;
    int nOffset = 0;

    if (listType != CGameObject::LIST_FLIGHT
        && m_bmHeight.GetRes() != NULL) {
        m_bmHeight.GetPixelValue(value, pt.x / 16, pt.y / 12, TRUE);
        nOffset = 8 - value;
        if (nOffset >= 7) {
            nOffset = 7;
        } else if (nOffset <= -7) {
            nOffset = -7;
        }

        if (nOffset == CGameObject::LIST_FRONT) {
            int index = (m_search.m_GridSquareDimensions.cx * (pt.y / 12) + pt.x / 16) / 2;
            if ((m_visibility.m_pDynamicHeight[index] & 0xF0) != 0) {
                nOffset -= 7;
            }
            if (nOffset <= -7) {
                nOffset = -7;
            }
        }
    }

    return nOffset;
}

// 0x470E60
void CGameArea::IncrHeightDynamic(const CPoint& point)
{
    int index = (m_search.m_GridSquareDimensions.cx * (point.y / 12) + point.x / 16) / 2;
    if ((m_visibility.m_pDynamicHeight[index] & 0xF0) < 0xF) {
        m_visibility.m_pDynamicHeight[index] += 16;
    }
}

// 0x470EC0
void CGameArea::DecrHeightDynamic(const CPoint& point)
{
    int index = (m_search.m_GridSquareDimensions.cx * (point.y / 12) + point.x / 16) / 2;
    if ((m_visibility.m_pDynamicHeight[index] & 0xF0) != 0) {
        m_visibility.m_pDynamicHeight[index] -= 16;
    }
}

// 0x470F10
COLORREF CGameArea::GetTintColor(const CPoint& cPoint, BYTE listType)
{
    COLORREF rgbColor = RGB(255, 255, 255);

    // TODO: Incomplete.

    return rgbColor;
}

// 0x472DE0
void CGameArea::Unmarshal(BYTE* pArea, LONG areaSize, const CString& sName, BOOLEAN bProgressBarInPlace)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
    // __LINE__: 4939
    UTIL_ASSERT(pArea != NULL && areaSize > 0);

    DWORD dwPerArea;
    if (bProgressBarInPlace == TRUE) {
        dwPerArea = CInfGame::PROGRESSBAR_AREA_ADDITIONAL / 22;
        ProgressBarCallback(0, TRUE);
    }

    if (m_bAreaLoaded) {
        ClearMarshal();
    }

    m_pGame = g_pBaldurChitin->GetObjectGame();

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    DWORD cnt = 8;

    areaSize -= cnt;
    areaSize -= sizeof(CAreaFileHeader);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
    // __LINE__: 4939
    UTIL_ASSERT(areaSize > 0);

    memcpy(&m_header, pArea + cnt, sizeof(CAreaFileHeader));
    cnt += sizeof(CAreaFileHeader);

    DWORD deltaTime;
    if (m_header.m_lastSaved) {
        deltaTime = m_pGame->GetWorldTimer()->m_gameTime - m_header.m_lastSaved * CTimerWorld::TIMESCALE_MSEC_PER_SEC + 1;
    } else {
        deltaTime = 0;
    }

    memcpy(m_header.m_areaName, (LPCSTR)sName, RESREF_SIZE);

    CString cStr(CString((char*)m_header.m_areaName, RESREF_SIZE).GetBuffer(RESREF_SIZE + 1));

    m_bmLum.SetResRef(CResRef(cStr + "LM"), TRUE, TRUE);
    m_bmLum.m_bDoubleSize = FALSE;
    m_bmLum.GetRes()->Demand();

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    m_bmHeight.SetResRef(CResRef(cStr + "HT"), TRUE, TRUE);
    m_bmHeight.m_bDoubleSize = FALSE;
    m_bmHeight.GetRes()->Demand();

    m_search.Init(this, cStr + "SR");

    CPoint ptLocation(-1, -1);
    if (m_pGame->GetRuleTables().m_tMasterArea.Find(cStr, ptLocation, TRUE)) {
        m_pGame->m_pGameAreaMaster = this;
    }

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    m_visibility.m_pDynamicHeight = new BYTE[m_search.m_GridSquareDimensions.cx * m_search.m_GridSquareDimensions.cy];
    if (m_visibility.m_pDynamicHeight == NULL) {
        return;
    }

    memset(m_visibility.m_pDynamicHeight, 0, m_search.m_GridSquareDimensions.cx * m_search.m_GridSquareDimensions.cy);

    m_pResWED = static_cast<CResWED*>(g_pChitin->cDimm.GetResObject(CResRef(m_header.m_areaName), 1001, TRUE));
    if (m_pResWED == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 5033
        UTIL_ASSERT_MSG(FALSE, (LPCSTR)("Missing WED file: " + cStr));
    }

    m_pResWED->Request();

    m_cInfinity.AttachWED(m_pResWED, m_header.m_areaType, TRUE);
    m_cInfinity.AttachVRamPool(&(g_pBaldurChitin->GetObjectGame()->m_cVRamPool));
    m_cInfinity.InitViewPort(CInfinity::stru_8E79B8);
    m_cInfinity.SetViewPosition(0, 0, TRUE);

    m_ptOldViewPos.x = 0;
    m_ptOldViewPos.y = 0;

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    CAreaFileOffsets* offsets = reinterpret_cast<CAreaFileOffsets*>(pArea + cnt);
    areaSize -= sizeof(CAreaFileOffsets);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
    // __LINE__: 5054
    UTIL_ASSERT(areaSize >= 0);

    m_visibility.Init(this);

    if (offsets->m_visibilityMapCount != 0) {
        m_visibility.Unmarshal(pArea + offsets->m_visibilityMapOffset,
            offsets->m_visibilityMapCount);
    }

    if (offsets->m_areaSoundsAndMusicOffset != 0) {
        memcpy(&m_headerSound, pArea + offsets->m_areaSoundsAndMusicOffset, sizeof(CAreaSoundsAndMusic));
        areaSize -= sizeof(CAreaSoundsAndMusic);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 5065
        UTIL_ASSERT(areaSize >= 0);

        if (m_headerSound.m_dayAmbientVolume > 100) {
            m_headerSound.m_dayAmbientVolume = 100;
        }

        if (m_headerSound.m_nightAmbientVolume > 100) {
            m_headerSound.m_nightAmbientVolume = 100;
        }
    } else {
        memset(&m_headerSound, 0, sizeof(CAreaSoundsAndMusic));
        m_headerSound.m_dayMusic = -1;
        m_headerSound.m_nightMusic = -1;
        m_headerSound.m_battleWinningMusic = -1;
        m_headerSound.m_battleStandOffMusic = -1;
        m_headerSound.m_battleLosingMusic = -1;
        m_headerSound.m_alt1Music0 = -1;
        m_headerSound.m_alt1Music1 = -1;
        m_headerSound.m_alt1Music2 = -1;
        m_headerSound.m_alt1Music3 = -1;
        m_headerSound.m_alt1Music4 = -1;
    }

    m_startedMusicCounter = 10;

    ULONG nDayTime = g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->GetCurrentDayTime();
    m_nCurrentSong = (nDayTime < CTimerWorld::TIME_DAY || nDayTime >= CTimerWorld::TIME_DUSK)
        && (nDayTime >= CTimerWorld::TIME_DAY || nDayTime < CTimerWorld::TIME_DAWN);

    if (offsets->m_restingEncounterOffset != 0) {
        memcpy(&m_headerRestEncounter, pArea + offsets->m_restingEncounterOffset, sizeof(CAreaFileRestEncounter));
        areaSize -= sizeof(CAreaFileRestEncounter);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 5106
        UTIL_ASSERT(areaSize >= 0);
    } else {
        memset(&m_headerRestEncounter, 0, sizeof(CAreaFileRestEncounter));
    }

    m_pObjectMarker = new CObjectMarker();
    if (m_pObjectMarker == NULL) {
        return;
    }

    INIFile.SetFileName(sName);
    INIFile.Load(sName);

    if (mpSpawner != NULL) {
        delete mpSpawner;
        mpSpawner = NULL;
    }

    mpSpawner = new CSpawnFile(&INIFile);

    // TODO: Incomplete.

    // CREATURES
    CCreatureFile creatureData;
    CVariable creatureName;

    if (offsets->m_creatureTableCount != 0) {
        for (DWORD nCreature = 0; nCreature < offsets->m_creatureTableCount; nCreature++) {
            CAreaFileCreature* pCreature = reinterpret_cast<CAreaFileCreature*>(pArea + offsets->m_creatureTableOffset) + nCreature;

            areaSize -= sizeof(CAreaFileCreature);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5197
            UTIL_ASSERT(areaSize >= 0);

            if (bProgressBarInPlace) {
                ProgressBarCallback(8 * dwPerArea / offsets->m_creatureTableCount, FALSE);
            }

            CGameSprite* pSprite = NULL;
            if (pCreature->m_creatureData[0] != '\0') {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5211
                UTIL_ASSERT(m_header.m_lastSaved == 0);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5211
                UTIL_ASSERT(pCreature->m_creatureSize == 0);

                if (pCreature->m_expirationTime == -1
                    || pCreature->m_expirationTime * CTimerWorld::TIMESCALE_MSEC_PER_SEC > m_pGame->GetWorldTimer()->m_gameTime) {
                    // NOTE: Uninline.
                    creatureData.SetResRef(CResRef(pCreature->m_creatureData), TRUE, TRUE);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                    // __LINE__: 5237
                    UTIL_ASSERT_MSG(creatureData.GetDataSize(),
                        CString("Creature file not found ") + CString(reinterpret_cast<char*>(pCreature->m_creatureData), RESREF_SIZE).GetBuffer(RESREF_SIZE + 1));

                    pSprite = new CGameSprite(creatureData.GetData(),
                        creatureData.GetDataSize(),
                        0,
                        pCreature->m_type,
                        -1,
                        pCreature->m_huntingRange,
                        pCreature->m_followRange,
                        pCreature->m_timeOfDayVisible,
                        CPoint(pCreature->m_startingPosX, pCreature->m_startingPosY),
                        pCreature->m_facing);

                    pSprite->SetResRef(CResRef(pCreature->m_creatureData));

                    if ((pCreature->m_dwFlags & 0x8) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x8000;

                        CAIObjectType typeAI = pSprite->GetAIType();
                        typeAI.m_nEnemyAlly = CAIObjectType::EA_EVILCUTOFF;
                        pSprite->SetAIType(typeAI, TRUE, TRUE);
                    }

                    if ((pCreature->m_dwFlags & 0x2) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x10000;
                    }

                    if ((pCreature->m_dwFlags & 0x4) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x20000;
                    }

                    creatureData.ReleaseData();
                }
            } else {
                areaSize -= pCreature->m_creatureSize;

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5309
                UTIL_ASSERT(areaSize >= 0);

                if (pCreature->m_expirationTime == -1
                    || pCreature->m_expirationTime * CTimerWorld::TIMESCALE_MSEC_PER_SEC > m_pGame->GetWorldTimer()->m_gameTime) {
                    pSprite = new CGameSprite(pArea + pCreature->m_creatureOffset,
                        pCreature->m_creatureSize,
                        0,
                        pCreature->m_type,
                        pCreature->m_expirationTime != -1
                            ? pCreature->m_expirationTime * CTimerWorld::TIMESCALE_MSEC_PER_SEC
                            : -1,
                        pCreature->m_huntingRange,
                        pCreature->m_followRange,
                        pCreature->m_timeOfDayVisible,
                        CPoint(pCreature->m_startingPosX, pCreature->m_startingPosY),
                        pCreature->m_facing);

                    pSprite->SetResRef(CResRef(pCreature->m_creatureData));

                    if ((pCreature->m_dwFlags & 0x8) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x8000;

                        CAIObjectType typeAI = pSprite->GetAIType();
                        typeAI.m_nEnemyAlly = CAIObjectType::EA_EVILCUTOFF;
                        pSprite->SetAIType(typeAI, TRUE, TRUE);
                    }

                    if ((pCreature->m_dwFlags & 0x2) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x10000;
                    }

                    if ((pCreature->m_dwFlags & 0x4) != 0) {
                        pSprite->GetBaseStats()->m_flags |= 0x20000;
                    }
                }
            }

            if (pSprite != NULL) {
                if ((pSprite->GetBaseStats()->m_generalState & STATE_DEAD) != 0
                    && pSprite->GetAnimation()->CanLieDown()) {
                    pSprite->AddToArea(this,
                        CPoint(pCreature->m_posX, pCreature->m_posY),
                        0,
                        CGameObject::LIST_BACK);
                } else {
                    pSprite->AddToArea(this,
                        CPoint(pCreature->m_posX, pCreature->m_posY),
                        0,
                        pSprite->GetAnimation()->GetListType());
                }

                pSprite->LoadAreaInformation(pCreature);

                if (pSprite->GetAIType().m_nEnemyAlly <= CAIObjectType::EA_CONTROLCUTOFF
                    && pSprite->GetAIType().m_nEnemyAlly == CAIObjectType::EA_FAMILIAR) {
                    g_pBaldurChitin->GetObjectGame()->AddCharacterToAllies(pSprite->GetId());
                }

                if (pSprite->CompressTime(deltaTime)) {
                    creatureName.SetName(CString(pSprite->GetScriptName()));
                    creatureName.m_intValue = pSprite->GetId();
                    m_namedCreatures.AddKey(creatureName);
                }
            }
        }
    }

    // VARIABLES
    CVariable variable;
    g_pBaldurChitin->GetObjectGame()->field_1B84 = 1;

    if (offsets->m_areaScriptVariablesCount != 0) {
        for (DWORD nVariable = 0; nVariable < offsets->m_areaScriptVariablesCount; nVariable++) {
            CAreaVariable* pAreaVariable = reinterpret_cast<CAreaVariable*>(pArea + offsets->m_areaScriptVariablesOffset) + nVariable;

            // NOTE: Uninline.
            variable = *static_cast<CVariable*>(pAreaVariable);

            areaSize -= sizeof(CAreaVariable);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5398
            UTIL_ASSERT(areaSize >= 0);

            m_variables.AddKey(variable);
        }
    }

    g_pBaldurChitin->GetObjectGame()->field_1B84 = 0;

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // ENTRY POINTS
    if (offsets->m_characterEntryPointTableCount != 0) {
        for (DWORD nEntryPoint = 0; nEntryPoint < offsets->m_characterEntryPointTableCount; nEntryPoint++) {
            CAreaFileCharacterEntryPoint* pEntryPoint = new CAreaFileCharacterEntryPoint();

            if (pEntryPoint == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5416
                UTIL_ASSERT(FALSE);
            }

            memcpy(pEntryPoint,
                pArea + offsets->m_characterEntryPointTableOffset + sizeof(CAreaFileCharacterEntryPoint) * nEntryPoint,
                sizeof(CAreaFileCharacterEntryPoint));

            areaSize -= sizeof(CAreaFileCharacterEntryPoint);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5421
            UTIL_ASSERT(areaSize >= 0);
        }
    }

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // DOORS
    if (offsets->m_doorObjectListCount != 0) {
        for (DWORD nDoor = 0; nDoor < offsets->m_doorObjectListCount; nDoor++) {
            CAreaFileDoorObject* pDoorObject = reinterpret_cast<CAreaFileDoorObject*>(pArea + offsets->m_doorObjectListOffset) + nDoor;
            areaSize -= sizeof(CAreaFileDoorObject);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5439
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CAreaPoint) * (pDoorObject->m_openSelectionPointCount + pDoorObject->m_closedSelectionPointCount + pDoorObject->m_openSearchSquaresCount + pDoorObject->m_closedSearchSquaresCount);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5444
            UTIL_ASSERT(areaSize >= 0);

            CGameDoor* pDoor = new CGameDoor(this,
                pDoorObject,
                reinterpret_cast<CAreaPoint*>(pArea + offsets->m_pointsOffset),
                offsets->m_pointsCount);

            if (pDoor == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5449
                UTIL_ASSERT(FALSE);
            }

            pDoor->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_doorObjectListCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_doorObjectListCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // TRIGGERS
    if (offsets->m_triggerObjectListCount != 0) {
        for (DWORD nTrigger = 0; nTrigger < offsets->m_triggerObjectListCount; nTrigger++) {
            CAreaFileTriggerObject* pTriggerObject = reinterpret_cast<CAreaFileTriggerObject*>(pArea + offsets->m_triggerObjectListOffset) + nTrigger;
            areaSize -= sizeof(CAreaFileTriggerObject);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5480
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CAreaPoint) * pTriggerObject->m_pickPointCount;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5482
            UTIL_ASSERT(areaSize >= 0);

            CGameTrigger* pTrigger = new CGameTrigger(this,
                pTriggerObject,
                reinterpret_cast<CAreaPoint*>(pArea + offsets->m_pointsOffset),
                offsets->m_pointsCount);

            if (pTrigger == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5487
                UTIL_ASSERT(FALSE);
            }

            pTrigger->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_triggerObjectListCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_triggerObjectListCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // TILED
    if (offsets->m_tiledObjectListCount != 0) {
        for (DWORD nTiledObject = 0; nTiledObject < offsets->m_tiledObjectListCount; nTiledObject++) {
            CAreaFileTiledObject* pTiledObject = reinterpret_cast<CAreaFileTiledObject*>(pArea + offsets->m_tiledObjectListOffset) + nTiledObject;
            areaSize -= sizeof(CAreaFileTiledObject);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5513
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CAreaPoint) * pTiledObject->m_primarySearchSquaresCount;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5515
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CAreaPoint) * pTiledObject->m_secondarySearchSquaresCount;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5517
            UTIL_ASSERT(areaSize >= 0);

            CGameTiledObject* pTiled = new CGameTiledObject(this,
                pTiledObject,
                reinterpret_cast<CAreaPoint*>(pArea + offsets->m_pointsOffset),
                offsets->m_pointsCount);

            if (pTiled == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5522
                UTIL_ASSERT(FALSE);
            }

            pTiled->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_tiledObjectListCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_tiledObjectListCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // SPAWNINGS
    if (offsets->m_randomMonsterSpawningPointTableCount != 0) {
        for (DWORD nSpawning = 0; nSpawning < offsets->m_randomMonsterSpawningPointTableCount; nSpawning++) {
            CAreaFileRandomMonsterSpawningPoint* pSpawnObject = reinterpret_cast<CAreaFileRandomMonsterSpawningPoint*>(pArea + offsets->m_randomMonsterSpawningPointTableOffset) + nSpawning;
            areaSize -= sizeof(CAreaFileRandomMonsterSpawningPoint);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5554
            UTIL_ASSERT(areaSize >= 0);

            CGameSpawning* pSpawning = new CGameSpawning(this, pSpawnObject);

            if (pSpawning == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5564
                UTIL_ASSERT(FALSE);
            }

            pSpawning->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_randomMonsterSpawningPointTableCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_randomMonsterSpawningPointTableCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // SOUNDS
    if (offsets->m_soundObjectCount != 0) {
        for (DWORD nSound = 0; nSound < offsets->m_soundObjectCount; nSound++) {
            CAreaFileSoundObject* pSoundObject = reinterpret_cast<CAreaFileSoundObject*>(pArea + offsets->m_soundObjectOffset) + nSound;
            areaSize -= sizeof(CAreaFileSoundObject);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5591
            UTIL_ASSERT(areaSize >= 0);

            CGameSound* pSound = new CGameSound(this, pSoundObject);

            if (pSound == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5600
                UTIL_ASSERT(FALSE);
            }

            pSound->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_soundObjectCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_soundObjectCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // STATICS
    if (offsets->m_staticObjectListCount != 0) {
        for (DWORD nStatic = 0; nStatic < offsets->m_staticObjectListCount; nStatic++) {
            CAreaFileStaticObject* pStaticObject = reinterpret_cast<CAreaFileStaticObject*>(pArea + offsets->m_staticObjectListOffset) + nStatic;
            areaSize -= sizeof(CAreaFileStaticObject);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5623
            UTIL_ASSERT(areaSize >= 0);

            CGameStatic* pStatic = new CGameStatic(this, pStaticObject);

            if (pStatic == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5627
                UTIL_ASSERT(FALSE);
            }

            pStatic->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_staticObjectListCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_staticObjectListCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    // CONTAINERS
    if (offsets->m_containerListCount != 0) {
        for (DWORD nContainer = 0; nContainer < offsets->m_containerListCount; nContainer++) {
            CAreaFileContainer* pContainerObject = reinterpret_cast<CAreaFileContainer*>(pArea + offsets->m_containerListOffset) + nContainer;
            areaSize -= sizeof(CAreaFileContainer);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5660
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CAreaPoint) * pContainerObject->m_pickPointCount;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5662
            UTIL_ASSERT(areaSize >= 0);

            areaSize -= sizeof(CCreatureFileItem) * pContainerObject->m_itemCount;

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5664
            UTIL_ASSERT(areaSize >= 0);

            CGameContainer* pContainer = new CGameContainer(this,
                pContainerObject,
                reinterpret_cast<CAreaPoint*>(pArea + offsets->m_pointsOffset),
                offsets->m_pointsCount,
                reinterpret_cast<CCreatureFileItem*>(pArea + offsets->m_itemObjectsOffset),
                offsets->m_itemObjectsCount);

            if (pContainer == NULL) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 5669
                UTIL_ASSERT(FALSE);
            }

            pContainer->CompressTime(deltaTime);

            if (bProgressBarInPlace) {
                ProgressBarCallback(dwPerArea / offsets->m_containerListCount, FALSE);
            }
        }
    }

    if (bProgressBarInPlace && offsets->m_containerListCount == 0) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    CGameAIArea* pAIArea = new CGameAIArea();
    pAIArea->SetDefaultScript(new CAIScript(CResRef(cStr)));
    m_nAIIndex = pAIArea->GetId();
    pAIArea->AddToArea(this, CPoint(0, 0), 0, CGameObject::LIST_BACK);

    m_firstRender = 8;
    m_bAreaLoaded = TRUE;
    m_nCharacters = -1;

    if (bProgressBarInPlace) {
        ProgressBarCallback(dwPerArea, FALSE);
    }

    if (g_pBaldurChitin->GetObjectGame()->m_pGameAreaMaster == this) {
        g_pBaldurChitin->m_pEngineWorld->m_weather.ResetWeather(this);
    }

    m_cInfinity.CacheTiles();

    g_pBaldurChitin->GetObjectGame()->m_cMoveList.CheckLoad(this);

    if (offsets->m_userMapNotesCount != 0) {
        CAreaUserNote cAreaNote;
        for (DWORD nNote = 0; nNote < offsets->m_userMapNotesCount; nNote++) {
            areaSize -= sizeof(CAreaUserNote);
            memcpy(&cAreaNote,
                pArea + offsets->m_userMapNotesOffset + sizeof(CAreaUserNote) * nNote,
                sizeof(CAreaUserNote));

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 5733
            UTIL_ASSERT(areaSize >= 0);

            m_cGameAreaNotes.AddANote(cAreaNote);
        }
    }

    CString sExtraVarName;

    // FIXME: Unsafe (UB when area name is exactly 8 chars).
    sExtraVarName = (LPCSTR)m_header.m_areaName;
    sExtraVarName += "_Visited";

    CVariable* pVisited = g_pBaldurChitin->GetObjectGame()->GetVariables()->FindKey(sExtraVarName);
    if (pVisited != NULL) {
        pVisited->m_intValue = 1;
    } else {
        CVariable cVisited;
        cVisited.SetName(sExtraVarName);
        cVisited.m_intValue = 1;
        g_pBaldurChitin->GetObjectGame()->GetVariables()->AddKey(cVisited);
    }

    // FIXME: Unsafe (UB when area name is exactly 8 chars).
    sExtraVarName = (LPCSTR)m_header.m_areaName;
    sExtraVarName += "_REVEALED";

    CVariable* pRevealed = g_pBaldurChitin->GetObjectGame()->GetVariables()->FindKey(sExtraVarName);
    if (pRevealed != NULL) {
        if (pRevealed == 0) {
            pRevealed->m_intValue = 1;
        }
    } else {
        CVariable cRevealed;
        cRevealed.SetName(sExtraVarName);
        cRevealed.m_intValue = 1;
        g_pBaldurChitin->GetObjectGame()->GetVariables()->AddKey(cRevealed);
    }

    g_pBaldurChitin->GetObjectGame()->field_1B86 = "";
}

// NOTE: Similar to `CInfGame::ProgressBarCallback`.
//
// 0x474E10
void CGameArea::ProgressBarCallback(DWORD dwSize, BOOLEAN bInitialize)
{
    if (bInitialize == TRUE) {
        m_dwLastProgressRenderTickCount = GetTickCount() - 250;
        m_dwLastProgressMsgTickCount = GetTickCount() - 5000;
    }

    g_pChitin->cProgressBar.m_nActionProgress += dwSize;

    if (GetTickCount() - m_dwLastProgressMsgTickCount >= 1000) {
        m_dwLastProgressMsgTickCount = GetTickCount();

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            g_pBaldurChitin->GetBaldurMessage()->SendProgressBarStatus(g_pChitin->cProgressBar.m_nActionProgress,
                g_pChitin->cProgressBar.m_nActionTarget,
                g_pChitin->cProgressBar.m_bWaiting,
                g_pChitin->cProgressBar.m_nWaitingReason,
                g_pChitin->cProgressBar.m_bTimeoutVisible,
                g_pChitin->cProgressBar.m_nSecondsToTimeout);
        }
    }

    if (GetTickCount() - m_dwLastProgressRenderTickCount >= 250) {
        m_dwLastProgressRenderTickCount = GetTickCount();

        g_pChitin->m_bDisplayStale = TRUE;
        g_pChitin->cDimm.field_0 = 1;
        g_pChitin->cDimm.field_4 = 1;
        SleepEx(25, TRUE);
    }
}

// 0x474F00
void CGameArea::SetListenPosition()
{
    BYTE cnt;
    BYTE range;
    CPoint ptListen;
    CPoint ptCheck;

    ptListen.x = m_cInfinity.nNewX + m_cInfinity.rViewPort.Width() / 2;
    ptListen.y = m_cInfinity.nNewY + m_cInfinity.rViewPort.Height() / 2;

    if (m_visibility.IsTileExplored(m_visibility.PointToTile(ptListen))) {
        g_pBaldurChitin->cSoundMixer.SetListenPosition(ptListen.x, ptListen.y, 0);
        return;
    }

    cnt = 0;
    range = m_cInfinity.rViewPort.Width() / CVisibilityMap::SQUARE_SIZEX;
    ptCheck.x = m_cInfinity.nNewX + CVisibilityMap::SQUARE_SIZEX / 2;
    ptCheck.y = m_cInfinity.nNewY + m_cInfinity.rViewPort.Height() / 2;
    while (cnt < range) {
        if (m_visibility.IsTileExplored(m_visibility.PointToTile(ptCheck))) {
            g_pBaldurChitin->cSoundMixer.SetListenPosition(ptListen.x, ptListen.y, 0);
            return;
        }
        ptCheck.x += CVisibilityMap::SQUARE_SIZEX;
        cnt++;
    }

    cnt = 0;
    range = m_cInfinity.rViewPort.Width() / CVisibilityMap::SQUARE_SIZEX;
    ptCheck.x = m_cInfinity.nNewX + m_cInfinity.rViewPort.Width() / 2;
    ptCheck.y = m_cInfinity.nNewY + CVisibilityMap::SQUARE_SIZEY / 2;
    while (cnt < range) {
        if (m_visibility.IsTileExplored(m_visibility.PointToTile(ptCheck))) {
            g_pBaldurChitin->cSoundMixer.SetListenPosition(ptListen.x, ptListen.y, 0);
            return;
        }
        ptCheck.y += CVisibilityMap::SQUARE_SIZEY;
        cnt++;
    }
}

// 0x4750E0
void CGameArea::OnActivation()
{
    SetListenPosition();

    m_ptMousePos = g_pChitin->m_ptPointer;
    m_nScrollState = 0;
    m_nKeyScrollState = 0;
    m_cInfinity.m_nScrollDelay = CInfinity::SCROLL_DELAY;
    m_cInfinity.bRefreshVRamRect = TRUE;

    if (g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
        g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StopTime();
    }

    if (g_pBaldurChitin->GetObjectGame()->GetVisibleArea() == this) {
        g_pBaldurChitin->cSoundMixer.m_nActiveArea = reinterpret_cast<DWORD>(this);
        g_pBaldurChitin->cSoundMixer.UpdateSoundList();

        if (g_pBaldurChitin->field_1C4A == 1 && byte_8D2138 == TRUE) {
            if (dword_8D212C == g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nVolumeAmbients) {
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, dword_8D212C);
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, dword_8D212C);
            } else {
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nVolumeAmbients);
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nVolumeAmbients);
            }
            byte_8D2138 = FALSE;
        } else {
            g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nVolumeAmbients);
            g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, g_pBaldurChitin->GetObjectGame()->GetOptions()->m_nVolumeAmbients);
        }

        SetTimeOfDay(m_pGame->GetWorldTimer()->m_gameTime % CTimerWorld::TIMESCALE_MSEC_PER_DAY, FALSE);
        m_cInfinity.UpdateLightning();
        SetSoundEnvironment();
        g_pBaldurChitin->m_pEngineWorld->m_weather.OnAreaChange(FALSE);
        m_firstRender = 8;

        if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDay()) {
            m_nCurrentSong = 0;
        } else if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsNight()) {
            m_nCurrentSong = 1;
        }

        if (m_nCurrentSong != -1) {
            if (!g_pBaldurChitin->cSoundMixer.sub_7ACA30()) {
                PlaySong(m_nCurrentSong, 5);
            }
        }

        g_pBaldurChitin->GetObjectGame()->ApplyVolumeSliders(TRUE);
    }
}

// 0x475330
void CGameArea::OnDeactivation()
{
    m_selectSquare.left = -1;
    m_selectSquare.top = -1;
    m_selectSquare.right = -1;
    m_selectSquare.bottom = -1;
    m_groupMove = FALSE;

    if (!m_pGame->field_43E6) {
        m_pGame->m_tempCursor = 4;
    }

    if (!g_pBaldurChitin->field_1C4A) {
        g_pBaldurChitin->cSoundMixer.m_nActiveArea = -1;
        g_pBaldurChitin->cSoundMixer.UpdateSoundList();
    } else {
        if (!byte_8D2138) {
            dword_8D212C = g_pBaldurChitin->cSoundMixer.GetChannelVolume(16);
            if (dword_8D212C > 0) {
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, dword_8D212C / 2);
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, dword_8D212C / 2);
            } else {
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, 0);
                g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, 0);
            }
            byte_8D2138 = TRUE;
        }
    }

    g_pBaldurChitin->sub_4286B0(m_resRef, g_pBaldurChitin->cSoundMixer.m_nCurrentSong);

    m_firstRender = 0;
}

// 0x475440
void CGameArea::OnActionButtonDown(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x475DC0
void CGameArea::OnActionButtonUp(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x475600
void CGameArea::OnActionButtonClickGround(const CPoint& pt)
{
    // TOOD: Incomplete.
}

// 0x4765C0
void CGameArea::OnActionButtonDblClk(const CPoint& pt)
{
    if (m_cInfinity.rViewPort.PtInRect(pt)
        && g_pBaldurChitin->GetObjectGame()->GetState() == 0) {
        CRect rView(m_cInfinity.rViewPort);
        LONG v1 = rView.Width() / -2;
        LONG v2 = rView.Height() / -2;
        CPoint ptWorld = m_cInfinity.GetWorldCoordinates(pt);
        m_cInfinity.SetViewPosition(ptWorld.x + v1, ptWorld.y + v2, TRUE);
    }
}

// 0x476680
void CGameArea::OnFormationButtonDown(const CPoint& pt)
{
    SHORT gameState = g_pBaldurChitin->GetObjectGame()->GetState();
    CPoint worldMousePoint = m_cInfinity.GetWorldCoordinates(pt);
    if (pt.x >= m_cInfinity.rViewPort.left
        && pt.x < m_cInfinity.rViewPort.right
        && pt.y >= m_cInfinity.rViewPort.top
        && pt.y < m_cInfinity.rViewPort.bottom
        && gameState == 0) {
        if (m_selectSquare.left == -1
            && m_visibility.IsTileExplored(m_visibility.PointToTile(worldMousePoint))) {
            // FIXME: Why not `worldMousePoint`?
            m_moveDest = m_cInfinity.GetWorldCoordinates(pt);
            if (g_pBaldurChitin->GetObjectGame()->GetGroup()->GetCount() != 0) {
                if (g_pBaldurChitin->GetObjectCursor()->m_nCurrentCursor == 4) {
                    m_pGame->GetGroup()->GroupDrawMove(m_moveDest,
                        m_pGame->m_curFormation,
                        CPoint(-1, -1));
                    m_groupMove = TRUE;
                }
            }
        } else {
            m_moveDest.x = -9;
            m_moveDest.y = -9;
        }
    }
}

// 0x4767E0
void CGameArea::OnFormationButtonUp(const CPoint& pt)
{
    SHORT gameState = g_pBaldurChitin->GetObjectGame()->GetState();
    CPoint worldMousePoint = m_cInfinity.GetWorldCoordinates(pt);
    if (gameState == 0) {
        if (abs(m_moveDest.x - worldMousePoint.x) <= 8
            && abs(m_moveDest.y - worldMousePoint.y) <= 8
            && m_iPicked != CGameObjectArray::INVALID_INDEX) {
            CGameObject* pObject;

            BYTE rc = m_pGame->GetObjectArray()->GetShare(m_iPicked,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
            if (rc == CGameObjectArray::SUCCESS) {
                pObject->OnFormationButton(worldMousePoint);
                m_pGame->GetObjectArray()->ReleaseShare(m_iPicked,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            }
        } else {
            if (m_groupMove) {
                OnActionButtonClickGround(worldMousePoint);
            }
        }

        if (m_groupMove) {
            m_groupMove = FALSE;
            m_pGame->GetGroup()->GroupCancelMove();
            m_pGame->SetTempCursor(4);
        }
    } else if (gameState != 3 || m_selectSquare.left == -1) {
        m_pGame->SetState(0);
        m_pGame->m_cButtonArray.m_nSelectedButton = 100;
        m_pGame->m_cButtonArray.UpdateState();
        m_pGame->SetTempCursor(4);
    }
}

// 0x476970
void CGameArea::OnMouseMove(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x477550
void CGameArea::RemoveObject(POSITION posVertList, BYTE listType, LONG id)
{
    POSITION pos;

    EnterCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));

    if (g_pBaldurChitin->cNetwork.GetSessionOpen()) {
        switch (listType) {
        case CGAMEOBJECT_LIST_FRONT:
            pos = m_lVertSortAdd.GetHeadPosition();
            while (pos != NULL) {
                if (reinterpret_cast<LONG>(m_lVertSortAdd.GetAt(pos)) == id) {
                    m_lVertSortAdd.RemoveAt(pos);
                    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
                    return;
                }

                m_lVertSortAdd.GetNext(pos);
            }
            break;
        case CGAMEOBJECT_LIST_BACK:
            pos = m_lVertSortBackAdd.GetHeadPosition();
            while (pos != NULL) {
                if (reinterpret_cast<LONG>(m_lVertSortBackAdd.GetAt(pos)) == id) {
                    m_lVertSortBackAdd.RemoveAt(pos);
                    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
                    return;
                }

                m_lVertSortBackAdd.GetNext(pos);
            }
            break;
        case CGAMEOBJECT_LIST_FLIGHT:
            pos = m_lVertSortFlightAdd.GetHeadPosition();
            while (pos != NULL) {
                if (reinterpret_cast<LONG>(m_lVertSortFlightAdd.GetAt(pos)) == id) {
                    m_lVertSortFlightAdd.RemoveAt(pos);
                    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
                    return;
                }

                m_lVertSortFlightAdd.GetNext(pos);
            }
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 7070
            UTIL_ASSERT(FALSE);
        }
    }

    // TODO: `Find` calls look redunant.
    switch (listType) {
    case CGAMEOBJECT_LIST_FRONT:
        if (m_lVertSortRemove.Find(posVertList) == NULL) {
            m_lVertSortRemove.AddTail(posVertList);
        }
        break;
    case CGAMEOBJECT_LIST_BACK:
        if (m_lVertSortBackRemove.Find(posVertList) == NULL) {
            m_lVertSortBackRemove.AddTail(posVertList);
        }
        break;
    case CGAMEOBJECT_LIST_FLIGHT:
        if (m_lVertSortFlightRemove.Find(posVertList) == NULL) {
            m_lVertSortFlightRemove.AddTail(posVertList);
        }
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 7095
        UTIL_ASSERT(FALSE);
    }

    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
}

// 0x4774B0
void CGameArea::OnLightningStrike()
{
    if (!m_lVertSort.IsEmpty()) {
        POSITION pos = m_lVertSort.FindIndex(rand() % m_lVertSort.GetCount());
        LONG nId = reinterpret_cast<LONG>(m_lVertSort.GetAt(pos));

        CGameObject* pObject;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nId,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
                static_cast<CGameSprite*>(pObject)->OnLightningStrike();
            }

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x477740
void CGameArea::Render(CVidMode* pVidMode, INT nSurface)
{
    POSITION pos;
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;

    if (!m_bAreaLoaded) {
        return;
    }

    g_pBaldurChitin->GetObjectGame()->BeginListManipulation(this);
    EnterCriticalSection(&field_1FC);

    if (CCacheStatus::dword_8D0BA8) {
        CCacheStatus::dword_8D0BA8 = FALSE;

        CVidMode* pCurrentVidMode = g_pChitin->GetCurrentVideoMode();
        pCurrentVidMode->m_bFadeTo = FALSE;
        pCurrentVidMode->m_nFade = 0;

        CScreenWorld::dword_8F85BC = 3;
    }

    if (m_firstRender > 0) {
        if (m_cInfinity.pVRPool != NULL) {
            m_cInfinity.pVRPool->ClearAll();
        }
    }

    pos = m_lTiledObjects.GetHeadPosition();
    while (pos != NULL) {
        CTiledObject* pTiledObject = m_lTiledObjects.GetNext(pos);
        pTiledObject->CheckTileState(m_cInfinity);
    }

    if (m_nKeyScrollState != 0) {
        m_cInfinity.Render(pVidMode, nSurface, m_nKeyScrollState, &m_visibility);
        m_nKeyScrollState = 0;
    } else {
        m_cInfinity.Render(pVidMode, nSurface, m_nScrollState, &m_visibility);
    }

    CInfTileSet::dword_8F2700 = 0;

    if (m_cInfinity.Render(pVidMode, nSurface, m_nScrollState, &m_visibility) != CInfinity::RENDER_MESSAGESCREEN) {
        pos = m_lVertSort.GetHeadPosition();
        while (pos != NULL) {
            iObject = reinterpret_cast<LONG>(m_lVertSort.GetNext(pos));

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_1,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                BYTE nObjectType = pObject->GetObjectType();
                if (pObject->m_posZ <= 0) {
                    switch (nObjectType) {
                    case 17:
                    case 33:
                    case 65:
                        pObject->Render(this, pVidMode, nSurface);
                        break;
                    case 48:
                        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bStaticAnimations
                            || (static_cast<CGameStatic*>(pObject)->m_header.m_dwFlags & 0x10) == 16) {
                            pObject->Render(this, pVidMode, nSurface);
                        }
                        break;
                    }
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }

        pos = m_lVertSortBack.GetHeadPosition();
        while (pos != NULL) {
            iObject = reinterpret_cast<LONG>(m_lVertSortBack.GetNext(pos));

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_1,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pObject->Render(this, pVidMode, nSurface);

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }

        pos = m_lVertSort.GetHeadPosition();
        while (pos != NULL) {
            iObject = reinterpret_cast<LONG>(m_lVertSort.GetNext(pos));

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_1,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                BYTE nObjectType = pObject->GetObjectType();
                switch (nObjectType) {
                case 17:
                case 33:
                case 65:
                    if (pObject->m_posZ > 0) {
                        pObject->Render(this, pVidMode, nSurface);
                    }
                    break;
                case 48:
                    if (pObject->m_posZ > 0) {
                        if (g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bStaticAnimations
                            || (static_cast<CGameStatic*>(pObject)->m_header.m_dwFlags & 0x10) == 16) {
                            pObject->Render(this, pVidMode, nSurface);
                        }
                    }
                    break;
                default:
                    pObject->Render(this, pVidMode, nSurface);
                    break;
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }

        pos = m_lVertSortFlight.GetHeadPosition();
        while (pos != NULL) {
            iObject = reinterpret_cast<LONG>(m_lVertSortFlight.GetNext(pos));

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_1,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pObject->Render(this, pVidMode, nSurface);

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }

        m_cInfinity.PostRender(pVidMode, nSurface, &m_search);

        if (g_pChitin->cVideo.Is3dAccelerated()) {
            CInfTileSet::sub_5D2DE0();
        }

        switch (m_pGame->GetState()) {
        case 0:
            if (abs(m_selectSquare.Width()) > 8 || abs(m_selectSquare.Height()) > 8) {
                CRect highlightRect;
                highlightRect.left = m_selectSquare.left;
                highlightRect.top = m_selectSquare.top;
                highlightRect.right = m_cInfinity.nCurrentX + min(max(m_selectSquare.right - m_cInfinity.nCurrentX, 0), m_cInfinity.rViewPort.Width() - 1);
                highlightRect.bottom = m_cInfinity.nCurrentY + min(max(m_selectSquare.bottom - m_cInfinity.nCurrentY, 0), m_cInfinity.rViewPort.Height() - 1);
                m_cInfinity.DrawHighlightRect(highlightRect, RGB(0, 255, 0), 1);
            }
            break;
        case 3:
            if (abs(m_selectSquare.Width()) > 8 || abs(m_selectSquare.Height()) > 8) {
                int width = abs(m_selectSquare.Width());
                int height = abs(m_selectSquare.Height());

                CSize axes;
                axes.cx = static_cast<LONG>(sqrt(width * width + (4 * height / 3) * (4 * height / 3)));
                axes.cy = 3 * axes.cx / 4;
                m_cInfinity.DrawEllipse(m_moveDest, axes, RGB(0, 255, 0));
            }
            break;
        }

        for (SHORT nPortrait = 0; nPortrait < m_nCharacters; nPortrait++) {
            iObject = g_pBaldurChitin->GetObjectGame()->GetCharacterId(nPortrait);

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_1,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                static_cast<CGameSprite*>(pObject)->RenderDamageArrow(this, pVidMode, nSurface);

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_1,
                    INFINITE);
            }
        }
    }

    if (m_firstRender > 0) {
        if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->StartTime();
        }
        m_firstRender = 0;
    }

    LeaveCriticalSection(&field_1FC);
    g_pBaldurChitin->GetObjectGame()->EndListManipulation(this);
}

// 0x477EE0
void CGameArea::SetDay()
{
    m_sndAmbientNight.Stop();
    // TODO: Check cast.
    m_sndAmbientDayVolume = static_cast<WORD>(m_headerSound.m_dayAmbientVolume);

    if (m_sndAmbientDay.IsSoundPlaying()) {
        m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
    } else {
        if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
            m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbient), TRUE, TRUE);
            if (m_sndAmbientDay.GetResRef() != "") {
                m_sndAmbientDay.SetLoopingFlag(TRUE);
                m_sndAmbientDay.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
                m_sndAmbientDay.Play(FALSE);
            }
        }
    }

    if ((m_cInfinity.m_areaType & 2) != 0) {
        m_cInfinity.SetDay();
    }
}

// 0x4781B0
void CGameArea::SetNight()
{
    m_sndAmbientDay.Stop();
    // TODO: Check cast.
    m_sndAmbientNightVolume = static_cast<WORD>(m_headerSound.m_nightAmbientVolume);

    if (m_sndAmbientNight.IsSoundPlaying()) {
        m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
    } else {
        if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
            m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbient), TRUE, TRUE);
            if (m_sndAmbientNight.GetResRef() != "") {
                m_sndAmbientNight.SetLoopingFlag(TRUE);
                m_sndAmbientNight.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
                m_sndAmbientNight.Play(FALSE);
            }
        }
    }

    if ((m_cInfinity.m_areaType & 2) != 0) {
        m_cInfinity.SetNight();
    }
}

// 0x478480
void CGameArea::SetApproachingDawn()
{
    m_cInfinity.SetApproachingDawn();
}

// 0x478480
void CGameArea::SetApproachingDusk()
{
    m_cInfinity.SetApproachingDusk();
}

// 0x478490
void CGameArea::SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    m_sndAmbientDayVolume = static_cast<WORD>(nIntensity * m_headerSound.m_dayAmbientVolume / 256);
    if (m_sndAmbientDay.IsSoundPlaying()) {
        m_sndAmbientDay.SetVolume(m_sndAmbientVolume * m_sndAmbientDayVolume / 100);
    } else {
        if (m_sndAmbientVolume * m_sndAmbientDayVolume / 100 > 0) {
            if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
                // NOTE: Uninline.
                m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbient), TRUE, TRUE);
            } else {
                // NOTE: Uninline.
                m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbientExtended), TRUE, TRUE);
            }

            if (m_sndAmbientDay.cResRef != "") {
                m_sndAmbientDay.SetLoopingFlag(1);
                m_sndAmbientDay.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientDay.SetVolume(m_sndAmbientVolume * m_sndAmbientDayVolume / 100);
                m_sndAmbientDay.Play(FALSE);
            }
        }
    }

    m_sndAmbientNightVolume = static_cast<WORD>(nIntensity * m_headerSound.m_nightAmbientVolume / 256);
    if (m_sndAmbientNight.IsSoundPlaying()) {
        m_sndAmbientNight.SetVolume(m_sndAmbientVolume * m_sndAmbientNightVolume / 100);
    } else {
        if (m_sndAmbientVolume * m_sndAmbientNightVolume / 100 > 0) {
            if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
                // NOTE: Uninline.
                m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbient), TRUE, TRUE);
            } else {
                // NOTE: Uninline.
                m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbientExtended), TRUE, TRUE);
            }

            if (m_sndAmbientNight.cResRef != "") {
                m_sndAmbientNight.SetLoopingFlag(1);
                m_sndAmbientNight.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientNight.SetVolume(m_sndAmbientVolume * m_sndAmbientNightVolume / 100);
                m_sndAmbientNight.Play(FALSE);
            }
        }
    }

    if (nIntensity == CInfinity::TRUE_DAWNDUSK_INTENSITY) {
        BYTE nSong = GetSong(0);
        g_pBaldurChitin->sub_4288E0(m_resRef, nSong);
        PlaySong(0, 0x4 | 0x2);
    }

    if ((m_cInfinity.m_areaType & 0x2) != 0) {
        m_cInfinity.SetDusk(nIntensity, bPlayDayNightMovie);
    }
}

// 0x478AC0
void CGameArea::SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    m_sndAmbientDayVolume = static_cast<WORD>(nIntensity * m_headerSound.m_dayAmbientVolume / 256);
    if (m_sndAmbientDay.IsSoundPlaying()) {
        m_sndAmbientDay.SetVolume(m_sndAmbientVolume * m_sndAmbientDayVolume / 100);
    } else {
        if (m_sndAmbientVolume * m_sndAmbientDayVolume / 100 > 0) {
            if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
                // NOTE: Uninline.
                m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbient), TRUE, TRUE);
            } else {
                // NOTE: Uninline.
                m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbientExtended), TRUE, TRUE);
            }

            if (m_sndAmbientDay.cResRef != "") {
                m_sndAmbientDay.SetLoopingFlag(1);
                m_sndAmbientDay.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientDay.SetVolume(m_sndAmbientVolume * m_sndAmbientDayVolume / 100);
                m_sndAmbientDay.Play(FALSE);
            }
        }
    }

    m_sndAmbientNightVolume = static_cast<WORD>(nIntensity * m_headerSound.m_nightAmbientVolume / 256);
    if (m_sndAmbientNight.IsSoundPlaying()) {
        m_sndAmbientNight.SetVolume(m_sndAmbientVolume * m_sndAmbientNightVolume / 100);
    } else {
        if (m_sndAmbientVolume * m_sndAmbientNightVolume / 100 > 0) {
            if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
                // NOTE: Uninline.
                m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbient), TRUE, TRUE);
            } else {
                // NOTE: Uninline.
                m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbientExtended), TRUE, TRUE);
            }

            if (m_sndAmbientNight.cResRef != "") {
                m_sndAmbientNight.SetLoopingFlag(1);
                m_sndAmbientNight.SetChannel(1, reinterpret_cast<DWORD>(this));
                m_sndAmbientNight.SetVolume(m_sndAmbientVolume * m_sndAmbientNightVolume / 100);
                m_sndAmbientNight.Play(FALSE);
            }
        }
    }

    if (nIntensity == CInfinity::TRUE_DAWNDUSK_INTENSITY) {
        PlaySong(1, 0x4 | 0x2);
    }

    if ((m_cInfinity.m_areaType & 0x2) != 0) {
        m_cInfinity.SetDusk(nIntensity, bPlayDayNightMovie);
    }
}

// 0x4790D0
void CGameArea::SetNewResWED(CResWED* pNewResWED)
{
    POSITION pos;
    CTiledObject* pTiledObject;

    m_pResWED = pNewResWED;

    pos = m_lTiledObjects.GetHeadPosition();
    while (pos != NULL) {
        pTiledObject = m_lTiledObjects.GetNext(pos);
        pTiledObject->SetNewResWED(pNewResWED);
    }
}

// 0x479110
void CGameArea::SetTimeOfDay(ULONG nTimeOfDay, BOOLEAN bPlayDayNightMovie)
{
    m_sndAmbientVolume = g_pBaldurChitin->m_pEngineWorld->m_weather.GetWind();
    m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
    m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);

    if (CTimerWorld::IsDay(nTimeOfDay)) {
        SetDay();
    } else if (CTimerWorld::IsDusk(nTimeOfDay)) {
        SetDusk(255 - static_cast<BYTE>(((nTimeOfDay - CTimerWorld::TIME_DUSK) * 256) / (CTimerWorld::TIME_NIGHT - CTimerWorld::TIME_DUSK)), bPlayDayNightMovie);
    } else if (CTimerWorld::IsNight(nTimeOfDay)) {
        SetNight();
    } else if (CTimerWorld::IsDawn(nTimeOfDay)) {
        SetDawn(static_cast<BYTE>(((nTimeOfDay - CTimerWorld::TIME_DAWN) * 256) / (CTimerWorld::TIME_DAY - CTimerWorld::TIME_DAWN)), bPlayDayNightMovie);
    }
}

// 0x479260
void CGameArea::SetSoundEnvironment()
{
    // NOTE: Not sure why they are explicit. Probably remapping from one enum
    // to other.
    switch (m_headerSound.m_reverb) {
    case 0:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_GENERIC);
        break;
    case 1:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PADDEDCELL);
        break;
    case 2:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ROOM);
        break;
    case 3:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_BATHROOM);
        break;
    case 4:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_LIVINGROOM);
        break;
    case 5:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_STONEROOM);
        break;
    case 6:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_AUDITORIUM);
        break;
    case 7:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CONCERTHALL);
        break;
    case 8:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CAVE);
        break;
    case 9:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ARENA);
        break;
    case 10:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_HANGAR);
        break;
    case 11:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CARPETEDHALLWAY);
        break;
    case 12:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_HALLWAY);
        break;
    case 13:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_STONECORRIDOR);
        break;
    case 14:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ALLEY);
        break;
    case 15:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_FOREST);
        break;
    case 16:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CITY);
        break;
    case 17:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_MOUNTAINS);
        break;
    case 18:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_QUARRY);
        break;
    case 19:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PLAIN);
        break;
    case 20:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PARKINGLOT);
        break;
    case 21:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_SEWERPIPE);
        break;
    case 22:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_UNDERWATER);
        break;
    case 23:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_DRUGGED);
        break;
    case 24:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_DIZZY);
        break;
    case 25:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PSYCHOTIC);
        break;
    }
}

// 0x4794E0
void CGameArea::SortLists()
{
    CTypedPtrList<CPtrList, CGameObject*> sortObjectsAdd;
    CGameObject** pObjects = NULL;
    LONG iObject;
    CGameObject* pObject;
    BYTE rc;
    POSITION pos;
    INT cnt;
    INT cnt2;

    EnterCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));

    if (AfxIsValidAddress(&m_header, sizeof(m_header), 1)) {
        g_pBaldurChitin->GetObjectGame()->BeginListManipulation(this);

        INT nFrontAdd = m_lVertSortAdd.GetCount();
        INT nFront = m_lVertSort.GetCount() - m_lVertSortRemove.GetCount();

        BOOLEAN bSort;
        if (nFrontAdd != 0
            || (m_firstRender != 0
                && m_pGame->GetWorldTimer()->m_gameTime % 5 == 0
                && g_pBaldurChitin->GetObjectGame()->GetVisibleArea() == this)) {
            bSort = TRUE;

            if (nFront + nFrontAdd == 0) {
                LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
                return;
            }

            pObjects = new CGameObject*[nFront + nFrontAdd];
            if (pObjects == NULL) {
                LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));
                return;
            }
        } else {
            bSort = FALSE;
        }

        while (!m_lVertSortAdd.IsEmpty()) {
            iObject = reinterpret_cast<LONG>(m_lVertSortAdd.RemoveHead());

            do {
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                pos = sortObjectsAdd.GetHeadPosition();
                while (pos != NULL) {
                    if (sortObjectsAdd.GetAt(pos)->GetPos().y >= pObject->GetPos().y) {
                        break;
                    }
                    sortObjectsAdd.GetNext(pos);
                }

                if (pos != NULL) {
                    sortObjectsAdd.InsertBefore(pos, pObject);
                } else {
                    sortObjectsAdd.AddTail(pObject);
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            } else if (rc != CGameObjectArray::DELETED) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 8076
                UTIL_ASSERT(FALSE);
            }
        }

        cnt = 0;
        while (!sortObjectsAdd.IsEmpty()) {
            pObjects[cnt++] = sortObjectsAdd.RemoveHead();
        }

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
        // __LINE__: 8099
        UTIL_ASSERT(cnt == nFrontAdd);

        while (!m_lVertSortBackRemove.IsEmpty()) {
            m_lVertSortBack.RemoveAt(m_lVertSortBackRemove.RemoveHead());
        }

        while (!m_lVertSortBackAdd.IsEmpty()) {
            do {
                // FIXME: Should be outside of the loop.
                iObject = reinterpret_cast<LONG>(m_lVertSortBackAdd.RemoveHead());
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (m_lVertSortBack.IsEmpty()) {
                    m_lVertSortBack.AddTail(reinterpret_cast<int*>(pObject->GetId()));
                } else {
                    m_lVertSortBack.InsertBefore(m_lVertSortBack.GetTailPosition(),
                        reinterpret_cast<int*>(pObject->GetId()));
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            } else if (rc == CGameObjectArray::DELETED) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 8148
                UTIL_ASSERT(FALSE);
            }
        }

        while (!m_lVertSortFlightRemove.IsEmpty()) {
            m_lVertSortFlight.RemoveAt(m_lVertSortFlightRemove.RemoveHead());
        }

        while (!m_lVertSortFlightAdd.IsEmpty()) {
            do {
                // FIXME: Should be outside of the loop.
                iObject = reinterpret_cast<LONG>(m_lVertSortFlightAdd.RemoveHead());
                rc = m_pGame->GetObjectArray()->GetShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::DENIED);

            if (rc == CGameObjectArray::SUCCESS) {
                if (m_lVertSortFlight.IsEmpty()) {
                    m_lVertSortFlight.AddTail(reinterpret_cast<int*>(pObject->GetId()));
                } else {
                    m_lVertSortFlight.InsertBefore(m_lVertSortFlight.GetTailPosition(),
                        reinterpret_cast<int*>(pObject->GetId()));
                }

                m_pGame->GetObjectArray()->ReleaseShare(iObject,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);
            } else if (rc == CGameObjectArray::DELETED) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                // __LINE__: 8195
                UTIL_ASSERT(FALSE);
            }
        }

        while (!m_lVertSortRemove.IsEmpty()) {
            m_lVertSort.RemoveAt(m_lVertSortRemove.RemoveHead());
        }

        if (bSort) {
            while (!m_lVertSort.IsEmpty()) {
                iObject = reinterpret_cast<LONG>(m_lVertSort.RemoveHead());

                do {
                    rc = m_pGame->GetObjectArray()->GetShare(iObject,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::DENIED);

                if (rc == CGameObjectArray::SUCCESS) {
                    pObjects[cnt++] = pObject;
                } else {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
                    // __LINE__: 8263
                    UTIL_ASSERT(FALSE);
                }
            }

            m_lVertSort.RemoveAll();

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameArea.cpp
            // __LINE__: 8268
            UTIL_ASSERT(cnt == nFront + nFrontAdd);

            if (nFront > 1) {
                for (cnt = 0; cnt < nFront - 1; cnt++) {
                    BOOL bDone = TRUE;

                    for (cnt2 = 1; cnt < nFront - cnt; cnt++) {
                        if (pObjects[nFrontAdd + cnt2 - 1]->GetPos().y > pObjects[nFrontAdd + cnt2]->GetPos().y) {
                            pObject = pObjects[nFrontAdd + cnt2 - 1];
                            pObjects[nFrontAdd + cnt2 - 1] = pObjects[nFrontAdd + cnt2];
                            pObjects[nFrontAdd + cnt2] = pObject;
                            bDone = FALSE;
                        }
                    }

                    if (bDone) {
                        break;
                    }
                }
            }

            cnt = 0;
            cnt2 = 0;
            while (cnt < nFrontAdd || cnt2 < nFront) {
                if (cnt2 != nFront
                    && (cnt == nFrontAdd || pObjects[cnt]->GetPos().y > pObjects[cnt2]->GetPos().y)) {
                    pos = m_lVertSort.AddTail(reinterpret_cast<int*>(pObjects[cnt2]->GetId()));
                    pObjects[cnt2]->SetVertListPos(pos);
                    m_pGame->GetObjectArray()->ReleaseShare(pObjects[cnt2]->GetId(),
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                    cnt2++;
                } else {
                    pos = m_lVertSort.AddTail(reinterpret_cast<int*>(pObjects[cnt]->GetId()));
                    pObjects[cnt]->SetVertListPos(pos);
                    m_pGame->GetObjectArray()->ReleaseShare(pObjects[cnt]->GetId(),
                        CGameObjectArray::THREAD_ASYNCH,
                        INFINITE);
                    cnt++;
                }
            }
        }

        g_pBaldurChitin->GetObjectGame()->EndListManipulation(this);
    }

    LeaveCriticalSection(&(g_pBaldurChitin->m_pEngineWorld->field_106));

    if (pObjects != NULL) {
        delete pObjects;
    }
}

// 0x479CC0
BOOL CGameArea::SetSong(SHORT slot, BYTE song)
{
    switch (slot) {
    case 0:
        m_headerSound.m_dayMusic = song;
        return TRUE;
    case 1:
        m_headerSound.m_nightMusic = song;
        return TRUE;
    case 2:
        m_headerSound.m_battleWinningMusic = song;
        return TRUE;
    case 3:
        m_headerSound.m_battleStandOffMusic = song;
        return TRUE;
    case 4:
        m_headerSound.m_battleLosingMusic = song;
        return TRUE;
    case 5:
        m_headerSound.m_alt1Music0 = song;
        return TRUE;
    case 6:
        m_headerSound.m_alt1Music1 = song;
        return TRUE;
    case 7:
        m_headerSound.m_alt1Music2 = song;
        return TRUE;
    case 8:
        m_headerSound.m_alt1Music3 = song;
        return TRUE;
    case 9:
        m_headerSound.m_alt1Music4 = song;
        return TRUE;
    default:
        return FALSE;
    }
}

// 0x479DB0
BYTE CGameArea::GetSong(SHORT slot)
{
    if (slot > 256) {
        return -1;
    }

    // TODO: Check casts.

    BYTE song;
    if (slot != 256) {
        switch (slot) {
        case 0:
            song = static_cast<BYTE>(m_headerSound.m_dayMusic);
            break;
        case 1:
            song = static_cast<BYTE>(m_headerSound.m_nightMusic);
            break;
        case 2:
            song = static_cast<BYTE>(m_headerSound.m_battleWinningMusic);
            break;
        case 3:
            song = static_cast<BYTE>(m_headerSound.m_battleStandOffMusic);
            break;
        case 4:
            song = static_cast<BYTE>(m_headerSound.m_battleLosingMusic);
            break;
        case 5:
            song = static_cast<BYTE>(m_headerSound.m_alt1Music0);
            break;
        case 6:
            song = static_cast<BYTE>(m_headerSound.m_alt1Music1);
            break;
        case 7:
            song = static_cast<BYTE>(m_headerSound.m_alt1Music2);
            break;
        case 8:
            song = static_cast<BYTE>(m_headerSound.m_alt1Music3);
            break;
        case 9:
            song = static_cast<BYTE>(m_headerSound.m_alt1Music4);
            break;
        default:
            return -1;
        }
    } else {
        if (g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDay() || g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->IsDusk()) {
            song = static_cast<BYTE>(m_headerSound.m_dayMusic);
        } else {
            song = static_cast<BYTE>(m_headerSound.m_nightMusic);
        }
    }

    if (song == 0) {
        song = -1;
    }

    return song;
}

// 0x479E80
void CGameArea::PlaySong(SHORT slot, DWORD flags)
{
    if (slot == 2 || slot == 3 || slot == 4) {
        if (m_headerSound.m_battleStandOffMusic == 0
            || m_headerSound.m_battleStandOffMusic == -1) {
            return;
        }
    }

    m_nCurrentSong = slot;

    if (slot == 3) {
        m_nBattleSongCounter = 150;
    }

    if (g_pBaldurChitin->GetObjectGame()->GetVisibleArea() == this) {
        INT nSong = GetSong(slot);
        if (nSong != g_pChitin->cSoundMixer.m_nCurrentSong) {
            INT nSection;
            INT nPosition;
            g_pBaldurChitin->sub_428820(m_resRef, nSong, nSection, nPosition);

            if (slot == 2 || slot == 3 || slot == 4) {
                g_pBaldurChitin->cSoundMixer.StartSong(nSong, 0x1);
            } else if (nSong == -1 && flags == 0x1) {
                g_pBaldurChitin->cSoundMixer.StartSong(-1, nSection, nPosition, 0x2 | 0x1);
            } else {
                g_pBaldurChitin->cSoundMixer.StartSong(nSong, nSection, nPosition, flags);
            }

            if (g_pBaldurChitin->cNetwork.GetSessionHosting() == TRUE) {
                CMessageStartCombatMusic* pStartCombatMusic = new CMessageStartCombatMusic(slot,
                    m_nAIIndex,
                    m_nAIIndex);

                g_pBaldurChitin->GetMessageHandler()->AddMessage(pStartCombatMusic, FALSE);
            }
        }
    }
}

// 0x453080
CInfinity* CGameArea::GetInfinity()
{
    return &m_cInfinity;
}

// 0x453090
CVariableHash* CGameArea::GetVariables()
{
    return &m_variables;
}

// 0x4530A0
CAreaFileRestEncounter* CGameArea::GetHeaderRestEncounter()
{
    return &m_headerRestEncounter;
}

// 0x40CAF0
CNamedCreatureVariableHash* CGameArea::GetNamedCreatures()
{
    return &m_namedCreatures;
}

// 0x43A5B0
CGameAreaNotes* CGameArea::GetAreaNotes()
{
    return &m_cGameAreaNotes;
}

// 0x47A060
void CGameArea::sub_47A060()
{
    CMemINISection* pSection = INIFile.GetSection(CString("locals"));
    if (pSection != NULL && pSection->GetCount() > 0) {
        POSITION pos = pSection->GetHeadPosition();
        while (pos != NULL) {
            CMemINIValue* pValue = pSection->GetNext(pos);
            if (pValue != NULL) {
                CVariable* pVariable = CGameAIBase::GetGlobalVariable(CString("GLOBAL"),
                    pValue->GetName(),
                    0);
                if (pVariable != NULL) {
                    pVariable->m_intValue = atoi(pValue->GetValue());
                }
            }
        }
    }
}

// 0x47A140
int CGameArea::ExitSpawn()
{
    if (mpSpawner != NULL) {
        return mpSpawner->ExitSpawn(this);
    } else {
        return 0;
    }
}

// 0x47A160
int CGameArea::EnterSpawn()
{
    if (mpSpawner != NULL && !g_pBaldurChitin->m_pEngineLoad->m_bInLoadGame) {
        return mpSpawner->EnterSpawn(this);
    } else {
        return 0;
    }
}

// 0x47A190
void CGameArea::sub_47A190()
{
    g_pBaldurChitin->sub_4286B0(m_resRef, g_pBaldurChitin->cSoundMixer.m_nCurrentSong);
}

// -----------------------------------------------------------------------------

// 0x47A020
BYTE* CAreaFile::GetData()
{
    if (pRes != NULL) {
        return static_cast<BYTE*>(pRes->Demand());
    } else {
        return NULL;
    }
}

// 0x47A030
DWORD CAreaFile::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

// 0x5C7B00
void CAreaFile::ReleaseData()
{
    if (pRes != NULL) {
        pRes->Release();
    }
}

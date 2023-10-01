#include "CGameArea.h"

#include "CBaldurChitin.h"
#include "CChitin.h"
#include "CGameContainer.h"
#include "CGameObject.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CPathSearch.h"
#include "CScreenWorld.h"
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
    field_24E = 0;
    field_3D6 = 0;
    m_firstRender = 0;
    m_dwLastProgressRenderTickCount = 0;
    m_dwLastProgressMsgTickCount = 0;
    m_sndAmbientDayVolume = 0;
    m_sndAmbientNightVolume = 0;
    field_3EC = 0;
    field_41A = 0;
    m_nCurrentSong = 0;
    m_id = id;
    field_1ED = 0;
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
    field_240 = 0;
    m_iPicked = CGameObjectArray::INVALID_INDEX;
    m_iPickedTarget = CGameObjectArray::INVALID_INDEX;
    m_nToolTip = 0;
    m_visibility.field_58 = 0;
    memset(&m_header, 0, sizeof(m_header));
    m_groupMove = FALSE;
    field_432 = 0;
    field_434 = 0;
    field_318 = 0;
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
    field_98A = 0;
    field_AE6 = 1;
    field_98E = 10;

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

    dword_8D212C = 0;
    byte_8D2138 = 0;

    field_B16 = 0;
}

// 0x46A070
CGameArea::~CGameArea()
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.

    return FALSE;
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
}

// 0x476680
void CGameArea::OnFormationButtonDown(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x4767E0
void CGameArea::OnFormationButtonUp(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x476970
void CGameArea::OnMouseMove(const CPoint& pt)
{
    // TODO: Incomplete.
}

// 0x477550
void CGameArea::RemoveObject(POSITION posVertList, BYTE listType, LONG id)
{
    // TODO: Incomplete.
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
void CGameArea::Render(CVidMode* pVidMode, int a2)
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.
}

// 0x478AC0
void CGameArea::SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    // TODO: Incomplete.
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
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
    // TODO: Incomplete.
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

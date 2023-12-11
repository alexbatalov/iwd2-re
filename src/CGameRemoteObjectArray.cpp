#include "CGameRemoteObjectArray.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CUtil.h"

// NOTE: Inlined.
CGameRemoteObjectControlChange::CGameRemoteObjectControlChange()
{
    oldPlayerID = 0;
    oldObjectID = CGameObjectArray::INVALID_INDEX;
    newPlayerID = 0;
    newObjectID = CGameObjectArray::INVALID_INDEX;
    localControl = FALSE;
    pNext = NULL;
}

// NOTE: Inlined.
CGameRemoteObjectListEntry::CGameRemoteObjectListEntry()
{
    remotePlayerID = 0;
    remoteObjectID = CGameObjectArray::INVALID_INDEX;
    localObjectID = CGameObjectArray::INVALID_INDEX;
    pNext = NULL;
}

// 0x59ACC0
CGameRemoteObjectArray::CGameRemoteObjectArray(SHORT nArraySize)
{
    SHORT nIndex;

    m_pArray = new CGameRemoteObjectListEntry*[nArraySize];

    if (m_pArray == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 1187
        UTIL_ASSERT(FALSE);
    }

    m_nArraySize = nArraySize;

    for (nIndex = 0; nIndex < nArraySize; nIndex++) {
        m_pArray[nIndex] = NULL;
    }

    m_nControlsChanged = 0;
    m_pControlsChanged = NULL;
    m_pControlsChangedTail = NULL;
    m_nControlsAreaChanged = 0;

    for (nIndex = 0; nIndex < 6; nIndex++) {
        m_psControlsAreaChangedName[nIndex] = "";
        m_pnControlsAreaChangedPlayerNum[nIndex] = 0;
        m_pnControlsAreaChangedFirstObject[nIndex] = -1;
    }
}

// 0x59ADD0
CGameRemoteObjectArray::~CGameRemoteObjectArray()
{
    // NOTE: Uninline.
    Clean();

    if (m_pArray != NULL) {
        delete m_pArray;
        m_pArray = NULL;
    }
}

// 0x59AEF0
BOOL CGameRemoteObjectArray::Add(PLAYER_ID remotePlayerID, LONG remoteObjectID, LONG localObjectID, BOOLEAN bSetInGame)
{
    SHORT arrayIndex = (remoteObjectID >> 16) & SHORT_MAX;
    if (arrayIndex >= m_nArraySize) {
        SHORT nNewArraySize = arrayIndex + 1;
        CGameRemoteObjectListEntry** pNewArray = new CGameRemoteObjectListEntry*[nNewArraySize];

        if (pNewArray == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 1289
            UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::Add: new failed in expanding array.");
        }

        for (SHORT cnt = 0; cnt < m_nArraySize; cnt++) {
            pNewArray[cnt] = m_pArray[cnt];
        }

        if (m_nArraySize < nNewArraySize) {
            memset(&(pNewArray[m_nArraySize]), 0, sizeof(CGameRemoteObjectListEntry*) * (nNewArraySize - m_nArraySize));
        }

        delete m_pArray;
        m_pArray = pNewArray;
        m_nArraySize = nNewArraySize;
    }

    LONG tempObjectID;

    // NOTE: Uninline.
    if (Find(remotePlayerID, remoteObjectID, tempObjectID)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 1313
        UTIL_ASSERT(localObjectID == tempObjectID);

        return FALSE;
    }

    CGameRemoteObjectListEntry* node = new CGameRemoteObjectListEntry();

    if (node == NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 1320
        UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::Add: new failed.");
    }

    node->pNext = NULL;
    node->remotePlayerID = remotePlayerID;
    node->remoteObjectID = remoteObjectID;
    node->localObjectID = localObjectID;

    if (m_pArray[arrayIndex] != NULL) {
        node->pNext = m_pArray[arrayIndex];
        m_pArray[arrayIndex] = node;
    } else {
        m_pArray[arrayIndex] = NULL;
    }

    if (bSetInGame == TRUE) {
        CGameObject* pObject;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(localObjectID,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc != CGameObjectArray::SUCCESS) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 1356
            UTIL_ASSERT(FALSE);
        }

        pObject->m_remoteObjectID = remoteObjectID;
        pObject->m_remotePlayerID = remotePlayerID;

        if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE) {
            CGameSprite* pSprite = static_cast<CGameSprite*>(pObject);
            pSprite->m_cLastSpriteUpdate.Initialize(TRUE);
            if (pSprite->InControl()) {
                CMessage* message = new CMessageSpriteUpdate(pSprite,
                    localObjectID,
                    localObjectID);
                g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
            }
        }

        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(localObjectID,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }

    return TRUE;
}

// 0x59B1C0
BOOL CGameRemoteObjectArray::CleanControlChanges()
{
    CSingleLock controlsLock(&m_critSect, FALSE);
    controlsLock.Lock(INFINITE);

    CGameRemoteObjectControlChange* node = m_pControlsChanged;
    while (node != NULL) {
        CGameRemoteObjectControlChange* next = node->pNext;
        node->pNext = NULL;
        delete node;
        node = next;
    }

    m_nControlsChanged = 0;
    m_pControlsChanged = NULL;
    m_pControlsChangedTail = NULL;
    m_nControlsAreaChanged = 0;

    controlsLock.Unlock();
    return TRUE;
}

// 0x59B260
BOOL CGameRemoteObjectArray::Delete(LONG localObjectID)
{
    for (SHORT arrayIndex = 0; arrayIndex < m_nArraySize; arrayIndex++) {
        CGameRemoteObjectListEntry* entry = m_pArray[arrayIndex];
        if (entry != NULL) {
            CGameRemoteObjectListEntry* prev = NULL;
            BOOLEAN head = TRUE;

            while (entry != NULL) {
                if (entry->localObjectID == localObjectID) {
                    if (head == TRUE) {
                        m_pArray[arrayIndex] = entry->pNext;
                        delete entry;
                        entry = m_pArray[arrayIndex];
                    } else {
                        prev->pNext = entry->pNext;
                        delete entry;
                        entry = prev->pNext;
                    }
                } else {
                    prev = entry;
                    entry = entry->pNext;
                    head = FALSE;
                }
            }
        }
    }
    return TRUE;
}

// 0x59B300
BOOL CGameRemoteObjectArray::Find(DWORD remotePlayerID, LONG remoteObjectID, LONG& localObjectID)
{
    SHORT arrayIndex = (remoteObjectID >> 16) & SHORT_MAX;
    if (arrayIndex >= m_nArraySize) {
        return FALSE;
    }

    CGameRemoteObjectListEntry* entry = m_pArray[arrayIndex];
    while (entry != NULL) {
        if (entry->remotePlayerID == remotePlayerID
            && entry->remoteObjectID == remoteObjectID) {
            localObjectID = entry->localObjectID;
            return TRUE;
        }
        entry = entry->pNext;
    }

    return FALSE;
}

// 0x59B350
BOOL CGameRemoteObjectArray::ChangeControl(DWORD oldRemotePlayerID, LONG oldRemoteObjectID, DWORD newRemotePlayerID, LONG newRemoteObjectID, BOOLEAN bLocalControl)
{
    CSingleLock controlsLock(&m_critSect, FALSE);

    SHORT arrayIndex = (oldRemoteObjectID >> 16) & SHORT_MAX;
    if (arrayIndex >= m_nArraySize) {
        return FALSE;
    }

    CGameRemoteObjectListEntry* entry = m_pArray[arrayIndex];
    while (entry != NULL) {
        if (entry->remotePlayerID == oldRemotePlayerID
            && entry->remoteObjectID == oldRemoteObjectID) {
            BOOL bResult;
            if (bLocalControl == TRUE) {
                bResult = Add(g_pChitin->cNetwork.m_idLocalPlayer,
                    entry->localObjectID,
                    entry->localObjectID,
                    TRUE);
            } else {
                bResult = Add(newRemotePlayerID,
                    newRemoteObjectID,
                    entry->localObjectID,
                    TRUE);
            }
            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                controlsLock.Lock(INFINITE);
                CGameRemoteObjectControlChange* change = new CGameRemoteObjectControlChange();
                change->oldPlayerID = oldRemotePlayerID;
                change->oldObjectID = oldRemoteObjectID;
                change->newPlayerID = newRemotePlayerID;
                change->newObjectID = newRemoteObjectID;
                change->localControl = bLocalControl;
                change->pNext = NULL;
                if (m_pControlsChanged != NULL) {
                    m_nControlsChanged++;
                    m_pControlsChangedTail->pNext = change;
                    m_pControlsChangedTail = change;
                } else {
                    m_nControlsChanged = 1;
                    m_pControlsChanged = change;
                    m_pControlsChangedTail = change;
                }
                controlsLock.Unlock();
            }
            return bResult;
        }
        entry = entry->pNext;
    }

    return FALSE;
}

// 0x59B4D0
BOOL CGameRemoteObjectArray::MarshalControlChanges(BYTE** pData, DWORD* dwSize)
{
    SHORT nIndex;
    DWORD cnt;
    CString sResRef;
    BYTE nResRefLength;
    CSingleLock controlsLock(&m_critSect, FALSE);
    controlsLock.Lock(INFINITE);

    if (m_nControlsChanged == 0) {
        controlsLock.Unlock();
        return FALSE;
    }

    *dwSize = sizeof(SHORT);
    for (nIndex = 0; nIndex < m_nControlsAreaChanged; nIndex++) {
        m_psControlsAreaChangedName[nIndex].CopyToString(sResRef);
        *dwSize += sizeof(BYTE)
            + sizeof(DWORD)
            + sizeof(SHORT)
            + sResRef.GetLength();
    }

    *dwSize += sizeof(SHORT)
        + (sizeof(PLAYER_ID)
              + sizeof(LONG)
              + sizeof(PLAYER_ID)
              + sizeof(LONG)
              + sizeof(BOOLEAN))
            * m_nControlsChanged;

    *pData = new BYTE[*dwSize];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 1743
    UTIL_ASSERT(*pData != NULL);

    cnt = 0;

    *reinterpret_cast<SHORT*>(*pData + cnt) = m_nControlsAreaChanged;
    cnt += sizeof(SHORT);

    for (nIndex = 0; nIndex < m_nControlsAreaChanged; nIndex++) {
        m_psControlsAreaChangedName[nIndex].CopyToString(sResRef);
        nResRefLength = static_cast<BYTE>(sResRef.GetLength());

        *reinterpret_cast<BYTE*>(*pData + cnt) = nResRefLength;
        cnt += sizeof(BYTE);

        memcpy(*pData + cnt, sResRef.GetBuffer(nResRefLength), nResRefLength);
        cnt += nResRefLength;

        *reinterpret_cast<DWORD*>(*pData + cnt) = m_pnControlsAreaChangedPlayerNum[nIndex];
        cnt += sizeof(DWORD);

        *reinterpret_cast<SHORT*>(*pData + cnt) = m_pnControlsAreaChangedFirstObject[nIndex];
        cnt += sizeof(SHORT);
    }

    *reinterpret_cast<SHORT*>(*pData + cnt) = m_nControlsChanged;
    cnt += sizeof(SHORT);

    for (nIndex = 0; nIndex < m_nControlsChanged; nIndex++) {
        if (m_pControlsChanged == NULL) {
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
            // __LINE__: 1796
            UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::MarshalControlChanges(): Not enough control changes in list!\n");
        }

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = m_pControlsChanged->oldPlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_pControlsChanged->oldObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<PLAYER_ID*>(*pData + cnt) = m_pControlsChanged->newPlayerID;
        cnt += sizeof(PLAYER_ID);

        *reinterpret_cast<LONG*>(*pData + cnt) = m_pControlsChanged->newObjectID;
        cnt += sizeof(LONG);

        *reinterpret_cast<BOOLEAN*>(*pData + cnt) = m_pControlsChanged->localControl;
        cnt += sizeof(BOOLEAN);

        CGameRemoteObjectControlChange* entry = m_pControlsChanged;
        m_pControlsChanged = m_pControlsChanged->pNext;
        delete entry;
    }

    m_nControlsAreaChanged = 0;
    m_nControlsChanged = 0;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 1806
    UTIL_ASSERT(m_pControlsChanged == NULL);

    m_pControlsChangedTail = NULL;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 1809
    UTIL_ASSERT(cnt == *dwSize);

    controlsLock.Unlock();
    return TRUE;
}

// 0x59B7A0
BOOL CGameRemoteObjectArray::UnmarshalControlChanges(BYTE* pData, DWORD dwSize)
{
    CString areas[MAX_AREAS_CHANGED];
    DWORD areasPlayerID[MAX_AREAS_CHANGED];
    SHORT areasObjectStart[MAX_AREAS_CHANGED];
    SHORT nIndex;
    DWORD cnt;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 1859
    UTIL_ASSERT(pData != NULL && dwSize != 0);

    cnt = 0;

    SHORT nControlsAreaChanged = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    for (nIndex = 0; nIndex < nControlsAreaChanged; nIndex++) {
        CHAR szAreaString[8];
        memset(szAreaString, 0, sizeof(szAreaString));

        BYTE szAreaStringLength = *reinterpret_cast<BYTE*>(pData + cnt);
        cnt += sizeof(BYTE);

        memcpy(szAreaString, pData + cnt, szAreaStringLength);
        cnt += szAreaStringLength;

        areas[nIndex] = szAreaString;

        areasPlayerID[nIndex] = *reinterpret_cast<DWORD*>(pData + cnt);
        cnt += sizeof(DWORD);

        areasObjectStart[nIndex] = *reinterpret_cast<SHORT*>(pData + cnt);
        cnt += sizeof(SHORT);
    }

    SHORT nControlsChanged = *reinterpret_cast<SHORT*>(pData + cnt);
    cnt += sizeof(SHORT);

    for (nIndex = 0; nIndex < nControlsChanged; nIndex++) {
        PLAYER_ID oldPlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
        cnt += sizeof(PLAYER_ID);

        LONG oldObjectID = *reinterpret_cast<LONG*>(pData + cnt);
        cnt += sizeof(LONG);

        PLAYER_ID newPlayerID = *reinterpret_cast<PLAYER_ID*>(pData + cnt);
        cnt += sizeof(PLAYER_ID);

        LONG newObjectID = *reinterpret_cast<LONG*>(pData + cnt);
        cnt += sizeof(LONG);

        BOOLEAN bLocalControl = *reinterpret_cast<BOOLEAN*>(pData + cnt);
        cnt += sizeof(BOOLEAN);

        for (SHORT area = 0; area < nControlsAreaChanged; area++) {
            if (oldPlayerID == areasPlayerID[area]) {
                g_pBaldurChitin->GetObjectGame()->LoadArea(areas[area],
                    -1,
                    FALSE,
                    FALSE);

                // NOTE: Why 7?
                for (SHORT otherArea = 0; otherArea < 7; otherArea++) {
                    CGameArea* pArea = g_pBaldurChitin->GetObjectGame()->GetArea(otherArea);
                    if (pArea != NULL && pArea->m_resRef == areas[area]) {
                        SHORT objectID = static_cast<SHORT>(pArea->m_nFirstObject + oldObjectID - areasObjectStart[area]);
                        LONG localObjectID = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->FindObjectId(objectID);

                        CGameObject* pObject;

                        BYTE rc;
                        do {
                            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(localObjectID,
                                CGameObjectArray::THREAD_ASYNCH,
                                &pObject,
                                INFINITE);
                        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                        if (rc == CGameObjectArray::SUCCESS) {
                            oldObjectID = pObject->m_remoteObjectID;
                            oldPlayerID = pObject->m_remotePlayerID;
                            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(localObjectID,
                                CGameObjectArray::THREAD_ASYNCH,
                                INFINITE);
                        }
                    }
                }
            }
        }

        ChangeControl(oldPlayerID,
            oldObjectID,
            newPlayerID,
            newObjectID,
            bLocalControl);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 1963
    UTIL_ASSERT(dwSize == cnt);

    return TRUE;
}

// 0x59BB40
BOOL CGameRemoteObjectArray::InitiateControl(PLAYER_ID remotePlayerID, LONG remoteObjectID, LONG localObjectID)
{
    Add(remotePlayerID, remoteObjectID, localObjectID, 0);

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        Add(g_pChitin->cNetwork.m_idLocalPlayer, localObjectID, localObjectID, 0);
    }

    return TRUE;
}

// 0x59BB90
BOOL CGameRemoteObjectArray::RemovePlayer(DWORD removedPlayerID)
{
    for (SHORT arrayIndex = 0; arrayIndex < m_nArraySize; arrayIndex++) {
        CGameRemoteObjectListEntry* entry = m_pArray[arrayIndex];
        while (entry != NULL) {
            if (entry->remotePlayerID == removedPlayerID) {
                CGameObject* pObject;

                BYTE rc;
                do {
                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(entry->localObjectID,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc != CGameObjectArray::SUCCESS) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                    // __LINE__: 2101
                    UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::RemovePlayer:  Deny not allowed on object.\n");
                }

                PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
                LONG remoteObjectID = pObject->m_remoteObjectID;

                if (pObject->GetObjectType() == CGameObject::TYPE_SPRITE
                    && static_cast<CGameSprite*>(pObject)->field_70F2 == 1) {
                    CMessage* message = new CMessage101(FALSE,
                        pObject->GetId(),
                        pObject->GetId(),
                        TRUE);
                    g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
                }

                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(entry->localObjectID,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);

                if (remotePlayerID == removedPlayerID) {
                    ChangeControl(remotePlayerID,
                        remoteObjectID,
                        g_pChitin->cNetwork.m_idLocalPlayer,
                        entry->localObjectID,
                        FALSE);
                }
            }
            entry = entry->pNext;
        }
    }

    return TRUE;
}

// 0x59BD00
BOOL CGameRemoteObjectArray::ChangeControlOnLoadArea(CGameArea* pArea)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 2150
    UTIL_ASSERT(pArea != NULL);

    if (!g_pChitin->cNetwork.GetSessionHosting()) {
        return FALSE;
    }

    DWORD initialAreaID = pArea->m_nInitialAreaID;
    SHORT lastObjectID = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->m_nNextObjectId;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 2162
    UTIL_ASSERT(m_nControlsAreaChanged < MAX_AREAS_CHANGED);

    m_psControlsAreaChangedName[m_nControlsAreaChanged] = pArea->m_resRef;
    m_pnControlsAreaChangedPlayerNum[m_nControlsAreaChanged] = pArea->m_nInitialAreaID;
    m_pnControlsAreaChangedFirstObject[m_nControlsAreaChanged] = static_cast<SHORT>(pArea->m_nFirstObject);
    m_nControlsAreaChanged++;

    for (SHORT objectID = static_cast<SHORT>(pArea->m_nFirstObject); objectID < lastObjectID; objectID++) {
        LONG localObjectID = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->FindObjectId(objectID);
        if (localObjectID != -1) {
            CGameObject* pObject;

            BYTE rc;
            do {
                rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(localObjectID,
                    CGameObjectArray::THREAD_ASYNCH,
                    &pObject,
                    INFINITE);
            } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

            if (rc != CGameObjectArray::SUCCESS) {
                return FALSE;
            }

            PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
            LONG remoteObjectID = pObject->m_remoteObjectID;
            BYTE listType = pObject->GetVertListType();
            BYTE objectType = pObject->GetObjectType();

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(localObjectID,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);

            if (remotePlayerID == initialAreaID) {
                if (objectType == CGameObject::TYPE_SPRITE) {
                    do {
                        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(localObjectID,
                            CGameObjectArray::THREAD_ASYNCH,
                            &pObject,
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        static_cast<CGameSprite*>(pObject)->m_inControlLastTime = TRUE;
                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(localObjectID,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }

                ChangeControl(remotePlayerID,
                    remoteObjectID,
                    g_pChitin->cNetwork.m_idLocalPlayer,
                    localObjectID,
                    listType == CGameObject::LIST_FLIGHT || objectType == CGameObject::TYPE_OBJECT_MARKER);
            }
        }
    }

    return TRUE;
}

// 0x59BF30
BOOL CGameRemoteObjectArray::ChangeControlOnLoadGame()
{
    if (!g_pChitin->cNetwork.GetSessionHosting()) {
        return FALSE;
    }

    for (SHORT arrayIndex = 0; arrayIndex < m_nArraySize; arrayIndex++) {
        CGameRemoteObjectListEntry* entry = m_pArray[arrayIndex];
        while (entry != NULL) {
            if (entry->remotePlayerID == 0) {
                CGameObject* pObject;

                BYTE rc;
                do {
                    rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(entry->localObjectID,
                        CGameObjectArray::THREAD_ASYNCH,
                        &pObject,
                        INFINITE);
                } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                if (rc != CGameObjectArray::SUCCESS) {
                    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                    // __LINE__: 2341
                    UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::ChangeControlOnLoadGame:  Share not allowed on object.\n");
                }

                PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
                LONG remoteObjectID = pObject->m_remoteObjectID;
                BYTE listType = pObject->GetVertListType();
                BYTE objectType = pObject->GetObjectType();
                g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(entry->localObjectID,
                    CGameObjectArray::THREAD_ASYNCH,
                    INFINITE);

                if (objectType == CGameObject::TYPE_SPRITE) {
                    do {
                        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(entry->localObjectID,
                            CGameObjectArray::THREAD_ASYNCH,
                            &pObject,
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        static_cast<CGameSprite*>(pObject)->m_inControlLastTime = TRUE;
                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(entry->localObjectID,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }

                ChangeControl(0,
                    remoteObjectID,
                    g_pChitin->cNetwork.m_idLocalPlayer,
                    entry->localObjectID,
                    listType == CGameObject::LIST_FLIGHT);
            }
            entry = entry->pNext;
        }
    }

    for (SHORT nCharacterSlot = 0; nCharacterSlot < CINFGAME_MAXCHARACTERS; nCharacterSlot++) {
        LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(nCharacterSlot);

        CGameObject* pObject;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                &pObject,
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            PLAYER_ID remotePlayerID = pObject->m_remotePlayerID;
            LONG remoteObjectID = pObject->m_remoteObjectID;
            BYTE objectType = pObject->GetObjectType();
            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);

            if (remotePlayerID == g_pChitin->cNetwork.m_idLocalPlayer) {
                INT playerLocation = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->GetCharacterControlledByPlayer(nCharacterSlot);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                // __LINE__: 2377
                UTIL_ASSERT(playerLocation >= 0);

                PLAYER_ID idPlayer = g_pChitin->cNetwork.GetPlayerID(playerLocation);
                if (objectType == CGameObject::TYPE_SPRITE) {
                    do {
                        rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            &pObject,
                            INFINITE);
                    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

                    if (rc == CGameObjectArray::SUCCESS) {
                        static_cast<CGameSprite*>(pObject)->m_inControlLastTime = remotePlayerID == idPlayer;
                        g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(nCharacterId,
                            CGameObjectArray::THREAD_ASYNCH,
                            INFINITE);
                    }
                }

                ChangeControl(remotePlayerID,
                    remoteObjectID,
                    idPlayer,
                    remoteObjectID,
                    FALSE);
            }
        } else {
            if (nCharacterId != -1) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                // __LINE__: 2403
                UTIL_ASSERT_MSG(FALSE, "CGameRemoteObjectArray::ChangeControlOnLoadGame:  Deny not allowed on object.\n");
            }
        }
    }

    return TRUE;
}

// NOTE: Inlined.
void CGameRemoteObjectArray::Clean()
{
    for (SHORT nIndex = 0; nIndex < m_nArraySize; nIndex++) {
        CGameRemoteObjectListEntry* node = m_pArray[nIndex];
        while (node != NULL) {
            CGameRemoteObjectListEntry* next = node->pNext;
            node->pNext = NULL;
            delete node;
            node = next;
        }
    }

    // NOTE: Uninline.
    CleanControlChanges();
}

#include "CGameObjectArray.h"

#include "CBaldurChitin.h"
#include "CGameContainer.h"
#include "CGameObject.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x85186C
const BYTE CGameObjectArray::SUCCESS = 0;

// 0x85186D
const BYTE CGameObjectArray::TIMEOUT = 1;

// 0x85186E
const BYTE CGameObjectArray::DELETED = 2;

// 0x85186F
const BYTE CGameObjectArray::BAD_INDEX = 3;

// 0x851870
const BYTE CGameObjectArray::SHARED = 4;

// 0x851871
const BYTE CGameObjectArray::DENIED = 5;

// 0x851872
const BYTE CGameObjectArray::NO_MEMORY = 6;

// 0x851873
const BYTE CGameObjectArray::THREAD_ASYNCH = 0;

// 0x851874
const BYTE CGameObjectArray::THREAD_1 = 1;

// 0x851875
const BYTE CGameObjectArray::THREAD_2 = 2;

// NOTE: Seen in `CScreenCreateChar::OnDoneButtonClick` assertion.
//
// 0x851878
const LONG CGameObjectArray::INVALID_INDEX = -1;

// 0x59A510
CGameObjectArrayEntry::CGameObjectArrayEntry()
{
    memset(m_shareCounts, 0, sizeof(m_shareCounts));
    memset(m_denyCounts, 0, sizeof(m_denyCounts));
    m_objectId = -1;
    m_objectIntPtr = -1;
}

// 0x599870
CGameObjectArray::CGameObjectArray(SHORT arrayStartSize, SHORT arrayGrowSize)
{
    m_nArrayGrowSize = arrayGrowSize;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 151
    UTIL_ASSERT(arrayStartSize >= 0 && arrayGrowSize > 0);

    m_nArraySize = 0;
    m_nMaxArrayIndex = -1;
    m_nNextObjectId = 0;
    m_deletedListHead = -1;

    // NOTE: Uninline.
    m_pArray = new CGameObjectArrayEntry[arrayStartSize];
    if (m_pArray != NULL) {
        m_nArraySize = arrayStartSize;
    }
}

// 0x599960
CGameObjectArray::~CGameObjectArray()
{
    while (m_nMaxArrayIndex >= 0) {
        if (m_pArray[m_nMaxArrayIndex].m_objectId != -1) {
            if (m_pArray[m_nMaxArrayIndex].m_objectPtr != NULL) {
                delete m_pArray[m_nMaxArrayIndex].m_objectPtr;
            }
            m_pArray[m_nMaxArrayIndex].m_objectIntPtr = -1;
            m_pArray[m_nMaxArrayIndex].m_objectId = -1;
            memset(m_pArray[m_nMaxArrayIndex].m_shareCounts, 0, sizeof(m_pArray[m_nMaxArrayIndex].m_shareCounts));
            memset(m_pArray[m_nMaxArrayIndex].m_denyCounts, 0, sizeof(m_pArray[m_nMaxArrayIndex].m_denyCounts));
        }
        m_nMaxArrayIndex--;
    }

    if (m_pArray != NULL) {
        delete m_pArray;
        m_pArray = NULL;
    }
}

// 0x599A50
BYTE CGameObjectArray::GetShare(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 225
    UTIL_ASSERT(ptr != NULL && threadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS);

    if (index == -1) {
        return BAD_INDEX;
    }

    if (threadNum == THREAD_ASYNCH) {
        SHORT arrayIndex = (index >> 16) & 0x7FFF;

        if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
            return BAD_INDEX;
        }

        if (m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
            return DELETED;
        }

        *ptr = m_pArray[arrayIndex].m_objectPtr;
        return SUCCESS;
    }

    CSingleLock lock(&m_cs, FALSE);
    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        lock.Unlock();
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        lock.Unlock();
        return DELETED;
    }

    for (BYTE otherThreadNum = 0; otherThreadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS; otherThreadNum++) {
        if (otherThreadNum != threadNum
            && m_pArray[arrayIndex].m_denyCounts[otherThreadNum] != 0) {
            lock.Unlock();
            return DENIED;
        }
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 297
    UTIL_ASSERT(m_pArray[arrayIndex].m_shareCounts[threadNum] < 255);

    m_pArray[arrayIndex].m_shareCounts[threadNum]++;
    *ptr = m_pArray[arrayIndex].m_objectPtr;

    lock.Unlock();
    return SUCCESS;
}

// 0x599C70
BYTE CGameObjectArray::GetDeny(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 398
    UTIL_ASSERT(threadNum == THREAD_ASYNCH);

    if (index == -1) {
        return BAD_INDEX;
    }

    CSingleLock lock(&m_cs, FALSE);
    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        lock.Unlock();
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        lock.Unlock();
        return DELETED;
    }

    for (BYTE otherThreadNum = 0; otherThreadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS; otherThreadNum++) {
        if (otherThreadNum != threadNum
            && m_pArray[arrayIndex].m_shareCounts[otherThreadNum] != 0) {
            lock.Unlock();
            SleepEx(1, FALSE);

            // FIXME: Redundant. There is also a implicit Unlock call in
            // destructor, so this branch calls `Unlock` three times.
            lock.Unlock();

            return SHARED;
        }
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 483
    UTIL_ASSERT(m_pArray[arrayIndex].m_denyCounts[threadNum] < 255);

    m_pArray[arrayIndex].m_denyCounts[threadNum]++;
    *ptr = m_pArray[arrayIndex].m_objectPtr;

    lock.Unlock();
    return SUCCESS;
}

// 0x599E70
BYTE CGameObjectArray::ReleaseShare(LONG index, BYTE threadNum, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 514
    UTIL_ASSERT(threadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS);

    if (index == -1) {
        return BAD_INDEX;
    }

    if (threadNum == THREAD_ASYNCH) {
        return SUCCESS;
    }

    CSingleLock lock(&m_cs, FALSE);
    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        lock.Unlock();
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != -1 && m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 559
        UTIL_ASSERT(FALSE);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 566
    UTIL_ASSERT(m_pArray[arrayIndex].m_shareCounts[threadNum] > 0);

    m_pArray[arrayIndex].m_shareCounts[threadNum]--;

    lock.Unlock();

    return SUCCESS;
}

// 0x59A010
BYTE CGameObjectArray::ReleaseDeny(LONG index, BYTE threadNum, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 647
    UTIL_ASSERT(threadNum == THREAD_ASYNCH);

    if (index == -1) {
        return BAD_INDEX;
    }

    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != -1 && m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        return DELETED;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 691
    UTIL_ASSERT(m_pArray[arrayIndex].m_denyCounts[threadNum] > 0);

    m_pArray[arrayIndex].m_denyCounts[threadNum]--;

    return SUCCESS;
}

// 0x59A0F0
BYTE CGameObjectArray::Add(LONG* index, CGameObject* ptr, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 559
    UTIL_ASSERT(index != NULL && ptr != NULL);

    CSingleLock lock(&m_cs, FALSE);
    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nNextObjectId == 0x7FFF) {
        lock.Unlock();
        return NO_MEMORY;
    }

    SHORT arrayIndex = m_deletedListHead;
    if (arrayIndex == -1) {
        if (m_nMaxArrayIndex + 1 >= m_nArraySize) {
            if (m_nArraySize + m_nArrayGrowSize >= 0x7FFF) {
                lock.Unlock();
                return NO_MEMORY;
            }

            CGameObjectArrayEntry* pNewArray = new CGameObjectArrayEntry[m_nArraySize + m_nArrayGrowSize];
            if (pNewArray == NULL) {
                lock.Unlock();
                return NO_MEMORY;
            }

            for (SHORT n = 0; n <= m_nMaxArrayIndex; n++) {
                // NOTE: Original code is slightly different, it copies every
                // property one by one. I'm not sure if such `memcpy` is allowed
                // in both old and new C++.
                memcpy(&(pNewArray[n]), &(m_pArray[n]), sizeof(CGameObjectArrayEntry));
            }

            delete m_pArray;

            m_nArraySize += m_nArrayGrowSize;
            m_pArray = pNewArray;

            m_nMaxArrayIndex++;
            arrayIndex = m_nMaxArrayIndex;
        } else {
            m_nMaxArrayIndex++;
            arrayIndex = m_nMaxArrayIndex;
        }
    } else {
        // NOTE: See `CGameObjectArray::Delete`.
        m_deletedListHead = m_pArray[arrayIndex].m_nextDeletedArrayIndex;
    }

    *index = m_nNextObjectId | (arrayIndex << 16);

    m_pArray[arrayIndex].m_objectId = m_nNextObjectId++;
    m_pArray[arrayIndex].m_objectPtr = ptr;

    CAIObjectType type(ptr->GetAIType());
    type.m_nInstance = *index;
    ptr->SetAIType(type, 0);

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
        if (pGame->m_bInLoadArea == TRUE) {
            pGame->GetRemoteObjectArray()->Add(pGame->m_nUniqueAreaID,
                *index,
                *index,
                FALSE);

            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                pGame->GetRemoteObjectArray()->Add(g_pChitin->cNetwork.m_idLocalPlayer,
                    *index,
                    *index,
                    FALSE);
            }

            ptr->m_remotePlayerID = pGame->m_nUniqueAreaID;
            ptr->m_remoteObjectID = *index;

            // NOTE: Unsigned compare.
            if (pGame->m_nAreaFirstObject > static_cast<DWORD>(m_nNextObjectId - 1)) {
                pGame->m_nAreaFirstObject = m_nNextObjectId - 1;
            }
        } else if (pGame->m_bInLoadGame == TRUE) {
            pGame->GetRemoteObjectArray()->Add(0,
                *index,
                *index,
                FALSE);

            if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                pGame->GetRemoteObjectArray()->Add(g_pChitin->cNetwork.m_idLocalPlayer,
                    *index,
                    *index,
                    FALSE);
            }

            ptr->m_remotePlayerID = 0;
            ptr->m_remoteObjectID = *index;
        } else {
            if (!g_pBaldurChitin->GetBaldurMessage()->m_bInOnObjectAdd) {
                pGame->GetRemoteObjectArray()->Add(g_pChitin->cNetwork.m_idLocalPlayer,
                    *index,
                    *index,
                    FALSE);

                if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                    pGame->GetRemoteObjectArray()->Add(g_pChitin->cNetwork.m_idLocalPlayer,
                        *index,
                        *index,
                        FALSE);
                }

                ptr->m_remotePlayerID = 0;
                ptr->m_remoteObjectID = *index;

                if (ptr->GetObjectType() == CGameObject::TYPE_CONTAINER) {
                    BYTE* pObjectData;
                    DWORD dwObjectDataSize;
                    static_cast<CGameContainer*>(ptr)->MarshalMessage(&pObjectData, &dwObjectDataSize);
                    g_pBaldurChitin->GetBaldurMessage()->ObjectAdd(*index,
                        ptr->GetObjectType(),
                        pObjectData,
                        dwObjectDataSize);
                }
            }
        }
    }

    lock.Unlock();

    return SUCCESS;
}

// 0x59A530
BYTE CGameObjectArray::Delete(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 881
    UTIL_ASSERT(threadNum == THREAD_ASYNCH);

    if (index == -1) {
        return BAD_INDEX;
    }

    CSingleLock lock(&m_cs, FALSE);

    if (ptr != NULL) {
        *ptr = NULL;
    }

    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        lock.Unlock();
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        lock.Unlock();
        return DELETED;
    }

    for (BYTE otherThreadNum = 0; otherThreadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS; otherThreadNum++) {
        if (otherThreadNum != THREAD_ASYNCH
            && m_pArray[arrayIndex].m_shareCounts[otherThreadNum] != 0) {
            lock.Unlock();
            SleepEx(1, FALSE);
            return SHARED;
        }
    }

    // TODO: Incomplete.

    if (ptr != NULL) {
        *ptr = m_pArray[arrayIndex].m_objectPtr;
    }

    m_pArray[arrayIndex].m_nextDeletedArrayIndex = m_deletedListHead;
    m_deletedListHead = arrayIndex;

    // TODO: Incomplete.

    return SUCCESS;
}

// 0x59A740
BYTE CGameObjectArray::ChangeEntry(LONG index, BYTE threadNum, CGameObject* ptr, DWORD dwTimeOut)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 979
    UTIL_ASSERT(threadNum == THREAD_ASYNCH);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
    // __LINE__: 982
    UTIL_ASSERT(ptr != NULL);

    if (index == -1) {
        return BAD_INDEX;
    }

    CSingleLock lock(&m_cs, FALSE);

    SHORT arrayIndex = (index >> 16) & 0x7FFF;

    if (!lock.Lock(dwTimeOut)) {
        return TIMEOUT;
    }

    if (m_nMaxArrayIndex < arrayIndex || (index & 0x8000) != 0 || m_nNextObjectId <= static_cast<SHORT>(index)) {
        lock.Unlock();
        return BAD_INDEX;
    }

    if (m_pArray[arrayIndex].m_objectId != static_cast<SHORT>(index)) {
        lock.Unlock();
        return DELETED;
    }

    for (BYTE otherThreadNum = 0; otherThreadNum < CGAMEOBJECTARRAYENTRY_MAXTHREADS; otherThreadNum++) {
        if (m_pArray[arrayIndex].m_denyCounts[otherThreadNum] != 0) {
            if (otherThreadNum == THREAD_ASYNCH) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                // __LINE__: 1012
                UTIL_ASSERT(FALSE);
            }

            lock.Unlock();
            SleepEx(1, FALSE);
            return DENIED;
        }

        if (m_pArray[arrayIndex].m_shareCounts[otherThreadNum] != 0) {
            if (otherThreadNum == THREAD_ASYNCH) {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
                // __LINE__: 1024
                UTIL_ASSERT(FALSE);
            }

            lock.Unlock();
            SleepEx(1, FALSE);
            return SHARED;
        }
    }

    delete m_pArray[arrayIndex].m_objectPtr;
    m_pArray[arrayIndex].m_objectPtr = ptr;

    CAIObjectType type(ptr->GetAIType());
    type.SetInstance(index);
    ptr->SetAIType(type, 0);

    // NOTE: No explicit unlock.

    return SUCCESS;
}

// 0x59A9D0
void CGameObjectArray::Clean()
{
    CSingleLock lock(&m_cs, FALSE);

    if (!lock.Lock(INFINITE)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 1071
        UTIL_ASSERT(FALSE);
    }

    while (m_nMaxArrayIndex >= 0) {
        if (m_pArray[m_nMaxArrayIndex].m_objectId != -1) {
            if (m_pArray[m_nMaxArrayIndex].m_objectPtr != NULL) {
                delete m_pArray[m_nMaxArrayIndex].m_objectPtr;
            }
        }

        m_pArray[m_nMaxArrayIndex].m_objectPtr = (CGameObject*)-1;
        m_pArray[m_nMaxArrayIndex].m_objectId = -1;
        memset(m_pArray[m_nMaxArrayIndex].m_shareCounts, 0, sizeof(m_pArray[m_nMaxArrayIndex].m_shareCounts));
        memset(m_pArray[m_nMaxArrayIndex].m_denyCounts, 0, sizeof(m_pArray[m_nMaxArrayIndex].m_denyCounts));

        m_nMaxArrayIndex--;
    }

    m_deletedListHead = -1;
    m_nNextObjectId = 0;

    // NOTE: Uninline.
    g_pBaldurChitin->GetObjectGame()->GetRemoteObjectArray()->Clean();
}

// 0x59ABD0
LONG CGameObjectArray::FindObjectId(SHORT id)
{
    CSingleLock lock(&m_cs, FALSE);

    if (!lock.Lock(INFINITE)) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfGame.cpp
        // __LINE__: 1130
        UTIL_ASSERT(FALSE);
    }

    SHORT arrayIndex = m_nMaxArrayIndex;
    while (arrayIndex >= 0) {
        if (m_pArray[arrayIndex].m_objectId == id) {
            lock.Unlock();
            return (arrayIndex << 16) | id;
        }
        arrayIndex--;
    }

    lock.Unlock();
    return -1;
}

#ifndef CGAMEOBJECTARRAY_H_
#define CGAMEOBJECTARRAY_H_

#include "mfc.h"

#define CGAMEOBJECTARRAYENTRY_MAXTHREADS 3

class CGameObject;

class CGameObjectArrayEntry {
public:
    CGameObjectArrayEntry();

    BYTE m_shareCounts[CGAMEOBJECTARRAYENTRY_MAXTHREADS];
    BYTE m_denyCounts[CGAMEOBJECTARRAYENTRY_MAXTHREADS];
    SHORT m_objectId;
    union {
        CGameObject* m_objectPtr;
        DWORD m_objectIntPtr;
        SHORT m_nextDeletedArrayIndex;
    };
};

class CGameObjectArray {
public:
    static const BYTE SUCCESS;
    static const BYTE TIMEOUT;
    static const BYTE DELETED;
    static const BYTE BAD_INDEX;
    static const BYTE SHARED;
    static const BYTE DENIED;
    static const BYTE NO_MEMORY;

    static const BYTE THREAD_ASYNCH;
    static const BYTE THREAD_1;
    static const BYTE THREAD_2;

    static const LONG INVALID_OBJECT_ID;

    CGameObjectArray(SHORT arrayStartSize = 100, SHORT arrayGrowSize = 10);
    ~CGameObjectArray();
    BYTE GetShare(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut);
    BYTE GetDeny(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut);
    BYTE ReleaseShare(LONG index, BYTE threadNum, DWORD dwTimeOut);
    BYTE ReleaseDeny(LONG index, BYTE threadNum, DWORD dwTimeOut);
    BYTE Add(LONG* index, CGameObject* ptr, DWORD dwTimeOut);
    BYTE Delete(LONG index, BYTE threadNum, CGameObject** ptr, DWORD dwTimeOut);
    void Clean();
    LONG FindObjectId(SHORT id);

    /* 0000 */ CCriticalSection m_cs;
    /* 0020 */ CGameObjectArrayEntry* m_pArray;
    /* 0024 */ SHORT m_nArraySize;
    /* 0026 */ SHORT m_nArrayGrowSize;
    /* 0028 */ SHORT m_nMaxArrayIndex;
    /* 002A */ SHORT m_nNextObjectId;
    /* 002C */ SHORT m_deletedListHead;
};

#endif /* CGAMEOBJECTARRAY_H_ */

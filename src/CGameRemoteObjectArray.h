#ifndef CGAMEREMOTEOBJECTARRAY_H_
#define CGAMEREMOTEOBJECTARRAY_H_

#include "mfc.h"

#include "CResRef.h"

class CGameArea;

// TODO: Reuse from `CNetwork`.
typedef DWORD PLAYER_ID;

#define MAX_AREAS_CHANGED 6

class CGameRemoteObjectControlChange {
public:
    CGameRemoteObjectControlChange();

    /* 0000 */ PLAYER_ID oldPlayerID;
    /* 0004 */ LONG oldObjectID;
    /* 0008 */ PLAYER_ID newPlayerID;
    /* 000C */ LONG newObjectID;
    /* 0010 */ CGameRemoteObjectControlChange* pNext;
    /* 0014 */ BOOLEAN localControl;
};

class CGameRemoteObjectListEntry {
public:
    CGameRemoteObjectListEntry();

    /* 0000 */ PLAYER_ID remotePlayerID;
    /* 0004 */ LONG remoteObjectID;
    /* 0008 */ LONG localObjectID;
    /* 000C */ CGameRemoteObjectListEntry* pNext;
};

class CGameRemoteObjectArray {
public:
    CGameRemoteObjectArray(SHORT nArraySize = 100);
    ~CGameRemoteObjectArray();
    BOOL Add(PLAYER_ID remotePlayerID, LONG remoteObjectID, LONG localObjectID, BOOLEAN bSetInGame);
    BOOL CleanControlChanges();
    BOOL Delete(LONG localObjectID);
    BOOL Find(DWORD remotePlayerID, LONG remoteObjectID, LONG& localObjectID);
    BOOL ChangeControl(PLAYER_ID oldRemotePlayerID, LONG oldRemoteObjectID, PLAYER_ID newRemotePlayerID, LONG newRemoteObjectID, BOOLEAN bLocalControl);
    BOOL MarshalControlChanges(BYTE** pData, DWORD* dwSize);
    BOOL UnmarshalControlChanges(BYTE* pData, DWORD dwSize);
    BOOL InitiateControl(PLAYER_ID remotePlayerID, LONG remoteObjectID, LONG localObjectID);
    BOOL RemovePlayer(DWORD removedPlayerID);
    BOOL ChangeControlOnLoadArea(CGameArea* pArea);
    BOOL ChangeControlOnLoadGame();

    void Clean();

    /* 0000 */ CGameRemoteObjectListEntry** m_pArray;
    /* 0004 */ SHORT m_nArraySize;
    /* 0006 */ SHORT m_nControlsChanged;
    /* 0008 */ CGameRemoteObjectControlChange* m_pControlsChanged;
    /* 000C */ CGameRemoteObjectControlChange* m_pControlsChangedTail;
    /* 0010 */ SHORT m_nControlsAreaChanged;
    /* 0012 */ CResRef m_psControlsAreaChangedName[MAX_AREAS_CHANGED];
    /* 0042 */ DWORD m_pnControlsAreaChangedPlayerNum[MAX_AREAS_CHANGED];
    /* 005A */ SHORT m_pnControlsAreaChangedFirstObject[MAX_AREAS_CHANGED];
    /* 0066 */ CCriticalSection m_critSect;
};

#endif /* CGAMEREMOTEOBJECTARRAY_H_ */

#ifndef CAIGROUP_H_
#define CAIGROUP_H_

#include "mfc.h"

class CGameSprite;

class CAIGroup {
public:
    CAIGroup(SHORT id = -1);

    LONG GetGroupLeader();
    LONG* GetGroupList();
    void Add(CGameSprite* pSprite);
    POSITION Add(LONG characterId);
    void Remove(CGameSprite* pSprite);
    BOOL IsPartyLeader();
    void Sort();
    void GroupCancelMove();
    BOOL InList(LONG characterId);

    /* 0000 */ SHORT m_groupId;
    /* 0002 */ BOOL m_groupChanged;
    /* 0006 */ CTypedPtrList<CPtrList, LONG*> m_memberList;
};

#endif /* CAIGROUP_H_ */

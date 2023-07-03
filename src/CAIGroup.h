#ifndef CAIGROUP_H_
#define CAIGROUP_H_

#include "mfc.h"

class CGameSprite;

class CAIGroup {
public:
    LONG GetGroupLeader();
    LONG* GetGroupList();
    void Add(CGameSprite* pSprite);
    POSITION Add(LONG characterId);
    void Remove(CGameSprite* pSprite);
    BOOL IsPartyLeader();
    BOOL InList(LONG characterId);

    /* 0004 */ BOOL m_groupChanged;
    /* 0006 */ CTypedPtrList<CPtrList, LONG*> m_memberList;
};

#endif /* CAIGROUP_H_ */

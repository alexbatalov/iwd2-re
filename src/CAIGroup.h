#ifndef CAIGROUP_H_
#define CAIGROUP_H_

#include "mfc.h"

class CAIGroup {
public:
    LONG GetGroupLeader();
    LONG* GetGroupList();
    POSITION Add(LONG characterId);
    BOOL IsPartyLeader();
    BOOL InList(LONG characterId);

    /* 0004 */ BOOL m_groupChanged;
    /* 0006 */ CTypedPtrList<CPtrList, LONG*> m_memberList;
};

#endif /* CAIGROUP_H_ */

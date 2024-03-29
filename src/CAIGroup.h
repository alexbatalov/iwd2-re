#ifndef CAIGROUP_H_
#define CAIGROUP_H_

#include "mfc.h"

#include "CAIAction.h"

#define CAIGROUP_FORMATION_GATHER 2
#define CAIGROUP_FORMATION_T 1
#define CAIGROUP_FORMATION_RANK 7
#define CAIGROUP_FORMATION_3BY2 4
#define CAIGROUP_FORMATION_2BY3 6
#define CAIGROUP_FORMATION_PROTECT 5
#define CAIGROUP_FORMATION_4AND2 3
#define CAIGROUP_FORMATION_V 8
#define CAIGROUP_FORMATION_WEDGE 9
#define CAIGROUP_FORMATION_LINE 11
#define CAIGROUP_FORMATION_S 10
#define CAIGROUP_FORMATION_FOLLOW 0
#define CAIGROUP_FORMATION_MAX_SIZE 12

class CAITrigger;
class CGameSprite;
class CSearchBitmap;

class CAIGroup {
public:
    static const LONG OFFSET_MULTIPLIER;

    static const SHORT FORMATION_NONE;

    static const SHORT FORMATION_GATHER;
    static const CPoint FORMATION_GATHER_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_GATHER_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_T;
    static const CPoint FORMATION_T_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_T_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_RANK;
    static const CPoint FORMATION_RANK_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_RANK_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_3BY2;
    static const CPoint FORMATION_3BY2_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_3BY2_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_2BY3;
    static const CPoint FORMATION_2BY3_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_2BY3_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_PROTECT;
    static const CPoint FORMATION_PROTECT_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_PROTECT_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_4AND2;
    static const CPoint FORMATION_4AND2_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_4AND2_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_V;
    static const CPoint FORMATION_V_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_V_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_WEDGE;
    static const CPoint FORMATION_WEDGE_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_WEDGE_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_LINE;
    static const CPoint FORMATION_LINE_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_LINE_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_S;
    static const CPoint FORMATION_S_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE];
    static const SHORT FORMATION_S_FACE[CAIGROUP_FORMATION_MAX_SIZE];

    static const SHORT FORMATION_FOLLOW;

    static const SHORT DEADZONE;
    static const SHORT WAIT_BASE;
    static const SHORT FORMATION_MAX_SIZE;

    CAIGroup(SHORT id = -1);

    void GroupAction(CAIAction action, BOOL override, CAIAction* leaderAction);
    void SetGroupTriggerId(LONG triggerId);
    void RemoveFromSearch(CSearchBitmap* search);
    void AddToSearch(CSearchBitmap* search);
    LONG GetGroupLeader();
    LONG* GetGroupList();
    void Add(CGameSprite* pSprite);
    POSITION Add(LONG characterId);
    void Remove(CGameSprite* pSprite);
    BOOL IsPartyLeader();
    void Sort();
    void GroupSetTarget(CPoint target, BOOL additive, SHORT formationType, CPoint cursor);
    void GroupProtectPoint(CPoint target, SHORT formationType, CPoint cursor, LONG range);
    void GroupDrawMove(CPoint target, SHORT formationType, CPoint cursor);
    void GroupCancelMove();
    void ClearActions();
    void GroupSetTarget(LONG iObject);
    void AddTrigger(CAITrigger& trigger);
    BOOL InList(LONG characterId);
    void FollowLeader(CPoint target, BOOL additive);
    void HandleFollowPath(LONG* pPath, INT nPath, CPoint target, CPoint start, BOOL additive);

    BYTE GetCount();

    /* 0000 */ SHORT m_groupId;
    /* 0002 */ BOOL m_groupChanged;
    /* 0006 */ CTypedPtrList<CPtrList, LONG*> m_memberList;
};

#endif /* CAIGROUP_H_ */

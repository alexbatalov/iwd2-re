#include "CAIGroup.h"

#include "CBaldurChitin.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
#include "CInfGame.h"

// 0x8479E4
const LONG CAIGroup::OFFSET_MULTIPLIER = 1000;

// 0x8479E8
const SHORT CAIGroup::FORMATION_NONE = 12;

// 0x8479EA
const SHORT CAIGroup::FORMATION_GATHER = CAIGROUP_FORMATION_GATHER;

// 0x8C6D98
const CPoint CAIGroup::FORMATION_GATHER_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, -3 },
    { 3, -2 },
    { -3, -2 },
    { 3, 2 },
    { -3, 2 },
    { 0, 3 },
    { 3, 5 },
    { -3, 5 },
    { 0, 6 },
    { 3, 8 },
    { -3, 8 },
    { 0, 9 },
};

// 0x8479EC
const SHORT CAIGroup::FORMATION_GATHER_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    10,
    6,
    14,
    2,
    0,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A04
const SHORT CAIGroup::FORMATION_T = CAIGROUP_FORMATION_T;

// 0x8C6DF8
const CPoint CAIGroup::FORMATION_T_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, 0 },
    { 4, 0 },
    { -4, 0 },
    { 0, 4 },
    { 0, 7 },
    { 0, 10 },
    { 4, 4 },
    { -4, 4 },
    { 4, 7 },
    { -4, 7 },
    { 4, 10 },
    { -4, 10 },
};

// 0x847A08
const SHORT CAIGroup::FORMATION_T_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A20
const SHORT CAIGroup::FORMATION_RANK = CAIGROUP_FORMATION_RANK;

// 0x8C66E0
const CPoint CAIGroup::FORMATION_RANK_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { -2, 0 },
    { 2, 0 },
    { -6, 0 },
    { 6, 0 },
    { -10, 0 },
    { 10, 0 },
    { -2, 3 },
    { 2, 3 },
    { -6, 3 },
    { 6, 3 },
    { -10, 3 },
    { 10, 3 },
};

// 0x847A24
const SHORT CAIGroup::FORMATION_RANK_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A3C
const SHORT CAIGroup::FORMATION_3BY2 = CAIGROUP_FORMATION_3BY2;

// 0x8C6BA0
const CPoint CAIGroup::FORMATION_3BY2_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, 0 },
    { 4, 0 },
    { -4, 0 },
    { 0, 4 },
    { 4, 4 },
    { -4, 4 },
    { 0, 8 },
    { 4, 8 },
    { -4, 8 },
    { 0, 12 },
    { 4, 12 },
    { -1, 12 },
};

// 0x847A40
const SHORT CAIGroup::FORMATION_3BY2_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A58
const SHORT CAIGroup::FORMATION_2BY3 = CAIGROUP_FORMATION_2BY3;

// 0x8C6C08
const CPoint CAIGroup::FORMATION_2BY3_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { -2, 0 },
    { 2, 0 },
    { -2, 4 },
    { 2, 4 },
    { -2, 7 },
    { 2, 7 },
    { -6, 0 },
    { 6, 0 },
    { -6, 4 },
    { 6, 4 },
    { -6, 7 },
    { 6, 7 },
};

// 0x847A5C
const SHORT CAIGroup::FORMATION_2BY3_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A74
const SHORT CAIGroup::FORMATION_PROTECT = CAIGROUP_FORMATION_PROTECT;

// 0x8C6740
const CPoint CAIGroup::FORMATION_PROTECT_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, -3 },
    { 4, 0 },
    { -4, 0 },
    { 2, 4 },
    { -2, 4 },
    { 0, 0 },
    { 0, -6 },
    { 4, -3 },
    { -4, -3 },
    { 5, 5 },
    { -5, 5 },
    { 0, 7 },
};

// 0x847A78
const SHORT CAIGroup::FORMATION_PROTECT_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    10,
    6,
    14,
    2,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847A90
const SHORT CAIGroup::FORMATION_4AND2 = CAIGROUP_FORMATION_4AND2;

// 0x8C6D30
const CPoint CAIGroup::FORMATION_4AND2_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { -2, 0 },
    { 2, 0 },
    { -6, 0 },
    { 6, 0 },
    { -2, 4 },
    { 2, 4 },
    { -6, 4 },
    { 6, 4 },
    { -2, 8 },
    { 2, 8 },
    { -6, 8 },
    { 6, 8 },
};

// 0x847A94
const SHORT CAIGroup::FORMATION_4AND2_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847AAC
const SHORT CAIGroup::FORMATION_V = CAIGROUP_FORMATION_V;

// 0x8C6C68
const CPoint CAIGroup::FORMATION_V_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { -1, 0 },
    { 1, 0 },
    { -2, 3 },
    { 2, 3 },
    { -4, 6 },
    { 4, 6 },
    { -1, 6 },
    { 1, 6 },
    { -2, 9 },
    { 2, 9 },
    { -4, 12 },
    { 4, 12 },
};

// 0x847AB0
const SHORT CAIGroup::FORMATION_V_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847AC8
const SHORT CAIGroup::FORMATION_WEDGE = CAIGROUP_FORMATION_WEDGE;

// 0x8C6618
const CPoint CAIGroup::FORMATION_WEDGE_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, 0 },
    { 4, 3 },
    { -4, 3 },
    { -8, 6 },
    { 8, 6 },
    { 0, 6 },
    { -8, 0 },
    { 8, 0 },
    { -12, 9 },
    { -6, 9 },
    { 6, 9 },
    { 12, 9 },
};

// 0x847ACC
const SHORT CAIGroup::FORMATION_WEDGE_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847AE4
const SHORT CAIGroup::FORMATION_LINE = CAIGROUP_FORMATION_LINE;

// 0x8C6680
const CPoint CAIGroup::FORMATION_LINE_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 0, 0 },
    { 0, 3 },
    { 0, 6 },
    { 0, 9 },
    { 0, 12 },
    { 0, 15 },
    { 0, 18 },
    { 0, 21 },
    { 0, 24 },
    { 0, 27 },
    { 0, 30 },
    { 0, 33 },
};

// 0x847AE8
const SHORT CAIGroup::FORMATION_LINE_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847B00
const SHORT CAIGroup::FORMATION_S = CAIGROUP_FORMATION_S;

// 0x8C6CC8
const CPoint CAIGroup::FORMATION_S_OFFSETS[CAIGROUP_FORMATION_MAX_SIZE] = {
    { 1, 0 },
    { -1, 2 },
    { 1, 4 },
    { -1, 6 },
    { 1, 8 },
    { -1, 10 },
    { 1, 12 },
    { -1, 14 },
    { 1, 16 },
    { -1, 18 },
    { 1, 20 },
    { -1, 22 },
};

// 0x847B04
const SHORT CAIGroup::FORMATION_S_FACE[CAIGROUP_FORMATION_MAX_SIZE] = {
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
    8,
};

// 0x847B1C
const SHORT CAIGroup::FORMATION_FOLLOW = CAIGROUP_FORMATION_FOLLOW;

// 0x847B1E
const SHORT CAIGroup::DEADZONE = 12;

// 0x847B20
const SHORT CAIGroup::WAIT_BASE = 5;

// 0x847B22
const SHORT CAIGroup::FORMATION_MAX_SIZE = CAIGROUP_FORMATION_MAX_SIZE;

// NOTE: Inlined.
CAIGroup::CAIGroup(SHORT id)
{
    m_groupId = id;
    m_groupChanged = FALSE;
}

// 0x4060C0
LONG CAIGroup::GetGroupLeader()
{
    if (m_memberList.GetCount() > 0) {
        return reinterpret_cast<LONG>(m_memberList.GetHead());
    }

    return CGameObjectArray::INVALID_INDEX;
}

// 0x4060E0
LONG* CAIGroup::GetGroupList()
{
    LONG* pList = new LONG(m_memberList.GetCount());

    int index = 0;
    POSITION pos = m_memberList.GetHeadPosition();
    while (pos != NULL) {
        pList[index++] = reinterpret_cast<LONG>(m_memberList.GetNext(pos));
    }

    return pList;
}

// 0x406110
void CAIGroup::Add(CGameSprite* pSprite)
{
    if (pSprite->m_groupPosition != NULL) {
        // NOTE: Uninline.
        Remove(pSprite);
    }

    pSprite->m_groupPosition = Add(pSprite->m_id);
}

// 0x406170
POSITION CAIGroup::Add(LONG characterId)
{
    SHORT portraitNum = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(characterId);
    m_groupChanged = TRUE;
    if (portraitNum == -1) {
        return m_memberList.AddTail(reinterpret_cast<LONG*>(characterId));
    }

    POSITION pos = m_memberList.GetHeadPosition();
    while (pos != NULL) {
        LONG memberId = reinterpret_cast<LONG>(m_memberList.GetAt(pos));
        SHORT memberPortraitNum = g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(memberId);
        if (memberPortraitNum == -1 || memberPortraitNum > portraitNum) {
            return m_memberList.InsertBefore(pos, reinterpret_cast<LONG*>(characterId));
        }
        m_memberList.GetNext(pos);
    }

    return m_memberList.AddTail(reinterpret_cast<LONG*>(characterId));
}

// 0x406210
void CAIGroup::Remove(CGameSprite* pSprite)
{
    m_groupChanged = TRUE;
    if (pSprite->m_groupPosition != NULL) {
        m_memberList.RemoveAt(pSprite->m_groupPosition);
        m_groupChanged = TRUE;
    }
    pSprite->m_groupPosition = NULL;
}

// 0x406250
BOOL CAIGroup::IsPartyLeader()
{
    if (m_memberList.GetCount() == 0) {
        return FALSE;
    }

    LONG memberId = reinterpret_cast<LONG>(m_memberList.GetHead());
    if (g_pBaldurChitin->GetObjectGame()->GetCharacterPortraitNum(memberId) != -1) {
        return TRUE;
    }

    return g_pBaldurChitin->GetObjectGame()->m_familiars.Find(reinterpret_cast<int*>(memberId)) != NULL;
}

// 0x4062B0
void CAIGroup::Sort()
{
    CAIGroup tempGroup;
    POSITION pos;

    m_groupChanged = TRUE;

    pos = m_memberList.GetHeadPosition();
    while (pos != NULL) {
        LONG memberId = reinterpret_cast<LONG>(m_memberList.GetNext(pos));
        tempGroup.Add(memberId);
    }

    m_memberList.RemoveAll();

    pos = tempGroup.m_memberList.GetHeadPosition();
    while (pos != NULL) {
        LONG memberId = reinterpret_cast<LONG>(tempGroup.m_memberList.GetNext(pos));

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(memberId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pSprite->m_groupPosition = m_memberList.AddTail(reinterpret_cast<LONG*>(memberId));

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(memberId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x408660
void CAIGroup::GroupCancelMove()
{
    if (m_memberList.GetCount() == 0) {
        return;
    }

    POSITION pos = m_memberList.GetHeadPosition();
    while (pos != NULL) {
        LONG memberId = reinterpret_cast<LONG>(m_memberList.GetNext(pos));

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetDeny(memberId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pSprite->m_targetPoint.x = -1;
            pSprite->m_targetPoint.y = -1;
            pSprite->m_groupMove = FALSE;

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseDeny(memberId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x4093E0
BOOL CAIGroup::InList(LONG characterId)
{
    return m_memberList.Find(reinterpret_cast<LONG*>(characterId)) != NULL;
}

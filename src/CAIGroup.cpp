#include "CAIGroup.h"

#include "CBaldurChitin.h"
#include "CGameObjectArray.h"
#include "CGameSprite.h"
#include "CInfGame.h"

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

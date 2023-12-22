#include "CGameObject.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameObjectArray.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CTimerWorld.h"
#include "CUtil.h"

// 0x84C500
const BYTE CGameObject::TYPE_NONE = 0;

// 0x84C501
const BYTE CGameObject::TYPE_AIBASE = 1;

// 0x84C502
const BYTE CGameObject::TYPE_CONTAINER = 17;

// 0x84C503
const BYTE CGameObject::TYPE_DOOR = 33;

// 0x84C504
const BYTE CGameObject::TYPE_OBJECT_MARKER = 64;

// 0x84C505
const BYTE CGameObject::TYPE_SOUND = 16;

// 0x84C506
const BYTE CGameObject::TYPE_SPAWNING = 32;

// 0x84C507
const BYTE CGameObject::TYPE_SPRITE = 49;

// 0x84C508
const BYTE CGameObject::TYPE_STATIC = 48;

// 0x84C509
const BYTE CGameObject::TYPE_TRIGGER = 65;

// 0x84C50A
const BYTE CGameObject::TYPE_TILED_OBJECT = 81;

// 0x84C50B
const BYTE CGameObject::TYPE_TEXT = 80;

// 0x84C50C
const BYTE CGameObject::LIST_FRONT = CGAMEOBJECT_LIST_FRONT;

// 0x84C50D
const BYTE CGameObject::LIST_BACK = CGAMEOBJECT_LIST_BACK;

// 0x84C50E
const BYTE CGameObject::LIST_FLIGHT = CGAMEOBJECT_LIST_FLIGHT;

// 0x84C50F
const BYTE CGameObject::VISIBLE_DELAY = 7;

// 0x84C510
const BYTE CGameObject::CHUNK_DURATION = 31;

// 0x84C511
const BYTE CGameObject::AI_SPEED_NORMAL = 1;

// 0x84C512
const BYTE CGameObject::AI_SPEED_SLOWED = 3;

// 0x84C513
const BYTE CGameObject::AI_SPEED_HASTED = 0;

// 0x84C514
const BYTE CGameObject::DEFAULT_VISIBLE_TERRAIN_TABLE[16] = {
    255,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    255,
    5,
    5,
    255,
    5,
    5,
};

// 0x84C524
const BYTE CGameObject::DEFAULT_TERRAIN_TABLE[16] = {
    255,
    5,
    5,
    5,
    5,
    5,
    5,
    5,
    255,
    5,
    255,
    5,
    255,
    255,
    255,
    5,
};

// 0x4C7B30
CGameObject::CGameObject()
{
    m_pos.x = -1;
    m_pos.y = -1;
    m_objectType = TYPE_NONE;
    m_posZ = 0;
    m_pArea = NULL;
    m_posVertList = NULL;
    m_id = CGameObjectArray::INVALID_INDEX;
    m_canBeSeen = 0;
    m_AISpeed = AI_SPEED_NORMAL;
    m_typeAI.Set(CAIObjectType::NOT_SPRITE);
    m_remotePlayerID = 0;
    m_remoteObjectID = CGameObjectArray::INVALID_INDEX;
    field_6B = 0;
    field_1C = 0;
    m_listType = LIST_FRONT;
    m_AIInhibitor = 0;
}

// 0x44CB10
CGameObject::~CGameObject()
{
    RemoveFromArea();
}

// 0x45B680
BYTE CGameObject::GetObjectType()
{
    return m_objectType;
}

// 0x4C7BE0
void CGameObject::AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameObject.cpp
    // __LINE__: 175
    UTIL_ASSERT(pNewArea != NULL);

    if (m_posVertList == NULL && m_pArea == NULL) {
        m_pos = pos;
        m_posZ = posZ;
        m_pArea = pNewArea;
        m_listType = listType;
        pNewArea->AddObject(m_id, listType);
    }
}

// 0x78E730
void CGameObject::AIUpdate()
{
}

// 0x44CB60
const CAIObjectType& CGameObject::GetAIType()
{
    return m_typeAI;
}

// 0x44CB70
LONG CGameObject::GetTargetId()
{
    return CGameObjectArray::INVALID_INDEX;
}

// 0x44CB80
void CGameObject::GetNextWaypoint(CPoint* pt)
{
    *pt = m_pos;
}

// 0x44CBA0
POSITION CGameObject::GetVertListPos()
{
    return m_posVertList;
}

// 0x44CBB0
BYTE CGameObject::GetVertListType()
{
    return m_listType;
}

// 0x41E1E0
CPoint& CGameObject::GetPos()
{
    return m_pos;
}

// 0x44CBC0
BOOLEAN CGameObject::CanSaveGame(STRREF& strError)
{
    strError = 16502; // "You cannot save at this time."
    return FALSE;
}

// 0x4C7C50
BOOLEAN CGameObject::CompressTime(DWORD deltaTime)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameObject.cpp
    // __LINE__: 210
    UTIL_ASSERT(deltaTime > (DWORD)CTimerWorld::TIMESCALE_MSEC_PER_SEC * CTimerWorld::TIMESCALE_SEC_PER_MIN);

    RemoveFromArea();

    return FALSE;
}

// 0x778900
void CGameObject::DebugDump(const CString& a1, BOOLEAN a2)
{
}

// 0x799E20
BOOL CGameObject::IsOver(const CPoint& pt)
{
    return FALSE;
}

// 0x44CBD0
BOOL CGameObject::DoesIntersect(CRect r)
{
    return FALSE;
}

// 0x44CBE0
BOOL CGameObject::OnSearchMap()
{
    return m_pArea != NULL && m_pos.x >= 0 && m_pos.y >= 0;
}

// 0x4C7CA0
void CGameObject::OnActionButton(const CPoint& pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    CAIGroup* pGroup = pGame->GetGroup();

    switch (pGame->GetState()) {
    case 0:
        if (pGroup->m_groupChanged || pGame->m_lastClick != pt) {
            pGroup->m_groupChanged = FALSE;
            pGame->m_lastClick = pt;
            pGame->m_lastTarget = CGameObjectArray::INVALID_INDEX;

            if (pGroup->GetCount() != 0) {
                BOOL bShift = g_pBaldurChitin->m_pEngineWorld->GetShiftKey();
                if (!bShift) {
                    pGroup->ClearActions();
                }

                if (pGroup->GetCount() == 1) {
                    pGroup->GroupSetTarget(pt,
                        bShift,
                        CAIGroup::FORMATION_NONE,
                        CPoint(-1, -1));
                } else if (m_pArea->m_groupMove) {
                    CPoint cursor = m_pArea->m_moveDest + m_pArea->m_moveDest - pt;

                    pGroup->GroupDrawMove(m_pArea->m_moveDest,
                        pGame->GetGameSave()->m_curFormation,
                        cursor);

                    pGroup->GroupSetTarget(pt,
                        bShift,
                        pGame->GetGameSave()->m_curFormation,
                        cursor);
                } else {
                    pGroup->GroupSetTarget(pt,
                        bShift,
                        pGame->GetGameSave()->m_curFormation,
                        CPoint(-1, -1));
                }
            }
        }
        break;
    case 2:
        pGame->m_lastClick.x = -1;
        pGame->m_lastClick.y = -1;
        pGame->m_lastTarget = CGameObjectArray::INVALID_INDEX;
        break;
    case 3:
        pGame->m_lastClick.x = -1;
        pGame->m_lastClick.y = -1;
        pGame->m_lastTarget = CGameObjectArray::INVALID_INDEX;

        pGroup->GroupProtectPoint(m_pArea->m_moveDest,
            pGame->GetGameSave()->m_curFormation,
            CPoint(-1, -1),
            FALSE);

        m_pArea->m_groupMove = FALSE;
        pGame->m_nState = 0;
        pGame->GetButtonArray()->m_nSelectedButton = 100;
        pGame->GetButtonArray()->UpdateState();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameObject.cpp
        // __LINE__: 298
        UTIL_ASSERT(FALSE);
    }
}

// 0x4C7EE0
void CGameObject::OnFormationButton(const CPoint& pt)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    switch (pGame->m_nState) {
    case 0:
        if (m_pArea != NULL && m_pArea->m_groupMove) {
            m_pArea->OnActionButtonClickGround(pt);
        }
        break;
    case 1:
    case 2:
        pGame->m_nState = 0;
        pGame->m_cButtonArray.m_nSelectedButton = 100;
        pGame->m_cButtonArray.UpdateState();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameObject.cpp
        // __LINE__ 340
        UTIL_ASSERT(FALSE);
    }
}

// 0x4C7F60
void CGameObject::RemoveFromArea()
{
    if (m_pArea != NULL) {
        if (m_posVertList != NULL) {
            m_pArea->RemoveObject(m_posVertList, m_listType, m_id);
            m_posVertList = NULL;
        }

        m_pArea = NULL;
        m_pos.x = -1;
        m_pos.y = -1;
        m_posZ = 0;
    }
}

// 0x78E750
void CGameObject::Render(CGameArea* pArea, CVidMode* pVidMode, int a3)
{
}

// 0x44CC00
BOOLEAN CGameObject::DoAIUpdate(BOOLEAN active, LONG counter)
{
    return active && (counter & m_AISpeed) == (m_AISpeed & m_id);
}

// 0x44CC30
void CGameObject::SetAIType(const CAIObjectType& type, int a2)
{
    m_typeAI.Set(type);
}

// 0x4C7FB0
void CGameObject::SetCursor(LONG nToolTip)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    switch (pGame->GetState()) {
    case 0:
        if (pGame->GetGroup()->GetCount() != 0) {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(4, FALSE);
        } else {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(0, FALSE);
        }
        break;
    case 1:
        if (pGame->GetIconIndex() != -1) {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(pGame->GetIconIndex(), FALSE);
        } else {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(20, FALSE);
        }
        break;
    case 2:
        if (pGame->GetIconIndex() != -1) {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(pGame->GetIconIndex(), FALSE);
            g_pBaldurChitin->GetObjectCursor()->SetGreyScale(TRUE);
        } else {
            g_pBaldurChitin->GetObjectCursor()->SetCursor(102, FALSE);
            g_pBaldurChitin->GetObjectCursor()->SetCustomCursor(pGame->m_iconResRef, FALSE, -1);
        }
        break;
    case 3:
        g_pBaldurChitin->GetObjectCursor()->SetCursor(16, FALSE);
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameObject.cpp
        // __LINE__: 434
        UTIL_ASSERT(FALSE);
    }
}

// 0x4C83F0
void CGameObject::FloatText(STRREF strRef, int a2, int a3)
{
    // TODO: Incomplete.
}

// 0x78E750
void CGameObject::SetTarget(CPoint pt, BOOL a2)
{
}

// 0x44CC40
void CGameObject::SetVertListPos(POSITION posVertList)
{
    m_posVertList = posVertList;
}

// 0x799E20
BOOL CGameObject::EvaluateStatusTrigger(const CAITrigger& trigger)
{
    return FALSE;
}

// 0x6A3C60
BOOLEAN CGameObject::IsProjectile()
{
    return FALSE;
}

// 0x40CB00
CGameArea* CGameObject::GetArea()
{
    return m_pArea;
}

// 0x4530B0
LONG CGameObject::GetId()
{
    return m_id;
}

// 0x4530C0
BOOLEAN CGameObject::InControl()
{
    if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
        return m_remotePlayerID == g_pChitin->cNetwork.m_idLocalPlayer;
    } else {
        return TRUE;
    }
}

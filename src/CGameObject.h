#ifndef CGAMEOBJECT_H_
#define CGAMEOBJECT_H_

#include "BalDataTypes.h"
#include "CAIObjectType.h"

class CAITrigger;
class CGameArea;
class CVidMode;

class CGameObject {
public:
    static const BYTE TYPE_NONE;
    static const BYTE TYPE_AIBASE;
    static const BYTE TYPE_CONTAINER;
    static const BYTE TYPE_DOOR;
    static const BYTE TYPE_OBJECT_MARKER;
    static const BYTE TYPE_SOUND;
    static const BYTE TYPE_SPAWNING;
    static const BYTE TYPE_SPRITE;
    static const BYTE TYPE_STATIC;
    static const BYTE TYPE_TRIGGER;
    static const BYTE TYPE_TILED_OBJECT;
    static const BYTE TYPE_TEXT;
    static const BYTE LIST_FRONT;
    static const BYTE LIST_BACK;
    static const BYTE LIST_FLIGHT;
    static const BYTE VISIBLE_DELAY;
    static const BYTE CHUNK_DURATION;
    static const BYTE AI_SPEED_NORMAL;
    static const BYTE AI_SPEED_SLOWED;
    static const BYTE AI_SPEED_HASTED;
    static const BYTE DEFAULT_VISIBLE_TERRAIN_TABLE[16];
    static const BYTE DEFAULT_TERRAIN_TABLE[16];

    CGameObject();
    /* 0000 */ virtual ~CGameObject();
    /* 0004 */ virtual BYTE GetObjectType();
    /* 0008 */ virtual void AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType);
    /* 000C */ virtual void AIUpdate();
    /* 0010 */ virtual const CAIObjectType& GetAIType();
    /* 0014 */ virtual LONG GetTargetId();
    /* 0018 */ virtual void GetNextWaypoint(CPoint* pt);
    /* 001C */ virtual CPoint& GetPos();
    /* 0020 */ virtual POSITION GetVertListPos();
    /* 0024 */ virtual BYTE GetVertListType();
    /* 0028 */ virtual BOOLEAN CanSaveGame(STRREF& strError);
    /* 002C */ virtual BOOLEAN CompressTime(DWORD deltaTime);
    /* 0030 */ virtual void DebugDump(const CString& a1, BOOLEAN a2);
    /* 0034 */ virtual BOOL IsOver(const CPoint& pt);
    /* 0038 */ virtual BOOL DoesIntersect(CRect r);
    /* 003C */ virtual BOOL OnSearchMap();
    /* 0040 */ virtual void OnActionButton(const CPoint& pt);
    /* 0044 */ virtual void OnFormationButton(const CPoint& pt);
    /* 0048 */ virtual void RemoveFromArea();
    /* 004C */ virtual void Render(int a1, int a2, int a3);
    /* 0050 */ virtual BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter);
    /* 0054 */ virtual void SetAIType(const CAIObjectType& type, int a2);
    /* 0058 */ virtual void SetCursor(int a1);
    /* 005C */ virtual void SetTarget(CPoint pt, BOOL a2);
    /* 0060 */ virtual void SetVertListPos(POSITION posVertList);
    /* 0064 */ virtual BOOL EvaluateStatusTrigger(const CAITrigger& trigger);
    /* 0068 */ virtual BOOLEAN func_68();

    /* 0004 */ BYTE m_objectType;
    /* 0006 */ CPoint m_pos;
    /* 000E */ LONG m_posZ;
    /* 0012 */ CGameArea* m_pArea;
    /* 0016 */ POSITION m_posVertList;
    /* 001A */ BYTE m_listType;
    /* 001C */ int field_1C;
    /* 0020 */ CAIObjectType m_typeAI;
    /* 005C */ LONG m_id;
    /* 0060 */ short field_60;
    /* 0062 */ DWORD m_remotePlayerID;
    /* 0066 */ int field_66;
    /* 006A */ BYTE m_AISpeed;
    /* 006B */ unsigned char field_6B;
    /* 006C */ unsigned char field_6C;
};

#endif /* CGAMEOBJECT_H_ */

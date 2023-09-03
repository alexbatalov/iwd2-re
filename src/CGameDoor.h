#ifndef CGAMEDOOR_H_
#define CGAMEDOOR_H_

#include "CGameAIBase.h"
#include "CResRef.h"

class CGameDoor : public CGameAIBase {
public:
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;

    void SetDrawPoly(SHORT time);

    /* 05A0 */ CRect m_rOpenBounding;
    /* 05B0 */ CRect m_rClosedBounding;
    /* 05C4 */ DWORD m_dwFlags;
    /* 05C8 */ CPoint* m_pOpenPolygon;
    /* 05CC */ WORD m_nOpenPolygon;
    /* 05CE */ CPoint* m_pClosedPolygon;
    /* 05D2 */ WORD m_nClosedPolygon;
    /* 05F0 */ RESREF m_scriptRes;
    /* 0648 */ WORD m_trapDetectionDifficulty;
    /* 064A */ WORD m_trapDisarmingDifficulty;
    /* 064C */ WORD m_trapActivated;
    /* 064E */ WORD m_trapDetected;
    /* 0650 */ WORD m_posXTrapOrigin;
    /* 0652 */ WORD m_posYTrapOrigin;
    /* 0654 */ CResRef m_keyType;
    /* 0660 */ DWORD m_lockDifficulty;
    /* 0664 */ SHORT m_drawPoly;
};

#endif /* CGAMEDOOR_H_ */

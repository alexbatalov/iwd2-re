#ifndef CGAMEDOOR_H_
#define CGAMEDOOR_H_

#include "CGameAIBase.h"
#include "CResRef.h"
#include "CTiledObject.h"
#include "FileFormat.h"

class CGameDoor : public CGameAIBase {
public:
    static const LONG RANGE_DOOR;

    CGameDoor(CGameArea* pArea, CAreaFileDoorObject* pDoorObject, CAreaPoint* pPoints, WORD maxPts);
    /* 0000 */ ~CGameDoor() override;
    /* 000C */ void AIUpdate() override;
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0058 */ void SetCursor(LONG nToolTip) override;

    void OnDoorStatusUpdate(BOOLEAN bDoorOpened, DWORD dwFlags, WORD nTrapActivated, WORD nTrapDetected);
    void SetDrawPoly(SHORT time);

    /* 0598 */ CResRef m_resID;
    /* 05A0 */ CRect m_rOpenBounding;
    /* 05B0 */ CRect m_rClosedBounding;
    /* 05C0 */ DWORD m_cursorType;
    /* 05C4 */ DWORD m_dwFlags;
    /* 05C8 */ CPoint* m_pOpenPolygon;
    /* 05CC */ WORD m_nOpenPolygon;
    /* 05CE */ CPoint* m_pClosedPolygon;
    /* 05D2 */ WORD m_nClosedPolygon;
    /* 05D4 */ CPoint* m_pOpenSearch;
    /* 05D8 */ WORD m_nOpenSearch;
    /* 05DA */ CPoint* m_pClosedSearch;
    /* 05DE */ WORD m_nClosedSearch;
    /* 05E0 */ CPoint m_ptDest1;
    /* 05E8 */ CPoint m_ptDest2;
    /* 05F0 */ RESREF m_scriptRes;
    /* 05F8 */ CTiledObject m_tiledObject;
    /* 0630 */ STRREF m_strNotPickable;
    /* 0634 */ SHORT m_hitPoints;
    /* 0636 */ SHORT m_armourClass;
    /* 0638 */ CResRef m_openSound;
    /* 0640 */ CResRef m_closeSound;
    /* 0648 */ WORD m_trapDetectionDifficulty;
    /* 064A */ WORD m_trapDisarmingDifficulty;
    /* 064C */ WORD m_trapActivated;
    /* 064E */ WORD m_trapDetected;
    /* 0650 */ WORD m_posXTrapOrigin;
    /* 0652 */ WORD m_posYTrapOrigin;
    /* 0654 */ CResRef m_keyType;
    /* 065C */ DWORD m_detectionDifficulty;
    /* 0660 */ DWORD m_lockDifficulty;
    /* 0664 */ SHORT m_drawPoly;
    /* 0666 */ CPoint m_ptOpenDest;
    /* 066E */ CPoint m_ptClosedDest;
    /* 06DA */ CArray<CRect*> field_6DA;
    /* 06EE */ CAreaPoint* field_6EE;
    /* 06F2 */ CArray<CRect*> field_6F2;
    /* 0706 */ CAreaPoint* field_706;
    /* 070A */ int m_nAICounter;
};

#endif /* CGAMEDOOR_H_ */

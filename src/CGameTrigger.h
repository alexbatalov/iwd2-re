#ifndef CGAMETRIGGER_H_
#define CGAMETRIGGER_H_

#include "CGameAIBase.h"
#include "CResRef.h"
#include "FileFormat.h"

class CGameTrigger : public CGameAIBase {
public:
    static const LONG RANGE_TRIGGER;
    static const LONG RANGE_EDGE;

    CGameTrigger(CGameArea* pArea, CAreaFileTriggerObject* pTriggerObject, CAreaPoint* pPoints, WORD maxPts);
    /* 0000 */ ~CGameTrigger() override;
    /* 000C */ void AIUpdate() override;
    /* 001C */ CPoint& GetPos() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0058 */ void SetCursor(LONG nToolTip) override;
    /* 00B8 */ virtual BOOL IsOverActivate(const CPoint& pt);

    void SetDrawPoly(SHORT time);

    /* 0598 */ WORD m_triggerType;
    /* 059A */ CRect m_rBounding;
    /* 05AA */ DWORD m_cursorType;
    /* 05AE */ RESREF m_newArea;
    /* 05B6 */ SCRIPTNAME m_newEntryPoint;
    /* 05D6 */ DWORD m_dwFlags;
    /* 05DA */ STRREF m_description;
    /* 05DE */ CPoint* m_pPolygon;
    /* 05E2 */ WORD m_nPolygon;
    /* 05E4 */ WORD m_boundingRange;
    /* 05E6 */ RESREF m_scriptRes;
    /* 05EE */ SCRIPTNAME m_scriptName;
    /* 060E */ WORD m_trapDetectionDifficulty;
    /* 0610 */ WORD m_trapDisarmingDifficulty;
    /* 0612 */ WORD m_trapActivated;
    /* 0614 */ WORD m_trapDetected;
    /* 0616 */ CPoint m_posTrapOrigin;
    /* 061E */ CResRef m_keyType;
    /* 0626 */ SHORT m_drawPoly;
    /* 0628 */ CPoint field_628;
    /* 0630 */ CArray<CRect*> field_630;
    /* 0644 */ CAreaPoint* field_644;
};

#endif /* CGAMETRIGGER_H_ */

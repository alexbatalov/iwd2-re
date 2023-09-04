#ifndef CGAMETRIGGER_H_
#define CGAMETRIGGER_H_

#include "CGameAIBase.h"
#include "CResRef.h"

class CGameTrigger : public CGameAIBase {
public:
    /* 0030 */ void DebugDump(const CString& message, BOOLEAN bEchoToScreen) override;
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;
    /* 00B8 */ virtual BOOL IsOverActivate(const CPoint& pt);

    void SetDrawPoly(SHORT time);

    /* 0598 */ WORD m_triggerType;
    /* 059A */ CRect m_rBounding;
    /* 05AE */ RESREF m_newArea;
    /* 05B6 */ SCRIPTNAME m_newEntryPoint;
    /* 05D6 */ DWORD m_dwFlags;
    /* 05DA */ STRREF m_description;
    /* 05DE */ CPoint* m_pPolygon;
    /* 05E2 */ WORD m_nPolygon;
    /* 05E6 */ RESREF m_scriptRes;
    /* 060E */ WORD m_trapDetectionDifficulty;
    /* 0610 */ WORD m_trapDisarmingDifficulty;
    /* 0612 */ WORD m_trapActivated;
    /* 0614 */ WORD m_trapDetected;
    /* 0616 */ CPoint m_posTrapOrigin;
    /* 061E */ CResRef m_keyType;
    /* 0626 */ SHORT m_drawPoly;
};

#endif /* CGAMETRIGGER_H_ */

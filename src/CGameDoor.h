#ifndef CGAMEDOOR_H_
#define CGAMEDOOR_H_

#include "CGameAIBase.h"

class CGameDoor : public CGameAIBase {
public:
    /* 0034 */ BOOL IsOver(const CPoint& pt) override;

    void SetDrawPoly(SHORT time);

    /* 05A0 */ CRect m_rOpenBounding;
    /* 05B0 */ CRect m_rClosedBounding;
    /* 05C4 */ DWORD m_dwFlags;
    /* 05C8 */ CPoint* m_pOpenPolygon;
    /* 05CC */ WORD m_nOpenPolygon;
    /* 05CE */ CPoint* m_pClosedPolygon;
    /* 05D2 */ WORD m_nClosedPolygon;
    /* 0664 */ SHORT m_drawPoly;
};

#endif /* CGAMEDOOR_H_ */

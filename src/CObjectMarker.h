#ifndef COBJECTMARKER_H_
#define COBJECTMARKER_H_

#include "mfc.h"

#include "CGameObject.h"

class CObjectMarker : public CGameObject {
public:
    CObjectMarker();
    /* 0000 */ ~CObjectMarker() override;
    /* 0008 */ void AddToArea(CGameArea* pNewArea, const CPoint& pos, LONG posZ, BYTE listType) override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 004C */ void Render(CGameArea* pArea, CVidMode* pVidMode, int a3) override;

    CList<LONG> m_lstObjectIds;
};

#endif /* COBJECTMARKER_H_ */

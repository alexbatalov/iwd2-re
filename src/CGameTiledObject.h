#ifndef CGAMETILEDOBJECT_H_
#define CGAMETILEDOBJECT_H_

#include "CGameAIBase.h"
#include "CTiledObject.h"
#include "FileFormat.h"

class CGameTiledObject : public CGameAIBase {
public:
    CGameTiledObject(CGameArea* pArea, CAreaFileTiledObject* pTiledObject, CAreaPoint* pPoints, WORD maxPts);
    /* 0000 */ ~CGameTiledObject() override;
    /* 0048 */ void RemoveFromArea() override;

    void ToggleState();

    /* 0598 */ CResRef m_resID;
    /* 05A0 */ DWORD m_dwFlags;
    /* 05A4 */ CPoint* m_pPrimarySearch;
    /* 05A8 */ WORD m_nPrimarySearch;
    /* 05AA */ CPoint* m_pSecondarySearch;
    /* 05AE */ WORD m_nSecondarySearch;
    /* 05B0 */ CTiledObject m_tiledObject;
    /* 05C8 */ RESREF m_scriptRes;
};

#endif /* CGAMETILEDOBJECT_H_ */

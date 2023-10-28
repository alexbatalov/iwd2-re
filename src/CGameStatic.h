#ifndef CGAMESTATIC_H_
#define CGAMESTATIC_H_

#include "CGameObject.h"
#include "CVidCell.h"
#include "FileFormat.h"

class CGameStatic : public CGameObject {
public:
    CGameStatic(CGameArea* pArea, CAreaFileStaticObject* pStaticObject);
    /* 0000 */ ~CGameStatic() override;
    /* 000C */ void AIUpdate() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;
    /* 004C */ void Render(CGameArea* pArea, CVidMode* pVidMode, INT nSurface) override;
    /* 0050 */ BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter) override;

    void Marshal(CAreaFileStaticObject** pStaticObject);

    /* 006E */ CAreaFileStaticObject m_header;
    /* 00BC */ CVidCell m_vidCell;
};

#endif /* CGAMESTATIC_H_ */

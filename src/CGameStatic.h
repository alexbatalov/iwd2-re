#ifndef CGAMESTATIC_H_
#define CGAMESTATIC_H_

#include "FileFormat.h"
#include "CGameObject.h"
#include "CVidCell.h"

class CGameStatic : public CGameObject {
public:
    CGameStatic(CGameArea* pArea, CAreaFileStaticObject* pStaticObject);
    /* 0000 */ ~CGameStatic() override;
    /* 000C */ void AIUpdate() override;
    /* 0048 */ void RemoveFromArea() override;
    /* 0050 */ virtual BOOLEAN DoAIUpdate(BOOLEAN active, LONG counter);

    void Marshal(CAreaFileStaticObject** pStaticObject);

    /* 006E */ CAreaFileStaticObject m_header;
    /* 00BC */ CVidCell m_vidCell;
};

#endif /* CGAMESTATIC_H_ */

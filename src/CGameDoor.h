#ifndef CGAMEDOOR_H_
#define CGAMEDOOR_H_

#include "CGameAIBase.h"

class CGameDoor : public CGameAIBase {
public:
    void SetDrawPoly(SHORT time);

    /* 0664 */ SHORT m_drawPoly;
};

#endif /* CGAMEDOOR_H_ */

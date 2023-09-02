#ifndef CGAMETRIGGER_H_
#define CGAMETRIGGER_H_

#include "CGameAIBase.h"

class CGameTrigger : public CGameAIBase {
public:
    void SetDrawPoly(SHORT time);

    /* 0626 */ SHORT m_drawPoly;
};

#endif /* CGAMETRIGGER_H_ */

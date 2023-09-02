#ifndef CGAMECONTAINER_H_
#define CGAMECONTAINER_H_

#include "CGameAIBase.h"

class CGameContainer : public CGameAIBase {
public:
    void SetTrapDetected(WORD state);
    void SetDrawPoly(SHORT time);

    /* 0898 */ WORD m_trapDetected;
    /* 08D0 */ SHORT m_drawPoly;
};

#endif /* CGAMECONTAINER_H_ */

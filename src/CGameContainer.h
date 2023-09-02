#ifndef CGAMECONTAINER_H_
#define CGAMECONTAINER_H_

#include "CGameAIBase.h"

class CGameContainer : public CGameAIBase {
public:
    void SetTrapActivated(WORD active);
    void SetTrapDetected(WORD state);
    void SetDrawPoly(SHORT time);

    /* 0896 */ WORD m_trapActivated;
    /* 0898 */ WORD m_trapDetected;
    /* 08D0 */ SHORT m_drawPoly;
};

#endif /* CGAMECONTAINER_H_ */

#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

class CScreenWorld : public CBaldurEngine {
public:
    CScreenWorld();
    ~CScreenWorld();
    void ClearChatMessages();

    /* 10DE */ int field_10DE;
};

#endif /* CSCREENWORLD_H_ */

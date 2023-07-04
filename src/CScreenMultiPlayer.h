#ifndef CSCREENMULTIPLAYER_H_
#define CSCREENMULTIPLAYER_H_

#include "CBaldurEngine.h"

class CScreenMultiPlayer : public CBaldurEngine {
public:
    CScreenMultiPlayer();
    ~CScreenMultiPlayer();
    void ClearChatMessages();

    void StartMultiPlayer(INT nEngineState);

    /* 045C */ int field_45C;
};

#endif /* CSCREENMULTIPLAYER_H_ */

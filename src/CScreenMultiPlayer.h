#ifndef CSCREENMULTIPLAYER_H_
#define CSCREENMULTIPLAYER_H_

#include "CBaldurEngine.h"

class CScreenMultiPlayer : public CBaldurEngine {
public:
    CScreenMultiPlayer();
    ~CScreenMultiPlayer();
    void ClearChatMessages();
};

#endif /* CSCREENMULTIPLAYER_H_ */

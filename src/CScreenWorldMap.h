#ifndef CSCREENWORLDMAP_H_
#define CSCREENWORLDMAP_H_

#include "CBaldurEngine.h"

class CScreenWorldMap : public CBaldurEngine {
public:
    CScreenWorldMap();
    ~CScreenWorldMap();
    void ClearChatMessages();

    /* 104A */ int field_104A;
};

#endif /* CSCREENWORLDMAP_H_ */

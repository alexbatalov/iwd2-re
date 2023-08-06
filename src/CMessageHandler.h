#ifndef CMESSAGEHANDLER_H_
#define CMESSAGEHANDLER_H_

#include "mfc.h"

class CMessageHandler {
public:
    CMessageHandler();
    ~CMessageHandler();
    void AsynchronousUpdate();
    void PostAsynchronousUpdate();

    /* 001C */ BOOLEAN m_bLastArbitrationLockStatus;
};

#endif /* CMESSAGEHANDLER_H_ */

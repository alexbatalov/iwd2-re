#ifndef CMESSAGEHANDLER_H_
#define CMESSAGEHANDLER_H_

class CMessageHandler {
public:
    CMessageHandler();
    ~CMessageHandler();
    void AsynchronousUpdate();
    void PostAsynchronousUpdate();
};

#endif /* CMESSAGEHANDLER_H_ */

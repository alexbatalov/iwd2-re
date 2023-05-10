#ifndef CSCREENSAVE_H_
#define CSCREENSAVE_H_

#include "CBaldurEngine.h"

class CScreenSave : public CBaldurEngine {
public:
    CScreenSave();
    ~CScreenSave();

    void StartSave(INT nEngineState);
};

#endif /* CSCREENSAVE_H_ */

#ifndef CSCREENLOAD_H_
#define CSCREENLOAD_H_

#include "CBaldurEngine.h"

class CScreenLoad : public CBaldurEngine {
public:
    CScreenLoad();
    ~CScreenLoad();

    void StartLoad(INT nEngineState);
};

#endif /* CSCREENLOAD_H_ */

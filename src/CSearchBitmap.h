#ifndef CSEARCHBITMAP_H_
#define CSEARCHBITMAP_H_

#include "mfc.h"

class CSearchBitmap {
public:
};

class CSearchRequest {
public:
    static LONG MINNODES;
    static LONG MAXNODES;
    static LONG MINNODESBACK;
    static LONG MAXNODESBACK;
};

void SearchThreadMain(void* userInfo);

#endif /* CSEARCHBITMAP_H_ */

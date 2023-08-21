#ifndef CSEARCHBITMAP_H_
#define CSEARCHBITMAP_H_

#include "mfc.h"

class CSearchBitmap {
public:
};

class CSearchRequest {
public:
    static const BYTE STATE_WAITING;
    static const BYTE STATE_PROCESSING;
    static const BYTE STATE_NO_TARGET;
    static const BYTE STATE_DONE;
    static const BYTE STATE_STALE;
    static const BYTE STATE_ERROR;

    static LONG MINNODES;
    static LONG MAXNODES;
    static LONG MINNODESBACK;
    static LONG MAXNODESBACK;

    /* 0000 */ BYTE m_serviceState;
    /* 0001 */ BYTE m_collisionDelay;
};

void SearchThreadMain(void* userInfo);

#endif /* CSEARCHBITMAP_H_ */

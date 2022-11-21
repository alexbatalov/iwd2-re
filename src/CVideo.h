#ifndef CVIDEO_H_
#define CVIDEO_H_

#include <windows.h>

#include "CVidBlitter.h"

class CVideo {
public:
    CVideo();
    ~CVideo();

    /* 0008 */ CVidBlitter cVidBlitter; // #guess
    /* 0132 */ BOOL m_bIs3dAccelerated;
};

#endif /* CVIDEO_H_ */

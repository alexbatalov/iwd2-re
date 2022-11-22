#ifndef CWARP_H_
#define CWARP_H_

#include <afx.h>

#include "CChitin.h"
#include "CDimm.h"
#include "CSoundMixer.h"
#include "CVidMode.h"
#include "CVideo.h"

class CWarp : public CObject {
public:
    static CSoundMixer* pSoundMixer;
    static CDimm* pDimm;
    static CVideo* pVideo;
    static CChitin* pChitin;

    CWarp();
    ~CWarp();

    /* 0004 */ CVidMode* pVidMode; // #guess
    /* 0008 */ CWarp* pLastEngine;
    /* 000C */ CObList lTimers;
};

#endif /* CWARP_H_ */

#ifndef CCACHESTATUS_H_
#define CCACHESTATUS_H_

#include "mfc.h"

#include "CVidCell.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

class CCacheStatus {
public:
    CCacheStatus();
    ~CCacheStatus();

    void Init();
    void InvalidateScreen();
    void Update(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout);

    /* 0004 */ INT m_nScreensDrawn;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 0020 */ CVidMosaic field_20[4];
    /* 02F0 */ CVidMosaic field_2F0;
    /* 03A4 */ CVidMosaic field_3A4;
    /* 0458 */ CVidFont field_458;
    /* 0958 */ CVidFont field_958;
    /* 0E58 */ CVidFont field_E58;
    /* 1358 */ CVidMosaic field_1358;
    /* 140C */ CVidMosaic field_140C;
    /* 14C0 */ CVidMosaic field_14C0;
    /* 1574 */ CVidCell field_1574;
    /* 164E */ CVidMosaic field_164E;
    /* 1702 */ CVidMosaic field_1702;
    /* 17B6 */ CVidMosaic field_17B6;
    /* 186A */ CVidMosaic field_186A;
    /* 191E */ CVidMosaic field_191E;
    /* 19D2 */ CVidMosaic field_19D2;
    /* 1A86 */ CVidMosaic field_1A86;
    /* 1B3A */ CVidMosaic field_1B3A;
    /* 1BEE */ CCriticalSection field_1BEE;
    /* 1C16 */ BOOL m_bActivateEngine;
    /* 1C1A */ int field_1C1A;
};

#endif /* CCACHESTATUS_H_ */

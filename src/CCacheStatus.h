#ifndef CCACHESTATUS_H_
#define CCACHESTATUS_H_

#include "mfc.h"

#include "CVidCell.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

class CCacheStatus {
public:
    static int dword_8A7BA8;
    static int dword_8A7BAC;
    static int dword_8A7BB0;
    static int dword_8A7BB4;
    static int dword_8A7BB8;
    static int dword_8A7BBC;
    static int dword_8A7BC0;
    static int dword_8A7BC4;
    static int dword_8A7BC8;
    static int dword_8A7BCC;
    static int dword_8A7BD0;
    static int dword_8A7BD4;
    static int dword_8A7BD8;
    static int dword_8A7BDC;
    static int dword_8A7BE0;
    static int dword_8A7BE4;
    static int dword_8A7BE8;
    static int dword_8A7BEC;
    static int dword_8A7BF0;
    static int dword_8A7BF4;
    static int dword_8A7BF8;
    static int dword_8A7BFC;
    static int dword_8A7C00;
    static int dword_8A7C04;
    static int dword_8A7C08;
    static int dword_8A7C0C;
    static int dword_8A7C10;
    static int dword_8A7C14;
    static int dword_8A7C18;
    static int dword_8A7C1C;
    static int dword_8A7C20;
    static int dword_8A7C24;
    static int dword_8A7C28;
    static int dword_8A7C2C;
    static int dword_8A7C30;
    static int dword_8A7C34;
    static int dword_8A7C38;
    static int dword_8A7C3C;
    static int dword_8D0770;
    static int dword_8D0B7C;
    static int dword_8D0B80;
    static int dword_8D0B8C;
    static int dword_8D0B90;
    static int dword_8D0BA0;
    static int dword_8D0BA4;
    static BOOL dword_8D0BA8;

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

#ifndef CPROGRESSBAR_H_
#define CPROGRESSBAR_H_

#include <windows.h>

class CProgressBar {
public:
    // NOTE: The `Initialize` function is called in implicit part of `CChitin`
    // constructor, but the constructor itself is inlined.
    CProgressBar()
    {
        Initialize();
    }

    void Initialize();

    /* 0000 */ int m_nSecondsToTimeout;
    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ unsigned char field_14;
    /* 0015 */ unsigned char field_15;
    /* 0016 */ int field_16;
    /* 001A */ unsigned char field_1A;
    /* 001B */ unsigned char field_1B;
    /* 001C */ unsigned char field_1C;
    /* 001D */ BOOLEAN m_bRemoteWaiting[6];
    /* 0024 */ int m_nRemoteActionProgress[6];
    /* 003C */ int m_nRemoteActionTarget[6];
    /* 0054 */ int m_nRemoteWaitingReason[6];
};

#endif /* CPROGRESSBAR_H_ */

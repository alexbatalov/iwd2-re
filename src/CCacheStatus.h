#ifndef CCACHESTATUS_H_
#define CCACHESTATUS_H_

#include "mfc.h"

#include "CVidCell.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

class CCacheStatus {
public:
    static int PARCHMENT_TEXT_START_X;
    static int PARCHMENT_TEXT_START_Y;
    static int dword_8A7BB0;
    static int dword_8A7BB4;
    static int TRAVEL_AREA_START_X;
    static int TRAVEL_AREA_START_Y;
    static int UPDATE_TEXT_X;
    static int UPDATE_TEXT_Y;
    static int PROGRESSBAR_BACKGROUND_START_X;
    static int PROGRESSBAR_BACKGROUND_START_Y;
    static int PROGRESSBAR_BACKGROUND_SIZE_X;
    static int PROGRESSBAR_FOREGROUND_X_OFFSET;
    static int PROGRESSBAR_FOREGROUND_SIZE_Y;
    static int PROGRESSBAR_FOREGROUND_CAP_OFFSET;
    static int MINIBAR_FOREGROUND_CAP_OFFSET;
    static int dword_8A7BE4;
    static int dword_8A7BE8;
    static int MINIBAR_X_FIRST;
    static int MINIBAR_X_INC;
    static int MINIBAR_Y_FIRST;
    static int MINIBAR_Y_INC;
    static int MINIBAR_NAME_START_X;
    static int MINIBAR_NAME_SIZE_X;
    static int MINIBAR_NAME_START_Y;
    static int MINIBAR_BACKGROUND_START_Y;
    static int MINIBAR_FOREGROUND_START_X;
    static int MINIBAR_FOREGROUND_START_Y;
    static int dword_8A7C14;
    static int MINIBAR_FOREGROUND_FORCE_DISPLAY_SIZE_X;
    static int dword_8A7C1C;
    static int MINIBAR_SKULL_START_X;
    static int MINIBAR_SKULL_START_Y;
    static int dword_8A7C28;
    static int PROGRESSBAR_TIMEOUT_CENTER_X;
    static int PROGRESSBAR_TIMEOUT_START1_Y;
    static int PROGRESSBAR_TIMEOUT_START2_Y;
    static int PROGRESSBAR_TIMEOUT_START3_Y;
    static int PROGRESSBAR_MAXHINTWIDTH;
    static int dword_8D0770;
    static int dword_8D0B7C;
    static int PROGRESSBAR_FOREGROUND_START_X;
    static int PROGRESSBAR_FOREGROUND_START_Y;
    static int PROGRESSBAR_SKULL_START_X;
    static int PROGRESSBAR_SKULL_START_Y;
    static int MINIBAR_BACKGROUND_START_X;
    static BOOL dword_8D0BA8;

    CCacheStatus();
    ~CCacheStatus();

    void Init();
    void InvalidateScreen();
    void Update(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout);

    /* 0004 */ INT m_nScreensDrawn;
    /* 0008 */ BOOL m_bDemandedResources;
    /* 000C */ BOOL m_bTravelScreen;
    /* 0010 */ LONG m_nProgressBarCaption;
    /* 0014 */ LONG m_nParchmentCaption;
    /* 0018 */ DWORD m_dwLastUpdateTickCount;
    /* 001C */ INT m_nCurrentHint;
    /* 0020 */ CVidMosaic m_mosBorders[4];
    /* 02F0 */ CVidMosaic m_mosBackground;
    /* 03A4 */ CVidMosaic m_mosTravelArea;
    /* 0458 */ CVidFont m_vidFont;
    /* 0958 */ CVidFont m_initialsFont;
    /* 0E58 */ CVidFont m_parchmentFont;
    /* 1358 */ CVidMosaic field_1358;
    /* 140C */ CVidMosaic m_mosProgressBarSkull;
    /* 14C0 */ CVidMosaic m_mosProgressBarSkullHighlighted;
    /* 1574 */ CVidCell m_skullAnimating;
    /* 164E */ CVidMosaic m_mosProgressBarBackground;
    /* 1702 */ CVidMosaic m_mosProgressBarForeground;
    /* 17B6 */ CVidMosaic m_mosProgressBarCap;
    /* 186A */ CVidMosaic m_mosMinibarSkull;
    /* 191E */ CVidMosaic m_mosMinibarSkullHighlighted;
    /* 19D2 */ CVidMosaic m_mosMinibarBackground;
    /* 1A86 */ CVidMosaic m_mosMinibarForeground;
    /* 1B3A */ CVidMosaic m_mosMinibarForegroundCap;
    /* 1BEE */ CCriticalSection m_critSect;
    /* 1C16 */ BOOL m_bActivateEngine;
    /* 1C1A */ BOOL m_bWaiting;
};

#endif /* CCACHESTATUS_H_ */

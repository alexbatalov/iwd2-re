#ifndef CPROGRESSBAR_H_
#define CPROGRESSBAR_H_

#include "mfc.h"

#define CPROGRESSBAR_MAX_PLAYERS 6

class CProgressBar {
public:
    // NOTE: The `Initialize` function is called in implicit part of `CChitin`
    // constructor, but the constructor itself is inlined.
    CProgressBar()
    {
        Initialize();
    }

    void Initialize();
    void AddActionTarget(LONG nUnits);
    LONG GetRemoteActionProgres(SHORT nPlayerNum);
    void SetRemoteActionProgress(SHORT nPlayerNum, LONG nUnits);
    LONG GetRemoteActionTarget(SHORT nPlayerNum);
    void SetRemoteActionTarget(SHORT nPlayerNum, LONG nUnits);
    BOOLEAN GetRemoteWaiting(SHORT nPlayerNum);
    void SetRemoteWaiting(SHORT nPlayerNum, BOOLEAN bValue);
    LONG GetRemoteWaitingReason(SHORT nPlayerNum);
    void SetRemoteWaitingReason(SHORT nPlayerNum, LONG nReason);

    /* 0000 */ DWORD m_nSecondsToTimeout;
    /* 0004 */ LONG m_nProgressBarCaption;
    /* 0008 */ LONG m_nParchmentCaption;
    /* 000C */ LONG m_nActionProgress;
    /* 0010 */ LONG m_nActionTarget;
    /* 0014 */ BOOLEAN m_bTravelActive;
    /* 0015 */ BOOLEAN m_bWaiting;
    /* 0016 */ LONG m_nWaitingReason;
    /* 001A */ BOOLEAN m_bDisableMinibars;
    /* 001B */ BOOLEAN m_bTimeoutVisible;
    /* 001C */ BOOLEAN m_bProgressBarActivated;
    /* 001D */ BOOLEAN m_bRemoteWaiting[CPROGRESSBAR_MAX_PLAYERS];
    /* 0024 */ LONG m_nRemoteActionProgress[CPROGRESSBAR_MAX_PLAYERS];
    /* 003C */ LONG m_nRemoteActionTarget[CPROGRESSBAR_MAX_PLAYERS];
    /* 0054 */ LONG m_nRemoteWaitingReason[CPROGRESSBAR_MAX_PLAYERS];
};

#endif /* CPROGRESSBAR_H_ */

#ifndef CTIMERWORLD_H_
#define CTIMERWORLD_H_

#include "mfc.h"

#include "BalDataTypes.h"

class CTimerWorld {
public:
    static const CString TOKEN_MINUTE;
    static const CString TOKEN_HOUR;
    static const CString TOKEN_DAY;
    static const CString TOKEN_MONTH;
    static const CString TOKEN_YEAR;
    static const CString TOKEN_MONTHNAME;
    static const CString TOKEN_DAYANDMONTH;
    static const CString TOKEN_GAMEDAY;
    static const CString TOKEN_GAMEDAYS;
    static const CString TOKEN_DURATION;
    static const CString TOKEN_DURATIONNOAND;
    static const BYTE TIMESCALE_MSEC_PER_SEC;
    static const BYTE TIMESCALE_SEC_PER_MIN;
    static const BYTE TIMESCALE_MIN_PER_HOUR;
    static const BYTE TIMESCALE_HOUR_PER_DAY;
    static const UINT TIMESCALE_MSEC_PER_DAY;
    static const UINT TIMESCALE_MSEC_PER_HOUR;
    static const BYTE TIME_DAWN_HOUR;
    static const UINT TIME_DAWN;
    static const BYTE TIME_DAY_HOUR;
    static const UINT TIME_DAY;
    static const BYTE TIME_DUSK_HOUR;
    static const UINT TIME_DUSK;
    static const BYTE TIME_NIGHT_HOUR;
    static const UINT TIME_NIGHT;
    static const UINT TIME_APPROACHING_DELTA;
    static const UINT TIME_APPROACHING_DAWN;
    static const UINT TIME_APPROACHING_DUSK;
    static const BYTE PERCENTAGE_RESET;
    static const BYTE MULTIPLAYER_TIME_SYNCH_DELTA;
    static const UINT MULTIPLAYER_TIME_SYNCH_INTERVAL;

    CTimerWorld();
    void AdvanceCurrentTime(ULONG gameTime);
    void AddCurrentTime(ULONG gameTime);
    void UpdateTime(BOOLEAN forceUpdate);
    void CheckForTriggerEventAbsolute();
    void CheckForTriggerEventPast();
    static void GetCurrentTimeString(ULONG nFromTime, STRREF strTimeFormat, CString& sTime);
    void StartTime();
    void StopTime();

    BOOLEAN IsDay();
    BOOLEAN IsNight();
    BOOLEAN IsDawn();
    BOOLEAN IsDusk();
    BYTE GetCurrentHour();

    ULONG GetCurrentDayTime();

    static BOOLEAN IsDay(ULONG nTimeOfDay);
    static BOOLEAN IsNight(ULONG nTimeOfDay);
    static BOOLEAN IsDawn(ULONG nTimeOfDay);
    static BOOLEAN IsDusk(ULONG nTimeOfDay);

    ULONG m_gameTime;
    BOOLEAN m_active;
    BYTE m_nLastPercentage;
};

#endif /* CTIMERWORLD_H_ */

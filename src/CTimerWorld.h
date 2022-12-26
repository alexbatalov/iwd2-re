#ifndef CTIMERWORLD_H_
#define CTIMERWORLD_H_

#include "mfc.h"

class CTimerWorld {
public:
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

    ULONG m_gameTime;
    BOOLEAN m_active;
    BYTE m_nLastPercentage;
};

#endif /* CTIMERWORLD_H_ */

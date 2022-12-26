#include "CTimerWorld.h"

// 0x84EC0C
const BYTE CTimerWorld::TIMESCALE_MSEC_PER_SEC = 15;

// 0x84EC0D
const BYTE CTimerWorld::TIMESCALE_SEC_PER_MIN = 60;

// 0x84EC0E
const BYTE CTimerWorld::TIMESCALE_MIN_PER_HOUR = 5;

// 0x84EC0F
const BYTE CTimerWorld::TIMESCALE_HOUR_PER_DAY = 24;

// 0x84EC10
const UINT CTimerWorld::TIMESCALE_MSEC_PER_DAY = 108000;

// 0x84EC14
const UINT CTimerWorld::TIMESCALE_MSEC_PER_HOUR = 4500;

// 0x84EC18
const BYTE CTimerWorld::TIME_DAWN_HOUR = 6;

// 0x84EC1C
const UINT CTimerWorld::TIME_DAWN = 27000;

// 0x84EC20
const BYTE CTimerWorld::TIME_DAY_HOUR = 7;

// 0x84EC24
const UINT CTimerWorld::TIME_DAY = 31500;

// 0x84EC28
const BYTE CTimerWorld::TIME_DUSK_HOUR = 21;

// 0x84EC2C
const UINT CTimerWorld::TIME_DUSK = 94500;

// 0x84EC30
const BYTE CTimerWorld::TIME_NIGHT_HOUR = 22;

// 0x84EC34
const UINT CTimerWorld::TIME_NIGHT = 99000;

// 0x84EC38
const UINT CTimerWorld::TIME_APPROACHING_DELTA = 450;

// 0x84EC3C
const UINT CTimerWorld::TIME_APPROACHING_DAWN = 26550;

// 0x84EC40
const UINT CTimerWorld::TIME_APPROACHING_DUSK = 94050;

// 0x84EC44
const BYTE CTimerWorld::PERCENTAGE_RESET = 255;

// 0x84EC45
const BYTE CTimerWorld::MULTIPLAYER_TIME_SYNCH_DELTA = 5;

// 0x84EC48
const UINT CTimerWorld::MULTIPLAYER_TIME_SYNCH_INTERVAL = 450;

// 0x54EDD0
CTimerWorld::CTimerWorld()
{
    m_active = FALSE;
    m_gameTime = 0;
    m_nLastPercentage = 0;
}

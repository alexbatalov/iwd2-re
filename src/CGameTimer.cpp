#include "CGameTimer.h"

// NOTE: Inlined.
LONG CGameTimer::GetTime()
{
    return m_time;
}

// 0x45B680
BYTE CGameTimer::GetId()
{
    return m_id;
}

// NOTE: Inlined.
void CGameTimer::SetTime(LONG time)
{
    m_time = time;
}

// NOTE: Inlined.
void CGameTimer::SetId(BYTE id)
{
    m_id = id;
}

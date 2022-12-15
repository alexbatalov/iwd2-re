#include "CCacheStatus.h"

// 0x4400D0
CCacheStatus::CCacheStatus()
{
    m_nScreensDrawn = 0;
    field_8 = 0;
    field_C = 0;
    field_10 = 0;
    field_14 = 0;
    field_18 = 0;
    field_1C16 = 0;
    field_1C1A = 0;
}

// 0x440270
CCacheStatus::~CCacheStatus()
{
}

// 0x440400
void CCacheStatus::Init()
{
    // TODO: Incomplete.
}

// 0x4406A0
void CCacheStatus::InvalidateScreen()
{
    m_nScreensDrawn = 0;
}

// 0x4406B0
void CCacheStatus::Update(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
    // TODO: Incomplete.
}

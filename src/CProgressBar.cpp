#include "CProgressBar.h"

#include "CUtil.h"

// #binary-identical
// 0x78BB60
void CProgressBar::Initialize()
{
    m_nProgressBarCaption = 0;
    m_nParchmentCaption = 0;
    m_bWaiting = FALSE;
    m_nWaitingReason = 0;
    m_nActionTarget = 0;
    m_bProgressBarActivated = FALSE;
    m_bTravelActive = FALSE;
    m_nActionProgress = 0;
    m_bDisableMinibars = FALSE;
    m_bTimeoutVisible = FALSE;
    m_nSecondsToTimeout = 255;

    for (int k = 0; k < CPROGRESSBAR_MAX_PLAYERS; k++) {
        m_nRemoteActionProgress[k] = 0;
        m_nRemoteActionTarget[k] = 0;
        m_bRemoteWaiting[k] = 0;
        m_nRemoteWaitingReason[k] = 0;
    }
}

// 0x78BBB0
void CProgressBar::AddActionTarget(LONG nUnits)
{
    ULONG oldActionTarget = m_nActionTarget;
    ULONG oldActionProgress = m_nActionProgress;

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10379
    UTIL_ASSERT(oldActionTarget > 0);

    // NOTE: Unsigned math.
    if (oldActionProgress < oldActionTarget && oldActionProgress < oldActionTarget + nUnits) {
        float v1 = static_cast<float>(oldActionTarget) - static_cast<float>(oldActionProgress);
        float v2 = (static_cast<float>(nUnits) + v1) / v1;
        m_nActionTarget = static_cast<LONG>(static_cast<float>(oldActionTarget) * v2);
        m_nActionProgress = static_cast<LONG>(static_cast<float>(oldActionProgress) * v2);
    } else {
        m_nActionTarget = oldActionTarget + nUnits;
        m_nActionProgress = oldActionTarget + nUnits;
    }

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10395
    UTIL_ASSERT(m_nActionTarget > 0);
}

// 0x78BC90
LONG CProgressBar::GetRemoteActionProgres(SHORT nPlayerNum)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10417
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    return m_nRemoteActionProgress[nPlayerNum];
}

// 0x78BCE0
void CProgressBar::SetRemoteActionProgress(SHORT nPlayerNum, LONG nUnits)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10439
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    m_nRemoteActionProgress[nPlayerNum] = nUnits;
}

// 0x78BD30
LONG CProgressBar::GetRemoteActionTarget(SHORT nPlayerNum)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10461
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    return m_nRemoteActionTarget[nPlayerNum];
}

// 0x78BD80
void CProgressBar::SetRemoteActionTarget(SHORT nPlayerNum, LONG nUnits)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10483
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    m_nRemoteActionTarget[nPlayerNum] = nUnits;
}

// 0x78BDD0
BOOLEAN CProgressBar::GetRemoteWaiting(SHORT nPlayerNum)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10505
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    return m_bRemoteWaiting[nPlayerNum];
}

// 0x78BE20
void CProgressBar::SetRemoteWaiting(SHORT nPlayerNum, BOOLEAN bValue)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10527
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    m_bRemoteWaiting[nPlayerNum] = bValue;
}

// 0x78BE70
LONG CProgressBar::GetRemoteWaitingReason(SHORT nPlayerNum)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10549
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    return m_nRemoteWaitingReason[nPlayerNum];
}

// 0x78BEC0
void CProgressBar::SetRemoteWaitingReason(SHORT nPlayerNum, LONG nReason)
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChDimm.cpp
    // __LINE__: 10571
    UTIL_ASSERT(nPlayerNum >= 0 && nPlayerNum < CPROGRESSBAR_MAX_PLAYERS);

    m_nRemoteWaitingReason[nPlayerNum] = nReason;
}

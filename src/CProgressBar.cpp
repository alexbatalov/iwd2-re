#include "CProgressBar.h"

// #binary-identical
// 0x78BB60
void CProgressBar::Initialize()
{
    field_4 = 0;
    field_8 = 0;
    field_15 = 0;
    field_16 = 0;
    field_10 = 0;
    field_1C = 0;
    field_14 = 0;
    field_C = 0;
    field_1A = 0;
    field_1B = 0;
    m_nSecondsToTimeout = 255;

    for (int k = 0; k < 6; k++) {
        m_nRemoteActionProgress[k] = 0;
        m_nRemoteActionTarget[k] = 0;
        m_bRemoteWaiting[k] = 0;
        m_nRemoteWaitingReason[k] = 0;
    }
}

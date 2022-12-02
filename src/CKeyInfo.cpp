#include "CKeyInfo.h"

#include "CChitin.h"

// 0x7B5600
CKeyInfo::CKeyInfo(BYTE keyCode, BYTE repeatDelay, BYTE repeatRate)
{
    m_keyCode = keyCode;

    // NOTE: Looks like inlined `SetRepeat`.
    m_repeatDelay = repeatDelay != 0 ? repeatDelay : g_pChitin->m_nKeyboardDelay;
    m_repeatRate = repeatRate != 0 ? repeatRate : g_pChitin->m_nKeyboardSpeed;
    m_repeatCount = 0;
}

// 0x7B5640
void CKeyInfo::SetRepeat(BYTE repeatDelay, BYTE repeatRate)
{
    m_repeatDelay = repeatDelay != 0 ? repeatDelay : g_pChitin->m_nKeyboardDelay;
    m_repeatRate = repeatRate != 0 ? repeatRate : g_pChitin->m_nKeyboardSpeed;
    m_repeatCount = 0;
}

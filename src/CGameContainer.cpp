#include "CGameContainer.h"

#include "CBaldurChitin.h"

// 0x481760
void CGameContainer::SetTrapActivated(WORD active)
{
    m_trapActivated = active;
}

// 0x481770
void CGameContainer::SetTrapDetected(WORD state)
{
    m_trapDetected = state;
}

// 0x481780
void CGameContainer::SetDrawPoly(SHORT time)
{
    if (m_drawPoly != time) {
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly) {
            CMessageSetDrawPoly* pMessage = new CMessageSetDrawPoly(time, GetId(), GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
    m_drawPoly = time;
}

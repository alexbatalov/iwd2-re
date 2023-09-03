#include "CGameDoor.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CVidPoly.h"

// 0x487C10
BOOL CGameDoor::IsOver(const CPoint& pt)
{
    if ((m_dwFlags & 0x2000) != 0) {
        return FALSE;
    }

    if ((m_dwFlags & 0x1) != 0) {
        if (!m_rOpenBounding.PtInRect(pt)) {
            return FALSE;
        }

        if (!g_pBaldurChitin->GetObjectGame()->GetGroup()->IsPartyLeader()) {
            return FALSE;
        }

        if (m_pOpenPolygon != NULL) {
            return CVidPoly::IsPtInPoly(m_pOpenPolygon, m_nOpenPolygon, pt);
        }
    } else {
        if (!m_rClosedBounding.PtInRect(pt)) {
            return FALSE;
        }

        if (!g_pBaldurChitin->GetObjectGame()->GetGroup()->IsPartyLeader()) {
            return FALSE;
        }

        if (m_pClosedPolygon != NULL) {
            return CVidPoly::IsPtInPoly(m_pClosedPolygon, m_nClosedPolygon, pt);
        }
    }

    return TRUE;
}

// 0x48B350
void CGameDoor::SetDrawPoly(SHORT time)
{
    if (m_drawPoly != time) {
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly) {
            CMessageSetDrawPoly* pMessage = new CMessageSetDrawPoly(time, GetId(), GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
    m_drawPoly = time;
}

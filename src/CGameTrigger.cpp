#include "CGameTrigger.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CVidPoly.h"

// 0x4CE1C0
void CGameTrigger::DebugDump(const CString& message, BOOLEAN bEchoToScreen)
{
    STR_RES strRes;
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    CString sTemp;

    switch (m_triggerType) {
    case 0:
        if (bEchoToScreen) {
            pWorld->DisplayText(CString(""),
                CString("DEBUG DUMP: CGameTrigger - Proximity"),
                -1,
                FALSE);

            pWorld->DisplayText(CString(""),
                message,
                -1,
                FALSE);

            sTemp.Format("Current Area: %.*s", RESREF_SIZE, m_pArea->m_resRef.GetResRef());
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Current Position: x=%d y=%d", m_pos.x, m_pos.y);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Key Type: %.*s", RESREF_SIZE, m_keyType.GetResRef());
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trapped: %s", m_trapActivated != 0 ? "TRUE" : "FALSE");
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trap Detected: %s", m_trapDetected != 0 ? "TRUE" : "FALSE");
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Reset Trap: %s", (m_dwFlags & 0x2) != 0 ? "TRUE" : "FALSE");
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trap Detection Difficulty: %d%%", m_trapDetectionDifficulty);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trap Removal Difficulty: %d%%", m_trapDisarmingDifficulty);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trap Script: %.*s", RESREF_SIZE, m_scriptRes);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Trap Launching Point: x=%d y=%d", m_posTrapOrigin.x, m_posTrapOrigin.y);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);
        }
        break;
    case 1:
        if (bEchoToScreen) {
            pWorld->DisplayText(CString(""),
                CString("DEBUG DUMP: CGameTrigger - Info"),
                -1,
                FALSE);

            pWorld->DisplayText(CString(""),
                message,
                -1,
                FALSE);

            sTemp.Format("Current Area: %.*s", RESREF_SIZE, m_pArea->m_resRef.GetResRef());
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Current Position: x=%d y=%d", m_pos.x, m_pos.y);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("STRREF: %d", m_description);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            // FIXME: `strRes` is never fetched (always empty string)
            sTemp.Format("Description: %s", (LPCSTR)strRes.szText);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);
        }
        break;
    case 2:
        if (bEchoToScreen) {
            pWorld->DisplayText(CString(""),
                CString("DEBUG DUMP: CGameTrigger - Travel"),
                -1,
                FALSE);

            pWorld->DisplayText(CString(""),
                message,
                -1,
                FALSE);

            sTemp.Format("Current Area: %.*s", RESREF_SIZE, m_pArea->m_resRef.GetResRef());
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Current Position: x=%d y=%d", m_pos.x, m_pos.y);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Target Area: %.*s", RESREF_SIZE, m_newArea);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Entry Point Name: %.*s", SCRIPTNAME_SIZE, m_newEntryPoint);
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);

            sTemp.Format("Party Required: %s", (m_dwFlags & 0x4) != 0 ? "TRUE" : "FALSE");
            pWorld->DisplayText(CString(""),
                sTemp,
                -1,
                FALSE);
        }
        break;
    }
}

// 0x4CEBE0
BOOL CGameTrigger::IsOver(const CPoint& pt)
{
    if ((m_dwFlags & 0x100) != 0) {
        return FALSE;
    }

    if (m_triggerType == 0) {
        if (m_trapActivated == 0) {
            return FALSE;
        }

        if (m_trapDetected == 0) {
            return FALSE;
        }

        if (g_pBaldurChitin->GetObjectGame()->GetState() != 2) {
            return FALSE;
        }

        if (g_pBaldurChitin->GetObjectGame()->GetIconIndex() != 36) {
            return FALSE;
        }
    }

    if (m_rBounding.PtInRect(pt)) {
        return FALSE;
    }

    if (!g_pBaldurChitin->GetObjectGame()->GetGroup()->IsPartyLeader()) {
        return FALSE;
    }

    if (m_pPolygon != NULL) {
        return CVidPoly::IsPtInPoly(m_pPolygon, m_nPolygon, pt);
    }

    return TRUE;
}

// 0x4D0230
void CGameTrigger::SetDrawPoly(SHORT time)
{
    if (m_drawPoly != time) {
        if (!g_pBaldurChitin->GetBaldurMessage()->m_bInMessageSetDrawPoly) {
            CMessageSetDrawPoly* pMessage = new CMessageSetDrawPoly(time, GetId(), GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);
        }
    }
    m_drawPoly = time;
}

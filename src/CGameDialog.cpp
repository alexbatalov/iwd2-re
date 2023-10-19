#include "CGameDialog.h"

#include "CBaldurChitin.h"
#include "CScreenWorld.h"
#include "CUIControlTextDisplay.h"
#include "CUtil.h"

// 0x483970
void CGameDialogSprite::ClearMarshal()
{
    m_characterIndex = 0;
    m_talkerIndex = 0;
    m_dialogFreezeCounter = 6;
    m_dialogFreezeMultiplayer = 0;
    m_file = "";
    m_waitingForResponse = FALSE;
    m_currentEntryIndex = 0;
    m_responseMarker = -1;

    for (INT nIndex = 0; nIndex < m_dialogEntries.GetCount(); nIndex++) {
        CGameDialogEntry* pEntry = m_dialogEntries.GetAt(nIndex);
        if (pEntry != NULL) {
            delete pEntry;
        }
    }

    m_dialogEntries.RemoveAll();
    m_dialogEntriesOrdered.RemoveAll();
}

// 0x4845C0
void CGameDialogSprite::UpdateDialogColors()
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameDialog.cpp
    // __LINE__: 1295
    UTIL_ASSERT(pWorld != NULL);

    if (m_waitingForResponse && pWorld->m_pActiveDialogDisplay != NULL) {
        COLORREF rgb = RGB(215, 215, 190);
        if (pWorld->m_bInControlOfDialog) {
            rgb = RGB(255, 46, 33);
        }

        CGameDialogEntry* pEntry = m_dialogEntries[m_currentEntryIndex];

        for (INT nIndex = 0; nIndex < pEntry->GetCount(); nIndex++) {
            CGameDialogReply* pReply = pEntry->GetAt(nIndex);
            if (pReply->m_displayPosition != NULL) {
                pWorld->m_pActiveDialogDisplay->SetItemTextColor(pReply->m_displayPosition, rgb);
            }
        }
    }
}

// 0x484680
CGameDialogEntry::~CGameDialogEntry()
{
    for (INT nIndex = 0; nIndex < GetCount(); nIndex++) {
        CGameDialogReply* pReply = GetAt(nIndex);
        if (pReply != NULL) {
            delete pReply;
        }
    }
    RemoveAll();
}

// 0x484730
void CGameDialogEntry::RemoveReplies(LONG lMarker, COLORREF rgbNameColor, const CString& sName)
{
    STR_RES strRes;
    BOOLEAN bRemoveIfPicked = FALSE;
    STRREF strReplyText;

    for (INT nIndex = 0; nIndex < GetCount(); nIndex++) {
        CGameDialogReply* pReply = GetAt(nIndex);
        if ((pReply->m_flags & 0x20) == 0) {
            if (pReply->m_displayPosition != NULL) {
                if (nIndex == lMarker) {
                    bRemoveIfPicked = pReply->m_removeIfPicked;
                    strReplyText = pReply->m_replyText;
                }

                g_pBaldurChitin->m_pEngineWorld->RemoveText(pReply->m_displayPosition);
                pReply->m_displayPosition = NULL;
            }
        }
    }

    if (!bRemoveIfPicked) {
        if (lMarker >= 0 && lMarker < GetCount()) {
            strReplyText = GetAt(lMarker)->m_replyText;
        }

        g_pBaldurChitin->GetTlkTable().Fetch(strReplyText, strRes);

        g_pBaldurChitin->m_pEngineWorld->DisplayText(sName,
            strRes.szText,
            rgbNameColor,
            RGB(160, 200, 215),
            -1,
            FALSE);

        g_pBaldurChitin->m_pEngineWorld->DisplayText(CString(""),
            CString(""),
            -1,
            FALSE);
    }
}

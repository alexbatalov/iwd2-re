#include "CGameDialog.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CScreenWorld.h"
#include "CUIControlTextDisplay.h"
#include "CUtil.h"

// NOTE: Inlined.
CGameDialogSprite::CGameDialogSprite()
{
    ClearMarshal();
}

// 0x67CB50
CGameDialogSprite::~CGameDialogSprite()
{
    ClearMarshal();
}

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

// 0x4839F0
BOOL CGameDialogSprite::StartDialog(CGameSprite* pSprite)
{
    g_pBaldurChitin->m_pEngineWorld->DisableKeyRepeat();

    m_nMusicThreadPriority = GetThreadPriority(g_pChitin->m_hMusicThread);
    if (GetPrivateProfileIntA("Program Options", "Volume Music", 0, g_pChitin->GetIniFileName())) {
        m_bMusicThreadPriorityChanged = SetThreadPriority(g_pChitin->m_hMusicThread, 15);
    }

    for (INT nIndex = 0; nIndex < m_dialogEntriesOrdered.GetCount(); nIndex++) {
        CGameDialogEntry* pEntry = m_dialogEntriesOrdered.GetAt(nIndex);
        if (pEntry != NULL
            && pEntry->m_startCondition.Hold(CTypedPtrList<CPtrList, CAITrigger*>(), pSprite)) {
            // FIXME: Unused.
            LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetProtagonist();

            CMessage* pMessage = new CMessageEnterDialog(pEntry->m_dialogIndex,
                TRUE,
                pSprite->GetId(),
                pSprite->GetId());
            g_pBaldurChitin->GetMessageHandler()->AddMessage(pMessage, FALSE);

            field_54 = 1;
            field_56 = "";

            return TRUE;
        }
    }

    return FALSE;
}

// 0x483B70
BOOL CGameDialogSprite::FetchRumor(const CResRef& file, CGameSprite* pSprite, LONG& nIndex, STR_RES& strRes)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x483CF0
void CGameDialogSprite::EndDialog()
{
    if (m_bMusicThreadPriorityChanged == TRUE) {
        SetThreadPriority(g_pChitin->m_hMusicThread, m_nMusicThreadPriority);
    }

    g_pBaldurChitin->m_pEngineWorld->EnableKeyRepeat();

    m_waitingForResponse = FALSE;
    m_responseMarker = -1;
    field_54 = 0;
    field_56 = "";

    CResRef cResRef("SilentDH");

    CSound cSound;
    cSound.SetResRef(cResRef, TRUE, TRUE);
    if (cSound.m_nLooping == 0) {
        cSound.SetFireForget(TRUE);
    }
    cSound.SetChannel(6, reinterpret_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetVisibleArea()));
    cSound.Play(FALSE);
}

// 0x483EB0
BOOL CGameDialogSprite::EnterDialog(DWORD index, CGameSprite* pSprite, int a3)
{
    CGameDialogEntry* pEntry = m_dialogEntries[index];
    if (pEntry == NULL) {
        m_currentEntryIndex = 0;
        return FALSE;
    }

    m_currentEntryIndex = index;
    m_waitingForResponse = TRUE;
    m_responseMarker = -1;
    pEntry->Handle(pSprite, m_playerColor, a3);
    return TRUE;
}

// 0x483F00
void CGameDialogSprite::AsynchronousUpdate()
{
    // TODO: Incomplete.
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

// 0x484900
void CGameDialogEntry::Handle(CGameSprite* pSprite, COLORREF playerColor, int a3)
{
    // TODO: Incomplete.
}

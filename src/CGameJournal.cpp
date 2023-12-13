#include "CGameJournal.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CScreenCharacter.h"
#include "CScreenJournal.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x84C4E4
const INT CGameJournal::NUM_CHAPTERS = 7;

// NOTE: Inlined.
CGameJournalEntry::CGameJournalEntry()
{
}

// NOTE: Inlined.
CGameJournalEntry::CGameJournalEntry(STRREF strText, LONG nTime, WORD nType)
{
    m_strText = strText;
    m_nTime = nTime;
    m_wType = nType;
    m_bCharacter = 0xFF;
}

// 0x4C5FC0
void CGameJournalEntry::UpdateTextDisplay(CUIControlTextDisplay* pText)
{
    CString sTime;
    STR_RES strRes;
    CScreenJournal* pJournal = g_pBaldurChitin->m_pEngineJournal;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 130
    UTIL_ASSERT(pJournal != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 132
    UTIL_ASSERT(pText != NULL);

    CTimerWorld::GetCurrentTimeString(m_nTime, 15980, sTime);
    g_pBaldurChitin->GetTlkTable().Fetch(m_strText, strRes);
    CBaldurEngine::UpdateTextForceColor(pText, RGB(200, 200, 0), "%s", sTime);

    COLORREF rgbTextColor;
    switch (m_wType) {
    case 0:
        rgbTextColor = RGB(250, 250, 250);
        break;
    case 1:
        rgbTextColor = RGB(255, 255, 255);
        break;
    case 2:
        rgbTextColor = RGB(180, 180, 180);
        break;
    case 4:
        rgbTextColor = RGB(255, 255, 255);
        break;
    }

    pText->DisplayString(CString(""),
        strRes.szText,
        pText->m_rgbLabelColor,
        rgbTextColor,
        -1,
        FALSE,
        TRUE);

    pText->DisplayString(CString(""),
        CString(""),
        pText->m_rgbLabelColor,
        pText->m_rgbTextColor,
        -1,
        FALSE,
        TRUE);
}

// 0x4C6200
CGameJournal::CGameJournal()
{
    m_aChapters.SetSize(NUM_CHAPTERS);

    for (INT i = 0; i < NUM_CHAPTERS; i++) {
        m_aChapters[i] = new CTypedPtrList<CPtrList, CGameJournalEntry*>();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 219
        UTIL_ASSERT(m_aChapters[i] != NULL);
    }
}

// 0x4C62C0
CGameJournal::~CGameJournal()
{
    ClearAllEntries();

    for (INT i = 0; i < NUM_CHAPTERS; i++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 248
        UTIL_ASSERT(m_aChapters[i] != NULL);

        delete m_aChapters[i];

        m_aChapters[i] = NULL;
    }
}

// 0x4C6360
BOOL CGameJournal::AddEntry(STRREF strText, WORD nType)
{
    INT nChapter = g_pBaldurChitin->GetObjectGame()->GetCurrentChapter();
    nChapter = max(min(nChapter, NUM_CHAPTERS - 1), 0);
    return AddEntry(strText,
        nChapter,
        g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime,
        nType);
}

// 0x4C63B0
BOOL CGameJournal::AddEntry(STRREF strText, INT nChapter, LONG nTime, WORD nType)
{
    nChapter = max(min(nChapter, NUM_CHAPTERS - 1), 0);

    BOOL bResult = TRUE;
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetBaldurMessage()->AnnounceJournalEntry(strText, nChapter, nTime);
        } else {
            if (!g_pBaldurChitin->GetBaldurMessage()->m_bInOnJournalAnnounce) {
                g_pBaldurChitin->GetBaldurMessage()->SendJournalEntryToServer(strText, nChapter, nTime);
                return 0;
            }
        }
    }

    CGameJournalEntry* pEntry = new CGameJournalEntry();

    BOOL bFound = FALSE;
    for (INT i = 0; i < NUM_CHAPTERS && !bFound; i++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 340
        UTIL_ASSERT(m_aChapters[i] != NULL);

        POSITION pos = m_aChapters[i]->GetHeadPosition();
        while (pos != NULL && !bFound) {
            CGameJournalEntry* node = m_aChapters[i]->GetNext(pos);
            if (pEntry->m_strText == node->m_strText) {
                bFound = TRUE;
                bResult = FALSE;
            }
        }
    }

    if (!bFound) {
        m_aChapters[nChapter]->AddTail(pEntry);
        if (!g_pChitin->cNetwork.GetSessionOpen()
            || g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetObjectGame()->FeedBack(CInfGame::FEEDBACK_JOURNAL_UPDATE,
                0,
                TRUE);
        }
    } else {
        delete pEntry;
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineJournal
        && nChapter == g_pBaldurChitin->m_pEngineJournal->m_nChapter) {
        UpdateTextDisplay(g_pBaldurChitin->m_pEngineJournal->m_nChapter,
            static_cast<CUIControlTextDisplay*>(g_pBaldurChitin->m_pEngineJournal->GetManager()->GetPanel(2)->GetControl(1)));
    }

    return bResult;
}

// 0x4C6580
BOOL CGameJournal::InsertEntryAfter(CString strText, DWORD nEntry, DWORD nType)
{
    // NOTE: Uninline.
    INT nChapter = max(min(g_pBaldurChitin->GetObjectGame()->GetCurrentChapter(), NUM_CHAPTERS - 1), 0);

    return InsertEntryAfter(strText,
        nEntry,
        nChapter,
        g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->m_gameTime,
        g_pBaldurChitin->GetObjectGame()->GetCharactersControlled(),
        static_cast<WORD>(nType));
}

// 0x4C66F0
BOOL CGameJournal::InsertEntryAfter(CString szText, DWORD nIndex, INT nChapter, LONG nTime, BYTE nCharacter, WORD nType)
{
    if (szText.GetLength() == 0) {
        return FALSE;
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetBaldurMessage()->AnnounceJournalUserEntry(szText,
                nCharacter,
                nChapter,
                nTime,
                nIndex);
        } else {
            if (!g_pBaldurChitin->GetBaldurMessage()->m_bInOnJournalAnnounce) {
                g_pBaldurChitin->GetBaldurMessage()->SendJournalUserEntry(szText,
                    nCharacter,
                    nChapter,
                    nTime,
                    nIndex);
                return TRUE;
            }
        }
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 462
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    DWORD cnt = 0;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL && cnt != nIndex) {
        CGameJournalEntry* pEntry = m_aChapters[nChapter]->GetAt(pos);
        if ((nCharacter & pEntry->m_bCharacter) != 0) {
            cnt++;
        }
        m_aChapters[nChapter]->GetNext(pos);
    }

    CGameJournalEntry* pEntry = new CGameJournalEntry(g_pBaldurChitin->GetTlkTable().m_override.Add(szText),
        nTime,
        nType);
    pEntry->m_bCharacter = nCharacter;

    if (pos != NULL) {
        m_aChapters[nChapter]->InsertAfter(pos, pEntry);
    } else {
        m_aChapters[nChapter]->AddTail(pEntry);
    }

    if ((g_pBaldurChitin->GetObjectGame()->GetCharactersControlled() & nCharacter) != 0
        && (!g_pChitin->cNetwork.GetSessionOpen() || g_pChitin->cNetwork.GetSessionOpen())) {
        g_pBaldurChitin->GetObjectGame()->FeedBack(CInfGame::FEEDBACK_JOURNAL_UPDATE,
            0,
            FALSE);
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineJournal
        && nChapter == g_pBaldurChitin->m_pEngineJournal->m_nChapter
        && (g_pBaldurChitin->GetObjectGame()->GetCharactersControlled() & nCharacter) != 0) {
        UpdateTextDisplay(g_pBaldurChitin->m_pEngineJournal->m_nChapter,
            static_cast<CUIControlTextDisplay*>(g_pBaldurChitin->m_pEngineJournal->GetManager()->GetPanel(2)->GetControl(1)));
    }

    return FALSE;
}

// 0x4C6970
BOOL CGameJournal::IsEntryChanged(DWORD nIndex)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;
    STR_RES strRes;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 544
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    DWORD nTempIndex = 0;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetNext(pos);
        if (nTempIndex == nIndex) {
            break;
        }
        nTempIndex++;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 553
    UTIL_ASSERT(pEntry != NULL);

    return g_pBaldurChitin->GetTlkTable().m_override.Fetch(pEntry->m_strText, strRes);
}

// 0x4C6A90
void CGameJournal::UpdateTextDisplay(INT nChapter, CUIControlTextDisplay* pText)
{
    nChapter = max(min(nChapter, NUM_CHAPTERS - 1), 0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 582
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 584
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    BYTE bControlled = g_pBaldurChitin->GetObjectGame()->GetCharactersControlled();

    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        CGameJournalEntry* pEntry = m_aChapters[nChapter]->GetNext(pos);
        if ((bControlled & pEntry->m_bCharacter) != 0) {
            pEntry->UpdateTextDisplay(pText);
        }
    }

    pText->ScrollToBottom();
}

// 0x4C6B40
void CGameJournal::ClearAllEntries()
{
    for (INT i = 0; i < NUM_CHAPTERS; i++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 623
        UTIL_ASSERT(m_aChapters[i] != NULL);

        POSITION pos = m_aChapters[i]->GetHeadPosition();
        while (pos != NULL) {
            CGameJournalEntry* pEntry = m_aChapters[i]->GetNext(pos);
            delete pEntry;
        }

        m_aChapters[i]->RemoveAll();
    }
}

// 0x4C6BA0
WORD CGameJournal::CountEntries()
{
    WORD nEntries = 0;

    for (INT cnt = 0; cnt < NUM_CHAPTERS; cnt++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 659
        UTIL_ASSERT(m_aChapters[cnt] != NULL);

        nEntries += m_aChapters[cnt]->GetCount();
    }

    return nEntries;
}

// 0x4C6BF0
void CGameJournal::Marshal(CSavedGameJournalEntry* pSavedEntry)
{
    for (INT cnt = 0; cnt < NUM_CHAPTERS; cnt++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 693
        UTIL_ASSERT(m_aChapters[cnt] != NULL);

        POSITION pos = m_aChapters[cnt]->GetHeadPosition();
        while (pos != NULL) {
            CGameJournalEntry* pEntry = m_aChapters[cnt]->GetNext(pos);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
            // __LINE__: 698
            UTIL_ASSERT(pEntry != NULL);

            pSavedEntry->m_strEntry = pEntry->m_strText;
            pSavedEntry->m_time = pEntry->m_nTime;
            pSavedEntry->m_chapter = static_cast<BYTE>(cnt);
            pSavedEntry->m_type = static_cast<BYTE>(pEntry->m_wType);
            pSavedEntry->m_character = pEntry->m_bCharacter;
            pSavedEntry++;
        }
    }
}

// 0x4C6CD0
void CGameJournal::Unmarshal(CSavedGameJournalEntry* pSavedEntry, DWORD nSavedEntry)
{
    for (DWORD cnt = 0; cnt < nSavedEntry; cnt++) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 735
        UTIL_ASSERT(m_aChapters[(pSavedEntry + cnt)->m_chapter] != NULL);

        CGameJournalEntry* pEntry = new CGameJournalEntry();

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 737
        UTIL_ASSERT(pEntry != NULL);

        pEntry->m_strText = pSavedEntry[cnt].m_strEntry;
        pEntry->m_nTime = pSavedEntry[cnt].m_time;
        pEntry->m_wType = pSavedEntry[cnt].m_type;

        pEntry->m_bCharacter = -1;
        if (pSavedEntry[cnt].m_character != 0) {
            pEntry->m_bCharacter = pEntry->m_bCharacter;
        } else {
            pEntry->m_bCharacter = 1;
        }

        m_aChapters[pSavedEntry[cnt].m_chapter]->AddTail(pEntry);
    }
}

// 0x4C6D90
void CGameJournal::ChangeEntry(STRREF strRef, CString szNewText)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;
    BYTE nCharacter = g_pBaldurChitin->GetObjectGame()->GetCharactersControlled();
    ChangeEntry(strRef, szNewText, nChapter, nCharacter);
}

// 0x4C6E20
void CGameJournal::ChangeEntry(DWORD nIndex, CString szNewText, INT nChapter, BYTE nCharacter)
{
    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetBaldurMessage()->AnnounceJournalEntryChange(szNewText,
                nCharacter,
                nChapter,
                nIndex);
        } else {
            if (!g_pBaldurChitin->GetBaldurMessage()->m_bInOnJournalAnnounce) {
                g_pBaldurChitin->GetBaldurMessage()->SendJournalEntryChangeToServer(szNewText,
                    nCharacter,
                    nChapter,
                    nIndex);
                return;
            }
        }
    }

    STR_RES strRes;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 815
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetAt(pos);
        if ((nCharacter & pEntry->m_bCharacter) != 0) {
            break;
        }
        m_aChapters[nChapter]->GetNext(pos);
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 829
    UTIL_ASSERT(pEntry != NULL);

    if (szNewText.GetLength() != 0) {
        strRes.szText = szNewText;
        g_pBaldurChitin->GetTlkTable().m_override.AddUserEntry(pEntry->m_strText, strRes);
    } else {
        if (g_pBaldurChitin->GetTlkTable().m_override.Fetch(pEntry->m_strText, strRes)) {
            g_pBaldurChitin->GetTlkTable().m_override.Remove(pEntry->m_strText);
        }
        m_aChapters[nChapter]->RemoveAt(pos);
    }

    if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
        && g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineJournal
        && nChapter == g_pBaldurChitin->m_pEngineJournal->m_nChapter
        && (g_pBaldurChitin->GetObjectGame()->GetCharactersControlled() & nCharacter) != 0) {
        UpdateTextDisplay(g_pBaldurChitin->m_pEngineJournal->m_nChapter,
            static_cast<CUIControlTextDisplay*>(g_pBaldurChitin->m_pEngineJournal->GetManager()->GetPanel(2)->GetControl(1)));
    }
}

// 0x4C70E0
void CGameJournal::RevertEntry(DWORD nIndex)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;
    STR_RES strRes;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 890
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    DWORD nTempIndex = 0;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetNext(pos);
        if (nTempIndex == nIndex) {
            break;
        }
        nTempIndex++;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 899
    UTIL_ASSERT(pEntry != NULL);

    if (pEntry->m_wType != 0) {
        if (g_pBaldurChitin->GetTlkTable().m_override.Fetch(pEntry->m_strText, strRes)) {
            g_pBaldurChitin->GetTlkTable().m_override.Remove(pEntry->m_strText);
        }
    }
}

// 0x4C7220
void CGameJournal::SetQuestDone(STRREF strRef)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 936
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetNext(pos);
        if (pEntry->m_strText == strRef) {
            break;
        }
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 945
    UTIL_ASSERT(pEntry != NULL);

    if (pEntry->m_wType == 1) {
        pEntry->m_wType = 2;
    }
}

// 0x4C7320
CString CGameJournal::GetEntryText(DWORD nIndex)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;
    STR_RES strRes;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 979
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    DWORD nTempIndex = 0;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetNext(pos);
        if (nTempIndex == nIndex) {
            break;
        }
        nTempIndex++;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 988
    UTIL_ASSERT(pEntry != NULL);

    g_pBaldurChitin->GetTlkTable().Fetch(pEntry->m_strText, strRes);

    return strRes.szText;
}

// 0x4C7460
WORD CGameJournal::GetEntryType(DWORD nIndex)
{
    INT nChapter = g_pBaldurChitin->m_pEngineJournal->m_nChapter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 1017
    UTIL_ASSERT(m_aChapters[nChapter] != NULL);

    CGameJournalEntry* pEntry;
    DWORD nTempIndex = 0;
    POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
    while (pos != NULL) {
        pEntry = m_aChapters[nChapter]->GetNext(pos);
        if (nTempIndex == nIndex) {
            break;
        }
        nTempIndex++;
    }

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 1026
    UTIL_ASSERT(pEntry != NULL);

    return pEntry->m_wType;
}

// 0x4C7560
void CGameJournal::DeleteEntry(STRREF strRef)
{
    for (INT nChapter = 0; nChapter < NUM_CHAPTERS; nChapter++) {
        POSITION pos = m_aChapters[nChapter]->GetHeadPosition();
        while (pos != NULL) {
            POSITION posOld = pos;
            CGameJournalEntry* pEntry = m_aChapters[nChapter]->GetNext(pos);
            if (pEntry->m_strText == strRef) {
                m_aChapters[nChapter]->RemoveAt(posOld);

                if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
                    if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineJournal
                        && nChapter == g_pBaldurChitin->m_pEngineJournal->m_nChapter) {
                        CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(g_pBaldurChitin->m_pEngineJournal->GetManager()->GetPanel(2)->GetControl(1));
                        UpdateTextDisplay(g_pBaldurChitin->m_pEngineJournal->m_nChapter,
                            pText);
                    }
                }

                return;
            }
        }
    }
}

// 0x4C7600
void CGameJournal::sub_4C7600(FILE* stream, const CString& sString)
{
    CString sMutableString(sString);
    int length = sString.GetLength();
    int index = 0;
    while (index < length) {
        CString sLine = sMutableString.Mid(index, 70);
        int pos = sLine.Find('\n');
        if (pos != -1) {
            sLine.SetAt(pos, '\0');
            fprintf(stream, "%s\n", (LPCSTR)sLine);
        } else {
            if (sLine.GetLength() < 70) {
                fputs((LPCSTR)sLine, stream);
                break;
            }

            pos = sLine.ReverseFind(' ');
            sLine.SetAt(pos, '\0');
            fprintf(stream, "%s\n", (LPCSTR)sLine);
        }
        index += pos + 1;
    }
}

// 0x4C7710
void CGameJournal::SaveAll()
{
    for (INT iChapter = 0; iChapter < NUM_CHAPTERS; iChapter++) {
        Save(iChapter);
    }
}

// 0x4C7740
void CGameJournal::Save(INT iChapter)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
    // __LINE__: 1122
    UTIL_ASSERT(m_aChapters[iChapter] != NULL);

    CString sBase = g_pBaldurChitin->GetObjectGame()->GetDirSaveRoot() + CScreenCharacter::SAVE_NAME + "\\Chapter";

    CString sPath;
    sPath.Format("%s%2d.txt", (LPCSTR)sBase, iChapter);

    FILE* stream = fopen(sPath, "wt");
    if (stream != NULL) {
        CString sResRef;
        CString sChapter;

        sResRef = "chapters";

        CList<STRREF, STRREF>* pList = g_pBaldurChitin->GetObjectGame()->GetRuleTables().GetChapterText(CResRef(sResRef), iChapter);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameJournal.cpp
        // __LINE__: 1149
        UTIL_ASSERT(pList != NULL);

        if (pList->GetCount() > 0) {
            sChapter = CBaldurEngine::FetchString(pList->GetHead());
        }

        delete pList;

        fputs(sChapter, stream);
        fputs(":\n\n", stream);

        BYTE nCharacter = g_pBaldurChitin->GetObjectGame()->GetCharactersControlled();

        POSITION pos = m_aChapters[iChapter]->GetHeadPosition();
        while (pos != NULL) {
            CGameJournalEntry* pEntry = m_aChapters[iChapter]->GetNext(pos);
            if ((nCharacter & pEntry->m_bCharacter) != 0) {
                CString sTime;
                STR_RES strRes;

                CTimerWorld::GetCurrentTimeString(pEntry->m_nTime, 15980, sTime);
                g_pBaldurChitin->m_cTlkTable.Fetch(pEntry->m_strText, strRes);

                sTime += strRes.szText;

                sub_4C7600(stream, sTime);
                fputs("\n\n", stream);
            }
        }

        fclose(stream);
    }
}

#include "CGameJournal.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CScreenJournal.h"
#include "CUIControlTextDisplay.h"
#include "CUtil.h"

// 0x84C4E4
const INT CGameJournal::NUM_CHAPTERS = 7;

// NOTE: Inlined.
CGameJournalEntry::CGameJournalEntry()
{
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
    g_pBaldurChitin->m_cTlkTable.Fetch(m_strText, strRes);
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
    INT nChapter = g_pBaldurChitin->m_pObjectGame->GetCurrentChapter();
    nChapter = max(min(nChapter, NUM_CHAPTERS - 1), 0);
    return AddEntry(strText,
        nChapter,
        g_pBaldurChitin->m_pObjectGame->GetWorldTimer()->m_gameTime,
        nType);
}

// 0x4C63B0
BOOL CGameJournal::AddEntry(STRREF strText, INT nChapter, LONG nTime, WORD nType)
{
    // TODO: Incomplete.

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

    return g_pBaldurChitin->m_cTlkTable.m_override.Fetch(pEntry->m_strText, strRes);
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

    BYTE bControlled = g_pBaldurChitin->m_pObjectGame->GetCharactersControlled();

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
        if (g_pBaldurChitin->m_cTlkTable.m_override.Fetch(pEntry->m_strText, strRes)) {
            g_pBaldurChitin->m_cTlkTable.m_override.Remove(pEntry->m_strText);
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

    g_pBaldurChitin->m_cTlkTable.Fetch(pEntry->m_strText, strRes);

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

    // TODO: Incomplete.
}

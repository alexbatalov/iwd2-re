#ifndef CGAMEJOURNAL_H_
#define CGAMEJOURNAL_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "FileFormat.h"

class CUIControlTextDisplay;

class CGameJournalEntry {
public:
    CGameJournalEntry();
    CGameJournalEntry(STRREF strText, LONG nTime, WORD nType);
    void UpdateTextDisplay(CUIControlTextDisplay* pText);

    /* 0000 */ STRREF m_strText;
    /* 0004 */ LONG m_nTime;
    /* 0008 */ DWORD m_dwFlags;
    /* 000C */ WORD m_wType;
    /* 000E */ BYTE m_bCharacter;
};

class CGameJournal {
public:
    static const INT NUM_CHAPTERS;

    CGameJournal();
    ~CGameJournal();
    BOOL AddEntry(STRREF strText, WORD nType);
    BOOL AddEntry(STRREF strText, INT nChapter, LONG nTime, WORD nType);
    BOOL InsertEntryAfter(CString strText, DWORD nEntry, DWORD nType);
    BOOL InsertEntryAfter(CString szText, DWORD nIndex, INT nChapter, LONG nTime, BYTE nCharacter, WORD nType);
    BOOL IsEntryChanged(DWORD nIndex);
    void UpdateTextDisplay(INT nChapter, CUIControlTextDisplay* pText);
    void ClearAllEntries();
    WORD CountEntries();
    void Marshal(CSavedGameJournalEntry* pSavedEntry);
    void Unmarshal(CSavedGameJournalEntry* pSavedEntry, DWORD nSavedEntry);
    void ChangeEntry(STRREF strRef, CString szNewText);
    void ChangeEntry(DWORD nIndex, CString szNewText, INT nChapter, BYTE nCharacter);
    void RevertEntry(DWORD nIndex);
    void SetQuestDone(STRREF strRef);
    CString GetEntryText(DWORD nIndex);
    WORD GetEntryType(DWORD nIndex);
    void DeleteEntry(STRREF strRef);
    static void sub_4C7600(FILE* stream, const CString& sString);
    void SaveAll();
    void Save(INT iChapter);

    /* 0000 */ CTypedPtrArray<CPtrArray, CTypedPtrList<CPtrList, CGameJournalEntry*>*> m_aChapters;
};

#endif /* CGAMEJOURNAL_H_ */

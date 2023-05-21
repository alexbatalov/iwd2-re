#ifndef CGAMEJOURNAL_H_
#define CGAMEJOURNAL_H_

#include "mfc.h"

#include "BalDataTypes.h"

class CUIControlTextDisplay;

class CGameJournalEntry {
public:
    CGameJournalEntry();
    void UpdateTextDisplay(CUIControlTextDisplay* pText);

    /* 0000 */ STRREF m_strText;
    /* 0004 */ LONG m_nTime;
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
    BOOL IsEntryChanged(DWORD nIndex);
    void UpdateTextDisplay(INT nChapter, CUIControlTextDisplay* pText);
    void ClearAllEntries();
    WORD CountEntries();
    void RevertEntry(DWORD nIndex);
    void SetQuestDone(STRREF strRef);
    CString GetEntryText(DWORD nIndex);
    WORD GetEntryType(DWORD nIndex);
    void SaveAll();
    void Save(INT iChapter);

    /* 0000 */ CTypedPtrArray<CPtrArray, CTypedPtrList<CPtrList, CGameJournalEntry*>*> m_aChapters;
};

#endif /* CGAMEJOURNAL_H_ */

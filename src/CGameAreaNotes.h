#ifndef CGAMEAREANOTES_H_
#define CGAMEAREANOTES_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "CResRef.h"
#include "FileFormat.h"

class CUIControlButtonMapAreaMap;

class CGameAreaNotes {
public:
    CGameAreaNotes();
    ~CGameAreaNotes();
    void IntrnlInitialize();
    void GetGridSquare(CPoint pt, CPoint& sq, BOOL a3);
    BOOL AddButton(CPoint pt);
    BOOL AddANote(const CAreaUserNote& cNote);
    void Add();
    BYTE sub_47B140();
    BOOL sub_47B150(WORD startX, WORD startY, CString szNote, DWORD dwFlags, STRREF strRef);
    void Add(CString area, WORD startX, WORD startY, CString szNote, DWORD dwFlags, STRREF strRef);
    STRREF GetNoteButtonText(DWORD id);
    CAreaUserNote* GetNoteAt(const CPoint& pt);
    void Marshal(BYTE**& pArea, DWORD& cnt);
    BOOL DeleteANote(DWORD id);
    void Invalidate();
    void SetStringBuffer(CString szTemp);

    /* 0000 */ DWORD** m_areaNoteGrid;
    /* 0004 */ BOOL m_bInitialized;
    /* 0008 */ CPoint m_ptCellSize;
    /* 0010 */ CPoint m_ptStart;
    /* 0018 */ CPoint m_ptButtonSize;
    /* 0020 */ CTypedPtrList<CPtrList, CAreaUserNote*> m_areaNoteList;
    /* 003C */ CAreaUserNote m_cAreaNote;
    /* 0070 */ int field_70;
    /* 0074 */ int field_74;
    /* 0078 */ CUIControlButtonMapAreaMap* m_pMapControl;
    /* 007C */ UI_CONTROL_BUTTON* m_pControlInfo;
    /* 0080 */ CResRef m_rArea;
    /* 0088 */ CString m_szBuffer;
    /* 008C */ unsigned char field_8C;
    /* 008D */ unsigned char field_8D;
    /* 008E */ unsigned char field_8E;
};

#endif /* CGAMEAREANOTES_H_ */

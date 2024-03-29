#include "CGameAreaNotes.h"

#include "CBaldurChitin.h"
#include "CScreenMap.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x47A730
CGameAreaNotes::CGameAreaNotes()
{
    field_70 = 0;
    field_74 = 0;
    m_pMapControl = NULL;
    field_8C = 0;
    field_8D = 0;
    field_8E = 0;
    m_bInitialized = FALSE;
    m_areaNoteGrid = NULL;
    m_pControlInfo = NULL;
}

// 0x47A7C0
CGameAreaNotes::~CGameAreaNotes()
{
    if (m_areaNoteGrid != NULL) {
        for (INT x = 0; x < m_ptCellSize.x; x++) {
            delete m_areaNoteGrid[x];
        }
        delete m_areaNoteGrid;
    }

    if (m_pControlInfo != NULL) {
        delete m_pControlInfo;
    }

    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    CUIPanel* pPanel = pMap->GetManager()->GetPanel(2);

    if (pPanel != NULL) {
        CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));
        if (pMapControl != NULL) {
            // NOTE: Uninline.
            pMapControl->field_7BE.RemoveAll();
        }
    }

    while (!m_areaNoteList.IsEmpty()) {
        CAreaUserNote* pNote = m_areaNoteList.GetHead();
        if (pNote != NULL) {
            pPanel->RemoveControl(pNote->m_id);
        }

        delete m_areaNoteList.RemoveHead();
    }
}

// 0x47A900
void CGameAreaNotes::IntrnlInitialize()
{
    if (!m_bInitialized) {
        field_8D = 0;

        CVidCell vcFlag(CResRef("FLAG1"), FALSE);

        CSize frameSize;
        vcFlag.GetFrameSize(0, 0, frameSize, FALSE);

        m_ptButtonSize.x = frameSize.cx;
        m_ptButtonSize.y = frameSize.cy;

        m_pControlInfo = new UI_CONTROL_BUTTON();
        memset(m_pControlInfo, 0, sizeof(UI_CONTROL_BUTTON));
        m_pControlInfo->base.nWidth = static_cast<WORD>(frameSize.cx);
        m_pControlInfo->base.nHeight = static_cast<WORD>(frameSize.cy);
        m_pControlInfo->nSequence = 0;
        m_pControlInfo->nDisabledFrame = 0;
        m_pControlInfo->nPressedFrame = 0;
        m_pControlInfo->nSelectedFrame = 0;
        m_pControlInfo->nNormalFrame = 0;
        vcFlag.GetResRef().GetResRef(m_pControlInfo->refBam);

        memset(&m_cAreaNote, 0, sizeof(m_cAreaNote));

        m_pMapControl = static_cast<CUIControlButtonMapAreaMap*>(g_pBaldurChitin->m_pEngineMap->GetManager()->GetPanel(2)->GetControl(2));

        m_ptCellSize.x = m_pMapControl->m_size.cx / m_ptButtonSize.x;
        m_ptCellSize.y = m_pMapControl->m_size.cy / m_ptButtonSize.y;

        m_pMapControl->GetStartPosition(m_ptStart);

        m_areaNoteGrid = new DWORD*[m_ptCellSize.x];
        for (INT x = 0; x < m_ptCellSize.x; x++) {
            m_areaNoteGrid[x] = new DWORD[m_ptCellSize.y];
            for (INT y = 0; y < m_ptCellSize.y; y++) {
                m_areaNoteGrid[x][y] = -1;
            }
        }

        m_bInitialized = TRUE;

        if (m_areaNoteList.GetCount() > 0) {
            CPoint sq;
            POSITION pos = m_areaNoteList.GetHeadPosition();
            while (pos != NULL) {
                POSITION posOld = pos;
                CAreaUserNote* pNote = m_areaNoteList.GetNext(pos);
                m_cAreaNote = *pNote;
                GetGridSquare(CPoint(m_cAreaNote.m_startX, m_cAreaNote.m_startY),
                    sq,
                    TRUE);
                if (IsANoteThere(sq)) {
                    CAreaUserNote* pOldNote = GetNoteAt(sq);
                    STR_RES stOld;
                    STR_RES stNew;

                    if (!g_pBaldurChitin->GetTlkTable().m_override.Fetch(pOldNote->m_note, stOld)) {
                        g_pBaldurChitin->GetTlkTable().Fetch(pOldNote->m_note, stOld);
                        g_pBaldurChitin->GetTlkTable().m_override.AddUserEntry(pOldNote->m_note, stOld);
                    }
                    g_pBaldurChitin->GetTlkTable().Fetch(pNote->m_note, stNew);
                    if (!stNew.szText.IsEmpty()) {
                        if ((pNote->m_dwflags & 0x1) != 0) {
                            stOld.szText += '\n' + stNew.szText;
                        } else {
                            stOld.szText = stNew.szText;
                        }
                        g_pBaldurChitin->GetTlkTable().m_override.AddUserEntry(pOldNote->m_note, stOld);
                        delete pNote;
                        m_areaNoteList.RemoveAt(posOld);
                    } else {
                        DeleteANote(pOldNote->m_id);
                        delete pNote;
                        m_areaNoteList.RemoveAt(posOld);
                    }
                } else {
                    field_8D = (m_cAreaNote.m_dwflags >> 16) & 0xFF;
                    AddButton(sq);
                    pNote->m_id = m_cAreaNote.m_id;
                }
            }
        }
    } else {
        if (field_8E) {
            if (m_areaNoteList.GetCount() > 0) {
                CPoint sq;
                POSITION pos = m_areaNoteList.GetHeadPosition();
                while (pos != NULL) {
                    CAreaUserNote* pNote = m_areaNoteList.GetAt(pos);
                    m_cAreaNote = *pNote;
                    GetGridSquare(CPoint(m_cAreaNote.m_startX, m_cAreaNote.m_startY),
                        sq,
                        TRUE);
                    if (!IsANoteThere(sq)) {
                        field_8D = (m_cAreaNote.m_dwflags >> 16) & 0xFF;
                        AddButton(sq);
                        pNote->m_id = m_cAreaNote.m_id;
                    }
                    m_areaNoteList.GetNext(pos);
                }
            }
        }
        field_8E = 0;
    }
}

// 0x47AE30
void CGameAreaNotes::GetGridSquare(CPoint pt, CPoint& sq, BOOL a3)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
    // __LINE__: 381
    UTIL_ASSERT(m_bInitialized);

    if (a3) {
        sq.x = 4 * pt.x / 32 / m_ptButtonSize.x;
        sq.y = 4 * pt.y / 32 / m_ptButtonSize.y;
    } else {
        sq.x = pt.x / m_ptButtonSize.x;
        sq.y = pt.y / m_ptButtonSize.y;
    }

    if (sq.x < 0) {
        sq.x = 0;
    } else if (sq.x >= m_ptCellSize.x) {
        sq.x = m_ptCellSize.x - 1;
    }

    if (sq.y < 0) {
        sq.y = 0;
    } else if (sq.y >= m_ptCellSize.y) {
        sq.y = m_ptCellSize.y - 1;
    }
}

// 0x47AEE0
BOOL CGameAreaNotes::AddButton(CPoint pt)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
    // __LINE__: 468
    UTIL_ASSERT(m_bInitialized);

    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    CUIPanel* pPanel = pMap->GetManager()->GetPanel(2);
    CUIControlButtonMapAreaMap* pMapControl = static_cast<CUIControlButtonMapAreaMap*>(pPanel->GetControl(2));

    UI_CONTROL_BUTTON* pControlInfo = new UI_CONTROL_BUTTON();
    memcpy(pControlInfo, m_pControlInfo, sizeof(UI_CONTROL_BUTTON));
    pControlInfo->base.x = static_cast<WORD>(pt.x * m_ptButtonSize.x);
    pControlInfo->base.y = static_cast<WORD>(pt.y * m_ptButtonSize.y);
    pControlInfo->base.nID = ++m_pMapControl->m_nUserNoteId;

    pPanel->AddControl(&(pControlInfo->base));
    pMapControl->AddNote(pControlInfo->base.nID);

    CUIControlButtonMapNote* pNoteControl = static_cast<CUIControlButtonMapNote*>(pPanel->GetControl(pControlInfo->base.nID));
    pNoteControl->m_areaResRef = m_rArea;
    pNoteControl->SetInactiveRender(FALSE);
    pNoteControl->m_cVidCell.SequenceSet(min(field_8D, 7));
    pNoteControl->m_ptWorld = pMapControl->ConvertScreenToWorldCoords(pNoteControl->m_ptOrigin);
    m_cAreaNote.m_id = pControlInfo->base.nID;
    m_areaNoteGrid[pt.x][pt.y] = pControlInfo->base.nID;

    delete pControlInfo;
    return TRUE;
}

// 0x47B040
BOOL CGameAreaNotes::AddANote(const CAreaUserNote& cNote)
{
    CAreaUserNote* pNote = new CAreaUserNote();
    memcpy(pNote, &cNote, sizeof(CAreaUserNote));
    m_areaNoteList.AddTail(pNote);
    return TRUE;
}

// 0x47B090
void CGameAreaNotes::Add()
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
    // __LINE__: 550
    UTIL_ASSERT(m_bInitialized);

    Add(m_rArea.GetResRefStr(),
        m_cAreaNote.m_startX,
        m_cAreaNote.m_startY,
        m_szBuffer,
        sub_47B140() << 16,
        -1);
}

// 0x47B140
BYTE CGameAreaNotes::sub_47B140()
{
    return field_8D;
}

// 0x47B150
BOOL CGameAreaNotes::sub_47B150(WORD startX, WORD startY, CString szNote, DWORD dwFlags, STRREF strRef)
{
    STR_RES strRes;

    if (m_areaNoteList.GetCount() > 0) {
        POSITION pos = m_areaNoteList.GetHeadPosition();
        while (pos != NULL) {
            CAreaUserNote* pNote = m_areaNoteList.GetAt(pos);
            if (pNote->m_startX == startX || pNote->m_startY == startY) {
                if (szNote.GetLength() != 0) {
                    pNote->m_dwflags = dwFlags;
                    if (g_pBaldurChitin->GetTlkTable().m_override.Fetch(pNote->m_note, strRes)) {
                        strRes.szText = szNote;
                        g_pBaldurChitin->GetTlkTable().m_override.AddUserEntry(pNote->m_note, strRes);
                    } else {
                        if (strRef != -1) {
                            strRes.szText = szNote;
                            g_pBaldurChitin->GetTlkTable().m_override.AddUserEntry(strRef, strRes);
                            pNote->m_note = strRef;
                        } else {
                            pNote->m_note = g_pBaldurChitin->GetTlkTable().m_override.Add(szNote);
                        }
                    }
                } else {
                    delete pNote;
                    m_areaNoteList.RemoveAt(pos);
                }
                return TRUE;
            }
            m_areaNoteList.GetNext(pos);
        }
    }

    return FALSE;
}

// 0x47B090
void CGameAreaNotes::Add(CString area, WORD startX, WORD startY, CString szNote, DWORD dwFlags, STRREF strRef)
{
    // TODO: Incomplete.
}

// 0x47BAD0
STRREF CGameAreaNotes::GetNoteButtonText(DWORD id)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
    // __LINE__: 1097
    UTIL_ASSERT(m_bInitialized);

    if (m_areaNoteList.IsEmpty()) {
        return -1;
    }

    POSITION pos = m_areaNoteList.GetHeadPosition();
    while (pos != NULL) {
        CAreaUserNote* pNote = m_areaNoteList.GetNext(pos);
        if (pNote->m_id == id) {
            return pNote->m_note;
        }
    }

    return -1;
}

// 0x47BB40
CAreaUserNote* CGameAreaNotes::GetNoteAt(const CPoint& pt)
{
    DWORD id = m_areaNoteGrid[pt.x][pt.y];

    if (id == -1) {
        return NULL;
    }

    if (m_areaNoteList.IsEmpty()) {
        return NULL;
    }

    POSITION pos = m_areaNoteList.GetHeadPosition();
    while (pos != NULL) {
        CAreaUserNote* pNote = m_areaNoteList.GetNext(pos);
        if (pNote->m_id == id) {
            return pNote;
        }
    }

    return NULL;
}

// 0x47BB90
void CGameAreaNotes::Marshal(BYTE**& pArea, DWORD& cnt)
{
    POSITION pos = m_areaNoteList.GetHeadPosition();
    while (pos != NULL) {
        CAreaUserNote* pNote = m_areaNoteList.GetNext(pos);
        memcpy(*pArea + cnt, pNote, sizeof(CAreaUserNote));
        cnt += sizeof(CAreaUserNote);
    }
}

// 0x47BBD0
BOOL CGameAreaNotes::DeleteANote(DWORD id)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x47BE80
void CGameAreaNotes::Invalidate()
{
    if (m_areaNoteList.IsEmpty()) {
        return;
    }

    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;

    CUIPanel* pPanel = pMap->GetManager()->GetPanel(2);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
    // __LINE__: 1406
    UTIL_ASSERT(pPanel != NULL);

    POSITION pos = m_areaNoteList.GetHeadPosition();
    while (pos != NULL) {
        CAreaUserNote* pNote = m_areaNoteList.GetNext(pos);

        CUIControlBase* pControl = pPanel->GetControl(pNote->m_id);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameAreaNotes.cpp
        // __LINE__: 1417
        UTIL_ASSERT(pControl != NULL);

        pControl->InvalidateRect();
    }
}

// FIXME: `szTemp` should be reference.
//
// 0x642670
void CGameAreaNotes::SetStringBuffer(CString szTemp)
{
    m_szBuffer = szTemp;
}

// NOTE: Inlined.
BOOL CGameAreaNotes::IsANoteThere(const CPoint& pt)
{
    return m_areaNoteGrid[pt.x][pt.y] != -1;
}

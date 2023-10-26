#include "CGameStatic.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x4CA530
CGameStatic::CGameStatic(CGameArea* pArea, CAreaFileStaticObject* pStaticObject)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameStatic.cpp
    // __LINE__: 106
    UTIL_ASSERT(pArea != NULL && pStaticObject != NULL);

    m_objectType = TYPE_STATIC;

    memcpy(&m_header, pStaticObject, sizeof(CAreaFileStaticObject));
    m_header.m_posY += m_header.m_height;

    m_vidCell.SetResRef(CResRef(m_header.m_resRef), FALSE, TRUE, TRUE);
    m_vidCell.SequenceSet(static_cast<SHORT>(m_header.m_nSequence));

    // FIXME: Calls `GetSequenceLength` twice.
    BYTE nSequenceLength = max(m_vidCell.GetSequenceLength(m_vidCell.m_nCurrentSequence, FALSE), 1);
    m_vidCell.FrameSet((pStaticObject->m_posX + pStaticObject->m_posY) % 64 % nSequenceLength);

    if (g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id, this, INFINITE) == CGameObjectArray::SUCCESS) {
        CVariable variable;
        variable.SetName(CString(m_header.m_scriptName));
        pArea->GetNamedCreatures()->AddKey(variable);

        AddToArea(pArea,
            CPoint(m_header.m_posX, m_header.m_posY),
            m_header.m_height,
            LIST_FRONT);
    } else {
        // FIXME: Doesn't look cool.
        delete this;
    }
}

// 0x4CA7D0
CGameStatic::~CGameStatic()
{
}

// 0x766660
BOOLEAN CGameStatic::CompressTime(DWORD deltaTime)
{
    return TRUE;
}

// 0x4CA840
BOOLEAN CGameStatic::DoAIUpdate(BOOLEAN active, LONG counter)
{
    if (active && (counter & m_AISpeed) == (m_AISpeed & m_id)) {
        return ((m_header.m_timeOfDayVisible >> g_pBaldurChitin->GetObjectGame()->GetWorldTimer()->GetCurrentHour()) & 0x1) != 0;
    } else {
        return FALSE;
    }
}

// 0x4CA8D0
void CGameStatic::AIUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if ((pGame->m_nTimeStop == 0 || pGame->m_nTimeStopCaster == m_id)
        && (m_header.m_dwFlags & 0x8) != 0) {
        m_vidCell.FrameAdvance();
    }
}

// 0x4CA910
void CGameStatic::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameStatic.cpp
        // __LINE__: 226
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x4CAD30
void CGameStatic::Marshal(CAreaFileStaticObject** pStaticObject)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameStatic.cpp
    // __LINE__: 381
    UTIL_ASSERT(pStaticObject != NULL);

    *pStaticObject = new CAreaFileStaticObject;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameStatic.cpp
    // __LINE__: 384
    UTIL_ASSERT(*pStaticObject != NULL);

    memcpy(*pStaticObject, &m_header, sizeof(CAreaFileStaticObject));

    (*pStaticObject)->m_posY -= (*pStaticObject)->m_height;
}

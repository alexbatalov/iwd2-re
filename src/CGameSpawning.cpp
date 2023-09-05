#include "CGameSpawning.h"

#include "CBaldurChitin.h"
#include "CGameArea.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x4C9780
CGameSpawning::CGameSpawning(CGameArea* pArea, CAreaFileRandomMonsterSpawningPoint* pSpawningObject)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSpawning.cpp
    // __LINE__: 108
    UTIL_ASSERT(pArea != NULL && pSpawningObject != NULL);

    m_objectType = TYPE_SPAWNING;

    memcpy(&m_spawningObject, pSpawningObject, sizeof(CAreaFileRandomMonsterSpawningPoint));

    CVariable variable;
    variable.SetName(m_spawningObject.m_scriptName);
    pArea->GetNamedCreatures()->AddKey(variable);

    if (m_spawningObject.m_probDay == 0) {
        m_spawningObject.m_probDay = 100;
    }

    if (m_spawningObject.m_probNight == 0) {
        m_spawningObject.m_probNight = 100;
    }

    field_136 = 0;

    // NOTE: This assignment is slightly incorrect. Original code refers to
    // other offsets (0x8A8168 and 0x8A8154 respectively). It can mean two
    // things:
    // - There was second set of terrain table defaults, which is exactly the
    // same as in `CGameObject`.
    // - Such split was a result of some compiler optimization.
    //
    // Since both sets have the same values, there is no harm to reuse what's
    // already present.
    memcpy(m_terrainTable, DEFAULT_TERRAIN_TABLE, 16);
    memcpy(m_visibleTerrainTable, DEFAULT_VISIBLE_TERRAIN_TABLE, 16);

    if (g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Add(&m_id, this, INFINITE) == CGameObjectArray::SUCCESS) {
        AddToArea(pArea,
            CPoint(m_spawningObject.m_posX, m_spawningObject.m_posY),
            0,
            LIST_BACK);
    } else {
        // FIXME: Doesn't look cool.
        delete this;
    }
}

// 0x4C9990
CGameSpawning::~CGameSpawning()
{
}

// 0x4CA3D0
void CGameSpawning::RemoveFromArea()
{
    CGameObject::RemoveFromArea();

    BYTE rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->Delete(m_id,
        CGameObjectArray::THREAD_ASYNCH,
        NULL,
        INFINITE);
    if (rc != CGameObjectArray::SUCCESS) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSpawning.cpp
        // __LINE__: 352
        UTIL_ASSERT(FALSE);
    }

    delete this;
}

// 0x4CA430
void CGameSpawning::Marshal(CAreaFileRandomMonsterSpawningPoint** pSpawningObject)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSpawning.cpp
    // __LINE__: 379
    UTIL_ASSERT(pSpawningObject != NULL);

    *pSpawningObject = new CAreaFileRandomMonsterSpawningPoint;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CGameSpawning.cpp
    // __LINE__: 382
    UTIL_ASSERT(*pSpawningObject != NULL);

    memcpy(*pSpawningObject, &m_spawningObject, sizeof(CAreaFileRandomMonsterSpawningPoint));
}

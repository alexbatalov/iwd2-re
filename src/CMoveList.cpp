#include "CMoveList.h"

#include "CGameObjectArray.h"

// 0x5170A0
CMoveListEntry::CMoveListEntry()
{
    m_nSpriteId = CGameObjectArray::INVALID_INDEX;
    m_areaResRef = "";
    m_ptDestination.x = 0;
    m_ptDestination.y = 0;
    m_nFacing = 0;
    m_nDelay = 0;
}

// NOTE: Inlined.
CMoveList::CMoveList()
{
}

// 0x59EAD0
CMoveList::~CMoveList()
{
    ClearAll();
}

// 0x4E71B0
void CMoveList::ClearAll()
{
    POSITION pos = GetHeadPosition();
    while (pos != NULL) {
        CMoveListEntry* pEntry = GetNext(pos);
        delete pEntry;
    }
    RemoveAll();
}

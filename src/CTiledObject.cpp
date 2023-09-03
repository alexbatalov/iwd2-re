#include "CTiledObject.h"

// 0x84EC08
const WORD CTiledObject::STATE_PRIMARY_TILE = 1;

// 0x84EC0A
const WORD CTiledObject::STATE_SECONDARY_TILE = 2;

// NOTE: Inlined.
CTiledObject::CTiledObject()
{
    m_posAreaList = NULL;
    m_pResWed = NULL;
    m_nWedIndex = 0;
    m_wAIState = 0;
    m_wRenderState = 0;
}

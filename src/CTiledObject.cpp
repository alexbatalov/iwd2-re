#include "CTiledObject.h"

#include "CInfinity.h"

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

// 0x54E5B0
void CTiledObject::CheckTileState(CInfinity& cInfinity)
{
    // TODO: Incomplete.
}

// 0x54E830
void CTiledObject::Initialize(CResWED* pResWed, CResRef resID, POSITION posAreaList, WORD wInitialState)
{
    // TODO: Incomplete.
}

// 0x54E980
void CTiledObject::SetNewResWED(CResWED* pNewResWED)
{
    // TODO: Incomplete.
}

#include "CGameSave.h"

// NOTE: Inlined.
CGameSave::CGameSave()
{
    m_nCurrentWorldLink = 0;
    m_nPartyGold = 0;
    m_curFormation = 0;
    memset(m_quickFormations, 0, sizeof(m_quickFormations));
    memset(m_groupInventory, 0, sizeof(m_groupInventory));
    field_1AC = 0;
    field_1B0 = 0;
    field_1B2 = 0;
    m_mode = 0;
    m_cutScene = FALSE;
}

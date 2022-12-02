#include "CBaldurEngine.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"

// 0x4277C0
CBaldurEngine::CBaldurEngine()
{
    m_nSelectedCharacter = 0;
    field_FA = 0;
    field_102 = 0;
    field_FE = 0;
    m_nPickedCharacter = -1;
}

// 0x427850
CUIManager* CBaldurEngine::GetUIManager()
{
    return &m_cUIManager;
}

// 0x427860
void CBaldurEngine::SetSelectedCharacter(int nNewSelectedCharacter)
{
    m_nSelectedCharacter = nNewSelectedCharacter;
}

// 0x427870
void CBaldurEngine::SetPickedCharacter(int nNewPickedCharacter)
{
    m_nPickedCharacter = nNewPickedCharacter;
}

// 0x427880
void CBaldurEngine::InvalidateCursorRect(const CRect& rect)
{
    CRect copy;
    copy.CopyRect(rect);
    m_cUIManager.InvalidateCursorRect(copy);
}

// 0x4278B0
void CBaldurEngine::ResetControls()
{
    m_cUIManager.InvalidateRect(NULL);
}

// 0x4278E0
CBaldurEngine::~CBaldurEngine()
{
}

// 0x427930
int CBaldurEngine::GetSelectedCharacter()
{
    if (m_nSelectedCharacter > g_pBaldurChitin->m_pObjectGame->m_nCharacters) {
        m_nSelectedCharacter = 0;
    }
    return m_nSelectedCharacter;
}

// 0x427960
int CBaldurEngine::GetPickedCharacter()
{
    if (m_nPickedCharacter > g_pBaldurChitin->m_pObjectGame->m_nCharacters) {
        m_nPickedCharacter = 0;
    }
    return m_nPickedCharacter;
}

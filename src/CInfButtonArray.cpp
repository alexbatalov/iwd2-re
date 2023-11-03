#include "CInfButtonArray.h"

#include "CBaldurChitin.h"
#include "CButtonData.h"
#include "CGameSprite.h"
#include "CInfGame.h"

// 0x851700
const BYTE CInfButtonArray::STATE_NONE = 0;

// 0x587960
CInfButtonSettings::CInfButtonSettings()
{
    field_1C8 = 0;
    field_1CC = 0;
    field_1D8 = 0;
    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
    field_1D0 = 0;
    m_bGreyOut = FALSE;
    field_C = -1;
    field_10 = -1;
}

// 0x587B80
CInfButtonSettings::~CInfButtonSettings()
{
}

// 0x5879E0
CInfButtonArray::CInfButtonArray()
{
    // TODO: Incomplete.
}

// 0x588240
void CInfButtonArray::GetSelectedQuickWeaponData(CButtonData& cButtonData)
{
    if (g_pBaldurChitin->GetObjectGame()->GetGroup()->GetCount() != 0) {
        LONG* groupList = g_pBaldurChitin->GetObjectGame()->GetGroup()->GetGroupList();
        LONG nCharacterId = groupList[0];
        delete groupList;

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pSprite->GetSelectedWeaponButton(cButtonData);

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// 0x5883C0
BYTE CInfButtonArray::GetSelectedModalMode()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    BYTE modalState = 0;

    if (pGame->GetGroup()->GetCount() != 0) {
        LONG nCharacterId = pGame->GetGroup()->GetGroupLeader();

        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = pGame->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            modalState = pSprite->GetModalState();

            pGame->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }

    return modalState;
}

// 0x588460
BYTE CInfButtonArray::GetButtonId(INT buttonType)
{
    for (BYTE id = 0; id < 12; id++) {
        if (m_buttonTypes[id] == buttonType && !m_buttonArray[id].m_bGreyOut) {
            return id;
        }
    }
    return -1;
}

// 0x588FF0
BOOL CInfButtonArray::ResetState()
{
    // TODO: Incomplete.

    return TRUE;
}

// 0x589100
void CInfButtonArray::UpdateState()
{
    SetState(m_nState, 0);
}

// 0x589110
BOOL CInfButtonArray::SetState(INT nState, int a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x58A340
void CInfButtonArray::UpdateButtons()
{
    // TODO: Incomplete.
}

// 0x452C50
void CInfButtonArray::SetSelectedButton(INT nSelectedButton)
{
    m_nSelectedButton = nSelectedButton;
}

// 0x58FF20
void CInfButtonArray::OnLButtonPressed(int buttonID)
{
    // TODO: Incomplete.
}

// 0x594720
void CInfButtonArray::OnRButtonPressed(int buttonID)
{
    // TODO: Incomplete.
}

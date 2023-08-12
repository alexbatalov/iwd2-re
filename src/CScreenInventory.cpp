#include "CScreenInventory.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CUIControlButton.h"
#include "CUIControlLabel.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x855050
const DWORD CScreenInventory::SLOT_ID[] = {
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    5,
    6,
    7,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    68,
    69,
    70,
    71,
    72,
    81,
    22,
    24,
    25,
    23,
    21,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
};

// 0x855124
const INT CScreenInventory::NUM_SLOTS = 53;

// 0x855128
const USHORT PERSONAL_INVENTORY_SIZE = 24;

// 0x85512C
const LONG RANGE_SWAPITEM = 0x40000;

// 0x8F3FC0
const CString CScreenInventory::OPTION_PAUSE_WARNING("Inventory Pause Warning");

// 0x623EA0
CScreenInventory::CScreenInventory()
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenInventory::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x624D00
void CScreenInventory::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x699600
SHORT CScreenInventory::GetNumVirtualKeys()
{
    return CSCREENINVENTORY_VIRTUAL_KEYS;
}

// 0x624D10
CKeyInfo* CScreenInventory::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x624D20
BYTE* CScreenInventory::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x624D50
CScreenInventory::~CScreenInventory()
{
    if (m_pTempItem) {
        delete m_pTempItem;
        m_pTempItem = NULL;
    }
}

// 0x624F70
void CScreenInventory::EngineActivated()
{
    // TODO: Incomplete.
}

// 0x6252D0
void CScreenInventory::EngineDeactivated()
{
    // TODO: Incomplete.
}

// 0x5D72C0
void CScreenInventory::EngineDestroyed()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x625490
void CScreenInventory::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUIINV"), g_pBaldurChitin->field_4A28);

    CPoint pt;
    if (g_pBaldurChitin->field_4A28) {
        pt.x = CVideo::SCREENWIDTH / 2 - CBaldurChitin::DEFAULT_SCREEN_WIDTH;
        pt.y = CVideo::SCREENHEIGHT / 2 - CBaldurChitin::DEFAULT_SCREEN_HEIGHT;
    } else {
        pt.x = (CVideo::SCREENWIDTH - CBaldurChitin::DEFAULT_SCREEN_WIDTH) / 2;
        pt.y = (CVideo::SCREENHEIGHT - CBaldurChitin::DEFAULT_SCREEN_HEIGHT) / 2;
    }

    m_cUIManager.ShiftPanels(pt);

    for (int index = 0; index < 4; index++) {
        m_cUIManager.AddPanel(&(g_pBaldurChitin->field_49B4[index]));
    }

    if (m_pTempItem != NULL) {
        delete m_pTempItem;
        m_pTempItem = NULL;
    }

    m_pCurrentScrollBar = NULL;
    m_nSelectedCharacter = 0;
    m_pTempItem = NULL;
    field_114 = 0;
    field_118 = -1;
    field_48C = -1;
    field_488 = -1;
    field_11E = 0;
    field_11F = 0;
    field_4AC = 0;
    field_4EC = 0;
    field_52C = 0;
    field_510 = -1;
    field_514 = -1;
    field_524 = 0;
    field_51C = 0;
    field_520 = 0;
    field_528 = 0;

    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(6)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(9)->SetActive(FALSE);
    m_cUIManager.GetPanel(50)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);

    CUIPanel* pPanel = m_cUIManager.GetPanel(0);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 632
    UTIL_ASSERT(pPanel != NULL);

    CUIControlBase* pControl;

    pControl = pPanel->GetControl(0x10000038);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 636
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17183, -1, -1); // "Armor Class"

    pControl = pPanel->GetControl(0x10000039);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 640
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17184, -1, -1); // "Current Hit Points"

    pControl = pPanel->GetControl(0x1000003A);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 644
    UTIL_ASSERT(pControl != NULL);

    pControl->SetToolTipStrRef(17378, -1, -1); // "Maximum Hit Points"

    m_nUseButtonMode = -1;
    field_508 = -1;
    field_510 = -1;
    field_514 = -1;
    field_52C = GetPrivateProfileIntA("Game Options",
        OPTION_PAUSE_WARNING,
        0,
        g_pBaldurChitin->GetIniFileName());
}

// 0x6257C0
void CScreenInventory::OnKeyDown(SHORT nKeysFlags)
{
    // TODO: Incomplete.
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseLButton()
{
    return TRUE;
}

// 0x625CD0
void CScreenInventory::OnLButtonDblClk(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonDblClk(pt);
}

// 0x625D00
void CScreenInventory::OnLButtonDown(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonDown(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 1;
}

// 0x625D40
void CScreenInventory::OnLButtonUp(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnLButtonUp(pt);
    g_pBaldurChitin->GetObjectCursor()->m_nState = 0;
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseMove()
{
    return TRUE;
}

// 0x625D80
void CScreenInventory::OnMouseMove(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnMouseMove(pt);
}

// 0x49FC40
BOOL CScreenInventory::CheckMouseRButton()
{
    return TRUE;
}

// 0x625DB0
void CScreenInventory::OnRButtonDown(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnRButtonDown(pt);
}

// 0x625DE0
void CScreenInventory::OnRButtonUp(CPoint pt)
{
    m_cLastMousePosition = pt;
    m_cUIManager.OnRButtonUp(pt);
}

// 0x625E10
void CScreenInventory::TimerAsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x626050
INT CScreenInventory::GetSlotByPosition(CPoint pt)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(2);
    CUIControlBase* pControl;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1151
    UTIL_ASSERT(pPanel != NULL);

    for (INT nIndex = 0; nIndex < NUM_SLOTS; nIndex++) {
        pControl = pPanel->GetControl(SLOT_ID[nIndex]);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1158
        UTIL_ASSERT(pControl != NULL);

        if (pControl->IsOver(pt)) {
            return pControl->m_nID;
        }
    }

    pControl = pPanel->GetControl(50);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1167
    UTIL_ASSERT(pControl != NULL);

    if (pControl->IsOver(pt)) {
        return pControl->m_nID;
    }

    return -1;
}

// 0x626140
INT CScreenInventory::GetPortraitByPosition(CPoint pt)
{
    CUIPanel* pPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1200
    UTIL_ASSERT(pPanel != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1202
    UTIL_ASSERT(pGame != NULL);

    for (INT nIndex = 0; nIndex < pGame->GetNumCharacters(); nIndex++) {
        CUIControlBase* pControl = pPanel->GetControl(nIndex);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 1210
        UTIL_ASSERT(pControl != NULL);

        if (pControl->IsOver(pt)) {
            return pControl->m_nID;
        }
    }

    return -1;
}

// 0x626230
void CScreenInventory::TimerSynchronousUpdate()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    pGame->SynchronousUpdate();

    if (m_lPopupStack.GetCount() > 0 && m_cUIManager.field_2E == 1) {
        SHORT nPortrait;

        for (nPortrait = 0; nPortrait <= 5; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }

        for (nPortrait = 50; nPortrait <= 55; nPortrait++) {
            pGame->sub_5AF420(nPortrait, 1);
        }
    }

    m_cUIManager.Render();
    pVidMode->Flip(TRUE);

    if (g_pBaldurChitin->pActiveEngine == g_pBaldurChitin->m_pEngineInventory) {
        CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
        renderLock.Lock(INFINITE);

        if (g_pBaldurChitin->m_pEngineInventory->GetTopPopup() == NULL) {
            CUIPanel* pPanel = m_cUIManager.GetPanel(2);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1272
            UTIL_ASSERT(pPanel != NULL);

            CUIControlBase* pControl = pPanel->GetControl(50);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
            // __LINE__: 1277
            UTIL_ASSERT(pControl != NULL);

            pControl->InvalidateRect();
        }

        renderLock.Unlock();
    }
}

// 0x626390
void CScreenInventory::OnPortraitLClick(DWORD nPortrait)
{
    // TODO: Incomplete.
}

// 0x6265E0
void CScreenInventory::SetErrorString(STRREF strError, COLORREF rgb)
{
    STR_RES strRes;

    if (g_pBaldurChitin->pActiveEngine == g_pBaldurChitin->m_pEngineInventory) {
        CUIPanel* pPanel = m_cUIManager.GetPanel(2);
        CUIControlLabel* pLabel = static_cast<CUIControlLabel*>(pPanel->GetControl(0x1000003F));
        pLabel->SetForegroundColor(rgb);

        g_pBaldurChitin->m_cTlkTable.Fetch(strError, strRes);
        pLabel->SetText(strRes.szText);

        strRes.cSound.SetChannel(0, 0);
        strRes.cSound.SetFireForget(TRUE);
        strRes.cSound.Play(FALSE);
    }
}

// 0x6266E0
void CScreenInventory::UpdatePersonalItemStatus()
{
    // TODO: Incomplete.
}

// 0x626780
void CScreenInventory::UpdateContainerStatus()
{
    // TODO: Incomplete.
}

// 0x626880
void CScreenInventory::UpdateCursorShape()
{
    CInfCursor* pCursor = g_pBaldurChitin->GetObjectCursor();
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    if (pGame->m_tempCursor != 4) {
        pCursor->SetCursor(pGame->m_tempCursor, FALSE);
        return;
    }

    if (m_pTempItem == NULL) {
        pCursor->SetCursor(0, FALSE);
        return;
    }

    if (GetTopPopup() != NULL) {
        pCursor->SetCursor(0, FALSE);
        return;
    }

    INT nPointerNumber;
    if (m_pTempItem->GetMaxStackable() > 1) {
        nPointerNumber = m_pTempItem->GetUsageCount(0);
    } else {
        nPointerNumber = 0;
    }

    CResRef iconResRef = m_pTempItem->GetItemIcon();
    pCursor->SetCustomCursor(iconResRef, FALSE, nPointerNumber);
}

// 0x626940
void CScreenInventory::FetchGroundPile()
{
    // TODO: Incomplete.
}

// 0x626AE0
void CScreenInventory::FlushGroundPiles()
{
    // TODO: Incomplete.
}

// 0x626C70
void CScreenInventory::EnableMainPanel()
{
    // TODO: Incomplete.
}

// 0x626DD0
void CScreenInventory::UpdateMainPanel(BOOL a1)
{
    // TODO: Incomplete.
}

// 0x627560
void CScreenInventory::ResetPopupPanel()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
CUIPanel* CScreenInventory::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x627700
void CScreenInventory::SummonPopup(DWORD dwPopupId)
{
    // TODO: Incomplete.
}

// 0x627990
void CScreenInventory::DismissPopup()
{
    // TODO: Incomplete.
}

// 0x627C20
void CScreenInventory::ResetHistoryPanel()
{
    // TODO: Incomplete.
}

// 0x627F20
void CScreenInventory::ResetAbilitiesPanel()
{
    // TODO: Incomplete.
}

// 0x628200
void CScreenInventory::SelectItemAbility()
{
    // TODO: Incomplete.
}

// 0x6285B0
void CScreenInventory::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x628D20
void CScreenInventory::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x628E70
void CScreenInventory::ResetErrorPanel()
{
    // TODO: Incomplete.
}

// 0x6290C0
void CScreenInventory::UpdateErrorPanel(CUIPanel* pPanel)
{
    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3191
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(IsErrorButtonClickable(nButton));
    }
}

// 0x629120
void CScreenInventory::OnRestButtonClick()
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3222
    UTIL_ASSERT(pGame != NULL);

    CSingleLock renderLock(&(m_cUIManager.field_36), FALSE);
    renderLock.Lock(INFINITE);

    STRREF strError;
    if (pGame->CanRestParty(strError, 0, 0, 0)) {
        m_nErrorState = 1;
        m_strErrorText = 15358;
        m_strErrorButtonText[0] = 17199;
        m_strErrorButtonText[1] = 11596;
        m_strErrorButtonText[2] = 13727;
        SummonPopup(50);
    } else {
        m_nErrorState = 0;
        m_strErrorText = strError;
        m_strErrorButtonText[0] = 11973;
        SummonPopup(7);
    }

    renderLock.Unlock();
}

// 0x629230
void CScreenInventory::IsAbilitiesButtonActive()
{
    // TODO: Incomplete.
}

// 0x6294D0
void CScreenInventory::SetUseButtonMode(INT nMode)
{
    if (m_nUseButtonMode == nMode) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(5);
    if (pPanel == NULL) {
        return;
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(9));
    if (pButton == NULL) {
        return;
    }

    m_nUseButtonMode = nMode;
    switch (nMode) {
    case 0:
        pButton->SetText(FetchString(19392)); // "Drink Potion"
        break;
    case 1:
        pButton->SetText(FetchString(17104)); // "Write Magic"
        break;
    case 2:
        pButton->SetText(FetchString(10874)); // "eat berries"
        break;
    case 3:
        pButton->SetText(FetchString(24891)); // "Open Container"
        break;
    case 4:
        pButton->SetText(FetchString(32477)); // "Eat Rations"
        break;
    }
}

// 0x629660
void CScreenInventory::SetAbilitiesButtonMode()
{
    // TODO: Incomplete.
}

// 0x629740
void CScreenInventory::IsUseButtonActive()
{
    // TODO: Incomplete.
}

// 0x629B90
void CScreenInventory::OnUseButtonClick()
{
    // TODO: Incomplete.
}

// 0x629DB0
void CScreenInventory::OnAbilitiesButtonClick()
{
    // TODO: Incomplete.
}

// 0x629F20
void CScreenInventory::CheckEnableButtons()
{
    // TODO: Incomplete.
}

// 0x62A060
BOOL CScreenInventory::IsErrorButtonClickable(INT nButton)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x62A2F0
void CScreenInventory::OnErrorButtonClick()
{
    // TODO: Incomplete.
}

// 0x62A4B0
void CScreenInventory::IdentifyWithSpell()
{
    // TODO: Incomplete.
}

// 0x62AE70
void CScreenInventory::IdentifyWithScroll()
{
    // TODO: Incomplete.
}

// 0x62B0B0
void CScreenInventory::CopySpell()
{
    // TODO: Incomplete.
}

// 0x62B4C0
void CScreenInventory::DrinkPotion()
{
    // TODO: Incomplete.
}

// 0x62B7D0
void CScreenInventory::PlaySwapSound()
{
    // TODO: Incomplete.
}

// 0x62C4E0
void CScreenInventory::CancelEngine()
{
    // TODO: Incomplete.
}

// 0x62C900
void CScreenInventory::UpdateCharacterStatus(LONG nCharacterId)
{
    CBaldurEngine::UpdateCharacterStatus(nCharacterId);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    if (pGame != NULL) {
        SHORT nPortrait = GetSelectedCharacter();
        if (pGame->GetCharacterId(nPortrait) == nCharacterId) {
            if (GetTopPopup() == NULL) {
                UpdateMainPanel(FALSE);
            }
        }
    }
}

// 0x62C970
void CScreenInventory::CheckMultiPlayerViewable()
{
    // TODO: Incomplete.
}

// 0x62CAA0
void CScreenInventory::UnPauseGame()
{
    // TOOD: Incomplete.
}

// 0x62CC50
void CScreenInventory::UpdateHelp()
{
    // TODO: Incomplete.
}

// 0x62CD60
void CScreenInventory::IsCharacterInRange()
{
    // TODO: Incomplete.
}

// 0x62CF50
void CScreenInventory::UpdatePartyGoldStatus()
{
    // TODO: Incomplete.
}

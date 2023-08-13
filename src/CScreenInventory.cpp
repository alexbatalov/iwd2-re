#include "CScreenInventory.h"

#include "CBaldurChitin.h"
#include "CGameSprite.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CItem.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlTextDisplay.h"
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
    m_bPauseWarningDisplayed = FALSE;
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
    m_nAbilitiesButtonMode = -1;
    field_510 = -1;
    field_514 = -1;
    m_bPauseWarningDisplayed = GetPrivateProfileIntA("Game Options",
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
void CScreenInventory::UpdatePersonalItemStatus(LONG nCharacterId)
{
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();
    SHORT nPortrait = GetSelectedCharacter();
    if (pGame->GetCharacterId(nPortrait) == nCharacterId) {
        if (GetTopPopup() != NULL) {
            switch (GetTopPopup()->m_nID) {
            case 4:
                UpdateRequesterPanel();
                break;
            case 5:
                UpdateHistoryPanel(0);
                break;
            case 6:
                UpdateAbilitiesPanel();
                break;
            }
        } else {
            UpdateMainPanel(FALSE);
            m_cUIManager.GetPanel(2)->InvalidateRect(NULL);
        }
    }
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
void CScreenInventory::EnableMainPanel(BOOL bEnable)
{
    CUIPanel* pMainPanel = m_cUIManager.GetPanel(2);
    CUIPanel* pLeftPanel = m_cUIManager.GetPanel(0);
    CUIPanel* pRightPanel = m_cUIManager.GetPanel(1);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1704
    UTIL_ASSERT(pMainPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1705
    UTIL_ASSERT(pLeftPanel != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 1706
    UTIL_ASSERT(pRightPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }

    pMainPanel->SetEnabled(bEnable);
    pLeftPanel->SetEnabled(bEnable);
    pRightPanel->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    CheckEnablePortaits(1);
    CheckEnableLeftPanel();
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
void CScreenInventory::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 7:
        m_nNumErrorButtons = 1;
        break;
    case 8:
        m_nNumErrorButtons = 2;
        break;
    case 9:
    case 50:
        m_nNumErrorButtons = 3;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3137
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(m_strErrorText, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 3150
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton + 1));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3159
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
        // __LINE__: 3998
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENINVENTORY_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
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
void CScreenInventory::SetAbilitiesButtonMode(INT nMode)
{
    if (m_nAbilitiesButtonMode == nMode) {
        return;
    }

    CUIPanel* pPanel = m_cUIManager.GetPanel(5);
    if (pPanel == NULL) {
        return;
    }

    CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(8));
    if (pButton == NULL) {
        return;
    }

    m_nAbilitiesButtonMode = nMode;
    switch (nMode) {
    case 0:
        pButton->SetText(FetchString(11960)); // "Abilities"
        break;
    case 1:
        pButton->SetText(FetchString(14133)); // "Identify"
        break;
    }
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
void CScreenInventory::OnErrorButtonClick(INT nButton)
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
void CScreenInventory::PlaySwapSound(CItem* pOldItem, CItem* pNewItem)
{
    WORD animationType;

    if (pOldItem != NULL) {
        switch (pOldItem->GetItemType()) {
        case 1:
            PlayGUISound(RESREF_SOUND_NECK2);
            break;
        case 3:
            PlayGUISound(RESREF_SOUND_BELT2);
            break;
        case 4:
            PlayGUISound(RESREF_SOUND_BOOT2);
            break;
        case 5:
            PlayGUISound(RESREF_SOUND_ARRW2);
            break;
        case 6:
            PlayGUISound(RESREF_SOUND_GLOVE2);
            break;
        case 7:
            PlayGUISound(RESREF_SOUND_HELM2);
            break;
        case 8:
            PlayGUISound(RESREF_SOUND_KEY2);
            break;
        case 9:
            PlayGUISound(RESREF_SOUND_POTN2);
            break;
        case 10:
            PlayGUISound(RESREF_SOUND_RING2);
            break;
        case 11:
            PlayGUISound(RESREF_SOUND_SCROL2);
            break;
        case 14:
            PlayGUISound(RESREF_SOUND_BULLT2);
            break;
        case 15:
            PlayGUISound(RESREF_SOUND_BOW2);
            break;
        case 16:
            PlayGUISound(RESREF_SOUND_DAGGR2);
            break;
        case 17:
            PlayGUISound(RESREF_SOUND_MACE2);
            break;
        case 18:
            PlayGUISound(RESREF_SOUND_SLING2);
            break;
        case 19:
            PlayGUISound(RESREF_SOUND_SMSWD2);
            break;
        case 20:
        case 57:
        case 69:
            PlayGUISound(RESREF_SOUND_LGSWD2);
            break;
        case 21:
            PlayGUISound(RESREF_SOUND_HAMMR2);
            break;
        case 22:
            PlayGUISound(RESREF_SOUND_MSTAR2);
            break;
        case 23:
            PlayGUISound(RESREF_SOUND_FLAIL2);
            break;
        case 24:
            PlayGUISound(RESREF_SOUND_DART2);
            break;
        case 25:
            PlayGUISound(RESREF_SOUND_AXE2);
            break;
        case 26:
            PlayGUISound(RESREF_SOUND_STAFF2);
            break;
        case 27:
            PlayGUISound(RESREF_SOUND_CROSB2);
            break;
        case 29:
            PlayGUISound(RESREF_SOUND_SPEAR2);
            break;
        case 30:
            PlayGUISound(RESREF_SOUND_HALB2);
            break;
        case 31:
            PlayGUISound(RESREF_SOUND_BOLT2);
            break;
        case 32:
            PlayGUISound(RESREF_SOUND_CLOAK2);
            break;
        case 33:
            PlayGUISound(RESREF_SOUND_GOLD2);
            break;
        case 34:
            PlayGUISound(RESREF_SOUND_GEM2);
            break;
        case 35:
            PlayGUISound(RESREF_SOUND_WAND2);
            break;
        case 36:
            PlayGUISound(RESREF_SOUND_BARM2);
            break;
        case 37:
            PlayGUISound(RESREF_SOUND_BSHD2);
            break;
        case 38:
            PlayGUISound(RESREF_SOUND_BWPN2);
            break;
        case 40:
            PlayGUISound(RESREF_SOUND_BROKN2);
            break;
        case 41:
            PlayGUISound(RESREF_SOUND_BUCKR2);
            break;
        case 42:
            PlayGUISound(RESREF_SOUND_CAND2);
            break;
        case 43:
            PlayGUISound(RESREF_SOUND_CHILD2);
            break;
        case 44:
            PlayGUISound(RESREF_SOUND_CLUB2);
            break;
        case 45:
            PlayGUISound(RESREF_SOUND_FEM2);
            break;
        case 46:
            PlayGUISound(RESREF_SOUND_KEYS2);
            break;
        case 47:
            PlayGUISound(RESREF_SOUND_LGSLD2);
            break;
        case 48:
            PlayGUISound(RESREF_SOUND_MALE2);
            break;
        case 49:
            PlayGUISound(RESREF_SOUND_MDSLD2);
            break;
        case 50:
            PlayGUISound(RESREF_SOUND_PAPR2);
            break;
        case 51:
            PlayGUISound(RESREF_SOUND_ROD2);
            break;
        case 52:
            PlayGUISound(RESREF_SOUND_SKULL2);
            break;
        case 53:
            PlayGUISound(RESREF_SOUND_SMSLD2);
            break;
        case 54:
            PlayGUISound(RESREF_SOUND_SPIDR2);
            break;
        case 55:
            PlayGUISound(RESREF_SOUND_TELE2);
            break;
        case 56:
            PlayGUISound(RESREF_SOUND_WINE2);
            break;
        case 59:
            PlayGUISound(RESREF_SOUND_8CB1D0);
            break;
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
            animationType = pOldItem->GetAnimationType();
            switch (animationType & 0xFF) {
            case 'A':
            case 'a':
                switch ((animationType >> 8) & 0xFF) {
                case '2':
                    PlayGUISound(RESREF_SOUND_LETHR2);
                    break;
                case '3':
                    PlayGUISound(RESREF_SOUND_CHAIN2);
                    break;
                case '4':
                    PlayGUISound(RESREF_SOUND_PLATE2);
                    break;
                default:
                    PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
                    break;
                }
                break;
            case 'W':
            case 'w':
                PlayGUISound(RESREF_SOUND_CLOAK2);
                break;
            default:
                PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
                break;
            }
            break;
        case 70:
            PlayGUISound(RESREF_SOUND_8CAD40);
            break;
        case 71:
            PlayGUISound(RESREF_SOUND_8CD260);
            break;
        case 72:
            PlayGUISound(RESREF_SOUND_8C8C80);
            break;
        case 73:
            PlayGUISound(RESREF_SOUND_8CD390);
            break;
        default:
            PlayGUISound(RESREF_SOUND_EQUIP_DROP_GENERIC);
            break;
        }
    } else if (pNewItem != NULL) {
        switch (pNewItem->GetItemType()) {
        case 1:
            PlayGUISound(RESREF_SOUND_NECK1);
            break;
        case 3:
            PlayGUISound(RESREF_SOUND_BELT1);
            break;
        case 4:
            PlayGUISound(RESREF_SOUND_BOOT1);
            break;
        case 5:
            PlayGUISound(RESREF_SOUND_ARRW1);
            break;
        case 6:
            PlayGUISound(RESREF_SOUND_GLOVE1);
            break;
        case 7:
            PlayGUISound(RESREF_SOUND_HELM1);
            break;
        case 8:
            PlayGUISound(RESREF_SOUND_KEY1);
            break;
        case 9:
            PlayGUISound(RESREF_SOUND_POTN1);
            break;
        case 10:
            PlayGUISound(RESREF_SOUND_RING1);
            break;
        case 11:
            PlayGUISound(RESREF_SOUND_SCROL1);
            break;
        case 14:
            PlayGUISound(RESREF_SOUND_BULLT1);
            break;
        case 15:
            PlayGUISound(RESREF_SOUND_BOW1);
            break;
        case 16:
            PlayGUISound(RESREF_SOUND_DAGGR1);
            break;
        case 17:
            PlayGUISound(RESREF_SOUND_MACE1);
            break;
        case 18:
            PlayGUISound(RESREF_SOUND_SLING1);
            break;
        case 19:
            PlayGUISound(RESREF_SOUND_SMSWD1);
            break;
        case 20:
        case 57:
        case 69:
            PlayGUISound(RESREF_SOUND_LGSWD1);
            break;
        case 21:
            PlayGUISound(RESREF_SOUND_HAMMR1);
            break;
        case 22:
            PlayGUISound(RESREF_SOUND_MSTAR1);
            break;
        case 23:
            PlayGUISound(RESREF_SOUND_FLAIL1);
            break;
        case 24:
            PlayGUISound(RESREF_SOUND_DART1);
            break;
        case 25:
            PlayGUISound(RESREF_SOUND_AXE1);
            break;
        case 26:
            PlayGUISound(RESREF_SOUND_STAFF1);
            break;
        case 27:
            PlayGUISound(RESREF_SOUND_CROSB1);
            break;
        case 29:
            PlayGUISound(RESREF_SOUND_SPEAR1);
            break;
        case 30:
            PlayGUISound(RESREF_SOUND_HALB1);
            break;
        case 31:
            PlayGUISound(RESREF_SOUND_BOLT1);
            break;
        case 32:
            PlayGUISound(RESREF_SOUND_CLOAK1);
            break;
        case 33:
            PlayGUISound(RESREF_SOUND_GOLD1);
            break;
        case 34:
            PlayGUISound(RESREF_SOUND_GEM1);
            break;
        case 35:
            PlayGUISound(RESREF_SOUND_WAND1);
            break;
        case 36:
            PlayGUISound(RESREF_SOUND_BARM1);
            break;
        case 37:
            PlayGUISound(RESREF_SOUND_BSHD1);
            break;
        case 38:
            PlayGUISound(RESREF_SOUND_BWPN1);
            break;
        case 40:
            PlayGUISound(RESREF_SOUND_BROKN1);
            break;
        case 41:
            PlayGUISound(RESREF_SOUND_BUCKR1);
            break;
        case 42:
            PlayGUISound(RESREF_SOUND_CAND1);
            break;
        case 43:
            PlayGUISound(RESREF_SOUND_CHILD1);
            break;
        case 44:
            PlayGUISound(RESREF_SOUND_CLUB1);
            break;
        case 45:
            PlayGUISound(RESREF_SOUND_FEM1);
            break;
        case 46:
            PlayGUISound(RESREF_SOUND_KEYS1);
            break;
        case 47:
            PlayGUISound(RESREF_SOUND_LGSLD1);
            break;
        case 48:
            PlayGUISound(RESREF_SOUND_MALE1);
            break;
        case 49:
            PlayGUISound(RESREF_SOUND_MDSLD1);
            break;
        case 50:
            PlayGUISound(RESREF_SOUND_PAPR1);
            break;
        case 51:
            PlayGUISound(RESREF_SOUND_ROD1);
            break;
        case 52:
            PlayGUISound(RESREF_SOUND_SKULL1);
            break;
        case 53:
            PlayGUISound(RESREF_SOUND_SMSLD1);
            break;
        case 54:
            PlayGUISound(RESREF_SOUND_SPIDR1);
            break;
        case 55:
            PlayGUISound(RESREF_SOUND_TELE1);
            break;
        case 56:
            PlayGUISound(RESREF_SOUND_WINE1);
            break;
        case 59:
            PlayGUISound(RESREF_SOUND_8CF680);
            break;
        case 60:
        case 61:
        case 62:
        case 63:
        case 64:
        case 65:
        case 66:
        case 67:
        case 68:
            animationType = pNewItem->GetAnimationType();
            switch (animationType & 0xFF) {
            case 'A':
            case 'a':
                switch ((animationType >> 8) & 0xFF) {
                case '2':
                    PlayGUISound(RESREF_SOUND_LETHR1);
                    break;
                case '3':
                    PlayGUISound(RESREF_SOUND_CHAIN1);
                    break;
                case '4':
                    PlayGUISound(RESREF_SOUND_PLATE1);
                    break;
                default:
                    PlayGUISound(RESREF_SOUND_EQUIP_TAKE_GENERIC);
                    break;
                }
                break;
            case 'W':
            case 'w':
                PlayGUISound(RESREF_SOUND_CLOAK1);
                break;
            default:
                PlayGUISound(RESREF_SOUND_EQUIP_TAKE_GENERIC);
                break;
            }
            break;
        case 70:
            PlayGUISound(RESREF_SOUND_8CF698);
            break;
        case 71:
            PlayGUISound(RESREF_SOUND_8CF628);
            break;
        case 72:
            PlayGUISound(RESREF_SOUND_8CAD98);
            break;
        case 73:
            PlayGUISound(RESREF_SOUND_8CB1B0);
            break;
        }
    }
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
    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5623
    UTIL_ASSERT(pGame != NULL);

    m_bMultiPlayerViewable = TRUE;

    LONG nCharacterId = pGame->GetCharacterId(m_nSelectedCharacter);

    CGameSprite* pSprite;

    BYTE rc;
    do {
        rc = pGame->GetObjectArray()->GetShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            reinterpret_cast<CGameObject**>(&pSprite),
            INFINITE);
    } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

    if (rc == CGameObjectArray::SUCCESS) {
        if (pSprite->Orderable(1)) {
            if (g_pChitin->cNetwork.GetServiceProvider() == CNetwork::SERV_PROV_NULL
                || g_pChitin->cNetwork.m_idLocalPlayer == pSprite->m_remotePlayerID) {
                m_bMultiPlayerViewable = TRUE;
            } else {
                if (g_pChitin->cNetwork.GetSessionOpen()) {
                    m_bMultiPlayerViewable = g_pChitin->cNetwork.GetSessionHosting()
                        || pGame->m_singlePlayerPermissions.GetSinglePermission(CGamePermission::LEADER);
                }
            }
        } else {
            m_bMultiPlayerViewable = FALSE;
        }

        pGame->GetObjectArray()->ReleaseShare(nCharacterId,
            CGameObjectArray::THREAD_ASYNCH,
            INFINITE);
    }
}

// 0x62CAA0
void CScreenInventory::UnPauseGame()
{
    CSingleLock renderLock(&(GetManager()->field_36), FALSE);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5754
    UTIL_ASSERT(pGame != NULL);

    if (g_pChitin->cNetwork.GetSessionOpen() != TRUE) {
        if (g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
            if (pGame->m_singlePlayerPermissions.m_bPermissions[CGamePermission::PAUSING]) {
                if (m_bPauseWarningDisplayed) {
                    SetErrorString(19381, RGB(255, 0, 0));
                } else {
                    renderLock.Lock(INFINITE);

                    m_nErrorState = 2;
                    m_strErrorText = 19381;
                    m_strErrorButtonText[0] = 11973;
                    SummonPopup(7);

                    renderLock.Unlock();

                    m_bPauseWarningDisplayed = TRUE;

                    WritePrivateProfileStringA("Game Options",
                        OPTION_PAUSE_WARNING,
                        "1",
                        g_pBaldurChitin->GetIniFileName());
                }

                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            } else {
                renderLock.Lock(INFINITE);

                m_nErrorState = 5;
                m_strErrorText = 10920;
                m_strErrorButtonText[0] = 11973;
                SummonPopup(7);

                renderLock.Unlock();
            }
        } else {
            pGame->GetWorldTimer()->StartTime();
        }
    }
}

// 0x62CC50
void CScreenInventory::UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId)
{
    STR_RES strRes;

    CUIPanel* pPanel = m_cUIManager.GetPanel(dwPanelId);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5842
    UTIL_ASSERT(pPanel != NULL);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(dwTextId));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 5844
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();

    g_pBaldurChitin->m_cTlkTable.Fetch(dwStrId, strRes);
    UpdateText(pText, "%s", strRes.szText);
}

// 0x62CD60
void CScreenInventory::IsCharacterInRange()
{
    // TODO: Incomplete.
}

// 0x62CF50
void CScreenInventory::UpdatePartyGoldStatus()
{
    if (GetTopPopup() == NULL) {
        UpdateMainPanel(FALSE);
    }
}

// 0x631640
void CScreenInventory::UpdateRequesterPanel()
{
    // TODO: Incomplete.
}

// 0x631790
void CScreenInventory::UpdateHistoryPanel(BOOL a1)
{
    // TODO: Incomplete.
}

// 0x631A20
void CScreenInventory::UpdateAbilitiesPanel()
{
    // TODO: Incomplete.
}

// -----------------------------------------------------------------------------

// 0x634E70
CUIControlButtonInventoryHistoryUse::CUIControlButtonInventoryHistoryUse(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x634EC0
CUIControlButtonInventoryHistoryUse::~CUIControlButtonInventoryHistoryUse()
{
}

// 0x634F60
void CUIControlButtonInventoryHistoryUse::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11676
    UTIL_ASSERT(pInventory != NULL);

    CSingleLock renderLock(&(pInventory->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pInventory->OnUseButtonClick();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x635270
CUIControlButtonInventoryError::CUIControlButtonInventoryError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x6352C0
CUIControlButtonInventoryError::~CUIControlButtonInventoryError()
{
}

// 0x635360
void CUIControlButtonInventoryError::OnLButtonClick(CPoint pt)
{
    CScreenInventory* pInventory = g_pBaldurChitin->m_pEngineInventory;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenInventory.cpp
    // __LINE__: 11832
    UTIL_ASSERT(pInventory != NULL);

    pInventory->OnErrorButtonClick(m_nID);
}

#include "CScreenStore.h"

#include "CBaldurChitin.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CScreenInventory.h"
#include "CScreenWorld.h"
#include "CStore.h"
#include "CUIControlEdit.h"
#include "CUIControlTextDisplay.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x8F8194
const CString CScreenStore::TOKEN_HP("HP");

// 0x8F8158
const CString CScreenStore::TOKEN_ITEMNAME("ITEMNAME");

// 0x8F8188
const CString CScreenStore::TOKEN_ITEMCOST("ITEMCOST");

// 0x8F8168
CRITICAL_SECTION CScreenStore::m_critSect;

// 0x8F8198
BOOLEAN CScreenStore::m_bInCancelEngine;

// -----------------------------------------------------------------------------

// 0x672360
CScreenStoreItem::CScreenStoreItem()
{
    m_cResSpell = "";
    m_pItem = NULL;
    m_bEnabled = FALSE;
    m_bSelected = FALSE;
    m_nValue = 0;
    m_nSingleValue = 0;
    m_nStoreCount = 1;
    m_nMaxCount = 1;
    m_nCount = 1;
    m_nSlot = -1;
}

// -----------------------------------------------------------------------------

// 0x6709E0
CScreenStore::CScreenStore()
{
    // TODO: Incomplete.

    InitializeCriticalSection(&m_critSect);
}

// 0x49FC40
BOOL CScreenStore::CheckSystemKeyShift()
{
    return TRUE;
}

// 0x671790
void CScreenStore::SetSystemKeyShift(BOOL bValue)
{
    m_bShiftKeyDown = bValue;
}

// 0x6717A0
BOOL CScreenStore::GetShiftKey()
{
    return m_bShiftKeyDown;
}

// 0x49FC40
BOOL CScreenStore::CheckSystemKeyCapsLock()
{
    return TRUE;
}

// 0x6717B0
void CScreenStore::SetSystemKeyCapsLock(BOOL bValue)
{
    m_bCapsLockKeyOn = bValue;
}

// 0x6717C0
BOOL CScreenStore::GetCapsLockKey()
{
    return m_bCapsLockKeyOn;
}

// 0x49FC40
BOOL CScreenStore::CheckSystemKeyCtrl()
{
    return TRUE;
}

// 0x6717D0
void CScreenStore::SetSystemKeyCtrl(BOOLEAN bValue)
{
    m_bCtrlKeyDown = bValue;
}

// 0x6717E0
BOOL CScreenStore::GetCtrlKey()
{
    return m_bCtrlKeyDown;
}

// 0x6717F0
SHORT CScreenStore::GetNumVirtualKeys()
{
    return CSCREENSTORE_VIRTUAL_KEYS;
}

// 0x699610
CKeyInfo* CScreenStore::GetVirtualKeys()
{
    return m_pVirtualKeys;
}

// 0x671800
BYTE* CScreenStore::GetVirtualKeysFlags()
{
    return m_pVirtualKeysFlags;
}

// 0x671830
CScreenStore::~CScreenStore()
{
    // TODO: Incomplete.

    DeleteCriticalSection(&m_critSect);
}

// 0x671A20
void CScreenStore::EngineActivated()
{
    // TODO: Incomplete.
}

// 0x671CC0
void CScreenStore::EngineDeactivated()
{
    if (CChitin::byte_8FB950) {
        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
            && g_pChitin->cNetwork.GetSessionHosting() == TRUE
            && g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
            if (!g_pBaldurChitin->m_pEngineWorld->m_bPaused) {
                g_pBaldurChitin->m_pEngineWorld->TogglePauseGame(0, 1, 0);
            }
        }
    }

    m_preLoadFontRealms.Unload();
    m_preLoadFontStnSml.Unload();
    m_preLoadFontTool.Unload();

    // NOTE: Uninline.
    m_cUIManager.KillCapture();
}

// 0x671D60
void CScreenStore::EngineGameInit()
{
    m_cUIManager.fInit(this, CResRef("GUISTORE"), g_pBaldurChitin->field_4A28);

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

    m_nSelectedCharacter = 0;
    m_pCurrentScrollBar = NULL;
    m_pMainPanel = NULL;
    m_nTopGroupItem = 0;
    m_nTopStoreItem = 0;
    m_nTopSpellItem = 0;
    m_nTopDrinkItem = 0;
    m_nTopIdentifyItem = 0;
    field_4F0 = 0;
    field_4F4 = 0;
    field_4F8 = 0;
    field_4FC = 0;
    m_pStore = 0;
    m_pBag = NULL;
    field_580 = -1;
    field_584 = -1;
    m_pButtonBar = NULL;
    m_bStoreStarted = FALSE;
    field_5BC = 0;

    m_cUIManager.GetPanel(4)->SetActive(FALSE);
    m_cUIManager.GetPanel(2)->SetActive(FALSE);
    m_cUIManager.GetPanel(5)->SetActive(FALSE);
    m_cUIManager.GetPanel(7)->SetActive(FALSE);
    m_cUIManager.GetPanel(8)->SetActive(FALSE);
    m_cUIManager.GetPanel(10)->SetActive(FALSE);
    m_cUIManager.GetPanel(11)->SetActive(FALSE);
    m_cUIManager.GetPanel(12)->SetActive(FALSE);
    m_cUIManager.GetPanel(14)->SetActive(FALSE);
    m_cUIManager.GetPanel(3)->SetActive(FALSE);
    m_cUIManager.GetPanel(15)->SetActive(FALSE);
    m_cUIManager.GetPanel(20)->SetActive(FALSE);
}

// 0x671FA0
void CScreenStore::EngineGameUninit()
{
    // NOTE: Uninline.
    m_cUIManager.fUninit();
}

// 0x672D50
void CScreenStore::TimerSynchronousUpdate()
{
    EnterCriticalSection(&m_critSect);

    g_pBaldurChitin->GetObjectGame()->SynchronousUpdate();
    m_cUIManager.Render();

    for (INT nIndex = 0; nIndex < m_lPopupStack.GetCount(); nIndex++) {
        POSITION pos = m_lPopupStack.FindIndex(nIndex);
        if (pos != NULL) {
            CUIPanel* pPanel = m_lPopupStack.GetAt(pos);
            pPanel->SetActive(TRUE);
            pPanel->SetInactiveRender(TRUE);
            pPanel->InvalidateRect(NULL);

            // NOTE: Inlining?
            if (pPanel->m_nID != 20 && pPanel->m_nID == 12) {
                CUIPanel* pPanel = m_cUIManager.GetPanel(12);
                CUIControlBase* pControl = pPanel->GetControl(9);
                pControl->SetActive(field_5A8);
                pControl->SetInactiveRender(field_5A8);
            }
        }
    }

    LeaveCriticalSection(&m_critSect);

    pVidMode->Flip(TRUE);
}

// 0x672E20
void CScreenStore::EnableMainPanel(BOOL bEnable)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 1284
    UTIL_ASSERT(m_pButtonBar != NULL);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 1285
    UTIL_ASSERT(m_pMainPanel != NULL);

    if (bEnable) {
        PlayGUISound(RESREF_SOUND_WINDOWCLOSE);
    }

    if (m_pMainPanel->m_nID == 2) {
        m_pMainPanel->GetControl(50)->SetInactiveRender(m_pBag != NULL);
    }

    m_pButtonBar->SetEnabled(bEnable);

    if (CVideo::SCREENWIDTH / (g_pBaldurChitin->field_4A28 ? 2 : 1) != CBaldurChitin::DEFAULT_SCREEN_WIDTH) {
        m_cUIManager.GetPanel(-5)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-4)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-3)->SetEnabled(bEnable);
        m_cUIManager.GetPanel(-2)->SetEnabled(bEnable);
    }

    CheckEnablePanels(bEnable);
}

// NOTE: Inlined.
CUIPanel* CScreenStore::GetTopPopup()
{
    return m_lPopupStack.GetTailPosition() != NULL ? m_lPopupStack.GetTail() : NULL;
}

// 0x6732F0
void CScreenStore::ResetErrorPanel(CUIPanel* pPanel)
{
    switch (pPanel->m_nID) {
    case 10:
        m_nNumErrorButtons = 1;
        break;
    case 11:
        m_nNumErrorButtons = 2;
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 1655
        UTIL_ASSERT(FALSE);
    }

    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(m_strErrorText, strRes);

    strRes.cSound.SetChannel(0, 0);
    strRes.cSound.SetFireForget(TRUE);
    strRes.cSound.Play(FALSE);

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(pPanel->GetControl(3));

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 1668
    UTIL_ASSERT(pText != NULL);

    pText->RemoveAll();
    UpdateText(pText, "%s", strRes.szText);

    for (INT nButton = 0; nButton < m_nNumErrorButtons; nButton++) {
        CUIControlButton* pButton = static_cast<CUIControlButton*>(pPanel->GetControl(nButton));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 1677
        UTIL_ASSERT(pButton != NULL);

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 8744
        UTIL_ASSERT(0 <= nButton && nButton < CSCREENSTORE_ERROR_BUTTONS);

        pButton->SetText(FetchString(m_strErrorButtonText[nButton]));
    }
}

// 0x673FE0
void CScreenStore::UpdateMainPanel()
{
    if (m_pStore != NULL) {
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 2221
        UTIL_ASSERT(m_pMainPanel != NULL);

        m_pCurrentScrollBar = static_cast<CUIControlScrollBar*>(m_pMainPanel->GetControl(7));

        CUIControlButton* pButton = static_cast<CUIControlButton*>(m_pButtonBar->GetControl(0));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 2225
        UTIL_ASSERT(pButton != NULL);

        pButton->SetEnabled(g_pBaldurChitin->m_pEngineWorld->m_bInControlOfStore);

        switch (m_pMainPanel->m_nID) {
        case 2:
            UpdateBuySellPanel();
            break;
        case 4:
            UpdateIdentifyPanel();
            break;
        case 5:
            UpdateBuySpellPanel();
            break;
        case 7:
            UpdateRentRoomPanel();
            break;
        case 8:
            UpdateBuyDrinksPanel();
            break;
        default:
            // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
            // __LINE__: 2259
            UTIL_ASSERT(FALSE);
        }
    }
}

// 0x6740F0
void CScreenStore::UpdateBuySellPanel()
{
    // TODO: Incomplete.
}

// 0x675380
void CScreenStore::UpdateIdentifyPanel()
{
    // TODO: Incomplete.
}

// 0x675940
void CScreenStore::UpdateBuySpellPanel()
{
    // TODO: Incomplete.
}

// 0x675E80
void CScreenStore::UpdateRentRoomPanel()
{
    // TODO: Incomplete.
}

// 0x676300
void CScreenStore::UpdateBuyDrinksPanel()
{
    // TODO: Incomplete.
}

// NOTE: Inlined.
INT CScreenStore::GetNumGroupItems()
{
    return m_lGroupItems.GetCount();
}

// NOTE: Inlined
void CScreenStore::SetTopGroupItem(INT nTopGroupItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3360
    UTIL_ASSERT(0 <= nTopGroupItem && nTopGroupItem <= GetNumGroupItems());

    m_nTopGroupItem = nTopGroupItem;
}

// NOTE: Inlined.
INT CScreenStore::GetNumIdentifyItems()
{
    return m_lIdentifyItems.GetCount();
}

// NOTE: Inlined
void CScreenStore::SetTopIdentifyItem(INT nTopIdentifyItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3387
    UTIL_ASSERT(0 <= nTopIdentifyItem && nTopIdentifyItem <= GetNumIdentifyItems());

    m_nTopIdentifyItem = nTopIdentifyItem;
}

// NOTE: Inlined.
INT CScreenStore::GetNumStoreItems()
{
    return m_lStoreItems.GetCount();
}

// NOTE: Inlined
void CScreenStore::SetTopStoreItem(INT nTopStoreItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3414
    UTIL_ASSERT(0 <= nTopStoreItem && nTopStoreItem <= GetNumStoreItems());

    m_nTopStoreItem = nTopStoreItem;
}

// NOTE: Inlined.
INT CScreenStore::GetNumSpellItems()
{
    return m_lSpellItems.GetCount();
}

// 0x676590
void CScreenStore::SetTopSpellItem(INT nTopSpellItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3441
    UTIL_ASSERT(0 <= nTopSpellItem && nTopSpellItem <= GetNumSpellItems());

    m_nTopSpellItem = nTopSpellItem;
}

// NOTE: Inlined.
INT CScreenStore::GetNumDrinkItems()
{
    return m_pStore->m_nDrinks;
}

// 0x6765D0
void CScreenStore::SetTopDrinkItem(INT nTopDrinkItem)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3468
    UTIL_ASSERT(0 <= nTopDrinkItem && nTopDrinkItem <= GetNumDrinkItems());

    m_nTopDrinkItem = nTopDrinkItem;
}

// 0x676610
void CScreenStore::GetGroupItem(INT nIndex, CScreenStoreItem& cItem)
{
    CScreenStoreItem cDefaultItem;

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3499
    UTIL_ASSERT(pGame != NULL);

    // TODO: Obtain `pSave` at 0x422C, not sure about type. Not used.

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 3451
    // UTIL_ASSERT(pSave != NULL);

    if (nIndex >= 0 && nIndex < m_lGroupItems.GetCount()) {
        CScreenStoreItem* pItem = m_lGroupItems.GetAt(m_lGroupItems.FindIndex(nIndex));
        cItem.m_cResSpell = pItem->m_cResSpell;
        cItem.m_pItem = pItem->m_pItem;
        cItem.m_bSelected = pItem->m_bSelected;
        cItem.m_bEnabled = pItem->m_bEnabled;
        cItem.m_nSlot = pItem->m_nSlot;
        cItem.m_nValue = pItem->m_nValue;
        cItem.m_nSingleValue = pItem->m_nSingleValue;
        cItem.m_nCount = pItem->m_nCount;
        cItem.m_nMaxCount = pItem->m_nMaxCount;
        cItem.m_nStoreCount = pItem->m_nStoreCount;
    } else {
        cItem.m_cResSpell = cDefaultItem.m_cResSpell;
        cItem.m_pItem = cDefaultItem.m_pItem;
        cItem.m_bSelected = cDefaultItem.m_bSelected;
        cItem.m_bEnabled = cDefaultItem.m_bEnabled;
        cItem.m_nSlot = cDefaultItem.m_nSlot;
        cItem.m_nValue = cDefaultItem.m_nValue;
        cItem.m_nSingleValue = cDefaultItem.m_nSingleValue;
        cItem.m_nCount = cDefaultItem.m_nCount;
        cItem.m_nMaxCount = cDefaultItem.m_nMaxCount;
        cItem.m_nStoreCount = cDefaultItem.m_nStoreCount;
    }
}

// 0x678050
void CScreenStore::OnBuyItemButtonClick()
{
    // TODO: Incomplete.
}

// 0x67A070
void CScreenStore::OnSellItemButtonClick()
{
    // TODO: Incomplete.
}

// 0x67B640
void CScreenStore::OnIdentifyItemButtonClick()
{
    // TODO: Incomplete.
}

// 0x67B8A0
void CScreenStore::OnBuySpellButtonClick()
{
    // TODO: Incomplete.
}

// 0x67C570
void CScreenStore::OnRentRoomButtonClick()
{
    // TODO: Incomplete.
}

// 0x67C710
void CScreenStore::OnBuyDrinkButtonClick(INT nButton)
{
    // TODO: Incomplete.
}

// 0x673B60
void CScreenStore::CheckEnablePanels(BOOL bEnable)
{
    // TODO: Incomplete.
}

// 0x67CBD0
void CScreenStore::OnDoneButtonClick()
{
    // TODO: Incomplete.
}

// 0x67CE40
void CScreenStore::OnCancelButtonClick()
{
    // TODO: Incomplete.
}

// 0x67E840
void CScreenStore::CancelEngine()
{
    m_bInCancelEngine = TRUE;

    while (GetTopPopup() != NULL) {
        OnCancelButtonClick();
    }

    m_bInCancelEngine = FALSE;
}

// 0x67DD30
void CScreenStore::OnErrorButtonClick(INT nButton)
{
    // TODO: Incomplete.
}

// 0x67E420
void CScreenStore::GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture)
{
    if (m_pButtonBar->m_nID == 3) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(m_pMainPanel->GetControl(8));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 9095
        UTIL_ASSERT(pEdit != NULL);

        sChatText = pEdit->GetText();
        bInputCapture = m_cUIManager.m_pFocusedControl == pEdit;
    } else {
        sChatText = "";
        bInputCapture = FALSE;
    }
}

// 0x67E4F0
void CScreenStore::SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture)
{
    if (m_pButtonBar->m_nID == 15) {
        CUIControlEdit* pEdit = static_cast<CUIControlEdit*>(m_pMainPanel->GetControl(8));

        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 9133
        UTIL_ASSERT(pEdit != NULL);

        pEdit->SetText(sChatText);

        if (bInputCapture) {
            m_cUIManager.SetCapture(pEdit, CUIManager::KEYBOARD);
        }
    }
}

// 0x67E870
void CScreenStore::UpdatePartyGoldStatus()
{
    if (GetTopPopup() == NULL) {
        UpdateMainPanel();
    }
}

// 0x684CD0
void CScreenStore::CloseBag(BOOL bSaveFile)
{
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
            g_pBaldurChitin->GetObjectGame()->ReleaseServerStore(m_pBag->m_resRef);
        } else {
            CMessageStoreRelease* message = new CMessageStoreRelease(m_pBag->m_resRef,
                CGameObjectArray::INVALID_INDEX,
                CGameObjectArray::INVALID_INDEX);
            g_pBaldurChitin->GetMessageHandler()->AddMessage(message, FALSE);
        }
    } else {
        if (bSaveFile) {
            m_pBag->Marshal(g_pBaldurChitin->GetObjectGame()->m_sTempDir);
        }
    }

    delete m_pBag;
    m_pBag = NULL;
}

// -----------------------------------------------------------------------------

// 0x67EA20
CUIControlButtonStoreBarDone::CUIControlButtonStoreBarDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes);
    SetText(strRes.szText);
}

// 0x67EB10
CUIControlButtonStoreBarDone::~CUIControlButtonStoreBarDone()
{
}

// 0x67EBB0
void CUIControlButtonStoreBarDone::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 9575
    UTIL_ASSERT(pStore != NULL);

    if (g_pBaldurChitin->m_pEngineWorld->m_bInControlOfStore) {
        if (pStore->m_pStore->m_header.m_nStoreType == 4) {
            pStore->SelectEngine(g_pBaldurChitin->m_pEngineInventory);
        } else {
            pStore->SelectEngine(g_pBaldurChitin->m_pEngineWorld);
        }

        g_pBaldurChitin->m_pEngineWorld->StopStore();
    }
}

// -----------------------------------------------------------------------------

// 0x67EEE0
CUIControlButtonStoreBuySellBuy::CUIControlButtonStoreBuySellBuy(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13703, strRes); // "Buy"
    SetText(strRes.szText);
}

// 0x67EFD0
CUIControlButtonStoreBuySellBuy::~CUIControlButtonStoreBuySellBuy()
{
}

// 0x67F070
void CUIControlButtonStoreBuySellBuy::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 9738
    UTIL_ASSERT(pStore != NULL);

    pStore->OnBuyItemButtonClick();
}

// -----------------------------------------------------------------------------

// 0x67F0B0
CUIControlButtonStoreBuySellSell::CUIControlButtonStoreBuySellSell(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13704, strRes); // "Sell"
    SetText(strRes.szText);
}

// 0x67F1A0
CUIControlButtonStoreBuySellSell::~CUIControlButtonStoreBuySellSell()
{
}

// 0x67F240
void CUIControlButtonStoreBuySellSell::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 9794
    UTIL_ASSERT(pStore != NULL);

    pStore->OnSellItemButtonClick();
}

// -----------------------------------------------------------------------------

// 0x67F280
CUIControlButtonStoreIdentifyIdentify::CUIControlButtonStoreIdentifyIdentify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(14133, strRes); // "Identify"
    SetText(strRes.szText);
}

// 0x67F370
CUIControlButtonStoreIdentifyIdentify::~CUIControlButtonStoreIdentifyIdentify()
{
}

// 0x67F410
void CUIControlButtonStoreIdentifyIdentify::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 9850
    UTIL_ASSERT(pStore != NULL);

    pStore->OnIdentifyItemButtonClick();
}

// -----------------------------------------------------------------------------

// 0x67F450
CUIControlButtonStoreBuySpellBuy::CUIControlButtonStoreBuySpellBuy(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13703, strRes); // "Buy"
    SetText(strRes.szText);
}

// 0x67F540
CUIControlButtonStoreBuySpellBuy::~CUIControlButtonStoreBuySpellBuy()
{
}

// 0x67F5E0
void CUIControlButtonStoreBuySpellBuy::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 9963
    UTIL_ASSERT(pStore != NULL);

    pStore->OnBuySpellButtonClick();
}

// -----------------------------------------------------------------------------

// 0x67F620
CUIControlScrollBarStoreBuyDrinksDrink::CUIControlScrollBarStoreBuyDrinksDrink(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarStoreBuyDrinksDrink::~CUIControlScrollBarStoreBuyDrinksDrink()
{
}

// NOTE: Inlined.
void CUIControlScrollBarStoreBuyDrinksDrink::UpdateScrollBar()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10015
    UTIL_ASSERT(pStore != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10017
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pStore->m_nTopDrinkItem, pStore->GetNumDrinkItems(), 8);
}

// 0x67F660
void CUIControlScrollBarStoreBuyDrinksDrink::OnScrollUp()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10047
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopDrinkItem = max(pStore->m_nTopDrinkItem - 1, 0);
    if (nNewTopDrinkItem != pStore->m_nTopDrinkItem) {
        // NOTE: Uninline.
        pStore->SetTopDrinkItem(nNewTopDrinkItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67F760
void CUIControlScrollBarStoreBuyDrinksDrink::OnScrollDown()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10083
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopDrinkItem = max(min(pStore->m_nTopDrinkItem + 1, pStore->GetNumDrinkItems() - 8), 0);
    if (nNewTopDrinkItem != pStore->m_nTopDrinkItem) {
        // NOTE: Uninline.
        pStore->SetTopDrinkItem(nNewTopDrinkItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67F870
void CUIControlScrollBarStoreBuyDrinksDrink::OnPageUp(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10119
    UTIL_ASSERT(pStore != NULL);

    INT nStep = min(nLines, 7);
    INT nNewTopDrinkItem = max(pStore->m_nTopDrinkItem - nStep, 0);
    if (nNewTopDrinkItem != pStore->m_nTopDrinkItem) {
        // NOTE: Uninline.
        pStore->SetTopDrinkItem(nNewTopDrinkItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67F980
void CUIControlScrollBarStoreBuyDrinksDrink::OnPageDown(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10159
    UTIL_ASSERT(pStore != NULL);

    INT nStep = nStep = min(nLines, 7);
    INT nNewTopDrinkItem = max(min(pStore->m_nTopDrinkItem + nStep, pStore->GetNumDrinkItems() - 8), 0);
    if (nNewTopDrinkItem != pStore->m_nTopDrinkItem) {
        // NOTE: Uninline.
        pStore->SetTopDrinkItem(nNewTopDrinkItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67FAA0
void CUIControlScrollBarStoreBuyDrinksDrink::OnScroll()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10199
    UTIL_ASSERT(pStore != NULL);

    // NOTE: Uninline.
    pStore->SetTopDrinkItem(max(field_144 * (pStore->GetNumDrinkItems() - 8), 0) / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x67FBA0
void CUIControlScrollBarStoreBuyDrinksDrink::InvalidateItems()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10231
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pStore->UpdateMainPanel();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x67FC40
CUIControlScrollBarStoreStore::CUIControlScrollBarStoreStore(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarStoreStore::~CUIControlScrollBarStoreStore()
{
}

// NOTE: Inlined.
void CUIControlScrollBarStoreStore::UpdateScrollBar()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10291
    UTIL_ASSERT(pStore != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10293
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pStore->m_nTopStoreItem, pStore->GetNumStoreItems(), 6);
}

// 0x67FC60
void CUIControlScrollBarStoreStore::OnScrollUp()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10323
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopStoreItem = max(pStore->m_nTopStoreItem - 1, 0);
    if (nNewTopStoreItem != pStore->m_nTopStoreItem) {
        // NOTE: Uninline.
        pStore->SetTopStoreItem(nNewTopStoreItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67FD50
void CUIControlScrollBarStoreStore::OnScrollDown()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10359
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopStoreItem = max(min(pStore->m_nTopStoreItem + 1, pStore->GetNumStoreItems() - 6), 0);
    if (nNewTopStoreItem != pStore->m_nTopStoreItem) {
        // NOTE: Uninline.
        pStore->SetTopStoreItem(nNewTopStoreItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67FE50
void CUIControlScrollBarStoreStore::OnPageUp(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10395
    UTIL_ASSERT(pStore != NULL);

    INT nStep = min(nLines, 5);
    INT nNewTopStoreItem = max(pStore->m_nTopStoreItem - nStep, 0);
    if (nNewTopStoreItem != pStore->m_nTopStoreItem) {
        // NOTE: Uninline.
        pStore->SetTopStoreItem(nNewTopStoreItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x67FF50
void CUIControlScrollBarStoreStore::OnPageDown(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10435
    UTIL_ASSERT(pStore != NULL);

    INT nStep = nStep = min(nLines, 5);
    INT nNewTopStoreItem = max(min(pStore->m_nTopStoreItem + nStep, pStore->GetNumStoreItems() - 6), 0);
    if (nNewTopStoreItem != pStore->m_nTopStoreItem) {
        // NOTE: Uninline.
        pStore->SetTopStoreItem(nNewTopStoreItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680070
void CUIControlScrollBarStoreStore::OnScroll()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10475
    UTIL_ASSERT(pStore != NULL);

    // NOTE: Uninline.
    pStore->SetTopStoreItem(max(field_144 * (pStore->GetNumStoreItems() - 6), 0) / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x680160
void CUIControlScrollBarStoreStore::InvalidateItems()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10507
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pStore->UpdateMainPanel();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x680200
CUIControlScrollBarStoreIdentify::CUIControlScrollBarStoreIdentify(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarStoreIdentify::~CUIControlScrollBarStoreIdentify()
{
}

// NOTE: Inlined.
void CUIControlScrollBarStoreIdentify::UpdateScrollBar()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10567
    UTIL_ASSERT(pStore != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10569
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pStore->m_nTopIdentifyItem, pStore->GetNumIdentifyItems(), 6);
}

// 0x680220
void CUIControlScrollBarStoreIdentify::OnScrollUp()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10599
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopIdentifyItem = max(pStore->m_nTopIdentifyItem - 1, 0);
    if (nNewTopIdentifyItem != pStore->m_nTopIdentifyItem) {
        // NOTE: Uninline.
        pStore->SetTopIdentifyItem(nNewTopIdentifyItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680310
void CUIControlScrollBarStoreIdentify::OnScrollDown()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10635
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopIdentifyItem = max(min(pStore->m_nTopIdentifyItem + 1, pStore->GetNumIdentifyItems() - 6), 0);
    if (nNewTopIdentifyItem != pStore->m_nTopIdentifyItem) {
        // NOTE: Uninline.
        pStore->SetTopIdentifyItem(nNewTopIdentifyItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680410
void CUIControlScrollBarStoreIdentify::OnPageUp(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10671
    UTIL_ASSERT(pStore != NULL);

    INT nStep = min(nLines, 5);
    INT nNewTopIdentifyItem = max(pStore->m_nTopIdentifyItem - nStep, 0);
    if (nNewTopIdentifyItem != pStore->m_nTopIdentifyItem) {
        // NOTE: Uninline.
        pStore->SetTopIdentifyItem(nNewTopIdentifyItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680510
void CUIControlScrollBarStoreIdentify::OnPageDown(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10711
    UTIL_ASSERT(pStore != NULL);

    INT nStep = nStep = min(nLines, 5);
    INT nNewTopIdentifyItem = max(min(pStore->m_nTopIdentifyItem + nStep, pStore->GetNumIdentifyItems() - 6), 0);
    if (nNewTopIdentifyItem != pStore->m_nTopIdentifyItem) {
        // NOTE: Uninline.
        pStore->SetTopIdentifyItem(nNewTopIdentifyItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680630
void CUIControlScrollBarStoreIdentify::OnScroll()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10751
    UTIL_ASSERT(pStore != NULL);

    // NOTE: Uninline.
    pStore->SetTopIdentifyItem(max(field_144 * (pStore->GetNumIdentifyItems() - 6), 0) / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x680720
void CUIControlScrollBarStoreIdentify::InvalidateItems()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10783
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pStore->UpdateMainPanel();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x6807C0
CUIControlScrollBarStoreGroup::CUIControlScrollBarStoreGroup(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarStoreGroup::~CUIControlScrollBarStoreGroup()
{
}

// NOTE: Inlined.
void CUIControlScrollBarStoreGroup::UpdateScrollBar()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10844
    UTIL_ASSERT(pStore != NULL);

    AdjustScrollBar(pStore->m_nTopGroupItem, pStore->GetNumGroupItems(), 6);
}

// 0x6807E0
void CUIControlScrollBarStoreGroup::OnScrollUp()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10873
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopGroupItem = max(pStore->m_nTopGroupItem - 1, 0);
    if (nNewTopGroupItem != pStore->m_nTopGroupItem) {
        // NOTE: Uninline.
        pStore->SetTopGroupItem(nNewTopGroupItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x6808A0
void CUIControlScrollBarStoreGroup::OnScrollDown()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10909
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopGroupItem = max(min(pStore->m_nTopGroupItem + 1, pStore->GetNumGroupItems() - 6), 0);
    if (nNewTopGroupItem != pStore->m_nTopGroupItem) {
        // NOTE: Uninline.
        pStore->SetTopGroupItem(nNewTopGroupItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680980
void CUIControlScrollBarStoreGroup::OnPageUp(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10945
    UTIL_ASSERT(pStore != NULL);

    INT nStep = min(nLines, 5);
    INT nNewTopGroupItem = max(pStore->m_nTopGroupItem - nStep, 0);
    if (nNewTopGroupItem != pStore->m_nTopGroupItem) {
        // NOTE: Uninline.
        pStore->SetTopGroupItem(nNewTopGroupItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680A50
void CUIControlScrollBarStoreGroup::OnPageDown(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 10985
    UTIL_ASSERT(pStore != NULL);

    INT nStep = nStep = min(nLines, 5);
    INT nNewTopGroupItem = max(min(pStore->m_nTopGroupItem + nStep, pStore->GetNumGroupItems() - 6), 0);
    if (nNewTopGroupItem != pStore->m_nTopGroupItem) {
        // NOTE: Uninline.
        pStore->SetTopGroupItem(nNewTopGroupItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680B40
void CUIControlScrollBarStoreGroup::OnScroll()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11025
    UTIL_ASSERT(pStore != NULL);

    // NOTE: Uninline.
    pStore->SetTopGroupItem(max(field_144 * (pStore->GetNumGroupItems() - 6), 0) / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x680C10
void CUIControlScrollBarStoreGroup::InvalidateItems()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11057
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pStore->UpdateMainPanel();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x680CB0
CUIControlScrollBarStoreSpell::CUIControlScrollBarStoreSpell(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo)
    : CUIControlScrollBar(panel, controlInfo)
{
}

// 0x632C00
CUIControlScrollBarStoreSpell::~CUIControlScrollBarStoreSpell()
{
}

// NOTE: Inlined.
void CUIControlScrollBarStoreSpell::UpdateScrollBar()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11118
    UTIL_ASSERT(pStore != NULL);

    CInfGame* pGame = g_pBaldurChitin->GetObjectGame();

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11120
    UTIL_ASSERT(pGame != NULL);

    AdjustScrollBar(pStore->m_nTopSpellItem, pStore->GetNumSpellItems(), 6);
}

// 0x680CD0
void CUIControlScrollBarStoreSpell::OnScrollUp()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11150
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopSpellItem = max(pStore->m_nTopSpellItem - 1, 0);
    if (nNewTopSpellItem != pStore->m_nTopSpellItem) {
        // NOTE: Uninline.
        pStore->SetTopSpellItem(nNewTopSpellItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680DC0
void CUIControlScrollBarStoreSpell::OnScrollDown()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11186
    UTIL_ASSERT(pStore != NULL);

    INT nNewTopSpellItem = max(min(pStore->m_nTopSpellItem + 1, pStore->GetNumSpellItems() - 6), 0);
    if (nNewTopSpellItem != pStore->m_nTopSpellItem) {
        // NOTE: Uninline.
        pStore->SetTopSpellItem(nNewTopSpellItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680EC0
void CUIControlScrollBarStoreSpell::OnPageUp(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11222
    UTIL_ASSERT(pStore != NULL);

    INT nStep = min(nLines, 5);
    INT nNewTopSpellItem = max(pStore->m_nTopSpellItem - nStep, 0);
    if (nNewTopSpellItem != pStore->m_nTopSpellItem) {
        // NOTE: Uninline.
        pStore->SetTopSpellItem(nNewTopSpellItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x680FC0
void CUIControlScrollBarStoreSpell::OnPageDown(DWORD nLines)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11262
    UTIL_ASSERT(pStore != NULL);

    INT nStep = nStep = min(nLines, 5);
    INT nNewTopSpellItem = max(min(pStore->m_nTopSpellItem + nStep, pStore->GetNumSpellItems() - 6), 0);
    if (nNewTopSpellItem != pStore->m_nTopSpellItem) {
        // NOTE: Uninline.
        pStore->SetTopSpellItem(nNewTopSpellItem);

        InvalidateItems();

        // NOTE: Uninline.
        UpdateScrollBar();
    }
}

// 0x6810E0
void CUIControlScrollBarStoreSpell::OnScroll()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11302
    UTIL_ASSERT(pStore != NULL);

    // NOTE: Uninline.
    pStore->SetTopSpellItem(max(field_144 * (pStore->GetNumSpellItems() - 6), 0) / field_142);

    InvalidateItems();

    // NOTE: Uninline.
    UpdateScrollBar();
}

// 0x6811D0
void CUIControlScrollBarStoreSpell::InvalidateItems()
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 11334
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    pStore->UpdateMainPanel();

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x681270
CUIControlButtonStoreStoreItem::CUIControlButtonStoreStoreItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON | RBUTTON, 0)
{
    m_nSelectedFrame = 0;
}

// 0x681310
CUIControlButtonStoreStoreItem::~CUIControlButtonStoreStoreItem()
{
}

// 0x6813C0
void CUIControlButtonStoreStoreItem::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x681500
void CUIControlButtonStoreStoreItem::OnLButtonDoubleClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x681690
void CUIControlButtonStoreStoreItem::OnRButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x6817A0
BOOL CUIControlButtonStoreStoreItem::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x681D90
CUIControlButtonStoreGroupItem::CUIControlButtonStoreGroupItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON | RBUTTON, 0)
{
    m_nSelectedFrame = 0;
}

// 0x681E30
CUIControlButtonStoreGroupItem::~CUIControlButtonStoreGroupItem()
{
}

// 0x681EE0
void CUIControlButtonStoreGroupItem::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// NOTE: Odd location.
//
// 0x685090
void CUIControlButtonStoreGroupItem::OnLButtonDoubleClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x6821A0
void CUIControlButtonStoreGroupItem::OnRButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x6822F0
BOOL CUIControlButtonStoreGroupItem::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x6828E0
CUIControlButtonStoreStoreSpell::CUIControlButtonStoreStoreSpell(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON | RBUTTON, 0)
{
    m_nSelectedFrame = 0;
    m_resRef = "";
}

// 0x682990
CUIControlButtonStoreStoreSpell::~CUIControlButtonStoreStoreSpell()
{
}

// 0x682A30
void CUIControlButtonStoreStoreSpell::OnLButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x682C00
void CUIControlButtonStoreStoreSpell::OnRButtonClick(CPoint pt)
{
    // TODO: Incomplete.
}

// 0x682D10
BOOL CUIControlButtonStoreStoreSpell::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

// 0x683080
CUIControlButtonStoreRentRoomRoomSelect::CUIControlButtonStoreRentRoomRoomSelect(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nSelectedFrame = 0;
    m_nNotSelectedFrame = 1;
    m_nPressedFrame = 2;
    m_nDisabledFrame = 3;

    STR_RES strRes;

    STRREF strText;
    switch (m_nID) {
    case 4:
        strText = 14294; // "Peasant"
        break;
    case 5:
        strText = 14295; // "Merchant"
        break;
    case 6:
        strText = 14296; // "Noble"
        break;
    case 7:
        strText = 14297; // "Royal"
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 12420
        UTIL_ASSERT(FALSE);
    }

    g_pBaldurChitin->GetTlkTable().Fetch(strText, strRes);
    SetText(strRes.szText);
}

// 0x6831E0
CUIControlButtonStoreRentRoomRoomSelect::~CUIControlButtonStoreRentRoomRoomSelect()
{
}

// 0x683280
void CUIControlButtonStoreRentRoomRoomSelect::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 12503
    UTIL_ASSERT(pStore != NULL);

    switch (m_nID) {
    case 4:
        pStore->m_dwRoomType = 1;
        pStore->UpdateMainPanel();
        break;
    case 5:
        pStore->m_dwRoomType = 2;
        pStore->UpdateMainPanel();
        break;
    case 6:
        pStore->m_dwRoomType = 3;
        pStore->UpdateMainPanel();
        break;
    case 7:
        pStore->m_dwRoomType = 4;
        pStore->UpdateMainPanel();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 12472
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x683360
CUIControlButtonStoreRentRoomRoomPicture::CUIControlButtonStoreRentRoomRoomPicture(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nSelectedFrame = 0;
    m_nNotSelectedFrame = 0;
    m_nPressedFrame = 0;
    m_nDisabledFrame = 1;
}

// 0x6833D0
CUIControlButtonStoreRentRoomRoomPicture::~CUIControlButtonStoreRentRoomRoomPicture()
{
}

// 0x683470
void CUIControlButtonStoreRentRoomRoomPicture::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 12612
    UTIL_ASSERT(pStore != NULL);

    switch (m_nID) {
    case 0:
        pStore->m_dwRoomType = 1;
        pStore->UpdateMainPanel();
        break;
    case 1:
        pStore->m_dwRoomType = 2;
        pStore->UpdateMainPanel();
        break;
    case 2:
        pStore->m_dwRoomType = 3;
        pStore->UpdateMainPanel();
        break;
    case 3:
        pStore->m_dwRoomType = 4;
        pStore->UpdateMainPanel();
        break;
    default:
        // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
        // __LINE__: 12581
        UTIL_ASSERT(FALSE);
    }
}

// -----------------------------------------------------------------------------

// 0x683550
CUIControlButtonStoreRentRoomRent::CUIControlButtonStoreRentRoomRent(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(14293, strRes); // "Rent"
    SetText(strRes.szText);
}

// 0x683640
CUIControlButtonStoreRentRoomRent::~CUIControlButtonStoreRentRoomRent()
{
}

// 0x6836E0
void CUIControlButtonStoreRentRoomRent::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 12669
    UTIL_ASSERT(pStore != NULL);

    pStore->OnRentRoomButtonClick();
}

// -----------------------------------------------------------------------------

// 0x683720
CUIControlPortraitStore::CUIControlPortraitStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x683770
CUIControlPortraitStore::~CUIControlPortraitStore()
{
}

// 0x683810
void CUIControlPortraitStore::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->GetActiveEngine()->OnPortraitLClick(m_nID);
}

// -----------------------------------------------------------------------------

// 0x6838E0
CUIControlButtonStoreBuyDrinksDrink::CUIControlButtonStoreBuyDrinksDrink(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(14293, strRes); // "Rent"
    SetText(strRes.szText);
}

// 0x683930
CUIControlButtonStoreBuyDrinksDrink::~CUIControlButtonStoreBuyDrinksDrink()
{
}

// 0x6839D0
void CUIControlButtonStoreBuyDrinksDrink::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 12811
    UTIL_ASSERT(pStore != NULL);

    CSingleLock renderLock(&(pStore->GetManager()->field_36), FALSE);
    renderLock.Lock(INFINITE);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 12817
    UTIL_ASSERT(CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK0 <= m_nID && m_nID <= CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK7);

    pStore->OnBuyDrinkButtonClick(m_nID - CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK0);

    renderLock.Unlock();
}

// -----------------------------------------------------------------------------

// 0x683C30
CUIControlButtonStoreError::CUIControlButtonStoreError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes); // "Done"
    SetText(strRes.szText);
}

// 0x683CE0
CUIControlButtonStoreError::~CUIControlButtonStoreError()
{
}

// 0x683D80
void CUIControlButtonStoreError::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 13133
    UTIL_ASSERT(pStore != NULL);

    pStore->OnErrorButtonClick(m_nID);
}

// -----------------------------------------------------------------------------

// 0x684210
CUIControlButtonStoreRequesterDone::CUIControlButtonStoreRequesterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(11973, strRes); // "Done"
    SetText(strRes.szText);
}

// 0x684300
CUIControlButtonStoreRequesterDone::~CUIControlButtonStoreRequesterDone()
{
}

// 0x6843A0
void CUIControlButtonStoreRequesterDone::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 13324
    UTIL_ASSERT(pStore != NULL);

    pStore->OnDoneButtonClick();
}

// -----------------------------------------------------------------------------

// 0x6843E0
CUIControlButtonStoreRequesterCancel::CUIControlButtonStoreRequesterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13727, strRes); // "Cancel"
    SetText(strRes.szText);
}

// 0x6844D0
CUIControlButtonStoreRequesterCancel::~CUIControlButtonStoreRequesterCancel()
{
}

// 0x684570
void CUIControlButtonStoreRequesterCancel::OnLButtonClick(CPoint pt)
{
    CScreenStore* pStore = g_pBaldurChitin->m_pEngineStore;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\InfScreenStore.cpp
    // __LINE__: 13380
    UTIL_ASSERT(pStore != NULL);

    pStore->OnCancelButtonClick();
}

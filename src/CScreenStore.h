#ifndef CSCREENSTORE_H_
#define CSCREENSTORE_H_

#include "CAIObjectType.h"
#include "CBaldurEngine.h"
#include "CItem.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlButtonPlusMinus.h"
#include "CUIControlEdit.h"
#include "CUIControlScrollBar.h"
#include "CVidFont.h"

#define CSCREENSTORE_VIRTUAL_KEYS 91
#define CSCREENSTORE_ERROR_BUTTONS 3

#define CSCREENSTORE_NUM_BOTTOMBUTTONS 4

#define CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK0 40
#define CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK7 47

class CStore;
class CUIControlTextDisplay;

class CScreenStoreItem {
public:
    CScreenStoreItem();

    /* 0000 */ CResRef m_cResSpell;
    /* 0008 */ CItem* m_pItem;
    /* 000C */ BOOL m_bSelected;
    /* 0010 */ BOOL m_bEnabled;
    /* 0014 */ INT m_nSlot;
    /* 0018 */ LONG m_nValue;
    /* 001C */ LONG m_nSingleValue;
    /* 0020 */ DWORD m_nCount;
    /* 0024 */ DWORD m_nMaxCount;
    /* 0028 */ DWORD m_nStoreCount;
};

class CScreenStore : public CBaldurEngine {
public:
    static const CString TOKEN_HP;
    static const CString TOKEN_ITEMNAME;
    static const CString TOKEN_ITEMCOST;
    static const INT STORE_SLOTS;
    static const INT GROUP_SLOTS;
    static const INT SPELL_SLOTS;
    static const INT DRINK_SLOTS;
    static const INT IDENTIFY_SLOTS;
    static const INT NUM_BOTTOMBUTTONS;
    static const WORD SEQUENCE_BUYSELL;
    static const WORD SEQUENCE_IDENTIFY;
    static const WORD SEQUENCE_STEAL;
    static const WORD SEQUENCE_BUYSPELL;
    static const WORD SEQUENCE_DONATE;
    static const WORD SEQUENCE_BUYDRINK;
    static const WORD SEQUENCE_RENTROOM;
    static const DWORD ROOMTYPE_NONE;
    static const DWORD ROOMTYPE_PEASANT;
    static const DWORD ROOMTYPE_MERCHANT;
    static const DWORD ROOMTYPE_NOBLE;
    static const DWORD ROOMTYPE_ROYAL;
    static const DWORD NUM_ROOMTYPES;
    static const DWORD SELL_MAXNUM_STORETOBAG;

    // FIXME: Make instance member.
    static CRITICAL_SECTION m_critSect;

    // FIXME: Make instance member.
    static BOOLEAN m_bInCancelEngine;

    CScreenStore();
    /* 0004 */ ~CScreenStore() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0038 */ BOOL GetCtrlKey() override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00AC */ void OnKeyDown(SHORT nKeysFlags) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;
    /* 0104 */ void CancelEngine() override;
    /* 010C */ void UpdatePartyGoldStatus() override;
    /* 0110 */ void GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture) override;
    /* 0114 */ void SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture) override;

    void EnableMainPanel(BOOL bEnable);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void sub_6734F0(CUIPanel* pPanel);
    void sub_673740(CUIPanel* pPanel);
    BOOL IsCharacterAlive(SHORT nPortraitNum);
    void CheckEnableButtonBar();
    void SwitchMainPanel(DWORD dwMainPanelId);
    void CheckEnablePanels(BOOL bEnable);
    void ResetMainPanel();
    void UpdateMainPanel();
    void UpdateBuySellPanel();
    void UpdateIdentifyPanel();
    void UpdateBuySpellPanel();
    void UpdateRentRoomPanel();
    void UpdateBuyDrinksPanel();
    INT GetNumGroupItems();
    void SetTopGroupItem(INT nTopGroupItem);
    INT GetNumIdentifyItems();
    void SetTopIdentifyItem(INT nTopIdentifyItem);
    INT GetNumStoreItems();
    void SetTopStoreItem(INT nTopStoreItem);
    INT GetNumSpellItems();
    void SetTopSpellItem(INT nTopSpellItem);
    INT GetNumDrinkItems();
    void SetTopDrinkItem(INT nTopDrinkItem);
    void GetGroupItem(INT nIndex, CScreenStoreItem& cItem);
    void UpdateGroupItems();
    void DestroyGroupItems(BOOL bShutDown);
    void GetStoreItem(INT nIndex, CScreenStoreItem& cItem);
    void UpdateStoreItems();
    void DestroyStoreItems(BOOL bShutDown);
    void GetSpellItem(INT nIndex, CScreenStoreItem& cItem);
    void UpdateSpellItems();
    void DestroySpellItems();
    void GetIdentifyItem(INT nIndex, CScreenStoreItem& cItem);
    void UpdateIdentifyItems();
    void DestroyIdentifyItems();
    void UpdateGroupCost();
    void UpdateIdentifyCost();
    void UpdateStoreCost();
    void UpdateSpellCost();
    void OnBuyItemButtonClick();
    BOOL IsSellItemButtonClickable();
    void OnSellItemButtonClick();
    void sub_67A130();
    void sub_67A5B0();
    void sub_67ABF0();
    void sub_67B030();
    void OnIdentifyItemButtonClick();
    void OnBuySpellButtonClick();
    void OnRentRoomButtonClick();
    void OnBuyDrinkButtonClick(INT nButton);
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void StartStore(const CAIObjectType& proprietor, const CAIObjectType& customer, const CResRef& cResStore);
    void StopStore();
    void DeleteStore();
    DWORD GetPanelButtonPanelId(INT nButtonIndex);
    SHORT GetPanelButtonSequence(INT nButtonIndex);
    STRREF GetPanelButtonToolTip(INT nButtonIndex);
    BOOL IsCharacterInRange(SHORT nPortraitNum);
    DWORD GetRoomCost();
    void OnErrorButtonClick(INT nButton);
    void RestParty();
    BOOL IsCharacterViewable(SHORT nPortraitNum);
    void FocusChatEditBox();
    void OpenBag(const CResRef& resRef);
    void CloseBag(BOOL bSaveFile);
    void UpdateRequesterPanel();
    DWORD GetDefaultMainPanel();
    CAIObjectType GetCustomer();

    void SelectGroupItem(INT nIndex, BOOL bSelected);
    void SelectIdentifyItem(INT nIndex, BOOL bSelected);
    void SelectStoreItem(INT nIndex, BOOL bSelected);
    void SelectSpellItem(INT nIndex, BOOL bSelected);

    void SelectAllGroupItems(BOOL bSelected);
    void SelectAllIdentifyItems(BOOL bSelected);
    void SelectAllStoreItems(BOOL bSelected);
    void SelectAllSpellItems(BOOL bSelected);

    void SetGroupItemCount(INT nIndex, DWORD nCount);
    void SetStoreItemCount(INT nIndex, DWORD nCount);

    // Seen in `CUIControlButtonStoreGroupItem::OnLButtonClick` assertion.
    CStore* GetBag() { return m_pBag; }

    // Seen in `CScreenStore::OnErrorButtonClick` assertion.
    INT GetNumErrorButtons() { return m_nNumErrorButtons; }

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENSTORE_VIRTUAL_KEYS];
    /* 039E */ BYTE m_pVirtualKeysFlags[CSCREENSTORE_VIRTUAL_KEYS];
    /* 0439 */ BOOLEAN m_bCtrlKeyDown;
    /* 043A */ BOOLEAN m_bShiftKeyDown;
    /* 043C */ BOOL m_bCapsLockKeyOn;
    /* 0440 */ CUIPanel* m_pMainPanel;
    /* 0444 */ INT m_nTopGroupItem;
    /* 0448 */ CTypedPtrList<CPtrList, CScreenStoreItem*> m_lGroupItems;
    /* 0464 */ INT m_nTopStoreItem;
    /* 0468 */ CTypedPtrList<CPtrList, CScreenStoreItem*> m_lStoreItems;
    /* 0484 */ INT m_nTopSpellItem;
    /* 0488 */ CTypedPtrList<CPtrList, CScreenStoreItem*> m_lSpellItems;
    /* 04A4 */ INT m_nTopIdentifyItem;
    /* 04A8 */ CTypedPtrList<CPtrList, CScreenStoreItem*> m_lIdentifyItems;
    /* 04C4 */ INT m_nTopDrinkItem;
    /* 04C8 */ CResRef m_cResStore;
    /* 04D0 */ CResRef m_cResBag;
    /* 04D8 */ DWORD m_adwButtonPanelId[CSCREENSTORE_NUM_BOTTOMBUTTONS];
    /* 04E8 */ CStore* m_pStore;
    /* 04EC */ CStore* m_pBag;
    /* 04F0 */ LONG m_nStoreCost;
    /* 04F4 */ LONG m_nGroupCost;
    /* 04F8 */ DWORD m_dwSpellCost;
    /* 04FC */ DWORD m_dwIdentifyCost;
    /* 0500 */ DWORD m_dwRoomType;
    /* 0504 */ CAIObjectType m_cAIProprietor;
    /* 0540 */ CAIObjectType m_cAICustomer;
    /* 057C */ int field_57C;
    /* 0580 */ LONG m_nDrinkRumorIndex;
    /* 0584 */ int field_584;
    /* 0588 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 05A4 */ CItem* field_5A4;
    /* 05A8 */ int field_5A8;
    /* 05AC */ CResRef m_cResInfoSpell;
    /* 05B4 */ CUIPanel* m_pButtonBar;
    /* 05B8 */ CUIControlTextDisplay* m_pChatDisplay;
    /* 05BC */ INT m_nChatMessageCount;
    /* 05C0 */ INT m_nErrorState;
    /* 05C4 */ STRREF m_strErrorText;
    /* 05C8 */ INT m_nNumErrorButtons;
    /* 05CC */ STRREF m_strErrorButtonText[CSCREENSTORE_ERROR_BUTTONS];
    /* 05D8 */ unsigned char field_5D8;
    /* 05D9 */ unsigned char field_5D9;
    /* 05DA */ CVidFont m_preLoadFontRealms;
    /* 0ADA */ CVidFont m_preLoadFontStnSml;
    /* 0FDA */ CVidFont m_preLoadFontTool;
    /* 14DA */ CUIControlScrollBar* field_14DA;
    /* 14DE */ DWORD field_14DE;
    /* 14E2 */ int field_14E2;
    /* 14E6 */ int field_14E6;
};

class CUIControlButtonStoreBarDone : public CUIControlButton {
public:
    CUIControlButtonStoreBarDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBarDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBarPanel : public CUIControlButton3State {
public:
    CUIControlButtonStoreBarPanel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBarPanel() override;
    BOOL Render(BOOL bRender) override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBuySellBuy : public CUIControlButton {
public:
    CUIControlButtonStoreBuySellBuy(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBuySellBuy() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBuySellSell : public CUIControlButton {
public:
    CUIControlButtonStoreBuySellSell(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBuySellSell() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreIdentifyIdentify : public CUIControlButton {
public:
    CUIControlButtonStoreIdentifyIdentify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreIdentifyIdentify() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBuySpellBuy : public CUIControlButton {
public:
    CUIControlButtonStoreBuySpellBuy(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBuySpellBuy() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarStoreBuyDrinksDrink : public CUIControlScrollBar {
public:
    CUIControlScrollBarStoreBuyDrinksDrink(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarStoreBuyDrinksDrink() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
    void UpdateScrollBar();
};

class CUIControlScrollBarStoreStore : public CUIControlScrollBar {
public:
    CUIControlScrollBarStoreStore(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarStoreStore() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
    void UpdateScrollBar();
};

class CUIControlScrollBarStoreIdentify : public CUIControlScrollBar {
public:
    CUIControlScrollBarStoreIdentify(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarStoreIdentify() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
    void UpdateScrollBar();
};

class CUIControlScrollBarStoreGroup : public CUIControlScrollBar {
public:
    CUIControlScrollBarStoreGroup(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarStoreGroup() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
    void UpdateScrollBar();
};

class CUIControlScrollBarStoreSpell : public CUIControlScrollBar {
public:
    CUIControlScrollBarStoreSpell(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarStoreSpell() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
    void UpdateScrollBar();
};

class CUIControlButtonStoreStoreItem : public CUIControlButton3State {
public:
    CUIControlButtonStoreStoreItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreStoreItem() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;

    /* 066E */ CItem m_item;
};

class CUIControlButtonStoreGroupItem : public CUIControlButton3State {
public:
    CUIControlButtonStoreGroupItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreGroupItem() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;

    /* 066E */ CItem m_item;
};

class CUIControlButtonStoreStoreSpell : public CUIControlButton3State {
public:
    CUIControlButtonStoreStoreSpell(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreStoreSpell() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;

    /* 066E */ CResRef m_resRef;
};

class CUIControlButtonStoreRentRoomRoomSelect : public CUIControlButton3State {
public:
    CUIControlButtonStoreRentRoomRoomSelect(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRentRoomRoomSelect() override;
    void OnLButtonClick(CPoint pt) override;

    DWORD GetRoomType();
};

class CUIControlButtonStoreRentRoomRoomPicture : public CUIControlButton3State {
public:
    CUIControlButtonStoreRentRoomRoomPicture(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRentRoomRoomPicture() override;
    void OnLButtonClick(CPoint pt) override;

    DWORD GetRoomType();
};

class CUIControlButtonStoreRentRoomRent : public CUIControlButton {
public:
    CUIControlButtonStoreRentRoomRent(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRentRoomRent() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlPortraitStore : public CUIControlButton {
public:
    CUIControlPortraitStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitStore() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBuyDrinksDrink : public CUIControlButton {
public:
    CUIControlButtonStoreBuyDrinksDrink(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBuyDrinksDrink() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStorePopupDone : public CUIControlButton {
public:
    CUIControlButtonStorePopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStorePopupDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreError : public CUIControlButton {
public:
    CUIControlButtonStoreError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreRequesterItem : public CUIControlButton {
public:
    CUIControlButtonStoreRequesterItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRequesterItem() override;
    BOOL Render(BOOL bForce) override;

    /* 0666 */ CResRef m_resRef;
};

class CUIControlButtonStoreRequesterDone : public CUIControlButton {
public:
    CUIControlButtonStoreRequesterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRequesterDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreRequesterCancel : public CUIControlButton {
public:
    CUIControlButtonStoreRequesterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRequesterCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreRequesterPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonStoreRequesterPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRequesterPlusMinus() override;
    void AdjustValue() override;
};

class CUIControlEditStoreRequesterAmount : public CUIControlEdit {
public:
    CUIControlEditStoreRequesterAmount(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditStoreRequesterAmount() override;
    void KillFocus() override;
};

class CUIControlButtonStoreCloseBag : public CUIControlButton {
public:
    CUIControlButtonStoreCloseBag(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreCloseBag() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreOpenBag : public CUIControlButton {
public:
    CUIControlButtonStoreOpenBag(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreOpenBag() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSTORE_H_ */

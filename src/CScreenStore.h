#ifndef CSCREENSTORE_H_
#define CSCREENSTORE_H_

#include "CBaldurEngine.h"
#include "CItem.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlScrollBar.h"
#include "CVidFont.h"

#define CSCREENSTORE_VIRTUAL_KEYS 91
#define CSCREENSTORE_ERROR_BUTTONS 3

#define CSCREENSTORE_NUM_BOTTOMBUTTON 4

#define CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK0 40
#define CRESUI_CONTROLBUTTONID_STORE_BUYDRINK_DRINK7 47

class CStore;

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
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 0104 */ void CancelEngine() override;
    /* 010C */ void UpdatePartyGoldStatus() override;
    /* 0110 */ void GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture) override;
    /* 0114 */ void SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture) override;

    void EnableMainPanel(BOOL bEnable);
    CUIPanel* GetTopPopup();
    void SummonPopup(DWORD dwPopupId);
    void ResetErrorPanel(CUIPanel* pPanel);
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
    void DestroyGroupItems(BOOL bShutDown);
    void GetStoreItem(INT nIndex, CScreenStoreItem& cItem);
    void DestroyStoreItems(BOOL bShutDown);
    void GetSpellItem(INT nIndex, CScreenStoreItem& cItem);
    void DestroySpellItems();
    void GetIdentifyItem(INT nIndex, CScreenStoreItem& cItem);
    void DestroyIdentifyItems();
    void UpdateGroupCost();
    void UpdateStoreCost();
    void UpdateSpellCost();
    void OnBuyItemButtonClick();
    void OnSellItemButtonClick();
    void OnIdentifyItemButtonClick();
    void OnBuySpellButtonClick();
    void OnRentRoomButtonClick();
    void OnBuyDrinkButtonClick(INT nButton);
    void CheckEnablePanels(BOOL bEnable);
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void OnErrorButtonClick(INT nButton);
    void CloseBag(BOOL bSaveFile);

    void SelectStoreItem(INT nIndex, BOOL bSelected);

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
    /* 04E8 */ CStore* m_pStore;
    /* 04EC */ CStore* m_pBag;
    /* 04F0 */ LONG m_nStoreCost;
    /* 04F4 */ LONG m_nGroupCost;
    /* 04F8 */ DWORD m_dwSpellCost;
    /* 04FC */ int field_4FC;
    /* 0500 */ DWORD m_dwRoomType;
    /* 0580 */ int field_580;
    /* 0584 */ int field_584;
    /* 0588 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 05A4 */ CItem* field_5A4;
    /* 05A8 */ int field_5A8;
    /* 05B4 */ CUIPanel* m_pButtonBar;
    /* 05B8 */ BOOL m_bStoreStarted;
    /* 05BC */ int field_5BC;
    /* 05C4 */ STRREF m_strErrorText;
    /* 05C8 */ INT m_nNumErrorButtons;
    /* 05CC */ STRREF m_strErrorButtonText[CSCREENSTORE_ERROR_BUTTONS];
    /* 05DA */ CVidFont m_preLoadFontRealms;
    /* 0ADA */ CVidFont m_preLoadFontStnSml;
    /* 0FDA */ CVidFont m_preLoadFontTool;
    /* 14DE */ int field_14DE;
    /* 14E2 */ int field_14E2;
    /* 14E6 */ int field_14E6;
};

class CUIControlButtonStoreBarDone : public CUIControlButton {
public:
    CUIControlButtonStoreBarDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBarDone() override;
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
};

class CUIControlButtonStoreRentRoomRoomPicture : public CUIControlButton3State {
public:
    CUIControlButtonStoreRentRoomRoomPicture(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreRentRoomRoomPicture() override;
    void OnLButtonClick(CPoint pt) override;
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
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreBuyDrinksDrink : public CUIControlButton {
public:
    CUIControlButtonStoreBuyDrinksDrink(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreBuyDrinksDrink() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStoreError : public CUIControlButton {
public:
    CUIControlButtonStoreError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStoreError() override;
    void OnLButtonClick(CPoint pt) override;
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

#endif /* CSCREENSTORE_H_ */

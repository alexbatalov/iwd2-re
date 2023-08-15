#ifndef CSCREENSTORE_H_
#define CSCREENSTORE_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CVidFont.h"

#define CSCREENSTORE_VIRTUAL_KEYS 91
#define CSCREENSTORE_ERROR_BUTTONS 3

#define CSCREENSTORE_NUM_BOTTOMBUTTON 4

class CStore;

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
    void ResetErrorPanel(CUIPanel* pPanel);
    void UpdateMainPanel();
    void UpdateBuySellPanel();
    void UpdateIdentifyPanel();
    void UpdateBuySpellPanel();
    void UpdateRentRoomPanel();
    void UpdateBuyDrinksPanel();
    void OnBuyItemButtonClick();
    void OnSellItemButtonClick();
    void OnIdentifyItemButtonClick();
    void OnBuySpellButtonClick();
    void CheckEnablePanels(BOOL bEnable);
    void OnCancelButtonClick();
    void CloseBag(BOOL bSaveFile);

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENSTORE_VIRTUAL_KEYS];
    /* 039E */ BYTE m_pVirtualKeysFlags[CSCREENSTORE_VIRTUAL_KEYS];
    /* 0439 */ BOOLEAN m_bCtrlKeyDown;
    /* 043A */ BOOLEAN m_bShiftKeyDown;
    /* 043C */ BOOL m_bCapsLockKeyOn;
    /* 0440 */ CUIPanel* m_pMainPanel;
    /* 0444 */ int field_444;
    /* 0464 */ int field_464;
    /* 0484 */ INT m_nTopSpellItem;
    /* 04A4 */ int field_4A4;
    /* 04C4 */ INT m_nTopDrinkItem;
    /* 04E8 */ CStore* m_pStore;
    /* 04EC */ CStore* m_pBag;
    /* 04F0 */ int field_4F0;
    /* 04F4 */ int field_4F4;
    /* 04F8 */ int field_4F8;
    /* 04FC */ int field_4FC;
    /* 0580 */ int field_580;
    /* 0584 */ int field_584;
    /* 0588 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
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

class CUIControlPortraitStore : public CUIControlButton {
public:
    CUIControlPortraitStore(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitStore() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSTORE_H_ */

#ifndef CSCREENINVENTORY_H_
#define CSCREENINVENTORY_H_

#include "C2DArray.h"
#include "CBaldurEngine.h"
#include "CGameAnimation.h"
#include "CItem.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlButtonPlusMinus.h"
#include "CUIControlEdit.h"
#include "CUIControlFactory.h"
#include "CUIControlScrollBar.h"

#define CSCREENINVENTORY_VIRTUAL_KEYS 90
#define CSCREENINVENTORY_ERROR_BUTTONS 3

#define CRESUI_CONTROLBUTTONID_INVENTORYCOLOR_LASTCOLOR 33

class CScreenInventory : public CBaldurEngine {
public:
    static const DWORD SLOT_ID[];
    static const INT NUM_SLOTS;
    static const USHORT PERSONAL_INVENTORY_SIZE;
    static const LONG RANGE_SWAPITEM;

    static const CString OPTION_PAUSE_WARNING;

    CScreenInventory();
    /* 0004 */ ~CScreenInventory() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
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
    /* 00E8 */ void UpdateContainerStatus(LONG nContainerId, SHORT nSlotNum) override;
    /* 0104 */ void CancelEngine() override;
    /* 0108 */ void UpdateCharacterStatus(LONG nCharacterId) override;
    /* 010C */ void UpdatePartyGoldStatus() override;

    INT GetSlotByPosition(CPoint pt);
    INT GetPortraitByPosition(CPoint pt);
    void SetErrorString(STRREF strError, COLORREF rgb);
    void UpdatePersonalItemStatus(LONG nCharacterId);
    void UpdateCursorShape();
    LONG FetchGroundPile(SHORT nPortraitId, BOOL bEvenIfDead);
    void FlushGroundPiles();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel(BOOL a1);
    void ResetPopupPanel();
    CUIPanel* GetTopPopup();
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetHistoryPanel();
    void ResetAbilitiesPanel();
    void SelectItemAbility();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void ResetErrorPanel(CUIPanel* pPanel);
    void UpdateErrorPanel(CUIPanel* pPanel);
    void OnRestButtonClick();
    void IsAbilitiesButtonActive();
    void SetUseButtonMode(INT nMode);
    void SetAbilitiesButtonMode(INT nMode);
    void IsUseButtonActive();
    void OnUseButtonClick();
    void OnAbilitiesButtonClick();
    void CheckEnableButtons();
    BOOL IsErrorButtonClickable(INT nButton);
    void OnErrorButtonClick(INT nButton);
    void IdentifyWithSpell();
    void IdentifyWithScroll();
    void CopySpell();
    void DrinkPotion();
    void PlaySwapSound(CItem* pOldItem, CItem* pNewItem);
    void CheckMultiPlayerViewable();
    void UnPauseGame();
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    void IsCharacterInRange();
    void UpdateRequesterPanel();
    void UpdateHistoryPanel(BOOL a1);
    void UpdateAbilitiesPanel();
    void SwapWithAppearance();
    INT MapButtonIdToInventoryId(INT nButton);
    INT MapInventoryIdToButtonId(INT nInventoryId);
    BOOL MapButtonIdToItemInfo(INT nButton, CItem*& pItem, STRREF& description, CResRef& cResIcon, CResRef& cResItem, WORD& wCount);
    void BeginSwap();
    void EndSwap();
    void SwapWithSlot(INT nButtonId, BOOL bShowError, WORD wCount, BOOL bAutoStacking);
    void SwapWithPortrait(INT nButtonId, BOOL bShowError);
    void SwapWithWeaponSet(UINT nIndex);

    /* 0106 */ CGameAnimation m_animation;
    /* 0110 */ CItem* m_pTempItem;
    /* 0114 */ int field_114;
    /* 0118 */ int field_118;
    /* 011C */ unsigned char field_11C;
    /* 011D */ unsigned char field_11D;
    /* 011E */ unsigned char field_11E;
    /* 011F */ unsigned char field_11F;
    /* 0120 */ CKeyInfo m_pVirtualKeys[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 03F0 */ BYTE m_pVirtualKeysFlags[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 044A */ BOOLEAN m_bCtrlKeyDown;
    /* 044C */ CPoint m_cLastMousePosition;
    /* 0454 */ int field_454;
    /* 0458 */ LONG m_nGroundPile[6];
    /* 0470 */ BOOL m_nGroundPileQueried[6];
    /* 0488 */ DWORD m_nRequesterAmount;
    /* 048C */ DWORD m_nRequesterButtonId;
    /* 0490 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 04AC */ int field_4AC;
    /* 04EC */ int field_4EC;
    /* 04F0 */ INT m_nErrorState;
    /* 04F4 */ STRREF m_strErrorText;
    /* 04F8 */ INT m_nNumErrorButtons;
    /* 04FC */ STRREF m_strErrorButtonText[CSCREENINVENTORY_ERROR_BUTTONS];
    /* 0508 */ int m_nAbilitiesButtonMode;
    /* 050C */ int m_nUseButtonMode;
    /* 0510 */ int field_510;
    /* 0514 */ int field_514;
    /* 0518 */ BOOL m_bMultiPlayerViewable;
    /* 051C */ int field_51C;
    /* 0520 */ int field_520;
    /* 0524 */ int field_524;
    /* 0528 */ int field_528;
    /* 052C */ BOOLEAN m_bPauseWarningDisplayed;
    /* 142E */ C2DArray field_142E;
    /* 1452 */ C2DArray field_1452;
    /* 1476 */ C2DArray field_1476;
};

class CUIControlButtonInventorySlot : public CUIControlButton {
public:
    CUIControlButtonInventorySlot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventorySlot() override;
    void OnMouseMove(CPoint pt) override;
    BOOL OnLButtonDown(CPoint pt) override;
    void OnLButtonUp(CPoint pt) override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonDoubleClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;

    /* 0666 */ BOOL field_666;
    /* 066A */ BOOL field_66A;
};

class CUIControlButtonInventoryAppearance : public CUIControlButton {
public:
    CUIControlButtonInventoryAppearance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryAppearance() override;
    BOOL OnLButtonDown(CPoint pt) override;
    BOOL Render(BOOL bForce) override;
};

class CUIControlButtonInventoryWeaponSet : public CUIControlButton3State {
public:
    CUIControlButtonInventoryWeaponSet(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryWeaponSet() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryColor : public CUIControlButton {
public:
    CUIControlButtonInventoryColor(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryColor() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 0666 */ CVidCell* m_pDecal;
    /* 066A */ CVidPalette* m_pPalette;
};

class CUIControlButtonInventoryColorChoice : public CUIControlButton {
public:
    CUIControlButtonInventoryColorChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryColorChoice() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    BOOL GetColorRange(BYTE& colorRange);

    /* 0666 */ CVidCell* m_pDecal;
    /* 066A */ CVidPalette* m_pPalette;
};

class CUIControlScrollBarInventoryGround : public CUIControlScrollBar {
public:
    CUIControlScrollBarInventoryGround(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarInventoryGround() override;
};

class CUIControlButtonInventoryRequesterItem : public CUIControlButton {
public:
    CUIControlButtonInventoryRequesterItem(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryRequesterItem() override;
    BOOL Render(BOOL bForce) override;

    /* 0666 */ CResRef m_resRef;
};

class CUIControlButtonInventoryRequesterDone : public CUIControlButton {
public:
    CUIControlButtonInventoryRequesterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryRequesterDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryRequesterCancel : public CUIControlButton {
public:
    CUIControlButtonInventoryRequesterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryRequesterCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryRequesterPlusMinus : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonInventoryRequesterPlusMinus(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryRequesterPlusMinus() override;
    void AdjustValue() override;
};

class CUIControlEditInventoryRequesterAmount : public CUIControlEdit {
public:
    CUIControlEditInventoryRequesterAmount(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditInventoryRequesterAmount() override;
    void KillFocus() override;
};

class CUIControlButtonInventoryHistoryIcon : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryIcon(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryIcon() override;
    BOOL Render(BOOL bForce) override;

    void SetItem(CItem* pItem);

    /* 0666 */ CItem* m_pItem;
    /* 066A */ CItem m_item;
};

class CUIControlButtonInventoryAbilitiesAbility : public CUIControlButton3State {
public:
    CUIControlButtonInventoryAbilitiesAbility(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryAbilitiesAbility() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryHistoryDone : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryHistoryCancel : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryHistoryImage : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryImage(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryImage() override;
    BOOL Render(BOOL bForce) override;

    void SetImage(CResRef imageResRef);

    /* 0666 */ CResRef m_imageResRef;
};

class CUIControlButtonInventoryHistoryAbilities : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryAbilities(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryAbilities() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonInventoryHistoryUse : public CUIControlButton {
public:
    CUIControlButtonInventoryHistoryUse(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryHistoryUse() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlPortraitInventory : public CUIControlPortraitGeneral {
public:
    CUIControlPortraitInventory(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlPortraitInventory() override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;

    /* 0666 */ int field_666;
};

class CUIControlButtonInventoryError : public CUIControlButton {
public:
    CUIControlButtonInventoryError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonInventoryError() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENINVENTORY_H_ */

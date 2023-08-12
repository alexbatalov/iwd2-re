#ifndef CSCREENINVENTORY_H_
#define CSCREENINVENTORY_H_

#include "C2DArray.h"
#include "CBaldurEngine.h"
#include "CGameAnimation.h"
#include "CKeyInfo.h"

#define CSCREENINVENTORY_VIRTUAL_KEYS 90
#define CSCREENINVENTORY_ERROR_BUTTONS 3

class CItem;

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
    /* 001C */ void EngineDestroyed() override;
    /* 0024 */ void EngineGameInit() override;
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
    /* 0104 */ void CancelEngine() override;
    /* 0108 */ void UpdateCharacterStatus(LONG nCharacterId) override;
    /* 010C */ void UpdatePartyGoldStatus() override;

    INT GetSlotByPosition(CPoint pt);
    INT GetPortraitByPosition(CPoint pt);
    void SetErrorString(STRREF strError, COLORREF rgb);
    void UpdatePersonalItemStatus(LONG nCharacterId);
    void UpdateContainerStatus();
    void UpdateCursorShape();
    void FetchGroundPile();
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
    void OnErrorButtonClick();
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

    /* 0106 */ CGameAnimation m_animation;
    /* 0110 */ CItem* m_pTempItem;
    /* 0114 */ int field_114;
    /* 0118 */ int field_118;
    /* 011E */ unsigned char field_11E;
    /* 011F */ unsigned char field_11F;
    /* 0120 */ CKeyInfo m_pVirtualKeys[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 03F0 */ BYTE m_pVirtualKeysFlags[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 044A */ BOOLEAN m_bCtrlKeyDown;
    /* 044C */ CPoint m_cLastMousePosition;
    /* 0488 */ int field_488;
    /* 048C */ int field_48C;
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

#endif /* CSCREENINVENTORY_H_ */

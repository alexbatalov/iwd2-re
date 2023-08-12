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

    INT GetSlotByPosition(CPoint pt);
    INT GetPortraitByPosition(CPoint pt);
    void SetErrorString(STRREF strError, COLORREF rgb);
    void UpdatePersonalItemStatus();
    void UpdateContainerStatus();
    void UpdateCursorShape();
    void FetchGroundPile();
    void FlushGroundPiles();
    void EnableMainPanel();
    void UpdateMainPanel(BOOL a1);
    void ResetPopupPanel();
    CUIPanel* GetTopPopup();
    void SummonPopup();
    void DismissPopup();
    void ResetHistoryPanel();
    void ResetAbilitiesPanel();
    void SelectItemAbility();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void ResetErrorPanel();
    void UpdateErrorPanel();
    void OnRestButtonClick();
    void IsAbilitiesButtonActive();
    void SetUseButtonMode();
    void SetAbilitiesButtonMode();
    void IsUseButtonActive();
    void OnUseButtonClick();
    void OnAbilitiesButtonClick();
    void CheckEnableButtons();
    void IsErrorButtonClickable();
    void OnErrorButtonClick();
    void IdentifyWithSpell();
    void IdentifyWithScroll();
    void CopySpell();
    void DrinkPotion();
    void PlaySwapSound();
    void CheckMultiPlayerViewable();
    void UnPauseGame();
    void UpdateHelp();
    void IsCharacterInRange();
    void UpdatePartyGoldStatus();

    /* 0106 */ CGameAnimation m_animation;
    /* 0110 */ CItem* m_pTempItem;
    /* 0120 */ CKeyInfo m_pVirtualKeys[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 03F0 */ BYTE m_pVirtualKeysFlags[CSCREENINVENTORY_VIRTUAL_KEYS];
    /* 0490 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 044A */ BOOLEAN m_bCtrlKeyDown;
    /* 044C */ CPoint m_cLastMousePosition;
    /* 142E */ C2DArray field_142E;
    /* 1452 */ C2DArray field_1452;
    /* 1476 */ C2DArray field_1476;
};

#endif /* CSCREENINVENTORY_H_ */

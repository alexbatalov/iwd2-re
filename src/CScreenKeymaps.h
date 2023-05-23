#ifndef CSCREENKEYMAPS_H_
#define CSCREENKEYMAPS_H_

#include "mfc.h"

#include "CBaldurEngine.h"
#include "CInfGame.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"

#define CSCREENKEYMAPS_VIRTUAL_KEYS 92
#define CSCREENKEYMAPS_ERROR_BUTTONS 3
#define CSCREENKEYMAPS_PAGES 1
#define CSCREENKEYMAPS_PER_PAGE 60

class CScreenKeymaps : public CBaldurEngine {
public:
    CScreenKeymaps();
    /* 0004 */ ~CScreenKeymaps() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
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
    /* 0104 */ void CancelEngine() override;

    void HandleKeyDown(BYTE nKey);
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void StartKeymaps();
    void sub_639E70();
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void OnPageButtonClick(INT nButton);
    void OnDefaultButtonClick();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void OnErrorButtonClick(INT nButton);
    void sub_63A660(CPoint pt);
    void sub_63A7A0(CPoint pt);
    void SetKeymap(INT nMode, INT nIndex, BYTE nKey, BYTE nKeyFlag);
    void SelectKeymap(INT nIndex);

    static INT dword_8B3FE0[CSCREENKEYMAPS_PAGES][CSCREENKEYMAPS_PER_PAGE];
    static STRREF dword_8B40D0[CSCREENKEYMAPS_PAGES][CSCREENKEYMAPS_PER_PAGE];

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENKEYMAPS_VIRTUAL_KEYS];
    /* 03E6 */ BYTE m_pVirtualKeysFlags[CSCREENKEYMAPS_VIRTUAL_KEYS];
    /* 0442 */ BOOL m_bSystemKeyShift;
    /* 0446 */ BOOL m_bSystemKeyCapsLock;
    /* 044A */ int field_44A;
    /* 044E */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 046A */ STRREF m_dwErrorTextId;
    /* 046E */ STRREF m_strErrorButtonText[3];
    /* 047A */ INT m_nNumErrorButtons;
    /* 047E */ BOOLEAN m_bSystemKeyCtrl;
    /* 0480 */ INT m_nPage;
    /* 0484 */ BYTE m_pKeymap[CINFGAME_KEYMAP_SIZE];
    /* 05F8 */ BYTE m_pKeymapFlags[CINFGAME_KEYMAP_SIZE];
    /* 076C */ INT m_nHighlightedKeymapIndex;
    /* 0770 */ INT m_nSelectedKeymapIndex;
    /* 0774 */ BYTE m_nConflictKey;
    /* 0775 */ BYTE m_nConflictKeyFlag;
    /* 0776 */ BOOLEAN m_bFromMainMenu;
};

class CUIControlButtonKeymap : public CUIControlButton {
public:
    CUIControlButtonKeymap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonKeymap() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENKEYMAPS_H_ */

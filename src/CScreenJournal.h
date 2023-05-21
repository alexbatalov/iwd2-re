#ifndef CSCREENJOURNAL_H_
#define CSCREENJOURNAL_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CVidFont.h"

#define CSCREENJOURNAL_VIRTUAL_KEYS 92
#define CSCREENJOURNAL_ERROR_BUTTONS 3

class CScreenJournal : public CBaldurEngine {
public:
    CScreenJournal();
    /* 0004 */ ~CScreenJournal() override;
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
    /* 00F0 */ void OnRestButtonClick() override;
    /* 0104 */ void CancelEngine() override;

    void UpdateMainPanel();
    void EnableMainPanel(BOOL bEnable);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void ResetAnnotatePanel();
    void OnErrorButtonClick(INT nButton);
    void OnCancelButtonClick();

    // NOTE: Seen in `OnErrorButtonClick` assertion.
    INT GetNumErrorButtons() { return m_nNumErrorButtons; }

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENJOURNAL_VIRTUAL_KEYS];
    /* 03E6 */ BYTE m_pVirtualKeysFlags[CSCREENJOURNAL_VIRTUAL_KEYS];
    /* 0442 */ INT m_nChapter;
    /* 0446 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0462 */ DWORD m_dwErrorState;
    /* 0466 */ DWORD m_dwErrorTextId;
    /* 046A */ INT m_nNumErrorButtons;
    /* 046E */ DWORD m_strErrorButtonText[CSCREENJOURNAL_ERROR_BUTTONS];
    /* 047A */ BOOL m_bShiftKeyDown;
    /* 047E */ BOOL m_bCapsLockKeyOn;
    /* 0482 */ BOOLEAN m_bCtrlKeyDown;
    /* 0483 */ unsigned char field_483;
    /* 0484 */ CResRef field_484;
    /* 048C */ CResRef field_48C;
    /* 049C */ CVidFont m_preLoadFontRealms;
    /* 099C */ CVidFont m_preLoadFontTool;
    /* 0E9C */ int field_E9C;
    /* 0EA0 */ unsigned char field_EA0;
};

class CUIControlButtonJournalScroll : public CUIControlButton {
public:
    CUIControlButtonJournalScroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonJournalScroll() override;
    void OnLButtonClick(CPoint pt) override;
    void OnLButtonDoubleClick(CPoint pt) override;
};

class CUIControlButtonJournalError : public CUIControlButton {
public:
    CUIControlButtonJournalError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonJournalError() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENJOURNAL_H_ */

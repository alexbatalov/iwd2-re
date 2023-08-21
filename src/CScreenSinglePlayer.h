#ifndef CSCREENSINGLEPLAYER_H_
#define CSCREENSINGLEPLAYER_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlScrollBar.h"
#include "CVidFont.h"

#define CSCREENSINGLEPLAYER_VIRTUAL_KEYS 92

// NOTE: There is a misleading typo in the original code. This constant is
// called `CSCREENMULTIPLAYER_ERROR_BUTTONS` as can be seen in
// `CScreenSinglePlayer::OnErrorButtonClick` assertion. Renamed for clarity.
#define CSCREENSINGLEPLAYER_ERROR_BUTTONS 3

class CScreenSinglePlayer : public CBaldurEngine {
public:
    static const CString TOKEN_GOLD;
    static const CString PARTY;
    static const CString DESCR;
    static const CString CHAR;
    static const CString NAME;

    CScreenSinglePlayer();
    /* 0004 */ ~CScreenSinglePlayer() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
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

    void ResetPopupPanel(DWORD dwPanelId);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    BOOL IsMainDoneButtonClickable();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void CheckEnableCharacters();
    void CheckCharacterButtons(INT nCharacterSlot, BOOL& bReadyActive, BOOL& bModifyPlayerActive, BOOL& bModifyCharacterActive);
    void UpdateMainPanelCharacter(CUIPanel* pPanel, INT nCharacterSlot);
    void UpdateModifyCharacterPanel();
    void OnMainDoneButtonClick();
    BOOL IsModifyButtonClickable();
    void OnModifyButtonClick();
    void OnErrorButtonClick(INT nButton);
    void ResetErrorPanel(CUIPanel* pPanel);
    void StartSinglePlayer(INT nEngineState);
    void sub_663EB0();
    void UpdatePartySelectionPanel();
    void OnPartySelectionDoneButtonClick();
    void sub_6644B0(CUIPanel* pPanel);
    BOOL IsPortraitButtonClickable(INT nCharacterSlot);
    void OnPortraitButtonClick(INT nButton);
    void OnLogoutButtonClick();
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);

    static int dword_8B4828;
    static char byte_8F64C0[20];
    static char byte_8F64E0[4096];
    static char byte_8F74E0[32];

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENSINGLEPLAYER_VIRTUAL_KEYS];
    /* 03D6 */ BYTE m_pVirtualKeysFlags[CSCREENSINGLEPLAYER_VIRTUAL_KEYS];
    /* 0430 */ BOOL m_bCtrlKeyDown;
    /* 0434 */ BOOL m_bShiftKeyDown;
    /* 0438 */ BOOL m_bCapsLockKeyOn;
    /* 043C */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0458 */ int field_458;
    /* 045C */ int field_45C;
    /* 0460 */ int field_460;
    /* 0460 */ int field_464;
    /* 0468 */ INT m_nErrorState;
    /* 046C */ STRREF m_dwErrorTextId;
    /* 0470 */ INT m_nNumErrorButtons;
    /* 0474 */ STRREF m_strErrorButtonText[CSCREENSINGLEPLAYER_ERROR_BUTTONS];
    /* 0480 */ int field_480;
    /* 0484 */ INT field_484;
    /* 0488 */ unsigned char field_488;
    /* 048A */ BOOL m_bLastLockAllowInput;
    /* 048E */ CVidFont m_preLoadFontRealms;
    /* 098E */ CVidFont m_preLoadFontStnSml;
    /* 0E8E */ CVidFont m_preLoadFontTool;
    /* 138E */ int field_138E;
    /* 1392 */ int m_nPartyCount;
    /* 1396 */ INT m_nTopParty;
    /* 139A */ INT m_nParty;
    /* 139E */ int field_139E;
};

class CUIControlButtonSinglePlayerReady : public CUIControlButton3State {
public:
    CUIControlButtonSinglePlayerReady(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerReady() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerPortrait : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerPortrait() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    void SetPortrait(const CResRef& resRef);

    /* 0666 */ CResRef m_portraitResRef;
};

class CUIControlButtonSinglePlayerCharacter : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerCharacter() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerDone : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerLogout : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerLogout(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerLogout() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerModifyCharacterCreate : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerModifyCharacterCreate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerModifyCharacterCreate() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerModifyCharacterDelete : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerModifyCharacterDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerModifyCharacterDelete() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerModifyCharacterCancel : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerModifyCharacterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerModifyCharacterCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerModify : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerModify() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerError : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerViewCharacterDone : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerViewCharacterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerViewCharacterDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerPartyCancel : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerPartyCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerPartyCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerPartyDone : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerPartyDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerPartyDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerPartyModify : public CUIControlButton {
public:
    CUIControlButtonSinglePlayerPartyModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerPartyModify() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSinglePlayerPartySelection : public CUIControlButton3State {
public:
    CUIControlButtonSinglePlayerPartySelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSinglePlayerPartySelection() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlScrollBarSinglePlayerParties : public CUIControlScrollBar {
public:
    CUIControlScrollBarSinglePlayerParties(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarSinglePlayerParties();
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void InvalidateItems();
};

#endif /* CSCREENSINGLEPLAYER_H_ */

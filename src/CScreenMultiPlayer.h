#ifndef CSCREENMULTIPLAYER_H_
#define CSCREENMULTIPLAYER_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton3State.h"
#include "CUIControlEdit.h"
#include "CVidFont.h"

#define CSCREENMULTIPLAYER_VIRTUAL_KEYS 90
#define CSCREENMULTIPLAYER_ERROR_BUTTONS 3

#define CRESUI_CONTROLBUTTONID_MULTIPLAYER_PLAYER0 12
#define CRESUI_CONTROLBUTTONID_MULTIPLAYER_PLAYER5 17

#define CRESUI_CONTROLBUTTONID_MULTIPLAYER_MODIFYPLAYER_PLAYER5 5

class CAIObjectType;
class CDerivedStats;

class CScreenMultiPlayer : public CBaldurEngine {
public:
    static const CString TOKEN_GOLD;

    CScreenMultiPlayer();
    /* 0004 */ ~CScreenMultiPlayer() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
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
    /* 0110 */ void GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture) override;
    /* 0114 */ void SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture) override;

    void ClearChatMessages();

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
    void UpdateOptionsPanel();
    void UpdateMainPanel();
    void CheckEnableCharacters();
    void CheckCharacterButtons(INT nCharacterSlot, BOOL& bReadyActive, BOOL& bModifyPlayerActive, BOOL& bModifyCharacterActive);
    void UpdateMainPanelCharacter(CUIPanel* pPanel, INT nCharacterSlot);
    void UpdatePermissionsPanel();
    void UpdatePermissionsPanelPlayer(CUIPanel* pPanel, INT nPlayerSlot);
    void UpdateModifyPlayerPanel();
    void UpdateModifyCharacterPanel();
    void OnMainDoneButtonClick();
    void StartMultiPlayer(INT nEngineState);
    BOOL IsModifyButtonClickable();
    void OnModifyButtonClick();
    void OnErrorButtonClick(INT nButton);
    void ResetErrorPanel(CUIPanel* pPanel);
    void FocusChatEditBox();
    void OnKickPlayerButtonClick(INT nButton);
    void UpdateExperienceEntry(CUIControlTextDisplay* pText, const CAIObjectType& typeAI, CDerivedStats& DStats, DWORD nSpecialization, BYTE nBestClass, DWORD dwFlags);
    void ResetViewCharacterPanel(CUIPanel* pPanel);
    BOOL IsPortraitButtonClickable(INT nCharacterSlot);
    void OnPortraitButtonClick(INT nButton);
    void OnLogoutButtonClick();
    void CopyChatEditBox(CUIPanel* pFrom, CUIPanel* pTo);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);

    void SetPermissionToolTips(CUIPanel* pPanel, DWORD nHeaderID, DWORD nFirstButtonID, DWORD nLastButtonID, STRREF strRef);
    void UpdatePermission(CUIPanel* pPanel, DWORD nButtonID, BOOL bEnabled, BOOL bSelected);

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENMULTIPLAYER_VIRTUAL_KEYS];
    /* 03D6 */ BYTE m_pVirtualKeysFlags[CSCREENMULTIPLAYER_VIRTUAL_KEYS];
    /* 0430 */ BOOL m_bCtrlKeyDown;
    /* 0434 */ BOOL m_bShiftKeyDown;
    /* 0438 */ BOOL m_bCapsLockKeyOn;
    /* 043C */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0458 */ int field_458;
    /* 045C */ int field_45C;
    /* 0460 */ INT m_nChatMessageCount;
    /* 0464 */ INT m_nPermissionsChatMessageCount;
    /* 0468 */ INT m_nErrorState;
    /* 046C */ STRREF m_dwErrorTextId;
    /* 0470 */ INT m_nNumErrorButtons;
    /* 0474 */ STRREF m_strErrorButtonText[CSCREENMULTIPLAYER_ERROR_BUTTONS];
    /* 0480 */ INT m_nKickPlayerSlot;
    /* 0484 */ INT m_nCharacterSlot;
    /* 0488 */ BOOLEAN m_bMultiplayerStartup;
    /* 048A */ BOOL m_bLastLockAllowInput;
    /* 048E */ CVidFont m_preLoadFontRealms;
    /* 098E */ CVidFont m_preLoadFontStnSml;
    /* 0E8E */ CVidFont m_preLoadFontTool;
    /* 138E */ int field_138E;
};

class CUIControlButtonMultiPlayerReady : public CUIControlButton3State {
public:
    CUIControlButtonMultiPlayerReady(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerReady() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerPortrait : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPortrait() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    void SetPortrait(const CResRef& resRef);

    CResRef GetPortrait();

    /* 0666 */ CResRef m_portraitResRef;
};

class CUIControlButtonMultiPlayerPlayer : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPlayer() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerCharacter : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerCharacter() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerDone : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerOptions : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerOptions() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerLogout : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerLogout(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerLogout() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlEditMultiPlayerChat : public CUIControlEdit {
public:
    CUIControlEditMultiPlayerChat(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditMultiPlayerChat() override;
    void OnEditReturn(CString sText) override;
};

class CUIControlButtonMultiPlayerPermissionsPermission : public CUIControlButton3State {
public:
    CUIControlButtonMultiPlayerPermissionsPermission(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPermissionsPermission() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ SHORT m_nDisabledSelectedFrame;
};

class CUIControlButtonMultiPlayerPermissionsKick : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerPermissionsKick(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPermissionsKick() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerPermissionsOptions : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerPermissionsOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPermissionsOptions() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerPermissionsListen : public CUIControlButton3State {
public:
    CUIControlButtonMultiPlayerPermissionsListen(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPermissionsListen() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ SHORT m_nDisabledSelectedFrame;
};

class CUIControlButtonMultiPlayerPermissionsDone : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerPermissionsDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerPermissionsDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerOptionsImport : public CUIControlButton3State {
public:
    CUIControlButtonMultiPlayerOptionsImport(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerOptionsImport() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ SHORT m_nDisabledSelectedFrame;
};

class CUIControlButtonMultiPlayerOptionsCancel : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerOptionsCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerOptionsCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerOptionsDone : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerOptionsDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerOptionsDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModifyCharacterCreate : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModifyCharacterCreate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModifyCharacterCreate() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModifyCharacterDelete : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModifyCharacterDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModifyCharacterDelete() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModifyCharacterCancel : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModifyCharacterCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModifyCharacterCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModifyPlayerPlayer : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModifyPlayerPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModifyPlayerPlayer() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModifyPlayerCancel : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModifyPlayerCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModifyPlayerCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerModify : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerModify(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerModify() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerError : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerViewCharacterDone : public CUIControlButton {
public:
    CUIControlButtonMultiPlayerViewCharacterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerViewCharacterDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMultiPlayerSelection : public CUIControlButton3State {
public:
    CUIControlButtonMultiPlayerSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMultiPlayerSelection() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ SHORT m_nDisabledSelectedFrame;
};

#endif /* CSCREENMULTIPLAYER_H_ */

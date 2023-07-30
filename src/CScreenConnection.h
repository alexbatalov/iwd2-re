#ifndef CSCREENCONNECTION_H_
#define CSCREENCONNECTION_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlEdit.h"
#include "CUIControlTextDisplay.h"
#include "CVidCell.h"
#include "CVidFont.h"

#define CSCREENCONNECTION_VIRTUAL_KEYS 91
#define CSCREENCONNECTION_ERROR_BUTTONS 2

class CUIPanel;

class CScreenConnection : public CBaldurEngine {
public:
    static const BYTE DEFAULT_SESSION_NAME;
    static const BYTE DEFAULT_SESSION_PASSWORD;
    static const BYTE DEFAULT_PLAYER_NAME;
    static const BYTE DEFAULT_TCP_IP_ADDRESS;
    static const BYTE DEFAULT_PHONE_NUMBER;
    static const CString TOKEN_SERVERVERSION;
    static const CString TOKEN_CLIENTVERSION;
    static BOOLEAN byte_8B3340;
    static BOOLEAN byte_8B3341;
    static BOOLEAN byte_8B3342;
    static int dword_8F3768;
    static BOOLEAN byte_8F376C;

    CScreenConnection();
    ~CScreenConnection();
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
    /* 00AC */ void OnKeyDown(SHORT nKeysFlags) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 0104 */ void CancelEngine() override;

    // Seen in `OnJoinGameButtonClick` assertion.
    INT GetSessionIndex() { return m_nSessionIndex; }

    void RenderTorch();
    CUIPanel* GetTopPopup();
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void ResetPopupPanel(DWORD nID);
    void UpdatePopupPanel(DWORD nID);
    void SummonPopup(DWORD nID);
    void DismissPopup();
    void OnLoadGameButtonClick(int a1);
    void sub_5FCF80();
    void OnNewGameButtonClick();
    BOOL IsDoneButtonClickable();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void OnJoinGameButtonClick();
    void sub_5FEB70();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void UpdateSessionList(CUIPanel* pPanel, DWORD nTextId);
    void UpdateProtocolPanel();
    void UpdateSerialPanel();
    void UpdateModemPanel();
    void UpdateTCPIPPanel();
    void sub_5FFDF0();
    void ResetProtocolPanel();
    void ResetSerialPanel();
    void ResetModemPanel();
    void ResetTCPIPPanel();
    void ResetCreateGamePanel();
    void ResetPasswordPanel();
    void ResetPhoneNumberPanel();
    void ResetPlayerNamePanel();
    void ResetLobbyPanel();
    void sub_600600();
    void StartConnection(BOOLEAN bDirectPlayLobby);
    void SetEliminateInitialize(BOOLEAN bEliminateInitialize);
    void OnErrorButtonClick(INT nButton);
    void ResetErrorPanel(CUIPanel* pPanel);
    void HandleEMEvent(BYTE nEvent, BYTE nEventStage);
    void HandleJoinCompletion(BYTE nEvent);
    BOOL AutoStartInitialize();
    void AutoStartConnect();
    void AutoStartDirectPlayLobby();
    void AutoSelectServiceProvider();
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    void OnLobbyNewGameButtonClick();
    void OnLobbyLoadGameButtonClick();
    void OnLobbyExitButtonClick();
    void ReadyEndCredits();
    void ShowSessionTerminatedMessage();
    void ResetVersionMismatchPanel(CUIPanel* pPanel);

    /* 0106 */ int field_106;
    /* 010A */ CKeyInfo m_pVirtualKeys[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 03E2 */ BYTE m_pVirtualKeysFlags[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 043E */ BOOL m_bCtrlKeyDown;
    /* 0442 */ BOOL m_bShiftKeyDown;
    /* 0446 */ BOOL m_bCapsLockKeyOn;
    /* 044A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0466 */ INT m_nProtocol;
    /* 046A */ UINT m_nSerialPort;
    /* 046E */ UINT m_nSerialBaudRate;
    /* 0472 */ INT m_nModemAddress;
    /* 0476 */ INT m_nSessionIndex;
    /* 047A */ GUID m_sessionGuid;
    /* 048A */ DWORD m_dwLastSessionRefresh;
    /* 048E */ INT m_nEnumServiceProvidersCountDown;
    /* 0492 */ BOOL m_bStartedCountDown;
    /* 0497 */ BOOLEAN m_bEliminateInitialize;
    /* 04B2 */ BOOL m_bAllowInput;
    /* 0496 */ unsigned char field_496;
    /* 0498 */ BOOLEAN m_bEMSwapped;
    /* 0499 */ BOOLEAN m_bEMValue;
    /* 049A */ BOOLEAN m_bEMWaiting;
    /* 049B */ BYTE m_nEMEvent;
    /* 049C */ BYTE m_nEMEventStage;
    /* 049D */ BOOLEAN m_bDirectPlayLobby;
    /* 049E */ INT m_nErrorState;
    /* 04A2 */ STRREF m_strErrorText;
    /* 04A6 */ INT m_nNumErrorButtons;
    /* 04AA */ STRREF m_strErrorButtonText[CSCREENCONNECTION_ERROR_BUTTONS];
    /* 04B6 */ unsigned char field_4B6;
    /* 04B7 */ BOOLEAN m_bJoinWaiting;
    /* 04B8 */ BOOLEAN m_bJoinComplete;
    /* 04B9 */ BYTE m_nJoinEvent;
    /* 04BA */ INT m_nJoinErrorCode;
    /* 04BE */ BOOLEAN m_bJoinReturnValue;
    /* 04C0 */ CVidFont m_preLoadFontRealms;
    /* 09C0 */ CVidFont m_preLoadFontStnSml;
    /* 0F9A */ BOOL m_bIsNight;
    /* 0F9E */ BOOL m_bPlayEndCredits;
    /* 0FA2 */ BOOL m_bExitProgram;
    /* 0FA6 */ unsigned char field_FA6;
    /* 0FA8 */ int field_FA8;
    /* 0FAC */ int field_FAC;
    /* 0FB4 */ int field_FB4;
    /* 0FB8 */ int field_FB8;
    /* 0EC0 */ CVidCell m_vcTorch;
    /* 0FB0 */ int field_FB0;
};

class CUIControlButtonConnectionGameMode : public CUIControlButton {
public:
    CUIControlButtonConnectionGameMode(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionGameMode();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionQuitGame : public CUIControlButton {
public:
    CUIControlButtonConnectionQuitGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionQuitGame();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionNewGame : public CUIControlButton {
public:
    CUIControlButtonConnectionNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionNewGame();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionQuickLoad : public CUIControlButton {
public:
    CUIControlButtonConnectionQuickLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionQuickLoad();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionLoadGame : public CUIControlButton {
public:
    CUIControlButtonConnectionLoadGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionLoadGame();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionJoinGame : public CUIControlButton {
public:
    CUIControlButtonConnectionJoinGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionJoinGame();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayConnectionTCPIPSessions : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayConnectionTCPIPSessions(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayConnectionTCPIPSessions() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonConnectionPopupDone : public CUIControlButton {
public:
    CUIControlButtonConnectionPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionPopupDone();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionPopupCancel : public CUIControlButton {
public:
    CUIControlButtonConnectionPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionPopupCancel();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionProtocolProtocol : public CUIControlButton3State {
public:
    CUIControlButtonConnectionProtocolProtocol(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionProtocolProtocol() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayConnectionModems : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayConnectionModems(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonConnectionSerialPort : public CUIControlButton3State {
public:
    CUIControlButtonConnectionSerialPort(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionSerialPort() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionSerialBaudRate : public CUIControlButton3State {
public:
    CUIControlButtonConnectionSerialBaudRate(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionSerialBaudRate() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlEditConnectionWithDefault : public CUIControlEdit {
public:
    CUIControlEditConnectionWithDefault(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo, BYTE nField);
    ~CUIControlEditConnectionWithDefault();
    void OnKeyDown(SHORT nKey) override;
    void OnEditReturn(CString sText) override;

    /* 0892 */ BYTE m_nField;
};

class CUIControlButtonConnectionCreateGameNewGame : public CUIControlButton {
public:
    CUIControlButtonConnectionCreateGameNewGame(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionCreateGameNewGame() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnection604C30 : public CUIControlButton {
public:
    CUIControlButtonConnection604C30(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnection604C30() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayConnection604E90 : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayConnection604E90(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    ~CUIControlTextDisplayConnection604E90() override;
    void OnItemSelected(LONG lMarker) override;
};

class CUIControlButtonConnectionErrorButton : public CUIControlButton {
public:
    CUIControlButtonConnectionErrorButton(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionErrorButton() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnectionLobbyMenu : public CUIControlButton {
public:
    CUIControlButtonConnectionLobbyMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnectionLobbyMenu() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnection6052A0 : public CUIControlButton3State {
public:
    CUIControlButtonConnection6052A0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnection6052A0() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonConnection605570 : public CUIControlButton {
public:
    CUIControlButtonConnection605570(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonConnection605570() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENCONNECTION_H_ */

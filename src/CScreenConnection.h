#ifndef CSCREENCONNECTION_H_
#define CSCREENCONNECTION_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CVidCell.h"
#include "CVidFont.h"

#define CSCREENCONNECTION_VIRTUAL_KEYS 91

class CUIPanel;

class CScreenConnection : public CBaldurEngine {
public:
    static const CString TOKEN_SERVERVERSION;
    static const CString TOKEN_CLIENTVERSION;
    static int dword_8F3768;

    CScreenConnection();
    ~CScreenConnection();
    /* 0018 */ void EngineDeactivated() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 0104 */ void CancelEngine() override;

    void SummonPopup(DWORD nID);
    void DismissPopup();
    void sub_5FCA00(int a1);
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void StartConnection(BOOLEAN bDirectPlayLobby);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);
    void sub_6024A0();
    void ShowSessionTerminatedMessage();

    /* 0106 */ int field_106;
    /* 010A */ CKeyInfo m_pVirtualKeys[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 03E2 */ BYTE m_pVirtualKeysFlags[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 043E */ BOOL m_bCtrlKeyDown;
    /* 0442 */ int field_442;
    /* 0446 */ int field_446;
    /* 044A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0466 */ INT m_nProtocol;
    /* 046A */ int field_46A;
    /* 046E */ int field_46E;
    /* 0472 */ int field_472;
    /* 0476 */ int field_476;
    /* 048A */ DWORD m_dwLastSessionRefresh;
    /* 048E */ INT m_nEnumServiceProvidersCountDown;
    /* 0492 */ BOOL m_bStartedCountDown;
    /* 0497 */ BOOLEAN m_bEliminateInitialize;
    /* 04B2 */ BOOL m_bAllowInput;
    /* 0496 */ unsigned char field_496;
    /* 0498 */ unsigned char field_498;
    /* 0499 */ unsigned char field_499;
    /* 049A */ BOOLEAN field_49A;
    /* 049B */ unsigned char field_49B;
    /* 049C */ unsigned char field_49C;
    /* 049D */ BOOLEAN m_bDirectPlayLobby;
    // Some flags related to popup.
    /* 049E */ int field_49E;
    /* 04A2 */ STRREF m_popupText;
    /* 04A6 */ int field_4A6;
    // Maybe part of array.
    /* 04AA */ STRREF m_popupButtonText1;
    /* 04AE */ STRREF m_popupButtonText2;
    /* 04B6 */ unsigned char field_4B6;
    /* 04B7 */ unsigned char field_4B7;
    /* 04B8 */ unsigned char field_4B8;
    /* 04B9 */ unsigned char field_4B9;
    /* 04BA */ int field_4BA;
    /* 04BE */ unsigned char field_4BE;
    /* 04C0 */ CVidFont field_4C0;
    /* 09C0 */ CVidFont field_9C0;
    /* 0F9A */ int field_F9A;
    /* 0F9E */ BOOL m_bPlayEndCredits;
    /* 0FA2 */ BOOL m_bExitProgram;
    /* 0FA6 */ unsigned char field_FA6;
    /* 0FA8 */ int field_FA8;
    /* 0FAC */ int field_FAC;
    /* 0FB4 */ int field_FB4;
    /* 0FB8 */ int field_FB8;
    /* 0EC0 */ CVidCell field_EC0;
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

#endif /* CSCREENCONNECTION_H_ */

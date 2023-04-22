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
    /* 0104 */ void CancelEngine() override;

    void SummonPopup(DWORD nID);
    void DismissPopup();
    void sub_5FCA00(int a1);
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void StartConnection(BOOLEAN bDirectPlayLobby);
    void sub_6024A0();

    /* 010A */ CKeyInfo m_pVirtualKeys[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 03E2 */ BYTE m_pVirtualKeysFlags[CSCREENCONNECTION_VIRTUAL_KEYS];
    /* 043E */ BOOL m_bCtrlKeyDown;
    /* 044A */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0466 */ INT m_nProtocol;
    /* 048A */ DWORD m_dwLastSessionRefresh;
    /* 048E */ INT m_nEnumServiceProvidersCountDown;
    /* 0492 */ BOOL m_bStartedCountDown;
    /* 0497 */ BOOLEAN m_bEliminateInitialize;
    /* 04B2 */ BOOL m_bAllowInput;
    /* 049A */ BOOLEAN field_49A;
    /* 049D */ BOOLEAN m_bDirectPlayLobby;
    // Some flags related to popup.
    /* 049E */ int field_49E;
    /* 04A2 */ STRREF m_popupText;
    // Maybe part of array.
    /* 04AA */ STRREF m_popupButtonText1;
    /* 04AE */ STRREF m_popupButtonText2;
    /* 04C0 */ CVidFont field_4C0;
    /* 09C0 */ CVidFont field_9C0;
    /* 0EC0 */ CVidCell field_EC0;
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

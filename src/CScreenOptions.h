#ifndef CSCREENOPTIONS_H_
#define CSCREENOPTIONS_H_

#include "CBaldurEngine.h"

#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlSlider.h"
#include "CVidFont.h"

#define CSCREENOPTIONS_VIRTUAL_KEYS 90
#define CSCREENOPTIONS_ERROR_BUTTONS 3

class CGameOptions;

class CScreenOptions : public CBaldurEngine {
public:
    CScreenOptions();
    /* 0004 */ ~CScreenOptions() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0060 */ BOOL CheckMouseMove() override;
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

    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD nID);
    void ResetErrorPanel(CUIPanel* pPanel);
    void UpdatePopupPanel(DWORD dwPanelId, BOOLEAN bInitialUpdate);
    void QuitGame();
    void SaveGraphicModeOptions();
    void CheckGraphicModeOptions(CUIPanel* pPanel);
    void LoadGame();
    void UpdateGraphicsPanel(BOOLEAN bInitialUpdate);
    void UpdateSoundPanel(BOOLEAN bInitialUpdate);
    void UpdateSelectSoundsPanel(BOOLEAN bInitialUpdate);
    void UpdateGamePlayPanel(BOOLEAN bInitialUpdate);
    void UpdateFeedbackPanel(BOOLEAN bInitialUpdate);
    void UpdateAutoPausePanel(BOOLEAN bInitialUpdate);
    void OnErrorButtonClick(INT nButton);
    void PushOptions(CGameOptions* pOptions);
    void PopOptions(CGameOptions* pOptions);
    void UpdateHelp(DWORD dwPanelId, DWORD dwTextId, DWORD dwStrId);

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENOPTIONS_VIRTUAL_KEYS];
    /* 03D6 */ BYTE m_pVirtualKeysFlags[CSCREENOPTIONS_VIRTUAL_KEYS];
    /* 0430 */ BOOL m_bExitProgram;
    /* 0434 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0450 */ DWORD m_dwErrorTextId;
    /* 0454 */ DWORD m_dwErrorState;
    /* 0458 */ INT m_nNumErrorButtons;
    /* 045C */ DWORD m_strErrorButtonText[CSCREENOPTIONS_ERROR_BUTTONS];
    /* 0468 */ CTypedPtrList<CPtrList, CGameOptions*> m_lOptionsStack;
    /* 0484 */ BOOL m_bSpriteMirror;
    /* 0488 */ USHORT m_nBpp;
    /* 048A */ BOOLEAN m_bFullscreen;
    /* 048B */ BOOLEAN m_bSoftMirrorBlt;
    /* 048C */ BOOLEAN m_bSoftSrcKeyBlt;
    /* 048D */ BOOLEAN m_bSoftBlt;
    /* 048E */ BOOLEAN m_bCtrlKeyDown;
    /* 0490 */ CVidFont m_preLoadFontRealms;
    /* 0990 */ CVidFont m_preLoadFontStnSml;
    /* 0E90 */ BOOLEAN m_bTranslucentBlts;
    /* 0E91 */ BOOLEAN m_bStaticAnimations;
    /* 0E92 */ BOOLEAN m_bFromMainMenu;
};

class CUIControlButtonOptionsSelection : public CUIControlButton3State {
public:
    CUIControlButtonOptionsSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsSelection();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonOptionsRadio : public CUIControlButton3State {
public:
    CUIControlButtonOptionsRadio(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsRadio();
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ SHORT m_nDisabledSelectedFrame;
};

class CUIControlSliderOptionsSlider : public CUIControlSlider {
public:
    CUIControlSliderOptionsSlider(CUIPanel* pale, UI_CONTROL_SLIDER* controlInfo);
    ~CUIControlSliderOptionsSlider();
    /* 0068 */ void OnThumbChange() override;
    /* 006C */ void OnThumbFinalChange() override;
};

class CUIControlButtonOptionsGameCommand : public CUIControlButton {
public:
    CUIControlButtonOptionsGameCommand(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsGameCommand();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonOptionsPopupDone : public CUIControlButton {
public:
    CUIControlButtonOptionsPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsPopupDone();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonOptionsPopupCancel : public CUIControlButton {
public:
    CUIControlButtonOptionsPopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsPopupCancel();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonOptionsError : public CUIControlButton {
public:
    CUIControlButtonOptionsError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonOptionsError();
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENOPTIONS_H_ */

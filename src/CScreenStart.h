#ifndef CSCREENSTART_H_
#define CSCREENSTART_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CVidFont.h"

#define CSCREENSTART_VIRTUAL_KEYS 5
#define CSCREENSTART_ERROR_BUTTONS 3

class CUIPanel;

// NOTE: Looks like this screen is not used in IWD2. The main menu screen is
// `CScreenConnection`.
class CScreenStart : public CBaldurEngine {
public:
    static const CString TOKEN_SERVERVERSION;
    static const CString TOKEN_CLIENTVERSION;

    CScreenStart();
    /* 0004 */ ~CScreenStart() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00AC */ void OnKeyDown(SHORT nKeyFlags) override;
    /* 00C4 */ void TimerSynchronousUpdate() override;

    void UpdateMainPanel();
    void OnQuitButtonClick();
    void sub_66F990();
    void EnableMainPanel(BOOL bEnabled);
    void SummonPopup(DWORD nID);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void OnErrorButtonClick(DWORD nID);
    void ResetVersionMismatchPanel(CUIPanel* pPanel);
    void sub_6702C0();

    void SetPopupEnabled(DWORD nID, BOOL bEnabled);
    void ResetPopupPanel(DWORD nID);
    void OnNewGameButtonClick();
    void OnLoadGameButtonClick();
    void OnPreGenerateButtonClick();

    /* 0106 */ int field_106;
    /* 010A */ BOOL m_bExitProgram;
    /* 010E */ CKeyInfo m_pVirtualKeys[CSCREENSTART_VIRTUAL_KEYS];
    /* 0136 */ BOOL m_bCtrlKeyDown;
    /* 013A */ BYTE m_pVirtualKeysFlags[CSCREENSTART_VIRTUAL_KEYS];
    /* 013F */ unsigned char field_13F;
    /* 0140 */ INT m_nEngineState;
    /* 0144 */ int field_144;
    /* 0148 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0164 */ INT m_nErrorState;
    /* 0168 */ STRREF m_dwErrorTextId;
    /* 016C */ INT m_nNumErrorButtons;
    /* 0170 */ STRREF m_strErrorButtonText[CSCREENSTART_ERROR_BUTTONS];
    /* 017C */ int field_17C;
    /* 0180 */ CVidFont field_180;
};

class CUIControlButtonStartMenu : CUIControlButton {
public:
    CUIControlButtonStartMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStartMenu();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonStart670770 : CUIControlButton {
public:
    CUIControlButtonStart670770(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonStart670770();
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSTART_H_ */

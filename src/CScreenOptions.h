#ifndef CSCREENOPTIONS_H_
#define CSCREENOPTIONS_H_

#include "CBaldurEngine.h"

#include "CKeyInfo.h"
#include "CVidFont.h"

#define CSCREENOPTIONS_VIRTUAL_KEYS 90
#define CSCREENOPTIONS_ERROR_BUTTONS 3

class CGameOptions;

class CScreenOptions : public CBaldurEngine {
public:
    CScreenOptions();
    /* 0004 */ ~CScreenOptions() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;

    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD nID);
    void ResetErrorPanel(CUIPanel* pPanel);
    void UpdatePopupPanel(DWORD dwPanelId, BOOLEAN bInitialUpdate);
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
    /* 0484 */ int field_484;
    /* 0488 */ short field_488;
    /* 048A */ unsigned char field_48A;
    /* 048B */ unsigned char field_48B;
    /* 048C */ unsigned char field_48C;
    /* 048D */ unsigned char field_48D;
    /* 048E */ BOOLEAN m_bCtrlKeyDown;
    /* 0490 */ CVidFont m_preLoadFontRealms;
    /* 0990 */ CVidFont m_preLoadFontStnSml;
    /* 0E90 */ unsigned char field_E90;
    /* 0E91 */ unsigned char field_E91;
    /* 0E92 */ BOOLEAN m_bFullScreenOptions;
};

#endif /* CSCREENOPTIONS_H_ */

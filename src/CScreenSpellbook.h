#ifndef CSCREENSPELLBOOK_H_
#define CSCREENSPELLBOOK_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlScrollBar.h"
#include "CVidCell.h"
#include "CVidFont.h"

// TODO: Move somewhere.
#define CSPELLLIST_NUM_CLASSES 7

#define CSCREENSPELLBOOK_VIRTUAL_KEYS 92
#define CSCREENSPELLBOOK_ERROR_BUTTONS 3

class CGameSprite;

class CScreenSpellbook : public CBaldurEngine {
public:
    CScreenSpellbook();
    /* 0004 */ ~CScreenSpellbook() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
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
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00F0 */ void OnRestButtonClick() override;
    /* 0104 */ void CancelEngine() override;

    void sub_669830(DWORD nPortrait);
    int sub_66A010(DWORD nIndex);
    void SetSpellLevel(INT nLevel);
    void SetClassIndex(DWORD nNewClassIndex);
    void sub_66A2D0();
    CUIPanel* GetTopPopup();
    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void ResetErrorPanel(CUIPanel* pPanel);
    void OnErrorButtonClick(INT nButton);
    void CheckMultiPlayerViewable();
    void UnmemorizeSpell(CGameSprite* pSprite, int a2);

    // NOTE: Seen in `OnErrorButtonClick` assertion.
    INT GetNumErrorButtons() { return m_nNumErrorButtons; }

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENSPELLBOOK_VIRTUAL_KEYS];
    /* 03E6 */ BYTE m_pVirtualKeysFlags[CSCREENSPELLBOOK_VIRTUAL_KEYS];
    /* 0442 */ int field_442;
    /* 0446 */ int field_446;
    /* 044A */ int field_44A;
    /* 044E */ unsigned char m_nSpellLevel;
    /* 0452 */ BYTE m_nClassIndex;
    /* 0454 */ INT m_nNumKnownSpells;
    /* 0458 */ INT m_nTopKnownSpell;
    /* 045C */ CVidCell field_45C;
    /* 0536 */ int field_536;
    /* 053A */ int field_53A;
    /* 053E */ int field_53E;
    /* 0542 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 055E */ CResRef field_55E;
    /* 0566 */ INT m_nErrorState;
    /* 056A */ STRREF m_dwErrorTextId;
    /* 056E */ INT m_nNumErrorButtons;
    /* 0572 */ STRREF m_strErrorButtonText[CSCREENSPELLBOOK_ERROR_BUTTONS];
    /* 057E */ BOOL m_bMultiPlayerViewable;
    /* 0582 */ int field_582;
    /* 0586 */ BOOLEAN m_bCtrlKeyDown;
    /* 0588 */ CVidFont m_preLoadFontRealms;
    /* 0A88 */ CVidFont m_preLoadFontStnSml;
    /* 0F88 */ CVidFont m_preLoadFontTool;
    /* 1488 */ int field_1488;
    /* 148C */ CResRef field_148C[24];
    /* 15C4 */ int field_154C[24];
    /* 15AC */ int field_15AC[24];
    /* 160C */ CResRef field_160C[8];
    /* 1650 */ DWORD m_nNumberOfSpellClasses;
    /* 1654 */ int field_1654[CSPELLLIST_NUM_CLASSES];
    /* 1670 */ int field_1670;
};

class CUIControlButtonSpellbookSpell : public CUIControlButton {
public:
    CUIControlButtonSpellbookSpell(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookSpell() override;
    BOOL OnLButtonDown(CPoint pt) override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;
    void OnRButtonClick(CPoint pt) override;

    void SetSpell(const CResRef& cSpellResRef);

    /* 0666 */ CResRef m_spellResRef;
    /* 066E */ CResRef m_iconResRef;
    /* 0676 */ int field_676;
    /* 067A */ int field_67A;
};

class CUIControlScrollBarSpellbookKnownSpells : public CUIControlScrollBar {
public:
    CUIControlScrollBarSpellbookKnownSpells(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarSpellbookKnownSpells() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void InvalidateItems();
};

class CUIControlButtonSpellbookSpellInfoIcon : public CUIControlButton {
public:
    CUIControlButtonSpellbookSpellInfoIcon(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookSpellInfoIcon();
    BOOL Render(BOOL bForce) override;

    void SetSpell(const CResRef& cSpellResRef);

    /* 0666 */ CResRef m_spellResRef;
    /* 066E */ CResRef m_iconResRef;
};

class CUIControlButtonSpellbookPopupDone : public CUIControlButton {
public:
    CUIControlButtonSpellbookPopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookPopupDone();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSpellbookError : public CUIControlButton {
public:
    CUIControlButtonSpellbookError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookError();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSpellbookLevelSelection : public CUIControlButton3State {
public:
    CUIControlButtonSpellbookLevelSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookLevelSelection();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSpellbookClassSelection : public CUIControlButton3State {
public:
    CUIControlButtonSpellbookClassSelection(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSpellbookClassSelection();
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSPELLBOOK_H_ */

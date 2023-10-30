#ifndef CSCREENLOAD_H_
#define CSCREENLOAD_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CResBitmap.h"
#include "CUIControlButton.h"
#include "CUIControlScrollBar.h"
#include "CVidFont.h"

#define CSCREENLOAD_VIRTUAL_KEYS 21
#define CSCREENLOAD_ERROR_BUTTONS 3

class CScreenLoadGameSlot {
public:
    CScreenLoadGameSlot();
    ~CScreenLoadGameSlot();

    /* 0000 */ CString m_sFileName;
    /* 0004 */ CString m_sSlotName;
    /* 0008 */ CResBitmap m_cResScreenShot;
    /* 0074 */ CResBitmap m_cBmpResPortrait0;
    /* 00E0 */ CResBitmap m_cBmpResPortrait1;
    /* 014C */ CResBitmap m_cBmpResPortrait2;
    /* 01B8 */ CResBitmap m_cBmpResPortrait3;
    /* 0224 */ CResBitmap m_cBmpResPortrait4;
    /* 0290 */ CResBitmap m_cBmpResPortrait5;
    /* 02FC */ CResRef m_cResPortrait;
    /* 0304 */ CString m_sCharacterName;
    /* 0308 */ ULONG m_nTime;
    /* 030C */ int m_nChapter;
    /* 0310 */ CString m_sChapter;
    /* 0314 */ CString m_sFileTime;
};

class CScreenLoad : public CBaldurEngine {
public:
    CScreenLoad();
    /* 0004 */ ~CScreenLoad() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
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

    void UpdateMainPanel();
    void LoadGame(INT nSlot);
    void OnDeleteButtonClick(INT nSlot);
    void OnMainCancelButtonClick();
    void StartLoad(INT nEngineState);
    void FreeGameSlots();
    void RefreshGameSlots();
    BOOL DrawScreenShot(INT nSlot, const CRect& rArea, const CRect& rClip);
    BOOL DrawPortrait(USHORT nPortrait, INT nSlot, const CRect& rArea, const CRect& rClip);
    void EnableMainPanel(BOOL bEnable);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void sub_63E150(CUIPanel* pPanel);
    void OnErrorButtonClick(INT nButton);
    void sub_63E440(INT nButton);
    void DeleteGame(INT nGameSlot);
    void OnCancelButtonClick();

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENLOAD_VIRTUAL_KEYS];
    /* 01AE */ BYTE m_pVirtualKeysFlags[CSCREENLOAD_VIRTUAL_KEYS];
    /* 01C3 */ BOOLEAN m_bCtrlKeyDown;
    /* 01C4 */ BOOLEAN m_bShiftKeyDown;
    /* 01C6 */ INT m_nTopGameSlot;
    /* 01CA */ INT m_nNumGameSlots;
    /* 01CE */ INT m_nEngineState;
    /* 01D2 */ CTypedPtrArray<CPtrArray, CScreenLoadGameSlot*> m_aGameSlots;
    /* 01E6 */ INT m_nCurrentGameSlot;
    /* 01EA */ DWORD m_dwErrorTextId;
    /* 01EE */ DWORD m_strErrorButtonText[CSCREENLOAD_ERROR_BUTTONS];
    /* 01FA */ INT m_nNumErrorButtons;
    /* 01FE */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 021A */ INT m_nMaxSlotNumber;
    /* 021E */ CVidFont m_preLoadFontRealms;
    /* 071E */ CVidFont m_preLoadFontStnSml;
    /* 0C1E */ BOOL m_bInLoadGame;
};

class CUIControlButtonLoadDelete : public CUIControlButton {
public:
    CUIControlButtonLoadDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadDelete() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonLoadLoad : public CUIControlButton {
public:
    CUIControlButtonLoadLoad(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadLoad() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonLoadCancel : public CUIControlButton {
public:
    CUIControlButtonLoadCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonLoadScreenShot : public CUIControlButton {
public:
    CUIControlButtonLoadScreenShot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadScreenShot() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonDoubleClick(CPoint pt) override;
};

class CUIControlButtonLoadPortrait : public CUIControlButton {
public:
    CUIControlButtonLoadPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadPortrait() override;
    BOOL Render(BOOL bForce) override;
};

class CUIControlScrollBarLoadGames : public CUIControlScrollBar {
public:
    CUIControlScrollBarLoadGames(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarLoadGames() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void UpdateMainPanel();
};

class CUIControlButtonLoadError : public CUIControlButton {
public:
    CUIControlButtonLoadError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonLoadError() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENLOAD_H_ */

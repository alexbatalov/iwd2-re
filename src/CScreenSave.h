#ifndef CSCREENSAVE_H_
#define CSCREENSAVE_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CResBitmap.h"
#include "CUIControlButton.h"
#include "CUIControlEdit.h"
#include "CUIControlScrollBar.h"
#include "CVidFont.h"

#define CSCREENSAVE_VIRTUAL_KEYS 93
#define CSCREENSAVE_ERROR_BUTTONS 3

class CScreenSaveGameSlot {
public:
    CScreenSaveGameSlot();
    ~CScreenSaveGameSlot();

    /* 0000 */ CString m_sFileName;
    /* 0004 */ CString m_sSlotName;
    /* 0008 */ CResBitmap m_cResScreenShot;
    /* 0074 */ CResBitmap m_cBmpResPortrait0;
    /* 00E0 */ CResBitmap m_cBmpResPortrait1;
    /* 014C */ CResBitmap m_cBmpResPortrait2;
    /* 01B8 */ CResBitmap m_cBmpResPortrait3;
    /* 0224 */ CResBitmap m_cBmpResPortrait4;
    /* 0290 */ CResBitmap m_cBmpResPortrait5;
    /* 02FC */ CResRef field_2FC;
    /* 0304 */ CString field_304;
    /* 0308 */ ULONG field_308;
    /* 030C */ int field_30C;
    /* 0310 */ CString field_310;
    /* 0314 */ CString field_314;
};

class CScreenSave : public CBaldurEngine {
public:
    CScreenSave();
    /* 0004 */ ~CScreenSave() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0038 */ BOOL GetCtrlKey() override;
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

    void UpdateMainPanel();
    void OnSaveButtonClick(INT nSlot);
    void OnDeleteButtonClick(INT nSlot);
    void OnMainCancelButtonClick();
    BOOL IsDoneButtonClickable();
    void OnDoneButtonClick();
    void OnCancelButtonClick();
    void StartSave(INT nEngineState);
    void StopSave();
    void FreeGameSlots();
    void RefreshGameSlots();
    void DrawScreenShot();
    BOOL DrawPortrait(USHORT nPortrait, INT nSlot, const CRect& rArea, const CRect& rClip);
    void EnableMainPanel(BOOL bEnable);
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetSaveAsPanel(CUIPanel* pPanel);
    void UpdateSaveAsPanel();
    void ResetErrorPanel(CUIPanel* pPanel);
    void OnErrorButtonClick(INT nButton);
    void SaveGame(INT nGameSlot, const CString& sSlotName);
    void DeleteSave(INT nGameSlot);

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENSAVE_VIRTUAL_KEYS];
    /* 03EE */ BYTE m_pVirtualKeysFlags[CSCREENSAVE_VIRTUAL_KEYS];
    /* 044C */ BOOL m_bShiftKeyDown;
    /* 0450 */ BOOL m_bCapsLockKeyOn;
    /* 0454 */ INT m_nTopGameSlot;
    /* 0458 */ INT m_nNumGameSlots;
    /* 045C */ INT m_nEngineState;
    /* 0460 */ CTypedPtrArray<CPtrArray, CScreenSaveGameSlot*> m_aGameSlots;
    /* 0474 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0490 */ DWORD m_dwErrorTextId;
    /* 0494 */ DWORD m_strErrorButtonText[CSCREENSAVE_ERROR_BUTTONS];
    /* 04A0 */ INT m_nNumErrorButtons;
    /* 04A4 */ INT m_nCurrentGameSlot;
    /* 04A8 */ INT m_nMaxSlotNumber;
    /* 04AC */ BOOLEAN m_bCtrlKeyDown;
    /* 04AE */ CVidFont m_preLoadFontRealms;
    /* 09AE */ CVidFont m_preLoadFontStnSml;
};

class CUIControlEditSaveName : public CUIControlEdit {
public:
    CUIControlEditSaveName(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditSaveName() override;
    void KillFocus() override;
    void OnKeyDown(SHORT nKey) override;
    void OnEditReturn(CString sText) override;
};

class CUIControlButtonSaveDelete : public CUIControlButton {
public:
    CUIControlButtonSaveDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSaveDelete() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSaveSave : public CUIControlButton {
public:
    CUIControlButtonSaveSave(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSaveSave() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSaveCancel : public CUIControlButton {
public:
    CUIControlButtonSaveCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSaveCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSaveScreenShot : public CUIControlButton {
public:
    CUIControlButtonSaveScreenShot(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSaveScreenShot() override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonDoubleClick(CPoint pt) override;
};

class CUIControlButtonSavePortrait : public CUIControlButton {
public:
    CUIControlButtonSavePortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSavePortrait() override;
    BOOL Render(BOOL bForce) override;
};

class CUIControlScrollBarSaveGames : public CUIControlScrollBar {
public:
    CUIControlScrollBarSaveGames(CUIPanel* panel, UI_CONTROL_SCROLLBAR* controlInfo);
    ~CUIControlScrollBarSaveGames() override;
    void OnScroll() override;
    void OnScrollUp() override;
    void OnScrollDown() override;
    void OnPageUp(DWORD nLines) override;
    void OnPageDown(DWORD nLines) override;
    void UpdateScrollBar();
    void UpdateMainPanel();
};

class CUIControlButtonSavePopupDone : public CUIControlButton {
public:
    CUIControlButtonSavePopupDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSavePopupDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSavePopupCancel : public CUIControlButton {
public:
    CUIControlButtonSavePopupCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSavePopupCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonSaveError : public CUIControlButton {
public:
    CUIControlButtonSaveError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonSaveError() override;
    void OnLButtonClick(CPoint pt) override;
};

#endif /* CSCREENSAVE_H_ */

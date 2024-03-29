#ifndef CSCREENMAP_H_
#define CSCREENMAP_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButton.h"
#include "CUIControlButton3State.h"
#include "CUIControlEditMultiLine.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

#define CSCREENMAP_VIRTUAL_KEYS 90
#define CSCREENMAP_ERROR_BUTTONS 3

class CGameArea;
class CGameSprite;
class CUIPanel;
class CVidInf;

typedef struct MAP_CHAR_POSITIONS {
    CPoint ptPos;
    LONG id;
} MAP_CHAR_POSITIONS;

class CScreenMap : public CBaldurEngine {
public:
    CScreenMap();
    /* 0004 */ ~CScreenMap() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0024 */ void EngineGameInit() override;
    /* 0028 */ void EngineGameUninit() override;
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
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;
    /* 00E4 */ void OnPortraitLDblClick(DWORD nPortrait) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00F0 */ void OnRestButtonClick() override;
    /* 0104 */ void CancelEngine() override;

    void EnableMainPanel(BOOL bEnable);
    void UpdateMainPanel();
    CUIPanel* GetTopPopup();
    void ShowPopupPanel(DWORD dwPanelId, BOOL bShow);
    void EnablePopupPanel(DWORD dwPanelId, BOOL bEnable);
    void ResetPopupPanel(DWORD dwPanelId);
    void UpdatePopupPanel(DWORD dwPanelId);
    void SummonPopup(DWORD dwPopupId);
    void DismissPopup();
    void ResetErrorPanel(CUIPanel* pPanel);
    void ResetAreaNotePanel(CUIPanel* pPanel);
    void UpdateNoteText(STRREF strRef);
    void OnErrorButtonClick(INT nButton);
    void OnCancelButtonClick();
    void OnDoneButtonClick();

    // NOTE: Seen in `OnErrorButtonClick` assertion.
    INT GetNumErrorButtons() { return m_nNumErrorButtons; }

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENMAP_VIRTUAL_KEYS];
    /* 03D6 */ BYTE m_pVirtualKeysFlags[CSCREENMAP_VIRTUAL_KEYS];
    /* 0430 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 044C */ SHORT m_nLastPicked;
    /* 044E */ INT m_nErrorState;
    /* 0452 */ STRREF m_dwErrorTextId;
    /* 0456 */ INT m_nNumErrorButtons;
    /* 045A */ STRREF m_strErrorButtonText[CSCREENMAP_ERROR_BUTTONS];
    /* 0466 */ BOOLEAN m_bSelectWorldOnUp;
    /* 0468 */ CVidFont m_preLoadFontRealms;
    /* 0968 */ CVidFont m_preLoadFontTool;
    /* 0E68 */ CVidFont m_preLoadFontStnSml;
    /* 1368 */ STRREF m_noteStrRef;
    /* 136C */ BOOL m_bShiftKeyDown;
    /* 1370 */ BOOL m_bCapsLockKeyOn;
    /* 1374 */ BOOL m_bCtrlKeyDown;
};

class CUIControlButtonMapWorld : public CUIControlButton {
public:
    CUIControlButtonMapWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapWorld() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapAreaMap : public CUIControlButton {
public:
    CUIControlButtonMapAreaMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    /* 0000 */ ~CUIControlButtonMapAreaMap() override;
    /* 0014 */ void OnMouseMove(CPoint pt) override;
    /* 0018 */ BOOL OnLButtonDown(CPoint pt) override;
    /* 001C */ void OnLButtonUp(CPoint pt) override;
    /* 0030 */ void TimerAsynchronousUpdate(BOOLEAN bInside) override;
    /* 0050 */ void InvalidateRect() override;
    /* 0058 */ BOOL Render(BOOL bForce) override;
    /* 0064 */ BOOL NeedRender() override;
    /* 0068 */ void OnLButtonClick(CPoint pt) override;
    /* 0070 */ void OnRButtonClick(CPoint pt) override;

    BOOLEAN sub_642C90(CGameSprite* pSprite, const CPoint& pt);
    CPoint ConvertScreenToWorldCoords(CPoint pt);
    void CenterViewPort(const CPoint& pt);
    void SetRenderCharacter(SHORT nPortrait, WORD nVisualRange);
    BOOL RenderCharactersOnly(const CPoint& pt);
    void RenderCharacters(const CRect& rClip);
    void RenderFogOfWar(CVidInf* pVidInf, const CPoint& pt, const CRect& rClip);
    void InvalidateNotes();
    void RenderViewRect(CVidInf* pVidInf, const CRect& r1, const CRect& r2);
    void SetMap(CGameArea* pArea);
    void GetStartPosition(CPoint& pt);
    void SetActiveNotes(BOOL bActive);
    void AddNote(DWORD id);
    void RemoveNote(DWORD id);

    /* 0666 */ CVidMosaic m_vmMap;
    /* 071A */ CGameArea* m_pArea;
    /* 071E */ BOOLEAN field_71E;
    /* 071F */ BOOLEAN field_71F;
    /* 0720 */ BOOLEAN field_720;
    /* 0722 */ LONG field_722;
    /* 0726 */ LONG field_726;
    /* 072A */ CRect field_72A;
    /* 073A */ CCriticalSection m_critSect;
    /* 075A */ BYTE field_75A;
    /* 075B */ unsigned char field_75B;
    /* 075C */ CPoint field_75C;
    /* 0764 */ CPoint field_764;
    /* 076C */ unsigned char field_76C;
    /* 076E */ MAP_CHAR_POSITIONS m_charPositions[6];
    /* 07B6 */ USHORT m_nCharInArea;
    /* 07B8 */ DWORD m_nUserNoteId;
    /* 07BC */ BOOLEAN field_7BC;
    /* 07BE */ CList<DWORD> field_7BE;
    /* 07DA */ unsigned char field_7DA;
};

class CUIControlButtonMapError : public CUIControlButton {
public:
    CUIControlButtonMapError(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapError() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNoteDone : public CUIControlButton {
public:
    CUIControlButtonMapNoteDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNoteCancel : public CUIControlButton {
public:
    CUIControlButtonMapNoteCancel(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteCancel() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNoteDelete : public CUIControlButton {
public:
    CUIControlButtonMapNoteDelete(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteDelete() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlEditMultiLineMapNote : public CUIControlEditMultiLine {
public:
    CUIControlEditMultiLineMapNote(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo);
    ~CUIControlEditMultiLineMapNote();
    void OnEditReturn(CString sText) override;
};

class CUIControlButtonMapShowNotes : public CUIControlButton3State {
public:
    CUIControlButtonMapShowNotes(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapShowNotes() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonMapNote : public CUIControlButton {
public:
    CUIControlButtonMapNote(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNote() override;
    void OnMouseMove(CPoint pt) override;
    BOOL Render(BOOL bForce) override;
    void SetInactiveRender(BOOL bInactiveRender) override;
    void OnRButtonClick(CPoint pt) override;

    /* 0666 */ unsigned char field_666;
    /* 0667 */ unsigned char fiedl_667;
    /* 0668 */ int field_668;
    /* 066C */ CResRef m_areaResRef;
    /* 0674 */ CPoint m_ptWorld;
};

class CUIControlButtonMapNoteFlagChoice : public CUIControlButton3State {
public:
    CUIControlButtonMapNoteFlagChoice(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonMapNoteFlagChoice() override;
    BOOL OnLButtonDown(CPoint pt) override;
    BOOL Render(BOOL bForce) override;
    void OnLButtonClick(CPoint pt) override;

    /* 066E */ BOOL field_66E;
};

#endif /* CSCREENMAP_H_ */

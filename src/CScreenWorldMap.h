#ifndef CSCREENWORLDMAP_H_
#define CSCREENWORLDMAP_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CUIControlButtonPlusMinus.h"
#include "CVidCell.h"
#include "CVidFont.h"
#include "CVidMosaic.h"

#define CSCREENWORLDMAP_VIRTUAL_KEYS 90

class CUIControlTextDisplay;
class CUIPanel;

class CScreenWorldMap : public CBaldurEngine {
public:
    static const LONG FATIGUE_TIME_CAP;

    CScreenWorldMap();
    /* 0004 */ ~CScreenWorldMap() override;
    /* 0018 */ void EngineDeactivated() override;
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
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 0110 */ void GetChatEditBoxStatus(CString& sChatText, BOOL& bInputCapture) override;
    /* 0114 */ void SetChatEditBoxStatus(const CString& sChatText, BOOL bInputCapture) override;

    void UpdateMainPanel();
    void OnDoneButtonClick();
    void SetMapView(const CPoint& ptMapView);
    void OnMapMouseDown(const CPoint& ptMousePos);
    void OnMapMouseUp(const CPoint& ptMousePos);
    void OnMapMouseMove(const CPoint& ptMousePos);
    void OnMapAsyncUpdate();
    BOOL DrawMap(const CRect& r);
    void StartWorldMap(INT nEngineState, LONG nLeavingEdge, BOOLEAN bInControl);
    void StopWorldMap(BOOLEAN bAreaClicked);
    void ClearChatMessages();

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENWORLDMAP_VIRTUAL_KEYS];
    /* 03D6 */ BYTE m_pVirtualKeysFlags[CSCREENWORLDMAP_VIRTUAL_KEYS];
    /* 0430 */ BOOLEAN m_bCtrlKeyDown;
    /* 0431 */ BOOLEAN m_bShiftKeyDown;
    /* 0432 */ BOOL m_bCapsLockKeyOn;
    /* 0436 */ CTypedPtrList<CPtrList, CUIPanel*> m_lPopupStack;
    /* 0452 */ INT m_nEngineState;
    /* 0456 */ CPoint m_ptMapView;
    /* 045E */ void* m_pMapControl;
    /* 0462 */ CVidMosaic m_vmMap;
    /* 0516 */ CVidCell m_vcAreas;
    /* 05F0 */ CVidCell m_vcMarker;
    /* 06CA */ CVidFont m_vfLabel;
    /* 0FCA */ COLORREF field_FCA;
    /* 0FCE */ int field_FCE;
    /* 0FD2 */ INT m_nSelectedArea;
    /* 0FD6 */ BOOL m_bOverSelectedArea;
    /* 0FDA */ CPoint m_ptMapStartMousePos;
    /* 0FE2 */ CPoint m_ptMapStartView;
    /* 0FEA */ BOOL m_bMapLeftDown;
    /* 0FEE */ BOOL m_bMapDragging;
    /* 0FF2 */ int field_FF2;
    /* 0FF6 */ int field_FF6;
    /* 0FFA */ void* m_pPath;
    /* 0FFE */ int field_FFE;
    /* 1002 */ int m_nCurrentLink;
    /* 1006 */ CResRef m_cResCurrentArea;
    /* 100E */ CArray<CRect, CRect&> field_100E;
    /* 1022 */ CCriticalSection field_1022;
    /* 1042 */ CUIPanel* m_pMainPanel;
    /* 1046 */ CUIControlTextDisplay* m_pChatDisplay;
    /* 104A */ int field_104A;
    /* 104E */ BOOLEAN m_bInControl;
    /* 104F */ BOOLEAN m_bClickedArea;
    /* 1050 */ int field_1050;
    /* 1054 */ int m_nToolTip;
    /* 1058 */ CVidFont m_preLoadFontRealms;
    /* 1558 */ CVidFont m_preLoadFontTool;
};

class CUIControlButtonWorldMapScroll : public CUIControlButtonPlusMinus {
public:
    CUIControlButtonWorldMapScroll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldMapScroll();
    void AdjustValue() override;
};

class CUIControlButtonWorldMapDone : public CUIControlButton {
public:
    CUIControlButtonWorldMapDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldMapDone();
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonWorldMapWorldMap : public CUIControlButton {
public:
    CUIControlButtonWorldMapWorldMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonWorldMapWorldMap();
    void OnMouseMove(CPoint pt) override;
    BOOL OnLButtonDown(CPoint pt) override;
    void OnLButtonUp(CPoint pt) override;
    BOOL Render(BOOL bForce) override;

    /* 0676 */ int field_676;
    /* 067A */ int field_67A;
};

#endif /* CSCREENWORLDMAP_H_ */

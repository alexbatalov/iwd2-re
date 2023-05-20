#ifndef CSCREENCHAPTER_H_
#define CSCREENCHAPTER_H_

#include "CBaldurEngine.h"
#include "CKeyInfo.h"
#include "CSound.h"
#include "CUIControlButton.h"
#include "CUIControlTextDisplay.h"
#include "CVidFont.h"

#define CSCREENCHAPTER_VIRTUAL_KEYS 5

class CScreenChapter : public CBaldurEngine {
public:
    CScreenChapter();
    /* 0004 */ ~CScreenChapter() override;
    /* 0014 */ void EngineActivated() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 001C */ void EngineDestroyed() override;
    /* 0020 */ void EngineInitialized() override;
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
    /* 00AC */ void OnKeyDown(SHORT a2) override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;
    /* 00E0 */ void OnPortraitLClick(DWORD nPortrait) override;
    /* 0104 */ void CancelEngine() override;

    void SwitchMainPanel(DWORD dwMainPanelId);
    void ResetMainPanel();
    void UpdateMainPanel();
    void OnDoneButtonClick();
    void OnReplayButtonClick();
    void StartChapter(const CResRef& cResText);
    void StartChapterMultiplayerHost(BYTE nChapter, BYTE* resRef);
    BOOL StartText(const CResRef& cResText);
    void StopText(BOOL bNotifyServer);
    void OnMixerInitialize();

    /* 0106 */ CKeyInfo m_pVirtualKeys[CSCREENCHAPTER_VIRTUAL_KEYS];
    /* 012E */ BYTE m_pVirtualKeysFlags[CSCREENCHAPTER_VIRTUAL_KEYS];
    /* 0133 */ BOOLEAN m_bCtrlKeyDown;
    /* 0134 */ CUIPanel* m_pMainPanel;
    /* 0138 */ INT m_nChapter;
    /* 013C */ CResRef m_cResText;
    /* 0144 */ CList<STRREF, STRREF>* m_pTextList;
    /* 0148 */ INT m_nParagraph;
    /* 014C */ int m_nLine;
    /* 0150 */ CSound m_cVoiceSound;
    /* 01B4 */ BOOL m_bStarted;
    /* 01B8 */ DWORD m_nStartTime;
    /* 01BC */ DWORD m_nTotalPlayTime;
    /* 01C0 */ int m_nLineDelay;
    /* 01C4 */ CUIControlTextDisplay* m_pTextControl;
    /* 01C8 */ DWORD m_nEndTime;
    /* 01CC */ int m_bEnded;
    /* 01D0 */ INT m_nEngineState;
    /* 01D4 */ CResRef field_1D4;
    /* 01DC */ INT m_nSongCountDown;
    /* 01E0 */ CVidFont m_preLoadFontRealms;
};

class CUIControlButtonChapterDone : public CUIControlButton {
public:
    CUIControlButtonChapterDone(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonChapterDone() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlButtonChapterReplay : public CUIControlButton {
public:
    CUIControlButtonChapterReplay(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonChapterReplay() override;
    void OnLButtonClick(CPoint pt) override;
};

class CUIControlTextDisplayChapter : public CUIControlTextDisplay {
public:
    CUIControlTextDisplayChapter(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo);
    void TimerAsynchronousUpdate(BOOLEAN bInside) override;
};

#endif /* CSCREENCHAPTER_H_ */

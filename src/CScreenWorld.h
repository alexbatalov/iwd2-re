#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

#include "CKeyInfo.h"
#include "CUIControlButton3State.h"
#include "CVidCell.h"
#include "CWeather.h"

#define CSCREENWORLD_VIRTUAL_KEYS 92

class CScreenWorld : public CBaldurEngine {
public:
    static const LONG BORED_TIME;

    CScreenWorld();
    /* 0004 */ ~CScreenWorld() override;
    /* 0018 */ void EngineDeactivated() override;
    /* 0030 */ BOOL CheckSystemKeyCtrl() override;
    /* 0034 */ void SetSystemKeyCtrl(BOOLEAN bValue) override;
    /* 0038 */ BOOL GetCtrlKey() override;
    /* 003C */ BOOL CheckSystemKeyShift() override;
    /* 0040 */ void SetSystemKeyShift(BOOL bValue) override;
    /* 0044 */ BOOL GetShiftKey() override;
    /* 0048 */ BOOL CheckSystemKeyMenu() override;
    /* 004C */ void SetSystemKeyMenu(BOOL bValue) override;
    /* 0050 */ BOOL CheckSystemKeyCapsLock() override;
    /* 0054 */ void SetSystemKeyCapsLock(BOOL bValue) override;
    /* 0058 */ BOOL GetCapsLockKey() override;
    /* 005C */ BOOL GetMenuKey() override;
    /* 0060 */ BOOL CheckMouseMove() override;
    /* 0064 */ void OnMouseMove(CPoint pt) override;
    /* 0068 */ BOOL CheckMouseLButton() override;
    /* 006C */ void OnLButtonDblClk(CPoint pt) override;
    /* 0070 */ void OnLButtonDown(CPoint pt) override;
    /* 0074 */ void OnLButtonUp(CPoint pt) override;
    /* 0088 */ BOOL CheckMouseRButton() override;
    /* 008C */ void OnRButtonDblClk(CPoint pt) override;
    /* 0090 */ void OnRButtonDown(CPoint pt) override;
    /* 0094 */ void OnRButtonUp(CPoint pt) override;
    /* 00A0 */ SHORT GetNumVirtualKeys() override;
    /* 00A4 */ CKeyInfo* GetVirtualKeys() override;
    /* 00A8 */ BYTE* GetVirtualKeysFlags() override;
    /* 00C0 */ void TimerAsynchronousUpdate() override;
    /* 00C4 */ void TimerSynchronousUpdate() override;

    void AsynchronousUpdate(BOOL bActiveEngine);
    BOOL TogglePauseGame(char a2, char a3, int a4);
    void StopStore();
    void ClearChatMessages();
    void HideInterface();
    void UnhideInterface();

    void CompressTime(DWORD deltaTime) { m_deltaTime = deltaTime; }

    /* 012E */ BOOL m_bShiftKeyDown;
    /* 0132 */ BOOL m_bMenuKeyDown;
    /* 0136 */ BOOL m_bCtrlKeyDown;
    /* 013A */ BOOL m_bCapsLockKeyOn;
    /* 013E */ BOOLEAN m_bPaused;
    /* 0146 */ BOOL m_bHardPaused;
    /* 0B68 */ CKeyInfo m_pVirtualKeys[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0E48 */ BYTE m_pVirtualKeysFlags[CSCREENWORLD_VIRTUAL_KEYS];
    /* 0EA4 */ int field_EA4;
    /* 0F46 */ CWeather m_weather;
    /* 10DA */ DWORD m_deltaTime;
    /* 10DE */ int field_10DE;
    /* 10EB */ BOOLEAN m_bInControlOfStore;
    /* 10EC */ BOOL m_bGameOverPanel;
    /* 10F0 */ int field_10F0;
    /* 10F4 */ int field_10F4;
    /* 1151 */ BOOLEAN m_bEndMajorEventListenToJoin;
    /* 1152 */ BOOLEAN m_bEndMajorEventPauseStatus;
    /* 119D */ BOOLEAN field_119D;
    /* 11CA */ BYTE m_nAutoHideInterface;
    /* 11CC */ INT m_nAutoUnhideInterface;
};

class CUIControlButtonClock : public CUIControlButton3State {
public:
    CUIControlButtonClock(CUIPanel* pPanel, UI_CONTROL_BUTTON* controlInfo);
    ~CUIControlButtonClock() override;

    /* 066E */ CVidCell field_66E;
    /* 0748 */ CVidCell field_748;
};

#endif /* CSCREENWORLD_H_ */

#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

#include "CUIControlButton3State.h"
#include "CVidCell.h"

class CScreenWorld : public CBaldurEngine {
public:
    static const LONG BORED_TIME;

    CScreenWorld();
    ~CScreenWorld();
    void AsynchronousUpdate(BOOL bActiveEngine);
    BOOL TogglePauseGame(char a2, char a3, int a4);
    void ClearChatMessages();
    void HideInterface();
    void UnhideInterface();

    void CompressTime(DWORD deltaTime) { m_deltaTime = deltaTime; }

    /* 013E */ BOOLEAN m_bPaused;
    /* 0146 */ BOOL m_bHardPaused;
    /* 10DA */ DWORD m_deltaTime;
    /* 10DE */ int field_10DE;
    /* 10EC */ BOOL m_bGameOverPanel;
    /* 1151 */ BOOLEAN m_bEndMajorEventListenToJoin;
    /* 1152 */ BOOLEAN m_bEndMajorEventPauseStatus;
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

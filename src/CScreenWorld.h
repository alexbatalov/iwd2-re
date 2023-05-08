#ifndef CSCREENWORLD_H_
#define CSCREENWORLD_H_

#include "CBaldurEngine.h"

class CScreenWorld : public CBaldurEngine {
public:
    CScreenWorld();
    ~CScreenWorld();
    BOOL TogglePauseGame(char a2, char a3, int a4);
    void ClearChatMessages();
    void HideInterface();
    void UnhideInterface();

    void CompressTime(DWORD deltaTime) { m_deltaTime = deltaTime; }

    /* 013E */ BOOLEAN m_bPaused;
    /* 10DA */ DWORD m_deltaTime;
    /* 10DE */ int field_10DE;
    /* 11CA */ BYTE m_nAutoHideInterface;
    /* 11CC */ INT m_nAutoUnhideInterface;
};

#endif /* CSCREENWORLD_H_ */

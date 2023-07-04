#ifndef CGAMEAIGAME_H_
#define CGAMEAIGAME_H_

#include "CGameAIBase.h"

class CGameAIGame : public CGameAIBase {
public:
    CGameAIGame();
    /* 0000 */ ~CGameAIGame() override;
    /* 0028 */ BOOLEAN CanSaveGame(STRREF& strError) override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
};

#endif /* CGAMEAIGAME_H_ */

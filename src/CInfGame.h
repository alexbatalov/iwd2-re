#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

#include "CGameOptions.h"

class CInfGame {
public:
    CInfGame();
    ~CInfGame();
    void StartSearchThread();
    void ApplyVolumeSliders(BOOLEAN a2);

    /* 3846 */ SHORT m_nCharacters;
    /* 43EA */ CGameOptions m_cOptions; // #guess
    /* 4A00 */ HANDLE m_hSearchThread; // #guess
};

#endif /* CINFGAME_H_ */

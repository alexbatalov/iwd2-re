#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

class CInfGame {
public:
    CInfGame();
    ~CInfGame();
    void StartSearchThread();

    /* 4A00 */ HANDLE m_hSearchThread; // #guess
};

#endif /* CINFGAME_H_ */

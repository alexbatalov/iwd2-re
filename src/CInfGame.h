#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

#include "CGameOptions.h"
#include "CRuleTables.h"
#include "CTimerWorld.h"

class CInfGame {
public:
    CInfGame();
    ~CInfGame();
    void StartSearchThread();
    void UpdatePortrait(SHORT nPortrait, DWORD dwPanelId);
    SHORT GetCharacterPortaitNum(LONG nCharacterId);
    void ApplyVolumeSliders(BOOLEAN a2);

    /* 0000 */ CRuleTables m_ruleTables;
    /* 1B58 */ CCriticalSection field_1B58;
    /* 1B78 */ CTimerWorld m_worldTime;
    /* 1BA1 */ unsigned char field_1BA1;
    /* 382E */ LONG m_nCharacterPortaits[6];
    /* 3846 */ SHORT m_nCharacters;
    /* 43EA */ CGameOptions m_cOptions; // #guess
    /* 4A00 */ HANDLE m_hSearchThread; // #guess
};

#endif /* CINFGAME_H_ */

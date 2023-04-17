#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

#include "CGameOptions.h"
#include "CRuleTables.h"
#include "CTimerWorld.h"

// Seen in `CRuleTables::GetStartPoint` assertion.
#define CINFGAME_MAXCHARACTERS 6

class CGameArea;

class CInfGame {
public:
    CInfGame();
    ~CInfGame();
    void StartSearchThread();
    void UpdatePortrait(SHORT nPortrait, DWORD dwPanelId);
    SHORT GetCharacterPortaitNum(LONG nCharacterId);
    BOOL Is3DSound(int nSoundChannel);
    float GetSoundReverbMix(int nSoundChannel, int nReverb);
    void ApplyVolumeSliders(BOOLEAN a2);

    CGameArea* GetVisibleArea() { return m_gameAreas[m_visibleArea]; }

    /* 0000 */ CRuleTables m_ruleTables;
    /* 1B58 */ CCriticalSection field_1B58;
    /* 1B78 */ CTimerWorld m_worldTime;
    /* 1BA1 */ unsigned char field_1BA1;
    /* 37E0 */ BYTE m_visibleArea;
    /* 37E2 */ CGameArea* m_gameAreas[12];
    /* 3812 */ CGameArea* m_pGameAreaMaster;
    /* 382E */ LONG m_nCharacterPortaits[6];
    /* 3846 */ SHORT m_nCharacters;
    /* 43E2 */ int field_43E2;
    /* 43EA */ CGameOptions m_cOptions; // #guess
    /* 4A00 */ HANDLE m_hSearchThread; // #guess
    // NOTE: Can also be BYTE indicating number of expansion pack.
    /* 4BD5 */ BOOLEAN m_bExpansion;
};

#endif /* CINFGAME_H_ */

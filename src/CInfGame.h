#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

#include "CGameJournal.h"
#include "CGameObjectArray.h"
#include "CGameOptions.h"
#include "CInfButtonArray.h"
#include "CMultiplayerSettings.h"
#include "CRuleTables.h"
#include "CTimerWorld.h"
#include "CVRamPool.h"

// Seen in `CRuleTables::GetStartPoint` assertion.
#define CINFGAME_MAXCHARACTERS 6

// Seen in `CScreenOptions::OnKeyDown` assertion.
#define CINFGAME_KEYMAP_SIZE 372

#define CINFGAME_SPECIAL_SYMBOLS 12

// Seen in `CScreenSinglePlayer::UpdateModifyCharacterPanel` assertion.
#define CINFGAME_MAXCHARACTERS 6

class CGameArea;

class CInfGame {
public:
    CInfGame();
    ~CInfGame();
    void StartSearchThread();
    void DestroyGame(unsigned char a1, unsigned char a2);
    BOOLEAN CanSaveGame(STRREF& strError, unsigned char a2, unsigned char a3);
    char sub_5A9780(BYTE nKey);
    BYTE sub_5A97D0(char ch);
    BYTE sub_5A9830(int index);
    void LoadKeymap();
    void LoadKey(const CString& sKey, SHORT index);
    void SetKey(INT nIndex, BYTE nKey, BYTE nKeyFlag);
    void LoadOptions();
    void SaveOptions();
    void UpdatePortrait(SHORT nPortrait, DWORD dwPanelId);
    SHORT GetCharacterPortaitNum(LONG nCharacterId);
    void WorldEngineActivated(CVidMode* pVidMode);
    void WorldEngineDeactivated();
    void OnPortraitLClick(DWORD id);
    void OnPortraitLDblClick(DWORD id);
    void EnablePortrait(BYTE nControlId, BOOL bEnable);
    BOOL Is3DSound(int nSoundChannel);
    float GetSoundReverbMix(int nSoundChannel, int nReverb);
    void SynchronousUpdate();
    BOOL DeleteSaveGame(const CString& sFileName);
    BOOL SaveGameExists(const CString& sSaveGame);
    void ApplyVolumeSliders(BOOLEAN a2);
    LONG GetCharacterSlot(INT nCharacterSlot);
    BYTE GetCharactersControlled();
    BOOLEAN RestParty(int a2, unsigned char a3);
    BOOL CanRestParty(STRREF& strError, unsigned char a2, unsigned char a3, unsigned char a4);
    CStringList* GetPortraits();
    CStringList* GetImportCharacters();
    CStringList* GetSounds();
    void MultiplayerSetCharacterCreationLocation();

    INT GetCurrentChapter();
    void SetCurrentChapter(INT nChapter);
    CInfButtonArray* GetButtonArray();
    LONG GetCharacterId(SHORT nPortrait);
    CTimerWorld* GetWorldTimer();
    SHORT GetNumCharacters();
    CGameObjectArray* GetObjectArray();
    CGameArea* GetVisibleArea();
    CMultiplayerSettings* GetMultiplayerSettings();
    CGameJournal* GetJournal();

    const CRuleTables& GetRuleTables() { return m_ruleTables; }

    static const CString FOGOWAR_RESREF;
    static const CString SAVE_OBJECT_LIST_NAME;
    static const CString CHAPTER_GLOBAL;
    static const CString TOKEN_CURRENT_CHAPTER;
    static const CString TOKEN_CHARACTER;
    static const CString TOKEN_GABBER;
    static const CString TOKEN_SIRMAAM;
    static const CString TOKEN_GIRLBOY;
    static const CString TOKEN_BROTHERSISTER;
    static const CString TOKEN_LADYLORD;
    static const CString TOKEN_MALEFEMALE;
    static const CString TOKEN_HESHE;
    static const CString TOKEN_HISHER;
    static const CString TOKEN_RACE;
    static const CString TOKEN_HIMHER;
    static const CString TOKEN_MANWOMAN;
    static const CString TOKEN_GABBER_SIRMAAM;
    static const CString TOKEN_GABBER_GIRLBOY;
    static const CString TOKEN_GABBER_BROTHERSISTER;
    static const CString TOKEN_GABBER_LADYLORD;
    static const CString TOKEN_GABBER_MALEFEMALE;
    static const CString TOKEN_GABBER_HESHE;
    static const CString TOKEN_GABBER_HISHER;
    static const CString TOKEN_GABBER_RACE;
    static const CString TOKEN_GABBER_HIMHER;
    static const CString TOKEN_GABBER_MANWOMAN;
    static const CString TOKEN_PLAYER1;
    static const CString TOKEN_PLAYER2;
    static const CString TOKEN_PLAYER3;
    static const CString TOKEN_PLAYER4;
    static const CString TOKEN_PLAYER5;
    static const CString TOKEN_PLAYER6;
    static const CString TOKEN_SURFACE_UNDERDARK;
    static const CString AUTO_SAVE_NAME;
    static const CString QUICK_SAVE_NAME;
    static const CString QUICK_SAVE_BACKUP_NAME;
    static const CString SILHOUETTE_PORTRAIT_SM;
    static const CString SILHOUETTE_PORTRAIT_LG;

    static BOOL dword_8E7524;

    /* 0000 */ CRuleTables m_ruleTables;
    /* 1B58 */ CCriticalSection field_1B58;
    /* 1B78 */ CTimerWorld m_worldTime;
    /* 1B96 */ SHORT m_nState;
    /* 1BA1 */ unsigned char field_1BA1;
    /* 1BB2 */ CMultiplayerSettings m_multiplayerSettings;
    /* 1C78 */ CInfButtonArray m_cButtonArray;
    /* 3662 */ CVRamPool m_cVRamPool;
    /* 366E */ int field_366E;
    /* 372C */ CGameObjectArray m_cObjectArray;
    /* 37E0 */ BYTE m_visibleArea;
    /* 37E2 */ CGameArea* m_gameAreas[12];
    /* 3812 */ CGameArea* m_pGameAreaMaster;
    /* 3816 */ LONG m_characters[6];
    /* 382E */ LONG m_characterPortraits[6];
    /* 3846 */ SHORT m_nCharacters;
    /* 43E2 */ int field_43E2;
    /* 43EA */ CGameOptions m_cOptions; // #guess
    /* 44C8 */ CGameJournal m_cJournal;
    /* 4514 */ BYTE m_pKeymap[CINFGAME_KEYMAP_SIZE];
    /* 4688 */ BOOLEAN m_pKeymapFlags[CINFGAME_KEYMAP_SIZE];
    /* 4A00 */ HANDLE m_hSearchThread; // #guess
    /* 4AA2 */ ULONG field_4AA2;
    // NOTE: Can also be BYTE indicating number of expansion pack.
    /* 4BD5 */ BOOLEAN m_bExpansion;
    /* 4BD8 */ DWORD m_nDifficultyLevel;
    /* 50D8 */ BOOL field_50D8;
    /* 50DC */ unsigned char field_50DC;
};

#endif /* CINFGAME_H_ */

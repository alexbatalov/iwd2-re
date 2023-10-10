#ifndef CINFGAME_H_
#define CINFGAME_H_

#include "mfc.h"

#include <vector>

#include "CAIGroup.h"
#include "CGameJournal.h"
#include "CGameObjectArray.h"
#include "CGameOptions.h"
#include "CGameRemoteObjectArray.h"
#include "CInfButtonArray.h"
#include "CInfinity.h"
#include "CMoveList.h"
#include "CMultiplayerSettings.h"
#include "CResGame.h"
#include "CRuleTables.h"
#include "CStrRes.h"
#include "CTimerWorld.h"
#include "CVariableHash.h"
#include "CVidBitmap.h"
#include "CVidPalette.h"
#include "CWorldMap.h"

// Seen in `CRuleTables::GetStartPoint` assertion.
#define CINFGAME_MAXCHARACTERS 6

// Seen in `CScreenOptions::OnKeyDown` assertion.
#define CINFGAME_KEYMAP_SIZE 372

#define CINFGAME_SPECIAL_SYMBOLS 12

// Seen in `CScreenSinglePlayer::UpdateModifyCharacterPanel` assertion.
#define CINFGAME_MAXCHARACTERS 6

// Seen in `CInfGame::GetArea` assertion.
#define CINFGAME_MAX_AREAS 12

class CGameArea;
class CItem;
class CStore;

// NOTE: The following spell-list related classes are new in IWD2, there are
// alsmost no hints about their names or structure. They were declared/defined
// in `InfGame.h` and `InfGame.cpp` respectively, but should ideally moved
// somewhere else.

class CSpellResRefList {
public:
    CSpellResRefList();
    ~CSpellResRefList();
    void Load(const C2DArray& Table, const INT& nResRefColumn);
    bool Find(const CResRef& resRef, UINT& nID);
    const CResRef& Get(UINT& nIndex);

    /* 0000 */ CResRef* m_pList;
    /* 0004 */ UINT m_nCount;
};

class CSpellListEntry {
public:
    /* 0000 */ UINT m_nID;
    /* 0004 */ UINT m_nLevel;
};

class CSpellList {
public:
    CSpellList();
    ~CSpellList();
    void Load(const std::vector<CSpellListEntry>& spells);
    bool GetSpellLevel(const UINT& nID, UINT& nLevel);

    UINT Get(UINT nIndex);

    /* 0000 */ CSpellListEntry* m_pList;
    /* 0004 */ UINT m_nCount;
};

class CGroupedSpellList {
public:
    CGroupedSpellList();
    ~CGroupedSpellList();
    void Load(const C2DArray& Table, const INT& nClassColumn, const INT& nResRefColumn, CSpellResRefList* pSpells);

    /* 0000 */ CSpellList m_lists[CSPELLLIST_MAX_LEVELS];
    /* 0048 */ UINT m_nHighestLevel;
};

class CInfGame {
public:
    static const SHORT KILL_INNOCENT;
    static const SHORT INJURE_INNOCENT;
    static const SHORT STEAL;
    static const SHORT KILL_FIST;
    static const SHORT MONEY_CHURCH;
    static const SHORT MONEY_BEGGAR;
    static const SHORT MAGIC_CHURCH;
    static const SHORT KILL_EVIL;
    static const SHORT BASE_CHURCH;
    static const SHORT REPUTATION_MULTIPLIER;

    static const DWORD PROGRESSBAR_AREA_ADDITIONAL;
    static const DWORD PROGRESSBAR_GAME_ADDITIONAL;
    static const DWORD PROGRESSBAR_REQUESTS_ADDITIONAL;
    static const DWORD PROGRESSBAR_CACHING_ADDITIONAL;

    static const SHORT FEEDBACK_GOLD;

    CInfGame();
    ~CInfGame();
    void StartSearchThread();
    void InitGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace);
    void BeginListManipulation(CGameArea* pArea);
    INT EndListManipulation(CGameArea* pArea);
    void sub_59FA00(BOOL a1);
    void DestroyGame(unsigned char a1, unsigned char a2);
    void sub_5A0160();
    LONG ImportCharacter(const CString& sFileName, INT nIndex);
    CString GetDirSounds();
    void CharacterExport(LONG nCharacterId, CString sFileName);
    CGameArea* LoadArea(CString areaName, BYTE nTravelScreenImageToUse, BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace);
    BOOLEAN CanSaveGame(STRREF& strError, unsigned char a2, unsigned char a3);
    BOOL SaveGame(unsigned char a1, unsigned char a2, unsigned char a3);
    BOOL Unmarshal(BYTE* pGame, LONG nGame, BOOLEAN bProgressBarInPlace);
    void ProgressBarCallback(DWORD dwSize, BOOLEAN bInitialize);
    char sub_5A9780(BYTE nKey);
    BYTE sub_5A97D0(char ch);
    BYTE sub_5A9830(int index);
    void LoadKeymap();
    void LoadKey(const CString& sKey, SHORT index);
    void SetKey(INT nIndex, BYTE nKey, BYTE nKeyFlag);
    void LoadOptions();
    void SaveOptions();
    void LoadMultiPlayerPermissions();
    void SaveMultiPlayerPermissions();
    void LoadGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace);
    void NewGame(BOOLEAN bProgressBarRequired, BOOLEAN bProgressBarInPlace);
    BOOLEAN sub_5AC0A0(CGameArea* pArea);
    void sub_5AC0D0();
    void SelectAll(BOOLEAN bPlaySound);
    void UnselectAll();
    BOOL SelectCharacter(LONG characterId, BOOLEAN bPlaySelectSound);
    void SelectToolbar();
    void DemandServerStore(const CResRef& store, BOOL bSaveToDisk);
    void ReleaseServerStore(const CResRef& store);
    CStore* GetServerStore(const CResRef& store);
    void SwapCharacters(DWORD pos1, DWORD pos2);
    void UpdatePortrait(SHORT nPortrait, DWORD dwPanelId);
    void sub_5AF420(SHORT nPortrait, DWORD dwPanelId);
    SHORT GetCharacterPortraitNum(LONG nCharacterId);
    SHORT GetFixedOrderCharacterPortraitNum(LONG nCharacterId);
    void RemoveFamiliarResRef(const CResRef& resRef, BYTE nAlignment, BYTE nLevel);
    void RenderPortrait(DWORD portraitId, const CPoint& cpRenderPosition, const CSize& szControl, BOOL bPressed, BOOL reorderHighlight, BOOL selectFromMarker, const CRect& rClip, BOOL bDoubleSize);
    void WorldEngineActivated(CVidMode* pVidMode);
    void WorldEngineDeactivated();
    void OnPortraitLClick(DWORD id);
    void OnPortraitLDblClick(DWORD id);
    void EnablePortrait(BYTE nControlId, BOOL bEnable);
    BOOLEAN ExtendedDayNightAreaActive();
    void UpdatePortraitToolTip(DWORD dwControlId, STRREF dwStrId);
    CGameArea* GetArea(CString sName);
    CGameArea* GetArea(SHORT nArea);
    LONG GetGroundPile(LONG iSprite);
    SHORT GetNumGroundSlots(LONG nContainerId);
    void InventoryInfoGround(LONG nContainerId, SHORT nSlotNum, CItem*& pItem, STRREF& description, CResRef& cResIcon, CResRef& cResItem, WORD& wCount);
    WORD GetContainerType(LONG nContainerId);
    void CompressContainer(LONG nContainerId);
    SHORT GetNumQuickWeaponSlots(SHORT nPortrait);
    void InventoryInfoPersonal(SHORT nPortraitNum, SHORT nSlotNum, CItem*& pItem, STRREF& description, CResRef& cResIcon, CResRef& cResItem, WORD& wCount, BOOL a8);
    BOOL Is3DSound(int nSoundChannel);
    float GetSoundReverbMix(int nSoundChannel, int nReverb);
    CResRef GetAnimationBam(SHORT nPortrait, BYTE range);
    BYTE GetFrameRate();
    void SynchronousUpdate();
    BOOL DeleteSaveGame(const CString& sFileName);
    BOOL SaveGameExists(const CString& sSaveGame);
    void ApplyVolumeSliders(BOOLEAN a2);
    BOOL AddCharacterToParty(LONG id, SHORT nPortraitNumber);
    BOOL RemoveCharacterFromParty(LONG id, BOOL& overflow);
    BOOL SetCharacterSlot(INT nCharacterSlot, LONG nCharacterId);
    BOOL ClearCharacterSlot(INT nCharacterSlot);
    LONG GetCharacterSlot(INT nCharacterSlot);
    INT GetCharacterSlotFromId(LONG nCharacterId);
    void UpdateCharacterSlots();
    BOOL AddCharacterToAllies(LONG nCharacterId);
    BOOL RemoveCharacterFromAllies(LONG nCharacterId);
    BOOL AddCharacterToFamiliars(LONG nCharacterId);
    BOOL RemoveCharacterFromFamiliars(LONG nCharacterId);
    DWORD GetScrollSpeed();
    void sub_5BDBA0(int a1, BOOL a2);
    void ReputationAdjustment(SHORT reputationAdjustment, BOOL set);
    void ChangeReputation(SHORT eventCode);
    void AddDisposableItem(CItem* pItem);
    void DestroyDisposableItems();
    void AddPartyGold(LONG dwAddPartyGold);
    void SetupCharacters(BOOLEAN bProgressBarInPlace);
    LONG GetProtagonist();
    void SetProtagonist(LONG nId);
    BOOLEAN FindAreaID(DWORD nAreaId);
    CStringList* GetSaveGames();
    CString GetDirSaveRoot();
    CString GetDirSave();
    CString sub_5C0B30();
    BOOL AddCharacterToOverflow(LONG id);
    CStringList* GetScripts();
    CString GetDirScripts();
    static void StartCharacterTerminationSequence();
    void ReadyCharacterTerminationSequence(int a1, int a2);
    void FeedBack(SHORT feedBackId, LONG value, BOOLEAN a3);
    CString GetDirPortraits();
    CString GetDirCharacters();
    BYTE GetCharactersControlled();
    BOOLEAN RestParty(int a2, unsigned char a3);
    BOOL CanRestParty(STRREF& strError, unsigned char a2, unsigned char a3, unsigned char a4);
    CStringList* GetPortraits();
    CStringList* GetImportCharacters();
    CStringList* GetSounds();
    void ChangeBiography(BYTE nFixedPartyId, CString szBiography);
    BOOLEAN GetGameSpyCharacterInformation(INT nCharacterSlot, CString& sName, CString& sRace, CString& sClass, CString& sLevel);
    void MultiplayerSetCharacterCreationLocation();
    INT sub_5C93E0();
    void ResetMultiPlayerPermissions();

    UINT GetSpellcasterIndex(const BYTE& nClass);
    BYTE GetSpellcasterClass(const UINT& nIndex);
    DWORD GetSpellcasterClassMask(const UINT& nIndex);
    UINT GetSpellcasterDomainIndex(const DWORD& dwMask);
    DWORD GetClassMask(const BYTE& nClass);
    BYTE GetSpellType(const CResRef& resRef);
    void sub_5CADF0();

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
    CAIGroup* GetGroup();
    CVariableHash* GetVariables();
    CVidBitmap* GetMasterBitmap();
    CNamedCreatureVariableHash* GetNamedCreatures();
    void SetTempCursor(BYTE tempCursor);
    CGameOptions* GetOptions();
    SHORT GetState();
    void SetState(SHORT nState);
    BYTE GetIconIndex();
    void SetIconIndex(BYTE iconIndex);
    CSpellResRefList* GetSongs();
    CSpellResRefList* GetInnateSpells();
    CSpellResRefList* GetShapeshifts();
    CString GetSaveGame();

    const CRuleTables& GetRuleTables() { return m_ruleTables; }

    // NOTE: Remote cousin of `GetObjectArray`.
    CGameRemoteObjectArray* GetRemoteObjectArray() { return &m_cRemoteObjectArray; }

    LONG GetFixedOrderCharacterId(SHORT nSlot);

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

    static BOOL m_bHealPartyOnRest;
    static BOOLEAN byte_8E7528;
    static int dword_8E752C;

    // NOTE: Probably does not belong here.
    static int dword_8E52EC;
    static int dword_8E52F0;

    /* 0000 */ CRuleTables m_ruleTables;
    /* 1B58 */ CCriticalSection field_1B58;
    /* 1B78 */ CTimerWorld m_worldTime;
    /* 1B7E */ BOOL m_bGameLoaded;
    /* 1B82 */ BOOLEAN m_bInLoadGame;
    /* 1B83 */ BOOLEAN m_bInLoadArea;
    /* 1B84 */ unsigned char field_1B84;
    /* 1B92 */ BOOLEAN m_bFromNewGame;
    /* 1B94 */ BOOLEAN m_bAnotherPlayerJoinedGame;
    /* 1B96 */ SHORT m_nState;
    /* 1B98 */ BYTE m_iconIndex;
    /* 1B99 */ CResRef m_iconResRef;
    /* 1BA1 */ unsigned char m_tempCursor;
    /* 1BA2 */ LONG m_iContainer;
    /* 1BAA */ CGamePermission m_singlePlayerPermissions;
    /* 1BB2 */ CMultiplayerSettings m_multiplayerSettings;
    /* 1C78 */ CInfButtonArray m_cButtonArray;
    /* 3662 */ CVRamPool m_cVRamPool;
    /* 366E */ int field_366E;
    /* 3672 */ CVidBitmap m_rgbMasterBitmap;
    /* 372C */ CGameObjectArray m_cObjectArray;
    /* 375A */ CGameRemoteObjectArray m_cRemoteObjectArray;
    /* 37E0 */ BYTE m_visibleArea;
    /* 37E1 */ BOOLEAN m_bPlayerScriptStyle;
    /* 37E2 */ CGameArea* m_gameAreas[CINFGAME_MAX_AREAS];
    /* 3812 */ CGameArea* m_pGameAreaMaster;
    /* 3816 */ LONG m_characters[6];
    /* 382E */ LONG m_characterPortraits[6];
    /* 3846 */ SHORT m_nCharacters;
    /* 3848 */ CTypedPtrList<CPtrList, int*> m_lstGlobalCreatures; // NOTE: Stores actual ints disguised as pointers.
    /* 3864 */ CTypedPtrList<CPtrList, int*> m_characterOverflow;
    /* 3878 */ SHORT m_nCharacterOverflowCount;
    /* 387A */ SHORT m_nReputation;
    /* 3884 */ CAIGroup m_group;
    /* 38A8 */ CTypedPtrList<CPtrList, int*> m_allies; // NOTE: Stores actual ints disguised as pointers.
    /* 38C4 */ CTypedPtrList<CPtrList, int*> m_familiars; // NOTES: Stores actual ints disguised as pointers.
    /* 38E0 */ unsigned char field_38E0[72];
    /* 3928 */ CTypedPtrList<CPtrList, CResRef*> m_familiarResRefs[9][9];
    /* 4204 */ int field_4204;
    /* 4208 */ CString m_sTempDir;
    /* 420C */ CString m_sTempSaveDir;
    /* 4210 */ CString m_sScriptsDir;
    /* 4214 */ CString m_sSoundsDir;
    /* 4218 */ CString m_sPortraitsDir;
    /* 421C */ CString m_sCharactersDir;
    /* 4220 */ CString m_sSaveGame;
    /* 4224 */ CString m_sSaveDir;
    /* 4228 */ CString m_sMultiplayerSaveDir;
    /* 4238 */ DWORD m_nPartyGold;
    /* 423C */ SHORT m_curFormation;
    /* 4248 */ CItem* m_groupInventory[100];
    /* 43D8 */ int field_43D8;
    /* 43DC */ short field_43DC;
    /* 43E2 */ int field_43E2;
    /* 43E6 */ int field_43E6;
    /* 43EA */ CGameOptions m_cOptions; // #guess
    /* 44C8 */ CGameJournal m_cJournal;
    /* 44DC */ CWorldMap m_cWorldMap;
    /* 4514 */ BYTE m_pKeymap[CINFGAME_KEYMAP_SIZE];
    /* 4688 */ BOOLEAN m_pKeymapFlags[CINFGAME_KEYMAP_SIZE];
    /* 47FC */ CVariableHash m_variables;
    /* 4808 */ CNamedCreatureVariableHash m_namedCreatures;
    /* 4814 */ STR_RES field_4814;
    /* 487C */ STR_RES field_487C;
    /* 48E4 */ BOOLEAN m_bForceDither;
    /* 4A8A */ LONG m_nProtagonistId;
    /* 4A8E */ BOOLEAN m_bPartyAI;
    /* 4A8F */ BOOLEAN m_bShowAreaNotes;
    /* 4A90 */ BYTE m_nTravelScreenImageToUse;
    /* 4A9A */ DWORD m_dwLastProgressRenderTickCount;
    /* 4A9E */ DWORD m_dwLastProgressMsgTickCount;
    /* 4A00 */ HANDLE m_hSearchThread; // #guess
    /* 4A04 */ CCriticalSection m_disposableItemsCritSect;
    /* 4A24 */ CTypedPtrList<CPtrList, CItem*> m_lDisposableItems;
    /* 4AA2 */ ULONG m_nLastSaveTime;
    /* 4AA6 */ CPoint m_lastClick;
    /* 4AAE */ LONG m_lastTarget;
    /* 4AB2 */ unsigned char field_4AB2;
    /* 4AB4 */ CVidPalette m_entanglePalette;
    /* 4AD8 */ CVidPalette m_webHoldPalette;
    /* 4AFC */ int field_4AFC;
    /* 4B00 */ CMoveList m_cMoveList;
    /* 4B1C */ CMoveList m_cLimboList;
    /* 4B38 */ int field_4B38;
    /* 4B3C */ LONG m_nAIIndex;
    /* 4B40 */ LONG m_nTimeStop;
    /* 4B44 */ LONG m_nTimeStopCaster;
    /* 4B48 */ CStore* m_aServerStore[12];
    /* 4B78 */ BYTE m_nServerStoreDemands[12];
    /* 4B84 */ CString field_4B84;
    /* 4B88 */ CString field_4B88;
    /* 4B8C */ CString field_4B8C;
    /* 4B90 */ CString field_4B90;
    // NOTE: Can also be BYTE indicating number of expansion pack.
    /* 4BD5 */ BOOLEAN m_bExpansion;
    /* 4BD6 */ BOOLEAN field_4BD6;
    /* 4BD8 */ DWORD m_nDifficultyLevel;
    /* 4BF8 */ CSpellResRefList m_spells;
    /* 4C00 */ CSpellResRefList m_innateSpells;
    /* 4C08 */ CSpellResRefList m_songs;
    /* 4C10 */ CSpellResRefList m_shapeshifts;
    /* 4C18 */ CGroupedSpellList m_spellsByClass[7];
    /* 4E2C */ CGroupedSpellList m_spellsByDomain[9];
    /* 50D8 */ BOOL field_50D8;
    /* 50DC */ unsigned char field_50DC;
};

class CGameFile : public CResHelper<CResGame, 1013> {
public:
    BYTE* GetData();
    DWORD GetDataSize();
};

#endif /* CINFGAME_H_ */

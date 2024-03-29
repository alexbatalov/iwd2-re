#ifndef CGAMEAREA_H_
#define CGAMEAREA_H_

#include "mfc.h"

#include "CGameAreaNotes.h"
#include "CInfinity.h"
#include "CMemINI.h"
#include "CResArea.h"
#include "CSearchBitmap.h"
#include "CSound.h"
#include "CVariableHash.h"
#include "CVidBitmap.h"
#include "CVisibility.h"
#include "FileFormat.h"

class CAIObjectType;
class CInfGame;
class CObjectMarker;
class CSpawnFile;
class CTiledObject;
class CVidMode;

class CAreaFileHeader {
public:
    CAreaFileHeader()
    {
        memset(this, 0, sizeof(*this));
    }

    RESREF m_areaName;
    DWORD m_lastSaved;
    DWORD m_flags;
    RESREF m_areaEdgeNorth;
    DWORD m_flagsEdgeNorth;
    RESREF m_areaEdgeEast;
    DWORD m_flagsEdgeEast;
    RESREF m_areaEdgeSouth;
    DWORD m_flagsEdgeSouth;
    RESREF m_areaEdgeWest;
    DWORD m_flagsEdgeWest;
    WORD m_areaType;
    WORD m_rainProbability;
    WORD m_snowProbability;
    WORD m_fogProbability;
    WORD m_lightningProbability;
    WORD m_windSpeed;
    DWORD field_4C;
    DWORD field_50;
    DWORD field_54;
    DWORD field_58;
};

class CAreaSoundsAndMusic {
public:
    CAreaSoundsAndMusic()
    {
        memset(this, 0, sizeof(*this));
    }

    DWORD m_dayMusic;
    DWORD m_nightMusic;
    DWORD m_battleWinningMusic;
    DWORD m_battleStandOffMusic;
    DWORD m_battleLosingMusic;
    DWORD m_alt1Music0;
    DWORD m_alt1Music1;
    DWORD m_alt1Music2;
    DWORD m_alt1Music3;
    DWORD m_alt1Music4;
    RESREF m_dayAmbient;
    RESREF m_dayAmbientExtended;
    DWORD m_dayAmbientVolume;
    RESREF m_nightAmbient;
    RESREF m_nightAmbientExtended;
    DWORD m_nightAmbientVolume;
    DWORD m_reverb;
    DWORD m_notUsed[15];
};

class CAreaFileOffsets {
public:
    CAreaFileOffsets()
    {
        memset(this, 0, sizeof(*this));
    }

    DWORD m_creatureTableOffset;
    WORD m_creatureTableCount;
    WORD m_triggerObjectListCount;
    DWORD m_triggerObjectListOffset;
    DWORD m_randomMonsterSpawningPointTableOffset;
    DWORD m_randomMonsterSpawningPointTableCount;
    DWORD m_characterEntryPointTableOffset;
    DWORD m_characterEntryPointTableCount;
    DWORD m_containerListOffset;
    WORD m_containerListCount;
    WORD m_itemObjectsCount;
    DWORD m_itemObjectsOffset;
    DWORD m_pointsOffset;
    WORD m_pointsCount;
    WORD m_soundObjectCount;
    DWORD m_soundObjectOffset;
    DWORD m_areaScriptVariablesOffset;
    WORD m_areaScriptVariablesCount;
    WORD m_tiledObjectFlagsCount;
    DWORD m_tiledObjectFlagsOffset;
    RESREF m_script;
    DWORD m_visibilityMapCount;
    DWORD m_visibilityMapOffset;
    DWORD m_doorObjectListCount;
    DWORD m_doorObjectListOffset;
    DWORD m_staticObjectListCount;
    DWORD m_staticObjectListOffset;
    DWORD m_tiledObjectListCount;
    DWORD m_tiledObjectListOffset;
    DWORD m_areaSoundsAndMusicOffset;
    DWORD m_restingEncounterOffset;
    DWORD m_userMapNotesOffset;
    DWORD m_userMapNotesCount;
    DWORD m_projectileTableOffset;
    DWORD m_projectileTableCount;
    RESREF m_restMovieDay;
    RESREF m_restMovieNight;
    DWORD m_notUsed[14];
};

class CAreaFileRestEncounter {
public:
    CAreaFileRestEncounter()
    {
        memset(this, 0, sizeof(*this));
    }

    /* 0000 */ SCRIPTNAME m_scriptName;
    /* 0020 */ STRREF m_randomCreatureString[10];
    /* 0048 */ RESREF m_randomCreature[10];
    /* 0098 */ WORD m_randomCreatureNum;
    /* 009A */ WORD m_difficulty;
    /* 009C */ DWORD m_lifeSpan;
    /* 00A0 */ WORD m_huntingRange;
    /* 00A2 */ WORD m_followRange;
    /* 00A4 */ WORD m_maxTypeNum;
    /* 00A6 */ WORD m_activated;
    /* 00A8 */ WORD m_probDay;
    /* 00AA */ WORD m_probNight;
    /* 00AC */ WORD m_wFlags;
    /* 00AE */ BYTE m_weights[10];
    /* 00B8 */ DWORD m_notUsed[11];
};

class CGameArea {
public:
    CGameArea(BYTE id);
    ~CGameArea();

    INT SetListManipulationThreadId(DWORD ThreadID);
    void AddObject(LONG id, BYTE listType);
    BOOL AdjustTarget(CPoint start, POINT* goal, BYTE personalSpace, SHORT tolerance);
    BOOL SnapshotAdjustTarget(CPoint start, POINT* goal, BOOL bBump, SHORT tolerance);
    void ApplyWindToAmbients(BYTE nPercentVolume);
    BOOL CheckLOS(const CPoint& start, const CPoint& goal, const BYTE* terrainTable, BOOLEAN bCheckIfExplored);
    BOOL CheckWalkable(const CPoint& start, const CPoint& goal, const BYTE* terrainTable, BYTE personalSpace, BOOLEAN bCheckIfExplored);
    LONG GetGroundPile(const CPoint& ptPos);
    LONG GetNearest(LONG startObject, const CAIObjectType& type, SHORT range, const BYTE* terrainTable, BOOL checkLOS, BOOL seeInvisible, BOOL ignoreSleeping, BYTE nNearest, BOOL ignoreDead);
    void GetAllInRange(const CPoint& center, const CAIObjectType& type, SHORT range, const BYTE* terrainTable, CTypedPtrList<CPtrList, LONG*>& targets, BOOL lineOfSight, BOOL checkForNonSprites);
    int GetCountInRange(const CPoint& center, SHORT range, const CAIObjectType& type);
    int GetCountInPoly(const CRect& rBounding, const CAIObjectType& type);
    void GetAllInRangeBack(const CPoint& center, const CAIObjectType& type, SHORT range, const BYTE* terrainTable, CTypedPtrList<CPtrList, LONG*>& targets, BOOL lineOfSight, BOOL ignoreDead, BOOL checkForNonSprites);
    void GetAllInPoly(const CRect& rBounding, CPoint* pPoly, SHORT nPoly, const CAIObjectType& type, const BYTE* terrainTable, CTypedPtrList<CPtrList, LONG*>& targets, BOOLEAN checkBackList);
    LONG sub_46DAE0(INT x, INT y, const CAIObjectType& type, int a4, const BYTE* terrainTable, int a6, int a7, int a8, int a9);
    BOOLEAN CanSaveGame(STRREF& strError);
    void AIUpdate();
    void CompressTime(DWORD deltaTime);
    void DebugDump(const CString& message, BOOLEAN bEchoToScreen);
    void ClearInput();
    void ClearMarshal();
    BOOLEAN GetEntryPoint(const CString& sName, CPoint& ptEnter, SHORT& facing);
    int GetHeightOffset(const CPoint& pt, BYTE listType);
    void IncrHeightDynamic(const CPoint& point);
    void DecrHeightDynamic(const CPoint& point);
    COLORREF GetTintColor(const CPoint& cPoint, BYTE listType);
    void Unmarshal(BYTE* pArea, LONG areaSize, const CString& sName, BOOLEAN bProgressBarInPlace);
    void ProgressBarCallback(DWORD dwSize, BOOLEAN bInitialize);
    void SetListenPosition();
    void OnActivation();
    void OnDeactivation();
    void OnActionButtonDown(const CPoint& pt);
    void OnActionButtonClickGround(const CPoint& pt);
    void OnActionButtonClickTravel(const CPoint& pt);
    void OnActionButtonUp(const CPoint& pt);
    void OnActionButtonDblClk(const CPoint& pt);
    void OnFormationButtonDown(const CPoint& pt);
    void OnFormationButtonUp(const CPoint& pt);
    void OnMouseMove(const CPoint& pt);
    void RemoveObject(POSITION posVertList, BYTE listType, LONG id);
    void OnLightningStrike();
    void Render(CVidMode* pVidMode, INT nSurface);
    void SetDay();
    void SetNight();
    void SetApproachingDawn();
    void SetApproachingDusk();
    void SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetNewResWED(CResWED* pNewResWED);
    void SetTimeOfDay(ULONG nTimeOfDay, BOOLEAN bPlayDayNightMovie);
    void SetSoundEnvironment();
    void SortLists();
    BOOL SetSong(SHORT slot, BYTE song);
    BYTE GetSong(SHORT slot);
    void PlaySong(SHORT slot, DWORD flags);
    void sub_47A060();
    int ExitSpawn();
    int EnterSpawn();
    void sub_47A190();

    CAreaFileHeader* GetHeader();
    CInfinity* GetInfinity();
    CVariableHash* GetVariables();
    CAreaFileRestEncounter* GetHeaderRestEncounter();
    CNamedCreatureVariableHash* GetNamedCreatures();
    CGameAreaNotes* GetAreaNotes();
    LONG GetBattleSongCounter();
    BYTE GetId();

    void AddToMarkers(LONG id);
    void RemoveFromMarkers(LONG id);

    static INT dword_8D212C;
    static BOOLEAN byte_8D2138;

    /* 0000 */ CAreaFileHeader m_header;
    /* 005C */ CAreaSoundsAndMusic m_headerSound;
    /* 00EC */ CAreaFileRestEncounter m_headerRestEncounter;
    /* 01D0 */ CTypedPtrList<CPtrList, CAreaFileCharacterEntryPoint*> m_entryPoints;
    /* 01EC */ BYTE m_id;
    /* 01ED */ BYTE m_nCharacters;
    /* 01EE */ BYTE m_nInfravision;
    /* 01EF */ BOOLEAN m_bAreaLoaded;
    /* 01F0 */ CResRef m_resRef;
    /* 01F8 */ CResWED* m_pResWED;
    /* 01FC */ CRITICAL_SECTION field_1FC;
    /* 0214 */ CRITICAL_SECTION field_214;
    /* 022C */ INT m_nListManipulationThreadCounter;
    /* 0230 */ DWORD m_ListManipulationThreadId;
    /* 0234 */ CInfGame* m_pGame;
    /* 0238 */ LONG m_nScrollState;
    /* 023C */ LONG m_nKeyScrollState;
    /* 0240 */ BOOLEAN m_bTravelSquare;
    /* 0241 */ unsigned char field_241;
    /* 0242 */ LONG m_iPickedOnDown;
    /* 0246 */ LONG m_iPicked;
    /* 024A */ LONG m_iPickedTarget;
    /* 024E */ BOOL m_bPicked;
    /* 0252 */ LONG m_nToolTip;
    /* 0256 */ CPoint m_ptMousePos;
    /* 025E */ CVidBitmap m_bmLum;
    /* 0318 */ CVidBitmap* m_pbmLumNight;
    /* 031C */ CVidBitmap m_bmHeight;
    /* 03D6 */ CObjectMarker* m_pObjectMarker;
    /* 03DA */ BYTE m_firstRender;
    /* 03DC */ CRect m_selectSquare;
    /* 03EC */ short field_3EC;
    /* 03EE */ CPoint m_moveDest;
    /* 03F6 */ BOOL m_groupMove;
    /* 03FA */ BYTE m_terrainTable[16];
    /* 040A */ BYTE m_visibleTerrainTable[16];
    /* 041A */ LONG m_nAIIndex;
    /* 041E */ BOOL m_bInPathSearch;
    /* 0422 */ DWORD m_nInitialAreaID;
    /* 0426 */ DWORD m_nFirstObject;
    /* 042A */ DWORD m_dwLastProgressRenderTickCount;
    /* 042E */ DWORD m_dwLastProgressMsgTickCount;
    /* 0432 */ BYTE m_nRandomMonster;
    /* 0434 */ SHORT m_nVisibleMonster;
    /* 0436 */ unsigned char field_436;
    /* 0438 */ int field_438;
    /* 043C */ CGameAreaNotes m_cGameAreaNotes;
    /* 04CC */ CInfinity m_cInfinity;
    /* 076C */ CSearchBitmap m_search;
    /* 0860 */ CVisibilityMap m_visibility;
    /* 08BC */ CSound m_sndAmbientDay;
    /* 0920 */ CSound m_sndAmbientNight;
    /* 0984 */ BYTE m_sndAmbientVolume;
    /* 0986 */ WORD m_sndAmbientDayVolume;
    /* 0988 */ WORD m_sndAmbientNightVolume;
    /* 098A */ BOOL m_startedMusic;
    /* 098E */ DWORD m_startedMusicCounter;
    /* 0992 */ CTypedPtrList<CPtrList, int*> m_lVertSort; // NOTE: Stores actual ints disguised as pointers.
    /* 09AE */ CTypedPtrList<CPtrList, int*> m_lVertSortBack; // NOTE: Stores actual ints disguised as pointers.
    /* 099A */ CTypedPtrList<CPtrList, int*> m_lVertSortFlight; // NOTE: Stores actual ints disguised as pointers.
    /* 09E6 */ CTypedPtrList<CPtrList, int*> m_lVertSortAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A02 */ CTypedPtrList<CPtrList, int*> m_lVertSortBackAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A1E */ CTypedPtrList<CPtrList, int*> m_lVertSortFlightAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A3A */ CTypedPtrList<CPtrList, POSITION> m_lVertSortRemove;
    /* 0A56 */ CTypedPtrList<CPtrList, POSITION> m_lVertSortBackRemove;
    /* 0A72 */ CTypedPtrList<CPtrList, POSITION> m_lVertSortFlightRemove;
    /* 0A8E */ CTypedPtrList<CPtrList, CTiledObject*> m_lTiledObjects;
    /* 0AC6 */ CPoint m_ptOldViewPos;
    /* 0ACE */ CVariableHash m_variables;
    /* 0ADA */ CNamedCreatureVariableHash m_namedCreatures;
    /* 0AE6 */ unsigned char field_AE6;
    /* 0AE8 */ SHORT m_nCurrentSong;
    /* 0AEA */ INT m_nBattleSongCounter;
    /* 0AEE */ CMemINI INIFile;
    /* 0B0E */ int field_B0E;
    /* 0B12 */ CSpawnFile* mpSpawner;
    /* 0B16 */ BOOL field_B16;
};

class CAreaFile : public CResHelper<CResArea, 1010> {
public:
    BYTE* GetData();
    DWORD GetDataSize();
    void ReleaseData();
};

#endif /* CGAMEAREA_H_ */

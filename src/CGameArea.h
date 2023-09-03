#ifndef CGAMEAREA_H_
#define CGAMEAREA_H_

#include "mfc.h"

#include "CGameAreaNotes.h"
#include "CInfinity.h"
#include "CSearchBitmap.h"
#include "CSound.h"
#include "CVariableHash.h"
#include "CVidBitmap.h"
#include "CVisibility.h"
#include "FileFormat.h"

class CInfGame;
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
    void ApplyWindToAmbients(BYTE nPercentVolume);
    BOOLEAN CanSaveGame(STRREF& strError);
    void ProgressBarCallback(DWORD dwSize, BOOLEAN bInitialize);
    void SetListenPosition();
    void OnActivation();
    void OnDeactivation();
    void OnActionButtonDown(const CPoint& pt);
    void OnActionButtonClickGround(const CPoint& pt);
    void OnActionButtonUp(const CPoint& pt);
    void OnActionButtonDblClk(const CPoint& pt);
    void OnFormationButtonDown(const CPoint& pt);
    void OnFormationButtonUp(const CPoint& pt);
    void OnMouseMove(const CPoint& pt);
    void RemoveObject(POSITION posVertList, BYTE listType, LONG id);
    void OnLightningStrike();
    void Render(CVidMode* pVidMode, int a2);
    void SetDay();
    void SetNight();
    void SetApproachingDawn();
    void SetApproachingDusk();
    void SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie);
    void SetTimeOfDay(ULONG nTimeOfDay, BOOLEAN bPlayDayNightMovie);
    void SetSoundEnvironment();
    BOOL SetSong(SHORT slot, BYTE song);
    BYTE GetSong(SHORT slot);
    void PlaySong(SHORT slot, DWORD flags);

    CInfinity* GetInfinity();
    CVariableHash* GetVariables();
    CAreaFileRestEncounter* GetHeaderRestEncounter();
    CNamedCreatureVariableHash* GetNamedCreatures();

    static INT dword_8D212C;
    static BOOLEAN byte_8D2138;

    /* 0000 */ CAreaFileHeader m_header;
    /* 005C */ CAreaSoundsAndMusic m_headerSound;
    /* 00EC */ CAreaFileRestEncounter m_headerRestEncounter;
    /* 01EC */ BYTE m_id;
    /* 01ED */ unsigned char field_1ED;
    /* 01EE */ unsigned char field_1EE;
    /* 01EF */ BOOLEAN m_bAreaLoaded;
    /* 01F0 */ CResRef m_resRef;
    /* 01F8 */ int field_1F8;
    /* 01FC */ CRITICAL_SECTION field_1FC;
    /* 0214 */ CRITICAL_SECTION field_214;
    /* 022C */ INT m_nListManipulationThreadCounter;
    /* 0230 */ DWORD m_ListManipulationThreadId;
    /* 0234 */ CInfGame* m_pGame;
    /* 0238 */ LONG m_nScrollState;
    /* 023C */ LONG m_nKeyScrollState;
    /* 0240 */ unsigned char field_240;
    /* 0241 */ unsigned char field_241;
    /* 0242 */ LONG field_242;
    /* 0246 */ LONG m_iPicked;
    /* 024A */ LONG m_iPickedTarget;
    /* 024E */ int field_24E;
    /* 0252 */ int field_252;
    /* 0256 */ CPoint m_ptMousePos;
    /* 025E */ CVidBitmap m_bmLum;
    /* 0318 */ int field_318;
    /* 031C */ CVidBitmap m_bmHeight;
    /* 03D6 */ int field_3D6;
    /* 03DA */ BYTE m_firstRender;
    /* 03DC */ int field_3DC;
    /* 03E0 */ int field_3E0;
    /* 03E4 */ int field_3E4;
    /* 03E8 */ int field_3E8;
    /* 03EC */ short field_3EC;
    /* 03EE */ int field_3EE;
    /* 03F2 */ int field_3F2;
    /* 03F6 */ BOOL m_groupMove;
    /* 03FA */ BYTE m_terrainTable[16];
    /* 040A */ BYTE m_visibleTerrainTable[16];
    /* 041A */ int field_41A;
    /* 041E */ int field_41E;
    /* 0422 */ DWORD m_nInitialAreaId;
    /* 0422 */ int m_nInitialAreaID;
    /* 0426 */ int field_426;
    /* 042A */ DWORD m_dwLastProgressRenderTickCount;
    /* 042E */ DWORD m_dwLastProgressMsgTickCount;
    /* 0432 */ unsigned char field_432;
    /* 0434 */ short field_434;
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
    /* 098A */ int field_98A;
    /* 098E */ int field_98E;
    /* 0992 */ CTypedPtrList<CPtrList, int*> m_lVertSort; // NOTE: Stores actual ints disguised as pointers.
    /* 09E6 */ CTypedPtrList<CPtrList, int*> m_lVertSortAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A02 */ CTypedPtrList<CPtrList, int*> m_lVertSortBackAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A1E */ CTypedPtrList<CPtrList, int*> m_lVertSortFlightAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A8E */ CTypedPtrList<CPtrList, CTiledObject*> m_lTiledObjects;
    /* 0AC6 */ CPoint m_ptOldViewPos;
    /* 0ACE */ CVariableHash m_variables;
    /* 0ADA */ CNamedCreatureVariableHash m_namedCreatures;
    /* 0AE6 */ unsigned char field_AE6;
    /* 0AE8 */ SHORT m_nCurrentSong;
    /* 0AEA */ INT m_nBattleSongCounter;
    /* 0B0E */ int field_B0E;
    /* 0B12 */ int field_B12;
    /* 0B16 */ BOOL field_B16;
};

#endif /* CGAMEAREA_H_ */

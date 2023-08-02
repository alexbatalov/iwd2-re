#ifndef CGAMEAREA_H_
#define CGAMEAREA_H_

#include "mfc.h"

#include "CInfinity.h"
#include "CSound.h"
#include "FileFormat.h"

class CInfGame;

typedef struct {
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
} CAreaFileHeader;

typedef struct {
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
} CAreaSoundsAndMusic;

typedef struct {
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
} CAreaFileRestEncounter;

class CGameArea {
public:
    CGameArea();
    ~CGameArea();

    INT SetListManipulationThreadId(DWORD ThreadID);
    void AddObject(LONG id, BYTE listType);
    void ApplyWindToAmbients(BYTE nPercentVolume);
    void SetListenPosition();
    void OnActivation();
    void OnDeactivation();
    void RemoveObject(POSITION posVertList, BYTE listType, LONG id);
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
    CAreaFileRestEncounter* GetHeaderRestEncounter();

    static INT dword_8D212C;
    static BOOLEAN byte_8D2138;

    /* 0000 */ CAreaFileHeader m_header;
    /* 005C */ CAreaSoundsAndMusic m_headerSound;
    /* 00EC */ CAreaFileRestEncounter m_headerRestEncounter;
    /* 01EF */ BOOLEAN m_bAreaLoaded;
    /* 01F0 */ CResRef m_resRef;
    /* 0214 */ CRITICAL_SECTION field_214;
    /* 022C */ INT m_nListManipulationThreadCounter;
    /* 0230 */ DWORD m_ListManipulationThreadId;
    /* 0234 */ CInfGame* m_pGame;
    /* 0238 */ LONG m_nScrollState;
    /* 023C */ LONG m_nKeyScrollState;
    /* 0256 */ CPoint m_ptMousePos;
    /* 03DA */ BYTE m_firstRender;
    /* 03DC */ int field_3DC;
    /* 03E0 */ int field_3E0;
    /* 03E4 */ int field_3E4;
    /* 03E8 */ int field_3E8;
    /* 03F6 */ int field_3F6;
    /* 0422 */ DWORD m_nInitialAreaId;
    /* 04CC */ CInfinity m_cInfinity;
    /* 08BC */ CSound m_sndAmbientDay;
    /* 0920 */ CSound m_sndAmbientNight;
    /* 0984 */ BYTE m_sndAmbientVolume;
    /* 0986 */ WORD m_sndAmbientDayVolume;
    /* 0988 */ WORD m_sndAmbientNightVolume;
    /* 09E6 */ CTypedPtrList<CPtrList, int*> m_lVertSortAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A02 */ CTypedPtrList<CPtrList, int*> m_lVertSortBackAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0A1E */ CTypedPtrList<CPtrList, int*> m_lVertSortFlightAdd; // NOTE: Stores actual ints disguised as pointers.
    /* 0AE8 */ SHORT m_nCurrentSong;
    /* 0AEA */ INT m_nBattleSongCounter;
};

#endif /* CGAMEAREA_H_ */

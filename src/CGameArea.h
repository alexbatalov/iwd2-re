#ifndef CGAMEAREA_H_
#define CGAMEAREA_H_

#include "mfc.h"

#include "CInfinity.h"
#include "CSound.h"

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

class CGameArea {
public:
    CGameArea();
    ~CGameArea();

    void ApplyWindToAmbients(BYTE nPercentVolume);
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

    static INT dword_8D212C;
    static BOOLEAN byte_8D2138;

    /* 0000 */ CAreaFileHeader m_header;
    /* 005C */ CAreaSoundsAndMusic m_headerSound;
    /* 01EF */ BOOLEAN m_bAreaLoaded;
    /* 04CC */ CInfinity m_cInfinity;
    /* 08BC */ CSound m_sndAmbientDay;
    /* 0920 */ CSound m_sndAmbientNight;
    /* 0984 */ BYTE m_sndAmbientVolume;
    /* 0986 */ WORD m_sndAmbientDayVolume;
    /* 0988 */ WORD m_sndAmbientNightVolume;
};

#endif /* CGAMEAREA_H_ */

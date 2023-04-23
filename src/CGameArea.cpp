#include "CGameArea.h"

#include "CBaldurChitin.h"
#include "CChitin.h"
#include "CInfGame.h"

// 0x469B60
CGameArea::CGameArea()
{
    // TODO: Incomplete.
}

// 0x46A070
CGameArea::~CGameArea()
{
    // TODO: Incomplete.
}

// 0x46A7B0
void CGameArea::ApplyWindToAmbients(BYTE nPercentVolume)
{
    m_sndAmbientVolume = nPercentVolume;
    m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
    m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
}

// 0x477EE0
void CGameArea::SetDay()
{
    m_sndAmbientNight.Stop();
    m_sndAmbientDayVolume = m_headerSound.m_dayAmbientVolume;

    if (m_sndAmbientDay.IsSoundPlaying()) {
        m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
    } else {
        if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
            m_sndAmbientDay.SetResRef(CResRef(m_headerSound.m_dayAmbient), TRUE, TRUE);
            if (m_sndAmbientDay.GetResRef() != "") {
                m_sndAmbientDay.SetLoopingFlag(TRUE);
                m_sndAmbientDay.SetChannel(1, reinterpret_cast<uintptr_t>(this));
                m_sndAmbientDay.SetVolume(m_sndAmbientDayVolume * m_sndAmbientVolume / 100);
                m_sndAmbientDay.Play(FALSE);
            }
        }
    }

    if ((m_cInfinity.m_areaType & 2) != 0) {
        m_cInfinity.SetDay();
    }
}

// 0x4781B0
void CGameArea::SetNight()
{
    m_sndAmbientDay.Stop();
    m_sndAmbientNightVolume = m_headerSound.m_nightAmbientVolume;

    if (m_sndAmbientNight.IsSoundPlaying()) {
        m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
    } else {
        if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
            m_sndAmbientNight.SetResRef(CResRef(m_headerSound.m_nightAmbient), TRUE, TRUE);
            if (m_sndAmbientNight.GetResRef() != "") {
                m_sndAmbientNight.SetLoopingFlag(TRUE);
                m_sndAmbientNight.SetChannel(1, reinterpret_cast<uintptr_t>(this));
                m_sndAmbientNight.SetVolume(m_sndAmbientNightVolume * m_sndAmbientVolume / 100);
                m_sndAmbientNight.Play(FALSE);
            }
        }
    }

    if ((m_cInfinity.m_areaType & 2) != 0) {
        m_cInfinity.SetNight();
    }
}

// 0x478480
void CGameArea::SetApproachingDawn()
{
    m_cInfinity.SetApproachingDawn();
}

// 0x478480
void CGameArea::SetApproachingDusk()
{
    m_cInfinity.SetApproachingDusk();
}

// 0x478490
void CGameArea::SetDawn(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    // TODO: Incomplete.
}

// 0x478AC0
void CGameArea::SetDusk(BYTE nIntensity, BOOLEAN bPlayDayNightMovie)
{
    // TODO: Incomplete.
}

// 0x479110
void CGameArea::SetTimeOfDay(ULONG nTimeOfDay, BOOLEAN bPlayDayNightMovie)
{
    // TODO: Incomplete.
}

// 0x479260
void CGameArea::SetSoundEnvironment()
{
    // NOTE: Not sure why they are explicit. Probably remapping from one enum
    // to other.
    switch (m_headerSound.m_reverb) {
    case 0:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_GENERIC);
        break;
    case 1:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PADDEDCELL);
        break;
    case 2:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ROOM);
        break;
    case 3:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_BATHROOM);
        break;
    case 4:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_LIVINGROOM);
        break;
    case 5:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_STONEROOM);
        break;
    case 6:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_AUDITORIUM);
        break;
    case 7:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CONCERTHALL);
        break;
    case 8:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CAVE);
        break;
    case 9:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ARENA);
        break;
    case 10:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_HANGAR);
        break;
    case 11:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CARPETEDHALLWAY);
        break;
    case 12:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_HALLWAY);
        break;
    case 13:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_STONECORRIDOR);
        break;
    case 14:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_ALLEY);
        break;
    case 15:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_FOREST);
        break;
    case 16:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_CITY);
        break;
    case 17:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_MOUNTAINS);
        break;
    case 18:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_QUARRY);
        break;
    case 19:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PLAIN);
        break;
    case 20:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PARKINGLOT);
        break;
    case 21:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_SEWERPIPE);
        break;
    case 22:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_UNDERWATER);
        break;
    case 23:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_DRUGGED);
        break;
    case 24:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_DIZZY);
        break;
    case 25:
        g_pBaldurChitin->cSoundMixer.m_cSoundProperties.SetEnvironmentPreset(EAX_ENVIRONMENT_PSYCHOTIC);
        break;
    }
}

// 0x479CC0
BOOL CGameArea::SetSong(SHORT slot, BYTE song)
{
    switch (slot) {
    case 0:
        m_headerSound.m_dayMusic = song;
        return TRUE;
    case 1:
        m_headerSound.m_nightMusic = song;
        return TRUE;
    case 2:
        m_headerSound.m_battleWinningMusic = song;
        return TRUE;
    case 3:
        m_headerSound.m_battleStandOffMusic = song;
        return TRUE;
    case 4:
        m_headerSound.m_battleLosingMusic = song;
        return TRUE;
    case 5:
        m_headerSound.m_alt1Music0 = song;
        return TRUE;
    case 6:
        m_headerSound.m_alt1Music1 = song;
        return TRUE;
    case 7:
        m_headerSound.m_alt1Music2 = song;
        return TRUE;
    case 8:
        m_headerSound.m_alt1Music3 = song;
        return TRUE;
    case 9:
        m_headerSound.m_alt1Music4 = song;
        return TRUE;
    default:
        return FALSE;
    }
}

// 0x479DB0
BYTE CGameArea::GetSong(SHORT slot)
{
    if (slot > 256) {
        return -1;
    }

    BYTE song;
    if (slot != 256) {
        switch (slot) {
        case 0:
            song = m_headerSound.m_dayMusic;
            break;
        case 1:
            song = m_headerSound.m_nightMusic;
            break;
        case 2:
            song = m_headerSound.m_battleWinningMusic;
            break;
        case 3:
            song = m_headerSound.m_battleStandOffMusic;
            break;
        case 4:
            song = m_headerSound.m_battleLosingMusic;
            break;
        case 5:
            song = m_headerSound.m_alt1Music0;
            break;
        case 6:
            song = m_headerSound.m_alt1Music1;
            break;
        case 7:
            song = m_headerSound.m_alt1Music2;
            break;
        case 8:
            song = m_headerSound.m_alt1Music3;
            break;
        case 9:
            song = m_headerSound.m_alt1Music4;
            break;
        default:
            return -1;
        }
    } else {
        if (g_pBaldurChitin->m_pObjectGame->m_worldTime.IsDay() || g_pBaldurChitin->m_pObjectGame->m_worldTime.IsDusk()) {
            song = m_headerSound.m_dayMusic;
        } else {
            song = m_headerSound.m_nightMusic;
        }
    }

    if (song == 0) {
        song = -1;
    }

    return song;
}

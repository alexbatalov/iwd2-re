#include "CSound.h"

#include "CChitin.h"
#include "CSoundMixer.h"

// 0x9060EC
CSoundMixer* CSound::m_pSoundMixer;

// #binary-identical
// 0x7A8BB0
CSound::CSound()
{
    m_pSoundMixer = &(g_pChitin->cSoundMixer);
    field_1C = 0;
    field_34 = 0;
    field_18 = 0;
    field_24 = 0;
    field_54 = 0;
    m_nChannel = 0;
    m_nLooping = 0;
    field_14 = 0;
    field_28 = 0;
    field_2C = 0;
    field_30 = 0;
    field_3C = 0;
    pSoundBuffer = NULL;
    field_4C = 0;
    field_50 = 0;
    m_bFireForget = FALSE;
    m_nArea = 0;
    m_nVolume = 100;
    m_nPriority = INT_MAX;
    m_nRange = 768;
}

// 0x7A8C90
CSound::CSound(CResRef cResRef, int nRange, int nChannel, int nLooping, int nPriority, BOOL bPositionedSound)
{
    SetResRef(cResRef, TRUE, TRUE);

    m_pSoundMixer = &(g_pChitin->cSoundMixer);
    field_1C = 0;
    field_34 = 0;
    m_nVolume = 100;
    field_18 = 0;
    field_24 = 0;
    field_54 = 0;
    field_28 = 0;
    field_2C = 0;
    field_30 = 0;
    m_nChannel = nChannel;
    m_nPriority = nPriority;
    if (nRange > 0) {
        m_nRange = nRange;
    } else {
        m_nRange = 1;
    }
    field_14 = 0;
    field_3C = 0;
    pSoundBuffer = NULL;
    field_4C = 0;
    field_50 = 0;
    m_bFireForget = FALSE;
    m_nArea = 0;
}

// 0x7A8F60
BOOL CSound::SetFireForget(BOOL bNewFireForget)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7AA110
void CSound::ResetVolume()
{
    // TODO: Incomplete.
}

// 0x7AA4B0
BOOL CSound::SetChannel(int nNewChannel, DWORD nArea)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A9AB0
DWORD CSound::GetStatus()
{
    if (pSoundBuffer != NULL) {
        DWORD dwStatus;
        pSoundBuffer->GetStatus(&dwStatus);
        return dwStatus;
    }
    return 0;
}

// 0x7A9AE0
BOOL CSound::IsSoundPlaying()
{
    if (pSoundBuffer != NULL) {
        DWORD dwStatus;
        pSoundBuffer->GetStatus(&dwStatus);
        return (dwStatus & DSBSTATUS_PLAYING) != 0;
    } else {
        return FALSE;
    }
}

// 0x7A9B10
BOOL CSound::Play(BOOL bReplay)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7AA690
BOOL CSound::SetLoopingFlag(int nNewLooping)
{
    if (nNewLooping != 0 && nNewLooping != 1) {
        return FALSE;
    }

    if (m_bFireForget) {
        return FALSE;
    }

    m_nLooping = nNewLooping;

    return TRUE;
}

// 0x7AA710
void CSound::SetRange(int nNewRange)
{
    if (nNewRange > 0) {
        m_nRange = nNewRange;
    } else {
        m_nRange = 1;
    }
}

// 0x7AA730
void CSound::SetVolume(int nNewVolume)
{
    // TODO: Incomplete.
}

// 0x7AA910
void CSound::Stop()
{
    // TODO: Incomplete.
}

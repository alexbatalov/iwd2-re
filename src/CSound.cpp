#include "CSound.h"

// 0x7AA110
void CSound::ResetVolume()
{
    // TODO: Incomplete.
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

// NOTE: Inlined in `CSoundMixer::UpdateSoundPositions`.
BOOL CSound::IsPlaying()
{
    if (pSoundBuffer != NULL) {
        DWORD dwStatus;
        pSoundBuffer->GetStatus(&dwStatus);
        return (dwStatus & DSBSTATUS_PLAYING) != 0;
    } else {
        return FALSE;
    }
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

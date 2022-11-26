#include "CSound.h"

// 0x7AA110
void CSound::ResetVolume()
{
    // TODO: Incomplete.
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

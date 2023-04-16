#include "CVoice.h"

#include "CSound.h"
#include "CUtil.h"

// NOTE: Inlined in `CSoundMixer::AddSound`.
CVoice::CVoice()
{
    m_pSound = NULL;
    m_pSoundBuffer = NULL;
    m_nChannel = -1;
    m_nPriority = 0x7FFFFFFF;
}

// 0x7AAB70
CVoice::~CVoice()
{
    if (m_pSound != NULL) {
        if (m_pSound->pSoundBuffer != NULL) {
            m_pSound->pSoundBuffer->Release();
            m_pSound->pSoundBuffer = NULL;
        }
    } else {
        if (m_pSoundBuffer != NULL) {
            m_pSoundBuffer->Release();
            m_pSoundBuffer = NULL;
        }
    }
}

// NOTE: Inlined in `CSoundMixer::AddSound`.
void CVoice::SetSound(CSound* pSound)
{
    m_pSound = pSound;
    if (pSound != NULL) {
        m_nChannel = pSound->m_nChannel;
        m_nPriority = pSound->m_nPriority;
    }
}

// NOTE: Inlined in `CSoundMixer::UpdateSoundPositions`.
BOOL CVoice::GetLooping()
{
    if (m_pSound != NULL) {
        return m_pSound->GetLooping();
    } else {
        return FALSE;
    }
}

// NOTE: Inlined in `CSoundMixer::UpdateSoundPositions`.
//
// 0x7AABF0
BOOL CVoice::IsSoundPlaying()
{
    if (m_pSound != NULL) {
        return m_pSound->IsSoundPlaying();
    } else {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
        // __LINE__: 2152
        UTIL_ASSERT(m_pSoundBuffer != NULL);

        DWORD dwStatus;
        m_pSoundBuffer->GetStatus(&dwStatus);
        return (dwStatus & DSBSTATUS_PLAYING) != 0;
    }
}

// 0x7AAC70
int CVoice::GetChannel()
{
    if (m_pSound != NULL) {
        return m_pSound->m_nChannel;
    }

    return m_nChannel;
}

// NOTE: Inlined in `CSoundMixer::UpdateSoundPositions`.
void CVoice::ResetVolume()
{
    if (m_pSound != NULL) {
        m_pSound->ResetVolume();
    }
}

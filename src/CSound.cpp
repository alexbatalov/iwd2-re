#include "CSound.h"

#include "CChitin.h"
#include "CSoundMixer.h"
#include "CUtil.h"

// 0x9060EC
CSoundMixer* CSound::m_pSoundMixer;

// #binary-identical
// 0x7A8BB0
CSound::CSound()
{
    m_pSoundMixer = &(g_pChitin->cSoundMixer);
    m_dwFrequency = 0;
    m_nPan = 0;
    m_nBuffer = 0;
    m_nRangeVolume = 0;
    m_b3DPositioning = FALSE;
    m_nChannel = 0;
    m_nLooping = 0;
    m_bPositionedSound = FALSE;
    m_nXCoordinate = 0;
    m_nYCoordinate = 0;
    m_nZCoordinate = 0;
    field_3C = 0;
    pSoundBuffer = NULL;
    m_nPitchVariance = 0;
    m_nVolumeVariance = 0;
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
    m_dwFrequency = 0;
    m_nPan = 0;
    m_nVolume = 100;
    m_nBuffer = 0;
    m_nRangeVolume = 0;
    m_b3DPositioning = FALSE;
    m_nXCoordinate = 0;
    m_nYCoordinate = 0;
    m_nZCoordinate = 0;
    m_nChannel = nChannel;
    m_nPriority = nPriority;
    if (nRange > 0) {
        m_nRange = nRange;
    } else {
        m_nRange = 1;
    }
    m_bPositionedSound = FALSE;
    field_3C = 0;
    pSoundBuffer = NULL;
    m_nPitchVariance = 0;
    m_nVolumeVariance = 0;
    m_bFireForget = FALSE;
    m_nArea = 0;
}

// 0x7A8E20
CSound::~CSound()
{
    if (m_pSoundMixer->GetMixerInitialized()) {
        if (m_bFireForget) {
            m_pSoundMixer->TransferBuffer(this);
        } else {
            if (m_nLooping) {
                m_pSoundMixer->RemoveFromLoopingList(this);
            }

            ExclusiveStop();
        }
    } else {
        ExclusiveStop();
    }
}

// 0x7A8F60
BOOL CSound::SetFireForget(BOOL bNewFireForget)
{
    if (!m_pSoundMixer->GetMixerInitialized()) {
        return FALSE;
    }

    if (m_nLooping != 0) {
        if (bNewFireForget) {
            return FALSE;
        }
    } else {
        if (bNewFireForget) {
            if (m_pSoundMixer->GetChannelType(m_nChannel) == 1) {
                return FALSE;
            }
        }
    }

    m_bFireForget = bNewFireForget;

    return FALSE;
}

// 0x7A9020
BOOL CSound::CopyData()
{
    // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
    // __LINE__: 317
    UTIL_ASSERT(pSoundBuffer != NULL);

    LPVOID pvAudioPtr1;
    DWORD dwAudioBytes1;
    LPVOID pvAudioPtr2;
    DWORD dwAudioBytes2;
    HRESULT hr = pSoundBuffer->Lock(0, m_nBuffer, &pvAudioPtr1, &dwAudioBytes1, &pvAudioPtr2, &dwAudioBytes2, 0);
    if (hr != S_OK) {
        return FALSE;
    }

    pRes->CopyWaveData(reinterpret_cast<BYTE*>(pvAudioPtr1));
    pSoundBuffer->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);

    // TODO: Strange cmp at 0x7A90AC, check.
    return TRUE;
}

// 0x7A90D0
BOOL CSound::Create2DBuffer(LPWAVEFORMATEX waveFormat)
{
    DSBUFFERDESC desc = { 0 };
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME;
    desc.dwBufferBytes = pRes->GetWaveSize();
    desc.lpwfxFormat = waveFormat;

    if (FAILED(m_pSoundMixer->m_pDirectSound->CreateSoundBuffer(&desc, &pSoundBuffer, NULL))) {
        return FALSE;
    }

    int nChannelVolume = m_pSoundMixer->GetChannelVolumeFast(m_nChannel);
    if (m_bPositionedSound) {
        if (FAILED(pSoundBuffer->SetVolume(30 * (m_nRangeVolume * (nChannelVolume * m_nVolume / 100) / 100 - 100)))) {
            DestroyBuffer(&pSoundBuffer);
            return FALSE;
        }
    } else {
        if (FAILED(pSoundBuffer->SetVolume(30 * (nChannelVolume * m_nVolume / 100 - 100)))) {
            DestroyBuffer(&pSoundBuffer);
            return FALSE;
        }
    }

    if (pSoundBuffer->SetPan(50 * m_nPan) != DS_OK) {
        DestroyBuffer(&pSoundBuffer);
        return FALSE;
    }

    if (pSoundBuffer->SetFrequency(500 * m_dwFrequency) != DS_OK) {
        DestroyBuffer(&pSoundBuffer);
        return FALSE;
    }

    m_nBuffer = desc.dwBufferBytes;

    return TRUE;
}

// 0x7A9260
BOOL CSound::Create3DBuffer(LPWAVEFORMATEX waveFormat, float mix)
{
    LPDIRECTSOUND3DBUFFER soundBuffer3D;

    DSBUFFERDESC desc = { 0 };
    desc.dwSize = sizeof(desc);
    desc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLVOLUME;
    desc.dwBufferBytes = pRes->GetWaveSize();
    desc.lpwfxFormat = waveFormat;

    if (FAILED(m_pSoundMixer->m_pDirectSound->CreateSoundBuffer(&desc, &pSoundBuffer, NULL))) {
        return Create2DBuffer(waveFormat);
    }

    int nChannelVolume = m_pSoundMixer->GetChannelVolumeFast(m_nChannel);

    HRESULT hr;
    if (m_bPositionedSound) {
        if (SUCCEEDED(pSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, reinterpret_cast<LPVOID*>(&soundBuffer3D)))) {
            hr = pSoundBuffer->SetVolume(30 * (nChannelVolume * m_nVolume / 100 - 100));
            m_b3DPositioning = TRUE;

            soundBuffer3D->SetMinDistance(128.0, 0);

            soundBuffer3D->SetPosition(m_nXCoordinate, m_nYCoordinate, m_nZCoordinate, 0);
            soundBuffer3D->Release();
        } else {
            hr = pSoundBuffer->SetVolume(30 * ((nChannelVolume * m_nVolume / 100) / 100 - 100));
            m_b3DPositioning = FALSE;
        }
    } else {
        if (SUCCEEDED(pSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, reinterpret_cast<LPVOID*>(&soundBuffer3D)))) {
            soundBuffer3D->SetMode(1, 0);
            soundBuffer3D->Release();
        }

        hr = pSoundBuffer->SetVolume(30 * (nChannelVolume * m_nVolume / 100 - 100));
        m_b3DPositioning = FALSE;
    }

    if (FAILED(hr)) {
        DestroyBuffer(&pSoundBuffer);
        return Create2DBuffer(waveFormat);
    }

    if (pSoundBuffer->SetFrequency(500 * m_dwFrequency) != DS_OK) {
        DestroyBuffer(&pSoundBuffer);
        return Create2DBuffer(waveFormat);
    }

    m_nBuffer = desc.dwBufferBytes;

    if (SUCCEEDED(pSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, reinterpret_cast<LPVOID*>(&soundBuffer3D)))) {
        m_pSoundMixer->m_cSoundProperties.SetBufferReverbMix(soundBuffer3D, mix);
    }

    return TRUE;
}

// NOTE: Inlined.
void CSound::DestroyBuffer(LPDIRECTSOUNDBUFFER* soundBufferPtr)
{
    if (soundBufferPtr != NULL) {
        (*soundBufferPtr)->Release();
        *soundBufferPtr = NULL;
    }
}

// 0x7A94F0
BOOL CSound::ExclusivePlay(BOOL bReplay)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7A9910
BOOL CSound::ExclusiveStop()
{
    // NOTE: Uninline.
    if (m_pSoundMixer->IsSoundWaiting(this)) {
        m_pSoundMixer->RemoveWaiting(this);
    }

    if (pSoundBuffer != NULL) {
        HRESULT hr = pSoundBuffer->Stop();
        m_pSoundMixer->UpdateSoundList();
        return hr == DS_OK;
    }

    return FALSE;
}

// 0x7A9A20
DWORD CSound::GetPlayTime()
{
    // FIXME: Can return uninitialized value.
    DWORD playTime;

    if (Request()) {
        LPWAVEFORMATEX waveFormat = pRes->GetWaveFormatPtr();
        if (waveFormat != NULL) {
            DWORD size = pRes->GetWaveSize();
            if (size >= 4294967) {
                playTime = 1000 * (size / waveFormat->nAvgBytesPerSec);
            } else {
                playTime = 1000 * size / waveFormat->nAvgBytesPerSec;
            }
        }
        Release();
    }

    return playTime;
}

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

// 0x7A9AD0
int CSound::GetVolume()
{
    return m_nVolume;
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

// 0x7A9DB0
BOOL CSound::Play(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate, BOOL bReplay)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x7AA4B0
BOOL CSound::SetChannel(int nNewChannel, DWORD nArea)
{
    if (m_pSoundMixer->GetMixerInitialized()) {
        return FALSE;
    }

    m_nArea = nArea;

    if (nNewChannel < 0 || nNewChannel >= m_pSoundMixer->m_nMaxChannels) {
        nNewChannel = g_pChitin->GetNumberSoundChannels() - 1;
    }

    if (m_bFireForget) {
        if (m_pSoundMixer->GetMixerInitialized()) {
            if (m_pSoundMixer->GetChannelType(nNewChannel) == 1) {
                m_nChannel = g_pChitin->GetNumberSoundChannels() - 1;
                m_nPriority >>= 1;
                return FALSE;
            }
        }
    }

    m_nChannel = nNewChannel;
    m_nPriority = 25 * (g_pChitin->GetNumberSoundChannels() - m_nChannel - 1);

    return TRUE;
}

// 0x7AA5E0
void CSound::SetCoordinates(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate)
{
    m_nXCoordinate = nNewXCoordinate;
    m_nYCoordinate = nNewYCoordinate;
    m_nZCoordinate = nNewZCoordinate;

    if (m_bPositionedSound && m_b3DPositioning) {
        if (IsSoundPlaying()) {
            LPDIRECTSOUND3DBUFFER soundBuffer3D;
            if (SUCCEEDED(pSoundBuffer->QueryInterface(IID_IDirectSound3DBuffer, reinterpret_cast<LPVOID*>(&soundBuffer3D)))) {
                soundBuffer3D->SetPosition(m_nXCoordinate, m_nYCoordinate, m_nZCoordinate, 0);
                soundBuffer3D->Release();
            }
        }
    } else {
        if (m_pSoundMixer->GetMixerInitialized()) {
            m_pSoundMixer->UpdateSoundPositions();
        }
    }
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

// 0x7AA6C0
void CSound::SetPriority(BYTE nNewPriority)
{
    if (nNewPriority > 99) {
        nNewPriority = 99;
    }

    m_nPriority = nNewPriority + 100 * (g_pChitin->GetNumberSoundChannels() - m_nChannel - 1);
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
BOOL CSound::SetVolume(int nNewVolume)
{
    if (!m_pSoundMixer->GetMixerInitialized()) {
        return FALSE;
    }

    int nChannelVolume = m_pSoundMixer->GetChannelVolumeFast(m_nChannel);
    m_nVolume = nNewVolume;

    if (pSoundBuffer != NULL) {
        if (m_nVolume != 0 && nChannelVolume != 0) {
            if (m_bPositionedSound) {
                if (FAILED(pSoundBuffer->SetVolume(30 * (m_nRangeVolume * (nChannelVolume * m_nVolume / 100) / 100 - 100)))) {
                    return FALSE;
                }
            } else {
                if (FAILED(pSoundBuffer->SetVolume(30 * (nChannelVolume * m_nVolume / 100 - 100)))) {
                    return FALSE;
                }
            }
        } else {
            // NOTE: Uninline.
            ExclusiveStop();
        }
    } else {
        if (m_nVolume > 0 && nChannelVolume > 0 && m_nLooping != 0) {
            if (m_bPositionedSound) {
                Play(m_nXCoordinate, m_nYCoordinate, m_nZCoordinate, FALSE);
            } else {
                Play(FALSE);
            }
        }
    }

    return TRUE;
}

// 0x7AA910
BOOL CSound::Stop()
{
    if (m_pSoundMixer->GetMixerInitialized()) {
        if (m_nLooping != 0) {
            // NOTE: Uninline.
            m_pSoundMixer->RemoveFromLoopingList(this);
        }

        // NOTE: Uninline.
        return ExclusiveStop();
    } else {
        if (m_nLooping != 0) {
            // NOTE: Uninline.
            m_pSoundMixer->RemoveFromLoopingList(this);
        }

        return FALSE;
    }
}

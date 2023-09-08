#include "CSound.h"

#include "CChitin.h"
#include "CSoundChannel.h"
#include "CSoundMixer.h"
#include "CUtil.h"
#include "CVoice.h"

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
    m_nLooping = nLooping;
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

    int nBytesRead = pRes->CopyWaveData(reinterpret_cast<BYTE*>(pvAudioPtr1));
    pSoundBuffer->Unlock(pvAudioPtr1, dwAudioBytes1, pvAudioPtr2, dwAudioBytes2);

    // TODO: Not sure what it means.
    return nBytesRead != 1190;
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

            soundBuffer3D->SetPosition(static_cast<D3DVALUE>(m_nXCoordinate),
                static_cast<D3DVALUE>(m_nYCoordinate),
                static_cast<D3DVALUE>(m_nZCoordinate),
                DS3D_IMMEDIATE);
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
    HRESULT hr;

    if (!m_pSoundMixer->m_bMixerInitialized) {
        return FALSE;
    }

    if (GetRes() == NULL) {
        return FALSE;
    }

    if (GetRes()->GetResRef() == CResRef("BLANK")) {
        return FALSE;
    }

    CSoundChannel* pChannel = static_cast<CSoundChannel*>(m_pSoundMixer->m_aChannels[m_nChannel]);

    if (m_nVolume > 0 && pChannel->m_nVolume > 0) {
        BOOL bFound = FALSE;

        if ((m_pSoundMixer->field_C0 & 0x1) != 0) {
            m_pSoundMixer->Lock();

            POSITION pos = m_pSoundMixer->m_lVoices.GetHeadPosition();
            while (pos != NULL) {
                CVoice* pVoice = static_cast<CVoice*>(m_pSoundMixer->m_lVoices.GetNext(pos));
                if (pVoice->m_pSound == this) {
                    bFound = TRUE;
                }
            }

            m_pSoundMixer->Unlock();
        }

        if (bFound) {
            // NOTE: Uninline.
            if (IsSoundPlaying() && bReplay) {
                return TRUE;
            }

            if (m_bPositionedSound) {
                hr = IDirectSoundBuffer_SetVolume(pSoundBuffer,
                    30 * (m_nRangeVolume * (pChannel->m_nVolume * m_nVolume / 100) / 100 - 100));
            } else {
                hr = IDirectSoundBuffer_SetVolume(pSoundBuffer,
                    30 * (pChannel->m_nVolume * m_nVolume / 100 - 100));
            }

            if (hr != DS_OK) {
                return FALSE;
            }
        } else {
            GetRes()->Demand();

            if (!GetRes()->m_bParsed) {
                GetRes()->Release();
                return FALSE;
            }

            m_pSoundMixer->UpdateSoundList(m_nPriority);

            if (GetRes() == NULL) {
                GetRes()->Release();
                return FALSE;
            }

            LPWAVEFORMATEX pWaveFormat = GetRes()->GetWaveFormatPtr();

            if (!field_3C) {
                m_dwFrequency = pWaveFormat->nSamplesPerSec / 500;
                field_3C = TRUE;
            }

            BOOL bCreated;
            if (g_pChitin->GetEAXActive()
                && g_pChitin->Is3DSound(m_nChannel)
                && (m_pSoundMixer->m_dwEAXProperties & CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT) != 0) {
                bCreated = Create3DBuffer(pWaveFormat,
                    g_pChitin->GetSoundReverbMix(m_nChannel, m_pSoundMixer->m_cSoundProperties.m_nPreset));
            } else {
                bCreated = Create2DBuffer(pWaveFormat);
            }

            if (!bCreated) {
                GetRes()->Release();
                return FALSE;
            }

            if (!CopyData()) {
                GetRes()->Release();
                return FALSE;
            }

            GetRes()->Release();
            m_pSoundMixer->AddSound(this);
        }

        hr = IDirectSoundBuffer_SetCurrentPosition(pSoundBuffer, 0);
        if (hr != DS_OK) {
            return FALSE;
        }

        if (m_nPitchVariance > 0) {
            int dwFrequency = m_dwFrequency + 100 * m_nPitchVariance / 100 * (rand() % 100 - 50) / 50;
            if (dwFrequency < 1) {
                dwFrequency = 1;
            } else if (dwFrequency > 100) {
                dwFrequency = 100;
            }

            hr = IDirectSoundBuffer_SetFrequency(pSoundBuffer, 500 * dwFrequency);
            if (hr != DS_OK) {
                return FALSE;
            }
        }

        if (m_nLooping != 0) {
            hr = IDirectSoundBuffer_Play(pSoundBuffer, 0, 0, DSBPLAY_LOOPING);
        } else {
            hr = IDirectSoundBuffer_Play(pSoundBuffer, 0, 0, 0);
        }

        if (hr != DS_OK) {
            return FALSE;
        }

        // NOTE: Uninline.
        if (m_pSoundMixer->IsSoundWaiting(this)) {
            // NOTE: Uninline.
            m_pSoundMixer->RemoveWaiting(this);
        }
    }

    return TRUE;
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
    // FIXME: This value is uninitialized in the original code.
    DWORD playTime = 0;

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
BOOL CSound::ResetVolume()
{
    if (!m_pSoundMixer->m_bMixerInitialized) {
        return FALSE;
    }

    int nChannelVolume = m_pSoundMixer->GetChannelVolumeFast(m_nChannel);

    if (pSoundBuffer == NULL) {
        if (m_nVolume > 0
            && nChannelVolume > 0
            && m_nLooping != 0) {
            if (m_bPositionedSound) {
                Play(m_nXCoordinate, m_nYCoordinate, m_nZCoordinate, FALSE);
            } else {
                Play(FALSE);
            }
        }

        return TRUE;
    }

    if (m_nVolume == 0 || nChannelVolume == 0) {
        // NOTE: Uninline.
        if (m_pSoundMixer->IsSoundWaiting(this)) {
            m_pSoundMixer->RemoveWaiting(this);
        }

        if (pSoundBuffer != NULL) {
            IDirectSoundBuffer_Stop(pSoundBuffer);
            m_pSoundMixer->UpdateSoundList();
        }

        return TRUE;
    }

    if (!m_bPositionedSound || m_b3DPositioning) {
        HRESULT hr = IDirectSoundBuffer_SetVolume(pSoundBuffer, 30 * (nChannelVolume * m_nVolume / 100 - 100));
        if (hr != DS_OK) {
            return FALSE;
        }

        return TRUE;
    }

    if (m_nArea == 0) {
        return FALSE;
    }

    if (m_pSoundMixer->m_nXCoordinate < 0) {
        // NOTE: Uninline.
        if (m_pSoundMixer->IsSoundWaiting(this)) {
            m_pSoundMixer->RemoveWaiting(this);
        }

        if (pSoundBuffer != NULL) {
            IDirectSoundBuffer_Stop(pSoundBuffer);
            m_pSoundMixer->UpdateSoundList();
        }

        return TRUE;
    }

    int dx = m_nXCoordinate - m_pSoundMixer->m_nXCoordinate;
    int dy = m_nYCoordinate - m_pSoundMixer->m_nYCoordinate;
    int distance = dx * dx + dy + dy;
    if (distance < m_nRange * m_nRange) {
        int v1 = 10000 * distance / (m_nRange * m_nRange);
        if (v1 > 10000) {
            m_nRangeVolume = 0;
        } else {
            m_nRangeVolume = 100 * (CSoundMixer::m_tSqrtTable[10000] - CSoundMixer::m_tSqrtTable[v1]) / CSoundMixer::m_tSqrtTable[10000];
        }

        m_nPan = 100 * dx / m_pSoundMixer->m_nPanRange;

        IDirectSoundBuffer_SetPan(pSoundBuffer, 50 * m_nPan);

        HRESULT hr = IDirectSoundBuffer_SetVolume(pSoundBuffer, 30 * (nChannelVolume * m_nVolume / 100 - 100));
        if (hr != DS_OK) {
            return FALSE;
        }

        return TRUE;
    }

    m_nRangeVolume = 0;

    // NOTE: Uninline.
    if (m_pSoundMixer->IsSoundWaiting(this)) {
        m_pSoundMixer->RemoveWaiting(this);
    }

    if (pSoundBuffer != NULL) {
        IDirectSoundBuffer_Stop(pSoundBuffer);
        m_pSoundMixer->UpdateSoundList();
    }

    return TRUE;
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
    if ((m_pSoundMixer->field_C0 & 0x1) == 0) {
        return FALSE;
    }

    if (!m_pSoundMixer->m_bMixerInitialized) {
        return FALSE;
    }

    if (m_nArea != 0 && m_nArea != m_pSoundMixer->m_nActiveArea) {
        return FALSE;
    }

    m_pSoundMixer->Lock();

    if (m_nLooping != 0) {
        m_pSoundMixer->Lock();

        BOOL bFound = FALSE;

        POSITION pos = m_pSoundMixer->m_lLooping.GetHeadPosition();
        while (pos != NULL) {
            CSound* pSound = static_cast<CSound*>(m_pSoundMixer->m_lLooping.GetNext(pos));
            if (this == pSound) {
                bFound = TRUE;
            }
        }

        if (!bFound) {
            m_pSoundMixer->m_lLooping.AddHead(this);
        }

        m_pSoundMixer->Unlock();
    }

    CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_pSoundMixer->m_aChannels[m_nChannel]);

    if (pSoundChannel->m_nType == 1) {
        if (!bReplay) {
            if (pSoundChannel->m_lQueue.GetHeadPosition() != NULL) {
                pSoundChannel->m_lQueue.AddTail(this);
                m_pSoundMixer->UpdateQueue();
                m_pSoundMixer->Unlock();
                return TRUE;
            } else {
                pSoundChannel->m_lQueue.AddTail(this);
            }
        }
    } else if (pSoundChannel->m_nType == 2) {
        m_pSoundMixer->Lock();

        BOOL bPlaying = FALSE;

        POSITION pos = m_pSoundMixer->m_lVoices.GetHeadPosition();
        while (pos != NULL) {
            CVoice* pVoice = static_cast<CVoice*>(m_pSoundMixer->m_lVoices.GetNext(pos));
            if (pVoice != NULL) {
                if (!pVoice->GetLooping()) {
                    if (pVoice->IsSoundPlaying()) {
                        bPlaying = TRUE;
                        break;
                    }
                }
            }
        }

        m_pSoundMixer->Unlock();

        if (bPlaying) {
            m_pSoundMixer->Unlock();
            return TRUE;
        }
    } else if (pSoundChannel->m_nType == 3) {
        m_pSoundMixer->Lock();

        POSITION pos = m_pSoundMixer->m_lVoices.GetHeadPosition();
        while (pos != NULL) {
            POSITION currPos = pos;
            CVoice* pVoice = static_cast<CVoice*>(m_pSoundMixer->m_lVoices.GetNext(pos));
            if (pVoice->GetChannel() == m_nChannel) {
                m_pSoundMixer->m_lVoices.RemoveAt(currPos);
                delete pVoice;
            }
        }

        m_pSoundMixer->Unlock();
    }

    if (!ExclusivePlay(bReplay)) {
        m_pSoundMixer->Unlock();
        return FALSE;
    }

    m_pSoundMixer->Unlock();
    return TRUE;
}

// 0x7A9DB0
BOOL CSound::Play(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate, BOOL bReplay)
{
    if (m_pSoundMixer->m_bMixerInitialized) {
        return FALSE;
    }

    if (m_nArea == 0 || m_nArea != m_pSoundMixer->m_nActiveArea) {
        return FALSE;
    }

    m_nXCoordinate = nNewXCoordinate;
    m_nYCoordinate = nNewYCoordinate;
    m_nZCoordinate = nNewZCoordinate;

    if (m_nLooping != 0) {
        m_pSoundMixer->Lock();

        BOOL bFound = FALSE;

        POSITION pos = m_pSoundMixer->m_lLooping.GetHeadPosition();
        while (pos != NULL) {
            CSound* pSound = static_cast<CSound*>(m_pSoundMixer->m_lLooping.GetNext(pos));
            if (this == pSound) {
                bFound = TRUE;
            }
        }

        if (!bFound) {
            m_pSoundMixer->m_lLooping.AddHead(this);
        }

        m_pSoundMixer->Unlock();
    }

    if (m_pSoundMixer->m_nXCoordinate < 0) {
        m_nRangeVolume = 0;
        return TRUE;
    }

    int nXMin = m_nXCoordinate - m_nRange;
    int nYMin = m_nYCoordinate - m_nRange;

    if (nXMin < 0) {
        nXMin = 0;
    }

    if (nYMin < 0) {
        nYMin = 0;
    }

    if (m_nXCoordinate < nXMin
        || m_nXCoordinate > m_nXCoordinate + m_nRange
        || m_nYCoordinate < nYMin
        || m_nYCoordinate > m_nYCoordinate + m_nRange) {
        m_nRangeVolume = 0;
        return TRUE;
    }

    int dx = m_nXCoordinate - m_pSoundMixer->m_nXCoordinate;
    int dy = m_nYCoordinate - m_pSoundMixer->m_nYCoordinate;
    int distance = dx * dx + dy * dy;
    if (distance >= m_nRange * m_nRange) {
        m_nRangeVolume = 0;
        return TRUE;
    }

    m_nRangeVolume = 100 * (m_nRange * m_nRange - distance) / (m_nRange * m_nRange);
    m_nPan = 100 * dx / m_pSoundMixer->m_nPanRange;

    if (pSoundBuffer != NULL) {
        IDirectSoundBuffer_SetPan(pSoundBuffer, 50 * m_nPan);
    }

    m_pSoundMixer->Lock();

    CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_pSoundMixer->m_aChannels[m_nChannel]);
    if (pSoundChannel->m_nType == 1) {
        if (!bReplay) {
            if (pSoundChannel->m_lQueue.GetHeadPosition() != NULL) {
                pSoundChannel->m_lQueue.AddTail(this);
                m_pSoundMixer->UpdateQueue();
                m_pSoundMixer->Unlock();
                return TRUE;
            }

            pSoundChannel->m_lQueue.AddTail(this);
        }
    } else if (pSoundChannel->m_nType == 2) {
        m_pSoundMixer->Lock();

        BOOL bPlaying = FALSE;

        POSITION pos = m_pSoundMixer->m_lVoices.GetHeadPosition();
        while (pos != NULL) {
            CVoice* pVoice = static_cast<CVoice*>(m_pSoundMixer->m_lVoices.GetNext(pos));
            if (pVoice != NULL) {
                if (!pVoice->GetLooping()) {
                    if (pVoice->IsSoundPlaying()) {
                        bPlaying = TRUE;
                        break;
                    }
                }
            }
        }

        m_pSoundMixer->Unlock();

        if (bPlaying) {
            m_pSoundMixer->Unlock();
            return TRUE;
        }
    } else if (pSoundChannel->m_nType == 3) {
        m_pSoundMixer->Lock();

        POSITION pos = m_pSoundMixer->m_lVoices.GetHeadPosition();
        while (pos != NULL) {
            POSITION currPos = pos;
            CVoice* pVoice = static_cast<CVoice*>(m_pSoundMixer->m_lVoices.GetNext(pos));
            if (pVoice->GetChannel() == m_nChannel) {
                m_pSoundMixer->m_lVoices.RemoveAt(currPos);
                delete pVoice;
            }
        }

        m_pSoundMixer->Unlock();
    }

    if (!ExclusivePlay(bReplay)) {
        m_pSoundMixer->Unlock();
        return FALSE;
    }

    m_pSoundMixer->Unlock();
    return TRUE;
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
                soundBuffer3D->SetPosition(static_cast<D3DVALUE>(m_nXCoordinate),
                    static_cast<D3DVALUE>(m_nYCoordinate),
                    static_cast<D3DVALUE>(m_nZCoordinate),
                    DS3D_IMMEDIATE);
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

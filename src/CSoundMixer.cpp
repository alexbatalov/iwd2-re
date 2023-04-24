#include "CSoundMixer.h"

#include <cmath>

#include "CChitin.h"
#include "CSound.h"
#include "CSoundChannel.h"
#include "CUtil.h"
#include "CVoice.h"

static void MusicDebugFunc(CHAR* a1);
static BOOL MusicCompressQuery(CHAR* a1);

// 0x9039D8
BYTE CSoundMixer::m_tSqrtTable[10000];

// 0x7AAD80
CSoundMixer::CSoundMixer()
{
    m_bInLoopingUpdate = FALSE;
    m_bInPositionUpdate = FALSE;
    m_bInReleaseAll = FALSE;
    field_50 = 0;
    field_C4 = 0;
    field_C8 = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    m_nMaxChannels = 0;
    field_DC = 0;
    m_nPanRange = 0;
    m_nXCoordinate = 0;
    m_nYCoordinate = 0;
    m_nZCoordinate = 0;
    field_F0 = 0;
    field_F4 = 0;
    field_F8 = 0;
    field_FC = 0;
    field_178 = 0;
    field_C0 |= 0x03;
    m_bMixerInitialized = FALSE;
    field_40 = 0;
    m_dwEAXProperties = 0;
    m_cSoundProperties.m_nPreset = 0;
    m_pDirectSound3DListener = NULL;
    m_pPrimarySoundBuffer = NULL;
    m_bMusicInitialized = FALSE;
    m_sMusicPath = ".\\music";
    m_nNumSongs = 0;
    field_11C = -1;
    field_124 = -1;
    m_aMusicSlots.SetSize(10);

    // NOTE: Generated assembly is different.
    for (int i = 0; i < 10000; i++) {
        m_tSqrtTable[i] = static_cast<BYTE>(sqrt(static_cast<double>(i)));
    }

    // FIXME: Initialize to prevent crash in `ReleaseAll`.
    m_pDirectSound = NULL;

    ReleaseAll();

    m_bMixerInitialized = FALSE;
    field_40 = 0;
    field_0 = 0;
}

// #binary-identical
// 0x7AAF50
CSoundMixer::~CSoundMixer()
{
    Lock();

    CleanUp();

    m_aMusicSlots.SetSize(0);

    Unlock();
}

// 0x7AB060
void CSoundMixer::AddSound(CSound* pSoundPtr)
{
    if (m_bMixerInitialized) {
        Lock();

        CVoice* pVoice = new CVoice();

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
        // __LINE__: 2763
        UTIL_ASSERT_MSG(pVoice != NULL, "Crash in AddSound");

        pVoice->SetSound(pSoundPtr);
        m_lVoices.AddHead(pVoice);

        Unlock();
    }
}

// 0x7AB130
void CSoundMixer::TransferBuffer(CSound* pSoundPtr)
{
    Lock();

    POSITION pos = m_lVoices.GetHeadPosition();
    while (pos != NULL) {
        CVoice* pVoice = static_cast<CVoice*>(m_lVoices.GetAt(pos));
        if (pVoice->m_pSound == pSoundPtr) {
            pVoice->m_pSound = NULL;

            // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
            // __LINE__: 2816
            UTIL_ASSERT_MSG(pSoundPtr->GetBuffer() != NULL, "Crash in TransferBuffer");

            pVoice->m_pSoundBuffer = pSoundPtr->GetBuffer();

            break;
        }

        m_lVoices.GetNext(pos);
    }

    Unlock();
}

// 0x7AB1E0
void CSoundMixer::CleanUp()
{
    Lock();

    if (m_aChannels.GetSize() > 0) {
        for (int k = 0; k < m_nMaxChannels; k++) {
            CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels.GetAt(k));
            if (pSoundChannel != NULL) {
                delete pSoundChannel;
            }
        }

        m_nMaxChannels = -1;
        m_aChannels.SetSize(0);
    }

    if (m_bMusicInitialized) {
        // TODO: Incomplete.
        // musicClose();
        // soundClose();
    }

    m_bMusicInitialized = FALSE;
    m_nNumSongs = 0;

    ReleaseAll();

    m_bMixerInitialized = FALSE;
    field_40 = 0;
    field_0 = 0;

    Unlock();
}

// NOTE: Inlined.
int CSoundMixer::GetChannelType(int nChannelNumber)
{
    int type = 0;

    Lock();

    if (nChannelNumber >= 0 && nChannelNumber <= m_nMaxChannels) {
        CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels.GetAt(nChannelNumber));
        type = pSoundChannel->m_nType;
    }

    Unlock();

    return type;
}

// 0x7AB2A0
int CSoundMixer::GetChannelVolume(int nChannelNumber)
{
    int volume = 0;

    Lock();

    if (nChannelNumber >= 0 && nChannelNumber <= m_nMaxChannels) {
        CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels.GetAt(nChannelNumber));
        volume = pSoundChannel->m_nVolume;
    }

    Unlock();

    return volume;
}

// 0x7AB310
void CSoundMixer::GetListenPosition(CPoint& pos, LONG& posZ)
{
    pos.x = m_nXCoordinate;
    pos.y = m_nYCoordinate;
    posZ = m_nZCoordinate;
}

// 0x7AB340
void CSoundMixer::Initialize(CWnd* pWnd, int nNewMaxVoices, int nNewMaxChannels)
{
    HRESULT hr;

    field_C4 = 1;
    field_C8 = 0;
    field_CC = 0;
    field_D0 = 0;
    m_nMaxChannels = -1;
    field_DC = nNewMaxVoices;
    m_nPanRange = 1;
    m_bInPositionUpdate = FALSE;
    m_bInReleaseAll = FALSE;
    field_50 = 0;
    field_0 = 0;
    field_F0 = 0;
    InitializeChannels(nNewMaxChannels);

    if (m_pDirectSound != NULL) {
        // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
        // __LINE__: 3276
        UTIL_ASSERT_MSG(FALSE, "Direct sound object not Released properly");
    }

    hr = DirectSoundCreate(NULL, &m_pDirectSound, NULL);
    if (hr != DS_OK) {
        m_bMixerInitialized = FALSE;
        return;
    }

    m_hWnd = (HWND)pWnd;

    hr = m_pDirectSound->SetCooperativeLevel(m_hWnd, DSSCL_EXCLUSIVE);
    if (hr == DSERR_INVALIDPARAM || hr == DSERR_ALLOCATED) {
        m_bMixerInitialized = 0;
        return;
    }

    if (hr != DS_OK) {
        m_bMixerInitialized = 0;
        return;
    }

    DSBUFFERDESC bufferDesc = { 0 };
    bufferDesc.dwSize = sizeof(bufferDesc);
    bufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

    hr = m_pDirectSound->CreateSoundBuffer(&bufferDesc, &m_pPrimarySoundBuffer, NULL);
    if (hr != DS_OK) {
        m_bMixerInitialized = 0;
        return;
    }

    WAVEFORMATEX waveFormat = { 0 };

    DSCAPS caps = { 0 };
    caps.dwSize = sizeof(caps);

    hr = m_pDirectSound->GetCaps(&caps);
    if (hr == DS_OK) {
        waveFormat.nSamplesPerSec = 22050;
        waveFormat.wFormatTag = 1;
        waveFormat.wBitsPerSample = (caps.dwSize & DSCAPS_PRIMARY16BIT) != 0 ? 16 : 8;
        waveFormat.cbSize = 0;
        waveFormat.nChannels = (caps.dwSize & DSCAPS_PRIMARYSTEREO) != 0 ? 2 : 1;
        waveFormat.nBlockAlign = waveFormat.wBitsPerSample * waveFormat.nChannels / 8;
        waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

        hr = m_pPrimarySoundBuffer->SetFormat(&waveFormat);
        if (hr != DS_OK) {
            m_bMixerInitialized = 0;
            return;
        }
    }

    // TODO: Incomplete.
    // if (soundInit(m_hWnd, m_pDirectSound, 16, 8192, 22050) == 0) {
    //     if (musicInit(MusicCompressQuery) == 0) {
    //         musicSetDebugFunc(MusicDebugFunc);
    //         m_bMusicInitialized = TRUE;
    //     }
    // }

    if (m_bMusicInitialized) {
        g_pChitin->OnMixerInitialize();
    }

    Lock();

    m_dwEAXProperties = m_cSoundProperties.Init(m_pDirectSound);
    m_cSoundProperties.SetEnvironmentPreset(m_cSoundProperties.m_nPreset);

    Unlock();

    if ((m_dwEAXProperties & CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT) != 0) {
        hr = m_pPrimarySoundBuffer->QueryInterface(IID_IDirectSound3DListener, reinterpret_cast<LPVOID*>(&m_pDirectSound3DListener));
        if (hr == DS_OK) {
            m_pDirectSound3DListener->SetOrientation(0.0, -1.0, 0.0, 0.0, 0.0, 1.0, 0);
        } else {
            m_dwEAXProperties = 0;
        }
    }

    if (field_178) {
        m_dwEAXProperties |= CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT;
    } else {
        if (field_144.sub_799C90()) {
            field_144.sub_7C25B0();
            field_178 = FALSE;
        } else {
            field_178 = TRUE;
            m_dwEAXProperties |= CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT;
        }
    }
}

// 0x7AB6B0
void CSoundMixer::InitializeChannels(int nNewMaxChannels)
{
    Lock();

    for (int k = 0; k <= m_nMaxChannels; k++) {
        CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels.GetAt(k));
        if (pSoundChannel != NULL) {
            delete pSoundChannel;
        }
    }

    m_aChannels.SetSize(0);

    m_nMaxChannels = nNewMaxChannels;

    for (int l = 0; l <= m_nMaxChannels; l++) {
        CSoundChannel* pSoundChannel = new CSoundChannel();
        m_aChannels.SetAtGrow(m_aChannels.GetSize(), pSoundChannel);
    }

    Unlock();
}

// #binary-identical
// 0x7AB7D0
BOOL CSoundMixer::ReleaseAll()
{
    if (m_bInReleaseAll || m_bInPositionUpdate) {
        return FALSE;
    }

    m_bInReleaseAll = TRUE;
    m_bInPositionUpdate = TRUE;

    Lock();

    if (m_pDirectSound3DListener != NULL) {
        m_pDirectSound3DListener->Release();
        m_pDirectSound3DListener = NULL;
    }

    Lock();

    m_cSoundProperties.Uninit();
    m_dwEAXProperties = 0;

    Unlock();

    while (!m_lVoices.IsEmpty()) {
        CVoice* pVoice = static_cast<CVoice*>(m_lVoices.RemoveHead());
        if (pVoice != NULL) {
            delete pVoice;
        }
    }

    while (!m_lWaiting.IsEmpty()) {
        CSound* sound = static_cast<CSound*>(m_lWaiting.RemoveHead());
        if (sound->pSoundBuffer != NULL) {
            sound->pSoundBuffer->Release();
            sound->pSoundBuffer = NULL;
        }
        // NOTE: Why sound itself is not deleted like the object above?
    }

    if (m_pDirectSound != NULL) {
        if (m_pPrimarySoundBuffer != NULL) {
            m_pPrimarySoundBuffer->Release();
            m_pPrimarySoundBuffer = NULL;
        }

        m_pDirectSound->Release();
        m_pDirectSound = NULL;
    }

    m_bInReleaseAll = FALSE;

    Unlock();

    return TRUE;
}

// 0x7AB930
void CSoundMixer::RemoveWaiting(CSound* pSoundPtr)
{
    Lock();

    m_lWaiting.RemoveAt(m_lWaiting.Find(pSoundPtr));

    Unlock();
}

// 0x7ABA90
void CSoundMixer::SetListenPosition(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate)
{
    Lock();

    m_nXCoordinate = nNewXCoordinate;
    m_nYCoordinate = nNewYCoordinate;
    m_nZCoordinate = nNewZCoordinate;

    if (m_pDirectSound3DListener != NULL) {
        m_pDirectSound3DListener->SetPosition(static_cast<D3DVALUE>(nNewXCoordinate),
            static_cast<D3DVALUE>(nNewYCoordinate),
            static_cast<D3DVALUE>(nNewZCoordinate),
            0);
    }

    UpdateSoundPositions();

    Unlock();
}

// 0x7ABB40
void CSoundMixer::SetPanRange(int nNewPanRange)
{
    Lock();

    m_nPanRange = nNewPanRange;

    Unlock();
}

// 0x7ABBA0
void CSoundMixer::UpdateSoundList()
{
    // TODO: Incomplete.
}

// 0x7AC030
void CSoundMixer::UpdateSoundPositions()
{
    if ((field_C0 & 1) != 0) {
        if (!m_bInPositionUpdate) {
            m_bInPositionUpdate = TRUE;
            Lock();

            POSITION pos = m_lLooping.GetHeadPosition();
            while (pos != NULL) {
                CSound* pSound = static_cast<CSound*>(m_lLooping.GetNext(pos));
                if (pSound != NULL) {
                    pSound->ResetVolume();
                }
            }

            POSITION voicesPos = m_lVoices.GetHeadPosition();
            while (voicesPos != NULL) {
                CVoice* pVoice = static_cast<CVoice*>(m_lVoices.GetNext(voicesPos));
                if (pVoice != NULL) {
                    if (!pVoice->GetLooping()) {
                        if (pVoice->IsSoundPlaying()) {
                            pVoice->ResetVolume();
                        }
                    }
                }
            }

            Unlock();
            m_bInPositionUpdate = FALSE;
        }
    }
}

// 0x7AC230
void CSoundMixer::SetMusicPath(CString& sNewMusicPath)
{
    if (m_bMusicInitialized) {
        Lock();

        // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
        // __LINE__: 5010
        UTIL_ASSERT(m_nNumSongs == 0);

        m_sMusicPath = sNewMusicPath;

        int length = m_sMusicPath.GetLength();
        if (m_sMusicPath[length - 1] == '/' || m_sMusicPath[length - 1] == '\\') {
            m_sMusicPath = m_sMusicPath.Left(length - 1);
        }

        Unlock();
    }
}

// 0x7AC480
void CSoundMixer::SetMusicVolume(int nNewVolume)
{
    Lock();

    // TODO: Incomplete.
    // musicSetVolume(0x7FFF * nNewVolume / 100);

    Unlock();
}

// #guess
// 0x7AC970
void CSoundMixer::Lock()
{
    if (g_pChitin != NULL) {
        if (g_pChitin->m_bExitMusicThread != TRUE) {
            EnterCriticalSection(&(g_pChitin->field_394));
        }
    }
}

// #guess
// 0x7AC990
void CSoundMixer::Unlock()
{
    if (g_pChitin != NULL) {
        if (g_pChitin->m_bExitMusicThread != TRUE) {
            LeaveCriticalSection(&(g_pChitin->field_394));
        }
    }
}

// 0x7AC9B0
void CSoundMixer::UpdateMusic()
{
    if ((field_C0 & 2) != 0) {
        if (m_bMusicInitialized) {
            Lock();

            // TODO: Incomplete.
            // soundUpdate();

            Unlock();
        }
    }
}

// NOTE: Inlined in `CInfGame::ApplyVolumeSliders` and probably other places.
void CSoundMixer::SetChannelVolume(int nChannelNumber, int nNewVolume)
{
    CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels[nChannelNumber]);
    pSoundChannel->SetVolume(nNewVolume);
}

// NOTE: Inlined in `CSound::Create2DBuffer` - returns volume without locking
// seen in `CSoundMixer::GetChannelVolume`.
int CSoundMixer::GetChannelVolumeFast(int nChannelNumber)
{
    CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels[nChannelNumber]);
    return pSoundChannel->m_nVolume;
}

// NOTE: Inlined in many places.
BOOL CSoundMixer::IsSoundWaiting(CSound* pSound)
{
    BOOL isWaiting = FALSE;

    if (pSound != NULL && pSound->GetResRef() != "") {
        Lock();

        if (m_lWaiting.Find(pSound) != NULL) {
            isWaiting = TRUE;
        }

        Unlock();
    }

    return isWaiting;
}

// NOTE: Inlined in many places.
void CSoundMixer::RemoveFromLoopingList(CSound* pSound)
{
    Lock();

    m_bInLoopingUpdate = TRUE;
    POSITION pos = m_lLooping.Find(pSound);
    if (pos != NULL) {
        m_lLooping.RemoveAt(pos);
        m_bInLoopingUpdate = FALSE;
    }

    Unlock();
}

// 0x7ACA40
static void MusicDebugFunc(CHAR* a1)
{
}

// 0x7ACA50
static BOOL MusicCompressQuery(CHAR* a1)
{
    return TRUE;
}

#include "CSoundMixer.h"

#include <cmath>

#include "CChitin.h"
#include "CSound.h"
#include "CSoundChannel.h"
#include "CUtil.h"
#include "CVoice.h"
#include "music/music.h"
#include "music/sound.h"

static void MusicDebug(char* string);
static int MusicCompressQuery(char* name);

// 0x9039D8
BYTE CSoundMixer::m_tSqrtTable[10001];

// 0x7AAD80
CSoundMixer::CSoundMixer()
{
    m_bInLoopingUpdate = FALSE;
    m_bInPositionUpdate = FALSE;
    m_bInReleaseAll = FALSE;
    m_bInQueueUpdate = FALSE;
    field_C4 = 0;
    field_C8 = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    m_nMaxChannels = 0;
    m_nMaxVoices = 0;
    m_nPanRange = 0;
    m_nXCoordinate = 0;
    m_nYCoordinate = 0;
    m_nZCoordinate = 0;
    m_nActiveArea = 0;
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
    m_nCurrentSong = -1;
    m_nLastSong = -1;
    m_aMusicSlots.SetSize(10);

    // NOTE: Generated assembly is different.
    for (int i = 0; i < 10001; i++) {
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
        for (int k = 0; k <= m_nMaxChannels; k++) {
            CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels.GetAt(k));
            if (pSoundChannel != NULL) {
                delete pSoundChannel;
            }
        }

        m_nMaxChannels = -1;
        m_aChannels.SetSize(0);
    }

    if (m_bMusicInitialized) {
        musicClose();
        soundClose();
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

// NOTE: Window pointer can probably be upgraded to reference since it cannot be
// null and should have attached HWND which is never validated.
//
// 0x7AB340
void CSoundMixer::Initialize(CWnd* pWnd, int nNewMaxVoices, int nNewMaxChannels)
{
    HRESULT hr;

    field_C4 = 1;
    field_C8 = 0;
    field_CC = 0;
    field_D0 = 0;
    m_nMaxChannels = -1;
    m_nMaxVoices = nNewMaxVoices;
    m_nPanRange = 1;
    m_bInPositionUpdate = FALSE;
    m_bInReleaseAll = FALSE;
    m_bInQueueUpdate = FALSE;
    field_0 = 0;
    m_nActiveArea = 0;
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

    m_hWnd = pWnd->m_hWnd;

    hr = m_pDirectSound->SetCooperativeLevel(m_hWnd, DSSCL_EXCLUSIVE);
    if (hr == DSERR_INVALIDPARAM || hr == DSERR_ALLOCATED) {
        m_bMixerInitialized = FALSE;
        return;
    }

    if (hr != DS_OK) {
        m_bMixerInitialized = FALSE;
        return;
    }

    m_bMixerInitialized = TRUE;

    DSBUFFERDESC bufferDesc = { 0 };
    bufferDesc.dwSize = sizeof(bufferDesc);
    bufferDesc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

    hr = m_pDirectSound->CreateSoundBuffer(&bufferDesc, &m_pPrimarySoundBuffer, NULL);
    if (hr != DS_OK) {
        m_bMixerInitialized = FALSE;
        return;
    }

    WAVEFORMATEX waveFormat = { 0 };

    DSCAPS caps = { 0 };
    caps.dwSize = sizeof(caps);

    hr = m_pDirectSound->GetCaps(&caps);
    if (hr == DS_OK) {
        waveFormat.nSamplesPerSec = 22050;
        waveFormat.wFormatTag = WAVE_FORMAT_PCM;
        waveFormat.wBitsPerSample = (caps.dwFlags & DSCAPS_PRIMARY16BIT) != 0 ? 16 : 8;
        waveFormat.cbSize = 0;
        waveFormat.nChannels = (caps.dwFlags & DSCAPS_PRIMARYSTEREO) != 0 ? 2 : 1;
        waveFormat.nBlockAlign = waveFormat.wBitsPerSample * waveFormat.nChannels / 8;
        waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;

        hr = m_pPrimarySoundBuffer->SetFormat(&waveFormat);
        if (hr != DS_OK) {
            m_bMixerInitialized = FALSE;
            return;
        }
    }

    if (soundInit(m_hWnd, m_pDirectSound, 16, 0x2000, 22050) == SOUND_NO_ERROR) {
        if (musicInit(MusicCompressQuery) == 0) {
            musicSetDebugFunc(MusicDebug);
            m_bMusicInitialized = TRUE;
        }
    }

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

// 0x7AB990
void CSoundMixer::SetChannelVolume(int nChannelNumber, int nNewVolume)
{
    Lock();

    if (nChannelNumber >= 0 && nChannelNumber <= m_nMaxChannels) {
        if (nNewVolume < 0) {
            nNewVolume = 0;
        } else if (nNewVolume > 100) {
            nNewVolume = 100;
        }

        CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels[nChannelNumber]);
        pSoundChannel->SetVolume(nNewVolume);

        POSITION pos = m_lVoices.GetHeadPosition();
        while (pos != NULL) {
            CVoice* pVoice = static_cast<CVoice*>(m_lVoices.GetNext(pos));
            if (pVoice->GetChannel() == nChannelNumber) {
                pVoice->ResetVolume();
            }
        }
    }

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
            DS3D_IMMEDIATE);
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
    if ((field_C0 & 0x1) != 0) {
        if (!m_bInReleaseAll) {
            m_bInReleaseAll = TRUE;
            Lock();

            if (!m_bInPositionUpdate) {
                POSITION voicePos = m_lVoices.GetHeadPosition();
                while (voicePos != NULL) {
                    POSITION pos = voicePos;
                    CVoice* pVoice = static_cast<CVoice*>(m_lVoices.GetNext(voicePos));
                    if (pVoice->IsSoundPlaying()) {
                        if (m_nActiveArea != 0
                            && pVoice->m_pSound != NULL
                            && pVoice->m_pSound->m_nArea != 0
                            && pVoice->m_pSound->m_nArea != m_nActiveArea
                            && m_nActiveArea != -1) {
                            if (pVoice->m_pSound->m_nLooping != 0) {
                                m_lWaiting.AddHead(pVoice->m_pSound);
                            }

                            if (m_lVoices.Find(pVoice) != NULL) {
                                m_lVoices.RemoveAt(pos);
                                delete pVoice;
                            }
                        }
                    } else {
                        if (m_lVoices.Find(pVoice) != NULL) {
                            m_lVoices.RemoveAt(pos);
                            delete pVoice;
                        }
                    }
                }

                while (m_lVoices.GetCount() > m_nMaxVoices) {
                    CVoice* pVoice = static_cast<CVoice*>(m_lVoices.RemoveHead());
                    if (pVoice->GetLooping()) {
                        m_lWaiting.AddHead(pVoice->m_pSound);
                    }

                    delete pVoice;
                }

                POSITION loopingPos = m_lLooping.GetHeadPosition();
                while (loopingPos != NULL) {
                    CSound* pSound = static_cast<CSound*>(m_lLooping.GetNext(loopingPos));
                    if (m_nActiveArea == 0
                        || pSound->m_nArea == 0
                        || m_nActiveArea == pSound->m_nArea) {
                        pSound->ResetVolume();
                    }
                }
            }

            POSITION waitingPos = m_lWaiting.GetHeadPosition();
            while (m_lVoices.GetCount() < m_nMaxVoices && waitingPos != NULL) {
                POSITION pos = waitingPos;
                CSound* pSound = static_cast<CSound*>(m_lWaiting.GetNext(waitingPos));
                if (m_nActiveArea != 0
                    && pSound->m_nArea != 0
                    && m_nActiveArea != pSound->m_nArea) {
                    if (!pSound->GetLooping()) {
                        m_lWaiting.RemoveAt(pos);

                        if (pSound->pSoundBuffer != NULL) {
                            pSound->pSoundBuffer->Release();
                            pSound->pSoundBuffer = NULL;
                        }
                    }
                } else {
                    if (pSound->m_bPositionedSound) {
                        pSound->Play(pSound->m_nXCoordinate, pSound->m_nYCoordinate, pSound->m_nZCoordinate, FALSE);
                    } else {
                        pSound->Play(FALSE);
                    }
                }
            }

            Unlock();
            m_bInReleaseAll = FALSE;
        }
    }
}

// 0x7ABE30
BOOL CSoundMixer::UpdateSoundList(INT nPriority)
{
    if ((field_C0 & 0x1) == 0) {
        return FALSE;
    }

    CVoice* v1 = NULL;
    BOOL v2 = TRUE;

    if (!m_bInReleaseAll) {
        m_bInReleaseAll = TRUE;
    }

    Lock();

    POSITION voicePos = m_lVoices.GetHeadPosition();
    while (voicePos != NULL) {
        POSITION pos = voicePos;
        CVoice* pVoice = static_cast<CVoice*>(m_lVoices.GetNext(voicePos));
        if (pVoice->IsSoundPlaying()) {
            if (m_nActiveArea && 0
                && pVoice->m_pSound && NULL
                && pVoice->m_pSound->m_nArea && 0
                && pVoice->m_pSound->m_nArea && m_nActiveArea
                && m_nActiveArea && -1) {
                if (pVoice->m_pSound->m_nLooping != 0) {
                    m_lWaiting.AddHead(pVoice->m_pSound);
                }

                if (m_lVoices.Find(pVoice) != NULL) {
                    m_lVoices.RemoveAt(pos);
                    delete pVoice;
                }
            } else {
                if (pVoice->GetPriority() < nPriority) {
                    nPriority = pVoice->GetPriority();
                    v1 = pVoice;
                }
            }
        } else {
            if (m_lVoices.Find(pVoice) != NULL) {
                m_lVoices.RemoveAt(pos);
                delete pVoice;
            }
        }
    }

    if (m_lVoices.GetCount() >= m_nMaxVoices) {
        if (v1 != NULL) {
            if (v1->m_pSound != NULL && v1->m_pSound->m_nLooping != 0) {
                m_lWaiting.AddHead(v1->m_pSound);
            }

            m_lVoices.RemoveAt(m_lVoices.Find(v1));
            delete v1;
        } else {
            m_bInReleaseAll = FALSE;
            v2 = FALSE;
        }
    }

    Unlock();
    m_bInReleaseAll = FALSE;

    return v2;
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

// 0x7AC150
void CSoundMixer::UpdateQueue()
{
    if ((field_C0 & 1) != 0) {
        if (!m_bInQueueUpdate) {
            m_bInQueueUpdate = TRUE;
            Lock();

            for (int nChannel = 0; nChannel < m_nMaxChannels; nChannel++) {
                CSoundChannel* pSoundChannel = static_cast<CSoundChannel*>(m_aChannels[nChannel]);
                if (pSoundChannel->m_nType == 1) {
                    if (!pSoundChannel->m_lQueue.IsEmpty()) {
                        CSound* pSound = static_cast<CSound*>(pSoundChannel->m_lQueue.GetHead());
                        if (!pSound->IsSoundPlaying()) {
                            pSoundChannel->m_lQueue.RemoveHead();

                            if (!pSoundChannel->m_lQueue.IsEmpty()) {
                                CSound* pNextSound = static_cast<CSound*>(pSoundChannel->m_lQueue.GetHead());
                                pNextSound->ExclusivePlay(FALSE);
                            }
                        }
                    }
                }
            }

            Unlock();
            m_bInQueueUpdate = FALSE;
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

// 0x7AC320
BOOL CSoundMixer::SetMusicSongs(INT nNumSongs, CHAR** ppSongFiles)
{
    if (!m_bMusicInitialized) {
        return 0;
    }

    Lock();

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
    // __LINE__: 5068
    UTIL_ASSERT(m_nNumSongs == 0);

    // __FILE__: C:\Projects\Icewind2\src\chitin\ChSound.cpp
    // __LINE__: 5069
    UTIL_ASSERT(0 < nNumSongs && nNumSongs <= CSOUNDMIXER_MAX_SONGS);

    musicSetPath(m_sMusicPath.GetBuffer(), "acm");
    m_sMusicPath.ReleaseBuffer();

    char buffer[MAX_PATH * CSOUNDMIXER_MAX_SONGS];
    char* paths[CSOUNDMIXER_MAX_SONGS];

    for (INT nIndex = 0; nIndex < nNumSongs; nIndex++) {
        paths[nIndex] = &(buffer[nIndex * MAX_PATH]);
        sprintf(paths[nIndex],
            "%s\\%s",
            (LPCSTR)m_sMusicPath,
            ppSongFiles[nIndex]);
    }

    musicLoadSongList(paths, nNumSongs);
    m_nNumSongs = nNumSongs;

    Unlock();
    return TRUE;
}

// 0x7AC480
void CSoundMixer::SetMusicVolume(int nNewVolume)
{
    Lock();

    musicSetVolume(VOLUME_MAX * nNewVolume / 100);

    Unlock();
}

// 0x7AC4F0
void CSoundMixer::StartSong(INT nSong, DWORD dwFlags)
{
    StartSong(nSong, 0, -1, dwFlags);
}

// 0x7AC510
void CSoundMixer::StartSong(INT nSong, INT nSection, INT nPosition, DWORD dwFlags)
{
    if ((field_C0 & 0x2) != 0) {
        BOOL bFadeIn = TRUE;

        if (m_bMusicInitialized) {
            Lock();

            if (nSection < 0) {
                nSection = 0;
                nPosition = -1;
            }

            if (m_nCurrentSong != nSong) {
                if (nSong == -1 || nSong == 0) {
                    switch (dwFlags) {
                    case 0:
                        bFadeIn = FALSE;
                        musicFade(-1, nSection, nPosition, 1500);
                        break;
                    case 1:
                        // NOTE: Uninline.
                        StopMusic(TRUE);
                        break;
                    case 3:
                        musicFade(-1, nSection, nPosition, 1500);
                        break;
                    case 4:
                    case 6:
                        musicFade(-1, nSection, nPosition, 15000);
                        break;
                    case 5:
                        musicFade(-1, nSection, nPosition, 500);
                        break;
                    case 7:
                        musicFade(-1, nSection, nPosition, 10);
                        break;
                    default:
                        if ((dwFlags & 0x10000) != 0) {
                            musicFade(-1, nSection, nPosition, dwFlags & 0xFFFF);
                        } else {
                            // NOTE: Uninline.
                            StopMusic(TRUE);
                        }
                        break;
                    }

                    m_nCurrentSong = -1;
                    m_nLastSong = -1;
                } else {
                    switch (dwFlags) {
                    case 0:
                        bFadeIn = FALSE;
                        musicFade(nSong, nSection, nPosition, 1500);
                        break;
                    case 1:
                        musicForceSection(nSong, nSection, nPosition);
                        break;
                    case 2:
                        musicSetSong(nSong, nSection, nPosition);
                        break;
                    case 3:
                        musicFade(nSong, nSection, nPosition, 1500);
                        break;
                    case 4:
                    case 6:
                        musicFade(nSong, nSection, nPosition, 15000);
                        break;
                    case 5:
                        musicFade(nSong, nSection, nPosition, 200);
                        break;
                    case 7:
                        musicFade(nSong, nSection, nPosition, 10);
                        break;
                    default:
                        if ((dwFlags & 0x10000) != 0) {
                            musicFade(nSong, nSection, nPosition, dwFlags & 0xFFFF);
                        }
                        break;
                    }

                    m_nCurrentSong = nSong;
                    m_nLastSong = nSong;
                }
            }

            if (nSong >= 0 && nPosition >= 0 && bFadeIn) {
                musicFadeIn(5000);
            }

            Unlock();
        }
    }
}

// 0x7AC8E0
void CSoundMixer::StopMusic(BOOL bForce)
{
    if (m_bMusicInitialized) {
        Lock();

        if (m_nCurrentSong != -1) {
            if (bForce) {
                musicForceStop();
            } else {
                musicStop();
            }

            m_nLastSong = m_nCurrentSong;
            m_nCurrentSong = -1;
        }

        Unlock();
    }
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

            soundUpdate();

            Unlock();
        }
    }
}

// 0x7AC840
int CSoundMixer::GetSectionPlaying()
{
    Lock();

    int section = musicGetSectionPlaying();

    Unlock();

    return section;
}

// 0x7AC890
int CSoundMixer::GetMusicPosition()
{
    Lock();

    int position = musicGetPosition();

    Unlock();

    return position;
}

// 0x7ACA10
BOOL CSoundMixer::sub_7ACA10()
{
    return musicGetSong() < 0;
}

// 0x7ACA20
int CSoundMixer::GetSongPlaying()
{
    return musicGetSongPlaying();
}

// 0x7ACA30
int CSoundMixer::sub_7ACA30()
{
    return (field_C0 << 30) >> 31;
}

// NOTE: Inlined in `CInfGame::ApplyVolumeSliders` and probably other places.
void CSoundMixer::SetChannelVolumeFast(int nChannelNumber, int nNewVolume)
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

// NOTE: Originally named `MusicDebugFunc` which clashes with eponymous typedef.
//
// 0x7ACA40
static void MusicDebug(char* string)
{
}

// 0x7ACA50
static int MusicCompressQuery(char* name)
{
    return 1;
}

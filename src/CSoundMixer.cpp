#include "CSoundMixer.h"

#include <cmath>

#include "CChitin.h"
#include "CSound.h"
#include "CSoundChannel.h"
#include "CUtil.h"
#include "CVoice.h"

// 0x9039D8
BYTE CSoundMixer::m_tSqrtTable[10000];

// 0x7AAD80
CSoundMixer::CSoundMixer()
{
    field_44 = 0;
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
    field_3C = 0;
    field_40 = 0;
    field_140 = 0;
    m_cSoundProperties.field_10 = 0;
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

    ReleaseAll();

    field_3C = 0;
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
    if (field_3C) {
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
            // TODO: Object type?
            CObject* v1 = m_aChannels.GetAt(k);
            if (v1 != NULL) {
                delete v1;
            }
        }

        m_nMaxChannels = -1;
        m_aChannels.SetSize(0);
    }

    m_bMusicInitialized = FALSE;
    m_nNumSongs = 0;

    ReleaseAll();

    field_3C = 0;
    field_40 = 0;
    field_0 = 0;

    Unlock();
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
BOOL CSoundMixer::Initialize(CWnd* pWnd, int nNewMaxVoices, int nNewMaxChannels)
{
    // TODO: Incomplete.

    return FALSE;
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
    field_140 = 0;

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
        if (g_pChitin->field_390 != 1) {
            EnterCriticalSection(&(g_pChitin->field_394));
        }
    }
}

// #guess
// 0x7AC990
void CSoundMixer::Unlock()
{
    if (g_pChitin != NULL) {
        if (g_pChitin->field_390 != 1) {
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

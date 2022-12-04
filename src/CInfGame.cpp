#include "CInfGame.h"

#include <process.h>

#include "CBaldurChitin.h"
#include "CSearchBitmap.h"

// 0x59CC30
CInfGame::CInfGame()
{
    // TODO: Incomplete.
}

// 0x59ECB0
CInfGame::~CInfGame()
{
    // TODO: Incomplete.
}

// 0x59F500
void CInfGame::StartSearchThread()
{
    if (_beginthread(SearchThreadMain, 0, NULL) == -1) {
        CloseHandle(m_hSearchThread);
        m_hSearchThread = NULL;
    }
}

// 0x5C0EA0
void CInfGame::ApplyVolumeSliders(BOOLEAN a2)
{
    g_pBaldurChitin->cSoundMixer.SetMusicVolume(m_cOptions.m_nVolumeMusic);

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(0, m_cOptions.m_nVolumeVoices);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(1, m_cOptions.m_nVolumeAmbients);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(3, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(4, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(5, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(2, m_cOptions.m_nVolumeVoices);

    for (int k = 7; k < 13; k++) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(k, m_cOptions.m_nVolumeVoices);
    }

    g_pBaldurChitin->cSoundMixer.SetChannelVolume(13, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(14, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(15, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(20, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(18, m_cOptions.m_nVolumeSFX);
    g_pBaldurChitin->cSoundMixer.SetChannelVolume(19, m_cOptions.m_nVolumeSFX);

    if (a2 == TRUE) {
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(16, m_cOptions.m_nVolumeAmbients);
        g_pBaldurChitin->cSoundMixer.SetChannelVolume(17, m_cOptions.m_nVolumeAmbients);
    }

    g_pBaldurChitin->cSoundMixer.UpdateSoundList();
}

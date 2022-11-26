#include "CSoundChannel.h"

// NOTE: Inlined in `CSoundMixer::InitializeChannels`.
CSoundChannel::CSoundChannel()
{
    m_nVolumeInit = 100;
    m_nVolume = 100;
    m_nType = 0;
}

// #binary-identical
// 0x7AACA0
CSoundChannel::~CSoundChannel()
{
    POSITION pos = m_lQueue.GetHeadPosition();
    POSITION next = pos;
    while (pos != NULL) {
        m_lQueue.GetNext(next);
        m_lQueue.RemoveAt(pos);
        pos = next;
    }
}

// #binary-identical
// 0x7AAD10
void CSoundChannel::SetType(int nNewChannelType)
{
    if (nNewChannelType == 0 || nNewChannelType == 1 || nNewChannelType == 2 || nNewChannelType == 3) {
        m_nType = nNewChannelType;
    }
}

// #binary-identical
// 0x7AAD30
void CSoundChannel::SetVolume(int nNewChannelVolume)
{
    if (nNewChannelVolume >= 0 && nNewChannelVolume <= 100) {
        m_nVolume = m_nVolumeInit * nNewChannelVolume / 100;
    }
}

// #binary-identical
// 0x7AAD60
void CSoundChannel::SetVolumeInit(int nNewChannelVolume)
{
    if (nNewChannelVolume >= 0 && nNewChannelVolume <= 100) {
        m_nVolumeInit = nNewChannelVolume;
    }
}

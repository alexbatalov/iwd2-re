#ifndef CSOUNDCHANNEL_H_
#define CSOUNDCHANNEL_H_

#include <afxwin.h>

// #memory-identical
class CSoundChannel : public CObject {
public:
    CSoundChannel();
    ~CSoundChannel();

    void SetType(int nNewChannelType);
    void SetVolume(int nNewChannelVolume);
    void SetVolumeInit(int nNewChannelVolume);

    /* 0004 */ int m_nType;
    /* 0008 */ int m_nVolume;
    /* 000C */ int m_nVolumeInit;
    /* 0010 */ CObList m_lQueue;
};

#endif /* CSOUNDCHANNEL_H_ */

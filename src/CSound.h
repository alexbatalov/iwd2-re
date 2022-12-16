#ifndef CSOUND_H_
#define CSOUND_H_

#include <afx.h>

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

class CSound : public CObject {
public:
    void ResetVolume();

    BOOL IsPlaying();
    DWORD GetStatus();

    BOOL GetLooping() { return m_nLooping; }
    IDirectSoundBuffer* GetBuffer() { return pSoundBuffer; }

    /* 0040 */ int m_nChannel; // #guess
    /* 0044 */ int m_nPriority; // #guess
    /* 0048 */ int m_nLooping; // #guess
    /* 0058 */ IDirectSoundBuffer* pSoundBuffer; // #guess
};

#endif /* CSOUND_H_ */

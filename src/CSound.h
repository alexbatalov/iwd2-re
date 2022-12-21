#ifndef CSOUND_H_
#define CSOUND_H_

#include "mfc.h"

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

#include "CResRef.h"
#include "CResWave.h"

class CSound : public CObject, public CResHelper<CResWave, 4> {
public:
    CSound();
    CSound(CResRef cResRef, int nRange, int nChannel, int nLooping, int nPriority, BOOL bPositionedSound);
    BOOL SetFireForget(BOOL bNewFireForget);
    void ResetVolume();
    BOOL SetChannel(int nNewChannel, DWORD nArea);

    BOOL IsPlaying();
    BOOL Play(BOOL bReplay);
    DWORD GetStatus();
    void SetRange(int nNewRange);

    BOOL GetLooping() { return m_nLooping; }
    IDirectSoundBuffer* GetBuffer() { return pSoundBuffer; }

    static CSoundMixer* m_pSoundMixer;

    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ int m_nRange; // #guess
    /* 0024 */ int field_24;
    /* 0028 */ int field_28;
    /* 002C */ int field_2C;
    /* 0030 */ int field_30;
    /* 0034 */ int field_34;
    /* 0038 */ int m_nVolume;
    /* 003C */ int field_3C;
    /* 0040 */ int m_nChannel; // #guess
    /* 0044 */ int m_nPriority; // #guess
    /* 0048 */ int m_nLooping; // #guess
    /* 004C */ int field_4C;
    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ IDirectSoundBuffer* pSoundBuffer; // #guess
    /* 005C */ int field_5C;
    /* 0060 */ int m_nArea;
};

#endif /* CSOUND_H_ */

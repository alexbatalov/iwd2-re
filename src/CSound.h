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
    ~CSound();
    BOOL SetFireForget(BOOL bNewFireForget);
    BOOL CopyData();
    BOOL Create2DBuffer(LPWAVEFORMATEX waveFormat);
    BOOL Create3DBuffer(LPWAVEFORMATEX waveFormat, float mix);
    void DestroyBuffer(LPDIRECTSOUNDBUFFER* soundBufferPtr);
    BOOL ExclusiveStop();
    DWORD GetPlayTime();
    void ResetVolume();
    BOOL SetChannel(int nNewChannel, uintptr_t nArea);

    BOOL IsSoundPlaying();
    BOOL Play(BOOL bReplay);
    BOOL Play(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate, BOOL bReplay);
    DWORD GetStatus();
    int GetVolume();
    void SetCoordinates(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate);
    BOOL SetLoopingFlag(int nNewLooping);
    void SetPriority(BYTE nNewPriority);
    void SetRange(int nNewRange);
    BOOL SetVolume(int nNewVolume);
    BOOL Stop();
    BOOL GetLooping() { return m_nLooping; }
    IDirectSoundBuffer* GetBuffer() { return pSoundBuffer; }

    static CSoundMixer* m_pSoundMixer;

    /* 0014 */ BOOL m_bPositionedSound;
    /* 0018 */ DWORD m_nBuffer;
    /* 001C */ int m_dwFrequency;
    /* 0020 */ int m_nRange; // #guess
    /* 0024 */ int m_nRangeVolume;
    /* 0028 */ int m_nXCoordinate;
    /* 002C */ int m_nYCoordinate;
    /* 0030 */ int m_nZCoordinate;
    /* 0034 */ int m_nPan;
    /* 0038 */ int m_nVolume;
    /* 003C */ int field_3C;
    /* 0040 */ int m_nChannel; // #guess
    /* 0044 */ int m_nPriority; // #guess
    /* 0048 */ int m_nLooping; // #guess
    /* 004C */ int m_nPitchVariance;
    /* 0050 */ int m_nVolumeVariance;
    /* 0054 */ BOOL m_b3DPositioning;
    /* 0058 */ IDirectSoundBuffer* pSoundBuffer; // #guess
    /* 005C */ BOOL m_bFireForget;
    /* 0060 */ uintptr_t m_nArea;
};

#endif /* CSOUND_H_ */

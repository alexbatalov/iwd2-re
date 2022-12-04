#ifndef CSOUNDMIXER_H_
#define CSOUNDMIXER_H_

#include <afx.h>
#include <afxwin.h>

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

#include "CSoundProperties.h"
#include "CUnknown2.h"

class CSound;

class CSoundMixer {
public:
    CSoundMixer();
    ~CSoundMixer();

    void AddSound(CSound* pSoundPtr);
    void TransferBuffer(CSound* pSoundPtr);
    void CleanUp();
    int GetChannelVolume(int nChannelNumber);
    void GetListenPosition(CPoint& pos, LONG& posZ);
    BOOL Initialize(CWnd* pWnd, int nNewMaxVoices, int nNewMaxChannels);
    void InitializeChannels(int nNewMaxChannels);
    BOOL ReleaseAll();
    void RemoveWaiting(CSound* pSoundPtr);
    void SetListenPosition(int nNewXCoordinate, int nNewYCoordinate, int nNewZCoordinate);
    void SetPanRange(int nNewPanRange);
    void UpdateSoundList();
    void UpdateSoundPositions();
    void SetMusicPath(CString& sMusicPath);
    void SetMusicVolume(int nNewVolume);
    void Lock();
    void Unlock();
    void UpdateMusic();

    void SetChannelVolume(int nChannelNumber, int nNewVolume);

    static BYTE m_tSqrtTable[10000];

    /* 0000 */ int field_0;
    /* 0004 */ IDirectSound* m_pDirectSound; // #guess
    /* 0008 */ IDirectSoundBuffer* m_pPrimarySoundBuffer; // #guess
    /* 003C */ int field_3C;
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ BOOL m_bInPositionUpdate;
    /* 004C */ BOOL m_bInReleaseAll; // #guess
    /* 0050 */ int field_50;
    /* 0054 */ CObArray m_aChannels;
    /* 0068 */ CObList m_lLooping;
    /* 0084 */ CObList m_lVoices;
    /* 00A0 */ CObList m_lWaiting; // #guess
    /* 00C0 */ int field_C0;
    /* 00C4 */ int field_C4;
    /* 00C8 */ int field_C8;
    /* 00CC */ int field_CC;
    /* 00D0 */ int field_D0;
    /* 00D4 */ int field_D4;
    /* 00D8 */ int m_nMaxChannels;
    /* 00DC */ int field_DC;
    /* 00E0 */ int m_nPanRange;
    /* 00E4 */ int m_nXCoordinate;
    /* 00E8 */ int m_nYCoordinate;
    /* 00EC */ int m_nZCoordinate;
    /* 00F0 */ int field_F0;
    /* 00F4 */ int field_F4;
    /* 00F8 */ int field_F8;
    /* 00FC */ int field_FC;
    /* 0100 */ CDWordArray m_aMusicSlots;
    /* 0114 */ CString m_sMusicPath; // #guess
    /* 0118 */ BOOL m_bMusicInitialized;
    /* 011C */ int field_11C;
    /* 0120 */ int m_nNumSongs;
    /* 0124 */ int field_124;
    /* 0128 */ CSoundProperties m_cSoundProperties; // #guess
    /* 013C */ IDirectSound3DListener* m_pDirectSound3DListener; // #guess
    /* 0140 */ int field_140;
    /* 0144 */ CUnknown2 field_144;
    /* 0178 */ int field_178;
};

#endif /* CSOUNDMIXER_H_ */

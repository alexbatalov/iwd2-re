#ifndef CSOUNDPROPERTIES_H_
#define CSOUNDPROPERTIES_H_

#include <windows.h>

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

#define CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT 0x1
#define CSOUNDPROPERTIES_EAX_SUPPORTS_REVERBMIX 0x2
#define CSOUNDPROPERTIES_EAX_SUPPORTS_VMANAGEMENT_MODE 0x4

typedef enum EAXEnvironment {
    EAX_ENVIRONMENT_GENERIC,
    EAX_ENVIRONMENT_PADDEDCELL,
    EAX_ENVIRONMENT_ROOM,
    EAX_ENVIRONMENT_BATHROOM,
    EAX_ENVIRONMENT_LIVINGROOM,
    EAX_ENVIRONMENT_STONEROOM,
    EAX_ENVIRONMENT_AUDITORIUM,
    EAX_ENVIRONMENT_CONCERTHALL,
    EAX_ENVIRONMENT_CAVE,
    EAX_ENVIRONMENT_ARENA,
    EAX_ENVIRONMENT_HANGAR,
    EAX_ENVIRONMENT_CARPETEDHALLWAY,
    EAX_ENVIRONMENT_HALLWAY,
    EAX_ENVIRONMENT_STONECORRIDOR,
    EAX_ENVIRONMENT_ALLEY,
    EAX_ENVIRONMENT_FOREST,
    EAX_ENVIRONMENT_CITY,
    EAX_ENVIRONMENT_MOUNTAINS,
    EAX_ENVIRONMENT_QUARRY,
    EAX_ENVIRONMENT_PLAIN,
    EAX_ENVIRONMENT_PARKINGLOT,
    EAX_ENVIRONMENT_SEWERPIPE,
    EAX_ENVIRONMENT_UNDERWATER,
    EAX_ENVIRONMENT_DRUGGED,
    EAX_ENVIRONMENT_DIZZY,
    EAX_ENVIRONMENT_PSYCHOTIC,
};

typedef struct EAXPRESET {
    int dwEnvironment;
    float fVolume;
    float fDecayTime;
    float fDaming;
};

class CSoundProperties {
public:
    CSoundProperties();
    ~CSoundProperties();
    DWORD Init(LPDIRECTSOUND lpDirectSound);
    void Uninit();
    BOOL SetVManagmentMode(int mode);
    BOOL SetEnvironmentPreset(int environment);
    BOOL SetBufferReverbMix(LPDIRECTSOUND3DBUFFER soundBuffer3D, float mix);

    /* 0000 */ IDirectSoundBuffer* m_pSoundBuffer;
    /* 0004 */ IKsPropertySet* m_pKsPropertySet;
    /* 0008 */ DWORD m_dwEAXProperties;
    /* 000C */ int m_nMode;
    /* 0010 */ int m_nPreset;
};

#endif /* CSOUNDPROPERTIES_H_ */

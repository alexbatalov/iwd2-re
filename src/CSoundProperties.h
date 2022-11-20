#ifndef CSOUNDPROPERTIES_H_
#define CSOUNDPROPERTIES_H_

#include <windows.h>

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

class CSoundProperties {
public:
    CSoundProperties();
    ~CSoundProperties();

    void Uninit();

    /* 0000 */ IDirectSoundBuffer* pSoundBuffer; // #guess
    /* 0004 */ IKsPropertySet* pKsPropertySet; // #guess
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
};

#endif /* CSOUNDPROPERTIES_H_ */

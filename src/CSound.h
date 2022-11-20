#ifndef CSOUND_H_
#define CSOUND_H_

#include <afx.h>

// clang-format off
#include <mmsystem.h>
#include <dsound.h>
// clang-format on

class CSound : public CObject {
public:
    /* 0058 */ IDirectSoundBuffer* pSoundBuffer; // #guess
};

#endif /* CSOUND_H_ */

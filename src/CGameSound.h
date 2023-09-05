#ifndef CGAMESOUND_H_
#define CGAMESOUND_H_

#include "CGameObject.h"
#include "CSound.h"
#include "FileFormat.h"

class CGameSound : public CGameObject {
public:
    /* 0000 */ ~CGameSound() override;
    /* 0048 */ void RemoveFromArea() override;

    void SetActive(BOOL bActive);
    BOOL IsActive();
    void Marshal(CAreaFileSoundObject** pSoundObject);

    /* 006E */ CAreaFileSoundObject m_soundObject;
    /* 0142 */ CSound m_looping;
    /* 01A6 */ BOOL m_bLoopPlaying;
};

#endif /* CGAMESOUND_H_ */

#ifndef CGAMESOUND_H_
#define CGAMESOUND_H_

#include "CGameObject.h"
#include "CSound.h"
#include "FileFormat.h"

class CGameSound : public CGameObject {
public:
    CGameSound(CGameArea* pArea, CAreaFileSoundObject* pSoundObject);
    /* 0000 */ ~CGameSound() override;
    /* 002C */ BOOLEAN CompressTime(DWORD deltaTime) override;
    /* 0048 */ void RemoveFromArea() override;

    void SetActive(BOOL bActive);
    BOOL IsActive();
    void Marshal(CAreaFileSoundObject** pSoundObject);

    /* 006E */ CAreaFileSoundObject m_soundObject;
    /* 0142 */ CSound m_looping;
    /* 01A6 */ BOOL m_bLoopPlaying;
    /* 01AA */ LONG m_period;
    /* 01AE */ LONG m_periodCount;
    /* 01B2 */ BYTE m_currentSound;
    /* 01B4 */ DWORD m_timeOfDayActive;
};

#endif /* CGAMESOUND_H_ */

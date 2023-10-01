#ifndef CDEATHSOUND_H_
#define CDEATHSOUND_H_

#include "CAITrigger.h"

class CDeathSound {
public:
    CDeathSound()
    {
        m_pTrigger = NULL;
    }

    ~CDeathSound()
    {
        if (m_pTrigger != NULL) {
            delete m_pTrigger;
        }
    }

    /* 0000 */ LONG m_soundLength;
    /* 0004 */ LONG m_characterId;
    /* 0008 */ SHORT m_soundNum;
    /* 000A */ BOOL m_started;
    /* 000E */ CAITrigger* m_pTrigger;
};

#endif /* CDEATHSOUND_H_ */

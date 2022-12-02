#ifndef CKEYINFO_H_
#define CKEYINFO_H_

#include "mfc.h"

class CKeyInfo {
public:
    CKeyInfo(BYTE keyCode = 0, BYTE repeatDelay = 0, BYTE repeatRate = 0);
    void SetRepeat(BYTE repeatDelay, BYTE repeatRate);

    ULONG m_repeatCount;
    BYTE m_keyCode;
    BYTE m_repeatDelay;
    BYTE m_repeatRate;
};

#endif /* CKEYINFO_H_ */

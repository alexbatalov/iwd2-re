#ifndef CGAMETIMER_H_
#define CGAMETIMER_H_

#include "mfc.h"

class CGameTimer {
public:
    LONG GetTime();
    BYTE GetId();
    void SetTime(LONG time);
    void SetId(BYTE id);

    LONG m_time;
    BYTE m_id;
};

#endif /* CGAMETIMER_H_ */

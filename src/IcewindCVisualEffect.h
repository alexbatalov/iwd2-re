#ifndef ICEWINDCVISUALEFFECT_H_
#define ICEWINDCVISUALEFFECT_H_

#include "mfc.h"

class IcewindCVisualEffect {
public:
    IcewindCVisualEffect();
    void sub_586A60(BOOLEAN a1);
    void sub_586A90(BOOLEAN a1);
    void sub_586AC0(BOOLEAN a1, INT nTransValue);

    /* 0000 */ BOOLEAN field_0;
    /* 0001 */ BOOLEAN field_1;
    /* 0002 */ BOOLEAN field_2;
    /* 0003 */ BOOLEAN field_3;
    /* 0004 */ INT m_nTransValue;
    /* 0008 */ DWORD m_dwFlags;
};

#endif /* ICEWINDCVISUALEFFECT_H_ */

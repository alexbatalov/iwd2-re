#ifndef CUNKNOWN2_H_
#define CUNKNOWN2_H_

#include "mfc.h"

// Unknown class in `CSoundMixer`.
class CUnknown2 {
public:
    CUnknown2();
    ~CUnknown2();
    BOOL sub_799C90();
    void sub_7C25B0();

    int field_0;
    int field_4;
    int field_8;
    CPtrList field_C;
    int field_28;
    int field_2C;
    int field_30;
};

#endif /* CUNKNOWN2_H_ */

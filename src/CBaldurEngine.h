#ifndef CBALDURENGINE_H_
#define CBALDURENGINE_H_

#include "CUIManager.h"
#include "CWarp.h"

class CBaldurEngine : public CWarp {
public:
    CBaldurEngine();
    ~CBaldurEngine() { }

    /* 0028 */ int field_28;
    /* 002C */ int field_2C;
    /* 0030 */ CUIManager field_30;
    /* 00FA */ int field_FA;
    /* 00FE */ int field_FE;
    /* 0102 */ int field_102;
};

#endif /* CBALDURENGINE_H_ */

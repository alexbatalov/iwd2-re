#ifndef CVIDBLITTER_H_
#define CVIDBLITTER_H_

#include <afx.h>

class CVidBlitter {
public:
    typedef void(Func1)(int, int, int, int, int, int);

    CVidBlitter();

    void Init();

    /* 0000 */ BOOLEAN m_bSoftSrcKeyBltFast; // #guess
    /* 0001 */ BOOLEAN m_bSoftBltFast; // #guess
    /* 0002 */ BOOLEAN m_bSoftSrcKeyBlt; // #guess
    /* 0003 */ BOOLEAN m_bSoftBlt; // #guess
    /* 0004 */ BOOLEAN m_bSoftMirrorBlt; // #guess
    /* 00DE */ int field_DE;
    /* 00E2 */ int field_E2;
    /* 00E6 */ unsigned char field_E6;
    /* 00E8 */ Func1* field_E8;
    /* 00EC */ Func1* field_EC;
    /* 00F0 */ Func1* field_F0;
    /* 00F4 */ Func1* field_F4;
    /* 00F8 */ Func1* field_F8;
    /* 00FC */ Func1* field_FC;
};

#endif /* CVIDBLITTER_H_ */

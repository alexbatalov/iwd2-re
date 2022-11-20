#ifndef CIMM_H_
#define CIMM_H_

#include <afxmt.h>
#include <afxwin.h>

// NOTE: For unknown reason the constructor and destructor for this class are
// inlined in `CChitin`. This is only way to explain how assignments appear
// before static objects constructor calls.
//
// #guess
class CImm {
public:
    // NOTE: Constructor is inlined in `CChitin` constructor. This is the only
    // way to explain how assignments appear before other static object
    // constructor calls.
    CImm()
    {
        field_0 = 0;
        field_12C = 0;
        field_128 = 0;
        field_104 = 0;
        field_13C = 0;
    }

    // NOTE: Destructor is inlined in `CChitin` destructor.
    ~CImm() { }

    /* 0000 */ int field_0;
    /* 0104 */ int field_104;
    /* 0108 */ CCriticalSection field_108;
    /* 0128 */ int field_128;
    /* 012C */ int field_12C;
    /* 0130 */ CString field_130;
    /* 0134 */ CString field_134;
    /* 0138 */ CString field_138;
    /* 013C */ int field_13C;
};

#endif /* CIMM_H_ */

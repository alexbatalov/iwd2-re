#ifndef CGAMESPY_H_
#define CGAMESPY_H_

#include <windows.h>

// #guess
class CGameSpy {
public:
    CGameSpy();
    ~CGameSpy();

    /* 0000 */ unsigned char field_0;
    /* 0001 */ unsigned char field_1;
    /* 0002 */ int field_2;
    /* 0012 */ int field_12;
    /* 0016 */ int field_16;
    /* 001A */ int field_1A;
    /* 001E */ int field_1E;
    /* 0022 */ int field_22;
    /* 0026 */ unsigned char field_26;
    /* 0028 */ int field_28;
};

#endif /* CGAMESPY_H_ */

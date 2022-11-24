#ifndef CVIDINF_H_
#define CVIDINF_H_

#include "CVidBitmap.h"
#include "CVidFont.h"
#include "CVidMode.h"

class CVidInf : public CVidMode {
public:
    CVidInf();
    /* 005C */ BOOL ActivateVideoMode(CVidMode* pPrevVidMode, int a2, int a3);
    /* 011C */ ~CVidInf();

    /* 00F4 */ unsigned char field_F4[108];
    /* 0160 */ RECT field_160;
    /* 0170 */ int field_170;
    /* 0174 */ int field_174;
    /* 0178 */ CVidFont field_178;
    /* 0678 */ int field_678;
    /* 067C */ int field_67C;
    /* 0680 */ CVidBitmap field_680;
    /* 073A */ CString field_73A;
};

#endif /* CVIDINF_H_ */

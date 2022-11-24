#ifndef CVIDEO_H_
#define CVIDEO_H_

#include <afx.h>

#include "CResRef.h"
#include "CVidBlitter.h"

class CVidMode;

class CVideo {
public:
    CVideo();
    ~CVideo();

    CVidMode* GetVidMode(int a1);

    /* 0000 */ short field_0;
    /* 0002 */ short field_2;
    /* 0004 */ unsigned char field_4;
    /* 0005 */ unsigned char field_5;
    /* 0006 */ unsigned char field_6;
    /* 0008 */ CVidBlitter cVidBlitter; // #guess
    /* 0108 */ int field_108;
    /* 010C */ int field_10C;
    /* 0110 */ int field_110;
    /* 0114 */ CResRef field_114;
    /* 011C */ short field_11C;
    /* 011E */ int field_11E;
    /* 0122 */ int field_122;
    /* 0126 */ int field_126;
    /* 012A */ int field_12A;
    /* 012E */ int field_12E;
    /* 0132 */ BOOL m_bIs3dAccelerated;
    /* 0136 */ int field_136;
    /* 013A */ int field_13A;
    /* 013E */ int field_13E;
    /* 0142 */ int field_142;
    /* 0146 */ int field_146;
    /* 014A */ int field_14A;
    /* 014E */ CVidMode* m_pVidModes[4];
    /* 015E */ int field_15E;
    /* 0162 */ unsigned char field_162;
    /* 0162 */ unsigned char field_163;
};

#endif /* CVIDEO_H_ */

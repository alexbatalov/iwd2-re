#ifndef CRESBITMAP_H_
#define CRESBITMAP_H_

#include "CRes.h"

class CResBitmap : public CRes {
public:
    CResBitmap();
    ~CResBitmap();
    BOOL GetPixelColor(INT nX, INT nY, RGBQUAD& color, BOOL bDoubleSize);

    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ int field_58;
    /* 005C */ int field_5C;
    /* 0060 */ int field_60;
    /* 0064 */ int field_64;
    /* 0068 */ int field_68;
};

#endif /* CRESBITMAP_H_ */

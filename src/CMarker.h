#ifndef CMARKER_H_
#define CMARKER_H_

#include "mfc.h"

class CMarker {
public:
    static const BYTE RECTICLE;
    static const BYTE ELLIPSE;

    CMarker();
    BYTE SetType(BYTE nType);

    /* 0000 */ BYTE m_type;
    /* 0002 */ SHORT m_nRecticleCounter;
    /* 0004 */ unsigned char field_4;
    /* 0005 */ unsigned char field_5;
    /* 0006 */ int field_6;
    /* 000A */ unsigned char field_A[24];
    /* 0022 */ unsigned char field_22;
};

#endif /* CMARKER_H_ */

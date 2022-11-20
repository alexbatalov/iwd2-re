#ifndef CSOUNDMIXER_H_
#define CSOUNDMIXER_H_

#include <afx.h>

#include "CSoundProperties.h"
#include "CUnknown2.h"

class CSoundMixer {
public:
    CSoundMixer();
    ~CSoundMixer();

    void CleanUp();
    BOOL ReleaseAll();

    static BYTE m_tSqrtTable[10000];

    /* 0000 */ int field_0;
    /* 0008 */ int field_8;
    /* 003C */ int field_3C;
    /* 0040 */ int field_40;
    /* 0044 */ int field_44;
    /* 0048 */ int field_48;
    /* 004C */ int field_4C;
    /* 0050 */ int field_50;
    /* 0054 */ CObArray field_54;
    /* 0068 */ CObList field_68;
    /* 0084 */ CObList field_84;
    /* 00A0 */ CObList field_A0;
    /* 00C0 */ int field_C0;
    /* 00C4 */ int field_C4;
    /* 00C8 */ int field_C8;
    /* 00CC */ int field_CC;
    /* 00D0 */ int field_D0;
    /* 00D4 */ int field_D4;
    /* 00D8 */ int field_D8;
    /* 00DC */ int field_DC;
    /* 00E0 */ int field_E0;
    /* 00E4 */ int field_E4;
    /* 00E8 */ int field_E8;
    /* 00EC */ int field_EC;
    /* 00F0 */ int field_F0;
    /* 00F4 */ int field_F4;
    /* 00F8 */ int field_F8;
    /* 00FC */ int field_FC;
    /* 0100 */ CDWordArray field_100;
    /* 0114 */ CString field_114;
    /* 0118 */ int field_118;
    /* 011C */ int field_11C;
    /* 0120 */ int field_120;
    /* 0124 */ int field_124;
    /* 0128 */ CSoundProperties cSoundProperties; // #guess
    /* 013C */ int field_13C;
    /* 0140 */ int field_140;
    /* 0144 */ CUnknown2 field_144;
    /* 0178 */ int field_178;
};

#endif /* CSOUNDMIXER_H_ */

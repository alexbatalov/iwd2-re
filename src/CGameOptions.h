#ifndef CGAMEOPTIONS_H_
#define CGAMEOPTIONS_H_

#include "mfc.h"

class CGameOptions {
public:
    CGameOptions();

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ DWORD m_nVolumeMusic; // #guess
    /* 001C */ DWORD m_nVolumeSFX; // #guess
    /* 0020 */ DWORD m_nVolumeVoices; // #guess
    /* 0024 */ DWORD m_nVolumeAmbients;
    /* 0028 */ DWORD m_nVolumeMovie; // #guess
    /* 002C */ int field_2C;
    /* 0030 */ int field_30;
    /* 0034 */ int m_nTranslucentShadows; // #guess
    /* 0038 */ int field_38;
    /* 003C */ int field_3C;
    /* 0040 */ int m_nTooltips; // #guess
    /* 0044 */ int field_44;
    /* 0048 */ int field_48;
    /* 004C */ int field_4C;
    /* 0050 */ int field_50;
    /* 0054 */ int field_54;
    /* 0058 */ int field_58;
    /* 005C */ int field_5C;
    /* 0060 */ int field_60;
    /* 0064 */ int field_64;
    /* 0068 */ int field_68;
    /* 006C */ int field_6C;
    /* 0070 */ int field_70;
    /* 0074 */ int field_74;
    /* 0078 */ int field_78;
    /* 007C */ int field_7C;
    /* 0080 */ int field_80;
    /* 0084 */ int field_84;
    /* 0088 */ BOOL m_bEnvironmentalAudio;
    /* 008C */ int field_8C;
    /* 0090 */ BOOL m_bDisplayMovieSubtitles; // #guess
    /* 0094 */ int field_94;
    /* 0098 */ int field_98;
    /* 009C */ int field_9C;
    /* 00A0 */ int field_A0;
    /* 00A4 */ int field_A4;
    /* 00A8 */ int field_A8;
    /* 00AC */ int field_AC;
    /* 00B0 */ int field_B0;
    /* 00B4 */ int field_B4;
    /* 00B8 */ int field_B8;
    /* 00BC */ int field_BC;
    /* 00C0 */ unsigned char field_C0;
    /* 00C2 */ int field_C2;
    /* 00C6 */ int field_C6;
    /* 00CA */ int field_CA;
    /* 00CE */ int m_nShadedSelectionBox; // #guess
    /* 00D2 */ int field_D2;
    /* 00D6 */ int field_D6;
    /* 00DA */ int field_DA;
};

#endif /* CGAMEOPTIONS_H_ */

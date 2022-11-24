#ifndef CVIDMODE_H_
#define CVIDMODE_H_

#include <afx.h>
#include <afxmt.h>
#include <afxtempl.h>

class CVidMode {
public:
    struct Entry {
        unsigned char dummy[1];
    };

    static BYTE NUM_FADE_FRAMES;
    static BOOL bInitialized;

    CVidMode();
    /* 005C */ virtual int ActivateVideoMode(CVidMode* pPrevVidMode, int a2, int a3) = 0;
    /* 011C */ virtual ~CVidMode();

    /* 0004 */ int field_4;
    /* 0008 */ int field_8;
    /* 000C */ int field_C;
    /* 0010 */ int field_10;
    /* 0014 */ int field_14;
    /* 0018 */ int field_18;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ CCriticalSection field_28;
    /* 0048 */ BOOLEAN m_bFadeTo;
    /* 0049 */ BYTE m_nFade;
    /* 004A */ CCriticalSection field_4A;
    /* 006A */ CTypedPtrList<CPtrList, Entry*> field_6A;
    /* 0086 */ int field_86;
    /* 008A */ int field_8A;
    /* 008E */ unsigned char field_8E;
    /* 008F */ unsigned char field_8F;
    /* 0090 */ DWORD nTickCount;
    /* 0094 */ int field_94;
    /* 0098 */ int field_98;
    /* 009C */ int field_9C;
    /* 00A0 */ void* field_A0;
    /* 00A4 */ COLORREF rgbGlobalTint;
    /* 00A8 */ unsigned char field_A8;
    /* 00A9 */ unsigned char field_A9;
    /* 00C2 */ int field_C2;
    /* 00C6 */ int field_C6;
    /* 00CA */ int field_CA;
    /* 00D2 */ short field_D2;
    /* 00D4 */ int field_D4;
    /* 00D8 */ int field_D8;
    /* 00DC */ int field_DC;
    /* 00E0 */ int field_E0;
    /* 00E4 */ int field_E4;
    /* 00E8 */ int field_E8;
    /* 00EC */ int field_EC;
    /* 00F0 */ int field_F0;
};

#endif /* CVIDMODE_H_ */

#ifndef CNETWORK_H_
#define CNETWORK_H_

#include <afx.h>

#include "CNetworkWindow.h"

class CNetwork {
public:
    struct S861078 {
        int field_0;
        int field_4;
        int field_8;
        int field_C;
    };

    CNetwork();
    ~CNetwork();

    static const S861078 stru_861078;

    /* 0000 */ int field_0;
    /* 0004 */ int field_4;
    /* 0008 */ S861078 field_8;
    /* 0018 */ unsigned char field_18;
    /* 0019 */ unsigned char field_19;
    /* 001A */ unsigned char field_1A;
    /* 001B */ unsigned char field_1B;
    /* 001C */ int field_1C;
    /* 0020 */ int field_20;
    /* 0024 */ int field_24;
    /* 0028 */ int field_28;
    /* 002C */ int field_2C;
    /* 0030 */ int field_30;
    /* 0034 */ int field_34;
    /* 0038 */ CString field_38[5];
    /* 004C */ S861078 field_4C;
    /* 009C */ unsigned char field_9C;
    /* 009D */ unsigned char field_9D;
    /* 009E */ unsigned char field_9E;
    /* 009F */ unsigned char field_9F;
    /* 00A0 */ unsigned char field_A0;
    /* 00A2 */ int field_A2;
    /* 00A6 */ int field_A6;
    /* 00AA */ CString field_AA[20];
    /* 00FA */ CString field_FA;
    /* 00FE */ CString field_FE;
    /* 0102 */ int field_102;
    /* 0106 */ int field_106;
    /* 010A */ int field_10A;
    /* 010E */ int field_10E;
    /* 0112 */ int field_112;
    /* 0116 */ unsigned char field_116;
    /* 0118 */ int field_118;
    /* 0120 */ unsigned char field_120;
    /* 0121 */ unsigned char field_121;
    /* 0122 */ int field_122;
    /* 0126 */ int field_126;
    /* 012A */ CString field_12A[64];
    /* 022A */ S861078 field_22A[64];
    /* 0630 */ unsigned char field_630[64];
    /* 066A */ S861078 field_66A;
    /* 067A */ unsigned char field_67A;
    /* 067C */ CString field_67C;
    /* 0680 */ unsigned char field_680;
    /* 0682 */ CString field_682;
    /* 0686 */ unsigned char field_686;
    /* 06D8 */ int field_6D8;
    /* 06DC */ int field_6DC;
    /* 06E0 */ BOOLEAN m_bConnectionEstablished;
    /* 06E1 */ BOOLEAN m_bIsHost;
    /* 06E2 */ int m_nMaxPlayers;
    /* 06E6 */ int field_6E6;
    /* 06EA */ unsigned char field_6EA;
    /* 06EB */ unsigned char field_6EB;
    /* 06EC */ CString field_6EC;
    /* 06F0 */ CString field_6F0;
    /* 06F4 */ CString field_6F4;
    /* 06F8 */ unsigned char field_6F8;
    /* 06F9 */ unsigned char field_6F9;
    /* 06FA */ int field_6FA;
    /* 06FE */ CString field_6FE;
    /* 0702 */ CString field_702[6];
    /* 071A */ int field_71A[6];
    /* 0732 */ int field_732;
    /* 0736 */ CString field_736[6];
    /* 074E */ int field_74E[6];
    /* 0766 */ unsigned char field_766[6];
    /* 076C */ unsigned char field_76C[6];
    /* 0772 */ int field_772[6];
    /* 078A */ int field_78A;
    /* 078E */ int field_78E;
    /* 0792 */ CString field_792;
    /* 0796 */ int field_796;
    /* 079A */ CNetworkWindow m_pSlidingWindow[6];
    /* 0ACA */ CNetworkWindow m_SystemWindow;
    /* 0B52 */ DWORD m_dwCRC32[256];
    /* 0F52 */ CRITICAL_SECTION field_F52;
    /* 0F6A */ CRITICAL_SECTION field_F6A;
};

#endif /* CNETWORK_H_ */

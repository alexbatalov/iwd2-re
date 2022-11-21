#include "CNetwork.h"

// 0x861078
const CNetwork::S861078 CNetwork::stru_861078 = { 0 };

// 0x7A3FD0
CNetwork::CNetwork()
{
    field_9D = 0;
    field_9E = 0;
    field_116 = 0;
    field_796 = 0;
    InitializeCriticalSection(&field_F52);
    InitializeCriticalSection(&field_F6A);
    field_0 = 0;
    field_4 = 0;
    field_8 = stru_861078;
    field_18 = 0;
    field_19 = 0;
    field_1A = 0;
    field_1B = 0;
    field_1C = -1;
    field_20 = 0;
    field_4C = stru_861078;
    field_20++;
    field_9C = 0;
    field_24 = 0;
    field_28 = 0;
    field_2C = 0;
    field_30 = 0;
    field_34 = 0;
    field_9F = 0;
    field_A0 = 0;
    field_A2 = -1;
    field_A6 = 0;
    field_FA = "";
    field_FE = "";
    field_106 = 57600;
    field_102 = 1;
    field_112 = 4;
    field_10E = 0;
    field_10A = 0;
    field_120 = 0;

    for (int k = 0; k < 64; k++) {
        field_12A[k] = "";
        field_22A[k] = stru_861078;
        field_630[k] = 0;
    }

    field_121 = 0;
    field_122 = -1;
    field_126 = 0;
    field_66A = stru_861078;
    field_67A = 0;
    field_67C = "";
    field_680 = 0;
    field_682 = "";
    field_686 = 1;
    field_6D8 = 0;
    field_6DC = 0;
    field_6E0 = 0;
    field_6E1 = 0;
    field_6EA = 0;
    field_6EB = 0;
    m_nMaxPlayers = 6;
    field_6E6 = 0;
    field_6F8 = 0;
    field_6F9 = 0;
    field_6FA = 0;
    field_6FE = "";
    field_78E = -1;
    field_78A = -1;
    field_732 = 0;

    for (int l = 0; l < 6; l++) {
        field_74E[l] = 0;
        field_772[l] = 0;
        field_736[l] = "";
        field_76C[l] = 0;
        field_766[l] = 0;
        m_pSlidingWindow[l].Initialize(l);
    }

    m_SystemWindow.Initialize(-1);

    for (unsigned int m = 0; m <= 255; m++) {
        unsigned int v1 = m;
        for (unsigned int bit = 8; bit > 0; bit--) {
            if ((v1 & 1) != 0) {
                v1 >>= 1;
                v1 ^= 0xEDB88320;
            } else {
                v1 >>= 1;
            }
        }
        m_dwCRC32[m] = v1;
    }

    for (int j = 0; j < 6; j++) {
        field_71A[j] = 0;
    }

    field_118 = 0;
}

// 0x7A4440
CNetwork::~CNetwork()
{
    // TODO: Incomplete.
}

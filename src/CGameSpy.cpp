#include "CGameSpy.h"

// #binary-identical
// 0x4D0930
CGameSpy::CGameSpy()
{
    field_2 = 0;
    field_12 = 0;
    field_16 = 0;
    field_22 = 0;
    field_1 = 0;
    field_1E = 0;
    field_1A = 0;
    field_28 = 0;
    field_0 = 0;
    field_26 = 0;
}

// #binary-identical
// 0x4D0960
CGameSpy::~CGameSpy()
{
    if (field_0 == 1) {
        WSACleanup();
    }
    field_0 = 0;
    field_1 = 0;
}

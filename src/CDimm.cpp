#include "CDimm.h"

// #binary-identical
// 0x781E60
CDimm::CDimm()
{
    field_2A4 = 0;
    field_295 = 0;
    field_296 = 0;
    field_297 = 0;

    MEMORYSTATUS memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUS);

    field_0 = 0;
    field_4 = 0;
    field_8 = 0;
    field_DA = 0;
    field_CE = 0;
    field_274 = 0;
    field_270 = 0;
    field_D2 = 0;
    field_E6 = 0;

    GlobalMemoryStatus(&memoryStatus);

    field_EA = 1;
    field_2A0 = 0;
    dwTotalPhysicalMemory = memoryStatus.dwTotalPhys;

    field_D6 = 12000000;
    field_29C = 0;
    field_EC = 0;
    field_E2 = 0;
    field_2A5 = 0;
    field_2A6 = 0;
    field_294 = 0;
}

// 0x782020
CDimm::~CDimm()
{
    // TODO: Incomplete.
}

// 0x7840E0
void CDimm::DestroyKeyTable()
{
    // TODO: Incomplete.
}

// 0x785FB0
void CDimm::DumpAll()
{
    // TODO: Incomplete.
}

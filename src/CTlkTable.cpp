#include "CTlkTable.h"

// NOTE: Probably static in `CTlkTable`.
//
// 0x8FB954
unsigned char byte_8FB954;

// 0x8FB955
BOOLEAN CTlkTable::STRREF_ON;

// #binary-identical
// 0x793DB0
CTlkTable::CTlkTable()
{
    field_A4 = 0;
    field_58 = byte_8FB954;
}

// 0x793EB0
CTlkTable::~CTlkTable()
{
    // TODO: Incomplete.
}

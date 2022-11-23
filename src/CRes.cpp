#include "CRes.h"

#include "CChitin.h"

// #binary-identical
// 0x77E250
CRes::CRes()
{
    field_48 = 0;
    field_40 = 0;
    field_4C = 0;
    field_44 = 0;
    field_14 = 0;
    field_1C = 0;
    field_8 = 0;
    field_10 = 0;
    field_C = 0;
    field_18 = 0;
    field_4 = 0;
}

// #binary-identical
// 0x77E2F0
CRes::~CRes()
{
    field_1C = 0;
    g_pChitin->cDimm.Dump(this, 1, 0);
}

// #binary-identical
// 0x77E370
int CRes::CancelRequest()
{
    return g_pChitin->cDimm.CancelRequest(this);
}

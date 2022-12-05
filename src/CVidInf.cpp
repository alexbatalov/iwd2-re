#include "CVidInf.h"

// #binary-identical
// 0x79AF00
CVidInf::CVidInf()
{
    m_nSurfaces = 0;
    m_pSurfaces = NULL;
    field_678 = 0;
    field_E0 = 4;
    field_67C = 0;
    field_98 = 0;
    field_94 = 0;
    field_73A = "";
    memset(field_F4, 0, sizeof(field_F4));
    SetRect(&field_160, 0, 0, 0, 0);
    field_170 = 0;
    field_174 = 1;
}

// NOTE: Parent destructor is not inlined. Even when it's inlined there is some
// difference in unwind stack, not sure how to replicate it one-to-one.
//
// 0x79B010
CVidInf::~CVidInf()
{
    if (m_pSurfaces != NULL) {
        delete m_pSurfaces;
        m_pSurfaces = NULL;
    }

    m_nSurfaces = 0;
}

// 0x79B100
BOOL CVidInf::ActivateVideoMode(CVidMode* pPrevVidMode, HWND hWnd, BOOL bFullscreen)
{
    // TODO: Incomplete.

    return FALSE;
}

BOOL CVidInf::DeactivateVideoMode(int a2)
{
    // TODO: Incomplete.

    return FALSE;
}

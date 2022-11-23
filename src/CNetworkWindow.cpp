#include "CNetworkWindow.h"

#include "CChitin.h"

// #binary-identical
// 0x7A1E50
CNetworkWindow::CNetworkWindow()
{
    m_bInitialized = 0;
    field_1 = 0;
    field_2 = 0;
    field_3 = 0;
    field_4 = 0;
    field_6 = 0;
    field_8 = 0;
    field_A = 0;
    field_C = 0;
    field_66 = 0;
    field_68 = 0;
    field_6C = 0;
    field_6E = 0;
    field_70 = 0;
    field_72 = 0;
    field_76 = 0;
    field_7A = 0;
    field_7B = 0;
    field_7C = 0;
    field_80 = 0;
    field_84 = 0;
}

// #binary-identical
// 0x7A1F00
CNetworkWindow::~CNetworkWindow()
{
    m_bInitialized = FALSE;
}

// #binary-identical
// 0x7A2770
void CNetworkWindow::Initialize(int a1)
{
    if (m_bInitialized) {
        RemoveFromAllQueues();
    }

    field_1 = 0;
    field_2 = 0;
    field_3 = static_cast<unsigned char>(a1);
    field_6 = 0;
    field_A = 1;
    field_4 = 0;
    field_6E = 0;
    field_8 = 0;
    field_70 = 01;
    field_72 = 3200;
    field_7A = 0;

    DWORD v1 = GetTickCount();
    DWORD v2 = GetTickCount() + 25000;
    if (v1 > v2) {
        v2 = -1;
    }
    field_80 = v2;

    DWORD v3 = GetTickCount();
    DWORD v4 = GetTickCount() + 200;
    if (v3 > v4) {
        v4 = -1;
    }
    field_84 = v4;

    field_66 = 0;
    field_6C = 0;
    field_1A = 0;
    field_16 = 0;
    field_2A = 0;
    field_26 = 0;
    field_68 = 0;
    m_bInitialized = TRUE;
}

// 0x7A2D10
void CNetworkWindow::RemoveFromAllQueues()
{
    if (field_16 != NULL) {
        delete field_16;
        field_16 = NULL;
        field_1A = 0;
    }

    if (field_26 != NULL) {
        delete field_26;
        field_26 = NULL;
        field_2A = 0;
    }

    EnterCriticalSection(&(g_pChitin->cNetwork.field_F52));

    // TODO: Incomplete.

    m_bInitialized = FALSE;
    LeaveCriticalSection(&(g_pChitin->cNetwork.field_F52));
}

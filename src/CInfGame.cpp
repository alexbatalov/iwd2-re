#include "CInfGame.h"

#include <process.h>

#include "CSearchBitmap.h"

// 0x59CC30
CInfGame::CInfGame()
{
    // TODO: Incomplete.
}

// 0x59ECB0
CInfGame::~CInfGame()
{
    // TODO: Incomplete.
}

// 0x59F500
void CInfGame::StartSearchThread()
{
    if (_beginthread(SearchThreadMain, 0, NULL) == -1) {
        CloseHandle(m_hSearchThread);
        m_hSearchThread = NULL;
    }
}

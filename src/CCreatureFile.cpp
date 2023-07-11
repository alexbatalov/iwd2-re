#include "CCreatureFile.h"

// 0x712370
CCreatureFile::CCreatureFile()
{
}

// 0x4821C0
CCreatureFile::~CCreatureFile()
{
}

// 0x7123B0
void* CCreatureFile::GetData()
{
    if (pRes != NULL) {
        return pRes->Demand();
    } else {
        return NULL;
    }
}

// 0x7123C0
DWORD CCreatureFile::GetDataSize()
{
    if (pRes == NULL) {
        return 0;
    }

    if (pRes->Demand() == NULL) {
        return 0;
    }

    DWORD nSize = pRes->m_nResSizeActual;

    pRes->Release();

    return nSize;
}

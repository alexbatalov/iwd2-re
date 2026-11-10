#include "CCharacterFile.h"

// 0x720480
BYTE* CCharacterFile::GetData()
{
    if (pRes != NULL) {
        return reinterpret_cast<BYTE*>(pRes->Demand());
    } else {
        return NULL;
    }
}

// 0x720490
DWORD CCharacterFile::GetDataSize()
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

// 0x5C7B00
void CCharacterFile::ReleaseData()
{
    if (pRes != NULL) {
        pRes->Release();
    }
}

// 0x722520
char* CBiographyFile::GetData()
{
    if (pRes != NULL) {
        return reinterpret_cast<char*>(pRes->Demand());
    } else {
        return NULL;
    }
}

#include "CSoundProperties.h"

// 0x7C20C0
CSoundProperties::CSoundProperties()
{
    pSoundBuffer = NULL;
    pKsPropertySet = NULL;
    field_8 = 0;
    field_C = 0;
    field_10 = 0;
}

// 0x7C22D0
CSoundProperties::~CSoundProperties()
{
    Uninit();
}

// #binary-identical
// 0x7C22D0
void CSoundProperties::Uninit()
{
    if (pKsPropertySet != NULL) {
        pKsPropertySet->Release();
    }
    pKsPropertySet = NULL;

    if (pSoundBuffer != NULL) {
        pSoundBuffer->Release();
    }
    pSoundBuffer = NULL;

    field_8 = 0;
}

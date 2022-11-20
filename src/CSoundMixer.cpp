#include "CSoundMixer.h"

#include <cmath>

#include "CBaldurChitin.h"

// 0x9039D8
BYTE CSoundMixer::m_tSqrtTable[10000];

// 0x7AAD80
CSoundMixer::CSoundMixer()
{
    field_44 = 0;
    field_48 = 0;
    field_4C = 0;
    field_50 = 0;
    field_C4 = 0;
    field_C8 = 0;
    field_CC = 0;
    field_D0 = 0;
    field_D4 = 0;
    field_D8 = 0;
    field_DC = 0;
    field_E0 = 0;
    field_E4 = 0;
    field_E8 = 0;
    field_EC = 0;
    field_F0 = 0;
    field_F4 = 0;
    field_F8 = 0;
    field_FC = 0;
    field_178 = 0;
    field_C0 |= 0x03;
    field_3C = 0;
    field_40 = 0;
    field_140 = 0;
    cSoundProperties.field_10 = 0;
    pDirectSound3DListener = NULL;
    pPrimarySoundBuffer = NULL;
    field_118 = 0;
    field_114 = ".\\music";
    field_120 = 0;
    field_11C = -1;
    field_124 = -1;
    field_100.SetSize(10);

    // NOTE: Generated assembly is different.
    for (int i = 0; i < 10000; i++) {
        m_tSqrtTable[i] = static_cast<BYTE>(sqrt(static_cast<double>(i)));
    }

    ReleaseAll();

    field_3C = 0;
    field_40 = 0;
    field_0 = 0;
}

// #binary-identical
// 0x7AAF50
CSoundMixer::~CSoundMixer()
{
    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        EnterCriticalSection(&(g_pChitin->field_394));
    }

    CleanUp();

    field_100.SetSize(0);

    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        LeaveCriticalSection(&(g_pChitin->field_394));
    }
}

// 0x7AB1E0
void CSoundMixer::CleanUp()
{
    // TODO: Incomplete.
}

// #binary-identical
// 0x7AB7D0
BOOL CSoundMixer::ReleaseAll()
{
    if (field_4C != 0 || field_48 != 0) {
        return FALSE;
    }

    field_4C = 1;
    field_48 = 1;

    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        EnterCriticalSection(&(g_pChitin->field_394));
    }

    if (pDirectSound3DListener != NULL) {
        pDirectSound3DListener->Release();
        pDirectSound3DListener = NULL;
    }

    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        EnterCriticalSection(&(g_pChitin->field_394));
    }

    cSoundProperties.Uninit();
    field_140 = 0;

    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        LeaveCriticalSection(&(g_pChitin->field_394));
    }

    while (!field_84.IsEmpty()) {
        // TODO: Object type?
        CObject* v1 = field_84.RemoveHead();
        if (v1 != NULL) {
            delete v1;
        }
    }

    while (!lSounds.IsEmpty()) {
        CSound* sound = static_cast<CSound*>(lSounds.RemoveHead());
        if (sound->pSoundBuffer != NULL) {
            sound->pSoundBuffer->Release();
            sound->pSoundBuffer = NULL;
        }
        // NOTE: Why sound itself is not deleted like the object above?
    }

    if (pDirectSound != NULL) {
        if (pPrimarySoundBuffer != NULL) {
            pPrimarySoundBuffer->Release();
            pPrimarySoundBuffer = NULL;
        }

        pDirectSound->Release();
        pDirectSound = NULL;
    }

    field_4C = 0;

    if (g_pChitin != NULL && g_pChitin->field_390 != 1) {
        LeaveCriticalSection(&(g_pChitin->field_394));
    }

    return TRUE;
}

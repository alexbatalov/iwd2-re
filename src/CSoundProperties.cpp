#include "CSoundProperties.h"

#include "CChitin.h"

#include <initguid.h>

// TODO: Check usage in `CSoundProperties::Init`, probably there were no parens
// used.
#define KSPROPERTY_SUPPORT_SETGET (KSPROPERTY_SUPPORT_SET | KSPROPERTY_SUPPORT_GET)

#define DSPROPERTY_EAX_ALL 0
#define DSPROPERTY_EAX_REVERBMIX 1

// 0x85E530
DEFINE_GUID(stru_85E530, 0x4A4E6FC1, 0xC341, 0x11D1, 0xB7, 0x3A, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// 0x8BD7C8
DEFINE_GUID(stru_8BD7C8, 0x4A4E6FC1, 0xC341, 0x11D1, 0xB7, 0x3A, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// 0x8BD7D8
DEFINE_GUID(stru_8BD7D8, 0x62A69BAE, 0xDF9D, 0x11D1, 0x99, 0xA6, 0x00, 0xC0, 0x4F, 0xC9, 0x9D, 0x46);

// 0x8BD7E8
DEFINE_GUID(stru_8BD7E8, 0x4A4E6FC0, 0xC341, 0x11D1, 0xB7, 0x3A, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

// 0x7C20C0
CSoundProperties::CSoundProperties()
{
    m_pSoundBuffer = NULL;
    m_pKsPropertySet = NULL;
    m_dwEAXProperties = 0;
    m_nMode = 0;
    m_nPreset = 0;
}

// 0x7C22D0
CSoundProperties::~CSoundProperties()
{
    Uninit();
}

// 0x7C20E0
DWORD CSoundProperties::Init(LPDIRECTSOUND lpDirectSound)
{
    ULONG support;

    if (m_pSoundBuffer == NULL) {
        WAVEFORMATEX waveFormat = { 0 };
        DSBUFFERDESC bufferDesc = { 0 };

        waveFormat.wFormatTag = 1;
        waveFormat.nChannels = 1;
        waveFormat.nSamplesPerSec = 22050;
        waveFormat.nAvgBytesPerSec = 44100;
        waveFormat.nBlockAlign = 2;
        waveFormat.wBitsPerSample = 16;

        bufferDesc.dwSize = sizeof(bufferDesc);
        bufferDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRL3D;
        bufferDesc.dwBufferBytes = 32;
        bufferDesc.lpwfxFormat = &waveFormat;

        if (FAILED(lpDirectSound->CreateSoundBuffer(&bufferDesc, &m_pSoundBuffer, NULL))) {
            return 0;
        }
    }

    if (m_pKsPropertySet == NULL) {
        if (FAILED(m_pSoundBuffer->QueryInterface(IID_IKsPropertySet, reinterpret_cast<LPVOID*>(&m_pKsPropertySet)))) {
            return 0;
        }
    }

    if (SUCCEEDED(m_pKsPropertySet->QuerySupport(stru_8BD7D8, DSPROPERTY_EAX_ALL, &support))) {
        if ((support & KSPROPERTY_SUPPORT_SETGET) == KSPROPERTY_SUPPORT_SETGET) {
            m_dwEAXProperties |= CSOUNDPROPERTIES_EAX_SUPPORTS_VMANAGEMENT_MODE;
            SetVManagmentMode(1);
        }
    }

    if (SUCCEEDED(m_pKsPropertySet->QuerySupport(stru_8BD7C8, DSPROPERTY_EAX_ALL, &support))) {
        if ((support & KSPROPERTY_SUPPORT_SETGET) == KSPROPERTY_SUPPORT_SETGET) {
            m_dwEAXProperties |= CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT;
            SetEnvironmentPreset(EAX_ENVIRONMENT_GENERIC);
        }
    }

    if (SUCCEEDED(m_pKsPropertySet->QuerySupport(stru_8BD7E8, DSPROPERTY_EAX_REVERBMIX, &support))) {
        if ((support & KSPROPERTY_SUPPORT_SETGET) == KSPROPERTY_SUPPORT_SETGET) {
            m_dwEAXProperties |= CSOUNDPROPERTIES_EAX_SUPPORTS_REVERBMIX;
        } else {
            return 0;
        }
    }

    return m_dwEAXProperties;
}

// #binary-identical
// 0x7C22D0
void CSoundProperties::Uninit()
{
    if (m_pKsPropertySet != NULL) {
        m_pKsPropertySet->Release();
    }
    m_pKsPropertySet = NULL;

    if (m_pSoundBuffer != NULL) {
        m_pSoundBuffer->Release();
    }
    m_pSoundBuffer = NULL;

    m_dwEAXProperties = 0;
}

// NOTE: Inlined.
BOOL CSoundProperties::SetVManagmentMode(int mode)
{
    if ((m_dwEAXProperties & CSOUNDPROPERTIES_EAX_SUPPORTS_VMANAGEMENT_MODE) == 0) {
        return FALSE;
    }

    if (FAILED(m_pKsPropertySet->Set(stru_8BD7D8, 0, NULL, 0, &mode, sizeof(mode)))) {
        return FALSE;
    }

    m_nMode = mode;

    return TRUE;
}

// 0x7C2310
BOOL CSoundProperties::SetEnvironmentPreset(int environment)
{
    if ((m_dwEAXProperties & CSOUNDPROPERTIES_EAX_SUPPORTS_ENVIRONMENT) == 0) {
        return FALSE;
    }

    EAXPRESET properties;
    int preset = g_pChitin->GetSoundEnvironment(properties, environment);
    if (FAILED(m_pKsPropertySet->Set(stru_85E530, 0, NULL, 0, &properties, sizeof(properties)))) {
        return FALSE;
    }

    m_nPreset = preset;

    return TRUE;
}

// 0x7C2370
BOOL CSoundProperties::SetBufferReverbMix(LPDIRECTSOUND3DBUFFER soundBuffer3D, float mix)
{
    BOOL ok = FALSE;

    if ((m_dwEAXProperties & CSOUNDPROPERTIES_EAX_SUPPORTS_REVERBMIX) != 0) {
        if (mix > 1.0) {
            mix = 1.0;
        } else if (mix != -1.0 && mix < 0.0) {
            mix = 0.0;
        }

        IKsPropertySet* pKsPropertySet;
        if (SUCCEEDED(soundBuffer3D->QueryInterface(IID_IKsPropertySet, reinterpret_cast<LPVOID*>(&pKsPropertySet)))) {
            if (SUCCEEDED(pKsPropertySet->Set(stru_8BD7E8, 1, NULL, 0, &mix, sizeof(mix)))) {
                ok = TRUE;
            }
            pKsPropertySet->Release();
        }
    }

    return ok;
}

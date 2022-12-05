#include "CVidMode.h"

#include "CChitin.h"

// 0x8BA322
BYTE CVidMode::NUM_FADE_FRAMES = 20;

// #guess
// 0x8FB968
BOOL CVidMode::bInitialized;

// #binary-identical
// 0x799CB0
CVidMode::CVidMode()
{
    field_18 = 0;
    field_1C = 0;
    field_20 = 0;
    field_24 = 0;
    field_98 = 0;
    field_C2 = 0;
    field_C6 = 0;
    field_CA = 0;
    field_D2 = 0;
    field_DC = 0;
    field_D4 = 0;
    field_D8 = 1;
    field_86 = 0;
    field_E0 = 0;
    field_9C = 0;
    nTickCount = GetTickCount();
    field_94 = 0;
    field_8A = 0;
    field_8E = 0;
    field_A0 = NULL;
    field_E4 = 0;
    field_EC = 0;
    field_E8 = 0;
    field_F0 = 0;
    rgbGlobalTint = 0xFFFFFF;
    field_4 = 0;
    field_8F = 0;
    m_nBrightnessCorrection = 0;
    m_nGammaCorrection = 0;
    field_8 = 0;
    field_C = 0;
    field_10 = 1;
    field_14 = 0;
    m_bFadeTo = 0;
    m_nFade = NUM_FADE_FRAMES;

    bInitialized = TRUE;
}

// #binary-identical
// 0x799EB0
CVidMode::~CVidMode()
{
    bInitialized = FALSE;
}

// 0x795BB0
BOOL CVidMode::CreateSurface(IDirectDrawSurface** lplpDirectDrawSurface, const CSize& cSize)
{
    DDCOLORKEY ddck;
    ddck.dwColorSpaceLowValue = field_1C;
    ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;

    DDSURFACEDESC ddsd = { 0 };
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDCAPS_BLT;
    ddsd.dwWidth = cSize.cx;
    ddsd.dwHeight = cSize.cy;

    if (g_pChitin->cVideo.m_pDirectDraw2->CreateSurface(&ddsd, lplpDirectDrawSurface, NULL) != DD_OK) {
        *lplpDirectDrawSurface = NULL;
        return FALSE;
    }

    (*lplpDirectDrawSurface)->SetColorKey(DDCKEY_SRCBLT, &ddck);

    return TRUE;
}

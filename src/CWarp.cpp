#include "CWarp.h"

#include "CBaldurChitin.h"

// 0x9068FC
CSoundMixer* CWarp::pSoundMixer;

// #guess
// 0x906900
CDimm* CWarp::pDimm;

// 0x906904
CVideo* CWarp::pVideo;

// 0x906908
CChitin* CWarp::pChitin;

// #binary-identical
// 0x7B53C0
CWarp::CWarp()
{
    pLastEngine = NULL;
    pVidMode = NULL;

    // #design-flaw: Changes static variables on every instantiation.
    pChitin = g_pChitin;
    pDimm = &(g_pChitin->cDimm);
    pVideo = &(g_pChitin->cVideo);
    pSoundMixer = &(g_pChitin->cSoundMixer);
}

// #binary-identical
// 0x7B5480
CWarp::~CWarp()
{
    lTimers.RemoveAll();
}

// 0x7B54D0
BOOL CWarp::SetVideoMode(int a1)
{
    CVidMode* pOldVideoMode = pVidMode;
    pVidMode = g_pChitin->cVideo.GetVidMode(a1);
    if (pVidMode != NULL) {
        // #design-flaw: Uses both `g_pChitin` and `CWarp::pChitin`.
        if (this == pChitin->pActiveEngine) {
            pVidMode->ActivateVideoMode(pOldVideoMode, 0, 1);
            g_pChitin->cVideo.cVidBlitter.Init();
        }
    }
    return pVidMode != NULL;
}

// 0x7B5530
void CWarp::SelectEngine(CWarp* pWarp)
{
    g_pChitin->SelectEngine(pWarp);
}

// 0x799E60
void CWarp::InvalidateCursorRect(const CRect& rect)
{
}

// 0x799CA0
void CWarp::EngineActivated()
{
}

// 0x799CA0
void CWarp::EngineDeactivated()
{
}

// 0x799CA0
void CWarp::EngineDestroyed()
{
}

// 0x799CA0
void CWarp::EngineInitialized()
{
}

// 0x0x799CA0
void CWarp::EngineGameInit()
{
}

// 0x0x799CA0
void CWarp::EngineGameUninit()
{
}

// 0x778900
void CWarp::OnLButtonDown(CPoint pt)
{
}

// 0x78E820
SHORT CWarp::GetNumVirtualKeys()
{
    return 0;
}

// 0x78E6E0
CKeyInfo* CWarp::GetVirtualKeys()
{
    return NULL;
}

// 0x78E6E0
BYTE* CWarp::GetVirtualKeysFlags()
{
    return NULL;
}

// 0x799E60
void CWarp::OnKeyDown(SHORT a2)
{
}

// 0x78E730
void CWarp::ResetControls()
{
}

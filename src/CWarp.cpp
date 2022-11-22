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

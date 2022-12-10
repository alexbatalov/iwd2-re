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

// 0x778900
void CWarp::NormalizePanelRect(DWORD nID, CRect& rect)
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

// 0x78E6E0
BOOL CWarp::CheckSystemKeyCtrl()
{
    return FALSE;
}

// 0x799E60
void CWarp::SetSystemKeyCtrl(BOOLEAN bValue)
{
}

// 0x78E6E0
BOOL CWarp::GetCtrlKey()
{
    return FALSE;
}

// 0x78E6E0
BOOL CWarp::CheckSystemKeyShift()
{
    return FALSE;
}

// 0x799E60
void CWarp::SetSystemKeyShift(BOOL bValue)
{
}

// 0x78E6E0
BOOL CWarp::GetShiftKey()
{
    return FALSE;
}

// 0x78E6E0
BOOL CWarp::CheckSystemKeyMenu()
{
    return FALSE;
}

// 0x799E60
void CWarp::SetSystemKeyMenu(BOOL bValue)
{
}

// 0x78E6E0
BOOL CWarp::CheckSystemKeyCapsLock()
{
    return FALSE;
}

// 0x799E60
void CWarp::SetSystemKeyCapsLock(BOOL bValue)
{
}

// 0x78E6E0
BOOL CWarp::GetCapsLockKey()
{
    return FALSE;
}

// 0x78E6E0
BOOL CWarp::GetMenuKey()
{
    return FALSE;
}

// 0x78E6E0
BOOL CWarp::CheckMouseMove()
{
    return FALSE;
}

// 0x778900
void CWarp::OnMouseMove(CPoint pt)
{
}

// 0x78E6E0
BOOL CWarp::CheckMouseLButton()
{
    return FALSE;
}

// 0x778900
void CWarp::OnLButtonDblClk(CPoint pt)
{
}

// 0x778900
void CWarp::OnLButtonDown(CPoint pt)
{
}

// 0x778900
void CWarp::OnLButtonUp(CPoint pt)
{
}

// 0x78E6E0
BOOL CWarp::CheckMouseMButton()
{
    return FALSE;
}

// 0x778900
void CWarp::OnMButtonDblClk(CPoint pt)
{
}

// 0x778900
void CWarp::OnMButtonDown(CPoint pt)
{
}

// 0x778900
void CWarp::OnMButtonUp(CPoint pt)
{
}

// 0x78E6E0
BOOL CWarp::CheckMouseRButton()
{
    return FALSE;
}

// 0x778900
void CWarp::OnRButtonDblClk(CPoint pt)
{
}

// 0x778900
void CWarp::OnRButtonDown(CPoint pt)
{
}

// 0x778900
void CWarp::OnRButtonUp(CPoint pt)
{
}

// 0x78E6E0
BOOL CWarp::CheckMouseWheel()
{
    return FALSE;
}

// 0x7B5450
void CWarp::OnMouseWheel(BOOL bForward, LONG nTicks, DWORD nLines, WORD wFlags)
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

// 0x799E60
void CWarp::EnableEditKeys(SHORT a2)
{
}

// 0x78E730
void CWarp::DisableEditKeys()
{
}

// 0x78E730
void CWarp::ResetControls()
{
}

// 0x799CA0
void CWarp::OnVideoChange()
{
}

// 0x799CA0
void CWarp::TimerAsynchronousUpdate()
{
}

// 0x799CA0
void CWarp::TimerSynchronousUpdate()
{
}

// 0x7B5550
void CWarp::TimerUpdate()
{
    // TODO: Incomplete.
}

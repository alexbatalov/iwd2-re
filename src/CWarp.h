#ifndef CWARP_H_
#define CWARP_H_

#include <afx.h>

#include "CChitin.h"
#include "CDimm.h"
#include "CSoundMixer.h"
#include "CVidMode.h"
#include "CVideo.h"

class CKeyInfo;

class CWarp : public CObject {
public:
    static CSoundMixer* pSoundMixer;
    static CDimm* pDimm;
    static CVideo* pVideo;
    static CChitin* pChitin;

    CWarp();
    /* 0000 */ /* GetRuntimeClass */
    /* 0004 */ ~CWarp() override;
    /* 0008 */ /* Serialize */
    /* 000C */ virtual void InvalidateCursorRect(const CRect& rect);
    /* 0010 */ virtual void NormalizePanelRect(DWORD nID, CRect& rect);
    /* 0014 */ virtual void EngineActivated();
    /* 0018 */ virtual void EngineDeactivated();
    /* 001C */ virtual void EngineDestroyed();
    /* 0020 */ virtual void EngineInitialized();
    /* 0024 */ virtual void EngineGameInit();
    /* 0028 */ virtual void EngineGameUninit();
    /* 002C */ virtual void SelectEngine(CWarp* pWarp);
    /* 0030 */ virtual BOOL CheckSystemKeyCtrl();
    /* 0034 */ virtual void SetSystemKeyCtrl(BOOLEAN bValue);
    /* 0038 */ virtual BOOL GetCtrlKey();
    /* 003C */ virtual BOOL CheckSystemKeyShift();
    /* 0040 */ virtual void SetSystemKeyShift(BOOL bValue);
    /* 0044 */ virtual BOOL GetShiftKey();
    /* 0048 */ virtual BOOL CheckSystemKeyMenu();
    /* 004C */ virtual void SetSystemKeyMenu(BOOL bValue);
    /* 0050 */ virtual BOOL CheckSystemKeyCapsLock();
    /* 0054 */ virtual void SetSystemKeyCapsLock(BOOL bValue);
    /* 0058 */ virtual BOOL GetCapsLockKey();
    /* 005C */ virtual BOOL GetMenuKey();
    /* 0060 */ virtual BOOL CheckMouseMove();
    /* 0064 */ virtual void OnMouseMove(CPoint pt);
    /* 0068 */ virtual BOOL CheckMouseLButton();
    /* 006C */ virtual void OnLButtonDblClk(CPoint pt);
    /* 0070 */ virtual void OnLButtonDown(CPoint pt);
    /* 0074 */ virtual void OnLButtonUp(CPoint pt);
    /* 0078 */ virtual BOOL CheckMouseMButton();
    /* 007C */ virtual void OnMButtonDblClk(CPoint pt);
    /* 0080 */ virtual void OnMButtonDown(CPoint pt);
    /* 0084 */ virtual void OnMButtonUp(CPoint pt);
    /* 0088 */ virtual BOOL CheckMouseRButton();
    /* 008C */ virtual void OnRButtonDblClk(CPoint pt);
    /* 0090 */ virtual void OnRButtonDown(CPoint pt);
    /* 0094 */ virtual void OnRButtonUp(CPoint pt);
    /* 0098 */ virtual BOOL CheckMouseWheel();
    /* 009C */ virtual void OnMouseWheel(BOOL bForward, LONG nTicks, DWORD nLines, WORD wFlags);
    /* 00A0 */ virtual SHORT GetNumVirtualKeys();
    /* 00A4 */ virtual CKeyInfo* GetVirtualKeys();
    /* 00A8 */ virtual BYTE* GetVirtualKeysFlags();
    /* 00AC */ virtual void OnKeyDown(SHORT a2);
    /* 00B0 */ virtual void EnableEditKeys(SHORT a2);
    /* 00B4 */ virtual void DisableEditKeys();
    /* 00B8 */ virtual void ResetControls();
    /* 00BC */ virtual void OnVideoChange();
    /* 00C0 */ virtual void TimerAsynchronousUpdate();
    /* 00C4 */ virtual void TimerSynchronousUpdate();
    /* 00C8 */ virtual void TimerUpdate();

    BOOL SetVideoMode(int a1);

    /* 0004 */ CVidMode* pVidMode; // #guess
    /* 0008 */ CWarp* pLastEngine;
    /* 000C */ CObList lTimers;
};

#endif /* CWARP_H_ */

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
    ~CWarp();

    BOOL SetVideoMode(int a1);

    /* 000C */ virtual void InvalidateCursorRect(const CRect& rect);
    /* 0014 */ virtual void EngineActivated();
    /* 0018 */ virtual void EngineDeactivated();
    /* 001C */ virtual void EngineDestroyed();
    /* 0020 */ virtual void EngineInitialized();
    /* 0024 */ virtual void EngineGameInit();
    /* 0028 */ virtual void EngineGameUninit();
    /* 002C */ virtual void SelectEngine(CWarp* pWarp);
    /* 0070 */ void OnLButtonDown(CPoint pt);
    /* 00A0 */ SHORT GetNumVirtualKeys();
    /* 00A4 */ CKeyInfo* GetVirtualKeys();
    /* 00A8 */ BYTE* GetVirtualKeysFlags();
    /* 00AC */ void OnKeyDown(SHORT a2);
    /* 00B8 */ virtual void ResetControls();

    /* 0004 */ CVidMode* pVidMode; // #guess
    /* 0008 */ CWarp* pLastEngine;
    /* 000C */ CObList lTimers;
};

#endif /* CWARP_H_ */

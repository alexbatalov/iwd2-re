#ifndef CRESUI_H_
#define CRESUI_H_

#include "mfc.h"

#include "BalDataTypes.h"
#include "CRes.h"

class CResUI : public CRes {
public:
    CResUI();
    ~CResUI() override;

    void* Demand();
    UI_PANELHEADER* GetPanel(UINT nPanel);
    int GetPanelNo();
    UI_CONTROL* GetControl(UINT nPanel, UINT nControl);
    int GetControlNo(UINT nPanel);
    int Release();

    /* 0050 */ UI_HEADER* m_pHeader;
    /* 0054 */ UI_PANELHEADER* m_pPanels;
    /* 0058 */ UI_CONTROLTABLEENTRY* m_pControlTable;
    /* 005C */ BOOL m_bParsed;
};

#endif /* CRESUI_H_ */

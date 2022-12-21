#include "CResUI.h"

// 0x4013B0
CResUI::CResUI()
{
    m_bParsed = FALSE;
    m_pHeader = NULL;
    m_pPanels = NULL;
    m_pControlTable = NULL;
}

// 0x4013F0
CResUI::~CResUI()
{
}

// 0x401400
void* CResUI::Demand()
{
    void* pData = CRes::Demand();
    if (!m_bParsed || GetDemands() <= 1) {
        if (pData != NULL) {
            m_pHeader = reinterpret_cast<UI_HEADER*>(pData);
            if (m_pHeader->nFileType == 'CHUI' && m_pHeader->nFileVersion == 'V1  ') {
                m_pPanels = reinterpret_cast<UI_PANELHEADER*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nOffsetToPanelTable);
                m_pControlTable = reinterpret_cast<UI_CONTROLTABLEENTRY*>(reinterpret_cast<unsigned char*>(pData) + m_pHeader->nOffsetToControlTable);
                m_bParsed = TRUE;
            }
        }

        if (!m_bParsed) {
            return NULL;
        }
    }

    return pData;
}

// 0x401460
UI_PANELHEADER* CResUI::GetPanel(UINT nPanel)
{
    if (!m_bParsed) {
        return NULL;
    }

    if (nPanel >= m_pHeader->nPanels) {
        return NULL;
    }

    return &(m_pPanels[nPanel]);
}

// 0x4014A0
int CResUI::GetPanelNo()
{
    if (!m_bParsed) {
        return 0;
    }

    return m_pHeader->nPanels;
}

// 0x4014C0
UI_CONTROL* CResUI::GetControl(UINT nPanel, UINT nControl)
{
    if (!m_bParsed) {
        return NULL;
    }

    if (nPanel >= m_pHeader->nPanels) {
        return NULL;
    }

    UI_PANELHEADER* pPanel = &(m_pPanels[nPanel]);
    if (nControl >= pPanel->nControls) {
        return NULL;
    }

    return reinterpret_cast<UI_CONTROL*>(reinterpret_cast<unsigned char*>(m_pHeader) + m_pControlTable[pPanel->nFirstControl + nControl].nControlOffset);
}

// 0x401520
int CResUI::GetControlNo(UINT nPanel)
{
    if (!m_bParsed) {
        return 0;
    }

    if (nPanel >= m_pHeader->nPanels) {
        return 0;
    }

    return m_pPanels[nPanel].nControls;
}

// 0x401BA0
int CResUI::Release()
{
    int rc = CRes::Release();
    if (GetDemands() <= 0) {
        m_bParsed = FALSE;
        m_pHeader = NULL;
        m_pPanels = NULL;
        m_pControlTable = NULL;
    }
    return rc;
}

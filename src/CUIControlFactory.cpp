#include "CUIControlBase.h"

#include "CUIManager.h"
#include "CUIPanel.h"
#include "CUtil.h"

// 0x76D370
CUIControlBase* CUIControlBase::CreateControl(CUIPanel* pPanel, UI_CONTROL* controlInfo)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
    // __LINE__: 106
    UTIL_ASSERT(controlInfo != NULL);

    // TODO: Incomplete.

    if (controlInfo->nID >= 0xFFFFFFF) {
    }

    if (pPanel->m_pManager->m_cResRef == "START") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIMOVIE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUILOAD") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISAVE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICHAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICONN") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIMP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIW" || pPanel->m_pManager->m_cResRef == "GUIW08" || pPanel->m_pManager->m_cResRef == "GUIW10" || pPanel->m_pManager->m_cResRef == "GUIW12" || pPanel->m_pManager->m_cResRef == "GUIW16" || pPanel->m_pManager->m_cResRef == "GUIW20") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISTORE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIOPT") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIJRNL") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIINV") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIREC") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISPL" || pPanel->m_pManager->m_cResRef == "GUISPL08") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIMAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIWMAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICG") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIKEYS") {
    }

    return NULL;
}

#include "CUIControlBase.h"

#include "CScreenConnection.h"
#include "CUIControlLabel.h"
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
        return new CUIControlLabel(pPanel, reinterpret_cast<UI_CONTROL_LABEL*>(controlInfo));
    }

    if (pPanel->m_pManager->m_cResRef == "START") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIMOVIE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUILOAD") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISAVE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICHAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICONN") {
        switch (pPanel->m_nID) {
        case 0:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonConnectionGameMode(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonConnectionQuitGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonConnectionNewGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionQuickLoad(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonConnectionLoadGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonConnectionJoinGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 1:
            switch (controlInfo->nID) {
            case 5:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 3:
            switch (controlInfo->nID) {
            case 5:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 4:
            switch (controlInfo->nID) {
            case 14:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 15:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 5:
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 6:
            switch (controlInfo->nID) {
            case 6:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 7:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 8:
            switch (controlInfo->nID) {
            case 6:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 11:
            switch (controlInfo->nID) {
            case 3:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 12:
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 23:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 24:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        case 25:
            switch (controlInfo->nID) {
            case 3:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                break;
            }
            break;
        default:
            break;
        }
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

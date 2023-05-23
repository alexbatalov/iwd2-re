#include "CUIControlFactory.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CInfGame.h"
#include "CScreenChapter.h"
#include "CScreenCharacter.h"
#include "CScreenConnection.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenKeymaps.h"
#include "CScreenLoad.h"
#include "CScreenMap.h"
#include "CScreenMovies.h"
#include "CScreenOptions.h"
#include "CScreenSpellbook.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CUIControlLabel.h"
#include "CUIControlScrollBar.h"
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
        switch (pPanel->m_nID) {
        case 1:
            // 0x76D661
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                // NOTE: Unclear why movies use store portraits?
                return new CUIControlPortraitStore(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                // NOTE: Uninline.
                return new CUIControlButton77DCC0(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
            // 0x76D547
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplayMovies(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 1:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 2:
                return new CUIControlButtonMoviesPlay(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonMoviesCredits(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonMoviesDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUILOAD") {
        // 0x76D7BF
        switch (pPanel->m_nID) {
        case 0:
            // 0x76D8D8
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonLoadScreenShot(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 22:
                return new CUIControlButtonLoadCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 23:
                return new CUIControlScrollBarLoadGames(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
                return new CUIControlButtonLoadPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
                return new CUIControlButtonLoadLoad(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 60:
            case 61:
            case 62:
            case 63:
            case 64:
                return new CUIControlButtonLoadDelete(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
            case 2:
                return new CUIControlButtonLoadError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 10:
                return new CUIControlButtonLoadError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // NOTE: Strange case - creating scrollbar in default section.
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUISAVE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICHAP") {
        // 0x76DD0D
        switch (pPanel->m_nID) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonChapterDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlTextDisplayChapter(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 3:
                return new CUIControlButtonChapterReplay(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUICONN") {
        // 0x76DDE8
        switch (pPanel->m_nID) {
        case 0:
            // 0x76DE2E
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
            case 8:
                return new CUIControlButtonGeneralOptionsFromMainMenu(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonConnectionJoinGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            // 0x76E017
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 10:
                return new CUIControlButtonConnectionProtocolProtocol(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 8:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 3:
            // 0x76E115
            switch (controlInfo->nID) {
            case 3:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 8:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 4:
            // 0x76E228
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
                return new CUIControlButtonConnectionSerialPort(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                return new CUIControlButtonConnectionSerialBaudRate(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 15:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 5:
            // 0x76E2E1
            switch (controlInfo->nID) {
            case 1:
                // TODO: Incomplete.
                return NULL;
            case 2:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                // TOOD: Incomplete.
                return NULL;
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 6:
            // 0x76E3DC
            switch (controlInfo->nID) {
            case 0:
                // TODO: Incomplete.
                return NULL;
            case 1:
                // TODO: Incomplete.
                return NULL;
            case 4:
                // TODO: Incomplete.
                return NULL;
            case 6:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                // TODO: Incomplete.
                return NULL;
            case 13:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 14:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 15:
                // TODO: Incomplete.
                return NULL;
            }
            break;
        case 7:
            // 0x76E56C
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                // TODO: Incomplete.
                return NULL;
            default:
                break;
            }
            break;
        case 8:
            // 0x76E5ED
            switch (controlInfo->nID) {
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                // TODO: Incomplete.
                return NULL;
            case 6:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 11:
            // 0x76E6D0
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlTextDisplayConnectionTCPIPSessions(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 12:
            // 0x76E7D0
            switch (controlInfo->nID) {
            case 1:
                // TODO: Incomplete.
                return NULL;
            case 2:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 19:
        case 20:
        case 22:
            // 0x76E8ED
            if (controlInfo->nID == 0) {
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            } else if (controlInfo->nID < CSCREENCONNECTION_ERROR_BUTTONS + 1) {
                return new CUIControlButtonConnectionErrorButton(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            } else {
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 947
                UTIL_ASSERT(FALSE);
            }
            break;
        case 21:
            // 0x76E868
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
                return new CUIControlButtonConnectionLobbyMenu(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 5:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 23:
            // 0x76E979
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 24:
            // 0x76E9FE
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
            case 5:
            case 6:
                // TODO: Incomplete.
                return NULL;
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 25:
            // 0x76EAD7
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
            case 2:
                // TODO: Incomplete.
                return NULL;
            case 3:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIMP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIW" || pPanel->m_pManager->m_cResRef == "GUIW08" || pPanel->m_pManager->m_cResRef == "GUIW10" || pPanel->m_pManager->m_cResRef == "GUIW12" || pPanel->m_pManager->m_cResRef == "GUIW16" || pPanel->m_pManager->m_cResRef == "GUIW20") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISTORE") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIOPT") {
        // 0x77052B
        switch (pPanel->m_nID) {
        case 0:
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralSpellbook(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralJournal(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonGeneralMap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonGeneralCharacter(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonClock(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonRest(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlButtonGeneralMultiPlayer(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlButtonAI(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlPortraitGeneral(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonRest(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                return new CUIControlButton77DCC0(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
            switch (controlInfo->nID) {
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 13:
            case 14:
                return new CUIControlButtonOptionsGameCommand(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
        case 4:
        case 5:
        case 50:
            if (controlInfo->nID < CSCREENOPTIONS_ERROR_BUTTONS) {
                return new CUIControlButtonOptionsError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            } else if (controlInfo->nID == 3) {
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 6:
            switch (controlInfo->nID) {
            case 3:
            case 22:
                return new CUIControlSliderOptionsSlider(pPanel, reinterpret_cast<UI_CONTROL_SLIDER*>(controlInfo));
            case 5:
            case 6:
            case 7:
                return new CUIControlButtonOptionsRadio(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
            case 40:
            case 41:
            case 42:
            case 51:
            case 56:
            case 57:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 21:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 32:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 33:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 34:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 35:
            case 36:
            case 37:
            case 38:
            case 44:
            case 46:
            case 48:
            case 50:
            case 52:
            case 54:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 7:
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 22:
                return new CUIControlSliderOptionsSlider(pPanel, reinterpret_cast<UI_CONTROL_SLIDER*>(controlInfo));
            case 13:
                return new CUIControlButtonOptionsGameCommand(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 15:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 28:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 24:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 25:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 26:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 8:
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
            case 12:
                return new CUIControlSliderOptionsSlider(pPanel, reinterpret_cast<UI_CONTROL_SLIDER*>(controlInfo));
            case 5:
            case 6:
                return new CUIControlButtonOptionsGameCommand(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
            case 19:
            case 42:
            case 47:
            case 50:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 20:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 27:
            case 44:
            case 46:
            case 49:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 40:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 41:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 9:
            switch (controlInfo->nID) {
            case 8:
            case 9:
                return new CUIControlSliderOptionsSlider(pPanel, reinterpret_cast<UI_CONTROL_SLIDER*>(controlInfo));
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 26:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 27:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 28:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 29:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 10:
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 13:
            case 25:
            case 26:
            case 30:
            case 33:
            case 36:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 15:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 16:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 24:
            case 28:
            case 31:
            case 34:
            case 37:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 12:
            switch (controlInfo->nID) {
            case 5:
            case 6:
            case 7:
                return new CUIControlButtonOptionsSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
            case 9:
            case 10:
            case 58:
            case 59:
            case 60:
                return new CUIControlButtonOptionsRadio(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 16:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 17:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 18:
            case 19:
            case 20:
            case 21:
            case 57:
                return new CUIControlButtonOptionsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 24:
                return new CUIControlButtonOptionsPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 25:
                return new CUIControlButtonOptionsPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 13:
            switch (controlInfo->nID) {
            case 7:
            case 8:
            case 9:
            case 11:
            case 13:
            case 14:
                return new CUIControlButtonOptionsGameCommand(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        default:
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIJRNL") {
        // 0x770EEA
        switch (pPanel->m_nID) {
        case 0:
            // 0x770F2D
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralSpellbook(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonGeneralMap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonGeneralCharacter(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlButtonGeneralOptions(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonClock(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonRest(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlButtonGeneralMultiPlayer(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlButtonAI(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            // 0x77114F
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlPortraitGeneral(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonRest(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                return new CUIControlButton77DCC0(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
            // 0x7711EB
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlTextDisplayJournal(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 3:
            case 4:
                return new CUIControlButtonJournalScroll(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                // TODO: Incomplete.
                return NULL;
            }
            break;
        case 7:
        case 8:
            // 0x77135F
            switch (controlInfo->nID) {
            case 0:
            case 1:
                return new CUIControlButtonJournalError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 3110
                UTIL_ASSERT(FALSE);
            }
            break;
        case 9:
            // 0x7712F8
            switch (controlInfo->nID) {
            case 0:
                // TODO: Incomplete.
                return NULL;
            case 1:
            case 2:
            case 3:
            case 4:
                // TODO: Incomplete.
                return NULL;
            }
            break;
        case 50:
            // 0x7713BF
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
                return new CUIControlButtonJournalError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIINV") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIREC") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISPL" || pPanel->m_pManager->m_cResRef == "GUISPL08") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIMAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIWMAP") {
    } else if (pPanel->m_pManager->m_cResRef == "GUICG") {
    } else if (pPanel->m_pManager->m_cResRef == "GUIKEYS") {
        switch (pPanel->m_nID) {
        case 0:
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonKeymap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 6289
                UTIL_ASSERT(FALSE);
            }
            break;
        case 1:
            if (controlInfo->nID == 0) {
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            } else if (controlInfo->nID < CSCREENKEYMAPS_ERROR_BUTTONS + 1) {
                return new CUIControlButtonKeymap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        }
    }

    return NULL;
}

// 0x7788D0
CUIControlButtonHotArea::CUIControlButtonHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x778960
CUIControlButtonHotArea::~CUIControlButtonHotArea()
{
}

// 0x799E20
BOOL CUIControlButtonHotArea::Render(BOOL bForce)
{
    return FALSE;
}

// 0x778910
BOOL CUIControlButtonHotArea::OnLButtonDown(CPoint pt)
{
    if (!m_bActive || (m_nMouseButtons & 1) == 0) {
        return FALSE;
    }

    OnHotAreaClick(pt);

    return TRUE;
}

// 0x778900
void CUIControlButtonHotArea::OnHotAreaClick(CPoint pt)
{
}

// 0x7798A0
CUIControlButtonOptionsHotArea::CUIControlButtonOptionsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x7798F0
CUIControlButtonOptionsHotArea::~CUIControlButtonOptionsHotArea()
{
}

// 0x779BC0
CUIControlTextDisplayJournal::CUIControlTextDisplayJournal(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo)
    : CUIControlTextDisplay(panel, controlInfo, TRUE)
{
}

// 0x603670
CUIControlTextDisplayJournal::~CUIControlTextDisplayJournal()
{
}

// 0x71E750
void CUIControlTextDisplayJournal::OnButtonLClick(CPoint pt)
{
}

// NOTE: Inlined.
CUIControlPortraitBase::CUIControlPortraitBase(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons)
    : CUIControlButton(panel, controlInfo, nMouseButtons, 0)
{
}

// NOTE: Inlined.
CUIControlPortraitBase::~CUIControlPortraitBase()
{
}

// 0x779CB0
CUIControlPortraitGeneral::CUIControlPortraitGeneral(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlPortraitBase(panel, controlInfo, LBUTTON | RBUTTON)
{
}

// 0x779D50
CUIControlPortraitGeneral::~CUIControlPortraitGeneral()
{
}

// 0x635200
void CUIControlPortraitGeneral::OnLButtonClick(CPoint pt)
{
    static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnPortraitLClick(m_nID);
}

// 0x779CF0
void CUIControlPortraitGeneral::OnLButtonDoubleClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;
    if (g_pBaldurChitin->pActiveEngine == pMap) {
        pMap->OnPortraitLDblClick(pMap->GetSelectedCharacter());
    }
}

// 0x635040
void CUIControlPortraitGeneral::OnRButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;
    pWorld->OnPortraitLClick(static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->GetSelectedCharacter());
    g_pBaldurChitin->m_pObjectGame->OnPortraitLClick(m_nID);
    g_pBaldurChitin->m_pObjectGame->OnPortraitLDblClick(m_nID);
    m_pPanel->m_pManager->m_pWarp->SelectEngine(pWorld);
}

// 0x77A170
CUIControlButtonAI::CUIControlButtonAI(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_nNormalFrame++;
    m_nToolTipHotKeyIndex1 = 27;
    m_nToolTipStrRef = 15918;
    m_cVidCell.FrameSet(m_nNormalFrame);
}

// 0x77A210
CUIControlButtonAI::~CUIControlButtonAI()
{
}

// 0x77B410
CUIControlButtonRest::CUIControlButtonRest(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_nToolTipHotKeyIndex1 = 29;
    m_nToolTipStrRef = 11942;
}

// 0x77B470
CUIControlButtonRest::~CUIControlButtonRest()
{
}

// 0x77B510
void CUIControlButtonRest::OnLButtonClick(CPoint pt)
{
    static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnRestButtonClick();
}

// 0x77CD30
CUIControlButtonGeneralBase::CUIControlButtonGeneralBase(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton3State(panel, controlInfo, LBUTTON, 0)
{
    m_nNotSelectedFrame = m_nNormalFrame;
    m_nSelectedFrame = m_nNotSelectedFrame / 2 + 20;
    field_66E = NULL;
}

// 0x77CDB0
CUIControlButtonGeneralBase::~CUIControlButtonGeneralBase()
{
}

// 0x77CE50
void CUIControlButtonGeneralBase::OnLButtonClick(CPoint pt)
{
    static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(m_nID);
}

// 0x77CE70
CUIControlButtonGeneralWorld::CUIControlButtonGeneralWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 2;
    m_nToolTipStrRef = 16313;
    field_66E = g_pBaldurChitin->m_pEngineWorld;
}

// 0x77CF10
CUIControlButtonGeneralWorld::~CUIControlButtonGeneralWorld()
{
}

// 0x77CFB0
void CUIControlButtonGeneralWorld::OnLButtonClick(CPoint pt)
{
    static_cast<CBaldurEngine*>(g_pBaldurChitin->pActiveEngine)->OnLeftPanelButtonClick(0);
}

// 0x77CFD0
CUIControlButtonGeneralInventory::CUIControlButtonGeneralInventory(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 0;
    m_nToolTipStrRef = 16307;
    field_66E = g_pBaldurChitin->m_pEngineInventory;
}

// 0x77D070
CUIControlButtonGeneralInventory::~CUIControlButtonGeneralInventory()
{
}

// 0x77D110
CUIControlButtonGeneralMap::CUIControlButtonGeneralMap(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 4;
    m_nToolTipStrRef = 16310;
    field_66E = g_pBaldurChitin->m_pEngineMap;
}

// 0x77D1B0
CUIControlButtonGeneralMap::~CUIControlButtonGeneralMap()
{
}

// 0x77D250
CUIControlButtonGeneralJournal::CUIControlButtonGeneralJournal(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 3;
    m_nToolTipStrRef = 16308;
    field_66E = g_pBaldurChitin->m_pEngineJournal;
}

// 0x77D2F0
CUIControlButtonGeneralJournal::~CUIControlButtonGeneralJournal()
{
}

// 0x77D390
CUIControlButtonGeneralCharacter::CUIControlButtonGeneralCharacter(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 1;
    m_nToolTipStrRef = 16306;
    field_66E = g_pBaldurChitin->m_pEngineCharacter;
}

// 0x77D430
CUIControlButtonGeneralCharacter::~CUIControlButtonGeneralCharacter()
{
}

// 0x77D4D0
CUIControlButtonGeneralSpellbook::CUIControlButtonGeneralSpellbook(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 5;
    m_nToolTipStrRef = 16309;
    field_66E = g_pBaldurChitin->m_pEngineSpellbook;
}

// 0x77D570
CUIControlButtonGeneralSpellbook::~CUIControlButtonGeneralSpellbook()
{
}

// 0x77D610
CUIControlButtonGeneralOptions::CUIControlButtonGeneralOptions(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 6;
    m_nToolTipStrRef = 16311;
    field_66E = g_pBaldurChitin->m_pEngineOptions;
}

// 0x77D6B0
CUIControlButtonGeneralOptions::~CUIControlButtonGeneralOptions()
{
}

// 0x77D750
void CUIControlButtonGeneralOptions::OnLButtonClick(CPoint pt)
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
    // __LINE__: 8988
    UTIL_ASSERT(pOptions != NULL);

    pOptions->m_bFromMainMenu = FALSE;
    g_pBaldurChitin->m_pObjectGame->LoadOptions();
    g_pBaldurChitin->m_pEngineConnection->SelectEngine(pOptions);
}

// NOTE: Inlined in `CUIControlBase::CreateControl` (0x76DF8B);
CUIControlButtonGeneralOptionsFromMainMenu::CUIControlButtonGeneralOptionsFromMainMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    STR_RES strRes;
    g_pBaldurChitin->m_cTlkTable.Fetch(13905, strRes);
    SetText(strRes.szText);

    field_66E = g_pBaldurChitin->m_pEngineOptions;
}

// 0x77D7D0
CUIControlButtonGeneralOptionsFromMainMenu::~CUIControlButtonGeneralOptionsFromMainMenu()
{
}

// 0x77D870
void CUIControlButtonGeneralOptionsFromMainMenu::OnLButtonClick(CPoint pt)
{
    CScreenOptions* pOptions = g_pBaldurChitin->m_pEngineOptions;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
    // __LINE__: 9050
    UTIL_ASSERT(pOptions != NULL);

    pOptions->m_bFromMainMenu = TRUE;
    g_pBaldurChitin->m_pObjectGame->LoadOptions();
    g_pBaldurChitin->m_pEngineConnection->SelectEngine(pOptions);
}

// 0x77D8D0
CUIControlButtonGeneralMultiPlayer::CUIControlButtonGeneralMultiPlayer(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    m_nToolTipHotKeyIndex1 = 7;
    m_nToolTipStrRef = 16312;
    field_66E = g_pBaldurChitin->m_pEngineOptions;
}

// 0x77D960
CUIControlButtonGeneralMultiPlayer::~CUIControlButtonGeneralMultiPlayer()
{
}

// 0x77DCC0
CUIControlButton77DCC0::CUIControlButton77DCC0(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 0)
{
    SetNeedAsyncUpdate();

    CSize frameSize;
    m_cVidCell.GetCurrentFrameSize(frameSize, FALSE);

    // TODO: Check.
    field_668 = frameSize.cx & 0xFF;
    field_666 = 0;

    InvalidateRect();
}

// 0x77DD70
CUIControlButton77DCC0::~CUIControlButton77DCC0()
{
}

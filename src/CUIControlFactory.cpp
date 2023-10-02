#include "CUIControlFactory.h"

#include "CBaldurChitin.h"
#include "CBaldurEngine.h"
#include "CGameSprite.h"
#include "CInfGame.h"
#include "CScreenChapter.h"
#include "CScreenCharacter.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenKeymaps.h"
#include "CScreenLoad.h"
#include "CScreenMap.h"
#include "CScreenMovies.h"
#include "CScreenMultiPlayer.h"
#include "CScreenOptions.h"
#include "CScreenSave.h"
#include "CScreenSinglePlayer.h"
#include "CScreenSpellbook.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CUIControlEditMultiLine.h"
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
        // 0x76DA1A
        switch (pPanel->m_nID) {
        case 0:
            // 0x76DA61
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonSaveScreenShot(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 22:
                return new CUIControlButtonSaveCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 23:
                return new CUIControlScrollBarSaveGames(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
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
                return new CUIControlButtonSavePortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
                return new CUIControlButtonSaveSave(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 60:
            case 61:
            case 62:
            case 63:
            case 64:
                return new CUIControlButtonSaveDelete(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            // 0x76DBA7
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonSaveScreenShot(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                // TODO: Incomplete.
                return NULL;
            case 7:
                return new CUIControlButtonSavePopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonSavePopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
                return new CUIControlButtonSavePortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
        case 3:
            // 0x76DC86
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
            case 2:
                return new CUIControlButtonSaveError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        }
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
            case 2:
                return new CUIControlTextDisplayConnectionModems(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
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
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_TCP_IP_ADDRESS);
            case 2:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlTextDisplayConnection604E90(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 6:
            // 0x76E3DC
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_SESSION_NAME);
            case 1:
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_PLAYER_NAME);
            case 4:
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_SESSION_PASSWORD);
            case 6:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonConnectionCreateGameNewGame(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 14:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 15:
                return new CUIControlButtonConnection604C30(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_SESSION_PASSWORD);
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
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_PLAYER_NAME);
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
                return new CUIControlEditConnectionWithDefault(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo), CScreenConnection::DEFAULT_PHONE_NUMBER);
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
                return new CUIControlButtonConnection6052A0(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
                return new CUIControlButtonConnection605570(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonConnectionPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIMP") {
        // 0x76EB90
        switch (pPanel->m_nID) {
        case 0:
        case 9:
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonMultiPlayerReady(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                return new CUIControlButtonMultiPlayerPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                return new CUIControlButtonMultiPlayerPlayer(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
                return new CUIControlButtonMultiPlayerCharacter(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 25:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 26:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 27:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 28:
                return new CUIControlButtonMultiPlayerDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 29:
                return new CUIControlButtonMultiPlayerOptions(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 30:
                return new CUIControlButtonMultiPlayerLogout(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 43:
                return new CUIControlButtonMultiPlayerModify(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
                return new CUIControlButtonMultiPlayerPermissionsKick(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
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
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
                return new CUIControlButtonMultiPlayerPermissionsPermission(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 61:
                return new CUIControlButtonMultiPlayerPermissionsListen(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 62:
                return new CUIControlButtonMultiPlayerPermissionsOptions(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 63:
                return new CUIControlButtonMultiPlayerPermissionsDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 64:
            case 65:
            case 66:
            case 67:
            case 68:
            case 69:
            case 70:
                return new CUIControlButtonHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 72:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 73:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 74:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            }
            break;
        case 2:
            switch (controlInfo->nID) {
            case 2:
            case 3:
            case 4:
                return new CUIControlButtonMultiPlayerOptionsImport(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonMultiPlayerOptionsCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonMultiPlayerOptionsDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
            case 12:
            case 13:
            case 17:
                return new CUIControlButtonMultiPlayerHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 15:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 18:
                return new CUIControlButtonMultiPlayerSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonMultiPlayerModifyCharacterCreate(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonMultiPlayerModifyCharacterDelete(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonMultiPlayerModifyCharacterCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 4:
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonMultiPlayerModifyPlayerPlayer(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonMultiPlayerModifyCharacterCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 5:
        case 6:
        case 7:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
            case 2:
                return new CUIControlButtonMultiPlayerError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 8:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonMultiPlayerViewCharacterDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUISP") {
        // 0x76F351
        switch (pPanel->m_nID) {
        case 0:
            // 0x76F39F
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonSinglePlayerReady(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
                return new CUIControlButtonSinglePlayerPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
                return new CUIControlButtonSinglePlayerCharacter(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 25:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 26:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 27:
                return new CUIControlEditSinglePlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 28:
                return new CUIControlButtonSinglePlayerDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 30:
                return new CUIControlButtonSinglePlayerLogout(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 43:
                return new CUIControlButtonSinglePlayerModify(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 1409
                UTIL_ASSERT(FALSE);
            }
            break;
        case 3:
            // 0x76F55B
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonSinglePlayerModifyCharacterCreate(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonSinglePlayerModifyCharacterDelete(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonSinglePlayerModifyCharacterCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 1430
                UTIL_ASSERT(FALSE);
            }
            break;
        case 5:
        case 6:
        case 7:
            // 0x76F6B0
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 1:
            case 2:
                return new CUIControlButtonSinglePlayerError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 1472
                UTIL_ASSERT(FALSE);
            }
            break;
        case 8:
            // 0x76F620
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonSinglePlayerViewCharacterDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 10:
            // 0x76F730
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonSinglePlayerPartySelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
                return new CUIControlScrollBarSinglePlayerParties(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 10:
                return new CUIControlButtonSinglePlayerPartyDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonSinglePlayerPartyCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonSinglePlayerPartyModify(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            default:
                // __FILE__: C:\Projects\Icewind2\src\Baldur\UIControlButtons.cpp
                // __LINE__: 1514
                UTIL_ASSERT(FALSE);
            }
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIW" || pPanel->m_pManager->m_cResRef == "GUIW08" || pPanel->m_pManager->m_cResRef == "GUIW10" || pPanel->m_pManager->m_cResRef == "GUIW12" || pPanel->m_pManager->m_cResRef == "GUIW16" || pPanel->m_pManager->m_cResRef == "GUIW20") {
        // 0x776028
        switch (pPanel->m_nID) {
        case 0:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
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
                return new CUIControlButtonGeneralOptions(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonClock(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonSelectAll(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
                return new CUIControlPortraitWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                return new CUIControlButtonAction(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                return new CUIControlButton77DCC0(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            switch (controlInfo->nID) {
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
                return new CUIControlButtonAction(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
        case 4:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButton85C434(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButton85C3BC(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButton85C344(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 6:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlEditLua(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            }
            break;
        case 7:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButton85C2CC(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlTextDisplayDialog(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), FALSE);
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 11:
                return new CUIControlButtonMultiPlayerPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 8:
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                return new CUIControlButtonWorldContainerSlot(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
                return new CUIControlButtonWorldContainerIcon(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 51:
                return new CUIControlButtonWorldContainerClose(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 52:
            case 53:
                return new CUIControlScrollBarWorldContainer(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 54:
                return new CUIControlEncumbrance(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 9:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonDialog(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 17:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonWorldDeathLoad(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonWorldDeathQuit(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 19:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonContractDialogChatMedium(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlTextDisplayDialog(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), FALSE);
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), FALSE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 11:
                return new CUIControlButtonMultiPlayerPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 21:
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonExpandDialogChatSmall(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlTextDisplayDialog(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), FALSE);
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 5:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 6:
                return new CUIControlButton85D45C(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButton85D3E4(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonMultiPlayerPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 22:
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 2:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 3:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
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
                return new CUIControlButtonGeneralOptions(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonClock(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonSelectAll(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonRest(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlButtonGeneralMultiPlayer(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
                return new CUIControlButtonAI(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 50:
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUISTORE") {
        // 0x76F98A
        switch (pPanel->m_nID) {
        case 0:
            // 0x76F9C2
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x76FB47
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlPortraitStore(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x76FCF5
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonStoreBuySellBuy(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonStoreBuySellSell(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                return new CUIControlButtonStoreStoreItem(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlScrollBarStoreStore(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 12:
                return new CUIControlScrollBarStoreGroup(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                return new CUIControlButtonStoreGroupItem(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 44:
                return new CUIControlEncumbrance(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
                return new CUIControlButtonStoreCloseBag(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
                return NULL;
            }
            break;
        case 3:
            // 0x76FBA1
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonStoreBarDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
            case 3:
            case 4:
                return new CUIControlButtonStoreBarPanel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 4:
            // 0x76FEA2
            switch (controlInfo->nID) {
            case 5:
                return new CUIControlButtonStoreIdentifyIdentify(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlScrollBarStoreIdentify(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                return new CUIControlButtonStoreGroupItem(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 23:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 24:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 5:
            // 0x76FF86
            switch (controlInfo->nID) {
            case 5:
                return new CUIControlButtonStoreBuySpellBuy(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlScrollBarStoreSpell(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                return new CUIControlButtonStoreStoreSpell(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 23:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 24:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 7:
            // 0x770078
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
                return new CUIControlButtonStoreRentRoomRoomPicture(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
            case 5:
            case 6:
            case 7:
                return new CUIControlButtonStoreRentRoomRoomSelect(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonStoreRentRoomRent(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 13:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            }
            break;
        case 8:
            // 0x77016D
            switch (controlInfo->nID) {
            case 5:
                return new CUIControlScrollBarStoreBuyDrinksDrink(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 13:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 14:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 40:
            case 41:
            case 42:
            case 43:
            case 44:
            case 45:
            case 46:
            case 47:
                return new CUIControlButtonStoreBuyDrinksDrink(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 10:
        case 11:
            // 0x77021A
            switch (controlInfo->nID) {
            case 0:
            case 1:
                return new CUIControlButtonStoreError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 12:
            // 0x77028B
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonInventoryHistoryIcon(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonStorePopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 7:
                return new CUIControlButtonInventoryHistoryImage(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlButtonStoreOpenBag(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 14:
            // 0x770388
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonSpellbookSpellInfoIcon(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                return new CUIControlButtonStorePopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 15:
            // 0x76FC25
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonStoreBarDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
            case 3:
            case 4:
                return new CUIControlButtonStoreBarPanel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
                return new CUIControlEditMultiPlayerChat(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            }
            break;
        case 20:
            // 0x77041E
            switch (controlInfo->nID) {
            case 0:
                // return new CUIControlButtonStoreRequesterItem(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonStoreRequesterCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonStoreRequesterDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
            case 4:
                return new CUIControlButtonStoreRequesterPlusMinus(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlEditStoreRequesterAmount(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            }
            break;
        }
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
        // 0x771437
        switch (pPanel->m_nID) {
        case 0:
            // 0x77147A
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralSpellbook(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralJournal(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x7715DE
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlPortraitInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x77164E
            switch (controlInfo->nID) {
            case 5:
            case 6:
            case 7:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
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
            case 68:
            case 69:
            case 70:
            case 71:
            case 72:
            case 73:
            case 74:
            case 75:
            case 76:
            case 77:
            case 78:
            case 79:
            case 80:
            case 81:
            case 101:
            case 102:
            case 103:
            case 104:
            case 105:
            case 106:
            case 107:
            case 108:
                return new CUIControlButtonInventorySlot(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
                return new CUIControlButtonInventoryAppearance(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 62:
            case 63:
            case 82:
            case 83:
                return new CUIControlButtonInventoryColor(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 66:
                return new CUIControlScrollBarInventoryGround(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 84:
                return new CUIControlButtonCharacterPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 85:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 86:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 109:
            case 110:
            case 111:
            case 112:
                return new CUIControlButtonInventoryWeaponSet(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            // 0x771EB7
            if (controlInfo->nID <= CRESUI_CONTROLBUTTONID_INVENTORYCOLOR_LASTCOLOR
                || controlInfo->nID == 35) {
                return new CUIControlButtonInventoryColorChoice(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 4:
            // 0x771F04
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonInventoryRequesterItem(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonInventoryRequesterCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonInventoryRequesterDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
            case 4:
                return new CUIControlButtonInventoryRequesterPlusMinus(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlEditInventoryRequesterAmount(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
                break;
            }
            break;
        case 5:
            // 0x772013
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonInventoryHistoryIcon(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonInventoryHistoryDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 7:
                return new CUIControlButtonInventoryHistoryImage(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonInventoryHistoryAbilities(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlButtonInventoryHistoryUse(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 6:
            // 0x772162
            switch (controlInfo->nID) {
            case 1:
            case 2:
            case 3:
                return new CUIControlButtonInventoryAbilitiesAbility(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonInventoryHistoryDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 9:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 10:
                return new CUIControlButtonInventoryHistoryCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
        case 7:
        case 8:
        case 9:
        case 50:
            // 0x772230
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
                return new CUIControlButtonInventoryError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIREC") {
    } else if (pPanel->m_pManager->m_cResRef == "GUISPL" || pPanel->m_pManager->m_cResRef == "GUISPL08") {
        // 0x775B04
        switch (pPanel->m_nID) {
        case 0:
            // 0x775B19
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralJournal(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x775D27
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlPortraitGeneral(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x775DA6
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonCharacterPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
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
            case 46:
            case 47:
            case 48:
            case 49:
            case 50:
            case 51:
            case 52:
            case 53:
                return new CUIControlButtonSpellbookSpell(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 54:
                return new CUIControlScrollBarSpellbookKnownSpells(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 62:
            case 63:
                return new CUIControlButtonSpellbookLevelSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 88:
            case 89:
            case 90:
            case 91:
            case 92:
            case 93:
                return new CUIControlButtonSpellbookClassSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            // 0x775EB5
            switch (controlInfo->nID) {
            case 2:
                return new CUIControlButtonSpellbookSpellInfoIcon(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                return new CUIControlButtonSpellbookPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 4:
        case 5:
            // 0x775F62
            switch (controlInfo->nID) {
            case 0:
            case 1:
                return new CUIControlButtonSpellbookError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 50:
            // 0x775FC5
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
                return new CUIControlButtonSpellbookError(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIMAP") {
        // 0x7739D6
        switch (pPanel->m_nID) {
        case 0:
            // 0x773A1F
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralSpellbook(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralJournal(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x773B94
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
            // 0x773BFE
            // TODO: Incomplete.
            break;
        case 3:
        case 4:
            // 0x773CE0
            // TODO: Incomplete.
            break;
        case 5:
            // 0x773D56
            // TODO: Incomplete.
            break;
        case 50:
            // 0x773E6C
            // TODO: Incomplete.
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUIWMAP") {
        // 0x773EDE
        switch (pPanel->m_nID) {
        case 0:
            // 0x773F1F
            switch (controlInfo->nID) {
            case 4:
                return new CUIControlButtonGeneralSpellbook(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonGeneralInventory(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonGeneralJournal(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonGeneralWorld(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            // 0x774096
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
            // 0x77410B
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonWorldMapDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
                // NOTE: Probably leftover from earlier games.
                return NULL;
            case 4:
                return new CUIControlButtonWorldMapWorldMap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            // 0x77415C
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonWorldMapDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
                return new CUIControlButtonWorldMapScroll(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlButtonWorldMapWorldMap(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 7:
                // TODO: Incomplete.
                return NULL;
            }
            break;
        }
    } else if (pPanel->m_pManager->m_cResRef == "GUICG") {
        // 0x774284
        switch (pPanel->m_nID) {
        case 0:
            // 0x7742D2
            switch (controlInfo->nID) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                return new CUIControlButtonCharGenMenu(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 8:
                return new CUIControlButtonCharGenAccept(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 10:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 11:
                return new CUIControlButtonCharGenBack(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlButtonCharGenPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlButtonCharGenImport(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 15:
                return new CUIControlButtonCharGenCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 16:
                return new CUIControlButtonCharGenBiography(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 1:
            // 0x774484
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 7:
            case 8:
                return new CUIControlButtonCharGenGenderSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 4:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 5:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 6:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 2:
            // 0x774576
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                return new CUIControlButtonCharGenClassSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 15:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 16:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 17:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 3:
            // 0x774883
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                return new CUIControlButtonCharGenAlignmentSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 12:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 13:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 4:
            // 0x774646
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonCharGenAbilitiesReroll(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
                return new CUIControlButtonCharGenAbilitiesPlusMinus(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 28:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 29:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
                return new CUIControlButtonCharGenAbilitiesHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 36:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 37:
                return new CUIControlButtonCharGenAbilitiesStore(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 38:
                return new CUIControlButtonCharGenAbilitiesRecall(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 43:
                return new CUIControlButtonCharGenAbilitiesAllocate(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 5:
            // 0x774940
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlEditCharGen(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 3:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 6:
            // 0x7749D9
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
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
                return new CUIControlButtonCharGenSkillsPlusMinus(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 91:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 92:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 93:
            case 94:
            case 95:
            case 96:
            case 97:
            case 98:
            case 99:
            case 100:
            case 101:
            case 102:
            case 103:
                return new CUIControlButtonCharGenSkillsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 104:
                return new CUIControlScrollBarCharGenSkills(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 105:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 7:
            // 0x774B0D
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                return new CUIControlButtonCharGenKnownArcaneSpellSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 26:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 27:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 29:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 30:
                return new CUIControlButtonCharGen61A130(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 8:
            // 0x774DAF
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
                return new CUIControlButtonCharGenRaceSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 9:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 10:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 11:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 11:
            // 0x774F47
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonCharGenAppearancePortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonCharGenAppearanceLeft(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlButtonCharGenAppearanceRight(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 5:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonCharGenAppearanceCustom(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 12:
            // 0x774E7F
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 13:
                return new CUIControlButtonClericWizardSpecializationSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 11:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 12:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 13:
            // 0x77506B
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonCharGenHairSkinAppearance(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
                return new CUIControlButtonCharGenHairSkinColor(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 13:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 14:
            // 0x775118
            if (controlInfo->nID <= CRESUI_CONTROLBUTTONID_CHARGEN_COLOR_LASTCOLOR
                || controlInfo->nID == 35) {
                return new CUIControlButtonCharGenColorChoice(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 15:
            // 0x77516E
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlScrollBarCharGenHatedRace(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 9:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 10:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 11:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 22:
            case 23:
            case 24:
            case 25:
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
                return new CUIControlButtonCharGenHatedRaceSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 16:
            // 0x774C0F
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                return new CUIControlButtonCharGenMemorizedArcaneSpellSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 26:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 27:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 29:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 17:
            // 0x774CDF
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                return new CUIControlButtonCharGenMemorizedDivineSpellSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 26:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 27:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 29:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 18:
            // 0x775268
            switch (controlInfo->nID) {
            case 0:
            case 1:
                return new CUIControlButtonCharGenPortrait(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
            case 4:
                return new CUIControlTextDisplayCharGenPortraits(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 3:
            case 5:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 6:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 7:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 19:
            // 0x775338
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 10:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 45:
                return new CUIControlTextDisplayCharGenSoundSounds(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 46:
            case 51:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 47:
                return new CUIControlButtonCharGenSoundPlay(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 50:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 20:
            // 0x775432
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlTextDisplayCharGenImportCharacters(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 3:
            case 5:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 4:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 21:
            // 0x7754FA
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlTextDisplayCharGenExportCharacters(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo));
            case 3:
            case 5:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 4:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 7:
                return new CUIControlEditCharGen(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            }
            break;
        case 51:
            // 0x77577C
            switch (controlInfo->nID) {
            case 1:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 3:
                return new CUIControlEditScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 4:
                return new CUIControlEditMultiLineScroller(pPanel, reinterpret_cast<UI_CONTROL_EDIT*>(controlInfo));
            case 5:
                return new CUIControlButtonCharGenBiographyClear(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlButtonCharGenBiographyRevert(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 52:
            // 0x7755EB
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
                return new CUIControlButtonMonkPaladinSpecializationSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 12:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 13:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 14:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 53:
            // 0x7747FD
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 2:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            }
            break;
        case 54:
            // 0x7756B3
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 1:
            case 2:
            case 3:
            case 4:
                return new CUIControlButtonCharGenSubRaceSelection(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 6:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 7:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 8:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        case 55:
            // 0x7758A0
            switch (controlInfo->nID) {
            case 0:
                return new CUIControlButtonCharGenPopupDone(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
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
                return new CUIControlButtonCharGenFeatsPlusMinus(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
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
            case 55:
            case 56:
            case 57:
            case 58:
            case 59:
            case 60:
            case 61:
            case 62:
            case 63:
            case 64:
            case 65:
            case 66:
            case 67:
            case 68:
            case 69:
            case 70:
            case 71:
            case 72:
            case 73:
            case 74:
            case 75:
            case 76:
            case 77:
            case 78:
            case 79:
            case 80:
            case 81:
            case 82:
            case 83:
            case 84:
            case 85:
            case 86:
            case 87:
            case 88:
            case 89:
            case 90:
                return new CUIControlButtonCharGenFeatsCircle(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 91:
                return new CUIControlScrollBar(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 92:
                return new CUIControlTextDisplay(pPanel, reinterpret_cast<UI_CONTROL_TEXTDISPLAY*>(controlInfo), TRUE);
            case 93:
            case 94:
            case 95:
            case 96:
            case 97:
            case 98:
            case 99:
            case 100:
            case 101:
            case 102:
            case 103:
                return new CUIControlButtonCharGenFeatsHotArea(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            case 104:
                return new CUIControlScrollBarCharGenFeats(pPanel, reinterpret_cast<UI_CONTROL_SCROLLBAR*>(controlInfo));
            case 105:
                return new CUIControlButtonCharGenPopupCancel(pPanel, reinterpret_cast<UI_CONTROL_BUTTON*>(controlInfo));
            }
            break;
        }
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

// -----------------------------------------------------------------------------

// 0x778A20
CUIControlButtonCharacterAbilitiesHotArea::CUIControlButtonCharacterAbilitiesHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x778A70
CUIControlButtonCharacterAbilitiesHotArea::~CUIControlButtonCharacterAbilitiesHotArea()
{
}

// -----------------------------------------------------------------------------

// 0x778B10
CUIControlButtonCharacterAppearanceLeft::CUIControlButtonCharacterAppearanceLeft(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x778B60
CUIControlButtonCharacterAppearanceLeft::~CUIControlButtonCharacterAppearanceLeft()
{
}

// -----------------------------------------------------------------------------

// 0x778C00
CUIControlButtonCharacterAppearanceRight::CUIControlButtonCharacterAppearanceRight(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x778C50
CUIControlButtonCharacterAppearanceRight::~CUIControlButtonCharacterAppearanceRight()
{
}

// -----------------------------------------------------------------------------

// 0x778CF0
CUIControlButtonCharacterFeatsHotArea::CUIControlButtonCharacterFeatsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x778D40
CUIControlButtonCharacterFeatsHotArea::~CUIControlButtonCharacterFeatsHotArea()
{
}

// -----------------------------------------------------------------------------

// 0x778DE0
CUIControlButtonCharacterSkillsHotArea::CUIControlButtonCharacterSkillsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x778E30
CUIControlButtonCharacterSkillsHotArea::~CUIControlButtonCharacterSkillsHotArea()
{
}

// -----------------------------------------------------------------------------

// 0x778FC0
CUIControlButtonCharGenPortrait::CUIControlButtonCharGenPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x779050
CUIControlButtonCharGenPortrait::~CUIControlButtonCharGenPortrait()
{
}

// -----------------------------------------------------------------------------

// 0x7790F0
CUIControlButtonCharGenAbilitiesHotArea::CUIControlButtonCharGenAbilitiesHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x779140
CUIControlButtonCharGenAbilitiesHotArea::~CUIControlButtonCharGenAbilitiesHotArea()
{
}

// -----------------------------------------------------------------------------

// 0x7791E0
CUIControlButtonCharGenSkillsHotArea::CUIControlButtonCharGenSkillsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x779230
CUIControlButtonCharGenSkillsHotArea::~CUIControlButtonCharGenSkillsHotArea()
{
}

// -----------------------------------------------------------------------------

// 0x7792D0
CUIControlButtonCharGenAppearancePortrait::CUIControlButtonCharGenAppearancePortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 1)
{
}

// 0x779350
CUIControlButtonCharGenAppearancePortrait::~CUIControlButtonCharGenAppearancePortrait()
{
}

// -----------------------------------------------------------------------------

// 0x7793F0
CUIControlButtonCharGenAppearanceLeft::CUIControlButtonCharGenAppearanceLeft(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x779440
CUIControlButtonCharGenAppearanceLeft::~CUIControlButtonCharGenAppearanceLeft()
{
}

// -----------------------------------------------------------------------------

// 0x7794E0
CUIControlButtonCharGenAppearanceRight::CUIControlButtonCharGenAppearanceRight(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x779530
CUIControlButtonCharGenAppearanceRight::~CUIControlButtonCharGenAppearanceRight()
{
}

// -----------------------------------------------------------------------------

// 0x7795D0
CUIControlButtonCharGenHairSkinAppearance::CUIControlButtonCharGenHairSkinAppearance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
}

// 0x779620
CUIControlButtonCharGenHairSkinAppearance::~CUIControlButtonCharGenHairSkinAppearance()
{
}

// -----------------------------------------------------------------------------

// 0x7796C0
CUIControlButtonCharGenFeatsHotArea::CUIControlButtonCharGenFeatsHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x779710
CUIControlButtonCharGenFeatsHotArea::~CUIControlButtonCharGenFeatsHotArea()
{
}

// -----------------------------------------------------------------------------

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

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlButtonMultiPlayerHotArea::CUIControlButtonMultiPlayerHotArea(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonHotArea(panel, controlInfo)
{
}

// 0x779C10
CUIControlButtonMultiPlayerHotArea::~CUIControlButtonMultiPlayerHotArea()
{
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlPortraitBase::CUIControlPortraitBase(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo, BYTE nMouseButtons)
    : CUIControlButton(panel, controlInfo, nMouseButtons, 0)
{
}

// NOTE: Inlined.
CUIControlPortraitBase::~CUIControlPortraitBase()
{
}

// 0x77AB90
void CUIControlPortraitBase::ActivateToolTip()
{
    LONG nCharacterId = g_pBaldurChitin->GetObjectGame()->GetCharacterSlot(m_nID);
    if (nCharacterId != CGameObjectArray::INVALID_INDEX) {
        CGameSprite* pSprite;

        BYTE rc;
        do {
            rc = g_pBaldurChitin->GetObjectGame()->GetObjectArray()->GetShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                reinterpret_cast<CGameObject**>(&pSprite),
                INFINITE);
        } while (rc == CGameObjectArray::SHARED || rc == CGameObjectArray::DENIED);

        if (rc == CGameObjectArray::SUCCESS) {
            pSprite->SetCharacterToolTip(this);

            g_pBaldurChitin->GetObjectGame()->GetObjectArray()->ReleaseShare(nCharacterId,
                CGameObjectArray::THREAD_ASYNCH,
                INFINITE);
        }
    }
}

// -----------------------------------------------------------------------------

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
    g_pBaldurChitin->GetActiveEngine()->OnPortraitLClick(m_nID);
}

// 0x779CF0
void CUIControlPortraitGeneral::OnLButtonDoubleClick(CPoint pt)
{
    CScreenMap* pMap = g_pBaldurChitin->m_pEngineMap;
    if (g_pBaldurChitin->GetActiveEngine() == pMap) {
        pMap->OnPortraitLDblClick(pMap->GetSelectedCharacter());
    }
}

// 0x635040
void CUIControlPortraitGeneral::OnRButtonClick(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;
    pWorld->OnPortraitLClick(g_pBaldurChitin->GetActiveEngine()->GetSelectedCharacter());
    g_pBaldurChitin->GetObjectGame()->OnPortraitLClick(m_nID);
    g_pBaldurChitin->GetObjectGame()->OnPortraitLDblClick(m_nID);
    m_pPanel->m_pManager->m_pWarp->SelectEngine(pWorld);
}

// 0x77AC40
BOOL CUIControlPortraitGeneral::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    if (!CUIControlButton::Render(bForce)) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;
    g_pBaldurChitin->GetObjectGame()->RenderPortrait(m_nID,
        pt,
        m_size,
        m_bPressed,
        FALSE,
        FALSE,
        m_rDirty,
        m_pPanel->m_pManager->m_bDoubleSize);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x779DF0
CUIControlButtonCharacterPortrait::CUIControlButtonCharacterPortrait(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 1)
{
}

// 0x779E70
CUIControlButtonCharacterPortrait::~CUIControlButtonCharacterPortrait()
{
}

// NOTE: Same as `CUIControlButtonCharGenAppearancePortrait::SetPortrait`.
//
// 0x61D0E0
void CUIControlButtonCharacterPortrait::SetPortrait(const CResRef& resRef)
{
    if (m_portraitResRef != resRef) {
        m_portraitResRef = resRef;
        InvalidateRect();
    }
}

// -----------------------------------------------------------------------------

// 0x779F10
CUIControlPortraitWorld::CUIControlPortraitWorld(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlPortraitBase(panel, controlInfo, LBUTTON | RBUTTON)
{
    m_bHighlighted = FALSE;
}

// 0x779FB0
CUIControlPortraitWorld::~CUIControlPortraitWorld()
{
}

// 0x779F50
void CUIControlPortraitWorld::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->GetObjectGame()->OnPortraitLClick(m_nID);
}

// 0x779F70
void CUIControlPortraitWorld::OnLButtonDoubleClick(CPoint pt)
{
    g_pBaldurChitin->GetObjectGame()->OnPortraitLDblClick(m_nID);
}

// 0x77AFD0
void CUIControlPortraitWorld::OnMouseMove(CPoint pt)
{
    if (IsOver(pt)) {
        if (!m_bPressed) {
            m_bHighlighted = FALSE;
            g_pBaldurChitin->GetObjectGame()->SetTempCursor(4);
            m_cVidCell.FrameSet(m_nPressedFrame);
            m_bPressed = TRUE;

            CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
            renderLock.Lock(INFINITE);
            m_nRenderCount = CUIManager::RENDER_COUNT;
            renderLock.Unlock();
        }
    } else {
        if (m_bPressed) {
            if (m_pPanel->m_pManager->m_nCaptureType == CUIManager::MOUSELBUTTON) {
                m_bHighlighted = TRUE;
                g_pBaldurChitin->GetObjectGame()->SetTempCursor(14);
            }

            m_cVidCell.FrameSet(m_nNormalFrame);
            m_bPressed = FALSE;

            CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
            renderLock.Lock(INFINITE);
            m_nRenderCount = CUIManager::RENDER_COUNT;
            renderLock.Unlock();
        }
    }
}

// 0x77B160
void CUIControlPortraitWorld::OnLButtonUp(CPoint pt)
{
    m_bHighlighted = FALSE;
    g_pBaldurChitin->GetObjectGame()->SetTempCursor(4);

    m_cVidCell.FrameSet(m_nNormalFrame);
    m_bPressed = FALSE;

    CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
    renderLock.Lock(INFINITE);
    m_nRenderCount = CUIManager::RENDER_COUNT;
    renderLock.Unlock();

    if (IsOver(pt)) {
        OnLButtonClick(pt);
    } else if (m_pPanel->IsOver(m_pPanel->m_ptOrigin + pt)) {
        // NOTE: Unsigned compare.
        for (DWORD nID = 0; nID < static_cast<DWORD>(g_pBaldurChitin->GetObjectGame()->GetNumCharacters()); nID++) {
            CUIControlPortraitWorld* pPortrait = static_cast<CUIControlPortraitWorld*>(m_pPanel->GetControl(nID));
            if (pPortrait != NULL
                && nID != m_nID
                && pPortrait->IsOver(pt)) {
                g_pBaldurChitin->GetObjectGame()->SwapCharacters(m_nID, nID);
                g_pBaldurChitin->GetObjectGame()->GetGroup()->Sort();
                pPortrait->InvalidateRect();
                break;
            }
        }
    }
}

// 0x77B310
void CUIControlPortraitWorld::OnRButtonClick(CPoint pt)
{
    g_pBaldurChitin->m_pEngineInventory->OnPortraitLClick(m_nID);
    g_pBaldurChitin->m_pEngineWorld->SelectEngine(g_pBaldurChitin->m_pEngineInventory);
    g_pBaldurChitin->m_pEngineInventory->UnPauseGame();
}

// 0x77B360
BOOL CUIControlPortraitWorld::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return FALSE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return FALSE;
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;
    g_pBaldurChitin->GetObjectGame()->RenderPortrait(m_nID,
        pt,
        m_size,
        m_bPressed,
        m_bHighlighted,
        TRUE,
        m_rDirty,
        m_pPanel->m_pManager->m_bDoubleSize);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x77A050
CUIControlButtonSelectAll::CUIControlButtonSelectAll(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
    m_nToolTipHotKeyIndex1 = 37;
    m_nToolTipStrRef = 10485;
}

// 0x77A0D0
CUIControlButtonSelectAll::~CUIControlButtonSelectAll()
{
}

// 0x77A090
void CUIControlButtonSelectAll::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->GetObjectGame()->SelectAll(TRUE);
}

// -----------------------------------------------------------------------------

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

// 0x77ACF0
void CUIControlButtonAI::OnLButtonClick(CPoint pt)
{
    if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineWorld
        || g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineInventory
        || g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineMap) {

        g_pBaldurChitin->GetObjectGame()->m_bPartyAI = !g_pBaldurChitin->GetObjectGame()->m_bPartyAI;
        if (g_pBaldurChitin->GetObjectGame()->m_bPartyAI) {
            m_nNormalFrame++;
            m_nToolTipStrRef = 15918;
        } else {
            m_nNormalFrame--;
            m_nToolTipStrRef = 15917;
        }

        m_cVidCell.FrameSet(m_nNormalFrame);
        InvalidateRect();

        if (g_pBaldurChitin->GetActiveEngine() == g_pBaldurChitin->m_pEngineWorld) {
            STRREF strText = g_pBaldurChitin->GetObjectGame()->m_bPartyAI
                ? 15918 // "Party AI On"
                : 15917; // "Party AI Off"
            g_pBaldurChitin->m_pEngineWorld->DisplayText(CString(""),
                CBaldurEngine::FetchString(strText),
                RGB(0, 0, 0),
                RGB(63, 255, 12),
                -1,
                FALSE);
        }
    } else {
        InvalidateRect();
    }
}

// 0x77AE50
BOOL CUIControlButtonAI::Render(BOOL bForce)
{
    if (!m_bActive && !m_bInactiveRender) {
        return TRUE;
    }

    if (m_nRenderCount == 0 && !bForce) {
        return TRUE;
    }

    if (m_nRenderCount != 0) {
        CSingleLock renderLock(&(m_pPanel->m_pManager->field_56), FALSE);
        renderLock.Lock(INFINITE);
        m_nRenderCount--;
        renderLock.Unlock();
    }

    CPoint pt = m_pPanel->m_ptOrigin + m_ptOrigin;

    CRect rControlFrame(pt, m_size);

    CRect rClip;
    rClip.IntersectRect(rControlFrame, m_rDirty);

    m_nNormalFrame = g_pBaldurChitin->GetObjectGame()->m_bPartyAI ? 1 : 0;
    m_cVidCell.FrameSet(m_nNormalFrame);

    m_cVidCell.Render(0, pt.x, pt.y, rClip, NULL, 0, 0, -1);

    return TRUE;
}

// -----------------------------------------------------------------------------

// 0x77A2B0
CUIControlButtonAction::CUIControlButtonAction(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON | RBUTTON, 0)
{
}

// 0x77A370
CUIControlButtonAction::~CUIControlButtonAction()
{
}

// 0x77A2F0
void CUIControlButtonAction::OnLButtonClick(CPoint pt)
{
    g_pBaldurChitin->GetObjectGame()->GetButtonArray()->OnLButtonPressed(m_nID - 6);
}

// 0x77A320
void CUIControlButtonAction::OnRButtonClick(CPoint pt)
{
    g_pBaldurChitin->GetObjectGame()->GetButtonArray()->OnRButtonPressed(m_nID - 6);
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlButton85C3BC::CUIControlButton85C3BC(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_nAUCounter = 0;
}

// 0x77A430
CUIControlButton85C3BC::~CUIControlButton85C3BC()
{
}

// 0x77B6F0
BOOL CUIControlButton85C3BC::OnLButtonDown(CPoint pt)
{
    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->OnScrollDown();

    m_nAUCounter = 1;

    return TRUE;
}

// 0x77B730
void CUIControlButton85C3BC::OnLButtonUp(CPoint pt)
{
    CUIControlButton::OnLButtonUp(pt);

    m_nAUCounter = 0;

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->field_A67 = 0;
}

// 0x77B770
void CUIControlButton85C3BC::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
            pText->OnScrollDown();
        } else {
            m_nAUCounter++;
        }
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlButton85C434::CUIControlButton85C434(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_nAUCounter = 0;
}

// 0x77A4D0
CUIControlButton85C434::~CUIControlButton85C434()
{
}

// 0x77E0F0
BOOL CUIControlButton85C434::OnLButtonDown(CPoint pt)
{
    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->OnScrollUp();

    m_nAUCounter = 1;

    return TRUE;
}

// 0x77B7C0
void CUIControlButton85C434::OnLButtonUp(CPoint pt)
{
    CUIControlButton::OnLButtonUp(pt);

    m_nAUCounter = 0;

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->field_A66 = 0;
}

// 0x77B800
void CUIControlButton85C434::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
            pText->OnScrollUp();
        } else {
            m_nAUCounter++;
        }
    }
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlButton85C344::CUIControlButton85C344(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x77A5B0
CUIControlButton85C344::~CUIControlButton85C344()
{
}

// 0x71E750
void CUIControlButton85C344::OnLButtonUp(CPoint pt)
{
    // NOTE: Probably leftover from earlier games.
}

// -----------------------------------------------------------------------------

// NOTE: Inlined.
CUIControlButton85C2CC::CUIControlButton85C2CC(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x77A670
CUIControlButton85C2CC::~CUIControlButton85C2CC()
{
}

// 0x71E750
void CUIControlButton85C2CC::OnLButtonUp(CPoint pt)
{
    // NOTE: Probably leftover from earlier games.
}

// -----------------------------------------------------------------------------

// 0x77A710
CUIControlButtonContractDialogChatMedium::CUIControlButtonContractDialogChatMedium(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x77A760
CUIControlButtonContractDialogChatMedium::~CUIControlButtonContractDialogChatMedium()
{
}

// 0x77B850
void CUIControlButtonContractDialogChatMedium::OnLButtonUp(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    if (IsOver(pt)
        && m_bActive
        && pWorld->m_pActiveDialogDisplay != NULL
        && pWorld->m_pActiveDialogDisplay->m_pPanel->m_nID == pWorld->GetPanel_19_0()) {
        CUIPanel* pNewPanel = m_pPanel->m_pManager->GetPanel(pWorld->GetPanel_21_0());

        m_cVidCell.FrameSet(m_nNormalFrame);
        m_bPressed = FALSE;
        InvalidateRect();

        m_pPanel->SetActive(FALSE);
        pNewPanel->SetActive(TRUE);

        pWorld->m_pActiveDialogDisplay = static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(1));
        pWorld->m_pActiveChatDisplay = static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(3));

        static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(1))->CopyDisplay(static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(1)));
        static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(3))->CopyDisplay(static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3)));

        pNewPanel->InvalidateRect(NULL);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pNewPanel->GetControl(0));
        if (pButton->m_bPressed) {
            pButton->m_cVidCell.FrameSet(pButton->m_nNormalFrame);
            pButton->m_bPressed = FALSE;
            pButton->InvalidateRect();
        }

        pWorld->CopyChatEditBox(m_pPanel, pNewPanel);
    }

    pWorld->GetManager()->InvalidateRect(NULL);
}

// -----------------------------------------------------------------------------

// 0x77A710
CUIControlButtonExpandDialogChatSmall::CUIControlButtonExpandDialogChatSmall(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 0)
{
}

// 0x77A850
CUIControlButtonExpandDialogChatSmall::~CUIControlButtonExpandDialogChatSmall()
{
}

// 0x77BA00
void CUIControlButtonExpandDialogChatSmall::OnLButtonUp(CPoint pt)
{
    CScreenWorld* pWorld = g_pBaldurChitin->m_pEngineWorld;

    if (IsOver(pt)
        && m_bActive
        && pWorld->m_pActiveDialogDisplay != NULL
        && pWorld->m_pActiveDialogDisplay->m_pPanel->m_nID == pWorld->GetPanel_21_0()) {
        CUIPanel* pNewPanel = m_pPanel->m_pManager->GetPanel(pWorld->GetPanel_19_0());

        m_cVidCell.FrameSet(m_nNormalFrame);
        m_bPressed = FALSE;
        InvalidateRect();

        m_pPanel->SetActive(FALSE);
        pNewPanel->SetActive(TRUE);

        pWorld->m_pActiveDialogDisplay = static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(1));
        pWorld->m_pActiveChatDisplay = static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(3));

        static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(1))->CopyDisplay(static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(1)));
        static_cast<CUIControlTextDisplay*>(pNewPanel->GetControl(3))->CopyDisplay(static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3)));

        pNewPanel->InvalidateRect(NULL);

        CUIControlButton* pButton = static_cast<CUIControlButton*>(pNewPanel->GetControl(0));
        if (pButton->m_bPressed) {
            pButton->m_cVidCell.FrameSet(pButton->m_nNormalFrame);
            pButton->m_bPressed = FALSE;
            pButton->InvalidateRect();
        }

        pWorld->CopyChatEditBox(m_pPanel, pNewPanel);

        static_cast<CUIControlLabel*>(pNewPanel->GetControl(0x10000009))->SetText(static_cast<CUIControlLabel*>(m_pPanel->GetControl(0x10000009))->GetText());
        static_cast<CUIControlButtonMultiPlayerPortrait*>(pNewPanel->GetControl(11))->SetPortrait(static_cast<CUIControlButtonMultiPlayerPortrait*>(m_pPanel->GetControl(11))->GetPortrait());
    }

    pWorld->GetManager()->InvalidateRect(NULL);
}

// -----------------------------------------------------------------------------

// 0x77A940
CUIControlTextDisplayDialog::CUIControlTextDisplayDialog(CUIPanel* panel, UI_CONTROL_TEXTDISPLAY* controlInfo, BOOLEAN a3)
    : CUIControlTextDisplay(panel, controlInfo, a3)
{
    // NOTE: Uninline.
    SetNeedMouseMove();
}

// 0x621470
CUIControlTextDisplayDialog::~CUIControlTextDisplayDialog()
{
}

// 0x77A8F0
void CUIControlTextDisplayDialog::HighlightItem(POSITION posBossItem)
{
    if (g_pBaldurChitin->m_pEngineWorld->m_bInControlOfDialog) {
        CUIControlTextDisplay::HighlightItem(posBossItem);
    }
}

// 0x77A920
void CUIControlTextDisplayDialog::UnHighlightItem()
{
    if (g_pBaldurChitin->m_pEngineWorld->m_bInControlOfDialog) {
        CUIControlTextDisplay::UnHighlightItem();
    }
}

// 0x77BC80
void CUIControlTextDisplayDialog::OnItemSelected(LONG lMarker)
{
    if (g_pBaldurChitin->m_pEngineWorld->m_bInControlOfDialog) {
        if (lMarker != -1) {
            if (GetTickCount() > g_pBaldurChitin->m_pEngineWorld->field_11BA + 600) {
                g_pBaldurChitin->m_pEngineWorld->m_internalLoadedDialog.m_responseMarker = lMarker;
                g_pBaldurChitin->m_pEngineWorld->field_11BA = GetTickCount();
            }
        } else {
            g_pBaldurChitin->m_pEngineWorld->m_internalLoadedDialog.m_responseMarker = -1;
        }
    }
}

// -----------------------------------------------------------------------------

// 0x77A980
CUIControlButton85D3E4::CUIControlButton85D3E4(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_nAUCounter = 0;
}

// 0x77A9E0
CUIControlButton85D3E4::~CUIControlButton85D3E4()
{
}

// 0x77B6F0
BOOL CUIControlButton85D3E4::OnLButtonDown(CPoint pt)
{
    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->OnScrollDown();

    m_nAUCounter = 1;

    return TRUE;
}

// 0x77B730
void CUIControlButton85D3E4::OnLButtonUp(CPoint pt)
{
    CUIControlButton::OnLButtonUp(pt);

    m_nAUCounter = 0;

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->field_A67 = 0;
}

// 0x77B770
void CUIControlButton85D3E4::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
            pText->OnScrollDown();
        } else {
            m_nAUCounter++;
        }
    }
}

// -----------------------------------------------------------------------------

// 0x77AA80
CUIControlButton85D45C::CUIControlButton85D45C(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, LBUTTON, 1)
{
    m_nAUCounter = 0;
}

// 0x77AAE0
CUIControlButton85D45C::~CUIControlButton85D45C()
{
}

// 0x77E0F0
BOOL CUIControlButton85D45C::OnLButtonDown(CPoint pt)
{
    if (!CUIControlButton::OnLButtonDown(pt)) {
        return FALSE;
    }

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->OnScrollUp();

    m_nAUCounter = 1;

    return TRUE;
}

// 0x77B7C0
void CUIControlButton85D45C::OnLButtonUp(CPoint pt)
{
    CUIControlButton::OnLButtonUp(pt);

    m_nAUCounter = 0;

    CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
    pText->field_A66 = 0;
}

// 0x77B800
void CUIControlButton85D45C::TimerAsynchronousUpdate(BOOLEAN bInside)
{
    if (m_nAUCounter != 0) {
        if (m_nAUCounter == 20) {
            CUIControlTextDisplay* pText = static_cast<CUIControlTextDisplay*>(m_pPanel->GetControl(3));
            pText->OnScrollUp();
        } else {
            m_nAUCounter++;
        }
    }
}

// -----------------------------------------------------------------------------

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
    g_pBaldurChitin->GetActiveEngine()->OnRestButtonClick();
}

// -----------------------------------------------------------------------------

// 0x77BD00
CUIControlEditLua::CUIControlEditLua(CUIPanel* panel, UI_CONTROL_EDIT* controlInfo)
    : CUIControlEdit(panel, controlInfo, TRUE)
{
    CString sKey("String0");

    m_nHistorySize = 10;

    for (BYTE nIndex = 0; nIndex < m_nHistorySize; nIndex++) {
        sKey.SetAt(sKey.GetLength() - 1, nIndex + '0');
        GetPrivateProfileStringA("Lua Edit",
            sKey,
            "",
            field_874[nIndex].GetBuffer(128),
            128,
            g_pBaldurChitin->GetIniFileName());
        field_874[nIndex].ReleaseBuffer();
    }

    if (field_874[0].GetLength() > 0) {
        m_sText = field_874[0];
    }

    field_8A6 = 0;
    field_8A2 = CGameObjectArray::INVALID_INDEX;
}

// 0x77BE60
CUIControlEditLua::~CUIControlEditLua()
{
}

// -----------------------------------------------------------------------------

// 0x77C4C0
CUIControlEncumbrance::CUIControlEncumbrance(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButton(panel, controlInfo, 0, 1)
{
    field_662 = 0;
    field_B6A = 0;
    field_B66 = 0;
    field_B72 = 0;
    field_B6E = 0;
}

// 0x77C560
CUIControlEncumbrance::~CUIControlEncumbrance()
{
}

// 0x77C610
void CUIControlEncumbrance::SetEncumbrance(int a1, int a2)
{
    if (field_B66 != a1 || field_B6A != a2) {
        field_B66 = a1;
        field_B6A = a2;
        InvalidateRect();
    }
}

// 0x77C640
void CUIControlEncumbrance::SetVolume(int a1, int a2)
{
    if (field_B6E != a1 || field_B72 != a2) {
        field_B6E = a1;
        field_B72 = a2;
        InvalidateRect();
    }
}

// 0x77C670
BOOL CUIControlEncumbrance::Render(BOOL bForce)
{
    // TODO: Incomplete.

    return FALSE;
}

// -----------------------------------------------------------------------------

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
    g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(m_nID);
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
    g_pBaldurChitin->GetActiveEngine()->OnLeftPanelButtonClick(0);
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
    g_pBaldurChitin->GetObjectGame()->LoadOptions();
    g_pBaldurChitin->m_pEngineConnection->SelectEngine(pOptions);
}

// NOTE: Inlined in `CUIControlBase::CreateControl` (0x76DF8B);
CUIControlButtonGeneralOptionsFromMainMenu::CUIControlButtonGeneralOptionsFromMainMenu(CUIPanel* panel, UI_CONTROL_BUTTON* controlInfo)
    : CUIControlButtonGeneralBase(panel, controlInfo)
{
    STR_RES strRes;
    g_pBaldurChitin->GetTlkTable().Fetch(13905, strRes);
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
    g_pBaldurChitin->GetObjectGame()->LoadOptions();
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

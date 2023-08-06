#include "CMessageHandler.h"

#include "CBaldurChitin.h"
#include "CChitin.h"
#include "CInfGame.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenLoad.h"
#include "CScreenMultiPlayer.h"
#include "CScreenSinglePlayer.h"

// 0x4F7470
CMessageHandler::CMessageHandler()
{
    m_bLastArbitrationLockStatus = FALSE;
}

// 0x4F7490
CMessageHandler::~CMessageHandler()
{
    // TODO: Incomplete.
}

// 0x4EE020
void CMessageHandler::AsynchronousUpdate()
{
    // TODO: Incomplete.
}

// 0x4F7110
void CMessageHandler::PostAsynchronousUpdate()
{
    if (g_pChitin->field_1932 == TRUE) {
        return;
    }

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        g_pChitin->cGameSpy.sub_4D2210();
    }

    if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
        STRREF strError;
        if (g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame == TRUE
            && (g_pBaldurChitin->GetObjectGame()->CanSaveGame(strError, 0, 0) == TRUE
                || g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus == TRUE)) {
            if ((g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineLoad
                    && g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineCreateChar
                    && g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineMultiPlayer
                    && g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineSinglePlayer
                    && g_pBaldurChitin->pActiveEngine != g_pBaldurChitin->m_pEngineConnection)
                || (g_pBaldurChitin->pActiveEngine == g_pBaldurChitin->m_pEngineMultiPlayer
                    && g_pBaldurChitin->m_pEngineMultiPlayer->field_45C != 1)) {
                g_pBaldurChitin->GetObjectGame()->MultiplayerSetCharacterCreationLocation();

                g_pBaldurChitin->GetObjectGame()->field_1BA1 = 4;

                g_pBaldurChitin->m_pEngineMultiPlayer->field_45C = 1;
                g_pBaldurChitin->m_pEngineMultiPlayer->StartMultiPlayer(1);
                g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineMultiPlayer);

                g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->SetArbitrationLockStatus(1, 0);
            }

            if (g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame == TRUE) {
                g_pBaldurChitin->GetBaldurMessage()->SendFullSettingsToClients(CString(""));
                g_pBaldurChitin->GetBaldurMessage()->UpdateDemandCharacters(1, 0, 0);
            } else {
                if (!m_bLastArbitrationLockStatus
                    && g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus != TRUE) {
                    g_pBaldurChitin->GetBaldurMessage()->UpdateDemandCharacters(1, 0, 0);
                }
            }

            g_pBaldurChitin->GetObjectGame()->m_bAnotherPlayerJoinedGame = FALSE;
        }
    }

    m_bLastArbitrationLockStatus = g_pBaldurChitin->GetObjectGame()->GetMultiplayerSettings()->m_bArbitrationLockStatus;

    if (g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSessionShutdown == TRUE) {
        g_pBaldurChitin->GetBaldurMessage()->m_bMultiplayerSessionShutdown = FALSE;
        g_pChitin->cNetwork.CloseSession(TRUE);
    }

    if (g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown == TRUE) {
        if (g_pBaldurChitin->GetObjectGame()->m_bGameLoaded) {
            g_pBaldurChitin->pActiveEngine->SelectEngine(g_pBaldurChitin->m_pEngineConnection);

            if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL) {
                g_pBaldurChitin->m_pEngineConnection->ShowSessionTerminatedMessage();
            }

            if (g_pChitin->cNetwork.GetSessionOpen() == TRUE
                && g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
                g_pBaldurChitin->GetObjectGame()->SaveGame(0, 0, 1);
            }

            g_pBaldurChitin->GetObjectGame()->DestroyGame(1, 0);
        }

        if (g_pChitin->cNetwork.GetSessionOpen() == TRUE) {
            g_pChitin->cNetwork.CloseSession(TRUE);
        }

        g_pBaldurChitin->GetBaldurMessage()->m_bPlayerShutdown = FALSE;
    }
}

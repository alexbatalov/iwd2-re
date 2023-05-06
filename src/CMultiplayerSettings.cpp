#include "CMultiplayerSettings.h"

#include "CBaldurChitin.h"
#include "CUtil.h"

// TODO: Too many `MAX_PLAYERS` constants.
#define MAX_PLAYERS 6

// 0x517510
CMultiplayerSettings::CMultiplayerSettings()
{
    InitializeSettings();
}

// 0x517580
CMultiplayerSettings::~CMultiplayerSettings()
{
}

// 0x5175F0
DWORD CMultiplayerSettings::GetDataSize()
{
    return 7 * CGamePermission::TOTAL_PERMISSIONS + 151;
}

// 0x517610
void CMultiplayerSettings::InitializeSettings()
{
    // TODO: Incomplete.
}

// 0x517FE0
BOOLEAN CMultiplayerSettings::GetPermission(INT nPlayerSlot, INT nPermission)
{
    if (!(nPermission >= 0 && nPermission < CGamePermission::TOTAL_PERMISSIONS)) {
        return FALSE;
    }

    if (nPlayerSlot != -1 && g_pChitin->cNetwork.GetPlayerID(nPlayerSlot) != 0) {
        return m_pcPermissions[nPlayerSlot].GetSinglePermission(nPermission);
    }

    return m_cDefaultPermissions.GetSinglePermission(nPermission);
}

// 0x518220
void CMultiplayerSettings::ResetPermissionsForPlayer(INT nPlayerSlot, BOOLEAN bFlush)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished && g_pChitin->cNetwork.m_bIsHost) {
        for (BYTE nPermission = 0; nPermission < CGamePermission::TOTAL_PERMISSIONS; nPermission++) {
            BOOLEAN bValue = m_cDefaultPermissions.GetSinglePermission(nPermission);
            m_pcPermissions[nPlayerSlot].SetSinglePermission(nPermission, bValue);
        }

        if (bFlush == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
        }
    }
}

// 0x518300
BOOLEAN CMultiplayerSettings::GetPlayerReady(SHORT nPlayerSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 974
    UTIL_ASSERT_MSG(((nPlayerSlot >= 0) && (nPlayerSlot < MAX_PLAYERS)),
        "CMultiplayerSettings::GetPlayerReady: Bad Player Slot.");

    PLAYER_ID playerID = g_pChitin->cNetwork.GetPlayerID(nPlayerSlot);

    for (int index = 0; index < MAX_PLAYERS; index++) {
        if (m_pnPlayerReady[index] == playerID) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x518370
BOOLEAN CMultiplayerSettings::GetPlayerReady(PLAYER_ID playerID)
{
    for (int index = 0; index < MAX_PLAYERS; index++) {
        if (m_pnPlayerReady[index] == playerID) {
            return TRUE;
        }
    }

    return FALSE;
}

// 0x5186C0
INT CMultiplayerSettings::GetCharacterControlledByPlayer(INT nCharacterSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1294
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::GetCharacterControlledByPlayer: Bad Character Slot.");

    return g_pChitin->cNetwork.FindPlayerLocationByID(m_pnCharacterControlledByPlayer[nCharacterSlot], FALSE);
}

// 0x518A30
BOOLEAN CMultiplayerSettings::GetCharacterReady(INT nCharacterSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1431
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::GetCharacterReady: Bad Character Slot.");

    return m_pbCharacterReady[nCharacterSlot];
}

// 0x518A70
void CMultiplayerSettings::SetCharacterReady(INT nCharacterSlot, BOOLEAN bReady, BOOLEAN bFlush)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1459
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::SetCharacterReady: Bad Character Slot.");

    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        if (g_pChitin->cNetwork.m_bIsHost) {
            m_pbCharacterReady[nCharacterSlot] = bReady;

            if (bFlush == TRUE) {
                g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
            }
        } else {
            g_pBaldurChitin->m_cBaldurMessage.SendCharacterReadyToServer(nCharacterSlot, bReady);
        }
    }
}

// 0x518B60
BYTE CMultiplayerSettings::GetCharacterStatus(INT nCharacterSlot)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1504
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::GetCharacterStatus: Bad Character Slot.");

    return m_pnCharacterStatus[nCharacterSlot];
}

// 0x518EB0
void CMultiplayerSettings::SetImportingCharacterOption(BYTE nImportingBitField)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1631
    UTIL_ASSERT(nImportingBitField == (IMPORT_ALL) || nImportingBitField == (IMPORT_EXPERIENCE | IMPORT_STATISTICS) || nImportingBitField == (IMPORT_STATISTICS));

    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        if (g_pChitin->cNetwork.m_bIsHost) {
            m_nImportingBitField = nImportingBitField;
            g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
        } else {
            g_pBaldurChitin->m_cBaldurMessage.SendImportingOptionToServer(nImportingBitField);
        }
    }
}

// 0x518F90
void CMultiplayerSettings::SetRestrictStoreOption(BOOLEAN bRestrictStore)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        if (g_pChitin->cNetwork.m_bIsHost) {
            m_bRestrictStoreOption = bRestrictStore;
            g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
        } else {
            g_pBaldurChitin->m_cBaldurMessage.SendRestrictStoreOptionToServer(bRestrictStore);
        }
    }
}

// 0x519040
void CMultiplayerSettings::SetListenToJoinOption(BOOLEAN bListenToJoin, BOOLEAN bFlush)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        if (g_pChitin->cNetwork.m_bIsHost) {
            m_bJoinRequests = bListenToJoin;

            g_pChitin->cNetwork.SetJoinEnabled(bListenToJoin);
            g_pChitin->cNetwork.SetInSessionOptions();

            if (bFlush == TRUE) {
                g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
            }
        } else {
            g_pBaldurChitin->m_cBaldurMessage.SendJoinRequestOptionToServer(bListenToJoin);
        }
    }
}

// 0x519120
void CMultiplayerSettings::SetArbitrationLockStatus(BOOLEAN bStatus)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        m_bArbitrationLockStatus = bStatus;

        if (g_pChitin->cNetwork.m_bIsHost == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendArbitrationLockStatus(bStatus);
        }
    }
}

// 0x519170
void CMultiplayerSettings::SetArbitrationLockAllowInput(BOOLEAN bAllowInput)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished) {
        m_bArbitrationLockAllowInput = bAllowInput;

        if (g_pChitin->cNetwork.m_bIsHost == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendArbitrationLockAllowInput(bAllowInput);
        }
    }
}

// FIXME: `sAreaName` should be reference.
//
// 0x5191B0
void CMultiplayerSettings::SetCharacterCreationLocation(CString sAreaName, CPoint ptStart)
{
    if (g_pChitin->cNetwork.m_bConnectionEstablished && g_pChitin->cNetwork.m_bIsHost) {
        m_sAreaName = sAreaName;
        m_ptAreaStart = ptStart;
        g_pBaldurChitin->m_cBaldurMessage.SendFullSettingsToClients(CString(""));
    }
}

// 0x5194F0
void CMultiplayerSettings::SetServerOnLoadGame(PLAYER_ID localPlayerID)
{
    for (int index = 0; index < MAX_CHARACTERS; index++) {
        m_pnLoadGameControlledByPlayer[index] = m_pnCharacterControlledByPlayer[index];
        m_pnCharacterControlledByPlayer[index] = localPlayerID;
    }
}

// 0x519510
void CMultiplayerSettings::ResetServerOnLoadGame()
{
    for (int index = 0; index < MAX_CHARACTERS; index++) {
        m_pnCharacterControlledByPlayer[index] = m_pnLoadGameControlledByPlayer[index];
    }
}

#include "CMultiplayerSettings.h"

#include "CBaldurChitin.h"
#include "CInfGame.h"
#include "CUtil.h"

// 0x84D59C
const BYTE CMultiplayerSettings::MAX_PLAYERS = 6;

// 0x84D59D
const BYTE CMultiplayerSettings::MAX_CHARACTERS = 6;

// 0x84D59E
const BYTE CMultiplayerSettings::IMPORT_ALL = 7;

// 0x84D59F
const BYTE CMultiplayerSettings::IMPORT_STATISTICS = 1;

// 0x84D5A0
const BYTE CMultiplayerSettings::IMPORT_EXPERIENCE = 2;

// 0x84D5A1
const BYTE CMultiplayerSettings::IMPORT_ITEMS = 4;

// 0x84D5A2
const BYTE CMultiplayerSettings::CHARSTATUS_NO_CHARACTER = 0;

// 0x84D5A3
const BYTE CMultiplayerSettings::CHARSTATUS_CHARACTER = 1;

// 0x84D5A4
const BYTE CMultiplayerSettings::CHARSTATUS_CREATING_CHARACTER = 2;

// 0x84D5A5
const BYTE CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_START = 8;

// 0x84D5A6
const BYTE CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_CANCEL = 9;

// 0x84D5A7
const BYTE CMultiplayerSettings::CHARSTATUS_SIGNAL_CREATION_COMPLETE = 10;

// 0x84D5A8
const BYTE CMultiplayerSettings::CHARSTATUS_SIGNAL_IMPORTED = 11;

// 0x84D5A9
const BYTE CMultiplayerSettings::CHARSTATUS_SIGNAL_DELETED = 12;

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
    // NOTE: Unused.
    CResRef cResRef;

    for (SHORT nIndex = 0; nIndex < MAX_PLAYERS; nIndex++) {
        for (INT nPermission = 0; nPermission < CGamePermission::TOTAL_PERMISSIONS; nPermission++) {
            BOOLEAN bValue = TRUE;
            if (g_pChitin->cNetwork.GetServiceProvider() != CNetwork::SERV_PROV_NULL
                && nIndex != 0
                && nPermission == CGamePermission::LEADER) {
                bValue = FALSE;
            }

            m_cDefaultPermissions.SetSinglePermission(nPermission, bValue);
            m_pcPermissions[nIndex].SetSinglePermission(nPermission, bValue);
        }

        m_pnPlayerReady[nIndex] = 0;
    }

    m_bRefreshCharacters = FALSE;

    for (INT nPlayerSlot = 0; nPlayerSlot < MAX_PLAYERS; nPlayerSlot++) {
        m_pbCharacterReady[nPlayerSlot] = FALSE;
        m_pnCharacterStatus[nPlayerSlot] = FALSE;
        field_AC[nPlayerSlot] = -1;

        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            m_pnCharacterControlledByPlayer[nPlayerSlot] = g_pChitin->cNetwork.m_idLocalPlayer;
        } else {
            m_pnCharacterControlledByPlayer[nPlayerSlot] = 0;
        }
    }

    m_nImportingBitField = IMPORT_ALL;
    m_bRestrictStoreOption = TRUE;
    m_bJoinRequests = TRUE;
    m_bArbitrationLockStatus = FALSE;
    m_bArbitrationLockAllowInput = TRUE;
    m_nHostPermittedDialogDelay = 0;
    m_bHostPermittedDialog = FALSE;
    m_idHostPermittedDialog = 0;
    field_A7 = 0;
    field_A8 = 0;
    m_bFirstConnected = FALSE;

    m_nDifficultyLevel = GetPrivateProfileIntA("Game Options",
        "Difficulty Level",
        3,
        g_pBaldurChitin->GetIniFileName());
    if (m_nDifficultyLevel < 1 || m_nDifficultyLevel > 5) {
        m_nDifficultyLevel = 3;
    }

    switch (m_nDifficultyLevel) {
    case 1:
        field_BE = -50;
        field_C2 = -50;
        break;
    case 2:
        field_BE = -25;
        field_C2 = -25;
        break;
    case 3:
        field_BE = 0;
        field_C2 = 0;
        break;
    case 4:
        field_BE = 50;
        field_C2 = 50;
        break;
    case 5:
        field_BE = 100;
        field_C2 = 100;
        break;
    }
}

// 0x517850
void CMultiplayerSettings::Marshal(BYTE** pData, DWORD* dwSize)
{
    DWORD nMsgPtr = 0;
    BYTE nPermission;
    INT nIndexPlayer;
    INT nIndexCharacter;

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 359
    UTIL_ASSERT_MSG(pData != NULL && dwSize != NULL, "CMultiplayerSettings::Marshal: Bad pointer to data or data size.");

    *dwSize = GetDataSize();
    *pData = new BYTE[*dwSize];

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 366
    UTIL_ASSERT(*pData != NULL);

    memset(*pData, 0, *dwSize);

    *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_bArbitrationLockStatus;
    nMsgPtr += sizeof(BOOLEAN);

    *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_bArbitrationLockAllowInput;
    nMsgPtr += sizeof(BOOLEAN);

    for (nPermission = 0; nPermission < CGamePermission::TOTAL_PERMISSIONS; nPermission++) {
        *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_cDefaultPermissions.GetSinglePermission(nPermission);
        nMsgPtr += sizeof(BOOLEAN);
    }

    for (nIndexPlayer = 0; nIndexPlayer < 6; nIndexPlayer++) {
        *reinterpret_cast<PLAYER_ID*>(*pData + nMsgPtr) = g_pChitin->cNetwork.GetPlayerID(nIndexPlayer);
        nMsgPtr += sizeof(PLAYER_ID);

        for (nPermission = 0; nPermission < CGamePermission::TOTAL_PERMISSIONS; nPermission++) {
            *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_pcPermissions[nIndexPlayer].GetSinglePermission(nPermission);
            nMsgPtr += sizeof(BOOLEAN);
        }

        *reinterpret_cast<PLAYER_ID*>(*pData + nMsgPtr) = g_pChitin->cNetwork.field_772[nIndexPlayer];
        nMsgPtr += sizeof(PLAYER_ID);
    }

    *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_bRefreshCharacters;
    nMsgPtr += sizeof(BOOLEAN);

    m_bRefreshCharacters = FALSE;

    for (nIndexCharacter = 0; nIndexCharacter < 6; nIndexCharacter++) {
        *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_pbCharacterReady[nIndexCharacter];
        nMsgPtr += sizeof(BOOLEAN);
    }

    for (nIndexCharacter = 0; nIndexCharacter < 6; nIndexCharacter++) {
        *reinterpret_cast<BYTE*>(*pData + nMsgPtr) = m_pnCharacterStatus[nIndexCharacter];
        nMsgPtr += sizeof(BYTE);
    }

    for (nIndexCharacter = 0; nIndexCharacter < 6; nIndexCharacter++) {
        *reinterpret_cast<PLAYER_ID*>(*pData + nMsgPtr) = m_pnCharacterControlledByPlayer[nIndexCharacter];
        nMsgPtr += sizeof(PLAYER_ID);
    }

    *reinterpret_cast<BYTE*>(*pData + nMsgPtr) = m_nImportingBitField;
    nMsgPtr += sizeof(BYTE);

    *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_bRestrictStoreOption;
    nMsgPtr += sizeof(BOOLEAN);

    *reinterpret_cast<BOOLEAN*>(*pData + nMsgPtr) = m_bJoinRequests;
    nMsgPtr += sizeof(BOOLEAN);

    *reinterpret_cast<LONG*>(*pData + nMsgPtr) = m_ptAreaStart.x;
    nMsgPtr += sizeof(LONG);

    *reinterpret_cast<LONG*>(*pData + nMsgPtr) = m_ptAreaStart.y;
    nMsgPtr += sizeof(LONG);

    DWORD nGore = g_pBaldurChitin->GetObjectGame()->GetOptions()->m_bGore;
    *reinterpret_cast<DWORD*>(*pData + nMsgPtr) = nGore;
    nMsgPtr += sizeof(DWORD);

    DWORD nGoreOption = g_pBaldurChitin->GetObjectGame()->GetOptions()->field_4;
    *reinterpret_cast<DWORD*>(*pData + nMsgPtr) = nGoreOption;
    nMsgPtr += sizeof(DWORD);

    BYTE nAreaStringLength = min(m_sAreaName.GetLength(), 8);

    *reinterpret_cast<BYTE*>(*pData + nMsgPtr) = nAreaStringLength;
    nMsgPtr += sizeof(BYTE);

    memcpy(*pData + nMsgPtr, m_sAreaName.GetBuffer(m_sAreaName.GetLength()), nAreaStringLength);
    nMsgPtr += nAreaStringLength;

    *reinterpret_cast<int*>(*pData + nMsgPtr) = m_nDifficultyLevel;
    nMsgPtr += sizeof(int);

    *reinterpret_cast<int*>(*pData + nMsgPtr) = field_BE;
    nMsgPtr += sizeof(int);

    *reinterpret_cast<int*>(*pData + nMsgPtr) = field_C2;
    nMsgPtr += sizeof(int);

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 482
    UTIL_ASSERT(nMsgPtr == *dwSize);
}

// 0x517B50
void CMultiplayerSettings::Unmarshal(BYTE* pData, DWORD dwSize)
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

// 0x518050
void CMultiplayerSettings::SetPermission(INT nPlayerSlot, INT nPermission, BOOLEAN bPermissionValue, BOOLEAN bFlush)
{
    // TODO: Incomplete.
}

// 0x518220
void CMultiplayerSettings::ResetPermissionsForPlayer(INT nPlayerSlot, BOOLEAN bFlush)
{
    if (g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting()) {
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

// 0x518390
void CMultiplayerSettings::SetPlayerReady(PLAYER_ID playerID, BOOLEAN bValue, BOOLEAN bFlush)
{
    // TODO: Incomplete.
}

// 0x518560
int CMultiplayerSettings::sub_518560()
{
    int count = 0;

    for (int index = 0; index < 6; index++) {
        if (field_AC[index] != -1) {
            count++;
        }
    }

    return count;
}

// 0x518580
void CMultiplayerSettings::sub_518580(PLAYER_ID playerID, INT characterSlotBeingViewed)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1185
    UTIL_ASSERT(characterSlotBeingViewed >= -1 && characterSlotBeingViewed < MAX_CHARACTERS);

    // TODO: Incomplete. There is some strange code which locks appropriate
    // character, but never releases it. Check in debugger.

    INT nPlayerSlot = g_pChitin->cNetwork.FindPlayerLocationByID(playerID, TRUE);
    field_AC[nPlayerSlot] = characterSlotBeingViewed;
}

// 0x518650
void CMultiplayerSettings::sub_518650()
{
    for (int index = 0; index < 6; index++) {
        field_AC[index] = -1;
    }
}

// 0x518660
void CMultiplayerSettings::sub_518660(PLAYER_ID playerID, BOOLEAN a2)
{
    INT nPlayerSlot = g_pChitin->cNetwork.FindPlayerLocationByID(playerID, TRUE);
    field_B2[nPlayerSlot] = a2;
}

// 0x518690
void CMultiplayerSettings::sub_518690()
{
    for (int index = 0; index < 6; index++) {
        field_B2[index] = FALSE;
    }
}

// 0x5186A0
int CMultiplayerSettings::sub_5186A0()
{
    int count = 0;

    for (int index = 0; index < 6; index++) {
        if (field_B2[index]) {
            count++;
        }
    }

    return count;
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

// 0x518710
void CMultiplayerSettings::SetCharacterControlledByPlayer(INT nCharacterSlot, INT nPlayerSlot, BOOLEAN bFlush, BOOLEAN bCharacterUpdate)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1322
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::SetCharacterControlledByPlayer: Bad Character Slot.");

    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1323
    UTIL_ASSERT_MSG(((nPlayerSlot >= -1) && (nPlayerSlot < MAX_PLAYERS)),
        "CMultiplayerSettings::SetCharacterControlledByPlayer: Bad player slot.");

    // TODO: Incomplete.
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

    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
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

// 0x518BA0
void CMultiplayerSettings::SignalCharacterStatus(INT nCharacterSlot, BYTE nStatus, BOOLEAN bLocalMessage, BOOLEAN bFlush)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1534
    UTIL_ASSERT_MSG(((nCharacterSlot >= 0) && (nCharacterSlot < MAX_CHARACTERS)),
        "CMultiplayerSettings::SignalCharacterStatus: Bad Character Slot.");

    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            m_pbCharacterReady[nCharacterSlot] = 0;

            if (nStatus == CHARSTATUS_SIGNAL_CREATION_START
                || nStatus == CHARSTATUS_SIGNAL_CREATION_CANCEL
                || nStatus == CHARSTATUS_SIGNAL_DELETED) {
                if (nStatus == CHARSTATUS_SIGNAL_CREATION_START) {
                    m_pnCharacterStatus[nCharacterSlot] = 2;
                } else {
                    m_pnCharacterStatus[nCharacterSlot] = 0;
                }

                if (g_pChitin->cNetwork.m_nLocalPlayer != g_pChitin->cNetwork.FindPlayerLocationByID(m_pnCharacterControlledByPlayer[nCharacterSlot], FALSE)) {
                    g_pBaldurChitin->GetObjectGame()->ClearCharacterSlot(nCharacterSlot);
                }
            } else if (nStatus == CHARSTATUS_SIGNAL_CREATION_COMPLETE
                || nStatus == CHARSTATUS_SIGNAL_IMPORTED) {
                if (g_pChitin->cNetwork.m_nLocalPlayer == g_pChitin->cNetwork.FindPlayerLocationByID(m_pnCharacterControlledByPlayer[nCharacterSlot], FALSE)
                    || bLocalMessage) {
                    m_pnCharacterStatus[nCharacterSlot] = 1;
                } else {
                    g_pBaldurChitin->GetBaldurMessage()->DemandCharacterSlot(nCharacterSlot,
                        FALSE,
                        g_pChitin->cNetwork.FindPlayerLocationByID(m_pnCharacterControlledByPlayer[nCharacterSlot], FALSE));
                }
            }

            if (bFlush == TRUE) {
                g_pBaldurChitin->GetBaldurMessage()->SendFullSettingsToClients(CString(""));
            }
        } else {
            INT v1 = g_pChitin->cNetwork.FindPlayerLocationByID(m_pnCharacterControlledByPlayer[nCharacterSlot], FALSE);
            INT v2 = g_pChitin->cNetwork.FindPlayerLocationByID(g_pChitin->cNetwork.m_idLocalPlayer, FALSE);
            if (v2 == v1) {
                g_pBaldurChitin->GetBaldurMessage()->SendCharacterSlotStatusToServer(nCharacterSlot, nStatus);
            }
        }
    }
}

// 0x518EB0
void CMultiplayerSettings::SetImportingCharacterOption(BYTE nImportingBitField)
{
    // __FILE__: C:\Projects\Icewind2\src\Baldur\CMultiplayerSettings.cpp
    // __LINE__: 1631
    UTIL_ASSERT(nImportingBitField == (IMPORT_ALL) || nImportingBitField == (IMPORT_EXPERIENCE | IMPORT_STATISTICS) || nImportingBitField == (IMPORT_STATISTICS));

    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
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
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
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
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        if (g_pChitin->cNetwork.GetSessionHosting()) {
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
void CMultiplayerSettings::SetArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2)
{
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        m_bArbitrationLockStatus = bStatus;

        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendArbitrationLockStatus(bStatus, a2);
        }
    }
}

// 0x519170
void CMultiplayerSettings::SetArbitrationLockAllowInput(BOOLEAN bAllowInput)
{
    if (g_pChitin->cNetwork.GetSessionOpen()) {
        m_bArbitrationLockAllowInput = bAllowInput;

        if (g_pChitin->cNetwork.GetSessionHosting() == TRUE) {
            g_pBaldurChitin->m_cBaldurMessage.SendArbitrationLockAllowInput(bAllowInput);
        }
    }
}

// FIXME: `sAreaName` should be reference.
//
// 0x5191B0
void CMultiplayerSettings::SetCharacterCreationLocation(CString sAreaName, CPoint ptStart)
{
    if (g_pChitin->cNetwork.GetSessionOpen() && g_pChitin->cNetwork.GetSessionHosting()) {
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

// NOTE: Odd location.
//
// 0x5BFBC0
CString CMultiplayerSettings::GetAreaStartName()
{
    return m_sAreaName;
}

// NOTE: Odd location.
//
// 0x452F40
BOOLEAN CMultiplayerSettings::GetListenToJoinOption()
{
    return m_bJoinRequests;
}

#include "CBaldurMessage.h"

#include "CBaldurChitin.h"

// 0x84CF76
const BYTE CBaldurMessage::DELETEAREA_EMPTY_VOTE = 101;

// 0x84CFBC
const BYTE CBaldurMessage::SIGNAL_SERVER = 83;

// 0x84CFBD
const BYTE CBaldurMessage::SIGNAL_END_MAJOR_EVENT = 49;

// 0x84CFC4
const DWORD CBaldurMessage::SIGNAL_SECONDSTOMPTIMEOUT = 200;

// 0x4294F0
CBaldurMessage::CBaldurMessage()
{
    field_6 = 0;
    field_EE = 0;
    field_0 = 0;
    field_1 = 0;
    field_2 = 0;
    field_3 = 0;
    field_5 = 0;
    field_4 = 0;
    field_D3 = 0;
    field_D4 = 0;
    field_D5 = 0;
    field_D6 = 0;
    field_DA = 0;
    field_DB = 0;
    field_DC = 0;
    field_DD = 0;
    field_DE = 0;
    field_DF = 0;
    field_74 = "";
    field_73 = 0;
    field_78 = 0;

    for (int k = 0; k < 6; k++) {
        field_82[k] = 0;
        field_7C[k] = DELETEAREA_EMPTY_VOTE;
    }

    field_E0 = 0;
    field_E1 = 0;
    field_E2 = 0;
    field_E3 = 0;
    field_E4 = -1;
    field_29 = 0;
    field_2A = 0;
    m_nSignalQueueSize = 24;

    for (BYTE l = 0; l < m_nSignalQueueSize; l++) {
        field_2B[l] = -1;
        field_5B[l] = 0;
        field_43[l] = 0;
    }

    field_D2 = 0;

    for (int m = 0; m < 6; m++) {
        field_BA[m] = 0;
    }

    field_E5 = 0;
    m_dwSignalSecondsToTimeout = SIGNAL_SECONDSTOMPTIMEOUT;
    field_7 = 0;
    m_bMultiplayerSessionShutdown = FALSE;
    field_F5 = 0;
    field_F6 = 0;
}

// 0x429720
CBaldurMessage::~CBaldurMessage()
{
}

// 0x42B2B0
BOOL CBaldurMessage::SendFullSettingsToClients(const CString& sPlayerName)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42BC00
BOOL CBaldurMessage::SendCharacterReadyToServer(INT nCharacterSlot, BOOLEAN bReady)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C0E0
BOOL CBaldurMessage::SendImportingOptionToServer(BYTE nImportingBitField)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C390
BOOL CBaldurMessage::SendRestrictStoreOptionToServer(BOOLEAN bRestrictStore)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C640
BOOL CBaldurMessage::SendJoinRequestOptionToServer(BOOLEAN bListenToJoin)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42C8F0
BOOLEAN CBaldurMessage::SendCharacterSlotStatusToServer(SHORT nCharacterSlot, BYTE nStatus)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CAD0
BOOLEAN CBaldurMessage::SendArbitrationLockRequestToServer(BOOLEAN bLockValue)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CCA0
BOOL CBaldurMessage::SendArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42CEF0
BOOL CBaldurMessage::SendArbitrationLockAllowInput(BOOLEAN bAllowInput)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42D070
BOOLEAN CBaldurMessage::KickPlayerRequest(const CString& sPlayerName)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x42F100
BOOLEAN CBaldurMessage::DemandCharacterSlot(SHORT nCharacterSlot, BOOLEAN bDemandFromHost, SHORT nPlayerSlot)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x430980
BOOL CBaldurMessage::ObjectControlRequest(LONG localObjectID)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x430C50
BOOL CBaldurMessage::ObjectControl()
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x433150
void CBaldurMessage::SetSignalDefaultSecondsToTimeout()
{
    m_dwSignalSecondsToTimeout = GetPrivateProfileIntA("Multiplayer",
        "Client Timeout",
        SIGNAL_SECONDSTOMPTIMEOUT,
        g_pBaldurChitin->GetIniFileName());

    if (m_dwSignalSecondsToTimeout <= 30 || m_dwSignalSecondsToTimeout > 9999) {
        m_dwSignalSecondsToTimeout = SIGNAL_SECONDSTOMPTIMEOUT;
    }
}

// 0x4333C0
BOOLEAN CBaldurMessage::SendSignal(BYTE signalType, BYTE signalToSend)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x434EB0
BOOLEAN CBaldurMessage::ChapterAnnounceStatus(BYTE nChapter, CResRef cResRef)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x436F50
void CBaldurMessage::WeatherBroadcast(WORD wWeatherFlags)
{
    // TODO: Incomplete.
}

// 0x4370B0
void CBaldurMessage::TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime)
{
    // TODO: Incomplete.
}

// 0x437240
void CBaldurMessage::TimeChangeToServer(DWORD deltaTime)
{
    // TODO: Incomplete.
}

// 0x43D590
BOOLEAN CBaldurMessage::DemandSettingsNightmareMode(BOOLEAN wait)
{
    // TODO: Incomplete.

    return FALSE;
}

// 0x43E0E0
BOOL CBaldurMessage::sub_43E0E0(DWORD a1, DWORD a2, COLORREF a3, COLORREF a4, int a5, int a6, int a7)
{
    // TODO: Incomplete.

    return FALSE;
}

#ifndef CMULTIPLAYERSETTINGS_H_
#define CMULTIPLAYERSETTINGS_H_

#include "mfc.h"

#include "CGamePermission.h"
#include "CNetwork.h"

// TODO: Should be defined elsewhere.
#define MAX_CHARACTERS 6

#define IMPORT_STATISTICS 1
#define IMPORT_EXPERIENCE 2
#define IMPORT_ALL 7

class CMultiplayerSettings {
public:
    static const BYTE CHARSTATUS_NO_CHARACTER;
    static const BYTE CHARSTATUS_CHARACTER;
    static const BYTE CHARSTATUS_CREATING_CHARACTER;
    static const BYTE CHARSTATUS_SIGNAL_CREATION_START;
    static const BYTE CHARSTATUS_SIGNAL_CREATION_CANCEL;
    static const BYTE CHARSTATUS_SIGNAL_CREATION_COMPLETE;
    static const BYTE CHARSTATUS_SIGNAL_IMPORTED;
    static const BYTE CHARSTATUS_SIGNAL_DELETED;

    CMultiplayerSettings();
    ~CMultiplayerSettings();
    DWORD GetDataSize();
    void InitializeSettings();
    BOOLEAN GetPermission(INT nPlayerNumber, INT nPermission);
    void ResetPermissionsForPlayer(INT nPlayerSlot, BOOLEAN bFlush);
    BOOLEAN GetPlayerReady(SHORT nPlayerSlot);
    BOOLEAN GetPlayerReady(PLAYER_ID playerID);
    void SetPlayerReady(PLAYER_ID playerID, BOOLEAN bValue, BOOLEAN bFlush);
    INT GetCharacterControlledByPlayer(INT nCharacterSlot);
    void SetCharacterControlledByPlayer(INT nCharacterSlot, INT nPlayerSlot, BOOLEAN bFlush, BOOLEAN bCharacterUpdate);
    BOOLEAN GetCharacterReady(INT nCharacterSlot);
    void SetCharacterReady(INT nCharacterSlot, BOOLEAN bReady, BOOLEAN bFlush);
    BYTE GetCharacterStatus(INT nCharacterSlot);
    void SetImportingCharacterOption(BYTE nImportingBitField);
    void SetRestrictStoreOption(BOOLEAN bRestrictStore);
    void SetListenToJoinOption(BOOLEAN bListenToJoin, BOOLEAN bFlush);
    void SetArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2);
    void SetArbitrationLockAllowInput(BOOLEAN bStatus);
    void SetCharacterCreationLocation(CString sAreaName, CPoint ptStart);
    void SetServerOnLoadGame(PLAYER_ID localPlayerID);
    void ResetServerOnLoadGame();

    /* 0000 */ CGamePermission m_pcPermissions[6];
    /* 0030 */ CGamePermission m_cDefaultPermissions;
    /* 0038 */ PLAYER_ID m_pnPlayerReady[6];
    /* 0050 */ PLAYER_ID m_pnCharacterControlledByPlayer[MAX_CHARACTERS];
    /* 0068 */ BOOLEAN m_pbCharacterReady[MAX_CHARACTERS];
    /* 006E */ BYTE m_pnCharacterStatus[MAX_CHARACTERS];
    /* 0074 */ PLAYER_ID m_pnLoadGameControlledByPlayer[MAX_CHARACTERS];
    /* 008D */ BYTE m_nImportingBitField;
    /* 008E */ BOOLEAN m_bRestrictStoreOption;
    /* 008F */ BOOLEAN m_bJoinRequests;
    /* 0090 */ BOOLEAN m_bArbitrationLockStatus;
    /* 0091 */ BOOLEAN m_bArbitrationLockAllowInput;
    /* 0092 */ CPoint m_ptAreaStart;
    /* 009A */ CString m_sAreaName;
    /* 00B8 */ unsigned char field_B8;
};

#endif /* CMULTIPLAYERSETTINGS_H_ */

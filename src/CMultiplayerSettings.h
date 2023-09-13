#ifndef CMULTIPLAYERSETTINGS_H_
#define CMULTIPLAYERSETTINGS_H_

#include "mfc.h"

#include "CGamePermission.h"
#include "CNetwork.h"

class CMultiplayerSettings {
public:
    static const BYTE MAX_PLAYERS;
    static const BYTE MAX_CHARACTERS;

    static const BYTE IMPORT_ALL;
    static const BYTE IMPORT_STATISTICS;
    static const BYTE IMPORT_EXPERIENCE;
    static const BYTE IMPORT_ITEMS;

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
    void Marshal(BYTE** pData, DWORD* dwSize);
    void Unmarshal(BYTE* pData, DWORD dwSize);
    BOOLEAN GetPermission(INT nPlayerNumber, INT nPermission);
    void SetPermission(INT nPlayerSlot, INT nPermission, BOOLEAN bPermissionValue, BOOLEAN bFlush);
    void ResetPermissionsForPlayer(INT nPlayerSlot, BOOLEAN bFlush);
    BOOLEAN GetPlayerReady(SHORT nPlayerSlot);
    BOOLEAN GetPlayerReady(PLAYER_ID playerID);
    void SetPlayerReady(PLAYER_ID playerID, BOOLEAN bValue, BOOLEAN bFlush);
    int sub_518560();
    void sub_518580(PLAYER_ID playerID, INT characterSlotBeingViewed);
    void sub_518650();
    void sub_518660(PLAYER_ID playerID, BOOLEAN a2);
    void sub_518690();
    int sub_5186A0();
    INT GetCharacterControlledByPlayer(INT nCharacterSlot);
    void SetCharacterControlledByPlayer(INT nCharacterSlot, INT nPlayerSlot, BOOLEAN bFlush, BOOLEAN bCharacterUpdate);
    BOOLEAN GetCharacterReady(INT nCharacterSlot);
    void SetCharacterReady(INT nCharacterSlot, BOOLEAN bReady, BOOLEAN bFlush);
    BYTE GetCharacterStatus(INT nCharacterSlot);
    void SignalCharacterStatus(INT nCharacterSlot, BYTE nStatus, BOOLEAN bLocalMessage, BOOLEAN bFlush);
    void SetImportingCharacterOption(BYTE nImportingBitField);
    void SetRestrictStoreOption(BOOLEAN bRestrictStore);
    void SetListenToJoinOption(BOOLEAN bListenToJoin, BOOLEAN bFlush);
    void SetArbitrationLockStatus(BOOLEAN bStatus, unsigned char a2);
    void SetArbitrationLockAllowInput(BOOLEAN bStatus);
    void SetCharacterCreationLocation(CString sAreaName, CPoint ptStart);
    void SetServerOnLoadGame(PLAYER_ID localPlayerID);
    void ResetServerOnLoadGame();

    CString GetAreaStartName();
    BOOLEAN GetListenToJoinOption();

    /* 0000 */ CGamePermission m_pcPermissions[6];
    /* 0030 */ CGamePermission m_cDefaultPermissions;
    /* 0038 */ PLAYER_ID m_pnPlayerReady[6];
    /* 0050 */ PLAYER_ID m_pnCharacterControlledByPlayer[6];
    /* 0068 */ BOOLEAN m_pbCharacterReady[6];
    /* 006E */ BYTE m_pnCharacterStatus[6];
    /* 0074 */ PLAYER_ID m_pnLoadGameControlledByPlayer[6];
    /* 008C */ unsigned char field_8C;
    /* 008D */ BYTE m_nImportingBitField;
    /* 008E */ BOOLEAN m_bRestrictStoreOption;
    /* 008F */ BOOLEAN m_bJoinRequests;
    /* 0090 */ BOOLEAN m_bArbitrationLockStatus;
    /* 0091 */ BOOLEAN m_bArbitrationLockAllowInput;
    /* 0092 */ CPoint m_ptAreaStart;
    /* 009A */ CString m_sAreaName;
    /* 009E */ int field_9E;
    /* 00A2 */ int field_A2;
    /* 00A6 */ unsigned char field_A6;
    /* 00A7 */ unsigned char field_A7;
    /* 00A8 */ unsigned char field_A8;
    /* 00AC */ unsigned char field_AC[6];
    /* 00B2 */ BOOLEAN field_B2[6];
    /* 00B8 */ BOOLEAN m_bFirstConnected;
    /* 00BA */ int m_nDifficultyLevel;
    /* 00BE */ int field_BE;
    /* 00C2 */ int field_C2;
};

#endif /* CMULTIPLAYERSETTINGS_H_ */

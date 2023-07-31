#ifndef CNETWORKWINDOW_H_
#define CNETWORKWINDOW_H_

#include <afx.h>
#include <afxtempl.h>

// TODO: Reuse from `CNetwork.h`.
typedef DWORD PLAYER_ID;

class CNetworkWindow {
public:
    struct Entry {
        unsigned char dummy;
    };

    CNetworkWindow();
    ~CNetworkWindow();

    void AddToIncomingQueue(PLAYER_ID idFrom, PLAYER_ID idTo, BYTE* pData, DWORD dwDataSize);
    void Initialize(int a1);
    void ShutDown();
    void RemoveFromAllQueues();

    /* 0000 */ BOOLEAN m_bInitialized; // #guess
    /* 0001 */ unsigned char field_1;
    /* 0002 */ unsigned char field_2;
    /* 0003 */ unsigned char field_3;
    /* 0004 */ short field_4;
    /* 0006 */ short field_6;
    /* 0008 */ short field_8;
    /* 000A */ short field_A;
    /* 000C */ short field_C;
    /* 0016 */ void* field_16;
    /* 001A */ int field_1A;
    /* 0026 */ void* field_26;
    /* 002A */ int field_2A;
    /* 002E */ CTypedPtrList<CPtrList, Entry*> m_lQueueIncomingMessages;
    /* 004A */ CTypedPtrList<CPtrList, Entry*> m_lQueueOutgoingMessages;
    /* 0066 */ unsigned char field_66;
    /* 0068 */ int field_68;
    /* 006C */ unsigned char field_6C;
    /* 006E */ short field_6E;
    /* 0070 */ unsigned char field_70;
    /* 0072 */ int field_72;
    /* 0076 */ int field_76;
    /* 007A */ unsigned char field_7A;
    /* 007B */ unsigned char field_7B;
    /* 007C */ int field_7C;
    /* 0080 */ int field_80;
    /* 0084 */ int field_84;
};

#endif /* CNETWORKWINDOW_H_ */

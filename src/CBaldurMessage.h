#ifndef CBALDURMESSAGE_H_
#define CBALDURMESSAGE_H_

#include <afx.h>
#include <afxmt.h>

#include "CChatBuffer.h"

class CBaldurMessage {
public:
    static const BYTE DELETEAREA_EMPTY_VOTE;
    static const DWORD SIGNAL_SECONDSTOMPTIMEOUT;

    CBaldurMessage();
    ~CBaldurMessage();
    void WeatherBroadcast(WORD wWeatherFlags);
    void TimeSynchBroadcast(ULONG nGameTime, BOOLEAN bCompressTime);
    void TimeChangeToServer(ULONG deltaTime);

    /* 0000 */ unsigned char field_0;
    /* 0001 */ unsigned char field_1;
    /* 0002 */ unsigned char field_2;
    /* 0003 */ unsigned char field_3;
    /* 0004 */ unsigned char field_4;
    /* 0005 */ unsigned char field_5;
    /* 0006 */ unsigned char field_6;
    /* 0007 */ unsigned char field_7;
    /* 0008 */ CChatBuffer m_cChatBuffer;
    /* 0028 */ BYTE m_nSignalQueueSize;
    /* 0029 */ unsigned char field_29;
    /* 002A */ unsigned char field_2A;
    /* 002B */ unsigned char field_2B[24];
    /* 0043 */ unsigned char field_43[24];
    /* 005B */ unsigned char field_5B[24];
    /* 0073 */ unsigned char field_73;
    /* 0074 */ CString field_74;
    /* 0078 */ int field_78;
    /* 007C */ unsigned char field_7C[6];
    /* 0082 */ int field_82[6];
    /* 009A */ CCriticalSection field_9A;
    /* 00BA */ int field_BA[6];
    /* 00D2 */ unsigned char field_D2;
    /* 00D3 */ unsigned char field_D3;
    /* 00D4 */ unsigned char field_D4;
    /* 00D5 */ unsigned char field_D5;
    /* 00D6 */ int field_D6;
    /* 00DA */ unsigned char field_DA;
    /* 00DB */ unsigned char field_DB;
    /* 00DC */ unsigned char field_DC;
    /* 00DD */ unsigned char field_DD;
    /* 00DE */ unsigned char field_DE;
    /* 00DF */ unsigned char field_DF;
    /* 00E0 */ unsigned char field_E0;
    /* 00E1 */ unsigned char field_E1;
    /* 00E2 */ unsigned char field_E2;
    /* 00E3 */ unsigned char field_E3;
    /* 00E4 */ unsigned char field_E4;
    /* 00E5 */ unsigned char field_E5;
    /* 00E6 */ CString field_E6;
    /* 00EA */ CString field_EA;
    /* 00EE */ unsigned char field_EE;
    /* 00F0 */ DWORD m_dwSignalSecondsToTimeout;
    /* 00F4 */ BOOLEAN m_bMultiplayerSessionShutdown;
    /* 00F5 */ unsigned char field_F5;
    /* 00F6 */ unsigned char field_F6;
};

#endif /* CBALDURMESSAGE_H_ */

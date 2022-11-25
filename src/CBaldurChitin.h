#ifndef CBALDURCHITIN_H_
#define CBALDURCHITIN_H_

#include <afxwin.h>

#include "CBaldurMessage.h"
#include "CCacheStatus.h"
#include "CChitin.h"
#include "CMessageHandler.h"
#include "CSwitchCDStatus.h"
#include "CTlkTable.h"
#include "CVidFont.h"

class CBaldurChitin : public CChitin {
public:
    // TODO: Some kind of layout info.
    struct S49B4 {
        /* 0000 */ int field_0;
        /* 0004 */ short field_4;
        /* 0006 */ short field_6;
        /* 0008 */ short field_8;
        /* 000A */ short field_A;
        /* 000C */ short field_C;
        /* 0010 */ char field_10[8];
    };

    static const USHORT DEFAULT_SCREEN_WIDTH;
    static const USHORT DEFAULT_SCREEN_HEIGHT;

    static short word_8BA320;
    static CString string_8C8CA0;
    static RECT stru_8E7538;
    static RECT stru_8E7548;
    static RECT stru_8E7958;
    static RECT stru_8E7988;
    static RECT stru_8E79A8;
    static RECT stru_8E79B8;
    static RECT stru_8E79C8;
    static RECT stru_8E79E0;
    static RECT stru_8E79F8;
    static RECT stru_8E7A10;

    CBaldurChitin();
    ~CBaldurChitin();
    void Init(HINSTANCE hInstance);
    void SaveOptions();

    /* 0010 */ DWORD GetIDSExclusiveMode();
    /* 009C */ void ShutDown(int nLineNumber, const char* szFileName, const char* text);
    /* 00A0 */ const char* GetConfigFileName();
    /* 00A4 */ const char* GetKeyFileName();
    /* 00A8 */ const char* GetLogFileName();
    /* 00A8 */ const char* GetErrorFileName();
    /* 00B0 */ void SaveBitsPerPixel(USHORT nBpp);

    /* 1C50 */ int field_1C50;
    /* 1C54 */ int field_1C54;
    /* 1C58 */ int field_1C58;
    /* 1C5C */ int field_1C5C;
    /* 1C60 */ int field_1C60;
    /* 1C64 */ int field_1C64;
    /* 1C68 */ int field_1C68;
    /* 1C6C */ int field_1C6C;
    /* 1C70 */ int field_1C70;
    /* 1C74 */ int field_1C74;
    /* 1C78 */ int field_1C78;
    /* 1C7C */ int field_1C7C;
    /* 1C80 */ int field_1C80;
    /* 1C84 */ int field_1C84;
    /* 1C88 */ int field_1C88;
    /* 1C8C */ int field_1C8C;
    /* 1C90 */ int field_1C90;
    /* 1C94 */ int field_1C94;
    /* 1C98 */ int field_1C98;
    /* 1C9C */ int field_1C9C;
    /* 1CA0 */ int field_1CA0;
    /* 1CA4 */ int field_1CA4;
    /* 1CA8 */ int field_1CA8;
    /* 1CAC */ CTlkTable m_cTlkTable;
    /* 1D52 */ CCacheStatus m_cCachingStatus;
    /* 3970 */ CSwitchCDStatus m_cSwitchingCDStatus; // #guess
    /* 4888 */ CBaldurMessage m_cBaldurMessage;
    /* 4980 */ CMessageHandler m_cMessageHandler;
    /* 499E */ int field_499E;
    /* 49A2 */ int field_49A2;
    /* 49A6 */ int field_49A6;
    /* 49AA */ unsigned char field_49AA;
    /* 49AB */ unsigned char field_49AB;
    /* 49B0 */ unsigned char field_49B0;
    /* 49B1 */ unsigned char field_49B1;
    /* 49AC */ CString field_49AC;
    /* 49B2 */ unsigned char field_49B2;
    /* 49B4 */ S49B4 field_49B4[4];
    /* 4A24 */ int field_4A24;
    /* 4A28 */ int field_4A28;
    /* 4A2C */ int field_4A2C;
    /* 4A34 */ CVidFont field_4A34;
    /* 4F38 */ int field_4F38;
    /* 4F3C */ int field_4F3C;
};

extern CBaldurChitin* g_pBaldurChitin;

#endif /* CBALDURCHITIN_H_ */

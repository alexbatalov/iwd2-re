#include "CCacheStatus.h"

#include "CBaldurChitin.h"

// 0x8A7BA8
int CCacheStatus::dword_8A7BA8 = 400;

// 0x8A7BAC
int CCacheStatus::dword_8A7BAC = 36;

// 0x8A7BB0
int CCacheStatus::dword_8A7BB0 = 320;

// 0x8A7BB4
int CCacheStatus::dword_8A7BB4 = 335;

// 0x8A7BB8
int CCacheStatus::dword_8A7BB8 = 18;

// 0x8A7BBC
int CCacheStatus::dword_8A7BBC = 50;

// 0x8A7BC0
int CCacheStatus::dword_8A7BC0 = 400;

// 0x8A7BC4
int CCacheStatus::dword_8A7BC4 = 481;

// 0x8A7BC8
int CCacheStatus::dword_8A7BC8 = 51;

// 0x8A7BCC
int CCacheStatus::dword_8A7BCC = 525;

// 0x8A7BD0
int CCacheStatus::dword_8A7BD0 = 595;

// 0x8A7BD4
int CCacheStatus::dword_8A7BD4 = 45;

// 0x8A7BD8
int CCacheStatus::dword_8A7BD8 = 26;

// 0x8A7BDC
int CCacheStatus::dword_8A7BDC = 7;

// 0x8A7BE0
int CCacheStatus::dword_8A7BE0 = 4;

// 0x8A7BE4
int CCacheStatus::dword_8A7BE4 = 230;

// 0x8A7BE8
int CCacheStatus::dword_8A7BE8 = 5;

// 0x8A7BEC
int CCacheStatus::dword_8A7BEC = 40;

// 0x8A7BF0
int CCacheStatus::dword_8A7BF0 = 155;

// 0x8A7BF4
int CCacheStatus::dword_8A7BF4 = 180;

// 0x8A7BF8
int CCacheStatus::dword_8A7BF8 = 80;

// 0x8A7BFC
int CCacheStatus::dword_8A7BFC = 20;

// 0x8A7C00
int CCacheStatus::dword_8A7C00 = 98;

// 0x8A7C04
int CCacheStatus::dword_8A7C04 = 35;

// 0x8A7C08
int CCacheStatus::dword_8A7C08 = 8;

// 0x8A7C0C
int CCacheStatus::dword_8A7C0C = 14;

// 0x8A7C10
int CCacheStatus::dword_8A7C10 = 48;

// 0x8A7C14
int CCacheStatus::dword_8A7C14 = 87;

// 0x8A7C18
int CCacheStatus::dword_8A7C18 = 20;

// 0x8A7C1C
int CCacheStatus::dword_8A7C1C = 24;

// 0x8A7C20
int CCacheStatus::dword_8A7C20 = 116;

// 0x8A7C24
int CCacheStatus::dword_8A7C24 = 39;

// 0x8A7C28
int CCacheStatus::dword_8A7C28 = 415;

// 0x8A7C2C
int CCacheStatus::dword_8A7C2C = 100;

// 0x8A7C30
int CCacheStatus::dword_8A7C30 = 130;

// 0x8A7C34
int CCacheStatus::dword_8A7C34 = 142;

// 0x8A7C38
int CCacheStatus::dword_8A7C38 = 159;

// 0x8A7C3C
int CCacheStatus::dword_8A7C3C = 466;

// 0x8D0770
int CCacheStatus::dword_8D0770 = dword_8A7BB8 + 84;

// 0x8D0B7C
int CCacheStatus::dword_8D0B7C = dword_8A7BBC + 47;

// 0x8D0B80
int CCacheStatus::dword_8D0B80 = dword_8A7BC8 + 22;

// 0x8D0B8C
int CCacheStatus::dword_8D0B8C = dword_8A7BCC + 18;

// 0x8D0B90
int CCacheStatus::dword_8D0B90 = dword_8A7BC8 + 623;

// 0x8D0BA0
int CCacheStatus::dword_8D0BA0 = dword_8A7BCC + 2;

// 0x8D0BA4
int CCacheStatus::dword_8D0BA4;

// 0x4400D0
CCacheStatus::CCacheStatus()
{
    m_nScreensDrawn = 0;
    field_8 = 0;
    field_C = 0;
    field_10 = 0;
    field_14 = 0;
    field_18 = 0;
    m_bActivateEngine = FALSE;
    field_1C1A = 0;
}

// 0x440270
CCacheStatus::~CCacheStatus()
{
}

// 0x440400
void CCacheStatus::Init()
{
    if (g_pBaldurChitin->field_4A28) {
        dword_8A7BA8 *= 2;
        dword_8A7BAC *= 2;
        dword_8A7BB0 *= 2;
        dword_8A7BB4 *= 2;
        dword_8A7BB8 *= 2;
        dword_8A7BBC *= 2;
        dword_8D0B7C *= 2;
        dword_8D0770 *= 2;
        dword_8A7BC4 *= 2;
        dword_8A7BC0 *= 2;
        dword_8A7BC8 *= 2;
        dword_8A7BCC *= 2;
        dword_8D0B80 *= 2;
        dword_8A7BD0 *= 2;
        dword_8A7BD4 *= 2;
        dword_8D0B8C *= 2;
        dword_8A7BD8 *= 2;
        dword_8A7BDC *= 2;
        dword_8A7BE0 *= 2;
        dword_8D0B90 *= 2;
        dword_8D0BA0 *= 2;
        dword_8A7BE4 *= 2;
        dword_8A7BE8 *= 2;
        dword_8A7BEC *= 2;
        dword_8A7BF0 *= 2;
        dword_8A7BF4 *= 2;
        dword_8A7BF8 *= 2;
        dword_8A7BFC *= 2;
        dword_8A7C00 *= 2;
        dword_8A7C04 *= 2;
        dword_8D0BA4 *= 2; // NOTE: This value is not initialized.
        dword_8A7C08 *= 2;
        dword_8A7C0C *= 2;
        dword_8A7C10 *= 2;
        dword_8A7C14 *= 2;
        dword_8A7C18 *= 2;
        dword_8A7C1C *= 2;
        dword_8A7C20 *= 2;
        dword_8A7C24 *= 2;
        dword_8A7C28 *= 2;
        dword_8A7C2C *= 2;
        dword_8A7C30 *= 2;
        dword_8A7C34 *= 2;
        dword_8A7C38 *= 2;
        dword_8A7C3C *= 2;
    }
}

// 0x4406A0
void CCacheStatus::InvalidateScreen()
{
    m_nScreensDrawn = 0;
}

// 0x4406B0
void CCacheStatus::Update(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
    // TODO: Incomplete.
}

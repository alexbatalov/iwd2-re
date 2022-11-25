#include "CBaldurChitin.h"

#include "CUtil.h"

#define FILE_NAME ".\\Icewind2.ini"
#define PROGRAM_OPTIONS_SECTION_KEY "Program Options"
#define FONT_NAME_KEY "Font Name"
#define DOUBLE_BYTE_CHARACTER_SUPPORT_KEY "Double Byte Character Support"
#define SIXTEEN_BIT_TEXTURES_KEY "16Bit Textures"
#define FULL_SCREEN_KEY "Full Screen"
#define DISPLAY_FREQUENCY_KEY "Display Frequency"
#define RESOLUTION_KEY "Resolution"
#define SCREEN_POSITION_X_KEY "Screen Position X"
#define SCREEN_POSITION_Y_KEY "Screen Position Y"
#define SOFT_BLT_KEY "SoftBlt"
#define SOFT_BLT_FAST_KEY "SoftBltFast"
#define SOFT_MIRROR_BLT_KEY "SoftMirrorBlt"
#define SOFT_SRC_KEY_BLT_KEY "SoftSrcKeyBlt"
#define SOFT_SRC_KEY_BLT_FAST_KEY "SoftSrcKeyBltFast"
#define USE_MIRROR_FX_KEY "Use Mirror FX"
#define STRREF_ON_KEY "Strref On"
#define BITS_PER_PIXEL_KEY "BitsPerPixel"

CChitin* g_pChitin;
CBaldurChitin* g_pBaldurChitin;

// #guess
// 0x85DE3C
const USHORT CBaldurChitin::DEFAULT_SCREEN_WIDTH = 800;

// #guess
// 0x85DE3E
const USHORT CBaldurChitin::DEFAULT_SCREEN_HEIGHT = 600;

// 0x8BA320
short CBaldurChitin::word_8BA320 = 100;

// 0x8C8CA0
CString CBaldurChitin::string_8C8CA0;

// 0x8E7538
RECT CBaldurChitin::stru_8E7538;

// 0x8E7548
RECT CBaldurChitin::stru_8E7548;

// 0x8E7958
RECT CBaldurChitin::stru_8E7958;

// 0x8E7988
RECT CBaldurChitin::stru_8E7988;

// 0x8E79A8
RECT CBaldurChitin::stru_8E79A8;

// 0x8E79B8
RECT CBaldurChitin::stru_8E79B8;

// 0x8E79C8
RECT CBaldurChitin::stru_8E79C8;

// 0x8E79E0
RECT CBaldurChitin::stru_8E79E0;

// 0x8E79F8
RECT CBaldurChitin::stru_8E79F8;

// 0x8E7A10
RECT CBaldurChitin::stru_8E7A10;

// 0x421E40
CBaldurChitin::CBaldurChitin()
{
    field_1C50 = 0;
    field_1C58 = 0;
    field_1C5C = 0;
    field_1C60 = 0;
    field_1C64 = 0;
    field_1C68 = 0;
    field_1C6C = 0;
    field_1C70 = 0;
    field_1C74 = 0;
    field_1C78 = 0;
    field_1C7C = 0;
    field_1C80 = 0;
    field_1C84 = 0;
    field_1C88 = 0;
    field_1C8C = 0;
    field_1C90 = 0;
    field_1C94 = 0;
    field_1C98 = 0;
    field_1C9C = 0;
    field_1CA0 = 0;
    field_1CA4 = 0;
    field_1CA8 = 0;
    field_1C54 = 0;
    field_499E = 0;
    field_49B2 = 1;

    GetPrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FONT_NAME_KEY,
        "",
        m_sFontName.GetBuffer(128),
        128,
        FILE_NAME);
    m_sFontName.ReleaseBuffer();

    field_1A0 = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DOUBLE_BYTE_CHARACTER_SUPPORT_KEY,
        0,
        FILE_NAME);
    if (field_1A0 != 0) {
        if (m_sFontName.Compare("") == 0) {
            switch (PRIMARYLANGID(GetSystemDefaultLangID())) {
            case LANG_CHINESE:
                switch (SUBLANGID(GetSystemDefaultLangID())) {
                case SUBLANG_CHINESE_TRADITIONAL:
                    m_sFontName = "\xB7\x73\xB2\xD3\xA9\xFA\xC5\xE9";
                    break;
                case SUBLANG_CHINESE_SIMPLIFIED:
                    m_sFontName = "\xCB\xCe\xCC\xE5";
                    break;
                }
                break;
            case LANG_JAPANESE:
                m_sFontName = "\x82\x6C\x82\x72\x20\x82\x6F\x83\x53\x83\x56\x83\x62\x83\x4E";
                break;
            case LANG_KOREAN:
                m_sFontName = "\xB1\xBC\xB8\xB2\xC3\xBC";
                break;
            }
        }
    }

    field_1A4 = field_1A0;

    // NOTE: Result is unused. Probably empty condition.
    m_sFontName.Compare("");

    field_2F4 = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SIXTEEN_BIT_TEXTURES_KEY,
        0,
        FILE_NAME);

    m_bFullscreen = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        FULL_SCREEN_KEY,
        TRUE,
        FILE_NAME);

    if (CUtil::GetCurrentBitsPerPixels() < 16) {
        m_bFullscreen = TRUE;
        field_E4 = 1;
    }

    field_E2 = m_bFullscreen;

    CVideo::FPS = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_FREQUENCY_KEY,
        60,
        FILE_NAME);

    if (CVideo::FPS < 60) {
        CVideo::FPS = 60;
    }

    cVideo.m_bIs3dAccelerated = FALSE;

    memset(field_49B4, 0, sizeof(field_49B4));
    field_4A24 = 1;

    CVideo::SCREENWIDTH = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        RESOLUTION_KEY,
        800,
        FILE_NAME);

    if (CVideo::SCREENWIDTH >= GetSystemMetrics(SM_CXFULLSCREEN)) {
        field_E4 = 1;
        field_E2 = 1;
        m_bFullscreen = TRUE;
    }

    field_4A28 = 0;
    field_4A2C = 0;

    // TODO: Check, assignments to rects are in random order.
    switch (CVideo::SCREENWIDTH) {
    case 2048:
        stru_8E7538.left = 0;
        stru_8E7538.top = 0;
        stru_8E7538.right = 960;
        stru_8E7538.bottom = 658;

        stru_8E7548.left = 0;
        stru_8E7548.top = 0;
        stru_8E7548.right = 2048;
        stru_8E7548.bottom = 1536;

        stru_8E7958.left = 0;
        stru_8E7958.top = 0;
        stru_8E7958.right = 2048;
        stru_8E7958.bottom = 968;

        stru_8E7988.left = 0;
        stru_8E7988.top = 0;
        stru_8E7988.right = 2048;
        stru_8E7988.bottom = 1258;

        stru_8E79A8.left = 256;
        stru_8E79A8.top = 150;
        stru_8E79A8.right = 768;
        stru_8E79A8.bottom = 534;

        stru_8E79B8.left = 0;
        stru_8E79B8.top = 0;
        stru_8E79B8.right = 2048;
        stru_8E79B8.bottom = 1202;

        stru_8E79C8.left = 0;
        stru_8E79C8.top = 0;
        stru_8E79C8.right = 2048;
        stru_8E79C8.bottom = 1416;

        stru_8E79E0.left = 0;
        stru_8E79E0.top = 0;
        stru_8E79E0.right = 2048;
        stru_8E79E0.bottom = 1322;

        stru_8E79F8.left = 0;
        stru_8E79F8.top = 0;
        stru_8E79F8.right = 2048;
        stru_8E79F8.bottom = 1288;

        stru_8E7A10.left = 0;
        stru_8E7A10.top = 0;
        stru_8E7A10.right = 960;
        stru_8E7A10.bottom = 522;

        CVideo::SCREENHEIGHT = 1536;
        string_8C8CA0 = "10";
        strncpy(field_49B4[0].field_10, "STON10L", sizeof(field_49B4[0].field_10));
        strncpy(field_49B4[1].field_10, "STON10R", sizeof(field_49B4[1].field_10));
        strncpy(field_49B4[2].field_10, "STON10T", sizeof(field_49B4[2].field_10));
        strncpy(field_49B4[3].field_10, "STON10B", sizeof(field_49B4[3].field_10));
        break;
    case 1600:
        stru_8E7538.left = 0;
        stru_8E7538.top = 0;
        stru_8E7538.right = 736;
        stru_8E7538.bottom = 490;

        stru_8E7548.left = 0;
        stru_8E7548.top = 0;
        stru_8E7548.right = 1600;
        stru_8E7548.bottom = 1200;

        stru_8E7958.left = 0;
        stru_8E7958.top = 0;
        stru_8E7958.right = 1600;
        stru_8E7958.bottom = 632;

        stru_8E7988.left = 0;
        stru_8E7988.top = 0;
        stru_8E7988.right = 1600;
        stru_8E7988.bottom = 922;

        stru_8E79A8.left = 544;
        stru_8E79A8.top = 366;
        stru_8E79A8.right = 1056;
        stru_8E79A8.bottom = 750;

        stru_8E79B8.left = 0;
        stru_8E79B8.top = 0;
        stru_8E79B8.right = 1600;
        stru_8E79B8.bottom = 866;

        stru_8E79C8.left = 0;
        stru_8E79C8.top = 0;
        stru_8E79C8.right = 1600;
        stru_8E79C8.bottom = 1080;

        stru_8E79E0.left = 0;
        stru_8E79E0.top = 0;
        stru_8E79E0.right = 1600;
        stru_8E79E0.bottom = 986;

        stru_8E79F8.left = 0;
        stru_8E79F8.top = 0;
        stru_8E79F8.right = 1600;
        stru_8E79F8.bottom = 952;

        stru_8E7A10.left = 0;
        stru_8E7A10.top = 0;
        stru_8E7A10.right = 736;
        stru_8E7A10.bottom = 354;

        CVideo::SCREENHEIGHT = 1200;
        string_8C8CA0 = "08";
        break;
    case 1024:
        stru_8E7538.left = 0;
        stru_8E7538.top = 0;
        stru_8E7538.right = 960;
        stru_8E7538.bottom = 658;

        stru_8E7548.left = 0;
        stru_8E7548.top = 0;
        stru_8E7548.right = 1024;
        stru_8E7548.bottom = 768;

        stru_8E7958.left = 0;
        stru_8E7958.top = 0;
        stru_8E7958.right = 1024;
        stru_8E7958.bottom = 484;

        stru_8E7988.left = 0;
        stru_8E7988.top = 0;
        stru_8E7988.right = 1024;
        stru_8E7988.bottom = 629;

        stru_8E79A8.left = 256;
        stru_8E79A8.top = 150;
        stru_8E79A8.right = 768;
        stru_8E79A8.bottom = 534;

        stru_8E79B8.left = 0;
        stru_8E79B8.top = 0;
        stru_8E79B8.right = 1024;
        stru_8E79B8.bottom = 601;

        stru_8E79C8.left = 0;
        stru_8E79C8.top = 0;
        stru_8E79C8.right = 1024;
        stru_8E79C8.bottom = 708;

        stru_8E79E0.left = 0;
        stru_8E79E0.top = 0;
        stru_8E79E0.right = 1024;
        stru_8E79E0.bottom = 661;

        stru_8E79F8.left = 0;
        stru_8E79F8.top = 0;
        stru_8E79F8.right = 1024;
        stru_8E79F8.bottom = 644;

        stru_8E7A10.left = 0;
        stru_8E7A10.top = 0;
        stru_8E7A10.right = 960;
        stru_8E7A10.bottom = 522;

        CVideo::SCREENHEIGHT = 768;
        string_8C8CA0 = "10";
        strncpy(field_49B4[0].field_10, "STON10L", sizeof(field_49B4[0].field_10));
        strncpy(field_49B4[1].field_10, "STON10R", sizeof(field_49B4[1].field_10));
        strncpy(field_49B4[2].field_10, "STON10T", sizeof(field_49B4[2].field_10));
        strncpy(field_49B4[3].field_10, "STON10B", sizeof(field_49B4[3].field_10));
        break;
    case 800:
    default:
        stru_8E7538.left = 0;
        stru_8E7538.top = 0;
        stru_8E7538.right = 736;
        stru_8E7538.bottom = 490;

        stru_8E7548.left = 0;
        stru_8E7548.top = 0;
        stru_8E7548.right = 800;
        stru_8E7548.bottom = 600;

        stru_8E7958.left = 0;
        stru_8E7958.top = 0;
        stru_8E7958.right = 800;
        stru_8E7958.bottom = 316;

        stru_8E7988.left = 0;
        stru_8E7988.top = 0;
        stru_8E7988.right = 800;
        stru_8E7988.bottom = 461;

        stru_8E79A8.left = 144;
        stru_8E79A8.top = 66;
        stru_8E79A8.right = 656;
        stru_8E79A8.bottom = 450;

        stru_8E79B8.left = 0;
        stru_8E79B8.top = 0;
        stru_8E79B8.right = 800;
        stru_8E79B8.bottom = 433;

        stru_8E79C8.left = 0;
        stru_8E79C8.top = 0;
        stru_8E79C8.right = 800;
        stru_8E79C8.bottom = 540;

        stru_8E79E0.left = 0;
        stru_8E79E0.top = 0;
        stru_8E79E0.right = 800;
        stru_8E79E0.bottom = 493;

        stru_8E79F8.left = 0;
        stru_8E79F8.top = 0;
        stru_8E79F8.right = 800;
        stru_8E79F8.bottom = 476;

        stru_8E7A10.left = 0;
        stru_8E7A10.top = 0;
        stru_8E7A10.right = 736;
        stru_8E7A10.bottom = 354;

        CVideo::SCREENHEIGHT = 600;
        string_8C8CA0 = "08";
        break;
    }

    word_8BA320 = 3 * (((stru_8E7548.right - stru_8E7548.left + 63) / 64 + 1) * ((stru_8E7548.bottom - stru_8E7548.top + 63) / 64 + 1)) / 2;

    // TODO: Check assignments to `field_49B4`. In binary they appear in random
    // order.
    field_49B4[0].field_0 = -5;
    field_49B4[0].field_C = 1;
    field_49B4[0].field_A = CVideo::SCREENHEIGHT;
    field_49B4[0].field_8 = (CVideo::SCREENWIDTH - DEFAULT_SCREEN_WIDTH) / 2;
    field_49B4[0].field_4 = 0;
    field_49B4[0].field_6 = 0;

    field_49B4[1].field_0 = -4;
    field_49B4[1].field_C = 1;
    field_49B4[1].field_A = CVideo::SCREENHEIGHT;
    field_49B4[1].field_8 = (CVideo::SCREENWIDTH - DEFAULT_SCREEN_WIDTH) / 2;
    field_49B4[1].field_4 = field_49B4[0].field_8 + DEFAULT_SCREEN_WIDTH;
    field_49B4[1].field_6 = 0;

    field_49B4[2].field_0 = -3;
    field_49B4[2].field_C = 1;
    field_49B4[2].field_A = (CVideo::SCREENHEIGHT - DEFAULT_SCREEN_HEIGHT) / 2;
    field_49B4[2].field_8 = DEFAULT_SCREEN_WIDTH;
    field_49B4[2].field_4 = field_49B4[0].field_8;
    field_49B4[2].field_6 = 0;

    field_49B4[3].field_0 = -2;
    field_49B4[3].field_C = 1;
    field_49B4[3].field_A = (CVideo::SCREENHEIGHT - DEFAULT_SCREEN_HEIGHT) / 2;
    field_49B4[3].field_8 = DEFAULT_SCREEN_WIDTH;
    field_49B4[3].field_4 = field_49B4[0].field_8;
    field_49B4[3].field_6 = field_49B4[2].field_A + DEFAULT_SCREEN_HEIGHT;

    m_ptScreen.x = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SCREEN_POSITION_X_KEY,
        (GetSystemMetrics(SM_CXFULLSCREEN) - CVideo::SCREENWIDTH) / 2,
        FILE_NAME);
    m_ptScreen.y = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SCREEN_POSITION_Y_KEY,
        (GetSystemMetrics(SM_CYFULLSCREEN) - CVideo::SCREENHEIGHT) / 2,
        FILE_NAME);

    field_49A2 = 292;
    field_49A6 = 20186;
    field_49AA = 0;
    field_49AB = 0;
    field_49B0 = 0;
    field_49B1 = 0;

    cVideo.cVidBlitter.m_bSoftBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftBltFast = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftMirrorBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftSrcKeyBlt = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    cVideo.cVidBlitter.m_bSoftSrcKeyBltFast = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        FALSE,
        FILE_NAME);
    cVideo.cVidBlitter.field_E6 = 0;

    m_bUseMirrorFX = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        USE_MIRROR_FX_KEY,
        TRUE,
        FILE_NAME);

    CTlkTable::STRREF_ON = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        STRREF_ON_KEY,
        FALSE,
        FILE_NAME);

    g_pBaldurChitin = this;
    g_pChitin = this;

    m_cCachingStatus.Init();
    m_cSwitchingCDStatus.Init();

    g_pChitin->field_2EC = field_4A28;
    field_4F38 = 0;
    field_4F3C = 0;
}

// 0x422EB0
CBaldurChitin::~CBaldurChitin()
{
    // TODO: Incomplete.
}

// 0x423800
void CBaldurChitin::Init(HINSTANCE hInstance)
{
    // TODO: Incomplete.
}

// #guess
// 0x422BA0
DWORD CBaldurChitin::GetIDSExclusiveMode()
{
    return 5;
}

// 0x424D60
void CBaldurChitin::ShutDown(int nLineNumber, const char* szFileName, const char* text)
{
    if (nLineNumber == -1) {
        SaveOptions();
    }
    CChitin::ShutDown(nLineNumber, szFileName, text);
}

// #guess
// 0x422DE0
const char* CBaldurChitin::GetConfigFileName()
{
    return ".\\Icewind2.ini";
}

// 0x422DF0
const char* CBaldurChitin::GetKeyFileName()
{
    return ".\\Chitin.key";
}

// #guess
// 0x422E00
const char* CBaldurChitin::GetLogFileName()
{
    return ".\\Icewind2.log";
}

// #guess
// 0x422E10
const char* CBaldurChitin::GetErrorFileName()
{
    return ".\\Icewind2.err";
}

// 0x425040
void CBaldurChitin::SaveOptions()
{
    // TODO: Incomplete.
}

// 0x425680
void CBaldurChitin::SaveBitsPerPixel(USHORT nBpp)
{
    switch (nBpp) {
    case 16:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "16",
            GetConfigFileName());
        break;
    case 24:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "24",
            GetConfigFileName());
        break;
    case 32:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "32",
            GetConfigFileName());
        break;
    }
}

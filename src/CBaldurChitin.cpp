#include "CBaldurChitin.h"

#include "CBaldurProjector.h"
#include "CDungeonMaster.h"
#include "CGameAnimationType.h"
#include "CInfCursor.h"
#include "CInfGame.h"
#include "CResItem.h"
#include "CResUI.h"
#include "CResWED.h"
#include "CScreenChapter.h"
#include "CScreenCharacter.h"
#include "CScreenConnection.h"
#include "CScreenCreateChar.h"
#include "CScreenInventory.h"
#include "CScreenJournal.h"
#include "CScreenKeymaps.h"
#include "CScreenLoad.h"
#include "CScreenMap.h"
#include "CScreenMovies.h"
#include "CScreenMultiPlayer.h"
#include "CScreenOptions.h"
#include "CScreenSave.h"
#include "CScreenSinglePlayer.h"
#include "CScreenSpellbook.h"
#include "CScreenStart.h"
#include "CScreenStore.h"
#include "CScreenWorld.h"
#include "CScreenWorldMap.h"
#include "CSearchBitmap.h"
#include "CUtil.h"
#include "resource.h"

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
#define FIRST_RUN_KEY "First Run"
#define IS_3D_ACCELERATED "3D Acceleration"
#define MAXIMUM_FRAME_RATE_KEY "Maximum Frame Rate"
#define PATH_SEARCH_NODES_KEY "Path Search Nodes"
#define TOOLTIPS_KEY "Tooltips"
#define TRANSLUCENT_SHADOWS_KEY "Translucent Shadows"
#define SPRITE_MIRROR_KEY "Sprite Mirror"
#define GAMMA_CORRECTION_KEY "Gamma Correction"
#define BRIGHTNESS_CORRECTION_KEY "Brightness Correction"
#define BACKWARDS_COMPATIBLE_3D_KEY "Backwards Compatible 3d"
#define VOLUME_MOVIE_KEY "Volume Movie"
#define VOLUME_MUSIC_KEY "Volume Music"
#define VOLUME_VOICES_KEY "Volume Voices"
#define VOLUME_AMBIENTS_KEY "Volume Ambients"
#define VOLUME_SFX_KEY "Volume SFX"
#define DISPLAY_MOVIE_SUBTITLES_KEY "Display Movie Subtitles"
#define SHADED_SELECTION_BOX_KEY "Shaded Selection Box"
#define SINGLE_MEDIA_KEY "Single Media"

CChitin* g_pChitin;
CBaldurChitin* g_pBaldurChitin;

// #guess
// 0x85DE3C
const USHORT CBaldurChitin::DEFAULT_SCREEN_WIDTH = 800;

// #guess
// 0x85DE3E
const USHORT CBaldurChitin::DEFAULT_SCREEN_HEIGHT = 600;

// #guess
// 0x8AB948
BYTE CBaldurChitin::RENDER_COUNT = 2;

// NOTE: Probably static in `CBaldurChitin`.
//
// 0x8BA28C
unsigned char byte_8BA28C = 1;

// 0x8BA320
short CBaldurChitin::word_8BA320 = 100;

// 0x8C8CA0
CString CBaldurChitin::CHUI_GUIEXT("");

// 0x8CB200
const CString CBaldurChitin::BALDUR_GAMESPY_GAMENAME("iwd2");

// 0x8CD358
const CString CBaldurChitin::BALDUR_GAMESPY_CODE1("]s{=$b");

// 0x8CD440
const CString CBaldurChitin::BALDUR_GAMESPY_CODE2("^@FH?2");

// 0x8CD340
const CString CBaldurChitin::BALDUR_GAMESPY_CODE3("Si8F5s");

// 0x8CB1A8
const CString CBaldurChitin::BALDUR_GAMESPY_CODE4("_0#9fJ");

// #guess
// 0x8CB238
CString CBaldurChitin::OVERRIDE_DIR_NAME(".\\override\\");

// 0x8CD308
const CString CBaldurChitin::PRINTSCREEN_FILE_NAME("iwd2");

// 0x8CD43C
const CString CBaldurChitin::ICON_RES_ID("IDI_GAMEICON");

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
    m_pObjectCursor = NULL;
    m_pEngineDM = NULL;
    m_pEngineProjector = NULL;
    m_pEngineCharacter = NULL;
    m_pEngineCreateChar = NULL;
    m_pEngineInventory = NULL;
    m_pEngineJournal = NULL;
    m_pEngineLoad = NULL;
    m_pEngineMap = NULL;
    m_pEngineOptions = NULL;
    m_pEngineSave = NULL;
    m_pEngineSpellbook = NULL;
    m_pEngineStart = NULL;
    m_pEngineWorld = NULL;
    m_pEngineStore = NULL;
    m_pEngineMultiPlayer = NULL;
    m_pEngineSinglePlayer = NULL;
    m_pEngineConnection = NULL;
    m_pEngineWorldMap = NULL;
    m_pEngineChapter = NULL;
    m_pEngineMovies = NULL;
    m_pEngineKeymaps = NULL;
    m_pObjectGame = NULL;
    m_bFontRectOutline = FALSE;
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
        CHUI_GUIEXT = "10";
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
        CHUI_GUIEXT = "08";
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
        CHUI_GUIEXT = "10";
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
        CHUI_GUIEXT = "08";
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
    if (CTlkTable::STRREF_ON) {
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            STRREF_ON_KEY,
            "1",
            FILE_NAME);
    } else {
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            STRREF_ON_KEY,
            "0",
            FILE_NAME);
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FIRST_RUN_KEY,
        "1",
        FILE_NAME);

    m_cTlkTable.CloseFile(0, byte_8FB954);
    m_cTlkTable.CloseFile(0, byte_8BA28C);

    if (m_pObjectGame != NULL) {
        delete m_pObjectGame;
        m_pObjectGame = NULL;
    }

    if (m_pEngineChapter != NULL) {
        delete m_pEngineChapter;
        m_pEngineChapter = NULL;
    }

    if (m_pEngineWorld != NULL) {
        delete m_pEngineWorld;
        m_pEngineWorld = NULL;
    }

    if (m_pEngineStore != NULL) {
        delete m_pEngineStore;
        m_pEngineStore = NULL;
    }

    if (m_pEngineWorldMap != NULL) {
        delete m_pEngineWorldMap;
        m_pEngineWorldMap = NULL;
    }

    if (m_pEngineConnection != NULL) {
        delete m_pEngineConnection;
        m_pEngineConnection = NULL;
    }

    if (m_pEngineMultiPlayer != NULL) {
        delete m_pEngineMultiPlayer;
        m_pEngineMultiPlayer = NULL;
    }

    if (m_pEngineSinglePlayer != NULL) {
        delete m_pEngineSinglePlayer;
        m_pEngineSinglePlayer = NULL;
    }

    if (m_pEngineStart != NULL) {
        delete m_pEngineStart;
        m_pEngineStart = NULL;
    }

    if (m_pEngineSpellbook != NULL) {
        delete m_pEngineSpellbook;
        m_pEngineSpellbook = NULL;
    }

    if (m_pEngineSave != NULL) {
        delete m_pEngineSave;
        m_pEngineSave = NULL;
    }

    if (m_pEngineOptions != NULL) {
        delete m_pEngineOptions;
        m_pEngineOptions = NULL;
    }

    if (m_pEngineMap != NULL) {
        delete m_pEngineMap;
        m_pEngineMap = NULL;
    }

    if (m_pEngineLoad != NULL) {
        delete m_pEngineLoad;
        m_pEngineLoad = NULL;
    }

    if (m_pEngineJournal != NULL) {
        delete m_pEngineJournal;
        m_pEngineJournal = NULL;
    }

    if (m_pEngineInventory != NULL) {
        delete m_pEngineInventory;
        m_pEngineInventory = NULL;
    }

    if (m_pEngineCreateChar != NULL) {
        delete m_pEngineCreateChar;
        m_pEngineCreateChar = NULL;
    }

    if (m_pEngineCharacter != NULL) {
        delete m_pEngineCharacter;
        m_pEngineCharacter = NULL;
    }

    if (m_pEngineProjector != NULL) {
        delete m_pEngineProjector;
        m_pEngineProjector = NULL;
    }

    if (m_pEngineDM != NULL) {
        delete m_pEngineDM;
        m_pEngineDM = NULL;
    }

    if (m_pEngineMovies != NULL) {
        delete m_pEngineMovies;
        m_pEngineMovies = NULL;
    }

    if (m_pEngineKeymaps != NULL) {
        delete m_pEngineKeymaps;
        m_pEngineKeymaps = NULL;
    }

    if (m_pObjectCursor != NULL) {
        delete m_pObjectCursor;
        m_pObjectCursor = NULL;
    }

    if (field_4F40 != NULL) {
        delete field_4F40;
        field_4F40 = NULL;
    }
}

// 0x423210
CRes* CBaldurChitin::AllocResObject(int nType)
{
    switch (nType) {
    case 1001:
        return new CResWED();
    case 1002:
        return new CResUI();
    case 1005:
        return new CResItem();
    default:
        return CChitin::AllocResObject(nType);
    }
}

// 0x4237A0
void CBaldurChitin::AsynchronousUpdate(UINT nTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
    if (!field_E0) {
        m_cMessageHandler.AsynchronousUpdate();
    }

    CChitin::AsynchronousUpdate(nTimerID, uMsg, dwUser, dw1, dw2);

    if (!field_E0) {
        m_cMessageHandler.PostAsynchronousUpdate();
    }
}

// 0x423800
void CBaldurChitin::Init(HINSTANCE hInstance)
{
    CString maleURI;
    CString femaleURI;
    CString path;
    BOOLEAN bOpened;

    field_4F40 = new S4F40[64];
    for (int k = 0; k < 64; k++) {
        field_4F40[k].cResRef = "XXXXXXXX";
        field_4F40[k].field_8 = -1;
        field_4F40[k].field_C = 0;
        field_4F40[k].field_10 = 0;
    }

    g_pChitin->cDimm.AddToDirectoryList(OVERRIDE_DIR_NAME, FALSE);

    InitResources();

    m_pObjectCursor = new CInfCursor();

    m_pEngineDM = new CDungeonMaster();
    m_pEngineProjector = new CBaldurProjector();
    m_pEngineCharacter = new CScreenCharacter();
    m_pEngineCreateChar = new CScreenCreateChar();
    m_pEngineInventory = new CScreenInventory();
    m_pEngineJournal = new CScreenJournal();
    m_pEngineLoad = new CScreenLoad();
    m_pEngineMap = new CScreenMap();
    m_pEngineOptions = new CScreenOptions();
    m_pEngineSave = new CScreenSave();
    m_pEngineSpellbook = new CScreenSpellbook();
    m_pEngineStart = new CScreenStart();
    m_pEngineWorld = new CScreenWorld();
    m_pEngineStore = new CScreenStore();
    m_pEngineMultiPlayer = new CScreenMultiPlayer();
    m_pEngineSinglePlayer = new CScreenSinglePlayer();
    m_pEngineConnection = new CScreenConnection();
    m_pEngineWorldMap = new CScreenWorldMap();
    m_pEngineChapter = new CScreenChapter();
    m_pEngineKeymaps = new CScreenKeymaps();

    m_pObjectGame = new CInfGame();
    m_pObjectGame->StartSearchThread();

    m_pStartingEngine = m_pEngineDM;

    AddEngine(m_pEngineDM);
    AddEngine(m_pEngineProjector);
    AddEngine(m_pEngineCharacter);
    AddEngine(m_pEngineCreateChar);
    AddEngine(m_pEngineInventory);
    AddEngine(m_pEngineJournal);
    AddEngine(m_pEngineLoad);
    AddEngine(m_pEngineMap);
    AddEngine(m_pEngineOptions);
    AddEngine(m_pEngineSave);
    AddEngine(m_pEngineSpellbook);
    AddEngine(m_pEngineStart);
    AddEngine(m_pEngineWorld);
    AddEngine(m_pEngineStore);
    AddEngine(m_pEngineMultiPlayer);
    AddEngine(m_pEngineSinglePlayer);
    AddEngine(m_pEngineConnection);
    AddEngine(m_pEngineWorldMap);
    AddEngine(m_pEngineChapter);
    AddEngine(m_pEngineMovies);
    AddEngine(m_pEngineKeymaps);

    maleURI = "hd0:\\dialog.tlk";
    femaleURI = "hd0:\\dialogf.tlk";
    path = "";

    if (lAliases.ResolveFileName(femaleURI, path) == TRUE) {
        CFileStatus fileStatus;
        if (CFile::GetStatus(path, fileStatus)) {
            bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8BA28C, 1);
            if (bOpened) {
                if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                    bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, 1);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                    // __LINE__: 1148
                    UTIL_ASSERT(bOpened);
                }
            } else {
                byte_8BA28C = byte_8FB954;
                if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                    bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, 1);

                    // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                    // __LINE__: 1158
                    UTIL_ASSERT(bOpened);
                }
            }
        } else {
            byte_8BA28C = byte_8FB954;
            if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
                bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, 1);

                // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
                // __LINE__: 1169
                UTIL_ASSERT(bOpened);
            }
        }
    } else {
        byte_8BA28C = byte_8FB954;
        if (lAliases.ResolveFileName(maleURI, path) == TRUE) {
            bOpened = m_cTlkTable.AddTlkFile(path, 0, byte_8FB954, 1);

            // __FILE__: C:\Projects\Icewind2\src\Baldur\CBaldurChitin.cpp
            // __LINE__: 1181
            UTIL_ASSERT(bOpened);
        }
    }

    if (g_pChitin->cDimm.GetMemoryAmount() == 1) {
        CGameAnimationType::MIRROR_BAM = 1;
    }
}

// 0x424180
void CBaldurChitin::MessageThreadMain(void* userInfo)
{
    // TODO: Incomplete.
}

// 0x424220
void CBaldurChitin::MusicThreadMain(void* userInfo)
{
    RegisterThread();

    while (field_390 == 0) {
        g_pChitin->cSoundMixer.UpdateMusic();
        SleepEx(25, FALSE);
    }
}

// 0x424260
void CBaldurChitin::RSThreadMain(void* userInfo)
{
    RegisterThread();

    while (field_374 == 0) {
        cDimm.Update();

        if (field_374 == 0) {
            SuspendThread(m_hRSThread);
        }
    }
}

// 0x4242B0
void CBaldurChitin::MainAIThread(void* userInfo)
{
    // TODO: Incomplete.
}

// 0x422B80
DWORD CBaldurChitin::GetIDSInvalidVideoMode()
{
    return IDS_INVALID_VIDEO_MODE;
}

// 0x422B90
DWORD CBaldurChitin::GetIDSOpenGLDll()
{
    return IDS_OPENGLL_DLL;
}

// 0x422BA0
DWORD CBaldurChitin::GetIDSExclusiveMode()
{
    return IDS_EXSLUSIVE_MODE;
}

// 0x49FC40
DWORD CBaldurChitin::GetIDSChoosePixelFormat()
{
    return IDS_CHOOSE_PIXEL_FORMAT;
}

// 0x422BB0
DWORD CBaldurChitin::GetIDSSetPixelFormat()
{
    return IDS_SET_PIXEL_FORMAT;
}

// 0x422BC0
DWORD CBaldurChitin::GetIDSSetGameResolution()
{
    return IDS_SET_GAME_RESOLUTION;
}

// 0x422BD0
DWORD CBaldurChitin::GetIDSSetGameBitDepth()
{
    return IDS_SET_GAME_BIT_DEPTH;
}

// 0x422BE0
DWORD CBaldurChitin::GetIDSBadDeskTopBitDepth()
{
    return IDS_BAD_DESKTOP_BIT_DEPTH;
}

// 0x422BF0
DWORD CBaldurChitin::GetIDSWindowsFonts()
{
    return IDS_WINDOWS_FONTS;
}

// 0x422C00
const CString& CBaldurChitin::GetIconRes()
{
    return ICON_RES_ID;
}

// 0x422C10
void CBaldurChitin::GetScreenShotFilePrefix(CString& szGameFileName)
{
    szGameFileName = PRINTSCREEN_FILE_NAME;
}

// 0x422C30
void CBaldurChitin::SetProgressBarActivateEngine(BOOL bValue)
{
    m_cCachingStatus.m_bActivateEngine = bValue;
}

// 0x422C40
void CBaldurChitin::SetCDSwitchActivateEngine(BOOL bValue)
{
    m_cSwitchingCDStatus.m_bActivateEngine = bValue;
}

// 0x424A90
BOOL CBaldurChitin::InitializeServices(HWND hWnd)
{
    return CChitin::InitializeServices(hWnd);
}

// 0x424AA0
void CBaldurChitin::FlipFullScreenMode(BOOLEAN a2)
{
    BOOL bWasFullscreen = m_bFullscreen;
    m_bFullscreen = bWasFullscreen == FALSE;
    field_E2 = bWasFullscreen == FALSE;

    if (a2) {
        if (bWasFullscreen) {
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                FULL_SCREEN_KEY,
                "0",
                GetIniFileName());
        } else {
            CString sValue;

            sValue.Format("%d", m_ptScreen.x);
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                SCREEN_POSITION_X_KEY,
                sValue,
                GetIniFileName());

            sValue.Format("%d", m_ptScreen.y);
            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                SCREEN_POSITION_Y_KEY,
                sValue,
                GetIniFileName());

            WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
                FULL_SCREEN_KEY,
                "1",
                GetIniFileName());
        }
    }
}

// 0x424BD0
void CBaldurChitin::SetSoftSrcKeyBltFast(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftSrcKeyBltFast = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424C20
void CBaldurChitin::SetSoftBltFast(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftBltFast = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424C70
void CBaldurChitin::SetSoftSrcKeyBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftSrcKeyBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424CC0
void CBaldurChitin::SetSoftBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424D10
void CBaldurChitin::SetSoftMirrorBlt(BOOLEAN a2, BOOLEAN a3)
{
    cVideo.cVidBlitter.m_bSoftMirrorBlt = a2;
    cVideo.cVidBlitter.field_E6 = a3;

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        a2 ? "1" : "0",
        GetIniFileName());
}

// 0x424D60
void CBaldurChitin::ShutDown(int nLineNumber, const char* szFileName, const char* text)
{
    if (nLineNumber == -1) {
        SaveOptions();
    }
    CChitin::ShutDown(nLineNumber, szFileName, text);
}

// 0x422D70
BOOL CBaldurChitin::GetEAXActive()
{
    if (m_pObjectGame != NULL) {
        return m_pObjectGame->m_cOptions.m_bEnvironmentalAudio;
    }

    return FALSE;
}

// 0x422DC0
void CBaldurChitin::GetGameSpyGameName(CString& sGameSpyName)
{
    sGameSpyName = BALDUR_GAMESPY_GAMENAME;
}

// #guess
// 0x422DE0
const char* CBaldurChitin::GetIniFileName()
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
const char* CBaldurChitin::GetErrFileName()
{
    return ".\\Icewind2.err";
}

// 0x422E20
BYTE CBaldurChitin::GetNumberSoundChannels()
{
    return 21;
}

// 0x422E30
LONG CBaldurChitin::GetMovieVolume()
{
    // NOTE: Looks odd, generated binary does not match.
    LONG v1 = m_pObjectGame->m_cOptions.m_nVolumeMovie - 100;
    return -(v1 * v1);
}

// 0x422E70
void CBaldurChitin::UnloadFonts()
{
    field_4A34.Unload();
    CVidFont::UnloadAllFonts();
}

// 0x422EA0
void CBaldurChitin::SetRenderCount(BYTE nCount)
{
    RENDER_COUNT = nCount;
}

// 0x422E50
void CBaldurChitin::SetSoundVolumes()
{
    if (m_pObjectGame != NULL) {
        m_pObjectGame->ApplyVolumeSliders(TRUE);
    }
}

// 0x424D90
void CBaldurChitin::LoadOptions()
{
    CGameOptions* pOptions = &(m_pObjectGame->m_cOptions);

    pOptions->m_nTooltips = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        TOOLTIPS_KEY,
        30,
        GetIniFileName());

    pOptions->m_nTranslucentShadows = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        TRANSLUCENT_SHADOWS_KEY,
        1,
        GetIniFileName());

    CVidCell::TRANSLUCENT_SHADOWS_ON = pOptions->m_nTranslucentShadows;

    if (pOptions->m_nTooltips > 99 && pOptions->m_nTooltips != INT_MAX) {
        pOptions->m_nTooltips = 30;
    }

    BYTE nGammaCorrection = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        GAMMA_CORRECTION_KEY,
        0,
        GetIniFileName());
    if (nGammaCorrection < 0 || nGammaCorrection > 5) {
        nGammaCorrection = 0;
    }

    cVideo.m_pVidModes[0]->m_nGammaCorrection = nGammaCorrection;

    BYTE nBrightnessCorrection = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BRIGHTNESS_CORRECTION_KEY,
        0,
        GetIniFileName());
    if (nBrightnessCorrection < 0 || nBrightnessCorrection > 40) {
        nBrightnessCorrection = 0;
    }

    cVideo.m_pVidModes[0]->m_nBrightnessCorrection = nBrightnessCorrection;

    cVideo.field_13A = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BACKWARDS_COMPATIBLE_3D_KEY,
        0,
        GetIniFileName());

    CGameAnimationType::MIRROR_BAM = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SPRITE_MIRROR_KEY,
        CGameAnimationType::MIRROR_BAM,
        GetIniFileName());

    pOptions->m_nVolumeMovie = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MOVIE_KEY,
        85,
        GetIniFileName());
    if (pOptions->m_nVolumeMovie > 100) {
        pOptions->m_nVolumeMovie = 85;
    }

    pOptions->m_nVolumeMusic = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MUSIC_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeMusic > 100) {
        pOptions->m_nVolumeMusic = 100;
    }

    pOptions->m_nVolumeVoices = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_VOICES_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeVoices > 100) {
        pOptions->m_nVolumeVoices = 100;
    }

    pOptions->m_nVolumeAmbients = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_AMBIENTS_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeAmbients > 100) {
        pOptions->m_nVolumeAmbients = 100;
    }

    pOptions->m_nVolumeSFX = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_SFX_KEY,
        100,
        GetIniFileName());
    if (pOptions->m_nVolumeSFX > 100) {
        pOptions->m_nVolumeSFX = 100;
    }

    m_pObjectGame->ApplyVolumeSliders(TRUE);

    pOptions->m_nShadedSelectionBox = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SHADED_SELECTION_BOX_KEY,
        0,
        GetIniFileName());
    if (pOptions->m_nShadedSelectionBox != 0 && pOptions->m_nShadedSelectionBox != 1) {
        pOptions->m_nShadedSelectionBox = 0;
    }

    pOptions->m_bDisplayMovieSubtitles = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_MOVIE_SUBTITLES_KEY,
        0,
        GetIniFileName());

    g_pChitin->field_1C4C = GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        SINGLE_MEDIA_KEY,
        0,
        GetIniFileName());
}

// 0x424FF0
void CBaldurChitin::PreLoadFonts()
{
    field_4A34.SetResRef(CResRef("NORMAL"), 0, 1);
    field_4A34.SetColor(0xFFFFFF, 0, 0);
    field_4A34.RegisterFont();
}

// 0x425040
void CBaldurChitin::SaveOptions()
{
    CGameOptions* pOptions = &(m_pObjectGame->m_cOptions);
    CString sString;

    if (m_bFullscreen) {
        SaveBitsPerPixel(cVideo.m_nBpp);
    } else {
        RECT rect;
        GetWindowRect(GetWnd()->GetSafeHwnd(), &rect);

        m_ptScreen.x = rect.left;
        m_ptScreen.y = rect.top;

        sString.Format("%d", m_ptScreen.x);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            SCREEN_POSITION_X_KEY,
            sString,
            GetIniFileName());

        sString.Format("%d", m_ptScreen.y);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            SCREEN_POSITION_Y_KEY,
            sString,
            GetIniFileName());
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        FONT_NAME_KEY,
        m_sFontName,
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DOUBLE_BYTE_CHARACTER_SUPPORT_KEY,
        field_1A0 ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        IS_3D_ACCELERATED,
        cVideo.m_bIs3dAccelerated ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SIXTEEN_BIT_TEXTURES_KEY,
        field_2F4 ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", CVideo::FPS);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_FREQUENCY_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CVideo::SCREENWIDTH);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        RESOLUTION_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CChitin::TIMER_UPDATES_PER_SECOND);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        MAXIMUM_FRAME_RATE_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CSearchRequest::MAXNODES);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        PATH_SEARCH_NODES_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nTooltips);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        TOOLTIPS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nTranslucentShadows);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        TRANSLUCENT_SHADOWS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", CGameAnimationType::MIRROR_BAM);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SPRITE_MIRROR_KEY,
        sString,
        GetIniFileName());

    if (CVidMode::bInitialized) {
        sString.Format("%d", GetCurrentVideoMode()->m_nGammaCorrection);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            GAMMA_CORRECTION_KEY,
            sString,
            GetIniFileName());

        sString.Format("%d", GetCurrentVideoMode()->m_nBrightnessCorrection);
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BRIGHTNESS_CORRECTION_KEY,
            sString,
            GetIniFileName());
    }

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        BACKWARDS_COMPATIBLE_3D_KEY,
        cVideo.field_13A ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeMovie);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MOVIE_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeMusic);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_MUSIC_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeVoices);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_VOICES_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeAmbients);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_AMBIENTS_KEY,
        sString,
        GetIniFileName());

    sString.Format("%d", pOptions->m_nVolumeSFX);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        VOLUME_SFX_KEY,
        sString,
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_FAST_KEY,
        cVideo.cVidBlitter.m_bSoftSrcKeyBltFast ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_FAST_KEY,
        cVideo.cVidBlitter.m_bSoftBltFast ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_SRC_KEY_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftSrcKeyBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SOFT_MIRROR_BLT_KEY,
        cVideo.cVidBlitter.m_bSoftMirrorBlt ? "1" : "0",
        GetIniFileName());

    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        DISPLAY_MOVIE_SUBTITLES_KEY,
        pOptions->m_bDisplayMovieSubtitles ? "1" : "0",
        GetIniFileName());

    sString.Format("%d", pOptions->m_nShadedSelectionBox);
    WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
        SHADED_SELECTION_BOX_KEY,
        sString,
        GetIniFileName());
}

// 0x425680
void CBaldurChitin::SaveBitsPerPixel(USHORT nBpp)
{
    switch (nBpp) {
    case 16:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "16",
            GetIniFileName());
        break;
    case 24:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "24",
            GetIniFileName());
        break;
    case 32:
        WritePrivateProfileStringA(PROGRAM_OPTIONS_SECTION_KEY,
            BITS_PER_PIXEL_KEY,
            "32",
            GetIniFileName());
        break;
    }
}

// 0x425710
void CBaldurChitin::SetProgressBar(BOOLEAN bEnabled, LONG nProgressBarCaption, INT nBytesCopied, INT nTotalBytes, BOOLEAN bTravel, LONG nParchmentCaption, BOOLEAN bWaiting, LONG nWaitingReason, BOOLEAN bDisplayMinibars, BOOLEAN bTimeoutCounter, DWORD nSecondsToTimeout)
{
    if (bEnabled == TRUE) {
        g_pChitin->cProgressBar.m_bProgressBarActivated = TRUE;
        g_pChitin->cProgressBar.m_bTravelActive = bTravel;
    }

    m_cCachingStatus.Update(bEnabled,
        nProgressBarCaption,
        nBytesCopied,
        nTotalBytes,
        bTravel,
        nParchmentCaption,
        bWaiting,
        nWaitingReason,
        bDisplayMinibars,
        bTimeoutCounter,
        nSecondsToTimeout);

    if (bEnabled == FALSE) {
        g_pChitin->cProgressBar.Initialize();
        g_pChitin->cProgressBar.m_bProgressBarActivated = FALSE;
        g_pChitin->cProgressBar.m_bTravelActive = bTravel;
    }
}

// 0x4258C0
void CBaldurChitin::OnMultiplayerSessionToClose()
{
    m_cBaldurMessage.m_bMultiplayerSessionShutdown = TRUE;
}

// 0x422C60
BOOL CBaldurChitin::FontRectOutline()
{
    return m_bFontRectOutline;
}

// 0x422C60
UINT CBaldurChitin::GetSavedBitsPerPixel()
{
    return GetPrivateProfileIntA(PROGRAM_OPTIONS_SECTION_KEY,
        BITS_PER_PIXEL_KEY,
        CVideo::word_85DE2C,
        GetIniFileName());
}

// 0x425BD0
void CBaldurChitin::ClearChatMessages()
{
    m_cBaldurMessage.m_cChatBuffer.ClearMessages();

    if (m_pEngineWorld != NULL) {
        m_pEngineWorld->ClearChatMessages();
    }

    if (m_pEngineMultiPlayer != NULL) {
        m_pEngineMultiPlayer->ClearChatMessages();
    }

    if (m_pEngineWorldMap != NULL) {
        m_pEngineWorldMap->ClearChatMessages();
    }
}

// 0x425CA0
CBaldurMessage* CBaldurChitin::GetBaldurMessage()
{
    return &m_cBaldurMessage;
}

// 0x425FB0
void CBaldurChitin::SynchronousUpdate()
{
    CChitin::SynchronousUpdate();
}

// 0x4268F0
void CBaldurChitin::AddPlayedMovie(const CResRef& cResMovie)
{
    CString sRes;
    cResMovie.CopyToString(sRes);
    WritePrivateProfileStringA("Movies", sRes, "1", GetIniFileName());
}

// 0x426970
void CBaldurChitin::GetGameSpyCode(CString& sGameSpyCode)
{
    sGameSpyCode = "";

    for (int k = 0; k < 6; k++) {
        sGameSpyCode += static_cast<char>(CBaldurChitin::BALDUR_GAMESPY_CODE1[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE2[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE3[k]
            ^ CBaldurChitin::BALDUR_GAMESPY_CODE4[k]);
    }
}

// 0x426EC0
WORD CBaldurChitin::GetMultiplayerDirectPlayPort()
{
    return GetPrivateProfileIntA("Multiplayer", "Port", 0, GetIniFileName());
}

// 0x426EE0
WORD CBaldurChitin::GetMultiplayerGameSpyPort()
{
    if (GetPrivateProfileIntA("GameSpy", "Enabled", 0, GetIniFileName()) != 1) {
        return 0;
    }

    return GetPrivateProfileIntA("GameSpy", "Port", 0, GetIniFileName());
}

// 0x4D26B0
CInfCursor* CBaldurChitin::GetObjectCursor()
{
    return m_pObjectCursor;
}
